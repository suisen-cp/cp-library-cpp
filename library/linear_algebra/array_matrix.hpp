#ifndef SUISEN_ARRAY_MATRIX
#define SUISEN_ARRAY_MATRIX

#include <array>
#include <cassert>
#include <optional>

#include "library/util/default_operator.hpp"

namespace suisen {
    template <
        typename T, size_t N, size_t M,
        T(*_add)(T, T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>, T(*_zero)() = default_operator_noref::zero<T>,
        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)()  = default_operator_noref::one<T>
    >
    struct ArrayMatrix : public std::array<std::array<T, M>, N> {
    private:
        enum Operator { Add, Mul };
        template <typename DummyType = void>
        static constexpr bool is_square_v = N == M;
        template <size_t X, size_t Y>
        using MatrixType = ArrayMatrix<T, X, Y, _add, _neg, _zero, _mul, _inv, _one>;
    public:
        using base_type = std::array<std::array<T, M>, N>;
        using container_type = base_type;
        using row_type = std::array<T, M>;

        using base_type::base_type;
        ArrayMatrix() : ArrayMatrix(_zero()) {}
        ArrayMatrix(T fill_value) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = fill_value;
        }
        ArrayMatrix(const container_type &c) : base_type{c} {}
        ArrayMatrix(const std::initializer_list<row_type> &c) {
            assert(c.size() == N);
            size_t i = 0;
            for (const auto &row : c) {
                for (size_t j = 0; j < M; ++j) (*this)[i][j] = row[j];
                ++i;
            }
        }

        static ArrayMatrix e0() { return ArrayMatrix(Operator::Add); }
        static MatrixType<M, M> e1() { return MatrixType<M, M>(Operator::Mul); }

        int size() const {
            static_assert(is_square_v<>);
            return N;
        }
        std::pair<int, int> shape() const { return { N, M }; }
        int row_size() const { return N; }
        int col_size() const { return M; }

        ArrayMatrix operator+() const { return *this; }
        ArrayMatrix operator-() const {
            ArrayMatrix res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _neg((*this)[i][j]);
            return res;
        }
        ArrayMatrix& operator+=(const ArrayMatrix& other) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _add((*this)[i][j], other[i][j]);
            return *this;
        }
        ArrayMatrix& operator-=(const ArrayMatrix& other) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _add((*this)[i][j], _neg(other[i][j]));
            return *this;
        }
        template <size_t K>
        MatrixType<N, K>& operator*=(const MatrixType<M, K>& other) { return *this = *this * other; }
        ArrayMatrix& operator*=(const T& val) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _mul((*this)[i][j], val);
            return *this;
        }
        ArrayMatrix& operator/=(const T& val) { return *this *= _inv(val); }
        friend ArrayMatrix operator+(ArrayMatrix lhs, const ArrayMatrix& rhs) { lhs += rhs; return lhs; }
        friend ArrayMatrix operator-(ArrayMatrix lhs, const ArrayMatrix& rhs) { lhs -= rhs; return lhs; }
        template <size_t K>
        friend MatrixType<N, K> operator*(const ArrayMatrix& lhs, const MatrixType<M, K>& rhs) {
            MatrixType<N, K> res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0; k < K; ++k) {
                res[i][k] = _add(res[i][k], _mul(lhs[i][j], rhs[j][k]));
            }
            return res;
        }
        friend ArrayMatrix operator*(ArrayMatrix A, const T& val) { A *= val; return A; }
        friend ArrayMatrix operator*(const T& val, ArrayMatrix A) { A *= val; return A; }
        friend ArrayMatrix operator/(ArrayMatrix A, const T& val) { A /= val; return A; }

        std::array<T, N> operator*(const std::array<T, M>& x) const {
            std::array<T, N> b;
            b.fill(_zero());
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) b[i] = _add(b[i], _mul((*this)[i][j], x[j]));
            return b;
        }

        static std::optional<ArrayMatrix> inv(const ArrayMatrix& A) {
            static_assert(is_square_v<>);
            std::array<std::array<T, 2 * N>, N> data;
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    data[i][j] = A[i][j];
                    data[i][N + j] = i == j ? _one() : _zero();
                }
            }
            for (size_t i = 0; i < N; ++i) {
                int pivot = -1;
                for (size_t k = i; k < N; ++k) if (data[k][i] != _zero()) {
                    pivot = k;
                    break;
                }
                if (pivot < 0) return std::nullopt;
                data[i].swap(data[pivot]);
                T coef = _inv(data[i][i]);
                for (size_t j = i; j < 2 * N; ++j) data[i][j] = _mul(data[i][j], coef);
                for (size_t k = 0; k < N; ++k) if (k != i and data[k][i] != _zero()) {
                    T c = data[k][i];
                    for (size_t j = i; j < 2 * N; ++j) data[k][j] = _add(data[k][j], _neg(_mul(c, data[i][j])));
                }
            }
            ArrayMatrix res;
            for (size_t i = 0; i < N; ++i) std::copy(data[i].begin() + N, data[i].begin() + 2 * N, res[i].begin());
            return res;
        }
        static T det(ArrayMatrix A) {
            static_assert(is_square_v<>);
            bool sgn = false;
            for (size_t j = 0; j < N; ++j) for (size_t i = j + 1; i < N; ++i) if (A[i][j] != _zero()) {
                std::swap(A[j], A[i]);
                T q = _mul(A[i][j], _inv(A[j][j]));
                for (size_t k = j; k < N; ++k) A[i][k] = _add(A[i][k], _neg(_mul(A[j][k], q)));
                sgn = not sgn;
            }
            T res = sgn ? _neg(_one()) : _one();
            for (size_t i = 0; i < N; ++i) res = _mul(res, A[i][i]);
            return res;
        }
        static T det_arbitrary_mod(ArrayMatrix A) {
            bool sgn = false;
            for (size_t j = 0; j < N; ++j) for (size_t i = j + 1; i < N; ++i) {
                for (; A[i][j].val(); sgn = not sgn) {
                    std::swap(A[j], A[i]);
                    T q = A[i][j].val() / A[j][j].val();
                    for (size_t k = j; k < N; ++k) A[i][k] -= A[j][k] * q;
                }
            }
            T res = sgn ? -1 : +1;
            for (size_t i = 0; i < N; ++i) res *= A[i][i];
            return res;
        }
        std::optional<ArrayMatrix> inv() const { static_assert(is_square_v<>); return inv(*this); }
        T det() const { static_assert(is_square_v<>); return det(*this); }
        T det_arbitrary_mod() const { static_assert(is_square_v<>); return det_arbitrary_mod(*this); }

        ArrayMatrix& operator/=(const ArrayMatrix& other) { static_assert(is_square_v<>); return *this *= other.inv(); }
        ArrayMatrix  operator/ (const ArrayMatrix& other) const { static_assert(is_square_v<>); return ArrayMatrix(*this) *= *other.inv(); }

        ArrayMatrix pow(long long b) const {
            static_assert(is_square_v<>);
            assert(b >= 0);
            ArrayMatrix res(e1()), p(*this);
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }
    private:
        ArrayMatrix(Operator op) : ArrayMatrix(_zero()) {
            if (op == Operator::Mul) for (size_t i = 0; i < N; ++i) (*this)[i][i] = _one();
        }
    };
    template <
        typename T, size_t N,
        T(*_add)(T, T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>, T(*_zero)() = default_operator_noref::zero<T>,
        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)()  = default_operator_noref::one<T>
    >
    using SquareArrayMatrix = ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one>;
} // namespace suisen

#endif // SUISEN_ARRAY_MATRIX
