#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN
#define SUISEN_DETERMINISTIC_MILLER_RABIN

#include <cassert>
#include <cstdint>
#include <iterator>

#include "library/type_traits/type_traits.hpp"

namespace suisen::miller_rabin {
    namespace internal {
        constexpr uint32_t THRESHOLD_1 = 341531U;
        constexpr uint64_t BASE_1[] { 9345883071009581737ULL };

        constexpr uint32_t THRESHOLD_2 = 1050535501U;
        constexpr uint64_t BASE_2[] { 336781006125ULL, 9639812373923155ULL };

        constexpr uint64_t THRESHOLD_3 = 350269456337ULL;
        constexpr uint64_t BASE_3[] { 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };

        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;
        constexpr uint64_t BASE_4[] { 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL };

        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;
        constexpr uint64_t BASE_5[] { 2ULL, 4130806001517ULL, 149795463772692060ULL, 186635894390467037ULL, 3967304179347715805ULL };

        constexpr uint64_t THRESHOLD_6 = 585226005592931977ULL;
        constexpr uint64_t BASE_6[] { 2ULL, 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL, 1263739024124850375ULL };

        constexpr uint32_t BASE_7[] { 2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U };

        template <auto BASE, std::size_t SIZE, typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
        constexpr bool miller_rabin(T _n) {
            using U = std::make_unsigned_t<T>;
            using M = safely_multipliable_t<U>;

            U n = _n, d = (n - 1) >> __builtin_ctzll(n - 1);

            if (n == 2 or n == 3 or n == 5 or n == 7) return true;
            if (n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;

            for (std::size_t i = 0; i < SIZE; ++i) {
                M y = 1, p = BASE[i] % n;
                if (p == 0) continue;
                for (U d2 = d; d2; d2 >>= 1) {
                    if (d2 & 1) y = y * p % n;
                    p = p * p % n;
                }
                if (y == 1) continue;
                for (U t = d; y != n - 1; t <<= 1) {
                    y = y * y % n;
                    if (y == 1 or t == n - 1) return false;
                }
            }
            return true;
        }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    constexpr bool is_prime(T n) {
        if (n <= 1) return false;
        using U = std::make_unsigned_t<T>;
        U n2 = n;
        using namespace internal;
        if (n2 < THRESHOLD_1) {
            return miller_rabin<BASE_1, 1>(n2);
        } else if (n2 < THRESHOLD_2) {
            return miller_rabin<BASE_2, 2>(n2);
        } else if (n2 < THRESHOLD_3) {
            return miller_rabin<BASE_3, 3>(n2);
        } else if (n2 < THRESHOLD_4) {
            return miller_rabin<BASE_4, 4>(n2);
        } else if (n2 < THRESHOLD_5) {
            return miller_rabin<BASE_5, 5>(n2);
        } else if (n2 < THRESHOLD_6) {
            return miller_rabin<BASE_6, 6>(n2);
        } else {
            return miller_rabin<BASE_7, 7>(n2);
        }
    }
} // namespace suisen::miller_rabin

#endif // SUISEN_DETERMINISTIC_MILLER_RABIN
