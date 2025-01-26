---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/arbitrary_mod_convolution.hpp
    title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/shift_of_sampling_points.hpp
    title: Shift of Sampling Points of Polynomial
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/src/math/factorial_large/yuki502.cpp
    title: test/src/math/factorial_large/yuki502.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/dummy.test.cpp
    title: test/src/math/factorial_large/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/factorial.test.cpp
    title: test/src/math/factorial_large/factorial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/many_factorials.test.cpp
    title: test/src/math/factorial_large/many_factorials.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/factorial_large.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 1 \"library/polynomial/shift_of_sampling_points.hpp\"\n\n\n\n#include\
    \ <vector>\n#include <atcoder/convolution>\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, typename U = T>\n    struct factorial {\n\
    \        factorial() = default;\n        factorial(int n) { ensure(n); }\n\n \
    \       static void ensure(const int n) {\n            int sz = _fac.size();\n\
    \            if (n + 1 <= sz) return;\n            int new_size = std::max(n +\
    \ 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        U polynom(const int n, const Ds& ...ds)\
    \ {\n            if (n < 0) return 0;\n            ensure(n);\n            int\
    \ sumd = 0;\n            U res = _fac[n];\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= _fac_inv[d];\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= _fac_inv[n - sumd];\n            return res;\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return _fac[n]\
    \ * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T> _fac;\n\
    \        static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 8 \"library/polynomial/shift_of_sampling_points.hpp\"\n\n\
    namespace suisen {\n    template <typename mint, typename Convolve,\n        std::enable_if_t<std::is_invocable_r_v<std::vector<mint>,\
    \ Convolve, std::vector<mint>, std::vector<mint>>, std::nullptr_t> = nullptr>\n\
    \    std::vector<mint> shift_of_sampling_points(const std::vector<mint>& ys, mint\
    \ t, int m, const Convolve &convolve) {\n        const int n = ys.size();\n  \
    \      factorial<mint> fac(std::max(n, m));\n\n        std::vector<mint> b = [&]\
    \ {\n            std::vector<mint> f(n), g(n);\n            for (int i = 0; i\
    \ < n; ++i) {\n                f[i] = ys[i] * fac.fac_inv(i);\n              \
    \  g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);\n            }\n            std::vector<mint>\
    \ b = convolve(f, g);\n            b.resize(n);\n            return b;\n     \
    \   }();\n        std::vector<mint> e = [&] {\n            std::vector<mint> c(n);\n\
    \            mint prd = 1;\n            std::reverse(b.begin(), b.end());\n  \
    \          for (int i = 0; i < n; ++i) {\n                b[i] *= fac.fac(n -\
    \ i - 1);\n                c[i] = prd * fac.fac_inv(i);\n                prd *=\
    \ t - i;\n            }\n            std::vector<mint> e = convolve(b, c);\n \
    \           e.resize(n);\n            return e;\n        }();\n        std::reverse(e.begin(),\
    \ e.end());\n        for (int i = 0; i < n; ++i) {\n            e[i] *= fac.fac_inv(i);\n\
    \        }\n\n        std::vector<mint> f(m);\n        for (int i = 0; i < m;\
    \ ++i) f[i] = fac.fac_inv(i);\n        std::vector<mint> res = convolve(e, f);\n\
    \        res.resize(m);\n        for (int i = 0; i < m; ++i) res[i] *= fac.fac(i);\n\
    \        return res;\n    }\n\n    template <typename mint>\n    std::vector<mint>\
    \ shift_of_sampling_points(const std::vector<mint>& ys, mint t, int m) {\n   \
    \     auto convolve = [&](const std::vector<mint> &f, const std::vector<mint>\
    \ &g) { return atcoder::convolution(f, g); };\n        return shift_of_sampling_points(ys,\
    \ t, m, convolve);\n    }\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/arbitrary_mod_convolution.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/arbitrary_mod_convolution.hpp\"\n#include\
    \ <iostream>\n\n#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n\
    #line 5 \"library/convolution/convolution_naive.hpp\"\n\nnamespace suisen::internal\
    \ {\n    template <typename T, typename R = T>\n    std::vector<R> convolution_naive(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n        const int n = a.size(),\
    \ m = b.size();\n        std::vector<R> c(n + m - 1);\n        if (n < m) {\n\
    \            for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) c[i + j]\
    \ += R(a[i]) * b[j];\n        } else {\n            for (int i = 0; i < n; i++)\
    \ for (int j = 0; j < m; j++) c[i + j] += R(a[i]) * b[j];\n        }\n       \
    \ return c;\n    }\n} // namespace suisen\n\n\n\n#line 8 \"library/convolution/arbitrary_mod_convolution.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \n        if constexpr (atcoder::internal::is_static_modint<mint>::value) {\n\
    \            if constexpr (not (mint::mod() & 63)) {\n                int maxz\
    \ = 1;\n                while (not ((mint::mod() - 1) & maxz)) maxz <<= 1;\n \
    \               int z = 1;\n                while (z < n + m - 1) z <<= 1;\n \
    \               if (z <= maxz) return atcoder::convolution<mint>(a, b);\n    \
    \        }\n        }\n\n        if (n == 0 or m == 0) return {};\n        if\
    \ (std::min(n, m) <= 120) return internal::convolution_naive(a, b);\n\n      \
    \  static constexpr long long MOD1 = 754974721;  // 2^24\n        static constexpr\
    \ long long MOD2 = 167772161;  // 2^25\n        static constexpr long long MOD3\
    \ = 469762049;  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n\
    \        static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1,\
    \ MOD2).second;\n        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n\n    std::vector<__uint128_t> convolution_int(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n        int n = int(a.size()),\
    \ m = int(b.size());\n\n        auto check_nonnegative = [](int e) { return e\
    \ >= 0; };\n        assert(std::all_of(a.begin(), a.end(), check_nonnegative));\n\
    \        assert(std::all_of(b.begin(), b.end(), check_nonnegative));\n\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 120) return\
    \ internal::convolution_naive<int, __uint128_t>(a, b);\n\n        static constexpr\
    \ long long MOD1 = 754974721;  // 2^24\n        static constexpr long long MOD2\
    \ = 167772161;  // 2^25\n        static constexpr long long MOD3 = 469762049;\
    \  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n        static\
    \ constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n\
    \        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        auto c1 = atcoder::convolution<MOD1>(a, b);\n     \
    \   auto c2 = atcoder::convolution<MOD2>(a, b);\n        auto c3 = atcoder::convolution<MOD3>(a,\
    \ b);\n        std::vector<__uint128_t> c(n + m - 1);\n        for (int i = 0;\
    \ i < n + m - 1; ++i) {\n            // Garner's Algorithm\n            // X =\
    \ x1 + x2 * m1 + x3 * m1 * m2\n            // x1 = c1[i], x2 = (c2[i] - x1) /\
    \ m1 (mod m2), x3 = (c3[i] - x1 - x2 * m1) / m2 (mod m3)\n            int x1 =\
    \ c1[i];\n            int x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n\
    \            int x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + __uint128_t(x3) *\
    \ M1M2;\n        }\n        return c;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 9 \"library/math/factorial_large.hpp\"\n\nnamespace suisen {\n    // mod must\
    \ be a prime number\n    template <typename mint,\n        std::enable_if_t<atcoder::internal::is_static_modint<mint>::value,\
    \ std::nullptr_t> = nullptr>\n    struct factorial_large {\n        using value_type\
    \ = mint;\n\n        static constexpr int LOG_BLOCK_SIZE = 9;\n        static\
    \ constexpr int BLOCK_SIZE = 1 << LOG_BLOCK_SIZE;\n        static constexpr int\
    \ BLOCK_NUM = value_type::mod() >> LOG_BLOCK_SIZE;\n\n        static inline int\
    \ threshold = 2000000;\n\n        static_assert(atcoder::internal::is_prime_constexpr(mint::mod()));\n\
    \n        static value_type fac(long long n) {\n            if (n >= mint::mod())\
    \ return 0;\n            return n <= threshold ? factorial<mint>{}.fac(n) : _large_fac(n);\n\
    \        }\n        static value_type fac_inv(long long n) {\n            assert(n\
    \ < (long long) mint::mod());\n            return n <= threshold ? factorial<mint>{}.fac_inv(n)\
    \ : _large_fac(n).inv();\n        }\n        static value_type binom(int n, int\
    \ r) {\n            if (r < 0 or r > n) return 0;\n            return fac(n) *\
    \ fac_inv(r) * fac_inv(n - r);\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        static value_type polynom(const int n, const\
    \ Ds& ...ds) {\n            if (n < 0) return 0;\n            long long sumd =\
    \ 0;\n            value_type res = fac(n);\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= fac_inv(d);\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= fac_inv(n - sumd);\n            return res;\n\
    \        }\n        static value_type perm(int n, int r) {\n            if (r\
    \ < 0 or r > n) return 0;\n            return fac(n) * fac_inv(n - r);\n     \
    \   }\n    private:\n        static inline std::vector<value_type> _block_fac{};\n\
    \n        static void _build() {\n            if (_block_fac.size()) {\n     \
    \           return;\n            }\n            std::vector<value_type> f{ 1 };\n\
    \            f.reserve(BLOCK_SIZE);\n            for (int i = 0; i < LOG_BLOCK_SIZE;\
    \ ++i) {\n                std::vector<value_type> g = shift_of_sampling_points<value_type>(f,\
    \ 1 << i, 3 << i, arbitrary_mod_convolution<value_type>);\n                const\
    \ auto get = [&](int j) { return j < (1 << i) ? f[j] : g[j - (1 << i)]; };\n \
    \               f.resize(2 << i);\n                for (int j = 0; j < 2 << i;\
    \ ++j) {\n                    f[j] = get(2 * j) * get(2 * j + 1) * ((2 * j + 1)\
    \ << i);\n                }\n            }\n            // f_B(x) = (x+1) * ...\
    \ * (x+B-1)\n            if (BLOCK_NUM > BLOCK_SIZE) {\n                std::vector<value_type>\
    \ g = shift_of_sampling_points<value_type>(f, BLOCK_SIZE, BLOCK_NUM - BLOCK_SIZE,\
    \ arbitrary_mod_convolution<value_type>);\n                std::move(g.begin(),\
    \ g.end(), std::back_inserter(f));\n            } else {\n                f.resize(BLOCK_NUM);\n\
    \            }\n            for (int i = 0; i < BLOCK_NUM; ++i) {\n          \
    \      f[i] *= value_type(i + 1) * BLOCK_SIZE;\n            }\n            //\
    \ f[i] = (i*B + 1) * ... * (i*B + B)\n\n            f.insert(f.begin(), 1);\n\
    \            for (int i = 1; i <= BLOCK_NUM; ++i) {\n                f[i] *= f[i\
    \ - 1];\n            }\n            _block_fac = std::move(f);\n        }\n\n\
    \        static value_type _large_fac(int n) {\n            _build();\n      \
    \      value_type res;\n            int q = n / BLOCK_SIZE, r = n % BLOCK_SIZE;\n\
    \            if (2 * r <= BLOCK_SIZE) {\n                res = _block_fac[q];\n\
    \                for (int i = 0; i < r; ++i) {\n                    res *= value_type::raw(n\
    \ - i);\n                }\n            } else if (q != factorial_large::BLOCK_NUM)\
    \ {\n                res = _block_fac[q + 1];\n                value_type den\
    \ = 1;\n                for (int i = 1; i <= BLOCK_SIZE - r; ++i) {\n        \
    \            den *= value_type::raw(n + i);\n                }\n             \
    \   res /= den;\n            } else {\n                // Wilson's theorem\n \
    \               res = value_type::mod() - 1;\n                value_type den =\
    \ 1;\n                for (int i = value_type::mod() - 1; i > n; --i) {\n    \
    \                den *= value_type::raw(i);\n                }\n             \
    \   res /= den;\n            }\n            return res;\n        }\n    };\n}\
    \ // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL_LARGE\n#define SUISEN_FACTORIAL_LARGE\n\n#include\
    \ <utility>\n\n#include \"library/polynomial/shift_of_sampling_points.hpp\"\n\
    #include \"library/convolution/arbitrary_mod_convolution.hpp\"\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n    // mod must be a prime number\n    template <typename\
    \ mint,\n        std::enable_if_t<atcoder::internal::is_static_modint<mint>::value,\
    \ std::nullptr_t> = nullptr>\n    struct factorial_large {\n        using value_type\
    \ = mint;\n\n        static constexpr int LOG_BLOCK_SIZE = 9;\n        static\
    \ constexpr int BLOCK_SIZE = 1 << LOG_BLOCK_SIZE;\n        static constexpr int\
    \ BLOCK_NUM = value_type::mod() >> LOG_BLOCK_SIZE;\n\n        static inline int\
    \ threshold = 2000000;\n\n        static_assert(atcoder::internal::is_prime_constexpr(mint::mod()));\n\
    \n        static value_type fac(long long n) {\n            if (n >= mint::mod())\
    \ return 0;\n            return n <= threshold ? factorial<mint>{}.fac(n) : _large_fac(n);\n\
    \        }\n        static value_type fac_inv(long long n) {\n            assert(n\
    \ < (long long) mint::mod());\n            return n <= threshold ? factorial<mint>{}.fac_inv(n)\
    \ : _large_fac(n).inv();\n        }\n        static value_type binom(int n, int\
    \ r) {\n            if (r < 0 or r > n) return 0;\n            return fac(n) *\
    \ fac_inv(r) * fac_inv(n - r);\n        }\n        template <typename ...Ds, std::enable_if_t<std::conjunction_v<std::is_integral<Ds>...>,\
    \ std::nullptr_t> = nullptr>\n        static value_type polynom(const int n, const\
    \ Ds& ...ds) {\n            if (n < 0) return 0;\n            long long sumd =\
    \ 0;\n            value_type res = fac(n);\n            for (int d : { ds... })\
    \ {\n                if (d < 0 or d > n) return 0;\n                sumd += d;\n\
    \                res *= fac_inv(d);\n            }\n            if (sumd > n)\
    \ return 0;\n            res *= fac_inv(n - sumd);\n            return res;\n\
    \        }\n        static value_type perm(int n, int r) {\n            if (r\
    \ < 0 or r > n) return 0;\n            return fac(n) * fac_inv(n - r);\n     \
    \   }\n    private:\n        static inline std::vector<value_type> _block_fac{};\n\
    \n        static void _build() {\n            if (_block_fac.size()) {\n     \
    \           return;\n            }\n            std::vector<value_type> f{ 1 };\n\
    \            f.reserve(BLOCK_SIZE);\n            for (int i = 0; i < LOG_BLOCK_SIZE;\
    \ ++i) {\n                std::vector<value_type> g = shift_of_sampling_points<value_type>(f,\
    \ 1 << i, 3 << i, arbitrary_mod_convolution<value_type>);\n                const\
    \ auto get = [&](int j) { return j < (1 << i) ? f[j] : g[j - (1 << i)]; };\n \
    \               f.resize(2 << i);\n                for (int j = 0; j < 2 << i;\
    \ ++j) {\n                    f[j] = get(2 * j) * get(2 * j + 1) * ((2 * j + 1)\
    \ << i);\n                }\n            }\n            // f_B(x) = (x+1) * ...\
    \ * (x+B-1)\n            if (BLOCK_NUM > BLOCK_SIZE) {\n                std::vector<value_type>\
    \ g = shift_of_sampling_points<value_type>(f, BLOCK_SIZE, BLOCK_NUM - BLOCK_SIZE,\
    \ arbitrary_mod_convolution<value_type>);\n                std::move(g.begin(),\
    \ g.end(), std::back_inserter(f));\n            } else {\n                f.resize(BLOCK_NUM);\n\
    \            }\n            for (int i = 0; i < BLOCK_NUM; ++i) {\n          \
    \      f[i] *= value_type(i + 1) * BLOCK_SIZE;\n            }\n            //\
    \ f[i] = (i*B + 1) * ... * (i*B + B)\n\n            f.insert(f.begin(), 1);\n\
    \            for (int i = 1; i <= BLOCK_NUM; ++i) {\n                f[i] *= f[i\
    \ - 1];\n            }\n            _block_fac = std::move(f);\n        }\n\n\
    \        static value_type _large_fac(int n) {\n            _build();\n      \
    \      value_type res;\n            int q = n / BLOCK_SIZE, r = n % BLOCK_SIZE;\n\
    \            if (2 * r <= BLOCK_SIZE) {\n                res = _block_fac[q];\n\
    \                for (int i = 0; i < r; ++i) {\n                    res *= value_type::raw(n\
    \ - i);\n                }\n            } else if (q != factorial_large::BLOCK_NUM)\
    \ {\n                res = _block_fac[q + 1];\n                value_type den\
    \ = 1;\n                for (int i = 1; i <= BLOCK_SIZE - r; ++i) {\n        \
    \            den *= value_type::raw(n + i);\n                }\n             \
    \   res /= den;\n            } else {\n                // Wilson's theorem\n \
    \               res = value_type::mod() - 1;\n                value_type den =\
    \ 1;\n                for (int i = value_type::mod() - 1; i > n; --i) {\n    \
    \                den *= value_type::raw(i);\n                }\n             \
    \   res /= den;\n            }\n            return res;\n        }\n    };\n}\
    \ // namespace suisen\n\n\n#endif // SUISEN_FACTORIAL_LARGE\n"
  dependsOn:
  - library/polynomial/shift_of_sampling_points.hpp
  - library/math/factorial.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/convolution/convolution_naive.hpp
  isVerificationFile: false
  path: library/math/factorial_large.hpp
  requiredBy:
  - test/src/math/factorial_large/yuki502.cpp
  timestamp: '2024-01-30 21:01:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/factorial_large/many_factorials.test.cpp
  - test/src/math/factorial_large/dummy.test.cpp
  - test/src/math/factorial_large/factorial.test.cpp
documentation_of: library/math/factorial_large.hpp
layout: document
title: Factorial Large
---
## Factorial Large
