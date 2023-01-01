#ifndef SUISEN_MODINT_2p61m1
#define SUISEN_MODINT_2p61m1

#include <cassert>
#include <cstdint>

namespace suisen {
    // reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
    struct modint2p61m1 {
        using self = modint2p61m1;

        constexpr modint2p61m1(): v(0) {}
        constexpr modint2p61m1(uint64_t v): v(fast_mod(v)) {}

        static constexpr uint64_t mod() {
            return _mod;
        }

        static constexpr uint64_t fast_mod(uint64_t v) {
            constexpr uint32_t mid = 61;
            constexpr uint64_t mask = (uint64_t(1) << mid) - 1;
            uint64_t u = v >> mid;
            uint64_t d = v & mask;
            uint64_t res = u + d;
            if (res >= _mod) res -= _mod;
            return res;
        }

        constexpr uint64_t val() const {
            return v;
        }

        constexpr self& operator+=(const self& rhs) {
            v += rhs.v;
            if (v >= _mod) v -= _mod;
            return *this;
        }
        constexpr self& operator-=(const self& rhs) {
            if (v < rhs.v) v += _mod;
            v -= rhs.v;
            return *this;
        }
        constexpr self& operator*=(const self& rhs) {
            uint64_t au = v >> mid31;     // < 2^30
            uint64_t ad = v & mask31;     // < 2^31
            uint64_t bu = rhs.v >> mid31; // < 2^30
            uint64_t bd = rhs.v & mask31; // < 2^31

            //   a * b
            // = (au * 2^31 + ad) * (bu * 2^31 + bd)
            // = au * bu * 2^62             # au * bu * 2^62 ≡ au * bu * 2 < 2^61
            // + (au * bd + ad * bu) * 2^31 # m := au * bd + ad * bu
            //                              # m <= 2 * (2^31 - 1) * (2^30 - 1) = 2^62 - 6 * 2^30 + 2
            //                              # m = mu * 2^30 + md (0 <= mu < 2^32, 0 <= md < 2^30)
            //                              # m * 2^31 ≡ mu + md * 2^31 < 2^61 + 2^31
            // + ad * bd                    # ad * bd <= (2^31 - 1) ** 2 = 2^62 - 2^32 + 1 < 2^62 - 2^31
            // ≡ au * bu * 2 + mu + md * 2^31 + ad * bd < 2^63

            uint64_t m = au * bd + ad * bu;
            uint64_t mu = m >> mid30;
            uint64_t md = m & mask30;

            v = fast_mod((au * bu << 1) + mu + (md << 31) + ad * bd);
            return *this;
        }

        constexpr friend self operator+(const self& l, const self& r) { return self(l) += r; }
        constexpr friend self operator-(const self& l, const self& r) { return self(l) -= r; }
        constexpr friend self operator*(const self& l, const self& r) { return self(l) *= r; }
        constexpr friend bool operator==(const self& l, const self& r) { return l.v == r.v; }

        constexpr self pow(long long b) const {
            assert(b >= 0);
            self x = 1, p = *this;
            for (; b; b >>= 1) {
                if (b & 1) x *= p;
                p *= p;
            }
            return x;
        }
        constexpr self inv() const {
            // a ** (p - 2) = a ** (2**61 - 3)
            // 2**61 - 3 = 0001_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1101
            self x = *this, p = *this * *this;
            for (int i = 2; i <= 60; ++i) {
                x *= (p *= p);
            }
            return x;
        }
    private:
        static constexpr uint64_t _mod = (uint64_t(1) << 61) - 1; // 2**61-1 : prime

        static constexpr uint32_t mid31 = 31;
        static constexpr uint64_t mask31 = (uint64_t(1) << 31) - 1;
        static constexpr uint32_t mid30 = 30;
        static constexpr uint64_t mask30 = (uint64_t(1) << mid30) - 1;

        uint64_t v;
    };
} // namespace suisen


#endif // SUISEN_MODINT_2p61m1
