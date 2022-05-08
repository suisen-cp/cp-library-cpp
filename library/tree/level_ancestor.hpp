#ifndef SUISEN_LEVEL_ANCESTOR
#define SUISEN_LEVEL_ANCESTOR

#include <algorithm>
#include <vector>

namespace suisen {
    struct LevelAncestor {
        LevelAncestor() = default;
        LevelAncestor(const std::vector<std::vector<int>>& g, const int root = 0)
            : _n(g.size()), _visit_time(_n), _visit_time_inv(_n), _depth(_n), _count(_n + 1), _bucket(_n) {
            build(g, root);
        }

        int query(const int u, const int k) const {
            if (k < 0 or k > _depth[u]) return -1;
            const int d = _depth[u] - k;
            const auto it_l = _bucket.begin() + _count[d], it_r = _bucket.begin() + _count[d + 1];
            const int visit_time_u = _visit_time[u];
            const int visit_time_v = *std::prev(std::upper_bound(it_l, it_r, visit_time_u));
            return _visit_time_inv[visit_time_v];
        }

        int operator()(const int u, const int k) const {
            return query(u, k);
        }

        int get_visit_time(const int u)     const { return _visit_time[u]; }
        int get_visit_time_inv(const int t) const { return _visit_time_inv[t]; }
        int get_kth_visited(const int k)    const { return _visit_time_inv[k]; }
        int get_depth(const int u)          const { return _depth[u]; }

    private:
        int _n;
        std::vector<int> _visit_time;     // vertex -> time
        std::vector<int> _visit_time_inv; // time   -> vertex
        std::vector<int> _depth;          // vertex -> depth
        std::vector<int> _count;          // the leftmost index of the i'th block in the `_bucket`
        std::vector<int> _bucket;         // [|dep=0|dep=1|dep=2|...|dep=n-1|]. Each block contains the visited times in ascending order.

        void build(const std::vector<std::vector<int>>& g, const int root) {
            int time = 0;
            auto dfs = [&](auto dfs, int u, int p) -> void {
                _visit_time[u] = time;
                _visit_time_inv[time] = u;
                ++time;
                ++_count[_depth[u] + 1];
                for (int v : g[u]) if (v != p) {
                    _depth[v] = _depth[u] + 1;
                    dfs(dfs, v, u);
                }
            };
            dfs(dfs, root, -1);

            for (int i = 0; i < _n; ++i) _count[i + 1] += _count[i];
            auto index = _count;
            for (int v : _visit_time_inv) _bucket[index[_depth[v]]++] = _visit_time[v];
        }
    };
} // namespace suisen


#endif // SUISEN_LEVEL_ANCESTOR
