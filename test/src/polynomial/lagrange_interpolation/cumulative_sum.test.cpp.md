---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':question:'
    path: library/number/linear_sieve.hpp
    title: "\u7DDA\u5F62\u7BE9"
  - icon: ':question:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  - icon: ':question:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
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
    PROBLEM: https://atcoder.jp/contests/abc208/tasks/abc208_f
    links:
    - https://atcoder.jp/contests/abc208/tasks/abc208_f
  bundledCode: "#line 1 \"test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc208/tasks/abc208_f\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/polynomial/lagrange_interpolation.hpp\"\
    \n\n\n\n#line 1 \"library/math/product_of_differences.hpp\"\n\n\n\n#include <deque>\n\
    #line 1 \"library/polynomial/multi_point_eval.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename FPSType, typename T>\n    std::vector<typename\
    \ FPSType::value_type> multi_point_eval(const FPSType& f, const std::vector<T>&\
    \ xs) {\n        int n = xs.size();\n        std::vector<FPSType> seg(2 * n);\n\
    \        for (int i = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i], 1 };\n    \
    \    for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n \
    \       seg[1] = f % seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i] =\
    \ seg[i / 2] % seg[i];\n        std::vector<typename FPSType::value_type> ys(n);\n\
    \        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n        return ys;\n\
    \    }\n} // namespace suisen\n\n\n#line 6 \"library/math/product_of_differences.hpp\"\
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
    \ T{0}, ys, t);\n    }\n} // namespace suisen\n\n\n\n#line 1 \"library/sequence/powers.hpp\"\
    \n\n\n\n#include <cstdint>\n#line 1 \"library/number/linear_sieve.hpp\"\n\n\n\n\
    #include <cassert>\n#include <numeric>\n#line 7 \"library/number/linear_sieve.hpp\"\
    \n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\nclass\
    \ LinearSieve {\n    public:\n        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n\
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
    } // namespace suisen\n\n\n#line 8 \"test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp\"\
    \n\nusing mint = atcoder::modint1000000007;\n\nint main() {\n    long long n;\n\
    \    int m, k;\n    std::cin >> n >> m >> k;\n\n    std::vector<mint> f = suisen::powers<mint>(k\
    \ + m, k);\n    for (int loop = 0; loop < m; ++loop) {\n        for (int i = 1;\
    \ i <= k + m; ++i) f[i] += f[i - 1];\n    }\n\n    std::cout << suisen::lagrange_interpolation_arithmetic_progression<mint>(f,\
    \ n).val() << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc208/tasks/abc208_f\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/polynomial/lagrange_interpolation.hpp\"\
    \n#include \"library/sequence/powers.hpp\"\n\nusing mint = atcoder::modint1000000007;\n\
    \nint main() {\n    long long n;\n    int m, k;\n    std::cin >> n >> m >> k;\n\
    \n    std::vector<mint> f = suisen::powers<mint>(k + m, k);\n    for (int loop\
    \ = 0; loop < m; ++loop) {\n        for (int i = 1; i <= k + m; ++i) f[i] += f[i\
    \ - 1];\n    }\n\n    std::cout << suisen::lagrange_interpolation_arithmetic_progression<mint>(f,\
    \ n).val() << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - library/polynomial/lagrange_interpolation.hpp
  - library/math/product_of_differences.hpp
  - library/polynomial/multi_point_eval.hpp
  - library/sequence/powers.hpp
  - library/number/linear_sieve.hpp
  isVerificationFile: true
  path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  requiredBy: []
  timestamp: '2022-07-23 23:55:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
- /verify/test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp.html
title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
---
