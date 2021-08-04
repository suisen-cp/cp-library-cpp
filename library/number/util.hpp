#ifndef SUISEN_NUMBER_UTIL
#define SUISEN_NUMBER_UTIL

#include <algorithm>
#include <array>
#include <cassert>
#include <tuple>
#include <vector>
#include "library/type_traits/type_traits.hpp"

namespace suisen {

// Returns pow(-1, n)
template <typename T>
constexpr inline int pow_m1(T n) {
    return -(n & 1) | 1;
}
// Returns pow(-1, n)
template <>
constexpr inline int pow_m1<bool>(bool n) {
    return -int(n) | 1;
}

// Returns floor(x / y)
template <typename T>
constexpr inline T fld(const T x, const T y) {
    return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) / y;
}
// Returns ceil(x / y)
template <typename T>
constexpr inline T cld(const T x, const T y) {
    return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;
}

/**
 * O(sqrt(n))
 * Returns a vector of { prime, index }. 
 * It is guaranteed that `prime` is ascending.
 */
template <typename T>
std::vector<std::pair<T, int>> factorize(T n) {
    assert(0 < n);
    std::vector<std::pair<T, int>> prime_powers;
    int c2 = 0;
    while ((n & 1) == 0) ++c2, n >>= 1;
    if (c2) prime_powers.emplace_back(2, c2);
    for (T p = 3; p * p <= n; p += 2) {
        int cp = 0;
        while (n % p == 0) n /= p, ++cp;
        if (cp) prime_powers.emplace_back(p, cp);
    }
    if (n > 1) prime_powers.emplace_back(n, 1);
    return prime_powers;
}

/**
 * O(sqrt(n))
 * Returns a vector that contains all divisors of `n` in ascending order.
 */
template <typename T, constraints_t<std::is_integral<T>> = nullptr>
std::vector<T> divisors(T n) {
    assert(0 < n);
    std::vector<T> l, r;
    for (T p = 1; p * p <= n; ++p) {
        if (n % p) continue;
        l.push_back(p);
        if (T q = n / p; p != q) r.push_back(q);
    }
    for (auto it = r.rbegin(); it != r.rend(); ++it) l.push_back(*it);
    return l;
}

/**
 * O(sigma(n))
 * Returns a vector that contains all divisors of `n`.
 * It is NOT guaranteed that the vector is sorted.
 */
template <typename T>
std::vector<T> divisors(const std::vector<std::pair<T, int>> &factorized) {
    std::vector<T> res { 1 };
    for (auto [p, c] : factorized) {
        for (int i = 0, sz = res.size(); i < sz; ++i) {
            T d = res[i];
            for (int j = 0; j < c; ++j) res.push_back(d *= p);
        }
    }
    return res;
}

/**
 * O(sqrt(n)).
 * Returns vector of { l : T, r : T, q : T } s.t. let S be { d | n / d = q }, l = min S and r = max S.
 * It is guaranteed that `l`, `r` is ascending (i.e. `q` is descending).
 */
template <typename T, constraints_t<std::is_integral<T>> = nullptr>
auto enumerate_quotients(T n) {
    assert(0 <= n);
    std::vector<std::tuple<T, T, T>> res;
    for (T l = 1, r = 1; l <= n; l = r + 1) {
        T q = n / l;
        res.emplace_back(l, r = n / q, q);
    }
    return res;
}

/**
 * Template Parameter:
 *  - vector<T> or array<T, N>
 * 
 * Time Complexity: O(|vs| * Sum_{v in vs} sqrt(v))
 * 
 * Returns vector of { l : T, r : T, qs : Container } s.t. let S be { d | vs[i] / d = qs[i] (for all i) }, l = min S and r = max S
 * It is guaranteed that `l`, `r` is ascending (i.e. for all `i`, `q[i]` is descending).
 */
template <typename Container>
std::vector<std::tuple<typename Container::value_type, typename Container::value_type, Container>>
enumerate_multiple_quotients(const Container &vs) {
    using T = typename Container::value_type;
    static_assert(std::is_integral_v<T>);
    int n = vs.size();
    T max_val = *std::max_element(vs.begin(), vs.end());
    assert(*std::min_element(vs.begin(), vs.end()) >= 0);
    std::vector<std::tuple<T, T, Container>> res;
    for (T l = 1, r = 1; l <= max_val; l = r + 1) {
        Container qs;
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

#endif // SUISEN_NUMBER_UTIL
