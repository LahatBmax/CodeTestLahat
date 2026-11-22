#include <iostream>
#include "P_intrinseque.hpp"
#include <vector>
using namespace std;


P_intrinseque::P_intrinseque(double Dsd, double PixelSpacing, double col, double ligne) {
    fx = Dsd / PixelSpacing;
    fy = Dsd / PixelSpacing;
    cx = col / 2.0;
    cy = ligne / 2.0;
}

Eigen::Matrix3d P_intrinseque::getMatrix_K() const {

    Eigen::Matrix3d K;
    K << fx, 0.0, cx,
         0.0, fy, cy,
         0.0, 0.0, 1.0;
    return K;
    
    }
    