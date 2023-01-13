#ifndef SUISEN_MOD_SQRT
#define SUISEN_MOD_SQRT

#include <optional>
#include <atcoder/math>

namespace suisen {
    namespace internal {
        long long inv_mod64(long long a, long long m) {
            return atcoder::inv_mod(a, m);
        }
        long long pow_mod64(long long a, long long b, long long m) {
            if ((a %= m) < 0) a += m;
            long long res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) {
                    res = __int128_t(res) * pow_a % m;
                }
                pow_a = __int128_t(pow_a) * pow_a % m;
            }
            return res;
        }
        long long mul_mod64(long long a, long long b, long long m) {
            return __int128_t(a) * b % m;
        }
    }

    std::optional<long long> prime_mod_sqrt(long long a, const long long p) {
        using namespace internal;

        if ((a %= p) < 0) a += p;

        if (a == 0) return 0;
        if (p == 2) return a;

        if (pow_mod64(a, (p - 1) / 2, p) != 1) {
            return std::nullopt;
        }

        long long b = 1;
        while (pow_mod64(b, (p - 1) / 2, p) == 1) {
            ++b;
        }

        int tlz = __builtin_ctz(p - 1);
        long long q = (p - 1) >> tlz;

        long long ia = inv_mod64(a, p);

        long long x = pow_mod64(a, (q + 1) / 2, p);
        b = pow_mod64(b, q, p);
        for (int shift = 2;; ++shift) {
            long long x2 = mul_mod64(x, x, p);
            if (x2 == a) {
                return x;
            }
            long long e = mul_mod64(ia, x2, p);
            if (pow_mod64(e, 1 << (tlz - shift), p) != 1) {
                x = mul_mod64(x, b, p);
            }
            b = mul_mod64(b, b, p);
        }
    }

    namespace internal {
        std::optional<long long> prime_power_mod_sqrt(long long a, long long p, int q) {
            std::vector<long long> pq(q + 1);
            pq[0] = 1;
            for (int i = 1; i <= q; ++i) {
                pq[i] = pq[i - 1] * p;
            }
            if ((a %= pq[q]) == 0) return 0;

            int b = 0;
            for (; a % p == 0; a /= p) {
                ++b;
            }
            if (b % 2) {
                return std::nullopt;
            }
            const long long c = pq[b / 2];

            q -= b;

            if (p != 2) {
                // reference: http://aozoragakuen.sakura.ne.jp/suuron/node24.html
                // f(x) = x^2 - a, f'(x) = 2x
                // Lifting from f(x_i)=0 mod p^i to f(x_{i+1})=0 mod p^{i+1}
                auto ox = prime_mod_sqrt(a, p);
                if (not ox) {
                    return std::nullopt;
                }
                long long x = *ox;
                // f'(x_i) != 0
                const long long inv_df_x0 = inv_mod64(2 * x, p);
                for (int i = 1; i < q; ++i) {
                    // Requirements:
                    //      x_{i+1} = x_i + p^i * y for some 0 <= y < p.
                    // Taylor expansion:
                    //      f(x_i + p^i y) = f(x_i) + y p^i f'(x_i) + p^{i+1} * (...)
                    // f(x_i) = 0 (mod p^i) and f'(x_i) = f'(x_0) != 0 (mod p), so
                    //      y = -(f(x_i)/p^i) * f'(x_0)^(-1) (mod p)
                    __int128_t f_x = __int128_t(x) * x - a;
                    long long y = mul_mod64(-(f_x / pq[i]) % p, inv_df_x0, p);
                    if (y < 0) y += p;
                    x += pq[i] * y;
                }
                return c * x;
            } else {
                // p = 2
                if (a % 8 != 1) {
                    return std::nullopt;
                }
                // reference: https://twitter.com/maspy_stars/status/1613931151718244352?s=20&t=lAf7ztW2fb_IZa544lo2xw
                long long x = 1; // or 3
                for (int i = 3; i < q; ++i) {
                    // Requirements:
                    //      x_{i+1} = x_i + 2^{i-1} y for some 0 <= y < 2.
                    // x_i is an odd number, so
                    //      (x_i + 2^{i-1} y)^2 = x_i^2 + y 2^i (mod 2^{i+1}).
                    // Therefore,
                    //      y = (a - x_i^2)/2^i (mod 2).
                    __int128_t f_x = __int128_t(x) * x - a;
                    x |= ((f_x >> i) & 1) << (i - 1);
                }
                return c * x;
            }
        }
    }

    template <typename PrimePowers>
    std::optional<long long> composite_mod_sqrt(long long a, const PrimePowers& factorized) {
        std::vector<long long> rs, ms;
        for (auto [p, q] : factorized) {
            auto x = internal::prime_power_mod_sqrt(a, p, q);
            if (not x) {
                return std::nullopt;
            }
            rs.push_back(*x);
            long long& pq = ms.emplace_back(1);
            for (int i = 0; i < q; ++i) pq *= p;
        }
        return atcoder::crt(rs, ms).first;
    }
} // namespace suisen


#endif // SUISEN_MOD_SQRT
