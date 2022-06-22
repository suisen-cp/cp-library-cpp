#ifndef SUISEN_LINK_CUT_TREE_LAZY
#define SUISEN_LINK_CUT_TREE_LAZY

#include "library/tree/link_cut_tree_base.hpp"

namespace suisen {
    namespace internal::link_cut_tree {
        template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)(), T(*toggle)(T)>
        struct PathFoldableSplayTreeNodeLazy : SplayTreeNodeBase<T, PathFoldableSplayTreeNodeLazy<T, op, e, F, mapping, composition, id, toggle>> {
            using base_node_type = SplayTreeNodeBase<T, PathFoldableSplayTreeNodeLazy<T, op, e, F, mapping, composition, id, toggle>>;
            
            template <typename, typename>
            friend struct SplayTreeNodeBase;
            template <typename, typename>
            friend struct LinkCutTreeBase;
            template <typename T2, T2(*)(T2, T2), T2(*)(), typename F2, T2(*)(F2, T2, int), F2(*)(F2, F2), F2(*)(), T2(*)(T2)>
            friend struct LinkCutTreePathFoldableLazy;

            using value_type = typename base_node_type::value_type;
            using operator_type = F;
            using node_type = typename base_node_type::node_type;
            using node_pointer_type = typename base_node_type::node_pointer_type;

            explicit PathFoldableSplayTreeNodeLazy(const value_type& val = e()) : base_node_type(val), _sum(val) {}

        protected:
            value_type _sum;
            operator_type _laz = id();

            static value_type sum(node_pointer_type node) {
                return node ? node->_sum : e();
            }
            static void update(node_pointer_type node) {
                base_node_type::update(node);
                node->_sum = op(op(node_type::sum(node_type::child(node, 0)), node_type::value(node)), node_type::sum(node_type::child(node, 1)));
            }
            static void apply_all(node_pointer_type node, const operator_type& f) {
                if (not node) return;
                node->_laz = composition(f, node->_laz);
                node_type::set_value(node, mapping(f, node_type::value(node), 1));
                node->_sum = mapping(f, node->_sum, node_type::size(node));
            }
            static void reverse_all(node_pointer_type node) {
                if (not node) return;
                base_node_type::reverse_all(node);
                node->_sum = toggle(node->_sum);
            }
            static void push(node_pointer_type node) {
                apply_all(node_type::child(node, 0), node->_laz);
                apply_all(node_type::child(node, 1), node->_laz);
                node->_laz = id();
                base_node_type::push(node);
            }
        };

        template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)(), T(*toggle)(T)>
        struct LinkCutTreePathFoldableLazy : LinkCutTreeBase<PathFoldableSplayTreeNodeLazy<T, op, e, F, mapping, composition, id, toggle>, LinkCutTreePathFoldableLazy<T, op, e, F, mapping, composition, id, toggle>> {
            using base_type = LinkCutTreeBase<PathFoldableSplayTreeNodeLazy<T, op, e, F, mapping, composition, id, toggle>, LinkCutTreePathFoldableLazy<T, op, e, F, mapping, composition, id, toggle>>;
            using node_type = typename base_type::node_type;
            using node_pointer_type = typename node_type::node_pointer_type;
            using value_type = typename node_type::value_type;
            using operator_type = typename node_type::operator_type;

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

            static value_type get(node_pointer_type u) {
                base_type::expose(u);
                return node_type::value(u);
            }

            static void apply_from_root(node_pointer_type u, const operator_type& f) {
                base_type::expose(u);
                node_type::apply_all(u, f);
                node_type::push(u);
            }
            static void apply(node_pointer_type u, node_pointer_type v, const operator_type& f) {
                base_type::evert(u);
                base_type::expose(v);
                assert(u == v or node_type::parent(u)); // check connectivity
                node_type::apply_all(v, f);
                node_type::push(v);
            }
        };
    } // namespace internal::link_cut_tree
    
    using internal::link_cut_tree::LinkCutTreePathFoldableLazy;
} // namespace suisen

#endif // SUISEN_LINK_CUT_TREE_LAZY
