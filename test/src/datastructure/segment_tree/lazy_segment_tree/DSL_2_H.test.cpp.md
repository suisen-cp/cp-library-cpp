---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    } // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
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
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 7 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n    struct LazySegmentTree {\n       \
    \ using value_type = T;\n        using operator_type = F;\n\n        LazySegmentTree()\
    \ : LazySegmentTree(0) {}\n        LazySegmentTree(int n) : LazySegmentTree(std::vector<value_type>(n,\
    \ e())) {}\n        LazySegmentTree(const std::vector<value_type>& init) : n(init.size()),\
    \ m(ceil_pow2(n)), lg(__builtin_ctz(m)), data(2 * m, e()), lazy(m, id()) {\n \
    \           std::copy(init.begin(), init.end(), data.begin() + m);\n         \
    \   for (int k = m - 1; k > 0; --k) update(k);\n        }\n\n        void apply(int\
    \ l, int r, const operator_type& f) {\n            assert(0 <= l and l <= r and\
    \ r <= n);\n            push_to(l, r);\n            for (int l2 = l + m, r2 =\
    \ r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {\n                if (l2 & 1) all_apply(l2++,\
    \ f);\n                if (r2 & 1) all_apply(--r2, f);\n            }\n      \
    \      update_from(l, r);\n        }\n        void apply(int p, const operator_type&\
    \ f) {\n            (*this)[p] = mapping(f, get(p));\n        }\n\n        value_type\
    \ operator()(int l, int r) {\n            assert(0 <= l and l <= r and r <= n);\n\
    \            push_to(l, r);\n            value_type res_l = e(), res_r = e();\n\
    \            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n               \
    \ if (l & 1) res_l = op(res_l, data[l++]);\n                if (r & 1) res_r =\
    \ op(data[--r], res_r);\n            }\n            return op(res_l, res_r);\n\
    \        }\n\n        value_type prod(int l, int r) { return (*this)(l, r); }\n\
    \        value_type prefix_prod(int r) { return (*this)(0, r); }\n        value_type\
    \ suffix_prod(int l) { return (*this)(l, m); }\n        value_type all_prod()\
    \ const { return data[1]; }\n\n        auto operator[](int p) {\n            assert(0\
    \ <= p and p < n);\n            push_to(p);\n            return UpdateProxyObject{\
    \ data[p + m], [this, p] { update_from(p); } };\n        }\n        value_type\
    \ get(int p) { return (*this)[p]; }\n        void set(int p, value_type v) { (*this)[p]\
    \ = v; }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, value_type>> = nullptr>\n        int max_right(int l, Pred g) {\n    \
    \        assert(0 <= l && l <= n);\n            assert(g(e()));\n            if\
    \ (l == n) return n;\n            l += m;\n            for (int i = lg; i >= 1;\
    \ --i) push(l >> i);\n            value_type sum = e();\n            do {\n  \
    \              while ((l & 1) == 0) l >>= 1;\n                if (not g(op(sum,\
    \ data[l]))) {\n                    while (l < m) {\n                        push(l);\n\
    \                        l = 2 * l;\n                        if (g(op(sum, data[l])))\
    \ sum = op(sum, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum = op(sum, data[l++]);\n     \
    \       } while ((l & -l) != l);\n            return n;\n        }\n        template\
    \ <bool(*f)(value_type)>\n        int max_right(int l) { return max_right(l, f);\
    \ }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
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
    \ = mapping(f, data[k]);\n            if (k < m) lazy[k] = composition(f, lazy[k]);\n\
    \        }\n        void push(int k) {\n            all_apply(2 * k, lazy[k]),\
    \ all_apply(2 * k + 1, lazy[k]);\n            lazy[k] = id();\n        }\n   \
    \     void push_to(int p) {\n            p += m;\n            for (int i = lg;\
    \ i >= 1; --i) push(p >> i);\n        }\n        void push_to(int l, int r) {\n\
    \            l += m, r += m;\n            int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n\
    \            for (int i = lg; i >= li + 1; --i) push(l >> i);\n            for\
    \ (int i = lg; i >= ri + 1; --i) push(r >> i);\n        }\n        void update(int\
    \ k) {\n            data[k] = op(data[2 * k], data[2 * k + 1]);\n        }\n \
    \       void update_from(int p) {\n            p += m;\n            for (int i\
    \ = 1; i <= lg; ++i) update(p >> i);\n        }\n        void update_from(int\
    \ l, int r) {\n            l += m, r += m;\n            int li = __builtin_ctz(l),\
    \ ri = __builtin_ctz(r);\n            for (int i = li + 1; i <= lg; ++i) update(l\
    \ >> i);\n            for (int i = ri + 1; i <= lg; ++i) update(r >> i);\n   \
    \     }\n    };\n}\n\n\n#line 6 \"test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp\"\
    \nusing suisen::LazySegmentTree;\n\nint op(int x, int y) {\n    return x < y ?\
    \ x : y;\n}\nint e() {\n    return std::numeric_limits<int>::max();\n}\nint mapping(int\
    \ f, int x) {\n    return f + x;\n}\nint composition(int f, int g) {\n    return\
    \ f + g;\n}\nint id() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    LazySegmentTree<int,\
    \ op, e, int, mapping, composition, id> seg(std::vector<int>(n, 0));\n    for\
    \ (int i = 0; i < q; ++i) {\n        int t, l, r;\n        std::cin >> t >> l\
    \ >> r;\n        ++r;\n        if (t == 0) {\n            long long x;\n     \
    \       std::cin >> x;\n            seg.apply(l, r, x);\n        } else {\n  \
    \          std::cout << seg(l, r) << '\\n';\n        }\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\
    \nusing suisen::LazySegmentTree;\n\nint op(int x, int y) {\n    return x < y ?\
    \ x : y;\n}\nint e() {\n    return std::numeric_limits<int>::max();\n}\nint mapping(int\
    \ f, int x) {\n    return f + x;\n}\nint composition(int f, int g) {\n    return\
    \ f + g;\n}\nint id() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    LazySegmentTree<int,\
    \ op, e, int, mapping, composition, id> seg(std::vector<int>(n, 0));\n    for\
    \ (int i = 0; i < q; ++i) {\n        int t, l, r;\n        std::cin >> t >> l\
    \ >> r;\n        ++r;\n        if (t == 0) {\n            long long x;\n     \
    \       std::cin >> x;\n            seg.apply(l, r, x);\n        } else {\n  \
    \          std::cout << seg(l, r) << '\\n';\n        }\n    }\n    return 0;\n\
    }"
  dependsOn:
  - library/datastructure/segment_tree/lazy_segment_tree.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
  requiredBy: []
  timestamp: '2022-05-09 17:42:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
- /verify/test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp.html
title: test/src/datastructure/segment_tree/lazy_segment_tree/DSL_2_H.test.cpp
---
