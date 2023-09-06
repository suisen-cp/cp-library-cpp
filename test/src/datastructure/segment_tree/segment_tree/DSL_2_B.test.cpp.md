---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/segment_tree/segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\n#line 1 \"library/util/update_proxy_object.hpp\"\
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
    \ suisen\n\n\n#line 8 \"library/datastructure/segment_tree/segment_tree.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T, T(*op)(T, T), T(*e)()>\nclass SegmentTree\
    \ {\n    public:\n        SegmentTree() : SegmentTree(0) {}\n        explicit\
    \ SegmentTree(int n) : SegmentTree(std::vector<T>(n, e())) {}\n        SegmentTree(const\
    \ std::vector<T> &a) : n(a.size()), m(ceil_pow2(n)), data(2 * m, e()) {\n    \
    \        build(a);\n        }\n\n        void build(const std::vector<T> &a) {\n\
    \            assert(int(a.size()) <= m);\n            std::copy(a.begin(), a.end(),\
    \ data.begin() + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n\
    \        }\n        const T& get(int i) const {\n            assert(0 <= i and\
    \ i < n);\n            return data[i + m];\n        }\n        T operator()(int\
    \ l, int r) const {\n            T res_l = e(), res_r = e();\n            for\
    \ (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l\
    \ = op(res_l, data[l++]);\n                if (r & 1) res_r = op(data[--r], res_r);\n\
    \            }\n            return op(res_l, res_r);\n        }\n        T prod(int\
    \ l, int r) const { return (*this)(l, r); }\n        T prefix_prod(int r) const\
    \ { return (*this)(0, r); }\n        T suffix_prod(int l) const { return (*this)(l,\
    \ m); }\n        T all_prod() const { return data[1]; }\n\n        void set(int\
    \ i, const T &val) {\n            (*this)[i] = val;\n        }\n        auto operator[](int\
    \ i) {\n            assert(0 <= i and i < n);\n            int k = i + m;\n  \
    \          return UpdateProxyObject { data[k], [this, k]{ update_from(k); } };\n\
    \        }\n\n        template <typename Pred, constraints_t<std::is_invocable_r<bool,\
    \ Pred, T>> = nullptr>\n        int max_right(int l, const Pred &f) const {\n\
    \            assert(0 <= l and l <= n);\n            assert(f(e));\n         \
    \   if (l == n) return n;\n            l += m;\n            T sum_l = e;\n   \
    \         do {\n                while (l % 2 == 0) l >>= 1;\n                if\
    \ (not f(op(sum_l, data[l]))) {\n                    while (l < m) {\n       \
    \                 l = 2 * l;\n                        if (f(op(sum_l, data[l])))\
    \ sum_l = op(sum_l, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum_l = op(sum_l, data[l]);\n   \
    \             l++;\n            } while ((l & -l) != l);\n            return n;\n\
    \        }\n        template <bool(*f)(T)>\n        int max_right(int l) { return\
    \ max_right(l, f); }\n\n        template <typename Pred, constraints_t<std::is_invocable_r<bool,\
    \ Pred, T>> = nullptr>\n        int min_left(int r, const Pred &f) const {\n \
    \           assert(0 <= r && r <= n);\n            assert(f(e));\n           \
    \ if (r == 0) return 0;\n            r += m;\n            T sum_r = e;\n     \
    \       do {\n                r--;\n                while (r > 1 && (r % 2)) r\
    \ >>= 1;\n                if (not f(op(data[r], sum_r))) {\n                 \
    \   while (r < m) {\n                        r = 2 * r + 1;\n                \
    \        if (f(op(data[r], sum_r))) sum_r = op(data[r--], sum_r);\n          \
    \          }\n                    return r + 1 - m;\n                }\n     \
    \           sum_r = op(data[r], sum_r);\n            } while ((r & -r) != r);\n\
    \            return 0;\n        }\n        template <bool(*f)(T)>\n        int\
    \ min_left(int l) { return min_left(l, f); }\n\n    private:\n        int n, m;\n\
    \        std::vector<T> data;\n\n        static constexpr int ceil_pow2(int n)\
    \ {\n            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n        void update_from(int k) {\n            for (k >>= 1;\
    \ k; k >>= 1) update(k);\n        }\n        void update(int k) {\n          \
    \  data[k] = op(data[k * 2], data[k * 2 + 1]);\n        }\n};\n} // namespace\
    \ suisen\n\n\n\n#line 6 \"test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp\"\
    \nusing suisen::SegmentTree;\n\nint op(int x, int y) {\n    return x + y;\n}\n\
    int e() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    SegmentTree<int,\
    \ op, e> seg(n);\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int i, x;\n            std::cin >>\
    \ i >> x;\n            seg[i - 1] += x;\n        } else {\n            int s,\
    \ t;\n            std::cin >> s >> t;\n            std::cout << seg(--s, t) <<\
    \ '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree/segment_tree.hpp\"\
    \nusing suisen::SegmentTree;\n\nint op(int x, int y) {\n    return x + y;\n}\n\
    int e() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    SegmentTree<int,\
    \ op, e> seg(n);\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int i, x;\n            std::cin >>\
    \ i >> x;\n            seg[i - 1] += x;\n        } else {\n            int s,\
    \ t;\n            std::cin >> s >> t;\n            std::cout << seg(--s, t) <<\
    \ '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/segment_tree.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
- /verify/test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp.html
title: test/src/datastructure/segment_tree/segment_tree/DSL_2_B.test.cpp
---
