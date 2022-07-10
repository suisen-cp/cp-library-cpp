#ifndef SUISEN_SORT_POINTS_BY_ARGUMENT
#define SUISEN_SORT_POINTS_BY_ARGUMENT

#include <algorithm>
#include <vector>

#include "library/integral_geom/point.hpp"

namespace suisen::integral_geometry {
    /**
     * 1. (x < 0, y = 0) -> pi
     * 2. (x = 0, y = 0) -> 0
     * 3. points with same argument -> arbitrary order
     */
    template <typename PointType, typename MultipliedType = long long>
    bool compare_by_atan2(const PointType &p, const PointType &q) {
        const auto &[x1, y1] = p;
        const auto &[x2, y2] = q;
        if ((y1 < 0) xor (y2 < 0)) return y1 < y2;
        if ((x1 < 0) xor (x2 < 0)) return (y1 >= 0) xor (x1 < x2);
        if (x1 == 0 and y1 == 0) return true;
        if (x2 == 0 and y2 == 0) return false;
        return (MultipliedType(y1) * x2 < MultipliedType(y2) * x1);
    }
    template <typename PointType, typename MultipliedType = long long>
    void sort_points_by_argument(std::vector<PointType> &points) {
        std::sort(points.begin(), points.end(), compare_by_atan2<PointType, MultipliedType>);
    }
} // namespace suisen::integral_geometry


#endif // SUISEN_SORT_POINTS_BY_ARGUMENT
