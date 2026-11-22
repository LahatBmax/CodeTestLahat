#include <iostream>
#include "Lire_jason.hpp"
#include "XACamera.hpp"
#include "P_intrinseque.hpp"
#include "P_extrinseque.hpp"
#include "ProjectionMultivues.hpp"
#include "GenerationPoint3D.hpp"
#include  "eigen-5.0.0/eigen5/Eigen/Dense"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include <filesystem>
#include <string>
#include <fstream>
#include "json.hpp" 
using namespace std;




nlohmann::json Lire_fichier_json();

int main() {
    const int nb_vues = 5;
    std::vector<XACamera> cameras;
    cameras.reserve(nb_vues);

    std::cout << "--- Chargement des " << nb_vues << " vues ---\n";
    for (int i = 0; i < nb_vues; ++i) {
        std::cout << "\nVue numero " << (i + 1) << " :\n";
        nlohmann::json data = Lire_fichier_json();

        double sid           = std::stod(data["DistanceSourceToDetector"].get<std::string>());
        double pixel_spacing = std::stod(data["ImagerPixelSpacingX"].get<std::string>());
        double cols          = std::stod(data["Columns"].get<std::string>());
        double rows          = std::stod(data["Rows"].get<std::string>());
        double rla           = std::stod(data["PositionerPrimaryAngle"].get<std::string>());
        double cca           = std::stod(data["PositionerSecondaryAngle"].get<std::string>());
        double sod           = std::stod(data["DistanceSourceToPatient"].get<std::string>());

        cameras.emplace_back(sid, pixel_spacing, cols, rows, rla, cca, sod);
    }

    // Generation des points 3D synthetiques de la bifurcation
    GenerationPoint3D synth;
    synth.genererBifurcation();
    synth.afficherPoint3D();

    double somme_erreur_3d = 0.0;

    std::cout << "\n=== TEST PROJECTION (3D -> 2D) ET TRIANGULATION (2D -> 3D) ===\n";
    for (const auto& pt : synth.getPoints()) {
        Point3D pt_gt;
        pt_gt.x = pt.position.x();
        pt_gt.y = pt.position.y();
        pt_gt.z = pt.position.z();

        // 1. Projection 3D -> 2D sur chaque vue
        std::vector<Point2D> proj_2d;
        proj_2d.reserve(cameras.size());
        for ( auto& cam : cameras) {
            proj_2d.push_back(cam.ProjectPoint2D(pt_gt));
        }

        // 2. Triangulation 2D -> 3D a partir des points projetes
        Point3D pt_rec = ProjectionMultivues::triangulatePoint(cameras, proj_2d);

        double dx = pt_rec.x - pt_gt.x;
        double dy = pt_rec.y - pt_gt.y;
        double dz = pt_rec.z - pt_gt.z;
        double err_3d = std::sqrt(dx * dx + dy * dy + dz * dz);
        somme_erreur_3d += err_3d;

        std::cout << "\nPoint " << pt.id << " (" << pt.branche << ") :\n"
                  << "  GT 3D  : (" << pt_gt.x << ", " << pt_gt.y << ", " << pt_gt.z << ")\n"
                  << "  Rec 3D : (" << pt_rec.x << ", " << pt_rec.y << ", " << pt_rec.z << ")\n"
                  << "  Erreur 3D : " << err_3d << " mm\n";
    }

    if (!synth.getPoints().empty()) {
        std::cout << "\nErreur 3D moyenne sur la bifurcation : "
                  << (somme_erreur_3d / synth.getPoints().size()) << " mm\n";
    }

    return 0;
}