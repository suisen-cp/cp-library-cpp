#ifndef SUISEN_SUBSET_ITERATOR
#define SUISEN_SUBSET_ITERATOR

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    struct all_subset {
        struct all_subset_iter {
            const T s; T t;
            constexpr all_subset_iter(T s) : s(s), t(s + 1) {}
            constexpr auto operator*() const { return t; }
            constexpr auto operator++() {}
            constexpr auto operator!=(std::nullptr_t) { return t ? (--t &= s, true) : false; }
        };
        T s;
        constexpr all_subset(T s) : s(s) {}
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
                    uint32_t y = t + _blsi_u32(t); // t + (-t & t)
                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));
                }
            }
            auto operator!=(std::nullptr_t) const { return t < n; }
        };
        uint32_t s, k;
        all_subset_k(uint32_t s, uint32_t k) : s(s), k(k) {
            assert(s != std::numeric_limits<uint32_t>::max());
        }
        auto begin() { return all_subset_k_iter(s, k); }
        auto end() { return nullptr; }
    };

    struct all_subset_k_64 {
        struct all_subset_k_iter_64 {
            const uint64_t n, s;
            const uint32_t k;
            uint64_t t;
            __attribute__((target("avx2")))
            all_subset_k_iter_64(uint64_t s, uint32_t k) : n(uint64_t(1) << _mm_popcnt_u64(s)), s(s), k(k), t((uint64_t(1) << k) - 1) {}
            __attribute__((target("bmi2")))
            auto operator*() const { return _pdep_u64(t, s); }
            __attribute__((target("bmi")))
            auto operator++() {
                if (k == 0) {
                    t = std::numeric_limits<uint64_t>::max();
                } else {
                    uint64_t y = t + _blsi_u64(t);
                    t = y | ((y ^ t) >> _tzcnt_u64(t << 2));
                }
            }
            auto operator!=(std::nullptr_t) const { return t < n; }
        };
        uint64_t s;
        uint32_t k;
        all_subset_k_64(uint64_t s, uint32_t k) : s(s), k(k) {
            assert(s != std::numeric_limits<uint64_t>::max());
        }
        auto begin() { return all_subset_k_iter_64(s, k); }
        auto end() { return nullptr; }
    };

    struct all_setbit {
        struct all_setbit_iter {
            uint32_t s;
            all_setbit_iter(uint32_t s) : s(s) {}
            __attribute__((target("bmi")))
            auto operator*() { return _tzcnt_u32(s); }
            __attribute__((target("bmi")))
            auto operator++() { s = __blsr_u32(s); }
            auto operator!=(std::nullptr_t) { return s; }
        };
        uint32_t s;
        all_setbit(uint32_t s) : s(s) {}
        auto begin() { return all_setbit_iter(s); }
        auto end() { return nullptr; }
    };

    struct all_setbit_64 {
        struct all_setbit_iter_64 {
            uint64_t s;
            all_setbit_iter_64(uint64_t s) : s(s) {}
            __attribute__((target("bmi")))
            auto operator*() { return _tzcnt_u64(s); }
            __attribute__((target("bmi")))
            auto operator++() { s = __blsr_u64(s); }
            auto operator!=(std::nullptr_t) { return s; }
        };
        uint64_t s;
        all_setbit_64(uint64_t s) : s(s) {}
        auto begin() { return all_setbit_iter_64(s); }
        auto end() { return nullptr; }
    };
} // namespace suisen

#endif // SUISEN_SUBSET_ITERATOR
