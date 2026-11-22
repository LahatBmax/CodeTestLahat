#include <vector>
#include <iostream>
using namespace std;
#include "eigen-5.0.0/eigen5/Eigen/Dense"
#ifndef P_extrinseque_hpp
#define P_extrinseque_hpp
class P_extrinseque {

     protected: 
     double Rla ;
     double Cca ;
     double Dsp ;

     
    public:
    P_extrinseque(double Rla, double Cca, double Dsp);
    Eigen::Matrix3d MatriceRotation() const ;
    Eigen::Vector3d vecteurTranslation() const ;
};
#endif // P_extrinseque_hpp