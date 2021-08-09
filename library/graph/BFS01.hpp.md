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
    \ Node, typename Container>\nclass BFS01_base {\n    protected:\n        Container\
    \ _dist;\n\n        template <typename ...Args>\n        BFS01_base(Args &&...args)\
    \ : _dist(std::forward<Args>(args)...) {}\n\n        virtual int get_dist(const\
    \ Node &node) const = 0;\n\n        template <typename Graph>\n        void bfs(const\
    \ std::vector<Node> &src_list, const Graph g) {\n            std::deque<Node>\
    \ dq;\n            for (auto &src : src_list) {\n                dq.push_back(src);\n\
    \                _dist[src] = 0;\n            }\n            while (dq.size())\
    \ {\n                Node u = dq.front(); dq.pop_front();\n                g(u,\
    \ [&](const Node &v, const bool cost) {\n                    int old_dist = get_dist(v);\n\
    \                    int new_dist = get_dist(u) + cost;\n                    if\
    \ (new_dist < old_dist) {\n                        _dist[v] = new_dist;\n    \
    \                    if (cost) {\n                            dq.push_back(v);\n\
    \                        } else {\n                            dq.push_front(v);\n\
    \                        }\n                    }\n                });\n     \
    \       }\n        }\n    public:\n        static constexpr int INF = std::numeric_limits<int>::max();\n\
    \n        int operator[](const Node &node)   const { return get_dist(node); }\n\
    \        bool is_reachable(const Node &node)   const { return get_dist(node) !=\
    \ INF; }\n        bool is_unreachable(const Node &node) const { return get_dist(node)\
    \ == INF; }\n};\n\nclass BFS01 : public BFS01_base<int, std::vector<int>> {\n\
    \    using base = BFS01_base<int, std::vector<int>>;\n    public:\n        template\
    \ <typename Graph>\n        BFS01(const int n, const int src, const Graph g) :\
    \ base(n, this->INF) {\n            this->bfs(std::vector<int>{src}, g);\n   \
    \     }\n        template <typename Graph>\n        BFS01(const int n, const std::vector<int>\
    \ &src_list, const Graph g) : base(n, this->INF) {\n            this->bfs(src_list,\
    \ g);\n        }\n    protected:\n        int get_dist(const int &node) const\
    \ override {\n            return this->_dist[node];\n        }\n};\n\ntemplate\
    \ <typename Node>\nclass MapBFS01 : public BFS01_base<Node, std::map<Node, int>>\
    \ {\n    using base = BFS01_base<Node, std::map<Node, int>>;\n    public:\n  \
    \      template <typename Graph>\n        MapBFS01(const Node src, const Graph\
    \ g) : base() {\n            this->bfs(std::vector<Node>{src}, g);\n        }\n\
    \        template <typename Graph>\n        MapBFS01(const std::vector<Node> &src_list,\
    \ const Graph g) : base() {\n            this->bfs(src_list, g);\n        }\n\
    \    protected:\n        int get_dist(const Node &node) const override {\n   \
    \         return this->_dist.count(node) ? this->_dist.at(node) : this->INF;\n\
    \        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BFS01\n#define SUISEN_BFS01\n\n#include <limits>\n#include\
    \ <map>\n#include <queue>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename\
    \ Node, typename Container>\nclass BFS01_base {\n    protected:\n        Container\
    \ _dist;\n\n        template <typename ...Args>\n        BFS01_base(Args &&...args)\
    \ : _dist(std::forward<Args>(args)...) {}\n\n        virtual int get_dist(const\
    \ Node &node) const = 0;\n\n        template <typename Graph>\n        void bfs(const\
    \ std::vector<Node> &src_list, const Graph g) {\n            std::deque<Node>\
    \ dq;\n            for (auto &src : src_list) {\n                dq.push_back(src);\n\
    \                _dist[src] = 0;\n            }\n            while (dq.size())\
    \ {\n                Node u = dq.front(); dq.pop_front();\n                g(u,\
    \ [&](const Node &v, const bool cost) {\n                    int old_dist = get_dist(v);\n\
    \                    int new_dist = get_dist(u) + cost;\n                    if\
    \ (new_dist < old_dist) {\n                        _dist[v] = new_dist;\n    \
    \                    if (cost) {\n                            dq.push_back(v);\n\
    \                        } else {\n                            dq.push_front(v);\n\
    \                        }\n                    }\n                });\n     \
    \       }\n        }\n    public:\n        static constexpr int INF = std::numeric_limits<int>::max();\n\
    \n        int operator[](const Node &node)   const { return get_dist(node); }\n\
    \        bool is_reachable(const Node &node)   const { return get_dist(node) !=\
    \ INF; }\n        bool is_unreachable(const Node &node) const { return get_dist(node)\
    \ == INF; }\n};\n\nclass BFS01 : public BFS01_base<int, std::vector<int>> {\n\
    \    using base = BFS01_base<int, std::vector<int>>;\n    public:\n        template\
    \ <typename Graph>\n        BFS01(const int n, const int src, const Graph g) :\
    \ base(n, this->INF) {\n            this->bfs(std::vector<int>{src}, g);\n   \
    \     }\n        template <typename Graph>\n        BFS01(const int n, const std::vector<int>\
    \ &src_list, const Graph g) : base(n, this->INF) {\n            this->bfs(src_list,\
    \ g);\n        }\n    protected:\n        int get_dist(const int &node) const\
    \ override {\n            return this->_dist[node];\n        }\n};\n\ntemplate\
    \ <typename Node>\nclass MapBFS01 : public BFS01_base<Node, std::map<Node, int>>\
    \ {\n    using base = BFS01_base<Node, std::map<Node, int>>;\n    public:\n  \
    \      template <typename Graph>\n        MapBFS01(const Node src, const Graph\
    \ g) : base() {\n            this->bfs(std::vector<Node>{src}, g);\n        }\n\
    \        template <typename Graph>\n        MapBFS01(const std::vector<Node> &src_list,\
    \ const Graph g) : base() {\n            this->bfs(src_list, g);\n        }\n\
    \    protected:\n        int get_dist(const Node &node) const override {\n   \
    \         return this->_dist.count(node) ? this->_dist.at(node) : this->INF;\n\
    \        }\n};\n} // namespace suisen\n\n#endif // SUISEN_BFS01\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/BFS01.hpp
  requiredBy: []
  timestamp: '2021-08-09 15:18:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/BFS01.hpp
layout: document
redirect_from:
- /library/library/graph/BFS01.hpp
- /library/library/graph/BFS01.hpp.html
title: library/graph/BFS01.hpp
---
