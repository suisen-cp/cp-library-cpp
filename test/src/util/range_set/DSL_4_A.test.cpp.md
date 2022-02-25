---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/coordinate_compressor.hpp
    title: Coordinate Compressor
  - icon: ':question:'
    path: library/util/range_set.hpp
    title: Range Set
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A
  bundledCode: "#line 1 \"test/src/util/range_set/DSL_4_A.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A\"\n\n#include <iostream>\n\
    #include <tuple>\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    };\n\n} // namespace suisen\n\n\n#line 1 \"library/util/range_set.hpp\"\n\n\n\n\
    #include <map>\n\nnamespace suisen {\n\ntemplate <typename T, bool merge_adjacent_segment\
    \ = true>\nstruct RangeSet : public std::map<T, T> {\n    public:\n        RangeSet()\
    \ : _size(0) {}\n\n        // returns the number of intergers in this set (not\
    \ the number of ranges). O(1)\n        T size() const { return number_of_elements();\
    \ }\n        // returns the number of intergers in this set (not the number of\
    \ ranges). O(1)\n        T number_of_elements() const { return _size; }\n    \
    \    // returns the number of ranges in this set (not the number of integers).\
    \ O(1)\n        int number_of_ranges() const { return std::map<T, T>::size();\
    \ }\n\n        // returns whether the given integer is in this set or not. O(log\
    \ N)\n        bool contains(T x) const {\n            auto it = this->upper_bound(x);\n\
    \            return it != this->begin() and x <= std::prev(it)->second;\n    \
    \    }\n\n        /**\n         * returns the iterator pointing to the range [l,\
    \ r] in this set s.t. l <= x <= r.\n         * if such a range does not exist,\
    \ returns `end()`.\n         * O(log N)\n         */\n        auto find_range(T\
    \ x) const {\n            auto it = this->upper_bound(x);\n            return\
    \ it != this->begin() and x <= (--it)->second ? it : this->end();\n        }\n\
    \n        // returns whether `x` and `y` is in this set and in the same range.\
    \ O(log N)\n        bool in_the_same_range(T x, T y) const {\n            auto\
    \ it = get_containing_range(x);\n            return it != this->end() and it->first\
    \ <= y and y <= it->second;\n        }\n\n        // inserts the range [x, x]\
    \ and returns the number of integers inserted to this set. O(log N)\n        T\
    \ insert(T x) {\n            return insert(x, x);\n        }\n        \n     \
    \   // inserts the range [l, r] and returns the number of integers inserted to\
    \ this set. amortized O(log N)\n        T insert(T l, T r) {\n            if (l\
    \ > r) return 0;\n            auto it = this->upper_bound(l);\n            if\
    \ (it != this->begin() and is_mergeable(std::prev(it)->second, l)) {\n       \
    \         it = std::prev(it);\n                l = std::min(l, it->first);\n \
    \           }\n            T inserted = 0;\n            for (; it != this->end()\
    \ and is_mergeable(r, it->first); it = std::map<T, T>::erase(it)) {\n        \
    \        auto [cl, cr] = *it; \n                r = std::max(r, cr);\n       \
    \         inserted -= cr - cl + 1;\n            }\n            inserted += r -\
    \ l + 1;\n            (*this)[l] = r;\n            _size += inserted;\n      \
    \      return inserted;\n        }\n\n        // erases the range [x, x] and returns\
    \ the number of intergers erased from this set. O(log N)\n        T erase(T x)\
    \ {\n            return erase(x, x);\n        }\n\n        // erases the range\
    \ [l, r] and returns the number of intergers erased from this set. amortized O(log\
    \ N)\n        T erase(T l, T r) {\n            if (l > r) return 0;\n        \
    \    T tl = l, tr = r;\n            auto it = this->upper_bound(l);\n        \
    \    if (it != this->begin() and l <= std::prev(it)->second) {\n             \
    \   it = std::prev(it);\n                tl = it->first;\n            }\n    \
    \        T erased = 0;\n            for (; it != this->end() and it->first <=\
    \ r; it = std::map<T, T>::erase(it)) {\n                auto [cl, cr] = *it;\n\
    \                tr = cr;\n                erased += cr - cl + 1;\n          \
    \  }\n            if (tl < l) {\n                (*this)[tl] = l - 1;\n      \
    \          erased -= l - tl;\n            }\n            if (r < tr) {\n     \
    \           (*this)[r + 1] = tr;\n                erased -= tr - r;\n        \
    \    }\n            _size -= erased;\n            return erased;\n        }\n\n\
    \        // returns minimum integer x s.t. x >= lower and x is NOT in this set\n\
    \        T minimum_excluded(T lower = 0) const {\n            static_assert(merge_adjacent_segment);\n\
    \            auto it = find_range(lower);\n            return it == this->end()\
    \ ? lower : it->second + 1;\n        }\n\n        // returns maximum integer x\
    \ s.t. x <= upper and x is NOT in this set\n        T maximum_excluded(T upper)\
    \ const {\n            static_assert(merge_adjacent_segment);\n            auto\
    \ it = find_range(upper);\n            return it == this->end() ? upper : it->first\
    \ - 1;\n        }\n\n    private:\n        T _size;\n\n        bool is_mergeable(T\
    \ cur_r, T next_l) {\n            return next_l <= cur_r + merge_adjacent_segment;\n\
    \        }\n};\n\n} // namespace suisen\n\n\n#line 8 \"test/src/util/range_set/DSL_4_A.test.cpp\"\
    \nusing suisen::CoordinateCompressorBuilder;\nusing suisen::RangeSet;\n\nconstexpr\
    \ int L = 31;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    CoordinateCompressorBuilder<long long> builder;\n\
    \    std::vector<std::tuple<long long, long long, long long, long long>> rectangles(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int xl, yl, xr, yr;\n        std::cin\
    \ >> xl >> yl >> xr >> yr;\n        rectangles[i] = { xl, yl, xr, yr };\n    \
    \    builder.push(yl);\n        builder.push(yr);\n    }\n    auto comp_y = builder.build();\n\
    \    int m = comp_y.size();\n    std::vector<RangeSet<long long>> sets(m);\n \
    \   for (const auto &[xl, yl, xr, yr] : rectangles) {\n        int cyl = comp_y[yl],\
    \ cyr = comp_y[yr];\n        for (int i = cyl; i < cyr; ++i) {\n            sets[i].insert(xl,\
    \ xr - 1);\n        }\n    }\n    long long ans = 0;\n    for (int i = 0; i <\
    \ m - 1; ++i) {\n        long long hight = comp_y.decomp(i + 1) -comp_y.decomp(i);\n\
    \        ans += hight * sets[i].size();\n    }\n    std::cout << ans << std::endl;\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A\"\n\n\
    #include <iostream>\n#include <tuple>\n\n#include \"library/util/coordinate_compressor.hpp\"\
    \n#include \"library/util/range_set.hpp\"\nusing suisen::CoordinateCompressorBuilder;\n\
    using suisen::RangeSet;\n\nconstexpr int L = 31;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    CoordinateCompressorBuilder<long\
    \ long> builder;\n    std::vector<std::tuple<long long, long long, long long,\
    \ long long>> rectangles(n);\n    for (int i = 0; i < n; ++i) {\n        int xl,\
    \ yl, xr, yr;\n        std::cin >> xl >> yl >> xr >> yr;\n        rectangles[i]\
    \ = { xl, yl, xr, yr };\n        builder.push(yl);\n        builder.push(yr);\n\
    \    }\n    auto comp_y = builder.build();\n    int m = comp_y.size();\n    std::vector<RangeSet<long\
    \ long>> sets(m);\n    for (const auto &[xl, yl, xr, yr] : rectangles) {\n   \
    \     int cyl = comp_y[yl], cyr = comp_y[yr];\n        for (int i = cyl; i < cyr;\
    \ ++i) {\n            sets[i].insert(xl, xr - 1);\n        }\n    }\n    long\
    \ long ans = 0;\n    for (int i = 0; i < m - 1; ++i) {\n        long long hight\
    \ = comp_y.decomp(i + 1) -comp_y.decomp(i);\n        ans += hight * sets[i].size();\n\
    \    }\n    std::cout << ans << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  - library/util/range_set.hpp
  isVerificationFile: true
  path: test/src/util/range_set/DSL_4_A.test.cpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/util/range_set/DSL_4_A.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/range_set/DSL_4_A.test.cpp
- /verify/test/src/util/range_set/DSL_4_A.test.cpp.html
title: test/src/util/range_set/DSL_4_A.test.cpp
---
