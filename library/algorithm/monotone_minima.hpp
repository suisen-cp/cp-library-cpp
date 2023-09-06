#ifndef SUISEN_MONOTONE_MINIMA
#define SUISEN_MONOTONE_MINIMA

#include <cassert>
#include <cstddef>
#include <vector>

namespace suisen {
    /**
     * @param n # rows
     * @param m # cols
     * @param compare (row, col1, col2 (> col1)) -> bool (= A(row, col1) <= A(row, col2))
     * @return std::vector<int> res s.t. res[i] = argmin_j f(i,j)
     */
    template <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, size_t, size_t, size_t>, std::nullptr_t> = nullptr>
    std::vector<int> monotone_minima(size_t n, size_t m, const Compare &compare) {
        std::vector<int> res(n);
        auto rec = [&](auto rec, size_t u, size_t d, size_t l, size_t r) -> void {
            if (u == d) return;
            assert(l < r);
            const size_t row = (u + d) >> 1;
            size_t argmin = l;
            for (size_t col = l + 1; col < r; ++col) if (not compare(row, argmin, col)) argmin = col;
            res[row] = argmin;
            rec(rec, u, row, l, argmin + 1);
            rec(rec, row + 1, d, argmin, r);
        };
        rec(rec, 0, n, 0, m);
        return res;
    }

    /**
     * @param n # rows
     * @param m # cols
     * @param matrix (row, col) -> value
     * @return std::vector<int> res s.t. res[i] = argmin_j f(i,j)
     */
    template <typename Matrix, std::enable_if_t<std::is_invocable_v<Matrix, size_t, size_t>, std::nullptr_t> = nullptr>
    std::vector<int> monotone_minima(size_t n, size_t m, const Matrix &matrix) {
        return monotone_minima(n, m, [&matrix](size_t i, size_t j1, size_t j2) { return matrix(i, j1) <= matrix(i, j2); });
    }
} // namespace suisen


#endif // SUISEN_MONOTONE_MINIMA
