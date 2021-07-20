---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/gaussian_elimination.hpp
    title: library/math/gaussian_elimination.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/system_of_linear_equations
    links:
    - https://judge.yosupo.jp/problem/system_of_linear_equations
  bundledCode: "#line 1 \"test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#line 1 \"library/math/gaussian_elimination.hpp\"\
    \n\n\n\n#include <cmath>\n#include <optional>\n#include <vector>\n\nnamespace\
    \ suisen {\nnamespace internal {\n    namespace gauss_jordan {\n        template\
    \ <typename T>\n        std::pair<unsigned int, unsigned int> pivoting(const std::vector<std::vector<T>>\
    \ &Ab, const T &zero, const unsigned int i) {\n            const unsigned int\
    \ n = Ab.size(), m = Ab[0].size() - 1;\n            unsigned int mse = m, pivot\
    \ = n;\n            for (unsigned int row = i; row < n; ++row) {\n           \
    \     for (unsigned int col = 0; col < mse; ++col) {\n                    if (Ab[row][col]\
    \ != zero) {\n                        mse = col, pivot = row;\n              \
    \          break;\n                    }\n                }\n            }\n \
    \           return {mse, pivot};\n        }\n        // Gauss pivoting\n     \
    \   template <>\n        std::pair<unsigned int, unsigned int> pivoting<long double>(const\
    \ std::vector<std::vector<long double>> &Ab, const long double &zero, const unsigned\
    \ int i) {\n            const unsigned int n = Ab.size(), m = Ab[0].size() - 1;\n\
    \            unsigned int mse = m, pivot = n;\n            long double max_val\
    \ = 0;\n            for (unsigned int row = i; row < n; ++row) {\n           \
    \     if (mse < m and std::abs(Ab[row][mse]) > max_val) {\n                  \
    \  pivot = row;\n                    max_val = std::abs(Ab[row][mse]);\n     \
    \           }\n                for (unsigned int col = 0; col < mse; ++col) {\n\
    \                    if (Ab[row][col] != zero) {\n                        mse\
    \ = col, pivot = row, max_val = std::abs(Ab[row][col]);\n                    \
    \    break;\n                    }\n                }\n            }\n       \
    \     return {mse, pivot};\n        }\n\n        template <typename T> constexpr\
    \ T add_fp_f2(T x, T y) { return x ^ y; }\n        template <typename T> constexpr\
    \ T add_inv_fp_f2(T x)  { return x; }\n        template <typename T> constexpr\
    \ T mul_fp_f2(T x, T y) { return x & y; }\n        template <typename T> constexpr\
    \ T mul_inv_fp_f2(T x)  { return x; }\n\n        template <typename T> constexpr\
    \ T add_fp_arithmetic(T x, T y) { return x + y; }\n        template <typename\
    \ T> constexpr T add_inv_fp_arithmetic(T x)  { return 0 - x; }\n        template\
    \ <typename T> constexpr T mul_fp_arithmetic(T x, T y) { return x * y; }\n   \
    \     template <typename T> constexpr T mul_inv_fp_arithmetic(T x)  { return 1\
    \ / x; }\n    }\n}\n\ntemplate <typename T, T(*add_fp)(T, T), T(*add_inv_fp)(T),\
    \ T(*mul_fp)(T, T), T(*mul_inv_fp)(T)>\nclass GaussianElimination {\n    public:\n\
    \        GaussianElimination(std::vector<std::vector<T>> &A, std::vector<T> &b,\
    \ const T zero, const T one) {\n            unsigned int n = A.size();\n     \
    \       for (unsigned int i = 0; i < n; ++i) A[i].push_back(b[i]);\n         \
    \   solve(zero, one, A);\n        }\n        GaussianElimination(std::vector<std::vector<T>>\
    \ &A, std::vector<T> &b) {\n            unsigned int n = A.size();\n         \
    \   for (unsigned int i = 0; i < n; ++i) A[i].push_back(b[i]);\n            solve(T(0),\
    \ T(1), A);\n        }\n        bool has_solution() const { return not _empty;\
    \ }\n        bool has_unique_solution() const { return not _empty and _basis.size()\
    \ == 0; }\n        bool has_multiple_solutions() const { return _basis.size()\
    \ > 0; }\n        const std::optional<std::vector<T>> get_solution() const {\n\
    \            return _empty ? std::nullopt : std::make_optional(_x0);\n       \
    \ }\n        const std::vector<std::vector<T>>& get_basis() const {\n        \
    \    return _basis;\n        }\n        int dimension() const {\n            return\
    \ _empty ? -1 : _basis.size();\n        }\n    private:\n        std::vector<T>\
    \ _x0;\n        std::vector<std::vector<T>> _basis;\n        bool _empty = false;\n\
    \n        void solve(const T zero, const T one, std::vector<std::vector<T>> &Ab)\
    \ {\n            const unsigned int n = Ab.size(), m = Ab[0].size() - 1;\n   \
    \         for (unsigned int i = 0; i < n; ++i) {\n                auto [mse, pivot]\
    \ = internal::gauss_jordan::pivoting(Ab, zero, i);\n                if (pivot\
    \ == n) break;\n                Ab[i].swap(Ab[pivot]);\n                T mse_val_inv\
    \ = mul_inv_fp(Ab[i][mse]);\n                for (unsigned int row = i + 1; row\
    \ < n; ++row) {\n                    if (Ab[row][mse] != zero) {\n           \
    \             T coef = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n      \
    \                  for (unsigned int col = mse; col <= m; ++col) {\n         \
    \                   Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));\n\
    \                        }\n                    }\n                }\n       \
    \     }\n            unsigned int basis_num = m;\n            std::vector<char>\
    \ down(m, false);\n            _x0.assign(m, zero);\n            for (unsigned\
    \ int i = n; i --> 0;) {\n                unsigned int mse = m + 1;\n        \
    \        for (unsigned int col = 0; col <= m; ++col) {\n                    if\
    \ (Ab[i][col] != zero) {\n                        mse = col;\n               \
    \         break;\n                    }\n                }\n                if\
    \ (mse < m) {\n                    T mse_val_inv = mul_inv_fp(Ab[i][mse]);\n \
    \                   for (unsigned int row = 0; row < i; ++row) {\n           \
    \             if (Ab[row][mse] != zero) {\n                            T coef\
    \ = add_inv_fp(mul_fp(Ab[row][mse], mse_val_inv));\n                         \
    \   for (unsigned int col = mse; col <= m; ++col) {\n                        \
    \        Ab[row][col] = add_fp(Ab[row][col], mul_fp(coef, Ab[i][col]));\n    \
    \                        }\n                        }\n                    }\n\
    \                    for (unsigned int col = mse; col <= m; ++col) {\n       \
    \                 Ab[i][col] = mul_fp(Ab[i][col], mse_val_inv);\n            \
    \        }\n                    _x0[mse] = Ab[i][m];\n                    down[mse]\
    \ = true;\n                    --basis_num;\n                } else if (mse ==\
    \ m) {\n                    _empty = true;\n                    return;\n    \
    \            }\n            }\n            _basis.assign(basis_num, std::vector<T>(m));\n\
    \            int basis_id = 0;\n            for (unsigned int j = 0; j < m; ++j)\
    \ {\n                if (down[j]) continue;\n                for (unsigned int\
    \ j2 = 0, i = 0; j2 < m; ++j2) {\n                    _basis[basis_id][j2] = down[j2]\
    \ ? Ab[i++][j] : zero;\n                }\n                _basis[basis_id][j]\
    \ = add_inv_fp(one);\n                basis_id++;\n            }\n        }\n\
    };\n\ntemplate <typename T>\nusing GaussianEliminationF2 = GaussianElimination<\n\
    \    T,\n    internal::gauss_jordan::add_fp_f2, internal::gauss_jordan::add_inv_fp_f2,\n\
    \    internal::gauss_jordan::mul_fp_f2, internal::gauss_jordan::mul_inv_fp_f2>;\n\
    template <typename T>\nusing GaussianEliminationArithmetic = GaussianElimination<\n\
    \    T,\n    internal::gauss_jordan::add_fp_arithmetic, internal::gauss_jordan::add_inv_fp_arithmetic,\n\
    \    internal::gauss_jordan::mul_fp_arithmetic, internal::gauss_jordan::mul_inv_fp_arithmetic>;\n\
    } // namespace suisen\n\n\n#line 7 \"test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector\
    \ A(n, std::vector(m, mint(0)));\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j = 0; j < m; ++j) {\n            int val;\n            std::cin >> val;\n\
    \            A[i][j] = val;\n        }\n    }\n    std::vector<mint> b(n);\n \
    \   for (int i = 0; i < n; ++i) {\n        int val;\n        std::cin >> val;\n\
    \        b[i] = val;\n    }\n    suisen::GaussianEliminationArithmetic<mint> solution(A,\
    \ b);\n    if (solution.has_solution()) {\n        int r = solution.dimension();\n\
    \        const auto c = *solution.get_solution();\n        const auto &basis =\
    \ solution.get_basis();\n        std::cout << r << '\\n';\n        for (int i\
    \ = 0; i < m; ++i) {\n            std::cout << c[i].val() << \" \\n\"[i == m -\
    \ 1];\n        }\n        for (const auto &x : basis) {\n            for (int\
    \ i = 0; i < m; ++i) {\n                std::cout << x[i].val() << \" \\n\"[i\
    \ == m - 1];\n            }\n        }\n    } else {\n        std::cout << -1\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\n#include \"library/math/gaussian_elimination.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector\
    \ A(n, std::vector(m, mint(0)));\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j = 0; j < m; ++j) {\n            int val;\n            std::cin >> val;\n\
    \            A[i][j] = val;\n        }\n    }\n    std::vector<mint> b(n);\n \
    \   for (int i = 0; i < n; ++i) {\n        int val;\n        std::cin >> val;\n\
    \        b[i] = val;\n    }\n    suisen::GaussianEliminationArithmetic<mint> solution(A,\
    \ b);\n    if (solution.has_solution()) {\n        int r = solution.dimension();\n\
    \        const auto c = *solution.get_solution();\n        const auto &basis =\
    \ solution.get_basis();\n        std::cout << r << '\\n';\n        for (int i\
    \ = 0; i < m; ++i) {\n            std::cout << c[i].val() << \" \\n\"[i == m -\
    \ 1];\n        }\n        for (const auto &x : basis) {\n            for (int\
    \ i = 0; i < m; ++i) {\n                std::cout << x[i].val() << \" \\n\"[i\
    \ == m - 1];\n            }\n        }\n    } else {\n        std::cout << -1\
    \ << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/math/gaussian_elimination.hpp
  isVerificationFile: true
  path: test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp
  requiredBy: []
  timestamp: '2021-07-20 19:42:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp
- /verify/test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp.html
title: test/src/math/gaussian_elimination/system_of_linear_equations.test.cpp
---
