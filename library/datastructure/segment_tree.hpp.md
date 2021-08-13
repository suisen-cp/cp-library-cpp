---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: library/util/update_proxy_object.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
    title: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
    title: test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\n#line 1 \"library/util/update_proxy_object.hpp\"\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 5 \"\
    library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>> = nullptr>\n\
    struct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T &v, UpdateFunc\
    \ update) : v(v), update(update) {}\n        operator T() const { return v; }\n\
    \        auto& operator++() && { ++v, update(); return *this; }\n        auto&\
    \ operator--() && { --v, update(); return *this; }\n        auto& operator+=(const\
    \ T &val) && { v += val, update(); return *this; }\n        auto& operator-=(const\
    \ T &val) && { v -= val, update(); return *this; }\n        auto& operator*=(const\
    \ T &val) && { v *= val, update(); return *this; }\n        auto& operator/=(const\
    \ T &val) && { v /= val, update(); return *this; }\n        auto& operator%=(const\
    \ T &val) && { v %= val, update(); return *this; }\n        auto& operator =(const\
    \ T &val) && { v  = val, update(); return *this; }\n        auto& operator<<=(const\
    \ T &val) && { v <<= val, update(); return *this; }\n        auto& operator>>=(const\
    \ T &val) && { v >>= val, update(); return *this; }\n        template <typename\
    \ F, constraints_t<is_uni_op<F, T>> = nullptr>\n        auto& apply(F f) && {\
    \ v = f(v), update(); return *this; }\n    private:\n        T &v;\n        UpdateFunc\
    \ update;\n};\n\n} // namespace suisen\n\n\n#line 8 \"library/datastructure/segment_tree.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, typename F, constraints_t<is_bin_op<F,\
    \ T>> = nullptr>\nclass SegmentTree {\n    public:\n        SegmentTree() : n(0),\
    \ m(0), e(), op() {}\n        SegmentTree(int n, const T &e, const F &op) : n(n),\
    \ m(ceil_pow2(n)), data(m * 2, e), e(e), op(op) {}\n        SegmentTree(const\
    \ std::vector<T> &a, const T &e, const F &op) : SegmentTree(a.size(), e, op) {\n\
    \            build(a);\n        }\n        void build(const std::vector<T> &a)\
    \ {\n            assert(int(a.size()) <= m);\n            std::copy(a.begin(),\
    \ a.end(), data.begin() + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n\
    \        }\n        T get(int i) const {\n            assert(0 <= i and i < n);\n\
    \            return data[i + m];\n        }\n        T operator()(int l, int r)\
    \ const {\n            T res_l = e, res_r = e;\n            for (l += m, r +=\
    \ m; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l,\
    \ data[l++]);\n                if (r & 1) res_r = op(data[--r], res_r);\n    \
    \        }\n            return op(res_l, res_r);\n        }\n        T prefix_prod(int\
    \ r) const {\n            assert(0 <= r and r <= n);\n            return (*this)(0,\
    \ r);\n        }\n        T suffix_prod(int l) const {\n            assert(0 <=\
    \ l and l <= n);\n            return (*this)(l, m);\n        }\n        T all_prod()\
    \ const {\n            return data[1];\n        }\n\n        void set(int i, const\
    \ T &val) {\n            (*this)[i] = val;\n        }\n        auto operator[](int\
    \ i) {\n            assert(0 <= i and i < n);\n            int k = i + m;\n  \
    \          return UpdateProxyObject { data[k], [this, k]{ update_from(k); } };\n\
    \        }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int max_right(int l, const Pred &f) const {\n\
    \            assert(0 <= l and l <= n);\n            assert(f(e));\n         \
    \   if (l == n) return n;\n            l += m;\n            T sum_l = e;\n   \
    \         do {\n                while (l % 2 == 0) l >>= 1;\n                if\
    \ (not f(op(sum_l, data[l]))) {\n                    while (l < m) {\n       \
    \                 l = 2 * l;\n                        if (f(op(sum_l, data[l])))\
    \ sum_l = op(sum_l, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum_l = op(sum_l, data[l]);\n   \
    \             l++;\n            } while ((l & -l) != l);\n            return n;\n\
    \        }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int min_left(int r, const Pred &f) const {\n \
    \           assert(0 <= r && r <= n);\n            assert(f(e));\n           \
    \ if (r == 0) return 0;\n            r += m;\n            T sum_r = e;\n     \
    \       do {\n                r--;\n                while (r > 1 && (r % 2)) r\
    \ >>= 1;\n                if (not f(op(data[r], sum_r))) {\n                 \
    \   while (r < m) {\n                        r = 2 * r + 1;\n                \
    \        if (f(op(data[r], sum_r))) sum_r = op(data[r--], sum_r);\n          \
    \          }\n                    return r + 1 - m;\n                }\n     \
    \           sum_r = op(data[r], sum_r);\n            } while ((r & -r) != r);\n\
    \            return 0;\n        }\n\n    private:\n        const int n, m;\n \
    \       std::vector<T> data;\n        const T e;\n        const F op;\n\n    \
    \    static constexpr int ceil_pow2(int n) {\n            int m = 1;\n       \
    \     while (m < n) m <<= 1;\n            return m;\n        }\n        void update_from(int\
    \ k) {\n            for (k >>= 1; k; k >>= 1) update(k);\n        }\n        void\
    \ update(int k) {\n            data[k] = op(data[k * 2], data[k * 2 + 1]);\n \
    \       }\n};\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SEGMENT_TREE\n#define SUISEN_SEGMENT_TREE\n\n#include <cassert>\n\
    #include <vector>\n\n#include \"library/util/update_proxy_object.hpp\"\n\nnamespace\
    \ suisen {\ntemplate <typename T, typename F, constraints_t<is_bin_op<F, T>> =\
    \ nullptr>\nclass SegmentTree {\n    public:\n        SegmentTree() : n(0), m(0),\
    \ e(), op() {}\n        SegmentTree(int n, const T &e, const F &op) : n(n), m(ceil_pow2(n)),\
    \ data(m * 2, e), e(e), op(op) {}\n        SegmentTree(const std::vector<T> &a,\
    \ const T &e, const F &op) : SegmentTree(a.size(), e, op) {\n            build(a);\n\
    \        }\n        void build(const std::vector<T> &a) {\n            assert(int(a.size())\
    \ <= m);\n            std::copy(a.begin(), a.end(), data.begin() + m);\n     \
    \       for (int k = m - 1; k > 0; --k) update(k);\n        }\n        T get(int\
    \ i) const {\n            assert(0 <= i and i < n);\n            return data[i\
    \ + m];\n        }\n        T operator()(int l, int r) const {\n            T\
    \ res_l = e, res_r = e;\n            for (l += m, r += m; l < r; l >>= 1, r >>=\
    \ 1) {\n                if (l & 1) res_l = op(res_l, data[l++]);\n           \
    \     if (r & 1) res_r = op(data[--r], res_r);\n            }\n            return\
    \ op(res_l, res_r);\n        }\n        T prefix_prod(int r) const {\n       \
    \     assert(0 <= r and r <= n);\n            return (*this)(0, r);\n        }\n\
    \        T suffix_prod(int l) const {\n            assert(0 <= l and l <= n);\n\
    \            return (*this)(l, m);\n        }\n        T all_prod() const {\n\
    \            return data[1];\n        }\n\n        void set(int i, const T &val)\
    \ {\n            (*this)[i] = val;\n        }\n        auto operator[](int i)\
    \ {\n            assert(0 <= i and i < n);\n            int k = i + m;\n     \
    \       return UpdateProxyObject { data[k], [this, k]{ update_from(k); } };\n\
    \        }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int max_right(int l, const Pred &f) const {\n\
    \            assert(0 <= l and l <= n);\n            assert(f(e));\n         \
    \   if (l == n) return n;\n            l += m;\n            T sum_l = e;\n   \
    \         do {\n                while (l % 2 == 0) l >>= 1;\n                if\
    \ (not f(op(sum_l, data[l]))) {\n                    while (l < m) {\n       \
    \                 l = 2 * l;\n                        if (f(op(sum_l, data[l])))\
    \ sum_l = op(sum_l, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum_l = op(sum_l, data[l]);\n   \
    \             l++;\n            } while ((l & -l) != l);\n            return n;\n\
    \        }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int min_left(int r, const Pred &f) const {\n \
    \           assert(0 <= r && r <= n);\n            assert(f(e));\n           \
    \ if (r == 0) return 0;\n            r += m;\n            T sum_r = e;\n     \
    \       do {\n                r--;\n                while (r > 1 && (r % 2)) r\
    \ >>= 1;\n                if (not f(op(data[r], sum_r))) {\n                 \
    \   while (r < m) {\n                        r = 2 * r + 1;\n                \
    \        if (f(op(data[r], sum_r))) sum_r = op(data[r--], sum_r);\n          \
    \          }\n                    return r + 1 - m;\n                }\n     \
    \           sum_r = op(data[r], sum_r);\n            } while ((r & -r) != r);\n\
    \            return 0;\n        }\n\n    private:\n        const int n, m;\n \
    \       std::vector<T> data;\n        const T e;\n        const F op;\n\n    \
    \    static constexpr int ceil_pow2(int n) {\n            int m = 1;\n       \
    \     while (m < n) m <<= 1;\n            return m;\n        }\n        void update_from(int\
    \ k) {\n            for (k >>= 1; k; k >>= 1) update(k);\n        }\n        void\
    \ update(int k) {\n            data[k] = op(data[k * 2], data[k * 2 + 1]);\n \
    \       }\n};\n} // namespace suisen\n\n\n#endif // SUISEN_SEGMENT_TREE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree.hpp
  requiredBy: []
  timestamp: '2021-08-11 01:57:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_A.test.cpp
  - test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  - test/src/datastructure/segment_tree/point_add_range_sum.test.cpp
documentation_of: library/datastructure/segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/segment_tree.hpp
- /library/library/datastructure/segment_tree.hpp.html
title: library/datastructure/segment_tree.hpp
---