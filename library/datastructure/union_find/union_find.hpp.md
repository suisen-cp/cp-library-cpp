---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/datastructure/union_find/linked_union_find.hpp
    title: "\u9023\u7D50\u6210\u5206\u3092\u53D6\u5F97\u3067\u304D\u308B Union Find"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/union_find_component_sum.hpp
    title: "\u9023\u7D50\u6210\u5206\u306E\u53EF\u63DB\u30E2\u30CE\u30A4\u30C9\u548C\
      \u3092\u53D6\u5F97\u3067\u304D\u308B Union Find"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
    title: test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
    title: test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/union_find/unionfind.test.cpp
    title: test/src/datastructure/union_find/union_find/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
    title: test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/union_find.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct UnionFind\
    \ {\n        UnionFind() {}\n        explicit UnionFind(int _n) : _n(_n), _dat(_n,\
    \ -1) {}\n        // Get the root of `x`. equivalent to `operator[](x)`\n    \
    \    int root(int x) {\n            static std::vector<int> buf;\n           \
    \ while (_dat[x] >= 0) buf.push_back(x), x = _dat[x];\n            while (buf.size())\
    \ _dat[buf.back()] = x, buf.pop_back();\n            return x;\n        }\n  \
    \      // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y`.\n        bool merge(int x, int y) {\n            x = root(x), y\
    \ = root(y);\n            if (x == y) return false;\n            if (_dat[x] >\
    \ _dat[y]) std::swap(x, y);\n            _dat[x] += _dat[y], _dat[y] = x;\n  \
    \          return true;\n        }\n        // Check if `x` and `y` belongs to\
    \ the same connected component.\n        bool same(int x, int y) {\n         \
    \   return root(x) == root(y);\n        }\n        // Get the size of connected\
    \ componet to which `x` belongs.\n        int size(int x) {\n            return\
    \ -_dat[root(x)];\n        }\n        // Get all of connected components.\n  \
    \      std::vector<std::vector<int>> groups() {\n            std::vector<std::vector<int>>\
    \ res(_n);\n            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n\
    \            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g)\
    \ { return g.empty(); }), res.end());\n            return res;\n        }\n  \
    \  protected:\n        int _n;\n        std::vector<int> _dat;\n    };\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_UNION_FIND\n#define SUISEN_UNION_FIND\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\n    struct UnionFind {\n        UnionFind()\
    \ {}\n        explicit UnionFind(int _n) : _n(_n), _dat(_n, -1) {}\n        //\
    \ Get the root of `x`. equivalent to `operator[](x)`\n        int root(int x)\
    \ {\n            static std::vector<int> buf;\n            while (_dat[x] >= 0)\
    \ buf.push_back(x), x = _dat[x];\n            while (buf.size()) _dat[buf.back()]\
    \ = x, buf.pop_back();\n            return x;\n        }\n        // Get the root\
    \ of `x`. euivalent to `root(x)`\n        int operator[](int x) {\n          \
    \  return root(x);\n        }\n        // Merge two vertices `x` and `y`.\n  \
    \      bool merge(int x, int y) {\n            x = root(x), y = root(y);\n   \
    \         if (x == y) return false;\n            if (_dat[x] > _dat[y]) std::swap(x,\
    \ y);\n            _dat[x] += _dat[y], _dat[y] = x;\n            return true;\n\
    \        }\n        // Check if `x` and `y` belongs to the same connected component.\n\
    \        bool same(int x, int y) {\n            return root(x) == root(y);\n \
    \       }\n        // Get the size of connected componet to which `x` belongs.\n\
    \        int size(int x) {\n            return -_dat[root(x)];\n        }\n  \
    \      // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(_n);\n           \
    \ for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto& g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n    protected:\n        int _n;\n        std::vector<int>\
    \ _dat;\n    };\n} // namespace suisen\n\n#endif // SUISEN_UNION_FIND\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/union_find/union_find.hpp
  requiredBy:
  - library/datastructure/union_find/union_find_component_sum.hpp
  - library/datastructure/union_find/linked_union_find.hpp
  timestamp: '2022-06-27 18:51:28+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/union_find/union_find/DSL_1_A.test.cpp
  - test/src/datastructure/union_find/union_find/unionfind.test.cpp
  - test/src/datastructure/union_find/union_find_component_sum/abc183_f.test.cpp
  - test/src/datastructure/union_find/linked_union_find/past202203_h.test.cpp
documentation_of: library/datastructure/union_find/union_find.hpp
layout: document
title: Union Find
---
## Union Find
