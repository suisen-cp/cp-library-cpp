#ifndef SUISEN_HESSENBERG_REDUCTION
#define SUISEN_HESSENBERG_REDUCTION

#include "library/math/matrix.hpp"

namespace suisen {
    /**
     * Reference: http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf
     * returns H := P^(-1) A P, where H is hessenberg matrix
     */
    template <typename T>
    SquareMatrix<T> hessenberg_reduction(SquareMatrix<T> A) {
        const int n = A.row_size();
        for (int r = 0; r < n - 2; ++r) {
            int pivot = -1;
            for (int r2 = r + 1; r2 < n; ++r2) if (A[r2][r] != 0) {
                pivot = r2;
                break;
            }
            if (pivot < 0) continue;
            if (pivot != r + 1) {
                for (int k = 0; k < n; ++k) std::swap(A[r + 1][k], A[pivot][k]);
                for (int k = 0; k < n; ++k) std::swap(A[k][r + 1], A[k][pivot]);
            }
            const T den = T{1} / A[r + 1][r];
            for (int r2 = r + 2; r2 < n; ++r2) if (T coef = A[r2][r] * den; coef != 0) {
                for (int k = r; k < n; ++k) A[r2][k] -= coef * A[r + 1][k];
                for (int k = 0; k < n; ++k) A[k][r + 1] += coef * A[k][r2];
            }
        }
        return A;
    }
} // namespace suisen


#endif // SUISEN_HESSENBERG_REDUCTION
