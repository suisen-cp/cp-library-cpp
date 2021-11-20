#ifndef SUISEN_CUMULATIVE_SUM_2D
#define SUISEN_CUMULATIVE_SUM_2D

#include <cassert>
#include <vector>
#include "library/util/default_operator.hpp"

namespace suisen {
    template <typename T, auto zero = default_operator::zero<T>, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
    struct CumulativeSum2D {
        CumulativeSum2D() {}
        CumulativeSum2D(const std::vector<std::vector<T>> &a) : n(a.size()), m(n == 0 ? 0 : a[0].size()), s(n + 1, std::vector<T>(m + 1, zero())) {
            for (size_t i = 0; i < n; ++i) for (size_t j = 0; j < m; ++j) {
                s[i + 1][j + 1] = sub(add(add(a[i][j], s[i + 1][j]), s[i][j + 1]), s[i][j]);
            }
        }
        T operator()(size_t u, size_t d, size_t l, size_t r) const {
            assert(u <= d and d <= n and l <= r and r <= m);
            return sub(add(s[d][r], s[u][l]), add(s[u][r], s[d][l]));
        }
    private:
        size_t n, m;
        std::vector<std::vector<T>> s;
    };
}

#endif // SUISEN_CUMULATIVE_SUM_2D
