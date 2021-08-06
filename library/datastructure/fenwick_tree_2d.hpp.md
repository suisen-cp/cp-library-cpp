---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree_2d.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n\ntemplate <typename T>\nclass FenwickTree2D\
    \ {\n    public:\n        FenwickTree2D() {}\n        explicit FenwickTree2D(int\
    \ n, int m) : n(n), m(m), data(n, std::vector<T>(m, T(0))) {}\n        void add(int\
    \ i, int j, T v) {\n            for (int x = i + 1; x <= n; x += (x & -x)) {\n\
    \                for (int y = j + 1; y <= m; y += (y & -y)) {\n              \
    \      data[x - 1][y - 1] += v;\n                }\n            }\n        }\n\
    \        T sum(int xl, int xr, int yl, int yr) const {\n            return sum(xr,\
    \ yr) - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);\n        }\n        auto operator[](std::pair<int,\
    \ int> index) {\n            auto [i, j] = index;\n            struct {\n    \
    \            int i, j;\n                FenwickTree2D &ft;\n                operator\
    \ T() const { return ft.sum(i, i + 1, j, j + 1); }\n                auto& operator++()\
    \ { return *this += 1; }\n                auto& operator--() { return *this -=\
    \ 1; }\n                auto& operator+=(T val) { ft.add(i, j,  val); return *this;\
    \ }\n                auto& operator-=(T val) { ft.add(i, j, -val); return *this;\
    \ }\n                auto& operator*=(T val) { T cur = *this; ft.add(i, cur *\
    \ val - cur); return *this; }\n                auto& operator/=(T val) { T cur\
    \ = *this; ft.add(i, cur / val - cur); return *this; }\n                auto&\
    \ operator%=(T val) { T cur = *this; ft.add(i, cur % val - cur); return *this;\
    \ }\n                auto& operator =(T val) { T cur = *this; ft.add(i,      \
    \ val - cur); return *this; }\n            } obj {i, j, *this};\n            return\
    \ obj;\n        }\n        T operator()(int xl, int xr, int yl, int yr) const\
    \ { return sum(xl, xr, yl, yr); }\n\n    private:\n        int n, m;\n       \
    \ std::vector<std::vector<T>> data;\n\n        T sum(int xr, int yr) const {\n\
    \            T s(0);\n            for (int x = xr; x; x -= x & -x) {\n       \
    \         for (int y = yr; y; y -= y & -y) {\n                    s += data[x\
    \ - 1][y - 1];\n                }\n            }\n            return s;\n    \
    \    }\n};\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_FENWICK_TREE_2D\n#define SUISEN_FENWICK_TREE_2D\n\n#include\
    \ <vector>\n\nnamespace suisen {\n\ntemplate <typename T>\nclass FenwickTree2D\
    \ {\n    public:\n        FenwickTree2D() {}\n        explicit FenwickTree2D(int\
    \ n, int m) : n(n), m(m), data(n, std::vector<T>(m, T(0))) {}\n        void add(int\
    \ i, int j, T v) {\n            for (int x = i + 1; x <= n; x += (x & -x)) {\n\
    \                for (int y = j + 1; y <= m; y += (y & -y)) {\n              \
    \      data[x - 1][y - 1] += v;\n                }\n            }\n        }\n\
    \        T sum(int xl, int xr, int yl, int yr) const {\n            return sum(xr,\
    \ yr) - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);\n        }\n        auto operator[](std::pair<int,\
    \ int> index) {\n            auto [i, j] = index;\n            struct {\n    \
    \            int i, j;\n                FenwickTree2D &ft;\n                operator\
    \ T() const { return ft.sum(i, i + 1, j, j + 1); }\n                auto& operator++()\
    \ { return *this += 1; }\n                auto& operator--() { return *this -=\
    \ 1; }\n                auto& operator+=(T val) { ft.add(i, j,  val); return *this;\
    \ }\n                auto& operator-=(T val) { ft.add(i, j, -val); return *this;\
    \ }\n                auto& operator*=(T val) { T cur = *this; ft.add(i, cur *\
    \ val - cur); return *this; }\n                auto& operator/=(T val) { T cur\
    \ = *this; ft.add(i, cur / val - cur); return *this; }\n                auto&\
    \ operator%=(T val) { T cur = *this; ft.add(i, cur % val - cur); return *this;\
    \ }\n                auto& operator =(T val) { T cur = *this; ft.add(i,      \
    \ val - cur); return *this; }\n            } obj {i, j, *this};\n            return\
    \ obj;\n        }\n        T operator()(int xl, int xr, int yl, int yr) const\
    \ { return sum(xl, xr, yl, yr); }\n\n    private:\n        int n, m;\n       \
    \ std::vector<std::vector<T>> data;\n\n        T sum(int xr, int yr) const {\n\
    \            T s(0);\n            for (int x = xr; x; x -= x & -x) {\n       \
    \         for (int y = yr; y; y -= y & -y) {\n                    s += data[x\
    \ - 1][y - 1];\n                }\n            }\n            return s;\n    \
    \    }\n};\n\n} // namespace suisen\n\n#endif // SUISEN_FENWICK_TREE_2D\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree_2d.hpp
  requiredBy: []
  timestamp: '2021-08-06 13:44:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/fenwick_tree_2d.hpp
layout: document
redirect_from:
- /library/library/datastructure/fenwick_tree_2d.hpp
- /library/library/datastructure/fenwick_tree_2d.hpp.html
title: library/datastructure/fenwick_tree_2d.hpp
---
