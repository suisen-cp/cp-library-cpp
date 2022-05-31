---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':heavy_check_mark:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc208/tasks/abc208_f
    links:
    - https://atcoder.jp/contests/abc208/tasks/abc208_f
  bundledCode: "#line 1 \"test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc208/tasks/abc208_f\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/polynomial/lagrange_interpolation.hpp\"\
    \n\n\n\n#line 1 \"library/math/product_of_differences.hpp\"\n\n\n\n#include <deque>\n\
    #line 1 \"library/polynomial/multi_point_eval.hpp\"\n\n\n\n#line 1 \"library/polynomial/fps.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#line 7 \"library/polynomial/fps.hpp\"\
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
    }\n\n\n#line 9 \"library/polynomial/fps.hpp\"\n\nnamespace suisen {\n\ntemplate\
    \ <typename mint>\nusing convolution_t = std::vector<mint> (*)(const std::vector<mint>\
    \ &, const std::vector<mint> &);\n\ntemplate <typename mint>\nclass FPS : public\
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
    \   if (max_deg <= 60) return *this = naive_exp(max_deg);\n            FPS res\
    \ {1};\n            for (int k = 1; k <= max_deg; k *= 2) res *= ++(pre(k * 2)\
    \ - res.log(k * 2)), res.pre_inplace(k * 2);\n            return *this = std::move(res),\
    \ pre_inplace(max_deg);\n        }\n        FPS& pow_inplace(const long long k,\
    \ const int max_deg) {\n            int tlz = 0;\n            while (tlz <= deg()\
    \ and unsafe_get(tlz) == 0) ++tlz;\n            if (tlz * k > max_deg) { this->clear();\
    \ return *this; }\n            *this >>= tlz;\n            mint base = (*this)[0];\n\
    \            *this *= base.inv(), log_inplace(max_deg), *this *= k, exp_inplace(max_deg),\
    \ *this *= base.pow(k);\n            return *this <<= tlz * k, pre_inplace(max_deg);\n\
    \        }\n        inline FPS diff() const { return FPS(*this).diff_inplace();\
    \ }\n        inline FPS intg() const { return FPS(*this).intg_inplace(); }\n \
    \       inline FPS inv(const int max_deg) const { return FPS(*this).inv_inplace(max_deg);\
    \ }\n        inline FPS log(const int max_deg) const { return FPS(*this).log_inplace(max_deg);\
    \ }\n        inline FPS exp(const int max_deg) const { return FPS(*this).exp_inplace(max_deg);\
    \ }\n        inline FPS pow(const long long k, const int max_deg) const { return\
    \ FPS(*this).pow_inplace(k, max_deg); }\n\n        mint eval(mint x) const {\n\
    \            mint y = 0;\n            for (int i = size() - 1; i >= 0; --i) y\
    \ = y * x + unsafe_get(i);\n            return y;\n        }\n\n    private:\n\
    \        static inline inv_mods<mint> invs;\n        static convolution_t<mint>\
    \ mult;\n        inline void ensure_deg(int d) { if (deg() < d) this->resize(d\
    \ + 1, 0); }\n        inline const mint& unsafe_get(int i) const { return std::vector<mint>::operator[](i);\
    \ }\n        inline       mint& unsafe_get(int i)       { return std::vector<mint>::operator[](i);\
    \ }\n\n        std::pair<FPS, FPS&> naive_div_inplace(FPS &&g, const int gd) {\n\
    \            const int k = deg() - gd;\n            mint head_inv = g.unsafe_get(gd).inv();\n\
    \            FPS q(k + 1);\n            for (int i = k; i >= 0; --i) {\n     \
    \           mint div = this->unsafe_get(i + gd) * head_inv;\n                q.unsafe_get(i)\
    \ = div;\n                for (int j = 0; j <= gd; ++j) this->unsafe_get(i + j)\
    \ -= div * g.unsafe_get(j);\n            }\n            return {q, pre_inplace(gd\
    \ - 1)};\n        }\n\n        FPS<mint> naive_exp(const int max_deg) const {\n\
    \            FPS<mint> g(max_deg + 1);\n            g[0] = 1;\n            for\
    \ (int i = 1; i <= max_deg; ++i) {\n                for (int j = 0; j < i; ++j)\
    \ g[i] += g[j] * (i - j) * (*this)[i - j];\n                g[i] *= invs[i];\n\
    \            }\n            return g;\n        }\n};\n\ntemplate <typename mint>\n\
    convolution_t<mint> FPS<mint>::mult = [](const auto &, const auto &) {\n    std::cerr\
    \ << \"convolution function is not available.\" << std::endl;\n    assert(false);\n\
    \    return std::vector<mint>{};\n};\n\n} // namespace suisen\n\ntemplate <typename\
    \ mint>\nauto sqrt(suisen::FPS<mint> a) -> decltype(mint::mod(), suisen::FPS<mint>{})\
    \  {\n    assert(false);\n}\ntemplate <typename mint>\nauto log(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{}) {\n    return a.log(a.deg());\n\
    }\ntemplate <typename mint>\nauto exp(suisen::FPS<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPS<mint>{}) {\n    return a.exp(a.deg());\n}\ntemplate <typename mint,\
    \ typename T>\nauto pow(suisen::FPS<mint> a, T b) -> decltype(mint::mod(), suisen::FPS<mint>{})\
    \ {\n    return a.pow(b, a.deg());\n}\ntemplate <typename mint>\nauto inv(suisen::FPS<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPS<mint>{})  {\n    return a.inv(a.deg());\n\
    }\n\n\n#line 5 \"library/polynomial/multi_point_eval.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename mint>\n    std::vector<mint> multi_point_eval(const\
    \ FPS<mint>& f, const std::vector<mint>& xs) {\n        int n = xs.size();\n \
    \       std::vector<FPS<mint>> seg(2 * n);\n        for (int i = 0; i < n; ++i)\
    \ seg[n + i] = FPS<mint>{ -xs[i], 1 };\n        for (int i = n - 1; i > 0; --i)\
    \ seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = f % seg[1];\n      \
    \  for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n        std::vector<mint>\
    \ ys(n);\n        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n       \
    \ return ys;\n    }\n} // namespace suisen\n\n\n#line 6 \"library/math/product_of_differences.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * O(N(logN)^2)\n     * return the vector\
    \ p of length xs.size() s.t. p[i]=\u03A0[j!=i](x[i]-x[j])\n     */\n    template\
    \ <typename mint>\n    std::vector<mint> product_of_differences(const std::vector<mint>&\
    \ xs) {\n        // f(x):=\u03A0_i(x-x[i])\n        // => f'(x)=\u03A3_i \u03A0\
    [j!=i](x-x[j])\n        // => f'(x[i])=\u03A0[j!=i](x[i]-x[j])\n        const\
    \ int n = xs.size();\n        std::deque<FPS<mint>> dq;\n        for (int i =\
    \ 0; i < n; ++i) dq.push_back(FPS<mint>{ -xs[i], mint{ 1 } });\n        while\
    \ (dq.size() >= 2) {\n            auto f = std::move(dq.front());\n          \
    \  dq.pop_front();\n            auto g = std::move(dq.front());\n            dq.pop_front();\n\
    \            dq.push_back(f * g);\n        }\n        auto f = std::move(dq.front());\n\
    \        f.diff_inplace();\n        return multi_point_eval(f, xs);\n    }\n}\
    \ // namespace suisen\n\n\n\n#line 5 \"library/polynomial/lagrange_interpolation.hpp\"\
    \n\nnamespace suisen {\n    // O(N^2+NlogP)\n    template <typename T>\n    T\
    \ lagrange_interpolation_naive(const std::vector<T>& xs, const std::vector<T>&\
    \ ys, const T t) {\n        const int n = xs.size();\n        assert(int(ys.size())\
    \ == n);\n\n        T p{ 1 };\n        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\
    \n        T res{ 0 };\n        for (int i = 0; i < n; ++i) {\n            T w\
    \ = 1;\n            for (int j = 0; j < n; ++j) if (j != i) w *= xs[i] - xs[j];\n\
    \            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));\n      \
    \  }\n        return res;\n    }\n\n    // O(N(logN)^2+NlogP)\n    template <typename\
    \ mint>\n    mint lagrange_interpolation(const std::vector<mint>& xs, const std::vector<mint>&\
    \ ys, const mint t) {\n        const int n = xs.size();\n        assert(int(ys.size())\
    \ == n);\n\n        std::vector<FPS<mint>> seg(2 * n);\n        for (int i = 0;\
    \ i < n; ++i) seg[n + i] = FPS<mint> {-xs[i], 1};\n        for (int i = n - 1;\
    \ i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = seg[1].diff()\
    \ % seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n\
    \n        mint p{ 1 };\n        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n\
    \        mint res{ 0 };\n        for (int i = 0; i < n; ++i) {\n            mint\
    \ w = seg[n + i][0];\n            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t\
    \ - xs[i])));\n        }\n        return res;\n    }\n\n    // xs[i] = ai + b\n\
    \    // requirement: for all 0\u2264i<j<n, ai+b \u2262 aj+b mod p\n    template\
    \ <typename T>\n    T lagrange_interpolation_arithmetic_progression(T a, T b,\
    \ const std::vector<T>& ys, const T t) {\n        const int n = ys.size();\n \
    \       T fac = 1;\n        for (int i = 1; i < n; ++i) fac *= i;\n        std::vector<T>\
    \ fac_inv(n), suf(n);\n        fac_inv[n - 1] = T(1) / fac;\n        suf[n - 1]\
    \ = 1;\n        for (int i = n - 1; i > 0; --i) {\n            fac_inv[i - 1]\
    \ = fac_inv[i] * i;\n            suf[i - 1] = suf[i] * (t - (a * i + b));\n  \
    \      }\n        T pre = 1, res = 0;\n        for (int i = 0; i < n; ++i) {\n\
    \            T val = ys[i] * pre * suf[i] * fac_inv[i] * fac_inv[n - i - 1];\n\
    \            if ((n - 1 - i) & 1) res -= val;\n            else              \
    \   res += val;\n            pre *= t - (a * i + b);\n        }\n        return\
    \ res / a.pow(n - 1);\n    }\n    // x = 0, 1, ...\n    template <typename T>\n\
    \    T lagrange_interpolation_arithmetic_progression(const std::vector<T>& ys,\
    \ const T t) {\n        return lagrange_interpolation_arithmetic_progression(T{1},\
    \ T{0}, ys, t);\n    }\n} // namespace suisen\n\n\n\n#line 1 \"library/number/linear_sieve.hpp\"\
    \n\n\n\n#line 5 \"library/number/linear_sieve.hpp\"\n#include <numeric>\n#line\
    \ 7 \"library/number/linear_sieve.hpp\"\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
    class LinearSieve {\n    public:\n        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n\
    \ + 1)) {\n            std::iota(min_prime_factor.begin(), min_prime_factor.end(),\
    \ 0);\n            prime_list.reserve(_n / 20);\n            for (int d = 2; d\
    \ <= _n; ++d) {\n                if (min_prime_factor[d] == d) prime_list.push_back(d);\n\
    \                const int prime_max = std::min(min_prime_factor[d], _n / d);\n\
    \                for (int prime : prime_list) {\n                    if (prime\
    \ > prime_max) break;\n                    min_prime_factor[prime * d] = prime;\n\
    \                }\n            }\n        }\n        int prime_num() const noexcept\
    \ { return prime_list.size(); }\n        /**\n         * Returns a vector of primes\
    \ in [0, n].\n         * It is guaranteed that the returned vector is sorted in\
    \ ascending order.\n         */\n        const std::vector<int>& get_prime_list()\
    \ const noexcept  {\n            return prime_list;\n        }\n        const\
    \ std::vector<int>& get_min_prime_factor() const noexcept { return min_prime_factor;\
    \ }\n        /**\n         * Returns a vector of `{ prime, index }`.\n       \
    \  * It is guaranteed that the returned vector is sorted in ascending order.\n\
    \         */\n        std::vector<std::pair<int, int>> factorize(int n) const\
    \ noexcept {\n            assert(0 < n and n <= _n);\n            std::vector<std::pair<int,\
    \ int>> prime_powers;\n            while (n > 1) {\n                int p = min_prime_factor[n],\
    \ c = 0;\n                do { n /= p, ++c; } while (n % p == 0);\n          \
    \      prime_powers.emplace_back(p, c);\n            }\n            return prime_powers;\n\
    \        }\n    private:\n        const int _n;\n        std::vector<int> min_prime_factor;\n\
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n\n#line 8\
    \ \"test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp\"\n\nusing\
    \ mint = atcoder::modint1000000007;\n\nint main() {\n    long long n;\n    int\
    \ m, k;\n    std::cin >> n >> m >> k;\n    const auto mpf = suisen::LinearSieve(k\
    \ + m).get_min_prime_factor();\n    std::vector<mint> f(k + m + 1);\n    for (int\
    \ i = 1; i <= k + m; ++i) {\n        if (i == 1) {\n            f[i] = 1;\n  \
    \      } else if (mpf[i] == i) {\n            f[i] = mint(i).pow(k);\n       \
    \ } else {\n            f[i] = f[mpf[i]] * f[i / mpf[i]];\n        }\n    }\n\
    \    for (int loop = 0; loop < m; ++loop) {\n        for (int i = 1; i <= k +\
    \ m; ++i) {\n            f[i] += f[i - 1];\n        }\n    }\n    std::cout <<\
    \ suisen::lagrange_interpolation_arithmetic_progression<mint>(f, n).val() << '\\\
    n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc208/tasks/abc208_f\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/polynomial/lagrange_interpolation.hpp\"\
    \n#include \"library/number/linear_sieve.hpp\"\n\nusing mint = atcoder::modint1000000007;\n\
    \nint main() {\n    long long n;\n    int m, k;\n    std::cin >> n >> m >> k;\n\
    \    const auto mpf = suisen::LinearSieve(k + m).get_min_prime_factor();\n   \
    \ std::vector<mint> f(k + m + 1);\n    for (int i = 1; i <= k + m; ++i) {\n  \
    \      if (i == 1) {\n            f[i] = 1;\n        } else if (mpf[i] == i) {\n\
    \            f[i] = mint(i).pow(k);\n        } else {\n            f[i] = f[mpf[i]]\
    \ * f[i / mpf[i]];\n        }\n    }\n    for (int loop = 0; loop < m; ++loop)\
    \ {\n        for (int i = 1; i <= k + m; ++i) {\n            f[i] += f[i - 1];\n\
    \        }\n    }\n    std::cout << suisen::lagrange_interpolation_arithmetic_progression<mint>(f,\
    \ n).val() << '\\n';\n    return 0;\n}\n"
  dependsOn:
  - library/polynomial/lagrange_interpolation.hpp
  - library/math/product_of_differences.hpp
  - library/polynomial/multi_point_eval.hpp
  - library/polynomial/fps.hpp
  - library/math/inv_mods.hpp
  - library/number/linear_sieve.hpp
  isVerificationFile: true
  path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  requiredBy: []
  timestamp: '2022-05-14 19:59:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
- /verify/test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp.html
title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
---
