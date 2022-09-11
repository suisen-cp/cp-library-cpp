---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bit_vector.hpp
    title: Bit Vector
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/uncategorized/static_range_xored_mex_query.hpp
    title: Static Range Xored Mex Query
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <random>\n\n#line 1 \"\
    library/uncategorized/static_range_xored_mex_query.hpp\"\n\n\n\n#include <cassert>\n\
    #include <array>\n#include <type_traits>\n#include <limits>\n\n#line 1 \"library/datastructure/bit_vector.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 6 \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\
    // ! utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    namespace suisen {\n    struct BitVector {\n        explicit BitVector(int n)\
    \ : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl, 0),\
    \ cum_s(ns, 0), bits(ns, 0) {}\n        BitVector() : BitVector(0) {}\n      \
    \  template <typename Gen, constraints_t<is_same_as_invoke_result<bool, Gen, int>>\
    \ = nullptr>\n        BitVector(int n, Gen gen) : BitVector(n) {\n           \
    \ build(gen);\n        }\n        BitVector& operator=(const BitVector& bv) {\n\
    \            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s = bv.cum_s,\
    \ bits = bv.bits;\n            return *this;\n        }\n        BitVector& operator=(BitVector&&\
    \ bv) {\n            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = std::move(bv.cum_l),\
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
    \ 10 \"library/uncategorized/static_range_xored_mex_query.hpp\"\n\nnamespace suisen\
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
    } // namespace suisen\n\n\n#line 8 \"test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp\"\
    \n\ntemplate <typename T>\nstruct NaiveSolution {\n    NaiveSolution() = default;\n\
    \    NaiveSolution(const std::vector<T> &dat) : dat(dat) {}\n\n    T minimum_excluded(int\
    \ l, int r, T x) {\n        std::vector<T> st;\n        for (int i = l; i < r;\
    \ ++i) st.push_back(dat[i] ^ x);\n        std::sort(st.begin(), st.end());\n \
    \       st.erase(std::unique(st.begin(), st.end()), st.end());\n        st.push_back(std::numeric_limits<int>::max());\n\
    \        for (int i = 0;; ++i) {\n            if (st[i] != i) return i;\n    \
    \    }\n    }\nprivate:\n    std::vector<T> dat;\n};\n\nstd::mt19937 rng{0};\n\
    \ntemplate <typename T, int bit_num>\nvoid test(int n, int q) {\n    std::uniform_int_distribution<T>\
    \ value_dist(0, (T(1) << bit_num) - 1);\n    std::vector<T> dat(n);\n    for (auto\
    \ &e : dat) e = value_dist(rng);\n    \n    suisen::RangeXoredMexQuery<T, bit_num>\
    \ wm(dat);\n    NaiveSolution<T> naive(dat);\n\n    for (int l = 0; l <= n; ++l)\
    \ for (int r = l; r <= n; ++r) {\n        for (int t = 0; t < q; ++t) {\n    \
    \        int x = value_dist(rng);\n            assert(wm.minimum_excluded(l, r,\
    \ x) == naive.minimum_excluded(l, r, x));\n        }\n    }\n    std::cerr <<\
    \ \"done\" << std::endl;\n}\n\nvoid tests() {\n    // std::vector<int> dat { 0,\
    \ 1, 2, 3, 4 };\n    // suisen::RangeXoredMexQuery<int, 3> wm(dat);\n    // NaiveSolution<int>\
    \ naive(dat);\n    // for (int l = 0; l <= 5; ++l) for (int r = l; r <= 5; ++r)\
    \ {\n    //     for (int x = 0; x <= 5; ++x) {\n    //         std::cerr << \"\
    sub array : [\";\n    //         for (int i = l; i < r; ++i) {\n    //       \
    \      std::cerr << (dat[i] ^ x);\n    //             if (i < r - 1) std::cerr\
    \ << \",\";\n    //         }\n    //         std::cerr << \"]\" << std::endl;\n\
    \    //         int mex1 = wm.minimum_excluded(l, r, x);\n    //         std::cerr\
    \ << \"actual   : \" << mex1 << std::endl;\n    //         int mex2 = naive.minimum_excluded(l,\
    \ r, x);\n    //         std::cerr << \"expected : \" << mex2 << std::endl;\n\
    \    //     }\n    // }\n\n\n    test<int, 1>(100, 100);\n    test<int, 2>(100,\
    \ 100);\n    test<int, 3>(100, 100);\n    test<int, 4>(100, 100);\n    test<int,\
    \ 5>(100, 100);\n    test<int, 6>(100, 100);\n}\n\nint main() {\n    tests();\n\
    \    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <random>\n\n#include \"\
    library/uncategorized/static_range_xored_mex_query.hpp\"\n\ntemplate <typename\
    \ T>\nstruct NaiveSolution {\n    NaiveSolution() = default;\n    NaiveSolution(const\
    \ std::vector<T> &dat) : dat(dat) {}\n\n    T minimum_excluded(int l, int r, T\
    \ x) {\n        std::vector<T> st;\n        for (int i = l; i < r; ++i) st.push_back(dat[i]\
    \ ^ x);\n        std::sort(st.begin(), st.end());\n        st.erase(std::unique(st.begin(),\
    \ st.end()), st.end());\n        st.push_back(std::numeric_limits<int>::max());\n\
    \        for (int i = 0;; ++i) {\n            if (st[i] != i) return i;\n    \
    \    }\n    }\nprivate:\n    std::vector<T> dat;\n};\n\nstd::mt19937 rng{0};\n\
    \ntemplate <typename T, int bit_num>\nvoid test(int n, int q) {\n    std::uniform_int_distribution<T>\
    \ value_dist(0, (T(1) << bit_num) - 1);\n    std::vector<T> dat(n);\n    for (auto\
    \ &e : dat) e = value_dist(rng);\n    \n    suisen::RangeXoredMexQuery<T, bit_num>\
    \ wm(dat);\n    NaiveSolution<T> naive(dat);\n\n    for (int l = 0; l <= n; ++l)\
    \ for (int r = l; r <= n; ++r) {\n        for (int t = 0; t < q; ++t) {\n    \
    \        int x = value_dist(rng);\n            assert(wm.minimum_excluded(l, r,\
    \ x) == naive.minimum_excluded(l, r, x));\n        }\n    }\n    std::cerr <<\
    \ \"done\" << std::endl;\n}\n\nvoid tests() {\n    // std::vector<int> dat { 0,\
    \ 1, 2, 3, 4 };\n    // suisen::RangeXoredMexQuery<int, 3> wm(dat);\n    // NaiveSolution<int>\
    \ naive(dat);\n    // for (int l = 0; l <= 5; ++l) for (int r = l; r <= 5; ++r)\
    \ {\n    //     for (int x = 0; x <= 5; ++x) {\n    //         std::cerr << \"\
    sub array : [\";\n    //         for (int i = l; i < r; ++i) {\n    //       \
    \      std::cerr << (dat[i] ^ x);\n    //             if (i < r - 1) std::cerr\
    \ << \",\";\n    //         }\n    //         std::cerr << \"]\" << std::endl;\n\
    \    //         int mex1 = wm.minimum_excluded(l, r, x);\n    //         std::cerr\
    \ << \"actual   : \" << mex1 << std::endl;\n    //         int mex2 = naive.minimum_excluded(l,\
    \ r, x);\n    //         std::cerr << \"expected : \" << mex2 << std::endl;\n\
    \    //     }\n    // }\n\n\n    test<int, 1>(100, 100);\n    test<int, 2>(100,\
    \ 100);\n    test<int, 3>(100, 100);\n    test<int, 4>(100, 100);\n    test<int,\
    \ 5>(100, 100);\n    test<int, 6>(100, 100);\n}\n\nint main() {\n    tests();\n\
    \    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/uncategorized/static_range_xored_mex_query.hpp
  - library/datastructure/bit_vector.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-07-11 23:27:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp
- /verify/test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp.html
title: test/src/uncategorized/static_range_xored_mex_query/dummy.test.cpp
---
