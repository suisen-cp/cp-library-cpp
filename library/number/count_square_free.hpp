#ifndef SUISEN_COUNT_SQ_FREE
#define SUISEN_COUNT_SQ_FREE

#include <cmath>
#include <cstdint>
#include <vector>

#include "library/number/kth_root_round.hpp"

namespace suisen {
    // O(n^(2/5) log log n)
    long long count_square_free(long long n) {
        if (n <= 0) return 0;
        if (n <= 3) return n;

        const int I = std::min<int>(floor_kth_root(n, 5) * 2, floor_kth_root(n / 4, 3));
        // NOTE. floor(sqrt(n/i)) = floor(sqrt(floor(n/i)))
        const int D = ::sqrtl(n / I);

        uint64_t ans = 0;

        std::vector<int> mobius(D + 1);
        mobius[1] = 1;
        std::vector<int8_t> sieve(D + 1, 1);
        for (int p = 2; p <= D; ++p) if (sieve[p]) {
            if (const int vmax = D / p; vmax < p) { // <==> p * p > D, so the sieve is complete.
                for (int v = vmax; v; --v) if (mobius[v]) mobius[v * p] = -mobius[v];
            } else {
                for (int v = vmax; v >= p; --v) {
                    if (mobius[v]) mobius[v * p] = -mobius[v];
                    sieve[v * p] = false;
                }
                for (int v = p - 1; v; --v) if (mobius[v]) mobius[v * p] = -mobius[v];
            }
        }

        for (int i = 1; i <= D; ++i) if (mobius[i]) ans += mobius[i] * (n / (1LL * i * i));

        auto& mertens = mobius;
        for (int i = 1; i <= D; ++i) mertens[i] += mertens[i - 1];

        std::vector<int> mertens_large(I + 1);
        for (int i = I - 1; i >= 1; --i) {
            const int xi = ::sqrtl(n / i);
            const int h = ::sqrt(xi), quo_num = 2 * h - (h == xi / h);
            auto quo = [xi, h, quo_num](int i) -> int {
                return i < h ? i + 1 : double(xi) / (2 * h - (quo_num & 1) - i);
            };
            long long sum = 1;
            for (int t = 1, l = 1; t < quo_num; ++t) {
                int r = quo(t), q = quo(quo_num - t - 1);
                sum -= 1LL * (r - l) * (q <= D ? mertens[q] : mertens_large[i * r * r]);
                l = r;
            }
            ans += (mertens_large[i] = sum);
        }
        return ans - 1LL * (I - 1) * mertens[D];
    }
} // namespace suisen


#endif // SUISEN_COUNT_SQ_FREE
