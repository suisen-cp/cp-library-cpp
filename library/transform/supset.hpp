#ifndef SUISEN_SUPSET_TRANSFORM
#define SUISEN_SUPSET_TRANSFORM

#include <cassert>
#include <vector>

namespace suisen::supset_transform {

template <typename T>
void zeta(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1; k < (1 << n); k <<= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[l + p] += f[m + p];
        }
    }
}

template <typename T>
void mobius(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1; k < (1 << n); k <<= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[l + p] -= f[m + p];
        }
    }
}

} // namespace suisen::supset_transform


#endif // SUISEN_SUPSET_TRANSFORM
