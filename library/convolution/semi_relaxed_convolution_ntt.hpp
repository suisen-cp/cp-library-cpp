#ifndef SUISEN_SEMI_RELAXED_CONVOLUTION_NTT
#define SUISEN_SEMI_RELAXED_CONVOLUTION_NTT

#include <atcoder/convolution>

namespace suisen {
    // reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
    template <typename mint>
    struct SemiRelaxedConvolutionNTT {
        SemiRelaxedConvolutionNTT() = default;
        SemiRelaxedConvolutionNTT(const std::vector<mint> &f) : _n(0), _f(f), _g{}, _h{} {}

        mint append(const mint& gi) {
            static constexpr int threshold_log = 6;
            static constexpr int threshold = 1 << threshold_log;
            static constexpr int threshold_mask = threshold - 1;

            ++_n;
            _g.push_back(gi);

            int q = _n >> threshold_log, r = _n & threshold_mask;
            if (r == 0) {
                if (q == (-q & q)) {
                    std::vector<mint> f_fft(_f.begin(), _f.begin() + std::min(int(_f.size()), 2 * _n));
                    f_fft.resize(2 * _n);
                    atcoder::internal::butterfly(f_fft);
                    _f_fft.push_back(std::move(f_fft));
                }
                const int log_q = __builtin_ctz(q);
                const int k = (-q & q) << threshold_log;
                std::vector<mint> g_fft(_g.end() - k, _g.end());
                g_fft.resize(2 * k);
                atcoder::internal::butterfly(g_fft);
                const mint z = mint(2 * k).inv();
                std::vector<mint> h(2 * k);
                for (int i = 0; i < 2 * k; ++i) h[i] = _f_fft[log_q][i] * g_fft[i] * z;
                atcoder::internal::butterfly_inv(h);
                ensure(_n - 1 + k);
                for (int i = 0; i < k; ++i) _h[_n - 1 + i] += h[k - 1 + i];
            } else {
                // naive convolve
                r = std::min(r, int(_f.size()));
                ensure(_n);
                for (int i = 0; i < r; ++i) {
                    _h[_n - 1] += _f[i] * _g[_n - 1 - i];
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

        std::vector<std::vector<mint>> _f_fft;

        void ensure(std::size_t n) {
            if (_h.size() < n) _h.resize(n);
        }
    };
} // namespace suisen


#endif // SUISEN_SEMI_RELAXED_CONVOLUTION_NTT
