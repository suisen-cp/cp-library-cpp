#ifndef SUISEN_FARTHEST_PAIR
#define SUISEN_FARTHEST_PAIR

#include <cassert>

#include "library/integral_geom/geometry.hpp"
#include "library/integral_geom/convex_hull.hpp"

namespace suisen::integral_geometry {
    template <typename PointType, typename MultipliedType = long long>
    std::pair<PointType, PointType> farthest_pair(const std::vector<PointType> &points) {
        const std::vector<int> ids = convex_hull<PointType, MultipliedType>(points);
        const int n = ids.size();
        Polygon convex(n);
        for (int i = 0; i < n; ++i) convex[i] = points[ids[i]];
        auto [i, j] = convex_diameter(convex);
        return { PointType{ convex[i] }, PointType{ convex[j] } };
    }
} // namespace suisen::integral_geometry

#endif // SUISEN_FARTHEST_PAIR
