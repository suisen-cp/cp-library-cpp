---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_eval_dynamic_sequence.hpp
    title: "\u53CD\u8EE2\u53EF\u80FD\u306A\u9045\u5EF6\u8A55\u4FA1\u4ED8\u304D\u5E73\
      \u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_eval_map.hpp
    title: Lazy Eval Map
  - icon: ':heavy_check_mark:'
    path: library/datastructure/range_foldable_dynamic_sequence.hpp
    title: Range Foldable Dynamic Sequence
  - icon: ':heavy_check_mark:'
    path: library/datastructure/range_foldable_map.hpp
    title: Range Foldable Map
  - icon: ':question:'
    path: library/datastructure/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/segment_tree_2d_sparse.hpp
    title: "2D \u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u70B9\u7FA4\u304C\u758E\u306A\
      \u5834\u5408)"
  - icon: ':question:'
    path: library/datastructure/segment_tree/segment_tree_beats.hpp
    title: library/datastructure/segment_tree/segment_tree_beats.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum.hpp
    title: library/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
    title: test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_F.test.cpp
    title: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_F.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_G.test.cpp
    title: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_G.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
    title: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_I.test.cpp
    title: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_I.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree/DSL_2_A.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree_2d_sparse/rectangle_sum.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_2d_sparse/rectangle_sum.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
    namespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
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
  - library/datastructure/lazy_eval_map.hpp
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  - library/datastructure/range_foldable_map.hpp
  - library/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum.hpp
  - library/datastructure/segment_tree/lazy_segment_tree.hpp
  - library/datastructure/segment_tree/segment_tree_beats.hpp
  - library/datastructure/segment_tree/segment_tree.hpp
  - library/datastructure/segment_tree/segment_tree_2d_sparse.hpp
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
  - test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/segment_tree/trees/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_2d_sparse/rectangle_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/point_add_range_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/DSL_2_A.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_I.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_G.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_F.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
  - test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
documentation_of: library/util/update_proxy_object.hpp
layout: document
title: Update Proxy Object
---
## Update Proxy Object