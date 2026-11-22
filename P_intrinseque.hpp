#include <vector>
#include <iostream>
#include "eigen-5.0.0/eigen5/Eigen/Dense"
using namespace std;
#ifndef P_intrinseque_hpp
#define P_intrinseque_hpp

class P_intrinseque {
protected:
   double fx;
   double fy;
   double cx;
   double cy;

public:
//On a bessoin de ces parametres pour calculer la matrice K
//Ils setrouvent dans le fichier .jason 
    P_intrinseque(double Dsd, double PixelSpacing, double col, double ligne);
    Eigen::Matrix3d getMatrix_K() const;
};
#endif // P_intrinseque_hpp