---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/shift_of_sampling_points.hpp
    title: Shift of Sampling Points of Polynomial
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
    links:
    - https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
  bundledCode: "#line 1 \"test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n#line 1 \"library/polynomial/shift_of_sampling_points.hpp\"\
    \n\n\n\n#include <vector>\n#include <atcoder/convolution>\n\n#line 1 \"library/math/factorial.hpp\"\
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
    \ t, m, convolve);\n    }\n} // namespace suisen\n\n\n\n#line 6 \"test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, c;\n    std::cin >> n >> m >> c;\n\
    \n    std::vector<mint> ys(n);\n    for (int i = 0, v; i < n; ++i) std::cin >>\
    \ v, ys[i] = v;\n\n    std::vector<mint> ans = suisen::shift_of_sampling_points<mint>(ys,\
    \ c, m);\n    for (int i = 0; i < m; ++i) {\n        std::cout << ans[i].val();\n\
    \        if (i + 1 != m) std::cout << ' ';\n    }\n    std::cout << '\\n';\n \
    \   return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n#include \"library/polynomial/shift_of_sampling_points.hpp\"\
    \n\nint main() {\n    using mint = atcoder::modint998244353;\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, c;\n    std::cin >> n >> m >> c;\n\
    \n    std::vector<mint> ys(n);\n    for (int i = 0, v; i < n; ++i) std::cin >>\
    \ v, ys[i] = v;\n\n    std::vector<mint> ans = suisen::shift_of_sampling_points<mint>(ys,\
    \ c, m);\n    for (int i = 0; i < m; ++i) {\n        std::cout << ans[i].val();\n\
    \        if (i + 1 != m) std::cout << ' ';\n    }\n    std::cout << '\\n';\n \
    \   return 0;\n}"
  dependsOn:
  - library/polynomial/shift_of_sampling_points.hpp
  - library/math/factorial.hpp
  isVerificationFile: true
  path: test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 20:59:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
layout: document
redirect_from:
- /verify/test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
- /verify/test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp.html
title: test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
---
