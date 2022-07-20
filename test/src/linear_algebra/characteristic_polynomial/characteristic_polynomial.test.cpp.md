---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/characteristic_polynomial.hpp
    title: "Characteristic Polynomial (\u7279\u6027\u591A\u9805\u5F0F)"
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/hessenberg_reduction.hpp
    title: Hessenberg Reduction
  - icon: ':question:'
    path: library/linear_algebra/matrix.hpp
    title: Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/characteristic_polynomial
    links:
    - https://judge.yosupo.jp/problem/characteristic_polynomial
  bundledCode: "#line 1 \"test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/linear_algebra/characteristic_polynomial.hpp\"\
    \n\n\n\n#line 1 \"library/linear_algebra/hessenberg_reduction.hpp\"\n\n\n\n#line\
    \ 1 \"library/linear_algebra/matrix.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T>\n    struct Matrix {\n        std::vector<std::vector<T>> data;\n\n     \
    \   Matrix() {}\n        Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m,\
    \ fill_value)) {}\n        Matrix(const std::vector<std::vector<T>>& data) noexcept\
    \ : data(data) {}\n        Matrix(std::vector<std::vector<T>>&& data) noexcept\
    \ : data(std::move(data)) {}\n        Matrix(const Matrix<T>& other) noexcept\
    \ : data(other.data) {}\n        Matrix(Matrix<T>&& other) noexcept : data(std::move(other.data))\
    \ {}\n\n        Matrix<T>& operator=(const Matrix<T>& other) noexcept {\n    \
    \        data = other.data;\n            return *this;\n        }\n        Matrix<T>&\
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
    \ suisen\n\n\n#line 5 \"library/linear_algebra/hessenberg_reduction.hpp\"\n\n\
    namespace suisen {\n    /**\n     * Reference: http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\n\
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
    \ suisen\n\n\n\n#line 5 \"library/linear_algebra/characteristic_polynomial.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * Reference: https://ipsen.math.ncsu.edu/ps/charpoly3.pdf\n\
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
    \   }\n        return p[n];\n    }\n} // namespace suisen\n\n\n\n#line 19 \"test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp\"\
    \n\nusing suisen::SquareMatrix;\nusing suisen::characteristic_polynomial;\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    \n    int n;\n    std::cin >> n;\n\n    SquareMatrix<mint> A(n);\n    for\
    \ (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];\n\n\
    \    std::vector<mint> p = characteristic_polynomial(A);\n    for (int i = 0;\
    \ i <= n; ++i) std::cout << p[i] << \" \\n\"[i == n];\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/linear_algebra/characteristic_polynomial.hpp\"\
    \n\nusing suisen::SquareMatrix;\nusing suisen::characteristic_polynomial;\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    \n    int n;\n    std::cin >> n;\n\n    SquareMatrix<mint> A(n);\n    for\
    \ (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];\n\n\
    \    std::vector<mint> p = characteristic_polynomial(A);\n    for (int i = 0;\
    \ i <= n; ++i) std::cout << p[i] << \" \\n\"[i == n];\n\n    return 0;\n}"
  dependsOn:
  - library/linear_algebra/characteristic_polynomial.hpp
  - library/linear_algebra/hessenberg_reduction.hpp
  - library/linear_algebra/matrix.hpp
  isVerificationFile: true
  path: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
  requiredBy: []
  timestamp: '2022-05-14 02:45:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
layout: document
redirect_from:
- /verify/test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
- /verify/test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp.html
title: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
---
