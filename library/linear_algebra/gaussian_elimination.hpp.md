---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/gaussian_elimination/system_of_linear_equations.test.cpp
    title: test/src/linear_algebra/gaussian_elimination/system_of_linear_equations.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/linear_algebra/gaussian_elimination.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cmath>\n#include <optional>\n#include <vector>\n\
    \nnamespace suisen {\n    namespace internal::gauss_jordan {\n        template\
    \ <typename T, typename EqZero, std::enable_if_t<std::negation_v<std::is_floating_point<T>>,\
    \ std::nullptr_t> = nullptr>\n        std::pair<size_t, size_t> pivoting(const\
    \ std::vector<std::vector<T>>& Ab, const size_t i, EqZero equals_zero) {\n   \
    \         const size_t n = Ab.size(), m = Ab[0].size() - 1;\n            size_t\
    \ mse = m, pivot = n;\n            for (size_t row = i; row < n; ++row) {\n  \
    \              const auto &v = Ab[row];\n                size_t col = std::find_if_not(v.begin(),\
    \ v.begin() + mse, equals_zero) - v.begin();\n                if (col < mse) mse\
    \ = col, pivot = row;\n            }\n            return { mse, pivot };\n   \
    \     }\n        // Gauss pivoting\n        template <typename T, typename EqZero,\
    \ std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>\n \
    \       std::pair<size_t, size_t> pivoting(const std::vector<std::vector<T>>&\
    \ Ab, const size_t i, EqZero equals_zero) {\n            const size_t n = Ab.size(),\
    \ m = Ab[0].size() - 1;\n            size_t mse = m, pivot = n;\n            T\
    \ max_val = 0;\n            for (size_t row = i; row < n; ++row) {\n         \
    \       const auto &v = Ab[row];\n                if (mse < m and std::abs(v[mse])\
    \ > max_val) pivot = row, max_val = std::abs(v[mse]);\n                size_t\
    \ col = std::find_if_not(v.begin(), v.begin() + mse, equals_zero) - v.begin();\n\
    \                if (col < mse) mse = col, pivot = row, max_val = std::abs(Ab[row][col]);\n\
    \            }\n            return { mse, pivot };\n        }\n\n        template\
    \ <typename T> constexpr T add_fp_f2(T x, T y) { return x ^ y; }\n        template\
    \ <typename T> constexpr T add_inv_fp_f2(T x) { return x; }\n        template\
    \ <typename T> constexpr T mul_fp_f2(T x, T y) { return x & y; }\n        template\
    \ <typename T> constexpr T mul_inv_fp_f2(T x) { return x; }\n\n        template\
    \ <typename T> constexpr T add_fp_arithmetic(T x, T y) { return x + y; }\n   \
    \     template <typename T> constexpr T add_inv_fp_arithmetic(T x) { return 0\
    \ - x; }\n        template <typename T> constexpr T mul_fp_arithmetic(T x, T y)\
    \ { return x * y; }\n        template <typename T> constexpr T mul_inv_fp_arithmetic(T\
    \ x) { return 1 / x; }\n    }\n\n    template <typename T, T(*add_fp)(T, T), T(*add_inv_fp)(T),\
    \ T(*mul_fp)(T, T), T(*mul_inv_fp)(T)>\n    struct GaussianElimination {\n   \
    \     GaussianElimination(std::vector<std::vector<T>> A, const std::vector<T>&\
    \ b, const T &zero = T(0), const T &one = T(1)) {\n            size_t n = A.size();\n\
    \            for (size_t i = 0; i < n; ++i) A[i].push_back(b[i]);\n          \
    \  solve(zero, one, A);\n        }\n        bool has_solution() const { return\
    \ not _empty; }\n        bool has_unique_solution() const { return not _empty\
    \ and _basis.size() == 0; }\n        bool has_multiple_solutions() const { return\
    \ _basis.size() > 0; }\n        const std::optional<std::vector<T>> get_solution()\
    \ const { return _empty ? std::nullopt : std::make_optional(_x0); }\n        const\
    \ std::vector<std::vector<T>>& get_basis() const { return _basis; }\n        int\
    \ dimension() const { return _empty ? -1 : _basis.size(); }\n    private:\n  \
    \      std::vector<T> _x0;\n        std::vector<std::vector<T>> _basis;\n    \
    \    bool _empty = false;\n\n        void solve(const T &zero, const T &one, std::vector<std::vector<T>>&\
    \ Ab) {\n            using namespace internal::gauss_jordan;\n            auto\
    \ equals_zero = [&](const T& v) {\n                if constexpr (std::is_floating_point_v<T>)\
    \ return std::abs(v) < 1e-9;\n                else return v == zero;\n       \
    \     };\n            const size_t n = Ab.size(), m = Ab[0].size() - 1;\n    \
    \        for (size_t i = 0; i < n; ++i) {\n                auto [mse, pivot] =\
    \ pivoting(Ab, i, equals_zero);\n                if (pivot == n) break;\n    \
    \            Ab[i].swap(Ab[pivot]);\n                T mse_val_inv = mul_inv_fp(Ab[i][mse]);\n\
    \                for (size_t row = i + 1; row < n; ++row) if (not equals_zero(Ab[row][mse]))\
    \ {\n                    T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n\
    \                    for (size_t col = mse; col <= m; ++col) Ab[row][col] = add_fp(Ab[row][col],\
    \ mul_fp(coef, Ab[i][col]));\n                }\n            }\n            size_t\
    \ basis_num = m;\n            std::vector<char> down(m, false);\n            _x0.assign(m,\
    \ zero);\n            for (size_t i = n; i-- > 0;) {\n                size_t mse\
    \ = m + 1;\n                for (size_t col = 0; col <= m; ++col) if (not equals_zero(Ab[i][col]))\
    \ {\n                    mse = col;\n                    break;\n            \
    \    }\n                if (mse < m) {\n                    T mse_val_inv = mul_inv_fp(Ab[i][mse]);\n\
    \                    for (size_t row = 0; row < i; ++row) if (not equals_zero(Ab[row][mse]))\
    \ {\n                        T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n\
    \                        for (size_t col = mse; col <= m; ++col) Ab[row][col]\
    \ = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));\n                    }\n \
    \                   for (size_t col = mse; col <= m; ++col) Ab[i][col] = mul_fp(Ab[i][col],\
    \ mse_val_inv);\n                    _x0[mse] = Ab[i][m];\n                  \
    \  down[mse] = true;\n                    --basis_num;\n                } else\
    \ if (mse == m) {\n                    _empty = true;\n                    return;\n\
    \                }\n            }\n            _basis.assign(basis_num, std::vector<T>(m));\n\
    \            int basis_id = 0;\n            for (size_t j = 0; j < m; ++j) if\
    \ (not down[j]) {\n                for (size_t j2 = 0, i = 0; j2 < m; ++j2) _basis[basis_id][j2]\
    \ = down[j2] ? Ab[i++][j] : zero;\n                _basis[basis_id++][j] = add_inv_fp(one);\n\
    \            }\n        }\n    };\n\n    template <typename T>\n    using GaussianEliminationF2\
    \ = GaussianElimination<\n        T,\n        internal::gauss_jordan::add_fp_f2,\
    \ internal::gauss_jordan::add_inv_fp_f2,\n        internal::gauss_jordan::mul_fp_f2,\
    \ internal::gauss_jordan::mul_inv_fp_f2>;\n    template <typename T>\n    using\
    \ GaussianEliminationArithmetic = GaussianElimination<\n        T,\n        internal::gauss_jordan::add_fp_arithmetic,\
    \ internal::gauss_jordan::add_inv_fp_arithmetic,\n        internal::gauss_jordan::mul_fp_arithmetic,\
    \ internal::gauss_jordan::mul_inv_fp_arithmetic>;\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_GAUSSIAN_ELIMINATION\n#define SUISEN_GAUSSIAN_ELIMINATION\n\
    \n#include <algorithm>\n#include <cmath>\n#include <optional>\n#include <vector>\n\
    \nnamespace suisen {\n    namespace internal::gauss_jordan {\n        template\
    \ <typename T, typename EqZero, std::enable_if_t<std::negation_v<std::is_floating_point<T>>,\
    \ std::nullptr_t> = nullptr>\n        std::pair<size_t, size_t> pivoting(const\
    \ std::vector<std::vector<T>>& Ab, const size_t i, EqZero equals_zero) {\n   \
    \         const size_t n = Ab.size(), m = Ab[0].size() - 1;\n            size_t\
    \ mse = m, pivot = n;\n            for (size_t row = i; row < n; ++row) {\n  \
    \              const auto &v = Ab[row];\n                size_t col = std::find_if_not(v.begin(),\
    \ v.begin() + mse, equals_zero) - v.begin();\n                if (col < mse) mse\
    \ = col, pivot = row;\n            }\n            return { mse, pivot };\n   \
    \     }\n        // Gauss pivoting\n        template <typename T, typename EqZero,\
    \ std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>\n \
    \       std::pair<size_t, size_t> pivoting(const std::vector<std::vector<T>>&\
    \ Ab, const size_t i, EqZero equals_zero) {\n            const size_t n = Ab.size(),\
    \ m = Ab[0].size() - 1;\n            size_t mse = m, pivot = n;\n            T\
    \ max_val = 0;\n            for (size_t row = i; row < n; ++row) {\n         \
    \       const auto &v = Ab[row];\n                if (mse < m and std::abs(v[mse])\
    \ > max_val) pivot = row, max_val = std::abs(v[mse]);\n                size_t\
    \ col = std::find_if_not(v.begin(), v.begin() + mse, equals_zero) - v.begin();\n\
    \                if (col < mse) mse = col, pivot = row, max_val = std::abs(Ab[row][col]);\n\
    \            }\n            return { mse, pivot };\n        }\n\n        template\
    \ <typename T> constexpr T add_fp_f2(T x, T y) { return x ^ y; }\n        template\
    \ <typename T> constexpr T add_inv_fp_f2(T x) { return x; }\n        template\
    \ <typename T> constexpr T mul_fp_f2(T x, T y) { return x & y; }\n        template\
    \ <typename T> constexpr T mul_inv_fp_f2(T x) { return x; }\n\n        template\
    \ <typename T> constexpr T add_fp_arithmetic(T x, T y) { return x + y; }\n   \
    \     template <typename T> constexpr T add_inv_fp_arithmetic(T x) { return 0\
    \ - x; }\n        template <typename T> constexpr T mul_fp_arithmetic(T x, T y)\
    \ { return x * y; }\n        template <typename T> constexpr T mul_inv_fp_arithmetic(T\
    \ x) { return 1 / x; }\n    }\n\n    template <typename T, T(*add_fp)(T, T), T(*add_inv_fp)(T),\
    \ T(*mul_fp)(T, T), T(*mul_inv_fp)(T)>\n    struct GaussianElimination {\n   \
    \     GaussianElimination(std::vector<std::vector<T>> A, const std::vector<T>&\
    \ b, const T &zero = T(0), const T &one = T(1)) {\n            size_t n = A.size();\n\
    \            for (size_t i = 0; i < n; ++i) A[i].push_back(b[i]);\n          \
    \  solve(zero, one, A);\n        }\n        bool has_solution() const { return\
    \ not _empty; }\n        bool has_unique_solution() const { return not _empty\
    \ and _basis.size() == 0; }\n        bool has_multiple_solutions() const { return\
    \ _basis.size() > 0; }\n        const std::optional<std::vector<T>> get_solution()\
    \ const { return _empty ? std::nullopt : std::make_optional(_x0); }\n        const\
    \ std::vector<std::vector<T>>& get_basis() const { return _basis; }\n        int\
    \ dimension() const { return _empty ? -1 : _basis.size(); }\n    private:\n  \
    \      std::vector<T> _x0;\n        std::vector<std::vector<T>> _basis;\n    \
    \    bool _empty = false;\n\n        void solve(const T &zero, const T &one, std::vector<std::vector<T>>&\
    \ Ab) {\n            using namespace internal::gauss_jordan;\n            auto\
    \ equals_zero = [&](const T& v) {\n                if constexpr (std::is_floating_point_v<T>)\
    \ return std::abs(v) < 1e-9;\n                else return v == zero;\n       \
    \     };\n            const size_t n = Ab.size(), m = Ab[0].size() - 1;\n    \
    \        for (size_t i = 0; i < n; ++i) {\n                auto [mse, pivot] =\
    \ pivoting(Ab, i, equals_zero);\n                if (pivot == n) break;\n    \
    \            Ab[i].swap(Ab[pivot]);\n                T mse_val_inv = mul_inv_fp(Ab[i][mse]);\n\
    \                for (size_t row = i + 1; row < n; ++row) if (not equals_zero(Ab[row][mse]))\
    \ {\n                    T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n\
    \                    for (size_t col = mse; col <= m; ++col) Ab[row][col] = add_fp(Ab[row][col],\
    \ mul_fp(coef, Ab[i][col]));\n                }\n            }\n            size_t\
    \ basis_num = m;\n            std::vector<char> down(m, false);\n            _x0.assign(m,\
    \ zero);\n            for (size_t i = n; i-- > 0;) {\n                size_t mse\
    \ = m + 1;\n                for (size_t col = 0; col <= m; ++col) if (not equals_zero(Ab[i][col]))\
    \ {\n                    mse = col;\n                    break;\n            \
    \    }\n                if (mse < m) {\n                    T mse_val_inv = mul_inv_fp(Ab[i][mse]);\n\
    \                    for (size_t row = 0; row < i; ++row) if (not equals_zero(Ab[row][mse]))\
    \ {\n                        T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n\
    \                        for (size_t col = mse; col <= m; ++col) Ab[row][col]\
    \ = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));\n                    }\n \
    \                   for (size_t col = mse; col <= m; ++col) Ab[i][col] = mul_fp(Ab[i][col],\
    \ mse_val_inv);\n                    _x0[mse] = Ab[i][m];\n                  \
    \  down[mse] = true;\n                    --basis_num;\n                } else\
    \ if (mse == m) {\n                    _empty = true;\n                    return;\n\
    \                }\n            }\n            _basis.assign(basis_num, std::vector<T>(m));\n\
    \            int basis_id = 0;\n            for (size_t j = 0; j < m; ++j) if\
    \ (not down[j]) {\n                for (size_t j2 = 0, i = 0; j2 < m; ++j2) _basis[basis_id][j2]\
    \ = down[j2] ? Ab[i++][j] : zero;\n                _basis[basis_id++][j] = add_inv_fp(one);\n\
    \            }\n        }\n    };\n\n    template <typename T>\n    using GaussianEliminationF2\
    \ = GaussianElimination<\n        T,\n        internal::gauss_jordan::add_fp_f2,\
    \ internal::gauss_jordan::add_inv_fp_f2,\n        internal::gauss_jordan::mul_fp_f2,\
    \ internal::gauss_jordan::mul_inv_fp_f2>;\n    template <typename T>\n    using\
    \ GaussianEliminationArithmetic = GaussianElimination<\n        T,\n        internal::gauss_jordan::add_fp_arithmetic,\
    \ internal::gauss_jordan::add_inv_fp_arithmetic,\n        internal::gauss_jordan::mul_fp_arithmetic,\
    \ internal::gauss_jordan::mul_inv_fp_arithmetic>;\n} // namespace suisen\n\n#endif\
    \ // SUISEN_GAUSSIAN_ELIMINATION"
  dependsOn: []
  isVerificationFile: false
  path: library/linear_algebra/gaussian_elimination.hpp
  requiredBy: []
  timestamp: '2022-05-14 02:45:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/linear_algebra/gaussian_elimination/system_of_linear_equations.test.cpp
documentation_of: library/linear_algebra/gaussian_elimination.hpp
layout: document
title: Gaussian Elimination
---
## Gaussian Elimination