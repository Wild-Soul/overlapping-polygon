#include <iostream>
#include <unordered_set>
#include "polygon_clipping.h"
#include <algorithm>
using namespace std;

std::ostream &operator<<(std::ostream &os, const point &p) {
    os << "x: " << p.get_x() << "\ty: " << p.get_y() << "\tangle: " << p.get_angle();
    return os;
}

int main() {

    int n,m;
    double x,y;
    cout << "Number of Polygons " << endl;
    cin >> n;

    vector< vector<point> > polys(n, vector<point>());

    for(int i=0; i<n; i++) {
        cout << "Number of points in " << i << "th polygon" << endl;
        cin >> m; // Number of points in that polygon.

        double c_x=0,c_y=0;
        for(int j=0; j<m; j++) {
            cin >> x >> y;
            c_x += x;
            c_y += y;
            polys[i].push_back( point(x,y) );
        }
        point center = point(c_x/m*1.0, c_y/m*1.0);
        //Sort points in anticlockwise direction.
        for(point &p : polys[i]) {
            double angle = center.get_angle(p);
            p.set_angle(angle);
            double d = sqrt( (center.x-p.x)*(center.x-p.x)+(center.y-p.y)*(center.y-p.y) );
            p.set_dist(d);
        }
        //Precalculate and store their area.
        sort(polys[i].begin(), polys[i].end());
        // for(int j=0;  j<polys[i].size(); j++) {
        //     cout << polys[i][j]  << endl;
        // }
        // cout << "============" << endl;
    }
    
    vector<point> currentWindow = polys[0];
    for(int i=1; i<n; i++) {
        currentWindow = SutherlandHodgman(currentWindow, polys[i]);
    }

    cout << "Overlapping polygon for all the given polygons (basically overlapping area)" << endl;
    for(point p : currentWindow) {
        cout << p << endl;
    }
    return 0;
}