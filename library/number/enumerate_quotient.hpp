#ifndef SUISEN_ENUMERATE_QUOTIENT
#define SUISEN_ENUMERATE_QUOTIENT

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <tuple>
#include <vector>

namespace suisen {
    /**
     * @return #{ d>0 | exists an integer x s.t. floor(n/x)=d }
    */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T quotient_num(const T& n) {
        const T h = sqrtl(n);
        return 2 * h - (h * (h + 1) > n);
    }

    /**
     * @brief Runs f(q) for each q>0 s.t. (there exists an integer x s.t. floor(n/x)=q) in ascending order.
     * @tparam T integer type
     */
    template <typename T, typename Fun,
        std::enable_if_t<std::conjunction_v<std::is_integral<T>, std::is_invocable<Fun, T>>, std::nullptr_t> = nullptr>
    void foreach_quotients(const T &n, Fun &&f) {
        assert(0 <= n);
        if (n == 0) return;
        const int h = sqrtl(n), m = 2 * h - (h == n / h);
        for (int l = 1; l <= h; ++l) f(l);
        if (n < 1LL << 53) { // the size of the fraction part of double is 52=53-1.
            for (int l = h - (m & 1); l >= 1; --l) f(static_cast<T>(static_cast<double>(n) / l));
        } else {
            for (int l = h - (m & 1); l >= 1; --l) f(n / l);
        }
    }
    /**
     * @brief Calculates an ascending vector of S = { d>0 | exists an integer x s.t. floor(n / x) = d } in O(√n) time.
     * @tparam T integer type
     * @return an ascending vector S = { d>0 | exists an integer x s.t. floor(n / x) = d }.
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<T> enumerate_quotients(T n) {
        std::vector<T> q(quotient_num(n));
        auto it = q.begin();
        foreach_quotients(n, [&it](const T& v) { *it++ = v; });
        return q;
    }

    /**
     * @brief Calculates vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in O(√n) time.
     * @tparam T integer type
     * @return vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q }.
     * It is guaranteed that l, r is ascending and q is descending.
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<std::tuple<T, T, T>> quotient_ranges(T n) {
        assert(0 <= n);
        const std::vector<T> qs = enumerate_quotients(n);
        const int m = qs.size();
        std::vector<std::tuple<T, T, T>> res(qs.size());
        for (int i = 0; i < m; ++i) {
            T l = i ? qs[i - 1] + 1 : 1, r = qs[i], q = qs[m - i - 1];
            res[i] = std::make_tuple(l, r, q);
        }
        return res;
    }

    /**
     * @brief Calculates vector of { l = min S, r = max S, (q[0], ..., q[k-1]) }, where S = { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1 } in O(|vs| * Σ√v) time.
     * @tparam Container vector or array
     * @return vector of { l = min S, r = max S, (q[0], ..., q[k-1]) }, where S is { d | floor(vs[i] / d) = q[i] for i = 0,...,k-1 }.
     * It is guaranteed that l, r is ascending and q[i] is descending. 
     */
    template <typename Container, std::enable_if_t<std::is_integral_v<typename Container::value_type>, std::nullptr_t> = nullptr>
    std::vector<std::tuple<typename Container::value_type, typename Container::value_type, Container>> multiple_quotients_ranges(const Container& vs) {
        using T = typename Container::value_type;
        int n = vs.size();
        T max_val = *std::max_element(vs.begin(), vs.end());
        assert(*std::min_element(vs.begin(), vs.end()) >= 0);
        std::vector<std::tuple<T, T, Container>> res;
        for (T l = 1, r = 1; l <= max_val; l = r + 1) {
            Container qs{};
            if constexpr (std::is_same_v<Container, std::vector<T>>) qs.resize(n);
            r = std::numeric_limits<T>::max();
            for (int i = 0; i < n; ++i) {
                qs[i] = vs[i] / l;
                r = std::min(r, qs[i] == 0 ? std::numeric_limits<T>::max() : vs[i] / qs[i]);
            }
            res.emplace_back(l, r, std::move(qs));
        }
        return res;
    }
} // namespace suisen


#endif // SUISEN_ENUMERATE_QUOTIENT
