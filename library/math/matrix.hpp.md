---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/matrix/determinant_of_matrix.test.cpp
    title: test/src/math/matrix/determinant_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/matrix/inverse_matrix.test.cpp
    title: test/src/math/matrix/inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/matrix/matrix_product.test.cpp
    title: test/src/math/matrix/matrix_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/matrix.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename T>\n\
    struct Matrix {\n    std::vector<std::vector<T>> data;\n    \n    Matrix() {}\n\
    \    Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m, fill_value))\
    \ {}\n    Matrix(const std::vector<std::vector<T>>  &data) noexcept : data(data)\
    \ {}\n    Matrix(      std::vector<std::vector<T>> &&data) noexcept : data(std::move(data))\
    \ {}\n    Matrix(const Matrix<T>  &other) noexcept : data(other.data) {}\n   \
    \ Matrix(      Matrix<T> &&other) noexcept : data(std::move(other.data)) {}\n\n\
    \    Matrix<T>& operator=(const Matrix<T> &other) noexcept {\n        data = other.data;\n\
    \        return *this;\n    }\n    Matrix<T>& operator=(Matrix<T> &&other) noexcept\
    \ {\n        data = std::move(other.data);\n        return *this;\n    }\n\n \
    \   const std::vector<T>& operator[](int i) const { return data[i]; }\n      \
    \    std::vector<T>& operator[](int i)       { return data[i]; }\n\n    std::pair<int,\
    \ int> size() const {\n        if (data.empty()) {\n            return {0, 0};\n\
    \        } else {\n            return {data.size(), data[0].size()};\n       \
    \ }\n    }\n    int row_size() const {\n        return data.size();\n    }\n \
    \   int col_size() const {\n        return data.empty() ? 0 : data[0].size();\n\
    \    }\n\n    Matrix<T>& operator+=(const Matrix<T> &other) {\n        assert(size()\
    \ == other.size());\n        auto [n, m] = size();\n        for (int i = 0; i\
    \ < n; ++i) for (int j = 0; j < m; ++j) {\n            data[i][j] += other[i][j];\n\
    \        }\n        return *this;\n    }\n    Matrix<T>& operator-=(const Matrix<T>\
    \ &other) {\n        assert(size() == other.size());\n        auto [n, m] = size();\n\
    \        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n         \
    \   data[i][j] -= other[i][j];\n        }\n        return *this;\n    }\n    Matrix<T>&\
    \ operator*=(const Matrix<T> &other) {\n        return *this = *this * other;\n\
    \    }\n    Matrix<T>& operator*=(const T &val) {\n        auto [n, m] = size();\n\
    \        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n         \
    \   data[i][j] *= val;\n        }\n        return *this;\n    }\n    Matrix<T>&\
    \ operator/=(const T &val) {\n        return *this *= T(1) / val;\n    }\n   \
    \ Matrix<T> operator+(const Matrix<T> &other) const {\n        return Matrix<T>(*this)\
    \ += other;\n    }\n    Matrix<T> operator-(const Matrix<T> &other) const {\n\
    \        return Matrix<T>(*this) -= other;\n    }\n    Matrix<T> operator*(const\
    \ Matrix<T> &other) const {\n        auto [n, m] = size();\n        auto [m2,\
    \ l] = other.size();\n        assert(m == m2);\n        std::vector res(n, std::vector(l,\
    \ T(0)));\n        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for\
    \ (int k = 0; k < l; ++k) {\n            res[i][k] += (*this)[i][j] * other[j][k];\n\
    \        }\n        return res;\n    }\n    Matrix<T> operator*(const T &val)\
    \ const {\n        return Matrix<T>(*this) *= val;\n    }\n    Matrix<T> operator/(const\
    \ T &val) const {\n        return Matrix<T>(*this) /= val;\n    }\n\n    std::vector<T>\
    \ operator*(const std::vector<T> &x) const {\n        auto [n, m] = size();\n\
    \        assert(m == int(x.size()));\n        std::vector<T> b(n, T(0));\n   \
    \     for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n            b[i]\
    \ += data[i][j] * x[j];\n        }\n        return b;\n    }\n};\n\ntemplate <typename\
    \ T>\nclass SquareMatrix : public Matrix<T> {\n    public:\n        SquareMatrix()\
    \ {}\n        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n,\
    \ n, fill_value) {}\n        SquareMatrix(const std::vector<std::vector<T>> &data)\
    \ : Matrix<T>::Matrix(data) {\n            auto [n, m] = this->size();\n     \
    \       assert(n == m);\n        }\n        SquareMatrix(std::vector<std::vector<T>>\
    \ &&data) : Matrix<T>::Matrix(std::move(data)) {\n            auto [n, m] = this->size();\n\
    \            assert(n == m);\n        }\n        SquareMatrix(const SquareMatrix<T>\
    \  &other) : SquareMatrix(other.data) {}\n        SquareMatrix(      SquareMatrix<T>\
    \ &&other) : SquareMatrix(std::move(other.data)) {}\n        SquareMatrix(const\
    \ Matrix<T>  &other) : Matrix<T>::Matrix(other.data) {}\n        SquareMatrix(\
    \      Matrix<T> &&other) : Matrix<T>::Matrix(std::move(other.data)) {}\n\n  \
    \      SquareMatrix<T>& operator=(const SquareMatrix<T> &other) noexcept {\n \
    \           this->data = other.data;\n            return *this;\n        }\n \
    \       SquareMatrix<T>& operator=(SquareMatrix<T> &&other) noexcept {\n     \
    \       this->data = std::move(other.data);\n            return *this;\n     \
    \   }\n\n        static SquareMatrix<T> e0(int n) { return SquareMatrix<T>(n,\
    \ false); }\n        static SquareMatrix<T> e1(int n) { return SquareMatrix<T>(n,\
    \ true); }\n\n        static std::optional<SquareMatrix<T>> inv(SquareMatrix<T>\
    \ &&A) {\n            auto &data = A.data;\n            int n = data.size();\n\
    \            for (int i = 0; i < n; ++i) {\n                data[i].resize(2 *\
    \ n, T{0});\n                data[i][n + i] = T{1};\n            }\n         \
    \   for (int i = 0; i < n; ++i) {\n                int pivot = -1;\n         \
    \       for (int k = i; k < n; ++k) {\n                    if (data[k][i] != T{0})\
    \ {\n                        pivot = k;\n                        break;\n    \
    \                }\n                }\n                if (pivot < 0) return std::nullopt;\n\
    \                data[i].swap(data[pivot]);\n                T coef = T{1} / data[i][i];\n\
    \                for (int j = i; j < 2 * n; ++j) data[i][j] *= coef;\n       \
    \         for (int k = 0; k < n; ++k) {\n                    if (k == i or data[k][i]\
    \ == T{0}) continue;\n                    T c = data[k][i];\n                \
    \    for (int j = i; j < 2 * n; ++j) data[k][j] -= c * data[i][j];\n         \
    \       }\n            }\n            for (auto &row : data) row.erase(row.begin(),\
    \ row.begin() + n);\n            return std::make_optional(std::move(A));\n  \
    \      }\n        static std::optional<SquareMatrix<T>> inv(const SquareMatrix<T>\
    \ &A) {\n            return SquareMatrix<T>::inv(SquareMatrix<T>(A));\n      \
    \  }\n        static T det(SquareMatrix<T> &&A) {\n            auto &data = A.data;\n\
    \            T det_inv = T{1};\n            int n = data.size();\n           \
    \ for (int i = 0; i < n; ++i) {\n                int pivot = -1;\n           \
    \     for (int k = i; k < n; ++k) {\n                    if (data[k][i] != T{0})\
    \ {\n                        pivot = k;\n                        break;\n    \
    \                }\n                }\n                if (pivot < 0) return T{0};\n\
    \                data[i].swap(data[pivot]);\n                if (pivot != i) det_inv\
    \ *= T{-1};\n                T coef = T{1} / data[i][i];\n                for\
    \ (int j = i; j < n; ++j) data[i][j] *= coef;\n                det_inv *= coef;\n\
    \                for (int k = i + 1; k < n; ++k) {\n                    if (data[k][i]\
    \ == T(0)) continue;\n                    T c = data[k][i];\n                \
    \    for (int j = i; j < n; ++j) data[k][j] -= c * data[i][j];\n             \
    \   }\n            }\n            return T{1} / det_inv;\n        }\n        static\
    \ T det(const SquareMatrix<T> &A) {\n            return SquareMatrix<T>::det(SquareMatrix<T>(A));\n\
    \        }\n        SquareMatrix<T>& inv_inplace() {\n            return *this\
    \ = *SquareMatrix<T>::inv(std::move(*this));\n        }\n        SquareMatrix<T>\
    \ inv() const {\n            return *SquareMatrix<T>::inv(*this);\n        }\n\
    \        T det() const {\n            return SquareMatrix<T>::det(SquareMatrix<T>(*this));\n\
    \        }\n\n        SquareMatrix<T>& operator/=(const SquareMatrix<T>  &other)\
    \       { return *this *= other.inv(); }\n        SquareMatrix<T>& operator/=(\
    \      SquareMatrix<T> &&other)       { return *this *= other.inv_inplace(); }\n\
    \        SquareMatrix<T>  operator/ (const SquareMatrix<T>  &other) const { return\
    \ SquareMatrix<T>(*this) *= other.inv(); }\n        SquareMatrix<T>  operator/\
    \ (      SquareMatrix<T> &&other) const { return SquareMatrix<T>(*this) *= other.inv_inplace();\
    \ }\n\n        SquareMatrix<T> pow(long long b) {\n            assert(b >= 0);\n\
    \            SquareMatrix<T> res(SquareMatrix<T>::e1(this->data.size())), p(*this);\n\
    \            for (; b; b >>= 1) {\n                if (b & 1) res *= p;\n    \
    \            p *= p;\n            }\n            return res;\n        }\n    private:\n\
    \        SquareMatrix(int n, bool mult_identity) : Matrix<T>::Matrix(n, n) {\n\
    \            if (mult_identity) for (int i = 0; i < n; ++i) this->data[i][i] =\
    \ 1;\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MATRIX\n#define SUISEN_MATRIX\n\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename T>\n\
    struct Matrix {\n    std::vector<std::vector<T>> data;\n    \n    Matrix() {}\n\
    \    Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m, fill_value))\
    \ {}\n    Matrix(const std::vector<std::vector<T>>  &data) noexcept : data(data)\
    \ {}\n    Matrix(      std::vector<std::vector<T>> &&data) noexcept : data(std::move(data))\
    \ {}\n    Matrix(const Matrix<T>  &other) noexcept : data(other.data) {}\n   \
    \ Matrix(      Matrix<T> &&other) noexcept : data(std::move(other.data)) {}\n\n\
    \    Matrix<T>& operator=(const Matrix<T> &other) noexcept {\n        data = other.data;\n\
    \        return *this;\n    }\n    Matrix<T>& operator=(Matrix<T> &&other) noexcept\
    \ {\n        data = std::move(other.data);\n        return *this;\n    }\n\n \
    \   const std::vector<T>& operator[](int i) const { return data[i]; }\n      \
    \    std::vector<T>& operator[](int i)       { return data[i]; }\n\n    std::pair<int,\
    \ int> size() const {\n        if (data.empty()) {\n            return {0, 0};\n\
    \        } else {\n            return {data.size(), data[0].size()};\n       \
    \ }\n    }\n    int row_size() const {\n        return data.size();\n    }\n \
    \   int col_size() const {\n        return data.empty() ? 0 : data[0].size();\n\
    \    }\n\n    Matrix<T>& operator+=(const Matrix<T> &other) {\n        assert(size()\
    \ == other.size());\n        auto [n, m] = size();\n        for (int i = 0; i\
    \ < n; ++i) for (int j = 0; j < m; ++j) {\n            data[i][j] += other[i][j];\n\
    \        }\n        return *this;\n    }\n    Matrix<T>& operator-=(const Matrix<T>\
    \ &other) {\n        assert(size() == other.size());\n        auto [n, m] = size();\n\
    \        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n         \
    \   data[i][j] -= other[i][j];\n        }\n        return *this;\n    }\n    Matrix<T>&\
    \ operator*=(const Matrix<T> &other) {\n        return *this = *this * other;\n\
    \    }\n    Matrix<T>& operator*=(const T &val) {\n        auto [n, m] = size();\n\
    \        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n         \
    \   data[i][j] *= val;\n        }\n        return *this;\n    }\n    Matrix<T>&\
    \ operator/=(const T &val) {\n        return *this *= T(1) / val;\n    }\n   \
    \ Matrix<T> operator+(const Matrix<T> &other) const {\n        return Matrix<T>(*this)\
    \ += other;\n    }\n    Matrix<T> operator-(const Matrix<T> &other) const {\n\
    \        return Matrix<T>(*this) -= other;\n    }\n    Matrix<T> operator*(const\
    \ Matrix<T> &other) const {\n        auto [n, m] = size();\n        auto [m2,\
    \ l] = other.size();\n        assert(m == m2);\n        std::vector res(n, std::vector(l,\
    \ T(0)));\n        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for\
    \ (int k = 0; k < l; ++k) {\n            res[i][k] += (*this)[i][j] * other[j][k];\n\
    \        }\n        return res;\n    }\n    Matrix<T> operator*(const T &val)\
    \ const {\n        return Matrix<T>(*this) *= val;\n    }\n    Matrix<T> operator/(const\
    \ T &val) const {\n        return Matrix<T>(*this) /= val;\n    }\n\n    std::vector<T>\
    \ operator*(const std::vector<T> &x) const {\n        auto [n, m] = size();\n\
    \        assert(m == int(x.size()));\n        std::vector<T> b(n, T(0));\n   \
    \     for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n            b[i]\
    \ += data[i][j] * x[j];\n        }\n        return b;\n    }\n};\n\ntemplate <typename\
    \ T>\nclass SquareMatrix : public Matrix<T> {\n    public:\n        SquareMatrix()\
    \ {}\n        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n,\
    \ n, fill_value) {}\n        SquareMatrix(const std::vector<std::vector<T>> &data)\
    \ : Matrix<T>::Matrix(data) {\n            auto [n, m] = this->size();\n     \
    \       assert(n == m);\n        }\n        SquareMatrix(std::vector<std::vector<T>>\
    \ &&data) : Matrix<T>::Matrix(std::move(data)) {\n            auto [n, m] = this->size();\n\
    \            assert(n == m);\n        }\n        SquareMatrix(const SquareMatrix<T>\
    \  &other) : SquareMatrix(other.data) {}\n        SquareMatrix(      SquareMatrix<T>\
    \ &&other) : SquareMatrix(std::move(other.data)) {}\n        SquareMatrix(const\
    \ Matrix<T>  &other) : Matrix<T>::Matrix(other.data) {}\n        SquareMatrix(\
    \      Matrix<T> &&other) : Matrix<T>::Matrix(std::move(other.data)) {}\n\n  \
    \      SquareMatrix<T>& operator=(const SquareMatrix<T> &other) noexcept {\n \
    \           this->data = other.data;\n            return *this;\n        }\n \
    \       SquareMatrix<T>& operator=(SquareMatrix<T> &&other) noexcept {\n     \
    \       this->data = std::move(other.data);\n            return *this;\n     \
    \   }\n\n        static SquareMatrix<T> e0(int n) { return SquareMatrix<T>(n,\
    \ false); }\n        static SquareMatrix<T> e1(int n) { return SquareMatrix<T>(n,\
    \ true); }\n\n        static std::optional<SquareMatrix<T>> inv(SquareMatrix<T>\
    \ &&A) {\n            auto &data = A.data;\n            int n = data.size();\n\
    \            for (int i = 0; i < n; ++i) {\n                data[i].resize(2 *\
    \ n, T{0});\n                data[i][n + i] = T{1};\n            }\n         \
    \   for (int i = 0; i < n; ++i) {\n                int pivot = -1;\n         \
    \       for (int k = i; k < n; ++k) {\n                    if (data[k][i] != T{0})\
    \ {\n                        pivot = k;\n                        break;\n    \
    \                }\n                }\n                if (pivot < 0) return std::nullopt;\n\
    \                data[i].swap(data[pivot]);\n                T coef = T{1} / data[i][i];\n\
    \                for (int j = i; j < 2 * n; ++j) data[i][j] *= coef;\n       \
    \         for (int k = 0; k < n; ++k) {\n                    if (k == i or data[k][i]\
    \ == T{0}) continue;\n                    T c = data[k][i];\n                \
    \    for (int j = i; j < 2 * n; ++j) data[k][j] -= c * data[i][j];\n         \
    \       }\n            }\n            for (auto &row : data) row.erase(row.begin(),\
    \ row.begin() + n);\n            return std::make_optional(std::move(A));\n  \
    \      }\n        static std::optional<SquareMatrix<T>> inv(const SquareMatrix<T>\
    \ &A) {\n            return SquareMatrix<T>::inv(SquareMatrix<T>(A));\n      \
    \  }\n        static T det(SquareMatrix<T> &&A) {\n            auto &data = A.data;\n\
    \            T det_inv = T{1};\n            int n = data.size();\n           \
    \ for (int i = 0; i < n; ++i) {\n                int pivot = -1;\n           \
    \     for (int k = i; k < n; ++k) {\n                    if (data[k][i] != T{0})\
    \ {\n                        pivot = k;\n                        break;\n    \
    \                }\n                }\n                if (pivot < 0) return T{0};\n\
    \                data[i].swap(data[pivot]);\n                if (pivot != i) det_inv\
    \ *= T{-1};\n                T coef = T{1} / data[i][i];\n                for\
    \ (int j = i; j < n; ++j) data[i][j] *= coef;\n                det_inv *= coef;\n\
    \                for (int k = i + 1; k < n; ++k) {\n                    if (data[k][i]\
    \ == T(0)) continue;\n                    T c = data[k][i];\n                \
    \    for (int j = i; j < n; ++j) data[k][j] -= c * data[i][j];\n             \
    \   }\n            }\n            return T{1} / det_inv;\n        }\n        static\
    \ T det(const SquareMatrix<T> &A) {\n            return SquareMatrix<T>::det(SquareMatrix<T>(A));\n\
    \        }\n        SquareMatrix<T>& inv_inplace() {\n            return *this\
    \ = *SquareMatrix<T>::inv(std::move(*this));\n        }\n        SquareMatrix<T>\
    \ inv() const {\n            return *SquareMatrix<T>::inv(*this);\n        }\n\
    \        T det() const {\n            return SquareMatrix<T>::det(SquareMatrix<T>(*this));\n\
    \        }\n\n        SquareMatrix<T>& operator/=(const SquareMatrix<T>  &other)\
    \       { return *this *= other.inv(); }\n        SquareMatrix<T>& operator/=(\
    \      SquareMatrix<T> &&other)       { return *this *= other.inv_inplace(); }\n\
    \        SquareMatrix<T>  operator/ (const SquareMatrix<T>  &other) const { return\
    \ SquareMatrix<T>(*this) *= other.inv(); }\n        SquareMatrix<T>  operator/\
    \ (      SquareMatrix<T> &&other) const { return SquareMatrix<T>(*this) *= other.inv_inplace();\
    \ }\n\n        SquareMatrix<T> pow(long long b) {\n            assert(b >= 0);\n\
    \            SquareMatrix<T> res(SquareMatrix<T>::e1(this->data.size())), p(*this);\n\
    \            for (; b; b >>= 1) {\n                if (b & 1) res *= p;\n    \
    \            p *= p;\n            }\n            return res;\n        }\n    private:\n\
    \        SquareMatrix(int n, bool mult_identity) : Matrix<T>::Matrix(n, n) {\n\
    \            if (mult_identity) for (int i = 0; i < n; ++i) this->data[i][i] =\
    \ 1;\n        }\n};\n} // namespace suisen\n\n#endif // SUISEN_MATRIX\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/matrix.hpp
  requiredBy: []
  timestamp: '2021-09-21 22:08:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/matrix/matrix_product.test.cpp
  - test/src/math/matrix/determinant_of_matrix.test.cpp
  - test/src/math/matrix/inverse_matrix.test.cpp
documentation_of: library/math/matrix.hpp
layout: document
redirect_from:
- /library/library/math/matrix.hpp
- /library/library/math/matrix.hpp.html
title: library/math/matrix.hpp
---
