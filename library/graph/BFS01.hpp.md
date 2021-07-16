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
  bundledCode: "#line 1 \"library/graph/BFS01.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <map>\n#include <queue>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename\
    \ Cost, typename Node, typename Container>\nclass BFS01_base {\n    protected:\n\
    \        Container _dist;\n\n        virtual Cost get_dist(const Node &node) const\
    \ = 0;\n\n        template <typename Iterable, typename Graph>\n        auto bfs(const\
    \ Iterable &src_list, const Graph g) -> decltype(src_list.begin(), src_list.end(),\
    \ void()) {\n            std::deque<Node> dq;\n            for (auto &src : src_list)\
    \ {\n                dq.push_back(src);\n                _dist[src] = 0;\n   \
    \         }\n            while (dq.size()) {\n                Node u = dq.front();\
    \ dq.pop_front();\n                g(u, [&](const Node &v, const bool cost) {\n\
    \                    Cost old_dist = get_dist(v);\n                    Cost new_dist\
    \ = get_dist(u) + cost;\n                    if (new_dist < old_dist) {\n    \
    \                    _dist[v] = new_dist;\n                        if (cost) {\n\
    \                            dq.push_back(v);\n                        } else\
    \ {\n                            dq.push_front(v);\n                        }\n\
    \                    }\n                });\n            }\n        }\n    public:\n\
    \        static constexpr Cost INF = std::numeric_limits<Cost>::max();\n\n   \
    \     inline Cost operator[](const Node &node)   const { return get_dist(node);\
    \ }\n        inline bool is_reachable(const Node &node)   const { return get_dist(node)\
    \ != INF; }\n        inline bool is_unreachable(const Node &node) const { return\
    \ get_dist(node) == INF; }\n};\n\ntemplate <typename Cost, typename Node = unsigned\
    \ int, typename Container = std::vector<Cost>>\nclass BFS01 : public BFS01_base<Cost,\
    \ Node, Container> {\n    using base = BFS01_base<Cost, Node, Container>;\n  \
    \  public:\n        template <typename Graph>\n        BFS01(const Node n, const\
    \ Node src, const Graph g) : base::_dist(n, this->INF) { this->bfs(std::vector<Node>{src},\
    \ g); }\n        template <typename Iterable, typename Graph>\n        BFS01(const\
    \ Node n, const Iterable &src_list, const Graph g) : base::_dist(n, this->INF)\
    \ { this->bfs(src_list, g); }\n    protected:\n        inline Cost get_dist(const\
    \ Node &node) const override { return this->_dist[node]; }\n};\n\ntemplate <typename\
    \ Cost, typename Node>\nclass BFS01<Cost, Node, std::map<Node, Cost>> : public\
    \ BFS01_base<Cost, Node, std::map<Node, Cost>> {\n    public:\n        template\
    \ <typename Graph>\n        BFS01(const Node src, const Graph g) { this->bfs(std::vector<Node>{src},\
    \ g); }\n        template <typename Iterable, typename Graph>\n        BFS01(const\
    \ Iterable &src_list, const Graph g) { this->bfs(src_list, g); }\n    protected:\n\
    \        inline Cost get_dist(const Node &node) const override { return this->_dist.count(node)\
    \ ? this->_dist.at(node) : this->INF; }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BFS01\n#define SUISEN_BFS01\n\n#include <limits>\n#include\
    \ <map>\n#include <queue>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename\
    \ Cost, typename Node, typename Container>\nclass BFS01_base {\n    protected:\n\
    \        Container _dist;\n\n        virtual Cost get_dist(const Node &node) const\
    \ = 0;\n\n        template <typename Iterable, typename Graph>\n        auto bfs(const\
    \ Iterable &src_list, const Graph g) -> decltype(src_list.begin(), src_list.end(),\
    \ void()) {\n            std::deque<Node> dq;\n            for (auto &src : src_list)\
    \ {\n                dq.push_back(src);\n                _dist[src] = 0;\n   \
    \         }\n            while (dq.size()) {\n                Node u = dq.front();\
    \ dq.pop_front();\n                g(u, [&](const Node &v, const bool cost) {\n\
    \                    Cost old_dist = get_dist(v);\n                    Cost new_dist\
    \ = get_dist(u) + cost;\n                    if (new_dist < old_dist) {\n    \
    \                    _dist[v] = new_dist;\n                        if (cost) {\n\
    \                            dq.push_back(v);\n                        } else\
    \ {\n                            dq.push_front(v);\n                        }\n\
    \                    }\n                });\n            }\n        }\n    public:\n\
    \        static constexpr Cost INF = std::numeric_limits<Cost>::max();\n\n   \
    \     inline Cost operator[](const Node &node)   const { return get_dist(node);\
    \ }\n        inline bool is_reachable(const Node &node)   const { return get_dist(node)\
    \ != INF; }\n        inline bool is_unreachable(const Node &node) const { return\
    \ get_dist(node) == INF; }\n};\n\ntemplate <typename Cost, typename Node = unsigned\
    \ int, typename Container = std::vector<Cost>>\nclass BFS01 : public BFS01_base<Cost,\
    \ Node, Container> {\n    using base = BFS01_base<Cost, Node, Container>;\n  \
    \  public:\n        template <typename Graph>\n        BFS01(const Node n, const\
    \ Node src, const Graph g) : base::_dist(n, this->INF) { this->bfs(std::vector<Node>{src},\
    \ g); }\n        template <typename Iterable, typename Graph>\n        BFS01(const\
    \ Node n, const Iterable &src_list, const Graph g) : base::_dist(n, this->INF)\
    \ { this->bfs(src_list, g); }\n    protected:\n        inline Cost get_dist(const\
    \ Node &node) const override { return this->_dist[node]; }\n};\n\ntemplate <typename\
    \ Cost, typename Node>\nclass BFS01<Cost, Node, std::map<Node, Cost>> : public\
    \ BFS01_base<Cost, Node, std::map<Node, Cost>> {\n    public:\n        template\
    \ <typename Graph>\n        BFS01(const Node src, const Graph g) { this->bfs(std::vector<Node>{src},\
    \ g); }\n        template <typename Iterable, typename Graph>\n        BFS01(const\
    \ Iterable &src_list, const Graph g) { this->bfs(src_list, g); }\n    protected:\n\
    \        inline Cost get_dist(const Node &node) const override { return this->_dist.count(node)\
    \ ? this->_dist.at(node) : this->INF; }\n};\n} // namespace suisen\n\n#endif //\
    \ SUISEN_BFS01\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/BFS01.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/BFS01.hpp
layout: document
redirect_from:
- /library/library/graph/BFS01.hpp
- /library/library/graph/BFS01.hpp.html
title: library/graph/BFS01.hpp
---
