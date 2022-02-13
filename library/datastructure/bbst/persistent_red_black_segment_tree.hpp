#ifndef SUISEN_SUISEN_PERSISTENT_RED_BLACK_SEGMENT_TREE
#define SUISEN_SUISEN_PERSISTENT_RED_BLACK_SEGMENT_TREE

#include "library/datastructure/bbst/persistent_red_black_tree_base.hpp"
#include "library/datastructure/bbst/red_black_segment_tree.hpp"

namespace suisen::bbst::segtree {
    template <typename T, T(*op)(T, T), T(*e)()>
    using PersistentRedBlackTreeNode = RedBlackTreeNode<T, op, e, internal::PersistentRedBlackTreeNodeBase>;
}

#endif // SUISEN_SUISEN_PERSISTENT_RED_BLACK_SEGMENT_TREE
