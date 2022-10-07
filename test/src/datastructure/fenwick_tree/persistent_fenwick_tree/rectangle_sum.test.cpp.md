---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp
    title: Persistent Fenwick Tree
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/coordinate_compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\
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
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 9 \"library/util/coordinate_compressor.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nclass CoordinateCompressorBuilder\
    \ {\n    public:\n        struct Compressor {\n            public:\n         \
    \       static constexpr int absent = -1;\n\n                // default constructor\n\
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
    };\n\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp\"\
    \n\n\n\n#line 5 \"library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp\"\
    \n\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include <deque>\n#line 6\
    \ \"library/util/object_pool.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ T, bool auto_extend = false>\n    struct ObjectPool {\n        using value_type\
    \ = T;\n        using value_pointer_type = T*;\n\n        template <typename U>\n\
    \        using container_type = std::conditional_t<auto_extend, std::deque<U>,\
    \ std::vector<U>>;\n\n        container_type<value_type> pool;\n        container_type<value_pointer_type>\
    \ stock;\n        decltype(stock.begin()) it;\n\n        ObjectPool() : ObjectPool(0)\
    \ {}\n        ObjectPool(int siz) : pool(siz), stock(siz) {\n            clear();\n\
    \        }\n\n        int capacity() const { return pool.size(); }\n        int\
    \ size() const { return it - stock.begin(); }\n\n        value_pointer_type alloc()\
    \ {\n            if constexpr (auto_extend) ensure();\n            return *it++;\n\
    \        }\n\n        void free(value_pointer_type t) {\n            *--it = t;\n\
    \        }\n\n        void clear() {\n            int siz = pool.size();\n   \
    \         it = stock.begin();\n            for (int i = 0; i < siz; i++) stock[i]\
    \ = &pool[i];\n        }\n\n        void ensure() {\n            if (it != stock.end())\
    \ return;\n            int siz = stock.size();\n            for (int i = siz;\
    \ i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct PersistentFenwickTree\
    \ {\n        struct Node;\n\n        using value_type = T;\n\n        using node_type\
    \ = Node;\n        using node_pointer_type = node_type*;\n\n        struct Node\
    \ {\n            static inline ObjectPool<node_type> _pool;\n\n            node_pointer_type\
    \ _ch[2]{ nullptr, nullptr };\n            value_type _dat;\n\n            Node()\
    \ : _dat{} {}\n\n            static node_pointer_type clone(node_pointer_type\
    \ node) {\n                return &(*_pool.alloc() = *node);\n            }\n\n\
    \            static node_pointer_type build(const std::vector<value_type> &dat,\
    \ int p) {\n                const int n = dat.size();\n                std::vector<node_pointer_type>\
    \ nodes(n + 1);\n                auto rec = [&](auto rec, int p, int id) -> node_pointer_type\
    \ {\n                    if (p == 0) return nullptr;\n                    const\
    \ int np = p >> 1;\n                    node_pointer_type res = _pool.alloc();\n\
    \                    res->_ch[0] = rec(rec, np, id - np);\n                  \
    \  if (id + 1 <= n) res->_ch[1] = rec(rec, np, id + np);\n                   \
    \ if (id <= n) nodes[id] = res;\n                    return res;\n           \
    \     };\n                node_pointer_type res = rec(rec, p, p);\n          \
    \      for (int i = 1; i <= n; ++i) {\n                    int par = i + (i &\
    \ -i);\n                    if (par <= n) nodes[par]->_dat += nodes[i]->_dat;\n\
    \                }\n                return res;\n            }\n\n           \
    \ static value_type sum(node_pointer_type node, int p, int l, int r) {\n     \
    \           return sum(node, p, r) - sum(node, p, l);\n            }\n\n     \
    \       static node_pointer_type add(node_pointer_type node, int p, int i, const\
    \ value_type& val) {\n                ++i;\n                node_pointer_type\
    \ res = clone(node);\n                for (node_pointer_type cur = res;; p >>=\
    \ 1) {\n                    if (i & p) {\n                        if (i ^= p)\
    \ {\n                            cur = cur->_ch[1] = clone(cur->_ch[1]);\n   \
    \                     } else {\n                            cur->_dat += val;\n\
    \                            return res;\n                        }\n        \
    \            } else {\n                        cur->_dat += val;\n           \
    \             cur = cur->_ch[0] = clone(cur->_ch[0]);\n                    }\n\
    \                }\n            }\n        private:\n            static value_type\
    \ sum(node_pointer_type node, int p, int r) {\n                value_type res{};\n\
    \                for (; r; p >>= 1) {\n                    if (r & p) {\n    \
    \                    r ^= p;\n                        res += node->_dat;\n   \
    \                     node = node->_ch[1];\n                    } else {\n   \
    \                     node = node->_ch[0];\n                    }\n          \
    \      }\n                return res;\n            }\n        };\n\n        PersistentFenwickTree()\
    \ : _p(0), _root(nullptr) {}\n        explicit PersistentFenwickTree(int n) :\
    \ PersistentFenwickTree(std::vector<value_type>(n, T{})) {}\n        PersistentFenwickTree(const\
    \ std::vector<value_type>& dat) : _p(floor_pow2(dat.size())), _root(node_type::build(dat,\
    \ _p)) {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type sum(int\
    \ l, int r) {\n            return node_type::sum(_root, _p, l, r);\n        }\n\
    \        PersistentFenwickTree add(int i, const value_type &val) {\n         \
    \   return PersistentFenwickTree(_p, node_type::add(_root, _p, i, val));\n   \
    \     }\n\n    private:\n        int _p;\n        node_pointer_type _root;\n \
    \       PersistentFenwickTree(int p, node_pointer_type root) : _p(p), _root(root)\
    \ {}\n\n        static constexpr int floor_pow2(int n) {\n            int x =\
    \ 31 - __builtin_clz(n);\n            return x < 0 ? 0 : 1 << x;\n        }\n\
    \    };\n}\n\n\n#line 8 \"test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp\"\
    \n\nusing suisen::CoordinateCompressorBuilder;\nusing suisen::PersistentFenwickTree;\n\
    \nusing Tree = PersistentFenwickTree<long long>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::tuple<int,\
    \ int, int>> points(n);\n    CoordinateCompressorBuilder<int> bx, by;\n\n    for\
    \ (auto &[x, y, w] : points) {\n        std::cin >> x >> y >> w;\n        bx.push(x);\n\
    \        by.push(y);\n    }\n    auto cmp_x = bx.build(), cmp_y = by.build();\n\
    \n    const int h = cmp_x.size(), w = cmp_y.size();\n\n    std::vector<std::vector<std::pair<int,\
    \ int>>> buckets(h);\n    for (auto &[x, y, w] : points) {\n        x = cmp_x[x];\n\
    \        y = cmp_y[y];\n        buckets[x].emplace_back(y, w);\n    }\n\n    Tree::init_pool(5000000);\n\
    \n    std::vector<Tree> fts(h + 1);\n    fts[0] = Tree(w);\n\n    for (int x =\
    \ 0; x < h; ++x) {\n        fts[x + 1] = fts[x];\n        for (const auto &[y,\
    \ w] : buckets[x]) {\n            fts[x + 1] = fts[x + 1].add(y, w);\n       \
    \ }\n    }\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n       \
    \ int l, r, d, u;\n        std::cin >> l >> d >> r >> u;\n\n        l = cmp_x.min_geq_index(l);\n\
    \        r = cmp_x.min_geq_index(r);\n        d = cmp_y.min_geq_index(d);\n  \
    \      u = cmp_y.min_geq_index(u);\n\n        std::cout << fts[r].sum(d, u) -\
    \ fts[l].sum(d, u) << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#include \"library/util/coordinate_compressor.hpp\"\
    \n#include \"library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp\"\n\
    \nusing suisen::CoordinateCompressorBuilder;\nusing suisen::PersistentFenwickTree;\n\
    \nusing Tree = PersistentFenwickTree<long long>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::tuple<int,\
    \ int, int>> points(n);\n    CoordinateCompressorBuilder<int> bx, by;\n\n    for\
    \ (auto &[x, y, w] : points) {\n        std::cin >> x >> y >> w;\n        bx.push(x);\n\
    \        by.push(y);\n    }\n    auto cmp_x = bx.build(), cmp_y = by.build();\n\
    \n    const int h = cmp_x.size(), w = cmp_y.size();\n\n    std::vector<std::vector<std::pair<int,\
    \ int>>> buckets(h);\n    for (auto &[x, y, w] : points) {\n        x = cmp_x[x];\n\
    \        y = cmp_y[y];\n        buckets[x].emplace_back(y, w);\n    }\n\n    Tree::init_pool(5000000);\n\
    \n    std::vector<Tree> fts(h + 1);\n    fts[0] = Tree(w);\n\n    for (int x =\
    \ 0; x < h; ++x) {\n        fts[x + 1] = fts[x];\n        for (const auto &[y,\
    \ w] : buckets[x]) {\n            fts[x + 1] = fts[x + 1].add(y, w);\n       \
    \ }\n    }\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n       \
    \ int l, r, d, u;\n        std::cin >> l >> d >> r >> u;\n\n        l = cmp_x.min_geq_index(l);\n\
    \        r = cmp_x.min_geq_index(r);\n        d = cmp_y.min_geq_index(d);\n  \
    \      u = cmp_y.min_geq_index(u);\n\n        std::cout << fts[r].sum(d, u) -\
    \ fts[l].sum(d, u) << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2022-06-14 00:04:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp
- /verify/test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp.html
title: test/src/datastructure/fenwick_tree/persistent_fenwick_tree/rectangle_sum.test.cpp
---
