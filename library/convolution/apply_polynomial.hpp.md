---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/apply_polynomial/nim_counting.test.cpp
    title: test/src/convolution/apply_polynomial/nim_counting.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/apply_polynomial.hpp\"\n\n\n\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    library/convolution/apply_polynomial.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, template <typename> class Transform, typename F, constraints_t<is_same_as_invoke_result<T,\
    \ F, T>> = nullptr>\nstd::vector<T> apply_polynomial(std::vector<T> &&a, F f)\
    \ {\n    Transform<T>::transform(a);\n    for (auto &x : a) x = f(x);\n    Transform<T>::inverse_transform(a);\n\
    \    return a;\n}\n\ntemplate <typename T, template <typename> class Transform,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(const std::vector<T> &a, F f) {\n    return apply_polynomial<T,\
    \ Transform>(std::vector<T>(a), f);\n}\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL\n#define SUISEN_APPLY_POLYNOMIAL\n\n#include\
    \ <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen\
    \ {\n\ntemplate <typename T, template <typename> class Transform, typename F,\
    \ constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(std::vector<T> &&a, F f) {\n    Transform<T>::transform(a);\n\
    \    for (auto &x : a) x = f(x);\n    Transform<T>::inverse_transform(a);\n  \
    \  return a;\n}\n\ntemplate <typename T, template <typename> class Transform,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(const std::vector<T> &a, F f) {\n    return apply_polynomial<T,\
    \ Transform>(std::vector<T>(a), f);\n}\n\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_APPLY_POLYNOMIAL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/convolution/apply_polynomial.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/convolution/apply_polynomial/nim_counting.test.cpp
documentation_of: library/convolution/apply_polynomial.hpp
layout: document
redirect_from:
- /library/library/convolution/apply_polynomial.hpp
- /library/library/convolution/apply_polynomial.hpp.html
title: library/convolution/apply_polynomial.hpp
---
