#ifndef SUISEN_ALIEN
#define SUISEN_ALIEN

#include <type_traits>
#include <utility>

namespace suisen {
    /**
     * @brief evaluates f(x) (f: convex)
     * @param g p -> inf(f(x)-px)
     */
    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<Cost, DP, Cost>, std::nullptr_t> = nullptr>
    Cost alien_convex(int x, Cost min_slope, Cost max_slope, DP g) {
        // x <= max (argmin (f(x)-rx))
        Cost lp = min_slope - 1, rp = max_slope + 1;
        while (rp - lp > 1) {
            Cost p = (lp + rp) / 2;
            // xp: max (argmin f(x)-px) (= min (argmin f(x)-(p+1)x))
            int xp = g(p) - g(p + 1);
            (x <= xp ? rp : lp) = p;
        }
        return g(rp) + Cost(rp) * x;
    }
    /**
     * @brief evaluates f(x) (f: convex)
     * @param g p -> { inf(f(x)-px), min argmin(f(x)-px) }
     */
    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost, int>, DP, Cost>, std::nullptr_t> = nullptr>
    Cost alien_convex(int x, Cost min_slope, Cost max_slope, DP g) {
        Cost lp = min_slope - 1, rp = max_slope + 1;
        while (rp - lp > 1) {
            Cost p = (lp + rp) / 2;
            // g(p).second: min (argmin f(x)-px)
            (g(p).second <= x ? lp : rp) = p;
        }
        return g(lp).first + Cost(lp) * x;
    }

    /**
     * @brief evaluates f(x) (f: concave)
     * @param g p -> sup(f(x)-px)
     */
    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<Cost, DP, Cost>, std::nullptr_t> = nullptr>
    Cost alien_concave(int x, Cost min_slope, Cost max_slope, DP g) {
        // min (argmax f(x)-rx) <= x
        Cost lp = min_slope - 1, rp = max_slope + 1;
        while (rp - lp > 1) {
            Cost p = (lp + rp) / 2;
            // xp: min (argmax f(x)-px) (= max (argmax f(x)-(p+1)x))
            int xp = g(p) - g(p + 1);
            (xp <= x ? rp : lp) = p;
        }
        return g(rp) + Cost(rp) * x;
    }
    /**
     * @brief evaluates f(x) (f: concave)
     * @param g p -> { sup(f(x)-px), max argmax(f(x)-px) }
     */
    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost, int>, DP, Cost>, std::nullptr_t> = nullptr>
    Cost alien_concave(int x, Cost min_slope, Cost max_slope, DP g) {
        // x <= max (argmax f(x)-lx)
        Cost lp = min_slope - 1, rp = max_slope + 1;
        while (rp - lp > 1) {
            Cost p = (lp + rp) / 2;
            // g(p).second: max (argmax f(x)-px)
            (x <= g(p).second ? lp : rp) = p;
        }
        return g(lp).first + Cost(lp) * x;
    }
} // namespace suisen


#endif // SUISEN_ALIEN
