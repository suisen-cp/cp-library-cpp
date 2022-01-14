---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/cumulative_sum_2d.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace\
    \ suisen {\n    namespace default_operator {\n        template <typename T>\n\
    \        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template\
    \ <typename T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n\
    \        template <typename T>\n        auto add(const T &x, const T &y) -> decltype(x\
    \ + y) { return x + y; }\n        template <typename T>\n        auto sub(const\
    \ T &x, const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 7 \"library/util/cumulative_sum_2d.hpp\"\n\nnamespace suisen {\n   \
    \ template <typename T, auto zero = default_operator::zero<T>, auto add = default_operator::add<T>,\
    \ auto sub = default_operator::sub<T>>\n    struct CumulativeSum2D {\n       \
    \ CumulativeSum2D() {}\n        CumulativeSum2D(const std::vector<std::vector<T>>\
    \ &a) : n(a.size()), m(n == 0 ? 0 : a[0].size()), s(n + 1, std::vector<T>(m +\
    \ 1, zero())) {\n            for (size_t i = 0; i < n; ++i) for (size_t j = 0;\
    \ j < m; ++j) {\n                s[i + 1][j + 1] = sub(add(add(a[i][j], s[i +\
    \ 1][j]), s[i][j + 1]), s[i][j]);\n            }\n        }\n        T operator()(size_t\
    \ u, size_t d, size_t l, size_t r) const {\n            if (not (u <= d and d\
    \ <= n and l <= r and r <= m)) return zero();\n            return sub(add(s[d][r],\
    \ s[u][l]), add(s[u][r], s[d][l]));\n        }\n    private:\n        size_t n,\
    \ m;\n        std::vector<std::vector<T>> s;\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_CUMULATIVE_SUM_2D\n#define SUISEN_CUMULATIVE_SUM_2D\n\n#include\
    \ <cassert>\n#include <vector>\n#include \"library/util/default_operator.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, auto zero = default_operator::zero<T>,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    struct CumulativeSum2D {\n        CumulativeSum2D() {}\n        CumulativeSum2D(const\
    \ std::vector<std::vector<T>> &a) : n(a.size()), m(n == 0 ? 0 : a[0].size()),\
    \ s(n + 1, std::vector<T>(m + 1, zero())) {\n            for (size_t i = 0; i\
    \ < n; ++i) for (size_t j = 0; j < m; ++j) {\n                s[i + 1][j + 1]\
    \ = sub(add(add(a[i][j], s[i + 1][j]), s[i][j + 1]), s[i][j]);\n            }\n\
    \        }\n        T operator()(size_t u, size_t d, size_t l, size_t r) const\
    \ {\n            if (not (u <= d and d <= n and l <= r and r <= m)) return zero();\n\
    \            return sub(add(s[d][r], s[u][l]), add(s[u][r], s[d][l]));\n     \
    \   }\n    private:\n        size_t n, m;\n        std::vector<std::vector<T>>\
    \ s;\n    };\n}\n\n#endif // SUISEN_CUMULATIVE_SUM_2D\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/util/cumulative_sum_2d.hpp
  requiredBy: []
  timestamp: '2022-01-15 00:29:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/cumulative_sum_2d.hpp
layout: document
redirect_from:
- /library/library/util/cumulative_sum_2d.hpp
- /library/library/util/cumulative_sum_2d.hpp.html
title: library/util/cumulative_sum_2d.hpp
---
