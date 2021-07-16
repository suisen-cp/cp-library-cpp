#ifndef SUISEN_MATRIX
#define SUISEN_MATRIX

#include <cassert>
#include <vector>

namespace suisen {
template <typename T>
class matrix_ops {
    public:
        std::vector<std::vector<T>> E0(int n, int m) {
            std::vector<std::vector<T>> e0(n, std::vector<T>(m, _zero));
            return e0;
        }
        std::vector<std::vector<T>> E0(int n) {
            std::vector<std::vector<T>> e0(n, std::vector<T>(n, _zero));
            return e0;
        }
        std::vector<std::vector<T>> E1(int n) {
            std::vector<std::vector<T>> e1(n, std::vector<T>(n, _zero));
            for (int i = 0; i < n; ++i) e1[i][i] = _one;
            return e1;
        }
        std::vector<std::vector<T>> add(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B) {
            int n = A.size(), m = A[0].size();
            assert(int(B.size()) == n and int(B[0].size()) == m);
            std::vector<std::vector<T>> C = E0(n, m);
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
            return C;
        }
        std::vector<std::vector<T>> mul(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B) {
            int n = A.size(), m = A[0].size(), l = B[0].size();
            assert(int(B.size()) == m);
            std::vector<std::vector<T>> C(n, std::vector<T>(l, _zero));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k)  {
                C[i][k] += A[i][j] * B[j][k];
            }
            return C;
        }
        std::vector<T> mul(std::vector<std::vector<T>>& A, std::vector<T>& x) {
            int n = A.size(), m = A[0].size();
            assert(m == int(x.size()));
            std::vector<T> b(n, _zero);
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                b[i] += A[i][j] * x[j];
            }
            return b;
        }
        std::vector<std::vector<T>> pow(std::vector<std::vector<T>>& A, unsigned long long b) {
            int n = A.size();
            std::vector<std::vector<T>> res = E1(n);
            while (b) {
                if (b & 1) res = mul(res, A);
                A = mul(A, A);
                b >>= 1;
            }
            return res;
        }
    private:
        T _zero = 0, _one = 1;
};
} // namespace suisen

#endif // SUISEN_MATRIX
