---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find.hpp
    title: "undo \u53EF\u80FD Union Find"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find_component_sum.hpp
    title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\
      \u3092\u53D6\u5F97\u3067\u304D\u308B undo \u53EF\u80FD Union Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
    title: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/offline_dynamic_connectivity_component_sum.hpp\"\
    \n\n\n\n#include <iostream>\n#include <map>\n#include <tuple>\n#include <variant>\n\
    \n#line 1 \"library/datastructure/union_find/undo_union_find_component_sum.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/union_find/undo_union_find.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \nnamespace suisen {\n    struct UndoUnionFind {\n        UndoUnionFind() : UndoUnionFind(0)\
    \ {}\n        explicit UndoUnionFind(int n) : _n(n), _dat(n, -1) {}\n\n      \
    \  int root(int x) const {\n            assert(x < _n);\n            return _dat[x]\
    \ < 0 ? x : root(_dat[x]);\n        }\n        int operator[](int x) const {\n\
    \            return root(x);\n        }\n        bool merge(int x, int y) {\n\
    \            x = root(x), y = root(y);\n            if (x == y) return false;\n\
    \            if (_dat[x] > _dat[y]) std::swap(x, y);\n            _history.emplace_back(x,\
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
    \ int>> _history;\n    };\n} // namespace suisen\n\n\n\n#line 5 \"library/datastructure/union_find/undo_union_find_component_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, void(*merge_data)(T&, const\
    \ T&), void(*undo_data)(T&)>\n    struct UndoUnionFindComponentSum : UndoUnionFind\
    \ {\n        UndoUnionFindComponentSum() : UndoUnionFindComponentSum(0) {}\n \
    \       explicit UndoUnionFindComponentSum(int n, const T &init_value = T{}) :\
    \ UndoUnionFindComponentSum(std::vector<T>(n, init_value)) {}\n        explicit\
    \ UndoUnionFindComponentSum(const std::vector<T> &init_values) : UndoUnionFind(init_values.size()),\
    \ _sum(init_values) {}\n\n        bool merge(int x, int y) {\n            x =\
    \ root(x), y = root(y);\n            if (x == y) return false;\n            if\
    \ (_dat[x] > _dat[y]) std::swap(x, y);\n            _history.emplace_back(x, std::exchange(_dat[x],\
    \ _dat[x] + _dat[y]));\n            _history.emplace_back(y, std::exchange(_dat[y],\
    \ x));\n            merge_data(_sum[x], _sum[y]);\n            return true;\n\
    \        }\n        void snapshot() {\n            _history.clear();\n       \
    \ }\n        void undo() {\n            assert(_history.size());\n           \
    \ _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \            undo_data(_sum[_history.back().first]);\n            _dat[_history.back().first]\
    \ = _history.back().second, _history.pop_back();\n        }\n        void rollback()\
    \ {\n            while (_history.size()) undo();\n        }\n        const T&\
    \ sum(int x) const {\n            return _sum[root(x)];\n        }\n    protected:\n\
    \        std::vector<T> _sum;\n    };\n} // namespace suisen\n\n\n\n#line 10 \"\
    library/algorithm/offline_dynamic_connectivity_component_sum.hpp\"\n\nnamespace\
    \ suisen {\n    struct OfflineDynamicConnectivityComponentSum {\n        OfflineDynamicConnectivityComponentSum()\
    \ = default;\n\n        void add_query(int u, int v) {\n            _active.emplace(std::minmax(u,\
    \ v), _get_queries.size());\n        }\n        void del_query(int u, int v) {\n\
    \            auto it = _active.find(std::minmax(u, v));\n            assert(it\
    \ != _active.end());\n            _active_range.emplace_back(u, v, it->second,\
    \ _get_queries.size());\n            _active.erase(it);\n        }\n        void\
    \ connectivity_query(int u, int v) {\n            _get_queries.emplace_back(u,\
    \ v);\n        }\n        void component_sum_query(int u) {\n            _get_queries.emplace_back(u,\
    \ -1);\n        }\n        \n        /**\n         * if k'th get-query is a connectivity\
    \ query, the index of ans[k] is 0,\n         * else if k'th get-query is a component\
    \ sum query, the index of ans[k] is 1.\n         */\n        template <typename\
    \ T, void(*merge_data)(T&, const T&), void(*undo_data)(T&), typename U, U(*get_value)(const\
    \ T&)>\n        std::vector<std::variant<bool, U>> answer(const std::vector<T>\
    \ &init_values) {\n            const int q = _get_queries.size();\n          \
    \  for (auto it = _active.begin(); it != _active.end(); it = _active.erase(it))\
    \ {\n                const auto &[u, v] = it->first;\n                _active_range.emplace_back(u,\
    \ v, it->second, q);\n            }\n            if (not q) return {};\n     \
    \       std::vector<std::vector<std::pair<int, int>>> seg(2 * q);\n          \
    \  for (auto [u, v, l, r] : _active_range) {\n                for (l += q, r +=\
    \ q; l < r; l >>= 1, r >>= 1) {\n                    if (l & 1) seg[l++].emplace_back(u,\
    \ v);\n                    if (r & 1) seg[--r].emplace_back(u, v);\n         \
    \       }\n            }\n            UndoUnionFindComponentSum<T, merge_data,\
    \ undo_data> uf(init_values);\n            std::vector<std::variant<bool, U>>\
    \ ans(q);\n\n            auto dfs = [&, this](auto dfs, int k) -> void {\n   \
    \             int update_counter = 0;\n                for (const auto &[u, v]\
    \ : seg[k]) update_counter += uf.merge(u, v);\n                seg[k].clear(),\
    \ seg[k].shrink_to_fit();\n                if (k >= q) {\n                   \
    \ const int query_id = k - q;\n                    const auto &[u, v] = _get_queries[query_id];\n\
    \                    if (v >= 0) {\n                        ans[query_id].template\
    \ emplace<0>(uf.same(u, v));\n                    } else {\n                 \
    \       ans[query_id].template emplace<1>(get_value(uf.sum(u)));\n           \
    \         }\n                } else {\n                    dfs(dfs, 2 * k), dfs(dfs,\
    \ 2 * k + 1);\n                }\n                while (update_counter --> 0)\
    \ uf.undo();\n            };\n            dfs(dfs, 1);\n            return ans;\n\
    \        }\n    private:\n        std::multimap<std::pair<int, int>, int> _active;\n\
    \        std::vector<std::tuple<int, int, int, int>> _active_range;\n        std::vector<std::pair<int,\
    \ int>> _get_queries;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM\n#define SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM\n\
    \n#include <iostream>\n#include <map>\n#include <tuple>\n#include <variant>\n\n\
    #include \"library/datastructure/union_find/undo_union_find_component_sum.hpp\"\
    \n\nnamespace suisen {\n    struct OfflineDynamicConnectivityComponentSum {\n\
    \        OfflineDynamicConnectivityComponentSum() = default;\n\n        void add_query(int\
    \ u, int v) {\n            _active.emplace(std::minmax(u, v), _get_queries.size());\n\
    \        }\n        void del_query(int u, int v) {\n            auto it = _active.find(std::minmax(u,\
    \ v));\n            assert(it != _active.end());\n            _active_range.emplace_back(u,\
    \ v, it->second, _get_queries.size());\n            _active.erase(it);\n     \
    \   }\n        void connectivity_query(int u, int v) {\n            _get_queries.emplace_back(u,\
    \ v);\n        }\n        void component_sum_query(int u) {\n            _get_queries.emplace_back(u,\
    \ -1);\n        }\n        \n        /**\n         * if k'th get-query is a connectivity\
    \ query, the index of ans[k] is 0,\n         * else if k'th get-query is a component\
    \ sum query, the index of ans[k] is 1.\n         */\n        template <typename\
    \ T, void(*merge_data)(T&, const T&), void(*undo_data)(T&), typename U, U(*get_value)(const\
    \ T&)>\n        std::vector<std::variant<bool, U>> answer(const std::vector<T>\
    \ &init_values) {\n            const int q = _get_queries.size();\n          \
    \  for (auto it = _active.begin(); it != _active.end(); it = _active.erase(it))\
    \ {\n                const auto &[u, v] = it->first;\n                _active_range.emplace_back(u,\
    \ v, it->second, q);\n            }\n            if (not q) return {};\n     \
    \       std::vector<std::vector<std::pair<int, int>>> seg(2 * q);\n          \
    \  for (auto [u, v, l, r] : _active_range) {\n                for (l += q, r +=\
    \ q; l < r; l >>= 1, r >>= 1) {\n                    if (l & 1) seg[l++].emplace_back(u,\
    \ v);\n                    if (r & 1) seg[--r].emplace_back(u, v);\n         \
    \       }\n            }\n            UndoUnionFindComponentSum<T, merge_data,\
    \ undo_data> uf(init_values);\n            std::vector<std::variant<bool, U>>\
    \ ans(q);\n\n            auto dfs = [&, this](auto dfs, int k) -> void {\n   \
    \             int update_counter = 0;\n                for (const auto &[u, v]\
    \ : seg[k]) update_counter += uf.merge(u, v);\n                seg[k].clear(),\
    \ seg[k].shrink_to_fit();\n                if (k >= q) {\n                   \
    \ const int query_id = k - q;\n                    const auto &[u, v] = _get_queries[query_id];\n\
    \                    if (v >= 0) {\n                        ans[query_id].template\
    \ emplace<0>(uf.same(u, v));\n                    } else {\n                 \
    \       ans[query_id].template emplace<1>(get_value(uf.sum(u)));\n           \
    \         }\n                } else {\n                    dfs(dfs, 2 * k), dfs(dfs,\
    \ 2 * k + 1);\n                }\n                while (update_counter --> 0)\
    \ uf.undo();\n            };\n            dfs(dfs, 1);\n            return ans;\n\
    \        }\n    private:\n        std::multimap<std::pair<int, int>, int> _active;\n\
    \        std::vector<std::tuple<int, int, int, int>> _active_range;\n        std::vector<std::pair<int,\
    \ int>> _get_queries;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_OFFLINE_DYNAMIC_CONNECTIVITY_COMPONENT_SUM\n"
  dependsOn:
  - library/datastructure/union_find/undo_union_find_component_sum.hpp
  - library/datastructure/union_find/undo_union_find.hpp
  isVerificationFile: false
  path: library/algorithm/offline_dynamic_connectivity_component_sum.hpp
  requiredBy: []
  timestamp: '2022-06-27 18:52:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
documentation_of: library/algorithm/offline_dynamic_connectivity_component_sum.hpp
layout: document
title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\u53D6\
  \u5F97\u30AF\u30A8\u30EA\u304C\u3042\u308B\u5834\u5408\u306E Offline Dynamic Connectivity"
---
## 連結成分の可換モノイド和取得クエリがある場合の Offline Dynamic Connectivity

Offline Dynamic Connectivity で用いる Undo 可能 Union Find に連結成分の和を持たせることで実現する。
