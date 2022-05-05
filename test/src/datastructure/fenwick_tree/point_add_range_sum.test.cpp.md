---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree.hpp
    title: Fenwick Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
    #include <iostream>\n\n#line 1 \"library/datastructure/fenwick_tree.hpp\"\n\n\n\
    \n#include <vector>\n#include <map>\n#include <unordered_map>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 9 \"library/datastructure/fenwick_tree.hpp\"\n\nnamespace suisen {\n    namespace\
    \ internal {\n        template <typename T, typename index_t = int, typename Container\
    \ = std::vector<T>>\n        class FenwickTreeBase {\n        public:\n      \
    \      FenwickTreeBase() {}\n            explicit FenwickTreeBase(index_t n) :\
    \ n(n) {}\n            void add(index_t i, T v) {\n                for (++i; i\
    \ <= n; i += (i & -i)) data[i - 1] += v;\n            }\n            T sum(index_t\
    \ l, index_t r) const {\n                return sum(r) - sum(l);\n           \
    \ }\n            auto operator[](int i) {\n                struct {\n        \
    \            int i;\n                    FenwickTreeBase& ft;\n              \
    \      operator T() const { return ft.sum(i, i + 1); }\n                    auto&\
    \ operator++() { return *this += 1; }\n                    auto& operator--()\
    \ { return *this -= 1; }\n                    auto& operator+=(T val) { ft.add(i,\
    \ val); return *this; }\n                    auto& operator-=(T val) { ft.add(i,\
    \ -val); return *this; }\n                    auto& operator*=(T val) { T cur\
    \ = ft.sum(i, i + 1); ft.add(i, cur * val - cur); return *this; }\n          \
    \          auto& operator/=(T val) { T cur = ft.sum(i, i + 1); ft.add(i, cur /\
    \ val - cur); return *this; }\n                    auto& operator%=(T val) { T\
    \ cur = ft.sum(i, i + 1); ft.add(i, cur % val - cur); return *this; }\n      \
    \              auto& operator =(T val) { T cur = ft.sum(i, i + 1); ft.add(i, val\
    \ - cur); return *this; }\n                } obj{ i, *this };\n              \
    \  return obj;\n            }\n            T operator()(int l, int r) const {\
    \ return sum(l, r); }\n        protected:\n            index_t n;\n          \
    \  Container data;\n            template <typename ...Args>\n            FenwickTreeBase(index_t\
    \ n, Args &&...args) : n(n), data(std::forward<Args>(args)...) {}\n        private:\n\
    \            T sum(int r) const {\n                T s(0);\n                for\
    \ (; r; r -= r & -r) s += data[r - 1];\n                return s;\n          \
    \  }\n        };\n\n        template <typename Key, typename Value, bool unordered>\n\
    \        using cond_map_t = std::conditional_t<unordered, std::unordered_map<Key,\
    \ Value>, std::map<Key, Value>>;\n\n    } // namespace internal\n\n    template\
    \ <typename T>\n    struct FenwickTree : public internal::FenwickTreeBase<T> {\n\
    \        FenwickTree() : FenwickTree(0) {}\n        explicit FenwickTree(int n)\
    \ : internal::FenwickTreeBase<T>::FenwickTreeBase(n, n, T(0)) {}\n        explicit\
    \ FenwickTree(std::vector<T>&& a) : internal::FenwickTreeBase<T>::FenwickTreeBase(a.size(),\
    \ std::move(a)) {\n            for (int i = 1; i <= this->n; ++i) {\n        \
    \        int p = i + (i & -i);\n                if (p <= this->n) this->data[p\
    \ - 1] += this->data[i - 1];\n            }\n        }\n        explicit FenwickTree(const\
    \ std::vector<T>& a) : FenwickTree(std::vector<T>(a)) {}\n    };\n\n    template\
    \ <typename T, typename index_t, bool use_unordered_map = false>\n    using MapFenwickTree\
    \ = internal::FenwickTreeBase<T, index_t, internal::cond_map_t<index_t, T, use_unordered_map>>;\n\
    \n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp\"\
    \n\nusing suisen::FenwickTree;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> a(n);\n    for (auto &e : a) std::cin >> e;\n    FenwickTree<long long>\
    \ ft(std::move(a));\n    while (q --> 0) {\n        int t;\n        std::cin >>\
    \ t;\n        if (t == 0) {\n            int p, x;\n            std::cin >> p\
    \ >> x;\n            ft[p] += x;\n        } else {\n            int l, r;\n  \
    \          std::cin >> l >> r;\n            std::cout << ft(l, r) << '\\n';\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n\n#include \"library/datastructure/fenwick_tree.hpp\"\n\
    \nusing suisen::FenwickTree;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> a(n);\n    for (auto &e : a) std::cin >> e;\n    FenwickTree<long long>\
    \ ft(std::move(a));\n    while (q --> 0) {\n        int t;\n        std::cin >>\
    \ t;\n        if (t == 0) {\n            int p, x;\n            std::cin >> p\
    \ >> x;\n            ft[p] += x;\n        } else {\n            int l, r;\n  \
    \          std::cin >> l >> r;\n            std::cout << ft(l, r) << '\\n';\n\
    \        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/fenwick_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
- /verify/test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp.html
title: test/src/datastructure/fenwick_tree/point_add_range_sum.test.cpp
---
