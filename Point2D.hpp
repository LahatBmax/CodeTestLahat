#ifndef Point2D_hpp
#define Point2D_hpp


class Point2D {      
public:
   double u;
   double v;

   public :
   Point2D() : u(0.0), v(0.0) {}
   Point2D(double u, double v) : u(u), v(v) {}
   
};
#endif // Point2D_hpp