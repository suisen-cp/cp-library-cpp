---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/algorithm/sliding_window_minimum.hpp
    title: library/algorithm/sliding_window_minimum.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: library/datastructure/bit_vector.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/compressed_wavelet_matrix.hpp
    title: library/datastructure/compressed_wavelet_matrix.hpp
  - icon: ':x:'
    path: library/datastructure/dual_segment_tree.hpp
    title: library/datastructure/dual_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree.hpp
    title: library/datastructure/fenwick_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree.hpp
    title: library/datastructure/segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/wavelet_matrix.hpp
    title: library/datastructure/wavelet_matrix.hpp
  - icon: ':warning:'
    path: library/template.cpp
    title: library/template.cpp
  - icon: ':warning:'
    path: library/template.hpp
    title: library/template.hpp
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
  - icon: ':heavy_check_mark:'
    path: library/util/coordinate_compressor.hpp
    title: library/util/coordinate_compressor.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
    title: test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
    title: test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
    title: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
    title: test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
    title: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
    title: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: '#line 1 "library/type_traits/type_traits.hpp"




    #include <limits>

    #include <type_traits>


    namespace suisen {

    // ! utility

    template <typename ...Types>

    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;


    // ! function

    template <typename ReturnType, typename Callable, typename ...Args>

    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,
    ReturnType>;

    template <typename F, typename T>

    using is_uni_op = is_same_as_invoke_result<T, F, T>;

    template <typename F, typename T>

    using is_bin_op = is_same_as_invoke_result<T, F, T, T>;


    template <typename Comparator, typename T>

    using is_comparator = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;


    // ! integral

    template <typename T, typename = constraints_t<std::is_integral<T>>>

    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;

    template <typename T, unsigned int n>

    struct is_nbit { static constexpr bool value = bit_num<T> == n; };

    template <typename T, unsigned int n>

    static constexpr bool is_nbit_v = is_nbit<T, n>::value;

    } // namespace suisen



    '
  code: '#ifndef SUISEN_TYPE_TRITS

    #define SUISEN_TYPE_TRITS


    #include <limits>

    #include <type_traits>


    namespace suisen {

    // ! utility

    template <typename ...Types>

    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;


    // ! function

    template <typename ReturnType, typename Callable, typename ...Args>

    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,
    ReturnType>;

    template <typename F, typename T>

    using is_uni_op = is_same_as_invoke_result<T, F, T>;

    template <typename F, typename T>

    using is_bin_op = is_same_as_invoke_result<T, F, T, T>;


    template <typename Comparator, typename T>

    using is_comparator = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;


    // ! integral

    template <typename T, typename = constraints_t<std::is_integral<T>>>

    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;

    template <typename T, unsigned int n>

    struct is_nbit { static constexpr bool value = bit_num<T> == n; };

    template <typename T, unsigned int n>

    static constexpr bool is_nbit_v = is_nbit<T, n>::value;

    } // namespace suisen


    #endif // SUISEN_TYPE_TRITS'
  dependsOn: []
  isVerificationFile: false
  path: library/type_traits/type_traits.hpp
  requiredBy:
  - library/datastructure/compressed_wavelet_matrix.hpp
  - library/datastructure/bit_vector.hpp
  - library/datastructure/fenwick_tree.hpp
  - library/datastructure/dual_segment_tree.hpp
  - library/datastructure/wavelet_matrix.hpp
  - library/datastructure/segment_tree.hpp
  - library/template.hpp
  - library/template.cpp
  - library/util/coordinate_compressor.hpp
  - library/tree/heavy_light_decomposition.hpp
  - library/algorithm/sliding_window_minimum.hpp
  timestamp: '2021-07-20 14:25:15+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  - test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
  - test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  - test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
  - test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
  - test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
  - test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
  - test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  - test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
  - test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
documentation_of: library/type_traits/type_traits.hpp
layout: document
redirect_from:
- /library/library/type_traits/type_traits.hpp
- /library/library/type_traits/type_traits.hpp.html
title: library/type_traits/type_traits.hpp
---
