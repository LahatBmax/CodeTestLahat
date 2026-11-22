#include "P_extrinseque.hpp"
#include "eigen-5.0.0/eigen5/Eigen/Dense"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

P_extrinseque::P_extrinseque(double nRla, double nCca, double nDsp) {
    Rla = nRla;
    Cca = nCca;
    Dsp = nDsp;
}

// On retourne directement un Eigen::Matrix3d au lieu d'un vector<vector<double>>
Eigen::Matrix3d P_extrinseque::MatriceRotation() const {
   const double pi = std::acos(-1.0);

   
    // 1. Rla (RAO/LAO) autour de l'axe Y avec un signe négatif (a revoir )
    auto q1 = Eigen::Quaterniond(Eigen::AngleAxisd(-Rla * pi / 180.0, Eigen::Vector3d::UnitY()));
    
    // 2. Cca (Cranio-Caudal) autour de l'axe X avec un signe négatif (a revoir )
    auto q2 = Eigen::Quaterniond(Eigen::AngleAxisd(-Cca * pi / 180.0, Eigen::Vector3d::UnitX()));
    
    // Composition des quaternions
    Eigen::Matrix3d R = (q2 * q1).matrix();
    
    return R;   
    
}

// le vecteur de translation est calculé en utilisant la matrice de rotation et la distance source-patient (Dsp).
Eigen::Vector3d P_extrinseque::vecteurTranslation() const {
   // Eigen::Matrix3d R = MatriceRotation();
    
    // Position de la source dans le repère caméra le long de l'axe Z 
    Eigen::Vector3d source_camera(0.0, 0.0, -Dsp);
    
    // t = - R * source_camera
    Eigen::Vector3d t = source_camera;
    return t;
}

