#ifndef SUISEN_XOR_CONVOLUTION
#define SUISEN_XOR_CONVOLUTION

#include "library/transform/walsh_hadamard.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>,
        auto div = default_operator::div<T>,
        std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr
    >
        auto xor_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            walsh_hadamard_transform::walsh_hadamard<T, add, sub>,
            walsh_hadamard_transform::walsh_hadamard_inv<T, add, sub, div>,
            mul
        >(std::move(a), std::move(b));
    }

    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>,
        auto inv = default_operator::inv<T>,
        std::enable_if_t<std::negation_v<std::is_integral<T>>, std::nullptr_t> = nullptr
    >
        auto xor_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            walsh_hadamard_transform::walsh_hadamard<T, add, sub>,
            walsh_hadamard_transform::walsh_hadamard_inv<T, add, sub, mul, inv>,
            mul
        >(std::move(a), std::move(b));
    }
} // namespace suisen

#endif // SUISEN_XOR_CONVOLUTION
