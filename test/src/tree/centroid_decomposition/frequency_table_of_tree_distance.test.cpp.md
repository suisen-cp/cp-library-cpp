---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/centroid_decomposition.hpp
    title: library/tree/centroid_decomposition.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes: {}
  bundledCode: "#line 1 \"test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include <iostream>\n#include <queue>\n#include <atcoder/convolution>\n\n\
    #line 1 \"library/tree/centroid_decomposition.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n\n    struct CentroidDecomposition : public std::vector<std::vector<int>>\
    \ {\n        using BaseType = std::vector<std::vector<int>>;\n    public:\n  \
    \      using BaseType::BaseType;\n\n        void add_edge(int u, int v) {\n  \
    \          BaseType::operator[](u).push_back(v);\n            BaseType::operator[](v).push_back(u);\n\
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
    \ suisen\n\n\n#line 8 \"test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp\"\
    \nusing suisen::CentroidDecomposition;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    size_t n;\n    std::cin >> n;\n    CentroidDecomposition\
    \ g(n);\n    for (size_t i = 0; i < n - 1; ++i) {\n        size_t u, v;\n    \
    \    std::cin >> u >> v;\n        g.add_edge(u, v);\n    }\n\n    std::vector<long\
    \ long> ans(n, 0);\n\n    auto f = [&](const size_t c, const size_t) {\n     \
    \   std::vector<long long> sum { 1 };\n        for (size_t r : g[c]) {\n     \
    \       std::vector<long long> d(g.component_size(r) + 1, 0);\n            auto\
    \ dfs = [&](auto dfs, size_t u, size_t p, size_t dep) -> void {\n            \
    \    ++d[dep];\n                for (size_t v : g[u]) {\n                    if\
    \ (v == p) continue;\n                    dfs(dfs, v, u, dep + 1);\n         \
    \       }\n            };\n            dfs(dfs, r, c, 1);\n            while (d.size()\
    \ and d.back() == 0) d.pop_back();\n            auto dmap = atcoder::convolution_ll(sum,\
    \ d);\n            for (size_t i = 0; i < dmap.size(); ++i) {\n              \
    \  ans[i] += dmap[i];\n            }\n            if (sum.size() < d.size()) sum.swap(d);\n\
    \            for (size_t i = 0; i < d.size(); ++i) {\n                sum[i] +=\
    \ d[i];\n            }\n        }\n    };\n    g.decomp(CentroidDecomposition::dummy,\
    \ f);\n\n    for (size_t d = 1; d < n; ++d) {\n        std::cout << ans[d] <<\
    \ \" \\n\"[d == n - 1];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include <iostream>\n#include <queue>\n#include <atcoder/convolution>\n\n\
    #include \"library/tree/centroid_decomposition.hpp\"\nusing suisen::CentroidDecomposition;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    size_t n;\n    std::cin >> n;\n    CentroidDecomposition g(n);\n    for\
    \ (size_t i = 0; i < n - 1; ++i) {\n        size_t u, v;\n        std::cin >>\
    \ u >> v;\n        g.add_edge(u, v);\n    }\n\n    std::vector<long long> ans(n,\
    \ 0);\n\n    auto f = [&](const size_t c, const size_t) {\n        std::vector<long\
    \ long> sum { 1 };\n        for (size_t r : g[c]) {\n            std::vector<long\
    \ long> d(g.component_size(r) + 1, 0);\n            auto dfs = [&](auto dfs, size_t\
    \ u, size_t p, size_t dep) -> void {\n                ++d[dep];\n            \
    \    for (size_t v : g[u]) {\n                    if (v == p) continue;\n    \
    \                dfs(dfs, v, u, dep + 1);\n                }\n            };\n\
    \            dfs(dfs, r, c, 1);\n            while (d.size() and d.back() == 0)\
    \ d.pop_back();\n            auto dmap = atcoder::convolution_ll(sum, d);\n  \
    \          for (size_t i = 0; i < dmap.size(); ++i) {\n                ans[i]\
    \ += dmap[i];\n            }\n            if (sum.size() < d.size()) sum.swap(d);\n\
    \            for (size_t i = 0; i < d.size(); ++i) {\n                sum[i] +=\
    \ d[i];\n            }\n        }\n    };\n    g.decomp(CentroidDecomposition::dummy,\
    \ f);\n\n    for (size_t d = 1; d < n; ++d) {\n        std::cout << ans[d] <<\
    \ \" \\n\"[d == n - 1];\n    }\n    return 0;\n}"
  dependsOn:
  - library/tree/centroid_decomposition.hpp
  isVerificationFile: true
  path: test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp
  requiredBy: []
  timestamp: '2021-11-23 20:31:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp
- /verify/test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp.html
title: test/src/tree/centroid_decomposition/frequency_table_of_tree_distance.test.cpp
---
