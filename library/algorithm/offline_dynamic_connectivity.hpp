#ifndef SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY
#define SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY

#include <map>
#include <tuple>

#include "library/datastructure/union_find/undo_union_find.hpp"

namespace suisen {
    struct OfflineDynamicConnectivity {
        OfflineDynamicConnectivity() : OfflineDynamicConnectivity(0) {}
        explicit OfflineDynamicConnectivity(int n) : _n(n) {}
        
        void add_query(int u, int v) {
            _active.emplace(std::minmax(u, v), _connectivity_queries.size());
        }
        void del_query(int u, int v) {
            auto it = _active.find(std::minmax(u, v));
            assert(it != _active.end());
            _active_range.emplace_back(u, v, it->second, _connectivity_queries.size());
            _active.erase(it);
        }
        void connectivity_query(int u, int v) {
            _connectivity_queries.emplace_back(u, v);
        }

        std::vector<bool> answer() {
            const int q = _connectivity_queries.size();
            for (auto it = _active.begin(); it != _active.end(); it = _active.erase(it)) {
                const auto &[u, v] = it->first;
                _active_range.emplace_back(u, v, it->second, q);
            }
            if (not q) return {};
            std::vector<std::vector<std::pair<int, int>>> seg(2 * q);
            for (auto [u, v, l, r] : _active_range) {
                for (l += q, r += q; l < r; l >>= 1, r >>= 1) {
                    if (l & 1) seg[l++].emplace_back(u, v);
                    if (r & 1) seg[--r].emplace_back(u, v);
                }
            }
            UndoUnionFind uf(_n);
            std::vector<bool> ans(q);
            auto dfs = [&](auto dfs, int k) -> void {
                int update_counter = 0;
                for (const auto &[u, v] : seg[k]) update_counter += uf.merge(u, v);
                if (k >= q) {
                    const int query_id = k - q;
                    const auto &[u, v] = _connectivity_queries[query_id];
                    ans[query_id] = uf.same(u, v);
                } else {
                    dfs(dfs, 2 * k), dfs(dfs, 2 * k + 1);
                }
                while (update_counter --> 0) uf.undo();
            };
            dfs(dfs, 1);
            return ans;
        }
    private:
        int _n;
        std::multimap<std::pair<int, int>, int> _active;
        std::vector<std::tuple<int, int, int, int>> _active_range;
        std::vector<std::pair<int, int>> _connectivity_queries;
    };
} // namespace suisen


#endif // SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY
