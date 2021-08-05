#ifndef SUISEN_WALSH_HADAMARD_TRANSFORM
#define SUISEN_WALSH_HADAMARD_TRANSFORM

#include <cassert>
#include <vector>

namespace suisen {

namespace internal {

template <typename T>
void fwht(std::vector<T>& a, bool rev) {
    const int n = a.size();
    assert((-n & n) == n);
    for (int i = 1; i < n; i *= 2) {
        for (int k = 0; k < n; k += i * 2) {
            for (int j = k; j < k + i; ++j) {
                T u = a[j], v = a[j + i];
                a[j] = u + v;
                a[j + i] = u - v;
            }
        }
    }
    if (rev) {
        T inv = T(1) / T(n);
        for (int i = 0; i < n; i++) a[i] *= inv;
    }
}

} // nemaspace internal

template <typename T>
struct WalshHadamard {
    static void transform(std::vector<T> &a) {
        internal::fwht(a, false);
    }
    static void inverse_transform(std::vector<T> &a) {
        internal::fwht(a, true);
    }
};

} // namespace suisen::walsh_hadamard_transform


#endif // SUISEN_WALSH_HADAMARD_TRANSFORM
