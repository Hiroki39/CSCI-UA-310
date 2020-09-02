#ifndef _CLOSEST_PAIR_
#define _CLOSEST_PAIR_

#include <algorithm>
#include <vector>
#include "point.hpp"

typedef std::vector<point>::iterator ptIter;

std::pair<point, point> closest_pair_helper(ptIter start, ptIter end,
                                            ptIter temp);

std::pair<point, point> closest_pair(std::vector<point> points);

#endif  // _CLOSEST_PAIR_
