#ifndef SUISEN_PERSISTENT_RED_BLACK_TREE
#define SUISEN_PERSISTENT_RED_BLACK_TREE

#include "library/datastructure/bbst/persistent_red_black_tree_base.hpp"
#include "library/datastructure/bbst/red_black_tree.hpp"

namespace suisen::bbst {
    template <typename T>
    using PersistentRedBlackTreeNode = RedBlackTreeNode<T, internal::PersistentRedBlackTreeNodeBase>;
}

#endif // SUISEN_PERSISTENT_RED_BLACK_TREE
