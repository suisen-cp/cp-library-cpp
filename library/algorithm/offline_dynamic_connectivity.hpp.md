---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find.hpp
    title: "undo \u53EF\u80FD Union Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/offline_dynamic_connectivity.hpp\"\n\n\
    \n\n#include <map>\n#include <tuple>\n\n#line 1 \"library/datastructure/union_find/undo_union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct UndoUnionFind {\n        UndoUnionFind()\
    \ : UndoUnionFind(0) {}\n        explicit UndoUnionFind(int n) : _n(n), _dat(n,\
    \ -1) {}\n\n        int root(int x) const {\n            assert(x < _n);\n   \
    \         return _dat[x] < 0 ? x : root(_dat[x]);\n        }\n        int operator[](int\
    \ x) const {\n            return root(x);\n        }\n        bool merge(int x,\
    \ int y) {\n            x = root(x), y = root(y);\n            if (x == y) return\
    \ false;\n            if (_dat[x] > _dat[y]) std::swap(x, y);\n            _history.emplace_back(x,\
    \ std::exchange(_dat[x], _dat[x] + _dat[y]));\n            _history.emplace_back(y,\
    \ std::exchange(_dat[y], x));\n            return true;\n        }\n        bool\
    \ same(int x, int y) const {\n            return root(x) == root(y);\n       \
    \ }\n        int size(int x) const {\n            return -_dat[root(x)];\n   \
    \     }\n        auto groups() const {\n            std::vector<std::vector<int>>\
    \ res(_n);\n            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n\
    \            res.erase(std::remove_if(res.begin(), res.end(), [](const auto &g)\
    \ { return g.empty(); }), res.end());\n            return res;\n        }\n  \
    \      void snapshot() {\n            _history.clear();\n        }\n        void\
    \ undo() {\n            assert(_history.size());\n            _dat[_history.back().first]\
    \ = _history.back().second, _history.pop_back();\n            _dat[_history.back().first]\
    \ = _history.back().second, _history.pop_back();\n        }\n        void rollback()\
    \ {\n            while (_history.size()) undo();\n        }\n    protected:\n\
    \        int _n;\n        std::vector<int> _dat;\n        std::vector<std::pair<int,\
    \ int>> _history;\n    };\n} // namespace suisen\n\n\n\n#line 8 \"library/algorithm/offline_dynamic_connectivity.hpp\"\
    \n\nnamespace suisen {\n    struct OfflineDynamicConnectivity {\n        OfflineDynamicConnectivity()\
    \ : OfflineDynamicConnectivity(0) {}\n        explicit OfflineDynamicConnectivity(int\
    \ n) : _n(n) {}\n        \n        void add_query(int u, int v) {\n          \
    \  _active.emplace(std::minmax(u, v), _connectivity_queries.size());\n       \
    \ }\n        void del_query(int u, int v) {\n            auto it = _active.find(std::minmax(u,\
    \ v));\n            assert(it != _active.end());\n            _active_range.emplace_back(u,\
    \ v, it->second, _connectivity_queries.size());\n            _active.erase(it);\n\
    \        }\n        void connectivity_query(int u, int v) {\n            _connectivity_queries.emplace_back(u,\
    \ v);\n        }\n\n        std::vector<bool> answer() {\n            const int\
    \ q = _connectivity_queries.size();\n            for (auto it = _active.begin();\
    \ it != _active.end(); it = _active.erase(it)) {\n                const auto &[u,\
    \ v] = it->first;\n                _active_range.emplace_back(u, v, it->second,\
    \ q);\n            }\n            if (not q) return {};\n            std::vector<std::vector<std::pair<int,\
    \ int>>> seg(2 * q);\n            for (auto [u, v, l, r] : _active_range) {\n\
    \                for (l += q, r += q; l < r; l >>= 1, r >>= 1) {\n           \
    \         if (l & 1) seg[l++].emplace_back(u, v);\n                    if (r &\
    \ 1) seg[--r].emplace_back(u, v);\n                }\n            }\n        \
    \    UndoUnionFind uf(_n);\n            std::vector<bool> ans(q);\n          \
    \  auto dfs = [&](auto dfs, int k) -> void {\n                int update_counter\
    \ = 0;\n                for (const auto &[u, v] : seg[k]) update_counter += uf.merge(u,\
    \ v);\n                if (k >= q) {\n                    const int query_id =\
    \ k - q;\n                    const auto &[u, v] = _connectivity_queries[query_id];\n\
    \                    ans[query_id] = uf.same(u, v);\n                } else {\n\
    \                    dfs(dfs, 2 * k), dfs(dfs, 2 * k + 1);\n                }\n\
    \                while (update_counter --> 0) uf.undo();\n            };\n   \
    \         dfs(dfs, 1);\n            return ans;\n        }\n    private:\n   \
    \     int _n;\n        std::multimap<std::pair<int, int>, int> _active;\n    \
    \    std::vector<std::tuple<int, int, int, int>> _active_range;\n        std::vector<std::pair<int,\
    \ int>> _connectivity_queries;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY\n#define SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY\n\
    \n#include <map>\n#include <tuple>\n\n#include \"library/datastructure/union_find/undo_union_find.hpp\"\
    \n\nnamespace suisen {\n    struct OfflineDynamicConnectivity {\n        OfflineDynamicConnectivity()\
    \ : OfflineDynamicConnectivity(0) {}\n        explicit OfflineDynamicConnectivity(int\
    \ n) : _n(n) {}\n        \n        void add_query(int u, int v) {\n          \
    \  _active.emplace(std::minmax(u, v), _connectivity_queries.size());\n       \
    \ }\n        void del_query(int u, int v) {\n            auto it = _active.find(std::minmax(u,\
    \ v));\n            assert(it != _active.end());\n            _active_range.emplace_back(u,\
    \ v, it->second, _connectivity_queries.size());\n            _active.erase(it);\n\
    \        }\n        void connectivity_query(int u, int v) {\n            _connectivity_queries.emplace_back(u,\
    \ v);\n        }\n\n        std::vector<bool> answer() {\n            const int\
    \ q = _connectivity_queries.size();\n            for (auto it = _active.begin();\
    \ it != _active.end(); it = _active.erase(it)) {\n                const auto &[u,\
    \ v] = it->first;\n                _active_range.emplace_back(u, v, it->second,\
    \ q);\n            }\n            if (not q) return {};\n            std::vector<std::vector<std::pair<int,\
    \ int>>> seg(2 * q);\n            for (auto [u, v, l, r] : _active_range) {\n\
    \                for (l += q, r += q; l < r; l >>= 1, r >>= 1) {\n           \
    \         if (l & 1) seg[l++].emplace_back(u, v);\n                    if (r &\
    \ 1) seg[--r].emplace_back(u, v);\n                }\n            }\n        \
    \    UndoUnionFind uf(_n);\n            std::vector<bool> ans(q);\n          \
    \  auto dfs = [&](auto dfs, int k) -> void {\n                int update_counter\
    \ = 0;\n                for (const auto &[u, v] : seg[k]) update_counter += uf.merge(u,\
    \ v);\n                if (k >= q) {\n                    const int query_id =\
    \ k - q;\n                    const auto &[u, v] = _connectivity_queries[query_id];\n\
    \                    ans[query_id] = uf.same(u, v);\n                } else {\n\
    \                    dfs(dfs, 2 * k), dfs(dfs, 2 * k + 1);\n                }\n\
    \                while (update_counter --> 0) uf.undo();\n            };\n   \
    \         dfs(dfs, 1);\n            return ans;\n        }\n    private:\n   \
    \     int _n;\n        std::multimap<std::pair<int, int>, int> _active;\n    \
    \    std::vector<std::tuple<int, int, int, int>> _active_range;\n        std::vector<std::pair<int,\
    \ int>> _connectivity_queries;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY\n"
  dependsOn:
  - library/datastructure/union_find/undo_union_find.hpp
  isVerificationFile: false
  path: library/algorithm/offline_dynamic_connectivity.hpp
  requiredBy: []
  timestamp: '2022-06-27 18:52:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/offline_dynamic_connectivity.hpp
layout: document
title: Offline Dynamic Connectivity
---
## Offline Dynamic Connectivity

Dynamic Conectivity Problem をクエリ先読みにより $O(Q \log Q \log N)$ 時間で解く。時間軸を添字とした双対セグ木のノードに辺を乗せ、セグ木を dfs しながら Union Find を更新する。dfs の帰りがけで undo 操作をする必要があるので、Undo 可能 Union Find を用いる。

各辺は $O(\log Q)$ 個のノードに存在するので、Union Find の操作回数は $O(Q\log Q)$ 回である。Undo 可能 Union Find の各種操作の計算量は経路圧縮を行わないため $O(\log N)$ であるから、全体の計算量は $O(Q \log Q \log N)$ となる。
