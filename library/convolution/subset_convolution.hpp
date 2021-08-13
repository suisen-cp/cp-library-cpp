#ifndef SUISEN_SUBSET_CONVOLUTION
#define SUISEN_SUBSET_CONVOLUTION

#include <vector>

namespace suisen::internal::arithmetic_operator {
template <typename T>
void operator+=(std::vector<T> &a, const std::vector<T> &b) {
    int n = b.size();
    for (int i = 0; i < n; ++i) a[i] += b[i];
}
template <typename T>
void operator-=(std::vector<T> &a, const std::vector<T> &b) {
    int n = b.size();
    for (int i = 0; i < n; ++i) a[i] -= b[i];
}
template <typename T>
void operator*=(std::vector<T> &a, const std::vector<T> &b) {
    int n = b.size();
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - i - 1; j > 0; --j) a[i + j] += a[i] * b[j];
        a[i] *= b[0];
    }
}
}

#include "library/transform/subset.hpp"
#include "library/convolution/convolution.hpp"

namespace suisen {

namespace internal::subset_convolution {
template <typename T, typename Container>
auto add_rank(const Container &a) {
    int n = a.size();
    assert((-n & n) == n);
    std::vector<std::vector<T>> fs(n, std::vector<T>(__builtin_ctz(n) + 1, T(0)));
    for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];
    return fs;
}
template <typename T>
auto remove_rank(const std::vector<std::vector<T>> &polys) {
    int n = polys.size();
    assert((-n & n) == n);
    std::vector<T> a(n);
    for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];
    return a;
}
} // namespace internal

template <typename T>
using SubsetConvolution = Convolution<std::vector<T>, SubsetTransform>;

template <typename T, typename ...Args>
std::vector<T> subset_convolution(Args &&...args) {
    using namespace internal::subset_convolution;
    return remove_rank<T>(SubsetConvolution<T>::convolution(add_rank<T>(args)...));
}

} // namespace suisen

#endif // SUISEN_SUBSET_CONVOLUTION
