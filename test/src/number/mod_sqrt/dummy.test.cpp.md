---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/mod_sqrt.hpp
    title: Mod Sqrt
  - icon: ':question:'
    path: library/number/util.hpp
    title: Util
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/number/mod_sqrt/dummy.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\n\n#include\
    \ <iostream>\n#include <random>\n\n#line 1 \"library/number/util.hpp\"\n\n\n\n\
    #include <array>\n#include <cassert>\n#include <cmath>\n#include <numeric>\n#include\
    \ <tuple>\n#include <vector>\n\n/**\n * @brief Utilities\n*/\n\nnamespace suisen\
    \ {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T powi(T a, int b) {\n        T res = 1, pow_a = a;\n      \
    \  for (; b; b >>= 1) {\n            if (b & 1) res *= pow_a;\n            pow_a\
    \ *= pow_a;\n        }\n        return res;\n    }\n\n    /**\n     * @brief Calculates\
    \ the prime factorization of n in O(\u221An).\n     * @tparam T integer type\n\
    \     * @param n integer to factorize\n     * @return vector of { prime, exponent\
    \ }. It is guaranteed that prime is ascending.\n     */\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    std::vector<std::pair<T,\
    \ int>> factorize(T n) {\n        static constexpr std::array primes{ 2, 3, 5,\
    \ 7, 11, 13 };\n        static constexpr int next_prime = 17;\n        static\
    \ constexpr int siz = std::array{ 1, 2, 8, 48, 480, 5760, 92160 } [primes.size()\
    \ - 1] ;\n        static constexpr int period = [] {\n            int res = 1;\n\
    \            for (auto e : primes) res *= e;\n            return res;\n      \
    \      }();\n        static constexpr struct S : public std::array<int, siz> {\n\
    \            constexpr S() {\n                for (int i = next_prime, j = 0;\
    \ i < period + next_prime; i += 2) {\n                    bool ok = true;\n  \
    \                  for (int p : primes) ok &= i % p > 0;\n                   \
    \ if (ok) (*this)[j++] = i - next_prime;\n                }\n            }\n \
    \       } s{};\n\n        assert(n > 0);\n        std::vector<std::pair<T, int>>\
    \ res;\n        auto f = [&res, &n](int p) {\n            if (n % p) return;\n\
    \            int cnt = 0;\n            do n /= p, ++cnt; while (n % p == 0);\n\
    \            res.emplace_back(p, cnt);\n            };\n        for (int p : primes)\
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
    \        for (int i = 1; i <= n; ++i) {\n            for (int j = i; j <= n; j\
    \ += i) divs[j].push_back(i);\n        }\n        return divs;\n    }\n\n    /**\n\
    \     * @brief Calculates \u03C6(n) from its prime-factorized form in O(log n).\n\
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
    \ = (i & 1) == 0 ? i >> 1 : i;\n        for (int p = 3; p <= n; p += 2) {\n  \
    \          if (res[p] != p) continue;\n            for (int q = p; q <= n; q +=\
    \ p) res[q] /= p, res[q] *= p - 1;\n        }\n        return res;\n    }\n\n\
    \    /**\n     * @brief Calculates \u03BB(n) from its prime-factorized form in\
    \ O(log n).\n     * @tparam T integer type\n     * @param factorized a prime-factorized\
    \ form of n (a vector of { prime, exponent })\n     * @return \u03BB(n)\n    \
    \ */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    T carmichael(const std::vector<std::pair<T, int>>& factorized)\
    \ {\n        T res = 1;\n        for (const auto& [p, c] : factorized) {\n   \
    \         res = std::lcm(res, ((p - 1) * powi(p, c - 1)) >> (p == 2 and c >= 3));\n\
    \        }\n        return res;\n    }\n    /**\n     * @brief Calculates \u03BB\
    (n) in O(\u221An).\n     * @tparam T integer type\n     * @param n\n     * @return\
    \ \u03BB(n)\n     */\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T carmichael(T n) {\n        return carmichael(factorize(n));\n\
    \    }\n} // namespace suisen\n\n\n#line 1 \"library/number/mod_sqrt.hpp\"\n\n\
    \n\n#include <optional>\n#include <atcoder/math>\n\nnamespace suisen {\n    namespace\
    \ internal {\n        long long inv_mod64(long long a, long long m) {\n      \
    \      return atcoder::inv_mod(a, m);\n        }\n        long long pow_mod64(long\
    \ long a, long long b, long long m) {\n            if ((a %= m) < 0) a += m;\n\
    \            long long res = 1, pow_a = a;\n            for (; b; b >>= 1) {\n\
    \                if (b & 1) {\n                    res = __int128_t(res) * pow_a\
    \ % m;\n                }\n                pow_a = __int128_t(pow_a) * pow_a %\
    \ m;\n            }\n            return res;\n        }\n        long long mul_mod64(long\
    \ long a, long long b, long long m) {\n            return __int128_t(a) * b %\
    \ m;\n        }\n    }\n\n    std::optional<long long> prime_mod_sqrt(long long\
    \ a, const long long p) {\n        using namespace internal;\n\n        if ((a\
    \ %= p) < 0) a += p;\n\n        if (a == 0) return 0;\n        if (p == 2) return\
    \ a;\n\n        if (pow_mod64(a, (p - 1) / 2, p) != 1) {\n            return std::nullopt;\n\
    \        }\n\n        long long b = 1;\n        while (pow_mod64(b, (p - 1) /\
    \ 2, p) == 1) {\n            ++b;\n        }\n\n        int tlz = __builtin_ctz(p\
    \ - 1);\n        long long q = (p - 1) >> tlz;\n\n        long long ia = inv_mod64(a,\
    \ p);\n\n        long long x = pow_mod64(a, (q + 1) / 2, p);\n        b = pow_mod64(b,\
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
    \    }\n} // namespace suisen\n\n\n\n#line 8 \"test/src/number/mod_sqrt/dummy.test.cpp\"\
    \n\nvoid test_small() {\n    for (int m = 1; m <= 700; ++m) {\n        for (int\
    \ a = 0; a < m; ++a) {\n            auto x = suisen::composite_mod_sqrt(a, suisen::factorize(m));\n\
    \            if (x) {\n                int x0 = *x;\n                assert(x0\
    \ * x0 % m == a);\n            } else {\n                for (int b = 0; b < m;\
    \ ++b) {\n                    assert(b * b % m != a);\n                }\n   \
    \         }\n        }\n    }\n}\n\nvoid test_large() {\n    std::mt19937 rng{\
    \ 0 };\n    std::uniform_int_distribution<long long> dist_m(1, 1000000000000);\n\
    \    \n    for (int q = 0; q < 100; ++q) {\n        long long m = dist_m(rng);\n\
    \        std::uniform_int_distribution<long long> dist_a(0, m - 1);\n        auto\
    \ factorized = suisen::factorize(m);\n\n        for (int inner_q = 0; inner_q\
    \ < 10000; ++inner_q) {\n            long long a = dist_a(rng);\n\n          \
    \  auto x = suisen::composite_mod_sqrt(a, factorized);\n            if (x) {\n\
    \                __int128_t x0 = *x;\n                assert(x0 * x0 % m == a);\n\
    \            }\n        }\n    }\n}\n\nvoid test() {\n    test_small();\n    test_large();\n\
    }\n\nint main() {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include \"library/number/util.hpp\"\
    \n#include \"library/number/mod_sqrt.hpp\"\n\nvoid test_small() {\n    for (int\
    \ m = 1; m <= 700; ++m) {\n        for (int a = 0; a < m; ++a) {\n           \
    \ auto x = suisen::composite_mod_sqrt(a, suisen::factorize(m));\n            if\
    \ (x) {\n                int x0 = *x;\n                assert(x0 * x0 % m == a);\n\
    \            } else {\n                for (int b = 0; b < m; ++b) {\n       \
    \             assert(b * b % m != a);\n                }\n            }\n    \
    \    }\n    }\n}\n\nvoid test_large() {\n    std::mt19937 rng{ 0 };\n    std::uniform_int_distribution<long\
    \ long> dist_m(1, 1000000000000);\n    \n    for (int q = 0; q < 100; ++q) {\n\
    \        long long m = dist_m(rng);\n        std::uniform_int_distribution<long\
    \ long> dist_a(0, m - 1);\n        auto factorized = suisen::factorize(m);\n\n\
    \        for (int inner_q = 0; inner_q < 10000; ++inner_q) {\n            long\
    \ long a = dist_a(rng);\n\n            auto x = suisen::composite_mod_sqrt(a,\
    \ factorized);\n            if (x) {\n                __int128_t x0 = *x;\n  \
    \              assert(x0 * x0 % m == a);\n            }\n        }\n    }\n}\n\
    \nvoid test() {\n    test_small();\n    test_large();\n}\n\nint main() {\n   \
    \ test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  dependsOn:
  - library/number/util.hpp
  - library/number/mod_sqrt.hpp
  isVerificationFile: true
  path: test/src/number/mod_sqrt/dummy.test.cpp
  requiredBy: []
  timestamp: '2025-01-26 15:55:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/mod_sqrt/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/mod_sqrt/dummy.test.cpp
- /verify/test/src/number/mod_sqrt/dummy.test.cpp.html
title: test/src/number/mod_sqrt/dummy.test.cpp
---
