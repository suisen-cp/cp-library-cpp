---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
    title: test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/array_matrix/inverse_matrix.test.cpp
    title: test/src/linear_algebra/array_matrix/inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/array_matrix/matrix_det.test.cpp
    title: test/src/linear_algebra/array_matrix/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
    title: test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/linear_algebra/array_matrix.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <optional>\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 9 \"library/linear_algebra/array_matrix.hpp\"\n\nnamespace suisen {\n\
    \    template <\n        typename T, size_t N, size_t M,\n        T(*_add)(T,\
    \ T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>,\n        T(*_mul)(T, T) = default_operator_noref::mul<T>,\
    \ T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)() = default_operator_noref::one<T>\n\
    \    >\n    struct ArrayMatrix : public std::array<std::array<T, M>, N> {\n  \
    \  private:\n        enum Operator { Add, Mul };\n        template <typename DummyType\
    \ = void>\n        static constexpr bool is_square_v = N == M;\n        template\
    \ <size_t X, size_t Y>\n        using MatrixType = ArrayMatrix<T, X, Y, _add,\
    \ _neg, _zero, _mul, _inv, _one>;\n    public:\n        using base_type = std::array<std::array<T,\
    \ M>, N>;\n        using container_type = base_type;\n        using row_type =\
    \ std::array<T, M>;\n\n        using base_type::base_type;\n        ArrayMatrix()\
    \ : ArrayMatrix(_zero()) {}\n        ArrayMatrix(T fill_value) {\n           \
    \ for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = fill_value;\n        }\n        ArrayMatrix(const container_type& c) : base_type{\
    \ c } {}\n        ArrayMatrix(const std::initializer_list<row_type>& c) {\n  \
    \          assert(c.size() == N);\n            size_t i = 0;\n            for\
    \ (const auto& row : c) {\n                for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = row[j];\n                ++i;\n            }\n        }\n\n        static\
    \ ArrayMatrix e0() { return ArrayMatrix(Operator::Add); }\n        static MatrixType<M,\
    \ M> e1() { return MatrixType<M, M>(Operator::Mul); }\n\n        int size() const\
    \ {\n            static_assert(is_square_v<>);\n            return N;\n      \
    \  }\n        std::pair<int, int> shape() const { return { N, M }; }\n       \
    \ int row_size() const { return N; }\n        int col_size() const { return M;\
    \ }\n\n        ArrayMatrix operator+() const { return *this; }\n        ArrayMatrix\
    \ operator-() const {\n            ArrayMatrix A;\n            for (size_t i =\
    \ 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _neg((*this)[i][j]);\n\
    \            return A;\n        }\n        friend ArrayMatrix& operator+=(ArrayMatrix&\
    \ A, const ArrayMatrix& B) {\n            for (size_t i = 0; i < N; ++i) for (size_t\
    \ j = 0; j < M; ++j) A[i][j] = _add(A[i][j], B[i][j]);\n            return A;\n\
    \        }\n        friend ArrayMatrix& operator-=(ArrayMatrix& A, const ArrayMatrix&\
    \ B) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j)\
    \ A[i][j] = _add(A[i][j], _neg(B[i][j]));\n            return A;\n        }\n\
    \        template <size_t K>\n        friend MatrixType<N, K>& operator*=(ArrayMatrix&\
    \ A, const MatrixType<M, K>& B) { return A = A * B; }\n        friend ArrayMatrix&\
    \ operator*=(ArrayMatrix& A, const T& val) {\n            for (size_t i = 0; i\
    \ < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _mul(A[i][j], val);\n   \
    \         return A;\n        }\n        friend ArrayMatrix& operator/=(ArrayMatrix&\
    \ A, const ArrayMatrix& B) { static_assert(is_square_v<>); return A *= *B.inv();\
    \ }\n        friend ArrayMatrix& operator/=(ArrayMatrix& A, const T& val) { return\
    \ A *= _inv(val); }\n\n        friend ArrayMatrix operator+(ArrayMatrix A, const\
    \ ArrayMatrix& B) { A += B; return A; }\n        friend ArrayMatrix operator-(ArrayMatrix\
    \ A, const ArrayMatrix& B) { A -= B; return A; }\n        template <size_t K>\n\
    \        friend MatrixType<N, K> operator*(const ArrayMatrix& A, const MatrixType<M,\
    \ K>& B) {\n            MatrixType<N, K> C;\n            for (size_t i = 0; i\
    \ < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0; k < K; ++k) C[i][k]\
    \ = _add(C[i][k], _mul(A[i][j], B[j][k]));\n            return C;\n        }\n\
    \        friend ArrayMatrix operator*(ArrayMatrix A, const T& val) { A *= val;\
    \ return A; }\n        friend ArrayMatrix operator*(const T& val, ArrayMatrix\
    \ A) { A *= val; return A; }\n        friend std::array<T, N> operator*(const\
    \ ArrayMatrix& A, const std::array<T, M>& x) {\n            std::array<T, N> b;\n\
    \            b.fill(_zero());\n            for (size_t i = 0; i < N; ++i) for\
    \ (size_t j = 0; j < M; ++j) b[i] = _add(b[i], _mul(A[i][j], x[j]));\n       \
    \     return b;\n        }\n        friend ArrayMatrix operator/(ArrayMatrix A,\
    \ const ArrayMatrix& B) { static_assert(is_square_v<>); return A * B.inv(); }\n\
    \        friend ArrayMatrix operator/(ArrayMatrix A, const T& val) { A /= val;\
    \ return A; }\n        friend ArrayMatrix operator/(const T& val, ArrayMatrix\
    \ A) { return A.inv() *= val; }\n\n        ArrayMatrix pow(long long b) const\
    \ {\n            static_assert(is_square_v<>);\n            assert(b >= 0);\n\
    \            ArrayMatrix res(e1()), p(*this);\n            for (; b; b >>= 1)\
    \ {\n                if (b & 1) res *= p;\n                p *= p;\n         \
    \   }\n            return res;\n        }\n\n        std::optional<ArrayMatrix>\
    \ safe_inv() const {\n            static_assert(is_square_v<>);\n            std::array<std::array<T,\
    \ 2 * N>, N> data;\n            for (size_t i = 0; i < N; ++i) {\n           \
    \     for (size_t j = 0; j < N; ++j) {\n                    data[i][j] = (*this)[i][j];\n\
    \                    data[i][N + j] = i == j ? _one() : _zero();\n           \
    \     }\n            }\n            for (size_t i = 0; i < N; ++i) {\n       \
    \         for (size_t k = i; k < N; ++k) if (data[k][i] != _zero()) {\n      \
    \              data[i].swap(data[k]);\n                    T c = _inv(data[i][i]);\n\
    \                    for (size_t j = i; j < 2 * N; ++j) data[i][j] = _mul(c, data[i][j]);\n\
    \                    break;\n                }\n                if (data[i][i]\
    \ == _zero()) return std::nullopt;\n                for (size_t k = 0; k < N;\
    \ ++k) if (k != i and data[k][i] != _zero()) {\n                    T c = data[k][i];\n\
    \                    for (size_t j = i; j < 2 * N; ++j) data[k][j] = _add(data[k][j],\
    \ _neg(_mul(c, data[i][j])));\n                }\n            }\n            ArrayMatrix\
    \ res;\n            for (size_t i = 0; i < N; ++i) std::copy(data[i].begin() +\
    \ N, data[i].begin() + 2 * N, res[i].begin());\n            return res;\n    \
    \    }\n        ArrayMatrix inv() const { return *safe_inv(); }\n        T det()\
    \ const {\n            static_assert(is_square_v<>);\n            ArrayMatrix\
    \ A = *this;\n            bool sgn = false;\n            for (size_t j = 0; j\
    \ < N; ++j) for (size_t i = j + 1; i < N; ++i) if (A[i][j] != _zero()) {\n   \
    \             std::swap(A[j], A[i]);\n                T q = _mul(A[i][j], _inv(A[j][j]));\n\
    \                for (size_t k = j; k < N; ++k) A[i][k] = _add(A[i][k], _neg(_mul(A[j][k],\
    \ q)));\n                sgn = not sgn;\n            }\n            T res = sgn\
    \ ? _neg(_one()) : _one();\n            for (size_t i = 0; i < N; ++i) res = _mul(res,\
    \ A[i][i]);\n            return res;\n        }\n        T det_arbitrary_mod()\
    \ const {\n            static_assert(is_square_v<>);\n            ArrayMatrix\
    \ A = *this;\n            bool sgn = false;\n            for (size_t j = 0; j\
    \ < N; ++j) for (size_t i = j + 1; i < N; ++i) {\n                for (; A[i][j].val();\
    \ sgn = not sgn) {\n                    std::swap(A[j], A[i]);\n             \
    \       T q = A[i][j].val() / A[j][j].val();\n                    for (size_t\
    \ k = j; k < N; ++k) A[i][k] -= A[j][k] * q;\n                }\n            }\n\
    \            T res = sgn ? -1 : +1;\n            for (size_t i = 0; i < N; ++i)\
    \ res *= A[i][i];\n            return res;\n        }\n    private:\n        ArrayMatrix(Operator\
    \ op) : ArrayMatrix(_zero()) {\n            if (op == Operator::Mul) for (size_t\
    \ i = 0; i < N; ++i) (*this)[i][i] = _one();\n        }\n    };\n    template\
    \ <\n        typename T, size_t N,\n        T(*_add)(T, T) = default_operator_noref::add<T>,\
    \ T(*_neg)(T) = default_operator_noref::neg<T>, T(*_zero)() = default_operator_noref::zero<T>,\n\
    \        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>,\
    \ T(*_one)() = default_operator_noref::one<T>\n    >\n    using SquareArrayMatrix\
    \ = ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one>;\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_ARRAY_MATRIX\n#define SUISEN_ARRAY_MATRIX\n\n#include <array>\n\
    #include <cassert>\n#include <optional>\n\n#include \"library/util/default_operator.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T, size_t N, size_t M,\n\
    \        T(*_add)(T, T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>,\n        T(*_mul)(T, T) = default_operator_noref::mul<T>,\
    \ T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)() = default_operator_noref::one<T>\n\
    \    >\n    struct ArrayMatrix : public std::array<std::array<T, M>, N> {\n  \
    \  private:\n        enum Operator { Add, Mul };\n        template <typename DummyType\
    \ = void>\n        static constexpr bool is_square_v = N == M;\n        template\
    \ <size_t X, size_t Y>\n        using MatrixType = ArrayMatrix<T, X, Y, _add,\
    \ _neg, _zero, _mul, _inv, _one>;\n    public:\n        using base_type = std::array<std::array<T,\
    \ M>, N>;\n        using container_type = base_type;\n        using row_type =\
    \ std::array<T, M>;\n\n        using base_type::base_type;\n        ArrayMatrix()\
    \ : ArrayMatrix(_zero()) {}\n        ArrayMatrix(T fill_value) {\n           \
    \ for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = fill_value;\n        }\n        ArrayMatrix(const container_type& c) : base_type{\
    \ c } {}\n        ArrayMatrix(const std::initializer_list<row_type>& c) {\n  \
    \          assert(c.size() == N);\n            size_t i = 0;\n            for\
    \ (const auto& row : c) {\n                for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = row[j];\n                ++i;\n            }\n        }\n\n        static\
    \ ArrayMatrix e0() { return ArrayMatrix(Operator::Add); }\n        static MatrixType<M,\
    \ M> e1() { return MatrixType<M, M>(Operator::Mul); }\n\n        int size() const\
    \ {\n            static_assert(is_square_v<>);\n            return N;\n      \
    \  }\n        std::pair<int, int> shape() const { return { N, M }; }\n       \
    \ int row_size() const { return N; }\n        int col_size() const { return M;\
    \ }\n\n        ArrayMatrix operator+() const { return *this; }\n        ArrayMatrix\
    \ operator-() const {\n            ArrayMatrix A;\n            for (size_t i =\
    \ 0; i < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _neg((*this)[i][j]);\n\
    \            return A;\n        }\n        friend ArrayMatrix& operator+=(ArrayMatrix&\
    \ A, const ArrayMatrix& B) {\n            for (size_t i = 0; i < N; ++i) for (size_t\
    \ j = 0; j < M; ++j) A[i][j] = _add(A[i][j], B[i][j]);\n            return A;\n\
    \        }\n        friend ArrayMatrix& operator-=(ArrayMatrix& A, const ArrayMatrix&\
    \ B) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j)\
    \ A[i][j] = _add(A[i][j], _neg(B[i][j]));\n            return A;\n        }\n\
    \        template <size_t K>\n        friend MatrixType<N, K>& operator*=(ArrayMatrix&\
    \ A, const MatrixType<M, K>& B) { return A = A * B; }\n        friend ArrayMatrix&\
    \ operator*=(ArrayMatrix& A, const T& val) {\n            for (size_t i = 0; i\
    \ < N; ++i) for (size_t j = 0; j < M; ++j) A[i][j] = _mul(A[i][j], val);\n   \
    \         return A;\n        }\n        friend ArrayMatrix& operator/=(ArrayMatrix&\
    \ A, const ArrayMatrix& B) { static_assert(is_square_v<>); return A *= *B.inv();\
    \ }\n        friend ArrayMatrix& operator/=(ArrayMatrix& A, const T& val) { return\
    \ A *= _inv(val); }\n\n        friend ArrayMatrix operator+(ArrayMatrix A, const\
    \ ArrayMatrix& B) { A += B; return A; }\n        friend ArrayMatrix operator-(ArrayMatrix\
    \ A, const ArrayMatrix& B) { A -= B; return A; }\n        template <size_t K>\n\
    \        friend MatrixType<N, K> operator*(const ArrayMatrix& A, const MatrixType<M,\
    \ K>& B) {\n            MatrixType<N, K> C;\n            for (size_t i = 0; i\
    \ < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0; k < K; ++k) C[i][k]\
    \ = _add(C[i][k], _mul(A[i][j], B[j][k]));\n            return C;\n        }\n\
    \        friend ArrayMatrix operator*(ArrayMatrix A, const T& val) { A *= val;\
    \ return A; }\n        friend ArrayMatrix operator*(const T& val, ArrayMatrix\
    \ A) { A *= val; return A; }\n        friend std::array<T, N> operator*(const\
    \ ArrayMatrix& A, const std::array<T, M>& x) {\n            std::array<T, N> b;\n\
    \            b.fill(_zero());\n            for (size_t i = 0; i < N; ++i) for\
    \ (size_t j = 0; j < M; ++j) b[i] = _add(b[i], _mul(A[i][j], x[j]));\n       \
    \     return b;\n        }\n        friend ArrayMatrix operator/(ArrayMatrix A,\
    \ const ArrayMatrix& B) { static_assert(is_square_v<>); return A * B.inv(); }\n\
    \        friend ArrayMatrix operator/(ArrayMatrix A, const T& val) { A /= val;\
    \ return A; }\n        friend ArrayMatrix operator/(const T& val, ArrayMatrix\
    \ A) { return A.inv() *= val; }\n\n        ArrayMatrix pow(long long b) const\
    \ {\n            static_assert(is_square_v<>);\n            assert(b >= 0);\n\
    \            ArrayMatrix res(e1()), p(*this);\n            for (; b; b >>= 1)\
    \ {\n                if (b & 1) res *= p;\n                p *= p;\n         \
    \   }\n            return res;\n        }\n\n        std::optional<ArrayMatrix>\
    \ safe_inv() const {\n            static_assert(is_square_v<>);\n            std::array<std::array<T,\
    \ 2 * N>, N> data;\n            for (size_t i = 0; i < N; ++i) {\n           \
    \     for (size_t j = 0; j < N; ++j) {\n                    data[i][j] = (*this)[i][j];\n\
    \                    data[i][N + j] = i == j ? _one() : _zero();\n           \
    \     }\n            }\n            for (size_t i = 0; i < N; ++i) {\n       \
    \         for (size_t k = i; k < N; ++k) if (data[k][i] != _zero()) {\n      \
    \              data[i].swap(data[k]);\n                    T c = _inv(data[i][i]);\n\
    \                    for (size_t j = i; j < 2 * N; ++j) data[i][j] = _mul(c, data[i][j]);\n\
    \                    break;\n                }\n                if (data[i][i]\
    \ == _zero()) return std::nullopt;\n                for (size_t k = 0; k < N;\
    \ ++k) if (k != i and data[k][i] != _zero()) {\n                    T c = data[k][i];\n\
    \                    for (size_t j = i; j < 2 * N; ++j) data[k][j] = _add(data[k][j],\
    \ _neg(_mul(c, data[i][j])));\n                }\n            }\n            ArrayMatrix\
    \ res;\n            for (size_t i = 0; i < N; ++i) std::copy(data[i].begin() +\
    \ N, data[i].begin() + 2 * N, res[i].begin());\n            return res;\n    \
    \    }\n        ArrayMatrix inv() const { return *safe_inv(); }\n        T det()\
    \ const {\n            static_assert(is_square_v<>);\n            ArrayMatrix\
    \ A = *this;\n            bool sgn = false;\n            for (size_t j = 0; j\
    \ < N; ++j) for (size_t i = j + 1; i < N; ++i) if (A[i][j] != _zero()) {\n   \
    \             std::swap(A[j], A[i]);\n                T q = _mul(A[i][j], _inv(A[j][j]));\n\
    \                for (size_t k = j; k < N; ++k) A[i][k] = _add(A[i][k], _neg(_mul(A[j][k],\
    \ q)));\n                sgn = not sgn;\n            }\n            T res = sgn\
    \ ? _neg(_one()) : _one();\n            for (size_t i = 0; i < N; ++i) res = _mul(res,\
    \ A[i][i]);\n            return res;\n        }\n        T det_arbitrary_mod()\
    \ const {\n            static_assert(is_square_v<>);\n            ArrayMatrix\
    \ A = *this;\n            bool sgn = false;\n            for (size_t j = 0; j\
    \ < N; ++j) for (size_t i = j + 1; i < N; ++i) {\n                for (; A[i][j].val();\
    \ sgn = not sgn) {\n                    std::swap(A[j], A[i]);\n             \
    \       T q = A[i][j].val() / A[j][j].val();\n                    for (size_t\
    \ k = j; k < N; ++k) A[i][k] -= A[j][k] * q;\n                }\n            }\n\
    \            T res = sgn ? -1 : +1;\n            for (size_t i = 0; i < N; ++i)\
    \ res *= A[i][i];\n            return res;\n        }\n    private:\n        ArrayMatrix(Operator\
    \ op) : ArrayMatrix(_zero()) {\n            if (op == Operator::Mul) for (size_t\
    \ i = 0; i < N; ++i) (*this)[i][i] = _one();\n        }\n    };\n    template\
    \ <\n        typename T, size_t N,\n        T(*_add)(T, T) = default_operator_noref::add<T>,\
    \ T(*_neg)(T) = default_operator_noref::neg<T>, T(*_zero)() = default_operator_noref::zero<T>,\n\
    \        T(*_mul)(T, T) = default_operator_noref::mul<T>, T(*_inv)(T) = default_operator_noref::inv<T>,\
    \ T(*_one)() = default_operator_noref::one<T>\n    >\n    using SquareArrayMatrix\
    \ = ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one>;\n} // namespace\
    \ suisen\n\n#endif // SUISEN_ARRAY_MATRIX\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/linear_algebra/array_matrix.hpp
  requiredBy: []
  timestamp: '2022-11-19 17:34:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/linear_algebra/array_matrix/matrix_det.test.cpp
  - test/src/linear_algebra/array_matrix/inverse_matrix.test.cpp
  - test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
  - test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
documentation_of: library/linear_algebra/array_matrix.hpp
layout: document
title: Array Matrix
---
## Array Matrix

行列のサイズがコンパイル時定数として書ける場合は、`std::array` を用いることで定数倍高速化を図ることが出来る (特に、行列のサイズが小さい場合)。
