---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: '#line 1 "library/util/bit_utils.hpp"




    #include <limits>

    #include <type_traits>


    namespace suisen {

    template <typename T>

    struct bit_num { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits;
    };

    template <typename T, unsigned int n>

    struct is_nbit { static constexpr bool value = bit_num<T>::value == n; };

    template <typename T>

    constexpr auto popcount(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return __builtin_popcount(x); }

    template <typename T>

    constexpr auto popcount(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return __builtin_popcountll(x); }

    template <typename T>

    constexpr auto count_lz(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return x ? __builtin_clz(x)   : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_lz(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return x ? __builtin_clzll(x) : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_tz(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return x ? __builtin_ctz(x)   : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_tz(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return x ? __builtin_ctzll(x) : bit_num<T>::value; }

    template <typename T>

    constexpr int floor_log2(const T x) { return bit_num<T>::value - 1 - count_lz(x);
    }

    template <typename T>

    constexpr int ceil_log2(const T x)  { return floor_log2(x) + ((x & -x) != x);
    }

    template <typename T>

    constexpr int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1;
    }

    } // namespace suisen



    '
  code: '#ifndef SUISEN_BIT_UTILS

    #define SUISEN_BIT_UTILS


    #include <limits>

    #include <type_traits>


    namespace suisen {

    template <typename T>

    struct bit_num { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits;
    };

    template <typename T, unsigned int n>

    struct is_nbit { static constexpr bool value = bit_num<T>::value == n; };

    template <typename T>

    constexpr auto popcount(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return __builtin_popcount(x); }

    template <typename T>

    constexpr auto popcount(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return __builtin_popcountll(x); }

    template <typename T>

    constexpr auto count_lz(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return x ? __builtin_clz(x)   : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_lz(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return x ? __builtin_clzll(x) : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_tz(const T x) -> std::enable_if_t<is_nbit<T, 32>::value,
    int> { return x ? __builtin_ctz(x)   : bit_num<T>::value; }

    template <typename T>

    constexpr auto count_tz(const T x) -> std::enable_if_t<is_nbit<T, 64>::value,
    int> { return x ? __builtin_ctzll(x) : bit_num<T>::value; }

    template <typename T>

    constexpr int floor_log2(const T x) { return bit_num<T>::value - 1 - count_lz(x);
    }

    template <typename T>

    constexpr int ceil_log2(const T x)  { return floor_log2(x) + ((x & -x) != x);
    }

    template <typename T>

    constexpr int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1;
    }

    } // namespace suisen


    #endif // SUISEN_BIT_UTILS'
  dependsOn: []
  isVerificationFile: false
  path: library/util/bit_utils.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/bit_utils.hpp
layout: document
redirect_from:
- /library/library/util/bit_utils.hpp
- /library/library/util/bit_utils.hpp.html
title: library/util/bit_utils.hpp
---
