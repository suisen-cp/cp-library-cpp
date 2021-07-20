#ifndef SUISEN_MATRIX
#define SUISEN_MATRIX

#include <cassert>
#include <optional>
#include <vector>

namespace suisen {
template <typename T>
class Matrix {
    public:
        Matrix() {}
        Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m, fill_value)) {}
        Matrix(const std::vector<std::vector<T>>  &data) noexcept : data(data) {}
        Matrix(      std::vector<std::vector<T>> &&data) noexcept : data(std::move(data)) {}
        Matrix(const Matrix<T>  &other) noexcept : data(other.data) {}
        Matrix(      Matrix<T> &&other) noexcept : data(std::move(other.data)) {}

        Matrix<T>& operator=(const Matrix<T> &other) noexcept {
            data = other.data;
            return *this;
        }
        Matrix<T>& operator=(Matrix<T> &&other) noexcept {
            data = std::move(other.data);
            return *this;
        }

        const std::vector<T>& operator[](int i) const { return data[i]; }
              std::vector<T>& operator[](int i)       { return data[i]; }

        std::pair<int, int> size() const {
            if (data.empty()) {
                return {0, 0};
            } else {
                return {data.size(), data[0].size()};
            }
        }
        int row_size() const {
            return data.size();
        }
        int col_size() const {
            return data.empty() ? 0 : data[0].size();
        }

        Matrix<T>& operator+=(const Matrix<T> &other) {
            assert(size() == other.size());
            auto [n, m] = size();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                data[i][j] += other[i][j];
            }
        }
        Matrix<T>& operator-=(const Matrix<T> &other) {
            assert(size() == other.size());
            auto [n, m] = size();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                data[i][j] -= other[i][j];
            }
        }
        Matrix<T>& operator*=(const Matrix<T> &other) {
            return *this = *this * other;
        }
        Matrix<T>& operator*=(const T &val) {
            auto [n, m] = size();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                data[i][j] *= val;
            }
            return *this;
        }
        Matrix<T>& operator/=(const T &val) {
            return *this *= T(1) / val;
        }
        Matrix<T> operator+(const Matrix<T> &other) const {
            return Matrix<T>(*this) += other;
        }
        Matrix<T> operator-(const Matrix<T> &other) const {
            return Matrix<T>(*this) -= other;
        }
        Matrix<T> operator*(const Matrix<T> &other) const {
            auto [n, m] = size();
            auto [m2, l] = other.size();
            assert(m == m2);
            std::vector res(n, std::vector(l, T(0)));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k) {
                res[i][k] += (*this)[i][j] * other[j][k];
            }
            return res;
        }
        Matrix<T> operator*(const T &val) const {
            return Matrix<T>(*this) *= val;
        }
        Matrix<T> operator/(const T &val) const {
            return Matrix<T>(*this) /= val;
        }

        std::vector<T> operator*(const std::vector<T> &x) const {
            auto [n, m] = size();
            assert(m == int(x.size()));
            std::vector<T> b(n, T(0));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                b[i] += data[i][j] * x[j];
            }
            return b;
        }
    protected:
        std::vector<std::vector<T>> data;
};

template <typename T>
class SquareMatrix : public Matrix<T> {
    public:
        SquareMatrix() {}
        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n, n, fill_value) {}
        SquareMatrix(const std::vector<std::vector<T>> &data) noexcept : Matrix<T>::Matrix(data) {
            auto [n, m] = this->size();
            assert(n == m);
        }
        SquareMatrix(std::vector<std::vector<T>> &&data) noexcept : Matrix<T>::Matrix(std::move(data)) {
            auto [n, m] = this->size();
            assert(n == m);
        }
        SquareMatrix(const SquareMatrix<T>  &other) noexcept : Matrix<T>::Matrix(other.data) {}
        SquareMatrix(      SquareMatrix<T> &&other) noexcept : Matrix<T>::Matrix(std::move(other.data)) {}

        SquareMatrix<T>& operator=(const SquareMatrix<T> &other) noexcept {
            this->data = other.data;
            return *this;
        }
        SquareMatrix<T>& operator=(SquareMatrix<T> &&other) noexcept {
            this->data = std::move(other.data);
            return *this;
        }

        static SquareMatrix<T> e0(int n) { return SquareMatrix<T>(n, false); }
        static SquareMatrix<T> e1(int n) { return SquareMatrix<T>(n, true); }

        static std::optional<SquareMatrix<T>> inv(SquareMatrix<T> &&A) {
            auto &data = A.data;
            int n = data.size();
            for (int i = 0; i < n; ++i) {
                data[i].resize(2 * n, T(0));
                data[i][n + i] = T(1);
            }
            for (int i = 0; i < n; ++i) {
                int pivot = -1;
                for (int k = i; k < n; ++k) {
                    if (data[k][i] != T(0)) {
                        pivot = k;
                        break;
                    }
                }
                if (pivot < 0) return std::nullopt;
                assert(pivot >= 0);
                data[i].swap(data[pivot]);
                T coef = T(1) / data[i][i];
                for (int j = i; j < 2 * n; ++j) data[i][j] *= coef;
                for (int k = 0; k < n; ++k) {
                    if (k == i or data[k][i] == T(0)) continue;
                    T c = data[k][i];
                    for (int j = i; j < 2 * n; ++j) data[k][j] -= c * data[i][j];
                }
            }
            for (auto &row : data) row.erase(row.begin(), row.begin() + n);
            return std::make_optional(std::move(A));
        }
        static std::optional<SquareMatrix<T>> inv(const SquareMatrix<T> &A) {
            return SquareMatrix<T>::inv(SquareMatrix<T>(A));
        }
        static T det(SquareMatrix<T> &&A) {
            auto &data = A.data;
            T det_inv = T(1);
            int n = data.size();
            for (int i = 0; i < n; ++i) {
                int pivot = -1;
                for (int k = i; k < n; ++k) {
                    if (data[k][i] != T(0)) {
                        pivot = k;
                        break;
                    }
                }
                if (pivot < 0) return T(0);
                data[i].swap(data[pivot]);
                if (pivot != i) det_inv *= T(-1);
                T coef = T(1) / data[i][i];
                for (int j = i; j < n; ++j) data[i][j] *= coef;
                det_inv *= coef;
                for (int k = i + 1; k < n; ++k) {
                    if (data[k][i] == T(0)) continue;
                    T c = data[k][i];
                    for (int j = i; j < n; ++j) data[k][j] -= c * data[i][j];
                }
            }
            return T(1) / det_inv;
        }
        static T det(const SquareMatrix<T> &A) {
            return SquareMatrix<T>::det(SquareMatrix<T>(A));
        }
        SquareMatrix<T>& inv_inplace() {
            return *this = *SquareMatrix<T>::inv(std::move(*this));
        }
        SquareMatrix<T> inv() const {
            return *SquareMatrix<T>::inv(*this);
        }
        T det() const {
            return SquareMatrix<T>::det(SquareMatrix<T>(*this));
        }

        SquareMatrix<T>& operator/=(const SquareMatrix<T>  &other)       { return *this *= other.inv(); }
        SquareMatrix<T>& operator/=(      SquareMatrix<T> &&other)       { return *this *= other.inv_inplace(); }
        SquareMatrix<T>  operator/ (const SquareMatrix<T>  &other) const { return SquareMatrix<T>(*this) *= other.inv(); }
        SquareMatrix<T>  operator/ (      SquareMatrix<T> &&other) const { return SquareMatrix<T>(*this) *= other.inv_inplace(); }

        SquareMatrix<T> pow(long long b) {
            assert(b >= 0);
            SquareMatrix<T> res(SquareMatrix<T>::e1(this->data.size())), p(*this);
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }
    private:
        SquareMatrix(int n, bool mult_identity) : Matrix<T>::Matrix(n) {
            if (mult_identity) for (int i = 0; i < n; ++i) this->data[i][i] = 1;
        }
};
} // namespace suisen

#endif // SUISEN_MATRIX
