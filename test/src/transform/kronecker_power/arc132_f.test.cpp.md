---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc132/tasks/arc132_f
    links:
    - https://atcoder.jp/contests/arc132/tasks/arc132_f
  bundledCode: "#line 1 \"test/src/transform/kronecker_power/arc132_f.test.cpp\"\n\
    #define PROBLEM \"https://atcoder.jp/contests/arc132/tasks/arc132_f\"\n\n#include\
    \ <array>\n#include <iostream>\n\n#line 1 \"library/transform/kronecker_power.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"\
    library/util/default_operator.hpp\"\n\n\n\nnamespace suisen {\n    namespace default_operator\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(const\
    \ T &x, const T &y) -> decltype(x + y) { return x + y; }\n        template <typename\
    \ T>\n        auto sub(const T &x, const T &y) -> decltype(x - y) { return x -\
    \ y; }\n        template <typename T>\n        auto mul(const T &x, const T &y)\
    \ -> decltype(x * y) { return x * y; }\n        template <typename T>\n      \
    \  auto div(const T &x, const T &y) -> decltype(x / y) { return x / y; }\n   \
    \     template <typename T>\n        auto mod(const T &x, const T &y) -> decltype(x\
    \ % y) { return x % y; }\n        template <typename T>\n        auto neg(const\
    \ T &x) -> decltype(-x) { return -x; }\n        template <typename T>\n      \
    \  auto inv(const T &x) -> decltype(one<T>() / x)  { return one<T>() / x; }\n\
    \    } // default_operator\n    namespace default_operator_noref {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(T x, T y) -> decltype(x\
    \ + y) { return x + y; }\n        template <typename T>\n        auto sub(T x,\
    \ T y) -> decltype(x - y) { return x - y; }\n        template <typename T>\n \
    \       auto mul(T x, T y) -> decltype(x * y) { return x * y; }\n        template\
    \ <typename T>\n        auto div(T x, T y) -> decltype(x / y) { return x / y;\
    \ }\n        template <typename T>\n        auto mod(T x, T y) -> decltype(x %\
    \ y) { return x % y; }\n        template <typename T>\n        auto neg(T x) ->\
    \ decltype(-x) { return -x; }\n        template <typename T>\n        auto inv(T\
    \ x) -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    } // namespace suisen\n\n\n#line 9 \"library/transform/kronecker_power.hpp\"\n\
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
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 7 \"test/src/transform/kronecker_power/arc132_f.test.cpp\"\
    \n\nusing suisen::kronecker_power_transform::kronecker_power_transform;\n\nvoid\
    \ trans(long long &x0, long long &x1, long long &x2, long long &x3) {\n    x3\
    \ += x0 + x1 + x2;\n}\n \nvoid trans2(long long &x0, long long &x1, long long\
    \ &x2, long long &x3) {\n    x0 = x3 - x0;\n    x1 = x3 - x1;\n    x2 = x3 - x2;\n\
    \    x3 = 0;\n}\n \nint main() {\n    std::array<int, 256> mp;\n    mp['P'] =\
    \ 0, mp['R'] = 1, mp['S'] = 2;\n \n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n \n    int k, n, m;\n    std::cin >> k >> n >> m;\n\
    \ \n    auto count = [&](int num) {\n        std::vector<long long> f(1 << (2\
    \ * k), 0);\n        for (int i = 0; i < num; ++i) {\n            int a = 0;\n\
    \            for (int j = 0; j < k; ++j) {\n                char c;\n        \
    \        std::cin >> c;\n                a |= mp[c] << (2 * j);\n            }\n\
    \            ++f[a];\n        }\n        return f;\n    };\n    auto f = count(n),\
    \ g = count(m);\n \n    kronecker_power_transform<long long, 4, trans>(f);\n \
    \   kronecker_power_transform<long long, 4, trans>(g);\n    for (int i = 0; i\
    \ < 1 << (2 * k); ++i) f[i] *= g[i];\n    kronecker_power_transform<long long,\
    \ 4, trans2>(f);\n \n    int pow3 = 1;\n    for (int i = 0; i < k; ++i) pow3 *=\
    \ 3;\n \n    for (int i = 0; i < pow3; ++i) {\n        int v = 0;\n        for\
    \ (int t = i, j = 0; j < k; ++j, t /= 3) {\n            int d = t % 3;\n     \
    \       v |= (d == 2 ? 0 : d + 1) << (2 * (k - j - 1));\n        }\n        std::cout\
    \ << (long long) n * m - f[v] << '\\n';\n    }\n    \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc132/tasks/arc132_f\"\n\n\
    #include <array>\n#include <iostream>\n\n#include \"library/transform/kronecker_power.hpp\"\
    \n\nusing suisen::kronecker_power_transform::kronecker_power_transform;\n\nvoid\
    \ trans(long long &x0, long long &x1, long long &x2, long long &x3) {\n    x3\
    \ += x0 + x1 + x2;\n}\n \nvoid trans2(long long &x0, long long &x1, long long\
    \ &x2, long long &x3) {\n    x0 = x3 - x0;\n    x1 = x3 - x1;\n    x2 = x3 - x2;\n\
    \    x3 = 0;\n}\n \nint main() {\n    std::array<int, 256> mp;\n    mp['P'] =\
    \ 0, mp['R'] = 1, mp['S'] = 2;\n \n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n \n    int k, n, m;\n    std::cin >> k >> n >> m;\n\
    \ \n    auto count = [&](int num) {\n        std::vector<long long> f(1 << (2\
    \ * k), 0);\n        for (int i = 0; i < num; ++i) {\n            int a = 0;\n\
    \            for (int j = 0; j < k; ++j) {\n                char c;\n        \
    \        std::cin >> c;\n                a |= mp[c] << (2 * j);\n            }\n\
    \            ++f[a];\n        }\n        return f;\n    };\n    auto f = count(n),\
    \ g = count(m);\n \n    kronecker_power_transform<long long, 4, trans>(f);\n \
    \   kronecker_power_transform<long long, 4, trans>(g);\n    for (int i = 0; i\
    \ < 1 << (2 * k); ++i) f[i] *= g[i];\n    kronecker_power_transform<long long,\
    \ 4, trans2>(f);\n \n    int pow3 = 1;\n    for (int i = 0; i < k; ++i) pow3 *=\
    \ 3;\n \n    for (int i = 0; i < pow3; ++i) {\n        int v = 0;\n        for\
    \ (int t = i, j = 0; j < k; ++j, t /= 3) {\n            int d = t % 3;\n     \
    \       v |= (d == 2 ? 0 : d + 1) << (2 * (k - j - 1));\n        }\n        std::cout\
    \ << (long long) n * m - f[v] << '\\n';\n    }\n    \n    return 0;\n}"
  dependsOn:
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/transform/kronecker_power/arc132_f.test.cpp
  requiredBy: []
  timestamp: '2022-06-05 20:18:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/transform/kronecker_power/arc132_f.test.cpp
layout: document
redirect_from:
- /verify/test/src/transform/kronecker_power/arc132_f.test.cpp
- /verify/test/src/transform/kronecker_power/arc132_f.test.cpp.html
title: test/src/transform/kronecker_power/arc132_f.test.cpp
---
