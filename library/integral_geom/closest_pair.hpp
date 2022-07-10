#ifndef SUISEN_CLOSEST_PAIR
#define SUISEN_CLOSEST_PAIR

#include <cassert>

#include "library/integral_geom/geometry.hpp"

namespace suisen::integral_geometry {
    std::pair<Point, Point> closest_pair(std::vector<Point> points) {
        const int n = points.size();
        assert(n > 0);
        if (n == 1) return { points[0], points[0] };
        std::sort(points.begin(), points.end(), XY_COMPARATOR);
        coordinate_t min_dist = std::numeric_limits<coordinate_t>::max();
        std::pair<Point, Point> ans;
        std::vector<coordinate_t> dmin(n, min_dist);

        auto update_min = [&](int l, const Point& p, const Point& q) {
            coordinate_t d = square_abs(p - q);
            if (d >= dmin[l]) return;
            dmin[l] = d;
            if (d >= min_dist) return;
            min_dist = d;
            ans.first = p, ans.second = q;
        };

        static constexpr int MIN_BLOCK = 4;
        std::vector<Point> y = points;
        for (int l = 0; l < n;) {
            int r = std::min(l + MIN_BLOCK, n);
            for (int j = l; j < r; ++j) for (int i = l; i < j; ++i) {
                update_min(l, points[i], points[j]);
            }
            std::sort(y.begin() + l, y.begin() + r, YX_COMPARATOR);
            l = r;
        }

        for (int block = MIN_BLOCK; block <= n; block <<= 1) {
            for (int l = 0; l + block < n;) {
                int m = l + block, r = std::min(m + block, n);
                std::inplace_merge(y.begin() + l, y.begin() + m, y.begin() + r, YX_COMPARATOR);
                dmin[l] = std::min(dmin[l], dmin[m]);
                std::vector<int> ids;
                for (int i = l; i < r; ++i) {
                    if (coordinate_t dx = y[i].x - points[m].x; dx * dx > dmin[l]) continue;
                    for (auto it = ids.rbegin(); it != ids.rend(); ++it) {
                        const Point& p = y[*it];
                        if (coordinate_t dy = y[i].y - p.y; dy * dy > dmin[l]) break;
                        update_min(l, y[i], p);
                    }
                    ids.push_back(i);
                }
                l = r;
            }
        }
        return ans;
    }
} // namespace suisen::integral_geometry


#endif // SUISEN_CLOSEST_PAIR
