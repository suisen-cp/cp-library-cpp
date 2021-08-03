---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_segment_tree.hpp
    title: library/datastructure/lazy_segment_tree.hpp
  - icon: ':x:'
    path: library/datastructure/segment_tree.hpp
    title: library/datastructure/segment_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 1 \"\
    library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include <type_traits>\n\
    \nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 5 \"\
    library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>>\nstruct\
    \ UpdateProxyObject {\n    T &v;\n    UpdateFunc update;\n    UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n    operator T() const { return\
    \ v; }\n    auto& operator++() { ++v, update(); return *this; }\n    auto& operator--()\
    \ { --v, update(); return *this; }\n    auto& operator+=(const T &val) { v +=\
    \ val, update(); return *this; }\n    auto& operator-=(const T &val) { v -= val,\
    \ update(); return *this; }\n    auto& operator*=(const T &val) { v *= val, update();\
    \ return *this; }\n    auto& operator/=(const T &val) { v /= val, update(); return\
    \ *this; }\n    auto& operator%=(const T &val) { v %= val, update(); return *this;\
    \ }\n    auto& operator =(const T &val) { v  = val, update(); return *this; }\n\
    \    auto& operator<<=(const T &val) { v <<= val, update(); return *this; }\n\
    \    auto& operator>>=(const T &val) { v >>= val, update(); return *this; }\n\
    };\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_UPDATE_PROXY_OBJECT\n#define SUISEN_UPDATE_PROXY_OBJECT\n\n\
    #include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\ntemplate\
    \ <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>>\n\
    struct UpdateProxyObject {\n    T &v;\n    UpdateFunc update;\n    UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n    operator T() const { return\
    \ v; }\n    auto& operator++() { ++v, update(); return *this; }\n    auto& operator--()\
    \ { --v, update(); return *this; }\n    auto& operator+=(const T &val) { v +=\
    \ val, update(); return *this; }\n    auto& operator-=(const T &val) { v -= val,\
    \ update(); return *this; }\n    auto& operator*=(const T &val) { v *= val, update();\
    \ return *this; }\n    auto& operator/=(const T &val) { v /= val, update(); return\
    \ *this; }\n    auto& operator%=(const T &val) { v %= val, update(); return *this;\
    \ }\n    auto& operator =(const T &val) { v  = val, update(); return *this; }\n\
    \    auto& operator<<=(const T &val) { v <<= val, update(); return *this; }\n\
    \    auto& operator>>=(const T &val) { v >>= val, update(); return *this; }\n\
    };\n\n} // namespace suisen\n\n#endif // SUISEN_UPDATE_PROXY_OBJECT\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/util/update_proxy_object.hpp
  requiredBy:
  - library/datastructure/segment_tree.hpp
  - library/datastructure/lazy_segment_tree.hpp
  timestamp: '2021-08-03 16:06:40+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
documentation_of: library/util/update_proxy_object.hpp
layout: document
redirect_from:
- /library/library/util/update_proxy_object.hpp
- /library/library/util/update_proxy_object.hpp.html
title: library/util/update_proxy_object.hpp
---
