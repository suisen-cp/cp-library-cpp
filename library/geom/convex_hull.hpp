#ifndef SUISEN_CONVEX_HULL
#define SUISEN_CONVEX_HULL

#include <numeric>

#include "library/geom/geometry.hpp"

namespace suisen {
namespace geometry {
    std::vector<int> convex_hull(const std::vector<Point> &points) {
        const int n = points.size();
        std::vector<int> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j) {
            auto &a = points[i], &b = points[j];
            return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();
        });
        std::vector<char> used(n, false);
        sorted.resize(2 * n - 1);
        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);
        std::vector<int> res;
        res.reserve(n);
        int first = sorted[0], last = sorted[n - 1];
        for (int k : sorted) {
            if (k != first and used[k]) continue;
            for (int sz = res.size(); sz >= 2; --sz) {
                int i = res[sz - 2], j = res[sz - 1];
                if (j == last or isp(points[i], points[j], points[k]) > 0) break;
                res.pop_back(), used[j] = false;
            }
            if (not used[k]) res.push_back(k);
            used[k] = true;
        }
        return res;
    }
}
} // namespace suisen

#endif // SUISEN_CONVEX_HULL
