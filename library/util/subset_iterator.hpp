#ifndef SUISEN_SUBSET_ITERATOR
#define SUISEN_SUBSET_ITERATOR

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include <cstdint>
#include <iostream>
#include <vector>

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
            const uint32_t s;
            uint32_t t, y;
            std::vector<uint32_t> tab;
            all_subset_k_iter(uint32_t s, uint32_t k) : s(s), t(0) {
                for (uint64_t i = 1; i <= s; i <<= 1) if (s & i) tab.push_back(i);
                if (y = tab.size() >= k; y) {
                    for (uint32_t i = 0; i < k; ++i) t |= tab[i];
                    for (auto &e : tab) --e &= s;
                    tab.insert(tab.begin(), 2, 0); // for k = 0, 1
                }
            }
            auto operator*() const { return t; }
            __attribute__((target("popcnt")))
            auto operator++() { y = (t + (~s | (-t & t))) & s, t = y | tab[_mm_popcnt_u32(y ^ t)]; }
            auto operator!=(std::nullptr_t) const { return y != 0; }
        };
        uint32_t s, k;
        all_subset_k(uint32_t s, uint32_t k) : s(s), k(k) {}
        auto begin() { return all_subset_k_iter(s, k); }
        auto end() { return nullptr; }
    };
} // namespace suisen

#endif // SUISEN_SUBSET_ITERATOR
