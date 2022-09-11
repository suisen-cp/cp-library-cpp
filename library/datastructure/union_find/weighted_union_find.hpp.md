---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
    title: test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.hatenablog.com/entry/2018/05/30/191943
  bundledCode: "#line 1 \"library/datastructure/union_find/weighted_union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace suisen\
    \ {\n    namespace default_operator {\n        template <typename T>\n       \
    \ auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(const T &x, const T &y) -> decltype(x + y) {\
    \ return x + y; }\n        template <typename T>\n        auto sub(const T &x,\
    \ const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n    namespace default_operator_noref\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 10 \"library/datastructure/union_find/weighted_union_find.hpp\"\
    \n\nnamespace suisen {\n\n    // reference: https://noshi91.hatenablog.com/entry/2018/05/30/191943\n\
    \n    template <typename T, T(*op)(T, T) = default_operator_noref::add<T>, T(*e)()\
    \ = default_operator_noref::zero<T>, T(*neg)(T) = default_operator_noref::neg<T>>\n\
    \        struct WeightedUnionFind {\n            WeightedUnionFind() = default;\n\
    \            explicit WeightedUnionFind(int n) : n(n), par(n), siz(n, 1), value(n,\
    \ e()) {\n                std::iota(par.begin(), par.end(), 0);\n            }\n\
    \            // Get the root of `x`. equivalent to `operator[](x)`\n         \
    \   int root(int x) {\n                while (par[x] != x) {\n               \
    \     int& p = par[x];\n                    value[x] = op(value[p], value[x]);\n\
    \                    x = p = par[p];\n                }\n                return\
    \ x;\n            }\n            // Get the root of `x`. euivalent to `root(x)`\n\
    \            int operator[](int x) {\n                return root(x);\n      \
    \      }\n            // Merge two vertices `x` and `y` with the distance d =\
    \ y - x.\n            bool merge(int x, int y, const T& d) {\n               \
    \ /**\n                 *   [root(x)] ----> [root(y)]\n                 *    \
    \   |     ??=rd     |\n                 *  w(x) |               | w(y)\n     \
    \            *       v               v\n                 *      [x] ---------->\
    \ [y]\n                 *               d\n                 */\n             \
    \   T rd = op(op(weight(x), d), neg(weight(y)));\n                x = root(x),\
    \ y = root(y);\n                if (x == y) return false;\n                if\
    \ (siz[x] < siz[y]) {\n                    std::swap(x, y);\n                \
    \    rd = neg(std::move(rd));\n                }\n                siz[x] += siz[y],\
    \ par[y] = x;\n                value[y] = std::move(rd);\n                return\
    \ true;\n            }\n            // Return the distance d = y - x.\n      \
    \      T diff(int x, int y) {\n                assert(same(x, y));\n         \
    \       return op(neg(weight(x)), weight(y));\n            }\n            // Check\
    \ if `x` and `y` belongs to the same connected component.\n            bool same(int\
    \ x, int y) {\n                return root(x) == root(y);\n            }\n   \
    \         // Get the size of connected componet to which `x` belongs.\n      \
    \      int size(int x) {\n                return siz[root(x)];\n            }\n\
    \            // Get all of connected components.\n            std::vector<std::vector<int>>\
    \ groups() {\n                std::vector<std::vector<int>> res(n);\n        \
    \        for (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n            \
    \    res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g) { return\
    \ g.empty(); }), res.end());\n                return res;\n            }\n   \
    \     private:\n            int n;\n            std::vector<int> par, siz;\n \
    \           std::vector<T> value;\n\n            T weight(int x) {\n         \
    \       T res = e();\n                while (par[x] != x) {\n                \
    \    int& p = par[x];\n                    value[x] = op(value[p], value[x]);\n\
    \                    res = op(value[x], res);\n                    x = p = par[p];\n\
    \                }\n                return res;\n            }\n    };\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_WEIGHTED_UNION_FIND\n#define SUISEN_WEIGHTED_UNION_FIND\n\n\
    #include <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\
    \n#include \"library/util/default_operator.hpp\"\n\nnamespace suisen {\n\n   \
    \ // reference: https://noshi91.hatenablog.com/entry/2018/05/30/191943\n\n   \
    \ template <typename T, T(*op)(T, T) = default_operator_noref::add<T>, T(*e)()\
    \ = default_operator_noref::zero<T>, T(*neg)(T) = default_operator_noref::neg<T>>\n\
    \        struct WeightedUnionFind {\n            WeightedUnionFind() = default;\n\
    \            explicit WeightedUnionFind(int n) : n(n), par(n), siz(n, 1), value(n,\
    \ e()) {\n                std::iota(par.begin(), par.end(), 0);\n            }\n\
    \            // Get the root of `x`. equivalent to `operator[](x)`\n         \
    \   int root(int x) {\n                while (par[x] != x) {\n               \
    \     int& p = par[x];\n                    value[x] = op(value[p], value[x]);\n\
    \                    x = p = par[p];\n                }\n                return\
    \ x;\n            }\n            // Get the root of `x`. euivalent to `root(x)`\n\
    \            int operator[](int x) {\n                return root(x);\n      \
    \      }\n            // Merge two vertices `x` and `y` with the distance d =\
    \ y - x.\n            bool merge(int x, int y, const T& d) {\n               \
    \ /**\n                 *   [root(x)] ----> [root(y)]\n                 *    \
    \   |     ??=rd     |\n                 *  w(x) |               | w(y)\n     \
    \            *       v               v\n                 *      [x] ---------->\
    \ [y]\n                 *               d\n                 */\n             \
    \   T rd = op(op(weight(x), d), neg(weight(y)));\n                x = root(x),\
    \ y = root(y);\n                if (x == y) return false;\n                if\
    \ (siz[x] < siz[y]) {\n                    std::swap(x, y);\n                \
    \    rd = neg(std::move(rd));\n                }\n                siz[x] += siz[y],\
    \ par[y] = x;\n                value[y] = std::move(rd);\n                return\
    \ true;\n            }\n            // Return the distance d = y - x.\n      \
    \      T diff(int x, int y) {\n                assert(same(x, y));\n         \
    \       return op(neg(weight(x)), weight(y));\n            }\n            // Check\
    \ if `x` and `y` belongs to the same connected component.\n            bool same(int\
    \ x, int y) {\n                return root(x) == root(y);\n            }\n   \
    \         // Get the size of connected componet to which `x` belongs.\n      \
    \      int size(int x) {\n                return siz[root(x)];\n            }\n\
    \            // Get all of connected components.\n            std::vector<std::vector<int>>\
    \ groups() {\n                std::vector<std::vector<int>> res(n);\n        \
    \        for (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n            \
    \    res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g) { return\
    \ g.empty(); }), res.end());\n                return res;\n            }\n   \
    \     private:\n            int n;\n            std::vector<int> par, siz;\n \
    \           std::vector<T> value;\n\n            T weight(int x) {\n         \
    \       T res = e();\n                while (par[x] != x) {\n                \
    \    int& p = par[x];\n                    value[x] = op(value[p], value[x]);\n\
    \                    res = op(value[x], res);\n                    x = p = par[p];\n\
    \                }\n                return res;\n            }\n    };\n} // namespace\
    \ suisen\n\n#endif // SUISEN_WEIGHTED_UNION_FIND\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/datastructure/union_find/weighted_union_find.hpp
  requiredBy: []
  timestamp: '2022-06-25 02:26:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
documentation_of: library/datastructure/union_find/weighted_union_find.hpp
layout: document
title: Weighted Union Find
---
## Weighted Union Find

[UnionFindTree に関する知見の諸々](https://noshi91.hatenablog.com/entry/2018/05/30/191943) で「ポテンシャル付きUnionFindTree」と呼ばれているもの。
