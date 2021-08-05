#ifndef SUISEN_AND_CONVOLUTION
#define SUISEN_AND_CONVOLUTION

#include "library/transform/supset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
template <typename T>
using AndConvolution = Convolution<T, SupsetTransform>;
template <typename T, typename ...Args>
std::vector<T> and_convolution(Args &&...args) {
    return AndConvolution<T>::convolution(std::forward<Args>(args)...);
}
} // namespace suisen

#endif // SUISEN_AND_CONVOLUTION
