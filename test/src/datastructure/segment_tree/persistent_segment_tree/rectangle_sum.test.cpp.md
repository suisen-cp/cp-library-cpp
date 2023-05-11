---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/persistent_segment_tree.hpp
    title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp\"\
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
    };\n\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/segment_tree/persistent_segment_tree.hpp\"\
    \n\n\n\n#line 5 \"library/datastructure/segment_tree/persistent_segment_tree.hpp\"\
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
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/segment_tree/persistent_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n   \
    \ struct PersistentSegmentTree {\n        struct Node;\n\n        using value_type\
    \ = T;\n\n        using node_type = Node;\n        using node_pointer_type = node_type*;\n\
    \n        struct Node {\n            static inline ObjectPool<node_type> _pool;\n\
    \n            node_pointer_type _ch[2]{ nullptr, nullptr };\n            value_type\
    \ _dat;\n\n            Node() : _dat(e()) {}\n\n            static node_pointer_type\
    \ clone(node_pointer_type node) {\n                return &(*_pool.alloc() = *node);\n\
    \            }\n\n            static void update(node_pointer_type node) {\n \
    \               node->_dat = op(node->_ch[0]->_dat, node->_ch[1]->_dat);\n   \
    \         }\n\n            static bool is_leaf(node_pointer_type node) {\n   \
    \             return not node->_ch[0];\n            }\n\n            static node_pointer_type\
    \ build(const std::vector<value_type>& dat) {\n                auto rec = [&](auto\
    \ rec, int l, int r) -> node_pointer_type {\n                    node_pointer_type\
    \ res = _pool.alloc();\n                    if (r - l == 1) {\n              \
    \          res->_dat = dat[l];\n                    } else {\n               \
    \         int m = (l + r) >> 1;\n                        res->_ch[0] = rec(rec,\
    \ l, m), res->_ch[1] = rec(rec, m, r);\n                        update(res);\n\
    \                    }\n                    return res;\n                };\n\
    \                return rec(rec, 0, dat.size());\n            }\n\n          \
    \  static value_type prod_all(node_pointer_type node) {\n                return\
    \ node ? node->_dat : e();\n            }\n            static value_type prod(node_pointer_type\
    \ node, int tl, int tr, int ql, int qr) {\n                if (tr <= ql or qr\
    \ <= tl) return e();\n                if (ql <= tl and tr <= qr) return node->_dat;\n\
    \                int tm = (tl + tr) >> 1;\n                return op(prod(node->_ch[0],\
    \ tl, tm, ql, qr), prod(node->_ch[1], tm, tr, ql, qr));\n            }\n\n   \
    \         template <bool do_update, typename F>\n            static auto search_node(node_pointer_type\
    \ node, int siz, int i, F &&f) {\n                static std::vector<node_pointer_type>\
    \ path;\n\n                node_pointer_type res = node;\n                if constexpr\
    \ (do_update) res = clone(res);\n                node_pointer_type cur = res;\n\
    \n                for (int l = 0, r = siz; r - l > 1;) {\n                   \
    \ if constexpr (do_update) path.push_back(cur);\n                    int m = (l\
    \ + r) >> 1;\n                    if (i < m) {\n                        if constexpr\
    \ (do_update) cur->_ch[0] = clone(cur->_ch[0]);\n                        cur =\
    \ cur->_ch[0];\n                        r = m;\n                    } else {\n\
    \                        if constexpr (do_update) cur->_ch[1] = clone(cur->_ch[1]);\n\
    \                        cur = cur->_ch[1];\n                        l = m;\n\
    \                    }\n                }\n                f(cur);\n\n       \
    \         if constexpr (do_update) {\n                    while (path.size())\
    \ update(path.back()), path.pop_back();\n                    return res;\n   \
    \             } else {\n                    return;\n                }\n     \
    \       }\n\n            static value_type get(node_pointer_type node, int siz,\
    \ int i) {\n                value_type res;\n                search_node</* do_update\
    \ = */false>(node, siz, i, [&](node_pointer_type i_th_node) { res = i_th_node->_dat;\
    \ });\n                return res;\n            }\n            template <typename\
    \ F>\n            static node_pointer_type apply(node_pointer_type node, int siz,\
    \ int i, F&& f) {\n                return search_node</* do_update = */true>(node,\
    \ siz, i, [&](node_pointer_type i_th_node) { i_th_node->_dat = f(i_th_node->_dat);\
    \ });\n            }\n            static node_pointer_type set(node_pointer_type\
    \ node, int siz, int i, const value_type& dat) {\n                return apply(node,\
    \ siz, i, [&](const value_type&) { return dat; });\n            }\n\n        \
    \    template <typename F>\n            static int max_right(node_pointer_type\
    \ node, int siz, int l, F&& f) {\n                assert(f(e()));\n          \
    \      auto rec = [&](auto rec, node_pointer_type cur, int tl, int tr, value_type&\
    \ sum) -> int {\n                    if (tr <= l) return tr;\n               \
    \     if (l <= tl) {\n                        value_type nxt_sum = op(sum, cur->_dat);\n\
    \                        if (f(nxt_sum)) {\n                            sum =\
    \ std::move(nxt_sum);\n                            return tr;\n              \
    \          }\n                        if (tr - tl == 1) return tl;\n         \
    \           }\n                    int tm = (tl + tr) >> 1;\n                \
    \    int res_l = rec(rec, cur->_ch[0], tl, tm, sum);\n                    return\
    \ res_l != tm ? res_l : rec(rec, cur->_ch[1], tm, tr, sum);\n                };\n\
    \                value_type sum = e();\n                return rec(rec, node,\
    \ 0, siz, sum);\n            }\n            template <typename F>\n          \
    \  static int min_left(node_pointer_type node, int siz, int r, F&& f) {\n    \
    \            assert(f(e()));\n                auto rec = [&](auto rec, node_pointer_type\
    \ cur, int tl, int tr, value_type& sum) -> int {\n                    if (r <=\
    \ tl) return tl;\n                    if (tr <= r) {\n                       \
    \ value_type nxt_sum = op(cur->_dat, sum);\n                        if (f(nxt_sum))\
    \ {\n                            sum = std::move(nxt_sum);\n                 \
    \           return tl;\n                        }\n                        if\
    \ (tr - tl == 1) return tr;\n                    }\n                    int tm\
    \ = (tl + tr) >> 1;\n                    int res_r = rec(rec, cur->_ch[1], tm,\
    \ tr, sum);\n                    return res_r != tm ? res_r : rec(rec, cur->_ch[0],\
    \ tl, tm, sum);\n                };\n                value_type sum = e();\n \
    \               return rec(rec, node, 0, siz, sum);\n            }\n\n       \
    \     template <typename OutputIterator>\n            static void dump(node_pointer_type\
    \ node, OutputIterator it) {\n                if (not node) return;\n        \
    \        auto rec = [&](auto rec, node_pointer_type cur) -> void {\n         \
    \           if (is_leaf(cur)) {\n                        *it++ = cur->_dat;\n\
    \                    } else {\n                        rec(rec, cur->_ch[0]),\
    \ rec(rec, cur->_ch[1]);\n                    }\n                };\n        \
    \        rec(rec, node);\n            }\n            static std::vector<value_type>\
    \ dump(node_pointer_type node) {\n                std::vector<value_type> res;\n\
    \                dump(node, std::back_inserter(res));\n                return\
    \ res;\n            }\n        };\n\n        PersistentSegmentTree() : _n(0),\
    \ _root(nullptr) {}\n        explicit PersistentSegmentTree(int n) : PersistentSegmentTree(std::vector<value_type>(n,\
    \ e())) {}\n        PersistentSegmentTree(const std::vector<value_type>& dat)\
    \ : _n(dat.size()), _root(node_type::build(dat)) {}\n\n        static void init_pool(int\
    \ siz) {\n            node_type::_pool = ObjectPool<node_type>(siz);\n       \
    \ }\n        static void clear_pool() {\n            node_type::_pool.clear();\n\
    \        }\n\n        value_type prod_all() {\n            return node_type::prod_all(_root);\n\
    \        }\n        value_type prod(int l, int r) {\n            assert(0 <= l\
    \ and l <= r and r <= _n);\n            return node_type::prod(_root, 0, _n, l,\
    \ r);\n        }\n        value_type operator()(int l, int r) {\n            return\
    \ prod(l, r);\n        }\n\n        value_type get(int i) {\n            assert(0\
    \ <= i and i < _n);\n            return node_type::get(_root, _n, i);\n      \
    \  }\n        value_type operator[](int i) {\n            return get(i);\n   \
    \     }\n\n        template <typename F>\n        PersistentSegmentTree apply(int\
    \ i, F&& f) {\n            assert(0 <= i and i < _n);\n            return PersistentSegmentTree(_n,\
    \ node_type::apply(_root, _n, i, std::forward<F>(f)));\n        }\n        PersistentSegmentTree\
    \ set(int i, const value_type& v) {\n            assert(0 <= i and i < _n);\n\
    \            return PersistentSegmentTree(_n, node_type::set(_root, _n, i, v));\n\
    \        }\n\n        template <typename F>\n        int max_right(int l, F&&\
    \ f) {\n            assert(0 <= l and l <= _n);\n            return node_type::max_right(_root,\
    \ _n, l, std::forward<F>(f));\n        }\n        template <bool(*pred)(value_type)>\n\
    \        static int max_right(int l) {\n            return max_right(l, pred);\n\
    \        }\n        template <typename F>\n        int min_left(int r, F&& f)\
    \ {\n            assert(0 <= r and r <= _n);\n            return node_type::min_left(_root,\
    \ _n, r, std::forward<F>(f));\n        }\n        template <bool(*pred)(value_type)>\n\
    \        static int min_left(int r) {\n            return min_left(r, pred);\n\
    \        }\n\n        template <typename OutputIterator>\n        void dump(OutputIterator\
    \ it) {\n            node_type::dump(_root, it);\n        }\n        std::vector<value_type>\
    \ dump() {\n            return node_type::dump(_root);\n        }\n\n    private:\n\
    \        int _n;\n        node_pointer_type _root;\n        PersistentSegmentTree(int\
    \ n, node_pointer_type root) : _n(n), _root(root) {}\n    };\n}\n\n\n#line 8 \"\
    test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp\"\
    \n\nlong long op(long long x, long long y) {\n    return x + y;\n}\nlong long\
    \ e() {\n    return 0;\n}\n\nusing suisen::CoordinateCompressorBuilder;\nusing\
    \ suisen::PersistentSegmentTree;\n\nusing Tree = PersistentSegmentTree<long long,\
    \ op, e>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::tuple<int, int,\
    \ int>> points(n);\n    CoordinateCompressorBuilder<int> bx, by;\n\n    for (auto\
    \ &[x, y, w] : points) {\n        std::cin >> x >> y >> w;\n        bx.push(x);\n\
    \        by.push(y);\n    }\n    auto cmp_x = bx.build(), cmp_y = by.build();\n\
    \n    const int h = cmp_x.size(), w = cmp_y.size();\n\n    std::vector<std::vector<std::pair<int,\
    \ int>>> buckets(h);\n    for (auto &[x, y, w] : points) {\n        x = cmp_x[x];\n\
    \        y = cmp_y[y];\n        buckets[x].emplace_back(y, w);\n    }\n\n    Tree::init_pool(5000000);\n\
    \n    std::vector<Tree> fts(h + 1);\n    fts[0] = Tree(w);\n\n    for (int x =\
    \ 0; x < h; ++x) {\n        fts[x + 1] = fts[x];\n        for (const auto yw :\
    \ buckets[x]) {\n            const int y = yw.first, w = yw.second;\n        \
    \    fts[x + 1] = fts[x + 1].apply(y, [w](long long e) { return e + w; });\n \
    \       }\n    }\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n \
    \       int l, r, d, u;\n        std::cin >> l >> d >> r >> u;\n\n        l =\
    \ cmp_x.min_geq_index(l);\n        r = cmp_x.min_geq_index(r);\n        d = cmp_y.min_geq_index(d);\n\
    \        u = cmp_y.min_geq_index(u);\n\n        std::cout << fts[r].prod(d, u)\
    \ - fts[l].prod(d, u) << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#include \"library/util/coordinate_compressor.hpp\"\
    \n#include \"library/datastructure/segment_tree/persistent_segment_tree.hpp\"\n\
    \nlong long op(long long x, long long y) {\n    return x + y;\n}\nlong long e()\
    \ {\n    return 0;\n}\n\nusing suisen::CoordinateCompressorBuilder;\nusing suisen::PersistentSegmentTree;\n\
    \nusing Tree = PersistentSegmentTree<long long, op, e>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::tuple<int,\
    \ int, int>> points(n);\n    CoordinateCompressorBuilder<int> bx, by;\n\n    for\
    \ (auto &[x, y, w] : points) {\n        std::cin >> x >> y >> w;\n        bx.push(x);\n\
    \        by.push(y);\n    }\n    auto cmp_x = bx.build(), cmp_y = by.build();\n\
    \n    const int h = cmp_x.size(), w = cmp_y.size();\n\n    std::vector<std::vector<std::pair<int,\
    \ int>>> buckets(h);\n    for (auto &[x, y, w] : points) {\n        x = cmp_x[x];\n\
    \        y = cmp_y[y];\n        buckets[x].emplace_back(y, w);\n    }\n\n    Tree::init_pool(5000000);\n\
    \n    std::vector<Tree> fts(h + 1);\n    fts[0] = Tree(w);\n\n    for (int x =\
    \ 0; x < h; ++x) {\n        fts[x + 1] = fts[x];\n        for (const auto yw :\
    \ buckets[x]) {\n            const int y = yw.first, w = yw.second;\n        \
    \    fts[x + 1] = fts[x + 1].apply(y, [w](long long e) { return e + w; });\n \
    \       }\n    }\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n \
    \       int l, r, d, u;\n        std::cin >> l >> d >> r >> u;\n\n        l =\
    \ cmp_x.min_geq_index(l);\n        r = cmp_x.min_geq_index(r);\n        d = cmp_y.min_geq_index(d);\n\
    \        u = cmp_y.min_geq_index(u);\n\n        std::cout << fts[r].prod(d, u)\
    \ - fts[l].prod(d, u) << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/segment_tree/persistent_segment_tree.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp
- /verify/test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp.html
title: test/src/datastructure/segment_tree/persistent_segment_tree/rectangle_sum.test.cpp
---
