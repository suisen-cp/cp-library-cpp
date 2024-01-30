---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: library/util/step_sum.hpp
    title: Step Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
    title: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/util/step_sum/dummy.test.cpp
    title: test/src/util/step_sum/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <cstdint>\n#include <utility>\n\nnamespace suisen\
    \ {\n    struct barrett {\n        constexpr barrett() : M(1), L(0) {}\n     \
    \   constexpr explicit barrett(uint32_t M) : M(M), L(uint64_t(-1) / M + 1) { assert(M);\
    \ }\n        constexpr int32_t mod() { return M; }\n        constexpr uint32_t\
    \ umod() const { return M; }\n        // floor(x/M) (correctly works for all 0<=x<2^64)\n\
    \        template <bool care_M1 = true> constexpr uint64_t quo(uint64_t x) const\
    \ { return quorem<care_M1>(x).first; }\n        // x%M (correctly works for all\
    \ 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint32_t rem(uint64_t\
    \ x) const { return quorem<care_M1>(x).second; }\n        // { floor(x/M), x%M\
    \ } (correctly works for all 0<=x<2^64)\n        template <bool care_M1 = true>\
    \ constexpr std::pair<uint64_t, uint32_t> quorem(uint64_t x) const {\n       \
    \     if constexpr (care_M1) if (M == 1) return { x, 0 };\n            uint64_t\
    \ q = (__uint128_t(x) * L) >> 64;\n            int32_t r = x - q * M;\n      \
    \      if (r < 0) --q, r += M;\n            return { q, uint32_t(r) };\n     \
    \   }\n        // a*b mod M\n        template <bool care_M1 = true> constexpr\
    \ uint32_t mul(uint32_t a, uint32_t b) const { return rem<care_M1>(uint64_t(a)\
    \ * b); }\n    private:\n        uint32_t M; // mod\n        uint64_t L; // ceil(2^K\
    \ / M), where K = 64 (if M != 1)\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BARRETT_REDUCTION\n#define SUISEN_BARRETT_REDUCTION\n\n#include\
    \ <array>\n#include <cassert>\n#include <cstdint>\n#include <utility>\n\nnamespace\
    \ suisen {\n    struct barrett {\n        constexpr barrett() : M(1), L(0) {}\n\
    \        constexpr explicit barrett(uint32_t M) : M(M), L(uint64_t(-1) / M + 1)\
    \ { assert(M); }\n        constexpr int32_t mod() { return M; }\n        constexpr\
    \ uint32_t umod() const { return M; }\n        // floor(x/M) (correctly works\
    \ for all 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint64_t\
    \ quo(uint64_t x) const { return quorem<care_M1>(x).first; }\n        // x%M (correctly\
    \ works for all 0<=x<2^64)\n        template <bool care_M1 = true> constexpr uint32_t\
    \ rem(uint64_t x) const { return quorem<care_M1>(x).second; }\n        // { floor(x/M),\
    \ x%M } (correctly works for all 0<=x<2^64)\n        template <bool care_M1 =\
    \ true> constexpr std::pair<uint64_t, uint32_t> quorem(uint64_t x) const {\n \
    \           if constexpr (care_M1) if (M == 1) return { x, 0 };\n            uint64_t\
    \ q = (__uint128_t(x) * L) >> 64;\n            int32_t r = x - q * M;\n      \
    \      if (r < 0) --q, r += M;\n            return { q, uint32_t(r) };\n     \
    \   }\n        // a*b mod M\n        template <bool care_M1 = true> constexpr\
    \ uint32_t mul(uint32_t a, uint32_t b) const { return rem<care_M1>(uint64_t(a)\
    \ * b); }\n    private:\n        uint32_t M; // mod\n        uint64_t L; // ceil(2^K\
    \ / M), where K = 64 (if M != 1)\n    };\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_BARRETT_REDUCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/barrett_reduction.hpp
  requiredBy:
  - library/util/step_sum.hpp
  - library/sequence/binomial_coefficient.hpp
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/util/step_sum/dummy.test.cpp
  - test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
documentation_of: library/number/barrett_reduction.hpp
layout: document
title: Barrett Reduction
---
## Barrett Reduction
