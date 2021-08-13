---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/convolution/polynomial_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1"
  - icon: ':question:'
    path: library/transform/walsh_hadamard.hpp
    title: "Walsh Hadamard \u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc212/tasks/abc212_h
    links:
    - https://atcoder.jp/contests/abc212/tasks/abc212_h
  bundledCode: "#line 1 \"test/src/convolution/polynomial_eval/nim_counting.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc212/tasks/abc212_h\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/transform/walsh_hadamard.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen::internal::arithmetic_operator\
    \ {}\n\nnamespace suisen {\nnamespace walsh_hadamard {\ntemplate <typename T>\n\
    void fwht(std::vector<T>& a, bool rev) {\n    using namespace suisen::internal::arithmetic_operator;\n\
    \    const int n = a.size();\n    assert((-n & n) == n);\n    for (int i = 1;\
    \ i < n; i *= 2) {\n        for (int k = 0; k < n; k += i * 2) {\n           \
    \ for (int j = k; j < k + i; ++j) {\n                T u = a[j], v = a[j + i];\n\
    \                a[j] = u + v;\n                a[j + i] = u - v;\n          \
    \  }\n        }\n    }\n    if (rev) {\n        T inv = T(1) / T(n);\n       \
    \ for (int i = 0; i < n; i++) a[i] *= inv;\n    }\n}\n} // nemaspace walsh_hadamard\n\
    \ntemplate <typename T>\nstruct WalshHadamard {\n    static void transform(std::vector<T>\
    \ &a) {\n        walsh_hadamard::fwht(a, false);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        walsh_hadamard::fwht(a, true);\n    }\n};\n\n} // namespace suisen::walsh_hadamard_transform\n\
    \n\n\n#line 1 \"library/convolution/polynomial_eval.hpp\"\n\n\n\n#line 5 \"library/convolution/polynomial_eval.hpp\"\
    \n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 7 \"\
    library/convolution/polynomial_eval.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, template <typename> class Transform, typename F, constraints_t<is_same_as_invoke_result<T,\
    \ F, T>> = nullptr>\nstd::vector<T> polynomial_eval(std::vector<T> &&a, F f) {\n\
    \    Transform<T>::transform(a);\n    for (auto &x : a) x = f(x);\n    Transform<T>::inverse_transform(a);\n\
    \    return a;\n}\n\ntemplate <typename T, template <typename> class Transform,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ polynomial_eval(const std::vector<T> &a, F f) {\n    return polynomial_eval<T,\
    \ Transform>(std::vector<T>(a), f);\n}\n\n} // namespace suisen\n\n\n\n#line 8\
    \ \"test/src/convolution/polynomial_eval/nim_counting.test.cpp\"\n\nusing mint\
    \ = atcoder::modint998244353;\n\nconstexpr int M = 1 << 16;\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, k;\n    std::cin >> n >> k;\n\n    std::vector<mint> c(M, 0);\n    for (int\
    \ i = 0; i < k; ++i) {\n        int v;\n        std::cin >> v;\n        ++c[v];\n\
    \    }\n\n    auto res = suisen::polynomial_eval<mint, suisen::WalshHadamard>(c,\
    \ [n](mint x) {\n        return x == 1 ? n : x * (x.pow(n) - 1) / (x - 1);\n \
    \   });\n\n    std::cout << std::accumulate(res.begin() + 1, res.end(), mint(0)).val()\
    \ << std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc212/tasks/abc212_h\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/transform/walsh_hadamard.hpp\"\
    \n#include \"library/convolution/polynomial_eval.hpp\"\n\nusing mint = atcoder::modint998244353;\n\
    \nconstexpr int M = 1 << 16;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, k;\n    std::cin >> n >> k;\n\n    std::vector<mint>\
    \ c(M, 0);\n    for (int i = 0; i < k; ++i) {\n        int v;\n        std::cin\
    \ >> v;\n        ++c[v];\n    }\n\n    auto res = suisen::polynomial_eval<mint,\
    \ suisen::WalshHadamard>(c, [n](mint x) {\n        return x == 1 ? n : x * (x.pow(n)\
    \ - 1) / (x - 1);\n    });\n\n    std::cout << std::accumulate(res.begin() + 1,\
    \ res.end(), mint(0)).val() << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/transform/walsh_hadamard.hpp
  - library/convolution/polynomial_eval.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/convolution/polynomial_eval/nim_counting.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/polynomial_eval/nim_counting.test.cpp
- /verify/test/src/convolution/polynomial_eval/nim_counting.test.cpp.html
title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
---
