#ifndef SUISEN_REROOTING
#define SUISEN_REROOTING

#include <vector>

namespace suisen {
    template <
        // type of DP array elements
        typename dp_value_type,
        // merge children ((op, dp_value_type) is required to be commutative monoid)
        dp_value_type(*op)(dp_value_type, dp_value_type),
        // identity element of op
        dp_value_type(*e)(),
        // add info as a root of subtree; add_subtree_root(dp[child], child, parent)
        dp_value_type(*add_subtree_root)(dp_value_type, int, int),
        // type of weights on the edges
        typename edge_data_type,
        // transition from child to parent using edge weight; trans_to_par(dp[child], child, parent, weight(child, parent))
        dp_value_type(*trans_to_par)(dp_value_type, int, int, edge_data_type)
    >
    struct ReRooting : public std::vector<std::vector<std::pair<int, edge_data_type>>> {
        using base_type = std::vector<std::vector<std::pair<int, edge_data_type>>>;
        public:
            static constexpr int NIL = -1;

            using base_type::base_type;

            void add_edge(int u, int v, const edge_data_type& w) {
                (*this)[u].emplace_back(v, w);
                (*this)[v].emplace_back(u, w);
            }

            const std::vector<dp_value_type>& rerooting(int initial_root = 0) {
                const int n = this->size();
                dp.resize(n), to_par.resize(n);
                dfs_subtree(initial_root, NIL);
                dfs(initial_root, NIL, e());
                return dp;
            }

        private:
            std::vector<dp_value_type> dp, to_par;

            void dfs_subtree(int u, int p) {
                dp[u] = e();
                for (auto [v, w] : (*this)[u]) {
                    if (v == p) continue;
                    dfs_subtree(v, u);
                    dp[u] = op(dp[u], to_par[v] = trans_to_par(add_subtree_root(dp[v], v, u), v, u, w));
                }
            }
            void dfs(int u, int p, dp_value_type from_p) {
                dp[u] = add_subtree_root(dp[u], u, NIL);
                const int sz = (*this)[u].size();
                std::vector<dp_value_type> cum_l { e() };
                cum_l.reserve(sz + 1);
                for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(), v == p ? from_p : to_par[v]));
                dp_value_type cum_r = e();
                for (int i = sz - 1; i >= 0; --i) {
                    const auto& [v, w] = (*this)[u][i];
                    if (v == p) {
                        cum_r = op(from_p, cum_r);
                    } else {
                        dp_value_type from_u = trans_to_par(add_subtree_root(op(cum_l[i], cum_r), u, v), u, v, w);
                        dp[v] = op(dp[v], from_u);
                        dfs(v, u, from_u);
                        cum_r = op(to_par[v], cum_r);
                    }
                }
            }
    };
} // namsepace suisen

#endif // SUISEN_REROOTING
