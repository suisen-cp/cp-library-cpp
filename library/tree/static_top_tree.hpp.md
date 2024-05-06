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
  bundledCode: "#line 1 \"library/tree/static_top_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    struct static_toptree {\n    private:\n\
    \        enum class NodeTag {\n            VERTEX,\n            ADD_EDGE,\n  \
    \          MERGE_SUBTREES,\n            ADD_ROOT,\n            MERGE_PATHS,\n\
    \        };\n\n        struct Node {\n            NodeTag tag;\n            int\
    \ ch_id[2]{ -1, -1 };\n            int par_id = -1;\n            int v;\n\n  \
    \          Node(NodeTag tag, int lch, int rch, int v) : tag(tag), ch_id{ lch,\
    \ rch }, v(v) {}\n\n            static int vertex(int v, std::vector<Node> &pool)\
    \ {\n                const int id = pool.size();\n                pool.emplace_back(NodeTag::VERTEX,\
    \ -1, -1, v);\n                return id;\n            }\n            static int\
    \ add_edge(int ch, int v, std::vector<Node> &pool) {\n                const int\
    \ id = pool.size();\n                pool.emplace_back(NodeTag::ADD_EDGE, ch,\
    \ -1, v);\n                return id;\n            }\n            static int merge_subtrees(int\
    \ lch, int rch, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::MERGE_SUBTREES, lch, rch, -1);\n \
    \               return id;\n            }\n            static int add_root(int\
    \ ch, int v, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::ADD_ROOT, ch, -1, v);\n          \
    \      return id;\n            }\n            static int merge_paths(int hi, int\
    \ lo, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::MERGE_PATHS, hi, lo, -1);\n      \
    \          return id;\n            }\n        };\n    public:\n\n        static_toptree()\
    \ = default;\n        static_toptree(const std::vector<std::vector<int>> &g, int\
    \ root) : _n(g.size()), _g(g), _par(_n, -1), _sub(_n), _idx(_n) {\n          \
    \  [&, dfs = [&](auto dfs, int u, int p) -> void {\n                _par[u] =\
    \ p;\n                int max_sub = -1;\n                _sub[u] = 1;\n      \
    \          for (int i = 0, siz = _g[u].size(); i < siz; ++i) {\n             \
    \       const int v = _g[u][i];\n                    if (v == p) {\n         \
    \               std::swap(_g[u][i], _g[u].back());\n                        _g[u].pop_back();\n\
    \                        --i, --siz;\n                    } else {\n         \
    \               dfs(dfs, v, u);\n                        _sub[u] += _sub[v];\n\
    \                        if (_sub[v] > max_sub) {\n                          \
    \  // heavy path\n                            std::swap(_g[u].front(), _g[u][i]);\n\
    \                            max_sub = _sub[v];\n                        }\n \
    \                   }\n                }\n            }]{ dfs(dfs, root, -1);\
    \ }();\n\n            _toptree_root = _merge_paths(_heavy_path(root));\n     \
    \   }\n\n        /**\n         * Path: with root\n         * Subtree: without\
    \ root\n         * vertex: vertex -> Path\n         * add_edge: Path, root, par[root]\
    \ -> Subtree\n         * merge_subtrees: Subtree, Subtree -> Subtree\n       \
    \  * add_root: Subtree, root -> Path\n         * merge_paths: Path (hi), Path\
    \ (lo) -> Path\n        */\n        template <\n            typename Subtree,\n\
    \            typename Path,\n            Path (*vertex)(int),\n            Subtree\
    \ (*add_edge)(Path&, int, int),\n            Subtree (*merge_subtrees)(Subtree&,\
    \ Subtree&),\n            Path (*add_root)(Subtree&, int),\n            Path (*merge_paths)(Path&,\
    \ Path&)>\n        auto tree_dp() const & {\n            struct tree_dp_impl {\n\
    \                friend static_toptree;\n\n                tree_dp_impl() = delete;\n\
    \n                const Path& operator()() const { return _pdp[_toptree->_toptree_root];\
    \ }\n                const Path& answer() const { return (*this)(); }\n      \
    \          const Path& update(int v) {\n                    for (int k = _toptree->_idx[v];;\
    \ k = _toptree->_nodes[k].par_id) {\n                        _update(k);\n   \
    \                     if (k == _toptree->_toptree_root) {\n                  \
    \          break;\n                        }\n                    }\n        \
    \            return _pdp[_toptree->_toptree_root];\n                }\n\n    \
    \        private:\n                const static_toptree* _toptree;\n         \
    \       std::vector<Subtree> _sdp;\n                std::vector<Path> _pdp;\n\n\
    \                tree_dp_impl(const static_toptree* toptree) : _toptree(toptree),\
    \ _sdp(_toptree->_node_num()), _pdp(_toptree->_node_num()) {\n               \
    \     _init(toptree->_toptree_root);\n                }\n\n                void\
    \ _update(int k) {\n                    const Node &node = _toptree->_nodes[k];\n\
    \                    const int v = node.v;\n                    if (node.tag ==\
    \ NodeTag::VERTEX) {\n                        _pdp[k] = vertex(v);\n         \
    \           } else if (node.tag == NodeTag::MERGE_PATHS) {\n                 \
    \       _pdp[k] = merge_paths(_pdp[node.ch_id[0]], _pdp[node.ch_id[1]]);\n   \
    \                 } else if (node.tag == NodeTag::MERGE_SUBTREES) {\n        \
    \                _sdp[k] = merge_subtrees(_sdp[node.ch_id[0]], _sdp[node.ch_id[1]]);\n\
    \                    } else if (node.tag == NodeTag::ADD_EDGE) {\n           \
    \             const int p = _toptree->_par[v];\n                        _sdp[k]\
    \ = add_edge(_pdp[node.ch_id[0]], v, p);\n                    } else if (node.tag\
    \ == NodeTag::ADD_ROOT) {\n                        _pdp[k] = add_root(_sdp[node.ch_id[0]],\
    \ v);\n                    } else {\n                        assert(false);\n\
    \                    }\n                }\n                void _init(int k) {\n\
    \                    const Node& node = _toptree->_nodes[k];\n               \
    \     const int lch = node.ch_id[0], rch = node.ch_id[1];\n                  \
    \  if (lch != -1) _init(lch);\n                    if (rch != -1) _init(rch);\n\
    \                    _update(k);\n                }\n            };\n        \
    \    return tree_dp_impl{ this };\n        }\n\n        int parent(int u) const\
    \ { return _par[u]; }\n        int subtree_size(int u) const { return _sub[u];\
    \ }\n\n    private:\n        int _n;\n        std::vector<std::vector<int>> _g;\n\
    \        std::vector<int> _par, _sub, _idx;\n        std::vector<Node> _nodes;\n\
    \        int _toptree_root;\n\n        int _node_num() const { return _nodes.size();\
    \ }\n\n        int _sub_size(int u) const { return _sub[u]; }\n        int _sub_size_without_heavy_child(int\
    \ u) const { return _sub[u] - (_g[u].empty() ? 0 : _sub[_g[u].front()]); }\n\n\
    \        std::vector<int> _heavy_path(int u) const {\n            std::vector<int>\
    \ heavy_path{ u };\n            for (int cur = u; _g[cur].size();) {\n       \
    \         const int nxt = _g[cur].front();\n                heavy_path.push_back(nxt);\n\
    \                cur = nxt;\n            }\n            return heavy_path;\n \
    \       }\n\n        // S\n        int _add_edge(int u) {\n            const int\
    \ ch_id = _merge_paths(_heavy_path(u));\n            const int res = Node::add_edge(ch_id,\
    \ u, _nodes);\n            _nodes[ch_id].par_id = res;\n            return res;\n\
    \        }\n        // P\n        int _add_root(int u) {\n            int res;\n\
    \            if (_g[u].size() <= 1) {\n                res = Node::vertex(u, _nodes);\n\
    \            } else {\n                const int ch_id = _merge_subtrees({ _g[u].begin()\
    \ + 1, _g[u].end() });\n                res = Node::add_root(ch_id, u, _nodes);\n\
    \                _nodes[ch_id].par_id = res;\n            }\n            return\
    \ _idx[u] = res;\n        }\n        // S\n        int _merge_subtrees(const std::vector<int>\
    \ &ch) {\n            if (ch.size() == 1) {\n                const int v = ch.front();\n\
    \                return _add_edge(v);\n            }\n            std::vector<int>\
    \ lch, rch;\n            int diff = 0;\n            for (int v : ch) diff += _sub_size(v);\n\
    \            for (int v : ch) {\n                diff -= 2 * _sub_size(v);\n \
    \               (diff >= 0 or lch.empty() ? lch : rch).push_back(v);\n       \
    \     }\n            const int lch_id = _merge_subtrees(std::move(lch));\n   \
    \         const int rch_id = _merge_subtrees(std::move(rch));\n            const\
    \ int res = Node::merge_subtrees(lch_id, rch_id, _nodes);\n            _nodes[lch_id].par_id\
    \ = res;\n            _nodes[rch_id].par_id = res;\n            return res;\n\
    \        }\n        // P\n        int _merge_paths(const std::vector<int> &heavy_path)\
    \ {\n            if (heavy_path.size() == 1) {\n                const int v =\
    \ heavy_path.front();\n                return _add_root(v);\n            }\n \
    \           std::vector<int> hi, lo;\n            int diff = 0;\n            for\
    \ (int v : heavy_path) diff += _sub_size_without_heavy_child(v);\n           \
    \ for (int v : heavy_path) {\n                diff -= 2 * _sub_size_without_heavy_child(v);\n\
    \                (diff >= 0 or hi.empty() ? hi : lo).push_back(v);\n         \
    \   }\n            const int hi_id = _merge_paths(std::move(hi));\n          \
    \  const int lo_id = _merge_paths(std::move(lo));\n            const int res =\
    \ Node::merge_paths(hi_id, lo_id, _nodes);\n            _nodes[hi_id].par_id =\
    \ res;\n            _nodes[lo_id].par_id = res;\n            return res;\n   \
    \     }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_STATIC_TOP_TREE_HPP\n#define SUISEN_STATIC_TOP_TREE_HPP\n\n\
    #include <cassert>\n#include <vector>\n\nnamespace suisen {\n    struct static_toptree\
    \ {\n    private:\n        enum class NodeTag {\n            VERTEX,\n       \
    \     ADD_EDGE,\n            MERGE_SUBTREES,\n            ADD_ROOT,\n        \
    \    MERGE_PATHS,\n        };\n\n        struct Node {\n            NodeTag tag;\n\
    \            int ch_id[2]{ -1, -1 };\n            int par_id = -1;\n         \
    \   int v;\n\n            Node(NodeTag tag, int lch, int rch, int v) : tag(tag),\
    \ ch_id{ lch, rch }, v(v) {}\n\n            static int vertex(int v, std::vector<Node>\
    \ &pool) {\n                const int id = pool.size();\n                pool.emplace_back(NodeTag::VERTEX,\
    \ -1, -1, v);\n                return id;\n            }\n            static int\
    \ add_edge(int ch, int v, std::vector<Node> &pool) {\n                const int\
    \ id = pool.size();\n                pool.emplace_back(NodeTag::ADD_EDGE, ch,\
    \ -1, v);\n                return id;\n            }\n            static int merge_subtrees(int\
    \ lch, int rch, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::MERGE_SUBTREES, lch, rch, -1);\n \
    \               return id;\n            }\n            static int add_root(int\
    \ ch, int v, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::ADD_ROOT, ch, -1, v);\n          \
    \      return id;\n            }\n            static int merge_paths(int hi, int\
    \ lo, std::vector<Node> &pool) {\n                const int id = pool.size();\n\
    \                pool.emplace_back(NodeTag::MERGE_PATHS, hi, lo, -1);\n      \
    \          return id;\n            }\n        };\n    public:\n\n        static_toptree()\
    \ = default;\n        static_toptree(const std::vector<std::vector<int>> &g, int\
    \ root) : _n(g.size()), _g(g), _par(_n, -1), _sub(_n), _idx(_n) {\n          \
    \  [&, dfs = [&](auto dfs, int u, int p) -> void {\n                _par[u] =\
    \ p;\n                int max_sub = -1;\n                _sub[u] = 1;\n      \
    \          for (int i = 0, siz = _g[u].size(); i < siz; ++i) {\n             \
    \       const int v = _g[u][i];\n                    if (v == p) {\n         \
    \               std::swap(_g[u][i], _g[u].back());\n                        _g[u].pop_back();\n\
    \                        --i, --siz;\n                    } else {\n         \
    \               dfs(dfs, v, u);\n                        _sub[u] += _sub[v];\n\
    \                        if (_sub[v] > max_sub) {\n                          \
    \  // heavy path\n                            std::swap(_g[u].front(), _g[u][i]);\n\
    \                            max_sub = _sub[v];\n                        }\n \
    \                   }\n                }\n            }]{ dfs(dfs, root, -1);\
    \ }();\n\n            _toptree_root = _merge_paths(_heavy_path(root));\n     \
    \   }\n\n        /**\n         * Path: with root\n         * Subtree: without\
    \ root\n         * vertex: vertex -> Path\n         * add_edge: Path, root, par[root]\
    \ -> Subtree\n         * merge_subtrees: Subtree, Subtree -> Subtree\n       \
    \  * add_root: Subtree, root -> Path\n         * merge_paths: Path (hi), Path\
    \ (lo) -> Path\n        */\n        template <\n            typename Subtree,\n\
    \            typename Path,\n            Path (*vertex)(int),\n            Subtree\
    \ (*add_edge)(Path&, int, int),\n            Subtree (*merge_subtrees)(Subtree&,\
    \ Subtree&),\n            Path (*add_root)(Subtree&, int),\n            Path (*merge_paths)(Path&,\
    \ Path&)>\n        auto tree_dp() const & {\n            struct tree_dp_impl {\n\
    \                friend static_toptree;\n\n                tree_dp_impl() = delete;\n\
    \n                const Path& operator()() const { return _pdp[_toptree->_toptree_root];\
    \ }\n                const Path& answer() const { return (*this)(); }\n      \
    \          const Path& update(int v) {\n                    for (int k = _toptree->_idx[v];;\
    \ k = _toptree->_nodes[k].par_id) {\n                        _update(k);\n   \
    \                     if (k == _toptree->_toptree_root) {\n                  \
    \          break;\n                        }\n                    }\n        \
    \            return _pdp[_toptree->_toptree_root];\n                }\n\n    \
    \        private:\n                const static_toptree* _toptree;\n         \
    \       std::vector<Subtree> _sdp;\n                std::vector<Path> _pdp;\n\n\
    \                tree_dp_impl(const static_toptree* toptree) : _toptree(toptree),\
    \ _sdp(_toptree->_node_num()), _pdp(_toptree->_node_num()) {\n               \
    \     _init(toptree->_toptree_root);\n                }\n\n                void\
    \ _update(int k) {\n                    const Node &node = _toptree->_nodes[k];\n\
    \                    const int v = node.v;\n                    if (node.tag ==\
    \ NodeTag::VERTEX) {\n                        _pdp[k] = vertex(v);\n         \
    \           } else if (node.tag == NodeTag::MERGE_PATHS) {\n                 \
    \       _pdp[k] = merge_paths(_pdp[node.ch_id[0]], _pdp[node.ch_id[1]]);\n   \
    \                 } else if (node.tag == NodeTag::MERGE_SUBTREES) {\n        \
    \                _sdp[k] = merge_subtrees(_sdp[node.ch_id[0]], _sdp[node.ch_id[1]]);\n\
    \                    } else if (node.tag == NodeTag::ADD_EDGE) {\n           \
    \             const int p = _toptree->_par[v];\n                        _sdp[k]\
    \ = add_edge(_pdp[node.ch_id[0]], v, p);\n                    } else if (node.tag\
    \ == NodeTag::ADD_ROOT) {\n                        _pdp[k] = add_root(_sdp[node.ch_id[0]],\
    \ v);\n                    } else {\n                        assert(false);\n\
    \                    }\n                }\n                void _init(int k) {\n\
    \                    const Node& node = _toptree->_nodes[k];\n               \
    \     const int lch = node.ch_id[0], rch = node.ch_id[1];\n                  \
    \  if (lch != -1) _init(lch);\n                    if (rch != -1) _init(rch);\n\
    \                    _update(k);\n                }\n            };\n        \
    \    return tree_dp_impl{ this };\n        }\n\n        int parent(int u) const\
    \ { return _par[u]; }\n        int subtree_size(int u) const { return _sub[u];\
    \ }\n\n    private:\n        int _n;\n        std::vector<std::vector<int>> _g;\n\
    \        std::vector<int> _par, _sub, _idx;\n        std::vector<Node> _nodes;\n\
    \        int _toptree_root;\n\n        int _node_num() const { return _nodes.size();\
    \ }\n\n        int _sub_size(int u) const { return _sub[u]; }\n        int _sub_size_without_heavy_child(int\
    \ u) const { return _sub[u] - (_g[u].empty() ? 0 : _sub[_g[u].front()]); }\n\n\
    \        std::vector<int> _heavy_path(int u) const {\n            std::vector<int>\
    \ heavy_path{ u };\n            for (int cur = u; _g[cur].size();) {\n       \
    \         const int nxt = _g[cur].front();\n                heavy_path.push_back(nxt);\n\
    \                cur = nxt;\n            }\n            return heavy_path;\n \
    \       }\n\n        // S\n        int _add_edge(int u) {\n            const int\
    \ ch_id = _merge_paths(_heavy_path(u));\n            const int res = Node::add_edge(ch_id,\
    \ u, _nodes);\n            _nodes[ch_id].par_id = res;\n            return res;\n\
    \        }\n        // P\n        int _add_root(int u) {\n            int res;\n\
    \            if (_g[u].size() <= 1) {\n                res = Node::vertex(u, _nodes);\n\
    \            } else {\n                const int ch_id = _merge_subtrees({ _g[u].begin()\
    \ + 1, _g[u].end() });\n                res = Node::add_root(ch_id, u, _nodes);\n\
    \                _nodes[ch_id].par_id = res;\n            }\n            return\
    \ _idx[u] = res;\n        }\n        // S\n        int _merge_subtrees(const std::vector<int>\
    \ &ch) {\n            if (ch.size() == 1) {\n                const int v = ch.front();\n\
    \                return _add_edge(v);\n            }\n            std::vector<int>\
    \ lch, rch;\n            int diff = 0;\n            for (int v : ch) diff += _sub_size(v);\n\
    \            for (int v : ch) {\n                diff -= 2 * _sub_size(v);\n \
    \               (diff >= 0 or lch.empty() ? lch : rch).push_back(v);\n       \
    \     }\n            const int lch_id = _merge_subtrees(std::move(lch));\n   \
    \         const int rch_id = _merge_subtrees(std::move(rch));\n            const\
    \ int res = Node::merge_subtrees(lch_id, rch_id, _nodes);\n            _nodes[lch_id].par_id\
    \ = res;\n            _nodes[rch_id].par_id = res;\n            return res;\n\
    \        }\n        // P\n        int _merge_paths(const std::vector<int> &heavy_path)\
    \ {\n            if (heavy_path.size() == 1) {\n                const int v =\
    \ heavy_path.front();\n                return _add_root(v);\n            }\n \
    \           std::vector<int> hi, lo;\n            int diff = 0;\n            for\
    \ (int v : heavy_path) diff += _sub_size_without_heavy_child(v);\n           \
    \ for (int v : heavy_path) {\n                diff -= 2 * _sub_size_without_heavy_child(v);\n\
    \                (diff >= 0 or hi.empty() ? hi : lo).push_back(v);\n         \
    \   }\n            const int hi_id = _merge_paths(std::move(hi));\n          \
    \  const int lo_id = _merge_paths(std::move(lo));\n            const int res =\
    \ Node::merge_paths(hi_id, lo_id, _nodes);\n            _nodes[hi_id].par_id =\
    \ res;\n            _nodes[lo_id].par_id = res;\n            return res;\n   \
    \     }\n    };\n} // namespace suisen\n\n#endif // SUISEN_STATIC_TOP_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/static_top_tree.hpp
  requiredBy: []
  timestamp: '2024-05-07 01:25:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/static_top_tree.hpp
layout: document
redirect_from:
- /library/library/tree/static_top_tree.hpp
- /library/library/tree/static_top_tree.hpp.html
title: library/tree/static_top_tree.hpp
---
