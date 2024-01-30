---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/bit_utils.hpp\"\n\n\n\n#ifdef _MSC_VER\n# \
    \ include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <iostream>\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
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
    } // namespace suisen\n\n#line 10 \"library/util/bit_utils.hpp\"\nnamespace suisen\
    \ {\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr\
    \ int popcount(const T x) { return _mm_popcnt_u32(x); }\n    template <typename\
    \ T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>\n \
    \   __attribute__((target(\"popcnt\"))) constexpr int popcount(const T x) { return\
    \ _mm_popcnt_u64(x); }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clz(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clzll(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctz(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctzll(x) : suisen::bitnum_v<T>; }\n    template <typename T> constexpr\
    \ int floor_log2(const T x) { return suisen::bitnum_v<T> -1 - count_lz(x); }\n\
    \    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x)\
    \ + ((x & -x) != x); }\n    template <typename T> constexpr int kth_bit(const\
    \ T x, const unsigned int k) { return (x >> k) & 1; }\n    template <typename\
    \ T> constexpr int parity(const T x) { return popcount(x) & 1; }\n}\n\n"
  code: "#ifndef SUISEN_BIT_UTILS\n#define SUISEN_BIT_UTILS\n\n#ifdef _MSC_VER\n#\
    \  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n#include \"library/type_traits/type_traits.hpp\"\
    \nnamespace suisen {\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    __attribute__((target(\"popcnt\"))) constexpr\
    \ int popcount(const T x) { return _mm_popcnt_u32(x); }\n    template <typename\
    \ T, std::enable_if_t<suisen::is_nbit_v<T, 64>, std::nullptr_t> = nullptr>\n \
    \   __attribute__((target(\"popcnt\"))) constexpr int popcount(const T x) { return\
    \ _mm_popcnt_u64(x); }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clz(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_lz(const T x) { return\
    \ x ? __builtin_clzll(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<std::negation_v<suisen::is_nbit<T,\
    \ 64>>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctz(x) : suisen::bitnum_v<T>; }\n    template <typename T, std::enable_if_t<suisen::is_nbit_v<T,\
    \ 64>, std::nullptr_t> = nullptr>\n    constexpr int count_tz(const T x) { return\
    \ x ? __builtin_ctzll(x) : suisen::bitnum_v<T>; }\n    template <typename T> constexpr\
    \ int floor_log2(const T x) { return suisen::bitnum_v<T> -1 - count_lz(x); }\n\
    \    template <typename T> constexpr int ceil_log2(const T x) { return floor_log2(x)\
    \ + ((x & -x) != x); }\n    template <typename T> constexpr int kth_bit(const\
    \ T x, const unsigned int k) { return (x >> k) & 1; }\n    template <typename\
    \ T> constexpr int parity(const T x) { return popcount(x) & 1; }\n}\n#endif //\
    \ SUISEN_BIT_UTILS"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/util/bit_utils.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/bit_utils.hpp
layout: document
title: Bit Utils
---
## Bit Utils