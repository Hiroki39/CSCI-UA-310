#ifndef _POINT_INCLUDED_
#define _POINT_INCLUDED_
#include <complex>
#include <limits>

typedef std::complex<double> point;
#define x(a) real(a)
#define y(a) imag(a)

const double eps = 1e-9;
const double pi = 2 * acos(0.0);
const double inf = std::numeric_limits<double>::max();

struct xComp {
    bool operator()(const point& a, const point& b);
};

struct yComp {
    bool operator()(const point& a, const point& b);
};

double dot(const point& a, const point& b);
double cross(const point& a, const point& b);
double length(const point& a);
void normalize(point& a);
double dist(const point& a, const point& b);
double angle(const point& a, const point& b, const point& c);
point rotateAt(const point& a, const point& b, double t);
point rotate(const point& a, double t);
point reflect(const point& a, const point& b, const point& p);
bool intersect(const point& a, const point& b, const point& p, const point& q,
               point& z);
bool do_segments_intersect(const point& a, const point& b, const point& p,
                           const point& q);
void perp_bisector(const point& a, const point& b, point& p, point& q);
void angle_bisector(const point a, const point b, const point c, point& p,
                    point& q);
point projectAt(const point& a, const point& b, const point& p);
point project(const point& p, const point& a);
int sideOfLine(const point& a, const point& b, const point& p);
double trap(const point& a, const point& b);
double triangle_area(const point& a, const point& b, const point& c);
double height(const point& a, const point& b, const point& p);
point closest_segment(const point& a, const point& b, const point& p);
bool orthocenter(const point& a, const point& b, const point& c, point& h);

#endif  // _POINT_INCLUDED_
