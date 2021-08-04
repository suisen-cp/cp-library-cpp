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
    \          min_prime_factor.fill(0);\n            mobius.fill(1);\n          \
    \  for (int p = 2; p <= N; ++p) {\n                if (min_prime_factor[p]) continue;\n\
    \                min_prime_factor[p] = p;\n                mobius[p] = -1;\n \
    \               for (int q = p * 2; q <= N; q += p) {\n                    if\
    \ (not min_prime_factor[q]) min_prime_factor[q] = p;\n                    mobius[q]\
    \ = q % (p * p) ? -mobius[q] : 0;\n                }\n            }\n        }\n\
    \        // Note: `n` must be in [1, N].\n        int operator[](int n) const\
    \ {\n            assert(0 < n and n <= N);\n            return mobius[n];\n  \
    \      }\n        // Note: `n` must be in [1, N].\n        int mobius(int n) const\
    \ {\n            return (*this)[n];\n        }\n        // Note: `n` must be in\
    \ [2, N].\n        int min_prime_factor(int n) const {\n            assert(2 <=\
    \ n and n <= N);\n            return min_prime_factor[n];\n        }\n       \
    \ /**\n         * Returns a vector of `{ prime, index }`.\n         * It is guaranteed\
    \ that the returned vector is sorted in ascending order.\n         */\n      \
    \  std::vector<std::pair<int, int>> factorize(int n) const {\n            assert(0\
    \ < n and n <= N);\n            std::vector<std::pair<int, int>> prime_powers;\n\
    \            while (n > 1) {\n                int p = min_prime_factor[n], c =\
    \ 0;\n                do { n /= p, ++c; } while (n % p == 0);\n              \
    \  prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n        bool is_prime(int n) const {\n            assert(n <= N);\n\
    \            return 2 <= n and min_prime_factor[n] == n;\n        }\n    private:\n\
    \        std::array<int, N + 1> min_prime_factor;\n        std::array<int, N +\
    \ 1> mobius;\n};\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MOBIUS_FUNCTION\n#define SUISEN_MOBIUS_FUNCTION\n\n#include\
    \ <array>\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n\ntemplate\
    \ <unsigned int N>\nclass MobiusFunction {\n    public:\n        MobiusFunction()\
    \ {\n            min_prime_factor.fill(0);\n            mobius.fill(1);\n    \
    \        for (int p = 2; p <= N; ++p) {\n                if (min_prime_factor[p])\
    \ continue;\n                min_prime_factor[p] = p;\n                mobius[p]\
    \ = -1;\n                for (int q = p * 2; q <= N; q += p) {\n             \
    \       if (not min_prime_factor[q]) min_prime_factor[q] = p;\n              \
    \      mobius[q] = q % (p * p) ? -mobius[q] : 0;\n                }\n        \
    \    }\n        }\n        // Note: `n` must be in [1, N].\n        int operator[](int\
    \ n) const {\n            assert(0 < n and n <= N);\n            return mobius[n];\n\
    \        }\n        // Note: `n` must be in [1, N].\n        int mobius(int n)\
    \ const {\n            return (*this)[n];\n        }\n        // Note: `n` must\
    \ be in [2, N].\n        int min_prime_factor(int n) const {\n            assert(2\
    \ <= n and n <= N);\n            return min_prime_factor[n];\n        }\n    \
    \    /**\n         * Returns a vector of `{ prime, index }`.\n         * It is\
    \ guaranteed that the returned vector is sorted in ascending order.\n        \
    \ */\n        std::vector<std::pair<int, int>> factorize(int n) const {\n    \
    \        assert(0 < n and n <= N);\n            std::vector<std::pair<int, int>>\
    \ prime_powers;\n            while (n > 1) {\n                int p = min_prime_factor[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n        bool is_prime(int n) const {\n            assert(n <= N);\n\
    \            return 2 <= n and min_prime_factor[n] == n;\n        }\n    private:\n\
    \        std::array<int, N + 1> min_prime_factor;\n        std::array<int, N +\
    \ 1> mobius;\n};\n} // namespace suisen\n\n\n#endif // SUISEN_MOBIUS_FUNCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/mobius_function.hpp
  requiredBy: []
  timestamp: '2021-08-04 13:32:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/mobius_function.hpp
layout: document
redirect_from:
- /library/library/number/mobius_function.hpp
- /library/library/number/mobius_function.hpp.html
title: library/number/mobius_function.hpp
---
