---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/fenwick_tree/fenwick_tree.hpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp
    title: Static Rectangle Add Rectangle Sum
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
    PROBLEM: https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n\n#line 1 \"library/util/tuple_ops.hpp\"\n\n\n\n\
    #include <tuple>\n\nnamespace suisen {\n    namespace internal::tuple_ops {\n\
    \        template <std::size_t N, typename F, typename ...Args>\n        std::tuple<Args...>&\
    \ update(std::tuple<Args...> &lhs, F &&fun) {\n            if constexpr (N ==\
    \ std::tuple_size_v<std::tuple<Args...>>) return lhs;\n            else return\
    \ fun(std::get<N>(lhs)), update<N + 1>(lhs, std::forward<F>(fun));\n        }\n\
    \        template <std::size_t N, typename F, typename ...Args>\n        std::tuple<Args...>&\
    \ merge(std::tuple<Args...> &lhs, const std::tuple<Args...>& rhs, F &&fun) {\n\
    \            if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return\
    \ lhs;\n            else return fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N\
    \ + 1>(lhs, rhs, std::forward<F>(fun));\n        }\n    }\n    template <typename\
    \ ...Args>\n    std::tuple<Args...>& operator+=(std::tuple<Args...>& t1, const\
    \ std::tuple<Args...>& t2) {\n        return internal::tuple_ops::merge<0>(t1,\
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
    \ &v) { return std::move(t1 /= v); }\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree.hpp\"\
    \n\n\n\n#include <vector>\n#include <map>\n#include <unordered_map>\n\nnamespace\
    \ suisen {\n    namespace internal {\n        template <typename T, typename index_t\
    \ = int, typename Container = std::vector<T>>\n        class FenwickTreeBase {\n\
    \        public:\n            FenwickTreeBase() = default;\n            explicit\
    \ FenwickTreeBase(index_t n) : n(n) {}\n\n            int size() const {\n   \
    \             return n;\n            }\n            void add(index_t i, T v) {\n\
    \                for (++i; i <= n; i += (i & -i)) data[i - 1] += v;\n        \
    \    }\n            T sum(index_t l, index_t r) const {\n                return\
    \ sum(r) - sum(l);\n            }\n            auto operator[](int i) {\n    \
    \            struct {\n                    int i;\n                    FenwickTreeBase&\
    \ ft;\n                    operator T() const { return ft.sum(i, i + 1); }\n \
    \                   auto& operator++() { return *this += 1; }\n              \
    \      auto& operator--() { return *this -= 1; }\n                    auto& operator+=(T\
    \ val) { ft.add(i, val); return *this; }\n                    auto& operator-=(T\
    \ val) { ft.add(i, -val); return *this; }\n                    auto& operator*=(T\
    \ val) { T cur = ft.sum(i, i + 1); ft.add(i, cur * val - cur); return *this; }\n\
    \                    auto& operator/=(T val) { T cur = ft.sum(i, i + 1); ft.add(i,\
    \ cur / val - cur); return *this; }\n                    auto& operator%=(T val)\
    \ { T cur = ft.sum(i, i + 1); ft.add(i, cur % val - cur); return *this; }\n  \
    \                  auto& operator =(T val) { T cur = ft.sum(i, i + 1); ft.add(i,\
    \ val - cur); return *this; }\n                } obj{ i, *this };\n          \
    \      return obj;\n            }\n            T operator()(int l, int r) const\
    \ { return sum(l, r); }\n\n            Container& get_internal_container() { return\
    \ data; }\n        protected:\n            index_t n;\n            Container data;\n\
    \            template <typename ...Args>\n            FenwickTreeBase(index_t\
    \ n, Args &&...args) : n(n), data(std::forward<Args>(args)...) {}\n        private:\n\
    \            T sum(int r) const {\n                T s{};\n                for\
    \ (; r; r -= r & -r) s += data[r - 1];\n                return s;\n          \
    \  }\n        };\n\n        template <typename Key, typename Value, bool unordered>\n\
    \        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key,\
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
    \n} // namespace suisen\n\n\n#line 8 \"library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct AddQuery {\n   \
    \     int l, r, d, u;\n        T val;\n        AddQuery() = default;\n       \
    \ AddQuery(int l, int r, int d, int u, const T &val) : l(l), r(r), d(d), u(u),\
    \ val(val) {}\n    };\n    struct SumQuery {\n        int l, r, d, u;\n      \
    \  SumQuery() = default;\n        SumQuery(int l, int r, int d, int u) : l(l),\
    \ r(r), d(d), u(u) {}\n    };\n\n    template <typename T>\n    std::vector<T>\
    \ static_rectangle_add_rectangle_sum(const std::vector<AddQuery<T>>& add_queries,\
    \ const std::vector<SumQuery>& sum_queries) {\n        using suffix_add_query_type\
    \ = std::tuple<int, int, T>;         // l, d, val\n        using prefix_sum_query_type\
    \ = std::tuple<int, int, int, bool>; // r, u, query_id, sign\n\n        std::vector<int>\
    \ ys;\n        std::vector<suffix_add_query_type> suf_add_queries;\n        for\
    \ (const auto& q : add_queries) {\n            ys.push_back(q.d), ys.push_back(q.u);\n\
    \            suf_add_queries.emplace_back(q.l, q.d, q.val), suf_add_queries.emplace_back(q.r,\
    \ q.d, -q.val);\n            suf_add_queries.emplace_back(q.l, q.u, -q.val), suf_add_queries.emplace_back(q.r,\
    \ q.u, q.val);\n        }\n\n        std::sort(ys.begin(), ys.end());\n      \
    \  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n        auto compress\
    \ = [&ys](int y) -> int { return std::lower_bound(ys.begin(), ys.end(), y) - ys.begin();\
    \ };\n\n        std::vector<prefix_sum_query_type> pre_sum_queries;\n        for\
    \ (std::size_t i = 0; i < sum_queries.size(); ++i) {\n            const auto&\
    \ q = sum_queries[i];\n            pre_sum_queries.emplace_back(q.l, q.d, i, true),\
    \ pre_sum_queries.emplace_back(q.r, q.d, i, false);\n            pre_sum_queries.emplace_back(q.l,\
    \ q.u, i, false), pre_sum_queries.emplace_back(q.r, q.u, i, true);\n        }\n\
    \n        static constexpr auto x_comparator = [](const auto& q1, const auto&\
    \ q2) { return std::get<0>(q1) < std::get<0>(q2); };\n        std::sort(suf_add_queries.begin(),\
    \ suf_add_queries.end(), x_comparator);\n        std::sort(pre_sum_queries.begin(),\
    \ pre_sum_queries.end(), x_comparator);\n\n        using data_type = std::tuple<T,\
    \ T, T, T>;\n        FenwickTree<data_type> ft(ys.size());\n\n        std::vector<T>\
    \ res(sum_queries.size(), T{ 0 });\n        const int n = suf_add_queries.size(),\
    \ m = pre_sum_queries.size();\n        for (int i = 0, j = 0; i < n or j < m;)\
    \ {\n            if (j == m or (i < n and std::get<0>(suf_add_queries[i]) < std::get<0>(pre_sum_queries[j])))\
    \ {\n                const auto& [l, d, v] = suf_add_queries[i++];\n         \
    \       // v * (x - l) * (y - d) = v * xy - vd * x - vl * y + vld\n          \
    \      ft.add(compress(d), data_type{ v, -v * d, -v * l, v * l * d });\n     \
    \       } else {\n                const auto& [x, y, qid, is_add] = pre_sum_queries[j++];\n\
    \                auto [a, b, c, d] = ft.sum(0, compress(y));\n               \
    \ const T sum = a * x * y + b * x + c * y + d;\n                if (is_add) res[qid]\
    \ += sum;\n                else        res[qid] -= sum;\n            }\n     \
    \   }\n        return res;\n    }\n} // namespace suisen\n\n\n\n#line 9 \"test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    \n    std::vector<suisen::AddQuery<mint>>\
    \ add_queries(n);\n    for (int i = 0; i < n; ++i) {\n        int l, d, r, u,\
    \ w;\n        std::cin >> l >> d >> r >> u >> w;\n        add_queries[i] = { l,\
    \ r, d, u, w };\n    }\n    std::vector<suisen::SumQuery> sum_queries(q);\n  \
    \  for (int i = 0; i < q; ++i) {\n        int l, d, r, u;\n        std::cin >>\
    \ l >> d >> r >> u;\n        sum_queries[i] = { l, r, d, u };\n    }\n    for\
    \ (mint ans : suisen::static_rectangle_add_rectangle_sum(add_queries, sum_queries))\
    \ {\n        std::cout << ans.val() << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    \n    std::vector<suisen::AddQuery<mint>>\
    \ add_queries(n);\n    for (int i = 0; i < n; ++i) {\n        int l, d, r, u,\
    \ w;\n        std::cin >> l >> d >> r >> u >> w;\n        add_queries[i] = { l,\
    \ r, d, u, w };\n    }\n    std::vector<suisen::SumQuery> sum_queries(q);\n  \
    \  for (int i = 0; i < q; ++i) {\n        int l, d, r, u;\n        std::cin >>\
    \ l >> d >> r >> u;\n        sum_queries[i] = { l, r, d, u };\n    }\n    for\
    \ (mint ans : suisen::static_rectangle_add_rectangle_sum(add_queries, sum_queries))\
    \ {\n        std::cout << ans.val() << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum.hpp
  - library/util/tuple_ops.hpp
  - library/datastructure/fenwick_tree/fenwick_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
- /verify/test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp.html
title: test/src/datastructure/fenwick_tree/static_rectangle_add_rectangle_sum/static_rectangle_add_rectangle_sum.test.cpp
---
