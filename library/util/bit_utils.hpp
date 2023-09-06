#ifndef SUISEN_BIT_UTILS
#define SUISEN_BIT_UTILS

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif
#include "library/type_traits/type_traits.hpp"
namespace suisen {
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    __attribute__((target("popcnt"))) constexpr int popcount(const T x) { return _mm_popcnt_u32(x); }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    __attribute__((target("popcnt"))) constexpr int popcount(const T x) { return _mm_popcnt_u64(x); }
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    constexpr int count_lz(const T x) { return x ? __builtin_clz(x) : suisen::bitnum_v<T>; }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    constexpr int count_lz(const T x) { return x ? __builtin_clzll(x) : suisen::bitnum_v<T>; }
    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T, 64>>, std::nullptr_t> = nullptr>
    constexpr int count_tz(const T x) { return x ? __builtin_ctz(x) : suisen::bitnum_v<T>; }
    template <typename T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>
    constexpr int count_tz(const T x) { return x ? __builtin_ctzll(x) : suisen::bitnum_v<T>; }
    template <typename T> constexpr int floor_log2(const T x) { return suisen::bitnum_v<T> -1 - count_lz(x); }
    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x) + ((x & -x) != x); }
    template <typename T> constexpr int kth_bit(const T x, const unsigned int k) { return (x >> k) & 1; }
    template <typename T> constexpr int parity(const T x) { return popcount(x) & 1; }
}
#endif // SUISEN_BIT_UTILS