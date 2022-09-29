#ifndef SUISEN_HEAP_TAG
#define SUISEN_HEAP_TAG

#include <type_traits>

namespace suisen {
    namespace internal::heap {
        struct heap_tag_base {};
    }
    struct min_heap_tag : internal::heap::heap_tag_base {
        static constexpr bool is_min_heap = true;
        static constexpr bool is_max_heap = false;
    };
    struct max_heap_tag : internal::heap::heap_tag_base {
        static constexpr bool is_min_heap = false;
        static constexpr bool is_max_heap = true;
    };

    template <typename T>
    struct is_heap_tag {
        static constexpr bool value = std::is_base_of_v<internal::heap::heap_tag_base, T>;
    };
    template <typename T>
    constexpr bool is_heap_tag_v = is_heap_tag<T>::value;
} // namespace suisen


#endif // SUISEN_HEAP_TAG
