---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/sequence/powers.hpp
    title: Powers
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2_small_prime_mod.hpp
    title: Stirling Number2 Small Prime Mod
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"library/sequence/stirling_number2.hpp\"\n\n\n\n#line 1 \"\
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
    } // namespace suisen\n\n\n#line 6 \"library/sequence/stirling_number2.hpp\"\n\
    \nnamespace suisen {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i]\
    \ = S2[n,i] for i=0,...,k\n     * constraints:\n     *   0 <= n <= 10^6\n    \
    \ */\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ stirling_number2(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        std::vector<mint> pows = powers<mint>(n, n);\n        factorial<mint>\
    \ fac(n);\n        FPSType a(n + 1), b(n + 1);\n        for (int i = 0; i <= n;\
    \ ++i) {\n            a[i] = pows[i] * fac.fac_inv(i);\n            b[i] = i &\
    \ 1 ? -fac.fac_inv(i) : fac.fac_inv(i);\n        }\n        a *= b, a.cut(n +\
    \ 1);\n        return a;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ stirling_number2_table(int n) {\n        std::vector dp(n + 1, std::vector<mint>{});\n\
    \        for (int i = 0; i <= n; ++i) {\n            dp[i].resize(i + 1);\n  \
    \          dp[i][0] = 0, dp[i][i] = 1;\n            for (int j = 1; j < i; ++j)\
    \ dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];\n        }\n        return dp;\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_STIRLING_NUMBER_2\n#define SUISEN_STIRLING_NUMBER_2\n\n#include\
    \ \"library/math/factorial.hpp\"\n#include \"library/sequence/powers.hpp\"\n\n\
    namespace suisen {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i]\
    \ = S2[n,i] for i=0,...,k\n     * constraints:\n     *   0 <= n <= 10^6\n    \
    \ */\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ stirling_number2(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        std::vector<mint> pows = powers<mint>(n, n);\n        factorial<mint>\
    \ fac(n);\n        FPSType a(n + 1), b(n + 1);\n        for (int i = 0; i <= n;\
    \ ++i) {\n            a[i] = pows[i] * fac.fac_inv(i);\n            b[i] = i &\
    \ 1 ? -fac.fac_inv(i) : fac.fac_inv(i);\n        }\n        a *= b, a.cut(n +\
    \ 1);\n        return a;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ stirling_number2_table(int n) {\n        std::vector dp(n + 1, std::vector<mint>{});\n\
    \        for (int i = 0; i <= n; ++i) {\n            dp[i].resize(i + 1);\n  \
    \          dp[i][0] = 0, dp[i][i] = 1;\n            for (int j = 1; j < i; ++j)\
    \ dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];\n        }\n        return dp;\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_STIRLING_NUMBER_2\n"
  dependsOn:
  - library/math/factorial.hpp
  - library/sequence/powers.hpp
  - library/number/linear_sieve.hpp
  isVerificationFile: false
  path: library/sequence/stirling_number2.hpp
  requiredBy:
  - library/sequence/stirling_number2_small_prime_mod.hpp
  timestamp: '2022-10-13 23:32:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/stirling_number2/stirling_number2_2.test.cpp
  - test/src/sequence/stirling_number2/stirling_number2.test.cpp
  - test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
documentation_of: library/sequence/stirling_number2.hpp
layout: document
title: Stirling Number2
---
## Stirling Number2

### stirling_number2

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number2(int n)
  ```

- 概要

  第二種スターリング数 $\\\{\mathrm{S2}(n,i)\\\} _ {i=0} ^ n$ を計算します．$\mathrm{S2}(n,i)$ は，ラベル付けされた $n$ 個の玉を $i$ 個のグループに分割する方法の数と一致します．ここで，$\\\{\\\{1,2\\\},\\\{3,4\\\}\\\}$ と $\\\{\\\{3,4\\\},\\\{1,2\\\}\\\}$ のような分け方は区別しません．

- テンプレート引数
  
  - `mint`: modint 型を想定

- 返り値

  第二種スターリング数 $\\\{\mathrm{S2}(n,i)\\\} _ {i=0} ^ n$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$

- 参考
  
  - [スターリング数 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%AA%E3%83%B3%E3%82%B0%E6%95%B0)
  - [FFT (NTT) 関連](https://min-25.hatenablog.com/entry/2015/04/07/160154)