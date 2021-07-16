#ifndef SUISEN_FZT_FMT
#define SUISEN_FZT_FMT

#include <cassert>
#include <vector>

namespace suisen {
template <typename T>
void fmt_subset(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[m + p] -= f[l + p];
        }
    }
}
template <typename T>
void fmt_supset(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[l + p] -= f[m + p];
        }
    }
}

template <typename T>
void fzt_subset(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1; k < (1 << n); k <<= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[m + p] += f[l + p];
        }
    }
}
template <typename T>
void fzt_supset(const int n, std::vector<T> &f) {
    int sz = f.size();
    assert(sz == 1 << n);
    for (int k = 1; k < (1 << n); k <<= 1) {
        for (int l = 0; l < (1 << n); l += 2 * k) {
            int m = l + k;
            for (int p = 0; p < k; ++p) f[l + p] += f[m + p];
        }
    }
}
} // namespace suisen

#endif // SUISEN_FZT_FMT
