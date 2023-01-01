---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
    title: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/cartesian_tree.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <functional>\n#include <vector>\n\nnamespace\
    \ suisen {\n    struct CartesianTree : public std::vector<std::array<int, 2>>\
    \ {\n        using base_type = std::vector<std::array<int, 2>>;\n\n        static\
    \ constexpr int absent = -1;\n\n        const int root;\n\n        CartesianTree()\
    \ : base_type(), root(0) {}\n        CartesianTree(int root, const base_type&\
    \ g) : base_type(g), root(root) {}\n        CartesianTree(int root, base_type&&\
    \ g) : base_type(std::move(g)), root(root) {}\n\n        auto ranges() const {\n\
    \            std::vector<std::pair<int, int>> res;\n            res.reserve(size());\n\
    \            auto rec = [&](auto rec, int l, int m, int r) -> void {\n       \
    \         if (m == absent) return;\n                const auto& [lm, rm] = (*this)[m];\n\
    \                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm,\
    \ r);\n            };\n            rec(rec, 0, root, size());\n            return\
    \ res;\n        }\n    };\n\n    template <typename Comparator>\n    struct CartesianTreeBuilder\
    \ {\n        CartesianTreeBuilder() {}\n        template <typename RandomAccessibleContainer>\n\
    \        CartesianTreeBuilder(const RandomAccessibleContainer& a, Comparator comp\
    \ = Comparator{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}\n\n   \
    \     CartesianTree build() const {\n            int root = -1;\n            std::vector<std::array<int,\
    \ 2>> g(n, { CartesianTree::absent, CartesianTree::absent });\n            for\
    \ (int i = 0; i < n; ++i) {\n                int p = par[i];\n               \
    \ (p >= 0 ? g[p][p <= i] : root) = i;\n            }\n            return CartesianTree{\
    \ root, std::move(g) };\n        }\n\n        template <typename RandomAccessibleContainer>\n\
    \        static CartesianTree build(const RandomAccessibleContainer& a, Comparator\
    \ comp = Comparator{}) {\n            return CartesianTreeBuilder(a, comp).build();\n\
    \        }\n\n        int parent(std::size_t i) const {\n            assert(i\
    \ < std::size_t(n));\n            return par[i];\n        }\n        int operator[](std::size_t\
    \ i) const {\n            return parent(i);\n        }\n    private:\n       \
    \ const int n;\n        const Comparator comp;\n        const std::vector<int>\
    \ par;\n\n        template <typename RandomAccessibleContainer>\n        static\
    \ std::vector<int> calc_par(const RandomAccessibleContainer& a, Comparator comp)\
    \ {\n            const int n = a.size();\n            std::vector<int> par(n,\
    \ -1);\n            for (int i = 1; i < n; ++i) {\n                int p = i -\
    \ 1, l = i;\n                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];\n\
    \                par[l] = i, par[i] = p;\n            }\n            return par;\n\
    \        }\n    };\n\n    using MinCartesianTreeBuilder = CartesianTreeBuilder<std::less<>>;\n\
    \    using MaxCartesianTreeBuilder = CartesianTreeBuilder<std::greater<>>;\n}\
    \ // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_CARTESIAN_TREE\n#define SUISEN_CARTESIAN_TREE\n\n#include\
    \ <array>\n#include <cassert>\n#include <functional>\n#include <vector>\n\nnamespace\
    \ suisen {\n    struct CartesianTree : public std::vector<std::array<int, 2>>\
    \ {\n        using base_type = std::vector<std::array<int, 2>>;\n\n        static\
    \ constexpr int absent = -1;\n\n        const int root;\n\n        CartesianTree()\
    \ : base_type(), root(0) {}\n        CartesianTree(int root, const base_type&\
    \ g) : base_type(g), root(root) {}\n        CartesianTree(int root, base_type&&\
    \ g) : base_type(std::move(g)), root(root) {}\n\n        auto ranges() const {\n\
    \            std::vector<std::pair<int, int>> res;\n            res.reserve(size());\n\
    \            auto rec = [&](auto rec, int l, int m, int r) -> void {\n       \
    \         if (m == absent) return;\n                const auto& [lm, rm] = (*this)[m];\n\
    \                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm,\
    \ r);\n            };\n            rec(rec, 0, root, size());\n            return\
    \ res;\n        }\n    };\n\n    template <typename Comparator>\n    struct CartesianTreeBuilder\
    \ {\n        CartesianTreeBuilder() {}\n        template <typename RandomAccessibleContainer>\n\
    \        CartesianTreeBuilder(const RandomAccessibleContainer& a, Comparator comp\
    \ = Comparator{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}\n\n   \
    \     CartesianTree build() const {\n            int root = -1;\n            std::vector<std::array<int,\
    \ 2>> g(n, { CartesianTree::absent, CartesianTree::absent });\n            for\
    \ (int i = 0; i < n; ++i) {\n                int p = par[i];\n               \
    \ (p >= 0 ? g[p][p <= i] : root) = i;\n            }\n            return CartesianTree{\
    \ root, std::move(g) };\n        }\n\n        template <typename RandomAccessibleContainer>\n\
    \        static CartesianTree build(const RandomAccessibleContainer& a, Comparator\
    \ comp = Comparator{}) {\n            return CartesianTreeBuilder(a, comp).build();\n\
    \        }\n\n        int parent(std::size_t i) const {\n            assert(i\
    \ < std::size_t(n));\n            return par[i];\n        }\n        int operator[](std::size_t\
    \ i) const {\n            return parent(i);\n        }\n    private:\n       \
    \ const int n;\n        const Comparator comp;\n        const std::vector<int>\
    \ par;\n\n        template <typename RandomAccessibleContainer>\n        static\
    \ std::vector<int> calc_par(const RandomAccessibleContainer& a, Comparator comp)\
    \ {\n            const int n = a.size();\n            std::vector<int> par(n,\
    \ -1);\n            for (int i = 1; i < n; ++i) {\n                int p = i -\
    \ 1, l = i;\n                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];\n\
    \                par[l] = i, par[i] = p;\n            }\n            return par;\n\
    \        }\n    };\n\n    using MinCartesianTreeBuilder = CartesianTreeBuilder<std::less<>>;\n\
    \    using MaxCartesianTreeBuilder = CartesianTreeBuilder<std::greater<>>;\n}\
    \ // namespace suisen\n\n#endif // SUISEN_CARTESIAN_TREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
documentation_of: library/datastructure/cartesian_tree.hpp
layout: document
title: Cartesian Tree
---
## Cartesian Tree