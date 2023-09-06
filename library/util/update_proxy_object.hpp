#ifndef SUISEN_UPDATE_PROXY_OBJECT
#define SUISEN_UPDATE_PROXY_OBJECT

#include "library/type_traits/type_traits.hpp"

namespace suisen {

template <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>> = nullptr>
struct UpdateProxyObject {
    public:
        UpdateProxyObject(T &v, UpdateFunc update) : v(v), update(update) {}
        operator T() const { return v; }
        auto& operator++() && { ++v, update(); return *this; }
        auto& operator--() && { --v, update(); return *this; }
        auto& operator+=(const T &val) && { v += val, update(); return *this; }
        auto& operator-=(const T &val) && { v -= val, update(); return *this; }
        auto& operator*=(const T &val) && { v *= val, update(); return *this; }
        auto& operator/=(const T &val) && { v /= val, update(); return *this; }
        auto& operator%=(const T &val) && { v %= val, update(); return *this; }
        auto& operator =(const T &val) && { v  = val, update(); return *this; }
        auto& operator<<=(const T &val) && { v <<= val, update(); return *this; }
        auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }
        template <typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>
        auto& apply(F f) && { v = f(v), update(); return *this; }
    private:
        T &v;
        UpdateFunc update;
};

} // namespace suisen

#endif // SUISEN_UPDATE_PROXY_OBJECT
