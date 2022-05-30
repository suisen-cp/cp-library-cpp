---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/util/subset_iterator/dummy_all_subset.test.cpp
    title: test/src/util/subset_iterator/dummy_all_subset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
    title: test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/subset_iterator.hpp\"\n\n\n\n#ifdef _MSC_VER\n\
    #  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n#include <cstdint>\n\
    #include <iostream>\n#include <limits>\n\nnamespace suisen {\n    struct all_subset\
    \ {\n        struct all_subset_iter {\n            const uint32_t s; uint32_t\
    \ t;\n            constexpr all_subset_iter(uint32_t s) : s(s), t(s + 1) {}\n\
    \            constexpr auto operator*() const { return t; }\n            constexpr\
    \ auto operator++() {}\n            constexpr auto operator!=(std::nullptr_t)\
    \ { return t ? (--t &= s, true) : false; }\n        };\n        uint32_t s;\n\
    \        constexpr all_subset(uint32_t s) : s(s) {}\n        constexpr auto begin()\
    \ { return all_subset_iter(s); }\n        constexpr auto end() { return nullptr;\
    \ }\n    };\n\n    // iterator over T s.t. T is subset of S and |T| = k\n    struct\
    \ all_subset_k {\n        struct all_subset_k_iter {\n            const uint32_t\
    \ n, k, s;\n            uint32_t t;\n            __attribute__((target(\"avx2\"\
    )))\n            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) <<\
    \ _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}\n            __attribute__((target(\"\
    bmi2\")))\n            auto operator*() const { return _pdep_u32(t, s); }\n  \
    \          __attribute__((target(\"bmi\")))\n            auto operator++() {\n\
    \                if (k == 0) {\n                    t = std::numeric_limits<uint32_t>::max();\n\
    \                } else {\n                    uint32_t y = t + (t & -t);\n  \
    \                  t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n                }\n\
    \            }\n            auto operator!=(std::nullptr_t) const { return t <\
    \ n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t s, uint32_t\
    \ k) : s(s), k(k) {}\n        auto begin() { return all_subset_k_iter(s, k); }\n\
    \        auto end() { return nullptr; }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_ITERATOR\n#define SUISEN_SUBSET_ITERATOR\n\n#ifdef\
    \ _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n\nnamespace suisen\
    \ {\n    struct all_subset {\n        struct all_subset_iter {\n            const\
    \ uint32_t s; uint32_t t;\n            constexpr all_subset_iter(uint32_t s) :\
    \ s(s), t(s + 1) {}\n            constexpr auto operator*() const { return t;\
    \ }\n            constexpr auto operator++() {}\n            constexpr auto operator!=(std::nullptr_t)\
    \ { return t ? (--t &= s, true) : false; }\n        };\n        uint32_t s;\n\
    \        constexpr all_subset(uint32_t s) : s(s) {}\n        constexpr auto begin()\
    \ { return all_subset_iter(s); }\n        constexpr auto end() { return nullptr;\
    \ }\n    };\n\n    // iterator over T s.t. T is subset of S and |T| = k\n    struct\
    \ all_subset_k {\n        struct all_subset_k_iter {\n            const uint32_t\
    \ n, k, s;\n            uint32_t t;\n            __attribute__((target(\"avx2\"\
    )))\n            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) <<\
    \ _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}\n            __attribute__((target(\"\
    bmi2\")))\n            auto operator*() const { return _pdep_u32(t, s); }\n  \
    \          __attribute__((target(\"bmi\")))\n            auto operator++() {\n\
    \                if (k == 0) {\n                    t = std::numeric_limits<uint32_t>::max();\n\
    \                } else {\n                    uint32_t y = t + (t & -t);\n  \
    \                  t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n                }\n\
    \            }\n            auto operator!=(std::nullptr_t) const { return t <\
    \ n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t s, uint32_t\
    \ k) : s(s), k(k) {}\n        auto begin() { return all_subset_k_iter(s, k); }\n\
    \        auto end() { return nullptr; }\n    };\n} // namespace suisen\n\n#endif\
    \ // SUISEN_SUBSET_ITERATOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/subset_iterator.hpp
  requiredBy: []
  timestamp: '2022-05-30 16:24:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/util/subset_iterator/dummy_all_subset.test.cpp
  - test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
documentation_of: library/util/subset_iterator.hpp
layout: document
title: Subset Iterator
---
## Subset Iterator

- `all_subset(s)` : $T\subseteq S$ を満たす $T$ を列挙する
- `all_subset_k(s, k)` : $T\subseteq S, \vert T\vert = k$ を満たす $T$ を列挙する

## 計算量

$n = \vert S\vert$ とする．

- `all_subset(s)`
  - 前計算 $O(1)$
  - 次の要素の計算 $O(1)$
  - 全体 $O(2 ^ n)$
- `all_subset_k(s, k)`
  - 前計算 $O(\log s)$
  - 次の要素の計算 $O(1)$ (ただし，`popcount` は $O(1)$ で計算できると仮定)
  - 全体 $O({} _ n C _ k)$

## 使い方

```cpp
uint32_t s = 0b1011;
for (uint32_t t : suisen::all_subset(s)) {
    std::cout << t << std::endl;
}
/**
 * 11 (= 1011)
 * 10 (= 1010)
 *  9 (= 1001)
 *  8 (= 1000)
 *  3 (= 0011)
 *  2 (= 0010)
 *  1 (= 0001)
 */

for (uint32_t t : suisen::all_subset_k(s, 2)) {
    std::cout << t << std::endl;
}
/**
 *  3 (= 0011)
 *  9 (= 1001)
 * 10 (= 1010)
 */
```