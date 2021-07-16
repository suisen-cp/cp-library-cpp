#ifndef SUISEN_MULTI_POINT_EVALUATION
#define SUISEN_MULTI_POINT_EVALUATION

#include "library/math/fps.hpp"

namespace suisen {
template <typename mint>
std::vector<mint> multi_point_eval(const FPS<mint> &f, const std::vector<mint> &xs) {
    int m = xs.size();
    int k = 1;
    while (k < m) k <<= 1;
    std::vector<FPS<mint>> seg(2 * k);
    for (int i = 0; i < m; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};
    for (int i = m; i < k; ++i) seg[k + i] = FPS<mint> {1};
    for (int i = k - 1; i> 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];
    seg[1] = f % seg[1];
    for (int i = 2; i < k + m; ++i) seg[i] = seg[i / 2] % seg[i];
    std::vector<mint> ys(m);
    for (int i = 0; i < m; ++i) ys[i] = seg[k + i][0];
    return ys;
}
} // namespace suisen

#endif // SUISEN_MULTI_POINT_EVALUATION