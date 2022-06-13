---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/graph/manhattan_mst.hpp
    title: Manhattan Mst
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/manhattan_mst/manhattanmst.test.cpp
    title: test/src/graph/manhattan_mst/manhattanmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/kruscal.hpp\"\n\n\n\n#include <atcoder/dsu>\n\
    \nnamespace suisen {\n    namespace internal::kruscal {\n        // CostType:\
    \ a type represents weights of edges i.e. (unsigned) int, (unsigned) long long,\
    \ ...\n        template <typename CostType, typename ComparatorType>\n       \
    \ struct KruscalMST {\n            using cost_type = CostType;\n            using\
    \ edge_type = std::tuple<int, int, cost_type>;\n            using comparator_type\
    \ = ComparatorType;\n\n            KruscalMST() : KruscalMST(0) {}\n         \
    \   explicit KruscalMST(const int n) : _n(n) {}\n\n            void add_edge(const\
    \ int u, const int v, const cost_type& cost) {\n                _built = false;\n\
    \                _edges.emplace_back(u, v, cost);\n            }\n           \
    \ void add_edge(const edge_type& e) {\n                _built = false;\n     \
    \           _edges.push_back(e);\n            }\n            /**\n           \
    \  * constructs the MST in O(ElogE) time using Kruskal's algprithm (E is the number\
    \ of edges).\n             * return: whether there exists MST or not (i.e. the\
    \ graph is connected or not)\n             */\n            bool build() {\n  \
    \              _built = true;\n                _weight_sum = 0;\n            \
    \    if (_n == 0) return true;\n                atcoder::dsu uf(_n);\n       \
    \         std::sort(_edges.begin(), _edges.end(), [this](const auto& e1, const\
    \ auto& e2) { return _comp(std::get<2>(e1), std::get<2>(e2)); });\n          \
    \      for (auto& [u, v, w] : _edges) {\n                    if (uf.same(u, v))\
    \ {\n                        u = v = _n;\n                    } else {\n     \
    \                   uf.merge(u, v);\n                        _weight_sum += w;\n\
    \                    }\n                }\n                _edges.erase(std::remove_if(_edges.begin(),\
    \ _edges.end(), [this](auto& e) { return std::get<0>(e) == _n; }), _edges.end());\n\
    \                return int(_edges.size()) == _n - 1;\n            }\n       \
    \     /**\n             * ! This must not be called before calling `solve()`.\n\
    \             * return:\n             * 1. connected: sum of weights of edges\
    \ in the minimum spanning tree\n             * 2. otherwise: sum of weights of\
    \ edges in the minimum spanning forest\n             */\n            cost_type\
    \ get_weight() const {\n                assert(_built);\n                return\
    \ _weight_sum;\n            }\n            /**\n             * ! This must not\
    \ be called before calling `solve()`.\n             * return:\n             *\
    \ 1. connected: edges in the minimum spanning tree\n             * 2. otherwise:\
    \ edges in the minimum spanning forest\n             * It is guaranteed that edges[i]\
    \ <= edges[j] iff i <= j.\n             */\n            const std::vector<edge_type>&\
    \ get_mst() const {\n                assert(_built);\n                return _edges;\n\
    \            }\n        private:\n            int _n;\n            cost_type _weight_sum;\n\
    \            std::vector<edge_type> _edges;\n            bool _built = false;\n\
    \            comparator_type _comp{};\n        };\n    } // namespace internal::kruscal\n\
    \n    template <typename CostType>\n    using KruscalMinimumSpanningTree = internal::kruscal::KruscalMST<CostType,\
    \ std::less<CostType>>;\n    template <typename CostType>\n    using KruscalMaximumSpanningTree\
    \ = internal::kruscal::KruscalMST<CostType, std::greater<CostType>>;\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_KRUSCAL\n#define SUISEN_KRUSCAL\n\n#include <atcoder/dsu>\n\
    \nnamespace suisen {\n    namespace internal::kruscal {\n        // CostType:\
    \ a type represents weights of edges i.e. (unsigned) int, (unsigned) long long,\
    \ ...\n        template <typename CostType, typename ComparatorType>\n       \
    \ struct KruscalMST {\n            using cost_type = CostType;\n            using\
    \ edge_type = std::tuple<int, int, cost_type>;\n            using comparator_type\
    \ = ComparatorType;\n\n            KruscalMST() : KruscalMST(0) {}\n         \
    \   explicit KruscalMST(const int n) : _n(n) {}\n\n            void add_edge(const\
    \ int u, const int v, const cost_type& cost) {\n                _built = false;\n\
    \                _edges.emplace_back(u, v, cost);\n            }\n           \
    \ void add_edge(const edge_type& e) {\n                _built = false;\n     \
    \           _edges.push_back(e);\n            }\n            /**\n           \
    \  * constructs the MST in O(ElogE) time using Kruskal's algprithm (E is the number\
    \ of edges).\n             * return: whether there exists MST or not (i.e. the\
    \ graph is connected or not)\n             */\n            bool build() {\n  \
    \              _built = true;\n                _weight_sum = 0;\n            \
    \    if (_n == 0) return true;\n                atcoder::dsu uf(_n);\n       \
    \         std::sort(_edges.begin(), _edges.end(), [this](const auto& e1, const\
    \ auto& e2) { return _comp(std::get<2>(e1), std::get<2>(e2)); });\n          \
    \      for (auto& [u, v, w] : _edges) {\n                    if (uf.same(u, v))\
    \ {\n                        u = v = _n;\n                    } else {\n     \
    \                   uf.merge(u, v);\n                        _weight_sum += w;\n\
    \                    }\n                }\n                _edges.erase(std::remove_if(_edges.begin(),\
    \ _edges.end(), [this](auto& e) { return std::get<0>(e) == _n; }), _edges.end());\n\
    \                return int(_edges.size()) == _n - 1;\n            }\n       \
    \     /**\n             * ! This must not be called before calling `solve()`.\n\
    \             * return:\n             * 1. connected: sum of weights of edges\
    \ in the minimum spanning tree\n             * 2. otherwise: sum of weights of\
    \ edges in the minimum spanning forest\n             */\n            cost_type\
    \ get_weight() const {\n                assert(_built);\n                return\
    \ _weight_sum;\n            }\n            /**\n             * ! This must not\
    \ be called before calling `solve()`.\n             * return:\n             *\
    \ 1. connected: edges in the minimum spanning tree\n             * 2. otherwise:\
    \ edges in the minimum spanning forest\n             * It is guaranteed that edges[i]\
    \ <= edges[j] iff i <= j.\n             */\n            const std::vector<edge_type>&\
    \ get_mst() const {\n                assert(_built);\n                return _edges;\n\
    \            }\n        private:\n            int _n;\n            cost_type _weight_sum;\n\
    \            std::vector<edge_type> _edges;\n            bool _built = false;\n\
    \            comparator_type _comp{};\n        };\n    } // namespace internal::kruscal\n\
    \n    template <typename CostType>\n    using KruscalMinimumSpanningTree = internal::kruscal::KruscalMST<CostType,\
    \ std::less<CostType>>;\n    template <typename CostType>\n    using KruscalMaximumSpanningTree\
    \ = internal::kruscal::KruscalMST<CostType, std::greater<CostType>>;\n} // namespace\
    \ suisen\n\n#endif // SUISEN_KRUSCAL"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/kruscal.hpp
  requiredBy:
  - library/graph/manhattan_mst.hpp
  timestamp: '2022-06-14 00:04:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/manhattan_mst/manhattanmst.test.cpp
documentation_of: library/graph/kruscal.hpp
layout: document
title: Kruscal
---
## Kruscal