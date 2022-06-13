---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree.hpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp
    title: "2D Binary Indexed Tree (\u70B9\u7FA4\u304C\u758E\u306A\u5834\u5408)"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp
    title: Rectangle Add Rectangle Sum
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/tuple_ops.hpp
    title: Tuple Ops
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include <atcoder/modint>\nusing\
    \ mint = atcoder::modint998244353;\n\n#line 1 \"library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp\"\
    \n\n\n\n#line 1 \"library/util/tuple_ops.hpp\"\n\n\n\n#include <tuple>\n\nnamespace\
    \ suisen {\n    namespace internal::tuple_ops {\n        template <std::size_t\
    \ N, typename F, typename ...Args>\n        std::tuple<Args...>& update(std::tuple<Args...>\
    \ &lhs, F &&fun) {\n            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>)\
    \ return lhs;\n            else return fun(std::get<N>(lhs)), update<N + 1>(lhs,\
    \ std::forward<F>(fun));\n        }\n        template <std::size_t N, typename\
    \ F, typename ...Args>\n        std::tuple<Args...>& merge(std::tuple<Args...>\
    \ &lhs, const std::tuple<Args...>& rhs, F &&fun) {\n            if constexpr (N\
    \ == std::tuple_size_v<std::tuple<Args...>>) return lhs;\n            else return\
    \ fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N + 1>(lhs, rhs, std::forward<F>(fun));\n\
    \        }\n    }\n    template <typename ...Args>\n    std::tuple<Args...>& operator+=(std::tuple<Args...>&\
    \ t1, const std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x += y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const\
    \ std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
    \ t2, [](auto &x, const auto &y) { x -= y; });\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...> operator+(std::tuple<Args...> t1, const std::tuple<Args...>&\
    \ t2) { return std::move(t1 += t2); }\n    template <typename ...Args>\n    std::tuple<Args...>\
    \ operator-(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1\
    \ -= t2); }\n    \n    template <typename V, typename ...Args>\n    std::tuple<Args...>&\
    \ operator*=(std::tuple<Args...>& t1, const V &v) { return internal::tuple_ops::update<0>(t1,\
    \ [&v](auto &x) { x *= v; }); }\n    template <typename V, typename ...Args>\n\
    \    std::tuple<Args...>& operator/=(std::tuple<Args...>& t1, const V &v) { return\
    \ internal::tuple_ops::update<0>(t1, [&v](auto &x) { x /= v; }); }\n\n    template\
    \ <typename V, typename ...Args>\n    std::tuple<Args...> operator*(const V &v,\
    \ std::tuple<Args...> t1) { return std::move(t1 *= v); }\n    template <typename\
    \ V, typename ...Args>\n    std::tuple<Args...> operator*(std::tuple<Args...>\
    \ t1, const V &v) { return std::move(t1 *= v); }\n    template <typename V, typename\
    \ ...Args>\n    std::tuple<Args...> operator/(std::tuple<Args...> t1, const V\
    \ &v) { return std::move(t1 /= v); }\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp\"\
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
    \ 6 \"library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp\"\n\n\
    namespace suisen {\n    template <typename T>\n    struct RectangleAddRectangleSum\
    \ {\n        using value_type = T;\n        using data_type = std::tuple<value_type,\
    \ value_type, value_type, value_type>;\n\n        RectangleAddRectangleSum() =\
    \ default;\n        explicit RectangleAddRectangleSum(int xnum) : _seg(xnum) {}\n\
    \n        void register_add_query_rectangle(int l, int r, int d, int u) {\n  \
    \          _seg.add_point(l, d), _seg.add_point(r, d);\n            _seg.add_point(l,\
    \ u), _seg.add_point(r, u);\n        }\n        void build() {\n            _seg.build();\n\
    \        }\n\n        void add(int l, int r, int d, int u, const value_type& val)\
    \ {\n            add(l, d, val), add(r, d, -val);\n            add(l, u, -val),\
    \ add(r, u, val);\n        }\n\n        value_type sum(int l, int r, int d, int\
    \ u) const {\n            return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);\n\
    \        }\n\n    private:\n        static constexpr data_type op_data(data_type\
    \ x, data_type y) { return x + y; }\n        static constexpr data_type e_data()\
    \ { return data_type{}; }\n\n        FenwickTree2DSparse<data_type> _seg;\n\n\
    \        void add(int l, int d, const value_type& v) {\n            // v(x - l)(y\
    \ - d) = v xy - vd x - vl y + vld\n            _seg.add(l, d, data_type{ v, -v\
    \ * d, -v * l, v * l * d });\n        }\n\n        value_type sum(int r, int u)\
    \ const {\n            static constexpr int inf = std::numeric_limits<int>::max();\n\
    \            auto [a, b, c, d] = _seg.sum(-inf, r, -inf, u);\n            return\
    \ a * r * u + b * r + c * u + d;\n        }\n    };\n} // namespace suisen\n\n\
    \n#line 10 \"test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp\"\
    \nusing suisen::RectangleAddRectangleSum;\n\ntemplate <typename T, int H, int\
    \ W>\nstruct RectangleAddRectangleSumNaive {\n    using value_type = T;\n    RectangleAddRectangleSumNaive()\
    \ {\n        for (auto& row : _dat) row.fill(T{ 0 });\n    }\n\n    void add(int\
    \ l, int r, int d, int u, const value_type& val) {\n        for (int x = l; x\
    \ < r; ++x) for (int y = d; y < u; ++y) _dat[x][y] += val;\n    }\n\n    value_type\
    \ sum(int l, int r, int d, int u) const {\n        value_type res{ 0 };\n    \
    \    for (int x = l; x < r; ++x) for (int y = d; y < u; ++y) res += _dat[x][y];\n\
    \        return res;\n    }\nprivate:\n    std::array<std::array<value_type, H>,\
    \ W> _dat;\n};\n\n\ntemplate <int H, int W, int Q>\nvoid random_test(uint32_t\
    \ seed = ~uint32_t(0)) {\n    std::mt19937 rng{ seed != ~uint32_t(0) ? seed :\
    \ std::random_device{}() };\n\n    RectangleAddRectangleSumNaive<mint, H, W> sol1;\n\
    \    RectangleAddRectangleSum<mint> sol2(H);\n\n    using query_t = std::tuple<int,\
    \ int, int, int, int>;\n\n    std::vector<query_t> queries(Q);\n    std::uniform_int_distribution<int>\
    \ dist_x(0, H - 1), dist_y(0, W - 1), dist_val(0, mint::mod() - 1);\n\n    for\
    \ (int i = 0; i < Q; ++i) {\n        int l = dist_x(rng), r = dist_x(rng);\n \
    \       if (l > r) std::swap(l, r);\n        int d = dist_y(rng), u = dist_y(rng);\n\
    \        if (d > u) std::swap(d, u);\n        if (rng() & 1) {\n            int\
    \ val = dist_val(rng);\n            queries[i] = { l, r, d, u, val };\n      \
    \      sol2.register_add_query_rectangle(l, r, d, u);\n        } else {\n    \
    \        queries[i] = { l, r, d, u, -1 };\n        }\n    }\n    sol2.build();\n\
    \n    for (const auto& [l, r, d, u, v] : queries) {\n        if (v >= 0) {\n \
    \           sol1.add(l, r, d, u, v), sol2.add(l, r, d, u, v);\n        } else\
    \ {\n            assert(sol1.sum(l, r, d, u) == sol2.sum(l, r, d, u));\n     \
    \   }\n    }\n}\n\nint main() {\n    random_test<1000, 1000, 2000>();\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include <atcoder/modint>\nusing\
    \ mint = atcoder::modint998244353;\n\n#include \"library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp\"\
    \nusing suisen::RectangleAddRectangleSum;\n\ntemplate <typename T, int H, int\
    \ W>\nstruct RectangleAddRectangleSumNaive {\n    using value_type = T;\n    RectangleAddRectangleSumNaive()\
    \ {\n        for (auto& row : _dat) row.fill(T{ 0 });\n    }\n\n    void add(int\
    \ l, int r, int d, int u, const value_type& val) {\n        for (int x = l; x\
    \ < r; ++x) for (int y = d; y < u; ++y) _dat[x][y] += val;\n    }\n\n    value_type\
    \ sum(int l, int r, int d, int u) const {\n        value_type res{ 0 };\n    \
    \    for (int x = l; x < r; ++x) for (int y = d; y < u; ++y) res += _dat[x][y];\n\
    \        return res;\n    }\nprivate:\n    std::array<std::array<value_type, H>,\
    \ W> _dat;\n};\n\n\ntemplate <int H, int W, int Q>\nvoid random_test(uint32_t\
    \ seed = ~uint32_t(0)) {\n    std::mt19937 rng{ seed != ~uint32_t(0) ? seed :\
    \ std::random_device{}() };\n\n    RectangleAddRectangleSumNaive<mint, H, W> sol1;\n\
    \    RectangleAddRectangleSum<mint> sol2(H);\n\n    using query_t = std::tuple<int,\
    \ int, int, int, int>;\n\n    std::vector<query_t> queries(Q);\n    std::uniform_int_distribution<int>\
    \ dist_x(0, H - 1), dist_y(0, W - 1), dist_val(0, mint::mod() - 1);\n\n    for\
    \ (int i = 0; i < Q; ++i) {\n        int l = dist_x(rng), r = dist_x(rng);\n \
    \       if (l > r) std::swap(l, r);\n        int d = dist_y(rng), u = dist_y(rng);\n\
    \        if (d > u) std::swap(d, u);\n        if (rng() & 1) {\n            int\
    \ val = dist_val(rng);\n            queries[i] = { l, r, d, u, val };\n      \
    \      sol2.register_add_query_rectangle(l, r, d, u);\n        } else {\n    \
    \        queries[i] = { l, r, d, u, -1 };\n        }\n    }\n    sol2.build();\n\
    \n    for (const auto& [l, r, d, u, v] : queries) {\n        if (v >= 0) {\n \
    \           sol1.add(l, r, d, u, v), sol2.add(l, r, d, u, v);\n        } else\
    \ {\n            assert(sol1.sum(l, r, d, u) == sol2.sum(l, r, d, u));\n     \
    \   }\n    }\n}\n\nint main() {\n    random_test<1000, 1000, 2000>();\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/fenwick_tree/rectangle_add_rectangle_sum.hpp
  - library/util/tuple_ops.hpp
  - library/datastructure/fenwick_tree/fenwick_tree_2d_sparse.hpp
  - library/datastructure/fenwick_tree/fenwick_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-06-14 00:04:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
- /verify/test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp.html
title: test/src/datastructure/fenwick_tree/rectangle_add_rectangle_sum/dummy.test.cpp
---
