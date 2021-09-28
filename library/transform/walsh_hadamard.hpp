#ifndef SUISEN_WALSH_HADAMARD_TRANSFORM
#define SUISEN_WALSH_HADAMARD_TRANSFORM

#include "library/transform/kronecker_power.hpp"

namespace suisen::walsh_hadamard {
    namespace internal {
        template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
        void unit_transform(T &x0, T &x1) {
            T y0 = x0, y1 = x1;
            x0 = add(y0, y1);   // 1,  1
            x1 = sub(y0, y1);   // 1, -1
        }
    } // namespace internal

    using kronecker_power_transform::kronecker_power_transform;

    template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
    constexpr auto walsh_hadamard_transform = kronecker_power_transform<T, 2, internal::unit_transform<T, add, sub>>;
    template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto div = default_operator::div<T>, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    void walsh_walsh_hadamard_transform_inv(std::vector<T> &a) {
        walsh_hadamard_transform<T, add, sub>(a);
        const T n { a.size() };
        for (auto &val : a) val = div(val, n);
    }
    template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto mul = default_operator::mul<T>, auto inv = default_operator::inv<T>, std::enable_if_t<std::negation_v<std::is_integral<T>>, std::nullptr_t> = nullptr>
    void walsh_hadamard_transform_inv(std::vector<T> &a) {
        walsh_hadamard_transform<T, add, sub>(a);
        const T n { a.size() };
        const T inv_n = inv(n);
        for (auto &val : a) val = mul(val, inv_n);
    }
} // namespace suisen::walsh_hadamard


#endif // SUISEN_WALSH_HADAMARD_TRANSFORM
