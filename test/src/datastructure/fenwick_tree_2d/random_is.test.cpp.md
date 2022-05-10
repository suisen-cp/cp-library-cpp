---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree_2d.hpp
    title: Fenwick Tree 2d
  - icon: ':question:'
    path: library/datastructure/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc108/tasks/arc108_e
    links:
    - https://atcoder.jp/contests/arc108/tasks/arc108_e
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree_2d/random_is.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/arc108/tasks/arc108_e\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/math/inv_mods.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\ntemplate <typename mint>\nclass\
    \ inv_mods {\n    public:\n        inv_mods() {}\n        inv_mods(int n) { ensure(n);\
    \ }\n        const mint& operator[](int i) const {\n            ensure(i);\n \
    \           return invs[i];\n        }\n        static void ensure(int n) {\n\
    \            int sz = invs.size();\n            if (sz < 2) invs = {0, 1}, sz\
    \ = 2;\n            if (sz < n + 1) {\n                invs.resize(n + 1);\n \
    \               for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) *\
    \ invs[mod % i];\n            }\n        }\n    private:\n        static std::vector<mint>\
    \ invs;\n        static constexpr int mod = mint::mod();\n};\ntemplate <typename\
    \ mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line 1 \"library/datastructure/segment_tree/segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/datastructure/segment_tree/segment_tree.hpp\"\
    \n\n#line 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 5 \"library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\n\ntemplate\
    \ <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
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
    #line 8 \"library/datastructure/segment_tree/segment_tree.hpp\"\n\nnamespace suisen\
    \ {\ntemplate <typename T, T(*op)(T, T), T(*e)()>\nclass SegmentTree {\n    public:\n\
    \        SegmentTree() : SegmentTree(0) {}\n        explicit SegmentTree(int n)\
    \ : SegmentTree(std::vector<T>(n, e())) {}\n        SegmentTree(const std::vector<T>\
    \ &a) : n(a.size()), m(ceil_pow2(n)), data(2 * m, e()) {\n            build(a);\n\
    \        }\n\n        void build(const std::vector<T> &a) {\n            assert(int(a.size())\
    \ <= m);\n            std::copy(a.begin(), a.end(), data.begin() + m);\n     \
    \       for (int k = m - 1; k > 0; --k) update(k);\n        }\n        const T&\
    \ get(int i) const {\n            assert(0 <= i and i < n);\n            return\
    \ data[i + m];\n        }\n        T operator()(int l, int r) const {\n      \
    \      T res_l = e(), res_r = e();\n            for (l += m, r += m; l < r; l\
    \ >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l, data[l++]);\n\
    \                if (r & 1) res_r = op(data[--r], res_r);\n            }\n   \
    \         return op(res_l, res_r);\n        }\n        T prod(int l, int r) const\
    \ { return (*this)(l, r); }\n        T prefix_prod(int r) const { return (*this)(0,\
    \ r); }\n        T suffix_prod(int l) const { return (*this)(l, m); }\n      \
    \  T all_prod() const { return data[1]; }\n\n        void set(int i, const T &val)\
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
    \        }\n        template <bool(*f)(T)>\n        int max_right(int l) { return\
    \ max_right(l, f); }\n\n        template <typename Pred, constraints_t<is_same_as_invoke_result<bool,\
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
    \ suisen\n\n\n\n#line 1 \"library/datastructure/fenwick_tree_2d.hpp\"\n\n\n\n\
    #line 5 \"library/datastructure/fenwick_tree_2d.hpp\"\n\nnamespace suisen {\n\n\
    \    template <typename T>\n    class FenwickTree2D {\n    public:\n        FenwickTree2D()\
    \ {}\n        explicit FenwickTree2D(int n, int m) : n(n), m(m), data(n, std::vector<T>(m,\
    \ T{})) {}\n        void add(int i, int j, T v) {\n            for (int x = i\
    \ + 1; x <= n; x += (x & -x)) for (int y = j + 1; y <= m; y += (y & -y)) {\n \
    \               data[x - 1][y - 1] += v;\n            }\n        }\n        T\
    \ sum(int xl, int xr, int yl, int yr) const {\n            return sum(xr, yr)\
    \ - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);\n        }\n        auto operator[](std::pair<int,\
    \ int> index) {\n            auto [i, j] = index;\n            struct {\n    \
    \            int i, j;\n                FenwickTree2D& ft;\n                operator\
    \ T() const { return ft.sum(i, i + 1, j, j + 1); }\n                auto& operator++()\
    \ { return *this += 1; }\n                auto& operator--() { return *this -=\
    \ 1; }\n                auto& operator+=(T val) { ft.add(i, j, val); return *this;\
    \ }\n                auto& operator-=(T val) { ft.add(i, j, -val); return *this;\
    \ }\n                auto& operator*=(T val) { T cur = *this; ft.add(i, j, cur\
    \ * val - cur); return *this; }\n                auto& operator/=(T val) { T cur\
    \ = *this; ft.add(i, j, cur / val - cur); return *this; }\n                auto&\
    \ operator%=(T val) { T cur = *this; ft.add(i, j, cur % val - cur); return *this;\
    \ }\n                auto& operator =(T val) { T cur = *this; ft.add(i, j, val\
    \ - cur); return *this; }\n            } obj{ i, j, *this };\n            return\
    \ obj;\n        }\n        T operator()(int xl, int xr, int yl, int yr) const\
    \ { return sum(xl, xr, yl, yr); }\n\n    private:\n        int n, m;\n       \
    \ std::vector<std::vector<T>> data;\n\n        T sum(int xr, int yr) const {\n\
    \            T s{};\n            for (int x = xr; x; x -= x & -x) for (int y =\
    \ yr; y; y -= y & -y) {\n                s += data[x - 1][y - 1];\n          \
    \  }\n            return s;\n        }\n    };\n\n} // namespace suisen\n\n\n\
    #line 9 \"test/src/datastructure/fenwick_tree_2d/random_is.test.cpp\"\n\nusing\
    \ namespace suisen;\nusing mint = atcoder::modint1000000007;\n\nmint op(mint x,\
    \ mint y) {\n    return x + y;\n}\nmint e() {\n    return 0;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n    std::vector<int> a(n);\n\n    inv_mods<mint>\
    \ invs(n);\n\n    for (int &e : a) std::cin >> e;\n    a.insert(a.begin(), 0);\n\
    \    a.insert(a.end(), n + 1);\n\n    std::vector dp_segs(n + 2, SegmentTree<mint,\
    \ op, e>(n + 2));\n    std::vector pd_segs(n + 2, SegmentTree<mint, op, e>(n +\
    \ 2));\n\n    FenwickTree2D<int> ft_point(n + 2, n + 2);\n    for (int i = 1;\
    \ i <= n; ++i) ++ft_point[{i, a[i]}];\n\n    mint ans = 0;\n    for (int w = 1;\
    \ w <= n; ++w) {\n        for (int l = 1, r = w; r <= n; ++l, ++r) {\n       \
    \     int vl = a[l - 1], vr = a[r + 1];\n            if (vl > vr) continue;\n\
    \            int k = ft_point(l, r + 1, vl, vr);\n            if (k == 0) continue;\n\
    \            mint val = 1 + ((dp_segs[l](vl, vr) + pd_segs[r](vl, vr)) * invs[k]).val();\n\
    \            dp_segs[l][a[r + 1]] += val;\n            pd_segs[r][a[l - 1]] +=\
    \ val;\n            if (w == n) ans = val;\n        }\n    }\n    std::cout <<\
    \ ans.val() << std::endl;\n    return 0;\n}\n\n\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc108/tasks/arc108_e\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\n#include \"library/math/inv_mods.hpp\"\
    \n#include \"library/datastructure/segment_tree/segment_tree.hpp\"\n#include \"\
    library/datastructure/fenwick_tree_2d.hpp\"\n\nusing namespace suisen;\nusing\
    \ mint = atcoder::modint1000000007;\n\nmint op(mint x, mint y) {\n    return x\
    \ + y;\n}\nmint e() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n    std::vector<int>\
    \ a(n);\n\n    inv_mods<mint> invs(n);\n\n    for (int &e : a) std::cin >> e;\n\
    \    a.insert(a.begin(), 0);\n    a.insert(a.end(), n + 1);\n\n    std::vector\
    \ dp_segs(n + 2, SegmentTree<mint, op, e>(n + 2));\n    std::vector pd_segs(n\
    \ + 2, SegmentTree<mint, op, e>(n + 2));\n\n    FenwickTree2D<int> ft_point(n\
    \ + 2, n + 2);\n    for (int i = 1; i <= n; ++i) ++ft_point[{i, a[i]}];\n\n  \
    \  mint ans = 0;\n    for (int w = 1; w <= n; ++w) {\n        for (int l = 1,\
    \ r = w; r <= n; ++l, ++r) {\n            int vl = a[l - 1], vr = a[r + 1];\n\
    \            if (vl > vr) continue;\n            int k = ft_point(l, r + 1, vl,\
    \ vr);\n            if (k == 0) continue;\n            mint val = 1 + ((dp_segs[l](vl,\
    \ vr) + pd_segs[r](vl, vr)) * invs[k]).val();\n            dp_segs[l][a[r + 1]]\
    \ += val;\n            pd_segs[r][a[l - 1]] += val;\n            if (w == n) ans\
    \ = val;\n        }\n    }\n    std::cout << ans.val() << std::endl;\n    return\
    \ 0;\n}\n\n\n"
  dependsOn:
  - library/math/inv_mods.hpp
  - library/datastructure/segment_tree/segment_tree.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/fenwick_tree_2d.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  requiredBy: []
  timestamp: '2022-05-09 17:42:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
- /verify/test/src/datastructure/fenwick_tree_2d/random_is.test.cpp.html
title: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
---
