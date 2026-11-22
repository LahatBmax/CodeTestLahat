#ifndef XACamera_hpp
#define XACamera_hpp
#include <iostream>
#include "P_intrinseque.hpp"
#include "P_extrinseque.hpp"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include "eigen-5.0.0/eigen5/Eigen/Dense"
using namespace std;


class XACamera {

    private:
        P_intrinseque intrinseque;
        P_extrinseque extrinseque;
        public :
        //cette methode prends en parametre les parametres intrinseque et extrinseque pour creer un objet XACamera
        XACamera(double Dsd, double pixel_spacing, double cols, double ligne, double rla, double cca, double dsp);
        //on cree une matrice de projection 3x4 en multipliant la matrice K par la matrice [R|t]
        Eigen ::Matrix <double,3,4> getMatriceProjection() const;
        Point2D ProjectPoint2D( Point3D& pt3D) ;
};
 #endif // XACamera_hpp