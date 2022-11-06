#ifndef SUISEN_MATRIX_F2
#define SUISEN_MATRIX_F2

#include <cassert>
#include <optional>
#include <vector>

#include "library/datastructure/util/dynamic_bitset.hpp"

namespace suisen {
    struct MatrixF2 {
        MatrixF2() : MatrixF2(0, 0) {}
        MatrixF2(int n, int m, bool fill_value = false) : n(n), m(m), dat(n, DynamicBitSet(m, fill_value)) {}

        const DynamicBitSet& operator[](std::size_t i) const { return dat[i]; }
        DynamicBitSet& operator[](std::size_t i) { return dat[i]; }

        operator std::vector<DynamicBitSet>() const { return dat; }

        friend bool operator==(const MatrixF2& x, const MatrixF2& y) { return x.dat == y.dat; }
        friend bool operator!=(const MatrixF2& x, const MatrixF2& y) { return x.dat != y.dat; }

        std::pair<int, int> shape() const { return { n, m }; }
        int row_size() const { return n; }
        int col_size() const { return m; }

        MatrixF2 transposed() const {
            MatrixF2 t(m, n);
            for (std::size_t i = 0; i < n; ++i) for (std::size_t j = 0; j < m; ++j) t[j][i] = dat[i][j];
            return t;
        }

        friend MatrixF2& operator+=(MatrixF2& x, const MatrixF2& y) {
            assert(x.n == y.n and x.m == y.m);
            for (std::size_t i = 0; i < x.n; ++i) x[i] ^= y[i];
            return x;
        }
        friend MatrixF2& operator-=(MatrixF2& x, const MatrixF2& y) { return x += y; }
        friend MatrixF2& operator*=(MatrixF2& x, const MatrixF2& y) { return x = x * y; }
        friend MatrixF2& operator*=(MatrixF2& x, bool val) {
            if (not val) for (auto& row : x.dat) row.reset();
            return x;
        }
        friend MatrixF2& operator/=(MatrixF2& x, const MatrixF2& y) { return x = x * *y.inv(); }
        friend MatrixF2& operator/=(MatrixF2& x, bool val) {
            assert(val);
            return x;
        }
        friend MatrixF2 operator+(MatrixF2 x, const MatrixF2& y) { x += y; return x; }
        friend MatrixF2 operator-(MatrixF2 x, const MatrixF2& y) { x -= y; return x; }
        friend MatrixF2 operator*(const MatrixF2& x, MatrixF2 y) {
            y = y.transposed();
            assert(x.m == y.m);
            MatrixF2 z(x.n, y.n);
            for (std::size_t i = 0; i < x.n; ++i) for (std::size_t j = 0; j < y.n; ++j) {
                z[i][j] = x[i].has_intersection(y[j]);
            }
            return z;
        }
        friend MatrixF2 operator*(MatrixF2 x, bool val) { x *= val; return x; }
        friend MatrixF2 operator*(bool val, MatrixF2 x) { x *= val; return x; }
        friend MatrixF2 operator/(const MatrixF2 &x, const MatrixF2& y) { return x * *y.inv(); }
        friend MatrixF2 operator/(MatrixF2 x, bool val) { x /= val; return x; }

        DynamicBitSet operator*(const DynamicBitSet& x) const {
            assert(m == std::size_t(x.size()));
            DynamicBitSet y(n);
            for (std::size_t i = 0; i < n; ++i) y[i] = dat[i].has_intersection(x);
            return y;
        }

        MatrixF2 pow(long long b) const {
            assert(n == m);
            MatrixF2 p = *this, res = e1(n);
            for (; b; b >>= 1) {
                if (b & 1) res *= p;
                p *= p;
            }
            return res;
        }

        static MatrixF2 e0(std::size_t n) {
            return MatrixF2(n, n);
        }
        static MatrixF2 e1(std::size_t n) {
            MatrixF2 res(n, n);
            for (std::size_t i = 0; i < n; ++i) res[i][i] = 1;
            return res;
        }

        std::optional<MatrixF2> inv() const {
            assert(n == m);
            MatrixF2 A = *this, B = e1(n);
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = i + 1; j < n; ++j) if (A[j][i]) {
                    std::swap(A[i], A[j]), std::swap(B[i], B[j]);
                    if (A[j][i]) A[j] ^= A[i];
                }
                if (not A[i][i]) return std::nullopt;
            }
            for (std::size_t i = n; i-- > 0;) {
                for (std::size_t j = 0; j < i; ++j) {
                    if (A[j][i]) A[j] ^= A[i], B[j] ^= B[i];
                }
            }
            return B;
        }
        bool det() const {
            MatrixF2 A = *this;
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = i + 1; j < n; ++j) if (A[j][i]) {
                    std::swap(A[i], A[j]);
                    if (A[j][i]) A[j] ^= A[i];
                }
                if (not A[i][i]) return false;
            }
            return true;
        }
        std::size_t rank() const {
            MatrixF2 A = *this;
            std::size_t r = 0;
            for (std::size_t j = 0; j < m; ++j) {
                for (std::size_t i = r + 1; i < n; ++i) if (A[i][j]) {
                    std::swap(A[r], A[i]);
                    if (A[i][j]) A[i] ^= A[r];
                }
                r += A[r][j];
            }
            return r;
        }

    private:
        std::size_t n, m;
        std::vector<DynamicBitSet> dat;
    };
} // namespace suisen


#endif // SUISEN_MATRIX_F2
