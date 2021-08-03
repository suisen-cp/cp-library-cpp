#ifndef SUISEN_UPDATE_PROXY_OBJECT
#define SUISEN_UPDATE_PROXY_OBJECT

#include "library/type_traits/type_traits.hpp"

namespace suisen {

template <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>>
struct UpdateProxyObject {
    T &v;
    UpdateFunc update;
    UpdateProxyObject(T &v, UpdateFunc update) : v(v), update(update) {}
    operator T() const { return v; }
    auto& operator++() { ++v, update(); return *this; }
    auto& operator--() { --v, update(); return *this; }
    auto& operator+=(const T &val) { v += val, update(); return *this; }
    auto& operator-=(const T &val) { v -= val, update(); return *this; }
    auto& operator*=(const T &val) { v *= val, update(); return *this; }
    auto& operator/=(const T &val) { v /= val, update(); return *this; }
    auto& operator%=(const T &val) { v %= val, update(); return *this; }
    auto& operator =(const T &val) { v  = val, update(); return *this; }
    auto& operator<<=(const T &val) { v <<= val, update(); return *this; }
    auto& operator>>=(const T &val) { v >>= val, update(); return *this; }
};

} // namespace suisen

#endif // SUISEN_UPDATE_PROXY_OBJECT
