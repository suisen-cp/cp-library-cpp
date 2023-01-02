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
            static inv_mods<mint> invs;
            f.push_back(fi);
            const int i = g.size();
            if (i == 0) {
                assert(f[i] == 1);
                g.push_back(0);
            } else if (i == 1) {
                g.push_back(f[i]);
            } else {
                g.push_back(f[i] - fg.append((i - 1) * g[i - 1], f[i - 1]) * invs[i]);
            }
            return g.back();
        }
        mint operator[](int i) const {
            return g[i];
        }
    private:
        std::vector<mint> f, g;
        RelaxedConvolution<mint> fg{ internal::fps_relaxed::convolve<mint> };
    };

    template <typename mint>
    struct RelaxedPow {
        RelaxedPow(long long k = 0) : k(k) {}

        mint append(const mint& fi) {
            if (k == 0) {
                return g.emplace_back(g.empty() ? 1 : 0);
            }
            static inv_mods<mint> invs;
            if (is_zero) {
                if (fi == 0) {
                    z = std::min(z + k, 1000000000LL);
                } else {
                    is_zero = false;
                    inv_base = fi.inv();
                }
            }
            if (not is_zero) {
                f.push_back(fi);
            }
            if (index < z) {
                g.push_back(0);
            } else if (index == z) {
                g.push_back(f[0].pow(k));
            } else {
                int i = index - z;
                mint v1 = fg1.append(mint(k - (i - 1)) * g[z + i - 1], f[i]);
                mint v2 = fg2.append(g[z + i - 1], mint(k) * (i - 1) * f[i]);
                g.push_back((v1 + v2) * inv_base * invs[i]);
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
        mint inv_base = 0;

        std::vector<mint> f, g;
        RelaxedConvolution<mint> fg1{ internal::fps_relaxed::convolve<mint> };
        RelaxedConvolution<mint> fg2{ internal::fps_relaxed::convolve<mint> };
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
