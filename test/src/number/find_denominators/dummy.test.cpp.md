---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/find_denominators.hpp
    title: "\u5206\u5B50\u3068\u5546\u304B\u3089\u5206\u6BCD\u3068\u3057\u3066\u3042\
      \u308A\u3046\u308B\u7BC4\u56F2\u3092\u8A08\u7B97"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/number/find_denominators/dummy.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <cassert>\n#include <iostream>\n\n#line 1 \"library/number/find_denominators.hpp\"\
    \n\n\n\n#include <limits>\n#include <optional>\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    /**\n     * @brief Calculates { min S, max S }, where S = { x>0\
    \ | floor(n/x)=q } in O(1) time.\n     * @tparam T integer type\n     * @param\
    \ n numerator\n     * @param q quotient (round down)\n     * @param max_val upper\
    \ bound (closed)\n     * @return { min S, max S } if S is not empty, otherwise\
    \ std::nullopt\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::optional<std::pair<T, T>> fld_denominators_positive(T\
    \ n, T q, T max_val = std::numeric_limits<T>::max()) {\n        T l, r;\n    \
    \    if (q >= 0) {\n            if (n < 0) return std::nullopt;\n            //\
    \ cld(n + 1, q + 1) <= x <= fld(n, q)\n            l = (n + 1 + q) / (q + 1),\
    \ r = q == 0 ? max_val : std::min(max_val, n / q);\n        } else {\n       \
    \     if (n >= 0) return std::nullopt;\n            // cld(n, q) <= x <= fld(n\
    \ + 1, q + 1)\n            l = (n + q + 1) / q, r = q == -1 ? max_val : std::min(max_val,\
    \ (n + 1) / (q + 1));\n        }\n        if (l <= r) return std::make_pair(l,\
    \ r);\n        else        return std::nullopt;\n    }\n    /**\n     * @brief\
    \ Calculates { min S, max S }, where S = { x<0 | floor(n/x)=q } in O(1) time.\n\
    \     * @tparam T integer type\n     * @param n numerator\n     * @param q quotient\
    \ (round down)\n     * @param min_val lower bound (closed)\n     * @return { min\
    \ S, max S } if S is not empty, otherwise std::nullopt\n     */\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::optional<std::pair<T, T>> fld_denominators_negative(T n, T q, T min_val\
    \ = std::numeric_limits<T>::min()) {\n        T l, r;\n        if (q >= 0) {\n\
    \            if (n > 0) return std::nullopt;\n            // cld(n, q) <= x <=\
    \ fld(n - 1, q + 1)\n            l = q == 0 ? min_val : std::max(min_val, n /\
    \ q), r = (n - 1 - q) / (q + 1);\n        } else {\n            if (n <= 0) return\
    \ std::nullopt;\n            // cld(n - 1, q + 1) <= x <= fld(n, q)\n        \
    \    l = q == -1 ? min_val : std::max(min_val, (n - 1) / (q + 1)), r = (n - q\
    \ - 1) / q;\n        }\n        if (l <= r) return std::make_pair(l, r);\n   \
    \     else        return std::nullopt;\n    }\n    /**\n     * @brief Calculates\
    \ { min S, max S }, where S = { x>0 | ceil(n/x)=q } in O(1) time.\n     * @tparam\
    \ T integer type\n     * @param n numerator\n     * @param q quotient (round down)\n\
    \     * @param max_val upper bound (closed)\n     * @return { min S, max S } if\
    \ S is not empty, otherwise std::nullopt\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::optional<std::pair<T, T>> cld_denominators_positive(T\
    \ n, T q, T max_val = std::numeric_limits<T>::max()) {\n        T l, r;\n    \
    \    if (q > 0) {\n            if (n <= 0) return std::nullopt;\n            l\
    \ = (n + q - 1) / q, r = q == 1 ? max_val : std::min(max_val, (n - 1) / (q - 1));\n\
    \        } else {\n            if (n > 0) return std::nullopt;\n            l\
    \ = (n - 1 + q) / (q - 1), r = q == 0 ? max_val : std::min(max_val, n / q);\n\
    \        }\n        if (l <= r) return std::make_pair(l, r);\n        else   \
    \     return std::nullopt;\n    }\n    /**\n     * @brief Calculates { min S,\
    \ max S }, where S = { x<0 | ceil(n/x)=q } in O(1) time.\n     * @tparam T integer\
    \ type\n     * @param n numerator\n     * @param q quotient (round down)\n   \
    \  * @param min_val lower bound (closed)\n     * @return { min S, max S } if S\
    \ is not empty, otherwise std::nullopt\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::optional<std::pair<T, T>> cld_denominators_negative(T\
    \ n, T q, T min_val = std::numeric_limits<T>::min()) {\n        T l, r;\n    \
    \    if (q > 0) {\n            if (n >= 0) return std::nullopt;\n            l\
    \ = q == 1 ? min_val : std::max(min_val, (n + 1) / (q - 1)), r = (n - q + 1) /\
    \ q;\n        } else {\n            if (n < 0) return std::nullopt;\n        \
    \    l = q == 0 ? min_val : std::max(min_val, n / q), r = (n + 1 - q) / (q - 1);\n\
    \        }\n        if (l <= r) return std::make_pair(l, r);\n        else   \
    \     return std::nullopt;\n    }\n} // namespace suisen\n\n\n#line 7 \"test/src/number/find_denominators/dummy.test.cpp\"\
    \n\nusing suisen::fld_denominators_positive;\nusing suisen::fld_denominators_negative;\n\
    using suisen::cld_denominators_positive;\nusing suisen::cld_denominators_negative;\n\
    \ntemplate <typename T>\nconstexpr inline int pow_m1(T n) {\n    return -(n &\
    \ 1) | 1;\n}\ntemplate <>\nconstexpr inline int pow_m1<bool>(bool n) {\n    return\
    \ -int(n) | 1;\n}\n\ntemplate <typename T>\nconstexpr inline T fld(const T x,\
    \ const T y) {\n    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) /\
    \ y;\n}\ntemplate <typename T>\nconstexpr inline T cld(const T x, const T y) {\n\
    \    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\nbool\
    \ in(const std::optional<std::pair<int, int>> &r, int x) {\n    return r.has_value()\
    \ and r->first <= x and x <= r->second;\n}\nbool out(const std::optional<std::pair<int,\
    \ int>> &r, int x) {\n    return not r.has_value() or x < r->first or x > r->second;\n\
    }\n\nvoid cld_test(int n, int q) {\n    auto res_pos = cld_denominators_positive(n,\
    \ q, 100);\n    if (res_pos.has_value()) {\n        auto [l, r] = *res_pos;\n\
    \        assert(1 <= l and r <= 100);\n    }\n    for (int x = 1; x <= 100; ++x)\
    \ {\n        if (not (cld(n, x) == q ? in : out)(res_pos, x)) {\n            assert(false);\n\
    \        }\n    }\n\n    auto res_neg = cld_denominators_negative(n, q, -100);\n\
    \    if (res_neg.has_value()) {\n        auto [l, r] = *res_neg;\n        assert(-100\
    \ <= l and r <= -1);\n    }\n    for (int x = -100; x <= -1; ++x) {\n        if\
    \ (not (cld(n, x) == q ? in : out)(res_neg, x)) {\n            assert(false);\n\
    \        }\n    }\n}\n\nvoid fld_test(int n, int q) {\n    auto res_pos = fld_denominators_positive(n,\
    \ q, 100);\n    if (res_pos.has_value()) {\n        auto [l, r] = *res_pos;\n\
    \        assert(1 <= l and r <= 100);\n    }\n    for (int x = 1; x <= 100; ++x)\
    \ {\n        if (not (fld(n, x) == q ? in : out)(res_pos, x)) {\n            assert(false);\n\
    \        }\n    }\n\n    auto res_neg = fld_denominators_negative(n, q, -100);\n\
    \    if (res_neg.has_value()) {\n        auto [l, r] = *res_neg;\n        assert(-100\
    \ <= l and r <= -1);\n    }\n    for (int x = -100; x <= -1; ++x) {\n        if\
    \ (not (fld(n, x) == q ? in : out)(res_neg, x)) {\n            assert(false);\n\
    \        }\n    }\n}\n\nint main() {\n    for (int n = -100; n <= 100; ++n) {\n\
    \        for (int q = -101; q <= 101; ++q) {\n            cld_test(n, q);\n  \
    \          fld_test(n, q);\n        }\n    }\n\n    std::cout << \"Hello World\"\
    \ << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <cassert>\n#include <iostream>\n\n#include \"library/number/find_denominators.hpp\"\
    \n\nusing suisen::fld_denominators_positive;\nusing suisen::fld_denominators_negative;\n\
    using suisen::cld_denominators_positive;\nusing suisen::cld_denominators_negative;\n\
    \ntemplate <typename T>\nconstexpr inline int pow_m1(T n) {\n    return -(n &\
    \ 1) | 1;\n}\ntemplate <>\nconstexpr inline int pow_m1<bool>(bool n) {\n    return\
    \ -int(n) | 1;\n}\n\ntemplate <typename T>\nconstexpr inline T fld(const T x,\
    \ const T y) {\n    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) /\
    \ y;\n}\ntemplate <typename T>\nconstexpr inline T cld(const T x, const T y) {\n\
    \    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;\n}\n\nbool\
    \ in(const std::optional<std::pair<int, int>> &r, int x) {\n    return r.has_value()\
    \ and r->first <= x and x <= r->second;\n}\nbool out(const std::optional<std::pair<int,\
    \ int>> &r, int x) {\n    return not r.has_value() or x < r->first or x > r->second;\n\
    }\n\nvoid cld_test(int n, int q) {\n    auto res_pos = cld_denominators_positive(n,\
    \ q, 100);\n    if (res_pos.has_value()) {\n        auto [l, r] = *res_pos;\n\
    \        assert(1 <= l and r <= 100);\n    }\n    for (int x = 1; x <= 100; ++x)\
    \ {\n        if (not (cld(n, x) == q ? in : out)(res_pos, x)) {\n            assert(false);\n\
    \        }\n    }\n\n    auto res_neg = cld_denominators_negative(n, q, -100);\n\
    \    if (res_neg.has_value()) {\n        auto [l, r] = *res_neg;\n        assert(-100\
    \ <= l and r <= -1);\n    }\n    for (int x = -100; x <= -1; ++x) {\n        if\
    \ (not (cld(n, x) == q ? in : out)(res_neg, x)) {\n            assert(false);\n\
    \        }\n    }\n}\n\nvoid fld_test(int n, int q) {\n    auto res_pos = fld_denominators_positive(n,\
    \ q, 100);\n    if (res_pos.has_value()) {\n        auto [l, r] = *res_pos;\n\
    \        assert(1 <= l and r <= 100);\n    }\n    for (int x = 1; x <= 100; ++x)\
    \ {\n        if (not (fld(n, x) == q ? in : out)(res_pos, x)) {\n            assert(false);\n\
    \        }\n    }\n\n    auto res_neg = fld_denominators_negative(n, q, -100);\n\
    \    if (res_neg.has_value()) {\n        auto [l, r] = *res_neg;\n        assert(-100\
    \ <= l and r <= -1);\n    }\n    for (int x = -100; x <= -1; ++x) {\n        if\
    \ (not (fld(n, x) == q ? in : out)(res_neg, x)) {\n            assert(false);\n\
    \        }\n    }\n}\n\nint main() {\n    for (int n = -100; n <= 100; ++n) {\n\
    \        for (int q = -101; q <= 101; ++q) {\n            cld_test(n, q);\n  \
    \          fld_test(n, q);\n        }\n    }\n\n    std::cout << \"Hello World\"\
    \ << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/number/find_denominators.hpp
  isVerificationFile: true
  path: test/src/number/find_denominators/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-10-20 19:29:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/find_denominators/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/find_denominators/dummy.test.cpp
- /verify/test/src/number/find_denominators/dummy.test.cpp.html
title: test/src/number/find_denominators/dummy.test.cpp
---
