---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/mod_sqrt/dummy.test.cpp
    title: test/src/number/mod_sqrt/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://aozoragakuen.sakura.ne.jp/suuron/node24.html
    - https://twitter.com/maspy_stars/status/1613931151718244352?s=20&t=lAf7ztW2fb_IZa544lo2xw
  bundledCode: "#line 1 \"library/number/mod_sqrt.hpp\"\n\n\n\n#include <optional>\n\
    #include <atcoder/math>\n\nnamespace suisen {\n    namespace internal {\n    \
    \    long long inv_mod64(long long a, long long m) {\n            return atcoder::inv_mod(a,\
    \ m);\n        }\n        long long pow_mod64(long long a, long long b, long long\
    \ m) {\n            if ((a %= m) < 0) a += m;\n            long long res = 1,\
    \ pow_a = a;\n            for (; b; b >>= 1) {\n                if (b & 1) {\n\
    \                    res = __int128_t(res) * pow_a % m;\n                }\n \
    \               pow_a = __int128_t(pow_a) * pow_a % m;\n            }\n      \
    \      return res;\n        }\n        long long mul_mod64(long long a, long long\
    \ b, long long m) {\n            return __int128_t(a) * b % m;\n        }\n  \
    \  }\n\n    std::optional<long long> prime_mod_sqrt(long long a, const long long\
    \ p) {\n        using namespace internal;\n\n        if ((a %= p) < 0) a += p;\n\
    \n        if (a == 0) return 0;\n        if (p == 2) return a;\n\n        if (pow_mod64(a,\
    \ (p - 1) / 2, p) != 1) {\n            return std::nullopt;\n        }\n\n   \
    \     long long b = 1;\n        while (pow_mod64(b, (p - 1) / 2, p) == 1) {\n\
    \            ++b;\n        }\n\n        int tlz = __builtin_ctz(p - 1);\n    \
    \    long long q = (p - 1) >> tlz;\n\n        long long ia = inv_mod64(a, p);\n\
    \n        long long x = pow_mod64(a, (q + 1) / 2, p);\n        b = pow_mod64(b,\
    \ q, p);\n        for (int shift = 2;; ++shift) {\n            long long x2 =\
    \ mul_mod64(x, x, p);\n            if (x2 == a) {\n                return x;\n\
    \            }\n            long long e = mul_mod64(ia, x2, p);\n            if\
    \ (pow_mod64(e, 1 << (tlz - shift), p) != 1) {\n                x = mul_mod64(x,\
    \ b, p);\n            }\n            b = mul_mod64(b, b, p);\n        }\n    }\n\
    \n    namespace internal {\n        std::optional<long long> prime_power_mod_sqrt(long\
    \ long a, long long p, int q) {\n            std::vector<long long> pq(q + 1);\n\
    \            pq[0] = 1;\n            for (int i = 1; i <= q; ++i) {\n        \
    \        pq[i] = pq[i - 1] * p;\n            }\n            if ((a %= pq[q]) ==\
    \ 0) return 0;\n\n            int b = 0;\n            for (; a % p == 0; a /=\
    \ p) {\n                ++b;\n            }\n            if (b % 2) {\n      \
    \          return std::nullopt;\n            }\n            const long long c\
    \ = pq[b / 2];\n\n            q -= b;\n\n            if (p != 2) {\n         \
    \       // reference: http://aozoragakuen.sakura.ne.jp/suuron/node24.html\n  \
    \              // f(x) = x^2 - a, f'(x) = 2x\n                // Lifting from\
    \ f(x_i)=0 mod p^i to f(x_{i+1})=0 mod p^{i+1}\n                auto ox = prime_mod_sqrt(a,\
    \ p);\n                if (not ox) {\n                    return std::nullopt;\n\
    \                }\n                long long x = *ox;\n                // f'(x_i)\
    \ != 0\n                const long long inv_df_x0 = inv_mod64(2 * x, p);\n   \
    \             for (int i = 1; i < q; ++i) {\n                    // Requirements:\n\
    \                    //      x_{i+1} = x_i + p^i * y for some 0 <= y < p.\n  \
    \                  // Taylor expansion:\n                    //      f(x_i + p^i\
    \ y) = f(x_i) + y p^i f'(x_i) + p^{i+1} * (...)\n                    // f(x_i)\
    \ = 0 (mod p^i) and f'(x_i) = f'(x_0) != 0 (mod p), so\n                    //\
    \      y = -(f(x_i)/p^i) * f'(x_0)^(-1) (mod p)\n                    __int128_t\
    \ f_x = __int128_t(x) * x - a;\n                    long long y = mul_mod64(-(f_x\
    \ / pq[i]) % p, inv_df_x0, p);\n                    if (y < 0) y += p;\n     \
    \               x += pq[i] * y;\n                }\n                return c *\
    \ x;\n            } else {\n                // p = 2\n                if (a %\
    \ 8 != 1) {\n                    return std::nullopt;\n                }\n   \
    \             // reference: https://twitter.com/maspy_stars/status/1613931151718244352?s=20&t=lAf7ztW2fb_IZa544lo2xw\n\
    \                long long x = 1; // or 3\n                for (int i = 3; i <\
    \ q; ++i) {\n                    // Requirements:\n                    //    \
    \  x_{i+1} = x_i + 2^{i-1} y for some 0 <= y < 2.\n                    // x_i\
    \ is an odd number, so\n                    //      (x_i + 2^{i-1} y)^2 = x_i^2\
    \ + y 2^i (mod 2^{i+1}).\n                    // Therefore,\n                \
    \    //      y = (a - x_i^2)/2^i (mod 2).\n                    __int128_t f_x\
    \ = __int128_t(x) * x - a;\n                    x |= ((f_x >> i) & 1) << (i -\
    \ 1);\n                }\n                return c * x;\n            }\n     \
    \   }\n    }\n\n    template <typename PrimePowers>\n    std::optional<long long>\
    \ composite_mod_sqrt(long long a, const PrimePowers& factorized) {\n        std::vector<long\
    \ long> rs, ms;\n        for (auto [p, q] : factorized) {\n            auto x\
    \ = internal::prime_power_mod_sqrt(a, p, q);\n            if (not x) {\n     \
    \           return std::nullopt;\n            }\n            rs.push_back(*x);\n\
    \            long long& pq = ms.emplace_back(1);\n            for (int i = 0;\
    \ i < q; ++i) pq *= p;\n        }\n        return atcoder::crt(rs, ms).first;\n\
    \    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MOD_SQRT\n#define SUISEN_MOD_SQRT\n\n#include <optional>\n\
    #include <atcoder/math>\n\nnamespace suisen {\n    namespace internal {\n    \
    \    long long inv_mod64(long long a, long long m) {\n            return atcoder::inv_mod(a,\
    \ m);\n        }\n        long long pow_mod64(long long a, long long b, long long\
    \ m) {\n            if ((a %= m) < 0) a += m;\n            long long res = 1,\
    \ pow_a = a;\n            for (; b; b >>= 1) {\n                if (b & 1) {\n\
    \                    res = __int128_t(res) * pow_a % m;\n                }\n \
    \               pow_a = __int128_t(pow_a) * pow_a % m;\n            }\n      \
    \      return res;\n        }\n        long long mul_mod64(long long a, long long\
    \ b, long long m) {\n            return __int128_t(a) * b % m;\n        }\n  \
    \  }\n\n    std::optional<long long> prime_mod_sqrt(long long a, const long long\
    \ p) {\n        using namespace internal;\n\n        if ((a %= p) < 0) a += p;\n\
    \n        if (a == 0) return 0;\n        if (p == 2) return a;\n\n        if (pow_mod64(a,\
    \ (p - 1) / 2, p) != 1) {\n            return std::nullopt;\n        }\n\n   \
    \     long long b = 1;\n        while (pow_mod64(b, (p - 1) / 2, p) == 1) {\n\
    \            ++b;\n        }\n\n        int tlz = __builtin_ctz(p - 1);\n    \
    \    long long q = (p - 1) >> tlz;\n\n        long long ia = inv_mod64(a, p);\n\
    \n        long long x = pow_mod64(a, (q + 1) / 2, p);\n        b = pow_mod64(b,\
    \ q, p);\n        for (int shift = 2;; ++shift) {\n            long long x2 =\
    \ mul_mod64(x, x, p);\n            if (x2 == a) {\n                return x;\n\
    \            }\n            long long e = mul_mod64(ia, x2, p);\n            if\
    \ (pow_mod64(e, 1 << (tlz - shift), p) != 1) {\n                x = mul_mod64(x,\
    \ b, p);\n            }\n            b = mul_mod64(b, b, p);\n        }\n    }\n\
    \n    namespace internal {\n        std::optional<long long> prime_power_mod_sqrt(long\
    \ long a, long long p, int q) {\n            std::vector<long long> pq(q + 1);\n\
    \            pq[0] = 1;\n            for (int i = 1; i <= q; ++i) {\n        \
    \        pq[i] = pq[i - 1] * p;\n            }\n            if ((a %= pq[q]) ==\
    \ 0) return 0;\n\n            int b = 0;\n            for (; a % p == 0; a /=\
    \ p) {\n                ++b;\n            }\n            if (b % 2) {\n      \
    \          return std::nullopt;\n            }\n            const long long c\
    \ = pq[b / 2];\n\n            q -= b;\n\n            if (p != 2) {\n         \
    \       // reference: http://aozoragakuen.sakura.ne.jp/suuron/node24.html\n  \
    \              // f(x) = x^2 - a, f'(x) = 2x\n                // Lifting from\
    \ f(x_i)=0 mod p^i to f(x_{i+1})=0 mod p^{i+1}\n                auto ox = prime_mod_sqrt(a,\
    \ p);\n                if (not ox) {\n                    return std::nullopt;\n\
    \                }\n                long long x = *ox;\n                // f'(x_i)\
    \ != 0\n                const long long inv_df_x0 = inv_mod64(2 * x, p);\n   \
    \             for (int i = 1; i < q; ++i) {\n                    // Requirements:\n\
    \                    //      x_{i+1} = x_i + p^i * y for some 0 <= y < p.\n  \
    \                  // Taylor expansion:\n                    //      f(x_i + p^i\
    \ y) = f(x_i) + y p^i f'(x_i) + p^{i+1} * (...)\n                    // f(x_i)\
    \ = 0 (mod p^i) and f'(x_i) = f'(x_0) != 0 (mod p), so\n                    //\
    \      y = -(f(x_i)/p^i) * f'(x_0)^(-1) (mod p)\n                    __int128_t\
    \ f_x = __int128_t(x) * x - a;\n                    long long y = mul_mod64(-(f_x\
    \ / pq[i]) % p, inv_df_x0, p);\n                    if (y < 0) y += p;\n     \
    \               x += pq[i] * y;\n                }\n                return c *\
    \ x;\n            } else {\n                // p = 2\n                if (a %\
    \ 8 != 1) {\n                    return std::nullopt;\n                }\n   \
    \             // reference: https://twitter.com/maspy_stars/status/1613931151718244352?s=20&t=lAf7ztW2fb_IZa544lo2xw\n\
    \                long long x = 1; // or 3\n                for (int i = 3; i <\
    \ q; ++i) {\n                    // Requirements:\n                    //    \
    \  x_{i+1} = x_i + 2^{i-1} y for some 0 <= y < 2.\n                    // x_i\
    \ is an odd number, so\n                    //      (x_i + 2^{i-1} y)^2 = x_i^2\
    \ + y 2^i (mod 2^{i+1}).\n                    // Therefore,\n                \
    \    //      y = (a - x_i^2)/2^i (mod 2).\n                    __int128_t f_x\
    \ = __int128_t(x) * x - a;\n                    x |= ((f_x >> i) & 1) << (i -\
    \ 1);\n                }\n                return c * x;\n            }\n     \
    \   }\n    }\n\n    template <typename PrimePowers>\n    std::optional<long long>\
    \ composite_mod_sqrt(long long a, const PrimePowers& factorized) {\n        std::vector<long\
    \ long> rs, ms;\n        for (auto [p, q] : factorized) {\n            auto x\
    \ = internal::prime_power_mod_sqrt(a, p, q);\n            if (not x) {\n     \
    \           return std::nullopt;\n            }\n            rs.push_back(*x);\n\
    \            long long& pq = ms.emplace_back(1);\n            for (int i = 0;\
    \ i < q; ++i) pq *= p;\n        }\n        return atcoder::crt(rs, ms).first;\n\
    \    }\n} // namespace suisen\n\n\n#endif // SUISEN_MOD_SQRT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/mod_sqrt.hpp
  requiredBy: []
  timestamp: '2023-01-14 03:03:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/mod_sqrt/dummy.test.cpp
documentation_of: library/number/mod_sqrt.hpp
layout: document
title: Mod Sqrt
---
## Mod Sqrt
