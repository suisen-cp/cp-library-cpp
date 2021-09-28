#ifndef SUISEN_AND_CONVOLUTION
#define SUISEN_AND_CONVOLUTION

#include "library/transform/supset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>
    >
    auto and_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            supset_transform::zeta<T, add>,
            supset_transform::mobius<T, sub>,
            mul
        >(std::move(a), std::move(b));
    }
} // namespace suisen

#endif // SUISEN_AND_CONVOLUTION
