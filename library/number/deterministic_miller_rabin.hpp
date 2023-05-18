#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN
#define SUISEN_DETERMINISTIC_MILLER_RABIN

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "library/number/montogomery.hpp"

namespace suisen::miller_rabin {
    namespace internal {
        constexpr uint64_t THRESHOLD_1 = 341531ULL;
        constexpr uint64_t BASE_1[] { 9345883071009581737ULL };

        constexpr uint64_t THRESHOLD_2 = 1050535501ULL;
        constexpr uint64_t BASE_2[] { 336781006125ULL, 9639812373923155ULL };

        constexpr uint64_t THRESHOLD_3 = 350269456337ULL;
        constexpr uint64_t BASE_3[] { 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };

        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;
        constexpr uint64_t BASE_4[] { 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL };

        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;
        constexpr uint64_t BASE_5[] { 2ULL, 4130806001517ULL, 149795463772692060ULL, 186635894390467037ULL, 3967304179347715805ULL };

        constexpr uint64_t THRESHOLD_6 = 585226005592931977ULL;
        constexpr uint64_t BASE_6[] { 2ULL, 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL, 1263739024124850375ULL };

        constexpr uint64_t BASE_7[] { 2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U };

        template <auto BASE, std::size_t SIZE>
        constexpr bool miller_rabin(uint64_t n) {
            if (n == 2 or n == 3 or n == 5 or n == 7) return true;
            if (n <= 1 or n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;

            const uint64_t d = (n - 1) >> __builtin_ctzll(n - 1);

            const Montgomery64 mg{n};

            const uint64_t one = mg.make(1), minus_one = mg.make(n - 1);

            for (std::size_t i = 0; i < SIZE; ++i) {
                uint64_t p = BASE[i] % n;
                if (p == 0) continue;
                uint64_t Y = mg.pow(mg.make(p), d);
                if (Y == one) continue;
                for (uint64_t t = d; Y != minus_one; t <<= 1) {
                    Y = mg.mul(Y, Y);
                    if (Y == one or t == n - 1) return false;
                }
            }
            return true;
        }
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    constexpr bool is_prime(T n) {
        if constexpr (std::is_signed_v<T>) {
            assert(n >= 0);
        }
        const std::make_unsigned_t<T> n_unsigned = n;
        assert(n_unsigned <= std::numeric_limits<uint64_t>::max()); // n < 2^64
        using namespace internal;
        if (n_unsigned < THRESHOLD_1) return miller_rabin<BASE_1, 1>(n_unsigned);
        if (n_unsigned < THRESHOLD_2) return miller_rabin<BASE_2, 2>(n_unsigned);
        if (n_unsigned < THRESHOLD_3) return miller_rabin<BASE_3, 3>(n_unsigned);
        if (n_unsigned < THRESHOLD_4) return miller_rabin<BASE_4, 4>(n_unsigned);
        if (n_unsigned < THRESHOLD_5) return miller_rabin<BASE_5, 5>(n_unsigned);
        if (n_unsigned < THRESHOLD_6) return miller_rabin<BASE_6, 6>(n_unsigned);
        return miller_rabin<BASE_7, 7>(n_unsigned);
    }
} // namespace suisen::miller_rabin

#endif // SUISEN_DETERMINISTIC_MILLER_RABIN
