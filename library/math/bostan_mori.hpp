#ifndef SUISEN_BOSTAN_MORI
#define SUISEN_BOSTAN_MORI

#include "library/math/fps.hpp"

namespace suisen {
template <typename mint>
mint bostan_mori(const FPS<mint> &P, const FPS<mint> &Q, const long long n) {
    if (n == 0) return P[0];
    FPS mQ(Q);
    for (int i = 0; i <= Q.deg(); i += 2) mQ[i] = -mQ[i];
    P *= mQ, Q *= mQ;
    FPS nP((P.deg() + 1) / 2), nQ((Q.deg() + 1) / 2);
    for (int i = 0    ; i <= Q.deg(); i += 2) nQ[i >> 1] = Q[i];
    for (int i = n & 1; i <= P.deg(); i += 2) nP[i >> 1] = P[i];
    return bostan_mori(nP, nQ, n / 2);
}
} // namespace suisen

#endif // SUISEN_BOSTAN_MORI