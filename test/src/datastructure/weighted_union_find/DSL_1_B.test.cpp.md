---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/weighted_union_find.hpp
    title: library/datastructure/weighted_union_find.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
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
  bundledCode: "#line 1 \"test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/weighted_union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 10\
    \ \"library/datastructure/weighted_union_find.hpp\"\n\nnamespace suisen {\n\n\
    // reference: https://noshi91.hatenablog.com/entry/2018/05/30/191943\n\ntemplate\
    \ <\n    typename T, typename Op = std::plus<T>, typename Inv = std::negate<T>,\n\
    \    constraints_t<is_uni_op<Inv, T>, is_bin_op<Op, T>> = nullptr\n>\nclass WeightedUnionFind\
    \ {\n    public:\n        WeightedUnionFind() {}\n        explicit WeightedUnionFind(int\
    \ n, const T &e = T(0)) : n(n), par(n), siz(n, 1), e(e), value(n, e) {\n     \
    \       std::iota(par.begin(), par.end(), 0);\n        }\n        WeightedUnionFind(int\
    \ n, const T &e, Op op, Inv inv) : n(n), par(n), siz(n, 1), e(e), value(n, e),\
    \ op(op), inv(inv) {\n            std::iota(par.begin(), par.end(), 0);\n    \
    \    }\n        // Get the root of `x`. equivalent to `operator[](x)`\n      \
    \  int root(int x) {\n            while (par[x] != x) {\n                int &p\
    \ = par[x];\n                value[x] = op(value[p], value[x]);\n            \
    \    x = p = par[p];\n            }\n            return x;\n        }\n      \
    \  // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y` with the distance d = y - x.\n        bool merge(int x, int y, const\
    \ T &d) {\n            /**\n             *   [root(x)] ----> [root(y)]  \n   \
    \          *       |     ??=rd     |      \n             *  w(x) |           \
    \    | w(y) \n             *       v               v      \n             *   \
    \   [x] ----------> [y]     \n             *               d              \n \
    \            */\n            T rd = op(op(weight(x), d), inv(weight(y)));\n  \
    \          x = root(x), y = root(y);\n            if (x == y) return false;\n\
    \            if (siz[x] < siz[y]) {\n                std::swap(x, y);\n      \
    \          rd = inv(std::move(rd));\n            }\n            siz[x] += siz[y],\
    \ par[y] = x;\n            value[y] = std::move(rd);\n            return true;\n\
    \        }\n        // Return the distance d = y - x.\n        T diff(int x, int\
    \ y) {\n            assert(same(x, y));\n            return op(inv(weight(x)),\
    \ weight(y));\n        }\n        // Check if `x` and `y` belongs to the same\
    \ connected component.\n        bool same(int x, int y) {\n            return\
    \ root(x) == root(y);\n        }\n        // Get the size of connected componet\
    \ to which `x` belongs.\n        int size(int x) {\n            return siz[root(x)];\n\
    \        }\n        // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(n);\n            for\
    \ (int i = 0; i < n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto &g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n    private:\n        int n;\n        std::vector<int>\
    \ par, siz;\n        T e;\n        std::vector<T> value;\n        Op op;\n   \
    \     Inv inv;\n\n        T weight(int x) {\n            T res = e;\n        \
    \    while (par[x] != x) {\n                int &p = par[x];\n               \
    \ value[x] = op(value[p], value[x]);\n                res = op(value[x], res);\n\
    \                x = p = par[p];\n            }\n            return res;\n   \
    \     }\n};\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp\"\
    \nusing suisen::WeightedUnionFind;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    WeightedUnionFind<long\
    \ long, std::plus<long long>, std::negate<long long>> uf(n);\n    for (int i =\
    \ 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n        if (t == 0)\
    \ {\n            int x, y, z;\n            std::cin >> x >> y >> z;\n        \
    \    uf.merge(x, y, z);\n        } else {\n            int x, y;\n           \
    \ std::cin >> x >> y;\n            if (uf.same(x, y)) {\n                std::cout\
    \ << uf.diff(x, y) << '\\n';\n            } else {\n                std::cout\
    \ << '?' << '\\n';\n            }\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/weighted_union_find.hpp\"\
    \nusing suisen::WeightedUnionFind;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    WeightedUnionFind<long\
    \ long, std::plus<long long>, std::negate<long long>> uf(n);\n    for (int i =\
    \ 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n        if (t == 0)\
    \ {\n            int x, y, z;\n            std::cin >> x >> y >> z;\n        \
    \    uf.merge(x, y, z);\n        } else {\n            int x, y;\n           \
    \ std::cin >> x >> y;\n            if (uf.same(x, y)) {\n                std::cout\
    \ << uf.diff(x, y) << '\\n';\n            } else {\n                std::cout\
    \ << '?' << '\\n';\n            }\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/weighted_union_find.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp
  requiredBy: []
  timestamp: '2021-07-25 09:49:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp
- /verify/test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp.html
title: test/src/datastructure/weighted_union_find/DSL_1_B.test.cpp
---
