#ifndef SUISEN_SUBSET_TRANSFORM
#define SUISEN_SUBSET_TRANSFORM

#include "library/transform/kronecker_power.hpp"

namespace suisen::subset_transform {
    namespace internal {
        template <typename T, auto add = default_operator::add<T>>
        void zeta_unit_transform(T &x0, T &x1) {
                                // 1, 0
            x1 = add(x1, x0);   // 1, 1
        }
        template <typename T, auto sub = default_operator::sub<T>>
        void mobius_unit_transform(T &x0, T &x1) {
                                //  1, 0
            x1 = sub(x1, x0);   // -1, 1
        }
    } // namespace internal

    using kronecker_power_transform::kronecker_power_transform;

    template <typename T, auto add = default_operator::add<T>>
    void zeta(std::vector<T> &a) {
        kronecker_power_transform<T, 2, internal::zeta_unit_transform<T, add>>(a);
    }
    template <typename T, auto sub = default_operator::sub<T>>
    void mobius(std::vector<T> &a) {
        kronecker_power_transform<T, 2, internal::mobius_unit_transform<T, sub>>(a);
    }
} // namespace suisen::subset_transform

#endif // SUISEN_SUBSET_TRANSFORM