---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/bit_vector.hpp
    title: Bit Vector
  - icon: ':heavy_check_mark:'
    path: library/datastructure/wavelet_matrix.hpp
    title: Wavelet Matrix
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/coordinate_compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  _extendedRequiredBy: []
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/compressed_wavelet_matrix.hpp\"\n\n\
    \n\n#include <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\
    \n#line 1 \"library/datastructure/wavelet_matrix.hpp\"\n\n\n\n#line 8 \"library/datastructure/wavelet_matrix.hpp\"\
    \n\n#line 1 \"library/datastructure/bit_vector.hpp\"\n\n\n\n#include <cstdint>\n\
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
    \ 10 \"library/datastructure/wavelet_matrix.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    \    struct WaveletMatrix {\n        // default constructor\n        WaveletMatrix()\
    \ noexcept : n(0) {}\n        // builds WaveletMatrix from generating function\
    \ typed as (int) -> T\n        template <typename Gen, constraints_t<std::is_invocable_r<T,\
    \ Gen, int>> = nullptr>\n        WaveletMatrix(int n, Gen generator) : n(n) {\n\
    \            build(generator);\n        }\n        // builds WaveletMatrix from\
    \ vector\n        template <typename U, constraints_t<std::is_constructible<T,\
    \ U>> = nullptr>\n        WaveletMatrix(const std::vector<U>& a) : WaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<std::is_invocable_r<T,\
    \ Gen, int>> = nullptr>\n        void build(Gen generator) {\n            std::vector<T>\
    \ a(n), l(n), r(n);\n            for (int i = 0; i < n; ++i) a[i] = generator(i);\n\
    \            for (int log = bit_num - 1; log >= 0; --log) {\n                bv[log]\
    \ = BitVector(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });\n  \
    \              int li = 0, ri = 0;\n                for (int i = 0; i < n; ++i)\
    \ {\n                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];\n   \
    \             }\n                a.swap(l);\n                std::copy(r.begin(),\
    \ r.begin() + ri, a.begin() + li);\n                mid[log] = li;\n         \
    \   }\n        }\n\n        // returns WaveletMatrix[i]\n        T operator[](int\
    \ i) const {\n            T res = 0;\n            for (int log = bit_num - 1;\
    \ log >= 0; --log) {\n                bool b = bv[log][i];\n                res\
    \ |= T(b) << log;\n                i = b * mid[log] + bv[log].rank(b, i);\n  \
    \          }\n            return res;\n        }\n        // returns WaveletMatrix[i]\n\
    \        T access(int i) const {\n            return (*this)[i];\n        }\n\n\
    \        // returns the number of `val` in WaveletMatrix[0, i).\n        int rank(T\
    \ val, int i) const {\n            check_value_bounds(val);\n            int l\
    \ = 0, r = i;\n            for (int log = bit_num - 1; log >= 0; --log) succ(l,\
    \ r, (val >> log) & 1, log);\n            return r - l;\n        }\n\n       \
    \ // returns the k'th smallest value in the multiset {| x ^ WaveletMatrix[i] :\
    \ i in [l, r) |} (k : 0-indexed)\n        T range_xor_kth_smallest(int l, int\
    \ r, int k, T x, T default_value = T(-1)) const {\n            if (k < 0 or k\
    \ >= r - l) return default_value;\n            T res = 0;\n            check_value_bounds(x);\n\
    \            for (int log = bit_num - 1; log >= 0; --log) {\n                bool\
    \ z = (x >> log) & 1;\n                int cnt_z = bv[log].rank(z, l, r);\n  \
    \              bool skip_z = k >= cnt_z, bit = z ^ skip_z;\n                succ(l,\
    \ r, bit, log);\n                res |= T(bit) << log;\n                k -= skip_z\
    \ * cnt_z;\n            }\n            return res;\n        }\n        // returns\
    \ the k'th largest value in the multiset {| x ^ WaveletMatrix[i] : i in [l, r)\
    \ |} (k : 0-indexed)\n        T range_xor_kth_largest(int l, int r, int k, T x,\
    \ T default_value = T(-1)) const {\n            return range_xor_kth_smallest(l,\
    \ r, r - l - 1 - k, x, default_value);\n        }\n        // returns the minimum\
    \ value in the set { x ^ WaveletMatrix[i] : i in [l, r) }\n        T range_xor_min(int\
    \ l, int r, T x) const {\n            assert(l < r);\n            return range_xor_kth_smallest(l,\
    \ r, 0, x);\n        }\n        // returns the maximum value in the set { x ^\
    \ WaveletMatrix[i] : i in [l, r) }\n        T range_xor_max(int l, int r, T x)\
    \ const {\n            assert(l < r);\n            return range_xor_kth_largest(l,\
    \ r, 0, x);\n        }\n\n        // returns the number of v in WaveletMatrix[l,\
    \ r) s.t. v ^ x < upper\n        int range_xor_freq(int l, int r, T x, T upper)\
    \ const {\n            if (r <= l) return 0;\n            if (upper > MAX) return\
    \ r - l;\n            check_value_bounds(x);\n            int res = 0;\n     \
    \       for (int log = bit_num - 1; log >= 0; --log) {\n                bool z\
    \ = (x >> log) & 1, u = (upper >> log) & 1;\n                if (u) res += bv[log].rank(z,\
    \ l, r);\n                succ(l, r, z ^ u, log);\n            }\n           \
    \ return res;\n        }\n        // returns the number of v in WaveletMatrix[l,\
    \ r) s.t. lower <= x ^ v < upper\n        int range_xor_freq(int l, int r, T x,\
    \ T lower, T upper) const {\n            if (lower >= upper) return 0;\n     \
    \       return range_xor_freq(l, r, x, upper) - range_xor_freq(l, r, x, lower);\n\
    \        }\n\n        // returns the minimum value v in WaveletMatrix[l, r) s.t.\
    \ lower <= x ^ v\n        T range_xor_min_geq(int l, int r, T x, T lower, T default_value\
    \ = T(-1)) const {\n            int cnt = range_xor_freq(l, r, x, lower);\n  \
    \          return cnt >= r - l ? default_value : range_xor_kth_smallest(l, r,\
    \ cnt, x);\n        }\n        // returns the minimum value v in WaveletMatrix[l,\
    \ r) s.t. lower < x ^ v\n        T range_xor_min_gt(int l, int r, T x, T lower,\
    \ T default_value = T(-1)) const {\n            return lower == MAX ? default_value\
    \ : range_xor_min_geq(l, r, x, lower + 1, default_value);\n        }\n       \
    \ // returns the maximum value v in WaveletMatrix[l, r) s.t. x ^ v < upper\n \
    \       T range_xor_max_lt(int l, int r, T x, T upper, T default_value = T(-1))\
    \ const {\n            int cnt = range_xor_freq(l, r, x, upper);\n           \
    \ return cnt == 0 ? default_value : range_xor_kth_smallest(l, r, cnt - 1, x, default_value);\n\
    \        }\n        // returns the maximum value v in WaveletMatrix[l, r) s.t.\
    \ x ^ v <= upper\n        T range_xor_max_leq(int l, int r, T x, T upper, T default_value\
    \ = T(-1)) const {\n            if (l >= r) return default_value;\n          \
    \  return upper == MAX ? range_xor_max(l, r, x) : range_xor_max_lt(l, r, x, upper\
    \ + 1, default_value);\n        }\n\n        // returns the k'th smallest value\
    \ in WaveletMatrix[l, r) (k : 0-indexed)\n        T range_kth_smallest(int l,\
    \ int r, int k, T default_value = T(-1)) const { return range_xor_kth_smallest(l,\
    \ r, k, 0, default_value); }\n        // returns the k'th largest value in WaveletMatrix[l,\
    \ r) (k : 0-indexed)\n        T range_kth_largest(int l, int r, int k, T default_value\
    \ = T(-1)) const { return range_xor_kth_largest(l, r, k, 0, default_value); }\n\
    \        // returns the minimum value in WaveletMatrix[l, r)\n        T range_min(int\
    \ l, int r) const { return range_xor_min(l, r, 0); }\n        // returns the maximum\
    \ value in WaveletMatrix[l, r)\n        T range_max(int l, int r) const { return\
    \ range_xor_max(l, r, 0); }\n\n        // returns the number of v in WaveletMatrix[l,\
    \ r) s.t. v < upper\n        int range_freq(int l, int r, T upper) const { return\
    \ range_xor_freq(l, r, 0, upper); }\n        // returns the number of v in WaveletMatrix[l,\
    \ r) s.t. lower <= v < upper\n        int range_freq(int l, int r, T lower, T\
    \ upper) const { return range_xor_freq(l, r, 0, lower, upper); }\n        // returns\
    \ the minimum value v in WaveletMatrix[l, r) s.t. lower <= v\n        T range_min_geq(int\
    \ l, int r, T lower, T default_value = T(-1)) const { return range_xor_min_geq(l,\
    \ r, 0, lower, default_value); }\n        // returns the minimum value v in WaveletMatrix[l,\
    \ r) s.t. lower < v\n        T range_min_gt(int l, int r, T lower, T default_value\
    \ = T(-1)) const { return range_xor_min_gt(l, r, 0, lower, default_value); }\n\
    \        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper\n\
    \        T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const\
    \ { return range_xor_max_lt(l, r, 0, upper, default_value); }\n        // returns\
    \ the maximum value v in WaveletMatrix[l, r) s.t. v <= upper\n        T range_max_leq(int\
    \ l, int r, T upper, T default_value = T(-1)) const { return range_xor_max_leq(l,\
    \ r, 0, upper, default_value); }\n    protected:\n        WaveletMatrix(int n)\
    \ noexcept : n(n) {}\n    private:\n        static_assert(bit_num > 0);\n    \
    \    static constexpr T MAX = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max()\
    \ : (T(1) << bit_num) - 1;\n\n        int n;\n        std::array<BitVector, bit_num>\
    \ bv;\n        std::array<int, bit_num> mid;\n\n        void succ(int& l, int&\
    \ r, const bool b, const int log) const {\n            l = b * mid[log] + bv[log].rank(b,\
    \ l);\n            r = b * mid[log] + bv[log].rank(b, r);\n        }\n\n     \
    \   static void check_value_bounds(T val) {\n            assert((val >> bit_num)\
    \ == 0);\n        }\n    };\n} // namespace suisen\n\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"library/util/coordinate_compressor.hpp\"\
    \n\n#line 9 \"library/util/coordinate_compressor.hpp\"\n\nnamespace suisen {\n\
    template <typename T>\nclass CoordinateCompressorBuilder {\n    public:\n    \
    \    struct Compressor {\n            public:\n                static constexpr\
    \ int absent = -1;\n\n                // default constructor\n               \
    \ Compressor() : _xs(std::vector<T>{}) {}\n                // Construct from strictly\
    \ sorted vector\n                Compressor(const std::vector<T> &xs) : _xs(xs)\
    \ {\n                    assert(is_strictly_sorted(xs));\n                }\n\n\
    \                // Return the number of distinct keys.\n                int size()\
    \ const {\n                    return _xs.size();\n                }\n       \
    \         // Check if the element is registered.\n                bool has_key(const\
    \ T &e) const {\n                    return std::binary_search(_xs.begin(), _xs.end(),\
    \ e);\n                }\n                // Compress the element. if not registered,\
    \ returns `default_value`. (default: Compressor::absent)\n                int\
    \ comp(const T &e, int default_value = absent) const {\n                    const\
    \ int res = min_geq_index(e);\n                    return res != size() and _xs[res]\
    \ == e ? res : default_value;\n                }\n                // Restore the\
    \ element from the index.\n                T decomp(const int compressed_index)\
    \ const {\n                    return _xs[compressed_index];\n               \
    \ }\n                // Compress the element. Equivalent to call `comp(e)`\n \
    \               int operator[](const T &e) const {\n                    return\
    \ comp(e);\n                }\n                // Return the minimum registered\
    \ value greater than `e`. if not exists, return `default_value`.\n           \
    \     T min_gt(const T &e, const T &default_value) const {\n                 \
    \   auto it = std::upper_bound(_xs.begin(), _xs.end(), e);\n                 \
    \   return it == _xs.end() ? default_value : *it;\n                }\n       \
    \         // Return the minimum registered value greater than or equal to `e`.\
    \ if not exists, return `default_value`.\n                T min_geq(const T &e,\
    \ const T &default_value) const {\n                    auto it = std::lower_bound(_xs.begin(),\
    \ _xs.end(), e);\n                    return it == _xs.end() ? default_value :\
    \ *it;\n                }\n                // Return the maximum registered value\
    \ less than `e`. if not exists, return `default_value`\n                T max_lt(const\
    \ T &e, const T &default_value) const {\n                    auto it = std::upper_bound(_xs.rbegin(),\
    \ _xs.rend(), e, std::greater<T>());\n                    return it == _xs.rend()\
    \ ? default_value : *it;\n                }\n                // Return the maximum\
    \ registered value less than or equal to `e`. if not exists, return `default_value`\n\
    \                T max_leq(const T &e, const T &default_value) const {\n     \
    \               auto it = std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>());\n\
    \                    return it == _xs.rend() ? default_value : *it;\n        \
    \        }\n                // Return the compressed index of the minimum registered\
    \ value greater than `e`. if not exists, return `compressor.size()`.\n       \
    \         int min_gt_index(const T &e) const {\n                    return std::upper_bound(_xs.begin(),\
    \ _xs.end(), e) - _xs.begin();\n                }\n                // Return the\
    \ compressed index of the minimum registered value greater than or equal to `e`.\
    \ if not exists, return `compressor.size()`.\n                int min_geq_index(const\
    \ T &e) const {\n                    return std::lower_bound(_xs.begin(), _xs.end(),\
    \ e) - _xs.begin();\n                }\n                // Return the compressed\
    \ index of the maximum registered value less than `e`. if not exists, return -1.\n\
    \                int max_lt_index(const T &e) const {\n                    return\
    \ int(_xs.rend() - std::upper_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>()))\
    \ - 1;\n                }\n                // Return the compressed index of the\
    \ maximum registered value less than or equal to `e`. if not exists, return -1.\n\
    \                int max_leq_index(const T &e) const {\n                    return\
    \ int(_xs.rend() - std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>()))\
    \ - 1;\n                }\n            private:\n                std::vector<T>\
    \ _xs;\n                static bool is_strictly_sorted(const std::vector<T> &v)\
    \ {\n                    return std::adjacent_find(v.begin(), v.end(), std::greater_equal<T>())\
    \ == v.end();\n                }\n        };\n        CoordinateCompressorBuilder()\
    \ : _xs(std::vector<T>{}) {}\n        explicit CoordinateCompressorBuilder(const\
    \ std::vector<T> &xs) : _xs(xs) {}\n        explicit CoordinateCompressorBuilder(std::vector<T>\
    \ &&xs) : _xs(std::move(xs)) {}\n        template <typename Gen, constraints_t<std::is_invocable_r<T,\
    \ Gen, int>> = nullptr>\n        CoordinateCompressorBuilder(const int n, Gen\
    \ generator) {\n            reserve(n);\n            for (int i = 0; i < n; ++i)\
    \ push(generator(i));\n        }\n        // Attempt to preallocate enough memory\
    \ for specified number of elements.\n        void reserve(int n) {\n         \
    \   _xs.reserve(n);\n        }\n        // Add data.\n        void push(const\
    \ T &first) {\n            _xs.push_back(first);\n        }\n        // Add data.\n\
    \        void push(T &&first) {\n            _xs.push_back(std::move(first));\n\
    \        }\n        // Add data in the range of [first, last). \n        template\
    \ <typename Iterator>\n        auto push(const Iterator &first, const Iterator\
    \ &last) -> decltype(std::vector<T>{}.push_back(*first), void()) {\n         \
    \   for (auto it = first; it != last; ++it) _xs.push_back(*it);\n        }\n \
    \       // Add all data in the container. Equivalent to `push(iterable.begin(),\
    \ iterable.end())`.\n        template <typename Iterable>\n        auto push(const\
    \ Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()),\
    \ void()) {\n            push(iterable.begin(), iterable.end());\n        }\n\
    \        // Add data.\n        template <typename ...Args>\n        void emplace(Args\
    \ &&...args) {\n            _xs.emplace_back(std::forward<Args>(args)...);\n \
    \       }\n        // Build compressor.\n        auto build() {\n            std::sort(_xs.begin(),\
    \ _xs.end()), _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());\n   \
    \         return Compressor {_xs};\n        }\n        // Build compressor from\
    \ vector.\n        static auto build(const std::vector<T> &xs) {\n           \
    \ return CoordinateCompressorBuilder(xs).build();\n        }\n        // Build\
    \ compressor from vector.\n        static auto build(std::vector<T> &&xs) {\n\
    \            return CoordinateCompressorBuilder(std::move(xs)).build();\n    \
    \    }\n        // Build compressor from generator.\n        template <typename\
    \ Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>\n        static\
    \ auto build(const int n, Gen generator) {\n            return CoordinateCompressorBuilder<T>(n,\
    \ generator).build();\n        }\n    private:\n        std::vector<T> _xs;\n\
    };\n\n} // namespace suisen\n\n\n#line 11 \"library/datastructure/compressed_wavelet_matrix.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, int log_max_len = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    \    struct CompressedWaveletMatrix : private WaveletMatrix<int, log_max_len>\
    \ {\n        // default constructor\n        CompressedWaveletMatrix() noexcept\
    \ : WaveletMatrix<int, log_max_len>(0) {}\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<std::is_invocable_r<T,\
    \ Gen, int>> = nullptr>\n        CompressedWaveletMatrix(int n, Gen generator)\
    \ : WaveletMatrix<int, log_max_len>(n), comp(CoordinateCompressorBuilder<T>::build(n,\
    \ generator)) {\n            this->build([this, &generator](int i) { return comp[generator(i)];\
    \ });\n        }\n        // builds WaveletMatrix from vector\n        template\
    \ <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>\n       \
    \ CompressedWaveletMatrix(const std::vector<U>& a) : CompressedWaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // returns WaveletMatrix[i]\n\
    \        inline T operator[](int i) const {\n            return comp.decomp(WaveletMatrix<int,\
    \ log_max_len>::operator[](i));\n        }\n        // returns WaveletMatrix[i]\n\
    \        inline T access(int i) const {\n            return (*this)[i];\n    \
    \    }\n        // returns the number of `val` in WaveletMatrix[0, i).\n     \
    \   inline int rank(T val, int i) const {\n            int x = comp.comp(val,\
    \ -1);\n            if (x == -1) return 0;\n            return WaveletMatrix<int,\
    \ log_max_len>::rank(x, i);\n        }\n        // returns the k'th smallest value\
    \ in WaveletMatrix[l, r) (k : 0-indexed)\n        inline T range_kth_smallest(int\
    \ l, int r, int k, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_kth_smallest(l, r, k, -1);\n            return x == -1 ?\
    \ default_value : comp.decomp(x);\n        }\n        // returns the k'th largest\
    \ value in WaveletMatrix[l, r) (k : 0-indexed)\n        inline T range_kth_largest(int\
    \ l, int r, int k, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_kth_largest(l, r, k, -1);\n            return x == -1 ?\
    \ default_value : comp.decomp(x);\n        }\n        // returns the minimum value\
    \ in WaveletMatrix[l, r)\n        inline T range_min(int l, int r) const {\n \
    \           return comp.decomp(WaveletMatrix<int, log_max_len>::range_min(l, r));\n\
    \        }\n        // returns the maximum value in WaveletMatrix[l, r)\n    \
    \    inline T range_max(int l, int r) const {\n            return comp.decomp(WaveletMatrix<int,\
    \ log_max_len>::range_max(l, r));\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. v < upper\n        inline int range_freq(int l,\
    \ int r, T upper) const {\n            return WaveletMatrix<int, log_max_len>::range_freq(l,\
    \ r, comp.min_geq_index(upper));\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. lower <= v < upper\n        inline int range_freq(int\
    \ l, int r, T lower, T upper) const {\n            if (lower >= upper) return\
    \ 0;\n            return range_freq(l, r, upper) - range_freq(l, r, lower);\n\
    \        }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t.\
    \ lower <= v\n        inline T range_min_geq(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            int x = WaveletMatrix<int, log_max_len>::range_min_geq(l,\
    \ r, comp.min_geq_index(lower), -1);\n            return x == -1 ? default_value\
    \ : comp.decomp(x);\n        }\n        // returns the minimum value v in WaveletMatrix[l,\
    \ r) s.t. lower < v\n        inline T range_min_gt(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            return lower == std::numeric_limits<T>::max()\
    \ ? default_value : range_min_geq(l, r, lower + 1, default_value);\n        }\n\
    \        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper\n\
    \        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1))\
    \ const {\n            int x = WaveletMatrix<int, log_max_len>::range_max_lt(l,\
    \ r, comp.min_geq_index(upper), -1);\n            return x == -1 ? default_value\
    \ : comp.decomp(x);\n        }\n        // returns the maximum value v in WaveletMatrix[l,\
    \ r) s.t. v <= upper\n        inline T range_max_leq(int l, int r, T upper, T\
    \ default_value = T(-1)) const {\n            if (r >= l) return default_value;\n\
    \            return upper == std::numeric_limits<T>::max() ? range_max(l, r) :\
    \ range_max_lt(l, r, upper + 1, default_value);\n        }\n    private:\n   \
    \     typename CoordinateCompressorBuilder<T>::Compressor comp;\n    };\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_COMP_WAVELET_MATRIX\n#define SUISEN_COMP_WAVELET_MATRIX\n\n\
    #include <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\
    \n#include \"library/datastructure/wavelet_matrix.hpp\"\n#include \"library/util/coordinate_compressor.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, int log_max_len = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    \    struct CompressedWaveletMatrix : private WaveletMatrix<int, log_max_len>\
    \ {\n        // default constructor\n        CompressedWaveletMatrix() noexcept\
    \ : WaveletMatrix<int, log_max_len>(0) {}\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<std::is_invocable_r<T,\
    \ Gen, int>> = nullptr>\n        CompressedWaveletMatrix(int n, Gen generator)\
    \ : WaveletMatrix<int, log_max_len>(n), comp(CoordinateCompressorBuilder<T>::build(n,\
    \ generator)) {\n            this->build([this, &generator](int i) { return comp[generator(i)];\
    \ });\n        }\n        // builds WaveletMatrix from vector\n        template\
    \ <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>\n       \
    \ CompressedWaveletMatrix(const std::vector<U>& a) : CompressedWaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // returns WaveletMatrix[i]\n\
    \        inline T operator[](int i) const {\n            return comp.decomp(WaveletMatrix<int,\
    \ log_max_len>::operator[](i));\n        }\n        // returns WaveletMatrix[i]\n\
    \        inline T access(int i) const {\n            return (*this)[i];\n    \
    \    }\n        // returns the number of `val` in WaveletMatrix[0, i).\n     \
    \   inline int rank(T val, int i) const {\n            int x = comp.comp(val,\
    \ -1);\n            if (x == -1) return 0;\n            return WaveletMatrix<int,\
    \ log_max_len>::rank(x, i);\n        }\n        // returns the k'th smallest value\
    \ in WaveletMatrix[l, r) (k : 0-indexed)\n        inline T range_kth_smallest(int\
    \ l, int r, int k, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_kth_smallest(l, r, k, -1);\n            return x == -1 ?\
    \ default_value : comp.decomp(x);\n        }\n        // returns the k'th largest\
    \ value in WaveletMatrix[l, r) (k : 0-indexed)\n        inline T range_kth_largest(int\
    \ l, int r, int k, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_kth_largest(l, r, k, -1);\n            return x == -1 ?\
    \ default_value : comp.decomp(x);\n        }\n        // returns the minimum value\
    \ in WaveletMatrix[l, r)\n        inline T range_min(int l, int r) const {\n \
    \           return comp.decomp(WaveletMatrix<int, log_max_len>::range_min(l, r));\n\
    \        }\n        // returns the maximum value in WaveletMatrix[l, r)\n    \
    \    inline T range_max(int l, int r) const {\n            return comp.decomp(WaveletMatrix<int,\
    \ log_max_len>::range_max(l, r));\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. v < upper\n        inline int range_freq(int l,\
    \ int r, T upper) const {\n            return WaveletMatrix<int, log_max_len>::range_freq(l,\
    \ r, comp.min_geq_index(upper));\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. lower <= v < upper\n        inline int range_freq(int\
    \ l, int r, T lower, T upper) const {\n            if (lower >= upper) return\
    \ 0;\n            return range_freq(l, r, upper) - range_freq(l, r, lower);\n\
    \        }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t.\
    \ lower <= v\n        inline T range_min_geq(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            int x = WaveletMatrix<int, log_max_len>::range_min_geq(l,\
    \ r, comp.min_geq_index(lower), -1);\n            return x == -1 ? default_value\
    \ : comp.decomp(x);\n        }\n        // returns the minimum value v in WaveletMatrix[l,\
    \ r) s.t. lower < v\n        inline T range_min_gt(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            return lower == std::numeric_limits<T>::max()\
    \ ? default_value : range_min_geq(l, r, lower + 1, default_value);\n        }\n\
    \        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper\n\
    \        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1))\
    \ const {\n            int x = WaveletMatrix<int, log_max_len>::range_max_lt(l,\
    \ r, comp.min_geq_index(upper), -1);\n            return x == -1 ? default_value\
    \ : comp.decomp(x);\n        }\n        // returns the maximum value v in WaveletMatrix[l,\
    \ r) s.t. v <= upper\n        inline T range_max_leq(int l, int r, T upper, T\
    \ default_value = T(-1)) const {\n            if (r >= l) return default_value;\n\
    \            return upper == std::numeric_limits<T>::max() ? range_max(l, r) :\
    \ range_max_lt(l, r, upper + 1, default_value);\n        }\n    private:\n   \
    \     typename CoordinateCompressorBuilder<T>::Compressor comp;\n    };\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_COMP_WAVELET_MATRIX\n"
  dependsOn:
  - library/datastructure/wavelet_matrix.hpp
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  - library/util/coordinate_compressor.hpp
  isVerificationFile: false
  path: library/datastructure/compressed_wavelet_matrix.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/compressed_wavelet_matrix/static_range_frequency.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
documentation_of: library/datastructure/compressed_wavelet_matrix.hpp
layout: document
title: Compressed Wavelet Matrix
---
## Compressed Wavelet Matrix