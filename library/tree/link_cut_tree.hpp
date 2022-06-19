#ifndef SUISEN_LINK_CUT_TREE
#define SUISEN_LINK_CUT_TREE

#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "library/util/object_pool.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>
    struct LinkCutTree {
        struct SplayTreeNode;

        using node_type = SplayTreeNode;
        using node_pointer_type = node_type*;
        using value_type = T;

        struct SplayTreeNode {
            friend struct LinkCutTree;

            explicit SplayTreeNode(const value_type& val = e()) : _val(val), _sum(val) {}

        private:
            node_pointer_type _p = nullptr;
            node_pointer_type _ch[2]{ nullptr, nullptr };

            int _siz = 1;
            value_type _val, _sum;

            bool _rev = false;
            
            bool is_root() const {
                return not _p or (_p->_ch[0] != this and _p->_ch[1] != this);
            }

            void update() {
                _siz = 1, _sum = _val;
                if (_ch[0]) _siz += _ch[0]->_siz, _sum = op(_ch[0]->_sum, _sum);
                if (_ch[1]) _siz += _ch[1]->_siz, _sum = op(_sum, _ch[1]->_sum);
            }

            void reverse_all() {
                _rev ^= true;
                std::swap(_ch[0], _ch[1]);
                _sum = toggle(_sum);
            }

            void push() {
                if (std::exchange(_rev, false)) {
                    if (_ch[0]) _ch[0]->reverse_all();
                    if (_ch[1]) _ch[1]->reverse_all();
                }
            }

            void rot(int ch_idx) {
                assert(_ch[ch_idx]);

                node_pointer_type rt = _ch[ch_idx];
                if (not is_root()) _p->_ch[_p->_ch[1] == this] = rt;

                if ((_ch[ch_idx] = rt->_ch[ch_idx ^ 1])) {
                    _ch[ch_idx]->_p = this;
                }
                rt->_ch[ch_idx ^ 1] = this;
                rt->_p = std::exchange(_p, rt);

                update(), rt->update();
            }

            void splay() {
                push();
                while (not is_root()) {
                    if (_p->is_root()) {
                        _p->push(), push();
                        _p->rot(_p->_ch[1] == this);
                    } else {
                        node_pointer_type pp = _p->_p;
                        pp->push(), _p->push(), push();
                        const int idx_pp = pp->_ch[1] == _p, idx_p = _p->_ch[1] == this;
                        if (idx_p == idx_pp) {
                            pp->rot(idx_pp), _p->rot(idx_p);
                        } else {
                            _p->rot(idx_p), pp->rot(idx_pp);
                        }
                    }
                }
            }
        };

        LinkCutTree() = delete;

        static void init_pool(int capacity) {
            _pool = ObjectPool<node_type>(capacity);
        }

        static node_pointer_type make_node(const value_type& val = e()) {
            return &(*_pool.alloc() = node_type(val));
        }
        static std::vector<node_pointer_type> make_nodes(const std::vector<value_type>& vals) {
            std::vector<node_pointer_type> nodes;
            nodes.reserve(vals.size());
            for (const auto& val : vals) nodes.push_back(make_node(val));
            return nodes;
        }

        static node_pointer_type expose(node_pointer_type node) {
            assert(node);
            node_pointer_type rch = nullptr;
            for (node_pointer_type cur = node; cur; cur = cur->_p) {
                cur->splay();
                cur->_ch[1] = std::exchange(rch, cur);
                cur->update();
            }
            node->splay();
            return rch;
        }

        static void link(node_pointer_type ch, node_pointer_type par) {
            evert(ch), expose(par);
            assert(not (ch == par or ch->_p)); // check un-connectivity
            par->_ch[1] = ch;
            ch->_p = par;
            par->update();
        }

        static void cut(node_pointer_type ch) {
            expose(ch);
            node_pointer_type par = ch->_ch[0];
            assert(par);
            par->_p = ch->_ch[0] = nullptr;
            ch->update();
        }
        static void cut(node_pointer_type u, node_pointer_type v) {
            evert(u);
            expose(v);
            assert(v->_ch[0] == u); // check connectivity
            u->_p = v->_ch[0] = nullptr;
            v->update();
        }

        static void evert(node_pointer_type u) {
            expose(u);
            u->reverse_all();
            u->push();
        }

        static bool is_connected(node_pointer_type u, node_pointer_type v) {
            expose(u), expose(v);
            return u == v or u->_p;
        }

        static node_pointer_type lca(node_pointer_type u, node_pointer_type v) {
            expose(u);
            node_pointer_type a = expose(v);
            return u == v or u->_p ? a : nullptr;
        }

        static value_type prod_from_root(node_pointer_type u) {
            expose(u);
            return u->_sum;
        }
        static value_type prod(node_pointer_type u, node_pointer_type v) {
            evert(u);
            expose(v);
            assert(u == v or u->_p); // check connectivity
            return v->_sum;
        }

        static value_type get(node_pointer_type u) {
            // expose(u);
            return u->_val;
        }
        static void set(node_pointer_type u, const value_type& val) {
            apply(u, [&val](const value_type&) { return val; });
        }
        template <typename Fun>
        static void apply(node_pointer_type u, Fun&& f) {
            expose(u);
            u->_val = f(u->_val);
            u->update();
        }

        static std::vector<node_pointer_type> path_from_root(node_pointer_type u) {
            std::vector<node_pointer_type> res;
            expose(u);
            auto dfs = [&](auto dfs, node_pointer_type cur) -> void {
                cur->push();
                if (cur->_ch[0]) dfs(dfs, cur->_ch[0]);
                res.push_back(cur);
                if (cur->_ch[1]) dfs(dfs, cur->_ch[1]);
            };
            dfs(dfs, u);
            return res;
        }
        static std::optional<std::vector<node_pointer_type>> path(node_pointer_type u, node_pointer_type v) {
            evert(u);
            expose(v);
            if (u == v or u->_p) return path_from_root(v);
            return std::nullopt;
        }
    
    private:
        static inline ObjectPool<node_type> _pool{};
    };
} // namespace suisen

#endif // SUISEN_LINK_CUT_TREE
