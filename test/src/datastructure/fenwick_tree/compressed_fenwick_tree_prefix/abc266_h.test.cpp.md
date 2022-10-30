---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/compressed_fenwick_tree_prefix.hpp
    title: Compressed Fenwick Tree Prefix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc266/tasks/abc266_Ex
    links:
    - https://atcoder.jp/contests/abc266/tasks/abc266_Ex
  bundledCode: "#line 1 \"test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc266/tasks/abc266_Ex\"\n\n#line\
    \ 1 \"library/datastructure/fenwick_tree/compressed_fenwick_tree_prefix.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace suisen\
    \ {\n    namespace internal::compressed_fenwick_tree_prefix {\n        template\
    \ <typename T>\n        struct Compressor {\n            using value_type = T;\n\
    \            Compressor() = default;\n            void add(const value_type& x)\
    \ { xs.push_back(x); }\n            int build() {\n                std::sort(xs.begin(),\
    \ xs.end());\n                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\
    \                return xs.size();\n            }\n            int operator()(const\
    \ value_type& x) const { return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();\
    \ }\n        private:\n            std::vector<value_type> xs;\n        };\n \
    \   }\n\n    template <typename T, T(*op)(T, T), T(*e)(), std::size_t K = 1, typename\
    \ Index = int>\n    struct CompressedFenwickTreePrefix {\n        using value_type\
    \ = T;\n        using index_type = Index;\n        using point_type = std::array<index_type,\
    \ K>;\n        using data_type = CompressedFenwickTreePrefix<value_type, op, e,\
    \ K - 1, index_type>;\n\n        CompressedFenwickTreePrefix() = default;\n\n\
    \        void add_point(const point_type& p) {\n            comp.add(p[0]);\n\
    \            points.push_back(p);\n        }\n        void build() {\n       \
    \     data.assign(n = comp.build(), data_type{});\n            for (const auto&\
    \ p : points) for (int k = comp(p[0]) + 1; k <= n; k += k & -k) {\n          \
    \      data[k - 1].add_point(tail(p));\n            }\n            points.clear();\n\
    \            points.shrink_to_fit();\n            for (auto& t : data) t.build();\n\
    \        }\n\n        value_type prefix_query(const point_type& p) const {\n \
    \           value_type res = e();\n            for (int r = comp(p[0]); r; r -=\
    \ r & -r) res = op(res, data[r - 1].prefix_query(tail(p)));\n            return\
    \ res;\n        }\n        void apply(const point_type& p, const value_type& val)\
    \ {\n            for (int r = comp(p[0]) + 1; r <= n; r += r & -r) data[r - 1].apply(tail(p),\
    \ val);\n        }\n    private:\n        int n;\n        internal::compressed_fenwick_tree_prefix::Compressor<index_type>\
    \ comp;\n        std::vector<point_type> points;\n        std::vector<data_type>\
    \ data;\n\n        static constexpr auto tail(const point_type& p) {\n       \
    \     return tail_impl(p, std::make_index_sequence<K - 1>{});\n        }\n   \
    \     template <std::size_t... Seq>\n        static constexpr auto tail_impl(const\
    \ point_type& p, std::index_sequence<Seq...>) {\n            return typename data_type::point_type{\
    \ p[1 + Seq]... };\n        }\n    };\n    template <typename T, T(*op)(T, T),\
    \ T(*e)(), typename Index>\n    struct CompressedFenwickTreePrefix<T, op, e, std::size_t(1),\
    \ Index> {\n        using value_type = T;\n        using index_type = Index;\n\
    \        using point_type = index_type;\n        using data_type = value_type;\n\
    \n        CompressedFenwickTreePrefix() = default;\n\n        void add_point(const\
    \ point_type& p) { comp.add(p); }\n        void build() { data.assign(n = comp.build(),\
    \ e()); }\n\n        value_type prefix_query(const point_type& p) const {\n  \
    \          value_type res = e();\n            for (int r = comp(p); r; r -= r\
    \ & -r) res = op(res, data[r - 1]);\n            return res;\n        }\n    \
    \    void apply(const point_type& p, const value_type& val) {\n            for\
    \ (int r = comp(p) + 1; r <= n; r += r & -r) data[r - 1] = op(data[r - 1], val);\n\
    \        }\n    private:\n        int n;\n        internal::compressed_fenwick_tree_prefix::Compressor<index_type>\
    \ comp;\n        std::vector<data_type> data;\n    };\n} // namespace suisen\n\
    \n\n\n#line 4 \"test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp\"\
    \n\n#include <iostream>\n#include <limits>\n \nlong long op(long long x, long\
    \ long y) {\n    return std::max(x, y);\n}\nlong long e() {\n    return std::numeric_limits<long\
    \ long>::min() / 2;\n}\n \nusing PrefixMaxQuery3D = suisen::CompressedFenwickTreePrefix<long\
    \ long, op, e, 3>;\n \nint main() {\n    \n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n \n    int n;\n    std::cin >> n;\n \n    std::vector<std::tuple<int,\
    \ int, int, int>> ps(n);\n    for (int i = 0; i < n; ++i) {\n        int t, x,\
    \ y, a;\n        std::cin >> t >> x >> y >> a;\n        ps[i] = { y, t - y + x,\
    \ t - y - x, a };\n    }\n    std::sort(ps.begin(), ps.end());\n \n    PrefixMaxQuery3D\
    \ ft;\n    ft.add_point({ 0, 0, 0 });\n    for (auto [x, y, z, val] : ps) {\n\
    \        ft.add_point({ x, y, z });\n    }\n    ft.build();\n \n    ft.apply({\
    \ 0, 0, 0 }, 0);\n    long long ans = 0;\n    for (auto [x, y, z, val] : ps) {\n\
    \        long long p = ft.prefix_query({ x + 1, y + 1, z + 1 });\n        ans\
    \ = std::max(ans, p + val);\n        ft.apply({ x, y, z }, p + val);\n    }\n\
    \ \n    std::cout << ans << std::endl;\n \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc266/tasks/abc266_Ex\"\n\n\
    #include \"library/datastructure/fenwick_tree/compressed_fenwick_tree_prefix.hpp\"\
    \n\n#include <iostream>\n#include <limits>\n \nlong long op(long long x, long\
    \ long y) {\n    return std::max(x, y);\n}\nlong long e() {\n    return std::numeric_limits<long\
    \ long>::min() / 2;\n}\n \nusing PrefixMaxQuery3D = suisen::CompressedFenwickTreePrefix<long\
    \ long, op, e, 3>;\n \nint main() {\n    \n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n \n    int n;\n    std::cin >> n;\n \n    std::vector<std::tuple<int,\
    \ int, int, int>> ps(n);\n    for (int i = 0; i < n; ++i) {\n        int t, x,\
    \ y, a;\n        std::cin >> t >> x >> y >> a;\n        ps[i] = { y, t - y + x,\
    \ t - y - x, a };\n    }\n    std::sort(ps.begin(), ps.end());\n \n    PrefixMaxQuery3D\
    \ ft;\n    ft.add_point({ 0, 0, 0 });\n    for (auto [x, y, z, val] : ps) {\n\
    \        ft.add_point({ x, y, z });\n    }\n    ft.build();\n \n    ft.apply({\
    \ 0, 0, 0 }, 0);\n    long long ans = 0;\n    for (auto [x, y, z, val] : ps) {\n\
    \        long long p = ft.prefix_query({ x + 1, y + 1, z + 1 });\n        ans\
    \ = std::max(ans, p + val);\n        ft.apply({ x, y, z }, p + val);\n    }\n\
    \ \n    std::cout << ans << std::endl;\n \n    return 0;\n}"
  dependsOn:
  - library/datastructure/fenwick_tree/compressed_fenwick_tree_prefix.hpp
  isVerificationFile: true
  path: test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp
  requiredBy: []
  timestamp: '2022-10-31 00:31:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp
- /verify/test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp.html
title: test/src/datastructure/fenwick_tree/compressed_fenwick_tree_prefix/abc266_h.test.cpp
---
