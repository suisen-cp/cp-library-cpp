---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/datastructure/cartesian_tree.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <functional>\n#include <vector>\n\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\n\
    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\n\
    template <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto)\
    \ constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n\
    \        return std::forward<Then>(then);\n    } else {\n        return std::forward<OrElse>(or_else);\n\
    \    }\n}\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 10 \"library/datastructure/cartesian_tree.hpp\"\
    \n\nnamespace suisen {\n    struct CartesianTree : public std::vector<std::array<int,\
    \ 2>> {\n        using base_type = std::vector<std::array<int, 2>>;\n\n      \
    \  static constexpr int absent = -1;\n\n        const int root;\n\n        CartesianTree()\
    \ : base_type(), root(0) {}\n        CartesianTree(int root, const base_type&\
    \ g) : base_type(g), root(root) {}\n        CartesianTree(int root, base_type&&\
    \ g) : base_type(std::move(g)), root(root) {}\n\n        auto ranges() const {\n\
    \            std::vector<std::pair<int, int>> res;\n            res.reserve(size());\n\
    \            auto rec = [&](auto rec, int l, int m, int r) -> void {\n       \
    \         if (m == absent) return;\n                const auto& [lm, rm] = (*this)[m];\n\
    \                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm,\
    \ r);\n            };\n            rec(rec, 0, root, size());\n            return\
    \ res;\n        }\n    };\n\n    template <typename T, typename Comparator, constraints_t<is_comparator<Comparator,\
    \ T>> = nullptr>\n    struct CartesianTreeBuilder {\n        CartesianTreeBuilder()\
    \ {}\n        template <typename RandomAccessibleContainer>\n        CartesianTreeBuilder(const\
    \ RandomAccessibleContainer& a, Comparator comp = Comparator{}) : n(a.size()),\
    \ comp(comp), par(calc_par(a, comp)) {}\n\n        CartesianTree build() const\
    \ {\n            int root = -1;\n            std::vector<std::array<int, 2>> g(n,\
    \ { CartesianTree::absent, CartesianTree::absent });\n            for (int i =\
    \ 0; i < n; ++i) {\n                int p = par[i];\n                (p >= 0 ?\
    \ g[p][p <= i] : root) = i;\n            }\n            return CartesianTree{\
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
    \        }\n    };\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<int> a(n);\n    for (int &e :\
    \ a) std::cin >> e;\n    suisen::CartesianTreeBuilder<int, std::less<int>> t(a);\n\
    \    for (int i = 0; i < n; ++i) {\n        int p = t.parent(i);\n        std::cout\
    \ << (p < 0 ? i : p) << \" \\n\"[i == n - 1];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <iostream>\n\n#include \"library/datastructure/cartesian_tree.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<int> a(n);\n    for (int &e : a) std::cin\
    \ >> e;\n    suisen::CartesianTreeBuilder<int, std::less<int>> t(a);\n    for\
    \ (int i = 0; i < n; ++i) {\n        int p = t.parent(i);\n        std::cout <<\
    \ (p < 0 ? i : p) << \" \\n\"[i == n - 1];\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/cartesian_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2022-01-15 03:56:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
- /verify/test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp.html
title: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
---
