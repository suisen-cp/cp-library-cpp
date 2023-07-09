---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/math/util/abc240_g.test.cpp
    title: test/src/math/util/abc240_g.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/util.hpp\"\n\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, typename U = T>\n    struct factorial {\n        factorial() =\
    \ default;\n        factorial(int n) { ensure(n); }\n\n        static void ensure(const\
    \ int n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        U perm(const int n, const int r) {\n            if\
    \ (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n            return\
    \ _fac[n] * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T>\
    \ _fac;\n        static std::vector<U> _fac_inv;\n    };\n    template <typename\
    \ T, typename U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template\
    \ <typename T, typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n\
    } // namespace suisen\n\n\n#line 5 \"library/math/util.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename mint>\n    mint random_walk_1d(int n, int x) {\n \
    \       if (x < 0) x = -x;\n        factorial<mint> fac(n);\n        int m = n\
    \ + x;\n        return m & 1 ? 0 : fac.binom(n, m / 2);\n    }\n    template <typename\
    \ mint>\n    mint random_walk_2d(int n, int x, int y) {\n        return random_walk_1d<mint>(n,\
    \ x + y) * random_walk_1d<mint>(n, x - y);\n    }\n\n    template <typename mint,\
    \ typename BinomialCoefficient>\n    mint random_walk_1d(int n, int x, const BinomialCoefficient\
    \ &binom_n) {\n        if (x < 0) x = -x;\n        int m = n + x;\n        return\
    \ m & 1 ? 0 : binom_n(m / 2);\n    }\n    template <typename mint, typename BinomialCoefficient>\n\
    \    mint random_walk_2d(int n, int x, int y, const BinomialCoefficient &binom_n)\
    \ {\n        return random_walk_1d<mint>(n, x + y, binom_n) * random_walk_1d<mint>(n,\
    \ x - y, binom_n);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MATH_UTIL\n#define SUISEN_MATH_UTIL\n\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    mint random_walk_1d(int\
    \ n, int x) {\n        if (x < 0) x = -x;\n        factorial<mint> fac(n);\n \
    \       int m = n + x;\n        return m & 1 ? 0 : fac.binom(n, m / 2);\n    }\n\
    \    template <typename mint>\n    mint random_walk_2d(int n, int x, int y) {\n\
    \        return random_walk_1d<mint>(n, x + y) * random_walk_1d<mint>(n, x - y);\n\
    \    }\n\n    template <typename mint, typename BinomialCoefficient>\n    mint\
    \ random_walk_1d(int n, int x, const BinomialCoefficient &binom_n) {\n       \
    \ if (x < 0) x = -x;\n        int m = n + x;\n        return m & 1 ? 0 : binom_n(m\
    \ / 2);\n    }\n    template <typename mint, typename BinomialCoefficient>\n \
    \   mint random_walk_2d(int n, int x, int y, const BinomialCoefficient &binom_n)\
    \ {\n        return random_walk_1d<mint>(n, x + y, binom_n) * random_walk_1d<mint>(n,\
    \ x - y, binom_n);\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_MATH_UTIL\n"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/math/util.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/math/util/abc240_g.test.cpp
documentation_of: library/math/util.hpp
layout: document
title: Util
---
## Util