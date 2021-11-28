---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_eval_dynamic_sequence.hpp
    title: "\u53CD\u8EE2\u53EF\u80FD\u306A\u9045\u5EF6\u8A55\u4FA1\u4ED8\u304D\u5E73\
      \u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_eval_map.hpp
    title: library/datastructure/lazy_eval_map.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_segment_tree.hpp
    title: library/datastructure/lazy_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/range_foldable_dynamic_sequence.hpp
    title: library/datastructure/range_foldable_dynamic_sequence.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/range_foldable_map.hpp
    title: library/datastructure/range_foldable_map.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree.hpp
    title: library/datastructure/segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree_2d_sparse.hpp
    title: library/datastructure/segment_tree_2d_sparse.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_lazy_segment_tree.hpp
    title: library/datastructure/sparse_lazy_segment_tree.hpp
  - icon: ':warning:'
    path: library/datastructure/sparse_segment_tree.hpp
    title: library/datastructure/sparse_segment_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
    title: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
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
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
    title: test/src/datastructure/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree_2d_sparse/rectangle_sum.test.cpp
    title: test/src/datastructure/segment_tree_2d_sparse/rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
    title: test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_UPDATE_PROXY_OBJECT\n#define SUISEN_UPDATE_PROXY_OBJECT\n\n\
    #include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\ntemplate\
    \ <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n#endif\
    \ // SUISEN_UPDATE_PROXY_OBJECT\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/util/update_proxy_object.hpp
  requiredBy:
  - library/datastructure/range_foldable_map.hpp
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/segment_tree_2d_sparse.hpp
  - library/datastructure/sparse_segment_tree.hpp
  - library/datastructure/sparse_lazy_segment_tree.hpp
  - library/datastructure/lazy_segment_tree.hpp
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  - library/datastructure/segment_tree.hpp
  - library/datastructure/lazy_eval_map.hpp
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
  - test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/segment_tree_2d_sparse/rectangle_sum.test.cpp
  - test/src/datastructure/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
  - test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
  - test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
documentation_of: library/util/update_proxy_object.hpp
layout: document
redirect_from:
- /library/library/util/update_proxy_object.hpp
- /library/library/util/update_proxy_object.hpp.html
title: library/util/update_proxy_object.hpp
---
