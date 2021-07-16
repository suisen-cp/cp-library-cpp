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
  bundledCode: "#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <unsigned int M>\nclass sieve_of_eratosthenes\
    \ {\n    public:\n        sieve_of_eratosthenes() {\n            pf.resize(M +\
    \ 1);\n            pf[0] = 0;\n            for (unsigned int i = 1; i <= M; ++i)\
    \ {\n                if (i & 1) {\n                    if (i % 3) pf[i] = i;\n\
    \                    else pf[i] = 3;\n                } else pf[i] = 2;\n    \
    \        }\n            for (unsigned int i = 5; i * i <= M; i += 6) {\n     \
    \           unsigned int p1 = i, p2 = i + 2;\n                if (pf[p1] == p1)\
    \ {\n                    for (unsigned int v = p1 * p1; v <= M; v += 2 * p1) {\n\
    \                        pf[v] = p1;\n                    }\n                }\n\
    \                if (pf[p2] == p2) {\n                    for (unsigned int v\
    \ = p2 * p2; v <= M; v += 2 * p2) {\n                        pf[v] = p2;\n   \
    \                 }\n                }\n            }\n        }\n        bool\
    \ is_prime(unsigned int v) {\n            return pf[v] == v;\n        }\n    \
    \    unsigned int prime_factor(unsigned int v) {\n            return pf[v];\n\
    \        }\n        std::vector<std::pair<unsigned int, unsigned int>> factorize(unsigned\
    \ int v) {\n            std::vector<std::pair<unsigned int, unsigned int>> pfs;\n\
    \            while (v != 1) {\n                unsigned int p = pf[v], c = 0;\n\
    \                do {\n                    v /= p;\n                    ++c;\n\
    \                } while (v % p == 0);\n                pfs.push_back({p, c});\n\
    \            }\n            return pfs;\n        }\n    private:\n        std::vector<int>\
    \ pf;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ERATOSTHENES\n#define SUISEN_ERATOSTHENES\n\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <unsigned int M>\nclass sieve_of_eratosthenes {\n\
    \    public:\n        sieve_of_eratosthenes() {\n            pf.resize(M + 1);\n\
    \            pf[0] = 0;\n            for (unsigned int i = 1; i <= M; ++i) {\n\
    \                if (i & 1) {\n                    if (i % 3) pf[i] = i;\n   \
    \                 else pf[i] = 3;\n                } else pf[i] = 2;\n       \
    \     }\n            for (unsigned int i = 5; i * i <= M; i += 6) {\n        \
    \        unsigned int p1 = i, p2 = i + 2;\n                if (pf[p1] == p1) {\n\
    \                    for (unsigned int v = p1 * p1; v <= M; v += 2 * p1) {\n \
    \                       pf[v] = p1;\n                    }\n                }\n\
    \                if (pf[p2] == p2) {\n                    for (unsigned int v\
    \ = p2 * p2; v <= M; v += 2 * p2) {\n                        pf[v] = p2;\n   \
    \                 }\n                }\n            }\n        }\n        bool\
    \ is_prime(unsigned int v) {\n            return pf[v] == v;\n        }\n    \
    \    unsigned int prime_factor(unsigned int v) {\n            return pf[v];\n\
    \        }\n        std::vector<std::pair<unsigned int, unsigned int>> factorize(unsigned\
    \ int v) {\n            std::vector<std::pair<unsigned int, unsigned int>> pfs;\n\
    \            while (v != 1) {\n                unsigned int p = pf[v], c = 0;\n\
    \                do {\n                    v /= p;\n                    ++c;\n\
    \                } while (v % p == 0);\n                pfs.push_back({p, c});\n\
    \            }\n            return pfs;\n        }\n    private:\n        std::vector<int>\
    \ pf;\n};\n} // namespace suisen\n\n#endif // SUISEN_ERATOSTHENES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/sieve_of_eratosthenes.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/sieve_of_eratosthenes.hpp
layout: document
redirect_from:
- /library/library/number/sieve_of_eratosthenes.hpp
- /library/library/number/sieve_of_eratosthenes.hpp.html
title: library/number/sieve_of_eratosthenes.hpp
---
