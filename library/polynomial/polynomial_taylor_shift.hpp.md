---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift_2.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/polynomial_taylor_shift.hpp\"\n\n\n\n\
    #include <algorithm>\n\n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    template <typename T,\
    \ typename U = T>\n    struct factorial {\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n\n        static void ensure(const int n) {\n           \
    \ int sz = _fac.size();\n            if (n + 1 <= sz) return;\n            int\
    \ new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 7 \"library/polynomial/polynomial_taylor_shift.hpp\"\n\nnamespace\
    \ suisen {\n    // return f(x + c) \n    template <typename FPSType, typename\
    \ T>\n    FPSType translate(const FPSType& f, const T c) {\n        int d = f.deg();\n\
    \        if (d < 0) return FPSType{ 0 };\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(d);\n        FPSType expc(d + 1), g(d + 1);\n   \
    \     mint p = 1;\n        for (int i = 0; i <= d; ++i, p *= c) {\n          \
    \  expc[i] = p * fac.fac_inv(i);\n            g[d - i] = f[i] * fac(i);\n    \
    \    }\n        g *= expc, g.resize(d + 1);\n        for (int i = 0; i <= d; ++i)\
    \ g[i] *= fac.fac_inv(d - i);\n        std::reverse(g.begin(), g.end());\n   \
    \     return g;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n#define SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n\
    \n#include <algorithm>\n\n#include \"library/math/factorial.hpp\"\n\nnamespace\
    \ suisen {\n    // return f(x + c) \n    template <typename FPSType, typename\
    \ T>\n    FPSType translate(const FPSType& f, const T c) {\n        int d = f.deg();\n\
    \        if (d < 0) return FPSType{ 0 };\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(d);\n        FPSType expc(d + 1), g(d + 1);\n   \
    \     mint p = 1;\n        for (int i = 0; i <= d; ++i, p *= c) {\n          \
    \  expc[i] = p * fac.fac_inv(i);\n            g[d - i] = f[i] * fac(i);\n    \
    \    }\n        g *= expc, g.resize(d + 1);\n        for (int i = 0; i <= d; ++i)\
    \ g[i] *= fac.fac_inv(d - i);\n        std::reverse(g.begin(), g.end());\n   \
    \     return g;\n    }\n} // namespace suisen\n\n#endif // SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/polynomial/polynomial_taylor_shift.hpp
  requiredBy: []
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift_2.test.cpp
documentation_of: library/polynomial/polynomial_taylor_shift.hpp
layout: document
title: Polynomial Taylor Shift
---
## Polynomial Taylor Shift

$\mathbb{F} _ p$ 上の $n$ 次多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {n} a _ i x ^ i$ および $c\in \mathbb{F} _ p$ に対して、多項式 $g(x) = f(x + c)$ を計算します。

## アルゴリズム

$$\begin{aligned}
f(x + c)
&=\sum _ {i = 0} ^ {n} a _ i (x + c) ^ i \\
&=\sum _ {i = 0} ^ {n} \sum _{j = 0} ^ i a _ i \cdot \binom{i}{j}\cdot c ^ {i - j} \cdot x ^ j \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {i = j} ^ {n} (a _ i \cdot i!) \cdot \dfrac{c ^ {i - j}}{(i - j)!} \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {k = 0} ^ {n - j} (a _ {j + k} \cdot (j + k)!) \cdot \dfrac{c ^ k}{k!} \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {k = 0} ^ {n - j} b _ {(n - j) - k} \cdot \dfrac{c ^ k}{k!} \quad (b _ i := a _ {n - i} \cdot (n - i)! )\\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ {n - j}}{(n - j)!} \sum _ {k = 0} ^ {j} b _ {j - k} \cdot \dfrac{c ^ k}{k!}
\end{aligned}$$

で、各 $j = 0, \ldots, n$ に対する $\displaystyle \sum _ {k = 0} ^ {j} b _ {j - k} \cdot \dfrac{c ^ k}{k!}$ は高速フーリエ変換等を用いた畳み込みにより $\Theta(n \log n)$ 時間で計算できます。

従って、$0!,\ldots,n!$ の乗法逆元の前計算の下で、$f(x + c)$ も $\Theta(n \log n)$ 時間で計算できます。

なお、$0!,\ldots,n!$ の乗法逆元が存在すること、即ち $n \lt p$ を仮定していることに注意します。
