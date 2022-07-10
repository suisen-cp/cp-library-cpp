---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/linear_algebra/array_matrix.hpp
    title: Array Matrix
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc258/tasks/abc258_Ex
    links:
    - https://atcoder.jp/contests/abc258/tasks/abc258_Ex
  bundledCode: "#line 1 \"test/src/linear_algebra/array_matrix/abc258_ex.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_Ex\"\n\n#include\
    \ <iostream>\n#include <vector>\n#include <atcoder/modint>\n\n#line 1 \"library/linear_algebra/array_matrix.hpp\"\
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
    \n\nnamespace suisen {\n    template <\n        typename T,\n        size_t N,\n\
    \        size_t M,\n        T(*_add)(T, T) = default_operator_noref::add<T>,\n\
    \        T(*_neg)(T) = default_operator_noref::neg<T>,\n        T(*_zero)() =\
    \ default_operator_noref::zero<T>,\n        T(*_mul)(T, T) = default_operator_noref::mul<T>,\n\
    \        T(*_inv)(T) = default_operator_noref::inv<T>,\n        T(*_one)()  =\
    \ default_operator_noref::one<T>\n    >\n    struct ArrayMatrix : public std::array<std::array<T,\
    \ M>, N> {\n#define MatrixType(N, M) ArrayMatrix<T, N, M, _add, _neg, _zero, _mul,\
    \ _inv, _one>\n        using base_type = std::array<std::array<T, M>, N>;\n  \
    \      using container_type = base_type;\n        using row_type = std::array<T,\
    \ M>;\n\n        using base_type::base_type;\n        constexpr ArrayMatrix()\
    \ : ArrayMatrix(_zero()) {}\n        constexpr ArrayMatrix(T fill_value) {\n \
    \           for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) (*this)[i][j]\
    \ = fill_value;\n        }\n        constexpr ArrayMatrix(const container_type\
    \ &c) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M;\
    \ ++j) (*this)[i][j] = c[i][j];\n        }\n\n        constexpr std::pair<int,\
    \ int> shape() const {\n            return { N, M };\n        }\n        constexpr\
    \ int row_size() const {\n            return N;\n        }\n        constexpr\
    \ int col_size() const {\n            return M;\n        }\n\n        constexpr\
    \ MatrixType(N, M) operator+() {\n            return *this;\n        }\n     \
    \   constexpr MatrixType(N, M) operator-() {\n            ArrayMatrix res;\n \
    \           for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j]\
    \ = _add(res[i][j], _neg((*this)[i][j]));\n            return res;\n        }\n\
    \        constexpr MatrixType(N, M)& operator+=(const MatrixType(N, M)& other)\
    \ {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j)\
    \ (*this)[i][j] = _add((*this)[i][j], other[i][j]);\n            return *this;\n\
    \        }\n        constexpr MatrixType(N, M)& operator-=(const MatrixType(N,\
    \ M)& other) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0;\
    \ j < M; ++j) (*this)[i][j] = _add((*this)[i][j], _neg(other[i][j]));\n      \
    \      return *this;\n        }\n        template <size_t K>\n        constexpr\
    \ MatrixType(N, M)& operator*=(const MatrixType(M, K)& other) {\n            return\
    \ *this = *this * other;\n        }\n        constexpr MatrixType(N, M)& operator*=(const\
    \ T& val) {\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j <\
    \ M; ++j) (*this)[i][j] = _mul((*this)[i][j], val);\n            return *this;\n\
    \        }\n        constexpr MatrixType(N, M)& operator/=(const T& val) {\n \
    \           return *this *= _inv(val);\n        }\n        constexpr friend MatrixType(N,\
    \ M) operator+(const MatrixType(N, M)& lhs, const MatrixType(N, M)& rhs) {\n \
    \           return MatrixType(N, M)(lhs) += rhs;\n        }\n        constexpr\
    \ friend MatrixType(N, M) operator-(const MatrixType(N, M)& lhs, const MatrixType(N,\
    \ M)& rhs) {\n            return MatrixType(N, M)(lhs) -= rhs;\n        }\n  \
    \      template <size_t K>\n        constexpr friend MatrixType(N, K) operator*(const\
    \ MatrixType(N, M)& lhs, const MatrixType(M, K)& rhs) {\n            MatrixType(N,\
    \ K) res;\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M;\
    \ ++j) for (size_t k = 0; k < K; ++k) {\n                res[i][k] = _add(res[i][k],\
    \ _mul(lhs[i][j], rhs[j][k]));\n            }\n            return res;\n     \
    \   }\n        constexpr friend MatrixType(N, M) operator*(const MatrixType(N,\
    \ M)& A, const T& val) {\n            MatrixType(N, M) res;\n            for (size_t\
    \ i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) res[i][j] = _mul(A[i][j],\
    \ val);\n            return res;\n        }\n        constexpr friend MatrixType(N,\
    \ M) operator*(const T& val, const MatrixType(N, M)& A) {\n            MatrixType(N,\
    \ M) res;\n            for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M;\
    \ ++j) res[i][j] = _mul(val, A[i][j]);\n            return res;\n        }\n \
    \       constexpr friend MatrixType(N, M) operator/(const MatrixType(N, M)& A,\
    \ const T& val) {\n            return MatrixType(N, M)(A) /= val;\n        }\n\
    \n        constexpr std::array<T, N> operator*(const std::array<T, M>& x) const\
    \ {\n            std::array<T, N> b;\n            b.fill(_zero());\n         \
    \   for (size_t i = 0; i < N; ++i) for (size_t j = 0; j < M; ++j) b[i] = _add(b[i],\
    \ _mul((*this)[i][j], x[j]));\n            return b;\n        }\n#undef MatrixType\n\
    \    };\n\n    template <\n        typename T,\n        size_t N,\n        T(*_add)(T,\
    \ T) = default_operator_noref::add<T>,\n        T(*_neg)(T) = default_operator_noref::neg<T>,\n\
    \        T(*_zero)() = default_operator_noref::zero<T>,\n        T(*_mul)(T, T)\
    \ = default_operator_noref::mul<T>,\n        T(*_inv)(T) = default_operator_noref::inv<T>,\n\
    \        T(*_one)()  = default_operator_noref::one<T>\n    >\n    class SquareArrayMatrix\
    \ : public ArrayMatrix<T, N, N, _add, _neg, _zero, _mul, _inv, _one> {\n    private:\n\
    \        enum Operator { Add, Mul };\n    public:\n#define MatrixType(N) SquareArrayMatrix<T,\
    \ N, _add, _neg, _zero, _mul, _inv, _one>\n        using base_type = ArrayMatrix<T,\
    \ N, N, _add, _neg, _zero, _mul, _inv, _one>;\n        using container_type =\
    \ typename base_type::container_type;\n        using row_type = typename base_type::row_type;\n\
    \n        using base_type::base_type;\n\n        static SquareArrayMatrix e0()\
    \ { return SquareArrayMatrix(Operator::Add); }\n        static SquareArrayMatrix\
    \ e1() { return SquareArrayMatrix(Operator::Mul); }\n\n        static constexpr\
    \ std::optional<SquareArrayMatrix> inv(const SquareArrayMatrix& A) {\n       \
    \     std::array<std::array<T, 2 * N>, N> data;\n            for (size_t i = 0;\
    \ i < N; ++i) {\n                for (size_t j = 0; j < N; ++j) {\n          \
    \          data[i][j] = A[i][j];\n                    data[i][N + j] = i == j\
    \ ? _one() : _zero();\n                }\n            }\n            for (size_t\
    \ i = 0; i < N; ++i) {\n                int pivot = -1;\n                for (size_t\
    \ k = i; k < N; ++k) if (data[k][i] != _zero()) {\n                    pivot =\
    \ k;\n                    break;\n                }\n                if (pivot\
    \ < 0) return std::nullopt;\n                data[i].swap(data[pivot]);\n    \
    \            T coef = _inv(data[i][i]);\n                for (size_t j = i; j\
    \ < 2 * N; ++j) data[i][j] = _mul(data[i][j], coef);\n                for (size_t\
    \ k = 0; k < N; ++k) if (k != i and data[k][i] != _zero()) {\n               \
    \     T c = data[k][i];\n                    for (size_t j = i; j < 2 * N; ++j)\
    \ data[k][j] = _add(data[k][j], _neg(_mul(c, data[i][j])));\n                }\n\
    \            }\n            SquareArrayMatrix res;\n            for (size_t i\
    \ = 0; i < N; ++i) std::copy(data[i].begin(), data[i].begin() + N, res[i].begin());\n\
    \            return res;\n        }\n        static constexpr T det(SquareArrayMatrix&&\
    \ A) {\n            T det_inv = _one();\n            for (size_t i = 0; i < N;\
    \ ++i) {\n                int pivot = -1;\n                for (size_t k = i;\
    \ k < N; ++k) if (A[k][i] != _zero()) {\n                    pivot = k;\n    \
    \                break;\n                }\n                if (pivot < 0) return\
    \ _zero();\n                A[i].swap(A[pivot]);\n                if (pivot !=\
    \ i) det_inv = _mul(det_inv, _neg(_one()));\n                T coef = _inv(A[i][i]);\n\
    \                for (size_t j = i; j < N; ++j) A[i][j] = _mul(A[i][j], coef);\n\
    \                det_inv = _mul(det_inv, coef);\n                for (size_t k\
    \ = i + 1; k < N; ++k) if (A[k][i] != _zero()) {\n                    T c = A[k][i];\n\
    \                    for (size_t j = i; j < N; ++j) A[k][j] = _add(A[k][j], _neg(_mul(c,\
    \ A[i][j])));\n                }\n            }\n            return _inv(det_inv);\n\
    \        }\n        static constexpr T det(const SquareArrayMatrix& A) {\n   \
    \         return det(SquareArrayMatrix(A));\n        }\n        constexpr SquareArrayMatrix\
    \ inv() const {\n            return *inv(*this);\n        }\n        constexpr\
    \ T det() const {\n            return det(*this);\n        }\n\n        constexpr\
    \ friend SquareArrayMatrix operator+(const SquareArrayMatrix& A, const SquareArrayMatrix&\
    \ B) {\n            auto res = *static_cast<base_type const*>(&A) + *static_cast<base_type\
    \ const*>(&B);\n            return *static_cast<SquareArrayMatrix*>(&res);\n \
    \       }\n        constexpr SquareArrayMatrix& operator+=(const SquareArrayMatrix&\
    \ B) {\n            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this)\
    \ += *static_cast<base_type const*>(&B)));\n        }\n        constexpr friend\
    \ SquareArrayMatrix operator-(const SquareArrayMatrix& A, const SquareArrayMatrix&\
    \ B) {\n            auto res = *static_cast<base_type const*>(&A) - *static_cast<base_type\
    \ const*>(&B);\n            return *static_cast<SquareArrayMatrix*>(&res);\n \
    \       }\n        constexpr SquareArrayMatrix& operator-=(const SquareArrayMatrix&\
    \ B) {\n            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this)\
    \ -= *static_cast<base_type const*>(&B)));\n        }\n        constexpr friend\
    \ SquareArrayMatrix operator*(const SquareArrayMatrix& A, const SquareArrayMatrix&\
    \ B) {\n            auto res = *static_cast<base_type const*>(&A) * *static_cast<base_type\
    \ const*>(&B);\n            return *static_cast<SquareArrayMatrix*>(&res);\n \
    \       }\n        constexpr SquareArrayMatrix& operator*=(const SquareArrayMatrix&\
    \ B) {\n            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this)\
    \ *= *static_cast<base_type const*>(&B)));\n        }\n        constexpr friend\
    \ SquareArrayMatrix operator*(const SquareArrayMatrix& A, const T& x) {\n    \
    \        auto res = *static_cast<base_type const*>(&A) * x;\n            return\
    \ *static_cast<SquareArrayMatrix*>(&res);\n        }\n        constexpr friend\
    \ SquareArrayMatrix operator*(const T& x, const SquareArrayMatrix& A) {\n    \
    \        auto res = x * *static_cast<base_type const*>(&A);\n            return\
    \ *static_cast<SquareArrayMatrix*>(&res);\n        }\n        constexpr SquareArrayMatrix&\
    \ operator*=(const T& x) {\n            return *static_cast<SquareArrayMatrix*>(&(*static_cast<base_type*>(this)\
    \ *= x));\n        }\n        constexpr SquareArrayMatrix& operator/=(const SquareArrayMatrix&\
    \ other) { return *this *= other.inv(); }\n        constexpr SquareArrayMatrix\
    \  operator/ (const SquareArrayMatrix& other) const { return SquareArrayMatrix(*this)\
    \ *= other.inv(); }\n\n        constexpr SquareArrayMatrix pow(long long b) const\
    \ {\n            assert(b >= 0);\n            SquareArrayMatrix res(e1()), p(*this);\n\
    \            for (; b; b >>= 1) {\n                if (b & 1) res *= p;\n    \
    \            p *= p;\n            }\n            return res;\n        }\n    private:\n\
    \        SquareArrayMatrix(Operator op) : base_type() {\n            if (op ==\
    \ Operator::Mul) for (size_t i = 0; i < N; ++i) (*this)[i][i] = _one();\n    \
    \    }\n#undef MatrixType\n    };\n} // namespace suisen\n\n\n#line 8 \"test/src/linear_algebra/array_matrix/abc258_ex.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\nusing matrix = suisen::SquareArrayMatrix<mint,\
    \ 4>;\n \nmatrix T { {\n    0, 0, 1, 0,\n    1, 0, 0, 0,\n    0, 0, 1, 1,\n  \
    \  0, 0, 1, 0\n} };\nmatrix U { { \n    0, 0, 0, 0,\n    1, 0, 0, 0,\n    0, 0,\
    \ 0, 1,\n    0, 0, 1, 0\n} };\n \nint main() {\n    int n;\n    long long s;\n\
    \    std::cin >> n >> s;\n    \n    std::vector<long long> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n    a.push_back(s);\n \n    std::array<mint, 4> x {\
    \ 1, 0, 1, 0 };\n    long long p = 0;\n    for (long long t : a) {\n        x\
    \ = (t == s ? T : U) * (T.pow(t - 1 - p) * x);\n        p = t;\n    }\n    std::cout\
    \ << x[0].val() << std::endl;\n \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_Ex\"\n\n\
    #include <iostream>\n#include <vector>\n#include <atcoder/modint>\n\n#include\
    \ \"library/linear_algebra/array_matrix.hpp\"\n\nusing mint = atcoder::modint998244353;\n\
    using matrix = suisen::SquareArrayMatrix<mint, 4>;\n \nmatrix T { {\n    0, 0,\
    \ 1, 0,\n    1, 0, 0, 0,\n    0, 0, 1, 1,\n    0, 0, 1, 0\n} };\nmatrix U { {\
    \ \n    0, 0, 0, 0,\n    1, 0, 0, 0,\n    0, 0, 0, 1,\n    0, 0, 1, 0\n} };\n\
    \ \nint main() {\n    int n;\n    long long s;\n    std::cin >> n >> s;\n    \n\
    \    std::vector<long long> a(n);\n    for (auto &e : a) std::cin >> e;\n    a.push_back(s);\n\
    \ \n    std::array<mint, 4> x { 1, 0, 1, 0 };\n    long long p = 0;\n    for (long\
    \ long t : a) {\n        x = (t == s ? T : U) * (T.pow(t - 1 - p) * x);\n    \
    \    p = t;\n    }\n    std::cout << x[0].val() << std::endl;\n \n    return 0;\n\
    }"
  dependsOn:
  - library/linear_algebra/array_matrix.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 15:07:59+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
layout: document
redirect_from:
- /verify/test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
- /verify/test/src/linear_algebra/array_matrix/abc258_ex.test.cpp.html
title: test/src/linear_algebra/array_matrix/abc258_ex.test.cpp
---
