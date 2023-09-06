#ifndef SUISEN_SUM_POWERS
#define SUISEN_SUM_POWERS

#include "library/math/pow_mods.hpp"
#include "library/sequence/bernoulli_number.hpp"

namespace suisen {
    // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent (O(k log k), where k=max_exponent)
    template <typename FPSType>
    auto sum_of_powers(int n, int max_exponent, const std::vector<typename FPSType::value_type> &bernoulli_table) {
        const int k = max_exponent;
        assert(bernoulli_table.size() >= size_t(k + 2));
        using fps = FPSType;
        using mint = typename FPSType::value_type;

        factorial<mint> fac(k + 1);
        pow_mods<mint> pow_n(n, k + 1);

        fps f(k + 2);
        for (int j = 0; j <= k + 1; ++j) {
            f[j] = pow_n[j] * fac.fac_inv(j);
        }
        std::vector<mint> b(bernoulli_table.begin(), bernoulli_table.begin() + (k + 2));
        b[1] *= -1; // b[1] = +1/2
        for (int j = 0; j <= k + 1; ++j) {
            b[j] *= fac.fac_inv(j);
        }
        f *= b;

        std::vector<mint> res(k + 1);
        for (int p = 0; p <= k; ++p) {
            res[p] = fac.fac(p) * (f[p + 1] - b[p + 1]);
        }
        return res;
    }

    // res[p] = 1^p + 2^p + ... + n^p for p=0, ..., max_exponent (O(k log k), where k=max_exponent)
    template <typename FPSType>
    auto sum_of_powers(int n, int max_exponent) {
        return sum_of_powers<FPSType>(n, max_exponent, bernoulli_number<FPSType>(max_exponent + 1));
    }
} // namespace suisen

#endif // SUISEN_SUM_POWERS
