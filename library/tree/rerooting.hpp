#ifndef SUISEN_REROOTING
#define SUISEN_REROOTING

#include <vector>

namespace suisen {
    template <
        // type of DP array elements
        typename dp_value_type,
        // merge children
        dp_value_type(*op)(dp_value_type, dp_value_type),
        // identity element of op
        dp_value_type(*e)(),
        // dp[v] = leaf() for all leaves v
        dp_value_type(*leaf)(),
        // type of weights on the edges
        typename edge_data_type,
        // transition from child to parent using edge weight; add_root(dp[child], parent, child, weight(parent, child))
        dp_value_type(*add_root)(dp_value_type, int, int, edge_data_type)
    >
    struct ReRooting : public std::vector<std::vector<std::pair<int, edge_data_type>>> {
        using base_type = std::vector<std::vector<std::pair<int, edge_data_type>>>;
        public:
            using base_type::base_type;

            void add_edge(int u, int v, const edge_data_type& w) {
                (*this)[u].emplace_back(v, w);
                (*this)[v].emplace_back(u, w);
            }

            const std::vector<dp_value_type>& rerooting() {
                const int n = this->size();
                dp.resize(n), to_par.resize(n);
                dfs_subtree(0, -1);
                dfs(0, -1, e());
                return dp;
            }

        private:
            // dp : subtree DP -> rerooting DP
            // to_par[v] : transition from v to par[v]
            std::vector<dp_value_type> dp, to_par;

            void dfs_subtree(int u, int p) {
                dp[u] = e();
                bool is_leaf = true;
                for (auto [v, w] : (*this)[u]) {
                    if (v == p) continue;
                    is_leaf = false;
                    dfs_subtree(v, u);
                    dp[u] = op(dp[u], to_par[v] = add_root(dp[v], u, v, w));
                }
                if (is_leaf) dp[u] = leaf();
            }
            void dfs(int u, int p, dp_value_type from_p) {
                const int sz = (*this)[u].size();
                // cumulative sum from left to right
                std::vector<dp_value_type> cum_l;
                cum_l.reserve(sz + 1);
                cum_l.push_back(e());
                for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(), v == p ? from_p : to_par[v]));
                // cumulative sum from right to left
                dp_value_type cum_r = e();
                for (int i = sz - 1; i >= 0; --i) {
                    const auto& [v, w] = (*this)[u][i];
                    if (v == p) {
                        cum_r = op(from_p, cum_r);
                    } else {
                        dp_value_type from_u = add_root(op(cum_l[i], cum_r), v, u, w);
                        dp[v] = op(dp[v], from_u);
                        dfs(v, u, from_u);
                        cum_r = op(to_par[v], cum_r);
                    }
                }
            }
    };
} // namsepace suisen

#endif // SUISEN_REROOTING
