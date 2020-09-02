#include <iostream>
#include "closest_pair.hpp"
using namespace std;

int main() {
    pair<point, point> pair =
        closest_pair({point(0, 1), point(1, 0), point(2, 0)});
    cout << pair.first << " " << pair.second << endl;
}
