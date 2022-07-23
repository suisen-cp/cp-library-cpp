#ifndef SUISEN_INVERSION_NUMBER
#define SUISEN_INVERSION_NUMBER

#include <atcoder/fenwicktree>
#include "library/util/coordinate_compressor.hpp"

namespace suisen {
    template <typename T>
    long long inversion_number(const std::vector<T> &a) {
        const int n = a.size();
        const auto cmp = CoordinateCompressorBuilder<T>::build(a);

        long long ans = 0;
        atcoder::fenwick_tree<int> ft(cmp.size());
        for (int i = n - 1; i >= 0; --i) {
            const int j = cmp[a[i]];
            ans += ft.sum(0, j), ft.add(j, 1);
        }
        return ans;
    }
} // namespace suisen

#endif // SUISEN_INVERSION_NUMBER
