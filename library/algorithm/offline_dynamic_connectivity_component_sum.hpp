#ifndef SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM
#define SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM

#include <iostream>
#include <map>
#include <tuple>
#include <variant>

#include "library/datastructure/union_find/undo_union_find_component_sum.hpp"

namespace suisen {
    struct OfflineDynamicConnectivityComponentSum {
        OfflineDynamicConnectivityComponentSum() = default;

        void add_query(int u, int v) {
            _active.emplace(std::minmax(u, v), _get_queries.size());
        }
        void del_query(int u, int v) {
            auto it = _active.find(std::minmax(u, v));
            assert(it != _active.end());
            _active_range.emplace_back(u, v, it->second, _get_queries.size());
            _active.erase(it);
        }
        void connectivity_query(int u, int v) {
            _get_queries.emplace_back(u, v);
        }
        void component_sum_query(int u) {
            _get_queries.emplace_back(u, -1);
        }
        
        /**
         * if k'th get-query is a connectivity query, the index of ans[k] is 0,
         * else if k'th get-query is a component sum query, the index of ans[k] is 1.
         */
        template <typename T, void(*merge_data)(T&, const T&), void(*undo_data)(T&), typename U, U(*get_value)(const T&)>
        std::vector<std::variant<bool, U>> answer(const std::vector<T> &init_values) {
            const int q = _get_queries.size();
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
            UndoUnionFindComponentSum<T, merge_data, undo_data> uf(init_values);
            std::vector<std::variant<bool, U>> ans(q);

            auto dfs = [&, this](auto dfs, int k) -> void {
                int update_counter = 0;
                for (const auto &[u, v] : seg[k]) update_counter += uf.merge(u, v);
                seg[k].clear(), seg[k].shrink_to_fit();
                if (k >= q) {
                    const int query_id = k - q;
                    const auto &[u, v] = _get_queries[query_id];
                    if (v >= 0) {
                        ans[query_id].template emplace<0>(uf.same(u, v));
                    } else {
                        ans[query_id].template emplace<1>(get_value(uf.sum(u)));
                    }
                } else {
                    dfs(dfs, 2 * k), dfs(dfs, 2 * k + 1);
                }
                while (update_counter --> 0) uf.undo();
            };
            dfs(dfs, 1);
            return ans;
        }
    private:
        std::multimap<std::pair<int, int>, int> _active;
        std::vector<std::tuple<int, int, int, int>> _active_range;
        std::vector<std::pair<int, int>> _get_queries;
    };
} // namespace suisen


#endif // SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM
