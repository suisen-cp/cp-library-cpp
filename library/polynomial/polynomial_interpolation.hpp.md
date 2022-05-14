---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
    title: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/polynomial_interpolation.hpp\"\n\n\n\n\
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
    \ {\n            FPS<mint>::mult = multiplication;\n        }\n\n        inline\
    \ const mint  operator[](int n) const noexcept { return n <= deg() ? unsafe_get(n)\
    \ : 0; }\n        inline       mint& operator[](int n)       noexcept { ensure_deg(n);\
    \ return unsafe_get(n); }\n\n        inline int size() const noexcept { return\
    \ std::vector<mint>::size(); }\n        inline int deg()  const noexcept { return\
    \ size() - 1; }\n        inline int normalize() {\n            while (this->size()\
    \ and this->back() == 0) this->pop_back();\n            return deg();\n      \
    \  }\n        inline FPS& pre_inplace(int max_deg) noexcept {\n            if\
    \ (deg() > max_deg) this->resize(std::max(0, max_deg + 1));\n            return\
    \ *this;\n        }\n        inline FPS pre(int max_deg) const noexcept { return\
    \ FPS(*this).pre_inplace(max_deg); }\n\n        inline FPS operator+() const {\
    \ return FPS(*this); }\n        FPS operator-() const {\n            FPS f(*this);\n\
    \            for (auto &e : f) e = mint::mod() - e;\n            return f;\n \
    \       }\n        inline FPS& operator++() { ++(*this)[0]; return *this; }\n\
    \        inline FPS& operator--() { --(*this)[0]; return *this; }\n        inline\
    \ FPS& operator+=(const mint x) { (*this)[0] += x; return *this; }\n        inline\
    \ FPS& operator-=(const mint x) { (*this)[0] -= x; return *this; }\n        FPS&\
    \ operator+=(const FPS &g) {\n            ensure_deg(g.deg());\n            for\
    \ (int i = 0; i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);\n         \
    \   return *this;\n        }\n        FPS& operator-=(const FPS &g) {\n      \
    \      ensure_deg(g.deg());\n            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i)\
    \ -= g.unsafe_get(i);\n            return *this;\n        }\n        inline FPS&\
    \ operator*=(const FPS  &g) { return *this = FPS<mint>::mult(*this, g); }\n  \
    \      inline FPS& operator*=(      FPS &&g) { return *this = FPS<mint>::mult(*this,\
    \ g); }\n        inline FPS& operator*=(const mint x) {\n            for (auto\
    \ &e : *this) e *= x;\n            return *this;\n        }\n        FPS& operator/=(FPS\
    \ &&g) {\n            const int fd = normalize(), gd = g.normalize();\n      \
    \      assert(gd >= 0);\n            if (fd < gd) { this->clear(); return *this;\
    \ }\n            if (gd == 0) return *this *= g.unsafe_get(0).inv();\n       \
    \     static constexpr int THRESHOLD_NAIVE_POLY_QUOTIENT = 256;\n            if\
    \ (gd <= THRESHOLD_NAIVE_POLY_QUOTIENT) {\n                *this = std::move(naive_div_inplace(std::move(g),\
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
    \ - 1);\n        }\n        inline FPS& operator/=(const FPS &g) { return *this\
    \ /= FPS(g); }\n        inline FPS& operator%=(const FPS &g) { return *this %=\
    \ FPS(g); }\n        FPS& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, 0);\n            return *this;\n        }\n        FPS& operator>>=(const\
    \ int shamt) {\n            if (shamt > size()) this->clear();\n            else\
    \ this->erase(this->begin(), this->begin() + shamt);\n            return *this;\n\
    \        }\n\n        inline FPS operator+(FPS &&g) const { return FPS(*this)\
    \ += std::move(g); }\n        inline FPS operator-(FPS &&g) const { return FPS(*this)\
    \ -= std::move(g); }\n        inline FPS operator*(FPS &&g) const { return FPS(*this)\
    \ *= std::move(g); }\n        inline FPS operator/(FPS &&g) const { return FPS(*this)\
    \ /= std::move(g); }\n        inline FPS operator%(FPS &&g) const { return FPS(*this)\
    \ %= std::move(g); }\n        inline FPS operator+(const FPS &g) const { return\
    \ FPS(*this) += g; }\n        inline FPS operator+(const mint x) const { return\
    \ FPS(*this) += x; }\n        inline FPS operator-(const FPS &g) const { return\
    \ FPS(*this) -= g; }\n        inline FPS operator-(const mint x) const { return\
    \ FPS(*this) -= x; }\n        inline FPS operator*(const FPS &g) const { return\
    \ FPS(*this) *= g; }\n        inline FPS operator*(const mint x) const { return\
    \ FPS(*this) *= x; }\n        inline FPS operator/(const FPS &g) const { return\
    \ FPS(*this) /= g; }\n        inline FPS operator%(const FPS &g) const { return\
    \ FPS(*this) %= g; }\n        inline friend FPS operator*(const mint x, const\
    \ FPS  &f) { return f * x; }\n        inline friend FPS operator*(const mint x,\
    \       FPS &&f) { return f *= x; }\n        inline FPS operator<<(const int shamt)\
    \ { return FPS(*this) <<= shamt; }\n        inline FPS operator>>(const int shamt)\
    \ { return FPS(*this) >>= shamt; }\n\n        friend bool operator==(const FPS\
    \ &f, const FPS &g) {\n            int n = f.size(), m = g.size();\n         \
    \   if (n < m) return g == f;\n            for (int i = 0; i < m; ++i) if (f.unsafe_get(i)\
    \ != g.unsafe_get(i)) return false;\n            for (int i = m; i < n; ++i) if\
    \ (f.unsafe_get(i) != 0) return false;\n            return true;\n        }\n\n\
    \        FPS& diff_inplace() {\n            if (this->size() == 0) return *this;\n\
    \            for (int i = 1; i <= deg(); ++i) unsafe_get(i - 1) = unsafe_get(i)\
    \ * i;\n            this->pop_back();\n            return *this;\n        }\n\
    \        FPS& intg_inplace() {\n            int d = deg();\n            ensure_deg(d\
    \ + 1);\n            for (int i = d; i >= 0; --i) unsafe_get(i + 1) = unsafe_get(i)\
    \ * invs[i + 1];\n            unsafe_get(0) = 0;\n            return *this;\n\
    \        }\n        FPS& inv_inplace(const int max_deg) {\n            FPS res\
    \ { unsafe_get(0).inv() };\n            for (int k = 1; k <= max_deg; k *= 2)\
    \ {\n                FPS tmp(this->pre(k * 2) * (res * res));\n              \
    \  res *= 2, res -= tmp.pre_inplace(2 * k);\n            }\n            return\
    \ *this = std::move(res), pre_inplace(max_deg);\n        }\n        FPS& log_inplace(const\
    \ int max_deg) {\n            FPS f_inv = inv(max_deg);\n            diff_inplace(),\
    \ *this *= f_inv, pre_inplace(max_deg - 1), intg_inplace();\n            return\
    \ *this;\n        }\n        FPS& exp_inplace(const int max_deg) {\n         \
    \   FPS res {1};\n            for (int k = 1; k <= max_deg; k *= 2) res *= ++(pre(k\
    \ * 2) - res.log(k * 2)), res.pre_inplace(k * 2);\n            return *this =\
    \ std::move(res), pre_inplace(max_deg);\n        }\n        FPS& pow_inplace(const\
    \ long long k, const int max_deg) {\n            int tlz = 0;\n            while\
    \ (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;\n            if (tlz * k > max_deg)\
    \ { this->clear(); return *this; }\n            *this >>= tlz;\n            mint\
    \ base = (*this)[0];\n            *this *= base.inv(), log_inplace(max_deg), *this\
    \ *= k, exp_inplace(max_deg), *this *= base.pow(k);\n            return *this\
    \ <<= tlz * k, pre_inplace(max_deg);\n        }\n        inline FPS diff() const\
    \ { return FPS(*this).diff_inplace(); }\n        inline FPS intg() const { return\
    \ FPS(*this).intg_inplace(); }\n        inline FPS inv(const int max_deg) const\
    \ { return FPS(*this).inv_inplace(max_deg); }\n        inline FPS log(const int\
    \ max_deg) const { return FPS(*this).log_inplace(max_deg); }\n        inline FPS\
    \ exp(const int max_deg) const { return FPS(*this).exp_inplace(max_deg); }\n \
    \       inline FPS pow(const long long k, const int max_deg) const { return FPS(*this).pow_inplace(k,\
    \ max_deg); }\n\n        mint eval(mint x) const {\n            mint y = 0;\n\
    \            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<mint>\
    \ invs;\n        static convolution_t<mint> mult;\n        inline void ensure_deg(int\
    \ d) { if (deg() < d) this->resize(d + 1, 0); }\n        inline const mint& unsafe_get(int\
    \ i) const { return std::vector<mint>::operator[](i); }\n        inline      \
    \ mint& unsafe_get(int i)       { return std::vector<mint>::operator[](i); }\n\
    \n        std::pair<FPS, FPS&> naive_div_inplace(FPS &&g, const int gd) {\n  \
    \          const int k = deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n\
    \            FPS q(k + 1);\n            for (int i = k; i >= 0; --i) {\n     \
    \           mint div = this->unsafe_get(i + gd) * head_inv;\n                q.unsafe_get(i)\
    \ = div;\n                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j)\
    \ -= div * g.unsafe_get(j);\n            }\n            return {q, pre_inplace(gd\
    \ - 1)};\n        }\n};\n\ntemplate <typename mint>\nconvolution_t<mint> FPS<mint>::mult\
    \ = [](const auto &, const auto &) {\n    std::cerr << \"convolution function\
    \ is not available.\" << std::endl;\n    assert(false);\n    return std::vector<mint>{};\n\
    };\n\n} // namespace suisen\n\ntemplate <typename mint>\nauto sqrt(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{})  {\n    assert(false);\n}\n\
    template <typename mint>\nauto log(suisen::FPS<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPS<mint>{}) {\n    return a.log(a.deg());\n}\ntemplate <typename mint>\n\
    auto exp(suisen::FPS<mint> a) -> decltype(mint::mod(), mint()) {\n    return a.exp(a.deg());\n\
    }\ntemplate <typename mint, typename T>\nauto pow(suisen::FPS<mint> a, T b) ->\
    \ decltype(mint::mod(), mint()) {\n    return a.pow(b, a.deg());\n}\ntemplate\
    \ <typename mint>\nauto inv(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{})\
    \  {\n    return a.inv(a.deg());\n}\n\n\n#line 5 \"library/polynomial/polynomial_interpolation.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    FPS<mint> polynomial_interpolation(const\
    \ std::vector<mint>& xs, const std::vector<mint>& ys) {\n        assert(xs.size()\
    \ == ys.size());\n        int n = xs.size();\n        std::vector<FPS<mint>> seg(2\
    \ * n), g(2 * n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint>{\
    \ -xs[i], 1 };\n        for (int i = n - 1; i > 0; --i) {\n            seg[i]\
    \ = seg[i * 2] * seg[i * 2 + 1];\n        }\n        g[1] = std::move(seg[1].diff_inplace());\n\
    \        for (int i = 1; i < n; ++i) {\n            int l = 2 * i, r = l + 1;\n\
    \            g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];\n        }\n        for\
    \ (int i = 0; i < n; ++i) g[n + i] = FPS<mint>{ ys[i] / g[n + i][0] };\n     \
    \   for (int i = n - 1; i > 0; --i) {\n            int l = 2 * i, r = l + 1;\n\
    \            g[i] = g[l] * seg[r] + g[r] * seg[l];\n        }\n        return\
    \ g[1];\n    }\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_POLYNOMIAL_INTERPOLATION\n#define SUISEN_POLYNOMIAL_INTERPOLATION\n\
    \n#include \"library/polynomial/fps.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    FPS<mint> polynomial_interpolation(const std::vector<mint>&\
    \ xs, const std::vector<mint>& ys) {\n        assert(xs.size() == ys.size());\n\
    \        int n = xs.size();\n        std::vector<FPS<mint>> seg(2 * n), g(2 *\
    \ n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint>{ -xs[i], 1 };\n\
    \        for (int i = n - 1; i > 0; --i) {\n            seg[i] = seg[i * 2] *\
    \ seg[i * 2 + 1];\n        }\n        g[1] = std::move(seg[1].diff_inplace());\n\
    \        for (int i = 1; i < n; ++i) {\n            int l = 2 * i, r = l + 1;\n\
    \            g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];\n        }\n        for\
    \ (int i = 0; i < n; ++i) g[n + i] = FPS<mint>{ ys[i] / g[n + i][0] };\n     \
    \   for (int i = n - 1; i > 0; --i) {\n            int l = 2 * i, r = l + 1;\n\
    \            g[i] = g[l] * seg[r] + g[r] * seg[l];\n        }\n        return\
    \ g[1];\n    }\n\n} // namespace suisen\n\n\n#endif // SUISEN_POLYNOMIAL_INTERPOLATION\n"
  dependsOn:
  - library/polynomial/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/polynomial/polynomial_interpolation.hpp
  requiredBy: []
  timestamp: '2022-05-14 03:01:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
documentation_of: library/polynomial/polynomial_interpolation.hpp
layout: document
title: "\u88DC\u9593\u591A\u9805\u5F0F"
---
## 補間多項式

$\mathbb{F} _ p$ 上の高々 $N - 1$ 次の多項式 $f(x)$ について、次の情報が分かっている。

$$
f(x _ i) = y _ i\ (i = 0, \ldots, N - 1).
$$

$x _ i$ が全て互いに相異なるとき、$f$ は存在して一意であり、次のような表示を持つ。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (x - x _ j)}{\prod _ {j \neq i} (x _ i - x _ j)}.
$$

この $f$ を __補間多項式__ と呼ぶ。

$x _ i$ および $y _ i$ に対して定まる補間多項式 $f$ を計算する。

## アルゴリズム

多項式 $l$ を以下で定義する。

$$l(x) = \prod _ {i = 0} ^ {N - 1} (x - x _ i)$$

このとき、$\displaystyle l'(x _ i) = \prod _ {j \neq i} (x _ i - x _ j)$ が成り立つ。

$l$ はマージテクおよび高速フーリエ変換による畳み込みなどを用いて $\Theta(N (\log N) ^ 2)$ 時間で計算でき、$l$ に対して $l'$ は $\Theta(N)$ 時間で計算できる。

各 $x _ 0, \ldots, x _ {N - 1}$ に対する $l'(x _ i)$ を求めるのは Multipoint Evaluation なので $\Theta(N (\log N) ^ 2)$ 時間で計算できる。

$l'$ を用いれば、補間多項式は次のように書ける。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {j \neq i} (x - x _ j).
$$

ここで、$0\leq l\lt r\leq N$ を満たす整数 $l, r$ に対して、多項式 $f _ {l, r}$ を以下で定義する。求めたいのは $f _ {0, N}(x)$ である。

$$
f _ {l, r} (x) = \sum _ {i = l} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {\scriptstyle l \leq j \lt r,j\neq i} (x - x _ j).
$$

$l\leq m\leq r$ を満たす整数 $m$ に対して、次が成り立つ。

$$\begin{aligned}
f _ {l, r} (x)
&= \sum _ {i = l} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {l \leq j \lt r,j\neq i} (x - x _ j) \\
&= \sum _ {i = l} ^ {m - 1} \dfrac{y _ i}{l'(x _ i)} \Biggl(\prod _ {l \leq j \lt m,j\neq i} (x - x _ j)\Biggr)\Biggl(\prod _ {m \leq j \lt r} (x - x _ j)\Biggr) \\
&+ \sum _ {i = m} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \Biggl(\prod _ {l \leq j \lt m} (x - x _ j)\Biggr)\Biggl(\prod _ {m \leq j \lt r,j\neq i} (x - x _ j)\Biggr) \\
&= \Biggl(\prod _ {m \leq j \lt r} (x - x _ j)\Biggr) f _ {l, m}(x) + \Biggl(\prod _ {l \leq j \lt m} (x - x _ j)\Biggr) f _ {m, r}(x)
\end{aligned}$$

従って、$f _ {l, r}(x)$ や $\prod _ {i = l} ^ {r - 1} (x - x _ i)$ を $m=\left\lfloor\dfrac{l+r}{2}\right\rfloor$ として再帰的に計算すると、$f _ {0, N}(x)$ の計算に掛かる時間計算量 $T(N)$ は次を満たす。

$$
T(N) = \begin{cases} 2T(N / 2) + \Theta(N \log N) & \text{if}\ N \gt 1 \\ O(1) & \text{otherwise} \end{cases}.
$$

即ち、$T(N) = \Theta(N (\log N) ^ 2)$ である (★)。

<details>
<summary> (★) の補足 </summary>

http://homepages.math.uic.edu/~leon/cs-mcs401-s08/handouts/extended_master_theorem.pdf の $(3')$ で $a = b = 2, \alpha = 1$ とすることで、$T(N) = \Theta(N (\log N) ^ 2)$ を得る。(補足終)

</details>

以上より、$\Theta(N (\log N) ^ 2)$ 時間で補間多項式を計算することが出来た。なお、$\prod _ {i = l} ^ {r - 1} (x - x _ i)$ については、Multipoint Evaluation で計算したものを再利用すると定数倍高速化が可能である。
