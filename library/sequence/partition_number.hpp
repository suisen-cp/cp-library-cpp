#ifndef SUISEN_PARTITON_NUMBER
#define SUISEN_PARTITON_NUMBER

#include "library/polynomial/fps.hpp"
#include "library/math/factorial.hpp"

namespace suisen {
    template <typename mint>
    std::vector<mint> partition_number(int n) {
        FPS<mint> inv(n + 1);
        inv[0] = 1;
        for (int i = 1, k = 1; k <= n; k += 3 * i + 1, i++) {
            if (i & 1) --inv[k];
            else ++inv[k];
        }
        for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {
            if (i & 1) --inv[k];
            else ++inv[k];
        }
        inv.inv_inplace(n), inv.resize(n + 1);
        return inv;
    }
} // namespace suisen

#endif // SUISEN_PARTITON_NUMBER
