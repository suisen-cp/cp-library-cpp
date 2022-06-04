---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':x:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/polynomial_taylor_shift.hpp\"\n\n\n\n\
    #line 1 \"library/polynomial/fps.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iostream>\n\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n\
    \        inv_mods() {}\n        inv_mods(int n) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ invs[i];\n        }\n        static void ensure(int n) {\n            int sz\
    \ = invs.size();\n            if (sz < 2) invs = {0, 1}, sz = 2;\n           \
    \ if (sz < n + 1) {\n                invs.resize(n + 1);\n                for\
    \ (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n \
    \           }\n        }\n    private:\n        static std::vector<mint> invs;\n\
    \        static constexpr int mod = mint::mod();\n};\ntemplate <typename mint>\n\
    std::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line 9 \"library/polynomial/fps.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename mint>\nusing convolution_t = std::vector<mint>\
    \ (*)(const std::vector<mint> &, const std::vector<mint> &);\n\ntemplate <typename\
    \ mint>\nclass FPS : public std::vector<mint> {\n    public:\n        using std::vector<mint>::vector;\n\
    \n        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l)\
    \ {}\n        FPS(const std::vector<mint> &v) : std::vector<mint>::vector(v) {}\n\
    \        FPS(std::vector<mint> &&v) : std::vector<mint>::vector(std::move(v))\
    \ {}\n\n        static void set_multiplication(convolution_t<mint> multiplication)\
    \ {\n            FPS<mint>::mult = multiplication;\n        }\n\n        const\
    \ mint  operator[](int n) const noexcept { return n <= deg() ? unsafe_get(n) :\
    \ 0; }\n              mint& operator[](int n)       noexcept { ensure_deg(n);\
    \ return unsafe_get(n); }\n\n        int size() const noexcept { return std::vector<mint>::size();\
    \ }\n        int deg()  const noexcept { return size() - 1; }\n        int normalize()\
    \ {\n            while (this->size() and this->back() == 0) this->pop_back();\n\
    \            return deg();\n        }\n        FPS& pre_inplace(int max_deg) noexcept\
    \ {\n            if (deg() > max_deg) this->resize(std::max(0, max_deg + 1));\n\
    \            return *this;\n        }\n        FPS pre(int max_deg) const noexcept\
    \ { return FPS(*this).pre_inplace(max_deg); }\n\n        FPS operator+() const\
    \ { return FPS(*this); }\n        FPS operator-() const {\n            FPS f(*this);\n\
    \            for (auto &e : f) e = mint::mod() - e;\n            return f;\n \
    \       }\n        FPS& operator++() { ++(*this)[0]; return *this; }\n       \
    \ FPS& operator--() { --(*this)[0]; return *this; }\n        FPS& operator+=(const\
    \ mint x) { (*this)[0] += x; return *this; }\n        FPS& operator-=(const mint\
    \ x) { (*this)[0] -= x; return *this; }\n        FPS& operator+=(const FPS &g)\
    \ {\n            ensure_deg(g.deg());\n            for (int i = 0; i <= g.deg();\
    \ ++i) unsafe_get(i) += g.unsafe_get(i);\n            return *this;\n        }\n\
    \        FPS& operator-=(const FPS &g) {\n            ensure_deg(g.deg());\n \
    \           for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);\n\
    \            return *this;\n        }\n        FPS& operator*=(const FPS  &g)\
    \ { return *this = FPS<mint>::mult(*this, g); }\n        FPS& operator*=(    \
    \  FPS &&g) { return *this = FPS<mint>::mult(*this, g); }\n        FPS& operator*=(const\
    \ mint x) {\n            for (auto &e : *this) e *= x;\n            return *this;\n\
    \        }\n        FPS& operator/=(FPS &&g) {\n            const int fd = normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ { this->clear(); return *this; }\n            if (gd == 0) return *this *= g.unsafe_get(0).inv();\n\
    \            static constexpr int THRESHOLD_NAIVE_POLY_QUOTIENT = 256;\n     \
    \       if (gd <= THRESHOLD_NAIVE_POLY_QUOTIENT) {\n                *this = std::move(naive_div_inplace(std::move(g),\
    \ gd).first);\n                return *this;\n            }\n            std::reverse(this->begin(),\
    \ this->end()), std::reverse(g.begin(), g.end());\n            const int k = fd\
    \ - gd;\n            *this *= g.inv_inplace(k), this->resize(k + 1);\n       \
    \     std::reverse(this->begin(), this->end());\n            return *this;\n \
    \       }\n        FPS& operator%=(FPS &&g) {\n            int fd = normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ return *this;\n            if (gd == 0) { this->clear(); return *this; }\n \
    \           static constexpr int THRESHOLD_NAIVE_REMAINDER = 256;\n          \
    \  if (gd <= THRESHOLD_NAIVE_REMAINDER) return naive_div_inplace(std::move(g),\
    \ gd).second;\n            *this -= g * (*this / g);\n            return pre_inplace(gd\
    \ - 1);\n        }\n        FPS& operator/=(const FPS &g) { return *this /= FPS(g);\
    \ }\n        FPS& operator%=(const FPS &g) { return *this %= FPS(g); }\n     \
    \   FPS& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, 0);\n            return *this;\n        }\n        FPS& operator>>=(const\
    \ int shamt) {\n            if (shamt > size()) this->clear();\n            else\
    \ this->erase(this->begin(), this->begin() + shamt);\n            return *this;\n\
    \        }\n\n        friend FPS operator+(FPS f, const FPS &g) { f += g; return\
    \ f; }\n        friend FPS operator+(FPS f, const mint x) { f += x; return f;\
    \ }\n        friend FPS operator-(FPS f, const FPS &g) { f -= g; return f; }\n\
    \        friend FPS operator-(FPS f, const mint x) { f -= x; return f; }\n   \
    \     friend FPS operator*(FPS f, const FPS &g) { f *= g; return f; }\n      \
    \  friend FPS operator*(FPS f, const mint x) { f *= x; return f; }\n        friend\
    \ FPS operator/(FPS f, const FPS &g) { f /= g; return f; }\n        friend FPS\
    \ operator%(FPS f, const FPS &g) { f %= g; return f; }\n        friend FPS operator*(const\
    \ mint x, FPS f) { f *= x; return f; }\n        friend FPS operator<<(FPS f, const\
    \ int shamt) { f <<= shamt; return f; }\n        friend FPS operator>>(FPS f,\
    \ const int shamt) { f >>= shamt; return f; }\n\n        friend bool operator==(const\
    \ FPS &f, const FPS &g) {\n            int n = f.size(), m = g.size();\n     \
    \       if (n < m) return g == f;\n            for (int i = 0; i < m; ++i) if\
    \ (f.unsafe_get(i) != g.unsafe_get(i)) return false;\n            for (int i =\
    \ m; i < n; ++i) if (f.unsafe_get(i) != 0) return false;\n            return true;\n\
    \        }\n\n        FPS& diff_inplace() {\n            if (this->size() == 0)\
    \ return *this;\n            for (int i = 1; i <= deg(); ++i) unsafe_get(i - 1)\
    \ = unsafe_get(i) * i;\n            this->pop_back();\n            return *this;\n\
    \        }\n        FPS& intg_inplace() {\n            int d = deg();\n      \
    \      ensure_deg(d + 1);\n            for (int i = d; i >= 0; --i) unsafe_get(i\
    \ + 1) = unsafe_get(i) * invs[i + 1];\n            unsafe_get(0) = 0;\n      \
    \      return *this;\n        }\n        FPS& inv_inplace(const int max_deg) {\n\
    \            FPS res { unsafe_get(0).inv() };\n            for (int k = 1; k <=\
    \ max_deg; k *= 2) {\n                FPS tmp(this->pre(k * 2) * (res * res));\n\
    \                res *= 2, res -= tmp.pre_inplace(2 * k);\n            }\n   \
    \         return *this = std::move(res), pre_inplace(max_deg);\n        }\n  \
    \      FPS& log_inplace(const int max_deg) {\n            FPS f_inv = inv(max_deg);\n\
    \            diff_inplace(), *this *= f_inv, pre_inplace(max_deg - 1), intg_inplace();\n\
    \            return *this;\n        }\n        FPS& exp_inplace(const int max_deg)\
    \ {\n            if (max_deg <= 60) return *this = naive_exp(max_deg);\n     \
    \       FPS res {1};\n            for (int k = 1; k <= max_deg; k *= 2) res *=\
    \ ++(pre(k * 2) - res.log(k * 2)), res.pre_inplace(k * 2);\n            return\
    \ *this = std::move(res), pre_inplace(max_deg);\n        }\n        FPS& pow_inplace(const\
    \ long long k, const int max_deg) {\n            int tlz = 0;\n            while\
    \ (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;\n            if (tlz * k > max_deg)\
    \ { this->clear(); return *this; }\n            *this >>= tlz;\n            mint\
    \ base = (*this)[0];\n            *this *= base.inv(), log_inplace(max_deg), *this\
    \ *= k, exp_inplace(max_deg), *this *= base.pow(k);\n            return *this\
    \ <<= tlz * k, pre_inplace(max_deg);\n        }\n        FPS diff() const { FPS\
    \ f{*this}; f.diff_inplace(); return f; }\n        FPS intg() const { FPS f{*this};\
    \ f.intg_inplace(); return f; }\n        FPS inv(const int max_deg) const { FPS\
    \ f{*this}; f.inv_inplace(max_deg); return f; }\n        FPS log(const int max_deg)\
    \ const { FPS f{*this}; f.log_inplace(max_deg); return f; }\n        FPS exp(const\
    \ int max_deg) const { FPS f{*this}; f.exp_inplace(max_deg); return f; }\n   \
    \     FPS pow(const long long k, const int max_deg) const { FPS f{*this}; f.pow_inplace(k,\
    \ max_deg); return f; }\n\n        mint eval(mint x) const {\n            mint\
    \ y = 0;\n            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<mint>\
    \ invs;\n        static convolution_t<mint> mult;\n        void ensure_deg(int\
    \ d) { if (deg() < d) this->resize(d + 1, 0); }\n        const mint& unsafe_get(int\
    \ i) const { return std::vector<mint>::operator[](i); }\n              mint& unsafe_get(int\
    \ i)       { return std::vector<mint>::operator[](i); }\n\n        std::pair<FPS,\
    \ FPS&> naive_div_inplace(FPS &&g, const int gd) {\n            const int k =\
    \ deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n         \
    \   FPS q(k + 1);\n            for (int i = k; i >= 0; --i) {\n              \
    \  mint div = this->unsafe_get(i + gd) * head_inv;\n                q.unsafe_get(i)\
    \ = div;\n                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j)\
    \ -= div * g.unsafe_get(j);\n            }\n            return {q, pre_inplace(gd\
    \ - 1)};\n        }\n};\n\ntemplate <typename mint>\nconvolution_t<mint> FPS<mint>::mult\
    \ = [](const auto &, const auto &) {\n    std::cerr << \"convolution function\
    \ is not available.\" << std::endl;\n    assert(false);\n    return std::vector<mint>{};\n\
    };\n\n} // namespace suisen\n\ntemplate <typename mint>\nauto sqrt(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{})  {\n    assert(false);\n}\n\
    template <typename mint>\nauto log(suisen::FPS<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPS<mint>{}) {\n    return a.log(a.deg());\n}\ntemplate <typename mint>\n\
    auto exp(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {\n\
    \    return a.exp(a.deg());\n}\ntemplate <typename mint, typename T>\nauto pow(suisen::FPS<mint>\
    \ a, T b) -> decltype(mint::mod(), suisen::FPS<mint>{}) {\n    return a.pow(b,\
    \ a.deg());\n}\ntemplate <typename mint>\nauto inv(suisen::FPS<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPS<mint>{})  {\n    return a.inv(a.deg());\n}\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T, typename U = T>\n    struct factorial {\n        factorial() {}\n\
    \        factorial(int n) { ensure(n); }\n\n        static void ensure(const int\
    \ n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
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
    } // namespace suisen\n\n\n#line 6 \"library/polynomial/polynomial_taylor_shift.hpp\"\
    \n\nnamespace suisen {\n// return f(x + c) \ntemplate <typename mint>\nFPS<mint>\
    \ translate(const FPS<mint> &f, const mint c) {\n    int d = f.deg();\n    if\
    \ (d < 0) return FPS<mint> {0};\n    factorial<mint> fac(d);\n    FPS<mint> expc(d\
    \ + 1), g(d + 1);\n    mint p = 1;\n    for (int i = 0; i <= d; ++i, p *= c) {\n\
    \        expc[i] = p * fac.fac_inv(i);\n        g[d - i] = f[i] * fac(i);\n  \
    \  }\n    g *= expc, g.resize(d + 1);\n    for (int i = 0; i <= d; ++i) g[i] *=\
    \ fac.fac_inv(d - i);\n    std::reverse(g.begin(), g.end());\n    return g;\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n#define SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n\
    \n#include \"library/polynomial/fps.hpp\"\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n// return f(x + c) \ntemplate <typename mint>\nFPS<mint>\
    \ translate(const FPS<mint> &f, const mint c) {\n    int d = f.deg();\n    if\
    \ (d < 0) return FPS<mint> {0};\n    factorial<mint> fac(d);\n    FPS<mint> expc(d\
    \ + 1), g(d + 1);\n    mint p = 1;\n    for (int i = 0; i <= d; ++i, p *= c) {\n\
    \        expc[i] = p * fac.fac_inv(i);\n        g[d - i] = f[i] * fac(i);\n  \
    \  }\n    g *= expc, g.resize(d + 1);\n    for (int i = 0; i <= d; ++i) g[i] *=\
    \ fac.fac_inv(d - i);\n    std::reverse(g.begin(), g.end());\n    return g;\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_POLYNOMIAL_TAYLOR_SHIFT\n"
  dependsOn:
  - library/polynomial/fps.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/polynomial/polynomial_taylor_shift.hpp
  requiredBy: []
  timestamp: '2022-06-03 19:04:31+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
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
