#ifndef SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION
#define SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION

#include <algorithm>
#include <cassert>
#include <map>
#include <utility>
#include <vector>

namespace suisen {
    // @returns (number of distinct (rooted) subtrees, id of subtrees)
    std::pair<int, std::vector<int>> tree_isomorphism_classification(const std::vector<std::vector<int>>& g, int root) {
        static constexpr int None = -1;
        const int n = g.size();

        std::vector<int> ids(n);

        std::vector<int> mp1(n, None);
        std::vector<std::map<std::vector<int>, int>> mps(n);
        int next_id = 0;

        std::vector<int> stk(n), par(n, None);
        auto stk_it = stk.begin();
        *stk_it++ = root;
        while (stk_it != stk.begin()) {
            int u = *--stk_it;
            for (int v : g[u]) if (v != par[u]) par[v] = u, *stk_it++ = v;
            for (const int par_of_nxt = stk_it != stk.begin() ? par[*std::prev(stk_it)] : None; u != par_of_nxt; u = par[u]) {
                // dfs post order
                std::vector<int> ch_ids;
                ch_ids.reserve(g[u].size());
                for (int v : g[u]) if (v != par[u]) ch_ids.push_back(ids[v]);
                if (const int siz = ch_ids.size(); siz == 1) {
                    int ch = ch_ids[0];
                    ids[u] = mp1[ch] != None ? mp1[ch] : mp1[ch] = next_id++;
                } else {
                    std::sort(ch_ids.begin(), ch_ids.end());
                    auto [it, inserted] = mps[siz].try_emplace(std::move(ch_ids), next_id);
                    next_id += inserted;
                    ids[u] = it->second;
                }
            }
        }
        return { next_id, ids };
    }
} // namespace suisen

#endif // SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION
