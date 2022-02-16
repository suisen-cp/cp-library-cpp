#ifndef SUISEN_LCM_CONVOLUTION
#define SUISEN_LCM_CONVOLUTION

#include "library/transform/divisor.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>
    >
    auto lcm_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            divisor_transform::zeta<T, add>,
            divisor_transform::mobius<T, sub>,
            mul
        >(std::move(a), std::move(b));
    }
} // namespace suisen

#endif // SUISEN_LCM_CONVOLUTION
