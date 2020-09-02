#include "closest_pair.hpp"
using namespace std;

pair<point, point> closest_pair_helper(ptIter start, ptIter end, ptIter temp) {
    int n = end - start;
    if (n <= 20) {
        double minDist = inf;
        point a;
        point b;
        for (ptIter i = start; i != end; i++)
            for (ptIter j = i + 1; j != end; j++) {
                double currDist = dist(*i, *j);
                if (currDist < minDist) {
                    minDist = currDist;
                    a = *i;
                    b = *j;
                }
            }
        sort(start, end, yComp());
        return make_pair(a, b);
    }
    ptIter mid = start + (n / 2);
    auto lpair = closest_pair_helper(start, mid, temp);
    auto rpair = closest_pair_helper(mid, end, temp + (n / 2));
    merge(start, mid, mid, end, temp, yComp());
    copy(temp, temp + n, start);
    double stripSize;
    point a, b;
    if (dist(lpair.first, lpair.second) < dist(rpair.first, rpair.second)) {
        a = lpair.first, b = lpair.second;
        stripSize = dist(lpair.first, lpair.second);
    } else {
        a = rpair.first, b = rpair.second;
        stripSize = dist(rpair.first, rpair.second);
    }
    double midX = (*mid).x();
    int cnt = 0;
    ptIter aux = temp;
    for (ptIter i = start; i != end; i++)
        if ((*i).x() >= midX - 2 * stripSize &&
            (*i).x() <= midX + 2 * stripSize)
            *(aux++) = *i, cnt++;
    for (ptIter i = temp; i != temp + cnt; i++)
        for (ptIter j = i + 1;
             j != temp + cnt && (*j).y() - (*i).y() <= stripSize; j++) {
            double currDist = dist(*i, *j);
            if (currDist < stripSize) {
                stripSize = currDist;
                a = *i, b = *j;
            }
        }
    return make_pair(a, b);
}

pair<point, point> closest_pair(std::vector<point> points) {
    std::vector<point> temp(points.size(), point(0, 0));
    sort(points.begin(), points.end(), xComp());
    return closest_pair_helper(points.begin(), points.end(), temp.begin());
}
