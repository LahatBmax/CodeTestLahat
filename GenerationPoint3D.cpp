#include "GenerationPoint3D.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

void GenerationPoint3D::genererBifurcation() {
    points.clear();

    // Branche principale
    points.push_back({"P0", Eigen::Vector3d(-40.0,  0.0,  0.0), "main"});
    points.push_back({"P1", Eigen::Vector3d(-30.0,  2.0,  1.0), "main"});
    points.push_back({"P2", Eigen::Vector3d(-20.0,  4.0,  2.0), "main"});
    points.push_back({"P3", Eigen::Vector3d(-10.0,  3.0,  4.0), "main"});

    // Point de bifurcation
    points.push_back({"B",  Eigen::Vector3d(  0.0,  0.0,  5.0), "bifurcation"});

    // Branche 1 (gauche)
    points.push_back({"L1", Eigen::Vector3d( 10.0,  8.0,  8.0), "left"});
    points.push_back({"L2", Eigen::Vector3d( 20.0, 15.0, 12.0), "left"});
    points.push_back({"L3", Eigen::Vector3d( 30.0, 20.0, 15.0), "left"});

    // Branche 2 (droite)
    points.push_back({"R1", Eigen::Vector3d(  8.0, -8.0,  7.0), "right"});
    points.push_back({"R2", Eigen::Vector3d( 18.0, -15.0, 10.0), "right"});
    points.push_back({"R3", Eigen::Vector3d( 28.0, -20.0, 14.0), "right"});
}

const std::vector<SyntheticPoint>& GenerationPoint3D::getPoints() const {
    return points;
}

void GenerationPoint3D::afficherPoint3D() const {
    std::cout << "Points 3D générés :\n";

    for (const auto& point : points) {
        std::cout << "ID: " << point.id << "\n"
                  << "Branche: " << point.branche << "\n"
                  << "Position: " << point.position.transpose() << "\n";
    }

}

