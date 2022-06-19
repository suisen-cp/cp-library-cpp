---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/compressed_wavelet_matrix.hpp
    title: Compressed Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: library/datastructure/wavelet_matrix.hpp
    title: Wavelet Matrix
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/static_range_frequency.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/static_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
    title: test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
    title: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/wavelet_matrix/static_range_frequency.test.cpp
    title: test/src/datastructure/wavelet_matrix/static_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
    title: test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/bit_vector.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
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
    } // namespace suisen\n\n\n#line 8 \"library/datastructure/bit_vector.hpp\"\n\n\
    namespace suisen {\n    class BitVector {\n        using u8 = std::uint8_t;\n\
    \    public:\n        explicit BitVector(int n) : n(n), nl((n >> LOG_BLOCK_L)\
    \ + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl, 0), cum_s(ns, 0), bits(ns, 0) {}\n\
    \        BitVector() : BitVector(0) {}\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
    \ Gen, int>> = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n\
    \            build(gen);\n        }\n        BitVector& operator=(const BitVector&\
    \ bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s\
    \ = bv.cum_s, bits = bv.bits;\n            return *this;\n        }\n        BitVector&\
    \ operator=(BitVector&& bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l\
    \ = std::move(bv.cum_l), cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);\n\
    \            return *this;\n        }\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
    \ Gen, int>> = nullptr>\n        void build(Gen gen) {\n            int i = 0;\n\
    \            for (int index_s = 1; index_s < ns; ++index_s) {\n              \
    \  int count = cum_s[index_s - 1];\n                for (; i < index_s << LOG_BLOCK_S;\
    \ ++i) {\n                    bool b = gen(i);\n                    bits[index_s\
    \ - 1] |= b << (i & MASK_S);\n                    count += b;\n              \
    \  }\n                if (index_s & ((1 << (LOG_BLOCK_L - LOG_BLOCK_S)) - 1))\
    \ {\n                    cum_s[index_s] = count;\n                } else {\n \
    \                   int index_l = i >> LOG_BLOCK_L;\n                    cum_l[index_l]\
    \ = cum_l[index_l - 1] + count;\n                }\n            }\n          \
    \  for (; i < n; ++i) bits[ns - 1] |= gen(i) << (i & MASK_S);\n        }\n   \
    \     inline bool operator[](int i) const {\n            return (bits[i >> LOG_BLOCK_S]\
    \ >> (i & MASK_S)) & 1;\n        }\n        // returns the i'th val (i: 0-indexed)\n\
    \        inline bool access(int i) const {\n            return (*this)[i];\n \
    \       }\n        // returns the number of val in [0, i)\n        inline int\
    \ rank(bool val, int i) const {\n            int res_1 = cum_l[i >> LOG_BLOCK_L]\
    \ + cum_s[i >> LOG_BLOCK_S] + popcount8(bits[i >> LOG_BLOCK_S] & ((1 << (i & MASK_S))\
    \ - 1));\n            return val ? res_1 : i - res_1;\n        }\n        // returns\
    \ the number of val in [l, r)\n        inline int rank(bool val, int l, int r)\
    \ const {\n            return rank(val, r) - rank(val, l);\n        }\n      \
    \  // find the index of num'th val. (num: 1-indexed). if not exists, returns default_value.\n\
    \        int select(bool val, int num, int default_value = -1) const {\n     \
    \       int l = -1, r = n + 1;\n            while (r - l > 1) {\n            \
    \    int m = (l + r) >> 1;\n                (rank(val, m) >= num ? r : l) = m;\n\
    \            }\n            return r == n + 1 ? default_value : r;\n        }\n\
    \    private:\n        static constexpr int LOG_BLOCK_L = 8;\n        static constexpr\
    \ int LOG_BLOCK_S = 3;\n        static constexpr int MASK_S = (1 << LOG_BLOCK_S)\
    \ - 1;\n\n        int n, nl, ns;\n        std::vector<int> cum_l;\n        std::vector<u8>\
    \ cum_s, bits;\n\n        static constexpr u8 popcount8(u8 x) {\n            x\
    \ = (x & 0b01010101) + ((x >> 1) & 0b01010101);\n            x = (x & 0b00110011)\
    \ + ((x >> 2) & 0b00110011);\n            return (x & 0b00001111) + (x >> 4);\n\
    \        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BIT_VECTOR\n#define SUISEN_BIT_VECTOR\n\n#include <cstdint>\n\
    #include <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace\
    \ suisen {\n    class BitVector {\n        using u8 = std::uint8_t;\n    public:\n\
    \        explicit BitVector(int n) : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >>\
    \ LOG_BLOCK_S) + 1), cum_l(nl, 0), cum_s(ns, 0), bits(ns, 0) {}\n        BitVector()\
    \ : BitVector(0) {}\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
    \ Gen, int>> = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n\
    \            build(gen);\n        }\n        BitVector& operator=(const BitVector&\
    \ bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s\
    \ = bv.cum_s, bits = bv.bits;\n            return *this;\n        }\n        BitVector&\
    \ operator=(BitVector&& bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l\
    \ = std::move(bv.cum_l), cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);\n\
    \            return *this;\n        }\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
    \ Gen, int>> = nullptr>\n        void build(Gen gen) {\n            int i = 0;\n\
    \            for (int index_s = 1; index_s < ns; ++index_s) {\n              \
    \  int count = cum_s[index_s - 1];\n                for (; i < index_s << LOG_BLOCK_S;\
    \ ++i) {\n                    bool b = gen(i);\n                    bits[index_s\
    \ - 1] |= b << (i & MASK_S);\n                    count += b;\n              \
    \  }\n                if (index_s & ((1 << (LOG_BLOCK_L - LOG_BLOCK_S)) - 1))\
    \ {\n                    cum_s[index_s] = count;\n                } else {\n \
    \                   int index_l = i >> LOG_BLOCK_L;\n                    cum_l[index_l]\
    \ = cum_l[index_l - 1] + count;\n                }\n            }\n          \
    \  for (; i < n; ++i) bits[ns - 1] |= gen(i) << (i & MASK_S);\n        }\n   \
    \     inline bool operator[](int i) const {\n            return (bits[i >> LOG_BLOCK_S]\
    \ >> (i & MASK_S)) & 1;\n        }\n        // returns the i'th val (i: 0-indexed)\n\
    \        inline bool access(int i) const {\n            return (*this)[i];\n \
    \       }\n        // returns the number of val in [0, i)\n        inline int\
    \ rank(bool val, int i) const {\n            int res_1 = cum_l[i >> LOG_BLOCK_L]\
    \ + cum_s[i >> LOG_BLOCK_S] + popcount8(bits[i >> LOG_BLOCK_S] & ((1 << (i & MASK_S))\
    \ - 1));\n            return val ? res_1 : i - res_1;\n        }\n        // returns\
    \ the number of val in [l, r)\n        inline int rank(bool val, int l, int r)\
    \ const {\n            return rank(val, r) - rank(val, l);\n        }\n      \
    \  // find the index of num'th val. (num: 1-indexed). if not exists, returns default_value.\n\
    \        int select(bool val, int num, int default_value = -1) const {\n     \
    \       int l = -1, r = n + 1;\n            while (r - l > 1) {\n            \
    \    int m = (l + r) >> 1;\n                (rank(val, m) >= num ? r : l) = m;\n\
    \            }\n            return r == n + 1 ? default_value : r;\n        }\n\
    \    private:\n        static constexpr int LOG_BLOCK_L = 8;\n        static constexpr\
    \ int LOG_BLOCK_S = 3;\n        static constexpr int MASK_S = (1 << LOG_BLOCK_S)\
    \ - 1;\n\n        int n, nl, ns;\n        std::vector<int> cum_l;\n        std::vector<u8>\
    \ cum_s, bits;\n\n        static constexpr u8 popcount8(u8 x) {\n            x\
    \ = (x & 0b01010101) + ((x >> 1) & 0b01010101);\n            x = (x & 0b00110011)\
    \ + ((x >> 2) & 0b00110011);\n            return (x & 0b00001111) + (x >> 4);\n\
    \        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_BIT_VECTOR\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/bit_vector.hpp
  requiredBy:
  - library/datastructure/compressed_wavelet_matrix.hpp
  - library/datastructure/wavelet_matrix.hpp
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_range_frequency.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  - test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/wavelet_matrix/static_range_frequency.test.cpp
  - test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
documentation_of: library/datastructure/bit_vector.hpp
layout: document
title: Bit Vector
---
## Bit Vector