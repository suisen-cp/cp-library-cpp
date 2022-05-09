---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/coordinate_compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/static_rectangle_add_rectangle_sum.hpp\"\
    \n\n\n\n#include <atcoder/lazysegtree>\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1\
    \ \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include <type_traits>\n\
    \nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
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
    };\n\n} // namespace suisen\n\n\n#line 7 \"library/datastructure/static_rectangle_add_rectangle_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct AddQuery {\n   \
    \     int l, r, d, u;\n        T val;\n    };\n    struct SumQuery {\n       \
    \ int l, r, d, u;\n    };\n\n    namespace internal::static_rectangle_add_rectangle_sum\
    \ {\n        template <typename T>\n        struct LinearFunction { T a, b; };\n\
    \n        template <typename T>\n        struct Data {\n            LinearFunction<T>\
    \ f;\n            int len;\n        };\n        template <typename T>\n      \
    \  Data<T> op(Data<T> x, Data<T> y) {\n            return Data<T>{ LinearFunction<T>\
    \ { x.f.a + y.f.a, x.f.b + y.f.b }, x.len + y.len };\n        }\n        template\
    \ <typename T>\n        Data<T> e() {\n            return Data<T>{ LinearFunction<T>\
    \ { T{ 0 }, T{ 0 } }, 0 };\n        }\n        template <typename T>\n       \
    \ Data<T> mapping(LinearFunction<T> f, Data<T> x) {\n            return Data<T>{\
    \ LinearFunction<T> { x.f.a + x.len * f.a, x.f.b + x.len * f.b }, x.len };\n \
    \       }\n        template <typename T>\n        LinearFunction<T> composition(LinearFunction<T>\
    \ f, LinearFunction<T> g) {\n            return LinearFunction<T>{ f.a + g.a,\
    \ f.b + g.b };\n        }\n        template <typename T>\n        LinearFunction<T>\
    \ id() {\n            return LinearFunction<T>{ T{ 0 }, T{ 0 } };\n        };\n\
    \    }\n\n    template <typename T>\n    std::vector<T> static_rectangle_add_rectangle_sum(std::vector<AddQuery<T>>\
    \ add_queries, std::vector<SumQuery> sum_queries) {\n        using namespace internal::static_rectangle_add_rectangle_sum;\n\
    \n        const int add_query_num = add_queries.size(), sum_query_num = sum_queries.size();\n\
    \n        CoordinateCompressorBuilder<int> bx, by;\n        for (const auto& add_query\
    \ : add_queries) {\n            bx.push(add_query.l), bx.push(add_query.r);\n\
    \            by.push(add_query.d), by.push(add_query.u);\n        }\n        for\
    \ (const auto& sum_query : sum_queries) {\n            bx.push(sum_query.l), bx.push(sum_query.r);\n\
    \            by.push(sum_query.d), by.push(sum_query.u);\n        }\n        const\
    \ auto cmp_x = bx.build(), cmp_y = by.build();\n\n        const int siz_x = cmp_x.size(),\
    \ siz_y = cmp_y.size();\n\n        std::vector<std::vector<std::tuple<int, int,\
    \ LinearFunction<T>>>> add_query_bucket(siz_x);\n        std::vector<std::vector<std::tuple<int,\
    \ int, bool, int>>> sum_query_bucket(siz_x);\n        for (int i = 0; i < add_query_num;\
    \ ++i) {\n            auto& add_query = add_queries[i];\n            add_query.l\
    \ = cmp_x[add_query.l], add_query.r = cmp_x[add_query.r];\n            add_query.d\
    \ = cmp_y[add_query.d], add_query.u = cmp_y[add_query.u];\n            add_query_bucket[add_query.l].emplace_back(\n\
    \                add_query.d, add_query.u,\n                LinearFunction<T>{\
    \ add_query.val, add_query.val * -cmp_x.decomp(add_query.l) }\n            );\n\
    \            add_query_bucket[add_query.r].emplace_back(\n                add_query.d,\
    \ add_query.u,\n                LinearFunction<T>{ -add_query.val, add_query.val\
    \ * cmp_x.decomp(add_query.r) }\n            );\n        }\n        for (int i\
    \ = 0; i < sum_query_num; ++i) {\n            auto& sum_query = sum_queries[i];\n\
    \            sum_query.l = cmp_x[sum_query.l], sum_query.r = cmp_x[sum_query.r];\n\
    \            sum_query.d = cmp_y[sum_query.d], sum_query.u = cmp_y[sum_query.u];\n\
    \            sum_query_bucket[sum_query.l].emplace_back(sum_query.d, sum_query.u,\
    \ /* is_add = */false, i);\n            sum_query_bucket[sum_query.r].emplace_back(sum_query.d,\
    \ sum_query.u, /* is_add = */true, i);\n        }\n\n        std::vector<Data<T>>\
    \ init(siz_y - 1, Data<T>{ id<T>(), 0 });\n        for (int i = 0; i < siz_y -\
    \ 1; ++i) init[i].len = cmp_y.decomp(i + 1) - cmp_y.decomp(i);\n\n        atcoder::lazy_segtree<Data<T>,\
    \ op<T>, e<T>, LinearFunction<T>, mapping<T>, composition<T>, id<T>> seg(init);\n\
    \n        std::vector<T> res(sum_query_num, T{ 0 });\n        for (int i = 0;\
    \ i < siz_x; ++i) {\n            for (const auto& [l, r, is_add, id] : sum_query_bucket[i])\
    \ {\n                Data<T> dat = seg.prod(l, r);\n                T val = dat.f.a\
    \ * cmp_x.decomp(i) + dat.f.b;\n                if (is_add) {\n              \
    \      res[id] += val;\n                } else {\n                    res[id]\
    \ -= val;\n                }\n            }\n            for (const auto& [l,\
    \ r, f] : add_query_bucket[i]) {\n                seg.apply(l, r, f);\n      \
    \      }\n        }\n\n        return res;\n    }\n} // namespace suisen\n\n\n\
    \n"
  code: "#ifndef SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM\n#define SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM\n\
    \n#include <atcoder/lazysegtree>\n\n#include \"library/util/coordinate_compressor.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct AddQuery {\n   \
    \     int l, r, d, u;\n        T val;\n    };\n    struct SumQuery {\n       \
    \ int l, r, d, u;\n    };\n\n    namespace internal::static_rectangle_add_rectangle_sum\
    \ {\n        template <typename T>\n        struct LinearFunction { T a, b; };\n\
    \n        template <typename T>\n        struct Data {\n            LinearFunction<T>\
    \ f;\n            int len;\n        };\n        template <typename T>\n      \
    \  Data<T> op(Data<T> x, Data<T> y) {\n            return Data<T>{ LinearFunction<T>\
    \ { x.f.a + y.f.a, x.f.b + y.f.b }, x.len + y.len };\n        }\n        template\
    \ <typename T>\n        Data<T> e() {\n            return Data<T>{ LinearFunction<T>\
    \ { T{ 0 }, T{ 0 } }, 0 };\n        }\n        template <typename T>\n       \
    \ Data<T> mapping(LinearFunction<T> f, Data<T> x) {\n            return Data<T>{\
    \ LinearFunction<T> { x.f.a + x.len * f.a, x.f.b + x.len * f.b }, x.len };\n \
    \       }\n        template <typename T>\n        LinearFunction<T> composition(LinearFunction<T>\
    \ f, LinearFunction<T> g) {\n            return LinearFunction<T>{ f.a + g.a,\
    \ f.b + g.b };\n        }\n        template <typename T>\n        LinearFunction<T>\
    \ id() {\n            return LinearFunction<T>{ T{ 0 }, T{ 0 } };\n        };\n\
    \    }\n\n    template <typename T>\n    std::vector<T> static_rectangle_add_rectangle_sum(std::vector<AddQuery<T>>\
    \ add_queries, std::vector<SumQuery> sum_queries) {\n        using namespace internal::static_rectangle_add_rectangle_sum;\n\
    \n        const int add_query_num = add_queries.size(), sum_query_num = sum_queries.size();\n\
    \n        CoordinateCompressorBuilder<int> bx, by;\n        for (const auto& add_query\
    \ : add_queries) {\n            bx.push(add_query.l), bx.push(add_query.r);\n\
    \            by.push(add_query.d), by.push(add_query.u);\n        }\n        for\
    \ (const auto& sum_query : sum_queries) {\n            bx.push(sum_query.l), bx.push(sum_query.r);\n\
    \            by.push(sum_query.d), by.push(sum_query.u);\n        }\n        const\
    \ auto cmp_x = bx.build(), cmp_y = by.build();\n\n        const int siz_x = cmp_x.size(),\
    \ siz_y = cmp_y.size();\n\n        std::vector<std::vector<std::tuple<int, int,\
    \ LinearFunction<T>>>> add_query_bucket(siz_x);\n        std::vector<std::vector<std::tuple<int,\
    \ int, bool, int>>> sum_query_bucket(siz_x);\n        for (int i = 0; i < add_query_num;\
    \ ++i) {\n            auto& add_query = add_queries[i];\n            add_query.l\
    \ = cmp_x[add_query.l], add_query.r = cmp_x[add_query.r];\n            add_query.d\
    \ = cmp_y[add_query.d], add_query.u = cmp_y[add_query.u];\n            add_query_bucket[add_query.l].emplace_back(\n\
    \                add_query.d, add_query.u,\n                LinearFunction<T>{\
    \ add_query.val, add_query.val * -cmp_x.decomp(add_query.l) }\n            );\n\
    \            add_query_bucket[add_query.r].emplace_back(\n                add_query.d,\
    \ add_query.u,\n                LinearFunction<T>{ -add_query.val, add_query.val\
    \ * cmp_x.decomp(add_query.r) }\n            );\n        }\n        for (int i\
    \ = 0; i < sum_query_num; ++i) {\n            auto& sum_query = sum_queries[i];\n\
    \            sum_query.l = cmp_x[sum_query.l], sum_query.r = cmp_x[sum_query.r];\n\
    \            sum_query.d = cmp_y[sum_query.d], sum_query.u = cmp_y[sum_query.u];\n\
    \            sum_query_bucket[sum_query.l].emplace_back(sum_query.d, sum_query.u,\
    \ /* is_add = */false, i);\n            sum_query_bucket[sum_query.r].emplace_back(sum_query.d,\
    \ sum_query.u, /* is_add = */true, i);\n        }\n\n        std::vector<Data<T>>\
    \ init(siz_y - 1, Data<T>{ id<T>(), 0 });\n        for (int i = 0; i < siz_y -\
    \ 1; ++i) init[i].len = cmp_y.decomp(i + 1) - cmp_y.decomp(i);\n\n        atcoder::lazy_segtree<Data<T>,\
    \ op<T>, e<T>, LinearFunction<T>, mapping<T>, composition<T>, id<T>> seg(init);\n\
    \n        std::vector<T> res(sum_query_num, T{ 0 });\n        for (int i = 0;\
    \ i < siz_x; ++i) {\n            for (const auto& [l, r, is_add, id] : sum_query_bucket[i])\
    \ {\n                Data<T> dat = seg.prod(l, r);\n                T val = dat.f.a\
    \ * cmp_x.decomp(i) + dat.f.b;\n                if (is_add) {\n              \
    \      res[id] += val;\n                } else {\n                    res[id]\
    \ -= val;\n                }\n            }\n            for (const auto& [l,\
    \ r, f] : add_query_bucket[i]) {\n                seg.apply(l, r, f);\n      \
    \      }\n        }\n\n        return res;\n    }\n} // namespace suisen\n\n\n\
    #endif // SUISEN_STATIC_RECTANGLE_ADD_RECTANGLE_SUM\n"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/static_rectangle_add_rectangle_sum.hpp
  requiredBy: []
  timestamp: '2022-05-09 17:42:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/static_rectangle_add_rectangle_sum.hpp
layout: document
redirect_from:
- /library/library/datastructure/static_rectangle_add_rectangle_sum.hpp
- /library/library/datastructure/static_rectangle_add_rectangle_sum.hpp.html
title: library/datastructure/static_rectangle_add_rectangle_sum.hpp
---
