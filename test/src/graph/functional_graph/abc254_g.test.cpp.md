---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/util/range_set.hpp
    title: Range Set
  - icon: ':question:'
    path: library/graph/functional_graph.hpp
    title: Functional Graph
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
    PROBLEM: https://atcoder.jp/contests/abc254/tasks/abc254_g
    links:
    - https://atcoder.jp/contests/abc254/tasks/abc254_g
  bundledCode: "#line 1 \"test/src/graph/functional_graph/abc254_g.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc254/tasks/abc254_g\"\n\n#include <iostream>\n\
    \n#line 1 \"library/datastructure/util/range_set.hpp\"\n\n\n\n#include <map>\n\
    \nnamespace suisen {\n\ntemplate <typename T, bool merge_adjacent_segment = true>\n\
    struct RangeSet : public std::map<T, T> {\n    public:\n        RangeSet() : _size(0)\
    \ {}\n\n        // returns the number of intergers in this set (not the number\
    \ of ranges). O(1)\n        T size() const { return number_of_elements(); }\n\
    \        // returns the number of intergers in this set (not the number of ranges).\
    \ O(1)\n        T number_of_elements() const { return _size; }\n        // returns\
    \ the number of ranges in this set (not the number of integers). O(1)\n      \
    \  int number_of_ranges() const { return std::map<T, T>::size(); }\n\n       \
    \ // returns whether the given integer is in this set or not. O(log N)\n     \
    \   bool contains(T x) const {\n            auto it = this->upper_bound(x);\n\
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
    \        }\n};\n\n} // namespace suisen\n\n\n#line 1 \"library/graph/functional_graph.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <optional>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ FunctionalGraph {\n        struct Doubling;\n        template <typename T, T(*)(T,\
    \ T), T(*)()>\n        struct DoublingSum;\n        friend struct Doubling;\n\
    \        template <typename T, T(*op)(T, T), T(*e)()>\n        friend struct DoublingSum;\n\
    \n        FunctionalGraph() : FunctionalGraph(0) {}\n        FunctionalGraph(int\
    \ n) : _n(n), _nxt(n) {}\n        FunctionalGraph(const std::vector<int>& nxt)\
    \ : _n(nxt.size()), _nxt(nxt) {}\n\n        const int& operator[](int u) const\
    \ {\n            return _nxt[u];\n        }\n        int& operator[](int u) {\n\
    \            return _nxt[u];\n        }\n\n        struct Doubling {\n       \
    \     friend struct FunctionalGraph;\n\n            int query(int u, long long\
    \ d) const {\n                for (int l = _log; l >= 0; --l) if ((d >> l) & 1)\
    \ u = _nxt[l][u];\n                return u;\n            }\n\n            struct\
    \ BinarySearchResult {\n                int v;\n                long long step;\n\
    \                operator std::pair<int, long long>() const { return std::pair<int,\
    \ long long>{ v, step }; }\n            };\n\n            template <typename Pred>\n\
    \            auto max_step(int u, Pred &&f) const {\n                assert(f(u));\n\
    \                long long step = 0;\n                for (int l = _log; l >=\
    \ 0; --l) if (int nxt_u = _nxt[l][u]; f(nxt_u)) {\n                    u = nxt_u,\
    \ step |= 1LL << l;\n                }\n                return BinarySearchResult{\
    \ u, step };\n            }\n\n            template <typename Pred>\n        \
    \    std::optional<BinarySearchResult> step_until(int u, Pred &&f) const {\n \
    \               if (f(u)) return BinarySearchResult { u, 0 };\n              \
    \  auto [v, step] = max_step(u, [&](int v) { return not f(v); });\n          \
    \      v = _nxt[0][v], ++step;\n                if (not f(v)) return std::nullopt;\n\
    \                return BinarySearchResult{ v, step };\n            }\n\n    \
    \    private:\n            int _n, _log;\n            std::vector<std::vector<int>>\
    \ _nxt;\n\n            Doubling(const std::vector<int>& nxt, long long max_step)\
    \ : _n(nxt.size()), _log(floor_log2(max_step)), _nxt(_log + 1, std::vector<int>(_n))\
    \ {\n                _nxt[0] = nxt;\n                for (int i = 1; i <= _log;\
    \ ++i) for (int j = 0; j < _n; ++j) {\n                    _nxt[i][j] = _nxt[i\
    \ - 1][_nxt[i - 1][j]];\n                }\n            }\n        };\n\n    \
    \    template <typename T, T(*op)(T, T), T(*e)()>\n        struct DoublingSum\
    \ : private Doubling {\n            friend struct FunctionalGraph;\n\n       \
    \     struct Result {\n                int v;\n                T sum;\n      \
    \          operator std::pair<int, T>() const { return std::pair<int, T>{ v, sum\
    \ }; }\n            };\n\n            auto query(int u, long long d) const {\n\
    \                T sum = e();\n                for (int l = _log; l >= 0; --l)\
    \ if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u, _nxt[l][u])]);\n  \
    \              return Result{ u, sum };\n            }\n\n            struct BinarySearchResult\
    \ {\n                int v;\n                T sum;\n                long long\
    \ step;\n                operator std::tuple<int, T, long long>() const { return\
    \ std::tuple<int, T, long long>{ v, sum, step }; }\n            };\n\n       \
    \     template <typename Pred>\n            auto max_step(int u, Pred &&f) const\
    \ {\n                assert(f(e()));\n                long long step = 0;\n  \
    \              T sum = e();\n                for (int l = _log; l >= 0; --l) {\n\
    \                    if (T nxt_sum = op(sum, _dat[l][u]); f(nxt_sum)) {\n    \
    \                    sum = std::move(nxt_sum), u = _nxt[l][u], step |= 1LL <<\
    \ l;\n                    }\n                }\n                return BinarySearchResult{\
    \ u, sum, step };\n            }\n            template <typename Pred>\n     \
    \       std::optional<BinarySearchResult> step_until(int u, Pred &&f) const {\n\
    \                if (f(e())) return BinarySearchResult { u, e(), 0 };\n      \
    \          auto [v, sum, step] = max_step(u, [&](const T& v) { return not f(v);\
    \ });\n                sum = op(sum, _dat[0][v]), v = _nxt[0][v], ++step;\n  \
    \              if (not f(sum)) return std::nullopt;\n                return BinarySearchResult{\
    \ v, sum, step };\n            }\n\n        private:\n            std::vector<std::vector<T>>\
    \ _dat;\n\n            DoublingSum(const std::vector<int>& nxt, long long max_step,\
    \ const std::vector<T>& dat) : Doubling(nxt, max_step), _dat(_log + 1, std::vector<T>(_n,\
    \ e())) {\n                _dat[0] = dat;\n                for (int i = 1; i <=\
    \ _log; ++i) for (int j = 0; j < _n; ++j) {\n                    _dat[i][j] =\
    \ op(_dat[i - 1][j], _dat[i - 1][_nxt[i - 1][j]]);\n                }\n      \
    \      }\n        };\n\n        Doubling doubling(long long max_step) const {\n\
    \            return Doubling(_nxt, max_step);\n        }\n\n        template <typename\
    \ T, T(*op)(T, T), T(*e)()>\n        DoublingSum<T, op, e> doubling(long long\
    \ max_step, const std::vector<T>& dat) const {\n            return DoublingSum<T,\
    \ op, e>(_nxt, max_step, dat);\n        }\n\n        struct InfinitePath {\n \
    \           int head_v;\n            int head_len;\n            int loop_v;\n\
    \            int loop_len;\n            InfinitePath() = default;\n          \
    \  InfinitePath(int head_v, int head_len, int loop_v, int loop_len) : head_v(head_v),\
    \ head_len(head_len), loop_v(loop_v), loop_len(loop_len) {}\n        };\n\n  \
    \      std::vector<InfinitePath> infinite_paths() const {\n            std::vector<InfinitePath>\
    \ res(_n);\n\n            std::vector<int> vis(_n, _n);\n            std::vector<int>\
    \ dep(_n, 0);\n\n            int time = 0;\n            auto dfs = [&](auto dfs,\
    \ int u) -> int {\n                vis[u] = time;\n                int v = _nxt[u];\n\
    \                if (vis[v] == vis[u]) { // found cycle\n                    int\
    \ loop_len = dep[u] - dep[v] + 1;\n                    res[u] = { u, 0, u, loop_len\
    \ };\n                    return loop_len - 1;\n                } else if (vis[v]\
    \ < vis[u]) {\n                    res[u] = { u, res[v].head_len + 1, res[v].loop_v,\
    \ res[v].loop_len };\n                    return 0;\n                } else {\n\
    \                    dep[v] = dep[u] + 1;\n                    int c = dfs(dfs,\
    \ v);\n                    if (c > 0) { // in cycle\n                        res[u]\
    \ = { u, 0, u, res[v].loop_len };\n                        return c - 1;\n   \
    \                 } else { // out of cycle\n                        res[u] = {\
    \ u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };\n                \
    \        return 0;\n                    }\n                }\n            };\n\
    \            for (int i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);\n\
    \            return res;\n        }\n\n        /**\n         * Calculates k'th\
    \ iterate: f(f(f(...f(i)))) for all 0 <= i < N in O(N) time.\n         * Reference:\
    \ https://noshi91.hatenablog.com/entry/2019/09/22/114149\n         */\n      \
    \  std::vector<int> kth_iterate(const long long k) const {\n            assert(k\
    \ >= 0);\n            std::vector<int> res(_n);\n            std::vector<int>\
    \ forest_roots;\n            std::vector<std::vector<int>> forest(_n);\n     \
    \       std::vector<std::vector<std::pair<long long, int>>> qs(_n);\n        \
    \    for (const auto& path : infinite_paths()) {\n                const int v\
    \ = path.head_v;\n                (path.head_len == 0 ? forest_roots : forest[_nxt[v]]).push_back(v);\n\
    \                if (path.head_len >= k) continue;\n                qs[path.loop_v].emplace_back(k\
    \ - path.head_len, v);\n            }\n            std::vector<int> dfs_path(_n);\n\
    \            auto dfs = [&](auto dfs, int u, int d) -> void {\n              \
    \  dfs_path[d] = u;\n                if (d >= k) res[u] = dfs_path[d - k];\n \
    \               for (int v : forest[u]) dfs(dfs, v, d + 1);\n            };\n\
    \            for (int root : forest_roots) dfs(dfs, root, 0);\n            std::vector<int8_t>\
    \ seen(_n, false);\n            for (int root : forest_roots) {\n            \
    \    if (seen[root]) continue;\n                std::vector<int> cycle{ root };\n\
    \                for (int v = _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);\n\
    \                const int len = cycle.size();\n                for (int i = 0;\
    \ i < len; ++i) {\n                    const int s = cycle[i];\n             \
    \       seen[s] = true;\n                    for (const auto& [rem, res_index]\
    \ : qs[s]) {\n                        res[res_index] = cycle[(i + rem) % len];\n\
    \                    }\n                }\n            }\n            return res;\n\
    \        }\n\n    private:\n        int _n;\n        std::vector<int> _nxt;\n\n\
    \        static int floor_log2(long long v) {\n            int l = 0;\n      \
    \      while (1LL << (l + 1) <= v) ++l;\n            return l;\n        }\n  \
    \  };\n} // namespace suisen\n\n\n\n#line 1 \"library/util/coordinate_compressor.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"library/util/coordinate_compressor.hpp\"\
    \n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\nnamespace suisen {\n    template <typename ...Constraints>\
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
    };\n\n} // namespace suisen\n\n\n#line 8 \"test/src/graph/functional_graph/abc254_g.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m, q;\n    std::cin >> n >> m >> q;\n\n    std::vector<suisen::RangeSet<int,\
    \ false>> range_sets(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b,\
    \ c;\n        std::cin >> a >> b >> c;\n        --a, --b, --c;\n        range_sets[a].insert(b,\
    \ c);\n    }\n\n    suisen::CoordinateCompressorBuilder<int> comp_builder;\n \
    \   std::vector<std::tuple<int, int, int, int>> queries(q);\n    for (auto& [x,\
    \ y, z, w] : queries) {\n        std::cin >> x >> y >> z >> w;\n        --x, --y,\
    \ --z, --w;\n        if (y > w) std::swap(x, z), std::swap(y, w);\n        comp_builder.push(y);\n\
    \    }\n\n    std::vector<std::pair<int, int>> ranges;\n    for (const auto& st\
    \ : range_sets) for (const auto& [l, r] : st) {\n        ranges.emplace_back(l,\
    \ r);\n        comp_builder.push(r);\n    }\n    std::sort(ranges.begin(), ranges.end());\n\
    \    const int range_num = ranges.size();\n\n    const auto comp = comp_builder.build();\n\
    \    const int k = comp.size();\n\n    suisen::FunctionalGraph g(k);\n    {\n\
    \        int i = 0, max_r = -1;\n        for (int j = 0; j < k; ++j) {\n     \
    \       const int pos = comp.decomp(j);\n            while (i < range_num and\
    \ ranges[i].first <= pos) max_r = std::max(max_r, ranges[i++].second);\n     \
    \       g[j] = max_r < pos ? j : comp[max_r];\n        }\n    }\n    const auto\
    \ doubling = g.doubling(range_num);\n\n    for (auto& [x, y, z, w] : queries)\
    \ {\n        const int ans = w - y;\n        if (const auto itx = range_sets[x].find_range(y);\
    \ itx != range_sets[x].end()) y = itx->second;\n        if (const auto itz = range_sets[z].find_range(w);\
    \ itz != range_sets[z].end()) w = itz->first;\n        if (y >= w) {\n       \
    \     std::cout << ans + (x != z) << '\\n';\n        } else {\n            const\
    \ int w_ = w;\n            const auto opt_res = doubling.step_until(comp[y], [&](int\
    \ v) { return comp.decomp(v) >= w_; });\n            std::cout << (opt_res.has_value()\
    \ ? ans + opt_res->step + 1 : -1) << '\\n';\n        }\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc254/tasks/abc254_g\"\n\n\
    #include <iostream>\n\n#include \"library/datastructure/util/range_set.hpp\"\n\
    #include \"library/graph/functional_graph.hpp\"\n#include \"library/util/coordinate_compressor.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m, q;\n    std::cin >> n >> m >> q;\n\n    std::vector<suisen::RangeSet<int,\
    \ false>> range_sets(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b,\
    \ c;\n        std::cin >> a >> b >> c;\n        --a, --b, --c;\n        range_sets[a].insert(b,\
    \ c);\n    }\n\n    suisen::CoordinateCompressorBuilder<int> comp_builder;\n \
    \   std::vector<std::tuple<int, int, int, int>> queries(q);\n    for (auto& [x,\
    \ y, z, w] : queries) {\n        std::cin >> x >> y >> z >> w;\n        --x, --y,\
    \ --z, --w;\n        if (y > w) std::swap(x, z), std::swap(y, w);\n        comp_builder.push(y);\n\
    \    }\n\n    std::vector<std::pair<int, int>> ranges;\n    for (const auto& st\
    \ : range_sets) for (const auto& [l, r] : st) {\n        ranges.emplace_back(l,\
    \ r);\n        comp_builder.push(r);\n    }\n    std::sort(ranges.begin(), ranges.end());\n\
    \    const int range_num = ranges.size();\n\n    const auto comp = comp_builder.build();\n\
    \    const int k = comp.size();\n\n    suisen::FunctionalGraph g(k);\n    {\n\
    \        int i = 0, max_r = -1;\n        for (int j = 0; j < k; ++j) {\n     \
    \       const int pos = comp.decomp(j);\n            while (i < range_num and\
    \ ranges[i].first <= pos) max_r = std::max(max_r, ranges[i++].second);\n     \
    \       g[j] = max_r < pos ? j : comp[max_r];\n        }\n    }\n    const auto\
    \ doubling = g.doubling(range_num);\n\n    for (auto& [x, y, z, w] : queries)\
    \ {\n        const int ans = w - y;\n        if (const auto itx = range_sets[x].find_range(y);\
    \ itx != range_sets[x].end()) y = itx->second;\n        if (const auto itz = range_sets[z].find_range(w);\
    \ itz != range_sets[z].end()) w = itz->first;\n        if (y >= w) {\n       \
    \     std::cout << ans + (x != z) << '\\n';\n        } else {\n            const\
    \ int w_ = w;\n            const auto opt_res = doubling.step_until(comp[y], [&](int\
    \ v) { return comp.decomp(v) >= w_; });\n            std::cout << (opt_res.has_value()\
    \ ? ans + opt_res->step + 1 : -1) << '\\n';\n        }\n    }\n    return 0;\n\
    }"
  dependsOn:
  - library/datastructure/util/range_set.hpp
  - library/graph/functional_graph.hpp
  - library/util/coordinate_compressor.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/graph/functional_graph/abc254_g.test.cpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/graph/functional_graph/abc254_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/functional_graph/abc254_g.test.cpp
- /verify/test/src/graph/functional_graph/abc254_g.test.cpp.html
title: test/src/graph/functional_graph/abc254_g.test.cpp
---
