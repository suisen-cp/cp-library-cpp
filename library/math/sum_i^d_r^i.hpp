#ifndef SUISEN_SUM_I_D_R_I
#define SUISEN_SUM_I_D_R_I

#include "library/sequence/powers.hpp"
#include "library/math/factorial.hpp"
#include "library/math/pow_mods.hpp"
#include "library/polynomial/lagrange_interpolation.hpp"
#include "library/polynomial/shift_of_sampling_points.hpp"

namespace suisen {
    template <typename mint>
    struct sum_i_i_pow_d_r_pow_i {
        sum_i_i_pow_d_r_pow_i(int d, mint r) : d(d), r(r), i_pow_d(powers<mint>(d + 1, d)), r_pow_i(r, d + 1), fac(d), c(calc_c()) {}

        mint sum() const {
            assert(r != 1);
            return c;
        }
        mint sum(long long n) {
            if (r == 0) return n > 0 and d == 0 ? 1 : 0;
            prepare();
            return lagrange_interpolation_arithmetic_progression<mint>(ys, n) * r.pow(n) + c;
        }
        std::vector<mint> sum(long long t, int m) {
            if (r == 0) {
                std::vector<mint> res(m);
                for (long long n = t; n < t + m; ++n) res[n - t] = sum(n);
                return res;
            }
            prepare();
            auto res = shift_of_sampling_points<mint>(ys, t, m);
            mint pr = r.pow(r);
            for (auto &e : res) e *= pr, e += c, pr *= r;
            return res;
        }
    private:
        int d;
        mint r;
        std::vector<mint> i_pow_d;
        pow_mods<mint> r_pow_i;
        factorial<mint> fac;

        mint c;

        std::vector<mint> ys;
        bool prepared = false;

        mint calc_c() {
            if (r == 1) return 0;
            mint num = 0, den = 0, sum = 0;
            for (int i = 0; i <= d + 1; ++i) {
                sum += i_pow_d[i] * r_pow_i[i];
                den += (i & 1 ? -1 : +1) * fac.binom(d + 1, i) * r_pow_i[i];
                num += ((d + 1 - i) & 1 ? -1 : +1) * fac.binom(d + 1, d + 1 - i) * r_pow_i[d + 1 - i] * sum;
            }
            return num / den;
        }

        void prepare() {
            if (prepared) return;
            prepared = true;

            ys.resize(d + 2);
            for (int i = 0; i <= d; ++i) ys[i + 1] = ys[i] + r_pow_i[i] * i_pow_d[i];
            
            if (r == 1) return;

            for (auto& e : ys) e -= c;

            mint inv_r = r.inv();
            mint pow_inv_r = inv_r.pow(d + 1);
            for (int i = d + 1; i >= 0; --i) {
                ys[i] *= pow_inv_r;
                pow_inv_r *= r;
            }
        }
    };
} // namespace suisen


#endif // SUISEN_SUM_I_D_R_I
