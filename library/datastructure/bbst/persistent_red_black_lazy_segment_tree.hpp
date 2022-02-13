#ifndef SUISEN_PERSISTENT_RED_BLACK_LAZY_SEGMENT_TREE
#define SUISEN_PERSISTENT_RED_BLACK_LAZY_SEGMENT_TREE

#include "library/datastructure/bbst/persistent_red_black_tree_base.hpp"
#include "library/datastructure/bbst/red_black_lazy_segment_tree.hpp"

namespace suisen::bbst::lazy_segtree {
    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)()>
    using PersistentRedBlackTreeNode = RedBlackTreeNode<T, op, e, F, mapping, composition, id, internal::PersistentRedBlackTreeNodeBase>;
}

#endif // SUISEN_PERSISTENT_RED_BLACK_LAZY_SEGMENT_TREE
