#ifndef SUISEN_MULTI_POINT_EVALUATION
#define SUISEN_MULTI_POINT_EVALUATION

#include <vector>

namespace suisen {
    template <typename FPSType, typename T>
    std::vector<typename FPSType::value_type> multi_point_eval(const FPSType& f, const std::vector<T>& xs) {
        int n = xs.size();
        if (n == 0) return {};
        std::vector<FPSType> seg(2 * n);
        for (int i = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i], 1 };
        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];
        seg[1] = f % seg[1];
        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];
        std::vector<typename FPSType::value_type> ys(n);
        for (int i = 0; i < n; ++i) ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;
        return ys;
    }
} // namespace suisen

#endif // SUISEN_MULTI_POINT_EVALUATION