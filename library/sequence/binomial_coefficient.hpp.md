---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/barrett_reduction.hpp
    title: Barrett Reduction
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
    title: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/binomial_coefficient.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n#include <atcoder/math>\n\
    \n#line 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <array>\n#line\
    \ 6 \"library/number/barrett_reduction.hpp\"\n#include <cstdint>\n#include <utility>\n\
    \nnamespace suisen {\n    struct barrett {\n        constexpr barrett() : M(1),\
    \ L(0) {}\n        constexpr explicit barrett(uint32_t M) : M(M), L(uint64_t(-1)\
    \ / M + 1) { assert(M); }\n        constexpr int32_t mod() { return M; }\n   \
    \     constexpr uint32_t umod() const { return M; }\n        // floor(x/M) (correctly\
    \ works for all 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint64_t\
    \ quo(uint64_t x) const { return quorem<care_M1>(x).first; }\n        // x%M (correctly\
    \ works for all 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint32_t\
    \ rem(uint64_t x) const { return quorem<care_M1>(x).second; }\n        // { floor(x/M),\
    \ x%M } (correctly works for all 0<=x<2^64)\n        template <bool care_M1 =\
    \ true> constexpr std::pair<uint64_t, uint32_t> quorem(uint64_t x) const {\n \
    \           if constexpr (care_M1) if (M == 1) return { x, 0 };\n            uint64_t\
    \ q = (__uint128_t(x) * L) >> 64;\n            int32_t r = x - q * M;\n      \
    \      if (r < 0) --q, r += M;\n            return { q, uint32_t(r) };\n     \
    \   }\n        // a*b mod M\n        template <bool care_M1 = true> constexpr\
    \ uint32_t mul(uint32_t a, uint32_t b) const { return rem<care_M1>(uint64_t(a)\
    \ * b); }\n    private:\n        uint32_t M; // mod\n        uint64_t L; // ceil(2^K\
    \ / M), where K = 64 (if M != 1)\n    };\n} // namespace suisen\n\n\n\n#line 10\
    \ \"library/sequence/binomial_coefficient.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T>\n    std::vector<std::vector<T>> binom_table(int n) {\n       \
    \ std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n + 1));\n        for\
    \ (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i] = 1;\n   \
    \         for (int j = 1; j < i; ++j) {\n                binom[i][j] = binom[i\
    \ - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n        return binom;\n\
    \    }\n\n    struct binom_small_mod {\n        struct binom_prime_power_mod {\n\
    \            static constexpr int MAX_MOD = 20000000;\n\n            uint32_t\
    \ p, q, m; // m = p ^ q\n            std::vector<uint32_t> f, inv_f;\n\n     \
    \       barrett br_p, br_m;\n\n            binom_prime_power_mod() = default;\n\
    \            binom_prime_power_mod(uint32_t p, uint32_t q, uint32_t m): p(p),\
    \ q(q), m(m), f(m), br_p(p), br_m(m) {\n                assert(m <= MAX_MOD);\n\
    \                f[0] = 1;\n                for (uint32_t i = 1; i < m; ++i) f[i]\
    \ = br_p.rem<false>(i) ? br_m.mul<false>(f[i - 1], i) : f[i - 1];\n          \
    \      inv_f = invs(f);\n            }\n\n            mutable uint32_t ns[64],\
    \ ks[64], ls[64];\n            int32_t operator()(int64_t n_, int64_t k_) const\
    \ {\n                if (k_ < 0 or k_ > n_) return 0;\n                \n    \
    \            uint64_t n = n_, k = k_;\n\n                uint64_t e1 = 0, eq =\
    \ 0;\n                size_t t = 0;\n                for (bool borrow = false;\
    \ n; ++t) {\n                    std::tie(n, ns[t]) = br_p.quorem<false>(n);\n\
    \                    std::tie(k, ks[t]) = br_p.quorem<false>(k);\n           \
    \         ls[t] = ns[t] - ks[t] - borrow;\n                    if (not (borrow\
    \ = ns[t] < ks[t] + borrow)) continue;\n                    ls[t] += p;\n    \
    \                e1 += 1;\n                    eq += t >= q - 1;\n           \
    \     }\n                if (e1 >= q) return 0;\n\n                uint32_t res\
    \ = 1;\n                while (e1--) res *= p;\n                if ((p != 2 or\
    \ q < 3) and (eq & 1)) res = m - res;\n\n                uint32_t ni = 0, ki =\
    \ 0, li = 0;\n                for (size_t i = t; i--;) {\n                   \
    \ ni = br_m.rem<false>(uint64_t(p) * ni + ns[i]);\n                    ki = br_m.rem<false>(uint64_t(p)\
    \ * ki + ks[i]);\n                    li = br_m.rem<false>(uint64_t(p) * li +\
    \ ls[i]);\n                    res = br_m.mul<false>(br_m.mul<false>(res, f[ni]),\
    \ br_m.mul<false>(inv_f[ki], inv_f[li]));\n                }\n               \
    \ return res;\n            }\n        private:\n            std::vector<uint32_t>\
    \ invs(const std::vector<uint32_t>& vs) const {\n                const uint32_t\
    \ n = vs.size();\n\n                uint32_t prod = 1;\n                for (const\
    \ uint32_t& v : vs) prod = br_m.mul<false>(prod, v);\n                uint32_t\
    \ inv_prod = atcoder::inv_mod(prod, m);\n\n                std::vector<uint32_t>\
    \ suf_prod(n + 1);\n                suf_prod[n] = 1;\n                for (uint32_t\
    \ i = n; i --> 0;) suf_prod[i] = br_m.mul<false>(suf_prod[i + 1], vs[i]);\n  \
    \              \n                std::vector<uint32_t> res(n);\n             \
    \   for (uint32_t i = 0; i < n; ++i) {\n                    res[i] = br_m.mul<false>(inv_prod,\
    \ suf_prod[i + 1]);\n                    inv_prod = br_m.mul<false>(inv_prod,\
    \ vs[i]);\n                }\n                return res;\n            }\n   \
    \     };\n\n        std::vector<binom_prime_power_mod> binoms;\n\n        binom_small_mod()\
    \ : binom_small_mod(1) {}\n        explicit binom_small_mod(int m) {\n       \
    \     for (int p = 2; p <= m; ++p) if (m % p == 0) {\n                int q =\
    \ 0, pq = 1;\n                do m /= p, ++q, pq *= p; while (m % p == 0);\n \
    \               binoms.push_back(binom_prime_power_mod(p, q, pq));\n         \
    \   }\n            // decreasing order of p^q\n            std::sort(binoms.begin(),\
    \ binoms.end(), [](const binom_prime_power_mod& b1, const binom_prime_power_mod\
    \ &b2) { return b1.m > b2.m; });\n            std::vector<int> mods;\n       \
    \     for (const auto &b : binoms) mods.push_back(b.m);\n            crt = crt_(std::move(mods));\n\
    \        }\n\n        int operator()(long long n, long long k) const {\n     \
    \       const int l = binoms.size();\n            std::vector<int> rs(l);\n  \
    \          for (int i = 0; i < l; ++i) rs[i] = binoms[i](n, k);\n            return\
    \ crt(rs);\n        }\n    private:\n        struct crt_ {\n            int n;\n\
    \            std::vector<int> mods, invs;\n            crt_() = default;\n   \
    \         crt_(std::vector<int> &&m) : n(m.size()), mods(std::move(m)), invs(n)\
    \ {\n                if (n) for (int i = 1, mod = mods[0]; i < n; ++i) {\n   \
    \                 assert(mod > mods[i]);\n                    invs[i] = atcoder::inv_mod(mod,\
    \ mods[i]);\n                    mod *= mods[i];\n                }\n        \
    \    }\n            int operator()(const std::vector<int>& r) const {\n      \
    \          if (n == 0) return 0;\n                int rem = r[0];\n          \
    \      for (int i = 1, mod = mods[0]; i < n; ++i) {\n                    rem +=\
    \ (r[i] - rem) * invs[i] % mods[i] * mod;\n                    mod *= mods[i];\n\
    \                    if (rem < 0) rem += mod;\n                }\n           \
    \     return rem;\n            }\n        } crt;\n    };\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_BINOMIAL_COEFFICIENT\n#define SUISEN_BINOMIAL_COEFFICIENT\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n#include <atcoder/math>\n\
    \n#include \"library/number/barrett_reduction.hpp\"\n\nnamespace suisen {\n  \
    \  template <typename T>\n    std::vector<std::vector<T>> binom_table(int n) {\n\
    \        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n + 1));\n  \
    \      for (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i] =\
    \ 1;\n            for (int j = 1; j < i; ++j) {\n                binom[i][j] =\
    \ binom[i - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n        return\
    \ binom;\n    }\n\n    struct binom_small_mod {\n        struct binom_prime_power_mod\
    \ {\n            static constexpr int MAX_MOD = 20000000;\n\n            uint32_t\
    \ p, q, m; // m = p ^ q\n            std::vector<uint32_t> f, inv_f;\n\n     \
    \       barrett br_p, br_m;\n\n            binom_prime_power_mod() = default;\n\
    \            binom_prime_power_mod(uint32_t p, uint32_t q, uint32_t m): p(p),\
    \ q(q), m(m), f(m), br_p(p), br_m(m) {\n                assert(m <= MAX_MOD);\n\
    \                f[0] = 1;\n                for (uint32_t i = 1; i < m; ++i) f[i]\
    \ = br_p.rem<false>(i) ? br_m.mul<false>(f[i - 1], i) : f[i - 1];\n          \
    \      inv_f = invs(f);\n            }\n\n            mutable uint32_t ns[64],\
    \ ks[64], ls[64];\n            int32_t operator()(int64_t n_, int64_t k_) const\
    \ {\n                if (k_ < 0 or k_ > n_) return 0;\n                \n    \
    \            uint64_t n = n_, k = k_;\n\n                uint64_t e1 = 0, eq =\
    \ 0;\n                size_t t = 0;\n                for (bool borrow = false;\
    \ n; ++t) {\n                    std::tie(n, ns[t]) = br_p.quorem<false>(n);\n\
    \                    std::tie(k, ks[t]) = br_p.quorem<false>(k);\n           \
    \         ls[t] = ns[t] - ks[t] - borrow;\n                    if (not (borrow\
    \ = ns[t] < ks[t] + borrow)) continue;\n                    ls[t] += p;\n    \
    \                e1 += 1;\n                    eq += t >= q - 1;\n           \
    \     }\n                if (e1 >= q) return 0;\n\n                uint32_t res\
    \ = 1;\n                while (e1--) res *= p;\n                if ((p != 2 or\
    \ q < 3) and (eq & 1)) res = m - res;\n\n                uint32_t ni = 0, ki =\
    \ 0, li = 0;\n                for (size_t i = t; i--;) {\n                   \
    \ ni = br_m.rem<false>(uint64_t(p) * ni + ns[i]);\n                    ki = br_m.rem<false>(uint64_t(p)\
    \ * ki + ks[i]);\n                    li = br_m.rem<false>(uint64_t(p) * li +\
    \ ls[i]);\n                    res = br_m.mul<false>(br_m.mul<false>(res, f[ni]),\
    \ br_m.mul<false>(inv_f[ki], inv_f[li]));\n                }\n               \
    \ return res;\n            }\n        private:\n            std::vector<uint32_t>\
    \ invs(const std::vector<uint32_t>& vs) const {\n                const uint32_t\
    \ n = vs.size();\n\n                uint32_t prod = 1;\n                for (const\
    \ uint32_t& v : vs) prod = br_m.mul<false>(prod, v);\n                uint32_t\
    \ inv_prod = atcoder::inv_mod(prod, m);\n\n                std::vector<uint32_t>\
    \ suf_prod(n + 1);\n                suf_prod[n] = 1;\n                for (uint32_t\
    \ i = n; i --> 0;) suf_prod[i] = br_m.mul<false>(suf_prod[i + 1], vs[i]);\n  \
    \              \n                std::vector<uint32_t> res(n);\n             \
    \   for (uint32_t i = 0; i < n; ++i) {\n                    res[i] = br_m.mul<false>(inv_prod,\
    \ suf_prod[i + 1]);\n                    inv_prod = br_m.mul<false>(inv_prod,\
    \ vs[i]);\n                }\n                return res;\n            }\n   \
    \     };\n\n        std::vector<binom_prime_power_mod> binoms;\n\n        binom_small_mod()\
    \ : binom_small_mod(1) {}\n        explicit binom_small_mod(int m) {\n       \
    \     for (int p = 2; p <= m; ++p) if (m % p == 0) {\n                int q =\
    \ 0, pq = 1;\n                do m /= p, ++q, pq *= p; while (m % p == 0);\n \
    \               binoms.push_back(binom_prime_power_mod(p, q, pq));\n         \
    \   }\n            // decreasing order of p^q\n            std::sort(binoms.begin(),\
    \ binoms.end(), [](const binom_prime_power_mod& b1, const binom_prime_power_mod\
    \ &b2) { return b1.m > b2.m; });\n            std::vector<int> mods;\n       \
    \     for (const auto &b : binoms) mods.push_back(b.m);\n            crt = crt_(std::move(mods));\n\
    \        }\n\n        int operator()(long long n, long long k) const {\n     \
    \       const int l = binoms.size();\n            std::vector<int> rs(l);\n  \
    \          for (int i = 0; i < l; ++i) rs[i] = binoms[i](n, k);\n            return\
    \ crt(rs);\n        }\n    private:\n        struct crt_ {\n            int n;\n\
    \            std::vector<int> mods, invs;\n            crt_() = default;\n   \
    \         crt_(std::vector<int> &&m) : n(m.size()), mods(std::move(m)), invs(n)\
    \ {\n                if (n) for (int i = 1, mod = mods[0]; i < n; ++i) {\n   \
    \                 assert(mod > mods[i]);\n                    invs[i] = atcoder::inv_mod(mod,\
    \ mods[i]);\n                    mod *= mods[i];\n                }\n        \
    \    }\n            int operator()(const std::vector<int>& r) const {\n      \
    \          if (n == 0) return 0;\n                int rem = r[0];\n          \
    \      for (int i = 1, mod = mods[0]; i < n; ++i) {\n                    rem +=\
    \ (r[i] - rem) * invs[i] % mods[i] * mod;\n                    mod *= mods[i];\n\
    \                    if (rem < 0) rem += mod;\n                }\n           \
    \     return rem;\n            }\n        } crt;\n    };\n} // namespace suisen\n\
    \n\n#endif // SUISEN_BINOMIAL_COEFFICIENT\n"
  dependsOn:
  - library/number/barrett_reduction.hpp
  isVerificationFile: false
  path: library/sequence/binomial_coefficient.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
documentation_of: library/sequence/binomial_coefficient.hpp
layout: document
title: Binomial Coefficient
---
## Binomial Coefficient
