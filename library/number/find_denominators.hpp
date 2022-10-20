#ifndef SUISEN_FIND_DENOMINATORS
#define SUISEN_FIND_DENOMINATORS

#include <limits>
#include <optional>
#include <type_traits>

namespace suisen {
    /**
     * @brief Calculates { min S, max S }, where S = { x>0 | floor(n/x)=q } in O(1) time.
     * @tparam T integer type
     * @param n numerator
     * @param q quotient (round down)
     * @param max_val upper bound (closed)
     * @return { min S, max S } if S is not empty, otherwise std::nullopt
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::optional<std::pair<T, T>> fld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max()) {
        T l, r;
        if (q >= 0) {
            if (n < 0) return std::nullopt;
            // cld(n + 1, q + 1) <= x <= fld(n, q)
            l = (n + 1 + q) / (q + 1), r = q == 0 ? max_val : std::min(max_val, n / q);
        } else {
            if (n >= 0) return std::nullopt;
            // cld(n, q) <= x <= fld(n + 1, q + 1)
            l = (n + q + 1) / q, r = q == -1 ? max_val : std::min(max_val, (n + 1) / (q + 1));
        }
        if (l <= r) return std::make_pair(l, r);
        else        return std::nullopt;
    }
    /**
     * @brief Calculates { min S, max S }, where S = { x<0 | floor(n/x)=q } in O(1) time.
     * @tparam T integer type
     * @param n numerator
     * @param q quotient (round down)
     * @param min_val lower bound (closed)
     * @return { min S, max S } if S is not empty, otherwise std::nullopt
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::optional<std::pair<T, T>> fld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min()) {
        T l, r;
        if (q >= 0) {
            if (n > 0) return std::nullopt;
            // cld(n, q) <= x <= fld(n - 1, q + 1)
            l = q == 0 ? min_val : std::max(min_val, n / q), r = (n - 1 - q) / (q + 1);
        } else {
            if (n <= 0) return std::nullopt;
            // cld(n - 1, q + 1) <= x <= fld(n, q)
            l = q == -1 ? min_val : std::max(min_val, (n - 1) / (q + 1)), r = (n - q - 1) / q;
        }
        if (l <= r) return std::make_pair(l, r);
        else        return std::nullopt;
    }
    /**
     * @brief Calculates { min S, max S }, where S = { x>0 | ceil(n/x)=q } in O(1) time.
     * @tparam T integer type
     * @param n numerator
     * @param q quotient (round down)
     * @param max_val upper bound (closed)
     * @return { min S, max S } if S is not empty, otherwise std::nullopt
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::optional<std::pair<T, T>> cld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max()) {
        T l, r;
        if (q > 0) {
            if (n <= 0) return std::nullopt;
            l = (n + q - 1) / q, r = q == 1 ? max_val : std::min(max_val, (n - 1) / (q - 1));
        } else {
            if (n > 0) return std::nullopt;
            l = (n - 1 + q) / (q - 1), r = q == 0 ? max_val : std::min(max_val, n / q);
        }
        if (l <= r) return std::make_pair(l, r);
        else        return std::nullopt;
    }
    /**
     * @brief Calculates { min S, max S }, where S = { x<0 | ceil(n/x)=q } in O(1) time.
     * @tparam T integer type
     * @param n numerator
     * @param q quotient (round down)
     * @param min_val lower bound (closed)
     * @return { min S, max S } if S is not empty, otherwise std::nullopt
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::optional<std::pair<T, T>> cld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min()) {
        T l, r;
        if (q > 0) {
            if (n >= 0) return std::nullopt;
            l = q == 1 ? min_val : std::max(min_val, (n + 1) / (q - 1)), r = (n - q + 1) / q;
        } else {
            if (n < 0) return std::nullopt;
            l = q == 0 ? min_val : std::max(min_val, n / q), r = (n + 1 - q) / (q - 1);
        }
        if (l <= r) return std::make_pair(l, r);
        else        return std::nullopt;
    }
} // namespace suisen

#endif // SUISEN_FIND_DENOMINATORS
