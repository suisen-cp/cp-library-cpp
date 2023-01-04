---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  - icon: ':heavy_check_mark:'
    path: library/sequence/eulerian_number.hpp
    title: Eulerian Number
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2.hpp
    title: Stirling Number2
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2_small_prime_mod.hpp
    title: Stirling Number2 Small Prime Mod
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/eulerian_number/yuki2005-2.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/eulerian_number/yuki2005.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number2/stirling_number2.test.cpp
    title: test/src/sequence/stirling_number2/stirling_number2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number2/stirling_number2_2.test.cpp
    title: test/src/sequence/stirling_number2/stirling_number2_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/powers.hpp\"\n\n\n\n#include <cstdint>\n\
    #line 1 \"library/number/linear_sieve.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <numeric>\n#include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
    class LinearSieve {\n    public:\n        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n\
    \ + 1)) {\n            std::iota(min_prime_factor.begin(), min_prime_factor.end(),\
    \ 0);\n            prime_list.reserve(_n / 20);\n            for (int d = 2; d\
    \ <= _n; ++d) {\n                if (min_prime_factor[d] == d) prime_list.push_back(d);\n\
    \                const int prime_max = std::min(min_prime_factor[d], _n / d);\n\
    \                for (int prime : prime_list) {\n                    if (prime\
    \ > prime_max) break;\n                    min_prime_factor[prime * d] = prime;\n\
    \                }\n            }\n        }\n        int prime_num() const noexcept\
    \ { return prime_list.size(); }\n        /**\n         * Returns a vector of primes\
    \ in [0, n].\n         * It is guaranteed that the returned vector is sorted in\
    \ ascending order.\n         */\n        const std::vector<int>& get_prime_list()\
    \ const noexcept  {\n            return prime_list;\n        }\n        const\
    \ std::vector<int>& get_min_prime_factor() const noexcept { return min_prime_factor;\
    \ }\n        /**\n         * Returns a vector of `{ prime, index }`.\n       \
    \  * It is guaranteed that the returned vector is sorted in ascending order.\n\
    \         */\n        std::vector<std::pair<int, int>> factorize(int n) const\
    \ noexcept {\n            assert(0 < n and n <= _n);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = min_prime_factor[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n    private:\n        const int _n;\n        std::vector<int> min_prime_factor;\n\
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n\n#line 6\
    \ \"library/sequence/powers.hpp\"\n\nnamespace suisen {\n    // returns { 0^k,\
    \ 1^k, ..., n^k }\n    template <typename mint>\n    std::vector<mint> powers(uint32_t\
    \ n, uint64_t k) {\n        const auto mpf = LinearSieve(n).get_min_prime_factor();\n\
    \        std::vector<mint> res(n + 1);\n        res[0] = k == 0;\n        for\
    \ (uint32_t i = 1; i <= n; ++i) res[i] = i == 1 ? 1 : uint32_t(mpf[i]) == i ?\
    \ mint(i).pow(k) : res[mpf[i]] * res[i / mpf[i]];\n        return res;\n    }\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_POWERS\n#define SUISEN_POWERS\n\n#include <cstdint>\n#include\
    \ \"library/number/linear_sieve.hpp\"\n\nnamespace suisen {\n    // returns {\
    \ 0^k, 1^k, ..., n^k }\n    template <typename mint>\n    std::vector<mint> powers(uint32_t\
    \ n, uint64_t k) {\n        const auto mpf = LinearSieve(n).get_min_prime_factor();\n\
    \        std::vector<mint> res(n + 1);\n        res[0] = k == 0;\n        for\
    \ (uint32_t i = 1; i <= n; ++i) res[i] = i == 1 ? 1 : uint32_t(mpf[i]) == i ?\
    \ mint(i).pow(k) : res[mpf[i]] * res[i / mpf[i]];\n        return res;\n    }\n\
    } // namespace suisen\n\n#endif // SUISEN_POWERS\n"
  dependsOn:
  - library/number/linear_sieve.hpp
  isVerificationFile: false
  path: library/sequence/powers.hpp
  requiredBy:
  - library/math/sum_i^d_r^i.hpp
  - library/sequence/stirling_number2.hpp
  - library/sequence/stirling_number2_small_prime_mod.hpp
  - library/sequence/eulerian_number.hpp
  timestamp: '2022-07-10 22:02:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - test/src/sequence/eulerian_number/yuki2005.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2.test.cpp
  - test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  - test/src/sequence/stirling_number2/stirling_number2.test.cpp
  - test/src/sequence/stirling_number2/stirling_number2_2.test.cpp
documentation_of: library/sequence/powers.hpp
layout: document
title: Powers
---
## Powers