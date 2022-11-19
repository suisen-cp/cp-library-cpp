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
        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)() = default_operator_noref::one<T>
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
        ArrayMatrix(const container_type& c) : base_type{ c } {}
        ArrayMatrix(const std::initializer_list<row_type>& c) {
            assert(c.size() == N);
            size_t i = 0;
            for (const auto& row : c) {
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
            ArrayMatrix A;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _neg((*this)[i][j]);
            return A;
        }
        friend ArrayMatrix& operator+=(ArrayMatrix& A, const ArrayMatrix& B) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _add(A[i][j], B[i][j]);
            return A;
        }
        friend ArrayMatrix& operator-=(ArrayMatrix& A, const ArrayMatrix& B) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _add(A[i][j], _neg(B[i][j]));
            return A;
        }
        template <size_t K>
        friend MatrixType<N, K>& operator*=(ArrayMatrix& A, const MatrixType<M, K>& B) { return A = A * B; }
        friend ArrayMatrix& operator*=(ArrayMatrix& A, const T& val) {
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _mul(A[i][j], val);
            return A;
        }
        friend ArrayMatrix& operator/=(ArrayMatrix& A, const ArrayMatrix& B) { static_assert(is_square_v<>); return A *= *B.inv(); }
        friend ArrayMatrix& operator/=(ArrayMatrix& A, const T& val) { return A *= _inv(val); }

        friend ArrayMatrix operator+(ArrayMatrix A, const ArrayMatrix& B) { A += B; return A; }
        friend ArrayMatrix operator-(ArrayMatrix A, const ArrayMatrix& B) { A -= B; return A; }
        template <size_t K>
        friend MatrixType<N, K> operator*(const ArrayMatrix& A, const MatrixType<M, K>& B) {
            MatrixType<N, K> C;
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0; k < K; ++k) C[i][k] = _add(C[i][k], _mul(A[i][j], B[j][k]));
            return C;
        }
        friend ArrayMatrix operator*(ArrayMatrix A, const T& val) { A *= val; return A; }
        friend ArrayMatrix operator*(const T& val, ArrayMatrix A) { A *= val; return A; }
        friend std::array<T, N> operator*(const ArrayMatrix& A, const std::array<T, M>& x) {
            std::array<T, N> b;
            b.fill(_zero());
            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) b[i] = _add(b[i], _mul(A[i][j], x[j]));
            return b;
        }
        friend ArrayMatrix operator/(ArrayMatrix A, const ArrayMatrix& B) { static_assert(is_square_v<>); return A * B.inv(); }
        friend ArrayMatrix operator/(ArrayMatrix A, const T& val) { A /= val; return A; }
        friend ArrayMatrix operator/(const T& val, ArrayMatrix A) { return A.inv() *= val; }

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

        std::optional<ArrayMatrix> safe_inv() const {
            static_assert(is_square_v<>);
            std::array<std::array<T, 2 * N>, N> data;
            for (size_t i = 0; i < N; ++i) {
                for (size_t j = 0; j < N; ++j) {
                    data[i][j] = (*this)[i][j];
                    data[i][N + j] = i == j ? _one() : _zero();
                }
            }
            for (size_t i = 0; i < N; ++i) {
                for (size_t k = i; k < N; ++k) if (data[k][i] != _zero()) {
                    data[i].swap(data[k]);
                    T c = _inv(data[i][i]);
                    for (size_t j = i; j < 2 * N; ++j) data[i][j] = _mul(c, data[i][j]);
                    break;
                }
                if (data[i][i] == _zero()) return std::nullopt;
                for (size_t k = 0; k < N; ++k) if (k != i and data[k][i] != _zero()) {
                    T c = data[k][i];
                    for (size_t j = i; j < 2 * N; ++j) data[k][j] = _add(data[k][j], _neg(_mul(c, data[i][j])));
                }
            }
            ArrayMatrix res;
            for (size_t i = 0; i < N; ++i) std::copy(data[i].begin() + N, data[i].begin() + 2 * N, res[i].begin());
            return res;
        }
        ArrayMatrix inv() const { return *safe_inv(); }
        T det() const {
            static_assert(is_square_v<>);
            ArrayMatrix A = *this;
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
        T det_arbitrary_mod() const {
            static_assert(is_square_v<>);
            ArrayMatrix A = *this;
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
    private:
        ArrayMatrix(Operator op) : ArrayMatrix(_zero()) {
            if (op == Operator::Mul) for (size_t i = 0; i < N; ++i) (*this)[i][i] = _one();
        }
    };
    template <
        typename T, size_t N,
        T(*_add)(T, T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>, T(*_zero)() = default_operator_noref::zero<T>,
        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)() = default_operator_noref::one<T>
    >
    using SquareArrayMatrix = ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one>;
} // namespace suisen

#endif // SUISEN_ARRAY_MATRIX
