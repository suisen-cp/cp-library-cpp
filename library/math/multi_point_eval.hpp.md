---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/polynomial_eval_multipoint_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
  - icon: ':question:'
    path: library/math/lagrange_interpolation.hpp
    title: library/math/lagrange_interpolation.hpp
  - icon: ':question:'
    path: library/math/product_of_differences.hpp
    title: library/math/product_of_differences.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/math/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':x:'
    path: test/src/math/lagrange_interpolation/dummy.test.cpp
    title: test/src/math/lagrange_interpolation/dummy.test.cpp
  - icon: ':x:'
    path: test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
    title: test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
  - icon: ':x:'
    path: test/src/math/product_of_differences/yuki1938.test.cpp
    title: test/src/math/product_of_differences/yuki1938.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/multi_point_eval.hpp\"\n\n\n\n#line 1 \"library/math/fps.hpp\"\
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
    \  {\n    return a.inv(a.deg());\n}\n\n\n#line 5 \"library/math/multi_point_eval.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    std::vector<mint> multi_point_eval(const\
    \ FPS<mint>& f, const std::vector<mint>& xs) {\n        int n = xs.size();\n \
    \       std::vector<FPS<mint>> seg(2 * n);\n        for (int i = 0; i < n; ++i)\
    \ seg[n + i] = FPS<mint>{ -xs[i], 1 };\n        for (int i = n - 1; i > 0; --i)\
    \ seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = f % seg[1];\n      \
    \  for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n        std::vector<mint>\
    \ ys(n);\n        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n       \
    \ return ys;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MULTI_POINT_EVALUATION\n#define SUISEN_MULTI_POINT_EVALUATION\n\
    \n#include \"library/math/fps.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ mint>\n    std::vector<mint> multi_point_eval(const FPS<mint>& f, const std::vector<mint>&\
    \ xs) {\n        int n = xs.size();\n        std::vector<FPS<mint>> seg(2 * n);\n\
    \        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint>{ -xs[i], 1 };\n  \
    \      for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n\
    \        seg[1] = f % seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i]\
    \ = seg[i / 2] % seg[i];\n        std::vector<mint> ys(n);\n        for (int i\
    \ = 0; i < n; ++i) ys[i] = seg[n + i][0];\n        return ys;\n    }\n} // namespace\
    \ suisen\n\n#endif // SUISEN_MULTI_POINT_EVALUATION"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/math/multi_point_eval.hpp
  requiredBy:
  - library/math/lagrange_interpolation.hpp
  - library/math/product_of_differences.hpp
  - library/convolution/polynomial_eval_multipoint_eval.hpp
  timestamp: '2022-05-14 02:35:26+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
  - test/src/math/product_of_differences/yuki1938.test.cpp
  - test/src/math/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/math/lagrange_interpolation/dummy.test.cpp
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
documentation_of: library/math/multi_point_eval.hpp
layout: document
title: Multi Point Evaluation
---
## Multi Point Evaluation