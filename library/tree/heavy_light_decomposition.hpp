#ifndef SUISEN_HLD
#define SUISEN_HLD

#include "library/type_traits/type_traits.hpp"
#include <vector>

namespace suisen {
class HeavyLightDecomposition {
    public:
        template <typename Q>
        using is_point_update_query = std::is_invocable<Q, int>;
        template <typename Q>
        using is_range_update_query = std::is_invocable<Q, int, int>;
        template <typename Q, typename T>
        using is_point_get_query  = std::is_same<std::invoke_result_t<Q, int>, T>;
        template <typename Q, typename T>
        using is_range_fold_query = std::is_same<std::invoke_result_t<Q, int, int>, T>;

        using Graph = std::vector<std::vector<int>>;

        HeavyLightDecomposition() = default;
        HeavyLightDecomposition(Graph &g) : n(g.size()), visit(n), leave(n), head(n), ord(n), siz(n), par(n, -1), dep(n, 0) {
            for (int i = 0; i < n; ++i) if (par[i] < 0) dfs(g, i, -1);
            int time = 0;
            for (int i = 0; i < n; ++i) if (par[i] < 0) hld(g, i, -1, time);
        }
        int size() const {
            return n;
        }
        int lca(int u, int v) const {
            for (;; v = par[head[v]]) {
                if (visit[u] > visit[v]) std::swap(u, v);
                if (head[u] == head[v]) return u;
            }
        }
        int la(int u, int k, int default_value = -1) const {
            if (k < 0) return default_value;
            while (u >= 0) {
                int h = head[u];
                if (visit[u] - k >= visit[h]) return ord[visit[u] - k];
                k -= visit[u] - visit[h] + 1;
                u = par[h];
            }
            return default_value;
        }
        int jump(int u, int v, int d, int default_value = -1) const {
            if (d < 0) return default_value;
            const int w = lca(u, v);
            int uw = dep[u] - dep[w];
            if (d <= uw) return la(u, d);
            int vw = dep[v] - dep[w];
            return d <= uw + vw ? la(v, (uw + vw) - d) : default_value;
        }
        int dist(int u, int v) const {
            return dep[u] + dep[v] - 2 * dep[lca(u, v)];
        }
        template <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q, T>, is_bin_op<F, T>> = nullptr>
        T fold_path(int u, int v, T identity, F bin_op, Q fold_query, bool is_edge_query = false) const {
            T res = identity;
            for (;; v = par[head[v]]) {
                if (visit[u] > visit[v]) std::swap(u, v);
                if (head[u] == head[v]) break;
                res = bin_op(fold_query(visit[head[v]], visit[v] + 1), res);
            }
            return bin_op(fold_query(visit[u] + is_edge_query, visit[v] + 1), res);
        }
        template <
            typename T, typename Q1, typename Q2, typename F,
            constraints_t<is_range_fold_query<Q1, T>, is_range_fold_query<Q2, T>, is_bin_op<F, T>> = nullptr
        >
        T fold_path_noncommutative(int u, int v, T identity, F bin_op, Q1 fold_query, Q2 fold_query_rev, bool is_edge_query = false) const {
            T res_u = identity, res_v = identity;
            // a := lca(u, v)
            // res = fold(u -> a) + fold(a -> v)
            while (head[u] != head[v]) {
                if (visit[u] < visit[v]) { // a -> v
                    res_v = bin_op(fold_query(visit[head[v]], visit[v] + 1), res_v);
                    v = par[head[v]];
                } else { // u -> a
                    res_u = bin_op(res_u, fold_query_rev(visit[head[u]], visit[u] + 1));
                    u = par[head[u]];
                }
            }
            if (visit[u] < visit[v]) { // a = u
                res_v = bin_op(fold_query(visit[u] + is_edge_query, visit[v] + 1), res_v);
            } else { // a = v
                res_u = bin_op(res_u, fold_query_rev(visit[v] + is_edge_query, visit[u] + 1));
            }
            return bin_op(res_u, res_v);
        }
        template <typename Q, constraints_t<is_range_update_query<Q>> = nullptr>
        void update_path(int u, int v, Q update_query, bool is_edge_query = false) const {
            for (;; v = par[head[v]]) {
                if (visit[u] > visit[v]) std::swap(u, v);
                if (head[u] == head[v]) break;
                update_query(visit[head[v]], visit[v] + 1);
            }
            update_query(visit[u] + is_edge_query, visit[v] + 1);
        }
        template <typename T, typename Q, constraints_t<is_range_fold_query<Q, T>> = nullptr>
        T fold_subtree(int u, Q fold_query, bool is_edge_query = false) const {
            return fold_query(visit[u] + is_edge_query, leave[u]);
        }
        template <typename Q, constraints_t<is_range_update_query<Q>> = nullptr>
        void update_subtree(int u, Q update_query, bool is_edge_query = false) const {
            update_query(visit[u] + is_edge_query, leave[u]);
        }
        template <typename T, typename Q, constraints_t<is_point_get_query<Q, T>> = nullptr>
        T get_point(int u, Q get_query) const {
            return get_query(visit[u]);
        }
        template <typename Q, constraints_t<is_point_update_query<Q>> = nullptr>
        void update_point(int u, Q update_query) const {
            update_query(visit[u]);
        }
        std::vector<int> inv_ids() const {
            std::vector<int> inv(n);
            for (int i = 0; i < n; ++i) inv[visit[i]] = i;
            return inv;
        }
        int get_visit_time(int u) const {
            return visit[u];
        }
        int get_leave_time(int u) const {
            return leave[u];
        }
        int get_head(int u) const {
            return head[u];
        }
        int get_kth_visited(int k) const {
            return ord[k];
        }
        int get_subtree_size(int u) const {
            return siz[u];
        }
        int get_parent(int u) const {
            return par[u];
        }
        int get_depth(int u) const {
            return dep[u];
        }
        std::vector<int> get_roots() const {
            std::vector<int> res;
            for (int i = 0; i < n; ++i) if (par[i] < 0) res.push_back(i);
            return res;
        }
    private:
        int n;
        std::vector<int> visit, leave, head, ord, siz, par, dep;
        int dfs(Graph &g, int u, int p) {
            par[u] = p;
            siz[u] = 1;
            int max_size = 0;
            for (int &v : g[u]) {
                if (v == p) continue;
                dep[v] = dep[u] + 1;
                siz[u] += dfs(g, v, u);
                if (max_size < siz[v]) {
                    max_size = siz[v];
                    std::swap(g[u].front(), v);
                }
            }
            return siz[u];
        }
        void hld(Graph &g, int u, int p, int &time) {
            visit[u] = time, ord[time] = u, ++time;
            head[u] = p >= 0 and g[p].front() == u ? head[p] : u;
            for (int v : g[u]) {
                if (v != p) hld(g, v, u, time);
            }
            leave[u] = time;
        }
};
} // namespace suisen

#endif // SUISEN_HLD
