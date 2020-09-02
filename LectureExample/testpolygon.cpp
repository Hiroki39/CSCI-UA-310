#include <iostream>
#include "polygon.hpp"
using namespace std;

int main() {
    vector<point> pts;
    pts.emplace_back(1, 0);
    pts.emplace_back(1, 1);
    pts.emplace_back(0, 2);
    pts.emplace_back(0, 0);
    vector<point> hull = monotone_chain(pts);
    for (const point& p : hull) {
        cout << p << endl;
    }
}
