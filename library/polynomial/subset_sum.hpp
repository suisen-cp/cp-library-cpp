#ifndef SUISEN_SUBSET_SUM
#define SUISEN_SUBSET_SUM

#include <vector>

#include "library/math/inv_mods.hpp"

namespace suisen {
    template <typename FPSType>
    std::vector<typename FPSType::value_type> subset_sum(const int n, const std::vector<int>& items) {
        using mint = typename FPSType::value_type;
        std::vector<int> a(n + 1, 0);
        for (int e : items) {
            assert(e >= 0);
            if (e <= n) ++a[e];
        }
        inv_mods<mint> invs(n);
        FPSType log(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 0) continue;
            for (int j = 1; i * j <= n; ++j) {
                if (j & 1) log[i * j] += invs[j] * a[i];
                else       log[i * j] -= invs[j] * a[i];
            }
        }
        log.exp_inplace(n + 1), log.resize(n + 1);
        mint p = mint(2).pow(a[0]);
        for (mint& e : log) e *= p;
        return log;
    }
} // namespace suisen

#endif // SUISEN_SUBSET_SUM
