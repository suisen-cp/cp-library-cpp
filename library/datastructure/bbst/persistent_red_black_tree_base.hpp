#ifndef SUISEN_PERSISTENT_RED_BLACK_TREE_BASE
#define SUISEN_PERSISTENT_RED_BLACK_TREE_BASE

#include "library/datastructure/bbst/red_black_tree_base.hpp"

namespace suisen::bbst::internal {
    template <typename T, typename Derived>
    struct PersistentRedBlackTreeNodeBase : public RedBlackTreeNodeBase<T, Derived> {
        using base_type = RedBlackTreeNodeBase<T, Derived>;
        using node_type = typename base_type::node_type;
        using tree_type = typename base_type::tree_type;
        using size_type = typename base_type::size_type;
        using value_type = typename base_type::value_type;

        friend base_type;

        PersistentRedBlackTreeNodeBase() : base_type() {}

        static std::pair<tree_type, tree_type> swap(tree_type t1, int l1, int r1, tree_type t2, int l2, int r2) {
            auto [tl1, tm1, tr1] = base_type::split_range(t1, l1, r1);
            auto [tl2, tm2, tr2] = base_type::split_range(t2, l2, r2);
            return { base_type::merge(base_type::merge(tl1, tm2), tr1), base_type::merge(base_type::merge(tl2, tm1), tr2) };
        }
        static tree_type cut(tree_type node, int l, int r) {
            auto [tl, tm, tr] = base_type::split_range(node, l, r);
            return tm;
        }
        static tree_type replace(tree_type from, tree_type to, int l, int r) {
            const int siz = base_type::size(from);
            auto [res, replaced] = swap(to, l, r, from, 0, siz);
            return res;
        }
        static tree_type replace(tree_type from, tree_type to, int pos) {
            return replace(from, to, pos, pos + base_type::size(from));
        }

        static tree_type rebuild(tree_type node) {
            std::vector<value_type> res;
            node_type::dump(node, std::back_inserter(res));
            base_type::clear_pool();
            return base_type::build(res);
        }

    protected:
        PersistentRedBlackTreeNodeBase(const value_type& val) : base_type(val) {}
        PersistentRedBlackTreeNodeBase(tree_type l, tree_type r) : base_type(l, r) {}

        static tree_type clone(tree_type node) {
            if (not node) return node;
            return &(*base_type::create_leaf() = *node);
        }
    };
}

#endif // SUISEN_PERSISTENT_RED_BLACK_TREE_BASE
