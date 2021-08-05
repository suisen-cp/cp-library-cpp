---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: library/transform/subset.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/subset_convolution.hpp\"\n\n\n\n#line\
    \ 1 \"library/math/fps.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
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
    std::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line 9 \"library/math/fps.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename mint>\nusing convolution_t = std::vector<mint>\
    \ (*)(const std::vector<mint> &, const std::vector<mint> &);\n\ntemplate <typename\
    \ mint>\nclass FPS : public std::vector<mint> {\n    public:\n        using std::vector<mint>::vector;\n\
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
    };\n\n} // namespace suisen\n\n\n#line 1 \"library/transform/subset.hpp\"\n\n\n\
    \n#line 6 \"library/transform/subset.hpp\"\n\nnamespace suisen {\n\nnamespace\
    \ subset_transform {\n\nnamespace internal {\n\ntemplate <typename T, typename\
    \ AssignOp>\nvoid transform(std::vector<T> &f, AssignOp assign_op) {\n    const\
    \ int n = f.size();\n    assert((-n & n) == n);\n    for (int k = 1; k < n; k\
    \ <<= 1) {\n        for (int l = 0; l < n; l += 2 * k) {\n            int m =\
    \ l + k;\n            for (int p = 0; p < k; ++p) assign_op(f[m + p], f[l + p]);\n\
    \        }\n    }\n}\n\n} // namespace internal\n\ntemplate <typename T, typename\
    \ AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign add_assign) {\n    internal::transform(f,\
    \ add_assign);\n}\ntemplate <typename T, typename SubAssign>\nvoid mobius(std::vector<T>\
    \ &f, SubAssign sub_assign) {\n    internal::transform(f, sub_assign);\n}\ntemplate\
    \ <typename T>\nvoid zeta(std::vector<T> &f) {\n    zeta(f, [](T &a, const T &b)\
    \ { a += b; });\n}\ntemplate <typename T>\nvoid mobius(std::vector<T> &f) {\n\
    \    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace subset_transform\n\
    \ntemplate <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign,\
    \ SubAssign sub_assign>\nstruct SubsetTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct SubsetTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        subset_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <typename T, template <typename> class Transform>\nstruct Convolution\
    \ {\n    static std::vector<T> convolution(std::vector<T> a, std::vector<T> b)\
    \ {\n        const int n = a.size();\n        assert(n == int(b.size()));\n  \
    \      Transform<T>::transform(a);\n        Transform<T>::transform(b);\n    \
    \    for (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        const int num = a.size();\n        if (num == 0) return {};\n\
    \        const int n = a[0].size();\n        for (auto &v : a) {\n           \
    \ assert(n == int(v.size()));\n            Transform<T>::transform(v);\n     \
    \   }\n        auto &res = a[0];\n        for (int i = 1; i < num; ++i) {\n  \
    \          for (int j = 0; j < n; ++j) res[j] *= a[i][j];\n        }\n       \
    \ Transform<T>::inverse_transform(res);\n        return res;\n    }\n};\n\n} //\
    \ namespace suisen\n\n\n\n#line 7 \"library/convolution/subset_convolution.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal {\n\ntemplate <typename T>\nstruct\
    \ SubsetTransformFPS : public SubsetTransform<T> {\n    static void transform(std::vector<T>\
    \ &a) {\n        SubsetTransform<T>::transform(a);\n        int lg = __builtin_ctz(a.size());\n\
    \        for (auto &v : a) v.pre_inplace(lg);\n    }\n};\n\ntemplate <typename\
    \ mint>\nauto to_polynomial(const std::vector<mint> &a) {\n    int n = a.size();\n\
    \    assert((-n & n) == n);\n    std::vector<FPS<mint>> fs(n);\n    for (int i\
    \ = 0; i < n; ++i) {\n        fs[i][__builtin_popcount(i)] = a[i];\n    }\n  \
    \  return fs;\n}\n\n} // namespace internal\n\ntemplate <typename mint>\nusing\
    \ SubsetConvolution = Convolution<FPS<mint>, internal::SubsetTransformFPS>;\n\n\
    template <typename mint, typename ...Args>\nstd::vector<mint> subset_convolution(Args\
    \ &&...args) {\n    auto fs = SubsetConvolution<mint>::convolution(internal::to_polynomial(args)...);\n\
    \    int n = fs.size();\n    std::vector<mint> res(n);\n    for (int i = 0; i\
    \ < n; ++i) {\n        res[i] = fs[i][__builtin_popcount(i)];\n    }\n    return\
    \ res;\n}\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_CONVOLUTION\n#define SUISEN_SUBSET_CONVOLUTION\n\n\
    #include \"library/math/fps.hpp\"\n#include \"library/transform/subset.hpp\"\n\
    #include \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n\nnamespace\
    \ internal {\n\ntemplate <typename T>\nstruct SubsetTransformFPS : public SubsetTransform<T>\
    \ {\n    static void transform(std::vector<T> &a) {\n        SubsetTransform<T>::transform(a);\n\
    \        int lg = __builtin_ctz(a.size());\n        for (auto &v : a) v.pre_inplace(lg);\n\
    \    }\n};\n\ntemplate <typename mint>\nauto to_polynomial(const std::vector<mint>\
    \ &a) {\n    int n = a.size();\n    assert((-n & n) == n);\n    std::vector<FPS<mint>>\
    \ fs(n);\n    for (int i = 0; i < n; ++i) {\n        fs[i][__builtin_popcount(i)]\
    \ = a[i];\n    }\n    return fs;\n}\n\n} // namespace internal\n\ntemplate <typename\
    \ mint>\nusing SubsetConvolution = Convolution<FPS<mint>, internal::SubsetTransformFPS>;\n\
    \ntemplate <typename mint, typename ...Args>\nstd::vector<mint> subset_convolution(Args\
    \ &&...args) {\n    auto fs = SubsetConvolution<mint>::convolution(internal::to_polynomial(args)...);\n\
    \    int n = fs.size();\n    std::vector<mint> res(n);\n    for (int i = 0; i\
    \ < n; ++i) {\n        res[i] = fs[i][__builtin_popcount(i)];\n    }\n    return\
    \ res;\n}\n\n} // namespace suisen\n\n#endif // SUISEN_SUBSET_CONVOLUTION\n"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/subset_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/convolution/subset_convolution.hpp
layout: document
title: Subset Convolution
---

### subset_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> subset_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の直和演算で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \sqcup j = k } A _ i \cdot B _ j $$

  ここで，$i\sqcup j=k$ は $i\And j=0$ かつ $i\mid j=k$ と等価です．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
     - $0\leq L\leq 20$
  2. - ある非負整数 $L$ が存在して $\vert\mathcal{A}^0\vert=\vert\mathcal{A}^1\vert=\cdots=2^L$ を満たす
     - $0\leq L\leq 20$

- 時間計算量

  1. $\Theta(N(\log N)^2)$，あるいは $\Theta(L^2\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N(\log N)^2)$，あるいは $\Theta(K\cdot L^2\cdot 2^L)$
