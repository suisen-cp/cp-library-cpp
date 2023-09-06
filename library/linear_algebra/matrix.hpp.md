---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/characteristic_polynomial.hpp
    title: "Characteristic Polynomial (\u7279\u6027\u591A\u9805\u5F0F)"
  - icon: ':x:'
    path: library/linear_algebra/count_spanning_trees.hpp
    title: "\u884C\u5217\u6728\u5B9A\u7406\u306B\u3088\u308B\u5168\u57DF\u6728\u306E\
      \u6570\u3048\u4E0A\u3052"
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/hessenberg_reduction.hpp
    title: Hessenberg Reduction
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
    title: test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/matrix/inverse_matrix.test.cpp
    title: test/src/linear_algebra/matrix/inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/matrix/matrix_det.test.cpp
    title: test/src/linear_algebra/matrix/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/matrix/matrix_det_arbitrary_mod.test.cpp
    title: test/src/linear_algebra/matrix/matrix_det_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/matrix/matrix_product.test.cpp
    title: test/src/linear_algebra/matrix/matrix_product.test.cpp
  - icon: ':x:'
    path: test/src/math/set_power_series/abc253_h.test.cpp
    title: test/src/math/set_power_series/abc253_h.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/linear_algebra/matrix.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <optional>\n#include <vector>\n\nnamespace suisen\
    \ {\n    template <typename T>\n    struct Matrix {\n        std::vector<std::vector<T>>\
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
    \ = 1;\n        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MATRIX\n#define SUISEN_MATRIX\n\n#include <algorithm>\n#include\
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
    \ = 1;\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_MATRIX\n"
  dependsOn: []
  isVerificationFile: false
  path: library/linear_algebra/matrix.hpp
  requiredBy:
  - library/linear_algebra/hessenberg_reduction.hpp
  - library/linear_algebra/characteristic_polynomial.hpp
  - library/linear_algebra/count_spanning_trees.hpp
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/linear_algebra/matrix/matrix_det_arbitrary_mod.test.cpp
  - test/src/linear_algebra/matrix/matrix_det.test.cpp
  - test/src/linear_algebra/matrix/matrix_product.test.cpp
  - test/src/linear_algebra/matrix/inverse_matrix.test.cpp
  - test/src/linear_algebra/characteristic_polynomial/characteristic_polynomial.test.cpp
  - test/src/math/set_power_series/abc253_h.test.cpp
documentation_of: library/linear_algebra/matrix.hpp
layout: document
title: Matrix
---
## Matrix