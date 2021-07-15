#include <cmath>
#include <optional>
#include <vector>

namespace suisen {
namespace internal {
    namespace gauss_jordan {
        template <typename T>
        std::pair<unsigned int, unsigned int> pivoting(const std::vector<std::vector<T>> &Ab, const T &zero, const unsigned int i) {
            const unsigned int n = Ab.size(), m = Ab[0].size() - 1;
            unsigned int mse = m, pivot = n;
            for (unsigned int row = i; row < n; ++row) {
                for (unsigned int col = 0; col < mse; ++col) {
                    if (Ab[row][col] != zero) {
                        mse = col, pivot = row;
                        break;
                    }
                }
            }
            return {mse, pivot};
        }
        // Gauss pivoting
        template <>
        std::pair<unsigned int, unsigned int> pivoting<long double>(const std::vector<std::vector<long double>> &Ab, const long double &zero, const unsigned int i) {
            const unsigned int n = Ab.size(), m = Ab[0].size() - 1;
            unsigned int mse = m, pivot = n;
            long double max_val = 0;
            for (unsigned int row = i; row < n; ++row) {
                if (mse < m and std::abs(Ab[row][mse]) > max_val) {
                    pivot = row;
                    max_val = std::abs(Ab[row][mse]);
                }
                for (unsigned int col = 0; col < mse; ++col) {
                    if (Ab[row][col] != zero) {
                        mse = col, pivot = row, max_val = std::abs(Ab[row][col]);
                        break;
                    }
                }
            }
            return {mse, pivot};
        }

        template <typename T> constexpr T add_fp_f2(T x, T y) { return x ^ y; }
        template <typename T> constexpr T add_inv_fp_f2(T x)  { return x; }
        template <typename T> constexpr T mul_fp_f2(T x, T y) { return x & y; }
        template <typename T> constexpr T mul_inv_fp_f2(T x)  { return x; }

        template <typename T> constexpr T add_fp_arithmetic(T x, T y) { return x + y; }
        template <typename T> constexpr T add_inv_fp_arithmetic(T x)  { return 0 - x; }
        template <typename T> constexpr T mul_fp_arithmetic(T x, T y) { return x * y; }
        template <typename T> constexpr T mul_inv_fp_arithmetic(T x)  { return 1 / x; }
    }
}

template <typename T, T(*add_fp)(T, T), T(*add_inv_fp)(T), T(*mul_fp)(T, T), T(*mul_inv_fp)(T)>
class GaussJordan {
    public:
        GaussJordan(std::vector<std::vector<T>> &A, std::vector<T> &b, const T zero, const T one) {
            unsigned int n = A.size();
            for (unsigned int i = 0; i < n; ++i) A[i].push_back(b[i]);
            solve(zero, one, A);
        }
        GaussJordan(std::vector<std::vector<T>> &A, std::vector<T> &b) {
            unsigned int n = A.size();
            for (unsigned int i = 0; i < n; ++i) A[i].push_back(b[i]);
            solve(T(0), T(1), A);
        }
        bool has_solution() const { return not _empty; }
        bool has_unique_solution() const { return not _empty and _basis.size() == 0; }
        bool has_multiple_solutions() const { return _basis.size() > 0; }
        const std::optional<std::vector<T>> get_solution() const {
            return _empty ? std::nullopt : std::make_optional(_x0);
        }
        const std::vector<std::vector<T>>& get_basis() const {
            return _basis;
        }
        int dimension() const {
            return _empty ? -1 : _basis.size();
        }
    private:
        std::vector<T> _x0;
        std::vector<std::vector<T>> _basis;
        bool _empty = false;

        void solve(const T zero, const T one, std::vector<std::vector<T>> &Ab) {
            const unsigned int n = Ab.size(), m = Ab[0].size() - 1;
            for (unsigned int i = 0; i < n; ++i) {
                auto [mse, pivot] = internal::gauss_jordan::pivoting(Ab, zero, i);
                if (pivot == n) break;
                Ab[i].swap(Ab[pivot]);
                T mse_val_inv = mul_inv_fp(Ab[i][mse]);
                for (unsigned int row = i + 1; row < n; ++row) {
                    if (Ab[row][mse] != zero) {
                        T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));
                        for (unsigned int col = mse; col <= m; ++col) {
                            Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));
                        }
                    }
                }
            }
            unsigned int basis_num = m;
            std::vector<char> down(m, false);
            _x0.assign(m, zero);
            for (unsigned int i = n; i --> 0;) {
                unsigned int mse = m + 1;
                for (unsigned int col = 0; col <= m; ++col) {
                    if (Ab[i][col] != zero) {
                        mse = col;
                        break;
                    }
                }
                if (mse < m) {
                    T mse_val_inv = mul_inv_fp(Ab[i][mse]);
                    for (unsigned int row = 0; row < i; ++row) {
                        if (Ab[row][mse] != zero) {
                            T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));
                            for (unsigned int col = mse; col <= m; ++col) {
                                Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));
                            }
                        }
                    }
                    for (unsigned int col = mse; col <= m; ++col) {
                        Ab[i][col] = mul_fp(Ab[i][col], mse_val_inv);
                    }
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
            for (unsigned int j = 0; j < m; ++j) {
                if (down[j]) continue;
                for (unsigned int j2 = 0, i = 0; j2 < m; ++j2) {
                    _basis[basis_id][j2] = down[j2] ? Ab[i++][j] : zero;
                }
                _basis[basis_id][j] = add_inv_fp(one);
                basis_id++;
            }
        }
};

template <typename T>
using GaussJordanF2 = GaussJordan<
    T,
    internal::gauss_jordan::add_fp_f2, internal::gauss_jordan::add_inv_fp_f2,
    internal::gauss_jordan::mul_fp_f2, internal::gauss_jordan::mul_inv_fp_f2>;
template <typename T>
using GaussJordanArithmetic = GaussJordan<
    T,
    internal::gauss_jordan::add_fp_arithmetic, internal::gauss_jordan::add_inv_fp_arithmetic,
    internal::gauss_jordan::mul_fp_arithmetic, internal::gauss_jordan::mul_inv_fp_arithmetic>;
} // namespace suisen