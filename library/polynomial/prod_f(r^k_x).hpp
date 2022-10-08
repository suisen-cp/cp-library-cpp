#ifndef SUISEN_PROD_F_RK_X
#define SUISEN_PROD_F_RK_X

#include "library/math/pow_mods.hpp"

/**
 * @brief $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
 */

namespace suisen {
    namespace internal::prod_f_rk_x {
        template <typename FPSType>
        FPSType prod_f_rk_x(FPSType f, typename FPSType::value_type r, int m, int result_size) {
            using mint = typename FPSType::value_type;
            pow_mods<mint> pow_r(r, result_size), pow_rm(r.pow(m), result_size);
            if (auto opt_sp_f = f.sparse_fps_format(15); opt_sp_f.has_value()) {
                bool all_invertible = true;
                for (int i = 1; i < result_size; ++i) {
                    if (pow_r[i] == mint{ 1 }) {
                        all_invertible = false;
                        break;
                    }
                }
                if (all_invertible) {
                    auto &sp_f = *opt_sp_f;
                    sp_f.erase(sp_f.begin());
                    FPSType g(result_size);
                    g[0] = 1;
                    for (int i = 1; i < result_size; ++i) {
                        for (auto [j, fj] : sp_f) {
                            if (j > i) break;
                            g[i] += g[i - j] * fj * (pow_r[i - j] - pow_rm[j]);
                        }
                        g[i] /= 1 - pow_r[i];
                    }
                    return g;
                }
            }
            f = f.log(result_size);
            for (int i = 1; i < result_size; ++i) f[i] *= pow_r[i] == mint{ 1 } ? mint{ m } : (pow_rm[i] - 1) / (pow_r[i] - 1);
            return f.exp(result_size);
        }
    }
    /**
     * \brief Calculates Π[k=0,m-1] f(r^k x) mod x^N in O(NlogN) time.
     * \tparam FPSType type of formal power series
     * \param f formal power series
     * \param r ratio
     * \param m the number of terms of the product
     * \param result_size N (default: size of f)
     * \return Π[k=0,m-1] f(r^k x) mod x^N 
     */
    template <typename FPSType>
    FPSType prod_f_rk_x(FPSType f, const typename FPSType::value_type r, const int m, int result_size = -1) {
        using mint = typename FPSType::value_type;
        if (result_size < 0) result_size = f.size();
        if (r == mint{ 1 }) return f.pow(m, result_size);
        if (m == 0) { FPSType res{ 1 }; res.resize(result_size); return res; }
        int z = 0;
        while (z < int(f.size()) and f[z] == mint{ 0 }) ++z;
        if (z == int(f.size()) or z >= (result_size + m - 1) / m) return FPSType(result_size, mint{ 0 });
        const mint c = f[z], d = c.pow(m) * r.pow((long long) m * (m - 1) / 2 * z);
        f >>= z, f /= c; // => f[0] = 1
        f = internal::prod_f_rk_x::prod_f_rk_x(f, r, m, result_size - z * m);
        f *= d, f <<= z * m;
        return f;
    }
} // namespace suisen

#endif // SUISEN_PROD_F_RK_X
