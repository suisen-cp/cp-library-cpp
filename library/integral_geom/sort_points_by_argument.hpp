#ifndef SUISEN_SORT_POINTS_BY_ARGUMENT
#define SUISEN_SORT_POINTS_BY_ARGUMENT

#include <algorithm>
#include <vector>

namespace suisen::integral_geometry {
    /**
     * 1. (x < 0, y = 0) -> pi
     * 2. (x = 0, y = 0) -> 0
     * 3. points with same argument -> arbitrary order
     */
    template <typename T>
    bool compare_by_atan2(const std::pair<T, T> &p, const std::pair<T, T> &q) {
        const auto &[x1, y1] = p;
        const auto &[x2, y2] = q;
        if ((y1 < 0) xor (y2 < 0)) return y1 < y2;
        if ((x1 < 0) xor (x2 < 0)) return (y1 >= 0) xor (x1 < x2);
        if (x1 == 0 and y1 == 0) return true;
        if (x2 == 0 and y2 == 0) return false;
        return ((long long) y1 * x2 < (long long) y2 * x1);
    }
    template <typename T>
    void sort_points_by_argument(std::vector<std::pair<T, T>> &points) {
        std::sort(points.begin(), points.end(), compare_by_atan2<T>);
    }
} // namespace suisen::integral_geometry


#endif // SUISEN_SORT_POINTS_BY_ARGUMENT
