#ifndef SUISEN_FACTORIAL_LARGE
#define SUISEN_FACTORIAL_LARGE

#include <cmath>
#include "library/polynomial/multi_point_eval.hpp"
#include "library/polynomial/formal_power_series.hpp"
#include "library/sequence/stirling_number1.hpp"

namespace suisen {
    template <typename mint>
    struct FactorialLarge {
        static constexpr int _p = mint::mod();
        static constexpr int _b = 4000; // or sqrt(_p * log(_p)) ?
        static constexpr int _q = _p / _b;

        FactorialLarge() {
            // f/x = (x+1)(x+2)...(x+b)
            FormalPowerSeries<mint> f = stirling_number1<FormalPowerSeries<mint>>(_b + 1);
            // 0,b,2b,...,(q-1)b
            std::vector<mint> xs(_q);
            for (int i = 0; i < _q; ++i) {
                xs[i] = i * _b;
            }
            // _acc[i] = (ib+1)(ib+2)...(ib+b)
            _acc = multi_point_eval(f >> 1, xs);

            // _acc[i]
            // = \prod_{j=0}^{i-1} ((jb+1)(jb+2)...(jb+b))
            // = (ib)!
            _acc.insert(_acc.begin(), 1);
            for (int i = 1; i < static_cast<int>(_acc.size()); ++i) {
                _acc[i] *= _acc[i - 1];
            }
        }

        mint operator()(long long n) {
            if (_p <= n) return 0;
            const int q = n / _b, r = n % _b;
            // n! = (qb)! * (n-r+1)(n-r+2)...(n)
            mint ans = _acc[q];
            for (int j = 0; j < r; ++j) {
                ans *= mint::raw(n - j);
            }
            return ans;
        }
    private:
        std::vector<mint> _acc;
    };
} // namespace suisen


#endif // SUISEN_FACTORIAL_LARGE
