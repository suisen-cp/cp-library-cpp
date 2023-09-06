#ifndef SUISEN_MIN_PLUS_CONVOLUTION
#define SUISEN_MIN_PLUS_CONVOLUTION

#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

#include "library/algorithm/monotone_minima.hpp"

namespace suisen {
    template <typename T>
    std::vector<T> min_plus_convolution_convex_convex(const std::vector<T> &a, const std::vector<T> &b) {
        const int n = a.size(), m = b.size();
        assert(n and m);
        // check if convex
        for (int i = 2; i < n; ++i) assert(a[i - 1] - a[i - 2] <= a[i] - a[i - 1]);
        // check if convex
        for (int j = 2; j < m; ++j) assert(b[j - 1] - b[j - 2] <= b[j] - b[j - 1]);

        std::vector<T> c(n + m - 1);
        c[0] = a[0] + b[0];
        for (int k = 0, i = 0; k < n + m - 2; ++k) {
            int j = k - i;
            if (j == m - 1 or (i < n - 1 and a[i + 1] + b[j] < a[i] + b[j + 1])) {
                c[k + 1] = a[++i] + b[j];
            } else {
                c[k + 1] = a[i] + b[++j];
            }
        }
        return c;
    }

    template <typename T>
    std::vector<T> min_plus_convolution_convex_arbitrary(const std::vector<T> &a, const std::vector<T> &b) {
        const int n = a.size(), m = b.size();
        assert(n and m);
        // check if convex
        for (int i = 2; i < n; ++i) assert(a[i - 1] - a[i - 2] <= a[i] - a[i - 1]);

        std::vector<int> argmin = monotone_minima(
            n + m - 1, m,
            [&](int k, int j1, int j2) {
                const int i1 = k - j1, i2 = k - j2;
                // upper right triangle
                if (i2 < 0) return true;
                // lower left triangle
                if (i1 >= n) return false;
                return a[i1] + b[j1] < a[i2] + b[j2];
            }
        );
        std::vector<T> c(n + m - 1);
        for (int k = 0; k < n + m - 1; ++k) {
            const int j = argmin[k], i = k - j;
            c[k] = a[i] + b[j];
        }
        return c;
    }
} // namespace suisen

#endif // SUISEN_MIN_PLUS_CONVOLUTION
