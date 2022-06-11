#ifndef SUISEN_MINIMUM_VERTEX_COVER
#define SUISEN_MINIMUM_VERTEX_COVER

#include "library/graph/maximum_independent_set.hpp"

namespace suisen {
    std::vector<int> minimum_vertex_cover(const std::vector<std::vector<int>>& g) {
        const int n = g.size();
        std::vector<int8_t> in_msi(n, false);
        for (int v : maximum_independent_set(g)) in_msi[v] = true;
        std::vector<int> res;
        for (int i = 0; i < n; ++i) if (not in_msi[i]) res.push_back(i);
        return res;
    }
} // namespace suisen

#endif // SUISEN_MINIMUM_VERTEX_COVER
