#ifndef SUISEN_BINOMIAL_COEFFICIENT
#define SUISEN_BINOMIAL_COEFFICIENT

#include <vector>

namespace suisen {
    template <typename T>
    std::vector<std::vector<T>> binom_table(int n) {
        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n + 1));
        for (int i = 0; i <= n; ++i) {
            binom[i][0] = binom[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
            }
        }
        return binom;
    }
} // namespace suisen


#endif // SUISEN_BINOMIAL_COEFFICIENT
