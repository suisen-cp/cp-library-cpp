#ifndef SUISEN_32BIT_POINTER
#define SUISEN_32BIT_POINTER

#include <vector>

namespace suisen {
    template <typename Object>
    struct ptr32 {
        static constexpr int null = -1;

        using object_type = Object;
        using pool_type = std::vector<object_type>;

        constexpr ptr32() : ptr(null) {}
        explicit constexpr ptr32(int ptr) : ptr(ptr) {}

        object_type& operator*() const { return pool[ptr]; }
        object_type* operator->() const { return &pool[ptr]; }

        constexpr operator bool() const { return ptr != null; }
        constexpr operator int() const { return ptr; }

        constexpr bool is_not_null() const { return bool(*this); }
        constexpr bool is_null() const { return not bool(*this); }

        friend constexpr bool operator==(const ptr32& l, const ptr32& r) { return l.ptr == r.ptr; }
        friend constexpr bool operator!=(const ptr32& l, const ptr32& r) { return l.ptr != r.ptr; }
        friend constexpr bool operator<(const ptr32& l, const ptr32& r) { return l.ptr < r.ptr; }
        friend constexpr bool operator<=(const ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }
        friend constexpr bool operator>(const ptr32& l, const ptr32& r) { return l.ptr > r.ptr; }
        friend constexpr bool operator>=(const ptr32& l, const ptr32& r) { return l.ptr >= r.ptr; }

        template <typename ...Args>
        static ptr32 alloc(Args &&...args) {
            if (del.size()) {
                ptr32 ptr(del.back());
                del.pop_back();
                *ptr = object_type(std::forward<Args>(args)...);
                return ptr;
            } else {
                ptr32 ptr(pool.size());
                pool.emplace_back(std::forward<Args>(args)...);
                return ptr;
            }
        }
        static void dealloc(ptr32 p) {
            del.push_back(p);
        }
        static void dealloc_all(bool shrink) {
            pool.clear(), del.clear();
            if (shrink) pool.shrink_to_fit(), del.shrink_to_fit();
        }
        static void reserve(size_t capacity) {
            pool.reserve(capacity);
        }
    private:
        static inline pool_type pool{};
        static inline std::vector<ptr32> del{};

        int ptr;
    };
} // namespace suisen


#endif // SUISEN_32BIT_POINTER
