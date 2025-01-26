#ifndef SUISEN_NUMBER_UTIL
#define SUISEN_NUMBER_UTIL

#include <array>
#include <cassert>
#include <cmath>
#include <numeric>
#include <tuple>
#include <vector>

/**
 * @brief Utilities
*/

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T powi(T a, int b) {
        T res = 1, pow_a = a;
        for (; b; b >>= 1) {
            if (b & 1) res *= pow_a;
            pow_a *= pow_a;
        }
        return res;
    }

    /**
     * @brief Calculates the prime factorization of n in O(√n).
     * @tparam T integer type
     * @param n integer to factorize
     * @return vector of { prime, exponent }. It is guaranteed that prime is ascending.
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
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
     * @brief Enumerates divisors of n from its prime-factorized form in O(# of divisors of n) time.
     * @tparam T integer type
     * @param factorized a prime-factorized form of n (a vector of { prime, exponent })
     * @return vector of divisors (NOT sorted)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
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
     * @brief Enumerates divisors of n in O(√n) time.
     * @tparam T integer type
     * @param n
     * @return vector of divisors (NOT sorted)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<T> divisors(T n) {
        return divisors(factorize(n));
    }
    /**
     * @brief Calculates the divisors for i=1,...,n in O(n log n) time.
     * @param n upper bound (closed)
     * @return 2-dim vector a of length n+1, where a[i] is the vector of divisors of i.
     */
    std::vector<std::vector<int>> divisors_table(int n) {
        std::vector<std::vector<int>> divs(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; j += i) divs[j].push_back(i);
        }
        return divs;
    }

    /**
     * @brief Calculates φ(n) from its prime-factorized form in O(log n).
     * @tparam T integer type
     * @param factorized a prime-factorized form of n (a vector of { prime, exponent })
     * @return φ(n)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T totient(const std::vector<std::pair<T, int>>& factorized) {
        T res = 1;
        for (const auto& [p, c] : factorized) res *= (p - 1) * powi(p, c - 1);
        return res;
    }
    /**
     * @brief Calculates φ(n) in O(√n).
     * @tparam T integer type
     * @param n
     * @return φ(n)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T totient(T n) {
        return totient(factorize(n));
    }
    /**
     * @brief Calculates φ(i) for i=1,...,n.
     * @param n upper bound (closed)
     * @return vector a of length n+1, where a[i]=φ(i) for i=1,...,n
     */
    std::vector<int> totient_table(int n) {
        std::vector<int> res(n + 1);
        for (int i = 0; i <= n; ++i) res[i] = (i & 1) == 0 ? i >> 1 : i;
        for (int p = 3; p <= n; p += 2) {
            if (res[p] != p) continue;
            for (int q = p; q <= n; q += p) res[q] /= p, res[q] *= p - 1;
        }
        return res;
    }

    /**
     * @brief Calculates λ(n) from its prime-factorized form in O(log n).
     * @tparam T integer type
     * @param factorized a prime-factorized form of n (a vector of { prime, exponent })
     * @return λ(n)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T carmichael(const std::vector<std::pair<T, int>>& factorized) {
        T res = 1;
        for (const auto& [p, c] : factorized) {
            res = std::lcm(res, ((p - 1) * powi(p, c - 1)) >> (p == 2 and c >= 3));
        }
        return res;
    }
    /**
     * @brief Calculates λ(n) in O(√n).
     * @tparam T integer type
     * @param n
     * @return λ(n)
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    T carmichael(T n) {
        return carmichael(factorize(n));
    }
} // namespace suisen

#endif // SUISEN_NUMBER_UTIL
