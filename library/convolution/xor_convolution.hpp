#ifndef SUISEN_XOR_CONVOLUTION
#define SUISEN_XOR_CONVOLUTION

#include "library/transform/walsh_hadamard.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {
template <typename T>
using XorConvolution = Convolution<T, WalshHadamard>;
template <typename T, typename ...Args>
std::vector<T> xor_convolution(Args &&...args) {
    return XorConvolution<T>::convolution(std::forward<Args>(args)...);
}
} // namespace suisen

#endif // SUISEN_XOR_CONVOLUTION
