---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
    title: test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/cartesian_tree.hpp\"\n\n\n\n#include\
    \ <array>\n#include <functional>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 9 \"library/datastructure/cartesian_tree.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, typename Comparator, constraints_t<is_comparator<Comparator,\
    \ T>> = nullptr>\nclass CartesianTree {\n    public:\n        CartesianTree(std::vector<T>\
    \ &&a, Comparator comp = Comparator{}) : n(a.size()), comp(comp), par(n, -1) {\n\
    \            for (int i = 1; i < n; ++i) {\n                int p = i - 1, l =\
    \ i;\n                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];\n\
    \                par[l] = i, par[i] = p;\n            }\n        }\n        CartesianTree(const\
    \ std::vector<T> &a, Comparator comp = Comparator{}) : CartesianTree(std::vector<T>(a),\
    \ comp) {}\n\n        struct Tree {\n            const int absent;\n         \
    \   const int root;\n            const std::vector<std::array<int, 2>> g;\n\n\
    \            std::vector<std::pair<int, int>> ranges() const {\n             \
    \   std::vector<std::pair<int, int>> res(g.size());\n                auto dfs\
    \ = [&](auto self, int u) -> void {\n                    res[u] = {u, u + 1};\n\
    \                    auto [l, r] = g[u];\n                    if (l != absent)\
    \ {\n                        self(self, l);\n                        res[u].first\
    \ = res[l].first;\n                    }\n                    if (r != absent)\
    \ {\n                        self(self, r);\n                        res[u].second\
    \ = res[r].second;\n                    }\n                };\n              \
    \  dfs(dfs, root);\n                return res;\n            }\n        };\n\n\
    \        std::vector<std::array<int, 2>> build_tree() const {\n            int\
    \ root = -1;\n            std::vector<std::array<int, 2>> g(n, {-1, -1});\n  \
    \          for (int i = 0; i < n; ++i) {\n                int p = par[i];\n  \
    \              if (p >= 0) {\n                    g[p][p <= i] = i;\n        \
    \        } else {\n                    root = p;\n                }\n        \
    \    }\n            return Tree {-1, root, std::move(g)};\n        }\n\n     \
    \   int parent(int i) const {\n            return par[i];\n        }\n    private:\n\
    \        const int n;\n        const Comparator comp;\n        std::vector<int>\
    \ par;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_CARTESIAN_TREE\n#define SUISEN_CARTESIAN_TREE\n\n#include\
    \ <array>\n#include <functional>\n#include <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, typename Comparator, constraints_t<is_comparator<Comparator,\
    \ T>> = nullptr>\nclass CartesianTree {\n    public:\n        CartesianTree(std::vector<T>\
    \ &&a, Comparator comp = Comparator{}) : n(a.size()), comp(comp), par(n, -1) {\n\
    \            for (int i = 1; i < n; ++i) {\n                int p = i - 1, l =\
    \ i;\n                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];\n\
    \                par[l] = i, par[i] = p;\n            }\n        }\n        CartesianTree(const\
    \ std::vector<T> &a, Comparator comp = Comparator{}) : CartesianTree(std::vector<T>(a),\
    \ comp) {}\n\n        struct Tree {\n            const int absent;\n         \
    \   const int root;\n            const std::vector<std::array<int, 2>> g;\n\n\
    \            std::vector<std::pair<int, int>> ranges() const {\n             \
    \   std::vector<std::pair<int, int>> res(g.size());\n                auto dfs\
    \ = [&](auto self, int u) -> void {\n                    res[u] = {u, u + 1};\n\
    \                    auto [l, r] = g[u];\n                    if (l != absent)\
    \ {\n                        self(self, l);\n                        res[u].first\
    \ = res[l].first;\n                    }\n                    if (r != absent)\
    \ {\n                        self(self, r);\n                        res[u].second\
    \ = res[r].second;\n                    }\n                };\n              \
    \  dfs(dfs, root);\n                return res;\n            }\n        };\n\n\
    \        std::vector<std::array<int, 2>> build_tree() const {\n            int\
    \ root = -1;\n            std::vector<std::array<int, 2>> g(n, {-1, -1});\n  \
    \          for (int i = 0; i < n; ++i) {\n                int p = par[i];\n  \
    \              if (p >= 0) {\n                    g[p][p <= i] = i;\n        \
    \        } else {\n                    root = p;\n                }\n        \
    \    }\n            return Tree {-1, root, std::move(g)};\n        }\n\n     \
    \   int parent(int i) const {\n            return par[i];\n        }\n    private:\n\
    \        const int n;\n        const Comparator comp;\n        std::vector<int>\
    \ par;\n};\n} // namespace suisen\n\n#endif // SUISEN_CARTESIAN_TREE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/cartesian_tree/cartesian_tree.test.cpp
documentation_of: library/datastructure/cartesian_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/cartesian_tree.hpp
- /library/library/datastructure/cartesian_tree.hpp.html
title: library/datastructure/cartesian_tree.hpp
---
