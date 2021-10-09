---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/polynomial_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1"
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/walsh_hadamard.hpp
    title: "Walsh Hadamard \u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc212/tasks/abc212_h
    links:
    - https://atcoder.jp/contests/abc212/tasks/abc212_h
  bundledCode: "#line 1 \"test/src/convolution/polynomial_eval/nim_counting.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc212/tasks/abc212_h\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/transform/walsh_hadamard.hpp\"\
    \n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace\
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
    \n\n#line 8 \"library/transform/kronecker_power.hpp\"\n\nnamespace suisen {\n\
    \    namespace kronecker_power_transform {\n        namespace internal {\n   \
    \         template <typename UnitTransform, typename ReferenceGetter, std::size_t...\
    \ Seq>\n            void unit_transform(UnitTransform transform, ReferenceGetter\
    \ ref_getter, std::index_sequence<Seq...>) {\n                transform(ref_getter(Seq)...);\n\
    \            }\n        }\n\n        template <typename T, std::size_t D, auto\
    \ unit_transform>\n        void kronecker_power_transform(std::vector<T> &x) {\n\
    \            const std::size_t n = x.size();\n            for (std::size_t block\
    \ = 1; block < n; block *= D) {\n                for (std::size_t l = 0; l < n;\
    \ l += D * block) {\n                    for (std::size_t offset = l; offset <\
    \ l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
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
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     for (auto& val : a) val = div(val, n);\n    }\n    template <typename T,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto\
    \ mul = default_operator::mul<T>, auto inv = default_operator::inv<T>, std::enable_if_t<std::negation_v<std::is_integral<T>>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     const T inv_n = inv(n);\n        for (auto& val : a) val = mul(val, inv_n);\n\
    \    }\n} // namespace suisen::walsh_hadamard_transform\n\n\n\n#line 1 \"library/convolution/polynomial_eval.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/polynomial_eval.hpp\"\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 7 \"library/convolution/polynomial_eval.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, auto transform, auto transform_inv,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\n  \
    \  std::vector<T> polynomial_eval(std::vector<T> &&a, F f) {\n        transform(a);\n\
    \        for (auto &x : a) x = f(x);\n        transform_inv(a);\n        return\
    \ a;\n    }\n\n    template <typename T, auto transform, auto transform_inv, typename\
    \ F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\n    std::vector<T>\
    \ polynomial_eval(const std::vector<T> &a, F f) {\n        return polynomial_eval<T,\
    \ transform, transform_inv>(std::vector<T>(a), f);\n    }\n} // namespace suisen\n\
    \n\n#line 8 \"test/src/convolution/polynomial_eval/nim_counting.test.cpp\"\nusing\
    \ namespace suisen;\n\nusing mint = atcoder::modint998244353;\n\nconstexpr int\
    \ M = 1 << 16;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, k;\n    std::cin >> n >> k;\n\n    std::vector<mint> c(M, 0);\n \
    \   for (int i = 0; i < k; ++i) {\n        int v;\n        std::cin >> v;\n  \
    \      ++c[v];\n    }\n\n    using namespace walsh_hadamard_transform;\n\n   \
    \ auto res = suisen::polynomial_eval<mint, walsh_hadamard<mint>, walsh_hadamard_inv<mint>>(c,\
    \ [n](mint x) {\n        return x == 1 ? n : x * (x.pow(n) - 1) / (x - 1);\n \
    \       });\n\n    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val()\
    \ << std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc212/tasks/abc212_h\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/transform/walsh_hadamard.hpp\"\
    \n#include \"library/convolution/polynomial_eval.hpp\"\nusing namespace suisen;\n\
    \nusing mint = atcoder::modint998244353;\n\nconstexpr int M = 1 << 16;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, k;\n    std::cin >> n >> k;\n\n    std::vector<mint> c(M, 0);\n \
    \   for (int i = 0; i < k; ++i) {\n        int v;\n        std::cin >> v;\n  \
    \      ++c[v];\n    }\n\n    using namespace walsh_hadamard_transform;\n\n   \
    \ auto res = suisen::polynomial_eval<mint, walsh_hadamard<mint>, walsh_hadamard_inv<mint>>(c,\
    \ [n](mint x) {\n        return x == 1 ? n : x * (x.pow(n) - 1) / (x - 1);\n \
    \       });\n\n    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val()\
    \ << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/transform/walsh_hadamard.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  - library/convolution/polynomial_eval.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  requiredBy: []
  timestamp: '2021-10-10 02:52:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/polynomial_eval/nim_counting.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/polynomial_eval/nim_counting.test.cpp
- /verify/test/src/convolution/polynomial_eval/nim_counting.test.cpp.html
title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
---
