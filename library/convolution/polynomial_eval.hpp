#ifndef SUISEN_APPLY_POLYNOMIAL
#define SUISEN_APPLY_POLYNOMIAL

#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
    template <typename T, auto transform, auto transform_inv, typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>
    std::vector<T> polynomial_eval(std::vector<T> &&a, F f) {
        transform(a);
        for (auto &x : a) x = f(x);
        transform_inv(a);
        return a;
    }

    template <typename T, auto transform, auto transform_inv, typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>
    std::vector<T> polynomial_eval(const std::vector<T> &a, F f) {
        return polynomial_eval<T, transform, transform_inv>(std::vector<T>(a), f);
    }
} // namespace suisen

#endif // SUISEN_APPLY_POLYNOMIAL
