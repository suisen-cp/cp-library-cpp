#ifndef SUISEN_LINK_CUT_TREE
#define SUISEN_LINK_CUT_TREE

#include "library/tree/link_cut_tree_base.hpp"

namespace suisen {
    namespace internal::link_cut_tree {
        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>
        struct PathFoldableSplayTreeNode : public SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T, op, e, toggle>> {
            using base_node_type = SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T, op, e, toggle>>;
            
            template <typename, typename>
            friend struct SplayTreeNodeBase;
            template <typename, typename>
            friend struct LinkCutTreeBase;
            template <typename T2, T2(*)(T2, T2), T2(*)(), T2(*)(T2)>
            friend struct LinkCutTreePathFoldable;

            using value_type = typename base_node_type::value_type;
            using node_type = typename base_node_type::node_type;
            using node_pointer_type = typename base_node_type::node_pointer_type;

            explicit PathFoldableSplayTreeNode(const value_type& val = e()) : base_node_type(val), _sum(val) {}

        protected:
            value_type _sum;

            static value_type sum(node_pointer_type node) {
                return node ? node->_sum : e();
            }
            static void update(node_pointer_type node) {
                base_node_type::update(node);
                node->_sum = op(op(node_type::sum(node_type::child(node, 0)), node_type::value(node)), node_type::sum(node_type::child(node, 1)));
            }

            static void reverse_all(node_pointer_type node) {
                if (not node) return;
                base_node_type::reverse_all(node);
                node->_sum = toggle(node->_sum);
            }
        };

        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>
        struct LinkCutTreePathFoldable : public LinkCutTreeBase<PathFoldableSplayTreeNode<T, op, e, toggle>, LinkCutTreePathFoldable<T, op, e, toggle>> {
            using base_type = LinkCutTreeBase<PathFoldableSplayTreeNode<T, op, e, toggle>, LinkCutTreePathFoldable<T, op, e, toggle>>;
            using node_type = PathFoldableSplayTreeNode<T, op, e, toggle>;
            using node_pointer_type = typename node_type::node_pointer_type;
            using value_type = typename node_type::value_type;

            static value_type prod_from_root(node_pointer_type u) {
                base_type::expose(u);
                return node_type::sum(u);
            }
            static value_type prod(node_pointer_type u, node_pointer_type v) {
                base_type::evert(u);
                base_type::expose(v);
                // check connectivity
                if (not (u == v or node_type::parent(u))) assert(false);
                return node_type::sum(v);
            }
        };
    } // namespace internal::link_cut_tree
    
    using internal::link_cut_tree::LinkCutTreePathFoldable;
} // namespace suisen

#endif // SUISEN_LINK_CUT_TREE
