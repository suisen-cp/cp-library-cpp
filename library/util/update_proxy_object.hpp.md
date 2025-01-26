---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
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
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/segment_tree_2d_sparse.hpp
    title: "2D \u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u70B9\u7FA4\u304C\u758E\u306A\
      \u5834\u5408)"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/segment_tree_beats.hpp
    title: Segment Tree Beats
  - icon: ':heavy_check_mark:'
    path: library/range_query/range_chmin_chmax_add_range_sum.hpp
    title: Range Chmin Chmax Add Range Sum
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
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
    title: test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
    title: test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 1 \"\
    library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include <iostream>\n\
    #include <type_traits>\n\nnamespace suisen {\n    template <typename ...Constraints>\
    \ using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;\n\
    \n    template <typename T, typename = std::nullptr_t> struct bitnum { static\
    \ constexpr int value = 0; };\n    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>>\
    \ { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits;\
    \ };\n    template <typename T> static constexpr int bitnum_v = bitnum<T>::value;\n\
    \    template <typename T, size_t n> struct is_nbit { static constexpr bool value\
    \ = bitnum_v<T> == n; };\n    template <typename T, size_t n> static constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n    template <typename T, typename\
    \ = std::nullptr_t> struct safely_multipliable { using type = T; };\n    template\
    \ <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 32>>> { using type = long long; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 64>>> { using\
    \ type = __int128_t; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> { using type = unsigned\
    \ long long; };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>,\
    \ is_nbit<T, 64>>> { using type = __uint128_t; };\n    template <typename T> using\
    \ safely_multipliable_t = typename safely_multipliable<T>::type;\n\n    template\
    \ <typename T, typename = void> struct rec_value_type { using type = T; };\n \
    \   template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>>\
    \ {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
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
    \        template <typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n\
    \        auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
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
    \        template <typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n\
    \        auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n#endif\
    \ // SUISEN_UPDATE_PROXY_OBJECT\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/util/update_proxy_object.hpp
  requiredBy:
  - library/range_query/range_chmin_chmax_add_range_sum.hpp
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/range_foldable_map.hpp
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  - library/datastructure/segment_tree/segment_tree.hpp
  - library/datastructure/segment_tree/segment_tree_2d_sparse.hpp
  - library/datastructure/segment_tree/segment_tree_beats.hpp
  - library/datastructure/segment_tree/lazy_segment_tree.hpp
  - library/datastructure/lazy_eval_map.hpp
  timestamp: '2024-01-30 22:04:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
  - test/src/datastructure/fenwick_tree/fenwick_tree_2d/random_is.test.cpp
  - test/src/datastructure/lazy_eval_map/leq_and_neq.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_beats/yuki880.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_G.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_F.test.cpp
  - test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_I.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_2d_sparse/rectangle_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree_2d_sparse/point_add_rectangle_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/point_add_range_sum.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/DSL_2_A.test.cpp
  - test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
  - test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
documentation_of: library/util/update_proxy_object.hpp
layout: document
title: Update Proxy Object
---
## Update Proxy Object