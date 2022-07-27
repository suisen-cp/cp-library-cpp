#ifndef SUISEN_MATRIX
#define SUISEN_MATRIX

#include <cassert>
#include <optional>
#include <vector>

namespace suisen {
    template <typename T>
    struct Matrix {
        std::vector<std::vector<T>> dat;

        Matrix() {}
        Matrix(int n, int m, T fill_value = T(0)) : dat(n, std::vector<T>(m, fill_value)) {}
        Matrix(const std::vector<std::vector<T>>& dat) : dat(dat) {}

        const std::vector<T>& operator[](int i) const { return dat[i]; }
        std::vector<T>& operator[](int i) { return dat[i]; }

        operator std::vector<std::vector<T>>() const { return dat; }

        bool operator==(const Matrix<T>& other) const { return this->dat == other.dat; }
        bool operator!=(const Matrix<T>& other) const { return this->dat != other.dat; }

        std::pair<int, int> shape() const { return dat.empty() ? std::make_pair<int, int>(0, 0) : std::make_pair<int, int>(dat.size(), dat[0].size()); }
        int row_size() const { return dat.size(); }
        int col_size() const { return dat.empty() ? 0 : dat[0].size(); }

        Matrix<T>& operator+=(const Matrix<T>& other) {
            assert(shape() == other.shape());
            auto [n, m] = shape();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) dat[i][j] += other[i][j];
            return *this;
        }
        Matrix<T>& operator-=(const Matrix<T>& other) {
            assert(shape() == other.shape());
            auto [n, m] = shape();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) dat[i][j] -= other[i][j];
            return *this;
        }
        Matrix<T>& operator*=(const Matrix<T>& other) { return *this = *this * other; }
        Matrix<T>& operator*=(const T& val) {
            for (auto &row : dat) for (auto &elm : row) elm *= val;
            return *this;
        }
        Matrix<T>& operator/=(const T& val) { return *this *= T(1) / val; }
        Matrix<T> operator+(const Matrix<T>& other) const { Matrix<T> res = *this; res += other; return res; }
        Matrix<T> operator-(const Matrix<T>& other) const { Matrix<T> res = *this; res -= other; return res; }
        Matrix<T> operator*(const Matrix<T>& other) const {
            auto [n, m] = shape();
            auto [m2, l] = other.shape();
            assert(m == m2);
            std::vector res(n, std::vector(l, T(0)));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k) res[i][k] += (*this)[i][j] * other[j][k];
            return res;
        }
        Matrix<T> operator*(const T& val) const { Matrix<T> res = *this; res *= val; return res; }
        Matrix<T> operator/(const T& val) const { Matrix<T> res = *this; res /= val; return res; }

        std::vector<T> operator*(const std::vector<T>& x) const {
            auto [n, m] = shape();
            assert(m == int(x.size()));
            std::vector<T> b(n, T(0));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) b[i] += dat[i][j] * x[j];
            return b;
        }
    };

    template <typename T>
    struct SquareMatrix : public Matrix<T> {
        SquareMatrix() {}
        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n, n, fill_value) {}
        SquareMatrix(const std::vector<std::vector<T>>& dat) : Matrix<T>::Matrix(dat) {
            auto [n, m] = this->shape();
            assert(n == m);
        }

        int size() const { return this->row_size(); }

        bool operator==(const SquareMatrix<T>& other) const { return this->dat == other.dat; }
        bool operator!=(const SquareMatrix<T>& other) const { return this->dat != other.dat; }

        static SquareMatrix<T> e0(int n) { return SquareMatrix<T>(n, false, /* dummy */ 0); }
        static SquareMatrix<T> e1(int n) { return SquareMatrix<T>(n, true, /* dummy */ 0); }

        static std::optional<SquareMatrix<T>> inv(SquareMatrix<T> A) {
            int n = A.size();
            for (int i = 0; i < n; ++i) {
                A[i].resize(2 * n, T{ 0 });
                A[i][n + i] = T{ 1 };
            }
            for (int i = 0; i < n; ++i) {
                int pivot = -1;
                for (int k = i; k < n; ++k) if (A[k][i] != T{ 0 }) {
                    pivot = k;
                    break;
                }
                if (pivot < 0) return std::nullopt;
                std::swap(A[i], A[pivot]);
                T coef = T{ 1 } / A[i][i];
                for (int j = i; j < 2 * n; ++j) A[i][j] *= coef;
                for (int k = 0; k < n; ++k) if (k != i and A[k][i] != T{ 0 }) {
                    T c = A[k][i];
                    for (int j = i; j < 2 * n; ++j) A[k][j] -= c * A[i][j];
                }
            }
            for (auto& row : A.dat) row.erase(row.begin(), row.begin() + n);
            return A;
        }
        static T det(SquareMatrix<T> A) {
            bool sgn = false;
            const int n = A.size();
            for (int j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) if (A[i][j] != T { 0 }) {
                std::swap(A[j], A[i]);
                T q = A[i][j] / A[j][j];
                for (int k = j; k < n; ++k) A[i][k] -= A[j][k] * q;
                sgn = not sgn;
            }
            T res = sgn ? T { -1 } : T { +1 };
            for (int i = 0; i < n; ++i) res *= A[i][i];
            return res;
        }
        static T det_arbitrary_mod(SquareMatrix<T> A) {
            bool sgn = false;
            const int n = A.size();
            for (int j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) {
                for (; A[i][j].val(); sgn = not sgn) {
                    std::swap(A[j], A[i]);
                    T q = A[i][j].val() / A[j][j].val();
                    for (int k = j; k < n; ++k) A[i][k] -= A[j][k] * q;
                }
            }
            T res = sgn ? -1 : +1;
            for (int i = 0; i < n; ++i) res *= A[i][i];
            return res;
        }
        SquareMatrix<T>& inv_inplace() {
            return *this = *SquareMatrix<T>::inv(std::move(*this));
        }
        SquareMatrix<T> inv() const {
            return *SquareMatrix<T>::inv(*this);
        }
        T det() const {
            return SquareMatrix<T>::det(*this);
        }
        T det_arbitrary_mod() const {
            return SquareMatrix<T>::det_arbitrary_mod(*this);
        }

        SquareMatrix<T>& operator/=(const SquareMatrix<T>& other) { return *this *= other.inv(); }
        SquareMatrix<T>  operator/ (const SquareMatrix<T>& other) const { SquareMatrix<T> res = *this; res /= other; return res; }

        SquareMatrix<T> pow(long long b) {
            assert(b >= 0);
            SquareMatrix<T> res(SquareMatrix<T>::e1(size())), p(*this);
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }
    private:
        SquareMatrix(int n, bool mult_identity, int) : Matrix<T>::Matrix(n, n) {
            if (mult_identity) for (int i = 0; i < n; ++i) this->dat[i][i] = 1;
        }
    };
} // namespace suisen

#endif // SUISEN_MATRIX
