#ifndef SUISEN_MINMAX_FLOYD_WARSHALL
#define SUISEN_MINMAX_FLOYD_WARSHALL

#include <algorithm>
#include <cstdint>
#include <functional>
#include <tuple>
#include <vector>

#include "library/util/subset_iterator.hpp"

namespace suisen {
    // Calculates D[i][j] := min{ max{ cost(e) | e in p } | p is an i-j path } in O(N^3/w) time.
    template <typename T, typename Compare = std::less<T>>
    std::vector<std::vector<T>> minmax_floyd_warshall(const std::vector<std::vector<T>>& cost_matrix, Compare comp = {}) {
        constexpr int B = 64;
        constexpr int LOG_B = 6;
        constexpr int MASK_B = B - 1;
 
        const int n = cost_matrix.size(), m = (n + B - 1) >> LOG_B;
        std::vector G(n, std::vector<uint64_t>(m)), rG(n, std::vector<uint64_t>(m));
        std::vector res(n, std::vector<T>(n));
 
        using E = std::tuple<T, int, int>;
        std::vector<E> edges(n * n);
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            edges[i * n + j] = { cost_matrix[i][j], i, j };
        }
        std::sort(edges.begin(), edges.end(), [&comp](const E& e1, const E& e2) { return comp(std::get<0>(e1), std::get<0>(e2)); });
 
        // Add edges in ascending order of their costs.
        for (const auto& [cost_, u, v] : edges) {
            const T& cost = cost_;
            auto add_edge = [&](int u, int v) {
                const int u_hi = u >> LOG_B, u_lo = u & MASK_B;
                const int v_hi = v >> LOG_B, v_lo = v & MASK_B;
                if ((G[u][v_hi] >> v_lo) & 1) {
                    // already reachable
                    return false; 
                }
                res[u][v] = cost;
                G[u][v_hi] |= uint64_t(1) << v_lo;
                rG[v][u_hi] |= uint64_t(1) << u_lo;
                return true;
            };
 
            auto rec = [&](auto rec, int u, int v) -> void {
                for (int i = 0; i < m; ++i) {
                    // if (u ---> v) and (v ---> w) and (u -/-> w): add (u ---> w)
                    if (uint64_t s = G[v][i] & ~G[u][i]) {
                        const int w_hi = i << LOG_B;
                        for (const int j : all_setbit_64(s)) add_edge(u, w_hi | j);
                        for (const int j : all_setbit_64(s)) rec(rec, u, w_hi | j);
                    }
                    // if (w ---> u) and (u ---> v) and (w -/-> v): add (w ---> v)
                    if (uint64_t s = rG[u][i] & ~rG[v][i]) {
                        const int w_hi = i << LOG_B;
                        for (const int j : all_setbit_64(s)) add_edge(w_hi | j, v);
                        for (const int j : all_setbit_64(s)) rec(rec, w_hi | j, v);
                    }
                }
            };
            if (add_edge(u, v)) {
                rec(rec, u, v);
            }
        }
 
        return res;
    }
} // namespace suisen


#endif // SUISEN_MINMAX_FLOYD_WARSHALL
