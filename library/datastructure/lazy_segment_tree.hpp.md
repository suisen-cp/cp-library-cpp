---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':question:'
    path: library/util/update_proxy_object.hpp
    title: library/util/update_proxy_object.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
    title: test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/lazy_segment_tree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
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
    struct UpdateProxyObject {\n    T &v;\n    UpdateFunc update;\n    UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n    operator T() const { return\
    \ v; }\n    auto& operator++() { ++v, update(); return *this; }\n    auto& operator--()\
    \ { --v, update(); return *this; }\n    auto& operator+=(const T &val) { v +=\
    \ val, update(); return *this; }\n    auto& operator-=(const T &val) { v -= val,\
    \ update(); return *this; }\n    auto& operator*=(const T &val) { v *= val, update();\
    \ return *this; }\n    auto& operator/=(const T &val) { v /= val, update(); return\
    \ *this; }\n    auto& operator%=(const T &val) { v %= val, update(); return *this;\
    \ }\n    auto& operator =(const T &val) { v  = val, update(); return *this; }\n\
    \    auto& operator<<=(const T &val) { v <<= val, update(); return *this; }\n\
    \    auto& operator>>=(const T &val) { v >>= val, update(); return *this; }\n\
    };\n\n} // namespace suisen\n\n\n#line 7 \"library/datastructure/lazy_segment_tree.hpp\"\
    \n\nnamespace suisen {\ntemplate <\n    typename T, typename OpTT, typename F,\
    \ typename OpFT, typename OpFF,\n    constraints_t<is_bin_op<OpTT, T>, is_same_as_invoke_result<T,\
    \ OpFT, F, T>, is_bin_op<OpFF, F>> = nullptr\n>\nclass LazySegmentTree {\n   \
    \ public:\n        LazySegmentTree(const std::vector<T> &init, T e, OpTT op, F\
    \ id, OpFT mapping, OpFF composition) : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)),\
    \ e(e), op(op), id(id), mapping(mapping), composition(composition), data(2 * m,\
    \ e), lazy(m, id) {\n            std::copy(init.begin(), init.end(), data.begin()\
    \ + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n        }\n \
    \       LazySegmentTree(int n, T e, OpTT op, F id, OpFT mapping, OpFF composition)\
    \ : LazySegmentTree(std::vector<T>(n, e), e, op, id, mapping, composition) {}\n\
    \n        void apply(int l, int r, const F &f) {\n            assert(0 <= l and\
    \ l <= r and r <= n);\n            push_to(l, r);\n            for (int l2 = l\
    \ + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {\n                if (l2 & 1)\
    \ apply(l2++, f);\n                if (r2 & 1) apply(--r2, f);\n            }\n\
    \            update_from(l, r);\n        }\n        T operator()(int l, int r)\
    \ {\n            assert(0 <= l and l <= r and r <= n);\n            push_to(l,\
    \ r);\n            T res_l = e, res_r = e;\n            for (l += m, r += m; l\
    \ < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l, data[l++]);\n\
    \                if (r & 1) res_r = op(data[--r], res_r);\n            }\n   \
    \         return op(res_l, res_r);\n        }\n        T prod(int l, int r) {\n\
    \            return (*this)(l, r);\n        }\n        T all_prod() {\n      \
    \      return data[1];\n        }\n        auto operator[](int p) {\n        \
    \    assert(0 <= p and p < n);\n            push_to(p);\n            return UpdateProxyObject\
    \ { data[p + m], [this, p]{ update_from(p); } };\n        }\n        T get(int\
    \ p) {\n            return (*this)[p];\n        }\n        void set(int p, T v)\
    \ {\n            (*this)[p] = v;\n        }\n        void apply_point(int p, const\
    \ F &f) {\n            (*this)[p] = mapping(f, get(p));\n        }\n\n       \
    \ template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred,\
    \ T>> = nullptr>\n        int max_right(int l, Pred g) {\n            assert(0\
    \ <= l && l <= n);\n            assert(g(e));\n            if (l == n) return\
    \ n;\n            l += m;\n            for (int i = lg; i >= 1; --i) push(l >>\
    \ i);\n            T sm = e;\n            do {\n                while (l % 2 ==\
    \ 0) l >>= 1;\n                if (not g(op(sm, data[l]))) {\n               \
    \     while (l < m) {\n                        push(l);\n                    \
    \    l = 2 * l;\n                        if (g(op(sm, data[l]))) {\n         \
    \                   sm = op(sm, data[l++]);\n                        }\n     \
    \               }\n                    return l - m;\n                }\n    \
    \            sm = op(sm, data[l++]);\n            } while ((l & -l) != l);\n \
    \           return n;\n        }\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int min_left(int r, Pred g) {\n            assert(0\
    \ <= r && r <= n);\n            assert(g(e));\n            if (r == 0) return\
    \ 0;\n            r += m;\n            for (int i = lg; i >= 1; --i) push(r >>\
    \ i);\n            T sm = e;\n            do {\n                r--;\n       \
    \         while (r > 1 && (r % 2)) r >>= 1;\n                if (not g(op(data[r],\
    \ sm))) {\n                    while (r < m) {\n                        push(r);\n\
    \                        r = 2 * r + 1;\n                        if (g(op(data[r],\
    \ sm))) {\n                            sm = op(data[r--], sm);\n             \
    \           }\n                    }\n                    return r + 1 - m;\n\
    \                }\n                sm = op(data[r], sm);\n            } while\
    \ ((r & -r) != r);\n            return 0;\n        }\n    private:\n        const\
    \ int n, m, lg;\n        const T e;\n        const OpTT op;\n        const F id;\n\
    \        const OpFT mapping;\n        const OpFF composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        static constexpr int ceil_pow2(int\
    \ n) {\n            int m = 1;\n            while (m < n) m <<= 1;\n         \
    \   return m;\n        }\n\n        void apply(int k, const F &f) {\n        \
    \    data[k] = mapping(f, data[k]);\n            if (k < m) lazy[k] = composition(f,\
    \ lazy[k]);\n        }\n\n        void push(int k) {\n            apply(2 * k,\
    \ lazy[k]), apply(2 * k + 1, lazy[k]);\n            lazy[k] = id;\n        }\n\
    \        void push_to(int p) {\n            p += m;\n            for (int i =\
    \ lg; i >= 1; --i) push(p >> i);\n        }\n        void push_to(int l, int r)\
    \ {\n            l += m, r += m;\n            int li = __builtin_ctz(l), ri =\
    \ __builtin_ctz(r);\n            for (int i = lg; i >= li + 1; --i) push(l >>\
    \ i);\n            for (int i = lg; i >= ri + 1; --i) push(r >> i);\n        }\n\
    \        void update(int k) {\n            data[k] = op(data[2 * k], data[2 *\
    \ k + 1]);\n        }\n        void update_from(int p) {\n            p += m;\n\
    \            for (int i = 1; i <= lg; ++i) update(p >> i);\n        }\n      \
    \  void update_from(int l, int r) {\n            l += m, r += m;\n           \
    \ int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n            for (int i =\
    \ li + 1; i <= lg; ++i) update(l >> i);\n            for (int i = ri + 1; i <=\
    \ lg; ++i) update(r >> i);\n        }\n};\n}\n\n\n"
  code: "#ifndef SUISEN_LAZY_SEGMENT_TREE\n#define SUISEN_LAZY_SEGMENT_TREE\n\n#include\
    \ <cassert>\n#include <vector>\n#include \"library/util/update_proxy_object.hpp\"\
    \n\nnamespace suisen {\ntemplate <\n    typename T, typename OpTT, typename F,\
    \ typename OpFT, typename OpFF,\n    constraints_t<is_bin_op<OpTT, T>, is_same_as_invoke_result<T,\
    \ OpFT, F, T>, is_bin_op<OpFF, F>> = nullptr\n>\nclass LazySegmentTree {\n   \
    \ public:\n        LazySegmentTree(const std::vector<T> &init, T e, OpTT op, F\
    \ id, OpFT mapping, OpFF composition) : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)),\
    \ e(e), op(op), id(id), mapping(mapping), composition(composition), data(2 * m,\
    \ e), lazy(m, id) {\n            std::copy(init.begin(), init.end(), data.begin()\
    \ + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n        }\n \
    \       LazySegmentTree(int n, T e, OpTT op, F id, OpFT mapping, OpFF composition)\
    \ : LazySegmentTree(std::vector<T>(n, e), e, op, id, mapping, composition) {}\n\
    \n        void apply(int l, int r, const F &f) {\n            assert(0 <= l and\
    \ l <= r and r <= n);\n            push_to(l, r);\n            for (int l2 = l\
    \ + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {\n                if (l2 & 1)\
    \ apply(l2++, f);\n                if (r2 & 1) apply(--r2, f);\n            }\n\
    \            update_from(l, r);\n        }\n        T operator()(int l, int r)\
    \ {\n            assert(0 <= l and l <= r and r <= n);\n            push_to(l,\
    \ r);\n            T res_l = e, res_r = e;\n            for (l += m, r += m; l\
    \ < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l, data[l++]);\n\
    \                if (r & 1) res_r = op(data[--r], res_r);\n            }\n   \
    \         return op(res_l, res_r);\n        }\n        T prod(int l, int r) {\n\
    \            return (*this)(l, r);\n        }\n        T all_prod() {\n      \
    \      return data[1];\n        }\n        auto operator[](int p) {\n        \
    \    assert(0 <= p and p < n);\n            push_to(p);\n            return UpdateProxyObject\
    \ { data[p + m], [this, p]{ update_from(p); } };\n        }\n        T get(int\
    \ p) {\n            return (*this)[p];\n        }\n        void set(int p, T v)\
    \ {\n            (*this)[p] = v;\n        }\n        void apply_point(int p, const\
    \ F &f) {\n            (*this)[p] = mapping(f, get(p));\n        }\n\n       \
    \ template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred,\
    \ T>> = nullptr>\n        int max_right(int l, Pred g) {\n            assert(0\
    \ <= l && l <= n);\n            assert(g(e));\n            if (l == n) return\
    \ n;\n            l += m;\n            for (int i = lg; i >= 1; --i) push(l >>\
    \ i);\n            T sm = e;\n            do {\n                while (l % 2 ==\
    \ 0) l >>= 1;\n                if (not g(op(sm, data[l]))) {\n               \
    \     while (l < m) {\n                        push(l);\n                    \
    \    l = 2 * l;\n                        if (g(op(sm, data[l]))) {\n         \
    \                   sm = op(sm, data[l++]);\n                        }\n     \
    \               }\n                    return l - m;\n                }\n    \
    \            sm = op(sm, data[l++]);\n            } while ((l & -l) != l);\n \
    \           return n;\n        }\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
    \ Pred, T>> = nullptr>\n        int min_left(int r, Pred g) {\n            assert(0\
    \ <= r && r <= n);\n            assert(g(e));\n            if (r == 0) return\
    \ 0;\n            r += m;\n            for (int i = lg; i >= 1; --i) push(r >>\
    \ i);\n            T sm = e;\n            do {\n                r--;\n       \
    \         while (r > 1 && (r % 2)) r >>= 1;\n                if (not g(op(data[r],\
    \ sm))) {\n                    while (r < m) {\n                        push(r);\n\
    \                        r = 2 * r + 1;\n                        if (g(op(data[r],\
    \ sm))) {\n                            sm = op(data[r--], sm);\n             \
    \           }\n                    }\n                    return r + 1 - m;\n\
    \                }\n                sm = op(data[r], sm);\n            } while\
    \ ((r & -r) != r);\n            return 0;\n        }\n    private:\n        const\
    \ int n, m, lg;\n        const T e;\n        const OpTT op;\n        const F id;\n\
    \        const OpFT mapping;\n        const OpFF composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        static constexpr int ceil_pow2(int\
    \ n) {\n            int m = 1;\n            while (m < n) m <<= 1;\n         \
    \   return m;\n        }\n\n        void apply(int k, const F &f) {\n        \
    \    data[k] = mapping(f, data[k]);\n            if (k < m) lazy[k] = composition(f,\
    \ lazy[k]);\n        }\n\n        void push(int k) {\n            apply(2 * k,\
    \ lazy[k]), apply(2 * k + 1, lazy[k]);\n            lazy[k] = id;\n        }\n\
    \        void push_to(int p) {\n            p += m;\n            for (int i =\
    \ lg; i >= 1; --i) push(p >> i);\n        }\n        void push_to(int l, int r)\
    \ {\n            l += m, r += m;\n            int li = __builtin_ctz(l), ri =\
    \ __builtin_ctz(r);\n            for (int i = lg; i >= li + 1; --i) push(l >>\
    \ i);\n            for (int i = lg; i >= ri + 1; --i) push(r >> i);\n        }\n\
    \        void update(int k) {\n            data[k] = op(data[2 * k], data[2 *\
    \ k + 1]);\n        }\n        void update_from(int p) {\n            p += m;\n\
    \            for (int i = 1; i <= lg; ++i) update(p >> i);\n        }\n      \
    \  void update_from(int l, int r) {\n            l += m, r += m;\n           \
    \ int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n            for (int i =\
    \ li + 1; i <= lg; ++i) update(l >> i);\n            for (int i = ri + 1; i <=\
    \ lg; ++i) update(r >> i);\n        }\n};\n}\n\n#endif // SUISEN_LAZY_SEGMENT_TREE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-08-03 16:31:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/lazy_segment_tree/DSL_2_I.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_H.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_G.test.cpp
  - test/src/datastructure/lazy_segment_tree/DSL_2_F.test.cpp
documentation_of: library/datastructure/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/lazy_segment_tree.hpp
- /library/library/datastructure/lazy_segment_tree.hpp.html
title: library/datastructure/lazy_segment_tree.hpp
---
