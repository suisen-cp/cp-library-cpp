---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':warning:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/multi_point_eval.hpp\"\n\n\n\n#line 1 \"library/math/fps.hpp\"\
    \n\n\n\n#include <cassert>\n#include <atcoder/convolution>\n\n#include <library/math/inv_mods.hpp>\n\
    \nnamespace suisen {\ntemplate <typename mint>\nclass FPS : public std::vector<mint>\
    \ {\n    public:\n        using std::vector<mint>::vector;\n\n        FPS(const\
    \ std::initializer_list<mint> l) : std::vector<mint>::vector(l) {}\n\n       \
    \ inline FPS& operator=(const std::vector<mint> &&f) & noexcept {\n          \
    \  std::vector<mint>::operator=(std::move(f));\n            return *this;\n  \
    \      }\n        inline FPS& operator=(const std::vector<mint>  &f) & {\n   \
    \         std::vector<mint>::operator=(f);\n            return *this;\n      \
    \  }\n\n        inline const mint  operator[](int n) const noexcept { return n\
    \ <= deg() ? unsafe_get(n) : 0; }\n        inline       mint& operator[](int n)\
    \       noexcept { ensure_deg(n); return unsafe_get(n); }\n\n        inline int\
    \ size() const noexcept { return std::vector<mint>::size(); }\n        inline\
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
    \      inline FPS& operator*=(const FPS  &g) { return *this = atcoder::convolution(*this,\
    \ g); }\n        inline FPS& operator*=(      FPS &&g) { return *this = atcoder::convolution(std::move(*this),\
    \ std::move(g)); }\n        inline FPS& operator*=(const mint x) {\n         \
    \   for (auto &e : *this) e *= x;\n            return *this;\n        }\n    \
    \    FPS& operator/=(FPS &&g) {\n            const int fd = normalize(), gd =\
    \ g.normalize();\n            assert(gd >= 0);\n            if (fd < gd) { this->clear();\
    \ return *this; }\n            if (gd == 0) return *this *= g.unsafe_get(0).inv();\n\
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
    \ - 1);\n        }\n        inline FPS& operator/=(const FPS &g) { return *this\
    \ /= FPS(g); }\n        inline FPS& operator%=(const FPS &g) { return *this %=\
    \ FPS(g); }\n        FPS& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, 0);\n            return *this;\n        }\n        FPS& operator>>=(const\
    \ int shamt) {\n            if (shamt > size()) this->clear();\n            else\
    \ this->erase(this->begin(), this->begin() + shamt);\n            return *this;\n\
    \        }\n\n        inline FPS operator+(FPS &&g) const { return FPS(*this)\
    \ += std::move(g); }\n        inline FPS operator-(FPS &&g) const { return FPS(*this)\
    \ -= std::move(g); }\n        inline FPS operator*(FPS &&g) const { return atcoder::convolution(std::move(*this),\
    \ std::move(g)); }\n        inline FPS operator/(FPS &&g) const { return FPS(*this)\
    \ /= std::move(g); }\n        inline FPS operator%(FPS &&g) const { return FPS(*this)\
    \ %= std::move(g); }\n        inline FPS operator+(const FPS &g) const { return\
    \ FPS(*this) += g; }\n        inline FPS operator+(const mint x) const { return\
    \ FPS(*this) += x; }\n        inline FPS operator-(const FPS &g) const { return\
    \ FPS(*this) -= g; }\n        inline FPS operator-(const mint x) const { return\
    \ FPS(*this) -= x; }\n        inline FPS operator*(const FPS &g) const { return\
    \ atcoder::convolution(*this, g); }\n        inline FPS operator*(const mint x)\
    \ const { return FPS(*this) *= x; }\n        inline FPS operator/(const FPS &g)\
    \ const { return FPS(*this) /= g; }\n        inline FPS operator%(const FPS &g)\
    \ const { return FPS(*this) %= g; }\n        inline friend FPS operator*(const\
    \ mint x, const FPS  &f) { return f * x; }\n        inline friend FPS operator*(const\
    \ mint x,       FPS &&f) { return f *= x; }\n        inline FPS operator<<(const\
    \ int shamt) { return FPS(*this) <<= shamt; }\n        inline FPS operator>>(const\
    \ int shamt) { return FPS(*this) >>= shamt; }\n\n        FPS& diff_inplace() {\n\
    \            if (this->size() == 0) return *this;\n            for (int i = 1;\
    \ i <= deg(); ++i) unsafe_get(i - 1) = unsafe_get(i) * i;\n            this->pop_back();\n\
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
    \ invs;\n        inline void ensure_deg(int d) { if (deg() < d) this->resize(d\
    \ + 1, 0); }\n        inline const mint& unsafe_get(int i) const { return std::vector<mint>::operator[](i);\
    \ }\n        inline       mint& unsafe_get(int i)       { return std::vector<mint>::operator[](i);\
    \ }\n\n        std::pair<FPS, FPS&> naive_div_inplace(FPS &&g, const int gd) {\n\
    \            const int k = deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n\
    \            FPS q(k + 1);\n            for (int i = k; i >= 0; --i) {\n     \
    \           mint div = this->unsafe_get(i + gd) * head_inv;\n                q.unsafe_get(i)\
    \ = div;\n                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j)\
    \ -= div * g.unsafe_get(j);\n            }\n            return {q, pre_inplace(gd\
    \ - 1)};\n        }\n};\n} // namespace suisen\n\n\n#line 5 \"library/math/multi_point_eval.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nstd::vector<mint> multi_point_eval(const\
    \ FPS<mint> &f, const std::vector<mint> &xs) {\n    int m = xs.size();\n    int\
    \ k = 1;\n    while (k < m) k <<= 1;\n    std::vector<FPS<mint>> seg(2 * k);\n\
    \    for (int i = 0; i < m; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};\n    for\
    \ (int i = m; i < k; ++i) seg[k + i] = FPS<mint> {1};\n    for (int i = k - 1;\
    \ i> 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n    seg[1] = f % seg[1];\n\
    \    for (int i = 2; i < k + m; ++i) seg[i] = seg[i / 2] % seg[i];\n    std::vector<mint>\
    \ ys(m);\n    for (int i = 0; i < m; ++i) ys[i] = seg[k + i][0];\n    return ys;\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MULTI_POINT_EVALUATION\n#define SUISEN_MULTI_POINT_EVALUATION\n\
    \n#include \"library/math/fps.hpp\"\n\nnamespace suisen {\ntemplate <typename\
    \ mint>\nstd::vector<mint> multi_point_eval(const FPS<mint> &f, const std::vector<mint>\
    \ &xs) {\n    int m = xs.size();\n    int k = 1;\n    while (k < m) k <<= 1;\n\
    \    std::vector<FPS<mint>> seg(2 * k);\n    for (int i = 0; i < m; ++i) seg[k\
    \ + i] = FPS<mint> {-xs[i], 1};\n    for (int i = m; i < k; ++i) seg[k + i] =\
    \ FPS<mint> {1};\n    for (int i = k - 1; i> 0; --i) seg[i] = seg[i * 2] * seg[i\
    \ * 2 + 1];\n    seg[1] = f % seg[1];\n    for (int i = 2; i < k + m; ++i) seg[i]\
    \ = seg[i / 2] % seg[i];\n    std::vector<mint> ys(m);\n    for (int i = 0; i\
    \ < m; ++i) ys[i] = seg[k + i][0];\n    return ys;\n}\n} // namespace suisen\n\
    \n#endif // SUISEN_MULTI_POINT_EVALUATION"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/math/multi_point_eval.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/multi_point_eval.hpp
layout: document
redirect_from:
- /library/library/math/multi_point_eval.hpp
- /library/library/math/multi_point_eval.hpp.html
title: library/math/multi_point_eval.hpp
---