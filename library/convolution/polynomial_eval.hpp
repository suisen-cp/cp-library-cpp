#ifndef SUISEN_APPLY_POLYNOMIAL
#define SUISEN_APPLY_POLYNOMIAL

#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {

template <typename T, template <typename> class Transform, typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>
std::vector<T> polynomial_eval(std::vector<T> &&a, F f) {
    Transform<T>::transform(a);
    for (auto &x : a) x = f(x);
    Transform<T>::inverse_transform(a);
    return a;
}

template <typename T, template <typename> class Transform, typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>
std::vector<T> polynomial_eval(const std::vector<T> &a, F f) {
    return polynomial_eval<T, Transform>(std::vector<T>(a), f);
}

} // namespace suisen


#endif // SUISEN_APPLY_POLYNOMIAL
