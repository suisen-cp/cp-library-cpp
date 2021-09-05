#ifndef SUISEN_BOSTAN_MORI
#define SUISEN_BOSTAN_MORI

#include "library/math/fps.hpp"

namespace suisen {
template <typename mint>
mint bostan_mori(FPS<mint> P, FPS<mint> Q, unsigned long long n) {
    auto alternate = [](FPS<mint> &&a, bool odd) -> FPS<mint>&& {
        std::size_t i = 0;
        for (std::size_t j = odd; j < a.size(); j += 2) a[i++] = a[j];
        a.erase(a.begin() + i, a.end());
        return std::move(a);
    };
    for (; n; n >>= 1) {
        FPS<mint> mQ(Q);
        for (std::size_t i = 1; i < Q.size(); i += 2) mQ[i] = -mQ[i];
        P = alternate(P * mQ, n & 1);
        Q = alternate(Q * mQ,     0);
    }
    return P[0];
}

template <typename mint>
mint nth_term_of_linear_recurrence(const FPS<mint> &a, const FPS<mint> &c, const unsigned long long n) {
    const std::size_t K = c.size();
    assert(K <= a.size());
    FPS<mint> Q(K + 1);
    Q[0] = 1;
    for (std::size_t i = 0; i < K; ++i) {
        Q[i + 1] = -c[i];
    }
    FPS<mint> P = a * Q;
    return bostan_mori(P.pre_inplace(K - 1), Q, n);
}

} // namespace suisen

#endif // SUISEN_BOSTAN_MORI