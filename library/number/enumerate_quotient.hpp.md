---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/enumerate_quotient/divide_both.test.cpp
    title: test/src/number/enumerate_quotient/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Calculates vector of { l = min S, r = max S, q }, where S = {\
      \ d | floor(n / d) = q } in O(\u221An) time."
    links: []
  bundledCode: "#line 1 \"library/number/enumerate_quotient.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <tuple>\n#include\
    \ <vector>\n\nnamespace suisen {\n    /**\n     * @brief Calculates vector of\
    \ { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in O(\u221A\
    n) time.\n     * @tparam T integer type\n     * @return vector of { l = min S,\
    \ r = max S, q }, where S = { d | floor(n / d) = q }.\n     * It is guaranteed\
    \ that l, r is ascending and q is descending.\n     */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<T,\
    \ T, T>> enumerate_quotients(T n) {\n        assert(0 <= n);\n        std::vector<std::tuple<T,\
    \ T, T>> res;\n        for (T l = 1, r = 1; l <= n; l = r + 1) {\n           \
    \ T q = n / l;\n            res.emplace_back(l, r = n / q, q);\n        }\n  \
    \      return res;\n    }\n\n    /**\n     * @brief Calculates vector of { l =\
    \ min S, r = max S, (q[0], ..., q[k-1]) }, where S = { d | floor(vs[i] / d) =\
    \ q[i] for i = 0,...,k-1 } in O(|vs| * \u03A3\u221Av) time.\n     * @tparam Container\
    \ vector or array\n     * @return vector of { l = min S, r = max S, (q[0], ...,\
    \ q[k-1]) }, where S is { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1 }.\n \
    \    * It is guaranteed that l, r is ascending and q[i] is descending. \n    \
    \ */\n    template <typename Container, std::enable_if_t<std::is_integral_v<typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>> enumerate_multiple_quotients(const\
    \ Container& vs) {\n        using T = typename Container::value_type;\n      \
    \  int n = vs.size();\n        T max_val = *std::max_element(vs.begin(), vs.end());\n\
    \        assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n        std::vector<std::tuple<T,\
    \ T, Container>> res;\n        for (T l = 1, r = 1; l <= max_val; l = r + 1) {\n\
    \            Container qs{};\n            if constexpr (std::is_same_v<Container,\
    \ std::vector<T>>) qs.resize(n);\n            r = std::numeric_limits<T>::max();\n\
    \            for (int i = 0; i < n; ++i) {\n                qs[i] = vs[i] / l;\n\
    \                r = std::min(r, qs[i] == 0 ? std::numeric_limits<T>::max() :\
    \ vs[i] / qs[i]);\n            }\n            res.emplace_back(l, r, std::move(qs));\n\
    \        }\n        return res;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ENUMERATE_QUOTIENT\n#define SUISEN_ENUMERATE_QUOTIENT\n\n\
    #include <algorithm>\n#include <cassert>\n#include <limits>\n#include <tuple>\n\
    #include <vector>\n\nnamespace suisen {\n    /**\n     * @brief Calculates vector\
    \ of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in O(\u221A\
    n) time.\n     * @tparam T integer type\n     * @return vector of { l = min S,\
    \ r = max S, q }, where S = { d | floor(n / d) = q }.\n     * It is guaranteed\
    \ that l, r is ascending and q is descending.\n     */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<T,\
    \ T, T>> enumerate_quotients(T n) {\n        assert(0 <= n);\n        std::vector<std::tuple<T,\
    \ T, T>> res;\n        for (T l = 1, r = 1; l <= n; l = r + 1) {\n           \
    \ T q = n / l;\n            res.emplace_back(l, r = n / q, q);\n        }\n  \
    \      return res;\n    }\n\n    /**\n     * @brief Calculates vector of { l =\
    \ min S, r = max S, (q[0], ..., q[k-1]) }, where S = { d | floor(vs[i] / d) =\
    \ q[i] for i = 0,...,k-1 } in O(|vs| * \u03A3\u221Av) time.\n     * @tparam Container\
    \ vector or array\n     * @return vector of { l = min S, r = max S, (q[0], ...,\
    \ q[k-1]) }, where S is { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1 }.\n \
    \    * It is guaranteed that l, r is ascending and q[i] is descending. \n    \
    \ */\n    template <typename Container, std::enable_if_t<std::is_integral_v<typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>> enumerate_multiple_quotients(const\
    \ Container& vs) {\n        using T = typename Container::value_type;\n      \
    \  int n = vs.size();\n        T max_val = *std::max_element(vs.begin(), vs.end());\n\
    \        assert(*std::min_element(vs.begin(), vs.end()) >= 0);\n        std::vector<std::tuple<T,\
    \ T, Container>> res;\n        for (T l = 1, r = 1; l <= max_val; l = r + 1) {\n\
    \            Container qs{};\n            if constexpr (std::is_same_v<Container,\
    \ std::vector<T>>) qs.resize(n);\n            r = std::numeric_limits<T>::max();\n\
    \            for (int i = 0; i < n; ++i) {\n                qs[i] = vs[i] / l;\n\
    \                r = std::min(r, qs[i] == 0 ? std::numeric_limits<T>::max() :\
    \ vs[i] / qs[i]);\n            }\n            res.emplace_back(l, r, std::move(qs));\n\
    \        }\n        return res;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_ENUMERATE_QUOTIENT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/enumerate_quotient.hpp
  requiredBy: []
  timestamp: '2022-10-31 01:25:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/enumerate_quotient/divide_both.test.cpp
documentation_of: library/number/enumerate_quotient.hpp
layout: document
title: "\u5546\u5217\u6319"
---
## 商列挙
