---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: library/number/internal_eratosthenes.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
    title: test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
    title: test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/sieve_of_eratosthenes_constexpr.hpp\"\n\n\
    \n\n#include <cmath>\n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\n\
    \n\n\n#include <cstdint>\n#include <cassert>\n\nnamespace suisen::internal::sieve\
    \ {\n\nconstexpr std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\n\
    constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t\
    \ DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K]\
    \ = {\n    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2,\
    \ 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3,\
    \ 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2,\
    \ 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 180, 120,  60, 120,\
    \  60, 120, 180,  60 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {   0,   0,\
    \   0,   0,   0,   0,   0,  30 }, {  30,  30,  30,   0,  30,  30,  30,  30 },\n\
    \    {  60,  60,   0,  60,   0,  60,  60,  30 }, {  90,  30,  30,  60,  30,  30,\
    \  90,  30 },\n    {  90,  90,  30,  60,  30,  90,  90,  30 }, { 120,  60,  60,\
    \  60,  60,  60, 120,  30 },\n    { 150,  90,  30, 120,  30,  90, 150,  30 },\
    \ { 180, 120,  60, 120,  60, 120, 180,  30 },\n};\n\nconstexpr std::uint8_t MASK[K][K]\
    \ = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10,\
    \ 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08,\
    \ 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80,\
    \ 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01,\
    \ 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80,\
    \ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K]\
    \ = {\n    {  1,  7, 11, 13, 17, 19, 23, 29 }, {  7, 19, 17,  1, 29, 13, 11, 23\
    \ },\n    { 11, 17,  1, 23,  7, 29, 13, 19 }, { 13,  1, 23, 19, 11,  7, 29, 17\
    \ },\n    { 17, 29,  7, 11, 19, 23,  1, 13 }, { 19, 13, 29,  7, 23,  1, 17, 11\
    \ },\n    { 23, 11, 13, 29,  1, 17, 19,  7 }, { 29, 23, 19, 17, 13, 11,  7,  1\
    \ },\n};\n\nconstexpr std::uint8_t mask_to_index(const std::uint8_t bits) {\n\
    \    switch (bits) {\n        case 1 << 0: return 0;\n        case 1 << 1: return\
    \ 1;\n        case 1 << 2: return 2;\n        case 1 << 3: return 3;\n       \
    \ case 1 << 4: return 4;\n        case 1 << 5: return 5;\n        case 1 << 6:\
    \ return 6;\n        case 1 << 7: return 7;\n        default: assert(false);\n\
    \    }\n}\n} // namespace suisen::internal::sieve\n\n\n#line 7 \"library/number/sieve_of_eratosthenes_constexpr.hpp\"\
    \n\nnamespace suisen {\n\nconstexpr unsigned int CONSTEXPR_SIMPLE_SIEVE_MAX =\
    \ 1200000;\n\ntemplate <unsigned int N = CONSTEXPR_SIMPLE_SIEVE_MAX>\nclass SimpleSieveConstexpr\
    \ {\n    private:\n        static constexpr unsigned int siz = N / internal::sieve::PROD\
    \ + 1;\n        std::uint8_t flag[siz];\n    public:\n        static_assert(N\
    \ <= CONSTEXPR_SIMPLE_SIEVE_MAX, \"compile-time operation limit\");\n        constexpr\
    \ SimpleSieveConstexpr() : flag() {\n            using namespace internal::sieve;\n\
    \            flag[0] |= 1;\n            unsigned int k_max = (unsigned int) std::sqrt(N\
    \ + 2) / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n \
    \               for (std::uint8_t bits = ~flag[kp]; bits; bits &= bits - 1) {\n\
    \                    const std::uint8_t mp = mask_to_index(bits & -bits), m =\
    \ RM[mp];\n                    unsigned int kr = kp * (PROD * kp + 2 * m) + m\
    \ * m / PROD;\n                    for (std::uint8_t mq = mp; kr < siz; kr +=\
    \ kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                        flag[kr] |=\
    \ MASK[mp][mq];\n                    }\n                }\n            }\n   \
    \     }\n        constexpr bool is_prime(const unsigned int p) const {\n     \
    \       using namespace internal::sieve;\n            switch (p) {\n         \
    \       case 2: case 3: case 5: return true;\n                default:\n     \
    \               switch (p % PROD) {\n                        case RM[0]: return\
    \ ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]: return\
    \ ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]: return\
    \ ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]: return\
    \ ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]: return\
    \ ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]: return\
    \ ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]: return\
    \ ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]: return\
    \ ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return false;\n\
    \                    }\n            }\n        }\n};\n\nconstexpr unsigned int\
    \ CONSTEXPR_SIEVE_MAX = 1200000;\n\ntemplate <unsigned int N = CONSTEXPR_SIEVE_MAX>\n\
    class SieveConstexpr {\n    private:\n        unsigned int pf[N + internal::sieve::PROD];\n\
    \    public:\n        constexpr SieveConstexpr() : pf() {\n            using namespace\
    \ internal::sieve;\n            static_assert(N <= CONSTEXPR_SIEVE_MAX, \"compile-time\
    \ operation limit\");\n            pf[1] = 1;\n            unsigned int k_max\
    \ = ((unsigned int) std::sqrt(N + 1) - 1) / PROD;\n            for (unsigned int\
    \ kp = 0; kp <= k_max; ++kp) {\n                const int base_i = kp * 30;\n\
    \                for (int mp = 0; mp < K; ++mp) {\n                    const int\
    \ m = RM[mp], i = base_i + m;\n                    if (pf[i] == 0) {\n       \
    \                 unsigned int base_j = (kp * (PROD * kp + 2 * m) + m * m / PROD)\
    \ * PROD;\n                        for (std::uint8_t mq = mp; base_j < N; base_j\
    \ += kp * DRP[mq] + DFP[mp][mq], ++mq &= 7) {\n                            int\
    \ j = base_j + OFFSET[mp][mq];\n                            pf[j] = i;\n     \
    \                   }\n                    }\n                }\n            }\n\
    \        }\n        constexpr bool is_prime(const unsigned int p) const {\n  \
    \          using namespace internal::sieve;\n            switch (p) {\n      \
    \          case 2: case 3: case 5: return true;\n                default:\n  \
    \                  switch (p % PROD) {\n                        case RM[0]: case\
    \ RM[1]: case RM[2]: case RM[3]: case RM[4]: case RM[5]: case RM[6]: case RM[7]:\
    \ return pf[p] == 0;\n                        default: return false;\n       \
    \             }\n            }\n        }\n        constexpr int prime_factor(const\
    \ unsigned int p) const {\n            return p % 2 == 0 ? 2 : p % 3 == 0 ? 3\
    \ : p % 5 == 0 ? 5 : pf[p] ? pf[p] : p;\n        }\n};\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_SIEVE_OF_ERATOSTHENES_CONSTEXPR\n#define SUISEN_SIEVE_OF_ERATOSTHENES_CONSTEXPR\n\
    \n#include <cmath>\n\n#include \"library/number/internal_eratosthenes.hpp\"\n\n\
    namespace suisen {\n\nconstexpr unsigned int CONSTEXPR_SIMPLE_SIEVE_MAX = 1200000;\n\
    \ntemplate <unsigned int N = CONSTEXPR_SIMPLE_SIEVE_MAX>\nclass SimpleSieveConstexpr\
    \ {\n    private:\n        static constexpr unsigned int siz = N / internal::sieve::PROD\
    \ + 1;\n        std::uint8_t flag[siz];\n    public:\n        static_assert(N\
    \ <= CONSTEXPR_SIMPLE_SIEVE_MAX, \"compile-time operation limit\");\n        constexpr\
    \ SimpleSieveConstexpr() : flag() {\n            using namespace internal::sieve;\n\
    \            flag[0] |= 1;\n            unsigned int k_max = (unsigned int) std::sqrt(N\
    \ + 2) / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n \
    \               for (std::uint8_t bits = ~flag[kp]; bits; bits &= bits - 1) {\n\
    \                    const std::uint8_t mp = mask_to_index(bits & -bits), m =\
    \ RM[mp];\n                    unsigned int kr = kp * (PROD * kp + 2 * m) + m\
    \ * m / PROD;\n                    for (std::uint8_t mq = mp; kr < siz; kr +=\
    \ kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                        flag[kr] |=\
    \ MASK[mp][mq];\n                    }\n                }\n            }\n   \
    \     }\n        constexpr bool is_prime(const unsigned int p) const {\n     \
    \       using namespace internal::sieve;\n            switch (p) {\n         \
    \       case 2: case 3: case 5: return true;\n                default:\n     \
    \               switch (p % PROD) {\n                        case RM[0]: return\
    \ ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]: return\
    \ ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]: return\
    \ ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]: return\
    \ ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]: return\
    \ ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]: return\
    \ ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]: return\
    \ ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]: return\
    \ ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return false;\n\
    \                    }\n            }\n        }\n};\n\nconstexpr unsigned int\
    \ CONSTEXPR_SIEVE_MAX = 1200000;\n\ntemplate <unsigned int N = CONSTEXPR_SIEVE_MAX>\n\
    class SieveConstexpr {\n    private:\n        unsigned int pf[N + internal::sieve::PROD];\n\
    \    public:\n        constexpr SieveConstexpr() : pf() {\n            using namespace\
    \ internal::sieve;\n            static_assert(N <= CONSTEXPR_SIEVE_MAX, \"compile-time\
    \ operation limit\");\n            pf[1] = 1;\n            unsigned int k_max\
    \ = ((unsigned int) std::sqrt(N + 1) - 1) / PROD;\n            for (unsigned int\
    \ kp = 0; kp <= k_max; ++kp) {\n                const int base_i = kp * 30;\n\
    \                for (int mp = 0; mp < K; ++mp) {\n                    const int\
    \ m = RM[mp], i = base_i + m;\n                    if (pf[i] == 0) {\n       \
    \                 unsigned int base_j = (kp * (PROD * kp + 2 * m) + m * m / PROD)\
    \ * PROD;\n                        for (std::uint8_t mq = mp; base_j < N; base_j\
    \ += kp * DRP[mq] + DFP[mp][mq], ++mq &= 7) {\n                            int\
    \ j = base_j + OFFSET[mp][mq];\n                            pf[j] = i;\n     \
    \                   }\n                    }\n                }\n            }\n\
    \        }\n        constexpr bool is_prime(const unsigned int p) const {\n  \
    \          using namespace internal::sieve;\n            switch (p) {\n      \
    \          case 2: case 3: case 5: return true;\n                default:\n  \
    \                  switch (p % PROD) {\n                        case RM[0]: case\
    \ RM[1]: case RM[2]: case RM[3]: case RM[4]: case RM[5]: case RM[6]: case RM[7]:\
    \ return pf[p] == 0;\n                        default: return false;\n       \
    \             }\n            }\n        }\n        constexpr int prime_factor(const\
    \ unsigned int p) const {\n            return p % 2 == 0 ? 2 : p % 3 == 0 ? 3\
    \ : p % 5 == 0 ? 5 : pf[p] ? pf[p] : p;\n        }\n};\n} // namespace suisen\n\
    \n#endif // SUISEN_SIEVE_OF_ERATOSTHENES_CONSTEXPR\n"
  dependsOn:
  - library/number/internal_eratosthenes.hpp
  isVerificationFile: false
  path: library/number/sieve_of_eratosthenes_constexpr.hpp
  requiredBy: []
  timestamp: '2021-07-22 12:50:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
  - test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
documentation_of: library/number/sieve_of_eratosthenes_constexpr.hpp
layout: document
redirect_from:
- /library/library/number/sieve_of_eratosthenes_constexpr.hpp
- /library/library/number/sieve_of_eratosthenes_constexpr.hpp.html
title: library/number/sieve_of_eratosthenes_constexpr.hpp
---
