---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/graph/tree_decomposition_tw2/nice_tree_decomposition_width_2.test.cpp
    title: test/src/graph/tree_decomposition_tw2/nice_tree_decomposition_width_2.test.cpp
  - icon: ':x:'
    path: test/src/graph/tree_decomposition_tw2/tree_decomposition_width_2.test.cpp
    title: test/src/graph/tree_decomposition_tw2/tree_decomposition_width_2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/tree_decomposition_tw2.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <atcoder/dsu>\n#include <cassert>\n#include <deque>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace suisen\
    \ {\n    struct DecompNode {\n        std::vector<int> bag;\n        std::vector<int>\
    \ adj;\n    };\n    struct DecompNodeRooted {\n        std::vector<int> bag;\n\
    \        int par;\n        std::vector<int> ch;\n    };\n\n    struct TreeDecompositionTW2\
    \ {\n        TreeDecompositionTW2(const int n = 0, const std::vector<std::pair<int,\
    \ int>>& edges = {}) : _n(n), _edges(edges) {}\n        TreeDecompositionTW2(const\
    \ std::vector<std::vector<int>>& g) : TreeDecompositionTW2(g.size()) {\n     \
    \       for (int i = 0; i < _n; ++i) for (int j : g[i]) if (i < j) add_edge(i,\
    \ j);\n        }\n\n        void add_edge(int u, int v) {\n            _edges.emplace_back(u,\
    \ v);\n        }\n\n        std::optional<std::vector<DecompNode>> decomp() const\
    \ {\n            std::vector<std::vector<std::pair<int, int>>> g(_n);\n      \
    \      for (auto [u, v] : _edges) if (u != v) {\n                if (u > v) std::swap(u,\
    \ v);\n                const int du = g[u].size(), dv = g[v].size();\n       \
    \         g[u].emplace_back(v, dv);\n                g[v].emplace_back(u, du);\n\
    \            }\n\n            std::vector<int8_t> seen(_n, false);\n         \
    \   std::deque<int> dq;\n            auto push_if_removable = [&](int i) {\n \
    \               if (g[i].size() > 2 or std::exchange(seen[i], true)) return;\n\
    \                if (g[i].size() == 2) dq.push_back(i);\n                else\
    \ dq.push_front(i);\n            };\n            for (int i = 0; i < _n; ++i)\
    \ push_if_removable(i);\n\n            std::vector<int> roots;\n            std::vector<std::pair<int,\
    \ int>> edges;\n            edges.reserve(_n - 1);\n            std::vector<std::vector<int>>\
    \ bag(_n);\n            std::vector<std::vector<int>> link(_n);\n\n          \
    \  atcoder::dsu uf(_n);\n            for (int id = 0; id < _n; ++id) {\n     \
    \           if (dq.empty()) return std::nullopt;\n                int u = dq.front();\n\
    \                dq.pop_front();\n                if (g[u].size() == 0) {\n  \
    \                  bag[id] = { u };\n                    roots.push_back(id);\n\
    \                } else if (g[u].size() == 1) {\n                    int v = remove_edge(g,\
    \ u, 0);\n                    push_if_removable(v);\n                    bag[id]\
    \ = { u, v };\n                    link[v].push_back(id);\n                } else\
    \ {\n                    int v = remove_edge(g, u, 0);\n                    int\
    \ w = remove_edge(g, u, 0);\n                    if (v > w) std::swap(v, w);\n\
    \                    bag[id] = { u, v, w };\n                    const int dv\
    \ = g[v].size(), dw = g[w].size();\n                    g[v].emplace_back(w, dw);\n\
    \                    g[w].emplace_back(v, dv);\n                    remove_multiedges(g,\
    \ v, dv);\n                    remove_multiedges(g, w, dw);\n                \
    \    push_if_removable(v);\n                    push_if_removable(w);\n      \
    \              link[v].push_back(id);\n                    link[w].push_back(id);\n\
    \                }\n                std::reverse(link[u].begin(), link[u].end());\n\
    \                for (int id2 : link[u]) if (not uf.same(id, id2)) {\n       \
    \             edges.emplace_back(id, id2);\n                    uf.merge(id, id2);\n\
    \                }\n                g[u].clear(), g[u].shrink_to_fit(), link[u].clear(),\
    \ link[u].shrink_to_fit();\n            }\n            const int root_num = roots.size();\n\
    \            for (int i = 0; i < root_num - 1; ++i) {\n                edges.emplace_back(roots[i],\
    \ roots[i + 1]);\n            }\n            std::vector<DecompNode> res(_n);\n\
    \            for (int i = 0; i < _n; ++i) {\n                res[i].bag = std::move(bag[i]);\n\
    \                std::sort(res[i].bag.begin(), res[i].bag.end());\n          \
    \  }\n            for (auto& [i, j] : edges) {\n                res[i].adj.push_back(j);\n\
    \                res[j].adj.push_back(i);\n            }\n            return res;\n\
    \        }\n        std::optional<std::vector<DecompNodeRooted>> nice_decomp()\
    \ const {\n            auto opt_decomp = decomp();\n            if (not opt_decomp.has_value())\
    \ return std::nullopt;\n            std::vector<DecompNodeRooted> res(_n);\n \
    \           for (int i = 0; i < _n; ++i) {\n                res[i].bag = std::move((*opt_decomp)[i].bag);\n\
    \            }\n\n            const int root = 0;\n\n            std::vector<std::vector<std::pair<int,\
    \ int>>> adj_idx(_n);\n            for (int i = 0; i < _n; ++i) for (int j : (*opt_decomp)[i].adj)\
    \ if (i < j) {\n                int u = i, v = j;\n                auto fix_deg\
    \ = [&](int& z) {\n                    if ((z == root) + adj_idx[z].size() !=\
    \ 3) return;\n                    const int n = res.size();\n                \
    \    const int idx_zw = 0;\n                    const auto [w, idx_wz] = adj_idx[z][idx_zw];\n\
    \                    auto& node = res.emplace_back();\n                    node.bag\
    \ = res[z].bag;\n                    adj_idx.push_back({ { z, idx_zw }, { w, idx_wz\
    \ } });\n                    adj_idx[z][idx_zw] = { n, 0 };\n                \
    \    adj_idx[w][idx_wz] = { n, 1 };\n                    z = n;\n            \
    \    };\n                fix_deg(u), fix_deg(v);\n                const int du\
    \ = adj_idx[u].size(), dv = adj_idx[v].size();\n                adj_idx[u].emplace_back(v,\
    \ dv);\n                adj_idx[v].emplace_back(u, du);\n            }\n     \
    \       for (int i = 0; i < int(res.size()); ++i) {\n                res[i].ch.reserve(adj_idx[i].size());\n\
    \                for (auto [j, idx] : adj_idx[i]) res[i].ch.push_back(j);\n  \
    \              adj_idx[i].clear(), adj_idx[i].shrink_to_fit();\n            }\n\
    \            adj_idx.clear(), adj_idx.shrink_to_fit();\n\n            const int\
    \ k = res.size();\n\n            std::deque<int> dq{ root };\n            while\
    \ (dq.size()) {\n                int u = dq.front();\n                dq.pop_front();\n\
    \                for (int v : res[u].ch) {\n                    res[v].par = u;\n\
    \                    res[v].ch.erase(std::find(res[v].ch.begin(), res[v].ch.end(),\
    \ u));\n                    dq.push_back(v);\n                }\n\n          \
    \      auto fix_path = [&](int u, int v) {\n                    std::vector<int>\
    \ dif;\n                    std::set_difference(res[v].bag.begin(), res[v].bag.end(),\
    \ res[u].bag.begin(), res[u].bag.end(), std::back_inserter(dif));\n          \
    \          std::set_difference(res[u].bag.begin(), res[u].bag.end(), res[v].bag.begin(),\
    \ res[v].bag.end(), std::back_inserter(dif));\n                    assert(dif.size());\n\
    \                    res[u].ch.erase(std::find(res[u].ch.begin(), res[u].ch.end(),\
    \ v));\n                    while (dif.size() > 1) {\n                       \
    \ const int n = res.size();\n                        auto& node = res.emplace_back();\n\
    \                        std::set_symmetric_difference(res[u].bag.begin(), res[u].bag.end(),\
    \ std::prev(dif.end()), dif.end(), std::back_inserter(node.bag));\n          \
    \              res[u].ch.push_back(n);\n                        dif.pop_back();\n\
    \                        node.par = u;\n                        u = n;\n     \
    \               }\n                    res[u].ch.push_back(v);\n             \
    \       res[v].par = u;\n                };\n\n                if (res[u].ch.size()\
    \ == 2) {\n                    for (int v : res[u].ch) if (res[u].bag != res[v].bag)\
    \ {\n                        const int n = res.size();\n                     \
    \   *std::find(res[u].ch.begin(), res[u].ch.end(), v) = n;\n                 \
    \       auto& node = res.emplace_back();\n                        node.bag = res[u].bag;\n\
    \                        node.ch = { v };\n                        node.par =\
    \ u;\n                        fix_path(n, v);\n                    }\n       \
    \         } else if (res[u].ch.size() == 1) {\n                    fix_path(u,\
    \ res[u].ch[0]);\n                } else if (res[u].ch.size() == 0) {\n      \
    \              while (res[u].bag.size() > 1) {\n                        const\
    \ int n = res.size();\n                        auto& node = res.emplace_back();\n\
    \                        node.bag = std::vector<int>(res[u].bag.begin(), std::prev(res[u].bag.end()));\n\
    \                        node.par = u;\n                        res[u].ch.push_back(n);\n\
    \                        u = n;\n                    }\n                } else\
    \ {\n                    assert(false);\n                }\n            }\n\n\
    \            return res;\n        }\n\n        static void assert_nice(const std::vector<DecompNodeRooted>&\
    \ nodes, int root) {\n            auto dfs = [&](auto dfs, int u) -> void {\n\
    \                for (int v : nodes[u].ch) dfs(dfs, v);\n                assert(nodes[u].ch.size()\
    \ <= 2);\n                if (nodes[u].ch.size() == 2) {\n                   \
    \ int x = nodes[u].ch[0], y = nodes[u].ch[1];\n                    assert(nodes[u].bag\
    \ == nodes[x].bag and nodes[u].bag == nodes[y].bag);\n                } else if\
    \ (nodes[u].ch.size() == 1) {\n                    int x = nodes[u].ch[0];\n \
    \                   std::vector<int> d;\n                    std::set_symmetric_difference(nodes[u].bag.begin(),\
    \ nodes[u].bag.end(), nodes[x].bag.begin(), nodes[x].bag.end(), std::back_inserter(d));\n\
    \                    assert(d.size() == 1);\n                } else {\n      \
    \              assert(nodes[u].bag.size() == 1);\n                }\n        \
    \    };\n            dfs(dfs, root);\n        }\n    private:\n        int _n;\n\
    \        std::vector<std::pair<int, int>> _edges;\n\n        static int remove_edge(std::vector<std::vector<std::pair<int,\
    \ int>>>& g, int u, int idx_uv) {\n            auto [v, idx_vu] = g[u][idx_uv];\n\
    \n            if (idx_vu != int(g[v].size()) - 1) {\n                auto [w,\
    \ idx_wv] = g[v].back();\n                std::swap(g[v][idx_vu], g[v].back());\n\
    \                g[w][idx_wv].second = idx_vu;\n            }\n            g[v].pop_back();\n\
    \            if (idx_uv != int(g[u].size()) - 1) {\n                auto [z, idx_zu]\
    \ = g[u].back();\n                std::swap(g[u][idx_uv], g[u].back());\n    \
    \            g[z][idx_zu].second = idx_uv;\n            }\n            g[u].pop_back();\n\
    \n            remove_multiedges(g, v, idx_vu);\n            remove_multiedges(g,\
    \ u, idx_uv);\n\n            return v;\n        }\n        static void remove_multiedges(std::vector<std::vector<std::pair<int,\
    \ int>>>& g, int u, int idx_uv) {\n            auto is_unnecessary = [&](int idx_uv)\
    \ {\n                const int du = int(g[u].size());\n                if (idx_uv\
    \ >= du) return false;\n                if (idx_uv + 1 < du and g[u][idx_uv].first\
    \ == g[u][idx_uv + 1].first) return true;\n                if (idx_uv + 2 < du\
    \ and g[u][idx_uv].first == g[u][idx_uv + 2].first) return true;\n           \
    \     if (idx_uv - 1 >= 0 and g[u][idx_uv].first == g[u][idx_uv - 1].first) return\
    \ true;\n                if (idx_uv - 2 >= 0 and g[u][idx_uv].first == g[u][idx_uv\
    \ - 2].first) return true;\n                return false;\n            };\n  \
    \          while (is_unnecessary(idx_uv)) remove_edge(g, u, idx_uv);\n       \
    \ }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TREE_DECOMP_TW2\n#define SUISEN_TREE_DECOMP_TW2\n\n#include\
    \ <algorithm>\n#include <atcoder/dsu>\n#include <cassert>\n#include <deque>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace suisen\
    \ {\n    struct DecompNode {\n        std::vector<int> bag;\n        std::vector<int>\
    \ adj;\n    };\n    struct DecompNodeRooted {\n        std::vector<int> bag;\n\
    \        int par;\n        std::vector<int> ch;\n    };\n\n    struct TreeDecompositionTW2\
    \ {\n        TreeDecompositionTW2(const int n = 0, const std::vector<std::pair<int,\
    \ int>>& edges = {}) : _n(n), _edges(edges) {}\n        TreeDecompositionTW2(const\
    \ std::vector<std::vector<int>>& g) : TreeDecompositionTW2(g.size()) {\n     \
    \       for (int i = 0; i < _n; ++i) for (int j : g[i]) if (i < j) add_edge(i,\
    \ j);\n        }\n\n        void add_edge(int u, int v) {\n            _edges.emplace_back(u,\
    \ v);\n        }\n\n        std::optional<std::vector<DecompNode>> decomp() const\
    \ {\n            std::vector<std::vector<std::pair<int, int>>> g(_n);\n      \
    \      for (auto [u, v] : _edges) if (u != v) {\n                if (u > v) std::swap(u,\
    \ v);\n                const int du = g[u].size(), dv = g[v].size();\n       \
    \         g[u].emplace_back(v, dv);\n                g[v].emplace_back(u, du);\n\
    \            }\n\n            std::vector<int8_t> seen(_n, false);\n         \
    \   std::deque<int> dq;\n            auto push_if_removable = [&](int i) {\n \
    \               if (g[i].size() > 2 or std::exchange(seen[i], true)) return;\n\
    \                if (g[i].size() == 2) dq.push_back(i);\n                else\
    \ dq.push_front(i);\n            };\n            for (int i = 0; i < _n; ++i)\
    \ push_if_removable(i);\n\n            std::vector<int> roots;\n            std::vector<std::pair<int,\
    \ int>> edges;\n            edges.reserve(_n - 1);\n            std::vector<std::vector<int>>\
    \ bag(_n);\n            std::vector<std::vector<int>> link(_n);\n\n          \
    \  atcoder::dsu uf(_n);\n            for (int id = 0; id < _n; ++id) {\n     \
    \           if (dq.empty()) return std::nullopt;\n                int u = dq.front();\n\
    \                dq.pop_front();\n                if (g[u].size() == 0) {\n  \
    \                  bag[id] = { u };\n                    roots.push_back(id);\n\
    \                } else if (g[u].size() == 1) {\n                    int v = remove_edge(g,\
    \ u, 0);\n                    push_if_removable(v);\n                    bag[id]\
    \ = { u, v };\n                    link[v].push_back(id);\n                } else\
    \ {\n                    int v = remove_edge(g, u, 0);\n                    int\
    \ w = remove_edge(g, u, 0);\n                    if (v > w) std::swap(v, w);\n\
    \                    bag[id] = { u, v, w };\n                    const int dv\
    \ = g[v].size(), dw = g[w].size();\n                    g[v].emplace_back(w, dw);\n\
    \                    g[w].emplace_back(v, dv);\n                    remove_multiedges(g,\
    \ v, dv);\n                    remove_multiedges(g, w, dw);\n                \
    \    push_if_removable(v);\n                    push_if_removable(w);\n      \
    \              link[v].push_back(id);\n                    link[w].push_back(id);\n\
    \                }\n                std::reverse(link[u].begin(), link[u].end());\n\
    \                for (int id2 : link[u]) if (not uf.same(id, id2)) {\n       \
    \             edges.emplace_back(id, id2);\n                    uf.merge(id, id2);\n\
    \                }\n                g[u].clear(), g[u].shrink_to_fit(), link[u].clear(),\
    \ link[u].shrink_to_fit();\n            }\n            const int root_num = roots.size();\n\
    \            for (int i = 0; i < root_num - 1; ++i) {\n                edges.emplace_back(roots[i],\
    \ roots[i + 1]);\n            }\n            std::vector<DecompNode> res(_n);\n\
    \            for (int i = 0; i < _n; ++i) {\n                res[i].bag = std::move(bag[i]);\n\
    \                std::sort(res[i].bag.begin(), res[i].bag.end());\n          \
    \  }\n            for (auto& [i, j] : edges) {\n                res[i].adj.push_back(j);\n\
    \                res[j].adj.push_back(i);\n            }\n            return res;\n\
    \        }\n        std::optional<std::vector<DecompNodeRooted>> nice_decomp()\
    \ const {\n            auto opt_decomp = decomp();\n            if (not opt_decomp.has_value())\
    \ return std::nullopt;\n            std::vector<DecompNodeRooted> res(_n);\n \
    \           for (int i = 0; i < _n; ++i) {\n                res[i].bag = std::move((*opt_decomp)[i].bag);\n\
    \            }\n\n            const int root = 0;\n\n            std::vector<std::vector<std::pair<int,\
    \ int>>> adj_idx(_n);\n            for (int i = 0; i < _n; ++i) for (int j : (*opt_decomp)[i].adj)\
    \ if (i < j) {\n                int u = i, v = j;\n                auto fix_deg\
    \ = [&](int& z) {\n                    if ((z == root) + adj_idx[z].size() !=\
    \ 3) return;\n                    const int n = res.size();\n                \
    \    const int idx_zw = 0;\n                    const auto [w, idx_wz] = adj_idx[z][idx_zw];\n\
    \                    auto& node = res.emplace_back();\n                    node.bag\
    \ = res[z].bag;\n                    adj_idx.push_back({ { z, idx_zw }, { w, idx_wz\
    \ } });\n                    adj_idx[z][idx_zw] = { n, 0 };\n                \
    \    adj_idx[w][idx_wz] = { n, 1 };\n                    z = n;\n            \
    \    };\n                fix_deg(u), fix_deg(v);\n                const int du\
    \ = adj_idx[u].size(), dv = adj_idx[v].size();\n                adj_idx[u].emplace_back(v,\
    \ dv);\n                adj_idx[v].emplace_back(u, du);\n            }\n     \
    \       for (int i = 0; i < int(res.size()); ++i) {\n                res[i].ch.reserve(adj_idx[i].size());\n\
    \                for (auto [j, idx] : adj_idx[i]) res[i].ch.push_back(j);\n  \
    \              adj_idx[i].clear(), adj_idx[i].shrink_to_fit();\n            }\n\
    \            adj_idx.clear(), adj_idx.shrink_to_fit();\n\n            const int\
    \ k = res.size();\n\n            std::deque<int> dq{ root };\n            while\
    \ (dq.size()) {\n                int u = dq.front();\n                dq.pop_front();\n\
    \                for (int v : res[u].ch) {\n                    res[v].par = u;\n\
    \                    res[v].ch.erase(std::find(res[v].ch.begin(), res[v].ch.end(),\
    \ u));\n                    dq.push_back(v);\n                }\n\n          \
    \      auto fix_path = [&](int u, int v) {\n                    std::vector<int>\
    \ dif;\n                    std::set_difference(res[v].bag.begin(), res[v].bag.end(),\
    \ res[u].bag.begin(), res[u].bag.end(), std::back_inserter(dif));\n          \
    \          std::set_difference(res[u].bag.begin(), res[u].bag.end(), res[v].bag.begin(),\
    \ res[v].bag.end(), std::back_inserter(dif));\n                    assert(dif.size());\n\
    \                    res[u].ch.erase(std::find(res[u].ch.begin(), res[u].ch.end(),\
    \ v));\n                    while (dif.size() > 1) {\n                       \
    \ const int n = res.size();\n                        auto& node = res.emplace_back();\n\
    \                        std::set_symmetric_difference(res[u].bag.begin(), res[u].bag.end(),\
    \ std::prev(dif.end()), dif.end(), std::back_inserter(node.bag));\n          \
    \              res[u].ch.push_back(n);\n                        dif.pop_back();\n\
    \                        node.par = u;\n                        u = n;\n     \
    \               }\n                    res[u].ch.push_back(v);\n             \
    \       res[v].par = u;\n                };\n\n                if (res[u].ch.size()\
    \ == 2) {\n                    for (int v : res[u].ch) if (res[u].bag != res[v].bag)\
    \ {\n                        const int n = res.size();\n                     \
    \   *std::find(res[u].ch.begin(), res[u].ch.end(), v) = n;\n                 \
    \       auto& node = res.emplace_back();\n                        node.bag = res[u].bag;\n\
    \                        node.ch = { v };\n                        node.par =\
    \ u;\n                        fix_path(n, v);\n                    }\n       \
    \         } else if (res[u].ch.size() == 1) {\n                    fix_path(u,\
    \ res[u].ch[0]);\n                } else if (res[u].ch.size() == 0) {\n      \
    \              while (res[u].bag.size() > 1) {\n                        const\
    \ int n = res.size();\n                        auto& node = res.emplace_back();\n\
    \                        node.bag = std::vector<int>(res[u].bag.begin(), std::prev(res[u].bag.end()));\n\
    \                        node.par = u;\n                        res[u].ch.push_back(n);\n\
    \                        u = n;\n                    }\n                } else\
    \ {\n                    assert(false);\n                }\n            }\n\n\
    \            return res;\n        }\n\n        static void assert_nice(const std::vector<DecompNodeRooted>&\
    \ nodes, int root) {\n            auto dfs = [&](auto dfs, int u) -> void {\n\
    \                for (int v : nodes[u].ch) dfs(dfs, v);\n                assert(nodes[u].ch.size()\
    \ <= 2);\n                if (nodes[u].ch.size() == 2) {\n                   \
    \ int x = nodes[u].ch[0], y = nodes[u].ch[1];\n                    assert(nodes[u].bag\
    \ == nodes[x].bag and nodes[u].bag == nodes[y].bag);\n                } else if\
    \ (nodes[u].ch.size() == 1) {\n                    int x = nodes[u].ch[0];\n \
    \                   std::vector<int> d;\n                    std::set_symmetric_difference(nodes[u].bag.begin(),\
    \ nodes[u].bag.end(), nodes[x].bag.begin(), nodes[x].bag.end(), std::back_inserter(d));\n\
    \                    assert(d.size() == 1);\n                } else {\n      \
    \              assert(nodes[u].bag.size() == 1);\n                }\n        \
    \    };\n            dfs(dfs, root);\n        }\n    private:\n        int _n;\n\
    \        std::vector<std::pair<int, int>> _edges;\n\n        static int remove_edge(std::vector<std::vector<std::pair<int,\
    \ int>>>& g, int u, int idx_uv) {\n            auto [v, idx_vu] = g[u][idx_uv];\n\
    \n            if (idx_vu != int(g[v].size()) - 1) {\n                auto [w,\
    \ idx_wv] = g[v].back();\n                std::swap(g[v][idx_vu], g[v].back());\n\
    \                g[w][idx_wv].second = idx_vu;\n            }\n            g[v].pop_back();\n\
    \            if (idx_uv != int(g[u].size()) - 1) {\n                auto [z, idx_zu]\
    \ = g[u].back();\n                std::swap(g[u][idx_uv], g[u].back());\n    \
    \            g[z][idx_zu].second = idx_uv;\n            }\n            g[u].pop_back();\n\
    \n            remove_multiedges(g, v, idx_vu);\n            remove_multiedges(g,\
    \ u, idx_uv);\n\n            return v;\n        }\n        static void remove_multiedges(std::vector<std::vector<std::pair<int,\
    \ int>>>& g, int u, int idx_uv) {\n            auto is_unnecessary = [&](int idx_uv)\
    \ {\n                const int du = int(g[u].size());\n                if (idx_uv\
    \ >= du) return false;\n                if (idx_uv + 1 < du and g[u][idx_uv].first\
    \ == g[u][idx_uv + 1].first) return true;\n                if (idx_uv + 2 < du\
    \ and g[u][idx_uv].first == g[u][idx_uv + 2].first) return true;\n           \
    \     if (idx_uv - 1 >= 0 and g[u][idx_uv].first == g[u][idx_uv - 1].first) return\
    \ true;\n                if (idx_uv - 2 >= 0 and g[u][idx_uv].first == g[u][idx_uv\
    \ - 2].first) return true;\n                return false;\n            };\n  \
    \          while (is_unnecessary(idx_uv)) remove_edge(g, u, idx_uv);\n       \
    \ }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_TREE_DECOMP_TW2\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/tree_decomposition_tw2.hpp
  requiredBy: []
  timestamp: '2022-10-22 18:09:01+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/graph/tree_decomposition_tw2/nice_tree_decomposition_width_2.test.cpp
  - test/src/graph/tree_decomposition_tw2/tree_decomposition_width_2.test.cpp
documentation_of: library/graph/tree_decomposition_tw2.hpp
layout: document
title: Tree Decomposition Tw2
---
## Tree Decomposition Tw2
