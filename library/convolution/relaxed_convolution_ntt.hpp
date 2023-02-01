#ifndef SUISEN_RELAXED_CONVOLUTION_NTT
#define SUISEN_RELAXED_CONVOLUTION_NTT

#include <atcoder/convolution>

namespace suisen {
    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
    template <typename mint>
    struct RelaxedConvolutionNTT {
        RelaxedConvolutionNTT(): _n(0), _f{}, _g{}, _h{} {}

        mint append(const mint& fi, const mint& gi) {
            static constexpr int threshold_log = 6;
            static constexpr int threshold = 1 << threshold_log;
            static constexpr int threshold_mask = threshold - 1;

            ++_n;
            _f.push_back(fi), _g.push_back(gi);

            const int q = _n >> threshold_log, r = _n & threshold_mask;
            if (r == 0) {
                if (q == (-q & q)) {
                    std::vector<mint> f_fft = _f;
                    std::vector<mint> g_fft = _g;
                    f_fft.resize(2 * _n);
                    g_fft.resize(2 * _n);
                    atcoder::internal::butterfly(f_fft);
                    atcoder::internal::butterfly(g_fft);
                    std::vector<mint> h(2 * _n);
                    for (int i = 0; i < 2 * _n; ++i) {
                        h[i] = f_fft[i] * g_fft[i];
                    }
                    atcoder::internal::butterfly_inv(h);
                    ensure(2 * _n);
                    const mint z = mint(2 * _n).inv();
                    for (int i = _n - 1; i < 2 * _n; ++i) {
                        _h[i] += h[i] * z;
                    }
                    _f_fft.push_back(std::move(f_fft));
                    _g_fft.push_back(std::move(g_fft));
                } else {
                    const int log_q = __builtin_ctz(q);
                    const int k = (-q & q) << threshold_log;

                    std::vector<mint> f_fft(_f.end() - k, _f.end());
                    std::vector<mint> g_fft(_g.end() - k, _g.end());
                    f_fft.resize(2 * k);
                    g_fft.resize(2 * k);
                    atcoder::internal::butterfly(f_fft);
                    atcoder::internal::butterfly(g_fft);
                    std::vector<mint> h(2 * k);
                    for (int i = 0; i < 2 * k; ++i) {
                        h[i] = _f_fft[log_q + 1][i] * g_fft[i] + f_fft[i] * _g_fft[log_q + 1][i];
                    }
                    atcoder::internal::butterfly_inv(h);
                    const mint z = mint(2 * k).inv();
                    for (int i = 0; i < k; ++i) {
                        _h[_n - 1 + i] += h[k - 1 + i] * z;
                    }
                }
            } else {
                // naive convolve
                ensure(_n);
                for (int i = 0; i < r; ++i) {
                    _h[_n - 1] += _f[i] * _g[_n - 1 - i];
                }
                if (_n != r) {
                    for (int i = 0; i < r; ++i) {
                        _h[_n - 1] += _f[_n - i - 1] * _g[i];
                    }
                }
            }
            return _h[_n - 1];
        }

        const mint& operator[](int i) const {
            return _h[i];
        }
        std::vector<mint> get() const {
            return _h;
        }

    private:
        int _n;
        std::vector<mint> _f, _g, _h;

        std::vector<std::vector<mint>> _f_fft, _g_fft;

        void ensure(std::size_t n) {
            if (_h.size() < n) _h.resize(n);
        }
    };
} // namespace suisen


#endif // SUISEN_RELAXED_CONVOLUTION_NTT
