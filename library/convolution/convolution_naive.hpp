#ifndef SUISEN_CONVOLUTION_NAIVE
#define SUISEN_CONVOLUTION_NAIVE

#include <vector>

namespace suisen::internal {
    template <typename T>
    std::vector<T> convolution_naive(const std::vector<T>& a, const std::vector<T>& b) {
        const int n = a.size(), m = b.size();
        std::vector<T> c(n + m - 1);
        if (n < m) {
            for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) c[i + j] += a[i] * b[j];
        } else {
            for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];
        }
        return c;
    }
} // namespace suisen


#endif // SUISEN_CONVOLUTION_NAIVE
