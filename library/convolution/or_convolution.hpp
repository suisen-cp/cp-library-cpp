#ifndef SUISEN_OR_CONVOLUTION
#define SUISEN_OR_CONVOLUTION

#include "library/transform/subset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
    template <
        typename T,
        auto add = default_operator::add<T>,
        auto sub = default_operator::sub<T>,
        auto mul = default_operator::mul<T>
    >
    auto or_convolution(std::vector<T> a, std::vector<T> b) {
        return convolution::transform_convolution<
            T,
            subset_transform::zeta<T, add>,
            subset_transform::mobius<T, sub>,
            mul
        >(std::move(a), std::move(b));
    }
} // namespace suisen

#endif // SUISEN_OR_CONVOLUTION
