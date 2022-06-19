---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree.hpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp
    title: "2D Binary Indexed Tree (\u70B9\u7FA4\u304C\u758E\u306A\u5834\u5408)"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
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
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#line 7 \"library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp\"\
    \n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree.hpp\"\n\n\n\n#include\
    \ <vector>\n#include <map>\n#include <unordered_map>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 9 \"library/datastructure/fenwick_tree/fenwick_tree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal {\n        template <typename T,\
    \ typename index_t = int, typename Container = std::vector<T>>\n        class\
    \ FenwickTreeBase {\n        public:\n            FenwickTreeBase() {}\n     \
    \       explicit FenwickTreeBase(index_t n) : n(n) {}\n\n            int size()\
    \ const {\n                return n;\n            }\n            void add(index_t\
    \ i, T v) {\n                for (++i; i <= n; i += (i & -i)) data[i - 1] += v;\n\
    \            }\n            T sum(index_t l, index_t r) const {\n            \
    \    return sum(r) - sum(l);\n            }\n            auto operator[](int i)\
    \ {\n                struct {\n                    int i;\n                  \
    \  FenwickTreeBase& ft;\n                    operator T() const { return ft.sum(i,\
    \ i + 1); }\n                    auto& operator++() { return *this += 1; }\n \
    \                   auto& operator--() { return *this -= 1; }\n              \
    \      auto& operator+=(T val) { ft.add(i, val); return *this; }\n           \
    \         auto& operator-=(T val) { ft.add(i, -val); return *this; }\n       \
    \             auto& operator*=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur\
    \ * val - cur); return *this; }\n                    auto& operator/=(T val) {\
    \ T cur = ft.sum(i, i + 1); ft.add(i, cur / val - cur); return *this; }\n    \
    \                auto& operator%=(T val) { T cur = ft.sum(i, i + 1); ft.add(i,\
    \ cur % val - cur); return *this; }\n                    auto& operator =(T val)\
    \ { T cur = ft.sum(i, i + 1); ft.add(i, val - cur); return *this; }\n        \
    \        } obj{ i, *this };\n                return obj;\n            }\n    \
    \        T operator()(int l, int r) const { return sum(l, r); }\n\n          \
    \  Container& get_internal_container() { return data; }\n        protected:\n\
    \            index_t n;\n            Container data;\n            template <typename\
    \ ...Args>\n            FenwickTreeBase(index_t n, Args &&...args) : n(n), data(std::forward<Args>(args)...)\
    \ {}\n        private:\n            T sum(int r) const {\n                T s{};\n\
    \                for (; r; r -= r & -r) s += data[r - 1];\n                return\
    \ s;\n            }\n        };\n\n        template <typename Key, typename Value,\
    \ bool unordered>\n        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key,\
    \ Value>, std::map<Key, Value>>;\n\n    } // namespace internal\n\n    template\
    \ <typename T>\n    struct FenwickTree : public internal::FenwickTreeBase<T> {\n\
    \        FenwickTree() : FenwickTree(0) {}\n        explicit FenwickTree(int n)\
    \ : internal::FenwickTreeBase<T>::FenwickTreeBase(n, n, T{}) {}\n        explicit\
    \ FenwickTree(std::vector<T>&& a) : internal::FenwickTreeBase<T>::FenwickTreeBase(a.size(),\
    \ std::move(a)) {\n            for (int i = 1; i <= this->n; ++i) {\n        \
    \        int p = i + (i & -i);\n                if (p <= this->n) this->data[p\
    \ - 1] += this->data[i - 1];\n            }\n        }\n        explicit FenwickTree(const\
    \ std::vector<T>& a) : FenwickTree(std::vector<T>(a)) {}\n    };\n\n    template\
    \ <typename T, typename index_t, bool use_unordered_map = false>\n    using MapFenwickTree\
    \ = internal::FenwickTreeBase<T, index_t, internal::cond_map_t<index_t, T, use_unordered_map>>;\n\
    \n} // namespace suisen\n\n\n#line 9 \"library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp\"\
    \n\nnamespace suisen {\n\n    template <typename T>\n    class FenwickTree2DSparse\
    \ {\n    public:\n        FenwickTree2DSparse() {}\n        explicit FenwickTree2DSparse(int\
    \ x_num) : n(x_num + 1), data(n), points(), pos_x(), pos_y(n) {}\n\n        void\
    \ add_point(int x, int y) {\n            built = false;\n            pos_x.push_back(x);\n\
    \            points.emplace_back(x, y);\n        }\n\n        void build() {\n\
    \            static constexpr int inf = std::numeric_limits<int>::max();\n   \
    \         built = true;\n            pos_x.push_back(inf);\n            std::sort(pos_x.begin(),\
    \ pos_x.end());\n            pos_x.erase(std::unique(pos_x.begin(), pos_x.end()),\
    \ pos_x.end());\n            assert(int(pos_x.size()) <= n);\n            for\
    \ (const auto& [x, y] : points) for (int k = comp_x(x) + 1; k <= n; k += k & -k)\
    \ {\n                pos_y[k - 1].push_back(y);\n            }\n            for\
    \ (int k = 0; k < n; ++k) {\n                pos_y[k].push_back(inf);\n      \
    \          std::sort(pos_y[k].begin(), pos_y[k].end());\n                pos_y[k].erase(std::unique(pos_y[k].begin(),\
    \ pos_y[k].end()), pos_y[k].end());\n                data[k] = FenwickTree<T>(pos_y[k].size());\n\
    \            }\n        }\n\n        // void build_and_init(const std::vector<std::tuple<int,\
    \ int, T>> &points) {\n        //     build();\n        //     for (const auto\
    \ &[x, y, w] : points) {\n        //         int kx = comp_x(x), ky = comp_y(kx,\
    \ y);\n        //         data[kx].get_internal_container()[ky] += w;\n      \
    \  //     }\n        //     for (int kx = n; kx; --kx) {\n        //         auto\
    \ &data_kx = data[kx - 1].get_internal_container();\n        //         const\
    \ int m = data[kx - 1].size();\n        //         for (int ky = m; ky; --ky)\
    \ {\n        //             const int pky = ky + (ky & -ky);\n        //     \
    \        if (pky > m) continue;\n        //             data_kx[pky - 1] += data[ky\
    \ - 1];\n        //         }\n        //         const int pkx = kx + (kx & -kx);\n\
    \        //         if (pkx > n) continue;\n        //         auto &data_pkx\
    \ = data[pkx - 1].get_internal_container();\n        //         for (int ky =\
    \ m; ky; --ky) {\n        //             int y = pos_y[kx - 1][ky - 1];\n    \
    \    //             data_pkx[comp_y(pkx - 1, y)] += data_kx[ky - 1];\n       \
    \ //         }\n        //     }\n        // }\n\n        T sum(int l, int r,\
    \ int d, int u) const {\n            return (*this)(l, r, d, u);\n        }\n\
    \        T operator()(int l, int r, int d, int u) const {\n            assert(built);\n\
    \            return sum(r, d, u) - sum(l, d, u);\n        }\n\n        T get(int\
    \ x, int y) const {\n            return (*this)(x, x + 1, y, y + 1);\n       \
    \ }\n        void add(int x, int y, const T& val) {\n            for (int k =\
    \ comp_x(x) + 1; k <= n; k += k & -k) data[k - 1].add(comp_y(k - 1, y), val);\n\
    \        }\n        template <typename F>\n        void apply(int x, int y, F\
    \ &&f) {\n            T old_val = get(x, y);\n            add(x, y, f(old_val)\
    \ - old_val);\n        }\n        void set(int x, int y, const T &val) {\n   \
    \         apply(x, y, [&](const T&) { return val; });\n        }\n\n    private:\n\
    \        int n, m;\n        std::vector<FenwickTree<T>> data;\n        std::vector<std::pair<int,\
    \ int>> points;\n        std::vector<int> pos_x;\n        std::vector<std::vector<int>>\
    \ pos_y;\n        bool built = true;\n\n        int comp_x(int x) const {\n  \
    \          return std::lower_bound(pos_x.begin(), pos_x.end(), x) - pos_x.begin();\n\
    \        }\n        int comp_y(int k, int y) const {\n            return std::lower_bound(pos_y[k].begin(),\
    \ pos_y[k].end(), y) - pos_y[k].begin();\n        }\n\n        T sum(int r, int\
    \ d, int u) const {\n            T res{};\n            for (r = comp_x(r); r;\
    \ r -= r & -r) res += data[r - 1].sum(comp_y(r - 1, d), comp_y(r - 1, u));\n \
    \           return res;\n        }\n    };\n} // namespace suisen\n\n\n\n#line\
    \ 7 \"test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp\"\
    \nusing suisen::FenwickTree2DSparse;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    FenwickTree2DSparse<long\
    \ long> seg(n);\n    std::vector<std::tuple<int, int, int>> points(n);\n    for\
    \ (int i = 0; i < n; ++i) {\n        int x, y, w;\n        std::cin >> x >> y\
    \ >> w;\n        points[i] = { x, y, w };\n        seg.add_point(x, y);\n    }\n\
    \    seg.build();\n    for (auto [x, y, w] : points) {\n        seg.add(x, y,\
    \ w);\n    }\n    for (int i = 0; i < q; ++i) {\n        int l, d, r, u;\n   \
    \     std::cin >> l >> d >> r >> u;\n        std::cout << seg.sum(l, r, d, u)\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#include \"library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp\"\
    \nusing suisen::FenwickTree2DSparse;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    FenwickTree2DSparse<long\
    \ long> seg(n);\n    std::vector<std::tuple<int, int, int>> points(n);\n    for\
    \ (int i = 0; i < n; ++i) {\n        int x, y, w;\n        std::cin >> x >> y\
    \ >> w;\n        points[i] = { x, y, w };\n        seg.add_point(x, y);\n    }\n\
    \    seg.build();\n    for (auto [x, y, w] : points) {\n        seg.add(x, y,\
    \ w);\n    }\n    for (int i = 0; i < q; ++i) {\n        int l, d, r, u;\n   \
    \     std::cin >> l >> d >> r >> u;\n        std::cout << seg.sum(l, r, d, u)\
    \ << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp
  - library/datastructure/fenwick_tree/fenwick_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2022-06-14 00:04:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp
- /verify/test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp.html
title: test/src/datastructure/fenwick_tree/fenwick_tree_2d_sparse/rectangle_sum.test.cpp
---