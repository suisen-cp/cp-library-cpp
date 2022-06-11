#ifndef SUISEN_MAXIMUM_CLIQUE
#define SUISEN_MAXIMUM_CLIQUE

#include "library/graph/maximum_independent_set.hpp"

namespace suisen {
    std::vector<int> maximum_clique(const std::vector<std::vector<int>>& g) {
        const int n = g.size();
        std::vector<std::vector<int>> h(n);
        for (int i = 0; i < n; ++i) {
            std::vector<int8_t> adj(n, false);
            for (int j : g[i]) adj[j] = true;
            for (int j = 0; j < n; ++j) if (not adj[j]) h[i].push_back(j);
        }
        return maximum_independent_set(h);
    }
} // namespace suisen

#endif // SUISEN_MAXIMUM_CLIQUE
