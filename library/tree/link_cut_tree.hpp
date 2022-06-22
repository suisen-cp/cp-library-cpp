#ifndef SUISEN_LINK_CUT_TREE
#define SUISEN_LINK_CUT_TREE

#include "library/tree/link_cut_tree_base.hpp"

namespace suisen {
    namespace internal::link_cut_tree {
        template <typename T>
        struct SplayTreeNode : public SplayTreeNodeBase<T, SplayTreeNode<T>> {
            using base_node_type = SplayTreeNodeBase<T, SplayTreeNode<T>>;
            
            template <typename, typename>
            friend struct SplayTreeNodeBase;
            template <typename, typename>
            friend struct LinkCutTreeBase;
            template <typename>
            friend struct LinkCutTree;

            using value_type = typename base_node_type::value_type;
            using node_type = typename base_node_type::node_type;
            using node_pointer_type = typename base_node_type::node_pointer_type;

            explicit SplayTreeNode(const value_type& val = value_type{}) : base_node_type(val) {}
        };

        template <typename T>
        struct LinkCutTree : public LinkCutTreeBase<SplayTreeNode<T>, LinkCutTree<T>> {
            using base_type = LinkCutTreeBase<SplayTreeNode<T>, LinkCutTree<T>>;
            using node_type = SplayTreeNode<T>;
            using node_pointer_type = typename node_type::node_pointer_type;
            using value_type = typename node_type::value_type;
        };
    } // namespace internal::link_cut_tree
    
    using internal::link_cut_tree::LinkCutTree;
} // namespace suisen

#endif // SUISEN_LINK_CUT_TREE
