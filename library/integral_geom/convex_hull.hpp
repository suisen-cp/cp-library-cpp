#ifndef SUISEN_CONVEX_HULL_INTEGRAL
#define SUISEN_CONVEX_HULL_INTEGRAL

#include <algorithm>
#include <numeric>
#include <vector>

namespace suisen::integral_geometry {
    template <typename PointType, typename MultipliedType = long long>
    std::vector<int> convex_hull(const std::vector<PointType> &points) {
        const int n = points.size();
        std::vector<int> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j) {
            const auto &[xi, yi] = points[i];
            const auto &[xj, yj] = points[j];
            return xi == xj ? yi < yj : xi < xj;
        });
        std::vector<int8_t> used(n, false);
        sorted.resize(2 * n - 1);
        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);
        std::vector<int> res;
        res.reserve(n);
        int first = sorted[0], last = sorted[n - 1];
        auto isp_pos = [](MultipliedType x1, MultipliedType y1, MultipliedType x2, MultipliedType y2) -> bool {
            auto det = x1 * y2 - y1 * x2;
            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);
        };
        for (int k : sorted) {
            if (k != first and used[k]) continue;
            for (int sz = res.size(); sz >= 2; --sz) {
                int i = res[sz - 2], j = res[sz - 1];
                if (j == last) break;
                const auto &[xi, yi] = points[i];
                const auto &[xj, yj] = points[j];
                const auto &[xk, yk] = points[k];
                auto ab_x = xj - xi, ab_y = yj - yi;
                auto bc_x = xk - xj, bc_y = yk - yj;
                if (isp_pos(ab_x, ab_y, bc_x, bc_y)) break;
                res.pop_back(), used[j] = false;
            }
            if (not used[k]) res.push_back(k);
            used[k] = true;
        }
        return res;
    }
} // namespace suisen::integral_geometry

#endif // SUISEN_CONVEX_HULL_INTEGRAL
