#ifndef SUISEN_ENUMERATE_QUOTIENT
#define SUISEN_ENUMERATE_QUOTIENT

#include <limits>
#include <tuple>
#include <vector>

namespace suisen {
    /**
     * @brief Calculates vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q } in O(√n) time.
     * @tparam T integer type
     * @return vector of { l = min S, r = max S, q }, where S = { d | floor(n / d) = q }.
     * It is guaranteed that l, r is ascending and q is descending.
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<std::tuple<T, T, T>> enumerate_quotients(T n) {
        assert(0 <= n);
        std::vector<std::tuple<T, T, T>> res;
        for (T l = 1, r = 1; l <= n; l = r + 1) {
            T q = n / l;
            res.emplace_back(l, r = n / q, q);
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
    std::vector<std::tuple<typename Container::value_type, typename Container::value_type, Container>> enumerate_multiple_quotients(const Container& vs) {
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
