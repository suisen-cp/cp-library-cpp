---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/number/enumerate_quotient/divide_both.test.cpp
    title: test/src/number/enumerate_quotient/divide_both.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/enumerate_quotient/enumerate_quotients.test.cpp
    title: test/src/number/enumerate_quotient/enumerate_quotients.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Runs f(q) for each q>0 s.t. (there exists an integer x s.t. floor(n/x)=q)
      in ascending order.
    links: []
  bundledCode: "#line 1 \"library/number/enumerate_quotient.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <limits>\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * @return #{\
    \ d>0 | exists an integer x s.t. floor(n/x)=d }\n    */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ quotient_num(const T& n) {\n        const T h = sqrtl(n);\n        return 2\
    \ * h - (h * (h + 1) > n);\n    }\n\n    /**\n     * @brief Runs f(q) for each\
    \ q>0 s.t. (there exists an integer x s.t. floor(n/x)=q) in ascending order.\n\
    \     * @tparam T integer type\n     */\n    template <typename T, typename Fun,\n\
    \        std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_invocable<Fun,\
    \ T>>, std::nullptr_t> = nullptr>\n    void foreach_quotients(const T &n, Fun\
    \ &&f) {\n        assert(0 <= n);\n        if (n == 0) return;\n        const\
    \ int h = sqrtl(n), m = 2 * h - (h == n / h);\n        for (int l = 1; l <= h;\
    \ ++l) f(l);\n        if (n < 1LL << 53) { // the size of the fraction part of\
    \ double is 52=53-1.\n            for (int l = h - (m & 1); l >= 1; --l) f(static_cast<T>(static_cast<double>(n)\
    \ / l));\n        } else {\n            for (int l = h - (m & 1); l >= 1; --l)\
    \ f(n / l);\n        }\n    }\n    /**\n     * @brief Calculates an ascending\
    \ vector of S = { d>0 | exists an integer x s.t. floor(n / x) = d } in O(\u221A\
    n) time.\n     * @tparam T integer type\n     * @return an ascending vector S\
    \ = { d>0 | exists an integer x s.t. floor(n / x) = d }.\n     */\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::vector<T> enumerate_quotients(T n) {\n        std::vector<T> q(quotient_num(n));\n\
    \        auto it = q.begin();\n        foreach_quotients(n, [&it](const T& v)\
    \ { *it++ = v; });\n        return q;\n    }\n\n    /**\n     * @brief Calculates\
    \ vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in\
    \ O(\u221An) time.\n     * @tparam T integer type\n     * @return vector of {\
    \ l = min S, r = max S, q }, where S = { d | floor(n / d) = q }.\n     * It is\
    \ guaranteed that l, r is ascending and q is descending.\n     */\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::vector<std::tuple<T, T, T>> quotient_ranges(T n) {\n        assert(0\
    \ <= n);\n        const std::vector<T> qs = enumerate_quotients(n);\n        const\
    \ int m = qs.size();\n        std::vector<std::tuple<T, T, T>> res(qs.size());\n\
    \        for (int i = 0; i < m; ++i) {\n            T l = i ? qs[i - 1] + 1 :\
    \ 1, r = qs[i], q = qs[m - i - 1];\n            res[i] = std::make_tuple(l, r,\
    \ q);\n        }\n        return res;\n    }\n\n    /**\n     * @brief Calculates\
    \ vector of { l = min S, r = max S, (q[0], ..., q[k-1]) }, where S = { d | floor(vs[i]\
    \ / d) = q[i] for i = 0,...,k-1 } in O(|vs| * \u03A3\u221Av) time.\n     * @tparam\
    \ Container vector or array\n     * @return vector of { l = min S, r = max S,\
    \ (q[0], ..., q[k-1]) }, where S is { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1\
    \ }.\n     * It is guaranteed that l, r is ascending and q[i] is descending. \n\
    \     */\n    template <typename Container, std::enable_if_t<std::is_integral_v<typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>> multiple_quotients_ranges(const\
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
    #include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <limits>\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * @return\
    \ #{ d>0 | exists an integer x s.t. floor(n/x)=d }\n    */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ quotient_num(const T& n) {\n        const T h = sqrtl(n);\n        return 2\
    \ * h - (h * (h + 1) > n);\n    }\n\n    /**\n     * @brief Runs f(q) for each\
    \ q>0 s.t. (there exists an integer x s.t. floor(n/x)=q) in ascending order.\n\
    \     * @tparam T integer type\n     */\n    template <typename T, typename Fun,\n\
    \        std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_invocable<Fun,\
    \ T>>, std::nullptr_t> = nullptr>\n    void foreach_quotients(const T &n, Fun\
    \ &&f) {\n        assert(0 <= n);\n        if (n == 0) return;\n        const\
    \ int h = sqrtl(n), m = 2 * h - (h == n / h);\n        for (int l = 1; l <= h;\
    \ ++l) f(l);\n        if (n < 1LL << 53) { // the size of the fraction part of\
    \ double is 52=53-1.\n            for (int l = h - (m & 1); l >= 1; --l) f(static_cast<T>(static_cast<double>(n)\
    \ / l));\n        } else {\n            for (int l = h - (m & 1); l >= 1; --l)\
    \ f(n / l);\n        }\n    }\n    /**\n     * @brief Calculates an ascending\
    \ vector of S = { d>0 | exists an integer x s.t. floor(n / x) = d } in O(\u221A\
    n) time.\n     * @tparam T integer type\n     * @return an ascending vector S\
    \ = { d>0 | exists an integer x s.t. floor(n / x) = d }.\n     */\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::vector<T> enumerate_quotients(T n) {\n        std::vector<T> q(quotient_num(n));\n\
    \        auto it = q.begin();\n        foreach_quotients(n, [&it](const T& v)\
    \ { *it++ = v; });\n        return q;\n    }\n\n    /**\n     * @brief Calculates\
    \ vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in\
    \ O(\u221An) time.\n     * @tparam T integer type\n     * @return vector of {\
    \ l = min S, r = max S, q }, where S = { d | floor(n / d) = q }.\n     * It is\
    \ guaranteed that l, r is ascending and q is descending.\n     */\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::vector<std::tuple<T, T, T>> quotient_ranges(T n) {\n        assert(0\
    \ <= n);\n        const std::vector<T> qs = enumerate_quotients(n);\n        const\
    \ int m = qs.size();\n        std::vector<std::tuple<T, T, T>> res(qs.size());\n\
    \        for (int i = 0; i < m; ++i) {\n            T l = i ? qs[i - 1] + 1 :\
    \ 1, r = qs[i], q = qs[m - i - 1];\n            res[i] = std::make_tuple(l, r,\
    \ q);\n        }\n        return res;\n    }\n\n    /**\n     * @brief Calculates\
    \ vector of { l = min S, r = max S, (q[0], ..., q[k-1]) }, where S = { d | floor(vs[i]\
    \ / d) = q[i] for i = 0,...,k-1 } in O(|vs| * \u03A3\u221Av) time.\n     * @tparam\
    \ Container vector or array\n     * @return vector of { l = min S, r = max S,\
    \ (q[0], ..., q[k-1]) }, where S is { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1\
    \ }.\n     * It is guaranteed that l, r is ascending and q[i] is descending. \n\
    \     */\n    template <typename Container, std::enable_if_t<std::is_integral_v<typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n    std::vector<std::tuple<typename\
    \ Container::value_type, typename Container::value_type, Container>> multiple_quotients_ranges(const\
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
  timestamp: '2023-05-11 13:32:09+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/number/enumerate_quotient/enumerate_quotients.test.cpp
  - test/src/number/enumerate_quotient/divide_both.test.cpp
documentation_of: library/number/enumerate_quotient.hpp
layout: document
title: "\u5546\u5217\u6319"
---
## 商列挙
