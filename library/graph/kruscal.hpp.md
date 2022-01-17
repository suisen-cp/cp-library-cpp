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
  bundledCode: "#line 1 \"library/graph/kruscal.hpp\"\n\n\n\n#include <queue>\n#include\
    \ <atcoder/dsu>\n\nnamespace suisen {\n// Cost: a type represents weights of edges\
    \ i.e. (unsigned) int, (unsigned) long long, ...\ntemplate <typename Cost>\nclass\
    \ minimum_spanning_tree {\n    public:\n        using edge = std::tuple<Cost,\
    \ int, int>;\n        minimum_spanning_tree(const int n) : _n(n), _m(0) {}\n \
    \       minimum_spanning_tree(const int n, const int edge_num) : _n(n), _m(edge_num)\
    \ {\n            edges.reserve(edge_num);\n        }\n        void add_edge(const\
    \ int u, const int v, const Cost cost) {\n            edges.emplace_back(cost,\
    \ u, v);\n        }\n        void add_edge(const edge &e) {\n            edges.push_back(e);\n\
    \        }\n        /**\n         * constructs the MST in O(ElogE) time using\
    \ Kruskal's algprithm (E is the number of edges).\n         * return: whether\
    \ there exists MST or not (i.e. the graph is connected or not)\n         */\n\
    \        bool build() {\n            _weight_sum = 0;\n            if (_n == 0)\
    \ {\n                edges.clear();\n                return true;\n          \
    \  }\n            atcoder::dsu uf(_n);\n            std::sort(edges.begin(), edges.end());\n\
    \            for (int i = 0; i < edges.size(); ++i) {\n                auto &[w,\
    \ u, v] = edges[i];\n                if (uf.same(u, v)) {\n                  \
    \  u = v = _n;\n                } else {\n                    uf.merge(u, v);\n\
    \                    _weight_sum += w;\n                }\n            }\n   \
    \         edges.erase(\n                std::remove_if(\n                    edges.begin(),\
    \ edges.end(), [this](auto &e) { return std::get<1>(e) == _n; }\n            \
    \    ), edges.end()\n            );\n            return edges.size() == _n - 1;\n\
    \        }\n        /**\n         * ! This must not be called before calling `solve()`.\n\
    \         * return:\n         * 1. connected: sum of weights of edges in the minimum\
    \ spanning tree\n         * 2. otherwise: sum of weights of edges in the minimum\
    \ spanning forest\n         */\n        Cost get_minimum_weight() const {\n  \
    \          return _weight_sum;\n        }\n        /**\n         * ! This must\
    \ not be called before calling `solve()`.\n         * return:\n         * 1. connected:\
    \ edges in the minimum spanning tree\n         * 2. otherwise: edges in the minimum\
    \ spanning forest\n         * It is guaranteed that edges[i] <= edges[j] iff i\
    \ <= j.\n         */\n        const std::vector<edge>& get_mst() const {\n   \
    \         return edges;\n        }\n    private:\n        const int _n, _m;\n\
    \        std::vector<edge> edges;\n        Cost _weight_sum;\n};\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_KRUSCAL\n#define SUISEN_KRUSCAL\n\n#include <queue>\n#include\
    \ <atcoder/dsu>\n\nnamespace suisen {\n// Cost: a type represents weights of edges\
    \ i.e. (unsigned) int, (unsigned) long long, ...\ntemplate <typename Cost>\nclass\
    \ minimum_spanning_tree {\n    public:\n        using edge = std::tuple<Cost,\
    \ int, int>;\n        minimum_spanning_tree(const int n) : _n(n), _m(0) {}\n \
    \       minimum_spanning_tree(const int n, const int edge_num) : _n(n), _m(edge_num)\
    \ {\n            edges.reserve(edge_num);\n        }\n        void add_edge(const\
    \ int u, const int v, const Cost cost) {\n            edges.emplace_back(cost,\
    \ u, v);\n        }\n        void add_edge(const edge &e) {\n            edges.push_back(e);\n\
    \        }\n        /**\n         * constructs the MST in O(ElogE) time using\
    \ Kruskal's algprithm (E is the number of edges).\n         * return: whether\
    \ there exists MST or not (i.e. the graph is connected or not)\n         */\n\
    \        bool build() {\n            _weight_sum = 0;\n            if (_n == 0)\
    \ {\n                edges.clear();\n                return true;\n          \
    \  }\n            atcoder::dsu uf(_n);\n            std::sort(edges.begin(), edges.end());\n\
    \            for (int i = 0; i < edges.size(); ++i) {\n                auto &[w,\
    \ u, v] = edges[i];\n                if (uf.same(u, v)) {\n                  \
    \  u = v = _n;\n                } else {\n                    uf.merge(u, v);\n\
    \                    _weight_sum += w;\n                }\n            }\n   \
    \         edges.erase(\n                std::remove_if(\n                    edges.begin(),\
    \ edges.end(), [this](auto &e) { return std::get<1>(e) == _n; }\n            \
    \    ), edges.end()\n            );\n            return edges.size() == _n - 1;\n\
    \        }\n        /**\n         * ! This must not be called before calling `solve()`.\n\
    \         * return:\n         * 1. connected: sum of weights of edges in the minimum\
    \ spanning tree\n         * 2. otherwise: sum of weights of edges in the minimum\
    \ spanning forest\n         */\n        Cost get_minimum_weight() const {\n  \
    \          return _weight_sum;\n        }\n        /**\n         * ! This must\
    \ not be called before calling `solve()`.\n         * return:\n         * 1. connected:\
    \ edges in the minimum spanning tree\n         * 2. otherwise: edges in the minimum\
    \ spanning forest\n         * It is guaranteed that edges[i] <= edges[j] iff i\
    \ <= j.\n         */\n        const std::vector<edge>& get_mst() const {\n   \
    \         return edges;\n        }\n    private:\n        const int _n, _m;\n\
    \        std::vector<edge> edges;\n        Cost _weight_sum;\n};\n} // namespace\
    \ suisen\n\n#endif // SUISEN_KRUSCAL"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/kruscal.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/kruscal.hpp
layout: document
title: Kruscal
---
## Kruscal