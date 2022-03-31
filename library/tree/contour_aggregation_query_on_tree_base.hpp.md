---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/tree/contour_aggregation_query_on_tree.hpp
    title: Contour Aggregation Query On Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
    title: test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/contour_aggregation_query_on_tree_base.hpp\"\
    \n\n\n\n#include <deque>\n#include <map>\n#include <tuple>\n\n#line 1 \"library/tree/centroid_decomposition.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n\n    struct CentroidDecomposition\
    \ : public std::vector<std::vector<int>> {\n        using BaseType = std::vector<std::vector<int>>;\n\
    \    public:\n        using BaseType::BaseType;\n\n        void add_edge(int u,\
    \ int v) {\n            BaseType::operator[](u).push_back(v);\n            BaseType::operator[](v).push_back(u);\n\
    \        }\n\n    private:\n        std::vector<bool> removed;\n        std::vector<int>\
    \ sub;\n\n        struct AdjacentListIterator {\n            using it_t = std::vector<int>::const_iterator;\n\
    \            const CentroidDecomposition* const ptr;\n            const int u;\n\
    \            it_t it;\n            AdjacentListIterator(const CentroidDecomposition*\
    \ const ptr, int u, it_t it) : ptr(ptr), u(u), it(it) { suc(); }\n           \
    \ AdjacentListIterator& operator++() { return ++it, suc(), * this; }\n       \
    \     int operator*() { return *it; }\n            bool operator!=(const AdjacentListIterator&\
    \ other) { return it != other.it; }\n            void suc() { while (it != (*ptr).BaseType::operator[](u).end()\
    \ and ptr->removed[*it]) ++it; }\n        };\n        struct AdjacentList {\n\
    \            CentroidDecomposition* const ptr;\n            const int u;\n   \
    \         std::vector<int>& base_vector()& { return ptr->BaseType::operator[](u);\
    \ }\n            auto begin() const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin());\
    \ }\n            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end());\
    \ }\n        };\n        struct ConstAdjacentList {\n            const CentroidDecomposition*\
    \ const ptr;\n            const int u;\n            const std::vector<int>& base_vector()\
    \ const& { return ptr->BaseType::operator[](u); }\n            auto begin() const\
    \ { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin());\
    \ }\n            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end());\
    \ }\n        };\n\n    public:\n        static constexpr void dummy(int, int)\
    \ {}\n\n        // Returns the list of vertices adjacent to `u`. If called during\
    \ decomposition, it skips removed vertices.\n        auto operator[](int u) {\n\
    \            return AdjacentList{ this, u };\n        }\n        // Returns the\
    \ (constant) list of vertices adjacent to `u`. If called during decomposition,\
    \ it skips removed vertices.\n        auto operator[](int u) const {\n       \
    \     return ConstAdjacentList{ this, u };\n        }\n\n        // This method\
    \ is expected to be called in functions passed to the `decomp`.\n        // The\
    \ argument `root` must be directly connected to the current centroid. If not,\
    \ the returned value will be undefined.\n        int component_size(int root)\
    \ const {\n            return sub[root];\n        }\n\n        struct DecompositionTree\
    \ {\n            DecompositionTree() {}\n            DecompositionTree(int root,\
    \ const std::vector<int> &par) : n(par.size()), root(root), par(par) {}\n\n  \
    \          int size() const { return n; }\n            int get_root() const {\
    \ return root; }\n            int get_parent(int u) const { return par[u]; }\n\
    \            const std::vector<int>& parents() const { return par; }\n       \
    \ private:\n            int n;\n            int root;\n            std::vector<int>\
    \ par;\n        };\n\n        // returns the centroid decomposition tree\n   \
    \     template <typename DownF = decltype(dummy), typename UpF = decltype(dummy)>\n\
    \        DecompositionTree decomp(DownF down = dummy, UpF up = dummy) {\n    \
    \        removed.assign(size(), false);\n            sub.assign(size(), 0);\n\
    \            std::vector<int> par(size(), -1);\n            auto rec = [&](auto\
    \ rec, int r, int siz) -> int {\n                int c = -1;\n               \
    \ auto get_centroid = [&](auto get_centroid, int u, int p) -> void {\n       \
    \             sub[u] = 1;\n                    for (int v : (*this)[u]) {\n  \
    \                      if (v == p) continue;\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub[u]\
    \ = siz - sub[c];\n                            break;\n                      \
    \  }\n                        sub[u] += sub[v];\n                    }\n     \
    \               if (c < 0 and sub[u] * 2 > siz) c = u;\n                };\n \
    \               get_centroid(get_centroid, r, -1);\n                down(c, siz);\n\
    \                removed[c] = true;\n                for (int v : (*this)[c])\
    \ {\n                    const int comp_size = sub[v];\n                    par[rec(rec,\
    \ v, comp_size)] = c;\n                    sub[v] = comp_size;\n             \
    \   }\n                removed[c] = false;\n                up(c, siz);\n    \
    \            return c;\n            };\n            int root = rec(rec, 0, size());\n\
    \            return DecompositionTree(root, par);\n        }\n    };\n\n} // namespace\
    \ suisen\n\n\n#line 9 \"library/tree/contour_aggregation_query_on_tree_base.hpp\"\
    \n\nnamespace suisen {\n    template <typename SequenceType>\n    struct ContourAggregationQueryOnTreeBase\
    \ : private CentroidDecomposition {\n        using base_type = CentroidDecomposition;\n\
    \        using base_type::base_type;\n        using base_type::add_edge;\n\n \
    \       using sequence_type = SequenceType;\n\n        template <typename T>\n\
    \        void build(const std::vector<T>& dat) {\n            const int n = size(),\
    \ log_n = ceil_log2(n);\n            _seq_idx.resize(n, { 0 });\n            _sub_idx_dep.resize(n,\
    \ { { -1, 0 } });\n            _sep.resize(n, { 0 });\n            _range.resize(n);\n\
    \            _seq.resize(n);\n            for (int i = 0; i < n; ++i) _seq_idx[i].reserve(log_n),\
    \ _sub_idx_dep.reserve(log_n);\n            _tree = base_type::decomp(\n     \
    \           base_type::dummy,\n                [&](int centroid, int siz) {\n\
    \                    std::vector<T> seq_dat{ dat[centroid] };\n              \
    \      seq_dat.reserve(siz);\n                    if (siz > 1) {\n           \
    \             // (current vertex, parent vertex, component id, depth)\n      \
    \                  std::deque<std::tuple<int, int, int, int>> dq;\n          \
    \              int sub_root_num = 0;\n                        for (int sub_root\
    \ : (*this)[centroid]) dq.emplace_back(sub_root, centroid, sub_root_num++, 1);\n\
    \                        _range[centroid].resize(sub_root_num, { { 0, 0 } });\n\
    \                        while (dq.size()) {\n                            const\
    \ auto [u, p, id, dep] = dq.front();\n                            dq.pop_front();\n\
    \                            const int ord = seq_dat.size();\n               \
    \             if (int(_sep[centroid].size()) <= dep) _sep[centroid].push_back(ord);\n\
    \                            if (int(_range[centroid][id].size()) <= dep) _range[centroid][id].emplace_back(ord,\
    \ ord);\n                            ++_range[centroid][id].back().second;\n \
    \                           _sub_idx_dep[u].emplace_back(id, dep);\n         \
    \                   _seq_idx[u].push_back(ord);\n                            seq_dat.push_back(dat[u]);\n\
    \                            for (int v : (*this)[u]) if (v != p) dq.emplace_back(v,\
    \ u, id, dep + 1);\n                        }\n                    }\n       \
    \             _sep[centroid].push_back(siz);\n                    _seq[centroid]\
    \ = sequence_type(std::move(seq_dat));\n                }\n            );\n  \
    \      }\n\n        // getter(seq, i)\n        template <typename Getter>\n  \
    \      auto get(int u, Getter&& getter) {\n            return getter(_seq[u],\
    \ 0);\n        }\n        // setter(seq, i)\n        template <typename Setter>\n\
    \        void set(int u, Setter&& setter) {\n            for (int i : _seq_idx[u])\
    \ setter(_seq[std::exchange(u, _tree.get_parent(u))], i);\n        }\n       \
    \ // agg(seq, l, r)\n        template <typename Aggregator>\n        void prod(int\
    \ u, int d, Aggregator&& agg) {\n            for (auto [sub_idx, sub_dep] : _sub_idx_dep[u])\
    \ prod(std::exchange(u, _tree.get_parent(u)), d - sub_dep, sub_idx, agg);\n  \
    \      }\n\n    protected:\n        CentroidDecomposition::DecompositionTree _tree;\n\
    \n        std::vector<std::vector<int>> _seq_idx;\n        std::vector<std::vector<std::pair<int,\
    \ int>>> _sub_idx_dep;\n        std::vector<std::vector<int>> _sep;\n        std::vector<std::vector<std::vector<std::pair<int,\
    \ int>>>> _range;\n        std::vector<sequence_type> _seq;\n\n        template\
    \ <typename Aggregator>\n        void prod(int u, int d, int skip_index, Aggregator&&\
    \ agg) {\n            if (d < 0 or int(_sep[u].size()) <= d + 1) return;\n   \
    \         if (d == 0) {\n                agg(_seq[u], 0, 1);\n               \
    \ return;\n            }\n            int l = _sep[u][d], r = _sep[u][d + 1];\n\
    \            if (skip_index < 0 or int(_range[u][skip_index].size()) <= d) {\n\
    \                agg(_seq[u], l, r);\n            } else {\n                auto\
    \ [ml, mr] = _range[u][skip_index][d];\n                agg(_seq[u], l, ml), agg(_seq[u],\
    \ mr, r);\n            }\n        }\n\n        static int ceil_log2(int n) {\n\
    \            int res = 0;\n            while (1 << res < n) ++res;\n         \
    \   return res;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONTOUR_QUERY_ON_TREE_BASE\n#define SUISEN_CONTOUR_QUERY_ON_TREE_BASE\n\
    \n#include <deque>\n#include <map>\n#include <tuple>\n\n#include \"library/tree/centroid_decomposition.hpp\"\
    \n\nnamespace suisen {\n    template <typename SequenceType>\n    struct ContourAggregationQueryOnTreeBase\
    \ : private CentroidDecomposition {\n        using base_type = CentroidDecomposition;\n\
    \        using base_type::base_type;\n        using base_type::add_edge;\n\n \
    \       using sequence_type = SequenceType;\n\n        template <typename T>\n\
    \        void build(const std::vector<T>& dat) {\n            const int n = size(),\
    \ log_n = ceil_log2(n);\n            _seq_idx.resize(n, { 0 });\n            _sub_idx_dep.resize(n,\
    \ { { -1, 0 } });\n            _sep.resize(n, { 0 });\n            _range.resize(n);\n\
    \            _seq.resize(n);\n            for (int i = 0; i < n; ++i) _seq_idx[i].reserve(log_n),\
    \ _sub_idx_dep.reserve(log_n);\n            _tree = base_type::decomp(\n     \
    \           base_type::dummy,\n                [&](int centroid, int siz) {\n\
    \                    std::vector<T> seq_dat{ dat[centroid] };\n              \
    \      seq_dat.reserve(siz);\n                    if (siz > 1) {\n           \
    \             // (current vertex, parent vertex, component id, depth)\n      \
    \                  std::deque<std::tuple<int, int, int, int>> dq;\n          \
    \              int sub_root_num = 0;\n                        for (int sub_root\
    \ : (*this)[centroid]) dq.emplace_back(sub_root, centroid, sub_root_num++, 1);\n\
    \                        _range[centroid].resize(sub_root_num, { { 0, 0 } });\n\
    \                        while (dq.size()) {\n                            const\
    \ auto [u, p, id, dep] = dq.front();\n                            dq.pop_front();\n\
    \                            const int ord = seq_dat.size();\n               \
    \             if (int(_sep[centroid].size()) <= dep) _sep[centroid].push_back(ord);\n\
    \                            if (int(_range[centroid][id].size()) <= dep) _range[centroid][id].emplace_back(ord,\
    \ ord);\n                            ++_range[centroid][id].back().second;\n \
    \                           _sub_idx_dep[u].emplace_back(id, dep);\n         \
    \                   _seq_idx[u].push_back(ord);\n                            seq_dat.push_back(dat[u]);\n\
    \                            for (int v : (*this)[u]) if (v != p) dq.emplace_back(v,\
    \ u, id, dep + 1);\n                        }\n                    }\n       \
    \             _sep[centroid].push_back(siz);\n                    _seq[centroid]\
    \ = sequence_type(std::move(seq_dat));\n                }\n            );\n  \
    \      }\n\n        // getter(seq, i)\n        template <typename Getter>\n  \
    \      auto get(int u, Getter&& getter) {\n            return getter(_seq[u],\
    \ 0);\n        }\n        // setter(seq, i)\n        template <typename Setter>\n\
    \        void set(int u, Setter&& setter) {\n            for (int i : _seq_idx[u])\
    \ setter(_seq[std::exchange(u, _tree.get_parent(u))], i);\n        }\n       \
    \ // agg(seq, l, r)\n        template <typename Aggregator>\n        void prod(int\
    \ u, int d, Aggregator&& agg) {\n            for (auto [sub_idx, sub_dep] : _sub_idx_dep[u])\
    \ prod(std::exchange(u, _tree.get_parent(u)), d - sub_dep, sub_idx, agg);\n  \
    \      }\n\n    protected:\n        CentroidDecomposition::DecompositionTree _tree;\n\
    \n        std::vector<std::vector<int>> _seq_idx;\n        std::vector<std::vector<std::pair<int,\
    \ int>>> _sub_idx_dep;\n        std::vector<std::vector<int>> _sep;\n        std::vector<std::vector<std::vector<std::pair<int,\
    \ int>>>> _range;\n        std::vector<sequence_type> _seq;\n\n        template\
    \ <typename Aggregator>\n        void prod(int u, int d, int skip_index, Aggregator&&\
    \ agg) {\n            if (d < 0 or int(_sep[u].size()) <= d + 1) return;\n   \
    \         if (d == 0) {\n                agg(_seq[u], 0, 1);\n               \
    \ return;\n            }\n            int l = _sep[u][d], r = _sep[u][d + 1];\n\
    \            if (skip_index < 0 or int(_range[u][skip_index].size()) <= d) {\n\
    \                agg(_seq[u], l, r);\n            } else {\n                auto\
    \ [ml, mr] = _range[u][skip_index][d];\n                agg(_seq[u], l, ml), agg(_seq[u],\
    \ mr, r);\n            }\n        }\n\n        static int ceil_log2(int n) {\n\
    \            int res = 0;\n            while (1 << res < n) ++res;\n         \
    \   return res;\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_CONTOUR_QUERY_ON_TREE_BASE\n"
  dependsOn:
  - library/tree/centroid_decomposition.hpp
  isVerificationFile: false
  path: library/tree/contour_aggregation_query_on_tree_base.hpp
  requiredBy:
  - library/tree/contour_aggregation_query_on_tree.hpp
  timestamp: '2022-03-22 04:55:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
documentation_of: library/tree/contour_aggregation_query_on_tree_base.hpp
layout: document
title: Contour Aggregation Query On Tree Base
---
## Contour Aggregation Query On Tree Base