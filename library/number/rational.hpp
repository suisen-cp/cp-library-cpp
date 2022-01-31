#ifndef SUISEN_RATIONAL
#define SUISEN_RATIONAL

#include <cmath>
#include <ostream>
#include <numeric>
#include <type_traits>
#include <vector>

namespace suisen {

template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
struct Rational {
    T num, den;

    Rational() : Rational(0) {}
    Rational(T n) : num(n), den(1) {}
    Rational(T n, T d) {
        if (n == 0) {
            assert(d != 0);
            num = 0, den = 1;
        } else {
            T g = std::gcd(n, d);
            n /= g, d /= g;
            if (d < 0) n = -n, d = -d;
            num = n, den = d;
        }
    }

    // l > 0 -> 1, l = 0 -> 0, l < 0 -> -1
    int signum() const {
        return -1 + (num >= 0) + (num > 0);
    }

    // l > r -> 1, l = r -> 0, l < r -> -1
    static int compare(const Rational &l, const Rational &r) {
        auto pow_m1 = [](bool x) { return -int(x) | 1; };
        const int sgn_l = l.signum(), sgn_r = r.signum();
        if (l.num == 0) return -sgn_r;
        if (r.num == 0) return +sgn_l;
        if ((sgn_l ^ sgn_r) < 0) return sgn_l;
        T nl = std::abs(l.num), dl = l.den, nr = std::abs(r.num), dr = r.den;
        bool rev = sgn_l < 0;
        for (; dl and dr; rev = -rev) {
            T ql = nl / dl, qr = nr / dr;
            if (ql != qr) return pow_m1((ql < qr) xor rev);
            T rl = nl % dl, rr = nr % dr;
            nl = dl, dl = rl;
            nr = dr, dr = rr;
        }
        return dl or dr ? pow_m1((dr > 0) xor rev) : 0;
    }
    
    friend bool operator<(const Rational &l, const Rational &r) {
        return compare(l, r) < 0;
    }
    friend bool operator>(const Rational &l, const Rational &r) {
        return compare(l, r) > 0;
    }
    friend bool operator<=(const Rational &l, const Rational &r) {
        return compare(l, r) <= 0;
    }
    friend bool operator>=(const Rational &l, const Rational &r) {
        return compare(l, r) >= 0;
    }
    friend bool operator==(const Rational &l, const Rational &r) {
        return compare(l, r) == 0;
    }
    friend bool operator!=(const Rational &l, const Rational &r) {
        return compare(l, r) != 0;
    }

    Rational operator+() const {
        return *this;
    }
    Rational operator-() const {
        return Rational(-num, den);
    }
    friend Rational operator+(const Rational &l, const Rational &r) {
        T lcm = l.den / std::gcd(l.den, r.den) * r.den;
        return Rational(l.num * (lcm / l.den) + r.num * (lcm / r.den), lcm);
    }
    friend Rational operator-(const Rational &l, const Rational &r) {
        T lcm = l.den / std::gcd(l.den, r.den) * r.den;
        return Rational(l.num * (lcm / l.den) - r.num * (lcm / r.den), lcm);
    }
    friend Rational operator*(const Rational &l, const Rational &r) {
        T g1 = std::gcd(l.num, r.den);
        T g2 = std::gcd(l.den, r.num);
        return Rational((l.num / g1) * (r.num / g2), (l.den / g2) * (r.den / g1));
    }
    friend Rational operator/(const Rational &l, const Rational &r) {
        return l * r.inv();
    }
    Rational& operator+=(const Rational &r) {
        *this = *this + r;
        return *this;
    }
    Rational& operator-=(const Rational &r) {
        *this = *this - r;
        return *this;
    }
    Rational& operator*=(const Rational &r) {
        *this = *this * r;
        return *this;
    }
    Rational& operator/=(const Rational &r) {
        *this = *this / r;
        return *this;
    }
    Rational inv() const {
        return Rational(den, num);
    }
    Rational abs() const {
        return Rational(std::abs(num), den);
    }

    explicit operator int() const {
        return (int) (num / den);
    }
    explicit operator long long() const {
        return (long long) (num / den);
    }
    explicit operator double() const {
        return (double) num / den;
    }
    explicit operator long double() const {
        return (long double) num / den;
    }

    T floor() const {
        return num >= 0 ? num / den : -(-num / den);
    }
    T ceil() const {
        return num >= 0 ? -(-num / den) : num / den;
    }

    static std::pair<Rational, Rational> approximate(long double target, T max_numerator, T max_denominator) {
        long double x = std::abs(target);
        T nl = 0, dl = 1, nr = 1, dr = 0;
        while (true) {
            T nm = nl + nr, dm = dl + dr;
            if (nm > max_numerator or dm > max_denominator) break;
            if ((long double) nm / dm < x) {
                nl = nm, dl = dm;
            } else {
                nr = nm, dr = dm;
            }
        }
        if (target >= 0) {
            return { Rational(+nl, dl), Rational(+nr, dr) };
        } else {
            return { Rational(-nr, dr), Rational(-nl, dl) };
        }
    }

    static std::vector<Rational> stern_brocot(int depth) {
        std::vector<Rational> t(1 << (depth + 1));
        for (int i = 1; i < int(t.size()); ++i) {
            int lk, rk;
            if (i & 1) {
                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);
            } else {
                rk = i >> 1, lk = i >> (__builtin_ctz( i) + 1);
            }
            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];
            Rational rr = rk == 0 ? Rational(1, 0) : t[rk];
            t[i] = Rational(lr.num + rr.num, lr.den + rr.den);
        }
        return t;
    }

    static std::vector<Rational> farey_sequence(int depth) {
        const int n = 1 << (depth + 1);
        std::vector<Rational> t(n);
        for (int i = 1; i < n; i++) {
            int lk, rk;
            if (i & 1) {
                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);
            } else {
                rk = i >> 1, lk = i >> (__builtin_ctz( i) + 1);
            }
            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];
            Rational rr = rk == 0 ? Rational(1, 1) : t[rk];
            t[i] = Rational(lr.num + rr.num, lr.den + rr.den);
        }
        std::vector<Rational> seq(n + 1);
        int i = 0;
        auto dfs = [&](auto dfs, int k) -> void {
            if (k >= n) return;
            dfs(dfs, k * 2 + 0);
            seq[i++] = t[k];
            dfs(dfs, k * 2 + 1);
        };
        seq[i++] = Rational(0, 1);
        dfs(dfs, 1);
        seq[i++] = Rational(1, 1);
        return seq;
    }
};

}

template <typename T>
std::ostream& operator<<(std::ostream &out, const suisen::Rational<T> &r) {
    return out << r.num << '/' << r.den;
}

template <typename T>
suisen::Rational<T> max(const suisen::Rational<T> &l, const suisen::Rational<T> &r) {
    return l > r ? l : r;
}
template <typename T>
suisen::Rational<T> min(const suisen::Rational<T> &l, const suisen::Rational<T> &r) {
    return l < r ? l : r;
}


#endif // SUISEN_RATIONAL
