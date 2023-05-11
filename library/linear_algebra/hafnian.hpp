#ifndef SUISEN_HAFNIAN
#define SUISEN_HAFNIAN

#include "library/math/set_power_series.hpp"

namespace suisen {
    template <typename T, typename U = T, std::enable_if_t<std::is_constructible_v<T, U>, std::nullptr_t> = nullptr>
    T hafnian(const std::vector<std::vector<U>>& mat) {
        const int n = mat.size();
        assert(n % 2 == 0);

        using ZetaSPS = typename SetPowerSeries<T>::ZetaSPS;

        std::vector P(n, std::vector<ZetaSPS>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) {
            P[i][j] = SetPowerSeries<T>{ mat[i][j] }.zeta();
            assert(mat[i][j] == mat[j][i]);
        }
        ZetaSPS h = SetPowerSeries<T>{ 1 }.zeta();
        for (int i = 0; i < n / 2 - 1; ++i) {
            const int lv = n - 2 * (i + 1), rv = lv + 1;

            h.concat(h * P[rv][lv]);

            std::vector<ZetaSPS> zPlr(lv);
            for (int k = 0; k < lv; ++k) {
                zPlr[k] = P[lv][k] * P[rv][k];
            }

            for (int j = 0; j < lv; ++j) for (int k = 0; k < j; ++k) {
                P[j][k].concat((P[lv][j] + P[lv][k]) * (P[rv][j] + P[rv][k]) - zPlr[j] - zPlr[k]);
            }
            P.pop_back(), P.pop_back();
        }
        SetPowerSeries<T> f = h.mobius_inplace(), g = P[1][0].mobius_inplace();
        T res = 0;
        for (int i = 0, siz = h.size(); i < siz; ++i) {
            res += f[i] * g[siz - i - 1];
        }
        return res;
    }
} // namespace suisen

#endif // SUISEN_HAFNIAN
