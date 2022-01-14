---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/mobius_function.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\nnamespace suisen {\n\ntemplate <unsigned\
    \ int N>\nclass MobiusFunction {\n    public:\n        MobiusFunction() {\n  \
    \          mpf.fill(0);\n            dat.fill(1);\n            for (long long\
    \ p = 2; p <= N; ++p) {\n                if (mpf[p]) continue;\n             \
    \   mpf[p] = p;\n                dat[p] = -1;\n                for (long long\
    \ q = p * 2; q <= N; q += p) {\n                    if (not mpf[q]) mpf[q] = p;\n\
    \                    dat[q] = q % (p * p) ? -dat[q] : 0;\n                }\n\
    \            }\n        }\n        // Note: `n` must be in [1, N].\n        int\
    \ operator()(unsigned int n) const {\n            assert(0 < n and n <= N);\n\
    \            return dat[n];\n        }\n        // Note: `n` must be in [1, N].\n\
    \        int operator[](unsigned int n) const {\n            return (*this)(n);\n\
    \        }\n        // Note: `n` must be in [1, N].\n        int mobius(unsigned\
    \ int n) const {\n            return (*this)(n);\n        }\n        // Note:\
    \ `n` must be in [2, N].\n        int min_prime_factor(unsigned int n) const {\n\
    \            assert(2 <= n and n <= N);\n            return mpf[n];\n        }\n\
    \        /**\n         * Returns a vector of `{ prime, index }`.\n         * It\
    \ is guaranteed that the returned vector is sorted in ascending order.\n     \
    \    */\n        std::vector<std::pair<int, int>> factorize(unsigned int n) const\
    \ {\n            assert(0 < n and n <= N);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = mpf[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n        bool is_prime(unsigned int n) const {\n            assert(n\
    \ <= N);\n            return 2 <= n and mpf[n] == n;\n        }\n    private:\n\
    \        std::array<int, N + 1> mpf;\n        std::array<int, N + 1> dat;\n};\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MOBIUS_FUNCTION\n#define SUISEN_MOBIUS_FUNCTION\n\n#include\
    \ <array>\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n\ntemplate\
    \ <unsigned int N>\nclass MobiusFunction {\n    public:\n        MobiusFunction()\
    \ {\n            mpf.fill(0);\n            dat.fill(1);\n            for (long\
    \ long p = 2; p <= N; ++p) {\n                if (mpf[p]) continue;\n        \
    \        mpf[p] = p;\n                dat[p] = -1;\n                for (long\
    \ long q = p * 2; q <= N; q += p) {\n                    if (not mpf[q]) mpf[q]\
    \ = p;\n                    dat[q] = q % (p * p) ? -dat[q] : 0;\n            \
    \    }\n            }\n        }\n        // Note: `n` must be in [1, N].\n  \
    \      int operator()(unsigned int n) const {\n            assert(0 < n and n\
    \ <= N);\n            return dat[n];\n        }\n        // Note: `n` must be\
    \ in [1, N].\n        int operator[](unsigned int n) const {\n            return\
    \ (*this)(n);\n        }\n        // Note: `n` must be in [1, N].\n        int\
    \ mobius(unsigned int n) const {\n            return (*this)(n);\n        }\n\
    \        // Note: `n` must be in [2, N].\n        int min_prime_factor(unsigned\
    \ int n) const {\n            assert(2 <= n and n <= N);\n            return mpf[n];\n\
    \        }\n        /**\n         * Returns a vector of `{ prime, index }`.\n\
    \         * It is guaranteed that the returned vector is sorted in ascending order.\n\
    \         */\n        std::vector<std::pair<int, int>> factorize(unsigned int\
    \ n) const {\n            assert(0 < n and n <= N);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = mpf[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n        bool is_prime(unsigned int n) const {\n            assert(n\
    \ <= N);\n            return 2 <= n and mpf[n] == n;\n        }\n    private:\n\
    \        std::array<int, N + 1> mpf;\n        std::array<int, N + 1> dat;\n};\n\
    } // namespace suisen\n\n\n#endif // SUISEN_MOBIUS_FUNCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/mobius_function.hpp
  requiredBy: []
  timestamp: '2022-01-15 00:28:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/mobius_function.hpp
layout: document
redirect_from:
- /library/library/number/mobius_function.hpp
- /library/library/number/mobius_function.hpp.html
title: library/number/mobius_function.hpp
---
