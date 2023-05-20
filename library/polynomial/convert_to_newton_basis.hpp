#ifndef SUISEN_CONVERT_TO_NEWTON_BASIS
#define SUISEN_CONVERT_TO_NEWTON_BASIS

#include <tuple>
#include <vector>

namespace suisen {
    // Returns b=(b_0,...,b_{N-1}) s.t. f(x) = Sum[i=0,N-1] b_i Prod[j=0,i-1](x - p_j)
    template <typename FPSType>
    std::vector<typename FPSType::value_type> convert_to_newton_basis(const FPSType& f, const std::vector<typename FPSType::value_type>& p) {
        const int n = p.size();
        assert(f.size() == n);

        int m = 1;
        while (m < n) m <<= 1;

        std::vector<FPSType> seg(2 * m);
        for (int i = 0; i < m; ++i) {
            seg[m + i] = { i < n ? -p[i] : 0, 1 };
        }
        for (int i = m - 1; i > 0; --i) {
            if (((i + 1) & -(i + 1)) == (i + 1)) continue; // i = 2^k - 1
            seg[i] = seg[2 * i] * seg[2 * i + 1];
        }

        seg[1] = f;
        for (int i = 1; i < m; ++i) {
            std::tie(seg[2 * i + 1], seg[2 * i]) = seg[i].div_mod(seg[2 * i]);
        }

        std::vector<typename FPSType::value_type> b(n);
        for (int i = 0; i < n; ++i) {
            b[i] = seg[m + i].safe_get(0);
        }
        return b;
    }
} // namespace suisen


#endif // SUISEN_CONVERT_TO_NEWTON_BASIS
