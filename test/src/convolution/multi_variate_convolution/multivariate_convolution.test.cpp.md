---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution.hpp
    title: Multi Variate Convolution
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/multivariate_convolution
    links:
    - https://judge.yosupo.jp/problem/multivariate_convolution
  bundledCode: "#line 1 \"test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/multivariate_convolution\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/convolution/multi_variate_convolution.hpp\"\
    \n\n\n\n#include <numeric>\n#include <atcoder/convolution>\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 8 \"library/convolution/multi_variate_convolution.hpp\"\n\nnamespace\
    \ suisen {\n    struct multi_variate_convolution {\n        multi_variate_convolution()\
    \ : multi_variate_convolution(std::vector<int>{}) {}\n        multi_variate_convolution(const\
    \ std::vector<int> &dim) : _n(std::accumulate(dim.begin(), dim.end(), 1, std::multiplies<int>())),\
    \ _k(dim.size()), _m(2 * ceil_pow2(_n)), _chi(_n, 0) {\n            for (int i\
    \ = 0; i < _n; ++i) {\n                int den = 1;\n                for (int\
    \ e : dim) den *= e, _chi[i] += i / den;\n                if (_k) _chi[i] %= _k;\n\
    \            }\n        }\n\n        int size() const { return _n; }\n       \
    \ int dim_num() const { return _k; }\n\n        template <typename T, typename\
    \ Inverse = decltype(default_operator::inv<T>)>\n        std::vector<T> convolution(std::vector<T>\
    \ f, std::vector<T> g, Inverse inv = default_operator::inv<T>) const {\n     \
    \       assert(int(f.size()) == _n and int(g.size()) == _n);\n            if (_k\
    \ == 0) return { f[0] * g[0] };\n            auto rf = ranked(f), rg = ranked(g);\n\
    \            for (auto &v : rf) atcoder::internal::butterfly(v);\n           \
    \ for (auto &v : rg) atcoder::internal::butterfly(v);\n            std::vector\
    \ rh(_k, std::vector<T>(_m, T{}));\n            for (int i = 0; i < _k; ++i) for\
    \ (int j = 0; j < _k; ++j) {\n                int r = i + j < _k ? i + j : i +\
    \ j - _k;\n                for (int p = 0; p < _m; ++p) rh[r][p] += rf[i][p] *\
    \ rg[j][p];\n            }\n            for (auto &v : rh) atcoder::internal::butterfly_inv(v);\n\
    \            const T isz = inv(T(_m));\n            std::vector<T> h(_n);\n  \
    \          for (int i = 0; i < _n; ++i) h[i] = rh[_chi[i]][i] * isz;\n       \
    \     return h;\n        }\n\n        template <typename T>\n        std::vector<T>\
    \ operator()(std::vector<T> f, std::vector<T> g) const {\n            return convolution(f,\
    \ g);\n        }\n\n    private:\n        int _n, _k, _m;\n        std::vector<int>\
    \ _chi;\n\n        static constexpr int ceil_pow2(int m) {\n            int res\
    \ = 1;\n            while (res < m) res *= 2;\n            return res;\n     \
    \   }\n\n        template <typename T>\n        auto ranked(const std::vector<T>\
    \ &f) const {\n            std::vector rf(_k, std::vector<T>(_m, T{}));\n    \
    \        for (int i = 0; i < _n; ++i) rf[_chi[i]][i] = f[i];\n            return\
    \ rf;\n        }\n    };\n} // namespace suisen\n\n\n\n#line 19 \"test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp\"\
    \nusing namespace suisen;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int k;\n    std::cin >> k;\n    std::vector<int>\
    \ dim(k);\n    for (int &e : dim) std::cin >> e;\n\n    multi_variate_convolution\
    \ convolution(dim);\n    int n = convolution.size();\n\n    std::vector<mint>\
    \ f(n), g(n);\n    for (auto &e : f) std::cin >> e;\n    for (auto &e : g) std::cin\
    \ >> e;\n    auto h = convolution(f, g);\n\n    for (int i = 0; i < n; ++i) std::cout\
    \ << h[i] << \" \\n\"[i == n - 1];\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multivariate_convolution\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/convolution/multi_variate_convolution.hpp\"\
    \nusing namespace suisen;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int k;\n    std::cin >> k;\n    std::vector<int>\
    \ dim(k);\n    for (int &e : dim) std::cin >> e;\n\n    multi_variate_convolution\
    \ convolution(dim);\n    int n = convolution.size();\n\n    std::vector<mint>\
    \ f(n), g(n);\n    for (auto &e : f) std::cin >> e;\n    for (auto &e : g) std::cin\
    \ >> e;\n    auto h = convolution(f, g);\n\n    for (int i = 0; i < n; ++i) std::cout\
    \ << h[i] << \" \\n\"[i == n - 1];\n\n    return 0;\n}"
  dependsOn:
  - library/convolution/multi_variate_convolution.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
  requiredBy: []
  timestamp: '2022-01-31 13:34:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
- /verify/test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp.html
title: test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
---
