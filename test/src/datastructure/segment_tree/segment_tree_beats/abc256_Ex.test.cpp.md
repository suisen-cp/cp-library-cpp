---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':x:'
    path: library/datastructure/segment_tree/segment_tree_beats.hpp
    title: Segment Tree Beats
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':x:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc256/tasks/abc256_Ex
    links:
    - https://atcoder.jp/contests/abc256/tasks/abc256_Ex
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc256/tasks/abc256_Ex\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\n\
    \n\n\n#include <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
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
    } // namespace suisen\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
    namespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<is_same_as_invoke_result<T, F, T>>\
    \ = nullptr>\n        auto& apply(F f) && { v = f(v), update(); return *this;\
    \ }\n    private:\n        T &v;\n        UpdateFunc update;\n};\n\n} // namespace\
    \ suisen\n\n\n#line 7 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)(), bool enable_beats = false>\n\
    \    struct LazySegmentTree {\n        using value_type = T;\n        using operator_type\
    \ = F;\n\n        LazySegmentTree() : LazySegmentTree(0) {}\n        LazySegmentTree(int\
    \ n) : LazySegmentTree(std::vector<value_type>(n, e())) {}\n        LazySegmentTree(const\
    \ std::vector<value_type>& init) : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)),\
    \ data(2 * m, e()), lazy(m, id()) {\n            std::copy(init.begin(), init.end(),\
    \ data.begin() + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n\
    \        }\n\n        void apply(int l, int r, const operator_type& f) {\n   \
    \         assert(0 <= l and l <= r and r <= n);\n            push_to(l, r);\n\
    \            for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {\n\
    \                if (l2 & 1) all_apply(l2++, f);\n                if (r2 & 1)\
    \ all_apply(--r2, f);\n            }\n            update_from(l, r);\n       \
    \ }\n        void apply(int p, const operator_type& f) {\n            (*this)[p]\
    \ = mapping(f, get(p));\n        }\n\n        value_type operator()(int l, int\
    \ r) {\n            assert(0 <= l and l <= r and r <= n);\n            push_to(l,\
    \ r);\n            value_type res_l = e(), res_r = e();\n            for (l +=\
    \ m, r += m; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l,\
    \ data[l++]);\n                if (r & 1) res_r = op(data[--r], res_r);\n    \
    \        }\n            return op(res_l, res_r);\n        }\n\n        value_type\
    \ prod(int l, int r) { return (*this)(l, r); }\n        value_type prefix_prod(int\
    \ r) { return (*this)(0, r); }\n        value_type suffix_prod(int l) { return\
    \ (*this)(l, m); }\n        value_type all_prod() const { return data[1]; }\n\n\
    \        auto operator[](int p) {\n            assert(0 <= p and p < n);\n   \
    \         push_to(p);\n            return UpdateProxyObject{ data[p + m], [this,\
    \ p] { update_from(p); } };\n        }\n        value_type get(int p) { return\
    \ (*this)[p]; }\n        void set(int p, value_type v) { (*this)[p] = v; }\n\n\
    \        template <typename Pred, constraints_t<std::is_invocable_r<bool, Pred,\
    \ value_type>> = nullptr>\n        int max_right(int l, Pred g) {\n          \
    \  assert(0 <= l && l <= n);\n            assert(g(e()));\n            if (l ==\
    \ n) return n;\n            l += m;\n            for (int i = lg; i >= 1; --i)\
    \ push(l >> i);\n            value_type sum = e();\n            do {\n       \
    \         while ((l & 1) == 0) l >>= 1;\n                if (not g(op(sum, data[l])))\
    \ {\n                    while (l < m) {\n                        push(l);\n \
    \                       l = 2 * l;\n                        if (g(op(sum, data[l])))\
    \ sum = op(sum, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum = op(sum, data[l++]);\n     \
    \       } while ((l & -l) != l);\n            return n;\n        }\n        template\
    \ <bool(*f)(value_type)>\n        int max_right(int l) { return max_right(l, f);\
    \ }\n\n        template <typename Pred, constraints_t<std::is_invocable_r<bool,\
    \ Pred, value_type>> = nullptr>\n        int min_left(int r, Pred g) {\n     \
    \       assert(0 <= r && r <= n);\n            assert(g(e()));\n            if\
    \ (r == 0) return 0;\n            r += m;\n            for (int i = lg; i >= 1;\
    \ --i) push(r >> i);\n            value_type sum = e();\n            do {\n  \
    \              r--;\n                while (r > 1 and (r & 1)) r >>= 1;\n    \
    \            if (not g(op(data[r], sum))) {\n                    while (r < m)\
    \ {\n                        push(r);\n                        r = 2 * r + 1;\n\
    \                        if (g(op(data[r], sum))) sum = op(data[r--], sum);\n\
    \                    }\n                    return r + 1 - m;\n              \
    \  }\n                sum = op(data[r], sum);\n            } while ((r & -r) !=\
    \ r);\n            return 0;\n        }\n        template <bool(*f)(value_type)>\n\
    \        int min_left(int l) { return min_left(l, f); }\n    private:\n      \
    \  int n, m, lg;\n        std::vector<value_type> data;\n        std::vector<operator_type>\
    \ lazy;\n\n        static constexpr int ceil_pow2(int n) {\n            int m\
    \ = 1;\n            while (m < n) m <<= 1;\n            return m;\n        }\n\
    \n        void all_apply(int k, const operator_type& f) {\n            data[k]\
    \ = mapping(f, data[k]);\n            if (k < m) {\n                lazy[k] =\
    \ composition(f, lazy[k]);\n                if constexpr (enable_beats) if (data[k].fail)\
    \ push(k), update(k);\n            }\n        }\n        void push(int k) {\n\
    \            all_apply(2 * k, lazy[k]), all_apply(2 * k + 1, lazy[k]);\n     \
    \       lazy[k] = id();\n        }\n        void push_to(int p) {\n          \
    \  p += m;\n            for (int i = lg; i >= 1; --i) push(p >> i);\n        }\n\
    \        void push_to(int l, int r) {\n            l += m, r += m;\n         \
    \   int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n            for (int i\
    \ = lg; i >= li + 1; --i) push(l >> i);\n            for (int i = lg; i >= ri\
    \ + 1; --i) push(r >> i);\n        }\n        void update(int k) {\n         \
    \   data[k] = op(data[2 * k], data[2 * k + 1]);\n        }\n        void update_from(int\
    \ p) {\n            p += m;\n            for (int i = 1; i <= lg; ++i) update(p\
    \ >> i);\n        }\n        void update_from(int l, int r) {\n            l +=\
    \ m, r += m;\n            int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n\
    \            for (int i = li + 1; i <= lg; ++i) update(l >> i);\n            for\
    \ (int i = ri + 1; i <= lg; ++i) update(r >> i);\n        }\n    };\n}\n\n\n#line\
    \ 5 \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n    using SegmentTreeBeats = LazySegmentTree<T,\
    \ op, e, F, mapping, composition, id, /* enable_beats = */ true>;\n} // namespace\
    \ suisen\n\n\n#line 6 \"test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp\"\
    \n\nconstexpr int inf = 200000;\n\nstruct S {\n    long long sum;\n    int len;\n\
    \    bool same;\n    bool fail = false;\n\n    S() : S(0, 0, true) {}\n    S(int\
    \ v, int len = 1) : S((long long) v * len, len, true) {}\n    S(long long sum,\
    \ int len, bool same) : sum(sum), len(len), same(same) {}\n};\n\nS op(S x, S y)\
    \ {\n    if (x.len == 0) return y;\n    if (y.len == 0) return x;\n    return\
    \ S { x.sum + y.sum, x.len + y.len, x.same and y.same and x.sum / x.len == y.sum\
    \ / y.len };\n}\nS e() {\n    return S{};\n}\nS mapping(int f, S x) {\n    if\
    \ (x.len == 0 or f == -1) return x;\n    if (f >= 0) return S { f, x.len };\n\
    \    if (x.same) return S { int((x.sum / x.len) / -f), x.len };\n    x.fail =\
    \ true;\n    return x;\n}\nint composition(int f, int g) {\n    if (f >= 0) return\
    \ f;\n    if (g >= 0) return g / -f;\n    return -((long long) f * g <= inf ?\
    \ f * g : inf);\n}\nint id() {\n    return -1;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    \n\
    \    std::vector<S> init(n);\n    for (int i = 0; i < n; ++i) {\n        int v;\n\
    \        std::cin >> v;\n        init[i] = v; \n    }\n\n    suisen::SegmentTreeBeats<S,\
    \ op, e, int, mapping, composition, id> seg(init);\n\n    while (q --> 0) {\n\
    \        int query_type, l, r;\n        std::cin >> query_type >> l >> r;\n  \
    \      --l;\n        if (query_type == 1) {\n            int x;\n            std::cin\
    \ >> x;\n            seg.apply(l, r, -x);\n        } else if (query_type == 2)\
    \ {\n            int y;\n            std::cin >> y;\n            seg.apply(l,\
    \ r, y);\n        } else if (query_type == 3) {\n            std::cout << seg.prod(l,\
    \ r).sum << '\\n';\n        } else {\n            assert(false);\n        }\n\
    \    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc256/tasks/abc256_Ex\"\n\n\
    #include <iostream>\n\n#include \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\
    \n\nconstexpr int inf = 200000;\n\nstruct S {\n    long long sum;\n    int len;\n\
    \    bool same;\n    bool fail = false;\n\n    S() : S(0, 0, true) {}\n    S(int\
    \ v, int len = 1) : S((long long) v * len, len, true) {}\n    S(long long sum,\
    \ int len, bool same) : sum(sum), len(len), same(same) {}\n};\n\nS op(S x, S y)\
    \ {\n    if (x.len == 0) return y;\n    if (y.len == 0) return x;\n    return\
    \ S { x.sum + y.sum, x.len + y.len, x.same and y.same and x.sum / x.len == y.sum\
    \ / y.len };\n}\nS e() {\n    return S{};\n}\nS mapping(int f, S x) {\n    if\
    \ (x.len == 0 or f == -1) return x;\n    if (f >= 0) return S { f, x.len };\n\
    \    if (x.same) return S { int((x.sum / x.len) / -f), x.len };\n    x.fail =\
    \ true;\n    return x;\n}\nint composition(int f, int g) {\n    if (f >= 0) return\
    \ f;\n    if (g >= 0) return g / -f;\n    return -((long long) f * g <= inf ?\
    \ f * g : inf);\n}\nint id() {\n    return -1;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    \n\
    \    std::vector<S> init(n);\n    for (int i = 0; i < n; ++i) {\n        int v;\n\
    \        std::cin >> v;\n        init[i] = v; \n    }\n\n    suisen::SegmentTreeBeats<S,\
    \ op, e, int, mapping, composition, id> seg(init);\n\n    while (q --> 0) {\n\
    \        int query_type, l, r;\n        std::cin >> query_type >> l >> r;\n  \
    \      --l;\n        if (query_type == 1) {\n            int x;\n            std::cin\
    \ >> x;\n            seg.apply(l, r, -x);\n        } else if (query_type == 2)\
    \ {\n            int y;\n            std::cin >> y;\n            seg.apply(l,\
    \ r, y);\n        } else if (query_type == 3) {\n            std::cout << seg.prod(l,\
    \ r).sum << '\\n';\n        } else {\n            assert(false);\n        }\n\
    \    }\n\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/segment_tree_beats.hpp
  - library/datastructure/segment_tree/lazy_segment_tree.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
- /verify/test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp.html
title: test/src/datastructure/segment_tree/segment_tree_beats/abc256_Ex.test.cpp
---
