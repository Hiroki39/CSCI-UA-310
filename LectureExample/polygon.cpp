#include "polygon.hpp"
using namespace std;

vector<point> monotone_chain(vector<point> points) {
    // assume that no three are collinear
    if (points.size() < 3) {
        throw invalid_argument("Only accept 3 or more points");
    }

    sort(points.begin(), points.end(), xComp());

    vector<point> hull;
    for (size_t i = 0; i < points.size(); i++) {
        while (hull.size() >= 2 && sideOfLine(hull[hull.size() - 2], points[i],
                                              hull[hull.size() - 1]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    for (int i = points.size() - 2, upper_size = hull.size() + 1; i >= 0; i--) {
        while (hull.size() >= upper_size &&
               sideOfLine(hull[hull.size() - 2], points[i],
                          hull[hull.size() - 1]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}

double perimeter(const std::vector<point>& polygon) {
    double total = 0.0;
    for (size_t i = 0; i < polygon.size(); i++)
        total += dist(polygon[i], polygon[(i + 1) % polygon.size()]);
    return total;
}

int is_convex(const std::vector<point>& polygon) {
    int conv = 0, coll = 0, conc = 0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        double theta =
            angle(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);
        if (fabs(theta - pi) < eps)
            coll++;
        else if (theta < pi)
            conv++;
        else
            conc++;
    }
    if (conc > 0)
        return -1;
    else if (coll > 0)
        return 0;
    return 1;
}

double area(const std::vector<point>& polygon) {
    double total = 0.0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) total += trap(polygon[i], polygon[(i + 1) % n]);
    return fabs(total);
}
