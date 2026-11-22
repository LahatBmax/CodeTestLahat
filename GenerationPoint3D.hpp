#pragma once

#include <string>
#include <vector>
#include "eigen-5.0.0/eigen5/Eigen/Dense"

struct SyntheticPoint {
    std::string id;
    Eigen::Vector3d position;
    std::string branche;
};

class GenerationPoint3D {
public:
    void genererBifurcation();
    const std::vector<SyntheticPoint>& getPoints() const;
    void afficherPoint3D() const;
   
private:
    std::vector<SyntheticPoint> points;
};