#ifndef SUISEN_SEGMENT_TREE_BEATS
#define SUISEN_SEGMENT_TREE_BEATS

#include "library/datastructure/segment_tree/lazy_segment_tree.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    using SegmentTreeBeats = LazySegmentTree<T, op, e, F, mapping, composition, id, /* enable_beats = */ true>;
} // namespace suisen

#endif // SUISEN_SEGMENT_TREE_BEATS
