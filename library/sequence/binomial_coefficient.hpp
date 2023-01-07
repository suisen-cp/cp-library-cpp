#ifndef SUISEN_BINOMIAL_COEFFICIENT
#define SUISEN_BINOMIAL_COEFFICIENT

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

    struct BinomialCoefficient {
        struct BinomialCoefficientPrimePower {
            static constexpr int MAX_MOD = 20000000;

            uint32_t p, q, m; // m = p ^ q
            std::vector<uint32_t> f, inv_f;

            BarrettReduction br_p;
            BarrettReduction br_m;

            BinomialCoefficientPrimePower() = default;
            BinomialCoefficientPrimePower(uint32_t p, uint32_t q, uint32_t m): p(p), q(q), m(m), f(m), br_p(p), br_m(m) {
                assert(m <= MAX_MOD);
                f[0] = 1;
                for (uint32_t i = 1; i < m; ++i) {
                    f[i] = br_p.rem(i) ? br_m.mul(f[i - 1], i) : f[i - 1];
                }
                inv_f = invs(f);
            }

            int32_t operator()(int64_t n_, int64_t k_) const {
                static uint32_t ns[64], ks[64], ls[64];
                if (k_ < 0 or k_ > n_) return 0;
                
                uint64_t n = n_, k = k_, l = n - k;

                uint32_t res = 1;
                uint64_t e1 = 0, eq = 0;
                uint32_t t = 0;
                for (; n; ++t) {
                    std::tie(n, ns[t]) = br_p.quorem(n);
                    std::tie(k, ks[t]) = br_p.quorem(k);
                    std::tie(l, ls[t]) = br_p.quorem(l);
                    e1 += n - k - l;
                    if (t >= q - 1) {
                        eq += n - k - l;
                    }
                }
                if (e1 >= q) {
                    return 0;
                }
                while (e1-- > 0) {
                    res *= p;
                }
                if ((p != 2 or q < 3) and (eq & 1)) {
                    res = m - res;
                }

                uint32_t ni = 0, ki = 0, li = 0;
                for (uint32_t i = t; i --> 0;) {
                    ni = br_m.mul(p, ni) + ns[i];
                    ki = br_m.mul(p, ki) + ks[i];
                    li = br_m.mul(p, li) + ls[i];
                    res = br_m.mul(res, f[ni], inv_f[ki], inv_f[li]);
                }
                return res;
            }
        private:
            std::vector<uint32_t> invs(const std::vector<uint32_t>& vs) const {
                const uint32_t n = vs.size();

                uint32_t p = 1;
                for (const uint32_t& v : vs) {
                    p = br_m.mul(p, v);
                }
                uint32_t ip = atcoder::inv_mod(p, m);

                std::vector<uint32_t> rp(n + 1);
                rp[n] = 1;
                for (uint32_t i = n; i --> 0;) {
                    rp[i] = br_m.mul(rp[i + 1], vs[i]);
                }
                std::vector<uint32_t> res(n);
                for (uint32_t i = 0; i < n; ++i) {
                    res[i] = br_m.mul(ip, rp[i + 1]);
                    ip = br_m.mul(ip, vs[i]);
                }
                return res;
            }
        };

        int l;
        std::vector<BinomialCoefficientPrimePower> binoms;

        BinomialCoefficient(int m) {
            for (int p = 2; p <= m; ++p) {
                if (m % p == 0) {
                    int q = 0, pq = 1;
                    do {
                        m /= p;
                        ++q, pq *= p;
                    } while (m % p == 0);
                    binoms.push_back(BinomialCoefficientPrimePower(p, q, pq));
                }
            }
            l = binoms.size();
        }

        int operator()(long long n, long long k) const {
            std::vector<long long> rs(l), ms(l);
            for (int i = 0; i < l; ++i) {
                rs[i] = binoms[i](n, k);
                ms[i] = binoms[i].m;
            }
            return atcoder::crt(rs, ms).first;
        }
    };
} // namespace suisen


#endif // SUISEN_BINOMIAL_COEFFICIENT
