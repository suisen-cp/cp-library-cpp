---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: Bit Vector
  - icon: ':heavy_check_mark:'
    path: library/datastructure/wavelet_matrix.hpp
    title: Wavelet Matrix
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/datastructure/wavelet_matrix.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\n#line\
    \ 1 \"library/datastructure/bit_vector.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 7 \"\
    library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
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
    \ == 0);\n        }\n    };\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp\"\
    \n\nusing suisen::WaveletMatrix;\n\nconstexpr int MAX_LOG = 30;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<int> a(n);\n    for (auto &e\
    \ : a) std::cin >> e;\n    WaveletMatrix<int, MAX_LOG> wm(a);\n    while (q -->\
    \ 0) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout\
    \ << wm.range_kth_smallest(l, r, k) << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include <iostream>\n\n#include \"library/datastructure/wavelet_matrix.hpp\"\n\
    \nusing suisen::WaveletMatrix;\n\nconstexpr int MAX_LOG = 30;\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n,\
    \ q;\n    std::cin >> n >> q;\n    std::vector<int> a(n);\n    for (auto &e :\
    \ a) std::cin >> e;\n    WaveletMatrix<int, MAX_LOG> wm(a);\n    while (q -->\
    \ 0) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout\
    \ << wm.range_kth_smallest(l, r, k) << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/wavelet_matrix.hpp
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
- /verify/test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp.html
title: test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
---
