#ifndef SUISEN_CHIRP_Z_TRANSFORM
#define SUISEN_CHIRP_Z_TRANSFORM

#include <algorithm>
#include <vector>

#include <atcoder/convolution>

/**
 * @brief chirp z-transform ($g _ k = f(a r^k)$)
*/

namespace suisen {
    namespace internal {
        const auto default_convolution = [](const auto &a, const auto &b) { return atcoder::convolution(a, b); };
    } // namespace internal
    /**
     * @brief Calculates f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m) time
     */
    template <typename T, typename Convolution>
    std::vector<T> chirp_z_transform(std::vector<T> f, T a, T r, int m, Convolution &&convolution = internal::default_convolution) {
        const int n = f.size();
        std::vector<T> g(m);
        if (n == 0 or m == 0) return g;
        if (r == 0) {
            for (int i = 0; i < n; ++i) g[0] += f[i];
            for (int k = 1; k < m; ++k) g[k] += f[0];
            return g;
        }
        T pow_a = 1;
        for (int i = 0; i < n; ++i, pow_a *= a) f[i] *= pow_a;

        const T w_inv = r.inv();

        const int l = n + m - 1;

        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);
        pow_r_tri[0] = pow_r_tri_inv[0] = 1;

        T pow_r = 1, pow_r_inv = 1;
        for (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= w_inv) {
            pow_r_tri[i] = pow_r_tri[i - 1] * pow_r;
            pow_r_tri_inv[i] = pow_r_tri_inv[i - 1] * pow_r_inv;
        }

        std::vector<T> p(n), q(l);
        for (int i = 0; i < n; ++i) p[i] = f[i] * pow_r_tri_inv[i];
        for (int i = 0; i < l; ++i) q[i] = pow_r_tri[i];
        std::reverse(p.begin(), p.end());
        std::vector<T> pq = convolution(p, q);
        for (int k = 0; k < m; ++k) {
            g[k] = pow_r_tri_inv[k] * pq[n - 1 + k];
        }

        return g;
    }
} // namespace suisen


#endif // SUISEN_CHIRP_Z_TRANSFORM
