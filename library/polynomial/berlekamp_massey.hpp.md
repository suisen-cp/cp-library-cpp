---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
    title: test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Find linear recurrence in O(|s|^2) time
    links: []
  bundledCode: "#line 1 \"library/polynomial/berlekamp_massey.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * @brief Find\
    \ linear recurrence in O(|s|^2) time\n     * @tparam F Arbitrary field (operator\
    \ +, -, *, /, +=, -=, *=, /= must be defined)\n     * @param s Prefix of a linearly\
    \ reccurent sequence\n     * @return The vector of length L+1 c s.t. c_0=1 and\
    \ s_i=Sum[j=1,L]c_i*s_{i-j} for all i>=L, where L is the minimum integer s.t.\
    \ there exists such c of length L+1.\n     */\n    template <typename F>\n   \
    \ std::vector<F> find_linear_recuurence(const std::vector<F>& s) {\n        std::vector<F>\
    \ B{ 1 }, C{ 1 };\n        B.reserve(s.size()), C.reserve(s.size());\n       \
    \ F b = 1;\n        std::size_t L = 0;\n        for (std::size_t N = 0, x = 1;\
    \ N < s.size(); ++N) {\n            F d = s[N];\n            for (std::size_t\
    \ i = 1; i <= L; ++i) d += C[i] * s[N - i];\n            if (d == 0) {\n     \
    \           ++x;\n            } else {\n                F c = d / b;\n       \
    \         if (C.size() < B.size() + x) C.resize(B.size() + x);\n             \
    \   if (2 * L > N) {\n                    for (std::size_t i = 0; i < B.size();\
    \ ++i) C[x + i] -= c * B[i];\n                    ++x;\n                } else\
    \ {\n                    std::vector<F> T = C;\n                    for (std::size_t\
    \ i = 0; i < B.size(); ++i) C[x + i] -= c * B[i];\n                    L = N +\
    \ 1 - L, B = std::move(T), b = d, x = 1;\n                }\n            }\n \
    \       }\n        C.resize(L + 1);\n        for (std::size_t N = 1; N <= L; ++N)\
    \ C[N] = -C[N];\n        return C;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BERLEKAMP_MASSEY\n#define SUISEN_BERLEKAMP_MASSEY\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * @brief Find\
    \ linear recurrence in O(|s|^2) time\n     * @tparam F Arbitrary field (operator\
    \ +, -, *, /, +=, -=, *=, /= must be defined)\n     * @param s Prefix of a linearly\
    \ reccurent sequence\n     * @return The vector of length L+1 c s.t. c_0=1 and\
    \ s_i=Sum[j=1,L]c_i*s_{i-j} for all i>=L, where L is the minimum integer s.t.\
    \ there exists such c of length L+1.\n     */\n    template <typename F>\n   \
    \ std::vector<F> find_linear_recuurence(const std::vector<F>& s) {\n        std::vector<F>\
    \ B{ 1 }, C{ 1 };\n        B.reserve(s.size()), C.reserve(s.size());\n       \
    \ F b = 1;\n        std::size_t L = 0;\n        for (std::size_t N = 0, x = 1;\
    \ N < s.size(); ++N) {\n            F d = s[N];\n            for (std::size_t\
    \ i = 1; i <= L; ++i) d += C[i] * s[N - i];\n            if (d == 0) {\n     \
    \           ++x;\n            } else {\n                F c = d / b;\n       \
    \         if (C.size() < B.size() + x) C.resize(B.size() + x);\n             \
    \   if (2 * L > N) {\n                    for (std::size_t i = 0; i < B.size();\
    \ ++i) C[x + i] -= c * B[i];\n                    ++x;\n                } else\
    \ {\n                    std::vector<F> T = C;\n                    for (std::size_t\
    \ i = 0; i < B.size(); ++i) C[x + i] -= c * B[i];\n                    L = N +\
    \ 1 - L, B = std::move(T), b = d, x = 1;\n                }\n            }\n \
    \       }\n        C.resize(L + 1);\n        for (std::size_t N = 1; N <= L; ++N)\
    \ C[N] = -C[N];\n        return C;\n    }\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_BERLEKAMP_MASSEY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/berlekamp_massey.hpp
  requiredBy: []
  timestamp: '2024-01-30 20:59:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/polynomial/berlekamp_massey/find_linear_recurrence.test.cpp
documentation_of: library/polynomial/berlekamp_massey.hpp
layout: document
title: "Berlekamp Massey (\u7DDA\u5F62\u56DE\u5E30\u6570\u5217\u306E\u4FC2\u6570\u8A08\
  \u7B97)"
---
## Berlekamp Massey (線形回帰数列の係数の計算)

体 $F$ 上の数列 $s=(s_0,s_1,\ldots,s_{n-1})$ に対して、

$$s_i=\sum_{j=1}^L c_j\cdot s_{i-j}\quad (\forall i\geq L)$$

を満たす数列 $c=(c_1,\ldots,c_L)$ のうち長さ $L$ が最小のものを $\Theta(n ^ 2)$ 時間で計算する。

## Reference

[1] J. Massey, "Shift-register synthesis and BCH decoding," in IEEE Transactions on Information Theory, vol. 15, no. 1, pp. 122-127, January 1969, doi: 10.1109/TIT.1969.1054260.
