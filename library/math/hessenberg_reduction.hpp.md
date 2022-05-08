---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/matrix.hpp
    title: Matrix
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/characteristic_polynomial.hpp
    title: "Characteristic Polynomial (\u7279\u6027\u591A\u9805\u5F0F)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
    title: test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf
  bundledCode: "#line 1 \"library/math/hessenberg_reduction.hpp\"\n\n\n\n#line 1 \"\
    library/math/matrix.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T>\n    struct Matrix\
    \ {\n        std::vector<std::vector<T>> data;\n\n        Matrix() {}\n      \
    \  Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m, fill_value))\
    \ {}\n        Matrix(const std::vector<std::vector<T>>& data) noexcept : data(data)\
    \ {}\n        Matrix(std::vector<std::vector<T>>&& data) noexcept : data(std::move(data))\
    \ {}\n        Matrix(const Matrix<T>& other) noexcept : data(other.data) {}\n\
    \        Matrix(Matrix<T>&& other) noexcept : data(std::move(other.data)) {}\n\
    \n        Matrix<T>& operator=(const Matrix<T>& other) noexcept {\n          \
    \  data = other.data;\n            return *this;\n        }\n        Matrix<T>&\
    \ operator=(Matrix<T>&& other) noexcept {\n            data = std::move(other.data);\n\
    \            return *this;\n        }\n\n        const std::vector<T>& operator[](int\
    \ i) const { return data[i]; }\n        std::vector<T>& operator[](int i) { return\
    \ data[i]; }\n\n        std::pair<int, int> size() const {\n            if (data.empty())\
    \ {\n                return { 0, 0 };\n            } else {\n                return\
    \ { data.size(), data[0].size() };\n            }\n        }\n        int row_size()\
    \ const {\n            return data.size();\n        }\n        int col_size()\
    \ const {\n            return data.empty() ? 0 : data[0].size();\n        }\n\n\
    \        Matrix<T>& operator+=(const Matrix<T>& other) {\n            assert(size()\
    \ == other.size());\n            auto [n, m] = size();\n            for (int i\
    \ = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n                data[i][j] +=\
    \ other[i][j];\n            }\n            return *this;\n        }\n        Matrix<T>&\
    \ operator-=(const Matrix<T>& other) {\n            assert(size() == other.size());\n\
    \            auto [n, m] = size();\n            for (int i = 0; i < n; ++i) for\
    \ (int j = 0; j < m; ++j) {\n                data[i][j] -= other[i][j];\n    \
    \        }\n            return *this;\n        }\n        Matrix<T>& operator*=(const\
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
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_HESSENBERG_REDUCTION\n#define SUISEN_HESSENBERG_REDUCTION\n\
    \n#include \"library/math/matrix.hpp\"\n\nnamespace suisen {\n    /**\n     *\
    \ Reference: http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\n     * returns\
    \ H := P^(-1) A P, where H is hessenberg matrix\n     */\n    template <typename\
    \ T>\n    SquareMatrix<T> hessenberg_reduction(SquareMatrix<T> A) {\n        const\
    \ int n = A.row_size();\n        for (int r = 0; r < n - 2; ++r) {\n         \
    \   int pivot = -1;\n            for (int r2 = r + 1; r2 < n; ++r2) if (A[r2][r]\
    \ != 0) {\n                pivot = r2;\n                break;\n            }\n\
    \            if (pivot < 0) continue;\n            if (pivot != r + 1) {\n   \
    \             for (int k = 0; k < n; ++k) std::swap(A[r + 1][k], A[pivot][k]);\n\
    \                for (int k = 0; k < n; ++k) std::swap(A[k][r + 1], A[k][pivot]);\n\
    \            }\n            const T den = T{1} / A[r + 1][r];\n            for\
    \ (int r2 = r + 2; r2 < n; ++r2) if (T coef = A[r2][r] * den; coef != 0) {\n \
    \               for (int k = r; k < n; ++k) A[r2][k] -= coef * A[r + 1][k];\n\
    \                for (int k = 0; k < n; ++k) A[k][r + 1] += coef * A[k][r2];\n\
    \            }\n        }\n        return A;\n    }\n} // namespace suisen\n\n\
    \n#endif // SUISEN_HESSENBERG_REDUCTION\n"
  dependsOn:
  - library/math/matrix.hpp
  isVerificationFile: false
  path: library/math/hessenberg_reduction.hpp
  requiredBy:
  - library/math/characteristic_polynomial.hpp
  timestamp: '2022-04-16 16:20:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/characteristic_polynomial/characteristic_polynomial.test.cpp
documentation_of: library/math/hessenberg_reduction.hpp
layout: document
title: Hessenberg Reduction
---
## Hessenberg Reduction

$N \times N$ 行列 $A$ と相似な上 Hessenberg 行列 $H$ を $\Theta(N ^ 3)$ 時間で計算します．

### 概要

Reference : http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf

__方針__

行列 $A$ に対して行基本変形を $k$ 回行った結果得られる行列 $B$ は基本変形を表す行列 $P _ 1, P_ 2, \ldots, P _ k$ により $B = P _ k P _ {k - 1} \cdots P _ 1 A$ と表される．

基本変形を表す行列は正則であるから，$(P _ k P _ {k - 1} \cdots P _ 1) A (P _ k P _ {k - 1} \cdots P _ 1) ^ {-1} = P _ k (P _ {k - 1} (\cdots (P _ 1 A P _ 1 ^ {-1}) \cdots) P _ {k - 1} ^ {-1}) P _ k ^ {-1}$ は相似変換である．

即ち，行基本変形とその逆行列による列基本変形をセットにして行列 $A$ を掃き出すことで上 Hessenberg 行列 $H$ を得ることが出来れば，$A$ と $H$ は相似である．

__アルゴリズム__

次のような，掃き出し法により上三角行列を得るアルゴリズムとよく似た手続きにより上 Hessenberg 行列へと相似変換することができる．

1. $i = 0, \ldots, N - 3$ の順に以下を行う．
   1. $i + 1\leq j \lt N$ かつ $A _ {j, i} \neq 0$ を満たす $j$ を任意に $1$ つ選ぶ．ただし，そのような $j$ が存在しない場合は，次の $i$ に進む．
   2. $A$ の $i + 1$ 行目と $j$ 行目を swap する．
   3. 相似変換であることを保つため，$A$ の $i + 1$ 列目と $j$ 列目を swap する．
   4. 各 $k = i + 2, \ldots, N - 1$ に対して以下を行う．
      1. $c := \dfrac{A _ {k, i}}{A _ {i + 1, i}}$ とする．
      2. $A$ の $k$ 行目から $i + 1$ 行目の $c$ 倍を差し引く．
      3. 相似変換であることを保つため，$A$ の $i + 1$ 列目に $k$ 列目の $c$ 倍を足し込む．

列基本変形により以前 $0$ にした部分が再び非零になったり，あるいは $A _ {i + 1, i} = 0$ となってしまったりすると上 Hessenberg 行列への変換は失敗するが，列基本変形は $i + 1$ 列目から $N - 1$ 列目までにしか変更を加えないため，そのようなことは起こり得ない．

従って，上記の手続きにより $A$ は上 Hessenberg 行列へと相似変換される．時間計算量は $\Theta(N ^ 3)$ である．