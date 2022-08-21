---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/algebra/monoid/affine_clamp.hpp
    title: library/algebra/monoid/affine_clamp.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
    title: test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algebra/monoid/affine.hpp\"\n\n\n\n#include <iostream>\n\
    #include <utility>\n\nnamespace suisen {\n    template <typename T>\n    struct\
    \ Affine {\n        T a, b;\n        Affine(const T &a = 1, const T &b = 0) :\
    \ a(a), b(b) {}\n\n        static Affine<T> id() { return Affine<T>{}; }\n   \
    \     static Affine<T> compose(const Affine<T>& f, const Affine<T>& g) { return\
    \ f.compose(g); }\n\n        Affine<T> compose(const Affine<T>& g) const { return\
    \ { a * g.a, affine(g.b) }; }\n\n        template <typename U = T>\n        U\
    \ affine(const T &x) const { return U(a) * x + b; }\n        T operator()(const\
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
    \n        template <typename U = T, typename V = T>\n        operator std::pair<U,\
    \ V>() { return std::pair<U, V>{ a, b }; }\n        template <typename U = T,\
    \ typename V = T>\n        operator std::tuple<U, V>() { return std::tuple<U,\
    \ V>{ a, b }; }\n\n        friend std::istream& operator<<(std::istream& in, Affine<T>\
    \ &f) { return in >> f.a >> f.b; }\n        friend std::ostream& operator>>(std::ostream&\
    \ out, const Affine<T> &f) { return out << f.a << ' ' << f.b; }\n    };\n} //\
    \ namespace suisen\n\n\n"
  code: "#ifndef SUISEN_AFFINE\n#define SUISEN_AFFINE\n\n#include <iostream>\n#include\
    \ <utility>\n\nnamespace suisen {\n    template <typename T>\n    struct Affine\
    \ {\n        T a, b;\n        Affine(const T &a = 1, const T &b = 0) : a(a), b(b)\
    \ {}\n\n        static Affine<T> id() { return Affine<T>{}; }\n        static\
    \ Affine<T> compose(const Affine<T>& f, const Affine<T>& g) { return f.compose(g);\
    \ }\n\n        Affine<T> compose(const Affine<T>& g) const { return { a * g.a,\
    \ affine(g.b) }; }\n\n        template <typename U = T>\n        U affine(const\
    \ T &x) const { return U(a) * x + b; }\n        T operator()(const T &x) const\
    \ { return affine<T>(x); }\n\n        Affine<T> operator+() const { return *this;\
    \ }\n        Affine<T> operator-() const { return { -a, -b }; }\n\n        Affine<T>&\
    \ operator++() { ++b; return *this; }\n        Affine<T>& operator--() { --b;\
    \ return *this; }\n        Affine<T> operator++(int) { Affine<T> f(*this); ++(*this);\
    \ return f; }\n        Affine<T> operator--(int) { Affine<T> f(*this); --(*this);\
    \ return f; }\n\n        Affine<T>& operator+=(const T& c) { b += c; return *this;\
    \ }\n        Affine<T>& operator-=(const T& c) { b -= c; return *this; }\n   \
    \     friend Affine<T> operator+(Affine<T> f, const T &c) { f += c; return f;\
    \ }\n        friend Affine<T> operator-(Affine<T> f, const T &c) { f -= c; return\
    \ f; }\n\n        Affine<T>& operator+=(const Affine<T> &g) { a += g.a, b += g.b;\
    \ return *this; }\n        Affine<T>& operator-=(const Affine<T> &g) { a -= g.a,\
    \ b -= g.b; return *this; }\n        friend Affine<T> operator+(Affine<T> f, const\
    \ Affine<T> &g) { f += g; return f; }\n        friend Affine<T> operator-(Affine<T>\
    \ f, const Affine<T> &g) { f -= g; return f; }\n\n        template <typename U\
    \ = T, typename V = T>\n        operator std::pair<U, V>() { return std::pair<U,\
    \ V>{ a, b }; }\n        template <typename U = T, typename V = T>\n        operator\
    \ std::tuple<U, V>() { return std::tuple<U, V>{ a, b }; }\n\n        friend std::istream&\
    \ operator<<(std::istream& in, Affine<T> &f) { return in >> f.a >> f.b; }\n  \
    \      friend std::ostream& operator>>(std::ostream& out, const Affine<T> &f)\
    \ { return out << f.a << ' ' << f.b; }\n    };\n} // namespace suisen\n\n#endif\
    \ // SUISEN_AFFINE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algebra/monoid/affine.hpp
  requiredBy:
  - library/algebra/monoid/affine_clamp.hpp
  timestamp: '2022-08-21 18:19:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
documentation_of: library/algebra/monoid/affine.hpp
layout: document
redirect_from:
- /library/library/algebra/monoid/affine.hpp
- /library/library/algebra/monoid/affine.hpp.html
title: library/algebra/monoid/affine.hpp
---
