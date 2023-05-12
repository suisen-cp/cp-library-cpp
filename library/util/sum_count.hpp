#ifndef SUISEN_SUM_COUNT
#define SUISEN_SUM_COUNT

namespace suisen {
    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b=sum)
    template <typename T, typename R = T>
    constexpr R sum_count(T min_a, T max_a, T min_b, T max_b, T sum) {
        // max(min_a, sum - max_b) <= a <= min(max_a, x - min_b)
        return std::max<R>(0, std::min<R>(max_a, sum - min_b) - std::max<R>(min_a, sum - max_b) + 1);
    }

    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<=max_sum)
    template <typename T, typename R = T>
    constexpr R sum_count_leq(T min_a, T max_a, T min_b, T max_b, T max_sum) {
        // count # of (a,b) s.t. 0<=a<=ra and 0<=b<=rb and a+b<=rs
        const R ra = R(max_a) - R(min_a), rb = R(max_b) - R(min_b), rs = R(max_sum) - R(min_a + min_b);
        if (ra < 0 or rb < 0 or rs < 0) {
            return 0;
        }
        const R t = std::max<R>(0, std::min<R>(ra, rs - rb) + 1);
        // Case 1. 0<=a<t  : 0<=b<=rb   <===> a+b<=rs
        // Case 2. t<=a<=ra: 0<=b<=rs-a <===> a+b<=rs
        // fr + ... + (to-1)
        const R fr = rs - std::min<R>(ra, rs) + 1, to = rs - t + 2 /* >= 1 */;
        return t * (rb + 1) + (to - fr) * (fr + to - 1) / 2;
    }

    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<x)
    template <typename T, typename R = T>
    constexpr R sum_count_lt(T min_a, T max_a, T min_b, T max_b, T x) {
        return sum_count_leq(min_a, max_a, min_b, max_b, x - 1);
    }

    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b>=min_sum)
    template <typename T, typename R = T>
    constexpr R sum_count_geq(T min_a, T max_a, T min_b, T max_b, T min_sum) {
        return std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b + 1) - sum_count_lt(min_a, max_a, min_b, max_b, min_sum);
    }

    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b>x)
    template <typename T, typename R = T>
    constexpr R sum_count_gt(T min_a, T max_a, T min_b, T max_b, T x) {
        return std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b + 1) - sum_count_leq(min_a, max_a, min_b, max_b, x);
    }
} // namespace suisen


#endif // SUISEN_SUM_COUNT
