#ifndef SUISEN_ARRAY_MATRIX
#define SUISEN_ARRAY_MATRIX

#include <array>
#include <cassert>
#include <optional>

#include "library/util/default_operator.hpp"

namespace suisen {
    template <
        typename T,
        size_t N,
        size_t M,
        T(*_add)(T, T) = default_operator_noref::add<T>,
        T(*_neg)(T) = default_operator_noref::neg<T>,
        T(*_zero)() = default_operator_noref::zero<T>,
        T(*_mul)(T, T) = default_operator_noref::mul<T>,
        T(*_inv)(T) = default_operator_noref::inv<T>,
        T(*_one)()  = default_operator_noref::one<T>
    >
    struct ArrayMatrix : public std::array<std::array<T, M>, N> {
#define MatrixType(N, M) ArrayMatrix<T, N, M, _add, _neg, _zero, _mul, _inv, _one>
        using base_type = std::array<std::array<T, M>, N>;
        using container_type = base_type;
        using row_type = std::array<T, M>;

        using base_type::base_type;
        constexpr ArrayMatrix() : ArrayMatrix(_zero()) {}
        constexpr ArrayMatrix(T fill_value) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = fill_value;
        }
        constexpr ArrayMatrix(const container_type &c) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = c[i][j];
        }

        constexpr std::pair<int, int> shape() const {
            return { N, M };
        }
        constexpr int row_size() const {
            return N;
        }
        constexpr int col_size() const {
            return M;
        }

        constexpr MatrixType(N, M) operator+() {
            return *this;
        }
        constexpr MatrixType(N, M) operator-() {
            ArrayMatrix res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _add(res[i][j], _neg((*this)[i][j]));
            return res;
        }
        constexpr MatrixType(N, M)& operator+=(const MatrixType(N, M)& other) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _add((*this)[i][j], other[i][j]);
            return *this;
        }
        constexpr MatrixType(N, M)& operator-=(const MatrixType(N, M)& other) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _add((*this)[i][j], _neg(other[i][j]));
            return *this;
        }
        template <size_t K>
        constexpr MatrixType(N, M)& operator*=(const MatrixType(M, K)& other) {
            return *this = *this * other;
        }
        constexpr MatrixType(N, M)& operator*=(const T& val) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j] = _mul((*this)[i][j], val);
            return *this;
        }
        constexpr MatrixType(N, M)& operator/=(const T& val) {
            return *this *= _inv(val);
        }
        constexpr friend MatrixType(N, M) operator+(const MatrixType(N, M)& lhs, const MatrixType(N, M)& rhs) {
            return MatrixType(N, M)(lhs) += rhs;
        }
        constexpr friend MatrixType(N, M) operator-(const MatrixType(N, M)& lhs, const MatrixType(N, M)& rhs) {
            return MatrixType(N, M)(lhs) -= rhs;
        }
        template <size_t K>
        constexpr friend MatrixType(N, K) operator*(const MatrixType(N, M)& lhs, const MatrixType(M, K)& rhs) {
            MatrixType(N, K) res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0; k < K; ++k) {
                res[i][k] = _add(res[i][k], _mul(lhs[i][j], rhs[j][k]));
            }
            return res;
        }
        constexpr friend MatrixType(N, M) operator*(const MatrixType(N, M)& A, const T& val) {
            MatrixType(N, M) res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _mul(A[i][j], val);
            return res;
        }
        constexpr friend MatrixType(N, M) operator*(const T& val, const MatrixType(N, M)& A) {
            MatrixType(N, M) res;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _mul(val, A[i][j]);
            return res;
        }
        constexpr friend MatrixType(N, M) operator/(const MatrixType(N, M)& A, const T& val) {
            return MatrixType(N, M)(A) /= val;
        }

        constexpr std::array<T, N> operator*(const std::array<T, M>& x) const {
            std::array<T, N> b;
            b.fill(_zero());
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) b[i] = _add(b[i], _mul((*this)[i][j], x[j]));
            return b;
        }
#undef MatrixType
    };

    template <
        typename T,
        size_t N,
        T(*_add)(T, T) = default_operator_noref::add<T>,
        T(*_neg)(T) = default_operator_noref::neg<T>,
        T(*_zero)() = default_operator_noref::zero<T>,
        T(*_mul)(T, T) = default_operator_noref::mul<T>,
        T(*_inv)(T) = default_operator_noref::inv<T>,
        T(*_one)()  = default_operator_noref::one<T>
    >
    class SquareArrayMatrix : public ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one> {
    private:
        enum Operator { Add, Mul };
    public:
#define MatrixType(N) SquareArrayMatrix<T, N, _add, _neg, _zero, _mul, _inv, _one>
        using base_type = ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one>;
        using container_type = typename base_type::container_type;
        using row_type = typename base_type::row_type;

        using base_type::base_type;

        static SquareArrayMatrix e0() { return SquareArrayMatrix(Operator::Add); }
        static SquareArrayMatrix e1() { return SquareArrayMatrix(Operator::Mul); }

        static constexpr std::optional<SquareArrayMatrix> inv(const SquareArrayMatrix& A) {
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
            SquareArrayMatrix res;
            for (size_t i = 0; i < N; ++i) std::copy(data[i].begin(), data[i].begin() + N, res[i].begin());
            return res;
        }
        static constexpr T det(SquareArrayMatrix&& A) {
            T det_inv = _one();
            for (size_t i = 0; i < N; ++i) {
                int pivot = -1;
                for (size_t k = i; k < N; ++k) if (A[k][i] != _zero()) {
                    pivot = k;
                    break;
                }
                if (pivot < 0) return _zero();
                A[i].swap(A[pivot]);
                if (pivot != i) det_inv = _mul(det_inv, _neg(_one()));
                T coef = _inv(A[i][i]);
                for (size_t j = i; j < N; ++j) A[i][j] = _mul(A[i][j], coef);
                det_inv = _mul(det_inv, coef);
                for (size_t k = i + 1; k < N; ++k) if (A[k][i] != _zero()) {
                    T c = A[k][i];
                    for (size_t j = i; j < N; ++j) A[k][j] = _add(A[k][j], _neg(_mul(c, A[i][j])));
                }
            }
            return _inv(det_inv);
        }
        static constexpr T det(const SquareArrayMatrix& A) {
            return det(SquareArrayMatrix(A));
        }
        constexpr SquareArrayMatrix inv() const {
            return *inv(*this);
        }
        constexpr T det() const {
            return det(*this);
        }

        constexpr friend SquareArrayMatrix operator+(const SquareArrayMatrix& A, const SquareArrayMatrix& B) {
            auto res = *static_cast<base_type const*>(&A) + *static_cast<base_type const*>(&B);
            return *static_cast<SquareArrayMatrix*>(&res);
        }
        constexpr SquareArrayMatrix& operator+=(const SquareArrayMatrix& B) {
            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this) += *static_cast<base_type const*>(&B)));
        }
        constexpr friend SquareArrayMatrix operator-(const SquareArrayMatrix& A, const SquareArrayMatrix& B) {
            auto res = *static_cast<base_type const*>(&A) - *static_cast<base_type const*>(&B);
            return *static_cast<SquareArrayMatrix*>(&res);
        }
        constexpr SquareArrayMatrix& operator-=(const SquareArrayMatrix& B) {
            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this) -= *static_cast<base_type const*>(&B)));
        }
        constexpr friend SquareArrayMatrix operator*(const SquareArrayMatrix& A, const SquareArrayMatrix& B) {
            auto res = *static_cast<base_type const*>(&A) * *static_cast<base_type const*>(&B);
            return *static_cast<SquareArrayMatrix*>(&res);
        }
        constexpr SquareArrayMatrix& operator*=(const SquareArrayMatrix& B) {
            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this) *= *static_cast<base_type const*>(&B)));
        }
        constexpr friend SquareArrayMatrix operator*(const SquareArrayMatrix& A, const T& x) {
            auto res = *static_cast<base_type const*>(&A) * x;
            return *static_cast<SquareArrayMatrix*>(&res);
        }
        constexpr friend SquareArrayMatrix operator*(const T& x, const SquareArrayMatrix& A) {
            auto res = x * *static_cast<base_type const*>(&A);
            return *static_cast<SquareArrayMatrix*>(&res);
        }
        constexpr SquareArrayMatrix& operator*=(const T& x) {
            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this) *= x));
        }
        constexpr SquareArrayMatrix& operator/=(const SquareArrayMatrix& other) { return *this *= other.inv(); }
        constexpr SquareArrayMatrix  operator/ (const SquareArrayMatrix& other) const { return SquareArrayMatrix(*this) *= other.inv(); }

        constexpr SquareArrayMatrix pow(long long b) const {
            assert(b >= 0);
            SquareArrayMatrix res(e1()), p(*this);
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }
    private:
        SquareArrayMatrix(Operator op) : base_type() {
            if (op == Operator::Mul) for (size_t i = 0; i < N; ++i) (*this)[i][i] = _one();
        }
#undef MatrixType
    };
} // namespace suisen

#endif // SUISEN_ARRAY_MATRIX
