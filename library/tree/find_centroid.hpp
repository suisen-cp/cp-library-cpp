#ifndef SUISEN_FIND_CENTROID
#define SUISEN_FIND_CENTROID

#include <cassert>
#include <cstdint>
#include <vector>

namespace suisen {
    template <typename GraphType>
    std::vector<int> find_centroids(const GraphType& g) {
        const int n = g.size();
        std::vector<int> res;
        std::vector<int8_t> is_centroid(n, true);
        std::vector<int> eid(n), par(n, -1), sub(n, 1);
        for (int cur = 0; cur >= 0;) {
            if (eid[cur] == int(g[cur].size())) {
                if (par[cur] >= 0) {
                    sub[par[cur]] += sub[cur];
                    is_centroid[par[cur]] &= 2 * sub[cur] <= n;
                }
                if (is_centroid[cur] and 2 * sub[cur] >= n) {
                    res.push_back(cur);
                }
                cur = par[cur];
            } else {
                int nxt = g[cur][eid[cur]++];
                if (nxt == par[cur]) continue;
                par[nxt] = cur;
                cur = nxt;
            }
        }
        assert(res.size() == 1 or res.size() == 2);
        return res;
    }
} // namespace suisen


#endif // SUISEN_FIND_CENTROID
