#ifndef SUISEN_CHARACTERISTIC_POLYNOMIAL
#define SUISEN_CHARACTERISTIC_POLYNOMIAL

#include "library/linear_algebra/hessenberg_reduction.hpp"

namespace suisen {
    /**
     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf
     * returns p(λ) = det(λE - A)
     */
    template <typename T>
    std::vector<T> characteristic_polynomial(const SquareMatrix<T> &A) {
        const int n = A.row_size();
        if (n == 0) return { T{1} };
        auto H = hessenberg_reduction(A);
        /**
         *     +-              -+
         *     | a0  *  *  *  * |
         *     | b1 a1  *  *  * |
         * H = |  0 b2 a2  *  * |
         *     |  0  0 b3 a3  * |
         *     |  0  0  0 b4 a4 |
         *     +-              -+
         * p_i(λ) := det(λ*E_i - H[:i][:i])
         * p_0(λ) = 1,
         * p_1(λ) = λ-a_0,
         * p_i(λ) = (λ-a_{i-1}) p_{i-1}(λ) - Σ[j=0,i-1] p_j(λ) * H_{j,i} * Π[k=j+1,i] b_k.
         */
        std::vector<std::vector<T>> p(n + 1);
        p[0] = { T{1} }, p[1] = { { -H[0][0], T{1} } };
        for (int i = 1; i < n; ++i) {
            p[i + 1].resize(i + 2, T{0});
            for (int k = 0; k < i + 1; ++k) {
                p[i + 1][k] -= H[i][i] * p[i][k];
                p[i + 1][k + 1] += p[i][k];
            }
            T prod_b = T{1};
            for (int j = i - 1; j >= 0; --j) {
                prod_b *= H[j + 1][j];
                T coef = H[j][i] * prod_b;
                for (int k = 0; k < j + 1; ++k) p[i + 1][k] -= coef * p[j][k];
            }
        }
        return p[n];
    }
} // namespace suisen


#endif // SUISEN_CHARACTERISTIC_POLYNOMIAL
