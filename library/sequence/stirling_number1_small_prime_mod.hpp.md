---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient_small_prime_mod.hpp
    title: Binomial Coefficient Small Prime Mod
  - icon: ':question:'
    path: library/sequence/stirling_number1.hpp
    title: Stirling Number1
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/stirling_number1_small_prime_mod.hpp\"\n\
    \n\n\n#line 1 \"library/sequence/stirling_number1.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen\
    \ {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n        inv_mods()\
    \ {}\n        inv_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return invs[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = invs.size();\n    \
    \        if (sz < 2) invs = {0, 1}, sz = 2;\n            if (sz < n + 1) {\n \
    \               invs.resize(n + 1);\n                for (int i = sz; i <= n;\
    \ ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n            }\n       \
    \ }\n    private:\n        static std::vector<mint> invs;\n        static constexpr\
    \ int mod = mint::mod();\n};\ntemplate <typename mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n\
    }\n\n\n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n#line\
    \ 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, typename U = T>\n    struct factorial {\n        factorial() {}\n       \
    \ factorial(int n) { ensure(n); }\n\n        static void ensure(const int n) {\n\
    \            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n   \
    \         int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
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
    } // namespace suisen\n\n\n#line 7 \"library/sequence/stirling_number1.hpp\"\n\
    \nnamespace suisen {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i]\
    \ = S1[n,n-i] for i=0,...,k (unsigned)\n     * constraints:\n     *   0 <= n <=\
    \ 10^6\n     */\n    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
    \ stirling_number1_reversed(int n) {\n        using mint = typename FPSType::value_type;\n\
    \        factorial<mint> fac(n);\n        int l = 0;\n        while ((n >> l)\
    \ != 0) ++l;\n        FPSType a{ 1 };\n        int m = 0;\n        while (l--\
    \ > 0) {\n            FPSType f(m + 1), g(m + 1);\n            mint powm = 1;\n\
    \            for (int i = 0; i <= m; ++i, powm *= m) {\n                f[i] =\
    \ powm * fac.fac_inv(i);\n                g[i] = a[i] * fac.fac(m - i);\n    \
    \        }\n            f *= g, f.cut(m + 1);\n            for (int i = 0; i <=\
    \ m; ++i) f[i] *= fac.fac_inv(m - i);\n            a *= f, m *= 2, a.cut(m + 1);\n\
    \            if ((n >> l) & 1) {\n                a.push_back(0);\n          \
    \      for (int i = m; i > 0; --i) a[i] += m * a[i - 1];\n                ++m;\n\
    \            }\n        }\n        return a;\n    }\n    template <typename FPSType>\n\
    \    std::vector<typename FPSType::value_type> stirling_number1(int n) {\n   \
    \     std::vector<typename FPSType::value_type> a(stirling_number1_reversed<FPSType>(n));\n\
    \        std::reverse(a.begin(), a.end());\n        return a;\n    }\n    /**\n\
    \     * return:\n     *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k,\
    \ where S1 is the stirling number of the first kind (unsigned).\n     * constraints:\n\
    \     * - 0 <= n <= 10^18\n     * - 0 <= k <= 5000\n     * - k < mod\n     */\n\
    \    template <typename mint>\n    std::vector<mint> stirling_number1_reversed(const\
    \ long long n, const int k) {\n        inv_mods<mint> invs(k + 1);\n        std::vector<mint>\
    \ a(k + 1, 0);\n        a[0] = 1;\n        int l = 0;\n        while (n >> l)\
    \ ++l;\n        mint m = 0;\n        while (l-- > 0) {\n            std::vector<mint>\
    \ b(k + 1, 0);\n            for (int j = 0; j <= k; ++j) {\n                mint\
    \ tmp = 1;\n                for (int i = j; i <= k; ++i) {\n                 \
    \   b[i] += a[j] * tmp;\n                    tmp *= (m - i) * invs[i - j + 1]\
    \ * m;\n                }\n            }\n            for (int i = k + 1; i--\
    \ > 0;) {\n                mint sum = 0;\n                for (int j = 0; j <=\
    \ i; ++j) sum += a[j] * b[i - j];\n                a[i] = sum;\n            }\n\
    \            m *= 2;\n            if ((n >> l) & 1) {\n                for (int\
    \ i = k; i > 0; --i) a[i] += m * a[i - 1];\n                ++m;\n           \
    \ }\n        }\n        return a;\n    }\n    template <typename mint>\n    std::vector<std::vector<mint>>\
    \ stirling_number1_table(int n) {\n        std::vector dp(n + 1, std::vector<mint>{});\n\
    \        for (int i = 0; i <= n; ++i) {\n            dp[i].resize(i + 1);\n  \
    \          dp[i][0] = 0, dp[i][i] = 1;\n            for (int j = 1; j < i; ++j)\
    \ dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j];\n        }\n        return\
    \ dp;\n    }\n} // namespace suisen\n\n\n#line 1 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\n\n\n#line 1 \"library/sequence/binomial_coefficient.hpp\"\n\n\n\n#line 5 \"\
    library/sequence/binomial_coefficient.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T>\n    std::vector<std::vector<T>> binom_table(int n) {\n       \
    \ std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n + 1));\n        for\
    \ (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i] = 1;\n   \
    \         for (int j = 1; j < i; ++j) {\n                binom[i][j] = binom[i\
    \ - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n        return binom;\n\
    \    }\n} // namespace suisen\n\n\n\n#line 5 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    struct BinomialCoefficientSmallPrimeMod\
    \ {\n        mint operator()(long long n, long long r) const {\n            return\
    \ binom(n, r);\n        }\n        static mint binom(long long n, long long r)\
    \ {\n            static const std::vector<std::vector<mint>> table = binom_table<mint>(mint::mod()\
    \ - 1);\n            if (r < 0 or n < r) return 0;\n            r = std::min(r,\
    \ n - r);\n            // Lucas's theorem\n            mint res = 1;\n       \
    \     while (r) {\n                int ni = n % mint::mod(), ri = r % mint::mod();\n\
    \                if (ni < ri) return 0;\n                res *= table[ni][ri];\n\
    \                n = n / mint::mod(), r = r / mint::mod();\n            }\n  \
    \          return res;\n        }\n    };\n} // namespace suisen\n\n\n\n#line\
    \ 6 \"library/sequence/stirling_number1_small_prime_mod.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename mint>\n    struct StirlingNumber1SmallPrimeMod {\n\
    \        mint operator()(long long n, long long k) const {\n            return\
    \ s1(n, k);\n        }\n        static mint s1(long long n, long long k) {\n \
    \           static const std::vector<std::vector<mint>> table = stirling_number1_table<mint>(mint::mod()\
    \ - 1);\n            static const BinomialCoefficientSmallPrimeMod<mint> binom{};\n\
    \            static const int p = mint::mod();\n            if (k < 0 or n < k)\
    \ return 0;\n            long long a = n / p, b = n % p;\n            if (k <\
    \ a) return 0;\n            long long c = (k - a) / (p - 1), d = (k - a) % (p\
    \ - 1);\n            return ((a - c) & 1 ? -1 : 1) * (b == p - 1 and d == 0 ?\
    \ -binom(a, c - 1) : d <= b ? table[b][d] * binom(a, c): 0);\n        }\n    };\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STIRLING_NUMBER1_SMALL_P\n#define SUISEN_STIRLING_NUMBER1_SMALL_P\n\
    \n#include \"library/sequence/stirling_number1.hpp\"\n#include \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    struct StirlingNumber1SmallPrimeMod\
    \ {\n        mint operator()(long long n, long long k) const {\n            return\
    \ s1(n, k);\n        }\n        static mint s1(long long n, long long k) {\n \
    \           static const std::vector<std::vector<mint>> table = stirling_number1_table<mint>(mint::mod()\
    \ - 1);\n            static const BinomialCoefficientSmallPrimeMod<mint> binom{};\n\
    \            static const int p = mint::mod();\n            if (k < 0 or n < k)\
    \ return 0;\n            long long a = n / p, b = n % p;\n            if (k <\
    \ a) return 0;\n            long long c = (k - a) / (p - 1), d = (k - a) % (p\
    \ - 1);\n            return ((a - c) & 1 ? -1 : 1) * (b == p - 1 and d == 0 ?\
    \ -binom(a, c - 1) : d <= b ? table[b][d] * binom(a, c): 0);\n        }\n    };\n\
    } // namespace suisen\n\n\n#endif // SUISEN_STIRLING_NUMBER1_SMALL_P\n"
  dependsOn:
  - library/sequence/stirling_number1.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  - library/sequence/binomial_coefficient_small_prime_mod.hpp
  - library/sequence/binomial_coefficient.hpp
  isVerificationFile: false
  path: library/sequence/stirling_number1_small_prime_mod.hpp
  requiredBy: []
  timestamp: '2022-10-13 23:32:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
documentation_of: library/sequence/stirling_number1_small_prime_mod.hpp
layout: document
title: Stirling Number of the First Kind (Small Prime Mod)
---
## Stirling Number of the First Kind (Small Prime Mod)

(符号無し) 第一種スターリング数 $\begin{bmatrix} n \newline k \end{bmatrix}$ を以下で定義する:

$$\begin{bmatrix} n \newline k \end{bmatrix} := [x^k] \prod _ {i = 0} ^ {n - 1} (x + i).$$

$\displaystyle \prod _ {i = 0} ^ {p - 1}(x - i)$ の根は $0,\ldots,p-1$ である。一方、Fermat の小定理より $x ^ p \equiv x \pmod{p}$ より $x ^ p - x$ の根も $0,\ldots,p-1$ である。従って、次が成り立つ。

$$\prod _ {i = 0} ^ {p - 1}(x - i) = x ^ p - x.$$

従って、$n=ap+b$ とすれば、次が成り立つ:

$$\prod _ {i = 0} ^ {n - 1} (x + i) = x ^ a (x ^ {p - 1} - 1) ^ a \prod _ {i = 0} ^ {b - 1} (x + i).$$

即ち、$k=a+c(p-1)+d$ とすれば、次が成り立つ:

$$\begin{bmatrix} n \newline k \end{bmatrix} = \sum _ {c,d} (-1) ^ {a - c} \cdot \binom{a}{c} \cdot \begin{bmatrix} b \newline d \end{bmatrix}.$$

$\begin{bmatrix} b \newline d \end{bmatrix}$ が非零になりうるのは $0\leq d\leq b\leq p-1$ の範囲なので、右辺は高々 $2$ 項の和として計算できる。

$\displaystyle \binom{a}{c}$ は Lucas の定理を用いることで $\langle O(p ^ 2),O(\log _p n)\rangle$ で計算できる [[1]](https://suisen-cp.github.io/cp-library-cpp/library/sequence/binomial_coefficient_small_prime_mod.hpp)。また、全ての $0\leq n\lt p,0\leq k\lt p$ に対する $\begin{bmatrix} n \newline k \end{bmatrix}$ も $O(p ^ 2)$ 時間で計算できる [[2]](https://suisen-cp.github.io/cp-library-cpp/library/sequence/stirling_number1.hpp)。

以上より、任意の整数 $n,k$ に対する $\begin{bmatrix} n \newline k \end{bmatrix}$ を $\langle O(p ^ 2),O(\log _p n)\rangle$ で計算できた。
