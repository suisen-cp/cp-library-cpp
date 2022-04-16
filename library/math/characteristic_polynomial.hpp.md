---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/hessenberg_reduction.hpp
    title: Hessenberg Reduction
  - icon: ':heavy_check_mark:'
    path: library/math/matrix.hpp
    title: Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
    title: test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ipsen.math.ncsu.edu/ps/charpoly3.pdf
  bundledCode: "#line 1 \"library/math/characteristic_polynomial.hpp\"\n\n\n\n#line\
    \ 1 \"library/math/hessenberg_reduction.hpp\"\n\n\n\n#line 1 \"library/math/matrix.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\nnamespace\
    \ suisen {\n    template <typename T>\n    struct Matrix {\n        std::vector<std::vector<T>>\
    \ data;\n\n        Matrix() {}\n        Matrix(int n, int m, T fill_value = T(0))\
    \ : data(n, std::vector<T>(m, fill_value)) {}\n        Matrix(const std::vector<std::vector<T>>&\
    \ data) noexcept : data(data) {}\n        Matrix(std::vector<std::vector<T>>&&\
    \ data) noexcept : data(std::move(data)) {}\n        Matrix(const Matrix<T>& other)\
    \ noexcept : data(other.data) {}\n        Matrix(Matrix<T>&& other) noexcept :\
    \ data(std::move(other.data)) {}\n\n        Matrix<T>& operator=(const Matrix<T>&\
    \ other) noexcept {\n            data = other.data;\n            return *this;\n\
    \        }\n        Matrix<T>& operator=(Matrix<T>&& other) noexcept {\n     \
    \       data = std::move(other.data);\n            return *this;\n        }\n\n\
    \        const std::vector<T>& operator[](int i) const { return data[i]; }\n \
    \       std::vector<T>& operator[](int i) { return data[i]; }\n\n        std::pair<int,\
    \ int> size() const {\n            if (data.empty()) {\n                return\
    \ { 0, 0 };\n            } else {\n                return { data.size(), data[0].size()\
    \ };\n            }\n        }\n        int row_size() const {\n            return\
    \ data.size();\n        }\n        int col_size() const {\n            return\
    \ data.empty() ? 0 : data[0].size();\n        }\n\n        Matrix<T>& operator+=(const\
    \ Matrix<T>& other) {\n            assert(size() == other.size());\n         \
    \   auto [n, m] = size();\n            for (int i = 0; i < n; ++i) for (int j\
    \ = 0; j < m; ++j) {\n                data[i][j] += other[i][j];\n           \
    \ }\n            return *this;\n        }\n        Matrix<T>& operator-=(const\
    \ Matrix<T>& other) {\n            assert(size() == other.size());\n         \
    \   auto [n, m] = size();\n            for (int i = 0; i < n; ++i) for (int j\
    \ = 0; j < m; ++j) {\n                data[i][j] -= other[i][j];\n           \
    \ }\n            return *this;\n        }\n        Matrix<T>& operator*=(const\
    \ Matrix<T>& other) {\n            return *this = *this * other;\n        }\n\
    \        Matrix<T>& operator*=(const T& val) {\n            auto [n, m] = size();\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n     \
    \           data[i][j] *= val;\n            }\n            return *this;\n   \
    \     }\n        Matrix<T>& operator/=(const T& val) {\n            return *this\
    \ *= T(1) / val;\n        }\n        Matrix<T> operator+(const Matrix<T>& other)\
    \ const {\n            return Matrix<T>(*this) += other;\n        }\n        Matrix<T>\
    \ operator-(const Matrix<T>& other) const {\n            return Matrix<T>(*this)\
    \ -= other;\n        }\n        Matrix<T> operator*(const Matrix<T>& other) const\
    \ {\n            auto [n, m] = size();\n            auto [m2, l] = other.size();\n\
    \            assert(m == m2);\n            std::vector res(n, std::vector(l, T(0)));\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int\
    \ k = 0; k < l; ++k) {\n                res[i][k] += (*this)[i][j] * other[j][k];\n\
    \            }\n            return res;\n        }\n        Matrix<T> operator*(const\
    \ T& val) const {\n            return Matrix<T>(*this) *= val;\n        }\n  \
    \      Matrix<T> operator/(const T& val) const {\n            return Matrix<T>(*this)\
    \ /= val;\n        }\n\n        std::vector<T> operator*(const std::vector<T>&\
    \ x) const {\n            auto [n, m] = size();\n            assert(m == int(x.size()));\n\
    \            std::vector<T> b(n, T(0));\n            for (int i = 0; i < n; ++i)\
    \ for (int j = 0; j < m; ++j) {\n                b[i] += data[i][j] * x[j];\n\
    \            }\n            return b;\n        }\n    };\n\n    template <typename\
    \ T>\n    class SquareMatrix : public Matrix<T> {\n    public:\n        SquareMatrix()\
    \ {}\n        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n,\
    \ n, fill_value) {}\n        SquareMatrix(const std::vector<std::vector<T>>& data)\
    \ : Matrix<T>::Matrix(data) {\n            auto [n, m] = this->size();\n     \
    \       assert(n == m);\n        }\n        SquareMatrix(std::vector<std::vector<T>>&&\
    \ data) : Matrix<T>::Matrix(std::move(data)) {\n            auto [n, m] = this->size();\n\
    \            assert(n == m);\n        }\n        SquareMatrix(const SquareMatrix<T>&\
    \ other) : SquareMatrix(other.data) {}\n        SquareMatrix(SquareMatrix<T>&&\
    \ other) : SquareMatrix(std::move(other.data)) {}\n        SquareMatrix(const\
    \ Matrix<T>& other) : Matrix<T>::Matrix(other.data) {}\n        SquareMatrix(Matrix<T>&&\
    \ other) : Matrix<T>::Matrix(std::move(other.data)) {}\n\n        SquareMatrix<T>&\
    \ operator=(const SquareMatrix<T>& other) noexcept {\n            this->data =\
    \ other.data;\n            return *this;\n        }\n        SquareMatrix<T>&\
    \ operator=(SquareMatrix<T>&& other) noexcept {\n            this->data = std::move(other.data);\n\
    \            return *this;\n        }\n\n        bool operator==(const SquareMatrix<T>&\
    \ other) noexcept {\n            return this->data == other.data;\n        }\n\
    \        bool operator!=(const SquareMatrix<T>& other) noexcept {\n          \
    \  return this->data != other.data;\n        }\n\n        static SquareMatrix<T>\
    \ e0(int n) { return SquareMatrix<T>(n, false); }\n        static SquareMatrix<T>\
    \ e1(int n) { return SquareMatrix<T>(n, true); }\n\n        static std::optional<SquareMatrix<T>>\
    \ inv(SquareMatrix<T>&& A) {\n            auto& data = A.data;\n            int\
    \ n = data.size();\n            for (int i = 0; i < n; ++i) {\n              \
    \  data[i].resize(2 * n, T{ 0 });\n                data[i][n + i] = T{ 1 };\n\
    \            }\n            for (int i = 0; i < n; ++i) {\n                int\
    \ pivot = -1;\n                for (int k = i; k < n; ++k) {\n               \
    \     if (data[k][i] != T{ 0 }) {\n                        pivot = k;\n      \
    \                  break;\n                    }\n                }\n        \
    \        if (pivot < 0) return std::nullopt;\n                data[i].swap(data[pivot]);\n\
    \                T coef = T{ 1 } / data[i][i];\n                for (int j = i;\
    \ j < 2 * n; ++j) data[i][j] *= coef;\n                for (int k = 0; k < n;\
    \ ++k) {\n                    if (k == i or data[k][i] == T{ 0 }) continue;\n\
    \                    T c = data[k][i];\n                    for (int j = i; j\
    \ < 2 * n; ++j) data[k][j] -= c * data[i][j];\n                }\n           \
    \ }\n            for (auto& row : data) row.erase(row.begin(), row.begin() + n);\n\
    \            return std::make_optional(std::move(A));\n        }\n        static\
    \ std::optional<SquareMatrix<T>> inv(const SquareMatrix<T>& A) {\n           \
    \ return SquareMatrix<T>::inv(SquareMatrix<T>(A));\n        }\n        static\
    \ T det(SquareMatrix<T>&& A) {\n            auto& data = A.data;\n           \
    \ T det_inv = T{ 1 };\n            int n = data.size();\n            for (int\
    \ i = 0; i < n; ++i) {\n                int pivot = -1;\n                for (int\
    \ k = i; k < n; ++k) {\n                    if (data[k][i] != T{ 0 }) {\n    \
    \                    pivot = k;\n                        break;\n            \
    \        }\n                }\n                if (pivot < 0) return T{ 0 };\n\
    \                data[i].swap(data[pivot]);\n                if (pivot != i) det_inv\
    \ *= T{ -1 };\n                T coef = T{ 1 } / data[i][i];\n               \
    \ for (int j = i; j < n; ++j) data[i][j] *= coef;\n                det_inv *=\
    \ coef;\n                for (int k = i + 1; k < n; ++k) {\n                 \
    \   if (data[k][i] == T(0)) continue;\n                    T c = data[k][i];\n\
    \                    for (int j = i; j < n; ++j) data[k][j] -= c * data[i][j];\n\
    \                }\n            }\n            return T{ 1 } / det_inv;\n    \
    \    }\n        static T det(const SquareMatrix<T>& A) {\n            return SquareMatrix<T>::det(SquareMatrix<T>(A));\n\
    \        }\n        SquareMatrix<T>& inv_inplace() {\n            return *this\
    \ = *SquareMatrix<T>::inv(std::move(*this));\n        }\n        SquareMatrix<T>\
    \ inv() const {\n            return *SquareMatrix<T>::inv(*this);\n        }\n\
    \        T det() const {\n            return SquareMatrix<T>::det(SquareMatrix<T>(*this));\n\
    \        }\n\n        SquareMatrix<T>& operator/=(const SquareMatrix<T>& other)\
    \ { return *this *= other.inv(); }\n        SquareMatrix<T>& operator/=(SquareMatrix<T>&&\
    \ other) { return *this *= other.inv_inplace(); }\n        SquareMatrix<T>  operator/\
    \ (const SquareMatrix<T>& other) const { return SquareMatrix<T>(*this) *= other.inv();\
    \ }\n        SquareMatrix<T>  operator/ (SquareMatrix<T>&& other) const { return\
    \ SquareMatrix<T>(*this) *= other.inv_inplace(); }\n\n        SquareMatrix<T>\
    \ pow(long long b) {\n            assert(b >= 0);\n            SquareMatrix<T>\
    \ res(SquareMatrix<T>::e1(this->data.size())), p(*this);\n            for (; b;\
    \ b >>= 1) {\n                if (b & 1) res *= p;\n                p *= p;\n\
    \            }\n            return res;\n        }\n    private:\n        SquareMatrix(int\
    \ n, bool mult_identity) : Matrix<T>::Matrix(n, n) {\n            if (mult_identity)\
    \ for (int i = 0; i < n; ++i) this->data[i][i] = 1;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#line 5 \"library/math/hessenberg_reduction.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * Reference: http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\n\
    \     * returns H := P^(-1) A P, where H is hessenberg matrix\n     */\n    template\
    \ <typename T>\n    SquareMatrix<T> hessenberg_reduction(SquareMatrix<T> A) {\n\
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
    \ suisen\n\n\n\n#line 5 \"library/math/characteristic_polynomial.hpp\"\n\nnamespace\
    \ suisen {\n    /**\n     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf\n\
    \     * returns p(\u03BB) = det(\u03BBE - A)\n     */\n    template <typename\
    \ T>\n    std::vector<T> characteristic_polynomial(const SquareMatrix<T> &A) {\n\
    \        const int n = A.row_size();\n        if (n == 0) return { T{1} };\n \
    \       auto H = hessenberg_reduction(A);\n        /**\n         *     +-    \
    \          -+\n         *     | a0  *  *  *  * |\n         *     | b1 a1  *  *\
    \  * |\n         * H = |  0 b2 a2  *  * |\n         *     |  0  0 b3 a3  * |\n\
    \         *     |  0  0  0 b4 a4 |\n         *     +-              -+\n      \
    \   * p_i(\u03BB) := det(\u03BB*E_i - H[:i][:i])\n         * p_0(\u03BB) = 1,\n\
    \         * p_1(\u03BB) = \u03BB-a_0,\n         * p_i(\u03BB) = (\u03BB-a_{i-1})\
    \ p_{i-1}(\u03BB) - \u03A3[j=0,i-1] p_j(\u03BB) * H_{j,i} * \u03A0[k=j+1,i] b_k.\n\
    \         */\n        std::vector<std::vector<T>> p(n + 1);\n        p[0] = {\
    \ T{1} }, p[1] = { { -H[0][0], T{1} } };\n        for (int i = 1; i < n; ++i)\
    \ {\n            p[i + 1].resize(i + 2, T{0});\n            for (int k = 0; k\
    \ < i + 1; ++k) {\n                p[i + 1][k] -= H[i][i] * p[i][k];\n       \
    \         p[i + 1][k + 1] += p[i][k];\n            }\n            T prod_b = T{1};\n\
    \            for (int j = i - 1; j >= 0; --j) {\n                prod_b *= H[j\
    \ + 1][j];\n                T coef = H[j][i] * prod_b;\n                for (int\
    \ k = 0; k < j + 1; ++k) p[i + 1][k] -= coef * p[j][k];\n            }\n     \
    \   }\n        return p[n];\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CHARACTERISTIC_POLYNOMIAL\n#define SUISEN_CHARACTERISTIC_POLYNOMIAL\n\
    \n#include \"library/math/hessenberg_reduction.hpp\"\n\nnamespace suisen {\n \
    \   /**\n     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf\n    \
    \ * returns p(\u03BB) = det(\u03BBE - A)\n     */\n    template <typename T>\n\
    \    std::vector<T> characteristic_polynomial(const SquareMatrix<T> &A) {\n  \
    \      const int n = A.row_size();\n        if (n == 0) return { T{1} };\n   \
    \     auto H = hessenberg_reduction(A);\n        /**\n         *     +-      \
    \        -+\n         *     | a0  *  *  *  * |\n         *     | b1 a1  *  * \
    \ * |\n         * H = |  0 b2 a2  *  * |\n         *     |  0  0 b3 a3  * |\n\
    \         *     |  0  0  0 b4 a4 |\n         *     +-              -+\n      \
    \   * p_i(\u03BB) := det(\u03BB*E_i - H[:i][:i])\n         * p_0(\u03BB) = 1,\n\
    \         * p_1(\u03BB) = \u03BB-a_0,\n         * p_i(\u03BB) = (\u03BB-a_{i-1})\
    \ p_{i-1}(\u03BB) - \u03A3[j=0,i-1] p_j(\u03BB) * H_{j,i} * \u03A0[k=j+1,i] b_k.\n\
    \         */\n        std::vector<std::vector<T>> p(n + 1);\n        p[0] = {\
    \ T{1} }, p[1] = { { -H[0][0], T{1} } };\n        for (int i = 1; i < n; ++i)\
    \ {\n            p[i + 1].resize(i + 2, T{0});\n            for (int k = 0; k\
    \ < i + 1; ++k) {\n                p[i + 1][k] -= H[i][i] * p[i][k];\n       \
    \         p[i + 1][k + 1] += p[i][k];\n            }\n            T prod_b = T{1};\n\
    \            for (int j = i - 1; j >= 0; --j) {\n                prod_b *= H[j\
    \ + 1][j];\n                T coef = H[j][i] * prod_b;\n                for (int\
    \ k = 0; k < j + 1; ++k) p[i + 1][k] -= coef * p[j][k];\n            }\n     \
    \   }\n        return p[n];\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_CHARACTERISTIC_POLYNOMIAL\n"
  dependsOn:
  - library/math/hessenberg_reduction.hpp
  - library/math/matrix.hpp
  isVerificationFile: false
  path: library/math/characteristic_polynomial.hpp
  requiredBy: []
  timestamp: '2022-04-16 16:40:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
documentation_of: library/math/characteristic_polynomial.hpp
layout: document
title: Characteristic Polynomial
---

## Characteristic Polynomial

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

上 Hessenberg 行列 $H$ の特性多項式を $\Theta(N ^ 3)$ で計算することができたので，あとは任意の $N \times N$ 行列 $A$ を相似変換により上 Hessenberg 行列へと変換することができればよいが，[Hessenberg Reduction](https://suisen-cp.github.io/cp-library-cpp/library/math/hessenberg_reduction.hpp) に示したように，これは $\Theta(N ^ 3)$ 時間で行うことが出来る．
