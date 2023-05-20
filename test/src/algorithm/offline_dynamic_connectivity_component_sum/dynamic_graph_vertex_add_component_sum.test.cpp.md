---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/offline_dynamic_connectivity_component_sum.hpp
    title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\
      \u53D6\u5F97\u30AF\u30A8\u30EA\u304C\u3042\u308B\u5834\u5408\u306E Offline Dynamic\
      \ Connectivity"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find.hpp
    title: "undo \u53EF\u80FD Union Find"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find_component_sum.hpp
    title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\
      \u3092\u53D6\u5F97\u3067\u304D\u308B undo \u53EF\u80FD Union Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <iostream>\n\n#line 1 \"library/algorithm/offline_dynamic_connectivity_component_sum.hpp\"\
    \n\n\n\n#line 5 \"library/algorithm/offline_dynamic_connectivity_component_sum.hpp\"\
    \n#include <map>\n#include <tuple>\n#include <variant>\n\n#line 1 \"library/datastructure/union_find/undo_union_find_component_sum.hpp\"\
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
    \ sum(int x) const {\n            return _sum[root(x)];\n        }\n        T&\
    \ sum(int x) {\n            return _sum[root(x)];\n        }\n    protected:\n\
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
    \ int>> _get_queries;\n    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n\nusing S = std::pair<long long, std::vector<long long>>;\n\nvoid merge(S &pd,\
    \ const S &cd) {\n    pd.second.push_back(std::exchange(pd.first, pd.first + cd.first));\n\
    }\nvoid undo(S &d) {\n    d.first = d.second.back();\n    d.second.pop_back();\n\
    }\nlong long get_value(const S& d) {\n    return d.first;\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S> init_values(n);\n \
    \   for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n  \
    \      init_values[i] = { v, {} };\n    }\n\n    suisen::OfflineDynamicConnectivityComponentSum\
    \ dyn_con{};\n    while (q --> 0) {\n        int query_type;\n        std::cin\
    \ >> query_type;\n        if (query_type == 0) {\n            int u, v;\n    \
    \        std::cin >> u >> v;\n            dyn_con.add_query(u, v);\n        }\
    \ else if (query_type == 1) {\n            int u, v;\n            std::cin >>\
    \ u >> v;\n            dyn_con.del_query(u, v);\n        } else if (query_type\
    \ == 2) {\n            int u, p;\n            std::cin >> u >> p;\n          \
    \  dyn_con.add_query(u, init_values.size());\n            init_values.push_back({\
    \ p, {} });\n        } else {\n            int u;\n            std::cin >> u;\n\
    \            dyn_con.component_sum_query(u);\n        }\n    }\n\n    auto ans\
    \ = dyn_con.answer<S, merge, undo, long long, get_value>(std::move(init_values));\n\
    \    for (const auto &v : ans) {\n        std::cout << std::get<1>(v) << '\\n';\n\
    \    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n\n#include <iostream>\n\n#include \"library/algorithm/offline_dynamic_connectivity_component_sum.hpp\"\
    \n\nusing S = std::pair<long long, std::vector<long long>>;\n\nvoid merge(S &pd,\
    \ const S &cd) {\n    pd.second.push_back(std::exchange(pd.first, pd.first + cd.first));\n\
    }\nvoid undo(S &d) {\n    d.first = d.second.back();\n    d.second.pop_back();\n\
    }\nlong long get_value(const S& d) {\n    return d.first;\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S> init_values(n);\n \
    \   for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n  \
    \      init_values[i] = { v, {} };\n    }\n\n    suisen::OfflineDynamicConnectivityComponentSum\
    \ dyn_con{};\n    while (q --> 0) {\n        int query_type;\n        std::cin\
    \ >> query_type;\n        if (query_type == 0) {\n            int u, v;\n    \
    \        std::cin >> u >> v;\n            dyn_con.add_query(u, v);\n        }\
    \ else if (query_type == 1) {\n            int u, v;\n            std::cin >>\
    \ u >> v;\n            dyn_con.del_query(u, v);\n        } else if (query_type\
    \ == 2) {\n            int u, p;\n            std::cin >> u >> p;\n          \
    \  dyn_con.add_query(u, init_values.size());\n            init_values.push_back({\
    \ p, {} });\n        } else {\n            int u;\n            std::cin >> u;\n\
    \            dyn_con.component_sum_query(u);\n        }\n    }\n\n    auto ans\
    \ = dyn_con.answer<S, merge, undo, long long, get_value>(std::move(init_values));\n\
    \    for (const auto &v : ans) {\n        std::cout << std::get<1>(v) << '\\n';\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - library/algorithm/offline_dynamic_connectivity_component_sum.hpp
  - library/datastructure/union_find/undo_union_find_component_sum.hpp
  - library/datastructure/union_find/undo_union_find.hpp
  isVerificationFile: true
  path: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
  requiredBy: []
  timestamp: '2023-05-21 01:49:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
- /verify/test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp.html
title: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
---
