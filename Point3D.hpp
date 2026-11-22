#ifndef Point3D_hpp
#define Point3D_hpp

class Point3D {
public:
   double x;
   double y;
   double z;

public:
   Point3D() : x(0.0), y(0.0), z(0.0) {}
   Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

};
#endif // Point3D_hpp