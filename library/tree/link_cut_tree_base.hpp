#ifndef SUISEN_LINK_CUT_TREE_BASE
#define SUISEN_LINK_CUT_TREE_BASE

#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "library/util/object_pool.hpp"

namespace suisen::internal::link_cut_tree {
    template <typename T, typename Derived>
    struct SplayTreeNodeBase {
        friend Derived;
        template <typename, typename>
        friend struct LinkCutTreeBase;

        using value_type = T;
        using node_type = Derived;
        using node_pointer_type = node_type*;

        explicit SplayTreeNodeBase(const value_type& val = value_type{}) : _val(val) {}

    protected:
        node_pointer_type _p = nullptr;
        node_pointer_type _ch[2]{ nullptr, nullptr };

        int _siz = 1;
        value_type _val;

        bool _rev = false;
        
        static bool is_root(node_pointer_type node) {
            return not node->_p or (node->_p->_ch[0] != node and node->_p->_ch[1] != node);
        }
        static node_pointer_type& parent(node_pointer_type node) {
            return node->_p;
        }
        static node_pointer_type& child(node_pointer_type node, int ch_idx) {
            return node->_ch[ch_idx];
        }
        static int size(node_pointer_type node) {
            return node ? node->_siz : 0;
        }
        static const value_type& value(node_pointer_type node) {
            return node->_val;
        }
        static void set_value(node_pointer_type node, const value_type &new_val) {
            node->_val = new_val;
        }
        static void update(node_pointer_type node) {
            node->_siz = 1 + node_type::size(node->_ch[0]) + node_type::size(node->_ch[1]);
        }

        static void reverse_all(node_pointer_type node) {
            if (not node) return;
            node->_rev ^= true;
            std::swap(node->_ch[0], node->_ch[1]);
        }

        static void push(node_pointer_type node) {
            if (std::exchange(node->_rev, false)) {
                node_type::reverse_all(node->_ch[0]);
                node_type::reverse_all(node->_ch[1]);
            }
        }

        static void rot(node_pointer_type node, int ch_idx) {
            assert(node->_ch[ch_idx]);

            node_pointer_type rt = node->_ch[ch_idx];
            if (not node_type::is_root(node)) node->_p->_ch[node->_p->_ch[1] == node] = rt;

            if ((node->_ch[ch_idx] = rt->_ch[ch_idx ^ 1])) node->_ch[ch_idx]->_p = node;

            rt->_ch[ch_idx ^ 1] = node;
            rt->_p = std::exchange(node->_p, rt);

            node_type::update(node), node_type::update(rt);
        }

        static void splay(node_pointer_type node) {
            node_type::push(node);
            while (not node_type::is_root(node)) {
                node_pointer_type p = node->_p;
                if (node_type::is_root(p)) {
                    node_type::push(p), node_type::push(node);
                    node_type::rot(p, p->_ch[1] == node);
                } else {
                    node_pointer_type pp = p->_p;
                    node_type::push(pp), node_type::push(p), node_type::push(node);
                    const int idx_pp = pp->_ch[1] == p, idx_p = p->_ch[1] == node;
                    if (idx_p == idx_pp) {
                        node_type::rot(pp, idx_pp), node_type::rot(p, idx_p);
                    } else {
                        node_type::rot(p, idx_p), node_type::rot(pp, idx_pp);
                    }
                }
            }
        }
    };

    template <typename NodeType, typename Derived>
    struct LinkCutTreeBase {
        using derived_tree_type = Derived;

        using node_type = typename NodeType::node_type;
        using node_pointer_type = typename NodeType::node_pointer_type;
        using value_type = typename NodeType::value_type;

        LinkCutTreeBase() = delete;

        static void init_pool(int capacity) {
            _pool = ObjectPool<node_type>(capacity);
        }

        template <typename ...Args>
        static node_pointer_type make_node(Args&&...args) {
            return &(*_pool.alloc() = node_type(std::forward<Args>(args)...));
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
            for (node_pointer_type cur = node; cur; cur = node_type::parent(cur)) {
                node_type::splay(cur);
                node_type::child(cur, 1) = std::exchange(rch, cur);
                node_type::update(cur);
            }
            node_type::splay(node);
            return rch;
        }

        static void link(node_pointer_type ch, node_pointer_type par) {
            derived_tree_type::evert(ch), derived_tree_type::expose(par);
            // check un-connectivity
            if (ch == par or node_type::parent(ch)) assert(false);
            node_type::child(par, 1) = ch;
            node_type::parent(ch) = par;
            node_type::update(par);
        }

        static void cut(node_pointer_type ch) {
            derived_tree_type::expose(ch);
            node_pointer_type par = node_type::child(ch, 0);
            assert(par);
            node_type::parent(par) = node_type::child(ch, 0) = nullptr;
            node_type::update(ch);
        }
        static void cut(node_pointer_type u, node_pointer_type v) {
            derived_tree_type::evert(u);
            derived_tree_type::expose(v);
            // check connectivity
            if (node_type::child(v, 0) != u) assert(false);
            node_type::parent(u) = node_type::child(v, 0) = nullptr;
            node_type::update(v);
        }

        static void evert(node_pointer_type u) {
            derived_tree_type::expose(u);
            node_type::reverse_all(u);
            node_type::push(u);
        }

        static bool is_connected(node_pointer_type u, node_pointer_type v) {
            derived_tree_type::expose(u), derived_tree_type::expose(v);
            return u == v or node_type::parent(u);
        }

        static node_pointer_type lca(node_pointer_type u, node_pointer_type v) {
            derived_tree_type::expose(u);
            node_pointer_type a = derived_tree_type::expose(v);
            return u == v or node_type::parent(u) ? a : nullptr;
        }

        static value_type get(node_pointer_type u) {
            // expose(u);
            return node_type::value(u);
        }
        static void set(node_pointer_type u, const value_type& val) {
            derived_tree_type::update_value(u, [&val](const value_type&) { return val; });
        }
        template <typename Fun>
        static void update_value(node_pointer_type u, Fun&& f) {
            derived_tree_type::expose(u);
            node_type::set_value(u, f(node_type::value(u)));
            node_type::update(u);
        }

        static std::vector<node_pointer_type> path_from_root(node_pointer_type u) {
            std::vector<node_pointer_type> res;
            derived_tree_type::expose(u);
            auto dfs = [&](auto dfs, node_pointer_type cur) -> void {
                node_type::push(cur);
                if (node_type::child(cur, 0)) dfs(dfs, node_type::child(cur, 0));
                res.push_back(cur);
                if (node_type::child(cur, 1)) dfs(dfs, node_type::child(cur, 1));
            };
            dfs(dfs, u);
            return res;
        }
        static std::optional<std::vector<node_pointer_type>> path(node_pointer_type u, node_pointer_type v) {
            derived_tree_type::evert(u);
            derived_tree_type::expose(v);
            if (u == v or node_type::parent(u)) return derived_tree_type::path_from_root(v);
            return std::nullopt;
        }
    
    private:
        static inline ObjectPool<node_type> _pool{};
    };
} // namespace suisen

#endif // SUISEN_LINK_CUT_TREE_BASE
