#ifndef SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL
#define SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL

#include "library/math/multi_point_eval.hpp"
#include "library/type_traits/type_traits.hpp"

namespace suisen {
    template <typename mint, auto transform, auto transform_inv>
    std::vector<mint> polynomial_eval(std::vector<mint> &&a, const FPS<mint> &f) {
        transform(a);
        a = multi_point_eval(f, a);
        transform_inv(a);
        return a;
    }

    template <typename mint, auto transform, auto transform_inv>
    std::vector<mint> polynomial_eval(const std::vector<mint> &a, const FPS<mint> &f) {
        return polynomial_eval<mint, transform, transform_inv>(std::vector<mint>(a), f);
    }
} // namespace suisen

#endif // SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL
