---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/algorithm/sliding_window_minimum.hpp
    title: library/algorithm/sliding_window_minimum.hpp
  - icon: ':warning:'
    path: library/template.cpp
    title: library/template.cpp
  - icon: ':warning:'
    path: library/template.hpp
    title: library/template.hpp
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: library/tree/heavy_light_decomposition.hpp
  - icon: ':warning:'
    path: test/src/tree/heavy_light_decomposition/do_use_segment_tree.cpp
    title: test/src/tree/heavy_light_decomposition/do_use_segment_tree.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/generated/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
    title: test/generated/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 1 "library/type_traits/type_traits.hpp"




    #include <limits>

    #include <type_traits>


    namespace suisen {

    // ! utility

    template <typename ...Types>

    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, nullptr_t>;


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

    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, nullptr_t>;


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
  - test/src/tree/heavy_light_decomposition/do_use_segment_tree.cpp
  - library/template.hpp
  - library/template.cpp
  - library/tree/heavy_light_decomposition.hpp
  - library/algorithm/sliding_window_minimum.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/generated/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
documentation_of: library/type_traits/type_traits.hpp
layout: document
redirect_from:
- /library/library/type_traits/type_traits.hpp
- /library/library/type_traits/type_traits.hpp.html
title: library/type_traits/type_traits.hpp
---
