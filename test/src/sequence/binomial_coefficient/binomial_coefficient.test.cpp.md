---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/barrett_reduction.hpp
    title: library/number/barrett_reduction.hpp
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient.hpp
    title: Binomial Coefficient
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 1 \"test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\n\
    #include <iostream>\n\n#line 1 \"library/sequence/binomial_coefficient.hpp\"\n\
    \n\n\n#include <cassert>\n#include <vector>\n#include <atcoder/math>\n\n#line\
    \ 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <utility>\n\nnamespace suisen {\n    struct BarrettReduction {\n        uint32_t\
    \ m;\n        uint64_t im;\n        BarrettReduction(uint32_t m) : m(m), im(uint64_t(-1)\
    \ / m + 1) {}\n\n        std::pair<uint64_t, uint32_t> quorem(uint64_t n) const\
    \ {\n            uint64_t q = uint64_t((__uint128_t(n) * im) >> 64);\n       \
    \     int64_t r = n - q * m;\n            if (r < 0) --q, r += m;\n          \
    \  return std::make_pair(q, r);\n        }\n        uint32_t quo(uint64_t n) const\
    \ {\n            return quorem(n).first;\n        }\n        uint32_t rem(uint64_t\
    \ n) const {\n            return quorem(n).second;\n        }\n\n        template\
    \ <typename Head, typename ...Tails>\n        uint32_t mul(Head &&head, Tails\
    \ &&...tails) const {\n            if constexpr (sizeof...(tails)) {\n       \
    \         return rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n \
    \           } else {\n                return head;\n            }\n        }\n\
    \    };\n} // namespace suisen\n\n\n\n#line 9 \"library/sequence/binomial_coefficient.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    std::vector<std::vector<T>>\
    \ binom_table(int n) {\n        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n\
    \ + 1));\n        for (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i]\
    \ = 1;\n            for (int j = 1; j < i; ++j) {\n                binom[i][j]\
    \ = binom[i - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n       \
    \ return binom;\n    }\n\n    struct BinomialCoefficient {\n        struct BinomialCoefficientPrimePower\
    \ {\n            static constexpr int MAX_MOD = 20000000;\n\n            uint32_t\
    \ p, q, m; // m = p ^ q\n            std::vector<uint32_t> f, inv_f;\n\n     \
    \       BarrettReduction br_p;\n            BarrettReduction br_m;\n\n       \
    \     BinomialCoefficientPrimePower() = default;\n            BinomialCoefficientPrimePower(uint32_t\
    \ p, uint32_t q, uint32_t m): p(p), q(q), m(m), f(m), br_p(p), br_m(m) {\n   \
    \             assert(m <= MAX_MOD);\n                f[0] = 1;\n             \
    \   for (uint32_t i = 1; i < m; ++i) {\n                    f[i] = br_p.rem(i)\
    \ ? br_m.mul(f[i - 1], i) : f[i - 1];\n                }\n                inv_f\
    \ = invs(f);\n            }\n\n            int32_t operator()(int64_t n_, int64_t\
    \ k_) const {\n                static uint32_t ns[64], ks[64], ls[64];\n     \
    \           if (k_ < 0 or k_ > n_) return 0;\n                \n             \
    \   uint64_t n = n_, k = k_, l = n - k;\n\n                uint32_t res = 1;\n\
    \                uint64_t e1 = 0, eq = 0;\n                uint32_t t = 0;\n \
    \               for (; n; ++t) {\n                    std::tie(n, ns[t]) = br_p.quorem(n);\n\
    \                    std::tie(k, ks[t]) = br_p.quorem(k);\n                  \
    \  std::tie(l, ls[t]) = br_p.quorem(l);\n                    e1 += n - k - l;\n\
    \                    if (t >= q - 1) {\n                        eq += n - k -\
    \ l;\n                    }\n                }\n                if (e1 >= q) {\n\
    \                    return 0;\n                }\n                while (e1--\
    \ > 0) {\n                    res *= p;\n                }\n                if\
    \ ((p != 2 or q < 3) and (eq & 1)) {\n                    res = m - res;\n   \
    \             }\n\n                uint32_t ni = 0, ki = 0, li = 0;\n        \
    \        for (uint32_t i = t; i --> 0;) {\n                    ni = br_m.mul(p,\
    \ ni) + ns[i];\n                    ki = br_m.mul(p, ki) + ks[i];\n          \
    \          li = br_m.mul(p, li) + ls[i];\n                    res = br_m.mul(res,\
    \ f[ni], inv_f[ki], inv_f[li]);\n                }\n                return res;\n\
    \            }\n        private:\n            std::vector<uint32_t> invs(const\
    \ std::vector<uint32_t>& vs) const {\n                const uint32_t n = vs.size();\n\
    \n                uint32_t p = 1;\n                for (const uint32_t& v : vs)\
    \ {\n                    p = br_m.mul(p, v);\n                }\n            \
    \    uint32_t ip = atcoder::inv_mod(p, m);\n\n                std::vector<uint32_t>\
    \ rp(n + 1);\n                rp[n] = 1;\n                for (uint32_t i = n;\
    \ i --> 0;) {\n                    rp[i] = br_m.mul(rp[i + 1], vs[i]);\n     \
    \           }\n                std::vector<uint32_t> res(n);\n               \
    \ for (uint32_t i = 0; i < n; ++i) {\n                    res[i] = br_m.mul(ip,\
    \ rp[i + 1]);\n                    ip = br_m.mul(ip, vs[i]);\n               \
    \ }\n                return res;\n            }\n        };\n\n        int l;\n\
    \        std::vector<BinomialCoefficientPrimePower> binoms;\n\n        BinomialCoefficient(int\
    \ m) {\n            for (int p = 2; p <= m; ++p) {\n                if (m % p\
    \ == 0) {\n                    int q = 0, pq = 1;\n                    do {\n\
    \                        m /= p;\n                        ++q, pq *= p;\n    \
    \                } while (m % p == 0);\n                    binoms.push_back(BinomialCoefficientPrimePower(p,\
    \ q, pq));\n                }\n            }\n            l = binoms.size();\n\
    \        }\n\n        int operator()(long long n, long long k) const {\n     \
    \       std::vector<long long> rs(l), ms(l);\n            for (int i = 0; i <\
    \ l; ++i) {\n                rs[i] = binoms[i](n, k);\n                ms[i] =\
    \ binoms[i].m;\n            }\n            return atcoder::crt(rs, ms).first;\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t, m;\n    std::cin >> t >> m;\n    \n    using suisen::BinomialCoefficient;\n\
    \n    BinomialCoefficient binom(m);\n    for (int qid = 0; qid < t; ++qid) {\n\
    \        long long n, k;\n        std::cin >> n >> k;\n        std::cout << binom(n,\
    \ k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    \n#include <iostream>\n\n#include \"library/sequence/binomial_coefficient.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t, m;\n    std::cin >> t >> m;\n    \n    using suisen::BinomialCoefficient;\n\
    \n    BinomialCoefficient binom(m);\n    for (int qid = 0; qid < t; ++qid) {\n\
    \        long long n, k;\n        std::cin >> n >> k;\n        std::cout << binom(n,\
    \ k) << '\\n';\n    }\n}"
  dependsOn:
  - library/sequence/binomial_coefficient.hpp
  - library/number/barrett_reduction.hpp
  isVerificationFile: true
  path: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
  requiredBy: []
  timestamp: '2023-01-08 00:05:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
layout: document
redirect_from:
- /verify/test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
- /verify/test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp.html
title: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
---
