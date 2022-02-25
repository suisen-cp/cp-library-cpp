---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: Factorial
  - icon: ':heavy_check_mark:'
    path: library/math/fps.hpp
    title: Fps
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: Inv Mods
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bernoulli_number
    links:
    - https://judge.yosupo.jp/problem/bernoulli_number
  bundledCode: "#line 1 \"test/src/math/common_sequences/bernoulli_number.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bernoulli_number\"\n\n#include\
    \ <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\n\
    #line 1 \"library/math/common_sequences.hpp\"\n\n\n\n#line 1 \"library/math/fps.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#line 7 \"library/math/fps.hpp\"\
    \n\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace\
    \ suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n        inv_mods()\
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
    \ max_deg); }\n\n    private:\n        static inv_mods<mint> invs;\n        static\
    \ convolution_t<mint> mult;\n        inline void ensure_deg(int d) { if (deg()\
    \ < d) this->resize(d + 1, 0); }\n        inline const mint& unsafe_get(int i)\
    \ const { return std::vector<mint>::operator[](i); }\n        inline       mint&\
    \ unsafe_get(int i)       { return std::vector<mint>::operator[](i); }\n\n   \
    \     std::pair<FPS, FPS&> naive_div_inplace(FPS &&g, const int gd) {\n      \
    \      const int k = deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n\
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
    \  {\n    return a.inv(a.deg());\n}\n\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\ntemplate\
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
    \n\n#line 6 \"library/math/common_sequences.hpp\"\n\nnamespace suisen {\n/**\n\
    \ * return:\n *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k (unsigned)\n\
    \ * constraints:\n *   0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1_reversed(int n) {\n    factorial<mint> fac(n);\n    int l =\
    \ 0;\n    while ((n >> l) != 0) ++l;\n    FPS<mint> a {1};\n    int m = 0;\n \
    \   while (l --> 0) {\n        FPS<mint> f(m + 1), g(m + 1);\n        mint powm\
    \ = 1;\n        for (int i = 0; i <= m; ++i, powm *= m) {\n            f[i] =\
    \ powm * fac.inv(i);\n            g[i] = a[i] * fac(m - i);\n        }\n     \
    \   f *= g, f.pre_inplace(m);\n        for (int i = 0; i <= m; ++i) f[i] *= fac.inv(m\
    \ - i);\n        a *= f, m *= 2, a.pre_inplace(m);\n        if ((n >> l) & 1)\
    \ {\n            a.push_back(0);\n            for (int i = m; i > 0; --i) a[i]\
    \ += m * a[i - 1];\n            ++m;\n        }\n    }\n    return a;\n}\ntemplate\
    \ <typename mint>\nstd::vector<mint> stirling_number1(int n) {\n    auto a(stirling_number1_reversed<mint>(n));\n\
    \    std::reverse(a.begin(), a.end());\n    return a;\n}\n/**\n * return:\n *\
    \   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling\
    \ number of the first kind (unsigned).\n * constraints:\n * - 0 <= n <= 10^18\n\
    \ * - 0 <= k <= 5000\n * - k < mod\n */\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1_reversed(const long long n, const int k) {\n    inv_mods<mint>\
    \ invs(k + 1);\n    std::vector<mint> a(k + 1, 0);\n    a[0] = 1;\n    int l =\
    \ 0;\n    while (n >> l) ++l;\n    mint m = 0;\n    while (l --> 0) {\n      \
    \  std::vector<mint> b(k + 1, 0);\n        for (int j = 0; j <= k; ++j) {\n  \
    \          mint tmp = 1;\n            for (int i = j; i <= k; ++i) {\n       \
    \         b[i] += a[j] * tmp;\n                tmp *= (m - i) * invs[i - j + 1]\
    \ * m;\n            }\n        }\n        for (int i = k + 1; i --> 0;) {\n  \
    \          mint sum = 0;\n            for (int j = 0; j <= i; ++j) sum += a[j]\
    \ * b[i - j];\n            a[i] = sum;\n        }\n        m *= 2;\n        if\
    \ ((n >> l) & 1) {\n            for (int i = k; i > 0; --i) a[i] += m * a[i -\
    \ 1];\n            ++m;\n        }\n    }\n    return a;\n}\n\n/**\n * return:\n\
    \ *   vector<mint> v s.t. v[i] = S2[n,i] for i=0,...,k\n * constraints:\n *  \
    \ 0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint> stirling_number2(int\
    \ n) {\n    factorial<mint> fac(n);\n    FPS<mint> a(n + 1), b(n + 1);\n    for\
    \ (int i = 0; i <= n; ++i) {\n        a[i] = mint(i).pow(n) * fac.inv(i);\n  \
    \      b[i] = i & 1 ? -fac.inv(i) : fac.inv(i);\n    }\n    a *= b, a.pre_inplace(n);\n\
    \    return a;\n}\n\n/**\n * return:\n *   vector<mint> v s.t. v[i] = B_i = \u03A3\
    _j S2[i,j] for i=0,...,n\n * constraints:\n *   0 <= n <= 10^6\n * note:\n * \
    \  EGF of B is e^(e^x-1)\n */\ntemplate <typename mint>\nstd::vector<mint> bell_number(int\
    \ n) {\n    factorial<mint> fac(n);\n    FPS<mint> f(n + 1);\n    for (int i =\
    \ 1; i <= n; ++i) f[i] = fac.inv(i);\n    f.exp_inplace(n);\n    for (int i =\
    \ 0; i <= n; ++i) f[i] *= fac.fac(i);\n    return f;\n}\n\ntemplate <typename\
    \ mint>\nstd::vector<mint> bernoulli_number(int n) {\n    factorial<mint> fac(n);\n\
    \    FPS<mint> a(n + 1);\n    for (int i = 0; i <= n; ++i) a[i] = fac.inv(i +\
    \ 1);\n    a.inv_inplace(n), a.resize(n + 1);\n    for (int i = 2; i <= n; ++i)\
    \ a[i] *= fac(i);\n    return a;\n}\n\ntemplate <typename mint>\nstd::vector<mint>\
    \ partition_number(int n) {\n    FPS<mint> inv(n + 1);\n    inv[0] = 1;\n    for\
    \ (int i = 1, k = 1; k <= n; k += 3 * i + 1, i++) {\n        if (i & 1) --inv[k];\n\
    \        else ++inv[k];\n    }\n    for (int i = 1, k = 2; k <= n; k += 3 * i\
    \ + 2, i++) {\n        if (i & 1) --inv[k];\n        else ++inv[k];\n    }\n \
    \   inv.inv_inplace(n), inv.resize(n + 1);\n    return inv;\n}\n\ntemplate <typename\
    \ mint>\nstd::vector<mint> montmort_number(int n) {\n    std::vector<mint> res\
    \ { 1, 0 };\n    for (int i = 2; i <= n; ++i) res.push_back((i - 1) * (res[i -\
    \ 1] + res[i - 2]));\n    res.resize(n + 1);\n    return res;\n}\n} // namespace\
    \ suisen\n\n\n#line 9 \"test/src/math/common_sequences/bernoulli_number.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nint main() {\n    suisen::FPS<mint>::set_multiplication([](const\
    \ auto &a, const auto &b) { return atcoder::convolution(a, b); });\n\n    int\
    \ n;\n    std::cin >> n;\n    auto f = suisen::bernoulli_number<mint>(n);\n  \
    \  for (int i = 0; i <= n; ++i) {\n        std::cout << f[i].val() << \" \\n\"\
    [i == n];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bernoulli_number\"\n\n\
    #include <iostream>\n\n#include <atcoder/modint>\n#include <atcoder/convolution>\n\
    \n#include \"library/math/common_sequences.hpp\"\n\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    suisen::FPS<mint>::set_multiplication([](const auto &a, const\
    \ auto &b) { return atcoder::convolution(a, b); });\n\n    int n;\n    std::cin\
    \ >> n;\n    auto f = suisen::bernoulli_number<mint>(n);\n    for (int i = 0;\
    \ i <= n; ++i) {\n        std::cout << f[i].val() << \" \\n\"[i == n];\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - library/math/common_sequences.hpp
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  isVerificationFile: true
  path: test/src/math/common_sequences/bernoulli_number.test.cpp
  requiredBy: []
  timestamp: '2022-02-26 02:46:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/common_sequences/bernoulli_number.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/common_sequences/bernoulli_number.test.cpp
- /verify/test/src/math/common_sequences/bernoulli_number.test.cpp.html
title: test/src/math/common_sequences/bernoulli_number.test.cpp
---
