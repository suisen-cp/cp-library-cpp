#ifndef SUISEN_CONVEX_HULL_INTEGRAL
#define SUISEN_CONVEX_HULL_INTEGRAL

#include <algorithm>
#include <numeric>
#include <vector>

namespace suisen {
namespace integral_geometry {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<int> convex_hull(const std::vector<std::pair<T, T>> &points) {
        const int n = points.size();
        std::vector<int> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j) {
            auto &a = points[i], &b = points[j];
            return a.first == b.first ? a.second < b.second : a.first < b.first;
        });
        std::vector<char> used(n, false);
        sorted.resize(2 * n - 1);
        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);
        std::vector<int> res;
        res.reserve(n);
        int first = sorted[0], last = sorted[n - 1];
        auto isp_pos = [](T x1, T y1, T x2, T y2) -> bool {
            T det = x1 * y2 - y1 * x2;
            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);
        };
        for (int k : sorted) {
            if (k != first and used[k]) continue;
            for (int sz = res.size(); sz >= 2; --sz) {
                int i = res[sz - 2], j = res[sz - 1];
                if (j == last) break;
                T ab_x = points[j].first - points[i].first, ab_y = points[j].second - points[i].second;
                T bc_x = points[k].first - points[j].first, bc_y = points[k].second - points[j].second;
                if (isp_pos(ab_x, ab_y, bc_x, bc_y)) break;
                res.pop_back(), used[j] = false;
            }
            if (not used[k]) res.push_back(k);
            used[k] = true;
        }
        return res;
    }
}
} // namespace suisen

#endif // SUISEN_CONVEX_HULL_INTEGRAL
