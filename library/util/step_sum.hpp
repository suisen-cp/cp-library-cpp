#ifndef SUISEN_STEP_SUM
#define SUISEN_STEP_SUM

#include <vector>

#include "library/number/barrett_reduction.hpp"

namespace suisen {
    template <typename T>
    struct StepSum {
        using value_type = T;

        StepSum() : StepSum(std::vector<value_type>{}, 1) {}
        template <typename Sequence>
        StepSum(const Sequence &a, int step) : _sum(a.begin(), a.end()), _step(step), _n(_sum.size()), _br(_step) {
            for (int i = _step; i < _n; ++i) {
                _sum[i] += _sum[i - _step];
            }
        }
        // sum A_i for i = k (mod step) and i in [l, r)
        value_type sum(int k, int l, int r) const {
            if (r <= k or r <= l or l >= _n) return 0;
            const int t = _br.quo(std::min(_n, r) - 1 - k);
            T ans = _sum[t * _step + k];
            if (l > k) {
                const int s = _br.quo(l - 1 - k);
                ans -= _sum[s * _step + k];
            }
            return ans;
        }
        // sum A_i for i = k (mod step) and i in [l, r)
        value_type operator()(int k, int l, int r) const { return sum(k, l, r); }

        // sum[i] = a[i] + a[i - step] + a[i - 2 * step] + ...
        std::vector<value_type>& data() { return _sum; }
        // sum[i] = a[i] + a[i - step] + a[i - 2 * step] + ...
        const std::vector<value_type>& data() const { return _sum; }
    private:
        std::vector<value_type> _sum;
        int _step, _n;
        BarrettReduction _br;
    };
    template <typename Sequence>
    StepSum(Sequence, int) -> StepSum<std::decay_t<decltype(*std::declval<Sequence>().begin())>>;
} // namespace suisen


#endif // SUISEN_STEP_SUM
