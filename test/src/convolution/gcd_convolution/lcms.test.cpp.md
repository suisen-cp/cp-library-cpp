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
    title: "\u500D\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes: {}
  bundledCode: "#line 1 \"test/src/convolution/gcd_convolution/lcms.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/agc038/tasks/agc038_c\"\n\n#include <iostream>\n\
    #include <atcoder/modint>\n\n#line 1 \"library/convolution/gcd_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/transform/multiple.hpp\"\n\n\n\n#include <vector>\n\
    #line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace suisen {\n    namespace\
    \ default_operator {\n        template <typename T>\n        auto zero() -> decltype(T\
    \ { 0 }) { return T { 0 }; }\n        template <typename T>\n        auto one()\
    \  -> decltype(T { 1 }) { return T { 1 }; }\n        template <typename T>\n \
    \       auto add(const T &x, const T &y) -> decltype(x + y) { return x + y; }\n\
    \        template <typename T>\n        auto sub(const T &x, const T &y) -> decltype(x\
    \ - y) { return x - y; }\n        template <typename T>\n        auto mul(const\
    \ T &x, const T &y) -> decltype(x * y) { return x * y; }\n        template <typename\
    \ T>\n        auto div(const T &x, const T &y) -> decltype(x / y) { return x /\
    \ y; }\n        template <typename T>\n        auto mod(const T &x, const T &y)\
    \ -> decltype(x % y) { return x % y; }\n        template <typename T>\n      \
    \  auto neg(const T &x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(const T &x) -> decltype(one<T>() / x)  { return one<T>()\
    \ / x; }\n    } // default_operator\n} // namespace suisen\n\n\n#line 6 \"library/transform/multiple.hpp\"\
    \n\nnamespace suisen::multiple_transform {\n    // Calculates `g` s.t. g(n) =\
    \ Sum_{n | m} f(m) inplace.\n    template <typename T, auto add = default_operator::add<T>>\n\
    \    void zeta(std::vector<T> &f) {\n        const int n = f.size();\n       \
    \ std::vector<char> is_prime(n, true);\n        auto cum = [&](const int p) {\n\
    \            const int qmax = (n - 1) / p, rmax = qmax * p;\n            for (int\
    \ q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n                f[q] = add(f[q],\
    \ f[pq]);\n                is_prime[pq] = false;\n            }\n        };\n\
    \        for (int p = 2; p < n; ++p) if (is_prime[p]) cum(p);\n    }\n    // Calculates\
    \ `f` s.t. g(n) = Sum_{n | m} f(m) inplace.\n    template <typename T, auto sub\
    \ = default_operator::sub<T>>\n    void mobius(std::vector<T> &f) {\n        const\
    \ int n = f.size();\n        std::vector<char> is_prime(n, true);\n        auto\
    \ diff = [&](const int p) {\n            for (int q = 1, pq = p; pq < n; ++q,\
    \ pq += p) {\n                f[q] = sub(f[q], f[pq]);\n                is_prime[pq]\
    \ = false;\n            }\n        };\n        for (int p = 2; p < n; ++p) if\
    \ (is_prime[p]) diff(p);\n    }\n} // namespace suisen::multiple_transform\n\n\
    \n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#include <cassert>\n\
    #line 6 \"library/convolution/convolution.hpp\"\n\n#line 8 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n    namespace convolution {\n        template <typename\
    \ T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>\n\
    \        std::vector<T> transform_convolution(std::vector<T> a, std::vector<T>\
    \ b) {\n            const std::size_t n = a.size(), m = b.size();\n          \
    \  assert(n == m);\n            transform(a), transform(b);\n            for (std::size_t\
    \ i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);\n            inv_transform(a);\n\
    \            return a;\n        }\n        template <typename T, auto transform,\
    \ auto inv_transform, auto mul = default_operator::mul<T>>\n        std::vector<T>\
    \ transform_convolution(std::vector<std::vector<T>> a) {\n            const std::size_t\
    \ num = a.size();\n            assert(num);\n            const std::size_t n =\
    \ a[0].size();\n            for (auto &v : a) {\n                assert(n == int(v.size()));\n\
    \                transform(v);\n            }\n            auto &res = a[0];\n\
    \            for (int i = 1; i < num; ++i) {\n                for (int j = 0;\
    \ j < n; ++j) res[j] = mul(res[j], a[i][j]);\n            }\n            inv_transform(res);\n\
    \            return res;\n        }\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 6 \"library/convolution/gcd_convolution.hpp\"\n\nnamespace suisen {\n    template\
    \ <\n        typename T,\n        auto add = default_operator::add<T>,\n     \
    \   auto sub = default_operator::sub<T>,\n        auto mul = default_operator::mul<T>\n\
    \    >\n    auto gcd_convolution(std::vector<T> a, std::vector<T> b) {\n     \
    \   return convolution::transform_convolution<\n            T,\n            multiple_transform::zeta<T,\
    \ add>,\n            multiple_transform::mobius<T, sub>,\n            mul\n  \
    \      >(std::move(a), std::move(b));\n    }\n} // namespace suisen\n\n\n#line\
    \ 7 \"test/src/convolution/gcd_convolution/lcms.test.cpp\"\n\nusing mint = atcoder::modint998244353;\n\
    \nconstexpr int M = 1000000;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ count(M + 1, 0);\n    for (int i = 0; i < n; ++i) {\n        int v;\n      \
    \  std::cin >> v;\n        ++count[v];\n    }\n\n    std::vector<mint> f(M + 1);\n\
    \    for (int i = 0; i <= M; ++i) f[i] = count[i] * i;\n\n    auto c = suisen::gcd_convolution<mint>(f,\
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
  - library/util/default_operator.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/gcd_convolution/lcms.test.cpp
  requiredBy: []
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/gcd_convolution/lcms.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/gcd_convolution/lcms.test.cpp
- /verify/test/src/convolution/gcd_convolution/lcms.test.cpp.html
title: test/src/convolution/gcd_convolution/lcms.test.cpp
---
