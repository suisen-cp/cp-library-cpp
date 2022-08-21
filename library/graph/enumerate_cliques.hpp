#ifndef SUISEN_ENUMERATE_CLIQUES
#define SUISEN_ENUMERATE_CLIQUES

#include <algorithm>
#include <vector>

namespace suisen {
    /**
     * Type Parameters
     * - CliqueComsumer : type of consumer function std::vector<int> -> void
     * 
     * Parameters
     * - std::vector<std::vector<int>> g : simple undirected graph
     * - CliqueComsumer fun
     * 
     * Requirements
     * - v in g[u] <=> u in g[v]
     * 
     * Complexity
     * - time : O(2^sqrt(2M) * N + (sum of size of cliques)) = O(2^sqrt(2M) * N * sqrt(2M)) ?
     * - space : O(N + M)
     */
    template <typename CliqueComsumer>
    void enumerate_cliques(std::vector<std::vector<int>> g, CliqueComsumer &&fun) {
        const int n = g.size();
        // sort by degree
        std::vector<int> ord(n), idx(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](int i, int j) { return g[i].size() < g[j].size(); });
        for (int i = 0; i < n; ++i) idx[ord[i]] = i;
        for (int i = 0; i < n; ++i) {
            g[i].erase(std::remove_if(g[i].begin(), g[i].end(), [&](int j) { return idx[j] < idx[i]; }), g[i].end());
            std::sort(g[i].begin(), g[i].end(), [&](int x, int y) { return idx[x] < idx[y]; });
        }

        std::vector<int> id(n, -1), inv_id(n);
        std::vector<int> clique(n);
        for (int i : ord) {
            const int l = g[i].size();
            for (int p = 0; p < l; ++p) {
                int j = g[i][p];
                inv_id[id[j] = p] = j;
            }
            std::vector<int> st(l);
            for (int p = 0; p < l; ++p) {
                st[p] = (1 << (p + 1)) - 1;
                for (int j : g[g[i][p]]) if (int k = id[j]; k >= 0) st[p] |= 1 << k;
            }
            std::vector<int>::iterator it = clique.begin();
            *it++ = i;
            fun(std::vector<int>(clique.begin(), it));
            std::vector<int> intersec(l, (1 << l) - 1);
            for (int c = 1; c < 1 << l; ++c) {
                const int k = __builtin_ctz(c);
                std::fill(intersec.begin(), intersec.begin() + k, intersec[k] &= st[k]);
                *(it -= k)++ = inv_id[k];
                if ((intersec[0] & c) == c) fun(std::vector<int>(clique.begin(), it));
            }
            for (int j : g[i]) id[j] = -1;
        }
    }
} // namespace suisen

#endif // SUISEN_ENUMERATE_CLIQUES