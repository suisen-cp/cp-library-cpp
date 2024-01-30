---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
    title: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h_2.test.cpp
    title: test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/compressed_segment_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace\
    \ suisen {\n    namespace internal::compressed_segment_tree {\n        template\
    \ <typename T>\n        struct Compressor {\n            using value_type = T;\n\
    \            Compressor() = default;\n            void add(const value_type& x)\
    \ { xs.push_back(x); }\n            int build() {\n                std::sort(xs.begin(),\
    \ xs.end());\n                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\
    \                return xs.size();\n            }\n            int operator()(const\
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
    \n\n\n"
  code: "#ifndef SUISEN_COMPRESSED_SEGMENT_TREE\n#define SUISEN_COMPRESSED_SEGMENT_TREE\n\
    \n#include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace suisen\
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
    \n\n#endif // SUISEN_COMPRESSED_SEGMENT_TREE"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/segment_tree/compressed_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-10-31 00:30:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h_2.test.cpp
  - test/src/datastructure/segment_tree/compressed_segment_tree/abc266_h.test.cpp
documentation_of: library/datastructure/segment_tree/compressed_segment_tree.hpp
layout: document
title: "\u4EFB\u610F\u6B21\u5143 Segment Tree"
---
## 任意次元 Segment Tree

空間 $O(q(\log q) ^ {d - 1})$、クエリ $O((\log q) ^ d)$ の $d$ 次元 Segment Tree。計算量は $d$ を定数とみなした場合である。クエリの定数倍として $2 ^ d$ が付くので注意 (prefix クエリの場合を除く)。
