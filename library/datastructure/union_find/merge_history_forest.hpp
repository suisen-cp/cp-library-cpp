#ifndef SUISEN_MERGE_HISTORY_FOREST
#define SUISEN_MERGE_HISTORY_FOREST

#include <atcoder/dsu>
#include <algorithm>
#include <deque>
#include <numeric>

namespace suisen {
    struct MergeHistoryForest : public atcoder::dsu {
        using base_type = atcoder::dsu;

        MergeHistoryForest() : MergeHistoryForest(0) {}
        explicit MergeHistoryForest(int n) : base_type(n), _g(n), _root(n) {
            std::iota(_root.begin(), _root.end(), 0);
        }

        int node_num() const { return _g.size(); }

        const auto& get_forest() const { return _g; }

        int tree_root(int i) { return _root[leader(i)]; }

        std::vector<int> tree_roots() {
            const int n = _root.size();
            std::vector<int> roots;
            for (int i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);
            return roots;
        }
 
        void merge(int u, int v) {
            const int ru = leader(u), rv = leader(v);
            if (ru == rv) return;
            _g.push_back({ _root[ru], _root[rv] });
            _root[base_type::merge(ru, rv)] = _g.size() - 1;
        }
        void merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }

        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges) {
            std::vector<int> vs;
            for (const auto &[u, v] : edges) {
                const int ru = leader(u), rv = leader(v);
                if (ru == rv) continue;
                const int r = base_type::merge(ru, rv), c = ru ^ rv ^ r;
                _g[r].push_back(c);
                vs.push_back(r);
            }
            for (int s : vs) if (s == leader(s)) dfs(s, _g.emplace_back()), _root[s] = _g.size() - 1;
        }

    private:
        std::vector<std::vector<int>> _g;
        std::vector<int> _root;

        void dfs(int u, std::vector<int> &con) {
            for (int v : _g[u]) dfs(v, con), _g[v].shrink_to_fit();
            con.push_back(_root[u]), _g[u].clear();
        }
    };
} // namespace suisen


#endif // SUISEN_MERGE_HISTORY_FOREST
