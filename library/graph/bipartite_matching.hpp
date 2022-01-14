#ifndef SUISEN_BIPARTITE_MATCHING
#define SUISEN_BIPARTITE_MATCHING

#include <algorithm>
#include <deque>
#include <random>
#include <utility>
#include <vector>

namespace suisen {
    struct BipartiteMatching {
        BipartiteMatching() {}
        BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, Absent), _to_l(_m, Absent), _g(n + m) {}

        void add_edge(int fr, int to) {
            _g[fr].push_back(to), _f = -1;
        }

        template <bool shuffle = true>
        int solve() {
            static std::mt19937 rng(std::random_device{}());
            if constexpr (shuffle) for (auto &adj : _g) std::shuffle(adj.begin(), adj.end(), rng);

            std::vector<int8_t> vis(_n, false);
        
            auto dfs = [&, this](auto dfs, int u) -> bool {
                if (std::exchange(vis[u], true)) return false;
                for (int v : _g[u]) if (_to_l[v] == Absent) return _to_r[u] = v, _to_l[v] = u, true;
                for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u] = v, _to_l[v] = u, true;
                return false;
            };
    
            for (bool upd = true; std::exchange(upd, false);) {
                vis.assign(_n + _m, false);
                for (int i = 0; i < _n; ++i) if (_to_r[i] == Absent) upd |= dfs(dfs, i);
            }

            return _f = _n - std::count(_to_r.begin(), _to_r.end(), Absent);
        }

        std::vector<std::pair<int, int>> max_matching() {
            if (_f < 0) _f = solve();
            std::vector<std::pair<int, int>> res;
            res.reserve(_f);
            for (int i = 0; i < _n; ++i) if (_to_r[i] != Absent) res.emplace_back(i, _to_r[i]);
            return res;
        }

        std::vector<std::pair<int, int>> min_edge_cover() {
            auto res = max_matching();
            std::vector<bool> vl(_n, false), vr(_n, false);
            for (const auto &[u, v] : res) vl[u] = vr[v] = true;
            for (int u = 0; u < _n; ++u) for (int v : _g[u]) if (not (vl[u] and vr[v])) {
                vl[u] = vr[v] = true;
                res.emplace_back(u, v);
            }
            return res;
        }

        std::vector<int> min_vertex_cover() {
            if (_f < 0) _f = solve();
            std::vector<std::vector<int>> g(_n + _m);
            std::vector<bool> cl(_n, true), cr(_m, false);
            for (int u = 0; u < _n; ++u) for (int v : _g[u]) {
                if (_to_r[u] == v) {
                    g[v + _n].push_back(u);
                    cl[u] = false;
                } else {
                    g[u].push_back(v + _n);
                }
            }
            std::vector<bool> vis(_n + _m, false);
            std::deque<int> dq;
            for (int i = 0; i < _n; ++i) if (cl[i]) {
                dq.push_back(i);
                vis[i] = true;
            }
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : g[u]) {
                    if (vis[v]) continue;
                    (v < _n ? cl[v] : cr[v - _n]) = true;
                    vis[v] = true;
                    dq.push_back(v);
                }
            }
            std::vector<int> res;
            for (int i = 0; i < _n; ++i) if (not cl[i]) res.push_back(i);
            for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n + i);
            return res;
        }
        
        std::vector<int> max_independent_set() {
            std::vector<bool> use(_n + _m, true);
            for (int v : min_vertex_cover()) use[v] = false;
            std::vector<int> res;
            for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);
            return res;
        }

    private:
        static constexpr int Absent = -1;

        int _n, _m;
        std::vector<int> _to_r, _to_l;
        std::vector<std::vector<int>> _g;
        int _f = 0;
    };
    
} // namespace suisen


#endif // SUISEN_BIPARTITE_MATCHING
