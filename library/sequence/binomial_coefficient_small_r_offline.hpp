#ifndef SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE
#define SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

namespace suisen {
    namespace internal::binom_small_r_offline {
        template <typename mint>
        using Polynomial = std::vector<mint>;

        // g s.t. fg=1 mod x^n
        // O(nlog n)
        template <typename mint>
        Polynomial<mint> inv(Polynomial<mint> f, int n) {
            const int siz_f = f.size();

            Polynomial<mint> f_fft, g_fft;
            Polynomial<mint> g{ f[0].inv() };
            for (int k = 1; k < n; k *= 2) {
                f_fft = Polynomial<mint>(f.begin(), f.begin() + std::min(siz_f, 2 * k));
                g_fft = g;
                f_fft.resize(2 * k);
                g_fft.resize(2 * k);
                atcoder::internal::butterfly(f_fft);
                atcoder::internal::butterfly(g_fft);

                Polynomial<mint> fg(2 * k);
                for (int i = 0; i < 2 * k; ++i) {
                    fg[i] = f_fft[i] * g_fft[i];
                }
                atcoder::internal::butterfly_inv(fg);
                for (int i = 0; i < k; ++i) {
                    fg[i] = std::exchange(fg[k + i], 0);
                }
                atcoder::internal::butterfly(fg);
                for (int i = 0; i < 2 * k; ++i) {
                    fg[i] *= g_fft[i];
                }
                atcoder::internal::butterfly_inv(fg);
                const mint iz = mint(2 * k).inv(), c = -iz * iz;
                g.resize(2 * k);
                for (int i = 0; i < k; ++i) {
                    g[k + i] = fg[i] * c;
                }
            }
            g.resize(n);
            return g;
        }

        // q s.t. qg=f-(f mod g)
        // O(k log k) where k:=|f|+|g|
        template <typename mint>
        Polynomial<mint> poly_div(Polynomial<mint> f, Polynomial<mint> g) {
            while (not f.empty() and f.back() == 0) {
                f.pop_back();
            }
            while (not g.empty() and g.back() == 0) {
                g.pop_back();
            }

            const int deg_f = static_cast<int>(f.size()) - 1, deg_g = static_cast<int>(g.size()) - 1;
            assert(deg_g >= 0);
            if (deg_f < deg_g) {
                return {};
            }

            std::reverse(f.begin(), f.end());
            std::reverse(g.begin(), g.end());
            const int deg_q = deg_f - deg_g;
            Polynomial<mint> q = atcoder::convolution(f, inv(g, deg_q + 1));
            q.resize(deg_q + 1);
            std::reverse(q.begin(), q.end());
            return q;
        }

        // f mod g
        // O(k log k) where k:=|f|+|g|
        template <typename mint>
        Polynomial<mint> poly_mod(Polynomial<mint> f, const Polynomial<mint>& g) {
            Polynomial<mint> q = poly_div(f, g);
            Polynomial<mint> qg = atcoder::convolution(q, g);
            for (std::size_t i = 0; i < std::min(f.size(), qg.size()); ++i) {
                f[i] -= qg[i];
            }
            while (not f.empty() and f.back() == 0) {
                f.pop_back();
            }
            return f;
        }

        // result[i][j] = S1[2^i,j] * (is_signed ? (-1)^(2^i+j) : +1) for 0<=i<t, 0<=j<=2^i
        // O(t*2^t)
        template <bool is_signed, typename mint>
        std::vector<Polynomial<mint>> stirling_number1_doubling(int t) {
            const int n = 1 << t;

            std::vector<mint> fac(n + 1), fac_inv(n + 1);
            fac[0] = 1;
            for (int i = 1; i <= n; ++i) {
                fac[i] = fac[i - 1] * i;
            }
            fac_inv[n] = fac[n].inv();
            for (int i = n; i >= 1; --i) {
                fac_inv[i - 1] = fac_inv[i] * i;
            }

            // S1[i][j] = S1[2^i,j] for 0<=i<t, 0<=j<=2^i
            std::vector<Polynomial<mint>> S1(t);
            S1[0] = { 1, 0 };

            for (int l = 0; l < t - 1; ++l) {
                const int m = 1 << l;
                Polynomial<mint> f(m + 1), g(m + 1);
                mint pow_m = 1;
                for (int i = 0; i <= m; ++i) {
                    f[i] = pow_m * fac_inv[i];
                    g[i] = S1[l][i] * fac[m - i];
                    pow_m *= (is_signed ? -m : +m);
                }
                f = atcoder::convolution(f, g);
                f.resize(m + 1);
                for (int i = 0; i <= m; ++i) {
                    f[i] *= fac_inv[m - i];
                }
                S1[l + 1] = atcoder::convolution(S1[l], f);
            }
            for (auto& S1_i : S1) {
                std::reverse(S1_i.begin(), S1_i.end());
            }
            return S1;
        }

        // O(|xs|*log(t)^2) where t:=min(|f|,|xs|)
        template <typename mint>
        std::vector<mint> multipoint_evaluation(const Polynomial<mint>& f, const std::vector<mint>& xs) {
            const int n = f.size();
            const int m = xs.size();
            if (n == 0) {
                return std::vector<mint>(m, 0);
            }

            auto impl = [&f](const std::vector<mint>& xs) {
                const int n = xs.size();
                std::vector<Polynomial<mint>> seg(2 * n);
                for (int i = 0; i < n; ++i) {
                    seg[n + i] = Polynomial<mint>{ -xs[i], 1 };
                }
                for (int i = n - 1; i > 0; --i) {
                    seg[i] = atcoder::convolution(seg[i * 2], seg[i * 2 + 1]);
                }
                seg[1] = poly_mod(f, seg[1]);
                for (int i = 2; i < 2 * n; ++i) {
                    seg[i] = poly_mod(seg[i / 2], seg[i]);
                }
                std::vector<mint> ys(n);
                for (int i = 0; i < n; ++i) {
                    ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;
                }
                return ys;
            };

            std::vector<mint> ys(m);
            for (int l = 0; l < m; l += n) {
                int r = std::min(m, l + n);
                std::vector<mint> ys_lr = impl(std::vector<mint>(xs.begin() + l, xs.begin() + r));
                std::move(ys_lr.begin(), ys_lr.end(), ys.begin() + l);
            }
            return ys;
        }
    }

    // O(QlogR(log min(Q,R))^2 + RlogR)
    template <typename mint>
    std::vector<mint> binomial_coefficient_small_r_offline(std::vector<std::pair<long long, int>> queries) {
        using namespace internal::binom_small_r_offline;

        const int q = queries.size();
        const int max_r = [&] {
            int max_r = 0;
            for (auto [n, r] : queries) {
                max_r = std::max(max_r, r);
            }
            return max_r;
        }(); // r <= max_r
        const int log_r = [&] {
            int log_r = 0;
            while (1 << log_r <= max_r) {
                ++log_r;
            }
            return log_r;
        }(); // r < 2^(log_r)

        const std::vector<mint> fac_inv = [&] {
            mint fac_max_r = 1;
            for (int i = 1; i <= max_r; ++i) {
                fac_max_r = fac_max_r * i;
            }
            std::vector<mint> fac_inv(max_r + 1);
            fac_inv[max_r] = fac_max_r.inv();
            for (int i = max_r; i >= 1; --i) {
                fac_inv[i - 1] = fac_inv[i] * i;
            }
            return fac_inv;
        }();

        std::vector<mint> ans(q);
        for (int i = 0; i < q; ++i) {
            ans[i] = fac_inv[queries[i].second];
        }

        // O(R log R)
        auto S1 = stirling_number1_doubling<true, mint>(log_r);

        // sum[bit=0,log R] O(Q*bit^2) = O(Q(log R)^3)
        for (int bit = 0; bit < log_r; ++bit) {
            // x (x - 1) (x - 2) ... (x - 2^bit + 1)
            std::vector<mint> xs;
            std::vector<int> ids;

            // O(Q)
            for (int i = 0; i < q; ++i) {
                auto& [n, r] = queries[i];
                if ((r >> bit) & 1) {
                    xs.push_back(n);
                    ids.push_back(i);
                    n -= 1 << bit;
                    r -= 1 << bit;
                }
            }
            const int siz = xs.size();

            // O(min(Q*bit^2, Q(logQ)^2 + bit 2^bit))
            std::vector<mint> ys = multipoint_evaluation<mint>(S1[bit], xs);
            for (int i = 0; i < siz; ++i) {
                ans[ids[i]] *= ys[i];
            }
        }

        return ans;
    }
}

#endif // SUISEN_BINOMIAL_COEFFICIENT_SMALL_R_OFFLINE
