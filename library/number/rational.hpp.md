---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/rational.hpp\"\n\n\n\n#include <cmath>\n\
    #include <ostream>\n#include <numeric>\n#include <type_traits>\n#include <vector>\n\
    \nnamespace suisen {\n\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstruct Rational {\n    T num, den;\n\n    Rational()\
    \ : Rational(0) {}\n    Rational(T n) : num(n), den(1) {}\n    Rational(T n, T\
    \ d) {\n        if (n == 0) {\n            assert(d != 0);\n            num =\
    \ 0, den = 1;\n        } else {\n            T g = std::gcd(n, d);\n         \
    \   n /= g, d /= g;\n            if (d < 0) n = -n, d = -d;\n            num =\
    \ n, den = d;\n        }\n    }\n\n    // l > 0 -> 1, l = 0 -> 0, l < 0 -> -1\n\
    \    int signum() const {\n        return -1 + (num >= 0) + (num > 0);\n    }\n\
    \n    // l > r -> 1, l = r -> 0, l < r -> -1\n    static int compare(const Rational\
    \ &l, const Rational &r) {\n        auto pow_m1 = [](bool x) { return -int(x)\
    \ | 1; };\n        const int sgn_l = l.signum(), sgn_r = r.signum();\n       \
    \ if (l.num == 0) return -sgn_r;\n        if (r.num == 0) return +sgn_l;\n   \
    \     if ((sgn_l ^ sgn_r) < 0) return sgn_l;\n        T nl = std::abs(l.num),\
    \ dl = l.den, nr = std::abs(r.num), dr = r.den;\n        bool rev = sgn_l < 0;\n\
    \        for (; dl and dr; rev = -rev) {\n            T ql = nl / dl, qr = nr\
    \ / dr;\n            if (ql != qr) return pow_m1((ql < qr) xor rev);\n       \
    \     T rl = nl % dl, rr = nr % dr;\n            nl = dl, dl = rl;\n         \
    \   nr = dr, dr = rr;\n        }\n        return dl or dr ? pow_m1((dr > 0) xor\
    \ rev) : 0;\n    }\n    \n    friend bool operator<(const Rational &l, const Rational\
    \ &r) {\n        return compare(l, r) < 0;\n    }\n    friend bool operator>(const\
    \ Rational &l, const Rational &r) {\n        return compare(l, r) > 0;\n    }\n\
    \    friend bool operator<=(const Rational &l, const Rational &r) {\n        return\
    \ compare(l, r) <= 0;\n    }\n    friend bool operator>=(const Rational &l, const\
    \ Rational &r) {\n        return compare(l, r) >= 0;\n    }\n    friend bool operator==(const\
    \ Rational &l, const Rational &r) {\n        return compare(l, r) == 0;\n    }\n\
    \    friend bool operator!=(const Rational &l, const Rational &r) {\n        return\
    \ compare(l, r) != 0;\n    }\n\n    Rational operator+() const {\n        return\
    \ *this;\n    }\n    Rational operator-() const {\n        return Rational(-num,\
    \ den);\n    }\n    friend Rational operator+(const Rational &l, const Rational\
    \ &r) {\n        T lcm = l.den / std::gcd(l.den, r.den) * r.den;\n        return\
    \ Rational(l.num * (lcm / l.den) + r.num * (lcm / r.den), lcm);\n    }\n    friend\
    \ Rational operator-(const Rational &l, const Rational &r) {\n        T lcm =\
    \ l.den / std::gcd(l.den, r.den) * r.den;\n        return Rational(l.num * (lcm\
    \ / l.den) - r.num * (lcm / r.den), lcm);\n    }\n    friend Rational operator*(const\
    \ Rational &l, const Rational &r) {\n        T g1 = std::gcd(l.num, r.den);\n\
    \        T g2 = std::gcd(l.den, r.num);\n        return Rational((l.num / g1)\
    \ * (r.num / g2), (l.den / g2) * (r.den / g1));\n    }\n    friend Rational operator/(const\
    \ Rational &l, const Rational &r) {\n        return l * r.inv();\n    }\n    Rational&\
    \ operator+=(const Rational &r) {\n        *this = *this + r;\n        return\
    \ *this;\n    }\n    Rational& operator-=(const Rational &r) {\n        *this\
    \ = *this - r;\n        return *this;\n    }\n    Rational& operator*=(const Rational\
    \ &r) {\n        *this = *this * r;\n        return *this;\n    }\n    Rational&\
    \ operator/=(const Rational &r) {\n        *this = *this / r;\n        return\
    \ *this;\n    }\n    Rational inv() const {\n        return Rational(den, num);\n\
    \    }\n    Rational abs() const {\n        return Rational(std::abs(num), den);\n\
    \    }\n\n    explicit operator int() const {\n        return (int) (num / den);\n\
    \    }\n    explicit operator long long() const {\n        return (long long)\
    \ (num / den);\n    }\n    explicit operator double() const {\n        return\
    \ (double) num / den;\n    }\n    explicit operator long double() const {\n  \
    \      return (long double) num / den;\n    }\n\n    T floor() const {\n     \
    \   return num >= 0 ? num / den : -(-num / den);\n    }\n    T ceil() const {\n\
    \        return num >= 0 ? -(-num / den) : num / den;\n    }\n\n    static std::pair<Rational,\
    \ Rational> approximate(long double target, T max_numerator, T max_denominator)\
    \ {\n        long double x = std::abs(target);\n        T nl = 0, dl = 1, nr =\
    \ 1, dr = 0;\n        while (true) {\n            T nm = nl + nr, dm = dl + dr;\n\
    \            if (nm > max_numerator or dm > max_denominator) break;\n        \
    \    if ((long double) nm / dm < x) {\n                nl = nm, dl = dm;\n   \
    \         } else {\n                nr = nm, dr = dm;\n            }\n       \
    \ }\n        if (target >= 0) {\n            return { Rational(+nl, dl), Rational(+nr,\
    \ dr) };\n        } else {\n            return { Rational(-nr, dr), Rational(-nl,\
    \ dl) };\n        }\n    }\n\n    static std::vector<Rational> stern_brocot(int\
    \ depth) {\n        std::vector<Rational> t(1 << (depth + 1));\n        for (int\
    \ i = 1; i < int(t.size()); ++i) {\n            int lk, rk;\n            if (i\
    \ & 1) {\n                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);\n  \
    \          } else {\n                rk = i >> 1, lk = i >> (__builtin_ctz( i)\
    \ + 1);\n            }\n            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];\n\
    \            Rational rr = rk == 0 ? Rational(1, 0) : t[rk];\n            t[i]\
    \ = Rational(lr.num + rr.num, lr.den + rr.den);\n        }\n        return t;\n\
    \    }\n\n    static std::vector<Rational> farey_sequence(int depth) {\n     \
    \   const int n = 1 << (depth + 1);\n        std::vector<Rational> t(n);\n   \
    \     for (int i = 1; i < n; i++) {\n            int lk, rk;\n            if (i\
    \ & 1) {\n                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);\n  \
    \          } else {\n                rk = i >> 1, lk = i >> (__builtin_ctz( i)\
    \ + 1);\n            }\n            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];\n\
    \            Rational rr = rk == 0 ? Rational(1, 1) : t[rk];\n            t[i]\
    \ = Rational(lr.num + rr.num, lr.den + rr.den);\n        }\n        std::vector<Rational>\
    \ seq(n + 1);\n        int i = 0;\n        auto dfs = [&](auto dfs, int k) ->\
    \ void {\n            if (k >= n) return;\n            dfs(dfs, k * 2 + 0);\n\
    \            seq[i++] = t[k];\n            dfs(dfs, k * 2 + 1);\n        };\n\
    \        seq[i++] = Rational(0, 1);\n        dfs(dfs, 1);\n        seq[i++] =\
    \ Rational(1, 1);\n        return seq;\n    }\n};\n\n}\n\ntemplate <typename T>\n\
    std::ostream& operator<<(std::ostream &out, const suisen::Rational<T> &r) {\n\
    \    return out << r.num << '/' << r.den;\n}\n\ntemplate <typename T>\nsuisen::Rational<T>\
    \ max(const suisen::Rational<T> &l, const suisen::Rational<T> &r) {\n    return\
    \ l > r ? l : r;\n}\ntemplate <typename T>\nsuisen::Rational<T> min(const suisen::Rational<T>\
    \ &l, const suisen::Rational<T> &r) {\n    return l < r ? l : r;\n}\n\n\n\n"
  code: "#ifndef SUISEN_RATIONAL\n#define SUISEN_RATIONAL\n\n#include <cmath>\n#include\
    \ <ostream>\n#include <numeric>\n#include <type_traits>\n#include <vector>\n\n\
    namespace suisen {\n\ntemplate <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\nstruct Rational {\n    T num, den;\n\n    Rational()\
    \ : Rational(0) {}\n    Rational(T n) : num(n), den(1) {}\n    Rational(T n, T\
    \ d) {\n        if (n == 0) {\n            assert(d != 0);\n            num =\
    \ 0, den = 1;\n        } else {\n            T g = std::gcd(n, d);\n         \
    \   n /= g, d /= g;\n            if (d < 0) n = -n, d = -d;\n            num =\
    \ n, den = d;\n        }\n    }\n\n    // l > 0 -> 1, l = 0 -> 0, l < 0 -> -1\n\
    \    int signum() const {\n        return -1 + (num >= 0) + (num > 0);\n    }\n\
    \n    // l > r -> 1, l = r -> 0, l < r -> -1\n    static int compare(const Rational\
    \ &l, const Rational &r) {\n        auto pow_m1 = [](bool x) { return -int(x)\
    \ | 1; };\n        const int sgn_l = l.signum(), sgn_r = r.signum();\n       \
    \ if (l.num == 0) return -sgn_r;\n        if (r.num == 0) return +sgn_l;\n   \
    \     if ((sgn_l ^ sgn_r) < 0) return sgn_l;\n        T nl = std::abs(l.num),\
    \ dl = l.den, nr = std::abs(r.num), dr = r.den;\n        bool rev = sgn_l < 0;\n\
    \        for (; dl and dr; rev = -rev) {\n            T ql = nl / dl, qr = nr\
    \ / dr;\n            if (ql != qr) return pow_m1((ql < qr) xor rev);\n       \
    \     T rl = nl % dl, rr = nr % dr;\n            nl = dl, dl = rl;\n         \
    \   nr = dr, dr = rr;\n        }\n        return dl or dr ? pow_m1((dr > 0) xor\
    \ rev) : 0;\n    }\n    \n    friend bool operator<(const Rational &l, const Rational\
    \ &r) {\n        return compare(l, r) < 0;\n    }\n    friend bool operator>(const\
    \ Rational &l, const Rational &r) {\n        return compare(l, r) > 0;\n    }\n\
    \    friend bool operator<=(const Rational &l, const Rational &r) {\n        return\
    \ compare(l, r) <= 0;\n    }\n    friend bool operator>=(const Rational &l, const\
    \ Rational &r) {\n        return compare(l, r) >= 0;\n    }\n    friend bool operator==(const\
    \ Rational &l, const Rational &r) {\n        return compare(l, r) == 0;\n    }\n\
    \    friend bool operator!=(const Rational &l, const Rational &r) {\n        return\
    \ compare(l, r) != 0;\n    }\n\n    Rational operator+() const {\n        return\
    \ *this;\n    }\n    Rational operator-() const {\n        return Rational(-num,\
    \ den);\n    }\n    friend Rational operator+(const Rational &l, const Rational\
    \ &r) {\n        T lcm = l.den / std::gcd(l.den, r.den) * r.den;\n        return\
    \ Rational(l.num * (lcm / l.den) + r.num * (lcm / r.den), lcm);\n    }\n    friend\
    \ Rational operator-(const Rational &l, const Rational &r) {\n        T lcm =\
    \ l.den / std::gcd(l.den, r.den) * r.den;\n        return Rational(l.num * (lcm\
    \ / l.den) - r.num * (lcm / r.den), lcm);\n    }\n    friend Rational operator*(const\
    \ Rational &l, const Rational &r) {\n        T g1 = std::gcd(l.num, r.den);\n\
    \        T g2 = std::gcd(l.den, r.num);\n        return Rational((l.num / g1)\
    \ * (r.num / g2), (l.den / g2) * (r.den / g1));\n    }\n    friend Rational operator/(const\
    \ Rational &l, const Rational &r) {\n        return l * r.inv();\n    }\n    Rational&\
    \ operator+=(const Rational &r) {\n        *this = *this + r;\n        return\
    \ *this;\n    }\n    Rational& operator-=(const Rational &r) {\n        *this\
    \ = *this - r;\n        return *this;\n    }\n    Rational& operator*=(const Rational\
    \ &r) {\n        *this = *this * r;\n        return *this;\n    }\n    Rational&\
    \ operator/=(const Rational &r) {\n        *this = *this / r;\n        return\
    \ *this;\n    }\n    Rational inv() const {\n        return Rational(den, num);\n\
    \    }\n    Rational abs() const {\n        return Rational(std::abs(num), den);\n\
    \    }\n\n    explicit operator int() const {\n        return (int) (num / den);\n\
    \    }\n    explicit operator long long() const {\n        return (long long)\
    \ (num / den);\n    }\n    explicit operator double() const {\n        return\
    \ (double) num / den;\n    }\n    explicit operator long double() const {\n  \
    \      return (long double) num / den;\n    }\n\n    T floor() const {\n     \
    \   return num >= 0 ? num / den : -(-num / den);\n    }\n    T ceil() const {\n\
    \        return num >= 0 ? -(-num / den) : num / den;\n    }\n\n    static std::pair<Rational,\
    \ Rational> approximate(long double target, T max_numerator, T max_denominator)\
    \ {\n        long double x = std::abs(target);\n        T nl = 0, dl = 1, nr =\
    \ 1, dr = 0;\n        while (true) {\n            T nm = nl + nr, dm = dl + dr;\n\
    \            if (nm > max_numerator or dm > max_denominator) break;\n        \
    \    if ((long double) nm / dm < x) {\n                nl = nm, dl = dm;\n   \
    \         } else {\n                nr = nm, dr = dm;\n            }\n       \
    \ }\n        if (target >= 0) {\n            return { Rational(+nl, dl), Rational(+nr,\
    \ dr) };\n        } else {\n            return { Rational(-nr, dr), Rational(-nl,\
    \ dl) };\n        }\n    }\n\n    static std::vector<Rational> stern_brocot(int\
    \ depth) {\n        std::vector<Rational> t(1 << (depth + 1));\n        for (int\
    \ i = 1; i < int(t.size()); ++i) {\n            int lk, rk;\n            if (i\
    \ & 1) {\n                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);\n  \
    \          } else {\n                rk = i >> 1, lk = i >> (__builtin_ctz( i)\
    \ + 1);\n            }\n            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];\n\
    \            Rational rr = rk == 0 ? Rational(1, 0) : t[rk];\n            t[i]\
    \ = Rational(lr.num + rr.num, lr.den + rr.den);\n        }\n        return t;\n\
    \    }\n\n    static std::vector<Rational> farey_sequence(int depth) {\n     \
    \   const int n = 1 << (depth + 1);\n        std::vector<Rational> t(n);\n   \
    \     for (int i = 1; i < n; i++) {\n            int lk, rk;\n            if (i\
    \ & 1) {\n                lk = i >> 1, rk = i >> (__builtin_ctz(~i) + 1);\n  \
    \          } else {\n                rk = i >> 1, lk = i >> (__builtin_ctz( i)\
    \ + 1);\n            }\n            Rational lr = lk == 0 ? Rational(0, 1) : t[lk];\n\
    \            Rational rr = rk == 0 ? Rational(1, 1) : t[rk];\n            t[i]\
    \ = Rational(lr.num + rr.num, lr.den + rr.den);\n        }\n        std::vector<Rational>\
    \ seq(n + 1);\n        int i = 0;\n        auto dfs = [&](auto dfs, int k) ->\
    \ void {\n            if (k >= n) return;\n            dfs(dfs, k * 2 + 0);\n\
    \            seq[i++] = t[k];\n            dfs(dfs, k * 2 + 1);\n        };\n\
    \        seq[i++] = Rational(0, 1);\n        dfs(dfs, 1);\n        seq[i++] =\
    \ Rational(1, 1);\n        return seq;\n    }\n};\n\n}\n\ntemplate <typename T>\n\
    std::ostream& operator<<(std::ostream &out, const suisen::Rational<T> &r) {\n\
    \    return out << r.num << '/' << r.den;\n}\n\ntemplate <typename T>\nsuisen::Rational<T>\
    \ max(const suisen::Rational<T> &l, const suisen::Rational<T> &r) {\n    return\
    \ l > r ? l : r;\n}\ntemplate <typename T>\nsuisen::Rational<T> min(const suisen::Rational<T>\
    \ &l, const suisen::Rational<T> &r) {\n    return l < r ? l : r;\n}\n\n\n#endif\
    \ // SUISEN_RATIONAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/rational.hpp
  requiredBy: []
  timestamp: '2022-01-31 13:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/rational.hpp
layout: document
title: Rational
---
## Rational