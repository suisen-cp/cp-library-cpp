---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree.hpp
    title: library/datastructure/segment_tree.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/DSL_2_B.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/segment_tree.hpp\"\n\
    \n\n\n#include <cassert>\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 8 \"\
    library/datastructure/segment_tree.hpp\"\n\nnamespace suisen {\ntemplate <typename\
    \ T, typename F, constraints_t<is_bin_op<F, T>> = nullptr>\nclass SegmentTree\
    \ {\n    public:\n        SegmentTree() : n(0), m(0), e(), op() {}\n        SegmentTree(int\
    \ n, const T &e, const F &op) : n(n), m(ceil_pow2(n)), data(m * 2, e), e(e), op(op)\
    \ {}\n        SegmentTree(const std::vector<T> &a, const T &e, const F &op) :\
    \ SegmentTree(a.size(), e, op) {\n            build(a);\n        }\n        void\
    \ build(const std::vector<T> &a) {\n            assert(int(a.size()) <= m);\n\
    \            std::copy(a.begin(), a.end(), data.begin() + m);\n            for\
    \ (int k = m - 1; k > 0; --k) update(k);\n        }\n        inline T get(int\
    \ i) const {\n            assert(0 <= i and i < n);\n            return data[i\
    \ + m];\n        }\n        T operator()(int l, int r) const {\n            T\
    \ res_l = e, res_r = e;\n            for (l += m, r += m; l < r; l >>= 1, r >>=\
    \ 1) {\n                if (l & 1) res_l = op(res_l, data[l++]);\n           \
    \     if (r & 1) res_r = op(data[--r], res_r);\n            }\n            return\
    \ op(res_l, res_r);\n        }\n        inline T prefix_prod(int r) const {\n\
    \            assert(0 <= r and r <= n);\n            return (*this)(0, r);\n \
    \       }\n        inline T suffix_prod(int l) const {\n            assert(0 <=\
    \ l and l <= n);\n            return (*this)(l, m);\n        }\n        inline\
    \ T all_prod() const {\n            return data[1];\n        }\n\n        inline\
    \ void set(int i, const T &val) {\n            assert(0 <= i and i < n);\n   \
    \         int k = i + m;\n            data[k] = val, propagate(k);\n        }\n\
    \        inline auto operator[](int i) {\n            assert(0 <= i and i < n);\n\
    \            struct {\n                const int k;\n                SegmentTree\
    \ &seg;\n                inline operator T() const { return seg.data[k]; }\n \
    \               inline auto& operator++() { ++seg.data[k], seg.propagate(k); return\
    \ *this; }\n                inline auto& operator--() { --seg.data[k], seg.propagate(k);\
    \ return *this; }\n                inline auto& operator+=(const T &val) { seg.data[k]\
    \ += val, seg.propagate(k); return *this; }\n                inline auto& operator-=(const\
    \ T &val) { seg.data[k] -= val, seg.propagate(k); return *this; }\n          \
    \      inline auto& operator*=(const T &val) { seg.data[k] *= val, seg.propagate(k);\
    \ return *this; }\n                inline auto& operator/=(const T &val) { seg.data[k]\
    \ /= val, seg.propagate(k); return *this; }\n                inline auto& operator%=(const\
    \ T &val) { seg.data[k] %= val, seg.propagate(k); return *this; }\n          \
    \      inline auto& operator =(const T &val) { seg.data[k]  = val, seg.propagate(k);\
    \ return *this; }\n            } obj {i + m, *this};\n            return obj;\n\
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
    \     while (m < n) m <<= 1;\n            return m;\n        }\n        inline\
    \ void propagate(int k) {\n            for (k >>= 1; k; k >>= 1) update(k);\n\
    \        }\n        inline void update(int k) {\n            data[k] = op(data[k\
    \ * 2], data[k * 2 + 1]);\n        }\n};\n} // namespace suisen\n\n\n\n#line 6\
    \ \"test/src/datastructure/segment_tree/DSL_2_B.test.cpp\"\nusing suisen::SegmentTree;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    SegmentTree seg(n, 0, std::plus<int>());\n\
    \    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n \
    \       if (t == 0) {\n            int i, x;\n            std::cin >> i >> x;\n\
    \            seg[i - 1] += x;\n        } else {\n            int s, t;\n     \
    \       std::cin >> s >> t;\n            std::cout << seg(--s, t) << '\\n';\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree.hpp\"\
    \nusing suisen::SegmentTree;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    SegmentTree\
    \ seg(n, 0, std::plus<int>());\n    for (int i = 0; i < q; ++i) {\n        int\
    \ t;\n        std::cin >> t;\n        if (t == 0) {\n            int i, x;\n \
    \           std::cin >> i >> x;\n            seg[i - 1] += x;\n        } else\
    \ {\n            int s, t;\n            std::cin >> s >> t;\n            std::cout\
    \ << seg(--s, t) << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
  requiredBy: []
  timestamp: '2021-07-25 09:50:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/DSL_2_B.test.cpp
- /verify/test/src/datastructure/segment_tree/DSL_2_B.test.cpp.html
title: test/src/datastructure/segment_tree/DSL_2_B.test.cpp
---
