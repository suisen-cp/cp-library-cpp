#ifndef SUISEN_MULTI_POINT_EVALUATION
#define SUISEN_MULTI_POINT_EVALUATION

#include "library/polynomial/fps.hpp"

namespace suisen {
    template <typename mint>
    std::vector<mint> multi_point_eval(const FPS<mint>& f, const std::vector<mint>& xs) {
        int n = xs.size();
        std::vector<FPS<mint>> seg(2 * n);
        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint>{ -xs[i], 1 };
        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];
        seg[1] = f % seg[1];
        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];
        std::vector<mint> ys(n);
        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];
        return ys;
    }
} // namespace suisen

#endif // SUISEN_MULTI_POINT_EVALUATION