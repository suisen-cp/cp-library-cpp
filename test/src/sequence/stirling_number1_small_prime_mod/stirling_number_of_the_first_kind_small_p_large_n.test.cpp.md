---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient_small_prime_mod.hpp
    title: Binomial Coefficient Small Prime Mod
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number1.hpp
    title: Stirling Number1
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number1_small_prime_mod.hpp
    title: Stirling Number of the First Kind (Small Prime Mod)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n
    links:
    - https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n
  bundledCode: "#line 1 \"test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \n#line 1 \"library/sequence/stirling_number1_small_prime_mod.hpp\"\n\n\n\n#line\
    \ 1 \"library/sequence/stirling_number1.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen\
    \ {\n    template <typename mint>\n    class inv_mods {\n    public:\n       \
    \ inv_mods() {}\n        inv_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return invs[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = invs.size();\n    \
    \        if (sz < 2) invs = { 0, 1 }, sz = 2;\n            if (sz < n + 1) {\n\
    \                invs.resize(n + 1);\n                for (int i = sz; i <= n;\
    \ ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n            }\n       \
    \ }\n    private:\n        static std::vector<mint> invs;\n        static constexpr\
    \ int mod = mint::mod();\n    };\n    template <typename mint>\n    std::vector<mint>\
    \ inv_mods<mint>::invs{};\n\n    template <typename mint>\n    std::vector<mint>\
    \ get_invs(const std::vector<mint>& vs) {\n        const int n = vs.size();\n\n\
    \        mint p = 1;\n        for (auto& e : vs) {\n            p *= e;\n    \
    \        assert(e != 0);\n        }\n        mint ip = p.inv();\n\n        std::vector<mint>\
    \ rp(n + 1);\n        rp[n] = 1;\n        for (int i = n - 1; i >= 0; --i) {\n\
    \            rp[i] = rp[i + 1] * vs[i];\n        }\n        std::vector<mint>\
    \ res(n);\n        for (int i = 0; i < n; ++i) {\n            res[i] = ip * rp[i\
    \ + 1];\n            ip *= vs[i];\n        }\n        return res;\n    }\n}\n\n\
    \n#line 1 \"library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n#line 6 \"\
    library/math/factorial.hpp\"\n\nnamespace suisen {\n    template <typename T,\
    \ typename U = T>\n    struct factorial {\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n\n        static void ensure(const int n) {\n           \
    \ int sz = _fac.size();\n            if (n + 1 <= sz) return;\n            int\
    \ new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n#line 7 \"library/sequence/stirling_number1.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * return:\n     *   vector<mint> v s.t. v[i] = S1[n,n-i] for\
    \ i=0,...,k (unsigned)\n     * constraints:\n     *   0 <= n <= 10^6\n     */\n\
    \    template <typename FPSType>\n    std::vector<typename FPSType::value_type>\
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
    \n\n\n\n#line 5 \"library/sequence/binomial_coefficient_small_prime_mod.hpp\"\n\
    \nnamespace suisen {\n    template <typename mint>\n    struct BinomialCoefficientSmallPrimeMod\
    \ {\n        mint operator()(long long n, long long r) const {\n            return\
    \ binom(n, r);\n        }\n        static mint binom(long long n, long long r)\
    \ {\n            factorial<mint> fac(mint::mod() - 1);\n\n            if (r <\
    \ 0 or n < r) return 0;\n            r = std::min(r, n - r);\n            // Lucas's\
    \ theorem\n            mint res = 1;\n            while (r) {\n              \
    \  int ni = n % mint::mod(), ri = r % mint::mod();\n                if (ni < ri)\
    \ return 0;\n                res *= fac.binom(ni, ri);\n                n = n\
    \ / mint::mod(), r = r / mint::mod();\n            }\n            return res;\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"library/sequence/stirling_number1_small_prime_mod.hpp\"\
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
    } // namespace suisen\n\n\n\n#line 10 \"test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t, p;\n    std::cin >> t >> p;\n\n    mint::set_mod(p);\n\n    suisen::StirlingNumber1SmallPrimeMod<mint>\
    \ s1;\n\n    for (int i = 0; i < t; ++i) {\n        long long n, k;\n        std::cin\
    \ >> n >> k;\n        std::cout << (((n - k) & 1 ? -1 : 1) * s1(n, k)).val() <<\
    \ '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\
    \n#include \"library/sequence/stirling_number1_small_prime_mod.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int t, p;\n    std::cin >> t >> p;\n\n    mint::set_mod(p);\n\n    suisen::StirlingNumber1SmallPrimeMod<mint>\
    \ s1;\n\n    for (int i = 0; i < t; ++i) {\n        long long n, k;\n        std::cin\
    \ >> n >> k;\n        std::cout << (((n - k) & 1 ? -1 : 1) * s1(n, k)).val() <<\
    \ '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/sequence/stirling_number1_small_prime_mod.hpp
  - library/sequence/stirling_number1.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  - library/sequence/binomial_coefficient_small_prime_mod.hpp
  isVerificationFile: true
  path: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
layout: document
redirect_from:
- /verify/test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
- /verify/test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp.html
title: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
---