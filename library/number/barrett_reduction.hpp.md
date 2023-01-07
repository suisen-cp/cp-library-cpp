---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient.hpp
    title: Binomial Coefficient
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
    title: test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/barrett_reduction.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <utility>\n\nnamespace suisen {\n    struct BarrettReduction {\n    \
    \    uint32_t m;\n        uint64_t im;\n        BarrettReduction(uint32_t m) :\
    \ m(m), im(uint64_t(-1) / m + 1) {}\n\n        std::pair<uint64_t, uint32_t> quorem(uint64_t\
    \ n) const {\n            uint64_t q = uint64_t((__uint128_t(n) * im) >> 64);\n\
    \            int64_t r = n - q * m;\n            if (r < 0) --q, r += m;\n   \
    \         return std::make_pair(q, r);\n        }\n        uint32_t quo(uint64_t\
    \ n) const {\n            return quorem(n).first;\n        }\n        uint32_t\
    \ rem(uint64_t n) const {\n            return quorem(n).second;\n        }\n\n\
    \        template <typename Head, typename ...Tails>\n        uint32_t mul(Head\
    \ &&head, Tails &&...tails) const {\n            if constexpr (sizeof...(tails))\
    \ {\n                return rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n\
    \            } else {\n                return head;\n            }\n        }\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BARRETT_REDUCTION\n#define SUISEN_BARRETT_REDUCTION\n\n#include\
    \ <cstdint>\n#include <utility>\n\nnamespace suisen {\n    struct BarrettReduction\
    \ {\n        uint32_t m;\n        uint64_t im;\n        BarrettReduction(uint32_t\
    \ m) : m(m), im(uint64_t(-1) / m + 1) {}\n\n        std::pair<uint64_t, uint32_t>\
    \ quorem(uint64_t n) const {\n            uint64_t q = uint64_t((__uint128_t(n)\
    \ * im) >> 64);\n            int64_t r = n - q * m;\n            if (r < 0) --q,\
    \ r += m;\n            return std::make_pair(q, r);\n        }\n        uint32_t\
    \ quo(uint64_t n) const {\n            return quorem(n).first;\n        }\n  \
    \      uint32_t rem(uint64_t n) const {\n            return quorem(n).second;\n\
    \        }\n\n        template <typename Head, typename ...Tails>\n        uint32_t\
    \ mul(Head &&head, Tails &&...tails) const {\n            if constexpr (sizeof...(tails))\
    \ {\n                return rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n\
    \            } else {\n                return head;\n            }\n        }\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_BARRETT_REDUCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/barrett_reduction.hpp
  requiredBy:
  - library/sequence/binomial_coefficient.hpp
  timestamp: '2023-01-08 00:05:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
documentation_of: library/number/barrett_reduction.hpp
layout: document
redirect_from:
- /library/library/number/barrett_reduction.hpp
- /library/library/number/barrett_reduction.hpp.html
title: library/number/barrett_reduction.hpp
---
