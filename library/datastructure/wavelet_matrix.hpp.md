---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: library/datastructure/bit_vector.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/compressed_wavelet_matrix.hpp
    title: library/datastructure/compressed_wavelet_matrix.hpp
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
  bundledCode: "#line 1 \"library/datastructure/wavelet_matrix.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\n#line\
    \ 1 \"library/datastructure/bit_vector.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 6 \"\
    library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n// ! utility\ntemplate\
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
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 8 \"library/datastructure/bit_vector.hpp\"\
    \n\nnamespace suisen {\nclass BitVector {\n    using u8 = std::uint8_t;\n    public:\n\
    \        explicit BitVector(int n) : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >>\
    \ LOG_BLOCK_S) + 1), cum_l(nl, 0), cum_s(ns, 0), bits(ns, 0) {}\n        BitVector()\
    \ : BitVector(0) {}\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
    \ Gen, int>> = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n\
    \            build(gen);\n        }\n        BitVector& operator=(const BitVector\
    \ &bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s\
    \ = bv.cum_s, bits = bv.bits;\n            return *this;\n        }\n        BitVector&\
    \ operator=(BitVector &&bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l\
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
    \        }\n};\n} // namespace suisen\n\n\n#line 10 \"library/datastructure/wavelet_matrix.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    class WaveletMatrix {\n    public:\n        // default constructor\n        WaveletMatrix()\
    \ noexcept : n(0) {}\n        // builds WaveletMatrix from generating function\
    \ typed as (int) -> T\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
    \ Gen, int>> = nullptr>\n        WaveletMatrix(int n, Gen generator) : n(n) {\n\
    \            build(generator);\n        }\n        // builds WaveletMatrix from\
    \ vector\n        template <typename U, constraints_t<std::is_constructible<T,\
    \ U>> = nullptr>\n        WaveletMatrix(const std::vector<U> &a) : WaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
    \ Gen, int>>  = nullptr>\n        void build(Gen generator) {\n            std::vector<T>\
    \ a(n), l(n), r(n);\n            for (int i = 0; i < n; ++i) a[i] = generator(i);\n\
    \            for (int log = bit_num - 1; log >= 0; --log) {\n                bv[log]\
    \ = BitVector(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });\n  \
    \              int li = 0, ri = 0;\n                for (int i = 0; i < n; ++i)\
    \ {\n                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];\n   \
    \             }\n                a.swap(l);\n                std::copy(r.begin(),\
    \ r.begin() + ri, a.begin() + li);\n                mid[log] = li;\n         \
    \   }\n        }\n        // returns WaveletMatrix[i]\n        T operator[](int\
    \ i) const {\n            T res = 0;\n            for (int log = bit_num - 1;\
    \ log >= 0; --log) {\n                bool b = bv[log][i];\n                res\
    \ |= T(b) << log;\n                i = b * mid[log] + bv[log].rank(b, i);\n  \
    \          }\n            return res;\n        }\n        // returns WaveletMatrix[i]\n\
    \        inline T access(int i) const {\n            return (*this)[i];\n    \
    \    }\n        // returns the number of `val` in WaveletMatrix[0, i).\n     \
    \   int rank(T val, int i) const {\n            check_value_bounds(val);\n   \
    \         int l = 0, r = i;\n            for (int log = bit_num - 1; log >= 0;\
    \ --log) succ(l, r, (val >> log) & 1, log);\n            return r - l;\n     \
    \   }\n        // returns the k'th smallest value in WaveletMatrix[l, r) (k :\
    \ 0-indexed)\n        T range_kth_smallest(int l, int r, int k, T default_value\
    \ = T(-1)) const {\n            if (k < 0 or k >= r - l) return default_value;\n\
    \            T res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                int cnt_0 = bv[log].rank(false, l, r);\n                bool\
    \ bit = k >= cnt_0;\n                succ(l, r, bit, log);\n                res\
    \ |= T(bit) << log;\n                k -= bit * cnt_0;\n            }\n      \
    \      return res;\n        }\n        // returns the k'th largest value in WaveletMatrix[l,\
    \ r) (k : 0-indexed)\n        inline T range_kth_largest(int l, int r, int k,\
    \ T default_value = T(-1)) const {\n            return range_kth_smallest(l, r,\
    \ r - l - 1 - k, default_value);\n        }\n        // returns the minimum value\
    \ in WaveletMatrix[l, r)\n        inline T range_min(int l, int r) const {\n \
    \           assert(l < r);\n            return range_kth_smallest(l, r, 0);\n\
    \        }\n        // returns the maximum value in WaveletMatrix[l, r)\n    \
    \    inline T range_max(int l, int r) const {\n            assert(l < r);\n  \
    \          return range_kth_largest(l, r, 0);\n        }\n        // returns the\
    \ number of v in WaveletMatrix[l, r) s.t. v < upper\n        int range_freq(int\
    \ l, int r, T upper) const {\n            if (r <= l) return 0;\n            check_value_bounds(upper);\n\
    \            int res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                bool b = (upper >> log) & 1;\n                if (b) res\
    \ += bv[log].rank(false, l, r);\n                succ(l, r, b, log);\n       \
    \     }\n            return res;\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. lower <= v < upper\n        inline int range_freq(int\
    \ l, int r, T lower, T upper) const {\n            if (lower >= upper) return\
    \ 0;\n            return range_freq(l, r, upper) - range_freq(l, r, lower);\n\
    \        }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t.\
    \ lower <= v\n        inline T range_min_geq(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            int cnt = range_freq(l, r, lower);\n         \
    \   return cnt >= r - l ? default_value : range_kth_smallest(l, r, cnt);\n   \
    \     }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower\
    \ < v\n        inline T range_min_gt(int l, int r, T lower, T default_value =\
    \ T(-1)) const {\n            return lower == MAX ? default_value : range_min_geq(l,\
    \ r, lower + 1);\n        }\n        // returns the maximum value v in WaveletMatrix[l,\
    \ r) s.t. v < upper\n        inline T range_max_lt(int l, int r, T upper, T default_value\
    \ = T(-1)) const {\n            int cnt = range_freq(l, r, upper);\n         \
    \   return cnt == 0 ? default_value : range_kth_smallest(l, r, cnt - 1);\n   \
    \     }\n        // returns the maximum value v in WaveletMatrix[l, r) s.t. v\
    \ <= upper\n        inline T range_max_leq(int l, int r, T upper, T default_value\
    \ = T(-1)) const {\n            if (r >= l) return default_value;\n          \
    \  return upper == MAX ? range_max(l, r) : range_max_lt(l, r, upper + 1);\n  \
    \      }\n    protected:\n        WaveletMatrix(int n) noexcept : n(n) {}\n  \
    \  private:\n        static_assert(bit_num > 0);\n        static constexpr T MAX\
    \ = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max()\
    \ : (T(1) << bit_num) - 1;\n\n        int n;\n        std::array<BitVector, bit_num>\
    \ bv;\n        std::array<int, bit_num> mid;\n\n        inline void succ(int &l,\
    \ int &r, const bool b, const int log) const {\n            l = b * mid[log] +\
    \ bv[log].rank(b, l);\n            r = b * mid[log] + bv[log].rank(b, r);\n  \
    \      }\n\n        static constexpr void check_value_bounds(T val) {\n      \
    \      assert((val >> bit_num) == 0);\n        }\n};\n\n\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_WAVELET_MATRIX\n#define SUISEN_WAVELET_MATRIX\n\n#include\
    \ <cassert>\n#include <array>\n#include <type_traits>\n#include <limits>\n\n#include\
    \ \"library/datastructure/bit_vector.hpp\"\n\nnamespace suisen {\ntemplate <typename\
    \ T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>\nclass\
    \ WaveletMatrix {\n    public:\n        // default constructor\n        WaveletMatrix()\
    \ noexcept : n(0) {}\n        // builds WaveletMatrix from generating function\
    \ typed as (int) -> T\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
    \ Gen, int>> = nullptr>\n        WaveletMatrix(int n, Gen generator) : n(n) {\n\
    \            build(generator);\n        }\n        // builds WaveletMatrix from\
    \ vector\n        template <typename U, constraints_t<std::is_constructible<T,\
    \ U>> = nullptr>\n        WaveletMatrix(const std::vector<U> &a) : WaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
    \ Gen, int>>  = nullptr>\n        void build(Gen generator) {\n            std::vector<T>\
    \ a(n), l(n), r(n);\n            for (int i = 0; i < n; ++i) a[i] = generator(i);\n\
    \            for (int log = bit_num - 1; log >= 0; --log) {\n                bv[log]\
    \ = BitVector(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });\n  \
    \              int li = 0, ri = 0;\n                for (int i = 0; i < n; ++i)\
    \ {\n                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];\n   \
    \             }\n                a.swap(l);\n                std::copy(r.begin(),\
    \ r.begin() + ri, a.begin() + li);\n                mid[log] = li;\n         \
    \   }\n        }\n        // returns WaveletMatrix[i]\n        T operator[](int\
    \ i) const {\n            T res = 0;\n            for (int log = bit_num - 1;\
    \ log >= 0; --log) {\n                bool b = bv[log][i];\n                res\
    \ |= T(b) << log;\n                i = b * mid[log] + bv[log].rank(b, i);\n  \
    \          }\n            return res;\n        }\n        // returns WaveletMatrix[i]\n\
    \        inline T access(int i) const {\n            return (*this)[i];\n    \
    \    }\n        // returns the number of `val` in WaveletMatrix[0, i).\n     \
    \   int rank(T val, int i) const {\n            check_value_bounds(val);\n   \
    \         int l = 0, r = i;\n            for (int log = bit_num - 1; log >= 0;\
    \ --log) succ(l, r, (val >> log) & 1, log);\n            return r - l;\n     \
    \   }\n        // returns the k'th smallest value in WaveletMatrix[l, r) (k :\
    \ 0-indexed)\n        T range_kth_smallest(int l, int r, int k, T default_value\
    \ = T(-1)) const {\n            if (k < 0 or k >= r - l) return default_value;\n\
    \            T res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                int cnt_0 = bv[log].rank(false, l, r);\n                bool\
    \ bit = k >= cnt_0;\n                succ(l, r, bit, log);\n                res\
    \ |= T(bit) << log;\n                k -= bit * cnt_0;\n            }\n      \
    \      return res;\n        }\n        // returns the k'th largest value in WaveletMatrix[l,\
    \ r) (k : 0-indexed)\n        inline T range_kth_largest(int l, int r, int k,\
    \ T default_value = T(-1)) const {\n            return range_kth_smallest(l, r,\
    \ r - l - 1 - k, default_value);\n        }\n        // returns the minimum value\
    \ in WaveletMatrix[l, r)\n        inline T range_min(int l, int r) const {\n \
    \           assert(l < r);\n            return range_kth_smallest(l, r, 0);\n\
    \        }\n        // returns the maximum value in WaveletMatrix[l, r)\n    \
    \    inline T range_max(int l, int r) const {\n            assert(l < r);\n  \
    \          return range_kth_largest(l, r, 0);\n        }\n        // returns the\
    \ number of v in WaveletMatrix[l, r) s.t. v < upper\n        int range_freq(int\
    \ l, int r, T upper) const {\n            if (r <= l) return 0;\n            check_value_bounds(upper);\n\
    \            int res = 0;\n            for (int log = bit_num - 1; log >= 0; --log)\
    \ {\n                bool b = (upper >> log) & 1;\n                if (b) res\
    \ += bv[log].rank(false, l, r);\n                succ(l, r, b, log);\n       \
    \     }\n            return res;\n        }\n        // returns the number of\
    \ v in WaveletMatrix[l, r) s.t. lower <= v < upper\n        inline int range_freq(int\
    \ l, int r, T lower, T upper) const {\n            if (lower >= upper) return\
    \ 0;\n            return range_freq(l, r, upper) - range_freq(l, r, lower);\n\
    \        }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t.\
    \ lower <= v\n        inline T range_min_geq(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            int cnt = range_freq(l, r, lower);\n         \
    \   return cnt >= r - l ? default_value : range_kth_smallest(l, r, cnt);\n   \
    \     }\n        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower\
    \ < v\n        inline T range_min_gt(int l, int r, T lower, T default_value =\
    \ T(-1)) const {\n            return lower == MAX ? default_value : range_min_geq(l,\
    \ r, lower + 1);\n        }\n        // returns the maximum value v in WaveletMatrix[l,\
    \ r) s.t. v < upper\n        inline T range_max_lt(int l, int r, T upper, T default_value\
    \ = T(-1)) const {\n            int cnt = range_freq(l, r, upper);\n         \
    \   return cnt == 0 ? default_value : range_kth_smallest(l, r, cnt - 1);\n   \
    \     }\n        // returns the maximum value v in WaveletMatrix[l, r) s.t. v\
    \ <= upper\n        inline T range_max_leq(int l, int r, T upper, T default_value\
    \ = T(-1)) const {\n            if (r >= l) return default_value;\n          \
    \  return upper == MAX ? range_max(l, r) : range_max_lt(l, r, upper + 1);\n  \
    \      }\n    protected:\n        WaveletMatrix(int n) noexcept : n(n) {}\n  \
    \  private:\n        static_assert(bit_num > 0);\n        static constexpr T MAX\
    \ = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max()\
    \ : (T(1) << bit_num) - 1;\n\n        int n;\n        std::array<BitVector, bit_num>\
    \ bv;\n        std::array<int, bit_num> mid;\n\n        inline void succ(int &l,\
    \ int &r, const bool b, const int log) const {\n            l = b * mid[log] +\
    \ bv[log].rank(b, l);\n            r = b * mid[log] + bv[log].rank(b, r);\n  \
    \      }\n\n        static constexpr void check_value_bounds(T val) {\n      \
    \      assert((val >> bit_num) == 0);\n        }\n};\n\n\n} // namespace suisen\n\
    \n#endif // SUISEN_WAVELET_MATRIX\n"
  dependsOn:
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/wavelet_matrix.hpp
  requiredBy:
  - library/datastructure/compressed_wavelet_matrix.hpp
  timestamp: '2021-11-28 20:19:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/compressed_wavelet_matrix/static_range_frequency.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/static_rmq.test.cpp
  - test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  - test/src/datastructure/wavelet_matrix/static_range_frequency.test.cpp
  - test/src/datastructure/wavelet_matrix/static_rmq.test.cpp
  - test/src/datastructure/wavelet_matrix/range_kth_smallest.test.cpp
documentation_of: library/datastructure/wavelet_matrix.hpp
layout: document
redirect_from:
- /library/library/datastructure/wavelet_matrix.hpp
- /library/library/datastructure/wavelet_matrix.hpp.html
title: library/datastructure/wavelet_matrix.hpp
---
