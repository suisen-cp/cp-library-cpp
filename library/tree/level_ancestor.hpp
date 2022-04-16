#ifndef SUISEN_LEVEL_ANCESTOR
#define SUISEN_LEVEL_ANCESTOR

#include <algorithm>
#include <vector>

namespace suisen {
    struct LevelAncestor {
        LevelAncestor() = default;
        LevelAncestor(const std::vector<std::vector<int>>& g, const int root = 0) : _n(g.size()), _visit_time(_n), _depth(_n), _bucket(_n) {
            build(g, root);
        }

        int query(const int u, const int k) const {
            const int d = _depth[u] - k;
            if (d < 0 or d > _depth[u]) return -1;
            auto comp = [this](int i, int j) {
                return _visit_time[i] < _visit_time[j];
            };
            return *std::prev(std::upper_bound(_bucket[d].begin(), _bucket[d].end(), u, comp));
        }
        int operator()(const int u, const int k) const {
            return query(u, k);
        }

        int get_depth(const int u) const {
            return _depth[u];
        }
    private:
        int _n;
        std::vector<int> _visit_time;
        std::vector<int> _depth;
        std::vector<std::vector<int>> _bucket;

        void build(const std::vector<std::vector<int>>& g, const int root) {
            int time = 0;
            auto dfs = [&](auto dfs, int u, int p) -> void {
                _visit_time[u] = time++;
                _bucket[_depth[u]].push_back(u);
                for (int v : g[u]) {
                    if (v == p) continue;
                    _depth[v] = _depth[u] + 1;
                    dfs(dfs, v, u);
                }
            };
            dfs(dfs, root, -1);
        }
    };
} // namespace suisen


#endif // SUISEN_LEVEL_ANCESTOR
