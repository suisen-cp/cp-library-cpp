---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/compressed_segment_tree.hpp
    title: "\u4EFB\u610F\u6B21\u5143 Segment Tree"
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
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc266/tasks/abc266_Ex\"\n\n#line\
    \ 1 \"library/datastructure/segment_tree/compressed_segment_tree.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace suisen\
    \ {\n    namespace internal::compressed_segment_tree {\n        template <typename\
    \ T>\n        struct Compressor {\n            using value_type = T;\n       \
    \     Compressor() = default;\n            void add(const value_type& x) { xs.push_back(x);\
    \ }\n            int build() {\n                std::sort(xs.begin(), xs.end());\n\
    \                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n    \
    \            return xs.size();\n            }\n            int operator()(const\
    \ value_type& x) const { return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();\
    \ }\n        private:\n            std::vector<value_type> xs;\n        };\n \
    \   }\n\n    template <typename T, T(*op)(T, T), T(*e)(), std::size_t K = 1, typename\
    \ Index = int>\n    struct CompressedSegmentTree {\n        using value_type =\
    \ T;\n        using index_type = Index;\n        using point_type = std::array<index_type,\
    \ K>;\n        using cube_type = std::array<std::pair<index_type, index_type>,\
    \ K>;\n        using data_type = CompressedSegmentTree<value_type, op, e, K -\
    \ 1, index_type>;\n\n        CompressedSegmentTree() = default;\n\n        void\
    \ add_point(const point_type& p) {\n            comp.add(p[0]);\n            points.push_back(p);\n\
    \        }\n        void build() {\n            n = comp.build();\n          \
    \  data.assign(2 * n, data_type{});\n            for (const auto& p : points)\
    \ for (int k = n + comp(p[0]); k; k >>= 1) {\n                data[k].add_point(tail(p));\n\
    \            }\n            points.clear();\n            points.shrink_to_fit();\n\
    \            for (auto& t : data) t.build();\n        }\n\n        value_type\
    \ query(const cube_type& p) const {\n            value_type sml = e(), smr = e();\n\
    \            int l = comp(p[0].first) + n, r = comp(p[0].second) + n;\n      \
    \      for (; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) sml = op(sml,\
    \ data[l++].query(tail(p)));\n                if (r & 1) smr = op(data[--r].query(tail(p)),\
    \ smr);\n            }\n            return op(sml, smr);\n        }\n        value_type\
    \ get(const point_type& p) const {\n            return data[comp(p[0]) + n].get(tail(p));\n\
    \        }\n        void set(const point_type& p, const value_type& val) {\n \
    \           for (int i = comp(p[0]) + n; i; i >>= 1) data[i].set(tail(p), val);\n\
    \        }\n        void apply(const point_type& p, const value_type& val) {\n\
    \            for (int i = comp(p[0]) + n; i; i >>= 1) data[i].apply(tail(p), val);\n\
    \        }\n    private:\n        int n;\n        internal::compressed_segment_tree::Compressor<index_type>\
    \ comp;\n        std::vector<point_type> points;\n        std::vector<data_type>\
    \ data;\n\n        template <typename X>\n        static constexpr auto tail(const\
    \ X& p) {\n            return tail_impl(p, std::make_index_sequence<K - 1>{});\n\
    \        }\n        template <typename X, std::size_t... Seq>\n        static\
    \ constexpr auto tail_impl(const X& p, std::index_sequence<Seq...>) {\n      \
    \      return std::conditional_t<std::is_same_v<X, point_type>, typename data_type::point_type,\
    \ typename data_type::cube_type>{ p[1 + Seq]... };\n        }\n    };\n    template\
    \ <typename T, T(*op)(T, T), T(*e)(), typename Index>\n    struct CompressedSegmentTree<T,\
    \ op, e, std::size_t(1), Index> {\n        using value_type = T;\n        using\
    \ index_type = Index;\n        using point_type = index_type;\n        using cube_type\
    \ = std::pair<index_type, index_type>;\n        using data_type = value_type;\n\
    \n        CompressedSegmentTree() = default;\n\n        void add_point(const point_type&\
    \ p) { comp.add(p); }\n        void build() {\n            n = comp.build();\n\
    \            data.assign(2 * n, e());\n        }\n\n        value_type query(const\
    \ index_type& l, const index_type& r) const {\n            return query({ l, r\
    \ });\n        }\n        value_type query(const cube_type& p) const {\n     \
    \       value_type sml = e(), smr = e();\n            int l = comp(p.first) +\
    \ n, r = comp(p.second) + n;\n            for (; l < r; l >>= 1, r >>= 1) {\n\
    \                if (l & 1) sml = op(sml, data[l++]);\n                if (r &\
    \ 1) smr = op(data[--r], smr);\n            }\n            return op(sml, smr);\n\
    \        }\n        value_type get(const point_type &i) const {\n            return\
    \ data[comp(i) + n];\n        }\n\n        void set(const point_type& p, const\
    \ value_type& val) {\n            int i = comp(p) + n;\n            data[i] =\
    \ val;\n            while (i >>= 1) data[i] = op(data[2 * i + 0], data[2 * i +\
    \ 1]);\n        }\n        void apply(const point_type& p, const value_type& val)\
    \ {\n            for (int i = comp(p) + n; i; i >>= 1) data[i] = op(data[i], val);\n\
    \        }\n    private:\n        int n;\n        internal::compressed_segment_tree::Compressor<index_type>\
    \ comp;\n        std::vector<data_type> data;\n    };\n} // namespace suisen\n\
    \n\n\n#line 4 \"test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp\"\
    \n\n#include <iostream>\n#include <limits>\n \nlong long op(long long x, long\
    \ long y) {\n    return std::max(x, y);\n}\nlong long e() {\n    return std::numeric_limits<long\
    \ long>::min() / 2;\n}\n\nusing CubeMaxQuery = suisen::CompressedSegmentTree<long\
    \ long, op, e, 3>;\n\nconstexpr int inf = std::numeric_limits<int>::max() / 2;\n\
    \nint main() {\n    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \ \n    int n;\n    std::cin >> n;\n \n    std::vector<std::tuple<int, int, int,\
    \ int>> ps(n);\n    for (int i = 0; i < n; ++i) {\n        int t, x, y, a;\n \
    \       std::cin >> t >> x >> y >> a;\n        ps[i] = { y, t - y + x, t - y -\
    \ x, a };\n    }\n    std::sort(ps.begin(), ps.end());\n \n    CubeMaxQuery seg;\n\
    \    seg.add_point({ 0, 0, 0 });\n    for (auto [x, y, z, val] : ps) {\n     \
    \   seg.add_point({ x, y, z });\n    }\n    seg.build();\n \n    seg.set({ 0,\
    \ 0, 0 }, op(seg.get({ 0, 0, 0 }), 0));\n    long long ans = 0;\n    for (auto\
    \ [x, y, z, val] : ps) {\n        long long p = seg.query({ std::pair{ -inf, x\
    \ + 1 }, std::pair{ -inf, y + 1 }, std::pair{ -inf, z + 1 } });\n        ans =\
    \ std::max(ans, p + val);\n        seg.set({ x, y, z }, op(seg.get({ x, y, z }),\
    \ p + val));\n    }\n \n    std::cout << ans << std::endl;\n \n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc266/tasks/abc266_Ex\"\n\n\
    #include \"library/datastructure/segment_tree/compressed_segment_tree.hpp\"\n\n\
    #include <iostream>\n#include <limits>\n \nlong long op(long long x, long long\
    \ y) {\n    return std::max(x, y);\n}\nlong long e() {\n    return std::numeric_limits<long\
    \ long>::min() / 2;\n}\n\nusing CubeMaxQuery = suisen::CompressedSegmentTree<long\
    \ long, op, e, 3>;\n\nconstexpr int inf = std::numeric_limits<int>::max() / 2;\n\
    \nint main() {\n    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \ \n    int n;\n    std::cin >> n;\n \n    std::vector<std::tuple<int, int, int,\
    \ int>> ps(n);\n    for (int i = 0; i < n; ++i) {\n        int t, x, y, a;\n \
    \       std::cin >> t >> x >> y >> a;\n        ps[i] = { y, t - y + x, t - y -\
    \ x, a };\n    }\n    std::sort(ps.begin(), ps.end());\n \n    CubeMaxQuery seg;\n\
    \    seg.add_point({ 0, 0, 0 });\n    for (auto [x, y, z, val] : ps) {\n     \
    \   seg.add_point({ x, y, z });\n    }\n    seg.build();\n \n    seg.set({ 0,\
    \ 0, 0 }, op(seg.get({ 0, 0, 0 }), 0));\n    long long ans = 0;\n    for (auto\
    \ [x, y, z, val] : ps) {\n        long long p = seg.query({ std::pair{ -inf, x\
    \ + 1 }, std::pair{ -inf, y + 1 }, std::pair{ -inf, z + 1 } });\n        ans =\
    \ std::max(ans, p + val);\n        seg.set({ x, y, z }, op(seg.get({ x, y, z }),\
    \ p + val));\n    }\n \n    std::cout << ans << std::endl;\n \n    return 0;\n\
    }"
  dependsOn:
  - library/datastructure/segment_tree/compressed_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
  requiredBy: []
  timestamp: '2022-10-31 00:30:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
- /verify/test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp.html
title: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
---