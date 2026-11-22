#include "ProjectionMultivues.hpp"
#include "XACamera.hpp"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include "eigen-5.0.0/eigen5/Eigen/Dense"
#include <iostream>
#include <vector>
using namespace std;

Point3D ProjectionMultivues::triangulatePoint(
    const std::vector<XACamera>& cameras, 
    const std::vector<Point2D>& observations
) {
    //on a mis un size_t parce que c'est un type non signé et qu'il est plus approprié pour les tailles de conteneurs
    //Onpeut aussi utiliser int mais size_t est plus sûr pour éviter les problèmes de dépassement de capacité
    size_t nbr_vues = cameras.size();
    //On doit au moins 2 vues pour trianguler un point 3D
    //cette boucle permet de vérifier que le nombre de vues est au moins 2 et que le nombre d'observations correspond au nombre de caméras
    if (nbr_vues < 2 || nbr_vues != observations.size()) {
        throw std::invalid_argument("Il faut au moins 2 vues et autant d'observations 2D que de caméras !");
    }

    // Chaque vue apporte 2 lignes d'équations, donc la matrice A aura (2 * nbr_vues) lignes et 4 colonnes
    Eigen::MatrixXd A(2 * nbr_vues, 4);
    for (size_t i = 0; i < nbr_vues; ++i) {
        // Récupération de la matrice de projection P (3x4) de la vue i
        Eigen::Matrix<double, 3, 4> P = cameras[i].getMatriceProjection();
        // Récupération des coordonnées 2D observées (u, v) pour la vue i
        double u = observations[i].u;
        double v = observations[i].v;

        // 2. Extraction des lignes de la matrice P
        Eigen::Vector4d p1 = P.row(0);
        Eigen::Vector4d p2 = P.row(1);
        Eigen::Vector4d p3 = P.row(2);

        // 3. Remplissage des 2 lignes correspondantes dans la matrice A
        // Ligne 1 : u * p3 - p1
        A.row(2 * i)     = u * p3 - p1;
        // Ligne 2 : v * p3 - p2
        A.row(2 * i + 1) = v * p3 - p2;
    }

    // 4. Résolution par SVD (Décomposition en Valeurs Singulières)
    // Eigen::ComputeFullV permet de récupérer toute la matrice V
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullV);

    // Le point 3D homogène correspond à la dernière colonne de la matrice V
    Eigen::Vector4d X_homogene = svd.matrixV().col(3);

    // 5. Normalisation (division par la composante homogène W / X_homogeneous[3])
    Point3D pt3D;
    if (std::abs(X_homogene[3]) > 1e-12) {
        pt3D.x = X_homogene[0] / X_homogene[3];
        pt3D.y = X_homogene[1] / X_homogene[3];
        pt3D.z = X_homogene[2] / X_homogene[3];
    } else {
        // Sécurité en cas de point à l'infini
        pt3D.x = X_homogene[0];
        pt3D.y = X_homogene[1];
        pt3D.z = X_homogene[2];
    }

    return pt3D;
}


