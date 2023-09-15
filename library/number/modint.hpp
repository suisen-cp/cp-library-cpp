#ifndef SUISEN_MODINT
#define SUISEN_MODINT

#include <cassert>
#include <limits>
#include <optional>
#include <iostream>

namespace suisen {
    namespace internal::modint {
        constexpr long long safe_mod(long long x, long long m) { return (x %= m) < 0 ? x + m : x; }
        constexpr long long pow_mod(long long x, long long n, int m) {
            if (m == 1) return 0;
            unsigned int um = m;
            unsigned long long r = 1, y = safe_mod(x, m);
            for (; n; n >>= 1) {
                if (n & 1) r = (r * y) % um;
                y = (y * y) % um;
            }
            return r;
        }
        constexpr bool is_prime(int n) {
            if (n <= 1) return false;
            if (n == 2 or n == 7 or n == 61) return true;
            if (n % 2 == 0) return false;
            long long d = n - 1;
            while (d % 2 == 0) d /= 2;
            constexpr long long bases[3] = { 2, 7, 61 };
            for (long long a : bases) {
                long long t = d, y = pow_mod(a, t, n);
                for (; t != n - 1 and y != 1 and y != n - 1; t <<= 1) y = y * y % n;
                if (y != n - 1 and t % 2 == 0) return false;
            }
            return true;
        }
        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return { b, 0 };
            long long s = b, t = a, m0 = 0, m1 = 1, tmp = 0;
            while (t) {
                long long u = s / t;
                s -= t * u, m0 -= m1 * u;
                tmp = s, s = t, t = tmp;
                tmp = m0, m0 = m1, m1 = tmp;
            }
            if (m0 < 0) m0 += b / s;
            return { s, m0 };
        }
        
        struct barrett_K128 {
            uint32_t M;      // mod
            __uint128_t L;   // ceil(2^K / M), where K = 128
            uint64_t dL, uL; // dL | (uL << 64) = L
            constexpr barrett_K128(uint32_t M) : M(M), L(~__uint128_t(0) / M + 1), dL(L), uL(L >> 64) {}
            constexpr uint32_t umod() const { return M; }
            // c mod M (correctly works for all 0<=c<2^64)
            template <bool care_M1 = true>
            constexpr uint32_t rem(uint64_t c) const {
                if constexpr (care_M1) if (M == 1) return 0;
                // uint32_t q = (c * L) >> 128;
                __uint128_t cu = __uint128_t(c) * uL;
                uint64_t cd = (__uint128_t(c) * dL) >> 64;
                uint32_t r = c - uint64_t(cu >> 64) * M;
                return uint64_t(cu) > ~cd ? r - M : r;
            }
            // a*b mod M
            constexpr uint32_t mul(uint32_t a, uint32_t b) const { return rem<false>(uint64_t(a) * b); }
        };
    }

    template <int m, std::enable_if_t<(1 <= m), std::nullptr_t> = nullptr>
    class static_modint {
        using mint = static_modint;

        struct raw_construct {};
        constexpr static_modint(int v, raw_construct) : _v(v) {}
    public:
        static constexpr int mod() { return m; }
        static constexpr unsigned int umod() { return m; }

        static constexpr mint raw(int v) { return mint(v, raw_construct{}); }

        constexpr static_modint() : _v(0) {}
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_signed<T>>, std::nullptr_t> = nullptr>
        constexpr static_modint(T v) : _v{} {
            int x = v % mod();
            if (x < 0) x += mod();
            _v = x;
        }
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_unsigned<T>>, std::nullptr_t> = nullptr>
        constexpr static_modint(T v) : _v(v % umod()) {}

        constexpr unsigned int val() const { return _v; }

        constexpr mint& operator++() {
            ++_v;
            if (_v == umod()) _v = 0;
            return *this;
        }
        constexpr mint& operator--() {
            if (_v == 0) _v = umod();
            --_v;
            return *this;
        }
        constexpr mint operator++(int) { mint x = *this; ++*this; return x; }
        constexpr mint operator--(int) { mint x = *this; --*this; return x; }

        constexpr mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        constexpr mint& operator-=(const mint& rhs) {
            _v -= rhs._v;
            if (_v >= umod()) _v += umod();
            return *this;
        }
        constexpr mint& operator*=(const mint& rhs) {
            _v = (unsigned long long) _v * rhs._v % umod();
            return *this;
        }
        constexpr mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

        constexpr mint operator+() const { return *this; }
        constexpr mint operator-() const { return _v == 0 ? *this : raw(umod() - _v); }

        constexpr mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            for (; n; n >>= 1) {
                if (n & 1) r *= x;
                x *= x;
            }
            return r;
        }
        constexpr mint xpow(long long n) const { return n < 0 ? inv().pow(-n) : pow(n); }
        constexpr mint inv() const {
            if constexpr (is_prime_mod) {
                assert(_v);
                return pow(umod() - 2);
            } else {
                const auto [g, res] = internal::modint::inv_gcd(_v, mod());
                assert(g == 1);
                return res;
            }
        }
        friend constexpr mint operator+(const mint& lhs, const mint& rhs) { mint res = lhs; res += rhs; return res; }
        friend constexpr mint operator-(const mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }
        friend constexpr mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs; return res; }
        friend constexpr mint operator/(const mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }
        friend constexpr bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
        friend constexpr bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }
    private:
        unsigned int _v;
        static constexpr bool is_prime_mod = internal::modint::is_prime(mod());
    };

    template <int id>
    class dynamic_modint {
        using mint = dynamic_modint;
        using barrett = internal::modint::barrett_K128;

        struct raw_construct {};
        constexpr dynamic_modint(int v, raw_construct) : _v(v) {}
    public:
        static int mod() { return bt.umod(); }
        static unsigned int umod() { return bt.umod(); }

        static void set_mod(int m) {
            assert(1 <= m);
            bt = barrett(m);
        }
        static mint raw(int v) { return dynamic_modint(v, raw_construct{}); }

        dynamic_modint() : _v(0) {}
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_signed<T>>, std::nullptr_t> = nullptr>
        dynamic_modint(T v) {
            if (v < 0) {
                int x = v % mod();
                if (x < 0) x += mod();
                _v = x;
            } else _v = bt.rem(v);
        }
        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_unsigned<T>>, std::nullptr_t> = nullptr>
        dynamic_modint(T v) : _v(bt.rem(v)) {}

        dynamic_modint(__uint128_t v) : _v(v % umod()) {}
        dynamic_modint(__int128_t v) {
            int x = v % mod();
            if (x < 0) x += mod();
            _v = x;
        }

        unsigned int val() const { return _v; }

        mint& operator++() {
            ++_v;
            if (_v == umod()) _v = 0;
            return *this;
        }
        mint& operator--() {
            if (_v == 0) _v = umod();
            --_v;
            return *this;
        }
        mint operator++(int) { mint x = *this; ++*this; return x; }
        mint operator--(int) { mint x = *this; --*this; return x; }

        mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        mint& operator-=(const mint& rhs) {
            _v -= rhs._v;
            if (_v >= umod()) _v += umod();
            return *this;
        }
        mint& operator*=(const mint& rhs) {
            _v = bt.mul(_v, rhs._v);
            return *this;
        }
        mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            for (; n; n >>= 1) {
                if (n & 1) r *= x;
                x *= x;
            }
            return r;
        }
        mint xpow(long long n) const { return n < 0 ? inv().pow(-n) : pow(n); }
        mint inv() const {
            const auto [g, res] = internal::modint::inv_gcd(_v, mod());
            assert(g == 1);
            return res;
        }

        friend mint operator+(const mint& lhs, const mint& rhs) { mint res = lhs; res += rhs; return res; }
        friend mint operator-(const mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }
        friend mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs; return res; }
        friend mint operator/(const mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }
        friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
        friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }
    private:
        unsigned int _v;
        static inline barrett bt{ 998244353 };
    };

    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;
    using modint = dynamic_modint<-1>;

    template <typename T> struct is_modint : std::false_type {};
    template <int m> struct is_modint<static_modint<m>> : std::true_type {};
    template <int id> struct is_modint<dynamic_modint<id>> : std::true_type {};
    template <typename T> constexpr bool is_modint_v = is_modint<T>::value;

    template <typename T> struct is_static_modint : std::false_type {};
    template <int m> struct is_static_modint<static_modint<m>> : std::true_type {};
    template <typename T> constexpr bool is_static_modint_v = is_static_modint<T>::value;

    template <typename T> struct is_dynamic_modint : std::false_type {};
    template <int id> struct is_dynamic_modint<dynamic_modint<id>> : std::true_type {};
    template <typename T> constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::optional<mint> mod_sqrt(mint a) {
        const int p = mint::mod();
        if (a == 0) return mint(0);
        if (p == 2) return a;
        if (a.pow((p - 1) / 2) != 1) return std::nullopt;
        mint b = 1;
        while (b.pow((p - 1) / 2) == 1) ++b;
        const int tlz = __builtin_ctz(p - 1), q = (p - 1) >> tlz;
        mint x = a.pow((q + 1) / 2);
        b = b.pow(q);
        for (int shift = 2; x * x != a; ++shift) {
            mint e = a.inv() * x * x;
            if (e.pow(1 << (tlz - shift)) != 1) x *= b;
            b *= b;
        }
        return x;
    }

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint sqrt(mint a) { return *safe_sqrt(a); }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint log(mint a) { assert(a == 1); return 0; }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint exp(mint a) { assert(a == 0); return 1; }
    template <typename mint, typename T, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint pow(mint a, T b) { return a.pow(b); }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    mint inv(mint a) { return a.inv(); }

    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::istream& operator>>(std::istream& is, mint& v) { long long val; is >> val, v = val; return is; }
    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>
    std::ostream& operator<<(std::ostream& os, const mint& v) { return os << v.val(); }
} // namespace suisen

#endif // SUISEN_MODINT
