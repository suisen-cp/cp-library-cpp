#ifndef SUISEN_CUMULATIVE_SUM
#define SUISEN_CUMULATIVE_SUM

#include <cassert>
#include <vector>
#include "library/util/default_operator.hpp"

namespace suisen {
    template <typename T, auto zero = default_operator::zero<T>, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
    struct CumulativeSum {
        CumulativeSum() {}
        CumulativeSum(const std::vector<T> &a) : n(a.size()), s(n + 1, zero()) {
            for (size_t i = 0; i < n; ++i) s[i + 1] = add(a[i], s[i]);
        }
        T operator()(size_t l, size_t r) const {
            assert(l <= r and r <= n);
            return sub(s[r], s[l]);
        }
    private:
        size_t n;
        std::vector<T> s;
    };
}

#endif // SUISEN_CUMULATIVE_SUM
