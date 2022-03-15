#ifndef SUISEN_MERGE_HISTORY_FOREST
#define SUISEN_MERGE_HISTORY_FOREST

#include <atcoder/dsu>
#include <algorithm>
#include <deque>
#include <numeric>
#include <limits>

namespace suisen {
    struct MergeHistoryForest : public atcoder::dsu {
        using base_type = atcoder::dsu;

        MergeHistoryForest() : MergeHistoryForest(0) {}
        explicit MergeHistoryForest(int n) : base_type(n), _g(n), _parent(n, -1), _root(n), _time(0), _created_time(n, _time) {
            std::iota(_root.begin(), _root.end(), 0);
        }

        int node_num() const { return _g.size(); }
        int leaf_num() const { return _root.size(); }

        const auto& get_forest() const { return _g; }
    
        int forest_root(int i) { return _root[leader(i)]; }
        int forest_parent(int vid) const { return _parent[vid]; }
        const auto& forest_children(int vid) { return _g[vid]; }
        bool is_forest_root(int vid) const { return _parent[vid] < 0; }
        bool is_forest_leaf(int vid) const { return vid < leaf_num(); }

        std::vector<int> forest_roots() {
            const int n = leaf_num();
            std::vector<int> roots;
            for (int i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);
            return roots;
        }
 
        void merge(int u, int v) {
            ++_time;
            const int ru = leader(u), rv = leader(v);
            if (ru == rv) return;
            const int new_root = create_node();
            create_edge(new_root, _root[ru]), create_edge(new_root, _root[rv]);
            _root[base_type::merge(ru, rv)] = new_root;
        }
        void merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }

        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges) {
            ++_time;
            std::vector<int> vs;
            for (const auto &[u, v] : edges) {
                const int ru = leader(u), rv = leader(v);
                if (ru == rv) continue;
                const int r = base_type::merge(ru, rv), c = ru ^ rv ^ r;
                _g[r].push_back(c);
                vs.push_back(r);
            }
            for (int s : vs) if (s == leader(s)) {
                const int new_root = create_node();
                merge_dfs(s, new_root);
                _root[s] = new_root;
            }
        }

        int current_time() const { return _time; }
        int created_time(int vid) const { return _created_time[vid]; }

        std::vector<int> group(int i, int time) {
            int root = i;
            while (_parent[root] >= 0 and _created_time[_parent[root]] <= time) root = _parent[root];
            std::vector<int> res;
            auto dfs = [&, this](auto dfs, int u) -> void {
                if (is_forest_leaf(u)) {
                    res.push_back(u);
                } else {
                    for (int v : _g[u]) dfs(dfs, v);
                }
            };
            dfs(dfs, root);
            return res;
        }
        std::vector<std::vector<int>> groups(int time) {
            std::vector<std::vector<int>> res;
            const int n = leaf_num();
            std::vector<bool> seen(n, false);
            for (int i = 0; i < n; ++i) if (not seen[i]) for (int v : res.emplace_back(group(i, time))) seen[v] = true;
            return res;
        }

        template <typename GetLCA>
        bool same(int u, int v, int time, GetLCA&& get_lca) {
            if (not base_type::same(u, v)) return false;
            int a = get_lca(u, v);
            return _created_time[a] <= time;
        }

    private:
        std::vector<std::vector<int>> _g;
        std::vector<int> _parent;
        std::vector<int> _root;

        // sum of the number of calls of function `merge` and those of `merge_simultaneously`
        int _time;
        std::vector<int> _created_time;

        void merge_dfs(int u, int new_root) {
            for (int v : _g[u]) merge_dfs(v, new_root), _g[v].shrink_to_fit();
            create_edge(new_root, _root[u]);
            _g[u].clear();
        }

        int create_node() {
            _g.emplace_back();
            _created_time.push_back(_time);
            _parent.push_back(-1);
            return _g.size() - 1;
        }
        void create_edge(int new_root, int old_root) {
            _g[new_root].push_back(old_root);
            _parent[old_root] = new_root;
        }
        static int floor_log2(int n) {
            int res = 0;
            while (1 << (res + 1) <= n) ++res;
            return res;
        }
    };
} // namespace suisen


#endif // SUISEN_MERGE_HISTORY_FOREST
