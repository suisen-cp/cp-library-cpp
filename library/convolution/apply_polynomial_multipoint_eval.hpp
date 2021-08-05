#ifndef SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL
#define SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL

#include "library/math/multi_point_eval.hpp"
#include "library/type_traits/type_traits.hpp"

namespace suisen {

template <typename mint, template <typename T> class Transform>
std::vector<mint> apply_polynomial(std::vector<mint> &&a, const FPS<mint> &f) {
    Transform<mint>::transform(a);
    a = multi_point_eval(f, a);
    Transform<mint>::inverse_transform(a);
    return a;
}

template <typename mint, template <typename T> class Transform>
std::vector<mint> apply_polynomial(const std::vector<mint> &a, const FPS<mint> &f) {
    return apply_polynomial<mint, Transform>(std::vector<mint>(a), f);
}

} // namespace suisen

#endif // SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL
