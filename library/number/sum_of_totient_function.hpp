#ifndef SUISEN_SUM_OF_TOTIENT_FUNCTION
#define SUISEN_SUM_OF_TOTIENT_FUNCTION

#include <cstdint>
#include <cmath>
#include <numeric>
#include <vector>

namespace suisen {
    // reference: https://yukicoder.me/wiki/sum_totient
    template <typename T>
    struct SumOfTotientFunction {
        SumOfTotientFunction() : SumOfTotientFunction(1) {}
        SumOfTotientFunction(uint64_t n) : _n(n), _sz_s(threshold(_n) + 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l) {
            std::vector<uint32_t> phi(_sz_s);
            std::iota(phi.begin(), phi.end(), 0);
            for (uint32_t p = 2; p < _sz_s; ++p) {
                if (phi[p] != p) continue;
                for (uint32_t q = p; q < _sz_s; q += p) phi[q] = phi[q] / p * (p - 1);
            }
            for (uint32_t i = 1; i < _sz_s; ++i) _dp_s[i] = phi[i] + _dp_s[i - 1];

            for (uint32_t d = _sz_l - 1; d > 0; --d) {
                uint64_t i = _n / d;
                // avoid overflow
                if (i & 1) {
                    _dp_l[d] = (i + 1) / 2, _dp_l[d] *= i;
                } else {
                    _dp_l[d] = i / 2, _dp_l[d] *= i + 1;
                }
                for (uint64_t l = 2; l <= i;) {
                    uint64_t q = i / l, r = i / q;
                    _dp_l[d] -= (q < _sz_s ? _dp_s[q] : _dp_l[d * l]) * (r - l + 1);
                    l = r + 1;
                }
            }
        }

        T operator()(uint64_t denominator = 1) const {
            uint64_t q = _n / denominator;
            return q < _sz_s ? _dp_s[q] : _dp_l[_n / (q + 1) + 1];
        }

    private:
        uint64_t _n;
        uint32_t _sz_s, _sz_l;
        std::vector<T> _dp_s;
        std::vector<T> _dp_l;

        // q = (n / log log n) ^ (2 / 3)
        static uint32_t threshold(uint64_t n) {
            double t = std::cbrt(n / std::max(1., std::log(std::max(1., std::log(n)))));
            return uint32_t(std::max(1., t * t));
        }
    };
} // namespace suisen


#endif // SUISEN_SUM_OF_TOTIENT_FUNCTION
