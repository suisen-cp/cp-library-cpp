#ifndef SUISEN_BINOMIAL_COEFFICIENT
#define SUISEN_BINOMIAL_COEFFICIENT

#include <algorithm>
#include <cassert>
#include <vector>
#include <atcoder/math>

#include "library/number/barrett_reduction.hpp"

namespace suisen {
    template <typename T>
    std::vector<std::vector<T>> binom_table(int n) {
        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n + 1));
        for (int i = 0; i <= n; ++i) {
            binom[i][0] = binom[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
            }
        }
        return binom;
    }

    struct binom_small_mod {
        struct binom_prime_power_mod {
            static constexpr int MAX_MOD = 20000000;

            uint32_t p, q, m; // m = p ^ q
            std::vector<uint32_t> f, inv_f;

            barrett br_p, br_m;

            binom_prime_power_mod() = default;
            binom_prime_power_mod(uint32_t p, uint32_t q, uint32_t m): p(p), q(q), m(m), f(m), br_p(p), br_m(m) {
                assert(m <= MAX_MOD);
                f[0] = 1;
                for (uint32_t i = 1; i < m; ++i) f[i] = br_p.rem<false>(i) ? br_m.mul<false>(f[i - 1], i) : f[i - 1];
                inv_f = invs(f);
            }

            mutable uint32_t ns[64], ks[64], ls[64];
            int32_t operator()(int64_t n_, int64_t k_) const {
                if (k_ < 0 or k_ > n_) return 0;
                
                uint64_t n = n_, k = k_;

                uint64_t e1 = 0, eq = 0;
                size_t t = 0;
                for (bool borrow = false; n; ++t) {
                    std::tie(n, ns[t]) = br_p.quorem<false>(n);
                    std::tie(k, ks[t]) = br_p.quorem<false>(k);
                    ls[t] = ns[t] - ks[t] - borrow;
                    if (not (borrow = ns[t] < ks[t] + borrow)) continue;
                    ls[t] += p;
                    e1 += 1;
                    eq += t >= q - 1;
                }
                if (e1 >= q) return 0;

                uint32_t res = 1;
                while (e1--) res *= p;
                if ((p != 2 or q < 3) and (eq & 1)) res = m - res;

                uint32_t ni = 0, ki = 0, li = 0;
                for (size_t i = t; i--;) {
                    ni = br_m.rem<false>(uint64_t(p) * ni + ns[i]);
                    ki = br_m.rem<false>(uint64_t(p) * ki + ks[i]);
                    li = br_m.rem<false>(uint64_t(p) * li + ls[i]);
                    res = br_m.mul<false>(br_m.mul<false>(res, f[ni]), br_m.mul<false>(inv_f[ki], inv_f[li]));
                }
                return res;
            }
        private:
            std::vector<uint32_t> invs(const std::vector<uint32_t>& vs) const {
                const uint32_t n = vs.size();

                uint32_t prod = 1;
                for (const uint32_t& v : vs) prod = br_m.mul<false>(prod, v);
                uint32_t inv_prod = atcoder::inv_mod(prod, m);

                std::vector<uint32_t> suf_prod(n + 1);
                suf_prod[n] = 1;
                for (uint32_t i = n; i --> 0;) suf_prod[i] = br_m.mul<false>(suf_prod[i + 1], vs[i]);
                
                std::vector<uint32_t> res(n);
                for (uint32_t i = 0; i < n; ++i) {
                    res[i] = br_m.mul<false>(inv_prod, suf_prod[i + 1]);
                    inv_prod = br_m.mul<false>(inv_prod, vs[i]);
                }
                return res;
            }
        };

        std::vector<binom_prime_power_mod> binoms;

        binom_small_mod() : binom_small_mod(1) {}
        explicit binom_small_mod(int m) {
            for (int p = 2; p <= m; ++p) if (m % p == 0) {
                int q = 0, pq = 1;
                do m /= p, ++q, pq *= p; while (m % p == 0);
                binoms.push_back(binom_prime_power_mod(p, q, pq));
            }
            // decreasing order of p^q
            std::sort(binoms.begin(), binoms.end(), [](const binom_prime_power_mod& b1, const binom_prime_power_mod &b2) { return b1.m > b2.m; });
            std::vector<int> mods;
            for (const auto &b : binoms) mods.push_back(b.m);
            crt = crt_(std::move(mods));
        }

        int operator()(long long n, long long k) const {
            const int l = binoms.size();
            std::vector<int> rs(l);
            for (int i = 0; i < l; ++i) rs[i] = binoms[i](n, k);
            return crt(rs);
        }
    private:
        struct crt_ {
            int n;
            std::vector<int> mods, invs;
            crt_() = default;
            crt_(std::vector<int> &&m) : n(m.size()), mods(std::move(m)), invs(n) {
                if (n) for (int i = 1, mod = mods[0]; i < n; ++i) {
                    assert(mod > mods[i]);
                    invs[i] = atcoder::inv_mod(mod, mods[i]);
                    mod *= mods[i];
                }
            }
            int operator()(const std::vector<int>& r) const {
                if (n == 0) return 0;
                int rem = r[0];
                for (int i = 1, mod = mods[0]; i < n; ++i) {
                    rem += (r[i] - rem) * invs[i] % mods[i] * mod;
                    mod *= mods[i];
                    if (rem < 0) rem += mod;
                }
                return rem;
            }
        } crt;
    };
} // namespace suisen


#endif // SUISEN_BINOMIAL_COEFFICIENT
