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
    path: library/sequence/binomial_coefficient_small_prime_mod.hpp
    title: Binomial Coefficient Small Prime Mod
  - icon: ':heavy_check_mark:'
    path: library/sequence/powers.hpp
    title: Powers
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2.hpp
    title: Stirling Number2
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2_small_prime_mod.hpp
    title: Stirling Number2 Small Prime Mod
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n
    links:
    - https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n
  bundledCode: "#line 1 \"test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \n#line 1 \"library/sequence/stirling_number2_small_prime_mod.hpp\"\n\n\n\n#line\
    \ 1 \"library/sequence/stirling_number2.hpp\"\n\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, typename U = T>\n    struct factorial {\n        factorial() {}\n\
    \        factorial(int n) { ensure(n); }\n\n        static void ensure(const int\
    \ n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        U perm(const int n, const int r) {\n            if\
    \ (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n            return\
    \ _fac[n] * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T>\
    \ _fac;\n        static std::vector<U> _fac_inv;\n    };\n    template <typename\
    \ T, typename U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template\
    \ <typename T, typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n\
    } // namespace suisen\n\n\n#line 1 \"library/sequence/powers.hpp\"\n\n\n\n#include\
    \ <cstdint>\n#line 1 \"library/number/linear_sieve.hpp\"\n\n\n\n#line 5 \"library/number/linear_sieve.hpp\"\
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
    \    }\n} // namespace suisen\n\n\n#line 1 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\n\n\n#line 5 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\n\
    \nnamespace suisen {\n    template <typename mint>\n    struct BinomialCoefficientSmallPrimeMod\
    \ {\n        mint operator()(long long n, long long r) const {\n            return\
    \ binom(n, r);\n        }\n        static mint binom(long long n, long long r)\
    \ {\n            factorial<mint> fac(mint::mod() - 1);\n\n            if (r <\
    \ 0 or n < r) return 0;\n            r = std::min(r, n - r);\n            // Lucas's\
    \ theorem\n            mint res = 1;\n            while (r) {\n              \
    \  int ni = n % mint::mod(), ri = r % mint::mod();\n                if (ni < ri)\
    \ return 0;\n                res *= fac.binom(ni, ri);\n                n = n\
    \ / mint::mod(), r = r / mint::mod();\n            }\n            return res;\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"library/sequence/stirling_number2_small_prime_mod.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    struct StirlingNumber2SmallPrimeMod\
    \ {\n        mint operator()(long long n, long long k) const {\n            return\
    \ s2(n, k);\n        }\n        static mint s2(long long n, long long k) {\n \
    \           static const std::vector<std::vector<mint>> table = stirling_number2_table<mint>(mint::mod()\
    \ - 1);\n            static const BinomialCoefficientSmallPrimeMod<mint> binom{};\n\
    \            static const int p = mint::mod();\n            if (k < 0 or n < k)\
    \ return 0;\n            if (n == 0) return 1;\n            long long c = k /\
    \ p, d = k % p;\n            long long a = (n - c - 1) / (p - 1), b = (n - c -\
    \ 1) % (p - 1) + 1;\n            if (b != p - 1) return d <= b ? binom(a, c) *\
    \ table[b][d] : 0;\n            else return d ? binom(a, c) * table[p - 1][d]\
    \ : binom(a, c - 1);\n        }\n    };\n} // namespace suisen\n\n\n\n#line 9\
    \ \"test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t, p;\n    std::cin >> t >> p;\n    mint::set_mod(p);\n\n    suisen::StirlingNumber2SmallPrimeMod<mint>\
    \ s2;\n\n    while (t --> 0) {\n        long long n, k;\n        std::cin >> n\
    \ >> k;\n        std::cout << s2(n, k).val() << '\\n';\n    }\n\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \n#include \"library/sequence/stirling_number2_small_prime_mod.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int t, p;\n    std::cin >> t >> p;\n    mint::set_mod(p);\n\n    suisen::StirlingNumber2SmallPrimeMod<mint>\
    \ s2;\n\n    while (t --> 0) {\n        long long n, k;\n        std::cin >> n\
    \ >> k;\n        std::cout << s2(n, k).val() << '\\n';\n    }\n\n    return 0;\n\
    }"
  dependsOn:
  - library/sequence/stirling_number2_small_prime_mod.hpp
  - library/sequence/stirling_number2.hpp
  - library/math/factorial.hpp
  - library/sequence/powers.hpp
  - library/number/linear_sieve.hpp
  - library/sequence/binomial_coefficient_small_prime_mod.hpp
  isVerificationFile: true
  path: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
layout: document
redirect_from:
- /verify/test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
- /verify/test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp.html
title: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
---