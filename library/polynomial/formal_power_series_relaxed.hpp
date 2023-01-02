#ifndef SUISEN_FPS_RELAXED
#define SUISEN_FPS_RELAXED

#include <atcoder/convolution>
#include "library/math/inv_mods.hpp"
#include "library/convolution/relaxed_convolution.hpp"
#include "library/math/modint_extension.hpp"

namespace suisen {
    namespace internal::fps_relaxed {
        template <typename mint>
        using polynomial_type = typename RelaxedConvolution<mint>::polynomial_type;

        template <typename mint>
        polynomial_type<mint> convolve(const polynomial_type<mint> &f, const polynomial_type<mint> &g) {
            return atcoder::convolution(f, g);
        }
    }
    
    template <typename mint>
    struct RelaxedInv {
        mint append(const mint& fi) {
            const int i = g.size();
            if (i == 0) {
                assert(fi != 0);
                g.push_back(fi.inv());
            } else {
                g.push_back(-g[0] * fg.append(fi, g[i - 1]));
            }
            return g.back();
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        std::vector<mint> g;
        RelaxedConvolution<mint> fg{ internal::fps_relaxed::convolve<mint> };
    };

    template <typename mint>
    struct RelaxedExp {
        mint append(const mint& fi) {
            static inv_mods<mint> invs;
            const int i = g.size();
            if (i == 0) {
                assert(fi == 0);
                g.push_back(1);
            } else {
                g.push_back(df_g.append(i * fi, g[i - 1]) * invs[i]);
            }
            return g.back();
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        std::vector<mint> g;
        RelaxedConvolution<mint> df_g{ internal::fps_relaxed::convolve<mint> };
    };

    template <typename mint>
    struct RelaxedLog {
        mint append(const mint& fi) {
            invf.append(fi);

            static inv_mods<mint> invs;
            const int i = g.size();
            if (i == 0) {
                assert(fi == 1);
                g.push_back(0);
            } else {
                g.push_back(df_invf.append(i * fi, invf[i - 1]) * invs[i]);
            }
            return g.back();
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        std::vector<mint> g;
        RelaxedConvolution<mint> df_invf{ internal::fps_relaxed::convolve<mint> };
        RelaxedInv<mint> invf;
    };

    template <typename mint>
    struct RelaxedPow {
        RelaxedPow(long long k = 0) : k(k) {}

        mint append(const mint& fi) {
            if (k == 0) {
                return g.emplace_back(g.empty() ? 1 : 0);
            }
            if (is_zero) {
                if (fi == 0) {
                    z = std::min(z + k, 1000000000LL);
                } else {
                    is_zero = false;
                    c = fi.pow(k);
                    inv_base = fi.inv();
                }
            }
            if (not is_zero) {
                f.push_back(fi * inv_base);
            }
            if (index < z) {
                g.push_back(0);
            } else {
                g.push_back(c * exp_k_log_f.append(k * log_f.append(f[index - z])));
            }
            ++index;
            return g.back();
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        long long k;
        long long z = 0;
        long long index = 0;
        bool is_zero = true;
        mint c = 0;
        mint inv_base = 0;

        std::vector<mint> f;
        std::vector<mint> g;

        RelaxedLog<mint> log_f;
        RelaxedExp<mint> exp_k_log_f;
    };

    template <typename mint>
    struct RelaxedSqrt {
        std::optional<mint> append(const mint& fi) {
            if (g.empty()) {
                auto opt_g0 = safe_sqrt(fi);
                if (not opt_g0) return std::nullopt;
                mint g0 = *opt_g0;
                c = (2 * g0).inv();
                return g.emplace_back(g0);
            } else if (g.size() == 1) {
                return g.emplace_back(c * fi);
            } else {
                mint gi = c * (fi - gg.append(g.back(), g.back()));
                return g.emplace_back(gi);
            }
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        mint c = 0;
        std::vector<mint> g;
        RelaxedConvolution<mint> gg{ internal::fps_relaxed::convolve<mint> };
    };
} // namespace suisen


#endif // SUISEN_FPS_RELAXED
