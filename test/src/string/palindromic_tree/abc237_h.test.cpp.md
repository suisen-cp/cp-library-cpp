---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/bipartite_matching.hpp
    title: Bipartite Matching
  - icon: ':heavy_check_mark:'
    path: library/string/palindromic_tree.hpp
    title: Palindromic Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc237/tasks/abc237_Ex
    links:
    - https://atcoder.jp/contests/abc237/tasks/abc237_Ex
  bundledCode: "#line 1 \"test/src/string/palindromic_tree/abc237_h.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc237/tasks/abc237_Ex\"\n\n#include <iostream>\n\
    \n#line 1 \"library/graph/bipartite_matching.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <deque>\n#include <random>\n#include <utility>\n#include <vector>\n\n\
    namespace suisen {\n    struct BipartiteMatching {\n        BipartiteMatching()\
    \ {}\n        BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, Absent),\
    \ _to_l(_m, Absent), _g(n + m) {}\n\n        void add_edge(int fr, int to) {\n\
    \            _g[fr].push_back(to), _f = -1;\n        }\n\n        template <bool\
    \ shuffle = true>\n        int solve() {\n            static std::mt19937 rng(std::random_device{}());\n\
    \            if constexpr (shuffle) for (auto &adj : _g) std::shuffle(adj.begin(),\
    \ adj.end(), rng);\n\n            std::vector<int8_t> vis(_n, false);\n      \
    \  \n            auto dfs = [&, this](auto dfs, int u) -> bool {\n           \
    \     if (std::exchange(vis[u], true)) return false;\n                for (int\
    \ v : _g[u]) if (_to_l[v] == Absent) return _to_r[u] = v, _to_l[v] = u, true;\n\
    \                for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u] =\
    \ v, _to_l[v] = u, true;\n                return false;\n            };\n    \n\
    \            for (bool upd = true; std::exchange(upd, false);) {\n           \
    \     vis.assign(_n, false);\n                for (int i = 0; i < _n; ++i) if\
    \ (_to_r[i] == Absent) upd |= dfs(dfs, i);\n            }\n\n            return\
    \ _f = _n - std::count(_to_r.begin(), _to_r.end(), Absent);\n        }\n\n   \
    \     std::vector<std::pair<int, int>> max_matching() {\n            if (_f <\
    \ 0) _f = solve();\n            std::vector<std::pair<int, int>> res;\n      \
    \      res.reserve(_f);\n            for (int i = 0; i < _n; ++i) if (_to_r[i]\
    \ != Absent) res.emplace_back(i, _to_r[i]);\n            return res;\n       \
    \ }\n\n        std::vector<std::pair<int, int>> min_edge_cover() {\n         \
    \   auto res = max_matching();\n            std::vector<bool> vl(_n, false), vr(_n,\
    \ false);\n            for (const auto &[u, v] : res) vl[u] = vr[v] = true;\n\
    \            for (int u = 0; u < _n; ++u) for (int v : _g[u]) if (not (vl[u] and\
    \ vr[v])) {\n                vl[u] = vr[v] = true;\n                res.emplace_back(u,\
    \ v);\n            }\n            return res;\n        }\n\n        std::vector<int>\
    \ min_vertex_cover() {\n            if (_f < 0) _f = solve();\n            std::vector<std::vector<int>>\
    \ g(_n + _m);\n            std::vector<bool> cl(_n, true), cr(_m, false);\n  \
    \          for (int u = 0; u < _n; ++u) for (int v : _g[u]) {\n              \
    \  if (_to_r[u] == v) {\n                    g[v + _n].push_back(u);\n       \
    \             cl[u] = false;\n                } else {\n                    g[u].push_back(v\
    \ + _n);\n                }\n            }\n            std::vector<bool> vis(_n\
    \ + _m, false);\n            std::deque<int> dq;\n            for (int i = 0;\
    \ i < _n; ++i) if (cl[i]) {\n                dq.push_back(i);\n              \
    \  vis[i] = true;\n            }\n            while (dq.size()) {\n          \
    \      int u = dq.front();\n                dq.pop_front();\n                for\
    \ (int v : g[u]) {\n                    if (vis[v]) continue;\n              \
    \      vis[v] = true;\n                    (v < _n ? cl[v] : cr[v - _n]) = true;\n\
    \                    dq.push_back(v);\n                }\n            }\n    \
    \        std::vector<int> res;\n            for (int i = 0; i < _n; ++i) if (not\
    \ cl[i]) res.push_back(i);\n            for (int i = 0; i < _m; ++i) if (cr[i])\
    \ res.push_back(_n + i);\n            return res;\n        }\n        \n     \
    \   std::vector<int> max_independent_set() {\n            std::vector<bool> use(_n\
    \ + _m, true);\n            for (int v : min_vertex_cover()) use[v] = false;\n\
    \            std::vector<int> res;\n            for (int i = 0; i < _n + _m; ++i)\
    \ if (use[i]) res.push_back(i);\n            return res;\n        }\n\n    private:\n\
    \        static constexpr int Absent = -1;\n\n        int _n, _m;\n        std::vector<int>\
    \ _to_r, _to_l;\n        std::vector<std::vector<int>> _g;\n        int _f = 0;\n\
    \    };\n    \n} // namespace suisen\n\n\n\n#line 1 \"library/string/palindromic_tree.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#line 7 \"library/string/palindromic_tree.hpp\"\
    \n#include <map>\n\nnamespace suisen {\n    namespace internal::palindromic_tree\
    \ {\n        template <typename T>\n        constexpr bool false_v = false;\n\n\
    \        template <typename T, typename Sequence, typename ChildrenContainerType>\n\
    \        struct PalindromicTreeBase {\n            using container_type = Sequence;\n\
    \            using value_type = T;\n\n            using children_container_type\
    \ = ChildrenContainerType;\n\n            struct PalindromicTreeNode {\n     \
    \           friend struct PalindromicTreeBase;\n                PalindromicTreeNode()\
    \ = default;\n            private:\n                children_container_type _children;\n\
    \                int _suffix_link;\n                int _length;\n           \
    \     int _multiplicity;\n                int _first_occurence;\n            };\n\
    \n            using node_type = PalindromicTreeNode;\n            using node_pointer_type\
    \ = node_type*;\n\n            static constexpr int NODE_NULL = -1;\n        \
    \    static constexpr int NODE_M1 = 0;\n            static constexpr int NODE_0\
    \ = 1;\n\n            PalindromicTreeBase() {\n                node_pointer_type\
    \ node_m1 = _new_node();\n                node_m1->_suffix_link = NODE_M1;\n \
    \               node_m1->_length = -1;\n                node_m1->_first_occurence\
    \ = 1;\n\n                node_pointer_type node_0 = _new_node();\n          \
    \      node_0->_suffix_link = NODE_M1;\n                node_0->_length = 0;\n\
    \                node_0->_first_occurence = 0;\n\n                _active_index\
    \ = 0;\n            }\n            template <typename Iterable>\n            PalindromicTreeBase(const\
    \ Iterable& seq) : PalindromicTreeBase() {\n                add_all(seq);\n  \
    \          }\n\n            void add(const value_type& val) {\n              \
    \  _seq.push_back(val);\n\n                node_pointer_type par_node = _find_next_longest_suffix_palindrome(_get_node(_active_index));\n\
    \                auto& ch = par_node->_children;\n\n                bool inserted\
    \ = false;\n\n                if constexpr (is_map) {\n                    const\
    \ auto [it, inserted_tmp] = ch.emplace(val, _nodes.size());\n                \
    \    inserted = inserted_tmp;\n                    _active_index = it->second;\n\
    \                } else if constexpr (is_vector) {\n                    if (value_type(ch.size())\
    \ <= val) ch.resize(val + 1, NODE_NULL);\n                    if (ch[val] == NODE_NULL)\
    \ {\n                        inserted = true;\n                        ch[val]\
    \ = _nodes.size();\n                        _active_index = _nodes.size();\n \
    \                   } else {\n                        _active_index = ch[val];\n\
    \                    }\n                } else if constexpr (is_array) {\n   \
    \                 if (ch[val] == NODE_NULL) {\n                        inserted\
    \ = true;\n                        ch[val] = _nodes.size();\n                \
    \        _active_index = _nodes.size();\n                    } else {\n      \
    \                  _active_index = ch[val];\n                    }\n         \
    \       } else static_assert(false_v<void>);\n                if (not inserted)\
    \ {\n                    ++_get_node(_active_index)->_multiplicity;\n        \
    \            return;\n                }\n\n                int par_length = par_node->_length;\n\
    \                int par_suffix_link = par_node->_suffix_link;\n\n           \
    \     node_pointer_type new_node = _new_node();\n\n                new_node->_multiplicity\
    \ = 1;\n                new_node->_length = par_length + 2;\n                new_node->_first_occurence\
    \ = _seq.size() - new_node->_length;\n                if (new_node->_length ==\
    \ 1) {\n                    new_node->_suffix_link = NODE_0;\n               \
    \ } else {\n                    new_node->_suffix_link = _find_next_longest_suffix_palindrome(_get_node(par_suffix_link))->_children[val];\n\
    \                }\n            }\n            template <typename Iterable>\n\
    \            void add_all(const Iterable &seq) {\n                for (const auto\
    \ &val : seq) add(val);\n            }\n\n            int node_num() const {\n\
    \                return _nodes.size();\n            }\n\n            const node_type&\
    \ get_node(int index) const {\n                return _nodes[index];\n       \
    \     }\n\n            int first_occurence(int index) const {\n              \
    \  return get_node(index)._first_occurence;\n            }\n            int length(int\
    \ index) const {\n                return get_node(index)._length;\n          \
    \  }\n            int suffix_link(int index) const {\n                return get_node(index)._suffix_link;\n\
    \            }\n            int node_multiplicity(int index) const {\n       \
    \         return get_node(index)._multiplicity;\n            }\n            const\
    \ children_container_type& children(int index) const {\n                return\
    \ get_node(index)._children;\n            }\n            std::vector<int> parents()\
    \ const {\n                int sz = node_num();\n                std::vector<int>\
    \ res(sz, -1);\n                for (int i = 0; i < sz; ++i) {\n             \
    \       for (const auto& p : children(i)) {\n                        if constexpr\
    \ (is_map) {\n                            res[p.second] = i;\n               \
    \         } else if (p != NODE_NULL) {\n                            res[p] = i;\n\
    \                        }\n                    }\n                }\n       \
    \         return res;\n            }\n\n            const container_type get_palindrome(int\
    \ index) {\n                if (index == NODE_M1) return container_type{};\n \
    \               int l = first_occurence(index), r = l + length(index);\n     \
    \           return container_type{ _seq.begin() + l, _seq.begin() + r };\n   \
    \         }\n\n            std::vector<int> frequency_table() const {\n      \
    \          int sz = node_num();\n                std::vector<int> res(sz);\n \
    \               for (int i = sz; i-- > 1;) {\n                    res[i] += node_multiplicity(i);\n\
    \                    res[suffix_link(i)] += res[i];\n                }\n     \
    \           return res;\n            }\n\n            template <bool erase_root\
    \ = false>\n            void clear() {\n                _active_index = 0;\n \
    \               _seq.clear();\n                if constexpr (erase_root) {\n \
    \                   _nodes.clear();\n                } else {\n              \
    \      _nodes.erase(_nodes.begin() + 2, _nodes.end());\n                }\n  \
    \          }\n\n            void shrink_to_fit() {\n                _seq.shrink_to_fit();\n\
    \                _nodes.shrink_to_fit();\n            }\n\n        private:\n\
    \            static constexpr bool is_map = std::is_same_v<std::map<value_type,\
    \ int>, children_container_type>;\n            static constexpr bool is_vector\
    \ = std::is_same_v<std::vector<value_type>, children_container_type>;\n      \
    \      static constexpr bool is_array = std::is_same_v<std::array<value_type,\
    \ std::tuple_size_v<children_container_type>>, children_container_type>;\n\n \
    \           int _active_index;\n            container_type _seq;\n           \
    \ std::vector<node_type> _nodes;\n\n            node_pointer_type _new_node()\
    \ {\n                node_pointer_type new_node = &_nodes.emplace_back();\n  \
    \              if constexpr (not (is_map or is_vector)) {\n                  \
    \  std::fill(new_node->_children.begin(), new_node->_children.end(), NODE_NULL);\n\
    \                }\n                return new_node;\n            }\n\n      \
    \      node_pointer_type _find_next_longest_suffix_palindrome(node_pointer_type\
    \ node) {\n                const int sz = _seq.size();\n                for (;;\
    \ node = _get_node(node->_suffix_link)) {\n                    int opposite_index\
    \ = sz - node->_length - 2;\n                    if (opposite_index >= 0 and _seq[opposite_index]\
    \ == _seq.back()) return node;\n                }\n            }\n\n         \
    \   node_pointer_type _get_node(int index) {\n                return &_nodes[index];\n\
    \            }\n        };\n    } // namespace internal::palindromic_tree\n\n\
    \    template <typename T, typename Sequence = std::vector<T>>\n    struct PalindromicTree\
    \ : public internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::map<T,\
    \ int>> {\n        using base_type = internal::palindromic_tree::PalindromicTreeBase<T,\
    \ Sequence, std::map<T, int>>;\n        using base_type::base_type;\n    };\n\n\
    \    template <typename T, typename Sequence = std::vector<T>>\n    struct PalindromicTreeVec\
    \ : public internal::palindromic_tree::PalindromicTreeBase<T, Sequence, std::vector<T>>\
    \ {\n        using base_type = internal::palindromic_tree::PalindromicTreeBase<T,\
    \ Sequence, std::vector<T>>;\n        using base_type::base_type;\n    };\n\n\
    \    template <typename T, std::size_t N, typename Sequence = std::vector<T>>\n\
    \    struct PalindromicTreeArr : public internal::palindromic_tree::PalindromicTreeBase<T,\
    \ Sequence, std::array<T, N>> {\n        using base_type = internal::palindromic_tree::PalindromicTreeBase<T,\
    \ Sequence, std::array<T, N>>;\n        using base_type::base_type;\n    };\n\
    } // namespace suisen\n\n\n\n#line 7 \"test/src/string/palindromic_tree/abc237_h.test.cpp\"\
    \n\nusing suisen::BipartiteMatching;\nusing suisen::PalindromicTree;\nusing suisen::PalindromicTreeVec;\n\
    using suisen::PalindromicTreeArr;\n\nint main() {\n    std::string s;\n    std::cin\
    \ >> s;\n\n    std::vector<int> s2;\n    for (char c : s) s2.push_back(c - 'a');\n\
    \n    PalindromicTree<char, std::string> t(s);\n\n    const int n = t.node_num()\
    \ - 2;\n    std::vector<int> par = t.parents();\n\n    BipartiteMatching matching(n,\
    \ n);\n    for (int i = 0; i < n; ++i) {\n        int j = t.suffix_link(i + 2)\
    \ - 2, k = par[i + 2] - 2;\n        if (j >= 0) matching.add_edge(i, j);\n   \
    \     if (k >= 0) matching.add_edge(i, k);\n    }\n\n    std::cout << n - matching.solve()\
    \ << std::endl;\n\n    // verification of other versions of palindromic tree\n\
    \    {\n        PalindromicTreeVec<int> tv(s2);\n        PalindromicTreeArr<int,\
    \ 26> ta(s2); \n        assert(par == tv.parents());\n        assert(par == ta.parents());\n\
    \        for (int i = 0; i < n + 2; ++i) {\n            assert(t.suffix_link(i)\
    \ == tv.suffix_link(i));\n            assert(t.suffix_link(i) == ta.suffix_link(i));\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc237/tasks/abc237_Ex\"\n\n\
    #include <iostream>\n\n#include \"library/graph/bipartite_matching.hpp\"\n#include\
    \ \"library/string/palindromic_tree.hpp\"\n\nusing suisen::BipartiteMatching;\n\
    using suisen::PalindromicTree;\nusing suisen::PalindromicTreeVec;\nusing suisen::PalindromicTreeArr;\n\
    \nint main() {\n    std::string s;\n    std::cin >> s;\n\n    std::vector<int>\
    \ s2;\n    for (char c : s) s2.push_back(c - 'a');\n\n    PalindromicTree<char,\
    \ std::string> t(s);\n\n    const int n = t.node_num() - 2;\n    std::vector<int>\
    \ par = t.parents();\n\n    BipartiteMatching matching(n, n);\n    for (int i\
    \ = 0; i < n; ++i) {\n        int j = t.suffix_link(i + 2) - 2, k = par[i + 2]\
    \ - 2;\n        if (j >= 0) matching.add_edge(i, j);\n        if (k >= 0) matching.add_edge(i,\
    \ k);\n    }\n\n    std::cout << n - matching.solve() << std::endl;\n\n    //\
    \ verification of other versions of palindromic tree\n    {\n        PalindromicTreeVec<int>\
    \ tv(s2);\n        PalindromicTreeArr<int, 26> ta(s2); \n        assert(par ==\
    \ tv.parents());\n        assert(par == ta.parents());\n        for (int i = 0;\
    \ i < n + 2; ++i) {\n            assert(t.suffix_link(i) == tv.suffix_link(i));\n\
    \            assert(t.suffix_link(i) == ta.suffix_link(i));\n        }\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - library/graph/bipartite_matching.hpp
  - library/string/palindromic_tree.hpp
  isVerificationFile: true
  path: test/src/string/palindromic_tree/abc237_h.test.cpp
  requiredBy: []
  timestamp: '2022-03-03 18:13:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/string/palindromic_tree/abc237_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/palindromic_tree/abc237_h.test.cpp
- /verify/test/src/string/palindromic_tree/abc237_h.test.cpp.html
title: test/src/string/palindromic_tree/abc237_h.test.cpp
---
