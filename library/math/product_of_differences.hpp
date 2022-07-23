#ifndef SUISEN_PRODUCT_OF_DIFFERNCES
#define SUISEN_PRODUCT_OF_DIFFERNCES

#include <deque>
#include "library/polynomial/multi_point_eval.hpp"

namespace suisen {
    /**
     * O(N(logN)^2)
     * return the vector p of length xs.size() s.t. p[i]=Π[j!=i](x[i]-x[j])
     */
    template <typename FPSType, typename T>
    std::vector<typename FPSType::value_type> product_of_differences(const std::vector<T>& xs) {
        // f(x):=Π_i(x-x[i])
        // => f'(x)=Σ_i Π[j!=i](x-x[j])
        // => f'(x[i])=Π[j!=i](x[i]-x[j])
        const int n = xs.size();
        std::deque<FPSType> dq;
        for (int i = 0; i < n; ++i) dq.push_back(FPSType{ -xs[i], 1 });
        while (dq.size() >= 2) {
            auto f = std::move(dq.front());
            dq.pop_front();
            auto g = std::move(dq.front());
            dq.pop_front();
            dq.push_back(f * g);
        }
        auto f = std::move(dq.front());
        f.diff_inplace();
        return multi_point_eval<FPSType, T>(f, xs);
    }
} // namespace suisen


#endif // SUISEN_PRODUCT_OF_DIFFERNCES
