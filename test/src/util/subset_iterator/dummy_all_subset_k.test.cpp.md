---
data:
  _extendedDependsOn:
  - icon: ':question:'
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
  bundledCode: "#line 1 \"test/src/util/subset_iterator/dummy_all_subset_k.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <iostream>\n\
    \n#line 1 \"library/util/subset_iterator.hpp\"\n\n\n\n#ifdef _MSC_VER\n#  include\
    \ <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n#line 11 \"library/util/subset_iterator.hpp\"\
    \n#include <cstdint>\n#line 13 \"library/util/subset_iterator.hpp\"\n#include\
    \ <limits>\n\nnamespace suisen {\n    struct all_subset {\n        struct all_subset_iter\
    \ {\n            const uint32_t s; uint32_t t;\n            constexpr all_subset_iter(uint32_t\
    \ s) : s(s), t(s + 1) {}\n            constexpr auto operator*() const { return\
    \ t; }\n            constexpr auto operator++() {}\n            constexpr auto\
    \ operator!=(std::nullptr_t) { return t ? (--t &= s, true) : false; }\n      \
    \  };\n        uint32_t s;\n        constexpr all_subset(uint32_t s) : s(s) {}\n\
    \        constexpr auto begin() { return all_subset_iter(s); }\n        constexpr\
    \ auto end() { return nullptr; }\n    };\n\n    // iterator over T s.t. T is subset\
    \ of S and |T| = k\n    struct all_subset_k {\n        struct all_subset_k_iter\
    \ {\n            const uint32_t n, k, s;\n            uint32_t t;\n          \
    \  __attribute__((target(\"avx2\")))\n            all_subset_k_iter(uint32_t s,\
    \ uint32_t k) : n(uint32_t(1) << _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1)\
    \ << k) - 1) {}\n            __attribute__((target(\"bmi2\")))\n            auto\
    \ operator*() const { return _pdep_u32(t, s); }\n            __attribute__((target(\"\
    bmi\")))\n            auto operator++() {\n                if (k == 0) {\n   \
    \                 t = std::numeric_limits<uint32_t>::max();\n                }\
    \ else {\n                    uint32_t y = t + _blsi_u32(t); // t + (-t & t)\n\
    \                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n              \
    \  }\n            }\n            auto operator!=(std::nullptr_t) const { return\
    \ t < n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t\
    \ s, uint32_t k) : s(s), k(k) {\n            assert(s != std::numeric_limits<uint32_t>::max());\n\
    \        }\n        auto begin() { return all_subset_k_iter(s, k); }\n       \
    \ auto end() { return nullptr; }\n    };\n\n    struct all_subset_k_64 {\n   \
    \     struct all_subset_k_iter_64 {\n            const uint64_t n, s;\n      \
    \      const uint32_t k;\n            uint64_t t;\n            __attribute__((target(\"\
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
    \ }\n    };\n} // namespace suisen\n\n\n#line 9 \"test/src/util/subset_iterator/dummy_all_subset_k.test.cpp\"\
    \n\nvoid test_all_subset_k(uint32_t s, uint32_t k) {\n    std::vector<uint32_t>\
    \ expected;\n    if (__builtin_popcount(s) >= k) {\n        for (uint32_t i =\
    \ 0; i <= s; ++i) if ((i & s) == i and __builtin_popcount(i) == k) {\n       \
    \     expected.push_back(i);\n        }\n    }\n\n    std::vector<uint32_t> actual;\n\
    \    for (uint32_t t : suisen::all_subset_k(s, k)) {\n        actual.push_back(t);\n\
    \    }\n\n    std::sort(expected.begin(), expected.end());\n    std::sort(actual.begin(),\
    \ actual.end());\n    assert(expected == actual);\n}\n\nvoid run_test() {\n  \
    \  for (uint32_t s = 0; s < 10000; ++s) for (uint32_t k = 0; k <= 15; ++k) {\n\
    \        test_all_subset_k(s, k);\n    }\n}\n\nvoid perf_test() {\n    const uint32_t\
    \ s = 0b0111'1111'1111'1111'1111'1111'1111'1111;\n    const uint32_t k = 15;\n\
    \n    std::cerr << \"|S| = \" << __builtin_popcount(s) << \", k = \" << k << std::endl;\n\
    \n    auto start = std::chrono::system_clock::now();\n\n    uint64_t cnt = 0;\n\
    \    for (uint32_t t : suisen::all_subset_k(s, k)) ++cnt;\n\n    auto elapsed\
    \ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - start).count();\n\n    std::cerr << \"Elapsed Time : \" << elapsed << \" ms\"\
    \ << std::endl;\n    std::cerr << \"Number of subsets of S with k elements : \"\
    \ << cnt << std::endl;\n}\n\nint main() {\n    run_test();\n    perf_test();\n\
    \    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <iostream>\n\
    \n#include \"library/util/subset_iterator.hpp\"\n\nvoid test_all_subset_k(uint32_t\
    \ s, uint32_t k) {\n    std::vector<uint32_t> expected;\n    if (__builtin_popcount(s)\
    \ >= k) {\n        for (uint32_t i = 0; i <= s; ++i) if ((i & s) == i and __builtin_popcount(i)\
    \ == k) {\n            expected.push_back(i);\n        }\n    }\n\n    std::vector<uint32_t>\
    \ actual;\n    for (uint32_t t : suisen::all_subset_k(s, k)) {\n        actual.push_back(t);\n\
    \    }\n\n    std::sort(expected.begin(), expected.end());\n    std::sort(actual.begin(),\
    \ actual.end());\n    assert(expected == actual);\n}\n\nvoid run_test() {\n  \
    \  for (uint32_t s = 0; s < 10000; ++s) for (uint32_t k = 0; k <= 15; ++k) {\n\
    \        test_all_subset_k(s, k);\n    }\n}\n\nvoid perf_test() {\n    const uint32_t\
    \ s = 0b0111'1111'1111'1111'1111'1111'1111'1111;\n    const uint32_t k = 15;\n\
    \n    std::cerr << \"|S| = \" << __builtin_popcount(s) << \", k = \" << k << std::endl;\n\
    \n    auto start = std::chrono::system_clock::now();\n\n    uint64_t cnt = 0;\n\
    \    for (uint32_t t : suisen::all_subset_k(s, k)) ++cnt;\n\n    auto elapsed\
    \ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - start).count();\n\n    std::cerr << \"Elapsed Time : \" << elapsed << \" ms\"\
    \ << std::endl;\n    std::cerr << \"Number of subsets of S with k elements : \"\
    \ << cnt << std::endl;\n}\n\nint main() {\n    run_test();\n    perf_test();\n\
    \    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/util/subset_iterator.hpp
  isVerificationFile: true
  path: test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
  requiredBy: []
  timestamp: '2022-05-30 16:24:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
layout: document
redirect_from:
- /verify/test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
- /verify/test/src/util/subset_iterator/dummy_all_subset_k.test.cpp.html
title: test/src/util/subset_iterator/dummy_all_subset_k.test.cpp
---
