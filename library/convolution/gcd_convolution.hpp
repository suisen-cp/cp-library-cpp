#ifndef SUISEN_GCD_CONVOLUTION
#define SUISEN_GCD_CONVOLUTION

#include "library/transform/multiple.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>
    >
    auto gcd_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            multiple_transform::zeta<T, add>,
            multiple_transform::mobius<T, sub>,
            mul
        >(std::move(a), std::move(b));
    }
} // namespace suisen

#endif // SUISEN_GCD_CONVOLUTION
