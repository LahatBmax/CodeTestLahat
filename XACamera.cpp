#include "XACamera.hpp"
#include "P_intrinseque.hpp"
#include "P_extrinseque.hpp"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include "eigen-5.0.0/eigen5/Eigen/Dense"
#include <iostream>
using namespace std;


XACamera::XACamera(double Dsd, double pixel_spacing, double cols, double ligne, double rla, double cca, double dsp): 
    intrinseque(Dsd, pixel_spacing, cols, ligne),
    extrinseque(rla, cca, dsp)
{
}

Eigen::Matrix<double,3,4> XACamera::getMatriceProjection() const {
    Eigen::Matrix3d K = intrinseque.getMatrix_K();
    Eigen::Matrix3d R = extrinseque.MatriceRotation();
    Eigen::Vector3d t = extrinseque.vecteurTranslation();

    // Construction de la matrice extrinsèque [R | t] 
    Eigen::Matrix<double, 3, 4> Rt;
    //https://libeigen.gitlab.io/eigen/docs-5.0/group__TutorialBlockOperations.html
    // on a .block<ligne , colonne>(ligne_debut, colonne_debut) pour selectionner un bloc de la matrice
    Rt.block<3, 3>(0, 0) = R;

    //ici on selectionne la colonne 3 de la matrice Rt et on lui affecte le vecteur t
    Rt.col(3) = t;

    // Matrice de projection globale P = K * [R | t] 
    Eigen::Matrix<double, 3, 4> P = K * Rt;
    return P;
}

// a revoir 
Point2D XACamera::ProjectPoint2D(Point3D& pt3D){
    Eigen::Matrix<double, 3, 4> P = getMatriceProjection();

    // Point 3D en coordonnées homogènes 
    Eigen::Vector4d X_h(pt3D.x, pt3D.y, pt3D.z, 1.0);

    // Projection 2D homogène
    Eigen::Vector3d p_prime = P * X_h;
    // Normalisation par w'
    Point2D pt2D;
    pt2D.u = p_prime[0] / p_prime[2];
    pt2D.v = p_prime[1] / p_prime[2];

    return pt2D;
}
