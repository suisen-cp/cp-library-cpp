#ifndef SUISEN_LCA
#define SUISEN_LCA

#include "library/algorithm/rmq_pm1_with_index.hpp"

namespace suisen {
class LowestCommonAncestor {
    public:
        LowestCommonAncestor(const std::vector<std::vector<int>> &g, int root = 0) : idx(g.size()), dep(2 * g.size() - 1), tour(2 * g.size() - 1), rmq(dfs(g, root)) {}

        int lca(int u, int v) const { return idx[u] <= idx[v] ? tour[rmq(idx[u], idx[v] + 1).second] : lca(v, u); }
        int dist(int u, int v) const { return dep[idx[u]] + dep[idx[v]] - 2 * dep[idx[operator()(u, v)]]; }
        int operator()(int u, int v) const { return lca(u, v); }
    private:
        std::vector<int> idx, dep, tour;
        RMQpm1WithIndex<true> rmq;

        std::vector<int>& dfs(const std::vector<std::vector<int>> &g, int root) {
            int k = 0;
            auto rec = [&](auto self, int u, int p, int d) -> void {
                dep[k] = d, tour[idx[u] = k++] = u;
                for (int v : g[u]) if (v != p) self(self, v, u, d + 1);
                if (p >= 0) {
                    dep[k] = d - 1, tour[idx[p] = k++] = p;
                }
            };
            rec(rec, root, -1, 0);
            return dep;
        }
};
} // namespace suisen


#endif // SUISEN_LCA
