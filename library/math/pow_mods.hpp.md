---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/binomial_coefficient_sum.hpp
    title: Binomial Coefficient Sum
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  - icon: ':heavy_check_mark:'
    path: library/polynomial/prod_f(r^k_x).hpp
    title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
  - icon: ':warning:'
    path: library/sequence/sum_of_powers.hpp
    title: library/sequence/sum_of_powers.hpp
  - icon: ':heavy_check_mark:'
    path: library/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/binomial_coefficient_sum/yuki2512.test.cpp
    title: test/src/math/binomial_coefficient_sum/yuki2512.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/compose_exp/arc154_f.test.cpp
    title: test/src/polynomial/compose_exp/arc154_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
    title: test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/rolling_hash/abc141_e.test.cpp
    title: test/src/string/rolling_hash/abc141_e.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/pow_mods.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    template <int base_as_int, typename mint>\n    struct\
    \ static_pow_mods {\n        static_pow_mods() = default;\n        static_pow_mods(int\
    \ n) { ensure(n); }\n        const mint& operator[](int i) const {\n         \
    \   ensure(i);\n            return pows[i];\n        }\n        static void ensure(int\
    \ n) {\n            int sz = pows.size();\n            if (sz > n) return;\n \
    \           pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i]\
    \ = base * pows[i - 1];\n        }\n    private:\n        static inline std::vector<mint>\
    \ pows { 1 };\n        static inline mint base = base_as_int;\n        static\
    \ constexpr int mod = mint::mod();\n    };\n\n    template <typename mint>\n \
    \   struct pow_mods {\n        pow_mods() = default;\n        pow_mods(mint base,\
    \ int n) : base(base) { ensure(n); }\n        const mint& operator[](int i) const\
    \ {\n            ensure(i);\n            return pows[i];\n        }\n        void\
    \ ensure(int n) const {\n            int sz = pows.size();\n            if (sz\
    \ > n) return;\n            pows.resize(n + 1);\n            for (int i = sz;\
    \ i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n      \
    \  mutable std::vector<mint> pows { 1 };\n        mint base;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_POW_MOD\n#define SUISEN_POW_MOD\n\n#include <vector>\n\nnamespace\
    \ suisen {\n    template <int base_as_int, typename mint>\n    struct static_pow_mods\
    \ {\n        static_pow_mods() = default;\n        static_pow_mods(int n) { ensure(n);\
    \ }\n        const mint& operator[](int i) const {\n            ensure(i);\n \
    \           return pows[i];\n        }\n        static void ensure(int n) {\n\
    \            int sz = pows.size();\n            if (sz > n) return;\n        \
    \    pows.resize(n + 1);\n            for (int i = sz; i <= n; ++i) pows[i] =\
    \ base * pows[i - 1];\n        }\n    private:\n        static inline std::vector<mint>\
    \ pows { 1 };\n        static inline mint base = base_as_int;\n        static\
    \ constexpr int mod = mint::mod();\n    };\n\n    template <typename mint>\n \
    \   struct pow_mods {\n        pow_mods() = default;\n        pow_mods(mint base,\
    \ int n) : base(base) { ensure(n); }\n        const mint& operator[](int i) const\
    \ {\n            ensure(i);\n            return pows[i];\n        }\n        void\
    \ ensure(int n) const {\n            int sz = pows.size();\n            if (sz\
    \ > n) return;\n            pows.resize(n + 1);\n            for (int i = sz;\
    \ i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n      \
    \  mutable std::vector<mint> pows { 1 };\n        mint base;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n}\n\n#endif // SUISEN_POW_MOD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/pow_mods.hpp
  requiredBy:
  - library/math/binomial_coefficient_sum.hpp
  - library/math/sum_i^d_r^i.hpp
  - library/sequence/sum_of_powers.hpp
  - library/polynomial/prod_f(r^k_x).hpp
  - library/string/rolling_hash.hpp
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - test/src/math/binomial_coefficient_sum/yuki2512.test.cpp
  - test/src/polynomial/prod_f(r^k_x)/yuki2097.test.cpp
  - test/src/polynomial/compose_exp/arc154_f.test.cpp
  - test/src/string/rolling_hash/abc141_e.test.cpp
documentation_of: library/math/pow_mods.hpp
layout: document
title: "\u51AA\u4E57\u30C6\u30FC\u30D6\u30EB"
---
## 冪乗テーブル