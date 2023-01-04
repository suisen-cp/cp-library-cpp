---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/subset_iterator.hpp
    title: Subset Iterator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/util/subset_iterator/dummy_all_setbit.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <iostream>\n\
    #include <random>\n\n#line 1 \"library/util/subset_iterator.hpp\"\n\n\n\n#ifdef\
    \ _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n\
    #line 11 \"library/util/subset_iterator.hpp\"\n#include <cstdint>\n#line 13 \"\
    library/util/subset_iterator.hpp\"\n#include <limits>\n\nnamespace suisen {\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    struct all_subset {\n        struct all_subset_iter {\n    \
    \        const T s; T t;\n            constexpr all_subset_iter(T s) : s(s), t(s\
    \ + 1) {}\n            constexpr auto operator*() const { return t; }\n      \
    \      constexpr auto operator++() {}\n            constexpr auto operator!=(std::nullptr_t)\
    \ { return t ? (--t &= s, true) : false; }\n        };\n        T s;\n       \
    \ constexpr all_subset(T s) : s(s) {}\n        constexpr auto begin() { return\
    \ all_subset_iter(s); }\n        constexpr auto end() { return nullptr; }\n  \
    \  };\n\n    // iterator over T s.t. T is subset of S and |T| = k\n    struct\
    \ all_subset_k {\n        struct all_subset_k_iter {\n            const uint32_t\
    \ n, k, s;\n            uint32_t t;\n            __attribute__((target(\"avx2\"\
    )))\n            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) <<\
    \ _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}\n            __attribute__((target(\"\
    bmi2\")))\n            auto operator*() const { return _pdep_u32(t, s); }\n  \
    \          __attribute__((target(\"bmi\")))\n            auto operator++() {\n\
    \                if (k == 0) {\n                    t = std::numeric_limits<uint32_t>::max();\n\
    \                } else {\n                    uint32_t y = t + _blsi_u32(t);\
    \ // t + (-t & t)\n                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n\
    \                }\n            }\n            auto operator!=(std::nullptr_t)\
    \ const { return t < n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t\
    \ s, uint32_t k) : s(s), k(k) {\n            assert(s != std::numeric_limits<uint32_t>::max());\n\
    \        }\n        static all_subset_k nCk(uint32_t n, uint32_t k) { return all_subset_k((uint32_t(1)\
    \ << n) - 1, k); }\n        auto begin() { return all_subset_k_iter(s, k); }\n\
    \        auto end() { return nullptr; }\n    };\n\n    struct all_subset_k_64\
    \ {\n        struct all_subset_k_iter_64 {\n            const uint64_t n, s;\n\
    \            const uint32_t k;\n            uint64_t t;\n            __attribute__((target(\"\
    avx2\")))\n            all_subset_k_iter_64(uint64_t s, uint32_t k) : n(uint64_t(1)\
    \ << _mm_popcnt_u64(s)), s(s), k(k), t((uint64_t(1) << k) - 1) {}\n          \
    \  __attribute__((target(\"bmi2\")))\n            auto operator*() const { return\
    \ _pdep_u64(t, s); }\n            __attribute__((target(\"bmi\")))\n         \
    \   auto operator++() {\n                if (k == 0) {\n                    t\
    \ = std::numeric_limits<uint64_t>::max();\n                } else {\n        \
    \            uint64_t y = t + _blsi_u64(t);\n                    t = y | ((y ^\
    \ t) >> _tzcnt_u64(t << 2));\n                }\n            }\n            auto\
    \ operator!=(std::nullptr_t) const { return t < n; }\n        };\n        uint64_t\
    \ s;\n        uint32_t k;\n        all_subset_k_64(uint64_t s, uint32_t k) : s(s),\
    \ k(k) {\n            assert(s != std::numeric_limits<uint64_t>::max());\n   \
    \     }\n        auto begin() { return all_subset_k_iter_64(s, k); }\n       \
    \ auto end() { return nullptr; }\n    };\n\n    struct all_setbit {\n        struct\
    \ all_setbit_iter {\n            uint32_t s;\n            all_setbit_iter(uint32_t\
    \ s) : s(s) {}\n            __attribute__((target(\"bmi\")))\n            auto\
    \ operator*() { return _tzcnt_u32(s); }\n            __attribute__((target(\"\
    bmi\")))\n            auto operator++() { s = __blsr_u32(s); }\n            auto\
    \ operator!=(std::nullptr_t) { return s; }\n        };\n        uint32_t s;\n\
    \        all_setbit(uint32_t s) : s(s) {}\n        auto begin() { return all_setbit_iter(s);\
    \ }\n        auto end() { return nullptr; }\n    };\n\n    struct all_setbit_64\
    \ {\n        struct all_setbit_iter_64 {\n            uint64_t s;\n          \
    \  all_setbit_iter_64(uint64_t s) : s(s) {}\n            __attribute__((target(\"\
    bmi\")))\n            auto operator*() { return _tzcnt_u64(s); }\n           \
    \ __attribute__((target(\"bmi\")))\n            auto operator++() { s = __blsr_u64(s);\
    \ }\n            auto operator!=(std::nullptr_t) { return s; }\n        };\n \
    \       uint64_t s;\n        all_setbit_64(uint64_t s) : s(s) {}\n        auto\
    \ begin() { return all_setbit_iter_64(s); }\n        auto end() { return nullptr;\
    \ }\n    };\n} // namespace suisen\n\n\n#line 10 \"test/src/util/subset_iterator/dummy_all_setbit.test.cpp\"\
    \n\nvoid test_all_setbit(uint32_t s) {\n    std::vector<uint8_t> expected;\n \
    \   for (uint8_t i = 0; i < 32; ++i) if ((s >> i) & 1) {\n        expected.push_back(i);\n\
    \    }\n\n    std::vector<uint8_t> actual;\n    for (uint8_t t : suisen::all_setbit(s))\
    \ {\n        actual.push_back(t);\n    }\n\n    std::sort(expected.begin(), expected.end());\n\
    \    std::sort(actual.begin(), actual.end());\n    assert(expected == actual);\n\
    }\n\nvoid test_all_setbit_64(uint64_t s) {\n    std::vector<uint8_t> expected;\n\
    \    for (uint8_t i = 0; i < 64; ++i) if ((s >> i) & 1) {\n        expected.push_back(i);\n\
    \    }\n\n    std::vector<uint8_t> actual;\n    for (uint8_t t : suisen::all_setbit_64(s))\
    \ {\n        actual.push_back(t);\n    }\n\n    std::sort(expected.begin(), expected.end());\n\
    \    std::sort(actual.begin(), actual.end());\n    assert(expected == actual);\n\
    }\n\nvoid run_test() {\n    for (uint32_t s = 0; s < 1000000; ++s) {\n       \
    \ test_all_setbit(s);\n    }\n\n    std::mt19937_64 rng{std::random_device{}()};\n\
    \    for (uint32_t i = 0; i < 1000000; ++i) {\n        uint64_t s = rng();\n \
    \       test_all_setbit_64(s);\n    }\n}\n\nint main() {\n    run_test();\n  \
    \  std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <iostream>\n\
    #include <random>\n\n#include \"library/util/subset_iterator.hpp\"\n\nvoid test_all_setbit(uint32_t\
    \ s) {\n    std::vector<uint8_t> expected;\n    for (uint8_t i = 0; i < 32; ++i)\
    \ if ((s >> i) & 1) {\n        expected.push_back(i);\n    }\n\n    std::vector<uint8_t>\
    \ actual;\n    for (uint8_t t : suisen::all_setbit(s)) {\n        actual.push_back(t);\n\
    \    }\n\n    std::sort(expected.begin(), expected.end());\n    std::sort(actual.begin(),\
    \ actual.end());\n    assert(expected == actual);\n}\n\nvoid test_all_setbit_64(uint64_t\
    \ s) {\n    std::vector<uint8_t> expected;\n    for (uint8_t i = 0; i < 64; ++i)\
    \ if ((s >> i) & 1) {\n        expected.push_back(i);\n    }\n\n    std::vector<uint8_t>\
    \ actual;\n    for (uint8_t t : suisen::all_setbit_64(s)) {\n        actual.push_back(t);\n\
    \    }\n\n    std::sort(expected.begin(), expected.end());\n    std::sort(actual.begin(),\
    \ actual.end());\n    assert(expected == actual);\n}\n\nvoid run_test() {\n  \
    \  for (uint32_t s = 0; s < 1000000; ++s) {\n        test_all_setbit(s);\n   \
    \ }\n\n    std::mt19937_64 rng{std::random_device{}()};\n    for (uint32_t i =\
    \ 0; i < 1000000; ++i) {\n        uint64_t s = rng();\n        test_all_setbit_64(s);\n\
    \    }\n}\n\nint main() {\n    run_test();\n    std::cout << \"Hello World\" <<\
    \ std::endl;\n    return 0;\n}"
  dependsOn:
  - library/util/subset_iterator.hpp
  isVerificationFile: true
  path: test/src/util/subset_iterator/dummy_all_setbit.test.cpp
  requiredBy: []
  timestamp: '2022-08-21 18:23:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/util/subset_iterator/dummy_all_setbit.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/subset_iterator/dummy_all_setbit.test.cpp
- /verify/test/src/util/subset_iterator/dummy_all_setbit.test.cpp.html
title: test/src/util/subset_iterator/dummy_all_setbit.test.cpp
---
