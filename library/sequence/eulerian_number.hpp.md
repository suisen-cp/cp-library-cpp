---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  - icon: ':question:'
    path: library/sequence/powers.hpp
    title: Powers
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
  - icon: ':x:'
    path: test/src/sequence/eulerian_number/yuki2005-2.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/eulerian_number/yuki2005.test.cpp
    title: test/src/sequence/eulerian_number/yuki2005.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Eulerian_number
  bundledCode: "#line 1 \"library/sequence/eulerian_number.hpp\"\n\n\n\n#line 1 \"\
    library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T, typename U = T>\n    struct factorial\
    \ {\n        factorial() {}\n        factorial(int n) { ensure(n); }\n\n     \
    \   static void ensure(const int n) {\n            int sz = _fac.size();\n   \
    \         if (n + 1 <= sz) return;\n            int new_size = std::max(n + 1,\
    \ sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n  \
    \          for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n  \
    \          _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n            for\
    \ (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n   \
    \     }\n\n        T fac(const int i) {\n            ensure(i);\n            return\
    \ _fac[i];\n        }\n        T operator()(int i) {\n            return fac(i);\n\
    \        }\n        U fac_inv(const int i) {\n            ensure(i);\n       \
    \     return _fac_inv[i];\n        }\n        U binom(const int n, const int r)\
    \ {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 1 \"library/sequence/powers.hpp\"\n\n\n\n#include <cstdint>\n\
    #line 1 \"library/number/linear_sieve.hpp\"\n\n\n\n#line 5 \"library/number/linear_sieve.hpp\"\
    \n#include <numeric>\n#line 7 \"library/number/linear_sieve.hpp\"\n\nnamespace\
    \ suisen {\n// referece: https://37zigen.com/linear-sieve/\nclass LinearSieve\
    \ {\n    public:\n        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n\
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
    } // namespace suisen\n\n\n#line 6 \"library/sequence/eulerian_number.hpp\"\n\n\
    // reference: https://en.wikipedia.org/wiki/Eulerian_number\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ eulerian_number(uint32_t n) {\n        using mint = typename FPSType::value_type;\n\
    \        if (n == 0) return {};\n        factorial<mint> fac(n + 1);\n       \
    \ const uint32_t h = (n + 1) >> 1;\n        FPSType f = powers<mint>(h, n);\n\
    \        f.erase(f.begin());\n        FPSType g(h);\n        for (uint32_t i =\
    \ 0; i < h; ++i) {\n            mint v = fac.binom(n + 1, i);\n            g[i]\
    \ = i & 1 ? -v : v;\n        }\n        FPSType res = f * g;\n        res.resize(n);\n\
    \        for (uint32_t i = h; i < n; ++i) res[i] = res[n - 1 - i];\n        return\
    \ res;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ eulerian_number_table(uint32_t n) {\n        if (n == 0) return {};\n      \
    \  std::vector dp(n + 1, std::vector<mint>{});\n        for (uint32_t i = 1; i\
    \ <= n; ++i) {\n            dp[i].resize(i);\n            dp[i][0] = dp[i][i -\
    \ 1] = 1;\n            for (uint32_t j = 1; j < i - 1; ++j) dp[i][j] = (i - j)\
    \ * dp[i - 1][j - 1] + (j + 1) * dp[i - 1][j];\n        }\n        return dp;\n\
    \    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_EULERIAN_NUMBER\n#define SUISEN_EULERIAN_NUMBER\n\n#include\
    \ \"library/math/factorial.hpp\"\n#include \"library/sequence/powers.hpp\"\n\n\
    // reference: https://en.wikipedia.org/wiki/Eulerian_number\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ eulerian_number(uint32_t n) {\n        using mint = typename FPSType::value_type;\n\
    \        if (n == 0) return {};\n        factorial<mint> fac(n + 1);\n       \
    \ const uint32_t h = (n + 1) >> 1;\n        FPSType f = powers<mint>(h, n);\n\
    \        f.erase(f.begin());\n        FPSType g(h);\n        for (uint32_t i =\
    \ 0; i < h; ++i) {\n            mint v = fac.binom(n + 1, i);\n            g[i]\
    \ = i & 1 ? -v : v;\n        }\n        FPSType res = f * g;\n        res.resize(n);\n\
    \        for (uint32_t i = h; i < n; ++i) res[i] = res[n - 1 - i];\n        return\
    \ res;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ eulerian_number_table(uint32_t n) {\n        if (n == 0) return {};\n      \
    \  std::vector dp(n + 1, std::vector<mint>{});\n        for (uint32_t i = 1; i\
    \ <= n; ++i) {\n            dp[i].resize(i);\n            dp[i][0] = dp[i][i -\
    \ 1] = 1;\n            for (uint32_t j = 1; j < i - 1; ++j) dp[i][j] = (i - j)\
    \ * dp[i - 1][j - 1] + (j + 1) * dp[i - 1][j];\n        }\n        return dp;\n\
    \    }\n} // namespace suisen\n\n\n#endif // SUISEN_EULERIAN_NUMBER\n"
  dependsOn:
  - library/math/factorial.hpp
  - library/sequence/powers.hpp
  - library/number/linear_sieve.hpp
  isVerificationFile: false
  path: library/sequence/eulerian_number.hpp
  requiredBy: []
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/sequence/eulerian_number/yuki2005.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2-2.test.cpp
  - test/src/sequence/eulerian_number/yuki2005-2.test.cpp
documentation_of: library/sequence/eulerian_number.hpp
layout: document
title: Eulerian Number
---
## Eulerian Number