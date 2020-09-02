#include "point.hpp"
using namespace std;

bool xComp::operator()(const point& a, const point& b) {
    if (fabs(a.x() - b.x()) < eps) return a.y() < b.y();
    return a.x() < b.x();
}

bool yComp::operator()(const point& a, const point& b) {
    if (fabs(a.y() - b.y()) < eps) return a.x() < b.x();
    return a.y() < b.y();
}

double dot(const point& a, const point& b) { return x(conj(a) * b); }

double cross(const point& a, const point& b) { return y(conj(a) * b); }

double length(const point& a) { return sqrt(dot(a, a)); }

void normalize(point& a) {
    double lgt = length(a);
    if (lgt > eps) a /= lgt;
}

double dist(const point& a, const point& b) { return length(a - b); }

double angle(const point& a, const point& b, const point& c) {
    // should check if none of the points are same before calling
    // Angle ABC, in this order
    double theta = arg(c - b) - arg(a - b);
    if (theta < 0) theta += 2.0 * pi;
    return theta;
}

point rotateAt(const point& a, const point& b, double t) {
    return a + (b - a) * std::polar(1.0, t);
}

point rotate(const point& a, double t) {
    return rotateAt(a, point(0.0, 0.0), t);
}

point reflect(const point& a, const point& b, const point& p) {
    point z = p - a;
    point w = b - a;
    return conj(z / w) * w + a;
}

bool intersect(const point& a, const point& b, const point& p, const point& q,
               point& z) {
    double d1 = cross(p - a, b - a);
    double d2 = cross(q - a, b - a);
    if (fabs(d1 - d2) < eps) {
        z = point(inf, inf);
        return false;
    }
    z = (d1 * q - d2 * p) / (d1 - d2);
    return true;
}

bool do_segments_intersect(const point& a, const point& b, const point& p,
                           const point& q) {
    point z;
    intersect(a, b, p, q, z);
    if (z.x() != inf) {
        double t = (length(z - b) + length(z - a)) / length(a - b);
        if (fabs(t - 1.0) < eps) return true;
    }
    return false;
}

void perp_bisector(const point& a, const point& b, point& p, point& q) {
    p = (a + b) / 2.0;
    q = rotateAt(p, b, pi / 2.0);
}

void angle_bisector(const point a, const point b, const point c, point& p,
                    point& q) {
    double theta = angle(a, b, c);
    p = b;
    q = rotateAt(b, a, theta / 2.0);
}

point projectAt(const point& a, const point& b, const point& p) {
    return a + (b - a) * dot(p - a, b - a) / length(b - a);
}

point project(const point& p, const point& a) {
    return projectAt(point(0.0, 0.0), a, p);
}

int sideOfLine(const point& a, const point& b, const point& p) {
    // returns which side p is of the line a->b
    double theta = angle(a, b, p);
    if (fabs(theta) < eps || fabs(theta - pi) < eps)
        return 0;
    else if (theta > pi)
        return 1;  // to the left
    return -1;     // on the right
}

double trap(const point& a, const point& b) {
    return (b.x() - a.x()) * (b.y() + a.y()) / 2;
}

double triangle_area(const point& a, const point& b, const point& c) {
    return fabs(trap(a, b) + trap(b, c) + trap(c, a));
}

double height(const point& a, const point& b, const point& p) {
    return triangle_area(a, b, p) / dist(a, b) * 2.0;
}

point closest_segment(const point& a, const point& b, const point& p) {
    point q = projectAt(a, b, p);
    double t = x((q - b) / (a - b));
    if (t < 0)
        return a;
    else if (t > 1)
        return b;
    return q;
}

bool orthocenter(const point& a, const point& b, const point& c, point& h) {
    if (triangle_area(a, b, c) < eps) {
        h = point(inf, inf);
        return false;
    }
    point p = closest_segment(b, c, a);
    point q = closest_segment(a, c, b);
    return intersect(a, p, b, q, h);
}
