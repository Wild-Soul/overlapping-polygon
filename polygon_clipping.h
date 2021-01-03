#include <vector>
#include "point.h"
#include <cmath>

using namespace std;

// check if a point is on the LEFT side of an edge
bool inside(point p, point p1, point p2)
{
    return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) <= 0;
}

// calculate intersection point
point intersection(point cp1, point cp2, point s, point e)
{
    point dc = point( cp1.x - cp2.x, cp1.y - cp2.y );
    point dp = point( s.x - e.x, s.y - e.y );
 
    float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
    float n2 = s.x * e.y - s.y * e.x;
    float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
 
    return point( (n1 * dp.x - n2 * dc.x) * n3, (n1 * dp.y - n2 * dc.y) * n3 );
}


double polygonArea(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}

// Sutherland-Hodgman clipping
vector<point> SutherlandHodgman(vector<point>& subjectPolygon, vector<point>& clipPolygon) {
    
    int subjectPolygonSize = subjectPolygon.size();
    int clipPolygonSize = clipPolygon.size();

    point cp1, cp2, s, e;
    vector<point> inputPolygon, newPolygon;
    
    for(int i = 0; i < subjectPolygonSize; i++)
        newPolygon.push_back(subjectPolygon[i]);
 
    int newPolygonSize = subjectPolygonSize;
 
    for(int j = 0; j < clipPolygonSize; j++)
    {
        for(int k = 0; k < newPolygonSize; k++){ inputPolygon.push_back(newPolygon[k]); }
        newPolygon.clear();
        int counter = 0;
        cp1 = clipPolygon[j];
        cp2 = clipPolygon[(j + 1) % clipPolygonSize];
 
        for(int i = 0; i < newPolygonSize; i++)
        {
            s = inputPolygon[i];
            e = inputPolygon[(i + 1) % newPolygonSize];
            
            // Case 1: Both the vertex are inside.
            if(inside(s, cp1, cp2) && inside(e, cp1, cp2))
                newPolygon.push_back(e);
 
            // Case 2: First vertex is outside while second one is inside:
            // Both the point of intersection of the edge with the clip boundary
            // and the second vertex are added to the output list
            else if(!inside(s, cp1, cp2) && inside(e, cp1, cp2))
            {
                newPolygon.push_back(intersection(cp1, cp2, s, e));
                newPolygon.push_back(e);
            }
 
            // Case 3: First vertex is inside while second one is outside:
            // Only the point of intersection of the edge with the clip boundary
            // is added to the output list
            else if(inside(s, cp1, cp2) && !inside(e, cp1, cp2))
                newPolygon.push_back(intersection(cp1, cp2, s, e));
 
            // Case 4: Both vertices are outside
            else if(!inside(s, cp1, cp2) && !inside(e, cp1, cp2))
            {
                // No vertices are added to the output list
            }
        }
        // set new polygon size
        newPolygonSize = newPolygon.size();
    }

    cout << "Clipped polygon points:" << endl;
    for(int i = 0; i < newPolygonSize; i++)
        cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;

    cout << polygonArea(newPolygon) << endl;
    return newPolygon;
}