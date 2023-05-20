---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/polynomial_gcd/inv_of_polynomials.test.cpp
    title: test/src/polynomial/polynomial_gcd/inv_of_polynomials.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/polynomial_gcd.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <tuple>\n\nnamespace suisen {\n    namespace\
    \ internal::poly_gcd {\n        template <typename Polynomial>\n        using\
    \ PolynomialMatrix = std::array<std::array<Polynomial, 2>, 2>;\n\n        template\
    \ <typename Polynomial>\n        PolynomialMatrix<Polynomial> e1() {\n       \
    \     return { Polynomial{1}, Polynomial{}, Polynomial{}, Polynomial{1} };\n \
    \       }\n        template <typename Polynomial>\n        PolynomialMatrix<Polynomial>\
    \ mul_mat(const PolynomialMatrix<Polynomial>& A, const PolynomialMatrix<Polynomial>&\
    \ B) {\n            PolynomialMatrix<Polynomial> C{};\n            for (int i\
    \ = 0; i < 2; ++i) {\n                for (int j = 0; j < 2; ++j) for (int k =\
    \ 0; k < 2; ++k) C[i][k] += A[i][j] * B[j][k];\n                for (int j = 0;\
    \ j < 2; ++j) C[i][j].cut_trailing_zeros();\n            }\n            return\
    \ C;\n        }\n        template <typename Polynomial>\n        std::array<Polynomial,\
    \ 2> mul_vec(const PolynomialMatrix<Polynomial>& A, const std::array<Polynomial,\
    \ 2>& x) {\n            std::array<Polynomial, 2> y{};\n            for (int i\
    \ = 0; i < 2; ++i) {\n                for (int j = 0; j < 2; ++j) y[i] += A[i][j]\
    \ * x[j];\n                y[i].cut_trailing_zeros();\n            }\n       \
    \     return y;\n        }\n\n        template <typename Polynomial>\n       \
    \ std::pair<PolynomialMatrix<Polynomial>, Polynomial> half_gcd(Polynomial f, Polynomial\
    \ g, int lo = -1) {\n            PolynomialMatrix<Polynomial> P = e1<Polynomial>();\n\
    \            while (g.size()) {\n                assert(f.size() >= g.size());\n\
    \                const int fd = f.deg(), gd = g.deg();\n                if (const\
    \ int k = fd / 2; k > 128 and k <= gd) {\n                    PolynomialMatrix<Polynomial>\
    \ Q = half_gcd(Polynomial(f.begin() + k, f.end()), Polynomial(g.begin() + k, g.end()),\
    \ (fd - k) / 2).first;\n                    if (Q != e1<Polynomial>()) {\n   \
    \                     auto [f2, g2] = mul_vec(Q, { std::move(f), std::move(g)\
    \ });\n                        f = std::move(f2), g = std::move(g2);\n       \
    \                 if (f.deg() <= lo) break;\n                        P = mul_mat(Q,\
    \ P);\n                    }\n                }\n                if (g.deg() <=\
    \ lo) break;\n                auto [p, q] = f.div_mod(g);\n                f =\
    \ std::move(g), g = std::move(q);\n                P = mul_mat(PolynomialMatrix<Polynomial>{\
    \ Polynomial{}, Polynomial{ 1 }, Polynomial{ 1 }, -p }, P);\n            }\n \
    \           return { P, f };\n        }\n\n        // { x, y, g=gcd(a,b) (monic)\
    \ } s.t. ax+by=g\n        template <typename Polynomial>\n        std::tuple<Polynomial,\
    \ Polynomial, Polynomial> ext_gcd(Polynomial a, Polynomial b) {\n            bool\
    \ swapped = false;\n            a.cut_trailing_zeros();\n            b.cut_trailing_zeros();\n\
    \            if (a.size() < b.size()) std::swap(a, b), swapped = true;\n     \
    \       auto [P, g] = half_gcd(a, b);\n            auto& [x, y] = P[0];\n    \
    \        if (g.size()) {\n                auto c = g.back().inv();\n         \
    \       x *= c, y *= c, g *= c;\n            }\n            if (swapped) std::swap(x,\
    \ y);\n            return { x, y, g };\n        }\n    }\n\n    // @return { x,\
    \ y, g=gcd(a,b) (monic) } s.t. ax+by=g\n    template <typename Polynomial>\n \
    \   std::tuple<Polynomial, Polynomial, Polynomial> polynomial_ext_gcd(const Polynomial\
    \ &a, const Polynomial &b) {\n        return internal::poly_gcd::ext_gcd(a, b);\n\
    \    }\n    // @return { x, g=gcd(a,b) (monic) } s.t. ax=g (mod m)\n    template\
    \ <typename Polynomial>\n    std::pair<Polynomial, Polynomial> polynomial_gcd_inv(const\
    \ Polynomial &a, const Polynomial &m) {\n        auto [x, _, g] = polynomial_ext_gcd(a,\
    \ m);\n        return { x, g };\n    }\n    // @return x s.t. ax=1 (mod m)\n \
    \   template <typename Polynomial>\n    std::pair<Polynomial, Polynomial> polynomial_inv(const\
    \ Polynomial &a, const Polynomial &m) {\n        auto [x, _, g] = polynomial_ext_gcd(a,\
    \ m);\n        assert(g == Polynomial{1});\n        return x;\n    }\n    // @return\
    \ gcd(a,b) (monic)\n    template <typename Polynomial>\n    std::tuple<Polynomial,\
    \ Polynomial, Polynomial> polynomial_gcd(const Polynomial &a, const Polynomial\
    \ &b) {\n        return std::get<2>(ext_gcd(a, b));\n    }\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_POLYNOMIAL_GCD\n#define SUISEN_POLYNOMIAL_GCD\n\n#include\
    \ <array>\n#include <cassert>\n#include <tuple>\n\nnamespace suisen {\n    namespace\
    \ internal::poly_gcd {\n        template <typename Polynomial>\n        using\
    \ PolynomialMatrix = std::array<std::array<Polynomial, 2>, 2>;\n\n        template\
    \ <typename Polynomial>\n        PolynomialMatrix<Polynomial> e1() {\n       \
    \     return { Polynomial{1}, Polynomial{}, Polynomial{}, Polynomial{1} };\n \
    \       }\n        template <typename Polynomial>\n        PolynomialMatrix<Polynomial>\
    \ mul_mat(const PolynomialMatrix<Polynomial>& A, const PolynomialMatrix<Polynomial>&\
    \ B) {\n            PolynomialMatrix<Polynomial> C{};\n            for (int i\
    \ = 0; i < 2; ++i) {\n                for (int j = 0; j < 2; ++j) for (int k =\
    \ 0; k < 2; ++k) C[i][k] += A[i][j] * B[j][k];\n                for (int j = 0;\
    \ j < 2; ++j) C[i][j].cut_trailing_zeros();\n            }\n            return\
    \ C;\n        }\n        template <typename Polynomial>\n        std::array<Polynomial,\
    \ 2> mul_vec(const PolynomialMatrix<Polynomial>& A, const std::array<Polynomial,\
    \ 2>& x) {\n            std::array<Polynomial, 2> y{};\n            for (int i\
    \ = 0; i < 2; ++i) {\n                for (int j = 0; j < 2; ++j) y[i] += A[i][j]\
    \ * x[j];\n                y[i].cut_trailing_zeros();\n            }\n       \
    \     return y;\n        }\n\n        template <typename Polynomial>\n       \
    \ std::pair<PolynomialMatrix<Polynomial>, Polynomial> half_gcd(Polynomial f, Polynomial\
    \ g, int lo = -1) {\n            PolynomialMatrix<Polynomial> P = e1<Polynomial>();\n\
    \            while (g.size()) {\n                assert(f.size() >= g.size());\n\
    \                const int fd = f.deg(), gd = g.deg();\n                if (const\
    \ int k = fd / 2; k > 128 and k <= gd) {\n                    PolynomialMatrix<Polynomial>\
    \ Q = half_gcd(Polynomial(f.begin() + k, f.end()), Polynomial(g.begin() + k, g.end()),\
    \ (fd - k) / 2).first;\n                    if (Q != e1<Polynomial>()) {\n   \
    \                     auto [f2, g2] = mul_vec(Q, { std::move(f), std::move(g)\
    \ });\n                        f = std::move(f2), g = std::move(g2);\n       \
    \                 if (f.deg() <= lo) break;\n                        P = mul_mat(Q,\
    \ P);\n                    }\n                }\n                if (g.deg() <=\
    \ lo) break;\n                auto [p, q] = f.div_mod(g);\n                f =\
    \ std::move(g), g = std::move(q);\n                P = mul_mat(PolynomialMatrix<Polynomial>{\
    \ Polynomial{}, Polynomial{ 1 }, Polynomial{ 1 }, -p }, P);\n            }\n \
    \           return { P, f };\n        }\n\n        // { x, y, g=gcd(a,b) (monic)\
    \ } s.t. ax+by=g\n        template <typename Polynomial>\n        std::tuple<Polynomial,\
    \ Polynomial, Polynomial> ext_gcd(Polynomial a, Polynomial b) {\n            bool\
    \ swapped = false;\n            a.cut_trailing_zeros();\n            b.cut_trailing_zeros();\n\
    \            if (a.size() < b.size()) std::swap(a, b), swapped = true;\n     \
    \       auto [P, g] = half_gcd(a, b);\n            auto& [x, y] = P[0];\n    \
    \        if (g.size()) {\n                auto c = g.back().inv();\n         \
    \       x *= c, y *= c, g *= c;\n            }\n            if (swapped) std::swap(x,\
    \ y);\n            return { x, y, g };\n        }\n    }\n\n    // @return { x,\
    \ y, g=gcd(a,b) (monic) } s.t. ax+by=g\n    template <typename Polynomial>\n \
    \   std::tuple<Polynomial, Polynomial, Polynomial> polynomial_ext_gcd(const Polynomial\
    \ &a, const Polynomial &b) {\n        return internal::poly_gcd::ext_gcd(a, b);\n\
    \    }\n    // @return { x, g=gcd(a,b) (monic) } s.t. ax=g (mod m)\n    template\
    \ <typename Polynomial>\n    std::pair<Polynomial, Polynomial> polynomial_gcd_inv(const\
    \ Polynomial &a, const Polynomial &m) {\n        auto [x, _, g] = polynomial_ext_gcd(a,\
    \ m);\n        return { x, g };\n    }\n    // @return x s.t. ax=1 (mod m)\n \
    \   template <typename Polynomial>\n    std::pair<Polynomial, Polynomial> polynomial_inv(const\
    \ Polynomial &a, const Polynomial &m) {\n        auto [x, _, g] = polynomial_ext_gcd(a,\
    \ m);\n        assert(g == Polynomial{1});\n        return x;\n    }\n    // @return\
    \ gcd(a,b) (monic)\n    template <typename Polynomial>\n    std::tuple<Polynomial,\
    \ Polynomial, Polynomial> polynomial_gcd(const Polynomial &a, const Polynomial\
    \ &b) {\n        return std::get<2>(ext_gcd(a, b));\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_POLYNOMIAL_GCD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/polynomial_gcd.hpp
  requiredBy: []
  timestamp: '2023-05-21 05:26:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/polynomial_gcd/inv_of_polynomials.test.cpp
documentation_of: library/polynomial/polynomial_gcd.hpp
layout: document
title: Polynomial Gcd
---
## Polynomial Gcd
