---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/linear_algebra/hessenberg_reduction.hpp
    title: Hessenberg Reduction
  - icon: ':x:'
    path: library/linear_algebra/matrix.hpp
    title: Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
    title: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://ipsen.math.ncsu.edu/ps/charpoly3.pdf
  bundledCode: "#line 1 \"library/linear_algebra/characteristic_polynomial.hpp\"\n\
    \n\n\n#line 1 \"library/linear_algebra/hessenberg_reduction.hpp\"\n\n\n\n#line\
    \ 1 \"library/linear_algebra/matrix.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <optional>\n#include <vector>\n\nnamespace suisen {\n  \
    \  template <typename T>\n    struct Matrix {\n        std::vector<std::vector<T>>\
    \ dat;\n\n        Matrix() = default;\n        Matrix(int n) : Matrix(n, n) {}\n\
    \        Matrix(int n, int m, T fill_value = T(0)) : dat(n, std::vector<T>(m,\
    \ fill_value)) {}\n        Matrix(const std::vector<std::vector<T>>& dat) : dat(dat)\
    \ {}\n\n        const std::vector<T>& operator[](int i) const { return dat[i];\
    \ }\n        std::vector<T>& operator[](int i) { return dat[i]; }\n\n        operator\
    \ std::vector<std::vector<T>>() const { return dat; }\n\n        friend bool operator==(const\
    \ Matrix<T>& A, const Matrix<T>& B) { return A.dat == B.dat; }\n        friend\
    \ bool operator!=(const Matrix<T>& A, const Matrix<T>& B) { return A.dat != B.dat;\
    \ }\n\n        std::pair<int, int> shape() const { return dat.empty() ? std::make_pair<int,\
    \ int>(0, 0) : std::make_pair<int, int>(dat.size(), dat[0].size()); }\n      \
    \  int row_size() const { return dat.size(); }\n        int col_size() const {\
    \ return dat.empty() ? 0 : dat[0].size(); }\n\n        friend Matrix<T>& operator+=(Matrix<T>&\
    \ A, const Matrix<T>& B) {\n            assert(A.shape() == B.shape());\n    \
    \        auto [n, m] = A.shape();\n            for (int i = 0; i < n; ++i) for\
    \ (int j = 0; j < m; ++j) A.dat[i][j] += B.dat[i][j];\n            return A;\n\
    \        }\n        friend Matrix<T>& operator-=(Matrix<T>& A, const Matrix<T>&\
    \ B) {\n            assert(A.shape() == B.shape());\n            auto [n, m] =\
    \ A.shape();\n            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)\
    \ A.dat[i][j] -= B.dat[i][j];\n            return A;\n        }\n        friend\
    \ Matrix<T>& operator*=(Matrix<T>& A, const Matrix<T>& B) { return A = A * B;\
    \ }\n        friend Matrix<T>& operator*=(Matrix<T>& A, const T& val) {\n    \
    \        for (auto& row : A.dat) for (auto& elm : row) elm *= val;\n         \
    \   return A;\n        }\n        friend Matrix<T>& operator/=(Matrix<T>& A, const\
    \ T& val) { return A *= T(1) / val; }\n        friend Matrix<T>& operator/=(Matrix<T>&\
    \ A, const Matrix<T>& B) { return A *= B.inv(); }\n\n        friend Matrix<T>\
    \ operator+(Matrix<T> A, const Matrix<T>& B) { A += B; return A; }\n        friend\
    \ Matrix<T> operator-(Matrix<T> A, const Matrix<T>& B) { A -= B; return A; }\n\
    \        friend Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {\n\
    \            assert(A.col_size() == B.row_size());\n            const int n =\
    \ A.row_size(), m = A.col_size(), l = B.col_size();\n\n            if (std::min({\
    \ n, m, l }) <= 70) {\n                // naive\n                Matrix<T> C(n,\
    \ l);\n                for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)\
    \ for (int k = 0; k < l; ++k) {\n                    C.dat[i][k] += A.dat[i][j]\
    \ * B.dat[j][k];\n                }\n                return C;\n            }\n\
    \n            // strassen\n            const int nl = 0, nm = n >> 1, nr = nm\
    \ + nm;\n            const int ml = 0, mm = m >> 1, mr = mm + mm;\n          \
    \  const int ll = 0, lm = l >> 1, lr = lm + lm;\n\n            auto A00 = A.submatrix(nl,\
    \ nm, ml, mm), A01 = A.submatrix(nl, nm, mm, mr);\n            auto A10 = A.submatrix(nm,\
    \ nr, ml, mm), A11 = A.submatrix(nm, nr, mm, mr);\n\n            auto B00 = B.submatrix(ml,\
    \ mm, ll, lm), B01 = B.submatrix(ml, mm, lm, lr);\n            auto B10 = B.submatrix(mm,\
    \ mr, ll, lm), B11 = B.submatrix(mm, mr, lm, lr);\n\n            auto P0 = (A00\
    \ + A11) * (B00 + B11);\n            auto P1 = (A10 + A11) * B00;\n          \
    \  auto P2 = A00 * (B01 - B11);\n            auto P3 = A11 * (B10 - B00);\n  \
    \          auto P4 = (A00 + A01) * B11;\n            auto P5 = (A10 - A00) * (B00\
    \ + B01);\n            auto P6 = (A01 - A11) * (B10 + B11);\n\n            Matrix<T>\
    \ C(n, l);\n\n            C.assign_submatrix(nl, ll, P0 + P3 - P4 + P6), C.assign_submatrix(nl,\
    \ lm, P2 + P4);\n            C.assign_submatrix(nm, ll, P1 + P3), C.assign_submatrix(nm,\
    \ lm, P0 + P2 - P1 + P5);\n\n            // fractions\n            if (l != lr)\
    \ {\n                for (int i = 0; i < nr; ++i) for (int j = 0; j < mr; ++j)\
    \ C.dat[i][lr] += A.dat[i][j] * B.dat[j][lr];\n            }\n            if (m\
    \ != mr) {\n                for (int i = 0; i < nr; ++i) for (int k = 0; k < l;\
    \ ++k) C.dat[i][k] += A.dat[i][mr] * B.dat[mr][k];\n            }\n          \
    \  if (n != nr) {\n                for (int j = 0; j < m; ++j) for (int k = 0;\
    \ k < l; ++k) C.dat[nr][k] += A.dat[nr][j] * B.dat[j][k];\n            }\n\n \
    \           return C;\n        }\n        friend Matrix<T> operator*(const T&\
    \ val, Matrix<T> A) { A *= val; return A; }\n        friend Matrix<T> operator*(Matrix<T>\
    \ A, const T& val) { A *= val; return A; }\n        friend Matrix<T> operator/(const\
    \ Matrix<T>& A, const Matrix<T>& B) { return A * B.inv(); }\n        friend Matrix<T>\
    \ operator/(Matrix<T> A, const T& val) { A /= val; return A; }\n        friend\
    \ Matrix<T> operator/(const T& val, const Matrix<T>& A) { return val * A.inv();\
    \ }\n\n        friend std::vector<T> operator*(const Matrix<T>& A, const std::vector<T>&\
    \ x) {\n            const auto [n, m] = A.shape();\n            assert(m == int(x.size()));\n\
    \            std::vector<T> b(n, T(0));\n            for (int i = 0; i < n; ++i)\
    \ for (int j = 0; j < m; ++j) b[i] += A.dat[i][j] * x[j];\n            return\
    \ b;\n        }\n\n        static Matrix<T> e0(int n) { return Matrix<T>(n, Identity::ADD);\
    \ }\n        static Matrix<T> e1(int n) { return Matrix<T>(n, Identity::MUL);\
    \ }\n\n        Matrix<T> pow(long long b) const {\n            assert_square();\n\
    \            assert(b >= 0);\n            Matrix<T> res = e1(row_size()), p =\
    \ *this;\n            for (; b; b >>= 1) {\n                if (b & 1) res *=\
    \ p;\n                p *= p;\n            }\n            return res;\n      \
    \  }\n        Matrix<T> inv() const { return *safe_inv(); }\n\n        std::optional<Matrix<T>>\
    \ safe_inv() const {\n            assert_square();\n            Matrix<T> A =\
    \ *this;\n            const int n = A.row_size();\n            for (int i = 0;\
    \ i < n; ++i) {\n                A[i].resize(2 * n, T{ 0 });\n               \
    \ A[i][n + i] = T{ 1 };\n            }\n            for (int i = 0; i < n; ++i)\
    \ {\n                for (int k = i; k < n; ++k) if (A[k][i] != T{ 0 }) {\n  \
    \                  std::swap(A[i], A[k]);\n                    T c = T{ 1 } /\
    \ A[i][i];\n                    for (int j = i; j < 2 * n; ++j) A[i][j] *= c;\n\
    \                    break;\n                }\n                if (A[i][i] ==\
    \ T{ 0 }) return std::nullopt;\n                for (int k = 0; k < n; ++k) if\
    \ (k != i and A[k][i] != T{ 0 }) {\n                    T c = A[k][i];\n     \
    \               for (int j = i; j < 2 * n; ++j) A[k][j] -= c * A[i][j];\n    \
    \            }\n            }\n            for (auto& row : A.dat) row.erase(row.begin(),\
    \ row.begin() + n);\n            return A;\n        }\n\n        T det() const\
    \ {\n            assert_square();\n            Matrix<T> A = *this;\n        \
    \    bool sgn = false;\n            const int n = A.row_size();\n            for\
    \ (int j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) if (A[i][j] != T{ 0\
    \ }) {\n                std::swap(A[j], A[i]);\n                T q = A[i][j]\
    \ / A[j][j];\n                for (int k = j; k < n; ++k) A[i][k] -= A[j][k] *\
    \ q;\n                sgn = not sgn;\n            }\n            T res = sgn ?\
    \ T{ -1 } : T{ +1 };\n            for (int i = 0; i < n; ++i) res *= A[i][i];\n\
    \            return res;\n        }\n        T det_arbitrary_mod() const {\n \
    \           assert_square();\n            Matrix<T> A = *this;\n            bool\
    \ sgn = false;\n            const int n = A.row_size();\n            for (int\
    \ j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) {\n                for (;\
    \ A[i][j].val(); sgn = not sgn) {\n                    std::swap(A[j], A[i]);\n\
    \                    T q = A[i][j].val() / A[j][j].val();\n                  \
    \  for (int k = j; k < n; ++k) A[i][k] -= A[j][k] * q;\n                }\n  \
    \          }\n            T res = sgn ? -1 : +1;\n            for (int i = 0;\
    \ i < n; ++i) res *= A[i][i];\n            return res;\n        }\n        void\
    \ assert_square() const { assert(row_size() == col_size()); }\n\n        Matrix<T>\
    \ submatrix(int row_begin, int row_end, int col_begin, int col_end) const {\n\
    \            Matrix<T> A(row_end - row_begin, col_end - col_begin);\n        \
    \    for (int i = row_begin; i < row_end; ++i) for (int j = col_begin; j < col_end;\
    \ ++j) {\n                A[i - row_begin][j - col_begin] = dat[i][j];\n     \
    \       }\n            return A;\n        }\n        void assign_submatrix(int\
    \ row_begin, int col_begin, const Matrix<T>& A) {\n            const int n = A.row_size(),\
    \ m = A.col_size();\n            assert(row_begin + n <= row_size() and col_begin\
    \ + m <= col_size());\n            for (int i = 0; i < n; ++i) for (int j = 0;\
    \ j < m; ++j) {\n                dat[row_begin + i][col_begin + j] = A[i][j];\n\
    \            }\n        }\n    private:\n        enum class Identity {\n     \
    \       ADD, MUL\n        };\n        Matrix(int n, Identity ident) : Matrix<T>::Matrix(n)\
    \ {\n            if (ident == Identity::MUL) for (int i = 0; i < n; ++i) dat[i][i]\
    \ = 1;\n        }\n    };\n} // namespace suisen\n\n\n#line 5 \"library/linear_algebra/hessenberg_reduction.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * Reference: http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\n\
    \     * returns H := P^(-1) A P, where H is hessenberg matrix\n     */\n    template\
    \ <typename T>\n    Matrix<T> hessenberg_reduction(Matrix<T> A) {\n        A.assert_square();\n\
    \        const int n = A.row_size();\n        for (int r = 0; r < n - 2; ++r)\
    \ {\n            int pivot = -1;\n            for (int r2 = r + 1; r2 < n; ++r2)\
    \ if (A[r2][r] != 0) {\n                pivot = r2;\n                break;\n\
    \            }\n            if (pivot < 0) continue;\n            if (pivot !=\
    \ r + 1) {\n                for (int k = 0; k < n; ++k) std::swap(A[r + 1][k],\
    \ A[pivot][k]);\n                for (int k = 0; k < n; ++k) std::swap(A[k][r\
    \ + 1], A[k][pivot]);\n            }\n            const T den = T{1} / A[r + 1][r];\n\
    \            for (int r2 = r + 2; r2 < n; ++r2) if (T coef = A[r2][r] * den; coef\
    \ != 0) {\n                for (int k = r; k < n; ++k) A[r2][k] -= coef * A[r\
    \ + 1][k];\n                for (int k = 0; k < n; ++k) A[k][r + 1] += coef *\
    \ A[k][r2];\n            }\n        }\n        return A;\n    }\n} // namespace\
    \ suisen\n\n\n\n#line 5 \"library/linear_algebra/characteristic_polynomial.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf\n\
    \     * returns p(\u03BB) = det(\u03BBE - A)\n     */\n    template <typename\
    \ T>\n    std::vector<T> characteristic_polynomial(const Matrix<T> &A) {\n   \
    \     A.assert_square();\n        const int n = A.row_size();\n        if (n ==\
    \ 0) return { T{1} };\n        auto H = hessenberg_reduction(A);\n        /**\n\
    \         *     +-              -+\n         *     | a0  *  *  *  * |\n      \
    \   *     | b1 a1  *  *  * |\n         * H = |  0 b2 a2  *  * |\n         *  \
    \   |  0  0 b3 a3  * |\n         *     |  0  0  0 b4 a4 |\n         *     +- \
    \             -+\n         * p_i(\u03BB) := det(\u03BB*E_i - H[:i][:i])\n    \
    \     * p_0(\u03BB) = 1,\n         * p_1(\u03BB) = \u03BB-a_0,\n         * p_i(\u03BB\
    ) = (\u03BB-a_{i-1}) p_{i-1}(\u03BB) - \u03A3[j=0,i-1] p_j(\u03BB) * H_{j,i} *\
    \ \u03A0[k=j+1,i] b_k.\n         */\n        std::vector<std::vector<T>> p(n +\
    \ 1);\n        p[0] = { T{1} }, p[1] = { { -H[0][0], T{1} } };\n        for (int\
    \ i = 1; i < n; ++i) {\n            p[i + 1].resize(i + 2, T{0});\n          \
    \  for (int k = 0; k < i + 1; ++k) {\n                p[i + 1][k] -= H[i][i] *\
    \ p[i][k];\n                p[i + 1][k + 1] += p[i][k];\n            }\n     \
    \       T prod_b = T{1};\n            for (int j = i - 1; j >= 0; --j) {\n   \
    \             prod_b *= H[j + 1][j];\n                T coef = H[j][i] * prod_b;\n\
    \                for (int k = 0; k < j + 1; ++k) p[i + 1][k] -= coef * p[j][k];\n\
    \            }\n        }\n        return p[n];\n    }\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_CHARACTERISTIC_POLYNOMIAL\n#define SUISEN_CHARACTERISTIC_POLYNOMIAL\n\
    \n#include \"library/linear_algebra/hessenberg_reduction.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf\n\
    \     * returns p(\u03BB) = det(\u03BBE - A)\n     */\n    template <typename\
    \ T>\n    std::vector<T> characteristic_polynomial(const Matrix<T> &A) {\n   \
    \     A.assert_square();\n        const int n = A.row_size();\n        if (n ==\
    \ 0) return { T{1} };\n        auto H = hessenberg_reduction(A);\n        /**\n\
    \         *     +-              -+\n         *     | a0  *  *  *  * |\n      \
    \   *     | b1 a1  *  *  * |\n         * H = |  0 b2 a2  *  * |\n         *  \
    \   |  0  0 b3 a3  * |\n         *     |  0  0  0 b4 a4 |\n         *     +- \
    \             -+\n         * p_i(\u03BB) := det(\u03BB*E_i - H[:i][:i])\n    \
    \     * p_0(\u03BB) = 1,\n         * p_1(\u03BB) = \u03BB-a_0,\n         * p_i(\u03BB\
    ) = (\u03BB-a_{i-1}) p_{i-1}(\u03BB) - \u03A3[j=0,i-1] p_j(\u03BB) * H_{j,i} *\
    \ \u03A0[k=j+1,i] b_k.\n         */\n        std::vector<std::vector<T>> p(n +\
    \ 1);\n        p[0] = { T{1} }, p[1] = { { -H[0][0], T{1} } };\n        for (int\
    \ i = 1; i < n; ++i) {\n            p[i + 1].resize(i + 2, T{0});\n          \
    \  for (int k = 0; k < i + 1; ++k) {\n                p[i + 1][k] -= H[i][i] *\
    \ p[i][k];\n                p[i + 1][k + 1] += p[i][k];\n            }\n     \
    \       T prod_b = T{1};\n            for (int j = i - 1; j >= 0; --j) {\n   \
    \             prod_b *= H[j + 1][j];\n                T coef = H[j][i] * prod_b;\n\
    \                for (int k = 0; k < j + 1; ++k) p[i + 1][k] -= coef * p[j][k];\n\
    \            }\n        }\n        return p[n];\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_CHARACTERISTIC_POLYNOMIAL\n"
  dependsOn:
  - library/linear_algebra/hessenberg_reduction.hpp
  - library/linear_algebra/matrix.hpp
  isVerificationFile: false
  path: library/linear_algebra/characteristic_polynomial.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
documentation_of: library/linear_algebra/characteristic_polynomial.hpp
layout: document
title: "Characteristic Polynomial (\u7279\u6027\u591A\u9805\u5F0F)"
---

## Characteristic Polynomial (特性多項式)

$N\times N$ 行列 $A$ の特性多項式 $p_A(\lambda) := \det(\lambda E _ N - A)$ を $\Theta(N ^ 3)$ 時間で計算するアルゴリズムの実装です．

### 概要

特性多項式に関する重要な性質として，__相似変換により不変__ ということが挙げられる．

<details>
<summary>証明</summary>

$N\times N$ 行列 $A$ と正則な $N\times N$ 行列 $P$ を任意に取る．任意の $\lambda$ に対して $\det(\lambda E _ N - A) = \det(\lambda E_N - P ^ {-1} A P)$ を示せばよいが，これは次のようにして示される．

$$\begin{aligned}
\det(\lambda E _ N - A)
&= \det(\lambda E_N - A) \det(E _ N) \\
&= \det(\lambda E_N - A) \det(P ^ {-1} P) \\
&= \det(P ^ {-1}) \det(\lambda E_N - A) \det(P) \\
&= \det(P ^ {-1} (\lambda E_N - A) P) \\
&= \det(\lambda E_N - P ^ {-1} A P) \\
\end{aligned}$$

</details>

そこで，$A$ に相似変換を施して特性多項式を求めやすい行列 $B$ を得，代わりに $B$ の特性多項式を計算することを考える．

ここでは，特性多項式を求めやすい行列として __上 Hessenberg 行列__ を用いる．上 Hessenberg 行列とは，以下のような形をした行列をいう．

$$
\begin{bmatrix}
\alpha _ 0 & \ast & \ast & \ast & \ast \\
\beta _ 1  & \alpha _ 1 & \ast & \ast & \ast \\
0 & \beta _ 2 & \alpha _ 2 & \ast & \ast \\
\vdots & \ddots & \ddots & \ddots & \vdots \\
0 & \cdots & 0 & \beta _ {N - 1} & \alpha _ {N - 1}
\end{bmatrix}
$$

$H$ を上 Hessenberg 行列として，$H$ の特性多項式 $p _ H(\lambda)$ は以下に示すアルゴリズムにより $\Theta(N ^ 3)$ 時間で計算できる．

#### 上 Hessenberg 行列 $H$ の特性多項式を計算するアルゴリズム

Reference : https://ipsen.math.ncsu.edu/ps/charpoly3.pdf

__方針__

$H ^ {(k)} := (H _ {i, j}) _ {0 \leq i, j \lt k}$ および $p _ H ^ {(k)} (\lambda) := p _ {H ^ {(k)} }(\lambda)$ と定義する．

多項式の列 $\\\{ p _ H ^ {(k)}\\\} _ {k = 0} ^ N$ に対して成り立つ漸化式を導出することで $k = 0, \ldots, N$ の順に $p _ H ^ {(k)} (\lambda)$ を計算する．$p _ H(\lambda) = p _ H ^ {(N)} (\lambda)$ が求めたい多項式である．

__アルゴリズム__

$N = 0$ の場合は自明なので，$N \gt 0$ を仮定する．

$H$ は以下のように表されるとする．

$$
H =
\begin{bmatrix}
\alpha _ 0 & \ast & \ast & \ast & \ast \\
\beta _ 1  & \alpha _ 1 & \ast & \ast & \ast \\
0 & \beta _ 2 & \alpha _ 2 & \ast & \ast \\
\vdots & \ddots & \ddots & \ddots & \vdots \\
0 & \cdots & 0 & \beta _ {N - 1} & \alpha _ {N - 1}
\end{bmatrix}
$$

まず，明らかに $p _ H ^ {(0)} (\lambda) = 1, \; p _ H ^ {(1)} (\lambda) = \lambda - \alpha _ 0$ である．$k \geq 2$ に対して，$p _ H ^ {(k)}$ を $p _ H ^ {(0)}, \ldots, p _ H ^ {(k - 1)}$ から計算することを考える．

$N\times N$ 行列 $A$ に対して，行列式 $\det(A)$ は次で定義される．ここで，$\mathfrak{S} _ N$ は $N$ 次の置換全体の集合，$\mathrm{sgn}: \mathfrak{S} _ N \to \\\{ -1, +1 \\\}$ は引数の置換 $\sigma$ が偶置換なら $+1$，奇置換なら $-1$ を取る関数である．

$$
\det (A) := \sum _ {\sigma \in \mathfrak{S} _ N} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {N - 1} A _ {i, \sigma(i)}
$$

$p _ H ^ {(k)} (\lambda) = \det (\lambda E _ k - H ^ {(k)})$ を上記の式を用いて計算する．$\sigma (i) = k - 1$ を満たす $i$ によって場合分けをする．

- $\sigma(k - 1) = k - 1$ の場合

  以下が成立する．

  $$\begin{aligned}
  & \sum _ {\sigma \in \{\sigma \in \mathfrak{S} _ k \mid \sigma(k - 1) = k - 1\}} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) \sum _ {\sigma' \in \mathfrak{S} _ {k - 1}} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {k - 2} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma'(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) \sum _ {\sigma' \in \mathfrak{S} _ {k - 1}} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {k - 2} (\lambda E _ {k - 1} - H ^ {(k - 1)}) _ {i, \sigma'(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) p _ H ^ {(k - 1)}
  \end{aligned}$$

- $\sigma(l) = k - 1,\; l \neq k - 1$ の場合

  $\displaystyle \prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \neq 0$ を満たすためには，全ての $i = l + 1, \ldots, k - 1$ に対して $\sigma(i) = i - 1$ を満たす必要がある．従って，以下が成り立つ．

  $$\begin{aligned}
  & \sum _ {\sigma \in \{\sigma \in \mathfrak{S} _ k \mid \sigma(l) = k - 1\land l \neq k - 1\}} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \\
  =\ & \Bigl(-H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} -\beta _ i\Bigr) \cdot (-1) ^ {k - l - 1} \sum _ {\sigma' \in \mathfrak{S} _ l} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {l - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma'(i)} \\
  =\ & -\Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) \sum _ {\sigma' \in \mathfrak{S} _ l} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {l - 1} (\lambda E _ l - H ^ {(l)}) _ {i, \sigma'(i)} \\
  =\ & -\Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) p _ H ^ {(l)}
  \end{aligned}$$

以上より，$k\geq 2$ に対して次が成立する．

$$
p _ H ^ {(k)} = (\lambda - \alpha _ {k - 1}) p _ H ^ {(k - 1)} - \sum _ {l = 0} ^ {k - 2} \Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) p _ H ^ {(l)}
$$

右辺は $\Theta(N ^ 2)$ 時間で計算できるので，結局全ての $p _ H ^ {(k)}$ を $\Theta(N ^ 3)$ 時間で計算することが出来る．

上 Hessenberg 行列 $H$ の特性多項式を $\Theta(N ^ 3)$ で計算することができたので，あとは任意の $N \times N$ 行列 $A$ を相似変換により上 Hessenberg 行列へと変換することができればよいが，[Hessenberg Reduction](https://suisen-cp.github.io/cp-library-cpp/library/linear_algebra/hessenberg_reduction.hpp) に示したように，これは $\Theta(N ^ 3)$ 時間で行うことが出来る．
