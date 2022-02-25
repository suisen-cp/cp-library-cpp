---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/algorithm/mo.hpp
    title: Mo
  - icon: ':question:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':question:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: Sieve Of Eratosthenes
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc238/tasks/abc238_g
    links:
    - https://atcoder.jp/contests/abc238/tasks/abc238_g
  bundledCode: "#line 1 \"test/src/algorithm/mo/abc238_g.test.cpp\"\n#define PROBLEM\
    \ \"https://atcoder.jp/contests/abc238/tasks/abc238_g\"\n\n#include <iostream>\n\
    #include <atcoder/modint>\n\nusing mint = atcoder::static_modint<3>;\n\n#line\
    \ 1 \"library/number/sieve_of_eratosthenes.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cmath>\n#include <vector>\n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\
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
    \       }\n        }\n        std::vector<int> prime_list(unsigned int max_val\
    \ = N) const {\n            using namespace internal::sieve;\n            std::vector<int>\
    \ res { 2, 3, 5 };\n            res.reserve(max_val / 25);\n            for (unsigned\
    \ int i = 0, offset = 0; i < siz and offset < max_val; ++i, offset += PROD) {\n\
    \                for (uint8_t f = ~flag[i]; f;) {\n                    uint8_t\
    \ g = f & -f;\n                    res.push_back(offset + RM[mask_to_index(g)]);\n\
    \                    f ^= g;\n                }\n            }\n            while\
    \ (res.size() and (unsigned int) res.back() > max_val) res.pop_back();\n     \
    \       return res;\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]:\
    \ return ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]:\
    \ return ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]:\
    \ return ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]:\
    \ return ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]:\
    \ return ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]:\
    \ return ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]:\
    \ return ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return\
    \ false;\n                    }\n            }\n        }\n};\ntemplate <unsigned\
    \ int N>\nstd::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];\n\ntemplate\
    \ <unsigned int N>\nclass Sieve {\n    private:\n        static constexpr unsigned\
    \ int base_max = (N + 1) * internal::sieve::K / internal::sieve::PROD;\n     \
    \   static unsigned int pf[base_max + internal::sieve::K];\n\n    public:\n  \
    \      Sieve() {\n            using namespace internal::sieve;\n            pf[0]\
    \ = 1;\n            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1)\
    \ / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n      \
    \          const int base_i = kp * K, base_act_i = kp * PROD;\n              \
    \  for (int mp = 0; mp < K; ++mp) {\n                    const int m = RM[mp],\
    \ i = base_i + mp;\n                    if (pf[i] == 0) {\n                  \
    \      unsigned int act_i = base_act_i + m;\n                        unsigned\
    \ int base_k = (kp * (PROD * kp + 2 * m) + m * m / PROD) * K;\n              \
    \          for (std::uint8_t mq = mp; base_k <= base_max; base_k += kp * DRP[mq]\
    \ + DFP[mp][mq], ++mq &= 7) {\n                            pf[base_k + OFFSET[mp][mq]]\
    \ = act_i;\n                        }\n                    }\n               \
    \ }\n            }\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return pf[p / PROD * K + 0] == 0;\n                        case RM[1]: return\
    \ pf[p / PROD * K + 1] == 0;\n                        case RM[2]: return pf[p\
    \ / PROD * K + 2] == 0;\n                        case RM[3]: return pf[p / PROD\
    \ * K + 3] == 0;\n                        case RM[4]: return pf[p / PROD * K +\
    \ 4] == 0;\n                        case RM[5]: return pf[p / PROD * K + 5] ==\
    \ 0;\n                        case RM[6]: return pf[p / PROD * K + 6] == 0;\n\
    \                        case RM[7]: return pf[p / PROD * K + 7] == 0;\n     \
    \                   default: return false;\n                    }\n          \
    \  }\n        }\n        int prime_factor(const unsigned int p) const {\n    \
    \        using namespace internal::sieve;\n            switch (p % PROD) {\n \
    \               case  0: case  2: case  4: case  6: case  8:\n               \
    \ case 10: case 12: case 14: case 16: case 18:\n                case 20: case\
    \ 22: case 24: case 26: case 28: return 2;\n                case  3: case  9:\
    \ case 15: case 21: case 27: return 3;\n                case  5: case 25: return\
    \ 5;\n                case RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD *\
    \ K + 0] : p;\n                case RM[1]: return pf[p / PROD * K + 1] ? pf[p\
    \ / PROD * K + 1] : p;\n                case RM[2]: return pf[p / PROD * K + 2]\
    \ ? pf[p / PROD * K + 2] : p;\n                case RM[3]: return pf[p / PROD\
    \ * K + 3] ? pf[p / PROD * K + 3] : p;\n                case RM[4]: return pf[p\
    \ / PROD * K + 4] ? pf[p / PROD * K + 4] : p;\n                case RM[5]: return\
    \ pf[p / PROD * K + 5] ? pf[p / PROD * K + 5] : p;\n                case RM[6]:\
    \ return pf[p / PROD * K + 6] ? pf[p / PROD * K + 6] : p;\n                case\
    \ RM[7]: return pf[p / PROD * K + 7] ? pf[p / PROD * K + 7] : p;\n           \
    \     default: assert(false);\n            }\n        }\n        /**\n       \
    \  * Returns a vector of `{ prime, index }`.\n         */\n        std::vector<std::pair<int,\
    \ int>> factorize(unsigned int n) const {\n            assert(0 < n and n <= N);\n\
    \            std::vector<std::pair<int, int>> prime_powers;\n            while\
    \ (n > 1) {\n                int p = prime_factor(n), c = 0;\n               \
    \ do { n /= p, ++c; } while (n % p == 0);\n                prime_powers.emplace_back(p,\
    \ c);\n            }\n            return prime_powers;\n        }\n        /**\n\
    \         * Returns the divisors of `n`.\n         * It is NOT guaranteed that\
    \ the returned vector is sorted.\n         */\n        std::vector<int> divisors(unsigned\
    \ int n) const {\n            assert(0 < n and n <= N);\n            std::vector<int>\
    \ divs { 1 };\n            for (auto [prime, index] : factorize(n)) {\n      \
    \          int sz = divs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    int d = divs[i];\n                    for (int j = 0;\
    \ j < index; ++j) {\n                        divs.push_back(d *= prime);\n   \
    \                 }\n                }\n            }\n            return divs;\n\
    \        }\n};\ntemplate <unsigned int N>\nunsigned int Sieve<N>::pf[Sieve<N>::base_max\
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 1 \"library/algorithm/mo.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 6 \"library/algorithm/mo.hpp\"\n#include <numeric>\n\
    #line 8 \"library/algorithm/mo.hpp\"\n\nnamespace suisen {\n    struct Mo {\n\
    \        Mo() {}\n        Mo(const int n, const std::vector<std::pair<int, int>>\
    \ &queries) : n(n), q(queries.size()), b(n / (::sqrt(q) + 1)), qs(queries), ord(q)\
    \ {\n            std::iota(ord.begin(), ord.end(), 0);\n            std::sort(\n\
    \                ord.begin(), ord.end(),\n                [&, this](int i, int\
    \ j) {\n                    const auto &[li, ri] = qs[i];\n                  \
    \  const auto &[lj, rj] = qs[j];\n                    const int bi = li / b, bj\
    \ = lj / b;\n                    if (bi != bj) return bi < bj;\n             \
    \       if (ri != rj) return bi & 1 ? ri > rj : ri < rj;\n                   \
    \ return li < lj;\n                }\n            );\n        }\n\n        //\
    \ getter methods used in updating functions: AddL, DelL, etc.\n        auto get_left()\
    \  const { return l; }\n        auto get_right() const { return r; }\n       \
    \ auto get_range() const { return std::make_pair(l, r); }\n\n        /**\n   \
    \      * [Parameters]\n         * Eval : () -> T : return the current answer\n\
    \         * AddL : int -> any (discarded) : add    `l` to   the current range\
    \ [l + 1, r)\n         * DelL : int -> any (discarded) : delete `l` from the current\
    \ range [l, r)\n         * AddR : int -> any (discarded) : add    `r` to   the\
    \ current range [l, r)\n         * DelR : int -> any (discarded) : delete `r`\
    \ from the current range [l, r + 1)\n         * \n         * [Note]\n        \
    \ * starting from the range [0, 0).\n         */\n        template <typename Eval,\
    \ typename AddL, typename DelL, typename AddR, typename DelR>\n        auto solve(Eval\
    \ eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r) {\n            l = 0,\
    \ r = 0;\n            std::vector<decltype(eval())> res(q);\n            for (int\
    \ qi : ord) {\n                const auto &[nl, nr] = qs[qi];\n              \
    \  while (r < nr) add_r(r), ++r;\n                while (l > nl) --l, add_l(l);\n\
    \                while (r > nr) --r, del_r(r);\n                while (l < nl)\
    \ del_l(l), ++l;\n                res[qi] = eval();\n            }\n         \
    \   return res;\n        }\n    \n        /**\n         * [Parameters]\n     \
    \    * Eval : () -> T : return the current answer\n         * Add : int -> any\
    \ (discarded) : add    `i` to   the current range [i + 1, r) or [l, i)\n     \
    \    * Del : int -> any (discarded) : delete `i` from the current range [i, r)\
    \ or [l, i + 1)\n         * \n         * [Note]\n         * starting from the\
    \ range [0, 0).\n         */\n        template <typename Eval, typename Add, typename\
    \ Del>\n        auto solve(Eval eval, Add add, Del del) {\n            return\
    \ solve(eval, add, del, add, del);\n        }\n\n    private:\n        int n,\
    \ q, b;\n        std::vector<std::pair<int, int>> qs;\n        std::vector<int>\
    \ ord;\n        int l = 0, r = 0;\n    };\n} // namespace suisen\n\n\n#line 10\
    \ \"test/src/algorithm/mo/abc238_g.test.cpp\"\n\nusing suisen::Sieve;\nusing suisen::Mo;\n\
    \nconstexpr int M = 1000000;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    Sieve<M>\
    \ sieve;\n    std::vector<std::vector<std::pair<int, mint>>> factorized(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n\n\
    \        for (auto &&[p, c] : sieve.factorize(v)) {\n            factorized[i].emplace_back(p,\
    \ c);\n        }\n    }\n\n    std::vector<std::pair<int, int>> queries(q);\n\
    \    for (auto &[l, r] : queries) {\n        std::cin >> l >> r;\n        --l;\n\
    \    }\n\n    std::vector<mint> index_sum(M + 1, 0);\n    int invalid = 0;\n\n\
    \    auto answers = Mo(n, queries).solve(\n        // Eval\n        [&]{\n   \
    \         return invalid == 0;\n        },\n        // Add\n        [&](int i)\
    \ {\n            for (const auto &[p, c] : factorized[i]) {\n                invalid\
    \ -= index_sum[p] != 0;\n                index_sum[p] += c;\n                invalid\
    \ += index_sum[p] != 0;\n            }\n        },\n        // Del\n        [&](int\
    \ i) {\n            for (const auto &[p, c] : factorized[i]) {\n             \
    \   invalid -= index_sum[p] != 0;\n                index_sum[p] -= c;\n      \
    \          invalid += index_sum[p] != 0;\n            }\n        }\n    );\n\n\
    \    for (bool answer : answers) {\n        if (answer) {\n            std::cout\
    \ << \"Yes\" << '\\n';\n        } else {\n            std::cout << \"No\" << '\\\
    n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc238/tasks/abc238_g\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::static_modint<3>;\n\
    \n#include \"library/number/sieve_of_eratosthenes.hpp\"\n#include \"library/algorithm/mo.hpp\"\
    \n\nusing suisen::Sieve;\nusing suisen::Mo;\n\nconstexpr int M = 1000000;\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    Sieve<M> sieve;\n    std::vector<std::vector<std::pair<int,\
    \ mint>>> factorized(n);\n    for (int i = 0; i < n; ++i) {\n        int v;\n\
    \        std::cin >> v;\n\n        for (auto &&[p, c] : sieve.factorize(v)) {\n\
    \            factorized[i].emplace_back(p, c);\n        }\n    }\n\n    std::vector<std::pair<int,\
    \ int>> queries(q);\n    for (auto &[l, r] : queries) {\n        std::cin >> l\
    \ >> r;\n        --l;\n    }\n\n    std::vector<mint> index_sum(M + 1, 0);\n \
    \   int invalid = 0;\n\n    auto answers = Mo(n, queries).solve(\n        // Eval\n\
    \        [&]{\n            return invalid == 0;\n        },\n        // Add\n\
    \        [&](int i) {\n            for (const auto &[p, c] : factorized[i]) {\n\
    \                invalid -= index_sum[p] != 0;\n                index_sum[p] +=\
    \ c;\n                invalid += index_sum[p] != 0;\n            }\n        },\n\
    \        // Del\n        [&](int i) {\n            for (const auto &[p, c] : factorized[i])\
    \ {\n                invalid -= index_sum[p] != 0;\n                index_sum[p]\
    \ -= c;\n                invalid += index_sum[p] != 0;\n            }\n      \
    \  }\n    );\n\n    for (bool answer : answers) {\n        if (answer) {\n   \
    \         std::cout << \"Yes\" << '\\n';\n        } else {\n            std::cout\
    \ << \"No\" << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  - library/algorithm/mo.hpp
  isVerificationFile: true
  path: test/src/algorithm/mo/abc238_g.test.cpp
  requiredBy: []
  timestamp: '2022-02-25 23:21:09+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/algorithm/mo/abc238_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/mo/abc238_g.test.cpp
- /verify/test/src/algorithm/mo/abc238_g.test.cpp.html
title: test/src/algorithm/mo/abc238_g.test.cpp
---
