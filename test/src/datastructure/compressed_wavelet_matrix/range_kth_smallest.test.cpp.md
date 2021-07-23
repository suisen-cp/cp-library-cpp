---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: library/datastructure/bit_vector.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/compressed_wavelet_matrix.hpp
    title: library/datastructure/compressed_wavelet_matrix.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/wavelet_matrix.hpp
    title: library/datastructure/wavelet_matrix.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/coordinate_compressor.hpp
    title: library/util/coordinate_compressor.hpp
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
  bundledCode: "#line 1 \"test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/datastructure/compressed_wavelet_matrix.hpp\"\
    \n\n\n\n#include <cassert>\n#include <array>\n#include <type_traits>\n#include\
    \ <limits>\n\n#line 1 \"library/datastructure/wavelet_matrix.hpp\"\n\n\n\n#line\
    \ 8 \"library/datastructure/wavelet_matrix.hpp\"\n\n#line 1 \"library/datastructure/bit_vector.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 6 \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\
    // ! utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 8 \"\
    library/datastructure/bit_vector.hpp\"\n\nnamespace suisen {\nclass BitVector\
    \ {\n    using u8 = std::uint8_t;\n    public:\n        explicit BitVector(int\
    \ n) : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl,\
    \ 0), cum_s(ns, 0), bits(ns, 0) {}\n        BitVector() : BitVector(0) {}\n  \
    \      template <typename Gen, constraints_t<is_same_as_invoke_result<bool, Gen,\
    \ int>> = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n     \
    \       build(gen);\n        }\n        BitVector& operator=(const BitVector &bv)\
    \ {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s = bv.cum_s,\
    \ bits = bv.bits;\n            return *this;\n        }\n        BitVector& operator=(BitVector\
    \ &&bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = std::move(bv.cum_l),\
    \ cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);\n            return\
    \ *this;\n        }\n        template <typename Gen, constraints_t<is_same_as_invoke_result<bool,\
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
    \ l, int r, T lower, T upper) const {\n            return range_freq(l, r, upper)\
    \ - range_freq(l, r, lower);\n        }\n        // returns the minimum value\
    \ v in WaveletMatrix[l, r) s.t. lower <= v\n        inline T range_min_geq(int\
    \ l, int r, T lower, T default_value = T(-1)) const {\n            int cnt = range_freq(l,\
    \ r, lower);\n            return cnt >= r - l ? default_value : range_kth_smallest(l,\
    \ r, cnt);\n        }\n        // returns the minimum value v in WaveletMatrix[l,\
    \ r) s.t. lower < v\n        inline T range_min_gt(int l, int r, T lower, T default_value\
    \ = T(-1)) const {\n            return lower == MAX ? default_value : range_min_geq(l,\
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
    \ : (T(1) << bit_num) - 1;\n\n        const int n;\n        std::array<BitVector,\
    \ bit_num> bv;\n        std::array<int, bit_num> mid;\n\n        inline void succ(int\
    \ &l, int &r, const bool b, const int log) const {\n            l = b * mid[log]\
    \ + bv[log].rank(b, l);\n            r = b * mid[log] + bv[log].rank(b, r);\n\
    \        }\n\n        static constexpr void check_value_bounds(T val) {\n    \
    \        assert((val >> bit_num) == 0);\n        }\n};\n\n\n} // namespace suisen\n\
    \n\n#line 1 \"library/util/coordinate_compressor.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 7 \"library/util/coordinate_compressor.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <typename T>\nclass coordinate_compressor {\n    public:\n        explicit coordinate_compressor()\
    \ noexcept {}\n\n        void reserve(int n) { _xs.reserve(n); }\n    \n     \
    \   void push(const T  &first) { _xs.push_back(first), _built = false; }\n   \
    \     void push(const T &&first) { _xs.push_back(first), _built = false; }\n \
    \       template <typename Iterator>\n        auto push(const Iterator first,\
    \ const Iterator last) -> decltype(std::vector<T>{}.push_back(*first), void())\
    \ {\n            for (auto it = first; it != last; ++it) _xs.push_back(*it);\n\
    \            _built = false;\n        }\n        template <typename Iterable>\n\
    \        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()),\
    \ void()) {\n            push(iterable.begin(), iterable.end());\n        }\n\
    \        template <typename ...Args>\n        void emplace(Args  &...args) { _xs.emplace_back(std::forward<Args>(args)...),\
    \ _built = false; }\n        template <typename ...Args>\n        void emplace(Args\
    \ &&...args) { _xs.emplace_back(std::forward<Args>(args)...), _built = false;\
    \ }\n    \n        void build() {\n            std::sort(_xs.begin(), _xs.end());\n\
    \            _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());\n    \
    \        _built = true;\n        }\n    \n        inline int size() const {\n\
    \            assert(_built);\n            return _xs.size();\n        }\n    \
    \    inline int comp(const T e, int default_value = -1) const {\n            const\
    \ int res = lower_bound(e);\n            return res < int(_xs.size()) and _xs[res]\
    \ == e ? res : default_value;\n        }\n        inline T decomp(const int compressed)\
    \ const {\n            assert(_built);\n            return _xs[compressed];\n\
    \        }\n        inline int operator[](const T e) const {\n            return\
    \ comp(e);\n        }\n        inline int lower_bound(const T e) const {\n   \
    \         assert(_built);\n            return std::lower_bound(_xs.begin(), _xs.end(),\
    \ e) - _xs.begin();\n        }\n        inline int upper_bound(const T e) const\
    \ {\n            assert(_built);\n            return std::upper_bound(_xs.begin(),\
    \ _xs.end(), e) - _xs.begin();\n        }\n        inline bool has_key(const T\
    \ e) const {\n            assert(_built);\n            int index = lower_bound(e);\n\
    \            return index < size() and _xs[index] == e;\n        }\n    private:\n\
    \        std::vector<T> _xs;\n        bool _built = true;\n};\n} // namespace\
    \ suisen\n\n\n#line 11 \"library/datastructure/compressed_wavelet_matrix.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, int log_max_len = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    class CompressedWaveletMatrix : public WaveletMatrix<int, log_max_len> {\n   \
    \ public:\n        // default constructor\n        CompressedWaveletMatrix() noexcept\
    \ : WaveletMatrix<int, log_max_len>(0) {}\n        // builds WaveletMatrix from\
    \ generating function typed as (int) -> T\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
    \ Gen, int>> = nullptr>\n        CompressedWaveletMatrix(int n, Gen generator)\
    \ : WaveletMatrix<int, log_max_len>(n) {\n            comp.reserve(n);\n     \
    \       for (int i = 0; i < n; ++i) comp.push(generator(i));\n            comp.build();\n\
    \            this->build([this, &generator](int i) { return comp[generator(i)];\
    \ });\n        }\n        // builds WaveletMatrix from vector\n        template\
    \ <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>\n       \
    \ CompressedWaveletMatrix(const std::vector<U> &a) : CompressedWaveletMatrix(a.size(),\
    \ [&a](int i) { return T(a[i]); }) {}\n\n        // returns WaveletMatrix[i]\n\
    \        inline T operator[](int i) const {\n            return comp.decomp(WaveletMatrix<int,\
    \ log_max_len>::operator[](i));\n        }\n        // returns WaveletMatrix[i]\n\
    \        inline T access(int i) const {\n            return (*this)[i];\n    \
    \    }\n        // returns the number of `val` in WaveletMatrix[0, i).\n     \
    \   inline int rank(T val, int i) const {\n            int x = comp.comp(val,\
    \ -1);\n            if (x == -1) return 0; \n            return WaveletMatrix<int,\
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
    \ r, comp.lower_bound(upper));\n        }\n        // returns the number of v\
    \ in WaveletMatrix[l, r) s.t. lower <= v < upper\n        inline int range_freq(int\
    \ l, int r, T lower, T upper) const {\n            return range_freq(l, r, upper)\
    \ - range_freq(l, r, lower);\n        }\n        // returns the minimum value\
    \ v in WaveletMatrix[l, r) s.t. lower <= v\n        inline T range_min_geq(int\
    \ l, int r, T lower, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_min_geq(l, r, comp.lower_bound(lower), -1);\n          \
    \  return x == -1 ? default_value : comp.decomp(x);\n        }\n        // returns\
    \ the minimum value v in WaveletMatrix[l, r) s.t. lower < v\n        inline T\
    \ range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {\n     \
    \       return lower == std::numeric_limits<T>::max() ? default_value : range_min_geq(l,\
    \ r, lower + 1, default_value);\n        }\n        // returns the maximum value\
    \ v in WaveletMatrix[l, r) s.t. v < upper\n        inline T range_max_lt(int l,\
    \ int r, T upper, T default_value = T(-1)) const {\n            int x = WaveletMatrix<int,\
    \ log_max_len>::range_max_lt(l, r, comp.lower_bound(upper), -1);\n           \
    \ return x == -1 ? default_value : comp.decomp(x);\n        }\n        // returns\
    \ the maximum value v in WaveletMatrix[l, r) s.t. v <= upper\n        inline T\
    \ range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {\n    \
    \        if (r >= l) return default_value;\n            return upper == std::numeric_limits<T>::max()\
    \ ? range_max(l, r) : range_max_lt(l, r, upper + 1, default_value);\n        }\n\
    \    private:\n        coordinate_compressor<T> comp;\n};\n} // namespace suisen\n\
    \n\n\n#line 6 \"test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp\"\
    \n\nusing suisen::CompressedWaveletMatrix;\n\nconstexpr int MAX_LOG = 18;\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n    CompressedWaveletMatrix<int, MAX_LOG> wm(a);\n \
    \   while (q --> 0) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\
    \        std::cout << wm.range_kth_smallest(l, r, k) << '\\n';\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include <iostream>\n\n#include \"library/datastructure/compressed_wavelet_matrix.hpp\"\
    \n\nusing suisen::CompressedWaveletMatrix;\n\nconstexpr int MAX_LOG = 18;\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n    CompressedWaveletMatrix<int, MAX_LOG> wm(a);\n \
    \   while (q --> 0) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\
    \        std::cout << wm.range_kth_smallest(l, r, k) << '\\n';\n    }\n    return\
    \ 0;\n}"
  dependsOn:
  - library/datastructure/compressed_wavelet_matrix.hpp
  - library/datastructure/wavelet_matrix.hpp
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  - library/util/coordinate_compressor.hpp
  isVerificationFile: true
  path: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2021-07-23 22:01:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
- /verify/test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp.html
title: test/src/datastructure/compressed_wavelet_matrix/range_kth_smallest.test.cpp
---
