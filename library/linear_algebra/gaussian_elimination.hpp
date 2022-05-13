#ifndef SUISEN_GAUSSIAN_ELIMINATION
#define SUISEN_GAUSSIAN_ELIMINATION

#include <algorithm>
#include <cmath>
#include <optional>
#include <vector>

namespace suisen {
    namespace internal::gauss_jordan {
        template <typename T, typename EqZero, std::enable_if_t<std::negation_v<std::is_floating_point<T>>, std::nullptr_t> = nullptr>
        std::pair<size_t, size_t> pivoting(const std::vector<std::vector<T>>& Ab, const size_t i, EqZero equals_zero) {
            const size_t n = Ab.size(), m = Ab[0].size() - 1;
            size_t mse = m, pivot = n;
            for (size_t row = i; row < n; ++row) {
                const auto &v = Ab[row];
                size_t col = std::find_if_not(v.begin(), v.begin() + mse, equals_zero) - v.begin();
                if (col < mse) mse = col, pivot = row;
            }
            return { mse, pivot };
        }
        // Gauss pivoting
        template <typename T, typename EqZero, std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
        std::pair<size_t, size_t> pivoting(const std::vector<std::vector<T>>& Ab, const size_t i, EqZero equals_zero) {
            const size_t n = Ab.size(), m = Ab[0].size() - 1;
            size_t mse = m, pivot = n;
            T max_val = 0;
            for (size_t row = i; row < n; ++row) {
                const auto &v = Ab[row];
                if (mse < m and std::abs(v[mse]) > max_val) pivot = row, max_val = std::abs(v[mse]);
                size_t col = std::find_if_not(v.begin(), v.begin() + mse, equals_zero) - v.begin();
                if (col < mse) mse = col, pivot = row, max_val = std::abs(Ab[row][col]);
            }
            return { mse, pivot };
        }

        template <typename T> constexpr T add_fp_f2(T x, T y) { return x ^ y; }
        template <typename T> constexpr T add_inv_fp_f2(T x) { return x; }
        template <typename T> constexpr T mul_fp_f2(T x, T y) { return x & y; }
        template <typename T> constexpr T mul_inv_fp_f2(T x) { return x; }

        template <typename T> constexpr T add_fp_arithmetic(T x, T y) { return x + y; }
        template <typename T> constexpr T add_inv_fp_arithmetic(T x) { return 0 - x; }
        template <typename T> constexpr T mul_fp_arithmetic(T x, T y) { return x * y; }
        template <typename T> constexpr T mul_inv_fp_arithmetic(T x) { return 1 / x; }
    }

    template <typename T, T(*add_fp)(T, T), T(*add_inv_fp)(T), T(*mul_fp)(T, T), T(*mul_inv_fp)(T)>
    struct GaussianElimination {
        GaussianElimination(std::vector<std::vector<T>> A, const std::vector<T>& b, const T &zero = T(0), const T &one = T(1)) {
            size_t n = A.size();
            for (size_t i = 0; i < n; ++i) A[i].push_back(b[i]);
            solve(zero, one, A);
        }
        bool has_solution() const { return not _empty; }
        bool has_unique_solution() const { return not _empty and _basis.size() == 0; }
        bool has_multiple_solutions() const { return _basis.size() > 0; }
        const std::optional<std::vector<T>> get_solution() const { return _empty ? std::nullopt : std::make_optional(_x0); }
        const std::vector<std::vector<T>>& get_basis() const { return _basis; }
        int dimension() const { return _empty ? -1 : _basis.size(); }
    private:
        std::vector<T> _x0;
        std::vector<std::vector<T>> _basis;
        bool _empty = false;

        void solve(const T &zero, const T &one, std::vector<std::vector<T>>& Ab) {
            using namespace internal::gauss_jordan;
            auto equals_zero = [&](const T& v) {
                if constexpr (std::is_floating_point_v<T>) return std::abs(v) < 1e-9;
                else return v == zero;
            };
            const size_t n = Ab.size(), m = Ab[0].size() - 1;
            for (size_t i = 0; i < n; ++i) {
                auto [mse, pivot] = pivoting(Ab, i, equals_zero);
                if (pivot == n) break;
                Ab[i].swap(Ab[pivot]);
                T mse_val_inv = mul_inv_fp(Ab[i][mse]);
                for (size_t row = i + 1; row < n; ++row) if (not equals_zero(Ab[row][mse])) {
                    T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));
                    for (size_t col = mse; col <= m; ++col) Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));
                }
            }
            size_t basis_num = m;
            std::vector<char> down(m, false);
            _x0.assign(m, zero);
            for (size_t i = n; i-- > 0;) {
                size_t mse = m + 1;
                for (size_t col = 0; col <= m; ++col) if (not equals_zero(Ab[i][col])) {
                    mse = col;
                    break;
                }
                if (mse < m) {
                    T mse_val_inv = mul_inv_fp(Ab[i][mse]);
                    for (size_t row = 0; row < i; ++row) if (not equals_zero(Ab[row][mse])) {
                        T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));
                        for (size_t col = mse; col <= m; ++col) Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));
                    }
                    for (size_t col = mse; col <= m; ++col) Ab[i][col] = mul_fp(Ab[i][col], mse_val_inv);
                    _x0[mse] = Ab[i][m];
                    down[mse] = true;
                    --basis_num;
                } else if (mse == m) {
                    _empty = true;
                    return;
                }
            }
            _basis.assign(basis_num, std::vector<T>(m));
            int basis_id = 0;
            for (size_t j = 0; j < m; ++j) if (not down[j]) {
                for (size_t j2 = 0, i = 0; j2 < m; ++j2) _basis[basis_id][j2] = down[j2] ? Ab[i++][j] : zero;
                _basis[basis_id++][j] = add_inv_fp(one);
            }
        }
    };

    template <typename T>
    using GaussianEliminationF2 = GaussianElimination<
        T,
        internal::gauss_jordan::add_fp_f2, internal::gauss_jordan::add_inv_fp_f2,
        internal::gauss_jordan::mul_fp_f2, internal::gauss_jordan::mul_inv_fp_f2>;
    template <typename T>
    using GaussianEliminationArithmetic = GaussianElimination<
        T,
        internal::gauss_jordan::add_fp_arithmetic, internal::gauss_jordan::add_inv_fp_arithmetic,
        internal::gauss_jordan::mul_fp_arithmetic, internal::gauss_jordan::mul_inv_fp_arithmetic>;
} // namespace suisen

#endif // SUISEN_GAUSSIAN_ELIMINATION