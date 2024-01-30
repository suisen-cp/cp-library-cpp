---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: Bit Vector
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/range_query/static_range_xored_mex_query/dummy.test.cpp
    title: test/src/range_query/static_range_xored_mex_query/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/range_query/static_range_xored_mex_query.hpp\"\n\
    \n\n\n#include <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\
    \n#line 1 \"library/datastructure/bit_vector.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line\
    \ 5 \"library/type_traits/type_traits.hpp\"\n#include <iostream>\n#line 7 \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n    template <typename ...Constraints> using constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;\n\n\
    \    template <typename T, typename = std::nullptr_t> struct bitnum { static constexpr\
    \ int value = 0; };\n    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>>\
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
    } // namespace suisen\n\n#line 8 \"library/datastructure/bit_vector.hpp\"\n\n\
    namespace suisen {\n    struct BitVector {\n        explicit BitVector(int n)\
    \ : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl, 0),\
    \ cum_s(ns, 0), bits(ns, 0) {}\n        BitVector() : BitVector(0) {}\n      \
    \  template <typename Gen, constraints_t<std::is_invocable_r<bool, Gen, int>>\
    \ = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n           \
    \ build(gen);\n        }\n        BitVector& operator=(const BitVector& bv) {\n\
    \            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s = bv.cum_s,\
    \ bits = bv.bits;\n            return *this;\n        }\n        BitVector& operator=(BitVector&&\
    \ bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = std::move(bv.cum_l),\
    \ cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);\n            return\
    \ *this;\n        }\n        template <typename Gen, constraints_t<std::is_invocable_r<bool,\
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
    \     bool operator[](int i) const {\n            return (bits[i >> LOG_BLOCK_S]\
    \ >> (i & MASK_S)) & 1;\n        }\n        // returns the i'th val (i: 0-indexed)\n\
    \        bool access(int i) const {\n            return (*this)[i];\n        }\n\
    \        // returns the number of val in [0, i)\n        int rank(bool val, int\
    \ i) const {\n            int res_1 = cum_l[i >> LOG_BLOCK_L] + cum_s[i >> LOG_BLOCK_S]\
    \ + popcount8(bits[i >> LOG_BLOCK_S] & ((1 << (i & MASK_S)) - 1));\n         \
    \   return val ? res_1 : i - res_1;\n        }\n        // returns the number\
    \ of val in [l, r)\n        int rank(bool val, int l, int r) const {\n       \
    \     return rank(val, r) - rank(val, l);\n        }\n        // find the index\
    \ of num'th val. (num: 1-indexed). if not exists, returns default_value.\n   \
    \     int select(bool val, int num, int default_value = -1) const {\n        \
    \    int l = -1, r = n + 1;\n            while (r - l > 1) {\n               \
    \ int m = (l + r) >> 1;\n                (rank(val, m) >= num ? r : l) = m;\n\
    \            }\n            return r == n + 1 ? default_value : r;\n        }\n\
    \    private:\n        static constexpr int LOG_BLOCK_L = 8;\n        static constexpr\
    \ int LOG_BLOCK_S = 3;\n        static constexpr int MASK_S = (1 << LOG_BLOCK_S)\
    \ - 1;\n\n        int n, nl, ns;\n        std::vector<int> cum_l;\n        std::vector<std::uint8_t>\
    \ cum_s, bits;\n\n        static constexpr std::uint8_t popcount8(std::uint8_t\
    \ x) {\n            x = (x & 0b01010101) + ((x >> 1) & 0b01010101);\n        \
    \    x = (x & 0b00110011) + ((x >> 2) & 0b00110011);\n            return (x &\
    \ 0b00001111) + (x >> 4);\n        }\n    };\n} // namespace suisen\n\n\n#line\
    \ 10 \"library/range_query/static_range_xored_mex_query.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    \    struct RangeXoredMexQuery {\n        // default constructor\n        RangeXoredMexQuery()\
    \ noexcept : n(0) {}\n        // builds WaveletMatrix from vector\n        template\
    \ <typename U, std::enable_if_t<std::is_constructible_v<T, U>, std::nullptr_t>\
    \ = nullptr>\n        RangeXoredMexQuery(const std::vector<U>& a) { build(a);\
    \ }\n\n        // builds WaveletMatrix from generating function typed as (int)\
    \ -> T\n        template <typename U, std::enable_if_t<std::is_constructible_v<T,\
    \ U>, std::nullptr_t> = nullptr>\n        void build(const std::vector<U> &dat)\
    \ {\n            n = dat.size();\n            std::vector<T> a(n), l(n), r(n);\n\
    \            for (int i = 0; i < n; ++i) a[i] = dat[i];\n\n            int floor_log2\
    \ = 0;\n            while (1 << (floor_log2 + 1) <= n) ++floor_log2;\n       \
    \     std::vector<int> cnt(1 << floor_log2, 0);\n            int dcnt = 0;\n\n\
    \            auto calc_min_r = [&, this](int log) {\n                min_r[log].assign(n\
    \ + 1, n + 1);\n                if (log > floor_log2) return;\n              \
    \  const int mask = (1 << log) - 1;\n                for (int l = 0, r = 0; l\
    \ < n;) {\n                    while (r < n and dcnt != 1 << log) dcnt += ++cnt[a[r++]\
    \ & mask] == 1;\n                    if (dcnt == 1 << log) min_r[log][l] = r;\n\
    \                    dcnt -= --cnt[a[l++] & mask] == 0;\n                }\n \
    \           };\n\n            calc_min_r(bit_num);\n            for (int log =\
    \ bit_num - 1; log >= 0; --log) {\n                bv[log] = BitVector(n, [&a,\
    \ log](int i) -> bool { return (a[i] >> log) & 1; });\n                int li\
    \ = 0, ri = 0;\n                for (int i = 0; i < n; ++i) {\n              \
    \      ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];\n                }\n  \
    \              a.swap(l);\n                std::copy(r.begin(), r.begin() + ri,\
    \ a.begin() + li);\n                mid[log] = li;\n                calc_min_r(log);\n\
    \            }\n        }\n\n        // returns mex { A_i ^ x | l <= i < r }\n\
    \        T minimum_excluded(int l, int r, T x) const {\n            if (x >> bit_num)\
    \ return 0;\n            if (min_r[bit_num][l] <= r) return T(1) << bit_num;\n\
    \            T res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                bool z = (x >> log) & 1;\n                auto [zl, zr] =\
    \ succ(l, r, z, log);\n                if (min_r[log][zl] <= zr) {\n         \
    \           std::tie(l, r) = succ(l, r, not z, log);\n                    res\
    \ |= T(1) << log;\n                } else {\n                    l = zl, r = zr;\n\
    \                }\n            }\n            return res;\n        }\n\n    private:\n\
    \        static_assert(bit_num > 0);\n\n        int n;\n        std::array<BitVector,\
    \ bit_num> bv;\n        std::array<int, bit_num> mid;\n        std::array<std::vector<int>,\
    \ bit_num + 1> min_r;\n\n        std::pair<int, int> succ(int l, int r, const\
    \ bool b, const int log) const {\n            return std::make_pair(b * mid[log]\
    \ + bv[log].rank(b, l), b * mid[log] + bv[log].rank(b, r));\n        }\n    };\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_RANGE_XORED_MEX_QUERY\n#define SUISEN_RANGE_XORED_MEX_QUERY\n\
    \n#include <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\
    \n#include \"library/datastructure/bit_vector.hpp\"\n\nnamespace suisen {\n  \
    \  template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    \    struct RangeXoredMexQuery {\n        // default constructor\n        RangeXoredMexQuery()\
    \ noexcept : n(0) {}\n        // builds WaveletMatrix from vector\n        template\
    \ <typename U, std::enable_if_t<std::is_constructible_v<T, U>, std::nullptr_t>\
    \ = nullptr>\n        RangeXoredMexQuery(const std::vector<U>& a) { build(a);\
    \ }\n\n        // builds WaveletMatrix from generating function typed as (int)\
    \ -> T\n        template <typename U, std::enable_if_t<std::is_constructible_v<T,\
    \ U>, std::nullptr_t> = nullptr>\n        void build(const std::vector<U> &dat)\
    \ {\n            n = dat.size();\n            std::vector<T> a(n), l(n), r(n);\n\
    \            for (int i = 0; i < n; ++i) a[i] = dat[i];\n\n            int floor_log2\
    \ = 0;\n            while (1 << (floor_log2 + 1) <= n) ++floor_log2;\n       \
    \     std::vector<int> cnt(1 << floor_log2, 0);\n            int dcnt = 0;\n\n\
    \            auto calc_min_r = [&, this](int log) {\n                min_r[log].assign(n\
    \ + 1, n + 1);\n                if (log > floor_log2) return;\n              \
    \  const int mask = (1 << log) - 1;\n                for (int l = 0, r = 0; l\
    \ < n;) {\n                    while (r < n and dcnt != 1 << log) dcnt += ++cnt[a[r++]\
    \ & mask] == 1;\n                    if (dcnt == 1 << log) min_r[log][l] = r;\n\
    \                    dcnt -= --cnt[a[l++] & mask] == 0;\n                }\n \
    \           };\n\n            calc_min_r(bit_num);\n            for (int log =\
    \ bit_num - 1; log >= 0; --log) {\n                bv[log] = BitVector(n, [&a,\
    \ log](int i) -> bool { return (a[i] >> log) & 1; });\n                int li\
    \ = 0, ri = 0;\n                for (int i = 0; i < n; ++i) {\n              \
    \      ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];\n                }\n  \
    \              a.swap(l);\n                std::copy(r.begin(), r.begin() + ri,\
    \ a.begin() + li);\n                mid[log] = li;\n                calc_min_r(log);\n\
    \            }\n        }\n\n        // returns mex { A_i ^ x | l <= i < r }\n\
    \        T minimum_excluded(int l, int r, T x) const {\n            if (x >> bit_num)\
    \ return 0;\n            if (min_r[bit_num][l] <= r) return T(1) << bit_num;\n\
    \            T res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                bool z = (x >> log) & 1;\n                auto [zl, zr] =\
    \ succ(l, r, z, log);\n                if (min_r[log][zl] <= zr) {\n         \
    \           std::tie(l, r) = succ(l, r, not z, log);\n                    res\
    \ |= T(1) << log;\n                } else {\n                    l = zl, r = zr;\n\
    \                }\n            }\n            return res;\n        }\n\n    private:\n\
    \        static_assert(bit_num > 0);\n\n        int n;\n        std::array<BitVector,\
    \ bit_num> bv;\n        std::array<int, bit_num> mid;\n        std::array<std::vector<int>,\
    \ bit_num + 1> min_r;\n\n        std::pair<int, int> succ(int l, int r, const\
    \ bool b, const int log) const {\n            return std::make_pair(b * mid[log]\
    \ + bv[log].rank(b, l), b * mid[log] + bv[log].rank(b, r));\n        }\n    };\n\
    } // namespace suisen\n\n#endif // SUISEN_RANGE_XORED_MEX_QUERY\n"
  dependsOn:
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/range_query/static_range_xored_mex_query.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/range_query/static_range_xored_mex_query/dummy.test.cpp
documentation_of: library/range_query/static_range_xored_mex_query.hpp
layout: document
title: Static Range Xored Mex Query
---
## Static Range Xored Mex Query