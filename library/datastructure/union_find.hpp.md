---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/datastructure/linked_union_find.hpp
    title: library/datastructure/linked_union_find.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/DSL_1_A.test.cpp
    title: test/src/datastructure/union_find/DSL_1_A.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\nclass UnionFind {\n    public:\n    \
    \    UnionFind() {}\n        explicit UnionFind(int n) : n(n), data(n, -1) {}\n\
    \        // Get the root of `x`. equivalent to `operator[](x)`\n        int root(int\
    \ x) {\n            static std::vector<int> buf;\n            while (data[x] >=\
    \ 0) buf.push_back(x), x = data[x];\n            while (buf.size()) data[buf.back()]\
    \ = x, buf.pop_back();\n            return x;\n        }\n        // Get the root\
    \ of `x`. euivalent to `root(x)`\n        int operator[](int x) {\n          \
    \  return root(x);\n        }\n        // Merge two vertices `x` and `y`.\n  \
    \      bool merge(int x, int y) {\n            x = root(x), y = root(y);\n   \
    \         if (x == y) return false;\n            if (data[x] > data[y]) std::swap(x,\
    \ y);\n            data[x] += data[y], data[y] = x;\n            return true;\n\
    \        }\n        // Check if `x` and `y` belongs to the same connected component.\n\
    \        bool same(int x, int y) {\n            return root(x) == root(y);\n \
    \       }\n        // Get the size of connected componet to which `x` belongs.\n\
    \        int size(int x) {\n            return -data[root(x)];\n        }\n  \
    \      // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(n);\n            for\
    \ (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto &g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n    private:\n        int n;\n        std::vector<int>\
    \ data;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_UNION_FIND\n#define SUISEN_UNION_FIND\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\nclass UnionFind {\n    public:\n    \
    \    UnionFind() {}\n        explicit UnionFind(int n) : n(n), data(n, -1) {}\n\
    \        // Get the root of `x`. equivalent to `operator[](x)`\n        int root(int\
    \ x) {\n            static std::vector<int> buf;\n            while (data[x] >=\
    \ 0) buf.push_back(x), x = data[x];\n            while (buf.size()) data[buf.back()]\
    \ = x, buf.pop_back();\n            return x;\n        }\n        // Get the root\
    \ of `x`. euivalent to `root(x)`\n        int operator[](int x) {\n          \
    \  return root(x);\n        }\n        // Merge two vertices `x` and `y`.\n  \
    \      bool merge(int x, int y) {\n            x = root(x), y = root(y);\n   \
    \         if (x == y) return false;\n            if (data[x] > data[y]) std::swap(x,\
    \ y);\n            data[x] += data[y], data[y] = x;\n            return true;\n\
    \        }\n        // Check if `x` and `y` belongs to the same connected component.\n\
    \        bool same(int x, int y) {\n            return root(x) == root(y);\n \
    \       }\n        // Get the size of connected componet to which `x` belongs.\n\
    \        int size(int x) {\n            return -data[root(x)];\n        }\n  \
    \      // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(n);\n            for\
    \ (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto &g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n    private:\n        int n;\n        std::vector<int>\
    \ data;\n};\n} // namespace suisen\n\n#endif // SUISEN_UNION_FIND\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/union_find.hpp
  requiredBy:
  - library/datastructure/linked_union_find.hpp
  timestamp: '2021-07-25 09:49:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/union_find/DSL_1_A.test.cpp
documentation_of: library/datastructure/union_find.hpp
layout: document
redirect_from:
- /library/library/datastructure/union_find.hpp
- /library/library/datastructure/union_find.hpp.html
title: library/datastructure/union_find.hpp
---
