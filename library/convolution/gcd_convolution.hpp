#ifndef SUISEN_GCD_CONVOLUTION
#define SUISEN_GCD_CONVOLUTION

#include "library/transform/multiple.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
template <typename T>
using GCDConvolution = Convolution<T, MultipleTransform>;
template <typename T, typename ...Args>
std::vector<T> gcd_convolution(Args &&...args) {
    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);
}
} // namespace suisen

#endif // SUISEN_GCD_CONVOLUTION
