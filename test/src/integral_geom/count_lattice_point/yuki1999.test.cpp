#define PROBLEM "https://yukicoder.me/problems/no/1999"

#include <iostream>

#include "library/integral_geom/convex_hull.hpp"
#include "library/integral_geom/count_lattice_point.hpp"
#include "library/integral_geom/sort_points_by_argument.hpp"

using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point> ps;
    for (int i = 0; i < n; ++i) {
        Point p;
        std::cin >> p;
        if (p.y < 0) p.x = -p.x, p.y = -p.y;
        if (p.x or p.y) ps.push_back(p);
    }
    sort_points_by_argument(ps);

    std::vector<Point> outer{ { 0, 0 } };

    for (int lp = 0; lp < 2; ++lp) {
        Point sum{ 0, 0 };
        for (const Point &p : ps) outer.push_back(sum += p);
        std::reverse(ps.begin(), ps.end());
    }

    std::vector<Point> convex;
    for (int i : convex_hull<Point, __int128_t>(outer)) convex.push_back(outer[i]);

    std::cout << int(count_lattice_points<Point, __int128_t>(convex) % 1000000007) << std::endl;

    return 0;
}
