#ifndef SUISEN_TREE_DECOMP_TW2
#define SUISEN_TREE_DECOMP_TW2

#include <algorithm>
#include <atcoder/dsu>
#include <cassert>
#include <deque>
#include <optional>
#include <utility>
#include <vector>

namespace suisen {
    struct TreeDecompositionTW2 {
        TreeDecompositionTW2(const int n = 0) : _n(n), _edges{} {}

        void add_edge(int u, int v) {
            _edges.emplace_back(u, v);
        }

        std::optional<std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>>> decomp() const {
            std::vector<std::vector<std::pair<int, int>>> g(_n);
            for (auto [u, v] : _edges) if (u != v) {
                if (u > v) std::swap(u, v);
                const int du = g[u].size(), dv = g[v].size();
                g[u].emplace_back(v, dv);
                g[v].emplace_back(u, du);
            }

            std::vector<int8_t> seen(_n, false);
            std::deque<int> dq;
            for (int i = 0; i < _n; ++i) if (g[i].size() <= 2) {
                dq.push_back(i);
                seen[i] = true;
            }

            std::vector<int> roots;
            std::vector<std::pair<int, int>> edges;
            edges.reserve(_n - 1);
            std::vector<std::vector<int>> bag(_n);
            std::vector<std::vector<int>> link(_n);

            atcoder::dsu uf(_n);
            for (int id = 0; id < _n; ++id) {
                if (dq.empty()) return std::nullopt;
                int u = dq.front();
                dq.pop_front();
                if (g[u].size() == 0) {
                    bag[id] = { u };
                    roots.push_back(id);
                } else if (g[u].size() == 1) {
                    int v = remove_edge(g, u, 0);
                    if (g[v].size() <= 2 and not std::exchange(seen[v], true)) dq.push_back(v);
                    bag[id] = { u, v };
                    link[v].push_back(id);
                } else {
                    int v = remove_edge(g, u, 0);
                    int w = remove_edge(g, u, 0);
                    if (v > w) std::swap(v, w);
                    bag[id] = { u, v, w };
                    const int dv = g[v].size(), dw = g[w].size();
                    g[v].emplace_back(w, dw);
                    g[w].emplace_back(v, dv);
                    remove_multiedges(g, v, dv);
                    remove_multiedges(g, w, dw);
                    if (g[v].size() <= 2 and not std::exchange(seen[v], true)) dq.push_back(v);
                    if (g[w].size() <= 2 and not std::exchange(seen[w], true)) dq.push_back(w);
                    link[v].push_back(id);
                    link[w].push_back(id);
                }
                std::reverse(link[u].begin(), link[u].end());
                for (int id2 : link[u]) if (not uf.same(id, id2)) {
                    edges.emplace_back(id, id2);
                    uf.merge(id, id2);
                }
                g[u].clear(), g[u].shrink_to_fit(), link[u].clear(), link[u].shrink_to_fit();
            }
            const int root_num = roots.size();
            for (int i = 0; i < root_num - 1; ++i) {
                edges.emplace_back(roots[i], roots[i + 1]);
            }
            for (auto& b : bag) std::sort(b.begin(), b.end());
            return std::pair{ std::move(bag), std::move(edges) };
        }
        std::optional<std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>>> nice_decomp() const {
            auto opt_decomp = decomp();
            if (not opt_decomp.has_value()) return std::nullopt;
            std::vector<std::vector<int>> bag = std::move(opt_decomp->first);
            std::vector<std::pair<int, int>> edges = std::move(opt_decomp->second);

            const int root = 0;

            std::vector<std::vector<int>> adj(bag.size());
            for (auto [u, v] : edges) {
                if ((u == root) + adj[u].size() == 3) {
                    const int n = bag.size();
                    const int w = adj[u].back();
                    bag.push_back(bag[u]);
                    adj.push_back({ u, w });
                    u = adj[u].back() = *std::find(adj[w].begin(), adj[w].end(), u) = n;
                }
                if ((v == root) + adj[v].size() == 3) {
                    const int n = bag.size();
                    const int w = adj[v].back();
                    bag.push_back(bag[v]);
                    adj.push_back({ v, w });
                    v = adj[v].back() = *std::find(adj[w].begin(), adj[w].end(), v) = n;
                }
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            std::vector<int> par(bag.size(), -1);
            std::deque<int> dq{ root };
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                std::vector<int> ch;
                for (int v : adj[u]) if (v != par[u]) {
                    par[v] = u;
                    dq.push_back(v);
                    ch.push_back(v);
                }

                auto fix_path = [&](int u) {
                    const int v = adj[u][adj[u][0] == par[u]];
                    std::vector<int> dif;
                    std::set_difference(bag[v].begin(), bag[v].end(), bag[u].begin(), bag[u].end(), std::back_inserter(dif));
                    std::set_difference(bag[u].begin(), bag[u].end(), bag[v].begin(), bag[v].end(), std::back_inserter(dif));
                    assert(dif.size());
                    adj[u].erase(std::find(adj[u].begin(), adj[u].end(), v));
                    adj[v].erase(std::find(adj[v].begin(), adj[v].end(), u));
                    while (dif.size() > 1) {
                        const int n = bag.size();
                        bag.emplace_back();
                        std::set_symmetric_difference(bag[u].begin(), bag[u].end(), std::prev(dif.end()), dif.end(), std::back_inserter(bag.back()));
                        adj.emplace_back().push_back(u);
                        adj[u].push_back(n);
                        par.push_back(u);
                        dif.pop_back();
                        u = n;
                    }
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                    par[v] = u;
                };

                if (ch.size() == 2) {
                    for (int v : ch) if (bag[u] != bag[v]) {
                        const int n = bag.size();
                        *std::find(adj[u].begin(), adj[u].end(), v) = *std::find(adj[v].begin(), adj[v].end(), u) = n;
                        bag.push_back(bag[u]);
                        adj.push_back({ u, v });
                        par.push_back(u);
                        fix_path(n);
                    }
                } else if (ch.size() == 1) {
                    fix_path(u);
                } else if (ch.size() == 0) {
                    while (bag[u].size() > 1) {
                        const int n = bag.size();
                        bag.emplace_back(bag[u].begin(), std::prev(bag[u].end()));
                        adj.emplace_back().push_back(u);
                        adj[u].push_back(n);
                        par.push_back(u);
                        u = n;
                    }
                } else {
                    assert(false);
                }
            }

            edges.clear();
            int n = bag.size();
            for (int i = 0; i < n; ++i) for (int j : adj[i]) if (i < j) {
                edges.emplace_back(i, j);
            }
            return std::pair{ std::move(bag), std::move(edges) };
        }

        static void assert_nice(const std::vector<std::vector<int>>& bag, const std::vector<std::pair<int, int>>& edges, int root) {
            std::vector<std::vector<int>> adj(bag.size());
            for (auto [u, v] : edges) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            auto dfs = [&](auto dfs, int u, int p) -> void {
                std::vector<int> ch;
                for (int v : adj[u]) if (v != p) {
                    dfs(dfs, v, u);
                    ch.push_back(v);
                }
                assert(ch.size() <= 2);
                if (ch.size() == 2) {
                    assert(bag[u] == bag[ch[0]] and bag[u] == bag[ch[1]]);
                } else if (ch.size() == 1) {
                    std::vector<int> d;
                    std::set_symmetric_difference(bag[u].begin(), bag[u].end(), bag[ch[0]].begin(), bag[ch[0]].end(), std::back_inserter(d));
                    assert(d.size() == 1);
                } else {
                    assert(bag[u].size() == 1);
                }
            };
            dfs(dfs, root, -1);
        }
    private:
        int _n;
        std::vector<std::pair<int, int>> _edges;

        static int remove_edge(std::vector<std::vector<std::pair<int, int>>>& g, int u, int idx_uv) {
            auto [v, idx_vu] = g[u][idx_uv];

            if (idx_vu != int(g[v].size()) - 1) {
                auto [w, idx_wv] = g[v].back();
                std::swap(g[v][idx_vu], g[v].back());
                g[w][idx_wv].second = idx_vu;
            }
            g[v].pop_back();
            if (idx_uv != int(g[u].size()) - 1) {
                auto [z, idx_zu] = g[u].back();
                std::swap(g[u][idx_uv], g[u].back());
                g[z][idx_zu].second = idx_uv;
            }
            g[u].pop_back();

            remove_multiedges(g, v, idx_vu);
            remove_multiedges(g, u, idx_uv);

            return v;
        }
        static void remove_multiedges(std::vector<std::vector<std::pair<int, int>>>& g, int u, int idx_uv) {
            auto is_unnecessary = [&](int idx_uv) {
                const int du = int(g[u].size());
                if (idx_uv >= du) return false;
                if (idx_uv + 1 < du and g[u][idx_uv].first == g[u][idx_uv + 1].first) return true;
                if (idx_uv + 2 < du and g[u][idx_uv].first == g[u][idx_uv + 2].first) return true;
                if (idx_uv - 1 >= 0 and g[u][idx_uv].first == g[u][idx_uv - 1].first) return true;
                if (idx_uv - 2 >= 0 and g[u][idx_uv].first == g[u][idx_uv - 2].first) return true;
                return false;
            };
            while (is_unnecessary(idx_uv)) remove_edge(g, u, idx_uv);
        }
    };
} // namespace suisen


#endif // SUISEN_TREE_DECOMP_TW2
