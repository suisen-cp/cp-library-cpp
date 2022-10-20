#ifndef SUISEN_KTH_ROOT_ROUND
#define SUISEN_KTH_ROOT_ROUND

#include <cmath>
#include <type_traits>

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T floor_kth_root(T x, int k) {
        if (k == 1 or x == 0 or x == 1) return x;
        if (k == 2) return ::sqrtl(x);
        if (k >= 64) return 1;
        T res = ::powl(x, ::nextafterl(1 / (long double) k, 0));
        while (::powl(res + 1, k) <= x) ++res;
        return res;
    }
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T ceil_kth_root(T x, int k) {
        T res = floor_kth_root(x, k);
        res += ::powl(res, k) < x;
        return res;
    }
} // namespace suisen


#endif // SUISEN_KTH_ROOT_ROUND
