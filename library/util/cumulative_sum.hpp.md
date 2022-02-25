---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/cumulative_sum.hpp\"\n\n\n\n#include <cassert>\n\
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
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n    namespace default_operator_noref\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 7 \"library/util/cumulative_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, auto zero = default_operator::zero<T>,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    struct CumulativeSum {\n        CumulativeSum() {}\n        CumulativeSum(const\
    \ std::vector<T> &a) : n(a.size()), s(n + 1, zero()) {\n            for (size_t\
    \ i = 0; i < n; ++i) s[i + 1] = add(a[i], s[i]);\n        }\n        T operator()(size_t\
    \ l, size_t r) const {\n            assert(l <= r and r <= n);\n            return\
    \ sub(s[r], s[l]);\n        }\n    private:\n        size_t n;\n        std::vector<T>\
    \ s;\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_CUMULATIVE_SUM\n#define SUISEN_CUMULATIVE_SUM\n\n#include\
    \ <cassert>\n#include <vector>\n#include \"library/util/default_operator.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, auto zero = default_operator::zero<T>,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    struct CumulativeSum {\n        CumulativeSum() {}\n        CumulativeSum(const\
    \ std::vector<T> &a) : n(a.size()), s(n + 1, zero()) {\n            for (size_t\
    \ i = 0; i < n; ++i) s[i + 1] = add(a[i], s[i]);\n        }\n        T operator()(size_t\
    \ l, size_t r) const {\n            assert(l <= r and r <= n);\n            return\
    \ sub(s[r], s[l]);\n        }\n    private:\n        size_t n;\n        std::vector<T>\
    \ s;\n    };\n}\n\n#endif // SUISEN_CUMULATIVE_SUM\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/util/cumulative_sum.hpp
  requiredBy: []
  timestamp: '2022-01-31 13:34:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/cumulative_sum.hpp
layout: document
title: Cumulative Sum
---
## Cumulative Sum