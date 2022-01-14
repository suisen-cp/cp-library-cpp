---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/supset.hpp
    title: "\u4E0A\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/src/convolution/and_convolution/and_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/convolution/and_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/transform/supset.hpp\"\n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\
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
    } // namespace suisen\n\n\n#line 8 \"library/transform/kronecker_power.hpp\"\n\
    \nnamespace suisen {\n    namespace kronecker_power_transform {\n        namespace\
    \ internal {\n            template <typename UnitTransform, typename ReferenceGetter,\
    \ std::size_t... Seq>\n            void unit_transform(UnitTransform transform,\
    \ ReferenceGetter ref_getter, std::index_sequence<Seq...>) {\n               \
    \ transform(ref_getter(Seq)...);\n            }\n        }\n\n        template\
    \ <typename T, std::size_t D, auto unit_transform>\n        void kronecker_power_transform(std::vector<T>\
    \ &x) {\n            const std::size_t n = x.size();\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/transform/supset.hpp\"\
    \n\nnamespace suisen::supset_transform {\n    namespace internal {\n        template\
    \ <typename T, auto add = default_operator::add<T>>\n        void zeta_unit_transform(T\
    \ &x0, T &x1) {\n            x0 = add(x0, x1);   // 1, 1\n                   \
    \             // 0, 1\n        }\n        template <typename T, auto sub = default_operator::sub<T>>\n\
    \        void mobius_unit_transform(T &x0, T &x1) {\n            x0 = sub(x0,\
    \ x1);   // 1, -1\n                                // 0,  1\n        }\n    }\
    \ // namespace internal\n\n    using kronecker_power_transform::kronecker_power_transform;\n\
    \n    template <typename T, auto add = default_operator::add<T>>\n    void zeta(std::vector<T>\
    \ &a) {\n        kronecker_power_transform<T, 2, internal::zeta_unit_transform<T,\
    \ add>>(a);\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void mobius(std::vector<T> &a) {\n        kronecker_power_transform<T, 2,\
    \ internal::mobius_unit_transform<T, sub>>(a);\n    }\n} // namespace suisen::supset_transform\n\
    \n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 6 \"library/convolution/convolution.hpp\"\
    \n\n#line 8 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n  \
    \  namespace convolution {\n        template <typename T, auto transform, auto\
    \ inv_transform, auto mul = default_operator::mul<T>>\n        std::vector<T>\
    \ transform_convolution(std::vector<T> a, std::vector<T> b) {\n            const\
    \ std::size_t n = a.size(), m = b.size();\n            assert(n == m);\n     \
    \       transform(a), transform(b);\n            for (std::size_t i = 0; i < n;\
    \ ++i) a[i] = mul(a[i], b[i]);\n            inv_transform(a);\n            return\
    \ a;\n        }\n        template <typename T, auto transform, auto inv_transform,\
    \ auto mul = default_operator::mul<T>>\n        std::vector<T> transform_convolution(std::vector<std::vector<T>>\
    \ a) {\n            const std::size_t num = a.size();\n            assert(num);\n\
    \            const std::size_t n = a[0].size();\n            for (auto &v : a)\
    \ {\n                assert(n == int(v.size()));\n                transform(v);\n\
    \            }\n            auto &res = a[0];\n            for (int i = 1; i <\
    \ num; ++i) {\n                for (int j = 0; j < n; ++j) res[j] = mul(res[j],\
    \ a[i][j]);\n            }\n            inv_transform(res);\n            return\
    \ res;\n        }\n    }\n} // namespace suisen\n\n\n\n#line 6 \"library/convolution/and_convolution.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T,\n        auto add\
    \ = default_operator::add<T>,\n        auto sub = default_operator::sub<T>,\n\
    \        auto mul = default_operator::mul<T>\n    >\n    auto and_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        return convolution::transform_convolution<\n\
    \            T,\n            supset_transform::zeta<T, add>,\n            supset_transform::mobius<T,\
    \ sub>,\n            mul\n        >(std::move(a), std::move(b));\n    }\n} //\
    \ namespace suisen\n\n\n#line 7 \"test/src/convolution/and_convolution/and_convolution.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::and_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/convolution/and_convolution.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::and_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/convolution/and_convolution.hpp
  - library/transform/supset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/and_convolution/and_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/and_convolution/and_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/and_convolution/and_convolution.test.cpp
- /verify/test/src/convolution/and_convolution/and_convolution.test.cpp.html
title: test/src/convolution/and_convolution/and_convolution.test.cpp
---
