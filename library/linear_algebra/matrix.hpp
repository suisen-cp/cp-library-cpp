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
        Matrix(int n) : Matrix(n, n) {}
        Matrix(int n, int m, T fill_value = T(0)) : dat(n, std::vector<T>(m, fill_value)) {}
        Matrix(const std::vector<std::vector<T>>& dat) : dat(dat) {}

        const std::vector<T>& operator[](int i) const { return dat[i]; }
        std::vector<T>& operator[](int i) { return dat[i]; }

        operator std::vector<std::vector<T>>() const { return dat; }

        friend bool operator==(const Matrix<T> &A, const Matrix<T>& B) { return A.dat == B.dat; }
        friend bool operator!=(const Matrix<T> &A, const Matrix<T>& B) { return A.dat != B.dat; }

        std::pair<int, int> shape() const { return dat.empty() ? std::make_pair<int, int>(0, 0) : std::make_pair<int, int>(dat.size(), dat[0].size()); }
        int row_size() const { return dat.size(); }
        int col_size() const { return dat.empty() ? 0 : dat[0].size(); }

        friend Matrix<T>& operator+=(Matrix<T>& A, const Matrix<T>& B) {
            assert(A.shape() == B.shape());
            auto [n, m] = A.shape();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) A.dat[i][j] += B.dat[i][j];
            return A;
        }
        friend Matrix<T>& operator-=(Matrix<T>& A, const Matrix<T>& B) {
            assert(A.shape() == B.shape());
            auto [n, m] = A.shape();
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) A.dat[i][j] -= B.dat[i][j];
            return A;
        }
        friend Matrix<T>& operator*=(Matrix<T>& A, const Matrix<T>& B) { return A = A * B; }
        friend Matrix<T>& operator*=(Matrix<T>& A, const T& val) {
            for (auto &row : A.dat) for (auto &elm : row) elm *= val;
            return A;
        }
        friend Matrix<T>& operator/=(Matrix<T>& A, const T& val) { return A *= T(1) / val; }
        friend Matrix<T>& operator/=(Matrix<T>& A, const Matrix<T> &B) { return A *= B.inv(); }
    
        friend Matrix<T> operator+(Matrix<T> A, const Matrix<T>& B) { A += B; return A; }
        friend Matrix<T> operator-(Matrix<T> A, const Matrix<T>& B) { A -= B; return A; }
        friend Matrix<T> operator*(const Matrix<T> &A, const Matrix<T>& B) {
            assert(A.col_size() == B.row_size());
            const int n = A.row_size(), m = A.col_size(), l = B.col_size();
            std::vector res(n, std::vector(l, T(0)));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k) res[i][k] += A.dat[i][j] * B.dat[j][k];
            return res;
        }
        friend Matrix<T> operator*(const T& val, Matrix<T> A) { A *= val; return A; }
        friend Matrix<T> operator*(Matrix<T> A, const T& val) { A *= val; return A; }
        friend Matrix<T> operator/(const Matrix<T> &A, const Matrix<T>& B) { return A * B.inv(); }
        friend Matrix<T> operator/(Matrix<T> A, const T& val) { A /= val; return A; }
        friend Matrix<T> operator/(const T& val, const Matrix<T> &A) { return val * A.inv(); }

        friend std::vector<T> operator*(const Matrix<T> &A, const std::vector<T>& x) {
            const auto [n, m] = A.shape();
            assert(m == int(x.size()));
            std::vector<T> b(n, T(0));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) b[i] += A.dat[i][j] * x[j];
            return b;
        }

        static Matrix<T> e0(int n) { return Matrix<T>(n, Identity::ADD); }
        static Matrix<T> e1(int n) { return Matrix<T>(n, Identity::MUL); }

        Matrix<T> pow(long long b) const {
            assert_square();
            assert(b >= 0);
            Matrix<T> res = e1(row_size()), p = *this;
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }
        Matrix<T> inv() const { return *safe_inv(); }

        std::optional<Matrix<T>> safe_inv() const {
            assert_square();
            Matrix<T> A = *this;
            const int n = A.row_size();
            for (int i = 0; i < n; ++i) {
                A[i].resize(2 * n, T{ 0 });
                A[i][n + i] = T{ 1 };
            }
            for (int i = 0; i < n; ++i) {
                for (int k = i; k < n; ++k) if (A[k][i] != T{ 0 }) {
                    std::swap(A[i], A[k]);
                    T c = T { 1 } / A[i][i];
                    for (int j = i; j < 2 * n; ++j) A[i][j] *= c;
                    break;
                }
                if (A[i][i] == T{ 0 }) return std::nullopt;
                for (int k = 0; k < n; ++k) if (k != i and A[k][i] != T{ 0 }) {
                    T c = A[k][i];
                    for (int j = i; j < 2 * n; ++j) A[k][j] -= c * A[i][j];
                }
            }
            for (auto& row : A.dat) row.erase(row.begin(), row.begin() + n);
            return A;
        }

        T det() const {
            assert_square();
            Matrix<T> A = *this;
            bool sgn = false;
            const int n = A.row_size();
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
        T det_arbitrary_mod() const {
            assert_square();
            Matrix<T> A = *this;
            bool sgn = false;
            const int n = A.row_size();
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
        void assert_square() const { assert(row_size() == col_size()); }
    private:
        enum class Identity {
            ADD, MUL
        };
        Matrix(int n, Identity ident) : Matrix<T>::Matrix(n) {
            if (ident == Identity::MUL) for (int i = 0; i < n; ++i) dat[i][i] = 1;
        }
    };
} // namespace suisen

#endif // SUISEN_MATRIX
