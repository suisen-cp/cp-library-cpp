#ifndef SUISEN_MULTI_VARIATE_CONVOLUTION_CIRCULAR
#define SUISEN_MULTI_VARIATE_CONVOLUTION_CIRCULAR

#include <atcoder/modint>

#include "library/transform/chirp_z_transform.hpp"
#include "library/convolution/arbitrary_mod_convolution.hpp"

#include "library/number/deterministic_miller_rabin.hpp"
#include "library/number/primitive_root.hpp"
#include "library/number/garner.hpp"

namespace suisen {
    namespace internal {
        template <typename mint, std::enable_if_t<atcoder::internal::is_modint<mint>::value, std::nullptr_t> = nullptr>
        struct multi_variate_convolution_circular {
            multi_variate_convolution_circular() = default;
            multi_variate_convolution_circular(std::vector<int> n) : _d(n.size()), _l(std::reduce(n.begin(), n.end(), 1, std::multiplies<int>())), _n(n), _g(_d), _ig(_d) {
                assert(miller_rabin::is_prime(mint::mod()));
                mint g = primitive_root(mint::mod());
                for (int i = 0; i < _d; ++i) {
                    assert((mint::mod() - 1) % n[i] == 0);
                    _g[i] = g.pow((mint::mod() - 1) / n[i]);
                    _ig[i] = _g[i].inv();
                }
            }

            std::vector<mint> convolution(std::vector<mint> f, std::vector<mint> g) {
                fft(f, false), fft(g, false);
                for (int i = 0; i < _l; ++i) f[i] *= g[i];
                fft(f, true);
                return f;
            }
            std::vector<mint> operator()(const std::vector<mint>& f, const std::vector<mint>& g) {
                return convolution(f, g);
            }
        private:
            int _d, _l;
            std::vector<int> _n;
            std::vector<mint> _g, _ig;

            void fft(std::vector<mint>& f, bool inverse) {
                const auto& g = inverse ? _g : _ig;
                for (int i = 0, block = 1; i < _d; ++i) {
                    std::vector<mint> x(_n[i]);
                    const int nblock = block * _n[i];
                    for (int l = 0; l + nblock <= _l; l += nblock) {
                        for (int start = l; start < l + block; ++start) {
                            if (_n[i] == 2) {
                                mint u = f[start], v = f[start + block];
                                f[start] = u + v;
                                f[start + block] = u - v;
                            } else if (_n[i] == 3) {
                                mint u = f[start], v = f[start + block], w = f[start + block + block];
                                f[start] = u + v + w;
                                f[start + block] = u + (v + w * g[i]) * g[i];
                                f[start + block + block] = u + (w + v * g[i]) * g[i];
                            } else {
                                for (int p = 0; p < _n[i]; ++p) x[p] = f[start + p * block];
                                if (_n[i] <= 100) {
                                    x = internal::chirp_z_transform_naive<mint>(x, 1, g[i], _n[i]);
                                } else {
                                    x = chirp_z_transform<mint>(x, 1, g[i], _n[i], arbitrary_mod_convolution<mint>);
                                }
                                for (int p = 0; p < _n[i]; ++p) f[start + p * block] = x[p];
                            }
                        }
                    }
                    block = nblock;
                }
                if (inverse) {
                    mint iz = mint(f.size()).inv();
                    for (auto& e : f) e *= iz;
                }
            }
        };
    }

    template <typename mint, std::enable_if_t<atcoder::internal::is_modint<mint>::value, std::nullptr_t> = nullptr>
    struct multi_variate_convolution_circular {
    private:
        using mint2 = atcoder::dynamic_modint<102938478>;
    public:
        multi_variate_convolution_circular() = default;
        multi_variate_convolution_circular(std::vector<int> n) : _d(n.size()), _l(std::reduce(n.begin(), n.end(), 1, std::multiplies<int>())), _n(n) {
            const __int128_t max_val = __int128_t(mint::mod() - 1) * (mint::mod() - 1) * _l;

            const int t = std::reduce(n.begin(), n.end(), 1, [](int x, int y) { return std::lcm(x, y); });

            if ((mint::mod() - 1) % t == 0) {
                _mods = { mint::mod() };
            } else {
                __int128_t prod = 1;
                for (int k = 1000000000 / t; k >= 0; --k) if (const int p = k * t + 1; miller_rabin::is_prime(p)) {
                    _mods.push_back(p);
                    prod *= p;
                    if (prod >= max_val) break;
                }
                assert(prod >= max_val);
            }
            const int m = _mods.size();
            _cnvs.resize(m);
            for (int i = 0; i < m; ++i) with_kth_mod(i, [&, this] {
                _cnvs[i] = internal::multi_variate_convolution_circular<mint2>(_n);
            });
        }

        std::vector<mint> convolution(std::vector<mint> f, const std::vector<mint>& g) {
            assert(int(f.size()) == _l and int(g.size()) == _l);
            if (_d == 0) return { f[0] * g[0] };
            // if (_d == 1) return arbitrary_mod_convolution<mint>(f, g);
            if (_l <= 60) return convolution_naive(f, g);
            const int m = _mods.size();
            std::vector res(m, std::vector<int>(_l));
            for (int i = 0; i < m; ++i) with_kth_mod(i, [&, this] {
                std::vector<mint2> f2(_l), g2(_l);
                for (int j = 0; j < _l; ++j) f2[j] = f[j].val(), g2[j] = g[j].val();
                std::vector<mint2> h = _cnvs[i](f2, g2);
                for (int j = 0; j < _l; ++j) res[i][j] = h[j].val();
            });
            std::vector<mint> h(_l);
            for (int j = 0; j < _l; ++j) {
                std::vector<std::pair<int, int>> eq(m);
                for (int i = 0; i < m; ++i) {
                    eq[i] = { res[i][j], _mods[i] };
                }
                h[j] = garner(eq, mint::mod());
            }
            return h;
        }
        std::vector<mint> operator()(const std::vector<mint>& f, const std::vector<mint>& g) {
            return convolution(f, g);
        }

        std::vector<mint> convolution_naive(const std::vector<mint>& f, const std::vector<mint>& g) {
            std::vector<mint> h(_l);
            for (int i = 0; i < _l; ++i) for (int j = 0; j < _l; ++j) {
                int k = 0;
                for (int d = 0, i2 = i, j2 = j, prd = 1; d < _d; ++d) {
                    k += prd * ((i2 + j2) % _n[d]);
                    i2 /= _n[d], j2 /= _n[d], prd *= _n[d];
                }
                h[k] += f[i] * g[j];
            }
            return h;
        }
    private:
        int _d, _l;
        std::vector<int> _n;
        std::vector<int> _mods;
        std::vector<internal::multi_variate_convolution_circular<mint2>> _cnvs;

        template <typename F>
        void with_kth_mod(int k, F&& f) {
            int old_mod = mint2::mod();
            mint2::set_mod(_mods[k]);
            f();
            if (old_mod >= 1) mint2::set_mod(old_mod);
        }
    };
} // namespace suisen


#endif // SUISEN_MULTI_VARIATE_CONVOLUTION_CIRCULAR
