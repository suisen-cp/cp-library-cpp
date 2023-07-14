---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/mod_sqrt/dummy.test.cpp
    title: test/src/number/mod_sqrt/dummy.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/dummy.test.cpp
    title: test/src/number/primitive_root/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/util/abc222_g.test.cpp
    title: test/src/number/util/abc222_g.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Utilities
    links: []
  bundledCode: "#line 1 \"library/number/util.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cmath>\n#include <numeric>\n#include <tuple>\n#include\
    \ <vector>\n\n/**\n * @brief Utilities\n*/\n\nnamespace suisen {\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    T powi(T a, int b) {\n        T res = 1, pow_a = a;\n        for (; b; b\
    \ >>= 1) {\n            if (b & 1) res *= pow_a;\n            pow_a *= pow_a;\n\
    \        }\n        return res;\n    }\n\n    /**\n     * @brief Calculates the\
    \ prime factorization of n in O(\u221An).\n     * @tparam T integer type\n   \
    \  * @param n integer to factorize\n     * @return vector of { prime, exponent\
    \ }. It is guaranteed that prime is ascending.\n     */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::pair<T,\
    \ int>> factorize(T n) {\n        static constexpr std::array primes{ 2, 3, 5,\
    \ 7, 11, 13 };\n        static constexpr int next_prime = 17;\n        static\
    \ constexpr int siz = std::array{ 1, 2, 8, 48, 480, 5760, 92160 } [primes.size()\
    \ - 1] ;\n        static constexpr int period = [] {\n            int res = 1;\n\
    \            for (auto e : primes) res *= e;\n            return res;\n      \
    \  }();\n        static constexpr struct S : public std::array<int, siz> {\n \
    \           constexpr S() {\n                for (int i = next_prime, j = 0; i\
    \ < period + next_prime; i += 2) {\n                    bool ok = true;\n    \
    \                for (int p : primes) ok &= i % p > 0;\n                    if\
    \ (ok) (*this)[j++] = i - next_prime;\n                }\n            }\n    \
    \    } s{};\n\n        assert(n > 0);\n        std::vector<std::pair<T, int>>\
    \ res;\n        auto f = [&res, &n](int p) {\n            if (n % p) return;\n\
    \            int cnt = 0;\n            do n /= p, ++cnt; while (n % p == 0);\n\
    \            res.emplace_back(p, cnt);\n        };\n        for (int p : primes)\
    \ f(p);\n        for (T b = next_prime; b * b <= n; b += period) {\n         \
    \   for (int offset : s) f(b + offset);\n        }\n        if (n != 1) res.emplace_back(n,\
    \ 1);\n        return res;\n    }\n\n    /**\n     * @brief Enumerates divisors\
    \ of n from its prime-factorized form in O(# of divisors of n) time.\n     * @tparam\
    \ T integer type\n     * @param factorized a prime-factorized form of n (a vector\
    \ of { prime, exponent })\n     * @return vector of divisors (NOT sorted)\n  \
    \   */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<T> divisors(const std::vector<std::pair<T, int>>&\
    \ factorized) {\n        std::vector<T> res{ 1 };\n        for (auto [p, c] :\
    \ factorized) {\n            for (int i = 0, sz = res.size(); i < sz; ++i) {\n\
    \                T d = res[i];\n                for (int j = 0; j < c; ++j) res.push_back(d\
    \ *= p);\n            }\n        }\n        return res;\n    }\n    /**\n    \
    \ * @brief Enumerates divisors of n in O(\u221An) time.\n     * @tparam T integer\
    \ type\n     * @param n\n     * @return vector of divisors (NOT sorted)\n    \
    \ */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<T> divisors(T n) {\n        return divisors(factorize(n));\n\
    \    }\n    /**\n     * @brief Calculates the divisors for i=1,...,n in O(n log\
    \ n) time.\n     * @param n upper bound (closed)\n     * @return 2-dim vector\
    \ a of length n+1, where a[i] is the vector of divisors of i.\n     */\n    std::vector<std::vector<int>>\
    \ divisors_table(int n) {\n        std::vector<std::vector<int>> divs(n + 1);\n\
    \        for (int i = 1; i <= n; ++i) {\n            for (int j = i; j <= n; ++j)\
    \ divs[j].push_back(i);\n        }\n        return divs;\n    }\n\n    /**\n \
    \    * @brief Calculates \u03C6(n) from its prime-factorized form in O(log n).\n\
    \     * @tparam T integer type\n     * @param factorized a prime-factorized form\
    \ of n (a vector of { prime, exponent })\n     * @return \u03C6(n)\n     */\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T totient(const std::vector<std::pair<T, int>>& factorized)\
    \ {\n        T res = 1;\n        for (const auto& [p, c] : factorized) res *=\
    \ (p - 1) * powi(p, c - 1);\n        return res;\n    }\n    /**\n     * @brief\
    \ Calculates \u03C6(n) in O(\u221An).\n     * @tparam T integer type\n     * @param\
    \ n\n     * @return \u03C6(n)\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T totient(T n) {\n        return totient(factorize(n));\n\
    \    }\n    /**\n     * @brief Calculates \u03C6(i) for i=1,...,n.\n     * @param\
    \ n upper bound (closed)\n     * @return vector a of length n+1, where a[i]=\u03C6\
    (i) for i=1,...,n\n     */\n    std::vector<int> totient_table(int n) {\n    \
    \    std::vector<int> res(n + 1);\n        for (int i = 0; i <= n; ++i) res[i]\
    \ = (i & 1) == 0 ? i >> 1 : i;\n        for (int p = 3; p * p <= n; p += 2) {\n\
    \            if (res[p] != p) continue;\n            for (int q = p; q <= n; q\
    \ += p) res[q] /= p, res[q] *= p - 1;\n        }\n        return res;\n    }\n\
    \n    /**\n     * @brief Calculates \u03BB(n) from its prime-factorized form in\
    \ O(log n).\n     * @tparam T integer type\n     * @param factorized a prime-factorized\
    \ form of n (a vector of { prime, exponent })\n     * @return \u03BB(n)\n    \
    \ */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T carmichael(const std::vector<std::pair<T, int>>& factorized)\
    \ {\n        T res = 1;\n        for (const auto &[p, c] : factorized) {\n   \
    \         res = std::lcm(res, ((p - 1) * powi(p, c - 1)) >> (p == 2 and c >= 3));\n\
    \        }\n        return res;\n    }\n    /**\n     * @brief Calculates \u03BB\
    (n) in O(\u221An).\n     * @tparam T integer type\n     * @param n\n     * @return\
    \ \u03BB(n)\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T carmichael(T n) {\n        return carmichael(factorize(n));\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_NUMBER_UTIL\n#define SUISEN_NUMBER_UTIL\n\n#include <array>\n\
    #include <cassert>\n#include <cmath>\n#include <numeric>\n#include <tuple>\n#include\
    \ <vector>\n\n/**\n * @brief Utilities\n*/\n\nnamespace suisen {\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    T powi(T a, int b) {\n        T res = 1, pow_a = a;\n        for (; b; b\
    \ >>= 1) {\n            if (b & 1) res *= pow_a;\n            pow_a *= pow_a;\n\
    \        }\n        return res;\n    }\n\n    /**\n     * @brief Calculates the\
    \ prime factorization of n in O(\u221An).\n     * @tparam T integer type\n   \
    \  * @param n integer to factorize\n     * @return vector of { prime, exponent\
    \ }. It is guaranteed that prime is ascending.\n     */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::pair<T,\
    \ int>> factorize(T n) {\n        static constexpr std::array primes{ 2, 3, 5,\
    \ 7, 11, 13 };\n        static constexpr int next_prime = 17;\n        static\
    \ constexpr int siz = std::array{ 1, 2, 8, 48, 480, 5760, 92160 } [primes.size()\
    \ - 1] ;\n        static constexpr int period = [] {\n            int res = 1;\n\
    \            for (auto e : primes) res *= e;\n            return res;\n      \
    \  }();\n        static constexpr struct S : public std::array<int, siz> {\n \
    \           constexpr S() {\n                for (int i = next_prime, j = 0; i\
    \ < period + next_prime; i += 2) {\n                    bool ok = true;\n    \
    \                for (int p : primes) ok &= i % p > 0;\n                    if\
    \ (ok) (*this)[j++] = i - next_prime;\n                }\n            }\n    \
    \    } s{};\n\n        assert(n > 0);\n        std::vector<std::pair<T, int>>\
    \ res;\n        auto f = [&res, &n](int p) {\n            if (n % p) return;\n\
    \            int cnt = 0;\n            do n /= p, ++cnt; while (n % p == 0);\n\
    \            res.emplace_back(p, cnt);\n        };\n        for (int p : primes)\
    \ f(p);\n        for (T b = next_prime; b * b <= n; b += period) {\n         \
    \   for (int offset : s) f(b + offset);\n        }\n        if (n != 1) res.emplace_back(n,\
    \ 1);\n        return res;\n    }\n\n    /**\n     * @brief Enumerates divisors\
    \ of n from its prime-factorized form in O(# of divisors of n) time.\n     * @tparam\
    \ T integer type\n     * @param factorized a prime-factorized form of n (a vector\
    \ of { prime, exponent })\n     * @return vector of divisors (NOT sorted)\n  \
    \   */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<T> divisors(const std::vector<std::pair<T, int>>&\
    \ factorized) {\n        std::vector<T> res{ 1 };\n        for (auto [p, c] :\
    \ factorized) {\n            for (int i = 0, sz = res.size(); i < sz; ++i) {\n\
    \                T d = res[i];\n                for (int j = 0; j < c; ++j) res.push_back(d\
    \ *= p);\n            }\n        }\n        return res;\n    }\n    /**\n    \
    \ * @brief Enumerates divisors of n in O(\u221An) time.\n     * @tparam T integer\
    \ type\n     * @param n\n     * @return vector of divisors (NOT sorted)\n    \
    \ */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<T> divisors(T n) {\n        return divisors(factorize(n));\n\
    \    }\n    /**\n     * @brief Calculates the divisors for i=1,...,n in O(n log\
    \ n) time.\n     * @param n upper bound (closed)\n     * @return 2-dim vector\
    \ a of length n+1, where a[i] is the vector of divisors of i.\n     */\n    std::vector<std::vector<int>>\
    \ divisors_table(int n) {\n        std::vector<std::vector<int>> divs(n + 1);\n\
    \        for (int i = 1; i <= n; ++i) {\n            for (int j = i; j <= n; ++j)\
    \ divs[j].push_back(i);\n        }\n        return divs;\n    }\n\n    /**\n \
    \    * @brief Calculates \u03C6(n) from its prime-factorized form in O(log n).\n\
    \     * @tparam T integer type\n     * @param factorized a prime-factorized form\
    \ of n (a vector of { prime, exponent })\n     * @return \u03C6(n)\n     */\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T totient(const std::vector<std::pair<T, int>>& factorized)\
    \ {\n        T res = 1;\n        for (const auto& [p, c] : factorized) res *=\
    \ (p - 1) * powi(p, c - 1);\n        return res;\n    }\n    /**\n     * @brief\
    \ Calculates \u03C6(n) in O(\u221An).\n     * @tparam T integer type\n     * @param\
    \ n\n     * @return \u03C6(n)\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T totient(T n) {\n        return totient(factorize(n));\n\
    \    }\n    /**\n     * @brief Calculates \u03C6(i) for i=1,...,n.\n     * @param\
    \ n upper bound (closed)\n     * @return vector a of length n+1, where a[i]=\u03C6\
    (i) for i=1,...,n\n     */\n    std::vector<int> totient_table(int n) {\n    \
    \    std::vector<int> res(n + 1);\n        for (int i = 0; i <= n; ++i) res[i]\
    \ = (i & 1) == 0 ? i >> 1 : i;\n        for (int p = 3; p * p <= n; p += 2) {\n\
    \            if (res[p] != p) continue;\n            for (int q = p; q <= n; q\
    \ += p) res[q] /= p, res[q] *= p - 1;\n        }\n        return res;\n    }\n\
    \n    /**\n     * @brief Calculates \u03BB(n) from its prime-factorized form in\
    \ O(log n).\n     * @tparam T integer type\n     * @param factorized a prime-factorized\
    \ form of n (a vector of { prime, exponent })\n     * @return \u03BB(n)\n    \
    \ */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T carmichael(const std::vector<std::pair<T, int>>& factorized)\
    \ {\n        T res = 1;\n        for (const auto &[p, c] : factorized) {\n   \
    \         res = std::lcm(res, ((p - 1) * powi(p, c - 1)) >> (p == 2 and c >= 3));\n\
    \        }\n        return res;\n    }\n    /**\n     * @brief Calculates \u03BB\
    (n) in O(\u221An).\n     * @tparam T integer type\n     * @param n\n     * @return\
    \ \u03BB(n)\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T carmichael(T n) {\n        return carmichael(factorize(n));\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_NUMBER_UTIL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/util.hpp
  requiredBy: []
  timestamp: '2022-10-20 19:29:51+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/number/mod_sqrt/dummy.test.cpp
  - test/src/number/util/abc222_g.test.cpp
  - test/src/number/primitive_root/dummy.test.cpp
documentation_of: library/number/util.hpp
layout: document
title: Util
---
## Util