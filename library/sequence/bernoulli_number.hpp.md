---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/bernoulli_number/bernoulli_number.test.cpp
    title: test/src/sequence/bernoulli_number/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/bernoulli_number/bernoulli_number_2.test.cpp
    title: test/src/sequence/bernoulli_number/bernoulli_number_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/bernoulli_number.hpp\"\n\n\n\n#line 1 \"\
    library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T, typename U = T>\n    struct factorial\
    \ {\n        factorial() {}\n        factorial(int n) { ensure(n); }\n\n     \
    \   static void ensure(const int n) {\n            int sz = _fac.size();\n   \
    \         if (n + 1 <= sz) return;\n            int new_size = std::max(n + 1,\
    \ sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n  \
    \          for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n  \
    \          _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n            for\
    \ (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n   \
    \     }\n\n        T fac(const int i) {\n            ensure(i);\n            return\
    \ _fac[i];\n        }\n        T operator()(int i) {\n            return fac(i);\n\
    \        }\n        U fac_inv(const int i) {\n            ensure(i);\n       \
    \     return _fac_inv[i];\n        }\n        U binom(const int n, const int r)\
    \ {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 5 \"library/sequence/bernoulli_number.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ bernoulli_number(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(n);\n        FPSType a(n + 1);\n        for (int\
    \ i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);\n        a.inv_inplace(n + 1),\
    \ a.resize(n + 1);\n        for (int i = 2; i <= n; ++i) a[i] *= fac(i);\n   \
    \     return a;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BERNOULLI_NUMBER\n#define SUISEN_BERNOULLI_NUMBER\n\n#include\
    \ \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ FPSType>\n    std::vector<typename FPSType::value_type> bernoulli_number(int\
    \ n) {\n        using mint = typename FPSType::value_type;\n        factorial<mint>\
    \ fac(n);\n        FPSType a(n + 1);\n        for (int i = 0; i <= n; ++i) a[i]\
    \ = fac.fac_inv(i + 1);\n        a.inv_inplace(n + 1), a.resize(n + 1);\n    \
    \    for (int i = 2; i <= n; ++i) a[i] *= fac(i);\n        return a;\n    }\n\
    } // namespace suisen\n\n#endif // SUISEN_BERNOULLI_NUMBER\n"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/sequence/bernoulli_number.hpp
  requiredBy: []
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/bernoulli_number/bernoulli_number_2.test.cpp
  - test/src/sequence/bernoulli_number/bernoulli_number.test.cpp
documentation_of: library/sequence/bernoulli_number.hpp
layout: document
title: Bernoulli Number
---
## Bernoulli Number

### bernoulli_number

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> bernoulli_number(int n)
  ```

- 概要

  ベルヌーイ数 $B_0,\ldots,B_N$ を計算します．

  $$\sum_{i=0} ^ \infty\dfrac{B_i}{i!}x ^ i=\dfrac{x}{e ^ x-1}$$

  より，

  $$B_i=i!\cdot [x ^ i]\left(\sum_{i=0} ^ \infty \dfrac{x ^ i}{(i+1)!}\right) ^ {-1}$$

  に従って計算します．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  ベルヌーイ数 $\\\{B_i\\\} _ {i=0} ^ N$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$