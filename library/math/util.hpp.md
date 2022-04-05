---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: Factorial
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/util/abc240_g.test.cpp
    title: test/src/math/util/abc240_g.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/util.hpp\"\n\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\ntemplate\
    \ <typename T, typename U = T>\nclass factorial {\n    public:\n        factorial()\
    \ {}\n        factorial(int n) { ensure(n); }\n        const T& fac(const int\
    \ i) {\n            ensure(i);\n            return fac_[i];\n        }\n     \
    \   const T& operator()(int i) {\n            return fac(i);\n        }\n    \
    \    const U& inv(const int i) {\n            ensure(i);\n            return inv_[i];\n\
    \        }\n        U binom(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return fac_[n]\
    \ * inv_[r] * inv_[n - r];\n        }\n        U perm(const int n, const int r)\
    \ {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return fac_[n] * inv_[n - r];\n        }\n    private:\n        static\
    \ std::vector<T> fac_;\n        static std::vector<U> inv_;\n        static void\
    \ ensure(const int n) {\n            int sz = fac_.size();\n            if (n\
    \ + 1 <= sz) return;\n            int new_size = std::max(n + 1, sz * 2);\n  \
    \          fac_.resize(new_size), inv_.resize(new_size);\n            for (int\
    \ i = sz; i < new_size; ++i) fac_[i] = fac_[i - 1] * i;\n            inv_[new_size\
    \ - 1] = U(1) / fac_[new_size - 1];\n            for (int i = new_size - 1; i\
    \ > sz; --i) inv_[i - 1] = inv_[i] * i;\n        }\n};\ntemplate <typename T,\
    \ typename U>\nstd::vector<T> factorial<T, U>::fac_ {1};\ntemplate <typename T,\
    \ typename U>\nstd::vector<U> factorial<T, U>::inv_ {1};\n} // namespace suisen\n\
    \n\n#line 5 \"library/math/util.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ mint>\n    mint random_walk_1d(int n, int x) {\n        if (x < 0) x = -x;\n\
    \        factorial<mint> fac(n);\n        int m = n + x;\n        return m & 1\
    \ ? 0 : fac.binom(n, m / 2);\n    }\n    template <typename mint>\n    mint random_walk_2d(int\
    \ n, int x, int y) {\n        return random_walk_1d<mint>(n, x + y) * random_walk_1d<mint>(n,\
    \ x - y);\n    }\n\n    template <typename mint, typename BinomialCoefficient>\n\
    \    mint random_walk_1d(int n, int x, const BinomialCoefficient &binom_n) {\n\
    \        if (x < 0) x = -x;\n        int m = n + x;\n        return m & 1 ? 0\
    \ : binom_n(m / 2);\n    }\n    template <typename mint, typename BinomialCoefficient>\n\
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
  timestamp: '2022-03-06 00:26:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/util/abc240_g.test.cpp
documentation_of: library/math/util.hpp
layout: document
title: Util
---
## Util