#ifndef SUISEN_NUMBER_UTIL
#define SUISEN_NUMBER_UTIL

#include <algorithm>
#include <array>
#include <cassert>
#include <optional>
#include <tuple>
#include <vector>
#include "library/type_traits/type_traits.hpp"

namespace suisen {

    // // Returns pow(-1, n)
    // template <typename T>
    // constexpr inline int pow_m1(T n) {
    //     return -(n & 1) | 1;
    // }
    // // Returns pow(-1, n)
    // template <>
    // constexpr inline int pow_m1<bool>(bool n) {
    //     return -int(n) | 1;
    // }

    // // Returns floor(x / y)
    // template <typename T>
    // constexpr inline T fld(const T x, const T y) {
    //     return (x ^ y) >= 0 ? x / y : (x - (y + pow_m1(y >= 0))) / y;
    // }
    // // Returns ceil(x / y)
    // template <typename T>
    // constexpr inline T cld(const T x, const T y) {
    //     return (x ^ y) <= 0 ? x / y : (x + (y + pow_m1(y >= 0))) / y;
    // }

    /**
     * O(sqrt(n))
     * Returns a vector of { prime, index }.
     * It is guaranteed that `prime` is ascending.
     */
    template <typename T>
    std::vector<std::pair<T, int>> factorize(T n) {
        static constexpr std::array primes{ 2, 3, 5, 7, 11, 13 };
        static constexpr int next_prime = 17;
        static constexpr int siz = std::array{ 1, 2, 8, 48, 480, 5760, 92160 } [primes.size() - 1] ;
        static constexpr int period = [] {
            int res = 1;
            for (auto e : primes) res *= e;
            return res;
        }();
        static constexpr struct S : public std::array<int, siz> {
            constexpr S() {
                for (int i = next_prime, j = 0; i < period + next_prime; i += 2) {
                    bool ok = true;
                    for (int p : primes) ok &= i % p > 0;
                    if (ok) (*this)[j++] = i - next_prime;
                }
            }
        } s{};

        assert(n > 0);
        std::vector<std::pair<T, int>> res;
        auto f = [&res, &n](int p) {
            if (n % p) return;
            int cnt = 0;
            do n /= p, ++cnt; while (n % p == 0);
            res.emplace_back(p, cnt);
        };
        for (int p : primes) f(p);
        for (T b = next_prime; b * b <= n; b += period) {
            for (int offset : s) f(b + offset);
        }
        if (n != 1) res.emplace_back(n, 1);
        return res;
    }

    /**
     * O(sigma(n))
     * Returns a vector that contains all divisors of `n`.
     * It is NOT guaranteed that the vector is sorted.
     */
    template <typename T>
    std::vector<T> divisors(const std::vector<std::pair<T, int>>& factorized) {
        std::vector<T> res{ 1 };
        for (auto [p, c] : factorized) {
            for (int i = 0, sz = res.size(); i < sz; ++i) {
                T d = res[i];
                for (int j = 0; j < c; ++j) res.push_back(d *= p);
            }
        }
        return res;
    }

    /**
     * O(sqrt(n))
     * Returns a vector that contains all divisors of `n`.
     * It is NOT guaranteed that the vector is sorted.
     */
    template <typename T, constraints_t<std::is_integral<T>> = nullptr>
    std::vector<T> divisors(T n) {
        return divisors(factorize(n));
    }

    template <typename T>
    T totient(T n) {
        for (const auto& [p, _] : factorize(n)) n /= p, n *= p - 1;
        return n;
    }
    std::vector<int> totient_table(int n) {
        std::vector<int> res(n + 1);
        for (int i = 0; i <= n; ++i) res[i] = (i & 1) == 0 ? i >> 1 : i;
        for (int p = 3; p * p <= n; p += 2) {
            if (res[p] != p) continue;
            for (int q = p; q <= n; q += p) res[q] /= p, res[q] *= p - 1;
        }
        return res;
    }

    // Returns { l, r } := min_max { x>0 | fld(n,x)=q }.
    template <typename T, constraints_t<std::is_integral<T>> = nullptr>
    std::optional<std::pair<T, T>> same_fld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max()) {
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
    // Returns { l, r } := min_max { x<0 | fld(n,x)=q }.
    template <typename T, constraints_t<std::is_integral<T>> = nullptr>
    std::optional<std::pair<T, T>> same_fld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min()) {
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
    // Returns { l, r } := min_max { x>0 | cld(n,x)=q }.
    template <typename T, constraints_t<std::is_integral<T>> = nullptr>
    std::optional<std::pair<T, T>> same_cld_denominators_positive(T n, T q, T max_val = std::numeric_limits<T>::max()) {
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
    // Returns { l, r } := min_max { x<0 | cld(n,x)=q }.
    template <typename T, constraints_t<std::is_integral<T>> = nullptr>
    std::optional<std::pair<T, T>> same_cld_denominators_negative(T n, T q, T min_val = std::numeric_limits<T>::min()) {
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
        enumerate_multiple_quotients(const Container& vs) {
        using T = typename Container::value_type;
        static_assert(std::is_integral_v<T>);
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

#endif // SUISEN_NUMBER_UTIL
