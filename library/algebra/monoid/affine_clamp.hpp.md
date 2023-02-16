---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algebra/monoid/affine.hpp
    title: Affine
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algebra/monoid/affine_clamp.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <limits>\n#include <type_traits>\n\n#line 1 \"library/algebra/monoid/affine.hpp\"\
    \n\n\n\n#include <iostream>\n#include <utility>\n\nnamespace suisen {\n    template\
    \ <typename T>\n    struct Affine {\n        T a, b;\n        Affine(const T &a\
    \ = 1, const T &b = 0) : a(a), b(b) {}\n\n        static Affine<T> id() { return\
    \ Affine<T>{}; }\n        static Affine<T> compose(const Affine<T>& f, const Affine<T>&\
    \ g) { return f.compose(g); }\n\n        Affine<T> compose(const Affine<T>& g)\
    \ const { return { a * g.a, affine(g.b) }; }\n\n        template <typename U =\
    \ T>\n        U affine(const T &x) const { return U(a) * x + b; }\n        T operator()(const\
    \ T &x) const { return affine<T>(x); }\n\n        Affine<T> operator+() const\
    \ { return *this; }\n        Affine<T> operator-() const { return { -a, -b };\
    \ }\n\n        Affine<T>& operator++() { ++b; return *this; }\n        Affine<T>&\
    \ operator--() { --b; return *this; }\n        Affine<T> operator++(int) { Affine<T>\
    \ f(*this); ++(*this); return f; }\n        Affine<T> operator--(int) { Affine<T>\
    \ f(*this); --(*this); return f; }\n\n        Affine<T>& operator+=(const T& c)\
    \ { b += c; return *this; }\n        Affine<T>& operator-=(const T& c) { b -=\
    \ c; return *this; }\n        friend Affine<T> operator+(Affine<T> f, const T\
    \ &c) { f += c; return f; }\n        friend Affine<T> operator-(Affine<T> f, const\
    \ T &c) { f -= c; return f; }\n\n        Affine<T>& operator+=(const Affine<T>\
    \ &g) { a += g.a, b += g.b; return *this; }\n        Affine<T>& operator-=(const\
    \ Affine<T> &g) { a -= g.a, b -= g.b; return *this; }\n        friend Affine<T>\
    \ operator+(Affine<T> f, const Affine<T> &g) { f += g; return f; }\n        friend\
    \ Affine<T> operator-(Affine<T> f, const Affine<T> &g) { f -= g; return f; }\n\
    \n        friend bool operator==(const Affine<T> &f, const Affine<T> &g) { return\
    \ f.a == g.a and f.b == g.b; }\n        friend bool operator!=(const Affine<T>\
    \ &f, const Affine<T> &g) { return not (f == g); }\n        friend bool operator<\
    \ (const Affine<T> &f, const Affine<T> &g) { return f.a < g.a or (f.a == g.a and\
    \ f.b < g.b); }\n        friend bool operator<=(const Affine<T> &f, const Affine<T>\
    \ &g) { return not (g < f); }\n        friend bool operator> (const Affine<T>\
    \ &f, const Affine<T> &g) { return g < f; }\n        friend bool operator>=(const\
    \ Affine<T> &f, const Affine<T> &g) { return not (f < g); }\n\n        template\
    \ <typename U = T, typename V = T>\n        operator std::pair<U, V>() { return\
    \ std::pair<U, V>{ a, b }; }\n        template <typename U = T, typename V = T>\n\
    \        operator std::tuple<U, V>() { return std::tuple<U, V>{ a, b }; }\n\n\
    \        friend std::istream& operator<<(std::istream& in, Affine<T> &f) { return\
    \ in >> f.a >> f.b; }\n        friend std::ostream& operator>>(std::ostream& out,\
    \ const Affine<T> &f) { return out << f.a << ' ' << f.b; }\n    };\n} // namespace\
    \ suisen\n\n\n#line 9 \"library/algebra/monoid/affine_clamp.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct AffineClamp : public Affine<T> {\n  \
    \      static constexpr T neg_inf = std::numeric_limits<T>::min();\n        static\
    \ constexpr T pos_inf = std::numeric_limits<T>::max();\n\n        T l, r;\n  \
    \      AffineClamp(const T &a = 1, const T &b = 0, const T &l = neg_inf, T r =\
    \ pos_inf) : Affine<T>(a, b), l(l), r(r) {}\n        AffineClamp(const Affine<T>\
    \ &f, const T &l = neg_inf, const T &r = pos_inf) : Affine<T>(f), l(l), r(r) {}\n\
    \n        static AffineClamp<T> id() { return AffineClamp<T>{}; }\n        static\
    \ AffineClamp<T> compose(const AffineClamp<T>& f, const AffineClamp<T>& g) {\n\
    \            AffineClamp<T> h{ Affine<T>::compose(f, g), f.affine_clamp(g.l),\
    \ f.affine_clamp(g.r) };\n            if (h.l > h.r) std::swap(h.l, h.r);\n  \
    \          return h;\n        }\n\n        AffineClamp<T> compose(const AffineClamp<T>&\
    \ g) const { return AffineClamp<T>::compose(*this, g); }\n\n        T affine_clamp(const\
    \ T &x) const { return std::clamp<__int128_t>(this->template affine<__int128_t>(x),\
    \ l, r); }\n        T operator()(const T &x) const { return affine_clamp(x); }\n\
    \n        template <typename U = T, typename V = T, typename W = T, typename X\
    \ = T>\n        operator std::tuple<U, V, W, X>() { return { this->a, this->b,\
    \ l, r }; }\n\n        friend std::istream& operator<<(std::istream& in, AffineClamp<T>&\
    \ f) { return in >> f.a >> f.b >> f.l >> f.r; }\n        friend std::ostream&\
    \ operator>>(std::ostream& out, const AffineClamp<T>& f) { return out << f.a <<\
    \ ' ' << f.b << ' ' << f.l << ' ' << f.r; }\n    };\n} // namespace suisen\n\n\
    \n"
  code: "#ifndef SUISEN_AFFINE_CLAMP\n#define SUISEN_AFFINE_CLAMP\n\n#include <algorithm>\n\
    #include <limits>\n#include <type_traits>\n\n#include \"library/algebra/monoid/affine.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct AffineClamp : public Affine<T> {\n  \
    \      static constexpr T neg_inf = std::numeric_limits<T>::min();\n        static\
    \ constexpr T pos_inf = std::numeric_limits<T>::max();\n\n        T l, r;\n  \
    \      AffineClamp(const T &a = 1, const T &b = 0, const T &l = neg_inf, T r =\
    \ pos_inf) : Affine<T>(a, b), l(l), r(r) {}\n        AffineClamp(const Affine<T>\
    \ &f, const T &l = neg_inf, const T &r = pos_inf) : Affine<T>(f), l(l), r(r) {}\n\
    \n        static AffineClamp<T> id() { return AffineClamp<T>{}; }\n        static\
    \ AffineClamp<T> compose(const AffineClamp<T>& f, const AffineClamp<T>& g) {\n\
    \            AffineClamp<T> h{ Affine<T>::compose(f, g), f.affine_clamp(g.l),\
    \ f.affine_clamp(g.r) };\n            if (h.l > h.r) std::swap(h.l, h.r);\n  \
    \          return h;\n        }\n\n        AffineClamp<T> compose(const AffineClamp<T>&\
    \ g) const { return AffineClamp<T>::compose(*this, g); }\n\n        T affine_clamp(const\
    \ T &x) const { return std::clamp<__int128_t>(this->template affine<__int128_t>(x),\
    \ l, r); }\n        T operator()(const T &x) const { return affine_clamp(x); }\n\
    \n        template <typename U = T, typename V = T, typename W = T, typename X\
    \ = T>\n        operator std::tuple<U, V, W, X>() { return { this->a, this->b,\
    \ l, r }; }\n\n        friend std::istream& operator<<(std::istream& in, AffineClamp<T>&\
    \ f) { return in >> f.a >> f.b >> f.l >> f.r; }\n        friend std::ostream&\
    \ operator>>(std::ostream& out, const AffineClamp<T>& f) { return out << f.a <<\
    \ ' ' << f.b << ' ' << f.l << ' ' << f.r; }\n    };\n} // namespace suisen\n\n\
    #endif // SUISEN_AFFINE_CLAMP\n"
  dependsOn:
  - library/algebra/monoid/affine.hpp
  isVerificationFile: false
  path: library/algebra/monoid/affine_clamp.hpp
  requiredBy: []
  timestamp: '2023-02-16 15:44:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algebra/monoid/affine_clamp.hpp
layout: document
title: Affine Clamp
---
## Affine Clamp