#ifndef SUISEN_RED_BLACK_TREE_BASE
#define SUISEN_RED_BLACK_TREE_BASE

#include <cassert>
#include <sstream>
#include <string>
#include <tuple>
#include "library/util/object_pool.hpp"

namespace suisen::bbst::internal {
    template <typename T, typename Derived>
    struct RedBlackTreeNodeBase {
        enum RedBlackTreeNodeColor { RED, BLACK };

        using base_type = void;
        using size_type = int;

        using value_type = T;

        using node_type = Derived;
        using tree_type = node_type*;

        using color_type = RedBlackTreeNodeColor;

        RedBlackTreeNodeBase() = default;

        static inline ObjectPool<node_type> pool{};

        static void init_pool(int siz) { pool = ObjectPool<node_type>(siz); }
        static int node_num() { return pool.size(); }

        static tree_type empty_tree() { return nullptr; }

        static size_type size(tree_type node) { return node ? node->_siz : 0; }
        static bool empty(tree_type node) { return not node; }

        template <bool force_black_root = true>
        static tree_type merge(tree_type l, tree_type r) {
            if (not l) return r;
            if (not r) return l;

            tree_type res = nullptr;
            if (size_type hl = height(l), hr = height(r); hl > hr) {
                l = node_type::push(l);
                tree_type c = l->_ch[1] = merge<false>(l->_ch[1], r);
                if (l->_col == BLACK and c->_col == RED and color(c->_ch[1]) == RED) {
                    std::swap(l->_col, c->_col);
                    if (std::exchange(l->_ch[0]->_col, BLACK) == BLACK) return rotate(l, 1);
                }
                res = node_type::update(l);
            } else if (hr > hl) {
                r = node_type::push(r);
                tree_type c = r->_ch[0] = merge<false>(l, r->_ch[0]);
                if (r->_col == BLACK and c->_col == RED and color(c->_ch[0]) == RED) {
                    std::swap(r->_col, c->_col);
                    if (std::exchange(r->_ch[1]->_col, BLACK) == BLACK) return rotate(r, 0);
                }
                res = node_type::update(r);
            } else {
                res = create_branch(l, r);
            }
            if constexpr (force_black_root) res->_col = BLACK;
            return res;
        }

        static std::pair<tree_type, tree_type> split(tree_type node, size_type k) {
            if (not node) return { nullptr, nullptr };
            node = node_type::push(node);
            if (k == 0) return { nullptr, node };
            if (k == size(node)) return { node, nullptr };

            tree_type l = std::exchange(node->_ch[0], nullptr);
            tree_type r = std::exchange(node->_ch[1], nullptr);

            free_node(node);

            if (color(l) == RED) l->_col = BLACK;
            if (color(r) == RED) r->_col = BLACK;

            size_type szl = size(l);
            tree_type m;
            if (k < szl) {
                std::tie(l, m) = split(l, k);
                return { l, merge(m, r) };
            }
            if (k > szl) {
                std::tie(m, r) = split(r, k - szl);
                return { merge(l, m), r };
            }
            return { l, r };
        }

        static std::tuple<tree_type, tree_type, tree_type> split_range(tree_type node, size_type l, size_type r) {
            auto [tlm, tr] = split(node, r);
            auto [tl, tm] = split(tlm, l);
            return { tl, tm, tr };
        }

        static tree_type insert(tree_type node, size_type k, const value_type& val) {
            auto [tl, tr] = split(node, k);
            return merge(merge(tl, create_leaf(val)), tr);
        }
        static tree_type push_front(tree_type node, const value_type &val) { return insert(node, 0, val); }
        static tree_type push_back(tree_type node, const value_type &val) { return insert(node, size(node), val); }

        static std::pair<tree_type, value_type> erase(tree_type node, size_type k) {
            auto [tl, tm, tr] = split_range(node, k, k + 1);
            value_type erased_value = tm->_val;
            free_node(tm);
            return { merge(tl, tr) , erased_value };
        }
        static std::pair<tree_type, value_type> pop_front(tree_type node) { return erase(node, 0); }
        static std::pair<tree_type, value_type> pop_back(tree_type node) { return erase(node, size(node) - 1); }

        template <typename Fun>
        static tree_type update_value(tree_type node, size_type k, Fun &&fun) {
            auto [tl, top, tr] = split_range(node, k, k + 1);
            top->_val = fun(top->_val);
            return merge(merge(tl, top), tr);
        }
        static tree_type set(tree_type node, size_type k, value_type val) {
            return update_value(node, k, [&val]{ return val; });
        }
        static std::pair<tree_type, value_type> get(tree_type node, size_type k) {
            auto [tl, top, tr] = split_range(node, k, k + 1);
            value_type res = top->_val;
            return { merge(merge(tl, top), tr), res };
        }

        template <typename Seq>
        static tree_type build(const Seq& a, int l, int r) {
            if (r - l == 1) return create_leaf(a[l]);
            int m = (l + r) >> 1;
            return merge(build(a, l, m), build(a, m, r));
        }
        template <typename Seq>
        static tree_type build(const Seq& a) {
            return a.empty() ? empty_tree() : build(a, 0, a.size());
        }

        template <typename OutputIterator>
        static void dump(tree_type node, OutputIterator it) {
            if (empty(node)) return;
            auto dfs = [&](auto dfs, tree_type cur) -> void {
                if (cur->is_leaf()) {
                    *it++ = cur->_val;
                    return;
                }
                dfs(dfs, cur->_ch[0]);
                dfs(dfs, cur->_ch[1]);
            };
            dfs(dfs, node);
        }

        // Don't use on persistent tree.
        static void free(tree_type node) {
            auto dfs = [&](auto dfs, tree_type cur) -> void {
                if (not cur) return;
                dfs(dfs, cur->_ch[0]);
                dfs(dfs, cur->_ch[1]);
                free_node(cur);
            };
            dfs(dfs, node);
        }

        template <typename ToStr>
        static std::string to_string(tree_type node, ToStr f) {
            std::vector<value_type> dat;
            node_type::dump(node, std::back_inserter(dat));
            std::ostringstream res;
            int siz = dat.size();
            res << '[';
            for (int i = 0; i < siz; ++i) {
                res << f(dat[i]);
                if (i != siz - 1) res << ", ";
            }
            res << ']';
            return res.str();
        }
        static std::string to_string(tree_type node) {
            return to_string(node, [](const auto &e) { return e; });
        }

        static void check_rbtree_properties(tree_type node) {
            assert(color(node) == BLACK);
            auto dfs = [&](auto dfs, tree_type cur) -> int {
                if (not cur) return 0;
                if (cur->_col == RED) {
                    assert(color(cur->_ch[0]) == BLACK);
                    assert(color(cur->_ch[1]) == BLACK);
                }
                int bl = dfs(dfs, cur->_ch[0]);
                int br = dfs(dfs, cur->_ch[1]);
                assert(bl == br);
                return bl + (cur->_col == BLACK);
            };
            dfs(dfs, node);
        }

    protected:
        color_type _col;
        tree_type _ch[2]{ nullptr, nullptr };
        value_type _val;
        size_type _siz, _lev;

        RedBlackTreeNodeBase(const value_type& val) : _col(BLACK), _val(val), _siz(1), _lev(0) {}
        RedBlackTreeNodeBase(tree_type l, tree_type r) : _col(RED), _ch{ l, r }, _siz(l->_siz + r->_siz), _lev(l->_lev + (l->_col == BLACK)) {}

        static void clear_pool() { pool.clear(); }
        static int pool_capacity() { return pool.capacity(); }

        static color_type color(tree_type node) { return node ? node->_col : BLACK; }
        static size_type height(tree_type node) { return node ? node->_lev : 0; }

        bool is_leaf() const { return not (_ch[0] or _ch[1]); }

        static tree_type clone(tree_type node) {
            return node;
        }
        static tree_type update(tree_type node) {
            node->_siz = node->is_leaf() ? 1 : size(node->_ch[0]) + size(node->_ch[1]);
            node->_lev = node->_ch[0] ? height(node->_ch[0]) + (node->_ch[0]->_col == BLACK) : 0;
            return node;
        }
        static tree_type push(tree_type node) {
            return node;
        }

        static tree_type rotate(tree_type node, int index) {
            node = node_type::push(node);
            tree_type ch_node = node_type::push(node->_ch[index]);
            node->_ch[index] = std::exchange(ch_node->_ch[index ^ 1], node);
            return node_type::update(node), node_type::update(ch_node);
        }

        static tree_type create_leaf(const value_type& val = value_type{}) {
            return &(*pool.alloc() = node_type(val));
        }

        static tree_type create_branch(tree_type l, tree_type r) {
            return node_type::update(&(*pool.alloc() = node_type(l, r)));
        }

        static void free_node(tree_type node) {
            if (node) pool.free(node);
        }
    };
} // namespace suisen

#endif // SUISEN_RED_BLACK_TREE_BASE
