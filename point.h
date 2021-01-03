#include <iostream>
#include <cmath>
using namespace std;

class point {
  public:
    //default constructor sets point to 0,0
    point() { x=0; y=0; angle = 0; }

    //manually assign point
    point(double xin, double yin) { x=xin; y=yin; angle = 0; }

    //other constructors
    point(const point &p) { x = p.x; y = p.y; angle = p.angle; }
    point &operator=(const point &p) { x = p.x; y = p.y; angle = p.angle; return *this; }


    //get angle between this point and another
    double get_angle(point &p) {
        //check to make sure the angle won't be "0"
        if(p.x == this->x) { return 0; }
        return( atan( double(p.y - this->y) / double(p.x - this->x) ) );
    }

    void set_angle(double d) { angle = d; }
    void set_dist(double d) { dist =  d; }

    double x;
    double y;
    double angle;
    double dist;
};