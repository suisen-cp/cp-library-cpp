#ifndef SUISEN_PRIORITY_QUEUE
#define SUISEN_PRIORITY_QUEUE

#include "library/datastructure/heap/binary_heap.hpp"

namespace suisen {
    template <typename T, typename Comp = std::less<T>>
    using MinPriorityQueue = suisen::BinaryHeap<T, Comp>;
    template <typename T>
    using MaxPriorityQueue = suisen::BinaryHeap<T, std::greater<T>>;
} // namespace suisen


#endif // SUISEN_PRIORITY_QUEUE
