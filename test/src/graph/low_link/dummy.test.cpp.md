---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/low_link.hpp
    title: Low Link
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/graph/low_link/dummy.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\
    \nnamespace suisen {\n    struct LowLink {\n        LowLink() : LowLink(0) {}\n\
    \        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n, -1), _low_link(n),\
    \ _built(false), _conn_comp_num(0), _par(n, -1) {}\n        LowLink(const int\
    \ n, const std::vector<std::pair<int, int>> &edges) : LowLink(n) {\n         \
    \   for (const auto &[u, v] : edges) add_edge(u, v);\n            build();\n \
    \       }\n        \n        // Add an edge and return its ID. IDs are assigned\
    \ in the order (0,1,2, ...).\n        int add_edge(int u, int v) {\n         \
    \   _built = false;\n            _edges.emplace_back(u, v);\n            _g[u].emplace_back(v,\
    \ _m);\n            _g[v].emplace_back(u, _m);\n            return _m++;\n   \
    \     }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
    \            _built = true;\n        }\n\n        int vertex_num() const { return\
    \ _n; }\n        int edge_num()   const { return _m; }\n\n        const std::pair<int,\
    \ int>& edge(int edge_id) const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
    \ int>>& edges() const { return _edges; }\n        // list of edges { u, edge_id\
    \ } adjacent to the vertex v.\n        const std::vector<std::pair<int, int>>&\
    \ operator[](int v) const { return _g[v]; }\n        \n        int pre_order(int\
    \ v) const {\n            assert(_built);\n            return _pre_order[v];\n\
    \        }\n        int low_link(int v) const {\n            assert(_built);\n\
    \            return _low_link[v];\n        }\n\n        // Returns IDs of bridges.\n\
    \        const std::vector<int>& bridge_ids() const {\n            assert(_built);\n\
    \            return _bridges;\n        }\n        const std::vector<int>& articulation_points()\
    \ const {\n            assert(_built);\n            return _articulation_points;\n\
    \        }\n\n        // O(1)\n        // Assuming that there exists the edge\
    \ {u,v}, return whether the edge is a bridge or not.\n        bool is_bridge(int\
    \ u, int v) const {\n            assert(_built);\n            if (_pre_order[u]\
    \ > _pre_order[v]) std::swap(u, v);\n            // u is an ancestor of v\n  \
    \          return _pre_order[u] < _low_link[v];\n        }\n\n        // O(# edges\
    \ incident with u)\n        // Return whether the vertex is a articulation point\
    \ or not.\n        bool is_articulation_point(int u) const {\n            assert(_built);\n\
    \            return connected_component_num_if_removed(u) > connected_component_num();\n\
    \        }\n\n        // Return the number of connected components\n        int\
    \ connected_component_num() const {\n            assert(_built);\n           \
    \ return _conn_comp_num;\n        }\n\n        // O(1)\n        // Assuming that\
    \ there exists the edge {u,v}, return the number of connected components of the\
    \ graph obtained by removing an edge {u,v}.\n        // If there are multiple\
    \ edges {u,v}, consider removing only one of them.\n        int connected_component_num_if_removed(int\
    \ u, int v) const {\n            assert(_built);\n            return _conn_comp_num\
    \ + is_bridge(u, v);\n        }\n\n        // O(# edges incident with u)\n   \
    \     // Return the number of connected components of the graph obtained by removing\
    \ an vertex u and edges incident with it.\n        int connected_component_num_if_removed(int\
    \ u) const {\n            assert(_built);\n            static std::vector<int8_t>\
    \ seen;\n            if (seen.size() < size_t(_n)) seen.resize(_n);\n        \
    \    bool is_root = true;\n            int res = 0;\n            for (const auto&\
    \ [v, _] : _g[u]) {\n                if (_pre_order[v] < _pre_order[u]) {\n  \
    \                  is_root = false;\n                    continue;\n         \
    \       }\n                if (_par[v] == u and not std::exchange(seen[v], true))\
    \ {\n                    res += (_pre_order[u] <= _low_link[v]);\n           \
    \     }\n            }\n            // rollback\n            for (const auto&\
    \ [v, _] : _g[u]) seen[v] = false;\n            return _conn_comp_num - 1 + res\
    \ + (not is_root);\n        }\n    protected:\n        int _n, _m;\n        //\
    \ list of edges\n        std::vector<std::pair<int, int>> _edges;\n        //\
    \ vertex -> list of (adjacent vertex, edge id)\n        std::vector<std::vector<std::pair<int,\
    \ int>>> _g;\n        // vertex -> pre order\n        std::vector<int> _pre_order;\n\
    \        std::vector<int> _low_link;\n        // list of ids of bridges\n    \
    \    std::vector<int> _bridges;\n        std::vector<int> _articulation_points;\n\
    \n        bool _built;\n\n    private:\n        // # connected components\n  \
    \      int _conn_comp_num;\n        std::vector<int> _par;\n\n        void dfs(const\
    \ int u, const int prev_id, int& ord) {\n            const bool is_root = prev_id\
    \ < 0;\n            bool is_articulation_point = false;\n            int ch_cnt\
    \ = 0;\n            _pre_order[u] = _low_link[u] = ord++;\n            for (const\
    \ auto& [v, id] : _g[u]) if (id != prev_id) {\n                if (_pre_order[v]\
    \ < 0) {\n                    _par[v] = u;\n                    ++ch_cnt;\n  \
    \                  dfs(v, id, ord);\n                    _low_link[u] = std::min(_low_link[u],\
    \ _low_link[v]);\n                    if (_pre_order[u] <= _low_link[v]) {\n \
    \                       is_articulation_point = not is_root;\n               \
    \         if (_pre_order[u] != _low_link[v]) _bridges.push_back(id);\n       \
    \             }\n                } else {\n                    _low_link[u] =\
    \ std::min(_low_link[u], _pre_order[v]);\n                }\n            }\n \
    \           if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);\n\
    \        }\n\n        void dfs_for_all_connected_components() {\n            for\
    \ (int i = 0, ord = 0; i < _n; ++i) if (_pre_order[i] < 0) {\n               \
    \ dfs(i, -1, ord);\n                ++_conn_comp_num;\n            }\n       \
    \ }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/graph/low_link/dummy.test.cpp\"\
    \n\nvoid test_compnum_1() {\n    suisen::LowLink ll(1);\n    ll.build();\n   \
    \ assert(ll.connected_component_num_if_removed(0) == 0);\n}\nvoid test_compnum_2()\
    \ {\n    suisen::LowLink ll(1);\n    ll.add_edge(0, 0);\n    ll.build();\n   \
    \ assert(ll.connected_component_num_if_removed(0) == 0);\n    assert(ll.connected_component_num_if_removed(0,\
    \ 0) == 1);\n}\nvoid test_compnum_3() {\n    suisen::LowLink ll(2);\n    ll.add_edge(0,\
    \ 1);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0) ==\
    \ 1);\n    assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(0,\
    \ 1) == 2);\n}\nvoid test_compnum_4() {\n    suisen::LowLink ll(2);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(0, 1);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(0,\
    \ 1) == 1);\n}\nvoid test_compnum_5() {\n    suisen::LowLink ll(3);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(1, 2);\n    ll.add_edge(2, 0);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 1);\n}\nvoid test_compnum_6() {\n    suisen::LowLink ll(3);\n    ll.add_edge(1,\
    \ 2);\n    ll.add_edge(1, 2);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 2);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 2);\n}\nvoid test_compnum_7() {\n    suisen::LowLink ll(3);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(1, 2);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 2);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 1);\n}\n\nvoid test() {\n    {\n        test_compnum_1();\n        test_compnum_2();\n\
    \        test_compnum_3();\n        test_compnum_4();\n        test_compnum_5();\n\
    \        test_compnum_6();\n        test_compnum_7();\n    }\n}\n\nint main()\
    \ {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/graph/low_link.hpp\"\n\nvoid test_compnum_1()\
    \ {\n    suisen::LowLink ll(1);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 0);\n}\nvoid test_compnum_2() {\n    suisen::LowLink ll(1);\n    ll.add_edge(0,\
    \ 0);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0) ==\
    \ 0);\n    assert(ll.connected_component_num_if_removed(0, 0) == 1);\n}\nvoid\
    \ test_compnum_3() {\n    suisen::LowLink ll(2);\n    ll.add_edge(0, 1);\n   \
    \ ll.build();\n    assert(ll.connected_component_num_if_removed(0) == 1);\n  \
    \  assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(0,\
    \ 1) == 2);\n}\nvoid test_compnum_4() {\n    suisen::LowLink ll(2);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(0, 1);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(0,\
    \ 1) == 1);\n}\nvoid test_compnum_5() {\n    suisen::LowLink ll(3);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(1, 2);\n    ll.add_edge(2, 0);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 1);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 1);\n}\nvoid test_compnum_6() {\n    suisen::LowLink ll(3);\n    ll.add_edge(1,\
    \ 2);\n    ll.add_edge(1, 2);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 2);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 2);\n}\nvoid test_compnum_7() {\n    suisen::LowLink ll(3);\n    ll.add_edge(0,\
    \ 1);\n    ll.add_edge(1, 2);\n    ll.build();\n    assert(ll.connected_component_num_if_removed(0)\
    \ == 1);\n    assert(ll.connected_component_num_if_removed(1) == 2);\n    assert(ll.connected_component_num_if_removed(2)\
    \ == 1);\n}\n\nvoid test() {\n    {\n        test_compnum_1();\n        test_compnum_2();\n\
    \        test_compnum_3();\n        test_compnum_4();\n        test_compnum_5();\n\
    \        test_compnum_6();\n        test_compnum_7();\n    }\n}\n\nint main()\
    \ {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }\n"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/low_link/dummy.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 20:12:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/low_link/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/low_link/dummy.test.cpp
- /verify/test/src/graph/low_link/dummy.test.cpp.html
title: test/src/graph/low_link/dummy.test.cpp
---
