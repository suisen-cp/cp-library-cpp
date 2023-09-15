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
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/util/coordinate_compressor/dummy.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1 \"\
    library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#line 6 \"library/type_traits/type_traits.hpp\"\
    \n#include <type_traits>\n\nnamespace suisen {\n    template <typename ...Constraints>\
    \ using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;\n\
    \n    template <typename T, typename = std::nullptr_t> struct bitnum { static\
    \ constexpr int value = 0; };\n    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>>\
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
    } // namespace suisen\n\n#line 9 \"library/util/coordinate_compressor.hpp\"\n\n\
    namespace suisen {\ntemplate <typename T>\nclass CoordinateCompressorBuilder {\n\
    \    public:\n        struct Compressor {\n            public:\n             \
    \   static constexpr int absent = -1;\n\n                // default constructor\n\
    \                Compressor() : _xs(std::vector<T>{}) {}\n                // Construct\
    \ from strictly sorted vector\n                Compressor(const std::vector<T>\
    \ &xs) : _xs(xs) {\n                    assert(is_strictly_sorted(xs));\n    \
    \            }\n\n                // Return the number of distinct keys.\n   \
    \             int size() const {\n                    return _xs.size();\n   \
    \             }\n                // Check if the element is registered.\n    \
    \            bool has_key(const T &e) const {\n                    return std::binary_search(_xs.begin(),\
    \ _xs.end(), e);\n                }\n                // Compress the element.\
    \ if not registered, returns `default_value`. (default: Compressor::absent)\n\
    \                int comp(const T &e, int default_value = absent) const {\n  \
    \                  const int res = min_geq_index(e);\n                    return\
    \ res != size() and _xs[res] == e ? res : default_value;\n                }\n\
    \                // Restore the element from the index.\n                T decomp(const\
    \ int compressed_index) const {\n                    return _xs[compressed_index];\n\
    \                }\n                // Compress the element. Equivalent to call\
    \ `comp(e)`\n                int operator[](const T &e) const {\n            \
    \        return comp(e);\n                }\n                // Return the minimum\
    \ registered value greater than `e`. if not exists, return `default_value`.\n\
    \                T min_gt(const T &e, const T &default_value) const {\n      \
    \              auto it = std::upper_bound(_xs.begin(), _xs.end(), e);\n      \
    \              return it == _xs.end() ? default_value : *it;\n               \
    \ }\n                // Return the minimum registered value greater than or equal\
    \ to `e`. if not exists, return `default_value`.\n                T min_geq(const\
    \ T &e, const T &default_value) const {\n                    auto it = std::lower_bound(_xs.begin(),\
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
    };\n\n} // namespace suisen\n\n\n#line 6 \"test/src/util/coordinate_compressor/dummy.test.cpp\"\
    \n\ntemplate <typename T>\nstruct NaiveCompressor {\n    static constexpr int\
    \ absent = suisen::CoordinateCompressorBuilder<T>::Compressor::absent;\n\n   \
    \ NaiveCompressor(const std::vector<T>& a) : _sorted(a) {\n        std::sort(_sorted.begin(),\
    \ _sorted.end());\n        _sorted.erase(std::unique(_sorted.begin(), _sorted.end()),\
    \ _sorted.end());\n        // check if strictly increasing\n        assert(std::adjacent_find(_sorted.begin(),\
    \ _sorted.end(), std::greater_equal<T>()) == _sorted.end());\n    }\n\n    //\
    \ Return the minimum registered value greater than `e`. if not exists, return\
    \ `default_value`.\n    T min_gt(const T& e, const T& default_value) const {\n\
    \        auto it = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x)\
    \ { return x > e; });\n        if (it != _sorted.begin()) assert(*std::prev(it)\
    \ <= e);\n        if (it != _sorted.end()) assert(*it > e);\n        return it\
    \ == _sorted.end() ? default_value : *it;\n    }\n    // Return the minimum registered\
    \ value greater than or equal to `e`. if not exists, return `default_value`.\n\
    \    T min_geq(const T& e, const T& default_value) const {\n        auto it =\
    \ std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x >= e;\
    \ });\n        if (it != _sorted.begin()) assert(*std::prev(it) < e);\n      \
    \  if (it != _sorted.end()) assert(*it >= e);\n        return it == _sorted.end()\
    \ ? default_value : *it;\n    }\n    // Return the maximum registered value less\
    \ than `e`. if not exists, return `default_value`\n    T max_lt(const T& e, const\
    \ T& default_value) const {\n        auto it = std::find_if(_sorted.rbegin(),\
    \ _sorted.rend(), [&](const T& x) { return x < e; });\n        if (it != _sorted.rbegin())\
    \ assert(*std::prev(it) >= e);\n        if (it != _sorted.rend()) assert(*it <\
    \ e);\n        return it == _sorted.rend() ? default_value : *it;\n    }\n   \
    \ // Return the maximum registered value less than or equal to `e`. if not exists,\
    \ return `default_value`\n    T max_leq(const T& e, const T& default_value) const\
    \ {\n        auto it = std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const\
    \ T& x) { return x <= e; });\n        if (it != _sorted.rbegin()) assert(*std::prev(it)\
    \ > e);\n        if (it != _sorted.rend()) assert(*it <= e);\n        return it\
    \ == _sorted.rend() ? default_value : *it;\n    }\n    // Return the compressed\
    \ index of the minimum registered value greater than `e`. if not exists, return\
    \ `compressor.size()`.\n    int min_gt_index(const T& e) const {\n        int\
    \ i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x\
    \ > e; }) - _sorted.begin();\n        if (i > 0) assert(_sorted[i - 1] <= e);\n\
    \        if (i < int(_sorted.size())) assert(_sorted[i] > e);\n        else assert(i\
    \ == int(_sorted.size()));\n        return i;\n    }\n    // Return the compressed\
    \ index of the minimum registered value greater than or equal to `e`. if not exists,\
    \ return `compressor.size()`.\n    int min_geq_index(const T& e) const {\n   \
    \     int i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return\
    \ x >= e; }) - _sorted.begin();\n        if (i > 0) assert(_sorted[i - 1] < e);\n\
    \        if (i < int(_sorted.size())) assert(_sorted[i] >= e);\n        else assert(i\
    \ == int(_sorted.size()));\n        return i;\n    }\n    // Return the compressed\
    \ index of the maximum registered value less than `e`. if not exists, return -1.\n\
    \    int max_lt_index(const T& e) const {\n        int i = _sorted.rend() - std::find_if(_sorted.rbegin(),\
    \ _sorted.rend(), [&](const T& x) { return x < e; }) - 1;\n        if (i + 1 <\
    \ int(_sorted.size())) assert(_sorted[i + 1] >= e);\n        if (i >= 0) assert(_sorted[i]\
    \ < e);\n        else assert(i == -1);\n        return i;\n    }\n    // Return\
    \ the compressed index of the maximum registered value less than or equal to `e`.\
    \ if not exists, return -1.\n    int max_leq_index(const T& e) const {\n     \
    \   int i = _sorted.rend() - std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const\
    \ T& x) { return x <= e; }) - 1;\n        if (i + 1 < int(_sorted.size())) assert(_sorted[i\
    \ + 1] > e);\n        if (i >= 0) assert(_sorted[i] <= e);\n        else assert(i\
    \ == -1);\n        return i;\n    }\nprivate:\n    std::vector<T> _sorted;\n};\n\
    \nvoid test(std::vector<int> a, int l, int r, int default_value) {\n    NaiveCompressor<int>\
    \ comp_naive(a);\n    auto comp = suisen::CoordinateCompressorBuilder<int>::build(a);\n\
    \n    for (int i = l; i <= r; ++i) {\n        assert(comp_naive.max_leq(i, default_value)\
    \ == comp.max_leq(i, default_value));\n        assert(comp_naive.max_lt (i, default_value)\
    \ == comp.max_lt (i, default_value));\n        assert(comp_naive.min_geq(i, default_value)\
    \ == comp.min_geq(i, default_value));\n        assert(comp_naive.min_gt (i, default_value)\
    \ == comp.min_gt (i, default_value));\n        assert(comp_naive.max_leq_index(i)\
    \ == comp.max_leq_index(i));\n        assert(comp_naive.max_lt_index (i) == comp.max_lt_index\
    \ (i));\n        assert(comp_naive.min_geq_index(i) == comp.min_geq_index(i));\n\
    \        assert(comp_naive.min_gt_index (i) == comp.min_gt_index (i));\n    }\n\
    }\n\nvoid tests() {\n    test({ 1, 3, 6, 3, 10, 1 }, 0, 11, -1);\n    test({ -5,\
    \ -4, 1, 4, -4, -6, 10, 12, 14, 14 }, -7, 15, 7);\n    test({ }, -10, +10, 0);\n\
    \    test({ 1, 1, 1, 1, 1, 1 }, 0, 2, 0);\n}\n\nint main() {\n    tests();\n \
    \   std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/util/coordinate_compressor.hpp\"\
    \n\ntemplate <typename T>\nstruct NaiveCompressor {\n    static constexpr int\
    \ absent = suisen::CoordinateCompressorBuilder<T>::Compressor::absent;\n\n   \
    \ NaiveCompressor(const std::vector<T>& a) : _sorted(a) {\n        std::sort(_sorted.begin(),\
    \ _sorted.end());\n        _sorted.erase(std::unique(_sorted.begin(), _sorted.end()),\
    \ _sorted.end());\n        // check if strictly increasing\n        assert(std::adjacent_find(_sorted.begin(),\
    \ _sorted.end(), std::greater_equal<T>()) == _sorted.end());\n    }\n\n    //\
    \ Return the minimum registered value greater than `e`. if not exists, return\
    \ `default_value`.\n    T min_gt(const T& e, const T& default_value) const {\n\
    \        auto it = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x)\
    \ { return x > e; });\n        if (it != _sorted.begin()) assert(*std::prev(it)\
    \ <= e);\n        if (it != _sorted.end()) assert(*it > e);\n        return it\
    \ == _sorted.end() ? default_value : *it;\n    }\n    // Return the minimum registered\
    \ value greater than or equal to `e`. if not exists, return `default_value`.\n\
    \    T min_geq(const T& e, const T& default_value) const {\n        auto it =\
    \ std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x >= e;\
    \ });\n        if (it != _sorted.begin()) assert(*std::prev(it) < e);\n      \
    \  if (it != _sorted.end()) assert(*it >= e);\n        return it == _sorted.end()\
    \ ? default_value : *it;\n    }\n    // Return the maximum registered value less\
    \ than `e`. if not exists, return `default_value`\n    T max_lt(const T& e, const\
    \ T& default_value) const {\n        auto it = std::find_if(_sorted.rbegin(),\
    \ _sorted.rend(), [&](const T& x) { return x < e; });\n        if (it != _sorted.rbegin())\
    \ assert(*std::prev(it) >= e);\n        if (it != _sorted.rend()) assert(*it <\
    \ e);\n        return it == _sorted.rend() ? default_value : *it;\n    }\n   \
    \ // Return the maximum registered value less than or equal to `e`. if not exists,\
    \ return `default_value`\n    T max_leq(const T& e, const T& default_value) const\
    \ {\n        auto it = std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const\
    \ T& x) { return x <= e; });\n        if (it != _sorted.rbegin()) assert(*std::prev(it)\
    \ > e);\n        if (it != _sorted.rend()) assert(*it <= e);\n        return it\
    \ == _sorted.rend() ? default_value : *it;\n    }\n    // Return the compressed\
    \ index of the minimum registered value greater than `e`. if not exists, return\
    \ `compressor.size()`.\n    int min_gt_index(const T& e) const {\n        int\
    \ i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return x\
    \ > e; }) - _sorted.begin();\n        if (i > 0) assert(_sorted[i - 1] <= e);\n\
    \        if (i < int(_sorted.size())) assert(_sorted[i] > e);\n        else assert(i\
    \ == int(_sorted.size()));\n        return i;\n    }\n    // Return the compressed\
    \ index of the minimum registered value greater than or equal to `e`. if not exists,\
    \ return `compressor.size()`.\n    int min_geq_index(const T& e) const {\n   \
    \     int i = std::find_if(_sorted.begin(), _sorted.end(), [&](const T& x) { return\
    \ x >= e; }) - _sorted.begin();\n        if (i > 0) assert(_sorted[i - 1] < e);\n\
    \        if (i < int(_sorted.size())) assert(_sorted[i] >= e);\n        else assert(i\
    \ == int(_sorted.size()));\n        return i;\n    }\n    // Return the compressed\
    \ index of the maximum registered value less than `e`. if not exists, return -1.\n\
    \    int max_lt_index(const T& e) const {\n        int i = _sorted.rend() - std::find_if(_sorted.rbegin(),\
    \ _sorted.rend(), [&](const T& x) { return x < e; }) - 1;\n        if (i + 1 <\
    \ int(_sorted.size())) assert(_sorted[i + 1] >= e);\n        if (i >= 0) assert(_sorted[i]\
    \ < e);\n        else assert(i == -1);\n        return i;\n    }\n    // Return\
    \ the compressed index of the maximum registered value less than or equal to `e`.\
    \ if not exists, return -1.\n    int max_leq_index(const T& e) const {\n     \
    \   int i = _sorted.rend() - std::find_if(_sorted.rbegin(), _sorted.rend(), [&](const\
    \ T& x) { return x <= e; }) - 1;\n        if (i + 1 < int(_sorted.size())) assert(_sorted[i\
    \ + 1] > e);\n        if (i >= 0) assert(_sorted[i] <= e);\n        else assert(i\
    \ == -1);\n        return i;\n    }\nprivate:\n    std::vector<T> _sorted;\n};\n\
    \nvoid test(std::vector<int> a, int l, int r, int default_value) {\n    NaiveCompressor<int>\
    \ comp_naive(a);\n    auto comp = suisen::CoordinateCompressorBuilder<int>::build(a);\n\
    \n    for (int i = l; i <= r; ++i) {\n        assert(comp_naive.max_leq(i, default_value)\
    \ == comp.max_leq(i, default_value));\n        assert(comp_naive.max_lt (i, default_value)\
    \ == comp.max_lt (i, default_value));\n        assert(comp_naive.min_geq(i, default_value)\
    \ == comp.min_geq(i, default_value));\n        assert(comp_naive.min_gt (i, default_value)\
    \ == comp.min_gt (i, default_value));\n        assert(comp_naive.max_leq_index(i)\
    \ == comp.max_leq_index(i));\n        assert(comp_naive.max_lt_index (i) == comp.max_lt_index\
    \ (i));\n        assert(comp_naive.min_geq_index(i) == comp.min_geq_index(i));\n\
    \        assert(comp_naive.min_gt_index (i) == comp.min_gt_index (i));\n    }\n\
    }\n\nvoid tests() {\n    test({ 1, 3, 6, 3, 10, 1 }, 0, 11, -1);\n    test({ -5,\
    \ -4, 1, 4, -4, -6, 10, 12, 14, 14 }, -7, 15, 7);\n    test({ }, -10, +10, 0);\n\
    \    test({ 1, 1, 1, 1, 1, 1 }, 0, 2, 0);\n}\n\nint main() {\n    tests();\n \
    \   std::cout << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/util/coordinate_compressor/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/util/coordinate_compressor/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/coordinate_compressor/dummy.test.cpp
- /verify/test/src/util/coordinate_compressor/dummy.test.cpp.html
title: test/src/util/coordinate_compressor/dummy.test.cpp
---
