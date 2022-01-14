#ifndef SUISEN_TUPLE_HASH
#define SUISEN_TUPLE_HASH

#include <cstdint>
#include <tuple>

namespace std {
    namespace {
        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v) {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl {
            static void apply(size_t& seed, Tuple const& t) {
                HashValueImpl<Tuple, Index - 1>::apply(seed, t);
                hash_combine(seed, get<Index>(t));
            }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple, 0> {
            static void apply(size_t& seed, Tuple const& t) {
                hash_combine(seed, get<0>(t));
            }
        };
    }

    template <typename ...Args>
    struct hash<std::tuple<Args...>> {
        size_t operator()(std::tuple<Args...> const& tt) const {
            size_t seed = 0;
            HashValueImpl<std::tuple<Args...>>::apply(seed, tt);
            return seed;
        }
    };
}

#endif // SUISEN_TUPLE_HASH
