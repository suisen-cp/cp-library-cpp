---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/weighted_union_find.hpp
    title: Weighted Union Find
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
  bundledCode: "#line 1 \"test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/union_find/weighted_union_find.hpp\"\
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
    \ suisen\n\n\n#line 6 \"test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp\"\
    \nusing suisen::WeightedUnionFind;\n\nlong long op(long long x, long long y) {\n\
    \    return x + y;\n}\nlong long e() {\n    return 0;\n}\nlong long neg(long long\
    \ x) {\n    return -x;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    WeightedUnionFind<long\
    \ long, op, e, neg> uf(n);\n    for (int i = 0; i < q; ++i) {\n        int t;\n\
    \        std::cin >> t;\n        if (t == 0) {\n            int x, y, z;\n   \
    \         std::cin >> x >> y >> z;\n            uf.merge(x, y, z);\n        }\
    \ else {\n            int x, y;\n            std::cin >> x >> y;\n           \
    \ if (uf.same(x, y)) {\n                std::cout << uf.diff(x, y) << '\\n';\n\
    \            } else {\n                std::cout << '?' << '\\n';\n          \
    \  }\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/union_find/weighted_union_find.hpp\"\
    \nusing suisen::WeightedUnionFind;\n\nlong long op(long long x, long long y) {\n\
    \    return x + y;\n}\nlong long e() {\n    return 0;\n}\nlong long neg(long long\
    \ x) {\n    return -x;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    WeightedUnionFind<long\
    \ long, op, e, neg> uf(n);\n    for (int i = 0; i < q; ++i) {\n        int t;\n\
    \        std::cin >> t;\n        if (t == 0) {\n            int x, y, z;\n   \
    \         std::cin >> x >> y >> z;\n            uf.merge(x, y, z);\n        }\
    \ else {\n            int x, y;\n            std::cin >> x >> y;\n           \
    \ if (uf.same(x, y)) {\n                std::cout << uf.diff(x, y) << '\\n';\n\
    \            } else {\n                std::cout << '?' << '\\n';\n          \
    \  }\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/union_find/weighted_union_find.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
  requiredBy: []
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
- /verify/test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp.html
title: test/src/datastructure/union_find/weighted_union_find/DSL_1_B.test.cpp
---
