---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test_commmutative.cpp
    title: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test_commmutative.cpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/dual_segment_tree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 7 \"\
    library/datastructure/dual_segment_tree.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <\n    typename T, typename F, typename Mapping, typename Composition,\n   \
    \ constraints_t<std::is_same<T, std::invoke_result_t<Mapping, F, T>>, std::is_same<F,\
    \ std::invoke_result_t<Composition, F, F>>> = nullptr\n>\nclass CommutativeDualSegmentTree\
    \ {\n    public:\n        CommutativeDualSegmentTree() {}\n        CommutativeDualSegmentTree(int\
    \ n, const T &fill_value, const F &id, Mapping mapping, Composition composition)\
    \ :\n            n(n), m(ceil_pow2(n)), id(id), mapping(mapping), composition(composition),\
    \ data(n, fill_value), lazy(m, id) {}\n        CommutativeDualSegmentTree(std::vector<T>\
    \ &&a, const F &id, Mapping mapping, Composition composition) :\n            n(a.size()),\
    \ m(ceil_pow2(a.size())), id(id), mapping(mapping), composition(composition),\
    \ data(std::move(a)), lazy(m, id) {}\n        CommutativeDualSegmentTree(const\
    \ std::vector<T> &a, const F &id, Mapping mapping, Composition composition) :\n\
    \            CommutativeDualSegmentTree(std::vector<T>(a), id, mapping, composition)\
    \ {}\n\n        T operator[](int i) const {\n            assert(0 <= i and i <\
    \ n);\n            T res = data[i];\n            for (i = (i + m) >> 1; i; i >>=\
    \ 1) res = mapping(lazy[i], res);\n            return res;\n        }\n      \
    \  T get(int i) const {\n            return (*this)[i];\n        }\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= n);\n\
    \            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n               \
    \ if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r, f);\n     \
    \       }\n        }\n    protected:\n        int n, m;\n        F id;\n     \
    \   Mapping mapping;\n        Composition composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F &f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n};\n\ntemplate <\n    typename T, typename F, typename Mapping,\
    \ typename Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass DualSegmentTree : public CommutativeDualSegmentTree<T, F, Mapping, Composition>\
    \ {\n    using BaseType = CommutativeDualSegmentTree<T, F, Mapping, Composition>;\n\
    \    public:\n        using BaseType::CommutativeDualSegmentTree;\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= this->n);\n\
    \            for (int lk = l + this->m, rk = r + this->m, i = 1; lk >> i; ++i)\
    \ {\n                if (((lk >> i) << i) != lk) push(lk >> i);\n            \
    \    if (((rk >> i) << i) != rk) push((rk - 1) >> i);\n            }\n       \
    \     BaseType::apply(l, r, f);\n        }\n    private:\n        void push(int\
    \ k) {\n            if (this->lazy[k] != this->id) {\n                BaseType::apply(2\
    \ * k, this->lazy[k]), BaseType::apply(2 * k + 1, this->lazy[k]);\n          \
    \      this->lazy[k] = this->id;\n            }\n        }\n};\n\ntemplate <typename\
    \ T, typename F, typename Mapping, typename Composition>\nDualSegmentTree(int,\
    \ T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;\n\
    \ntemplate <typename T, typename F, typename Mapping, typename Composition>\n\
    DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T,\
    \ F, Mapping, Composition>;\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DUAL_SEGTREE\n#define SUISEN_DUAL_SEGTREE\n\n#include <cassert>\n\
    #include <vector>\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace\
    \ suisen {\ntemplate <\n    typename T, typename F, typename Mapping, typename\
    \ Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass CommutativeDualSegmentTree {\n    public:\n        CommutativeDualSegmentTree()\
    \ {}\n        CommutativeDualSegmentTree(int n, const T &fill_value, const F &id,\
    \ Mapping mapping, Composition composition) :\n            n(n), m(ceil_pow2(n)),\
    \ id(id), mapping(mapping), composition(composition), data(n, fill_value), lazy(m,\
    \ id) {}\n        CommutativeDualSegmentTree(std::vector<T> &&a, const F &id,\
    \ Mapping mapping, Composition composition) :\n            n(a.size()), m(ceil_pow2(a.size())),\
    \ id(id), mapping(mapping), composition(composition), data(std::move(a)), lazy(m,\
    \ id) {}\n        CommutativeDualSegmentTree(const std::vector<T> &a, const F\
    \ &id, Mapping mapping, Composition composition) :\n            CommutativeDualSegmentTree(std::vector<T>(a),\
    \ id, mapping, composition) {}\n\n        T operator[](int i) const {\n      \
    \      assert(0 <= i and i < n);\n            T res = data[i];\n            for\
    \ (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);\n            return\
    \ res;\n        }\n        T get(int i) const {\n            return (*this)[i];\n\
    \        }\n        void apply(int l, int r, const F &f) {\n            assert(0\
    \ <= l and r <= n);\n            for (l += m, r += m; l < r; l >>= 1, r >>= 1)\
    \ {\n                if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r,\
    \ f);\n            }\n        }\n    protected:\n        int n, m;\n        F\
    \ id;\n        Mapping mapping;\n        Composition composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F &f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n};\n\ntemplate <\n    typename T, typename F, typename Mapping,\
    \ typename Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass DualSegmentTree : public CommutativeDualSegmentTree<T, F, Mapping, Composition>\
    \ {\n    using BaseType = CommutativeDualSegmentTree<T, F, Mapping, Composition>;\n\
    \    public:\n        using BaseType::CommutativeDualSegmentTree;\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= this->n);\n\
    \            for (int lk = l + this->m, rk = r + this->m, i = 1; lk >> i; ++i)\
    \ {\n                if (((lk >> i) << i) != lk) push(lk >> i);\n            \
    \    if (((rk >> i) << i) != rk) push((rk - 1) >> i);\n            }\n       \
    \     BaseType::apply(l, r, f);\n        }\n    private:\n        void push(int\
    \ k) {\n            if (this->lazy[k] != this->id) {\n                BaseType::apply(2\
    \ * k, this->lazy[k]), BaseType::apply(2 * k + 1, this->lazy[k]);\n          \
    \      this->lazy[k] = this->id;\n            }\n        }\n};\n\ntemplate <typename\
    \ T, typename F, typename Mapping, typename Composition>\nDualSegmentTree(int,\
    \ T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;\n\
    \ntemplate <typename T, typename F, typename Mapping, typename Composition>\n\
    DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T,\
    \ F, Mapping, Composition>;\n\n} // namespace suisen\n\n\n#endif // SUISEN_DUAL_SEGTREE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/dual_segment_tree.hpp
  requiredBy:
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons.test_commmutative.cpp
  timestamp: '2021-07-25 00:33:55+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
documentation_of: library/datastructure/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/dual_segment_tree.hpp
- /library/library/datastructure/dual_segment_tree.hpp.html
title: library/datastructure/dual_segment_tree.hpp
---
