#ifndef SUISEN_RED_BLACK_SEGMENT_TREE
#define SUISEN_RED_BLACK_SEGMENT_TREE

#include "library/datastructure/bbst/red_black_tree_base.hpp"

namespace suisen::bbst::segtree {
    template <typename T, T(*op)(T, T), T(*e)(), template <typename, typename> typename BaseNode = internal::RedBlackTreeNodeBase>
    struct RedBlackTreeNode : public BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>> {
        using base_type = BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>>;
        using node_type = typename base_type::node_type;
        using tree_type = typename base_type::tree_type;
        using size_type = typename base_type::size_type;
        using value_type = typename base_type::value_type;

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

    private:
        RedBlackTreeNode(const value_type& val) : base_type(val) {}
        RedBlackTreeNode(tree_type l, tree_type r) : base_type(l, r) {}

        static value_type value(tree_type node) { return node ? node->_val : e(); }

        static tree_type update(tree_type node) {
            base_type::update(node);
            node->_val = op(value(node->_ch[0]), value(node->_ch[1]));
            return node;
        }
    };
}

#endif // SUISEN_RED_BLACK_SEGMENT_TREE
