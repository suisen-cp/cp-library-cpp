#ifndef SUISEN_RED_BLACK_TREE
#define SUISEN_RED_BLACK_TREE

#include "library/datastructure/bbst/red_black_tree_base.hpp"

namespace suisen::bbst {
    template <typename T, template <typename, typename> typename BaseNode = internal::RedBlackTreeNodeBase>
    struct RedBlackTreeNode : public BaseNode<T, RedBlackTreeNode<T, BaseNode>> {
        using base_type = BaseNode<T, RedBlackTreeNode<T, BaseNode>>;
        using node_type = typename base_type::node_type;
        using tree_type = typename base_type::tree_type;
        using size_type = typename base_type::size_type;
        using value_type = typename base_type::value_type;

        friend base_type;
        friend typename base_type::base_type;

        RedBlackTreeNode() = default;

    private:
        RedBlackTreeNode(const value_type& val) : base_type(val) {}
        RedBlackTreeNode(tree_type l, tree_type r) : base_type(l, r) {}
    };
}

#endif // SUISEN_RED_BLACK_TREE
