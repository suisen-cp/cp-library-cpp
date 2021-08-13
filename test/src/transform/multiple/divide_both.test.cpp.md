---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/number/internal_eratosthenes.hpp
    title: library/number/internal_eratosthenes.hpp
  - icon: ':question:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: library/number/sieve_of_eratosthenes.hpp
  - icon: ':x:'
    path: library/transform/divisor.hpp
    title: "\u7D04\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/transform/multiple.hpp
    title: "\u500D\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc206/tasks/abc206_e
    links:
    - https://atcoder.jp/contests/abc206/tasks/abc206_e
  bundledCode: "#line 1 \"test/src/transform/multiple/divide_both.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc206/tasks/abc206_e\"\n\n#include <cassert>\n\
    #include <iostream>\n\n#line 1 \"library/transform/multiple.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen::internal::arithmetic_operator {}\n\nnamespace\
    \ suisen {\nnamespace multiple_transform {\n\nusing namespace suisen::internal::arithmetic_operator;\n\
    \n// Calculates `g` s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename\
    \ T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign add_assign) {\n\
    \    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n    auto\
    \ cum = [&](const int p) {\n        const int qmax = (n - 1) / p, rmax = qmax\
    \ * p;\n        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n      \
    \      add_assign(f[q], f[pq]);\n            is_prime[pq] = false;\n        }\n\
    \    };\n    cum(2);\n    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n\
    }\n\n// Calculates `f` s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename\
    \ T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n \
    \   auto diff = [&](const int p) {\n        for (int q = 1, pq = p; pq < n; ++q,\
    \ pq += p) {\n            sub_assign(f[q], f[pq]);\n            is_prime[pq] =\
    \ false;\n        }\n    };\n    diff(2);\n    for (int p = 3; p < n; p += 2)\
    \ if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t. g(n) = Sum_{n | m} f(m)\
    \ inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T> &f) {\n    zeta(f,\
    \ [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f` s.t. g(n) = Sum_{n\
    \ | m} f(m) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T> &f) {\n\
    \    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace multiple_transform\n\
    \ntemplate <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign,\
    \ SubAssign sub_assign>\nstruct MultipleTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        multiple_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        multiple_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct MultipleTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        multiple_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        multiple_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/transform/divisor.hpp\"\
    \n\n\n\n#line 5 \"library/transform/divisor.hpp\"\n\nnamespace suisen::internal::arithmetic_operator\
    \ {}\n\nnamespace suisen {\nnamespace divisor_transform {\n\nusing namespace suisen::internal::arithmetic_operator;\n\
    \n// Calculates `g` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename\
    \ T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign add_assign) {\n\
    \    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n    auto\
    \ cum = [&](const int p) {\n        for (int q = 1, pq = p; pq < n; ++q, pq +=\
    \ p) {\n            add_assign(f[pq], f[q]);\n            is_prime[pq] = false;\n\
    \        }\n    };\n    cum(2);\n    for (int p = 3; p < n; p += 2) if (is_prime[p])\
    \ cum(p);\n}\n\n// Calculates `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate\
    \ <typename T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n \
    \   auto diff = [&](const int p) {\n        const int qmax = (n - 1) / p, rmax\
    \ = qmax * p;\n        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n\
    \            sub_assign(f[pq], f[q]);\n            is_prime[pq] = false;\n   \
    \     }\n    };\n    diff(2);\n    for (int p = 3; p < n; p += 2) if (is_prime[p])\
    \ diff(p);\n}\n\n// Calculates `g` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate\
    \ <typename T>\nvoid zeta(std::vector<T> &f) {\n    zeta(f, [](T &a, const T &b)\
    \ { a += b; });\n}\n\n// Calculates `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\n\
    template <typename T>\nvoid mobius(std::vector<T> &f) {\n    mobius(f, [](T &a,\
    \ const T &b) { a -= b; });\n}\n\n} // namespace divisor_transform\n\ntemplate\
    \ <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign\
    \ sub_assign>\nstruct DivisorTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        divisor_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        divisor_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct DivisorTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        divisor_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        divisor_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\
    \n\n\n\n#line 5 \"library/number/sieve_of_eratosthenes.hpp\"\n#include <cmath>\n\
    #line 7 \"library/number/sieve_of_eratosthenes.hpp\"\n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\
    \n\n\n\n#include <cstdint>\n#line 6 \"library/number/internal_eratosthenes.hpp\"\
    \n\nnamespace suisen::internal::sieve {\n\nconstexpr std::uint8_t K = 8;\nconstexpr\
    \ std::uint8_t PROD = 2 * 3 * 5;\nconstexpr std::uint8_t RM[K] = { 1,  7, 11,\
    \ 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2, \
    \ 4,  6,  2 };\nconstexpr std::uint8_t DF[K][K] = {\n    { 0, 0, 0, 0, 0, 0, 0,\
    \ 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1,\
    \ 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n\
    \    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t\
    \ DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K]\
    \ = {\n    {  0,  0,  0,  0,  0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8, \
    \ 8 },\n    { 16, 16,  0, 16,  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,\
    \  8 },\n    { 24, 24,  8, 16,  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,\
    \  8 },\n    { 40, 24,  8, 32,  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,\
    \  8 },\n};\n\nconstexpr std::uint8_t MASK[K][K] = {\n    { 0x01, 0x02, 0x04,\
    \ 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04,\
    \ 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01,\
    \ 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40,\
    \ 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },\n    { 0x40,\
    \ 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08,\
    \ 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K] = {\n    { 0, 1,\
    \ 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3, 2, 6, },\n    { 2, 4, 0, 6, 1,\
    \ 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n    { 4, 7, 1, 2, 5, 6, 0, 3,\
    \ },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6, 2, 3, 7, 0, 4, 5, 1, },\n   \
    \ { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t mask_to_index(const\
    \ std::uint8_t bits) {\n    switch (bits) {\n        case 1 << 0: return 0;\n\
    \        case 1 << 1: return 1;\n        case 1 << 2: return 2;\n        case\
    \ 1 << 3: return 3;\n        case 1 << 4: return 4;\n        case 1 << 5: return\
    \ 5;\n        case 1 << 6: return 6;\n        case 1 << 7: return 7;\n       \
    \ default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\n\
    \n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <unsigned int N>\nclass SimpleSieve {\n    private:\n        static\
    \ constexpr unsigned int siz = N / internal::sieve::PROD + 1;\n        static\
    \ std::uint8_t flag[siz];\n    public:\n        SimpleSieve() {\n            using\
    \ namespace internal::sieve;\n            flag[0] |= 1;\n            unsigned\
    \ int k_max = (unsigned int) std::sqrt(N + 2) / PROD;\n            for (unsigned\
    \ int kp = 0; kp <= k_max; ++kp) {\n                for (std::uint8_t bits = ~flag[kp];\
    \ bits; bits &= bits - 1) {\n                    const std::uint8_t mp = mask_to_index(bits\
    \ & -bits), m = RM[mp];\n                    unsigned int kr = kp * (PROD * kp\
    \ + 2 * m) + m * m / PROD;\n                    for (std::uint8_t mq = mp; kr\
    \ < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                      \
    \  flag[kr] |= MASK[mp][mq];\n                    }\n                }\n     \
    \       }\n        }\n        bool is_prime(const unsigned int p) const {\n  \
    \          using namespace internal::sieve;\n            switch (p) {\n      \
    \          case 2: case 3: case 5: return true;\n                default:\n  \
    \                  switch (p % PROD) {\n                        case RM[0]: return\
    \ ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]: return\
    \ ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]: return\
    \ ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]: return\
    \ ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]: return\
    \ ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]: return\
    \ ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]: return\
    \ ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]: return\
    \ ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return false;\n\
    \                    }\n            }\n        }\n};\ntemplate <unsigned int N>\n\
    std::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];\n\ntemplate <unsigned\
    \ int N>\nclass Sieve {\n    private:\n        static constexpr unsigned int base_max\
    \ = (N + 1) * internal::sieve::K / internal::sieve::PROD;\n        static unsigned\
    \ int pf[base_max + internal::sieve::K];\n\n    public:\n        Sieve() {\n \
    \           using namespace internal::sieve;\n            pf[0] = 1;\n       \
    \     unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1) / PROD;\n   \
    \         for (unsigned int kp = 0; kp <= k_max; ++kp) {\n                const\
    \ int base_i = kp * K, base_act_i = kp * PROD;\n                for (int mp =\
    \ 0; mp < K; ++mp) {\n                    const int m = RM[mp], i = base_i + mp;\n\
    \                    if (pf[i] == 0) {\n                        unsigned int act_i\
    \ = base_act_i + m;\n                        unsigned int base_k = (kp * (PROD\
    \ * kp + 2 * m) + m * m / PROD) * K;\n                        for (std::uint8_t\
    \ mq = mp; base_k <= base_max; base_k += kp * DRP[mq] + DFP[mp][mq], ++mq &= 7)\
    \ {\n                            pf[base_k + OFFSET[mp][mq]] = act_i;\n      \
    \                  }\n                    }\n                }\n            }\n\
    \        }\n        bool is_prime(const unsigned int p) const {\n            using\
    \ namespace internal::sieve;\n            switch (p) {\n                case 2:\
    \ case 3: case 5: return true;\n                default:\n                   \
    \ switch (p % PROD) {\n                        case RM[0]: return pf[p / PROD\
    \ * K + 0] == 0;\n                        case RM[1]: return pf[p / PROD * K +\
    \ 1] == 0;\n                        case RM[2]: return pf[p / PROD * K + 2] ==\
    \ 0;\n                        case RM[3]: return pf[p / PROD * K + 3] == 0;\n\
    \                        case RM[4]: return pf[p / PROD * K + 4] == 0;\n     \
    \                   case RM[5]: return pf[p / PROD * K + 5] == 0;\n          \
    \              case RM[6]: return pf[p / PROD * K + 6] == 0;\n               \
    \         case RM[7]: return pf[p / PROD * K + 7] == 0;\n                    \
    \    default: return false;\n                    }\n            }\n        }\n\
    \        int prime_factor(const unsigned int p) const {\n            using namespace\
    \ internal::sieve;\n            switch (p % PROD) {\n                case  0:\
    \ case  2: case  4: case  6: case  8:\n                case 10: case 12: case\
    \ 14: case 16: case 18:\n                case 20: case 22: case 24: case 26: case\
    \ 28: return 2;\n                case  3: case  9: case 15: case 21: case 27:\
    \ return 3;\n                case  5: case 25: return 5;\n                case\
    \ RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD * K + 0] : p;\n           \
    \     case RM[1]: return pf[p / PROD * K + 1] ? pf[p / PROD * K + 1] : p;\n  \
    \              case RM[2]: return pf[p / PROD * K + 2] ? pf[p / PROD * K + 2]\
    \ : p;\n                case RM[3]: return pf[p / PROD * K + 3] ? pf[p / PROD\
    \ * K + 3] : p;\n                case RM[4]: return pf[p / PROD * K + 4] ? pf[p\
    \ / PROD * K + 4] : p;\n                case RM[5]: return pf[p / PROD * K + 5]\
    \ ? pf[p / PROD * K + 5] : p;\n                case RM[6]: return pf[p / PROD\
    \ * K + 6] ? pf[p / PROD * K + 6] : p;\n                case RM[7]: return pf[p\
    \ / PROD * K + 7] ? pf[p / PROD * K + 7] : p;\n                default: assert(false);\n\
    \            }\n        }\n        /**\n         * Returns a vector of `{ prime,\
    \ index }`.\n         */\n        std::vector<std::pair<int, int>> factorize(unsigned\
    \ int n) const {\n            assert(0 < n and n <= N);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = prime_factor(n),\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n        /**\n         * Returns the divisors of `n`.\n         * It\
    \ is NOT guaranteed that the returned vector is sorted.\n         */\n       \
    \ std::vector<int> divisors(unsigned int n) const {\n            assert(0 < n\
    \ and n <= N);\n            std::vector<int> divs { 1 };\n            for (auto\
    \ [prime, index] : factorize(n)) {\n                int sz = divs.size();\n  \
    \              for (int i = 0; i < sz; ++i) {\n                    int d = divs[i];\n\
    \                    for (int j = 0; j < index; ++j) {\n                     \
    \   divs.push_back(d *= prime);\n                    }\n                }\n  \
    \          }\n            return divs;\n        }\n};\ntemplate <unsigned int\
    \ N>\nunsigned int Sieve<N>::pf[Sieve<N>::base_max + internal::sieve::K];\n} //\
    \ namespace suisen\n\n\n#line 9 \"test/src/transform/multiple/divide_both.test.cpp\"\
    \nusing namespace suisen;\n\nconst Sieve<1000000> sieve;\n\n// count l <= x, y\
    \ <= r s.t. gcd(x, y) = 1\nlong long count_coprime_pairs(int l, int r) {\n   \
    \ std::vector<long long> f(r + 1, 0);\n    for (int g = 1; g <= r; ++g) {\n  \
    \      long long w = r / g - (l + g - 1) / g + 1;\n        f[g] = w * w;\n   \
    \ }\n    std::vector<long long> f_copy = f;\n    multiple_transform::mobius(f);\n\
    \    long long ret = f[1];\n    {\n        {\n            multiple_transform::zeta(f);\n\
    \            assert(f == f_copy);\n            multiple_transform::mobius(f);\n\
    \            f_copy = f;\n        }\n        std::vector<long long> div_cum_naive(r\
    \ + 1, 0);\n        for (int g = 1; g <= r; ++g) {\n            for (int d : sieve.divisors(g))\
    \ {\n                div_cum_naive[g] += f[d];\n            }\n        }\n   \
    \     divisor_transform::zeta(f);\n        assert(f == div_cum_naive);\n     \
    \   divisor_transform::mobius(f);\n        assert(f == f_copy);\n    }\n    return\
    \ ret;\n}\n\nint main() {\n    int l, r;\n    std::cin >> l >> r;\n\n    long\
    \ long whole = (long long) (r - l + 1) * (r - l + 1);\n    long long coprime_pairs_num\
    \ = count_coprime_pairs(l, r);\n    long long divisor_pairs_num = 0;\n    for\
    \ (int g = l + (l == 1); g <= r; ++g) {\n        divisor_pairs_num += 2 * (r /\
    \ g - 1) + 1;\n    }\n    long long ans = whole - (coprime_pairs_num + divisor_pairs_num);\n\
    \    std::cout << ans << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc206/tasks/abc206_e\"\n\n\
    #include <cassert>\n#include <iostream>\n\n#include \"library/transform/multiple.hpp\"\
    \n#include \"library/transform/divisor.hpp\"\n#include \"library/number/sieve_of_eratosthenes.hpp\"\
    \nusing namespace suisen;\n\nconst Sieve<1000000> sieve;\n\n// count l <= x, y\
    \ <= r s.t. gcd(x, y) = 1\nlong long count_coprime_pairs(int l, int r) {\n   \
    \ std::vector<long long> f(r + 1, 0);\n    for (int g = 1; g <= r; ++g) {\n  \
    \      long long w = r / g - (l + g - 1) / g + 1;\n        f[g] = w * w;\n   \
    \ }\n    std::vector<long long> f_copy = f;\n    multiple_transform::mobius(f);\n\
    \    long long ret = f[1];\n    {\n        {\n            multiple_transform::zeta(f);\n\
    \            assert(f == f_copy);\n            multiple_transform::mobius(f);\n\
    \            f_copy = f;\n        }\n        std::vector<long long> div_cum_naive(r\
    \ + 1, 0);\n        for (int g = 1; g <= r; ++g) {\n            for (int d : sieve.divisors(g))\
    \ {\n                div_cum_naive[g] += f[d];\n            }\n        }\n   \
    \     divisor_transform::zeta(f);\n        assert(f == div_cum_naive);\n     \
    \   divisor_transform::mobius(f);\n        assert(f == f_copy);\n    }\n    return\
    \ ret;\n}\n\nint main() {\n    int l, r;\n    std::cin >> l >> r;\n\n    long\
    \ long whole = (long long) (r - l + 1) * (r - l + 1);\n    long long coprime_pairs_num\
    \ = count_coprime_pairs(l, r);\n    long long divisor_pairs_num = 0;\n    for\
    \ (int g = l + (l == 1); g <= r; ++g) {\n        divisor_pairs_num += 2 * (r /\
    \ g - 1) + 1;\n    }\n    long long ans = whole - (coprime_pairs_num + divisor_pairs_num);\n\
    \    std::cout << ans << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/transform/multiple.hpp
  - library/transform/divisor.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  isVerificationFile: true
  path: test/src/transform/multiple/divide_both.test.cpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/transform/multiple/divide_both.test.cpp
layout: document
redirect_from:
- /verify/test/src/transform/multiple/divide_both.test.cpp
- /verify/test/src/transform/multiple/divide_both.test.cpp.html
title: test/src/transform/multiple/divide_both.test.cpp
---