#ifndef SUISEN_OR_CONVOLUTION
#define SUISEN_OR_CONVOLUTION

#include "library/transform/subset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
template <typename T>
using OrConvolution = Convolution<T, SubsetTransform>;
template <typename T, typename ...Args>
std::vector<T> or_convolution(Args &&...args) {
    return OrConvolution<T>::convolution(std::forward<Args>(args)...);
}
} // namespace suisen

#endif // SUISEN_OR_CONVOLUTION
