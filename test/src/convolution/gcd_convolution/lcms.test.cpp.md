---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/gcd_convolution.hpp
    title: GCD Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/multiple.hpp
    title: library/transform/multiple.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/agc038/tasks/agc038_c
    links:
    - https://atcoder.jp/contests/agc038/tasks/agc038_c
  bundledCode: "#line 1 \"test/src/convolution/gcd_convolution/lcms.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/agc038/tasks/agc038_c\"\n\n#include <iostream>\n\
    #include <atcoder/modint>\n\n#line 1 \"library/convolution/gcd_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/transform/multiple.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n\nnamespace multiple_transform {\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto cum = [&](const int p) {\n\
    \        const int qmax = (n - 1) / p, rmax = qmax * p;\n        for (int q =\
    \ qmax, pq = rmax; q >= 1; --q, pq -= p) {\n            add_assign(f[q], f[pq]);\n\
    \            is_prime[pq] = false;\n        }\n    };\n    cum(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\n// Calculates `f` s.t.\
    \ g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T, typename SubAssign>\n\
    void mobius(std::vector<T> &f, SubAssign sub_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto diff = [&](const int p) {\n\
    \        for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n            sub_assign(f[q],\
    \ f[pq]);\n            is_prime[pq] = false;\n        }\n    };\n    diff(2);\n\
    \    for (int p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates\
    \ `g` s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ multiple_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct MultipleTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        multiple_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        multiple_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct MultipleTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        multiple_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        multiple_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename T, template <typename> class Transform>\n\
    struct Convolution {\n    static std::vector<T> convolution(std::vector<T> a,\
    \ std::vector<T> b) {\n        const int n = a.size();\n        assert(n == int(b.size()));\n\
    \        Transform<T>::transform(a);\n        Transform<T>::transform(b);\n  \
    \      for (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        const int num = a.size();\n        if (num == 0) return {};\n\
    \        const int n = a[0].size();\n        for (auto &v : a) {\n           \
    \ assert(n == int(v.size()));\n            Transform<T>::transform(v);\n     \
    \   }\n        auto &res = a[0];\n        for (int i = 1; i < num; ++i) {\n  \
    \          for (int j = 0; j < n; ++j) res[j] *= a[i][j];\n        }\n       \
    \ Transform<T>::inverse_transform(res);\n        return res;\n    }\n};\n\n} //\
    \ namespace suisen\n\n\n\n#line 6 \"library/convolution/gcd_convolution.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nusing GCDConvolution = Convolution<T,\
    \ MultipleTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T>\
    \ gcd_convolution(Args &&...args) {\n    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n#line 7 \"test/src/convolution/gcd_convolution/lcms.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nconstexpr int M = 1000000;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    std::vector<mint> count(M + 1, 0);\n   \
    \ for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n    \
    \    ++count[v];\n    }\n\n    std::vector<mint> f(M + 1);\n    for (int i = 0;\
    \ i <= M; ++i) f[i] = count[i] * i;\n\n    auto c = suisen::gcd_convolution<mint>(f,\
    \ f);\n\n    mint ans = 0;\n    for (int g = 1; g <= M; ++g) {\n        ans +=\
    \ (c[g] - f[g] * f[g]) / (2 * g);\n    }\n\n    for (int i = 1; i <= M; ++i) {\n\
    \        ans += count[i] * (count[i] - 1) * i / 2;\n    }\n    std::cout << ans.val()\
    \ << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/agc038/tasks/agc038_c\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/convolution/gcd_convolution.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nconstexpr int M = 1000000;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    std::vector<mint> count(M + 1, 0);\n   \
    \ for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n    \
    \    ++count[v];\n    }\n\n    std::vector<mint> f(M + 1);\n    for (int i = 0;\
    \ i <= M; ++i) f[i] = count[i] * i;\n\n    auto c = suisen::gcd_convolution<mint>(f,\
    \ f);\n\n    mint ans = 0;\n    for (int g = 1; g <= M; ++g) {\n        ans +=\
    \ (c[g] - f[g] * f[g]) / (2 * g);\n    }\n\n    for (int i = 1; i <= M; ++i) {\n\
    \        ans += count[i] * (count[i] - 1) * i / 2;\n    }\n    std::cout << ans.val()\
    \ << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/convolution/gcd_convolution.hpp
  - library/transform/multiple.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/gcd_convolution/lcms.test.cpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/gcd_convolution/lcms.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/gcd_convolution/lcms.test.cpp
- /verify/test/src/convolution/gcd_convolution/lcms.test.cpp.html
title: test/src/convolution/gcd_convolution/lcms.test.cpp
---
