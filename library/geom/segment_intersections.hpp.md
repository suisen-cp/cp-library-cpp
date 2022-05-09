---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/fenwick_tree.hpp
    title: Fenwick Tree
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/coordinate_compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/geom/segment_intersections/CGL_6_A.test.cpp
    title: test/src/geom/segment_intersections/CGL_6_A.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/geom/segment_intersections.hpp\"\n\n\n\n#include\
    \ <iostream>\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 9 \"library/util/coordinate_compressor.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <typename T>\nclass CoordinateCompressorBuilder {\n    public:\n        struct\
    \ Compressor {\n            public:\n                static constexpr int absent\
    \ = -1;\n\n                // default constructor\n                Compressor()\
    \ : _xs(std::vector<T>{}) {}\n                // Construct from strictly sorted\
    \ vector\n                Compressor(const std::vector<T> &xs) : _xs(xs) {\n \
    \                   assert(is_strictly_sorted(xs));\n                }\n\n   \
    \             // Return the number of distinct keys.\n                int size()\
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
    \ &&xs) : _xs(std::move(xs)) {}\n        template <typename Gen, constraints_t<is_same_as_invoke_result<T,\
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
    \ Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>\n     \
    \   static auto build(const int n, Gen generator) {\n            return CoordinateCompressorBuilder<T>(n,\
    \ generator).build();\n        }\n    private:\n        std::vector<T> _xs;\n\
    };\n\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/fenwick_tree.hpp\"\
    \n\n\n\n#line 5 \"library/datastructure/fenwick_tree.hpp\"\n#include <map>\n#include\
    \ <unordered_map>\n\n#line 9 \"library/datastructure/fenwick_tree.hpp\"\n\nnamespace\
    \ suisen {\n    namespace internal {\n        template <typename T, typename index_t\
    \ = int, typename Container = std::vector<T>>\n        class FenwickTreeBase {\n\
    \        public:\n            FenwickTreeBase() {}\n            explicit FenwickTreeBase(index_t\
    \ n) : n(n) {}\n\n            int size() const {\n                return n;\n\
    \            }\n            void add(index_t i, T v) {\n                for (++i;\
    \ i <= n; i += (i & -i)) data[i - 1] += v;\n            }\n            T sum(index_t\
    \ l, index_t r) const {\n                return sum(r) - sum(l);\n           \
    \ }\n            auto operator[](int i) {\n                struct {\n        \
    \            int i;\n                    FenwickTreeBase& ft;\n              \
    \      operator T() const { return ft.sum(i, i + 1); }\n                    auto&\
    \ operator++() { return *this += 1; }\n                    auto& operator--()\
    \ { return *this -= 1; }\n                    auto& operator+=(T val) { ft.add(i,\
    \ val); return *this; }\n                    auto& operator-=(T val) { ft.add(i,\
    \ -val); return *this; }\n                    auto& operator*=(T val) { T cur\
    \ = ft.sum(i, i + 1); ft.add(i, cur * val - cur); return *this; }\n          \
    \          auto& operator/=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur /\
    \ val - cur); return *this; }\n                    auto& operator%=(T val) { T\
    \ cur = ft.sum(i, i + 1); ft.add(i, cur % val - cur); return *this; }\n      \
    \              auto& operator =(T val) { T cur = ft.sum(i, i + 1); ft.add(i, val\
    \ - cur); return *this; }\n                } obj{ i, *this };\n              \
    \  return obj;\n            }\n            T operator()(int l, int r) const {\
    \ return sum(l, r); }\n\n            Container& get_internal_container() { return\
    \ data; }\n        protected:\n            index_t n;\n            Container data;\n\
    \            template <typename ...Args>\n            FenwickTreeBase(index_t\
    \ n, Args &&...args) : n(n), data(std::forward<Args>(args)...) {}\n        private:\n\
    \            T sum(int r) const {\n                T s{};\n                for\
    \ (; r; r -= r & -r) s += data[r - 1];\n                return s;\n          \
    \  }\n        };\n\n        template <typename Key, typename Value, bool unordered>\n\
    \        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key,\
    \ Value>, std::map<Key, Value>>;\n\n    } // namespace internal\n\n    template\
    \ <typename T>\n    struct FenwickTree : public internal::FenwickTreeBase<T> {\n\
    \        FenwickTree() : FenwickTree(0) {}\n        explicit FenwickTree(int n)\
    \ : internal::FenwickTreeBase<T>::FenwickTreeBase(n, n, T{}) {}\n        explicit\
    \ FenwickTree(std::vector<T>&& a) : internal::FenwickTreeBase<T>::FenwickTreeBase(a.size(),\
    \ std::move(a)) {\n            for (int i = 1; i <= this->n; ++i) {\n        \
    \        int p = i + (i & -i);\n                if (p <= this->n) this->data[p\
    \ - 1] += this->data[i - 1];\n            }\n        }\n        explicit FenwickTree(const\
    \ std::vector<T>& a) : FenwickTree(std::vector<T>(a)) {}\n    };\n\n    template\
    \ <typename T, typename index_t, bool use_unordered_map = false>\n    using MapFenwickTree\
    \ = internal::FenwickTreeBase<T, index_t, internal::cond_map_t<index_t, T, use_unordered_map>>;\n\
    \n} // namespace suisen\n\n\n#line 8 \"library/geom/segment_intersections.hpp\"\
    \n\nnamespace suisen::geometry {\n\ntemplate <typename T>\nlong long segment_intersections(std::vector<std::pair<T,\
    \ std::pair<T, T>>> vertical, std::vector<std::pair<std::pair<T, T>, T>> horizontal)\
    \ {\n    CoordinateCompressorBuilder<T> bx, by;\n    for (const auto &[x, range_y]\
    \ : vertical) bx.push(x);\n    for (const auto &[range_x, y] : horizontal) by.push(y);\n\
    \    const auto cx = bx.build();\n    const auto cy = by.build();\n    const int\
    \ n = cx.size(), m = cy.size();\n    std::vector<std::vector<std::pair<int, int>>>\
    \ queries(n);\n    for (const auto &[x, range_y] : vertical) {\n        auto [yl,\
    \ yr] = range_y;\n        if (yl > yr) std::swap(yl, yr);\n        queries[cx[x]].emplace_back(cy.min_geq_index(yl),\
    \ cy.min_gt_index(yr));\n    }\n    std::vector<std::vector<int>> in(n + 1), out(n\
    \ + 1);\n    for (const auto &[range_x, y] : horizontal) {\n        auto [xl,\
    \ xr] = range_x;\n        if (xl > xr) std::swap(xl, xr);\n        in[cx.min_geq_index(xl)].push_back(cy[y]);\n\
    \        out[cx.min_gt_index(xr)].push_back(cy[y]);\n    }\n    FenwickTree<int>\
    \ ft(m);\n    long long ans = 0;\n    for (int x = 0; x < n; ++x) {\n        for\
    \ (int y : in[x])  ++ft[y];\n        for (int y : out[x]) --ft[y];\n        for\
    \ (auto [yl, yr] : queries[x]) ans += ft(yl, yr);\n    }\n    return ans;\n}\n\
    \n} // namespace suisen::geometry\n\n\n"
  code: "#ifndef SUISEN_SEGMENT_INTERSECTIONS\n#define SUISEN_SEGMENT_INTERSECTIONS\n\
    \n#include <iostream>\n\n#include \"library/util/coordinate_compressor.hpp\"\n\
    #include \"library/datastructure/fenwick_tree.hpp\"\n\nnamespace suisen::geometry\
    \ {\n\ntemplate <typename T>\nlong long segment_intersections(std::vector<std::pair<T,\
    \ std::pair<T, T>>> vertical, std::vector<std::pair<std::pair<T, T>, T>> horizontal)\
    \ {\n    CoordinateCompressorBuilder<T> bx, by;\n    for (const auto &[x, range_y]\
    \ : vertical) bx.push(x);\n    for (const auto &[range_x, y] : horizontal) by.push(y);\n\
    \    const auto cx = bx.build();\n    const auto cy = by.build();\n    const int\
    \ n = cx.size(), m = cy.size();\n    std::vector<std::vector<std::pair<int, int>>>\
    \ queries(n);\n    for (const auto &[x, range_y] : vertical) {\n        auto [yl,\
    \ yr] = range_y;\n        if (yl > yr) std::swap(yl, yr);\n        queries[cx[x]].emplace_back(cy.min_geq_index(yl),\
    \ cy.min_gt_index(yr));\n    }\n    std::vector<std::vector<int>> in(n + 1), out(n\
    \ + 1);\n    for (const auto &[range_x, y] : horizontal) {\n        auto [xl,\
    \ xr] = range_x;\n        if (xl > xr) std::swap(xl, xr);\n        in[cx.min_geq_index(xl)].push_back(cy[y]);\n\
    \        out[cx.min_gt_index(xr)].push_back(cy[y]);\n    }\n    FenwickTree<int>\
    \ ft(m);\n    long long ans = 0;\n    for (int x = 0; x < n; ++x) {\n        for\
    \ (int y : in[x])  ++ft[y];\n        for (int y : out[x]) --ft[y];\n        for\
    \ (auto [yl, yr] : queries[x]) ans += ft(yl, yr);\n    }\n    return ans;\n}\n\
    \n} // namespace suisen::geometry\n\n#endif // SUISEN_SEGMENT_INTERSECTIONS\n"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/fenwick_tree.hpp
  isVerificationFile: false
  path: library/geom/segment_intersections.hpp
  requiredBy: []
  timestamp: '2022-05-09 18:17:40+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/geom/segment_intersections/CGL_6_A.test.cpp
documentation_of: library/geom/segment_intersections.hpp
layout: document
title: Segment Intersections
---
## Segment Intersections