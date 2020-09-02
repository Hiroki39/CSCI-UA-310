#ifndef _POLYGON_
#define _POLYGON_

#include <algorithm>
#include <vector>
#include "point.hpp"

std::vector<point> monotone_chain(std::vector<point> points);

double perimeter(const std::vector<point>& polygon);

int is_convex(const std::vector<point>& polygon);

double area(const std::vector<point>& polygon);

#endif  // _POLYGON_
