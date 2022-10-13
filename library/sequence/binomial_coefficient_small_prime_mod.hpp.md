---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient.hpp
    title: Binomial Coefficient
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number1_small_prime_mod.hpp
    title: Stirling Number of the First Kind (Small Prime Mod)
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2_small_prime_mod.hpp
    title: Stirling Number2 Small Prime Mod
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\n\n\n#line 1 \"library/sequence/binomial_coefficient.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T>\n    std::vector<std::vector<T>>\
    \ binom_table(int n) {\n        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n\
    \ + 1));\n        for (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i]\
    \ = 1;\n            for (int j = 1; j < i; ++j) {\n                binom[i][j]\
    \ = binom[i - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n       \
    \ return binom;\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    struct BinomialCoefficientSmallPrimeMod\
    \ {\n        mint operator()(long long n, long long r) const {\n            return\
    \ binom(n, r);\n        }\n        static mint binom(long long n, long long r)\
    \ {\n            static const std::vector<std::vector<mint>> table = binom_table<mint>(mint::mod()\
    \ - 1);\n            if (r < 0 or n < r) return 0;\n            r = std::min(r,\
    \ n - r);\n            // Lucas's theorem\n            mint res = 1;\n       \
    \     while (r) {\n                int ni = n % mint::mod(), ri = r % mint::mod();\n\
    \                if (ni < ri) return 0;\n                res *= table[ni][ri];\n\
    \                n = n / mint::mod(), r = r / mint::mod();\n            }\n  \
    \          return res;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BINOMIAL_COEFFICIENT_SMALL_P\n#define SUISEN_BINOMIAL_COEFFICIENT_SMALL_P\n\
    \n#include \"library/sequence/binomial_coefficient.hpp\"\n\nnamespace suisen {\n\
    \    template <typename mint>\n    struct BinomialCoefficientSmallPrimeMod {\n\
    \        mint operator()(long long n, long long r) const {\n            return\
    \ binom(n, r);\n        }\n        static mint binom(long long n, long long r)\
    \ {\n            static const std::vector<std::vector<mint>> table = binom_table<mint>(mint::mod()\
    \ - 1);\n            if (r < 0 or n < r) return 0;\n            r = std::min(r,\
    \ n - r);\n            // Lucas's theorem\n            mint res = 1;\n       \
    \     while (r) {\n                int ni = n % mint::mod(), ri = r % mint::mod();\n\
    \                if (ni < ri) return 0;\n                res *= table[ni][ri];\n\
    \                n = n / mint::mod(), r = r / mint::mod();\n            }\n  \
    \          return res;\n        }\n    };\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_BINOMIAL_COEFFICIENT_SMALL_P\n"
  dependsOn:
  - library/sequence/binomial_coefficient.hpp
  isVerificationFile: false
  path: library/sequence/binomial_coefficient_small_prime_mod.hpp
  requiredBy:
  - library/sequence/stirling_number2_small_prime_mod.hpp
  - library/sequence/stirling_number1_small_prime_mod.hpp
  timestamp: '2022-10-13 23:32:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  - test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
documentation_of: library/sequence/binomial_coefficient_small_prime_mod.hpp
layout: document
title: Binomial Coefficient Small Prime Mod
---
## Binomial Coefficient Small Prime Mod

以下に示す Lucas の定理を用いる。

> $p$ が素数のとき、非負整数 $n, r$ に対して次が成り立つ:
> $$\binom{n}{r} \equiv \prod_{i=0}^{k-1}\binom{n _ i}{r _ i} \pmod{p}.$$
> ここで、$n$ を $p$ 進表記したときの $i$ 桁目を $n_i$ とした ($r$ についても同様)。

全ての $0\leq n\lt p,0\leq r\lt p$ に対する $\displaystyle \binom{n}{r} \bmod p$ を $O(p ^ 2)$ 時間だけ掛けて前計算しておくことで、クエリあたり $O(\log _ p n)$ で計算できる。
