#ifndef SUISEN_AFFINE
#define SUISEN_AFFINE

#include <iostream>
#include <utility>

namespace suisen {
    template <typename T>
    struct Affine {
        T a, b;
        Affine(const T &a = 1, const T &b = 0) : a(a), b(b) {}

        static Affine<T> id() { return Affine<T>{}; }
        static Affine<T> compose(const Affine<T>& f, const Affine<T>& g) { return f.compose(g); }

        Affine<T> compose(const Affine<T>& g) const { return { a * g.a, affine(g.b) }; }

        template <typename U = T>
        U affine(const T &x) const { return U(a) * x + b; }
        T operator()(const T &x) const { return affine<T>(x); }

        Affine<T> operator+() const { return *this; }
        Affine<T> operator-() const { return { -a, -b }; }

        Affine<T>& operator++() { ++b; return *this; }
        Affine<T>& operator--() { --b; return *this; }
        Affine<T> operator++(int) { Affine<T> f(*this); ++(*this); return f; }
        Affine<T> operator--(int) { Affine<T> f(*this); --(*this); return f; }

        Affine<T>& operator+=(const T& c) { b += c; return *this; }
        Affine<T>& operator-=(const T& c) { b -= c; return *this; }
        friend Affine<T> operator+(Affine<T> f, const T &c) { f += c; return f; }
        friend Affine<T> operator-(Affine<T> f, const T &c) { f -= c; return f; }

        Affine<T>& operator+=(const Affine<T> &g) { a += g.a, b += g.b; return *this; }
        Affine<T>& operator-=(const Affine<T> &g) { a -= g.a, b -= g.b; return *this; }
        friend Affine<T> operator+(Affine<T> f, const Affine<T> &g) { f += g; return f; }
        friend Affine<T> operator-(Affine<T> f, const Affine<T> &g) { f -= g; return f; }

        friend bool operator==(const Affine<T> &f, const Affine<T> &g) { return f.a == g.a and f.b == g.b; }
        friend bool operator!=(const Affine<T> &f, const Affine<T> &g) { return not (f == g); }
        friend bool operator< (const Affine<T> &f, const Affine<T> &g) { return f.a < g.a or (f.a == g.a and f.b < g.b); }
        friend bool operator<=(const Affine<T> &f, const Affine<T> &g) { return not (g < f); }
        friend bool operator> (const Affine<T> &f, const Affine<T> &g) { return g < f; }
        friend bool operator>=(const Affine<T> &f, const Affine<T> &g) { return not (f < g); }

        template <typename U = T, typename V = T>
        operator std::pair<U, V>() { return std::pair<U, V>{ a, b }; }
        template <typename U = T, typename V = T>
        operator std::tuple<U, V>() { return std::tuple<U, V>{ a, b }; }

        friend std::istream& operator<<(std::istream& in, Affine<T> &f) { return in >> f.a >> f.b; }
        friend std::ostream& operator>>(std::ostream& out, const Affine<T> &f) { return out << f.a << ' ' << f.b; }
    };
} // namespace suisen

#endif // SUISEN_AFFINE
