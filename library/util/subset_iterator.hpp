#ifndef SUISEN_SUBSET_ITERATOR
#define SUISEN_SUBSET_ITERATOR

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include <cstdint>
#include <iostream>
#include <limits>

namespace suisen {
    struct all_subset {
        struct all_subset_iter {
            const uint32_t s; uint32_t t;
            constexpr all_subset_iter(uint32_t s) : s(s), t(s + 1) {}
            constexpr auto operator*() const { return t; }
            constexpr auto operator++() {}
            constexpr auto operator!=(std::nullptr_t) { return t ? (--t &= s, true) : false; }
        };
        uint32_t s;
        constexpr all_subset(uint32_t s) : s(s) {}
        constexpr auto begin() { return all_subset_iter(s); }
        constexpr auto end() { return nullptr; }
    };

    // iterator over T s.t. T is subset of S and |T| = k
    struct all_subset_k {
        struct all_subset_k_iter {
            const uint32_t n, k, s;
            uint32_t t;
            __attribute__((target("avx2")))
            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) << _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}
            __attribute__((target("bmi2")))
            auto operator*() const { return _pdep_u32(t, s); }
            __attribute__((target("bmi")))
            auto operator++() {
                if (k == 0) {
                    t = std::numeric_limits<uint32_t>::max();
                } else {
                    uint32_t y = t + (t & -t);
                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));
                }
            }
            auto operator!=(std::nullptr_t) const { return t < n; }
        };
        uint32_t s, k;
        all_subset_k(uint32_t s, uint32_t k) : s(s), k(k) {}
        auto begin() { return all_subset_k_iter(s, k); }
        auto end() { return nullptr; }
    };
} // namespace suisen

#endif // SUISEN_SUBSET_ITERATOR
