---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_2d.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n\n    template <typename T>\n\
    \    class FenwickTree2D {\n    public:\n        FenwickTree2D() = default;\n\
    \        explicit FenwickTree2D(int n, int m) : n(n), m(m), data(n, std::vector<T>(m,\
    \ T{})) {}\n        void add(int i, int j, T v) {\n            for (int x = i\
    \ + 1; x <= n; x += (x & -x)) for (int y = j + 1; y <= m; y += (y & -y)) {\n \
    \               data[x - 1][y - 1] += v;\n            }\n        }\n        T\
    \ sum(int xl, int xr, int yl, int yr) const {\n            return sum(xr, yr)\
    \ - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);\n        }\n        auto operator[](std::pair<int,\
    \ int> index) {\n            auto [i, j] = index;\n            struct {\n    \
    \            int i, j;\n                FenwickTree2D& ft;\n                operator\
    \ T() const { return ft.sum(i, i + 1, j, j + 1); }\n                auto& operator++()\
    \ { return *this += 1; }\n                auto& operator--() { return *this -=\
    \ 1; }\n                auto& operator+=(T val) { ft.add(i, j, val); return *this;\
    \ }\n                auto& operator-=(T val) { ft.add(i, j, -val); return *this;\
    \ }\n                auto& operator*=(T val) { T cur = *this; ft.add(i, j, cur\
    \ * val - cur); return *this; }\n                auto& operator/=(T val) { T cur\
    \ = *this; ft.add(i, j, cur / val - cur); return *this; }\n                auto&\
    \ operator%=(T val) { T cur = *this; ft.add(i, j, cur % val - cur); return *this;\
    \ }\n                auto& operator =(T val) { T cur = *this; ft.add(i, j, val\
    \ - cur); return *this; }\n            } obj{ i, j, *this };\n            return\
    \ obj;\n        }\n        T operator()(int xl, int xr, int yl, int yr) const\
    \ { return sum(xl, xr, yl, yr); }\n\n    private:\n        int n, m;\n       \
    \ std::vector<std::vector<T>> data;\n\n        T sum(int xr, int yr) const {\n\
    \            T s{};\n            for (int x = xr; x; x -= x & -x) for (int y =\
    \ yr; y; y -= y & -y) {\n                s += data[x - 1][y - 1];\n          \
    \  }\n            return s;\n        }\n    };\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_FENWICK_TREE_2D\n#define SUISEN_FENWICK_TREE_2D\n\n#include\
    \ <vector>\n\nnamespace suisen {\n\n    template <typename T>\n    class FenwickTree2D\
    \ {\n    public:\n        FenwickTree2D() = default;\n        explicit FenwickTree2D(int\
    \ n, int m) : n(n), m(m), data(n, std::vector<T>(m, T{})) {}\n        void add(int\
    \ i, int j, T v) {\n            for (int x = i + 1; x <= n; x += (x & -x)) for\
    \ (int y = j + 1; y <= m; y += (y & -y)) {\n                data[x - 1][y - 1]\
    \ += v;\n            }\n        }\n        T sum(int xl, int xr, int yl, int yr)\
    \ const {\n            return sum(xr, yr) - sum(xl, yr) - sum(xr, yl) + sum(xl,\
    \ yl);\n        }\n        auto operator[](std::pair<int, int> index) {\n    \
    \        auto [i, j] = index;\n            struct {\n                int i, j;\n\
    \                FenwickTree2D& ft;\n                operator T() const { return\
    \ ft.sum(i, i + 1, j, j + 1); }\n                auto& operator++() { return *this\
    \ += 1; }\n                auto& operator--() { return *this -= 1; }\n       \
    \         auto& operator+=(T val) { ft.add(i, j, val); return *this; }\n     \
    \           auto& operator-=(T val) { ft.add(i, j, -val); return *this; }\n  \
    \              auto& operator*=(T val) { T cur = *this; ft.add(i, j, cur * val\
    \ - cur); return *this; }\n                auto& operator/=(T val) { T cur = *this;\
    \ ft.add(i, j, cur / val - cur); return *this; }\n                auto& operator%=(T\
    \ val) { T cur = *this; ft.add(i, j, cur % val - cur); return *this; }\n     \
    \           auto& operator =(T val) { T cur = *this; ft.add(i, j, val - cur);\
    \ return *this; }\n            } obj{ i, j, *this };\n            return obj;\n\
    \        }\n        T operator()(int xl, int xr, int yl, int yr) const { return\
    \ sum(xl, xr, yl, yr); }\n\n    private:\n        int n, m;\n        std::vector<std::vector<T>>\
    \ data;\n\n        T sum(int xr, int yr) const {\n            T s{};\n       \
    \     for (int x = xr; x; x -= x & -x) for (int y = yr; y; y -= y & -y) {\n  \
    \              s += data[x - 1][y - 1];\n            }\n            return s;\n\
    \        }\n    };\n\n} // namespace suisen\n\n#endif // SUISEN_FENWICK_TREE_2D\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree/fenwick_tree_2d.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
documentation_of: library/datastructure/fenwick_tree/fenwick_tree_2d.hpp
layout: document
title: Fenwick Tree 2d
---
## Fenwick Tree 2d