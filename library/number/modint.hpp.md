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
  bundledCode: "#line 1 \"library/number/modint.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n#include <optional>\n#include <iostream>\n\
    \nnamespace suisen {\n    namespace internal::modint {\n        constexpr long\
    \ long safe_mod(long long x, long long m) { return (x %= m) < 0 ? x + m : x; }\n\
    \        constexpr long long pow_mod(long long x, long long n, int m) {\n    \
    \        if (m == 1) return 0;\n            unsigned int um = m;\n           \
    \ unsigned long long r = 1, y = safe_mod(x, m);\n            for (; n; n >>= 1)\
    \ {\n                if (n & 1) r = (r * y) % um;\n                y = (y * y)\
    \ % um;\n            }\n            return r;\n        }\n        constexpr bool\
    \ is_prime(int n) {\n            if (n <= 1) return false;\n            if (n\
    \ == 2 or n == 7 or n == 61) return true;\n            if (n % 2 == 0) return\
    \ false;\n            long long d = n - 1;\n            while (d % 2 == 0) d /=\
    \ 2;\n            constexpr long long bases[3] = { 2, 7, 61 };\n            for\
    \ (long long a : bases) {\n                long long t = d, y = pow_mod(a, t,\
    \ n);\n                for (; t != n - 1 and y != 1 and y != n - 1; t <<= 1) y\
    \ = y * y % n;\n                if (y != n - 1 and t % 2 == 0) return false;\n\
    \            }\n            return true;\n        }\n        constexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\n            a = safe_mod(a,\
    \ b);\n            if (a == 0) return { b, 0 };\n            long long s = b,\
    \ t = a, m0 = 0, m1 = 1, tmp = 0;\n            while (t) {\n                long\
    \ long u = s / t;\n                s -= t * u, m0 -= m1 * u;\n               \
    \ tmp = s, s = t, t = tmp;\n                tmp = m0, m0 = m1, m1 = tmp;\n   \
    \         }\n            if (m0 < 0) m0 += b / s;\n            return { s, m0\
    \ };\n        }\n        \n        struct barrett_K128 {\n            uint32_t\
    \ M;      // mod\n            __uint128_t L;   // ceil(2^K / M), where K = 128\n\
    \            uint64_t dL, uL; // dL | (uL << 64) = L\n            constexpr barrett_K128(uint32_t\
    \ M) : M(M), L(~__uint128_t(0) / M + 1), dL(L), uL(L >> 64) {}\n            constexpr\
    \ uint32_t umod() const { return M; }\n            // c mod M (correctly works\
    \ for all 0<=c<2^64)\n            template <bool care_M1 = true>\n           \
    \ constexpr uint32_t rem(uint64_t c) const {\n                if constexpr (care_M1)\
    \ if (M == 1) return 0;\n                // uint32_t q = (c * L) >> 128;\n   \
    \             __uint128_t cu = __uint128_t(c) * uL;\n                uint64_t\
    \ cd = (__uint128_t(c) * dL) >> 64;\n                uint32_t r = c - uint64_t(cu\
    \ >> 64) * M;\n                return uint64_t(cu) > ~cd ? r - M : r;\n      \
    \      }\n            // a*b mod M\n            constexpr uint32_t mul(uint32_t\
    \ a, uint32_t b) const { return rem<false>(uint64_t(a) * b); }\n        };\n \
    \   }\n\n    template <int m, std::enable_if_t<(1 <= m), std::nullptr_t> = nullptr>\n\
    \    class static_modint {\n        using mint = static_modint;\n\n        struct\
    \ raw_construct {};\n        constexpr static_modint(int v, raw_construct) : _v(v)\
    \ {}\n    public:\n        static constexpr int mod() { return m; }\n        static\
    \ constexpr unsigned int umod() { return m; }\n\n        static constexpr mint\
    \ raw(int v) { return mint(v, raw_construct{}); }\n\n        constexpr static_modint()\
    \ : _v(0) {}\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_signed<T>>, std::nullptr_t> = nullptr>\n        constexpr static_modint(T\
    \ v) : _v{} {\n            int x = v % mod();\n            if (x < 0) x += mod();\n\
    \            _v = x;\n        }\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_unsigned<T>>, std::nullptr_t> = nullptr>\n        constexpr static_modint(T\
    \ v) : _v(v % umod()) {}\n\n        constexpr unsigned int val() const { return\
    \ _v; }\n\n        constexpr mint& operator++() {\n            ++_v;\n       \
    \     if (_v == umod()) _v = 0;\n            return *this;\n        }\n      \
    \  constexpr mint& operator--() {\n            if (_v == 0) _v = umod();\n   \
    \         --_v;\n            return *this;\n        }\n        constexpr mint\
    \ operator++(int) { mint x = *this; ++*this; return x; }\n        constexpr mint\
    \ operator--(int) { mint x = *this; --*this; return x; }\n\n        constexpr\
    \ mint& operator+=(const mint& rhs) {\n            _v += rhs._v;\n           \
    \ if (_v >= umod()) _v -= umod();\n            return *this;\n        }\n    \
    \    constexpr mint& operator-=(const mint& rhs) {\n            _v -= rhs._v;\n\
    \            if (_v >= umod()) _v += umod();\n            return *this;\n    \
    \    }\n        constexpr mint& operator*=(const mint& rhs) {\n            _v\
    \ = (unsigned long long) _v * rhs._v % umod();\n            return *this;\n  \
    \      }\n        constexpr mint& operator/=(const mint& rhs) { return *this *=\
    \ rhs.inv(); }\n\n        constexpr mint operator+() const { return *this; }\n\
    \        constexpr mint operator-() const { return _v == 0 ? *this : raw(umod()\
    \ - _v); }\n\n        constexpr mint pow(long long n) const {\n            assert(0\
    \ <= n);\n            mint x = *this, r = 1;\n            for (; n; n >>= 1) {\n\
    \                if (n & 1) r *= x;\n                x *= x;\n            }\n\
    \            return r;\n        }\n        constexpr mint xpow(long long n) const\
    \ { return n < 0 ? inv().pow(-n) : pow(n); }\n        constexpr mint inv() const\
    \ {\n            if constexpr (is_prime_mod) {\n                assert(_v);\n\
    \                return pow(umod() - 2);\n            } else {\n             \
    \   const auto [g, res] = internal::modint::inv_gcd(_v, mod());\n            \
    \    assert(g == 1);\n                return res;\n            }\n        }\n\
    \        friend constexpr mint operator+(const mint& lhs, const mint& rhs) { mint\
    \ res = lhs; res += rhs; return res; }\n        friend constexpr mint operator-(const\
    \ mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }\n  \
    \      friend constexpr mint operator*(const mint& lhs, const mint& rhs) { mint\
    \ res = lhs; res *= rhs; return res; }\n        friend constexpr mint operator/(const\
    \ mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }\n  \
    \      friend constexpr bool operator==(const mint& lhs, const mint& rhs) { return\
    \ lhs._v == rhs._v; }\n        friend constexpr bool operator!=(const mint& lhs,\
    \ const mint& rhs) { return lhs._v != rhs._v; }\n    private:\n        unsigned\
    \ int _v;\n        static constexpr bool is_prime_mod = internal::modint::is_prime(mod());\n\
    \    };\n\n    template <int id>\n    class dynamic_modint {\n        using mint\
    \ = dynamic_modint;\n        using barrett = internal::modint::barrett_K128;\n\
    \n        struct raw_construct {};\n        constexpr dynamic_modint(int v, raw_construct)\
    \ : _v(v) {}\n    public:\n        static int mod() { return bt.umod(); }\n  \
    \      static unsigned int umod() { return bt.umod(); }\n\n        static void\
    \ set_mod(int m) {\n            assert(1 <= m);\n            bt = barrett(m);\n\
    \        }\n        static mint raw(int v) { return dynamic_modint(v, raw_construct{});\
    \ }\n\n        dynamic_modint() : _v(0) {}\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_signed<T>>, std::nullptr_t> = nullptr>\n        dynamic_modint(T v)\
    \ {\n            if (v < 0) {\n                int x = v % mod();\n          \
    \      if (x < 0) x += mod();\n                _v = x;\n            } else _v\
    \ = bt.rem(v);\n        }\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_unsigned<T>>, std::nullptr_t> = nullptr>\n        dynamic_modint(T v)\
    \ : _v(bt.rem(v)) {}\n\n        dynamic_modint(__uint128_t v) : _v(v % umod())\
    \ {}\n        dynamic_modint(__int128_t v) {\n            int x = v % mod();\n\
    \            if (x < 0) x += mod();\n            _v = x;\n        }\n\n      \
    \  unsigned int val() const { return _v; }\n\n        mint& operator++() {\n \
    \           ++_v;\n            if (_v == umod()) _v = 0;\n            return *this;\n\
    \        }\n        mint& operator--() {\n            if (_v == 0) _v = umod();\n\
    \            --_v;\n            return *this;\n        }\n        mint operator++(int)\
    \ { mint x = *this; ++*this; return x; }\n        mint operator--(int) { mint\
    \ x = *this; --*this; return x; }\n\n        mint& operator+=(const mint& rhs)\
    \ {\n            _v += rhs._v;\n            if (_v >= umod()) _v -= umod();\n\
    \            return *this;\n        }\n        mint& operator-=(const mint& rhs)\
    \ {\n            _v -= rhs._v;\n            if (_v >= umod()) _v += umod();\n\
    \            return *this;\n        }\n        mint& operator*=(const mint& rhs)\
    \ {\n            _v = bt.mul(_v, rhs._v);\n            return *this;\n       \
    \ }\n        mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }\n\
    \n        mint pow(long long n) const {\n            assert(0 <= n);\n       \
    \     mint x = *this, r = 1;\n            for (; n; n >>= 1) {\n             \
    \   if (n & 1) r *= x;\n                x *= x;\n            }\n            return\
    \ r;\n        }\n        mint xpow(long long n) const { return n < 0 ? inv().pow(-n)\
    \ : pow(n); }\n        mint inv() const {\n            const auto [g, res] = internal::modint::inv_gcd(_v,\
    \ mod());\n            assert(g == 1);\n            return res;\n        }\n\n\
    \        friend mint operator+(const mint& lhs, const mint& rhs) { mint res =\
    \ lhs; res += rhs; return res; }\n        friend mint operator-(const mint& lhs,\
    \ const mint& rhs) { mint res = lhs; res -= rhs; return res; }\n        friend\
    \ mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs;\
    \ return res; }\n        friend mint operator/(const mint& lhs, const mint& rhs)\
    \ { mint res = lhs; res /= rhs; return res; }\n        friend bool operator==(const\
    \ mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }\n        friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }\n\
    \    private:\n        unsigned int _v;\n        static inline barrett bt{ 998244353\
    \ };\n    };\n\n    using modint998244353 = static_modint<998244353>;\n    using\
    \ modint1000000007 = static_modint<1000000007>;\n    using modint = dynamic_modint<-1>;\n\
    \n    template <typename T> struct is_modint : std::false_type {};\n    template\
    \ <int m> struct is_modint<static_modint<m>> : std::true_type {};\n    template\
    \ <int id> struct is_modint<dynamic_modint<id>> : std::true_type {};\n    template\
    \ <typename T> constexpr bool is_modint_v = is_modint<T>::value;\n\n    template\
    \ <typename T> struct is_static_modint : std::false_type {};\n    template <int\
    \ m> struct is_static_modint<static_modint<m>> : std::true_type {};\n    template\
    \ <typename T> constexpr bool is_static_modint_v = is_static_modint<T>::value;\n\
    \n    template <typename T> struct is_dynamic_modint : std::false_type {};\n \
    \   template <int id> struct is_dynamic_modint<dynamic_modint<id>> : std::true_type\
    \ {};\n    template <typename T> constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;\n\
    \n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    std::optional<mint> mod_sqrt(mint a) {\n        const int p\
    \ = mint::mod();\n        if (a == 0) return mint(0);\n        if (p == 2) return\
    \ a;\n        if (a.pow((p - 1) / 2) != 1) return std::nullopt;\n        mint\
    \ b = 1;\n        while (b.pow((p - 1) / 2) == 1) ++b;\n        const int tlz\
    \ = __builtin_ctz(p - 1), q = (p - 1) >> tlz;\n        mint x = a.pow((q + 1)\
    \ / 2);\n        b = b.pow(q);\n        for (int shift = 2; x * x != a; ++shift)\
    \ {\n            mint e = a.inv() * x * x;\n            if (e.pow(1 << (tlz -\
    \ shift)) != 1) x *= b;\n            b *= b;\n        }\n        return x;\n \
    \   }\n\n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    mint sqrt(mint a) { return *mod_sqrt(a); }\n    template <typename\
    \ mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>\n    mint\
    \ log(mint a) { assert(a == 1); return 0; }\n    template <typename mint, std::enable_if_t<is_modint_v<mint>,\
    \ std::nullptr_t> = nullptr>\n    mint exp(mint a) { assert(a == 0); return 1;\
    \ }\n    template <typename mint, typename T, std::enable_if_t<is_modint_v<mint>,\
    \ std::nullptr_t> = nullptr>\n    mint pow(mint a, T b) { return a.xpow(b); }\n\
    \    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    mint inv(mint a) { return a.inv(); }\n\n    template <typename\
    \ mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>\n    std::istream&\
    \ operator>>(std::istream& is, mint& v) { long long val; is >> val, v = val; return\
    \ is; }\n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    std::ostream& operator<<(std::ostream& os, const mint& v) {\
    \ return os << v.val(); }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MODINT\n#define SUISEN_MODINT\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <limits>\n#include <optional>\n#include <iostream>\n\nnamespace\
    \ suisen {\n    namespace internal::modint {\n        constexpr long long safe_mod(long\
    \ long x, long long m) { return (x %= m) < 0 ? x + m : x; }\n        constexpr\
    \ long long pow_mod(long long x, long long n, int m) {\n            if (m == 1)\
    \ return 0;\n            unsigned int um = m;\n            unsigned long long\
    \ r = 1, y = safe_mod(x, m);\n            for (; n; n >>= 1) {\n             \
    \   if (n & 1) r = (r * y) % um;\n                y = (y * y) % um;\n        \
    \    }\n            return r;\n        }\n        constexpr bool is_prime(int\
    \ n) {\n            if (n <= 1) return false;\n            if (n == 2 or n ==\
    \ 7 or n == 61) return true;\n            if (n % 2 == 0) return false;\n    \
    \        long long d = n - 1;\n            while (d % 2 == 0) d /= 2;\n      \
    \      constexpr long long bases[3] = { 2, 7, 61 };\n            for (long long\
    \ a : bases) {\n                long long t = d, y = pow_mod(a, t, n);\n     \
    \           for (; t != n - 1 and y != 1 and y != n - 1; t <<= 1) y = y * y %\
    \ n;\n                if (y != n - 1 and t % 2 == 0) return false;\n         \
    \   }\n            return true;\n        }\n        constexpr std::pair<long long,\
    \ long long> inv_gcd(long long a, long long b) {\n            a = safe_mod(a,\
    \ b);\n            if (a == 0) return { b, 0 };\n            long long s = b,\
    \ t = a, m0 = 0, m1 = 1, tmp = 0;\n            while (t) {\n                long\
    \ long u = s / t;\n                s -= t * u, m0 -= m1 * u;\n               \
    \ tmp = s, s = t, t = tmp;\n                tmp = m0, m0 = m1, m1 = tmp;\n   \
    \         }\n            if (m0 < 0) m0 += b / s;\n            return { s, m0\
    \ };\n        }\n        \n        struct barrett_K128 {\n            uint32_t\
    \ M;      // mod\n            __uint128_t L;   // ceil(2^K / M), where K = 128\n\
    \            uint64_t dL, uL; // dL | (uL << 64) = L\n            constexpr barrett_K128(uint32_t\
    \ M) : M(M), L(~__uint128_t(0) / M + 1), dL(L), uL(L >> 64) {}\n            constexpr\
    \ uint32_t umod() const { return M; }\n            // c mod M (correctly works\
    \ for all 0<=c<2^64)\n            template <bool care_M1 = true>\n           \
    \ constexpr uint32_t rem(uint64_t c) const {\n                if constexpr (care_M1)\
    \ if (M == 1) return 0;\n                // uint32_t q = (c * L) >> 128;\n   \
    \             __uint128_t cu = __uint128_t(c) * uL;\n                uint64_t\
    \ cd = (__uint128_t(c) * dL) >> 64;\n                uint32_t r = c - uint64_t(cu\
    \ >> 64) * M;\n                return uint64_t(cu) > ~cd ? r - M : r;\n      \
    \      }\n            // a*b mod M\n            constexpr uint32_t mul(uint32_t\
    \ a, uint32_t b) const { return rem<false>(uint64_t(a) * b); }\n        };\n \
    \   }\n\n    template <int m, std::enable_if_t<(1 <= m), std::nullptr_t> = nullptr>\n\
    \    class static_modint {\n        using mint = static_modint;\n\n        struct\
    \ raw_construct {};\n        constexpr static_modint(int v, raw_construct) : _v(v)\
    \ {}\n    public:\n        static constexpr int mod() { return m; }\n        static\
    \ constexpr unsigned int umod() { return m; }\n\n        static constexpr mint\
    \ raw(int v) { return mint(v, raw_construct{}); }\n\n        constexpr static_modint()\
    \ : _v(0) {}\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_signed<T>>, std::nullptr_t> = nullptr>\n        constexpr static_modint(T\
    \ v) : _v{} {\n            int x = v % mod();\n            if (x < 0) x += mod();\n\
    \            _v = x;\n        }\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_unsigned<T>>, std::nullptr_t> = nullptr>\n        constexpr static_modint(T\
    \ v) : _v(v % umod()) {}\n\n        constexpr unsigned int val() const { return\
    \ _v; }\n\n        constexpr mint& operator++() {\n            ++_v;\n       \
    \     if (_v == umod()) _v = 0;\n            return *this;\n        }\n      \
    \  constexpr mint& operator--() {\n            if (_v == 0) _v = umod();\n   \
    \         --_v;\n            return *this;\n        }\n        constexpr mint\
    \ operator++(int) { mint x = *this; ++*this; return x; }\n        constexpr mint\
    \ operator--(int) { mint x = *this; --*this; return x; }\n\n        constexpr\
    \ mint& operator+=(const mint& rhs) {\n            _v += rhs._v;\n           \
    \ if (_v >= umod()) _v -= umod();\n            return *this;\n        }\n    \
    \    constexpr mint& operator-=(const mint& rhs) {\n            _v -= rhs._v;\n\
    \            if (_v >= umod()) _v += umod();\n            return *this;\n    \
    \    }\n        constexpr mint& operator*=(const mint& rhs) {\n            _v\
    \ = (unsigned long long) _v * rhs._v % umod();\n            return *this;\n  \
    \      }\n        constexpr mint& operator/=(const mint& rhs) { return *this *=\
    \ rhs.inv(); }\n\n        constexpr mint operator+() const { return *this; }\n\
    \        constexpr mint operator-() const { return _v == 0 ? *this : raw(umod()\
    \ - _v); }\n\n        constexpr mint pow(long long n) const {\n            assert(0\
    \ <= n);\n            mint x = *this, r = 1;\n            for (; n; n >>= 1) {\n\
    \                if (n & 1) r *= x;\n                x *= x;\n            }\n\
    \            return r;\n        }\n        constexpr mint xpow(long long n) const\
    \ { return n < 0 ? inv().pow(-n) : pow(n); }\n        constexpr mint inv() const\
    \ {\n            if constexpr (is_prime_mod) {\n                assert(_v);\n\
    \                return pow(umod() - 2);\n            } else {\n             \
    \   const auto [g, res] = internal::modint::inv_gcd(_v, mod());\n            \
    \    assert(g == 1);\n                return res;\n            }\n        }\n\
    \        friend constexpr mint operator+(const mint& lhs, const mint& rhs) { mint\
    \ res = lhs; res += rhs; return res; }\n        friend constexpr mint operator-(const\
    \ mint& lhs, const mint& rhs) { mint res = lhs; res -= rhs; return res; }\n  \
    \      friend constexpr mint operator*(const mint& lhs, const mint& rhs) { mint\
    \ res = lhs; res *= rhs; return res; }\n        friend constexpr mint operator/(const\
    \ mint& lhs, const mint& rhs) { mint res = lhs; res /= rhs; return res; }\n  \
    \      friend constexpr bool operator==(const mint& lhs, const mint& rhs) { return\
    \ lhs._v == rhs._v; }\n        friend constexpr bool operator!=(const mint& lhs,\
    \ const mint& rhs) { return lhs._v != rhs._v; }\n    private:\n        unsigned\
    \ int _v;\n        static constexpr bool is_prime_mod = internal::modint::is_prime(mod());\n\
    \    };\n\n    template <int id>\n    class dynamic_modint {\n        using mint\
    \ = dynamic_modint;\n        using barrett = internal::modint::barrett_K128;\n\
    \n        struct raw_construct {};\n        constexpr dynamic_modint(int v, raw_construct)\
    \ : _v(v) {}\n    public:\n        static int mod() { return bt.umod(); }\n  \
    \      static unsigned int umod() { return bt.umod(); }\n\n        static void\
    \ set_mod(int m) {\n            assert(1 <= m);\n            bt = barrett(m);\n\
    \        }\n        static mint raw(int v) { return dynamic_modint(v, raw_construct{});\
    \ }\n\n        dynamic_modint() : _v(0) {}\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_signed<T>>, std::nullptr_t> = nullptr>\n        dynamic_modint(T v)\
    \ {\n            if (v < 0) {\n                int x = v % mod();\n          \
    \      if (x < 0) x += mod();\n                _v = x;\n            } else _v\
    \ = bt.rem(v);\n        }\n        template <class T, std::enable_if_t<std::conjunction_v<std::is_integral<T>,\
    \ std::is_unsigned<T>>, std::nullptr_t> = nullptr>\n        dynamic_modint(T v)\
    \ : _v(bt.rem(v)) {}\n\n        dynamic_modint(__uint128_t v) : _v(v % umod())\
    \ {}\n        dynamic_modint(__int128_t v) {\n            int x = v % mod();\n\
    \            if (x < 0) x += mod();\n            _v = x;\n        }\n\n      \
    \  unsigned int val() const { return _v; }\n\n        mint& operator++() {\n \
    \           ++_v;\n            if (_v == umod()) _v = 0;\n            return *this;\n\
    \        }\n        mint& operator--() {\n            if (_v == 0) _v = umod();\n\
    \            --_v;\n            return *this;\n        }\n        mint operator++(int)\
    \ { mint x = *this; ++*this; return x; }\n        mint operator--(int) { mint\
    \ x = *this; --*this; return x; }\n\n        mint& operator+=(const mint& rhs)\
    \ {\n            _v += rhs._v;\n            if (_v >= umod()) _v -= umod();\n\
    \            return *this;\n        }\n        mint& operator-=(const mint& rhs)\
    \ {\n            _v -= rhs._v;\n            if (_v >= umod()) _v += umod();\n\
    \            return *this;\n        }\n        mint& operator*=(const mint& rhs)\
    \ {\n            _v = bt.mul(_v, rhs._v);\n            return *this;\n       \
    \ }\n        mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }\n\
    \n        mint pow(long long n) const {\n            assert(0 <= n);\n       \
    \     mint x = *this, r = 1;\n            for (; n; n >>= 1) {\n             \
    \   if (n & 1) r *= x;\n                x *= x;\n            }\n            return\
    \ r;\n        }\n        mint xpow(long long n) const { return n < 0 ? inv().pow(-n)\
    \ : pow(n); }\n        mint inv() const {\n            const auto [g, res] = internal::modint::inv_gcd(_v,\
    \ mod());\n            assert(g == 1);\n            return res;\n        }\n\n\
    \        friend mint operator+(const mint& lhs, const mint& rhs) { mint res =\
    \ lhs; res += rhs; return res; }\n        friend mint operator-(const mint& lhs,\
    \ const mint& rhs) { mint res = lhs; res -= rhs; return res; }\n        friend\
    \ mint operator*(const mint& lhs, const mint& rhs) { mint res = lhs; res *= rhs;\
    \ return res; }\n        friend mint operator/(const mint& lhs, const mint& rhs)\
    \ { mint res = lhs; res /= rhs; return res; }\n        friend bool operator==(const\
    \ mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }\n        friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }\n\
    \    private:\n        unsigned int _v;\n        static inline barrett bt{ 998244353\
    \ };\n    };\n\n    using modint998244353 = static_modint<998244353>;\n    using\
    \ modint1000000007 = static_modint<1000000007>;\n    using modint = dynamic_modint<-1>;\n\
    \n    template <typename T> struct is_modint : std::false_type {};\n    template\
    \ <int m> struct is_modint<static_modint<m>> : std::true_type {};\n    template\
    \ <int id> struct is_modint<dynamic_modint<id>> : std::true_type {};\n    template\
    \ <typename T> constexpr bool is_modint_v = is_modint<T>::value;\n\n    template\
    \ <typename T> struct is_static_modint : std::false_type {};\n    template <int\
    \ m> struct is_static_modint<static_modint<m>> : std::true_type {};\n    template\
    \ <typename T> constexpr bool is_static_modint_v = is_static_modint<T>::value;\n\
    \n    template <typename T> struct is_dynamic_modint : std::false_type {};\n \
    \   template <int id> struct is_dynamic_modint<dynamic_modint<id>> : std::true_type\
    \ {};\n    template <typename T> constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;\n\
    \n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    std::optional<mint> mod_sqrt(mint a) {\n        const int p\
    \ = mint::mod();\n        if (a == 0) return mint(0);\n        if (p == 2) return\
    \ a;\n        if (a.pow((p - 1) / 2) != 1) return std::nullopt;\n        mint\
    \ b = 1;\n        while (b.pow((p - 1) / 2) == 1) ++b;\n        const int tlz\
    \ = __builtin_ctz(p - 1), q = (p - 1) >> tlz;\n        mint x = a.pow((q + 1)\
    \ / 2);\n        b = b.pow(q);\n        for (int shift = 2; x * x != a; ++shift)\
    \ {\n            mint e = a.inv() * x * x;\n            if (e.pow(1 << (tlz -\
    \ shift)) != 1) x *= b;\n            b *= b;\n        }\n        return x;\n \
    \   }\n\n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    mint sqrt(mint a) { return *mod_sqrt(a); }\n    template <typename\
    \ mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>\n    mint\
    \ log(mint a) { assert(a == 1); return 0; }\n    template <typename mint, std::enable_if_t<is_modint_v<mint>,\
    \ std::nullptr_t> = nullptr>\n    mint exp(mint a) { assert(a == 0); return 1;\
    \ }\n    template <typename mint, typename T, std::enable_if_t<is_modint_v<mint>,\
    \ std::nullptr_t> = nullptr>\n    mint pow(mint a, T b) { return a.xpow(b); }\n\
    \    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    mint inv(mint a) { return a.inv(); }\n\n    template <typename\
    \ mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t> = nullptr>\n    std::istream&\
    \ operator>>(std::istream& is, mint& v) { long long val; is >> val, v = val; return\
    \ is; }\n    template <typename mint, std::enable_if_t<is_modint_v<mint>, std::nullptr_t>\
    \ = nullptr>\n    std::ostream& operator<<(std::ostream& os, const mint& v) {\
    \ return os << v.val(); }\n} // namespace suisen\n\n#endif // SUISEN_MODINT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/modint.hpp
  requiredBy: []
  timestamp: '2024-01-30 21:03:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/modint.hpp
layout: document
redirect_from:
- /library/library/number/modint.hpp
- /library/library/number/modint.hpp.html
title: library/number/modint.hpp
---
