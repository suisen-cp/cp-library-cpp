---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  - icon: ':question:'
    path: library/math/multi_point_eval.hpp
    title: library/math/multi_point_eval.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/apply_polynomial_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/apply_polynomial_multipoint_eval/nim_counting.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/apply_polynomial_multipoint_eval.hpp\"\
    \n\n\n\n#line 1 \"library/math/multi_point_eval.hpp\"\n\n\n\n#line 1 \"library/math/fps.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n\n#line\
    \ 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen\
    \ {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n        inv_mods()\
    \ {}\n        inv_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return invs[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = invs.size();\n    \
    \        if (sz < 2) invs = {0, 1}, sz = 2;\n            if (sz < n + 1) {\n \
    \               invs.resize(n + 1);\n                for (int i = sz; i <= n;\
    \ ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n            }\n       \
    \ }\n    private:\n        static std::vector<mint> invs;\n        static constexpr\
    \ int mod = mint::mod();\n};\ntemplate <typename mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n\
    }\n\n\n#line 9 \"library/math/fps.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ mint>\nusing convolution_t = std::vector<mint> (*)(const std::vector<mint> &,\
    \ const std::vector<mint> &);\n\ntemplate <typename mint>\nclass FPS : public\
    \ std::vector<mint> {\n    public:\n        using std::vector<mint>::vector;\n\
    \n        FPS(const std::initializer_list<mint> l) : std::vector<mint>::vector(l)\
    \ {}\n\n        static void set_multiplication(convolution_t<mint> multiplication)\
    \ {\n            FPS<mint>::mult = multiplication;\n        }\n\n        inline\
    \ FPS& operator=(const std::vector<mint> &&f) & noexcept {\n            std::vector<mint>::operator=(std::move(f));\n\
    \            return *this;\n        }\n        inline FPS& operator=(const std::vector<mint>\
    \  &f) & {\n            std::vector<mint>::operator=(f);\n            return *this;\n\
    \        }\n\n        inline const mint  operator[](int n) const noexcept { return\
    \ n <= deg() ? unsafe_get(n) : 0; }\n        inline       mint& operator[](int\
    \ n)       noexcept { ensure_deg(n); return unsafe_get(n); }\n\n        inline\
    \ int size() const noexcept { return std::vector<mint>::size(); }\n        inline\
    \ int deg()  const noexcept { return size() - 1; }\n        inline int normalize()\
    \ {\n            while (this->size() and this->back() == 0) this->pop_back();\n\
    \            return deg();\n        }\n        inline FPS& pre_inplace(int max_deg)\
    \ noexcept {\n            if (deg() > max_deg) this->resize(std::max(0, max_deg\
    \ + 1));\n            return *this;\n        }\n        inline FPS pre(int max_deg)\
    \ const noexcept { return FPS(*this).pre_inplace(max_deg); }\n\n        inline\
    \ FPS operator+() const { return FPS(*this); }\n        FPS operator-() const\
    \ {\n            FPS f(*this);\n            for (auto &e : f) e = mint::mod()\
    \ - e;\n            return f;\n        }\n        inline FPS& operator++() { ++(*this)[0];\
    \ return *this; }\n        inline FPS& operator--() { --(*this)[0]; return *this;\
    \ }\n        inline FPS& operator+=(const mint x) { (*this)[0] += x; return *this;\
    \ }\n        inline FPS& operator-=(const mint x) { (*this)[0] -= x; return *this;\
    \ }\n        FPS& operator+=(const FPS &g) {\n            ensure_deg(g.deg());\n\
    \            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);\n\
    \            return *this;\n        }\n        FPS& operator-=(const FPS &g) {\n\
    \            ensure_deg(g.deg());\n            for (int i = 0; i <= g.deg(); ++i)\
    \ unsafe_get(i) -= g.unsafe_get(i);\n            return *this;\n        }\n  \
    \      inline FPS& operator*=(const FPS  &g) { return *this = FPS<mint>::mult(*this,\
    \ g); }\n        inline FPS& operator*=(      FPS &&g) { return *this = FPS<mint>::mult(*this,\
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
    \ { return FPS(*this) >>= shamt; }\n\n        FPS& diff_inplace() {\n        \
    \    if (this->size() == 0) return *this;\n            for (int i = 1; i <= deg();\
    \ ++i) unsafe_get(i - 1) = unsafe_get(i) * i;\n            this->pop_back();\n\
    \            return *this;\n        }\n        FPS& intg_inplace() {\n       \
    \     int d = deg();\n            ensure_deg(d + 1);\n            for (int i =\
    \ d; i >= 0; --i) unsafe_get(i + 1) = unsafe_get(i) * invs[i + 1];\n         \
    \   unsafe_get(0) = 0;\n            return *this;\n        }\n        FPS& inv_inplace(const\
    \ int max_deg) {\n            FPS res { unsafe_get(0).inv() };\n            for\
    \ (int k = 1; k <= max_deg; k *= 2) {\n                FPS tmp(this->pre(k * 2)\
    \ * (res * res));\n                res *= 2, res -= tmp.pre_inplace(2 * k);\n\
    \            }\n            return *this = std::move(res), pre_inplace(max_deg);\n\
    \        }\n        FPS& log_inplace(const int max_deg) {\n            FPS f_inv\
    \ = inv(max_deg);\n            diff_inplace(), *this *= f_inv, pre_inplace(max_deg\
    \ - 1), intg_inplace();\n            return *this;\n        }\n        FPS& exp_inplace(const\
    \ int max_deg) {\n            FPS res {1};\n            for (int k = 1; k <= max_deg;\
    \ k *= 2) res *= ++(pre(k * 2) - res.log(k * 2)), res.pre_inplace(k * 2);\n  \
    \          return *this = std::move(res), pre_inplace(max_deg);\n        }\n \
    \       FPS& pow_inplace(const long long k, const int max_deg) {\n           \
    \ int tlz = 0;\n            while (tlz <= deg() and unsafe_get(tlz) == 0) ++tlz;\n\
    \            if (tlz * k > max_deg) { this->clear(); return *this; }\n       \
    \     *this >>= tlz;\n            mint base = (*this)[0];\n            *this *=\
    \ base.inv(), log_inplace(max_deg), *this *= k, exp_inplace(max_deg), *this *=\
    \ base.pow(k);\n            return *this <<= tlz * k, pre_inplace(max_deg);\n\
    \        }\n        inline FPS diff() const { return FPS(*this).diff_inplace();\
    \ }\n        inline FPS intg() const { return FPS(*this).intg_inplace(); }\n \
    \       inline FPS inv(const int max_deg) const { return FPS(*this).inv_inplace(max_deg);\
    \ }\n        inline FPS log(const int max_deg) const { return FPS(*this).log_inplace(max_deg);\
    \ }\n        inline FPS exp(const int max_deg) const { return FPS(*this).exp_inplace(max_deg);\
    \ }\n        inline FPS pow(const long long k, const int max_deg) const { return\
    \ FPS(*this).pow_inplace(k, max_deg); }\n\n    private:\n        static inv_mods<mint>\
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
    };\n\n} // namespace suisen\n\n\n#line 5 \"library/math/multi_point_eval.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nstd::vector<mint> multi_point_eval(const\
    \ FPS<mint> &f, const std::vector<mint> &xs) {\n    int m = xs.size();\n    int\
    \ k = 1;\n    while (k < m) k <<= 1;\n    std::vector<FPS<mint>> seg(2 * k);\n\
    \    for (int i = 0; i < m; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};\n    for\
    \ (int i = m; i < k; ++i) seg[k + i] = FPS<mint> {1};\n    for (int i = k - 1;\
    \ i> 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n    seg[1] = f % seg[1];\n\
    \    for (int i = 2; i < k + m; ++i) seg[i] = seg[i / 2] % seg[i];\n    std::vector<mint>\
    \ ys(m);\n    for (int i = 0; i < m; ++i) ys[i] = seg[k + i][0];\n    return ys;\n\
    }\n} // namespace suisen\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\
    \n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\n\
    template <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 6 \"\
    library/convolution/apply_polynomial_multipoint_eval.hpp\"\n\nnamespace suisen\
    \ {\n\ntemplate <typename mint, template <typename T> class Transform>\nstd::vector<mint>\
    \ apply_polynomial(std::vector<mint> &&a, const FPS<mint> &f) {\n    Transform<mint>::transform(a);\n\
    \    a = multi_point_eval(f, a);\n    Transform<mint>::inverse_transform(a);\n\
    \    return a;\n}\n\ntemplate <typename mint, template <typename T> class Transform>\n\
    std::vector<mint> apply_polynomial(const std::vector<mint> &a, const FPS<mint>\
    \ &f) {\n    return apply_polynomial<mint, Transform>(std::vector<mint>(a), f);\n\
    }\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n#define SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n\
    \n#include \"library/math/multi_point_eval.hpp\"\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename mint, template <typename T> class\
    \ Transform>\nstd::vector<mint> apply_polynomial(std::vector<mint> &&a, const\
    \ FPS<mint> &f) {\n    Transform<mint>::transform(a);\n    a = multi_point_eval(f,\
    \ a);\n    Transform<mint>::inverse_transform(a);\n    return a;\n}\n\ntemplate\
    \ <typename mint, template <typename T> class Transform>\nstd::vector<mint> apply_polynomial(const\
    \ std::vector<mint> &a, const FPS<mint> &f) {\n    return apply_polynomial<mint,\
    \ Transform>(std::vector<mint>(a), f);\n}\n\n} // namespace suisen\n\n#endif //\
    \ SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n"
  dependsOn:
  - library/math/multi_point_eval.hpp
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/convolution/apply_polynomial_multipoint_eval.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/convolution/apply_polynomial_multipoint_eval/nim_counting.test.cpp
documentation_of: library/convolution/apply_polynomial_multipoint_eval.hpp
layout: document
title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\u306E\
  \u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
---

### apply_polynomial

- シグネチャ

  ```cpp
  template <typename mint, template <typename T> class Transform>
  std::vector<mint> apply_polynomial(std::vector<mint> &&a, const FPS<mint> &f) // (1)

  template <typename mint, template <typename T> class Transform>
  std::vector<mint> apply_polynomial(const std::vector<mint> &a, const FPS<mint> &f) // (2)
  ```

- 概要

  列 $A$ を変数に持つ多項式 $\displaystyle f(A)=\sum_{i=0}^{M-1} C_i \cdot A^i$ を評価します．ここで，$A^i$ はある畳み込み演算 $\ast$ に対して以下で定義されるものとします．

  $$ A^i = \underbrace{A \ast A \ast \cdots \ast A}_{i} $$

  また，$\ast$ に対してある正則な変換行列 $\mathcal{F}$ が存在して，任意の列 $X,Y$ に対して

  $$ \mathcal{F}[X] \odot \mathcal{F}[Y]=\mathcal{F}[X\ast Y]$$

  を満たす必要があります．ここで，$\odot$ は各点積をとる演算です．このとき，$f(A)$ は次のように計算されます．

  $$\begin{aligned}
  f(A)
  &=\mathcal{F}^{-1}\left[\sum_{i=0}^{M-1}C_i\cdot \left(\underbrace{\mathcal{F}[A]\odot\cdots\odot\mathcal{F}[A]}_{i}\right)\right]\\
  &=\mathcal{F}^{-1}\left[\begin{pmatrix}
  f(\mathcal{F}[A]_0)\\
  f(\mathcal{F}[A]_1)\\
  \vdots\\
  f(\mathcal{F}[A]_{\vert A\vert-1})\\
  \end{pmatrix}\right]
  \end{aligned}$$

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `Transform` の静的メンバ関数 `Transform<T>::transform` と `Transform<T>::inverse_transform` で，$f(\cdot)$ を評価するのが引数 `f` です．

  このライブラリでは $f(\cdot)$ たちの計算に多点評価のアルゴリズムを用いることで高速化を図ります．従って，引数として与える多項式 $f$ を形式的冪級数型 `FPS` に制限し，値型は `atcoder::modint` であることを想定しています．

- テンプレート引数

  - `mint`: 列の要素の型．`atcoder::modint` 型を想定しています．
  - `Transform`: 列に対して inplace に線形写像 $\mathcal{F}$ を施す `static` 関数 `Transform<T>::transform(std::vector<T>&)` およびその逆変換 $\mathcal{F}^{-1}$ を施す `static` 関数 `Transform<T>::inverse_transform(std::vector<T>&)` を持つクラス．

- 引数

  - `a`: 列 $A$
  - `f`: 多項式 $f$

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`Transform<T>::transform` の計算量を $\Theta(f(N))$, `Transform<T>::inverse_transform` の計算量を $\Theta(g(N))$ として，$\Theta(f(N)+g(N)+N (\log N) ^ 2)$ です．

