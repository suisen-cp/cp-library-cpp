#ifndef SUISEN_FACTORIZED_FORM
#define SUISEN_FACTORIZED_FORM

#include <type_traits>
#include <tuple>
#include <vector>

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    struct PrimePower {
        T prime;
        int exponent;
        template <std::size_t Index>
        std::tuple_element_t<Index, PrimePower>& get() {
            static_assert(Index < 2);
            if constexpr (Index == 0) return prime;
            if constexpr (Index == 1) return exponent;
        }
        template <std::size_t Index>
        const std::tuple_element_t<Index, PrimePower>& get() const {
            static_assert(Index < 2);
            if constexpr (Index == 0) return prime;
            if constexpr (Index == 1) return exponent;
        }
    };
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    using FactorizedForm = std::vector<PrimePower>;
} // namespace suisen

namespace std {
    template <typename T>
    struct tuple_size<suisen::PrimePower<T>> : std::integral_constant<std::size_t, 2> {};
    template <std::size_t Index, typename T>
    struct tuple_element<Index, suisen::PrimePower<T>> : std::tuple_element<Index, std::tuple<T, int>> {};
}

#endif // SUISEN_FACTORIZED_FORM
