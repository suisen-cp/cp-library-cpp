#ifndef SUISEN_RED_BLACK_REVERSIBLE_LAZY_SEGMENT_TREE
#define SUISEN_RED_BLACK_REVERSIBLE_LAZY_SEGMENT_TREE

#include "library/datastructure/bbst/red_black_tree_base.hpp"

namespace suisen::bbst::reversible_lazy_segtree {
    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)(), template <typename, typename> typename BaseNode = internal::RedBlackTreeNodeBase>
    struct RedBlackTreeNode : public BaseNode<T, RedBlackTreeNode<T, op, e, F, mapping, composition, id, BaseNode>> {
        using base_type = BaseNode<T, RedBlackTreeNode<T, op, e, F, mapping, composition, id, BaseNode>>;
        using node_type = typename base_type::node_type;
        using tree_type = typename base_type::tree_type;
        using size_type = typename base_type::size_type;
        using value_type = typename base_type::value_type;
        using operator_type = F;

        friend base_type;
        friend typename base_type::base_type;

        RedBlackTreeNode() : base_type() {}

        static std::pair<tree_type, value_type> prod(tree_type node, size_type l, size_type r) {
            auto [tl, tm, tr] = base_type::split_range(node, l, r);
            value_type res = value(tm);
            return { base_type::merge(base_type::merge(tl, tm), tr), res };
        }
        static value_type prod_all(tree_type node) {
            return value(node);
        }

        static tree_type apply(tree_type node, size_type l, size_type r, const operator_type& f) {
            auto [tl, tm, tr] = base_type::split_range(node, l, r);
            return base_type::merge(base_type::merge(tl, apply_all(tm, f)), tr);
        }
        static tree_type apply_all(tree_type node, const operator_type& f) {
            if (not node) return node;
            node = base_type::clone(node);
            node->_val = mapping(f, node->_val, base_type::size(node));
            node->_laz = composition(f, node->_laz);
            return node;
        }

        static tree_type reverse(tree_type node, size_type l, size_type r) {
            auto [tl, tm, tr] = base_type::split_range(node, l, r);
            return base_type::merge(base_type::merge(tl, reverse_all(tm)), tr);
        }
        static tree_type reverse_all(tree_type node) {
            if (not node) return node;
            node = base_type::clone(node);
            std::swap(node->_ch[0], node->_ch[1]);
            node->_rev ^= true;
            return node;
        }

        template <typename OutputIterator>
        static void dump(tree_type node, OutputIterator it) {
            if (base_type::empty(node)) return;
            auto dfs = [&](auto dfs, tree_type cur, operator_type laz, bool rev) -> void {
                if (cur->is_leaf()) {
                    *it++ = mapping(laz, cur->_val, 1);
                    return;
                }
                operator_type next_laz = composition(laz, cur->_laz);
                bool next_rev = rev ^ cur->_rev;
                dfs(dfs, cur->_ch[rev], next_laz, next_rev);
                dfs(dfs, cur->_ch[not rev], next_laz, next_rev);
            };
            dfs(dfs, node, id(), false);
        }

    private:
        operator_type _laz;
        bool _rev;

        RedBlackTreeNode(const value_type& val) : base_type(val), _laz(id()), _rev(false) {}
        RedBlackTreeNode(tree_type l, tree_type r) : base_type(l, r), _laz(id()), _rev(false) {}

        static value_type value(tree_type node) { return node ? node->_val : e(); }

        static tree_type update(tree_type node) {
            base_type::update(node);
            node->_val = op(value(node->_ch[0]), value(node->_ch[1]));
            return node;
        }
        static tree_type push(tree_type node) {
            node = base_type::clone(node);
            if (node->_laz != id()) {
                node->_ch[0] = apply_all(node->_ch[0], node->_laz);
                node->_ch[1] = apply_all(node->_ch[1], node->_laz);
                node->_laz = id();
            }
            if (node->_rev) {
                node->_ch[0] = reverse_all(node->_ch[0]);
                node->_ch[1] = reverse_all(node->_ch[1]);
                node->_rev = false;
            }
            return node;
        }
    };
}

#endif // SUISEN_RED_BLACK_REVERSIBLE_LAZY_SEGMENT_TREE
