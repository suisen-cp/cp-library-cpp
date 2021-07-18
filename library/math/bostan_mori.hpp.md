---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/bostan_mori.hpp\"\n\n\n\n#line 1 \"library/math/fps.hpp\"\
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
    };\n\n} // namespace suisen\n\n\n#line 5 \"library/math/bostan_mori.hpp\"\n\n\
    namespace suisen {\ntemplate <typename mint>\nmint bostan_mori(const FPS<mint>\
    \ &P, const FPS<mint> &Q, const long long n) {\n    if (n == 0) return P[0];\n\
    \    FPS mQ(Q);\n    for (int i = 0; i <= Q.deg(); i += 2) mQ[i] = -mQ[i];\n \
    \   P *= mQ, Q *= mQ;\n    FPS nP((P.deg() + 1) / 2), nQ((Q.deg() + 1) / 2);\n\
    \    for (int i = 0    ; i <= Q.deg(); i += 2) nQ[i >> 1] = Q[i];\n    for (int\
    \ i = n & 1; i <= P.deg(); i += 2) nP[i >> 1] = P[i];\n    return bostan_mori(nP,\
    \ nQ, n / 2);\n}\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BOSTAN_MORI\n#define SUISEN_BOSTAN_MORI\n\n#include \"library/math/fps.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nmint bostan_mori(const FPS<mint>\
    \ &P, const FPS<mint> &Q, const long long n) {\n    if (n == 0) return P[0];\n\
    \    FPS mQ(Q);\n    for (int i = 0; i <= Q.deg(); i += 2) mQ[i] = -mQ[i];\n \
    \   P *= mQ, Q *= mQ;\n    FPS nP((P.deg() + 1) / 2), nQ((Q.deg() + 1) / 2);\n\
    \    for (int i = 0    ; i <= Q.deg(); i += 2) nQ[i >> 1] = Q[i];\n    for (int\
    \ i = n & 1; i <= P.deg(); i += 2) nP[i >> 1] = P[i];\n    return bostan_mori(nP,\
    \ nQ, n / 2);\n}\n} // namespace suisen\n\n#endif // SUISEN_BOSTAN_MORI"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/math/bostan_mori.hpp
  requiredBy: []
  timestamp: '2021-07-18 18:22:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/bostan_mori.hpp
layout: document
redirect_from:
- /library/library/math/bostan_mori.hpp
- /library/library/math/bostan_mori.hpp.html
title: library/math/bostan_mori.hpp
---
