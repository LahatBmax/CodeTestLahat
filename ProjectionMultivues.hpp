#ifndef ProjectionMultivues_hpp
#define ProjectionMultivues_hpp
#include "eigen-5.0.0/eigen5/Eigen/Dense"
#include <vector>
#include "XACamera.hpp" // Contient tes structures Point3D, Point2D et ta classe XACameraView

class ProjectionMultivues {
public:
    // Méthode pour trianguler un point 3D à partir de plusieurs vues et de leurs observations 2D
    // cameras : vecteur de caméras (XACamera)
    // observations : vecteur de points 2D correspondants aux observations dans chaque caméra
    static Point3D triangulatePoint(
        const std::vector<XACamera>& cameras, 
        const std::vector<Point2D>& observations
    );
};

#endif // ProjectionMultivues_hpp 