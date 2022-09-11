---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/array_matrix.hpp
    title: Array Matrix
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod
    links:
    - https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod
  bundledCode: "#line 1 \"test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/linear_algebra/array_matrix.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <optional>\n\n#line 1 \"\
    library/util/default_operator.hpp\"\n\n\n\nnamespace suisen {\n    namespace default_operator\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(const\
    \ T &x, const T &y) -> decltype(x + y) { return x + y; }\n        template <typename\
    \ T>\n        auto sub(const T &x, const T &y) -> decltype(x - y) { return x -\
    \ y; }\n        template <typename T>\n        auto mul(const T &x, const T &y)\
    \ -> decltype(x * y) { return x * y; }\n        template <typename T>\n      \
    \  auto div(const T &x, const T &y) -> decltype(x / y) { return x / y; }\n   \
    \     template <typename T>\n        auto mod(const T &x, const T &y) -> decltype(x\
    \ % y) { return x % y; }\n        template <typename T>\n        auto neg(const\
    \ T &x) -> decltype(-x) { return -x; }\n        template <typename T>\n      \
    \  auto inv(const T &x) -> decltype(one<T>() / x)  { return one<T>() / x; }\n\
    \    } // default_operator\n    namespace default_operator_noref {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(T x, T y) -> decltype(x\
    \ + y) { return x + y; }\n        template <typename T>\n        auto sub(T x,\
    \ T y) -> decltype(x - y) { return x - y; }\n        template <typename T>\n \
    \       auto mul(T x, T y) -> decltype(x * y) { return x * y; }\n        template\
    \ <typename T>\n        auto div(T x, T y) -> decltype(x / y) { return x / y;\
    \ }\n        template <typename T>\n        auto mod(T x, T y) -> decltype(x %\
    \ y) { return x % y; }\n        template <typename T>\n        auto neg(T x) ->\
    \ decltype(-x) { return -x; }\n        template <typename T>\n        auto inv(T\
    \ x) -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    } // namespace suisen\n\n\n#line 9 \"library/linear_algebra/array_matrix.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T, size_t N, size_t M,\n\
    \        T(*_add)(T, T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>,\n        T(*_mul)(T, T) = default_operator_noref::mul<T>,\
    \ T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)()  = default_operator_noref::one<T>\n\
    \    >\n    struct ArrayMatrix : public std::array<std::array<T, M>, N> {\n  \
    \  private:\n        enum Operator { Add, Mul };\n        template <typename DummyType\
    \ = void>\n        static constexpr bool is_square_v = N == M;\n        template\
    \ <size_t X, size_t Y>\n        using MatrixType = ArrayMatrix<T, X, Y, _add,\
    \ _neg, _zero, _mul, _inv, _one>;\n    public:\n        using base_type = std::array<std::array<T,\
    \ M>, N>;\n        using container_type = base_type;\n        using row_type =\
    \ std::array<T, M>;\n\n        using base_type::base_type;\n        ArrayMatrix()\
    \ : ArrayMatrix(_zero()) {}\n        ArrayMatrix(T fill_value) {\n           \
    \ for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = fill_value;\n        }\n        ArrayMatrix(const container_type &c) : base_type{c}\
    \ {}\n        ArrayMatrix(const std::initializer_list<row_type> &c) {\n      \
    \      assert(c.size() == N);\n            size_t i = 0;\n            for (const\
    \ auto &row : c) {\n                for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = row[j];\n                ++i;\n            }\n        }\n\n        static\
    \ ArrayMatrix e0() { return ArrayMatrix(Operator::Add); }\n        static MatrixType<M,\
    \ M> e1() { return MatrixType<M, M>(Operator::Mul); }\n\n        int size() const\
    \ {\n            static_assert(is_square_v<>);\n            return N;\n      \
    \  }\n        std::pair<int, int> shape() const { return { N, M }; }\n       \
    \ int row_size() const { return N; }\n        int col_size() const { return M;\
    \ }\n\n        ArrayMatrix operator+() const { return *this; }\n        ArrayMatrix\
    \ operator-() const {\n            ArrayMatrix res;\n            for (size_t i\
    \ = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _neg((*this)[i][j]);\n\
    \            return res;\n        }\n        ArrayMatrix& operator+=(const ArrayMatrix&\
    \ other) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j <\
    \ M; ++j) (*this)[i][j] = _add((*this)[i][j], other[i][j]);\n            return\
    \ *this;\n        }\n        ArrayMatrix& operator-=(const ArrayMatrix& other)\
    \ {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j)\
    \ (*this)[i][j] = _add((*this)[i][j], _neg(other[i][j]));\n            return\
    \ *this;\n        }\n        template <size_t K>\n        MatrixType<N, K>& operator*=(const\
    \ MatrixType<M, K>& other) { return *this = *this * other; }\n        ArrayMatrix&\
    \ operator*=(const T& val) {\n            for (size_t i = 0; i < N; ++i) for (size_t\
    \ j = 0; j < M; ++j) (*this)[i][j] = _mul((*this)[i][j], val);\n            return\
    \ *this;\n        }\n        ArrayMatrix& operator/=(const T& val) { return *this\
    \ *= _inv(val); }\n        friend ArrayMatrix operator+(ArrayMatrix lhs, const\
    \ ArrayMatrix& rhs) { lhs += rhs; return lhs; }\n        friend ArrayMatrix operator-(ArrayMatrix\
    \ lhs, const ArrayMatrix& rhs) { lhs -= rhs; return lhs; }\n        template <size_t\
    \ K>\n        friend MatrixType<N, K> operator*(const ArrayMatrix& lhs, const\
    \ MatrixType<M, K>& rhs) {\n            MatrixType<N, K> res;\n            for\
    \ (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) for (size_t k = 0;\
    \ k < K; ++k) {\n                res[i][k] = _add(res[i][k], _mul(lhs[i][j], rhs[j][k]));\n\
    \            }\n            return res;\n        }\n        friend ArrayMatrix\
    \ operator*(ArrayMatrix A, const T& val) { A *= val; return A; }\n        friend\
    \ ArrayMatrix operator*(const T& val, ArrayMatrix A) { A *= val; return A; }\n\
    \        friend ArrayMatrix operator/(ArrayMatrix A, const T& val) { A /= val;\
    \ return A; }\n\n        std::array<T, N> operator*(const std::array<T, M>& x)\
    \ const {\n            std::array<T, N> b;\n            b.fill(_zero());\n   \
    \         for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) b[i] =\
    \ _add(b[i], _mul((*this)[i][j], x[j]));\n            return b;\n        }\n\n\
    \        static std::optional<ArrayMatrix> inv(const ArrayMatrix& A) {\n     \
    \       static_assert(is_square_v<>);\n            std::array<std::array<T, 2\
    \ * N>, N> data;\n            for (size_t i = 0; i < N; ++i) {\n             \
    \   for (size_t j = 0; j < N; ++j) {\n                    data[i][j] = A[i][j];\n\
    \                    data[i][N + j] = i == j ? _one() : _zero();\n           \
    \     }\n            }\n            for (size_t i = 0; i < N; ++i) {\n       \
    \         int pivot = -1;\n                for (size_t k = i; k < N; ++k) if (data[k][i]\
    \ != _zero()) {\n                    pivot = k;\n                    break;\n\
    \                }\n                if (pivot < 0) return std::nullopt;\n    \
    \            data[i].swap(data[pivot]);\n                T coef = _inv(data[i][i]);\n\
    \                for (size_t j = i; j < 2 * N; ++j) data[i][j] = _mul(data[i][j],\
    \ coef);\n                for (size_t k = 0; k < N; ++k) if (k != i and data[k][i]\
    \ != _zero()) {\n                    T c = data[k][i];\n                    for\
    \ (size_t j = i; j < 2 * N; ++j) data[k][j] = _add(data[k][j], _neg(_mul(c, data[i][j])));\n\
    \                }\n            }\n            ArrayMatrix res;\n            for\
    \ (size_t i = 0; i < N; ++i) std::copy(data[i].begin() + N, data[i].begin() +\
    \ 2 * N, res[i].begin());\n            return res;\n        }\n        static\
    \ T det(ArrayMatrix A) {\n            static_assert(is_square_v<>);\n        \
    \    bool sgn = false;\n            for (size_t j = 0; j < N; ++j) for (size_t\
    \ i = j + 1; i < N; ++i) if (A[i][j] != _zero()) {\n                std::swap(A[j],\
    \ A[i]);\n                T q = _mul(A[i][j], _inv(A[j][j]));\n              \
    \  for (size_t k = j; k < N; ++k) A[i][k] = _add(A[i][k], _neg(_mul(A[j][k], q)));\n\
    \                sgn = not sgn;\n            }\n            T res = sgn ? _neg(_one())\
    \ : _one();\n            for (size_t i = 0; i < N; ++i) res = _mul(res, A[i][i]);\n\
    \            return res;\n        }\n        static T det_arbitrary_mod(ArrayMatrix\
    \ A) {\n            bool sgn = false;\n            for (size_t j = 0; j < N; ++j)\
    \ for (size_t i = j + 1; i < N; ++i) {\n                for (; A[i][j].val();\
    \ sgn = not sgn) {\n                    std::swap(A[j], A[i]);\n             \
    \       T q = A[i][j].val() / A[j][j].val();\n                    for (size_t\
    \ k = j; k < N; ++k) A[i][k] -= A[j][k] * q;\n                }\n            }\n\
    \            T res = sgn ? -1 : +1;\n            for (size_t i = 0; i < N; ++i)\
    \ res *= A[i][i];\n            return res;\n        }\n        std::optional<ArrayMatrix>\
    \ inv() const { static_assert(is_square_v<>); return inv(*this); }\n        T\
    \ det() const { static_assert(is_square_v<>); return det(*this); }\n        T\
    \ det_arbitrary_mod() const { static_assert(is_square_v<>); return det_arbitrary_mod(*this);\
    \ }\n\n        ArrayMatrix& operator/=(const ArrayMatrix& other) { static_assert(is_square_v<>);\
    \ return *this *= other.inv(); }\n        ArrayMatrix  operator/ (const ArrayMatrix&\
    \ other) const { static_assert(is_square_v<>); return ArrayMatrix(*this) *= *other.inv();\
    \ }\n\n        ArrayMatrix pow(long long b) const {\n            static_assert(is_square_v<>);\n\
    \            assert(b >= 0);\n            ArrayMatrix res(e1()), p(*this);\n \
    \           for (; b; b >>= 1) {\n                if (b & 1) res *= p;\n     \
    \           p *= p;\n            }\n            return res;\n        }\n    private:\n\
    \        ArrayMatrix(Operator op) : ArrayMatrix(_zero()) {\n            if (op\
    \ == Operator::Mul) for (size_t i = 0; i < N; ++i) (*this)[i][i] = _one();\n \
    \       }\n    };\n    template <\n        typename T, size_t N,\n        T(*_add)(T,\
    \ T) = default_operator_noref::add<T>, T(*_neg)(T) = default_operator_noref::neg<T>,\
    \ T(*_zero)() = default_operator_noref::zero<T>,\n        T(*_mul)(T, T) = default_operator_noref::mul<T>,\
    \ T(*_inv)(T) = default_operator_noref::inv<T>, T(*_one)()  = default_operator_noref::one<T>\n\
    \    >\n    using SquareArrayMatrix = ArrayMatrix<T, N, N, _add, _neg, _zero,\
    \ _mul, _inv, _one>;\n} // namespace suisen\n\n\n#line 7 \"test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp\"\
    \n\nusing mint = atcoder::modint;\nusing matrix = suisen::SquareArrayMatrix<mint,\
    \ 500>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    mint::set_mod(m);\n\n    matrix\
    \ A = matrix::e1();\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0;\
    \ j < n; ++j) {\n            int val;\n            std::cin >> val;\n        \
    \    A[i][j] = val;\n        }\n    }\n    std::cout << A.det_arbitrary_mod().val()\
    \ << '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/linear_algebra/array_matrix.hpp\"\
    \n\nusing mint = atcoder::modint;\nusing matrix = suisen::SquareArrayMatrix<mint,\
    \ 500>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    mint::set_mod(m);\n\n    matrix\
    \ A = matrix::e1();\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0;\
    \ j < n; ++j) {\n            int val;\n            std::cin >> val;\n        \
    \    A[i][j] = val;\n        }\n    }\n    std::cout << A.det_arbitrary_mod().val()\
    \ << '\\n';\n    return 0;\n}\n"
  dependsOn:
  - library/linear_algebra/array_matrix.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
  requiredBy: []
  timestamp: '2022-08-07 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
layout: document
redirect_from:
- /verify/test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
- /verify/test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp.html
title: test/src/linear_algebra/array_matrix/matrix_det_arbitrary_mod.test.cpp
---
