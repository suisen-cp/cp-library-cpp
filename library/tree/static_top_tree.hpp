#ifndef SUISEN_STATIC_TOP_TREE_HPP
#define SUISEN_STATIC_TOP_TREE_HPP

#include <cassert>
#include <vector>

namespace suisen {
    struct static_toptree {
    private:
        enum class NodeTag {
            VERTEX,
            ADD_EDGE,
            MERGE_SUBTREES,
            ADD_ROOT,
            MERGE_PATHS,
        };

        struct Node {
            NodeTag tag;
            int ch_id[2]{ -1, -1 };
            int par_id = -1;
            int v;

            Node(NodeTag tag, int lch, int rch, int v) : tag(tag), ch_id{ lch, rch }, v(v) {}

            static int vertex(int v, std::vector<Node> &pool) {
                const int id = pool.size();
                pool.emplace_back(NodeTag::VERTEX, -1, -1, v);
                return id;
            }
            static int add_edge(int ch, int v, std::vector<Node> &pool) {
                const int id = pool.size();
                pool.emplace_back(NodeTag::ADD_EDGE, ch, -1, v);
                return id;
            }
            static int merge_subtrees(int lch, int rch, std::vector<Node> &pool) {
                const int id = pool.size();
                pool.emplace_back(NodeTag::MERGE_SUBTREES, lch, rch, -1);
                return id;
            }
            static int add_root(int ch, int v, std::vector<Node> &pool) {
                const int id = pool.size();
                pool.emplace_back(NodeTag::ADD_ROOT, ch, -1, v);
                return id;
            }
            static int merge_paths(int hi, int lo, std::vector<Node> &pool) {
                const int id = pool.size();
                pool.emplace_back(NodeTag::MERGE_PATHS, hi, lo, -1);
                return id;
            }
        };
    public:

        static_toptree() = default;
        static_toptree(const std::vector<std::vector<int>> &g, int root) : _n(g.size()), _g(g), _par(_n, -1), _sub(_n), _idx(_n) {
            [&, dfs = [&](auto dfs, int u, int p) -> void {
                _par[u] = p;
                int max_sub = -1;
                _sub[u] = 1;
                for (int i = 0, siz = _g[u].size(); i < siz; ++i) {
                    const int v = _g[u][i];
                    if (v == p) {
                        std::swap(_g[u][i], _g[u].back());
                        _g[u].pop_back();
                        --i, --siz;
                    } else {
                        dfs(dfs, v, u);
                        _sub[u] += _sub[v];
                        if (_sub[v] > max_sub) {
                            // heavy path
                            std::swap(_g[u].front(), _g[u][i]);
                            max_sub = _sub[v];
                        }
                    }
                }
            }]{ dfs(dfs, root, -1); }();

            _toptree_root = _merge_paths(_heavy_path(root));
        }

        /**
         * Path: with root
         * Subtree: without root
         * vertex: vertex -> Path
         * add_edge: Path, root, par[root] -> Subtree
         * merge_subtrees: Subtree, Subtree -> Subtree
         * add_root: Subtree, root -> Path
         * merge_paths: Path (hi), Path (lo) -> Path
        */
        template <
            typename Subtree,
            typename Path,
            Path (*vertex)(int),
            Subtree (*add_edge)(Path&, int, int),
            Subtree (*merge_subtrees)(Subtree&, Subtree&),
            Path (*add_root)(Subtree&, int),
            Path (*merge_paths)(Path&, Path&)>
        auto tree_dp() const & {
            struct tree_dp_impl {
                friend static_toptree;

                tree_dp_impl() = delete;

                const Path& operator()() const { return _pdp[_toptree->_toptree_root]; }
                const Path& answer() const { return (*this)(); }
                const Path& update(int v) {
                    for (int k = _toptree->_idx[v];; k = _toptree->_nodes[k].par_id) {
                        _update(k);
                        if (k == _toptree->_toptree_root) {
                            break;
                        }
                    }
                    return _pdp[_toptree->_toptree_root];
                }

            private:
                const static_toptree* _toptree;
                std::vector<Subtree> _sdp;
                std::vector<Path> _pdp;

                tree_dp_impl(const static_toptree* toptree) : _toptree(toptree), _sdp(_toptree->_node_num()), _pdp(_toptree->_node_num()) {
                    _init(toptree->_toptree_root);
                }

                void _update(int k) {
                    const Node &node = _toptree->_nodes[k];
                    const int v = node.v;
                    if (node.tag == NodeTag::VERTEX) {
                        _pdp[k] = vertex(v);
                    } else if (node.tag == NodeTag::MERGE_PATHS) {
                        _pdp[k] = merge_paths(_pdp[node.ch_id[0]], _pdp[node.ch_id[1]]);
                    } else if (node.tag == NodeTag::MERGE_SUBTREES) {
                        _sdp[k] = merge_subtrees(_sdp[node.ch_id[0]], _sdp[node.ch_id[1]]);
                    } else if (node.tag == NodeTag::ADD_EDGE) {
                        const int p = _toptree->_par[v];
                        _sdp[k] = add_edge(_pdp[node.ch_id[0]], v, p);
                    } else if (node.tag == NodeTag::ADD_ROOT) {
                        _pdp[k] = add_root(_sdp[node.ch_id[0]], v);
                    } else {
                        assert(false);
                    }
                }
                void _init(int k) {
                    const Node& node = _toptree->_nodes[k];
                    const int lch = node.ch_id[0], rch = node.ch_id[1];
                    if (lch != -1) _init(lch);
                    if (rch != -1) _init(rch);
                    _update(k);
                }
            };
            return tree_dp_impl{ this };
        }

        int parent(int u) const { return _par[u]; }
        int subtree_size(int u) const { return _sub[u]; }

    private:
        int _n;
        std::vector<std::vector<int>> _g;
        std::vector<int> _par, _sub, _idx;
        std::vector<Node> _nodes;
        int _toptree_root;

        int _node_num() const { return _nodes.size(); }

        int _sub_size(int u) const { return _sub[u]; }
        int _sub_size_without_heavy_child(int u) const { return _sub[u] - (_g[u].empty() ? 0 : _sub[_g[u].front()]); }

        std::vector<int> _heavy_path(int u) const {
            std::vector<int> heavy_path{ u };
            for (int cur = u; _g[cur].size();) {
                const int nxt = _g[cur].front();
                heavy_path.push_back(nxt);
                cur = nxt;
            }
            return heavy_path;
        }

        // S
        int _add_edge(int u) {
            const int ch_id = _merge_paths(_heavy_path(u));
            const int res = Node::add_edge(ch_id, u, _nodes);
            _nodes[ch_id].par_id = res;
            return res;
        }
        // P
        int _add_root(int u) {
            int res;
            if (_g[u].size() <= 1) {
                res = Node::vertex(u, _nodes);
            } else {
                const int ch_id = _merge_subtrees({ _g[u].begin() + 1, _g[u].end() });
                res = Node::add_root(ch_id, u, _nodes);
                _nodes[ch_id].par_id = res;
            }
            return _idx[u] = res;
        }
        // S
        int _merge_subtrees(const std::vector<int> &ch) {
            if (ch.size() == 1) {
                const int v = ch.front();
                return _add_edge(v);
            }
            std::vector<int> lch, rch;
            int diff = 0;
            for (int v : ch) diff += _sub_size(v);
            for (int v : ch) {
                diff -= 2 * _sub_size(v);
                (diff >= 0 or lch.empty() ? lch : rch).push_back(v);
            }
            const int lch_id = _merge_subtrees(std::move(lch));
            const int rch_id = _merge_subtrees(std::move(rch));
            const int res = Node::merge_subtrees(lch_id, rch_id, _nodes);
            _nodes[lch_id].par_id = res;
            _nodes[rch_id].par_id = res;
            return res;
        }
        // P
        int _merge_paths(const std::vector<int> &heavy_path) {
            if (heavy_path.size() == 1) {
                const int v = heavy_path.front();
                return _add_root(v);
            }
            std::vector<int> hi, lo;
            int diff = 0;
            for (int v : heavy_path) diff += _sub_size_without_heavy_child(v);
            for (int v : heavy_path) {
                diff -= 2 * _sub_size_without_heavy_child(v);
                (diff >= 0 or hi.empty() ? hi : lo).push_back(v);
            }
            const int hi_id = _merge_paths(std::move(hi));
            const int lo_id = _merge_paths(std::move(lo));
            const int res = Node::merge_paths(hi_id, lo_id, _nodes);
            _nodes[hi_id].par_id = res;
            _nodes[lo_id].par_id = res;
            return res;
        }
    };
} // namespace suisen

#endif // SUISEN_STATIC_TOP_TREE_HPP
