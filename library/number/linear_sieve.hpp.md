---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/number/anymod_binom.hpp
    title: "\u4EFB\u610F mod \u3067\u306E\u4E8C\u9805\u4FC2\u6570\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: library/sequence/eulerian_number.hpp
    title: Eulerian Number
  - icon: ':heavy_check_mark:'
    path: library/sequence/powers.hpp
    title: Powers
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2.hpp
    title: Stirling Number2
  _extendedVerifiedWith:
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://37zigen.com/linear-sieve/
  bundledCode: "#line 1 \"library/number/linear_sieve.hpp\"\n\n\n\n#include <cassert>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
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
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_LINEAR_SIEVE\n#define SUISEN_LINEAR_SIEVE\n\n#include <cassert>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
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
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n#endif //\
    \ SUISEN_LINEAR_SIEVE"
  dependsOn: []
  isVerificationFile: false
  path: library/number/linear_sieve.hpp
  requiredBy:
  - library/sequence/eulerian_number.hpp
  - library/sequence/powers.hpp
  - library/sequence/stirling_number2.hpp
  - library/number/anymod_binom.hpp
  timestamp: '2021-08-04 13:32:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/stirling_number2/stirling_number2_2.test.cpp
  - test/src/sequence/stirling_number2/stirling_number2.test.cpp
  - test/src/sequence/eulerian_number/yuki2005.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
documentation_of: library/number/linear_sieve.hpp
layout: document
title: "\u7DDA\u5F62\u7BE9"
---
## 線形篩