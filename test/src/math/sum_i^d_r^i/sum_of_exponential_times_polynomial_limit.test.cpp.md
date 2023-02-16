---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/pow_mods.hpp
    title: "\u51AA\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  - icon: ':question:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  - icon: ':question:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  - icon: ':question:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  - icon: ':heavy_check_mark:'
    path: library/polynomial/shift_of_sampling_points.hpp
    title: Shift of Sampling Points of Polynomial
  - icon: ':question:'
    path: library/sequence/powers.hpp
    title: Powers
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
    links:
    - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
  bundledCode: "#line 1 \"test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/math/sum_i^d_r^i.hpp\"\
    \n\n\n\n#line 1 \"library/sequence/powers.hpp\"\n\n\n\n#include <cstdint>\n#line\
    \ 1 \"library/number/linear_sieve.hpp\"\n\n\n\n#include <cassert>\n#include <numeric>\n\
    #include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
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
    \        std::vector<int> prime_list;\n};\n} // namespace suisen\n\n\n#line 6\
    \ \"library/sequence/powers.hpp\"\n\nnamespace suisen {\n    // returns { 0^k,\
    \ 1^k, ..., n^k }\n    template <typename mint>\n    std::vector<mint> powers(uint32_t\
    \ n, uint64_t k) {\n        const auto mpf = LinearSieve(n).get_min_prime_factor();\n\
    \        std::vector<mint> res(n + 1);\n        res[0] = k == 0;\n        for\
    \ (uint32_t i = 1; i <= n; ++i) res[i] = i == 1 ? 1 : uint32_t(mpf[i]) == i ?\
    \ mint(i).pow(k) : res[mpf[i]] * res[i / mpf[i]];\n        return res;\n    }\n\
    } // namespace suisen\n\n\n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#line\
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
    } // namespace suisen\n\n\n#line 1 \"library/math/pow_mods.hpp\"\n\n\n\n#line\
    \ 5 \"library/math/pow_mods.hpp\"\n\nnamespace suisen {\n    template <int base_as_int,\
    \ typename mint>\n    struct static_pow_mods {\n        static_pow_mods() {}\n\
    \        static_pow_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return pows[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = pows.size();\n    \
    \        if (sz > n) return;\n            pows.resize(n + 1);\n            for\
    \ (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n        }\n    private:\n\
    \        static inline std::vector<mint> pows { 1 };\n        static inline mint\
    \ base = base_as_int;\n        static constexpr int mod = mint::mod();\n    };\n\
    \n    template <typename mint>\n    struct pow_mods {\n        pow_mods() {}\n\
    \        pow_mods(mint base, int n) : base(base) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ pows[i];\n        }\n        void ensure(int n) const {\n            int sz\
    \ = pows.size();\n            if (sz > n) return;\n            pows.resize(n +\
    \ 1);\n            for (int i = sz; i <= n; ++i) pows[i] = base * pows[i - 1];\n\
    \        }\n    private:\n        mutable std::vector<mint> pows { 1 };\n    \
    \    mint base;\n        static constexpr int mod = mint::mod();\n    };\n}\n\n\
    \n#line 1 \"library/polynomial/lagrange_interpolation.hpp\"\n\n\n\n#line 1 \"\
    library/math/product_of_differences.hpp\"\n\n\n\n#include <deque>\n#line 1 \"\
    library/polynomial/multi_point_eval.hpp\"\n\n\n\n#line 5 \"library/polynomial/multi_point_eval.hpp\"\
    \n\nnamespace suisen {\n    template <typename FPSType, typename T>\n    std::vector<typename\
    \ FPSType::value_type> multi_point_eval(const FPSType& f, const std::vector<T>&\
    \ xs) {\n        int n = xs.size();\n        if (n == 0) return {};\n        std::vector<FPSType>\
    \ seg(2 * n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i],\
    \ 1 };\n        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i *\
    \ 2 + 1];\n        seg[1] = f % seg[1];\n        for (int i = 2; i < 2 * n; ++i)\
    \ seg[i] = seg[i / 2] % seg[i];\n        std::vector<typename FPSType::value_type>\
    \ ys(n);\n        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n       \
    \ return ys;\n    }\n} // namespace suisen\n\n\n#line 6 \"library/math/product_of_differences.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * O(N(logN)^2)\n     * return the vector\
    \ p of length xs.size() s.t. p[i]=\u03A0[j!=i](x[i]-x[j])\n     */\n    template\
    \ <typename FPSType, typename T>\n    std::vector<typename FPSType::value_type>\
    \ product_of_differences(const std::vector<T>& xs) {\n        // f(x):=\u03A0\
    _i(x-x[i])\n        // => f'(x)=\u03A3_i \u03A0[j!=i](x-x[j])\n        // => f'(x[i])=\u03A0\
    [j!=i](x[i]-x[j])\n        const int n = xs.size();\n        std::deque<FPSType>\
    \ dq;\n        for (int i = 0; i < n; ++i) dq.push_back(FPSType{ -xs[i], 1 });\n\
    \        while (dq.size() >= 2) {\n            auto f = std::move(dq.front());\n\
    \            dq.pop_front();\n            auto g = std::move(dq.front());\n  \
    \          dq.pop_front();\n            dq.push_back(f * g);\n        }\n    \
    \    auto f = std::move(dq.front());\n        f.diff_inplace();\n        return\
    \ multi_point_eval<FPSType, T>(f, xs);\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 5 \"library/polynomial/lagrange_interpolation.hpp\"\n\nnamespace suisen {\n\
    \    // O(N^2+NlogP)\n    template <typename T>\n    T lagrange_interpolation_naive(const\
    \ std::vector<T>& xs, const std::vector<T>& ys, const T t) {\n        const int\
    \ n = xs.size();\n        assert(int(ys.size()) == n);\n\n        T p{ 1 };\n\
    \        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n        T res{ 0 };\n\
    \        for (int i = 0; i < n; ++i) {\n            T w = 1;\n            for\
    \ (int j = 0; j < n; ++j) if (j != i) w *= xs[i] - xs[j];\n            res +=\
    \ ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));\n        }\n        return\
    \ res;\n    }\n\n    // O(N(logN)^2+NlogP)\n    template <typename FPSType, typename\
    \ T>\n    typename FPSType::value_type lagrange_interpolation(const std::vector<T>&\
    \ xs, const std::vector<T>& ys, const T t) {\n        const int n = xs.size();\n\
    \        assert(int(ys.size()) == n);\n\n        std::vector<FPSType> seg(2 *\
    \ n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPSType {-xs[i], 1};\n\
    \        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n\
    \        seg[1] = seg[1].diff() % seg[1];\n        for (int i = 2; i < 2 * n;\
    \ ++i) seg[i] = seg[i / 2] % seg[i];\n\n        using mint = typename FPSType::value_type;\n\
    \        mint p{ 1 };\n        for (int i = 0; i < n; ++i) p *= t - xs[i];\n\n\
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
    \ T{0}, ys, t);\n    }\n} // namespace suisen\n\n\n\n#line 1 \"library/polynomial/shift_of_sampling_points.hpp\"\
    \n\n\n\n#line 5 \"library/polynomial/shift_of_sampling_points.hpp\"\n#include\
    \ <atcoder/convolution>\n\n#line 8 \"library/polynomial/shift_of_sampling_points.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    std::vector<mint> shift_of_sampling_points(const\
    \ std::vector<mint>& ys, mint t, int m) {\n        const int n = ys.size();\n\
    \        factorial<mint> fac(std::max(n, m));\n\n        std::vector<mint> b =\
    \ [&] {\n            std::vector<mint> f(n), g(n);\n            for (int i = 0;\
    \ i < n; ++i) {\n                f[i] = ys[i] * fac.fac_inv(i);\n            \
    \    g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);\n            }\n            std::vector<mint>\
    \ b = atcoder::convolution(f, g);\n            b.resize(n);\n            return\
    \ b;\n        }();\n        std::vector<mint> e = [&] {\n            std::vector<mint>\
    \ c(n);\n            mint prd = 1;\n            std::reverse(b.begin(), b.end());\n\
    \            for (int i = 0; i < n; ++i) {\n                b[i] *= fac.fac(n\
    \ - i - 1);\n                c[i] = prd * fac.fac_inv(i);\n                prd\
    \ *= t - i;\n            }\n            std::vector<mint> e = atcoder::convolution(b,\
    \ c);\n            e.resize(n);\n            return e;\n        }();\n       \
    \ std::reverse(e.begin(), e.end());\n        for (int i = 0; i < n; ++i) {\n \
    \           e[i] *= fac.fac_inv(i);\n        }\n\n        std::vector<mint> f(m);\n\
    \        for (int i = 0; i < m; ++i) f[i] = fac.fac_inv(i);\n        std::vector<mint>\
    \ res = atcoder::convolution(e, f);\n        res.resize(m);\n        for (int\
    \ i = 0; i < m; ++i) res[i] *= fac.fac(i);\n        return res;\n    }\n} // namespace\
    \ suisen\n\n\n\n#line 9 \"library/math/sum_i^d_r^i.hpp\"\n\nnamespace suisen {\n\
    \    template <typename mint>\n    struct sum_i_i_pow_d_r_pow_i {\n        sum_i_i_pow_d_r_pow_i(int\
    \ d, mint r) : d(d), r(r), i_pow_d(powers<mint>(d + 1, d)), r_pow_i(r, d + 1),\
    \ fac(d), c(calc_c()) {}\n\n        mint sum() const {\n            assert(r !=\
    \ 1);\n            return c;\n        }\n        mint sum(long long n) {\n   \
    \         if (r == 0) return n > 0 and d == 0 ? 1 : 0;\n            prepare();\n\
    \            return lagrange_interpolation_arithmetic_progression<mint>(ys, n)\
    \ * r.pow(n) + c;\n        }\n        std::vector<mint> sum(long long t, int m)\
    \ {\n            if (r == 0) {\n                std::vector<mint> res(m);\n  \
    \              for (long long n = t; n < t + m; ++n) res[n - t] = sum(n);\n  \
    \              return res;\n            }\n            prepare();\n          \
    \  auto res = shift_of_sampling_points<mint>(ys, t, m);\n            mint pr =\
    \ r.pow(r);\n            for (auto &e : res) e *= pr, e += c, pr *= r;\n     \
    \       return res;\n        }\n    private:\n        int d;\n        mint r;\n\
    \        std::vector<mint> i_pow_d;\n        pow_mods<mint> r_pow_i;\n       \
    \ factorial<mint> fac;\n\n        mint c;\n\n        std::vector<mint> ys;\n \
    \       bool prepared = false;\n\n        mint calc_c() {\n            if (r ==\
    \ 1) return 0;\n            mint num = 0, den = 0, sum = 0;\n            for (int\
    \ i = 0; i <= d + 1; ++i) {\n                sum += i_pow_d[i] * r_pow_i[i];\n\
    \                den += (i & 1 ? -1 : +1) * fac.binom(d + 1, i) * r_pow_i[i];\n\
    \                num += ((d + 1 - i) & 1 ? -1 : +1) * fac.binom(d + 1, d + 1 -\
    \ i) * r_pow_i[d + 1 - i] * sum;\n            }\n            return num / den;\n\
    \        }\n\n        void prepare() {\n            if (prepared) return;\n  \
    \          prepared = true;\n\n            ys.resize(d + 2);\n            for\
    \ (int i = 0; i <= d; ++i) ys[i + 1] = ys[i] + r_pow_i[i] * i_pow_d[i];\n    \
    \        \n            if (r == 1) return;\n\n            for (auto& e : ys) e\
    \ -= c;\n\n            mint inv_r = r.inv();\n            mint pow_inv_r = inv_r.pow(d\
    \ + 1);\n            for (int i = d + 1; i >= 0; --i) {\n                ys[i]\
    \ *= pow_inv_r;\n                pow_inv_r *= r;\n            }\n        }\n \
    \   };\n} // namespace suisen\n\n\n\n#line 7 \"test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n    int r, d;\n\
    \    std::cin >> r >> d;\n    std::cout << suisen::sum_i_i_pow_d_r_pow_i<mint>(d,\
    \ r).sum().val() << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/math/sum_i^d_r^i.hpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n    int r, d;\n\
    \    std::cin >> r >> d;\n    std::cout << suisen::sum_i_i_pow_d_r_pow_i<mint>(d,\
    \ r).sum().val() << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/math/sum_i^d_r^i.hpp
  - library/sequence/powers.hpp
  - library/number/linear_sieve.hpp
  - library/math/factorial.hpp
  - library/math/pow_mods.hpp
  - library/polynomial/lagrange_interpolation.hpp
  - library/math/product_of_differences.hpp
  - library/polynomial/multi_point_eval.hpp
  - library/polynomial/shift_of_sampling_points.hpp
  isVerificationFile: true
  path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  requiredBy: []
  timestamp: '2023-02-16 15:43:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
- /verify/test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp.html
title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
---
