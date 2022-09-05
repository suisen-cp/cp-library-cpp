---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace\
    \ suisen {\n    namespace internal::compressed_fenwick_tree {\n        template\
    \ <typename T>\n        struct Compressor {\n            using value_type = T;\n\
    \            Compressor() = default;\n            void add(const value_type& x)\
    \ { xs.push_back(x); }\n            int build() {\n                std::sort(xs.begin(),\
    \ xs.end());\n                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\
    \                return xs.size();\n            }\n            int operator()(const\
    \ value_type& x) const { return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();\
    \ }\n        private:\n            std::vector<value_type> xs;\n        };\n \
    \   }\n\n    template <typename T, T(*op)(T, T), T(*e)(), T(*inv)(T), std::size_t\
    \ K = 1, typename Index = int>\n    struct CompressedFenwickTree {\n        using\
    \ value_type = T;\n        using index_type = Index;\n        using point_type\
    \ = std::array<index_type, K>;\n        using cube_type = std::array<std::pair<index_type,\
    \ index_type>, K>;\n        using data_type = CompressedFenwickTree<value_type,\
    \ op, e, inv, K - 1, index_type>;\n\n        CompressedFenwickTree() = default;\n\
    \n        void add_point(const point_type& p) {\n            comp.add(p[0]);\n\
    \            points.push_back(p);\n        }\n        void build() {\n       \
    \     data.assign(n = comp.build(), data_type{});\n            for (const auto&\
    \ p : points) for (int k = comp(p[0]) + 1; k; k -= k & -k) {\n               \
    \ data[k - 1].add_point(tail(p));\n            }\n            points.clear();\n\
    \            points.shrink_to_fit();\n            for (auto& t : data) t.build();\n\
    \        }\n\n        value_type query(const cube_type& p) const {\n         \
    \   return op(query(p[0].second, tail(p)), inv(query(p[0].first, tail(p))));\n\
    \        }\n        void apply(const point_type& p, const value_type& val) {\n\
    \            for (int r = comp(p[0]) + 1; r <= n; r += r & -r) data[r - 1].apply(tail(p),\
    \ val);\n        }\n    private:\n        int n;\n        internal::compressed_fenwick_tree::Compressor<index_type>\
    \ comp;\n        std::vector<point_type> points;\n        std::vector<data_type>\
    \ data;\n\n        value_type query(const index_type& head_r, const typename data_type::cube_type&\
    \ p) const {\n            value_type res = e();\n            for (int r = comp(head_r);\
    \ r; r -= r & -r) res = op(res, data[r - 1].query(p));\n            return res;\n\
    \        }\n\n        template <typename X>\n        static constexpr auto tail(const\
    \ X& p) {\n            return tail_impl(p, std::make_index_sequence<K - 1>{});\n\
    \        }\n        template <typename X, std::size_t... Seq>\n        static\
    \ constexpr auto tail_impl(const X& p, std::index_sequence<Seq...>) {\n      \
    \      if constexpr (std::is_same_v<X, point_type>) {\n                return\
    \ typename data_type::point_type{ p[1 + Seq]... };\n            } else if constexpr\
    \ (std::is_same_v<X, cube_type>) {\n                return typename data_type::cube_type{\
    \ p[1 + Seq]... };\n            }\n        }\n    };\n    template <typename T,\
    \ T(*op)(T, T), T(*e)(), T(*inv)(T), typename Index>\n    struct CompressedFenwickTree<T,\
    \ op, e, inv, std::size_t(1), Index> {\n        using value_type = T;\n      \
    \  using index_type = Index;\n        using point_type = index_type;\n       \
    \ using cube_type = std::pair<index_type, index_type>;\n        using data_type\
    \ = value_type;\n\n        CompressedFenwickTree() = default;\n\n        void\
    \ add_point(const point_type& p) { comp.add(p); }\n        void build() { data.assign(n\
    \ = comp.build(), e()); }\n\n        value_type query(const index_type& l, const\
    \ index_type& r) const {\n            return op(query(r), inv(query(l)));\n  \
    \      }\n        value_type query(const cube_type& p) const {\n            return\
    \ query(p.first, p.second);\n        }\n\n        void apply(const point_type&\
    \ p, const value_type& val) {\n            for (int r = comp(p) + 1; r <= n; r\
    \ += r & -r) data[r - 1] = op(data[r - 1], val);\n        }\n    private:\n  \
    \      int n;\n        internal::compressed_fenwick_tree::Compressor<index_type>\
    \ comp;\n        std::vector<data_type> data;\n\n        value_type query(const\
    \ point_type& p) const {\n            value_type res = e();\n            for (int\
    \ r = comp(p); r; r -= r & -r) res = op(res, data[r - 1]);\n            return\
    \ res;\n        }\n\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_COMPRESSED_FENWICK_TREE\n#define SUISEN_COMPRESSED_FENWICK_TREE\n\
    \n#include <algorithm>\n#include <array>\n#include <vector>\n\nnamespace suisen\
    \ {\n    namespace internal::compressed_fenwick_tree {\n        template <typename\
    \ T>\n        struct Compressor {\n            using value_type = T;\n       \
    \     Compressor() = default;\n            void add(const value_type& x) { xs.push_back(x);\
    \ }\n            int build() {\n                std::sort(xs.begin(), xs.end());\n\
    \                xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n    \
    \            return xs.size();\n            }\n            int operator()(const\
    \ value_type& x) const { return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();\
    \ }\n        private:\n            std::vector<value_type> xs;\n        };\n \
    \   }\n\n    template <typename T, T(*op)(T, T), T(*e)(), T(*inv)(T), std::size_t\
    \ K = 1, typename Index = int>\n    struct CompressedFenwickTree {\n        using\
    \ value_type = T;\n        using index_type = Index;\n        using point_type\
    \ = std::array<index_type, K>;\n        using cube_type = std::array<std::pair<index_type,\
    \ index_type>, K>;\n        using data_type = CompressedFenwickTree<value_type,\
    \ op, e, inv, K - 1, index_type>;\n\n        CompressedFenwickTree() = default;\n\
    \n        void add_point(const point_type& p) {\n            comp.add(p[0]);\n\
    \            points.push_back(p);\n        }\n        void build() {\n       \
    \     data.assign(n = comp.build(), data_type{});\n            for (const auto&\
    \ p : points) for (int k = comp(p[0]) + 1; k; k -= k & -k) {\n               \
    \ data[k - 1].add_point(tail(p));\n            }\n            points.clear();\n\
    \            points.shrink_to_fit();\n            for (auto& t : data) t.build();\n\
    \        }\n\n        value_type query(const cube_type& p) const {\n         \
    \   return op(query(p[0].second, tail(p)), inv(query(p[0].first, tail(p))));\n\
    \        }\n        void apply(const point_type& p, const value_type& val) {\n\
    \            for (int r = comp(p[0]) + 1; r <= n; r += r & -r) data[r - 1].apply(tail(p),\
    \ val);\n        }\n    private:\n        int n;\n        internal::compressed_fenwick_tree::Compressor<index_type>\
    \ comp;\n        std::vector<point_type> points;\n        std::vector<data_type>\
    \ data;\n\n        value_type query(const index_type& head_r, const typename data_type::cube_type&\
    \ p) const {\n            value_type res = e();\n            for (int r = comp(head_r);\
    \ r; r -= r & -r) res = op(res, data[r - 1].query(p));\n            return res;\n\
    \        }\n\n        template <typename X>\n        static constexpr auto tail(const\
    \ X& p) {\n            return tail_impl(p, std::make_index_sequence<K - 1>{});\n\
    \        }\n        template <typename X, std::size_t... Seq>\n        static\
    \ constexpr auto tail_impl(const X& p, std::index_sequence<Seq...>) {\n      \
    \      if constexpr (std::is_same_v<X, point_type>) {\n                return\
    \ typename data_type::point_type{ p[1 + Seq]... };\n            } else if constexpr\
    \ (std::is_same_v<X, cube_type>) {\n                return typename data_type::cube_type{\
    \ p[1 + Seq]... };\n            }\n        }\n    };\n    template <typename T,\
    \ T(*op)(T, T), T(*e)(), T(*inv)(T), typename Index>\n    struct CompressedFenwickTree<T,\
    \ op, e, inv, std::size_t(1), Index> {\n        using value_type = T;\n      \
    \  using index_type = Index;\n        using point_type = index_type;\n       \
    \ using cube_type = std::pair<index_type, index_type>;\n        using data_type\
    \ = value_type;\n\n        CompressedFenwickTree() = default;\n\n        void\
    \ add_point(const point_type& p) { comp.add(p); }\n        void build() { data.assign(n\
    \ = comp.build(), e()); }\n\n        value_type query(const index_type& l, const\
    \ index_type& r) const {\n            return op(query(r), inv(query(l)));\n  \
    \      }\n        value_type query(const cube_type& p) const {\n            return\
    \ query(p.first, p.second);\n        }\n\n        void apply(const point_type&\
    \ p, const value_type& val) {\n            for (int r = comp(p) + 1; r <= n; r\
    \ += r & -r) data[r - 1] = op(data[r - 1], val);\n        }\n    private:\n  \
    \      int n;\n        internal::compressed_fenwick_tree::Compressor<index_type>\
    \ comp;\n        std::vector<data_type> data;\n\n        value_type query(const\
    \ point_type& p) const {\n            value_type res = e();\n            for (int\
    \ r = comp(p); r; r -= r & -r) res = op(res, data[r - 1]);\n            return\
    \ res;\n        }\n\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_COMPRESSED_FENWICK_TREE"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp
  requiredBy: []
  timestamp: '2022-09-05 23:58:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp
- /library/library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp.html
title: library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp
---
