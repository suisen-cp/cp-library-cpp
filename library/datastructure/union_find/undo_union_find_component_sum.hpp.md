---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/undo_union_find.hpp
    title: "Undo \u53EF\u80FD Union Find"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/offline_dynamic_connectivity_component_sum.hpp
    title: library/algorithm/offline_dynamic_connectivity_component_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
    title: test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/undo_union_find_component_sum.hpp\"\
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
    \        std::vector<T> _sum;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_UNDO_UNION_FIND_COMPONENT_SUM\n#define SUISEN_UNDO_UNION_FIND_COMPONENT_SUM\n\
    \n#include \"library/datastructure/union_find/undo_union_find.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, void(*merge_data)(T&, const T&), void(*undo_data)(T&)>\n\
    \    struct UndoUnionFindComponentSum : UndoUnionFind {\n        UndoUnionFindComponentSum()\
    \ : UndoUnionFindComponentSum(0) {}\n        explicit UndoUnionFindComponentSum(int\
    \ n, const T &init_value = T{}) : UndoUnionFindComponentSum(std::vector<T>(n,\
    \ init_value)) {}\n        explicit UndoUnionFindComponentSum(const std::vector<T>\
    \ &init_values) : UndoUnionFind(init_values.size()), _sum(init_values) {}\n\n\
    \        bool merge(int x, int y) {\n            x = root(x), y = root(y);\n \
    \           if (x == y) return false;\n            if (_dat[x] > _dat[y]) std::swap(x,\
    \ y);\n            _history.emplace_back(x, std::exchange(_dat[x], _dat[x] + _dat[y]));\n\
    \            _history.emplace_back(y, std::exchange(_dat[y], x));\n          \
    \  merge_data(_sum[x], _sum[y]);\n            return true;\n        }\n      \
    \  void snapshot() {\n            _history.clear();\n        }\n        void undo()\
    \ {\n            assert(_history.size());\n            _dat[_history.back().first]\
    \ = _history.back().second, _history.pop_back();\n            undo_data(_sum[_history.back().first]);\n\
    \            _dat[_history.back().first] = _history.back().second, _history.pop_back();\n\
    \        }\n        void rollback() {\n            while (_history.size()) undo();\n\
    \        }\n        const T& sum(int x) const {\n            return _sum[root(x)];\n\
    \        }\n    protected:\n        std::vector<T> _sum;\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_UNDO_UNION_FIND_COMPONENT_SUM\n"
  dependsOn:
  - library/datastructure/union_find/undo_union_find.hpp
  isVerificationFile: false
  path: library/datastructure/union_find/undo_union_find_component_sum.hpp
  requiredBy:
  - library/algorithm/offline_dynamic_connectivity_component_sum.hpp
  timestamp: '2022-06-27 18:51:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/offline_dynamic_connectivity_component_sum/dynamic_graph_vertex_add_component_sum.test.cpp
documentation_of: library/datastructure/union_find/undo_union_find_component_sum.hpp
layout: document
redirect_from:
- /library/library/datastructure/union_find/undo_union_find_component_sum.hpp
- /library/library/datastructure/union_find/undo_union_find_component_sum.hpp.html
title: library/datastructure/union_find/undo_union_find_component_sum.hpp
---
