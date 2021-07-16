---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':warning:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/BostanMori.hpp\"\n\n\n\n#include <library/math/fps.hpp>\n\
    \nnamespace suisen {\ntemplate <typename mint>\nmint bostan_mori(const FPS<mint>\
    \ &P, const FPS<mint> &Q, const long long n) {\n    if (n == 0) return P[0];\n\
    \    FPS mQ(Q);\n    for (int i = 0; i <= Q.deg(); i += 2) mQ[i] = -mQ[i];\n \
    \   P *= mQ, Q *= mQ;\n    FPS nP((P.deg() + 1) / 2), nQ((Q.deg() + 1) / 2);\n\
    \    for (int i = 0    ; i <= Q.deg(); i += 2) nQ[i >> 1] = Q[i];\n    for (int\
    \ i = n & 1; i <= P.deg(); i += 2) nP[i >> 1] = P[i];\n    return bostan_mori(nP,\
    \ nQ, n / 2);\n}\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BOSTAN_MORI\n#define SUISEN_BOSTAN_MORI\n\n#include <library/math/fps.hpp>\n\
    \nnamespace suisen {\ntemplate <typename mint>\nmint bostan_mori(const FPS<mint>\
    \ &P, const FPS<mint> &Q, const long long n) {\n    if (n == 0) return P[0];\n\
    \    FPS mQ(Q);\n    for (int i = 0; i <= Q.deg(); i += 2) mQ[i] = -mQ[i];\n \
    \   P *= mQ, Q *= mQ;\n    FPS nP((P.deg() + 1) / 2), nQ((Q.deg() + 1) / 2);\n\
    \    for (int i = 0    ; i <= Q.deg(); i += 2) nQ[i >> 1] = Q[i];\n    for (int\
    \ i = n & 1; i <= P.deg(); i += 2) nP[i >> 1] = P[i];\n    return bostan_mori(nP,\
    \ nQ, n / 2);\n}\n} // namespace suisen\n\n#endif // SUISEN_BOSTAN_MORI"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/math/BostanMori.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/BostanMori.hpp
layout: document
redirect_from:
- /library/library/math/BostanMori.hpp
- /library/library/math/BostanMori.hpp.html
title: library/math/BostanMori.hpp
---
