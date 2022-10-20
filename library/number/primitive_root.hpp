#ifndef SUISEN_PRIMITIVE_ROOT
#define SUISEN_PRIMITIVE_ROOT

#include "library/number/order_Z_mZ.hpp"

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T primitive_root(T p) {
        return OrderMod<T>{p}.primitive_root();
    }
} // namespace suisen

#endif // SUISEN_PRIMITIVE_ROOT
