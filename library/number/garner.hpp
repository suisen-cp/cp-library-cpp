#ifndef SUISEN_GARNER
#define SUISEN_GARNER

#include <vector>
#include "library/number/ext_gcd.hpp"

namespace suisen {
    /**
     * @brief Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime each other.
     * @param eq vector of { x_i, m_i }
     * @return x mod m s.t. x = x_i (mod m_i)
     */
    int garner(std::vector<std::pair<int, int>> eq, int m) {
        const int n = eq.size();
        std::vector<long long> a(n);

        auto calc_prefix = [&](int i, long long mod) {
            long long res = 0;
            long long prd = 1;
            for (int j = 0; j < i; ++j) {
                (res += a[j] * prd) %= mod;
                (prd *= eq[j].second) %= mod;
            }
            return res;
        };
    
        for (int i = 0; i < n; ++i) {
            auto [xi, mi] = eq[i];
            a[i] = (xi - calc_prefix(i, mi)) % mi;
            if (a[i] < 0) a[i] += mi;
            for (int j = 0; j < i; ++j) {
                long long mj = eq[j].second;
                a[i] *= inv_mod(mj, mi);
                a[i] %= mi;
            }
        }
        return calc_prefix(n, m);
    }
} // namespace suisen


#endif // SUISEN_GARNER
