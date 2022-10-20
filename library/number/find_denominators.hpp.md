---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/find_denominators/dummy.test.cpp
    title: test/src/number/find_denominators/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Calculates { min S, max S }, where S = { x>0 | floor(n/x)=q }
      in O(1) time.
    links: []
  bundledCode: "#line 1 \"library/number/find_denominators.hpp\"\n\n\n\n#include <limits>\n\
    #include <optional>\n#include <type_traits>\n\nnamespace suisen {\n    /**\n \
    \    * @brief Calculates { min S, max S }, where S = { x>0 | floor(n/x)=q } in\
    \ O(1) time.\n     * @tparam T integer type\n     * @param n numerator\n     *\
    \ @param q quotient (round down)\n     * @param max_val upper bound (closed)\n\
    \     * @return { min S, max S } if S is not empty, otherwise std::nullopt\n \
    \    */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::optional<std::pair<T, T>> fld_denominators_positive(T n,\
    \ T q, T max_val = std::numeric_limits<T>::max()) {\n        T l, r;\n       \
    \ if (q >= 0) {\n            if (n < 0) return std::nullopt;\n            // cld(n\
    \ + 1, q + 1) <= x <= fld(n, q)\n            l = (n + 1 + q) / (q + 1), r = q\
    \ == 0 ? max_val : std::min(max_val, n / q);\n        } else {\n            if\
    \ (n >= 0) return std::nullopt;\n            // cld(n, q) <= x <= fld(n + 1, q\
    \ + 1)\n            l = (n + q + 1) / q, r = q == -1 ? max_val : std::min(max_val,\
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
    \     return std::nullopt;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_FIND_DENOMINATORS\n#define SUISEN_FIND_DENOMINATORS\n\n#include\
    \ <limits>\n#include <optional>\n#include <type_traits>\n\nnamespace suisen {\n\
    \    /**\n     * @brief Calculates { min S, max S }, where S = { x>0 | floor(n/x)=q\
    \ } in O(1) time.\n     * @tparam T integer type\n     * @param n numerator\n\
    \     * @param q quotient (round down)\n     * @param max_val upper bound (closed)\n\
    \     * @return { min S, max S } if S is not empty, otherwise std::nullopt\n \
    \    */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::optional<std::pair<T, T>> fld_denominators_positive(T n,\
    \ T q, T max_val = std::numeric_limits<T>::max()) {\n        T l, r;\n       \
    \ if (q >= 0) {\n            if (n < 0) return std::nullopt;\n            // cld(n\
    \ + 1, q + 1) <= x <= fld(n, q)\n            l = (n + 1 + q) / (q + 1), r = q\
    \ == 0 ? max_val : std::min(max_val, n / q);\n        } else {\n            if\
    \ (n >= 0) return std::nullopt;\n            // cld(n, q) <= x <= fld(n + 1, q\
    \ + 1)\n            l = (n + q + 1) / q, r = q == -1 ? max_val : std::min(max_val,\
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
    \     return std::nullopt;\n    }\n} // namespace suisen\n\n#endif // SUISEN_FIND_DENOMINATORS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/find_denominators.hpp
  requiredBy: []
  timestamp: '2022-10-20 19:29:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/find_denominators/dummy.test.cpp
documentation_of: library/number/find_denominators.hpp
layout: document
title: "\u5206\u5B50\u3068\u5546\u304B\u3089\u5206\u6BCD\u3068\u3057\u3066\u3042\u308A\
  \u3046\u308B\u7BC4\u56F2\u3092\u8A08\u7B97"
---
## 分子と商から分母としてありうる範囲を計算
