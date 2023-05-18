#ifndef SUISEN_FAST_FACTORIZE
#define SUISEN_FAST_FACTORIZE

#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <utility>

#include "library/type_traits/type_traits.hpp"

#include "library/number/deterministic_miller_rabin.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"

namespace suisen::fast_factorize {
    namespace internal {
        template <typename T>
        constexpr int floor_log2(T n) {
            int i = 0;
            while (n) n >>= 1, ++i;
            return i - 1;
        }
        template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        T pollard_rho(T n) {
            using M = safely_multipliable_t<T>;
            const T m = T(1) << (floor_log2(n) / 5);

            static std::mt19937_64 rng{std::random_device{}()};
            std::uniform_int_distribution<T> dist(0, n - 1);

            while (true) {
                T c = dist(rng);
                auto f = [&](T x) -> T { return (M(x) * x + c) % n; };
                T x, y = 2, ys, q = 1, g = 1;
                for (T r = 1; g == 1; r <<= 1) {
                    x = y;
                    for (T i = 0; i < r; ++i) y = f(y);
                    for (T k = 0; k < r and g == 1; k += m) {
                        ys = y;
                        for (T i = 0; i < std::min(m, r - k); ++i) y = f(y), q = M(q) * (x > y ? x - y : y - x) % n;
                        g = std::gcd(q, n);
                    }
                }
                if (g == n) {
                    g = 1;
                    while (g == 1) ys = f(ys), g = std::gcd(x > ys ? x - ys : ys - x, n);
                }
                if (g < n) {
                    if (miller_rabin::is_prime(g)) return g;
                    if (T d = n / g; miller_rabin::is_prime(d)) return d;
                    return pollard_rho(g);
                }
            }
        }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    std::vector<std::pair<T, int>> factorize(T n) {
        static constexpr int threshold = 1000000;
        static Sieve<threshold> sieve;

        std::vector<std::pair<T, int>> res;
        if (n <= threshold) {
            for (auto [p, q] : sieve.factorize(n)) res.emplace_back(p, q);
            return res;
        }

        if ((n & 1) == 0) {
            int q = 0;
            do ++q, n >>= 1; while ((n & 1) == 0);
            res.emplace_back(2, q);
        }
        for (T p = 3; p * p <= n; p += 2) {
            if (p >= 101 and n >= 1 << 20) {
                while (n > 1) {
                    if (miller_rabin::is_prime(n)) {
                        res.emplace_back(std::exchange(n, 1), 1);
                    } else {
                        p = internal::pollard_rho(n);
                        int q = 0;
                        do ++q, n /= p; while (n % p == 0);
                        res.emplace_back(p, q);
                    }
                }
                break;
            }
            if (n % p == 0) {
                int q = 0;
                do ++q, n /= p; while (n % p == 0);
                res.emplace_back(p, q);
            }
        }
        if (n > 1) res.emplace_back(n, 1);
        return res;
    }
} // namespace suisen::fast_factorize

#endif // SUISEN_FAST_FACTORIZE
