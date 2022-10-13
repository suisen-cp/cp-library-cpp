---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multiplicative_convolution_mod_2^n.hpp
    title: Multiplicative Convolution Mod 2^n ($c_k = \sum_{i\times j \equiv k \pmod{2
      ^ n}} a_i \cdot b_j$)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/mul_mod2n_convolution
    links:
    - https://judge.yosupo.jp/problem/mul_mod2n_convolution
  bundledCode: "#line 1 \"test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/mul_mod2n_convolution\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/convolution/multiplicative_convolution_mod_2^n.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <vector>\n\n#include <atcoder/convolution>\n\
    \nnamespace suisen {\n    namespace internal::mul_mod_2_n_convolution {\n    \
    \    template <typename T, int n>\n        std::vector<T> multiplicative_convolution_mod_2_n_naive(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n            static constexpr\
    \ int mask = (1 << n) - 1;\n            std::vector<T> c(1 << n);\n          \
    \  for (int i = 0; i < 1 << n; ++i) for (int j = 0; j < 1 << n; ++j) c[(i * j)\
    \ & mask] += a[i] * b[j];\n            return c;\n        }\n\n        constexpr\
    \ int pow_m1(int x) {\n            return x & 1 ? -1 : +1;\n        }\n    }\n\
    \    template <typename T>\n    std::vector<T> multiplicative_convolution_mod_2_n(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n        using namespace internal::mul_mod_2_n_convolution;\n\
    \        const int n = [&a] {\n            int n = 0;\n            while (1 <<\
    \ n < int(a.size())) ++n;\n            return n;\n        }();\n        assert(1\
    \ << n == int(a.size()));\n        assert(1 << n == int(b.size()));\n        const\
    \ int mask = (1 << n) - 1;\n        if (n <= 6) {\n            if (n == 0) return\
    \ multiplicative_convolution_mod_2_n_naive<T, 0>(a, b);\n            if (n ==\
    \ 1) return multiplicative_convolution_mod_2_n_naive<T, 1>(a, b);\n          \
    \  if (n == 2) return multiplicative_convolution_mod_2_n_naive<T, 2>(a, b);\n\
    \            if (n == 3) return multiplicative_convolution_mod_2_n_naive<T, 3>(a,\
    \ b);\n            if (n == 4) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 4>(a, b);\n            if (n == 5) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 5>(a, b);\n            if (n == 6) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 6>(a, b);\n        }\n        static constexpr int g = 5;\n        std::vector<int>\
    \ pows(1 << (n - 2));\n        std::vector<int> p(1 << n), q(1 << n), r(1 << n);\n\
    \        for (int i = 0, pow_g = 1; i < 1 << (n - 2); ++i) {\n            pows[i]\
    \ = pow_g;\n            q[pow_g] = i;\n            r[pow_g] = 0;\n           \
    \ q[-pow_g & mask] = i;\n            r[-pow_g & mask] = 1;\n            pow_g\
    \ = (pow_g * g) & mask;\n        }\n        p[0] = n;\n        for (int i = 2;\
    \ i < 1 << n; i += 2) {\n            p[i] = __builtin_ctz(i);\n            const\
    \ int len = 1 << std::max(n - p[i] - 2, 0);\n            q[i] = q[i >> p[i]] &\
    \ (len - 1);\n            r[i] = r[i >> p[i]];\n        }\n\n        std::array<std::vector<std::vector<T>>,\
    \ 2> a2{}, b2{}, c2{};\n        a2[0].resize(n + 1), a2[1].resize(n + 1);\n  \
    \      b2[0].resize(n + 1), b2[1].resize(n + 1);\n        c2[0].resize(n + 1),\
    \ c2[1].resize(n + 1);\n        for (int i = 0; i <= n; ++i) {\n            const\
    \ int len = 1 << std::max(n - i - 2, 0);\n            a2[0][i].resize(len), a2[1][i].resize(len);\n\
    \            b2[0][i].resize(len), b2[1][i].resize(len);\n            c2[0][i].resize(len),\
    \ c2[1][i].resize(len);\n        }\n        for (int i = 0; i < 1 << n; ++i) {\n\
    \            a2[r[i]][p[i]][q[i]] += a[i];\n            b2[r[i]][p[i]][q[i]] +=\
    \ b[i];\n        }\n        auto adjust_size = [](std::vector<T>& v, int len)\
    \ {\n            for (int i = len; i < int(v.size()); ++i) v[i & (len - 1)] +=\
    \ v[i];\n            v.resize(len);\n        };\n        \n        std::vector<T>\
    \ c(1 << n);\n        constexpr int naive_threshold_log = 4;\n        for (int\
    \ pi = 0; pi <= n; ++pi) for (int pj = 0; pj <= n; ++pj) {\n            const\
    \ int k = pi + pj;\n            const int len = 1 << std::max(n - k - 2, 0);\n\
    \            if (len <= 1 << naive_threshold_log) {\n                for (int\
    \ f = 0; f < 2; ++f) {\n                    adjust_size(a2[f][pi], len);\n   \
    \                 adjust_size(b2[f][pj], len);\n                }\n          \
    \      for (int af = 0; af < 2; ++af) for (int bf = 0; bf < 2; ++bf) {\n     \
    \               for (int ai = 0; ai < len; ++ai) for (int bi = 0; bi < len; ++bi)\
    \ {\n                        int j = (pow_m1(af ^ bf) * ((long long) pows[(ai\
    \ + bi) & (len - 1)] << k)) & mask;\n                        c[j] += a2[af][pi][ai]\
    \ * b2[bf][pj][bi];\n                    }\n                }\n              \
    \  continue;\n            }\n            for (int f = 0; f < 2; ++f) {\n     \
    \           adjust_size(a2[f][pi], len);\n                adjust_size(b2[f][pj],\
    \ len);\n                atcoder::internal::butterfly(a2[f][pi]);\n          \
    \      atcoder::internal::butterfly(b2[f][pj]);\n            }\n            const\
    \ T z = T{ len }.inv();\n            for (int i = 0; i < len; ++i) {\n       \
    \         T &au = a2[0][pi][i], &av = a2[1][pi][i];\n                T &bu = b2[0][pj][i],\
    \ &bv = b2[1][pj][i];\n                c2[0][k][i] += (au * bu + av * bv) * z;\n\
    \                c2[1][k][i] += (au * bv + av * bu) * z;\n                au *=\
    \ z, av *= z, bu *= z, bv *= z;\n            }\n            for (int f = 0; f\
    \ < 2; ++f) {\n                atcoder::internal::butterfly_inv(a2[f][pi]);\n\
    \                atcoder::internal::butterfly_inv(b2[f][pj]);\n            }\n\
    \        }\n        for (int f = 0; f < 2; ++f) for (int k = 0; k < n - 2 - naive_threshold_log;\
    \ ++k) {\n            const int len = 1 << (n - k - 2);\n            atcoder::internal::butterfly_inv(c2[f][k]);\n\
    \            for (int i = 0; i < len; ++i) {\n                int j = (pow_m1(f)\
    \ * ((long long) pows[i] << k)) & mask;\n                c[j] += c2[f][k][i];\n\
    \            }\n        }\n        return c;\n    }\n} // namespace suisen\n\n\
    \n\n#line 7 \"test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v,\
    \ a[i] = v;\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, b[i] = v;\n\
    \n    std::vector<mint> c = suisen::multiplicative_convolution_mod_2_n(a, b);\n\
    \n    for (int i = 0; i < 1 << n; ++i) {\n        std::cout << c[i].val();\n \
    \       if (i + 1 != 1 << n) std::cout << ' ';\n    }\n    std::cout << '\\n';\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/mul_mod2n_convolution\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/convolution/multiplicative_convolution_mod_2^n.hpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v,\
    \ a[i] = v;\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, b[i] = v;\n\
    \n    std::vector<mint> c = suisen::multiplicative_convolution_mod_2_n(a, b);\n\
    \n    for (int i = 0; i < 1 << n; ++i) {\n        std::cout << c[i].val();\n \
    \       if (i + 1 != 1 << n) std::cout << ' ';\n    }\n    std::cout << '\\n';\n\
    \    return 0;\n}"
  dependsOn:
  - library/convolution/multiplicative_convolution_mod_2^n.hpp
  isVerificationFile: true
  path: test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp
  requiredBy: []
  timestamp: '2022-10-13 20:09:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp
- /verify/test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp.html
title: test/src/convolution/multiplicative_convolution_mod_2^n/mul_mod2n_convolution.test.cpp
---
