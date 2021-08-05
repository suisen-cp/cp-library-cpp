#ifndef SUISEN_SUBSET_CONVOLUTION
#define SUISEN_SUBSET_CONVOLUTION

#include "library/math/fps.hpp"
#include "library/transform/subset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {

namespace internal {

template <typename T>
struct SubsetTransformFPS : public SubsetTransform<T> {
    static void transform(std::vector<T> &a) {
        SubsetTransform<T>::transform(a);
        int lg = __builtin_ctz(a.size());
        for (auto &v : a) v.pre_inplace(lg);
    }
};

template <typename mint>
auto to_polynomial(const std::vector<mint> &a) {
    int n = a.size();
    assert((-n & n) == n);
    std::vector<FPS<mint>> fs(n);
    for (int i = 0; i < n; ++i) {
        fs[i][__builtin_popcount(i)] = a[i];
    }
    return fs;
}

} // namespace internal

template <typename mint>
using SubsetConvolution = Convolution<FPS<mint>, internal::SubsetTransformFPS>;

template <typename mint, typename ...Args>
std::vector<mint> subset_convolution(Args &&...args) {
    auto fs = SubsetConvolution<mint>::convolution(internal::to_polynomial(args)...);
    int n = fs.size();
    std::vector<mint> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = fs[i][__builtin_popcount(i)];
    }
    return res;
}

} // namespace suisen

#endif // SUISEN_SUBSET_CONVOLUTION
