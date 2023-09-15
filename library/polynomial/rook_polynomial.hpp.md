---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/polynomial/convert_to_newton_basis.hpp
    title: Convert To Newton Basis
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
    title: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/rook_polynomial.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n#line\
    \ 1 \"library/polynomial/convert_to_newton_basis.hpp\"\n\n\n\n#include <tuple>\n\
    #line 6 \"library/polynomial/convert_to_newton_basis.hpp\"\n\nnamespace suisen\
    \ {\n    // Returns b=(b_0,...,b_{N-1}) s.t. f(x) = Sum[i=0,N-1] b_i Prod[j=0,i-1](x\
    \ - p_j)\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ convert_to_newton_basis(const FPSType& f, const std::vector<typename FPSType::value_type>&\
    \ p) {\n        const int n = p.size();\n        assert(f.size() == n);\n\n  \
    \      int m = 1;\n        while (m < n) m <<= 1;\n\n        std::vector<FPSType>\
    \ seg(2 * m);\n        for (int i = 0; i < m; ++i) {\n            seg[m + i] =\
    \ { i < n ? -p[i] : 0, 1 };\n        }\n        for (int i = m - 1; i > 0; --i)\
    \ {\n            if (((i + 1) & -(i + 1)) == (i + 1)) continue; // i = 2^k - 1\n\
    \            seg[i] = seg[2 * i] * seg[2 * i + 1];\n        }\n\n        seg[1]\
    \ = f;\n        for (int i = 1; i < m; ++i) {\n            std::tie(seg[2 * i\
    \ + 1], seg[2 * i]) = seg[i].div_mod(seg[2 * i]);\n        }\n\n        std::vector<typename\
    \ FPSType::value_type> b(n);\n        for (int i = 0; i < n; ++i) {\n        \
    \    b[i] = seg[m + i].safe_get(0);\n        }\n        return b;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 10 \"library/polynomial/rook_polynomial.hpp\"\n\
    \nnamespace suisen {\n    // O(n(log n)^2). returns rook polynomial r s.t. r[k]\
    \ := # ways to put k non-attacking rooks on a Young tableau\n    template <typename\
    \ FPSType>\n    FPSType rook_polynomial_young_tableau(const std::vector<int> &h)\
    \ {\n        using mint = typename FPSType::value_type;\n        assert(std::is_sorted(h.begin(),\
    \ h.end()));\n        const int n = h.size();\n        std::vector<FPSType> fs(n);\n\
    \        for (int i = 0; i < n; ++i) fs[i] = FPSType{ h[i] - i, 1 };\n       \
    \ FPSType f = FPSType::prod(fs);\n        std::vector<mint> p(n + 1);\n      \
    \  std::iota(p.begin(), p.end(), 0);\n        FPSType r = convert_to_newton_basis(f,\
    \ p);\n        std::reverse(r.begin(), r.end());\n        return r;\n    }\n}\
    \ // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ROOK_POLYNOMIAL\n#define SUISEN_ROOK_POLYNOMIAL\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n#include\
    \ \"library/polynomial/convert_to_newton_basis.hpp\"\n\nnamespace suisen {\n \
    \   // O(n(log n)^2). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking\
    \ rooks on a Young tableau\n    template <typename FPSType>\n    FPSType rook_polynomial_young_tableau(const\
    \ std::vector<int> &h) {\n        using mint = typename FPSType::value_type;\n\
    \        assert(std::is_sorted(h.begin(), h.end()));\n        const int n = h.size();\n\
    \        std::vector<FPSType> fs(n);\n        for (int i = 0; i < n; ++i) fs[i]\
    \ = FPSType{ h[i] - i, 1 };\n        FPSType f = FPSType::prod(fs);\n        std::vector<mint>\
    \ p(n + 1);\n        std::iota(p.begin(), p.end(), 0);\n        FPSType r = convert_to_newton_basis(f,\
    \ p);\n        std::reverse(r.begin(), r.end());\n        return r;\n    }\n}\
    \ // namespace suisen\n\n\n#endif // SUISEN_ROOK_POLYNOMIAL\n"
  dependsOn:
  - library/polynomial/convert_to_newton_basis.hpp
  isVerificationFile: false
  path: library/polynomial/rook_polynomial.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/polynomial/rook_polynomial/abc272_h.test.cpp
documentation_of: library/polynomial/rook_polynomial.hpp
layout: document
redirect_from:
- /library/library/polynomial/rook_polynomial.hpp
- /library/library/polynomial/rook_polynomial.hpp.html
title: library/polynomial/rook_polynomial.hpp
---
