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
    struct DecompNode {
        std::vector<int> bag;
        std::vector<int> adj;
    };
    struct DecompNodeRooted {
        std::vector<int> bag;
        int par;
        std::vector<int> ch;
    };

    struct TreeDecompositionTW2 {
        TreeDecompositionTW2(const int n = 0, const std::vector<std::pair<int, int>>& edges = {}) : _n(n), _edges(edges) {}
        TreeDecompositionTW2(const std::vector<std::vector<int>>& g) : TreeDecompositionTW2(g.size()) {
            for (int i = 0; i < _n; ++i) for (int j : g[i]) if (i < j) add_edge(i, j);
        }

        void add_edge(int u, int v) {
            _edges.emplace_back(u, v);
        }

        std::optional<std::vector<DecompNode>> decomp() const {
            std::vector<std::vector<std::pair<int, int>>> g(_n);
            for (auto [u, v] : _edges) if (u != v) {
                if (u > v) std::swap(u, v);
                const int du = g[u].size(), dv = g[v].size();
                g[u].emplace_back(v, dv);
                g[v].emplace_back(u, du);
            }

            std::vector<int8_t> seen(_n, false);
            std::deque<int> dq;
            auto push_if_removable = [&](int i) {
                if (g[i].size() > 2 or std::exchange(seen[i], true)) return;
                if (g[i].size() == 2) dq.push_back(i);
                else dq.push_front(i);
            };
            for (int i = 0; i < _n; ++i) push_if_removable(i);

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
                    push_if_removable(v);
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
                    push_if_removable(v);
                    push_if_removable(w);
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
            std::vector<DecompNode> res(_n);
            for (int i = 0; i < _n; ++i) {
                res[i].bag = std::move(bag[i]);
                std::sort(res[i].bag.begin(), res[i].bag.end());
            }
            for (auto& [i, j] : edges) {
                res[i].adj.push_back(j);
                res[j].adj.push_back(i);
            }
            return res;
        }
        std::optional<std::vector<DecompNodeRooted>> nice_decomp() const {
            auto opt_decomp = decomp();
            if (not opt_decomp.has_value()) return std::nullopt;
            std::vector<DecompNodeRooted> res(_n);
            for (int i = 0; i < _n; ++i) {
                res[i].bag = std::move((*opt_decomp)[i].bag);
            }

            const int root = 0;

            std::vector<std::vector<std::pair<int, int>>> adj_idx(_n);
            for (int i = 0; i < _n; ++i) for (int j : (*opt_decomp)[i].adj) if (i < j) {
                int u = i, v = j;
                auto fix_deg = [&](int& z) {
                    if ((z == root) + adj_idx[z].size() != 3) return;
                    const int n = res.size();
                    const int idx_zw = 0;
                    const auto [w, idx_wz] = adj_idx[z][idx_zw];
                    auto& node = res.emplace_back();
                    node.bag = res[z].bag;
                    adj_idx.push_back({ { z, idx_zw }, { w, idx_wz } });
                    adj_idx[z][idx_zw] = { n, 0 };
                    adj_idx[w][idx_wz] = { n, 1 };
                    z = n;
                };
                fix_deg(u), fix_deg(v);
                const int du = adj_idx[u].size(), dv = adj_idx[v].size();
                adj_idx[u].emplace_back(v, dv);
                adj_idx[v].emplace_back(u, du);
            }
            for (int i = 0; i < int(res.size()); ++i) {
                res[i].ch.reserve(adj_idx[i].size());
                for (auto [j, idx] : adj_idx[i]) res[i].ch.push_back(j);
                adj_idx[i].clear(), adj_idx[i].shrink_to_fit();
            }
            adj_idx.clear(), adj_idx.shrink_to_fit();

            std::deque<int> dq{ root };
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : res[u].ch) {
                    res[v].par = u;
                    res[v].ch.erase(std::find(res[v].ch.begin(), res[v].ch.end(), u));
                    dq.push_back(v);
                }

                auto fix_path = [&](int u, int v) {
                    std::vector<int> dif;
                    std::set_difference(res[v].bag.begin(), res[v].bag.end(), res[u].bag.begin(), res[u].bag.end(), std::back_inserter(dif));
                    std::set_difference(res[u].bag.begin(), res[u].bag.end(), res[v].bag.begin(), res[v].bag.end(), std::back_inserter(dif));
                    assert(dif.size());
                    res[u].ch.erase(std::find(res[u].ch.begin(), res[u].ch.end(), v));
                    while (dif.size() > 1) {
                        const int n = res.size();
                        auto& node = res.emplace_back();
                        std::set_symmetric_difference(res[u].bag.begin(), res[u].bag.end(), std::prev(dif.end()), dif.end(), std::back_inserter(node.bag));
                        res[u].ch.push_back(n);
                        dif.pop_back();
                        node.par = u;
                        u = n;
                    }
                    res[u].ch.push_back(v);
                    res[v].par = u;
                };

                if (res[u].ch.size() == 2) {
                    for (int v : res[u].ch) if (res[u].bag != res[v].bag) {
                        const int n = res.size();
                        *std::find(res[u].ch.begin(), res[u].ch.end(), v) = n;
                        auto& node = res.emplace_back();
                        node.bag = res[u].bag;
                        node.ch = { v };
                        node.par = u;
                        fix_path(n, v);
                    }
                } else if (res[u].ch.size() == 1) {
                    fix_path(u, res[u].ch[0]);
                } else if (res[u].ch.size() == 0) {
                    while (res[u].bag.size() > 1) {
                        const int n = res.size();
                        auto& node = res.emplace_back();
                        node.bag = std::vector<int>(res[u].bag.begin(), std::prev(res[u].bag.end()));
                        node.par = u;
                        res[u].ch.push_back(n);
                        u = n;
                    }
                } else {
                    assert(false);
                }
            }
            res[root].par = -1;

            return res;
        }

        static void assert_nice(const std::vector<DecompNodeRooted>& nodes, int root) {
            auto dfs = [&](auto dfs, int u) -> void {
                for (int v : nodes[u].ch) dfs(dfs, v);
                assert(nodes[u].ch.size() <= 2);
                if (nodes[u].ch.size() == 2) {
                    int x = nodes[u].ch[0], y = nodes[u].ch[1];
                    assert(nodes[u].bag == nodes[x].bag and nodes[u].bag == nodes[y].bag);
                } else if (nodes[u].ch.size() == 1) {
                    int x = nodes[u].ch[0];
                    std::vector<int> d;
                    std::set_symmetric_difference(nodes[u].bag.begin(), nodes[u].bag.end(), nodes[x].bag.begin(), nodes[x].bag.end(), std::back_inserter(d));
                    assert(d.size() == 1);
                } else {
                    assert(nodes[u].bag.size() == 1);
                }
            };
            dfs(dfs, root);
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
