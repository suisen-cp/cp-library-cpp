#ifndef SUISEN_DIRICHLET_CONVOLUTION
#define SUISEN_DIRICHLET_CONVOLUTION

#include <vector>
#include <limits>

namespace suisen {

template <typename T>
static std::vector<T> dirichlet_convolution(const std::vector<T> &a, const std::vector<T> &b, const int n) {
    std::vector<T> c(n, T(0));
    const int m = std::min(int(a.size()), n), k = std::min(int(b.size()), n);
    for (int i = 1; i < m; ++i) {
        int jmax = std::min((n + i - 1) / i, k);
        for (int j = 1; j < jmax; ++j) {
            c[i * j] += a[i] * b[j];
        }
    }
    return c;
}

template <typename T>
static std::vector<T> dirichlet_convolution_coprime(const std::vector<T> &a, const std::vector<T> &b, const int n) {
    std::vector<T> c(n, T(0));
    const int m = std::min(int(a.size()), n), k = std::min(int(b.size()), n);
    std::vector<std::vector<int>> dp(m);
    for (int i = 1; i < m; ++i) {
        const int jmax = std::min((n + i - 1) / i, k);
        dp[i].reserve(jmax);
        dp[i].push_back(i);
        for (int j = 1; j < jmax; ++j) {
            int g = i > j ? dp[i - j][j] : dp[i][j - i];
            dp[i].push_back(g);
            if (g == 1) c[i * j] += a[i] * b[j];
        }
    }
    return c;
}

} // namespace suisen


#endif // SUISEN_DIRICHLET_CONVOLUTION
