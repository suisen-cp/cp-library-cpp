---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: library/transform/kronecker_power.hpp
  - icon: ':question:'
    path: library/transform/walsh_hadamard.hpp
    title: "Walsh Hadamard \u5909\u63DB"
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"test/src/convolution/xor_convolution/xor_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/convolution/xor_convolution.hpp\"\
    \n\n\n\n#line 1 \"library/transform/walsh_hadamard.hpp\"\n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\
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
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/transform/walsh_hadamard.hpp\"\
    \n\nnamespace suisen::walsh_hadamard_transform {\n    namespace internal {\n \
    \       template <typename T, auto add = default_operator::add<T>, auto sub =\
    \ default_operator::sub<T>>\n        void unit_transform(T& x0, T& x1) {\n   \
    \         T y0 = x0, y1 = x1;\n            x0 = add(y0, y1);   // 1,  1\n    \
    \        x1 = sub(y0, y1);   // 1, -1\n        }\n    } // namespace internal\n\
    \n    using kronecker_power_transform::kronecker_power_transform;\n\n    template\
    \ <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    void walsh_hadamard(std::vector<T>& a) {\n        kronecker_power_transform<T,\
    \ 2, internal::unit_transform<T, add, sub>>(a);\n    }\n    template <typename\
    \ T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>,\
    \ auto div = default_operator::div<T>, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_walsh_hadamard_inv(std::vector<T>&\
    \ a) {\n        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n\
    \        for (auto& val : a) val = div(val, n);\n    }\n    template <typename\
    \ T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>,\
    \ auto mul = default_operator::mul<T>, auto inv = default_operator::inv<T>, std::enable_if_t<std::negation_v<std::is_integral<T>>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     const T inv_n = inv(n);\n        for (auto& val : a) val = mul(val, inv_n);\n\
    \    }\n} // namespace suisen::walsh_hadamard_transform\n\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#line 6 \"library/convolution/convolution.hpp\"\n\n#line 8 \"library/convolution/convolution.hpp\"\
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
    \ 6 \"library/convolution/xor_convolution.hpp\"\n\nnamespace suisen {\n    template\
    \ <\n        typename T,\n        auto add = default_operator::add<T>,\n     \
    \   auto sub = default_operator::sub<T>,\n        auto mul = default_operator::mul<T>,\n\
    \        auto div = default_operator::div<T>,\n        std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr\n    >\n        auto xor_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        return convolution::transform_convolution<\n\
    \            T,\n            walsh_hadamard_transform::walsh_hadamard<T, add,\
    \ sub>,\n            walsh_hadamard_transform::walsh_hadamard_inv<T, add, sub,\
    \ div>,\n            mul\n        >(std::move(a), std::move(b));\n    }\n\n  \
    \  template <\n        typename T,\n        auto add = default_operator::add<T>,\n\
    \        auto sub = default_operator::sub<T>,\n        auto mul = default_operator::mul<T>,\n\
    \        auto inv = default_operator::inv<T>,\n        std::enable_if_t<std::negation_v<std::is_integral<T>>,\
    \ std::nullptr_t> = nullptr\n    >\n        auto xor_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        return convolution::transform_convolution<\n\
    \            T,\n            walsh_hadamard_transform::walsh_hadamard<T, add,\
    \ sub>,\n            walsh_hadamard_transform::walsh_hadamard_inv<T, add, sub,\
    \ mul, inv>,\n            mul\n        >(std::move(a), std::move(b));\n    }\n\
    } // namespace suisen\n\n\n#line 7 \"test/src/convolution/xor_convolution/xor_convolution.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::xor_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/convolution/xor_convolution.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nstd::istream& operator>>(std::istream&\
    \ in, mint &a) {\n    long long e; in >> e; a = e;\n    return in;\n}\n\nstd::ostream&\
    \ operator<<(std::ostream& out, const mint &a) {\n    out << a.val();\n    return\
    \ out;\n}\n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out,\
    \ const std::vector<T> &a) {\n    int n = a.size();\n    for (int i = 0; i < n;\
    \ ++i) {\n        out << a[i];\n        if (i != n - 1) out << ' ';\n    }\n \
    \   return out;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (auto &v : a) std::cin >> v;\n    for (auto &v\
    \ : b) std::cin >> v;\n    std::cout << suisen::xor_convolution<mint>(std::move(a),\
    \ std::move(b)) << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/convolution/xor_convolution.hpp
  - library/transform/walsh_hadamard.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: true
  path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-09-29 03:14:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/xor_convolution/xor_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/xor_convolution/xor_convolution.test.cpp
- /verify/test/src/convolution/xor_convolution/xor_convolution.test.cpp.html
title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
---
