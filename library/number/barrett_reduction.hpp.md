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
    #include <cstdint>\n#include <utility>\n\nnamespace suisen {\n    struct BarrettReduction\
    \ {\n        uint32_t m;\n        uint64_t im;\n        BarrettReduction() = default;\n\
    \        BarrettReduction(uint32_t m) : m(m), im(uint64_t(0x7fff'ffff'ffff'ffff)\
    \ / m + 1) {}\n\n        // 0 <= n < 2**63\n        std::pair<uint64_t, uint32_t>\
    \ quorem(uint64_t n) const {\n            uint64_t q = uint64_t((__uint128_t(n)\
    \ * im) >> 63);\n            int64_t r = n - q * m;\n            if (r < 0) --q,\
    \ r += m;\n            return std::make_pair(q, r);\n        }\n        // 0 <=\
    \ n < 2**63\n        uint32_t quo(uint64_t n) const {\n            return quorem(n).first;\n\
    \        }\n        // 0 <= n < 2**63\n        uint32_t rem(uint64_t n) const\
    \ {\n            return quorem(n).second;\n        }\n\n        template <typename\
    \ Head, typename ...Tails>\n        uint32_t mul(Head &&head, Tails &&...tails)\
    \ const {\n            if constexpr (sizeof...(tails)) {\n                return\
    \ rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n            } else\
    \ {\n                return head;\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_BARRETT_REDUCTION\n#define SUISEN_BARRETT_REDUCTION\n\n#include\
    \ <array>\n#include <cstdint>\n#include <utility>\n\nnamespace suisen {\n    struct\
    \ BarrettReduction {\n        uint32_t m;\n        uint64_t im;\n        BarrettReduction()\
    \ = default;\n        BarrettReduction(uint32_t m) : m(m), im(uint64_t(0x7fff'ffff'ffff'ffff)\
    \ / m + 1) {}\n\n        // 0 <= n < 2**63\n        std::pair<uint64_t, uint32_t>\
    \ quorem(uint64_t n) const {\n            uint64_t q = uint64_t((__uint128_t(n)\
    \ * im) >> 63);\n            int64_t r = n - q * m;\n            if (r < 0) --q,\
    \ r += m;\n            return std::make_pair(q, r);\n        }\n        // 0 <=\
    \ n < 2**63\n        uint32_t quo(uint64_t n) const {\n            return quorem(n).first;\n\
    \        }\n        // 0 <= n < 2**63\n        uint32_t rem(uint64_t n) const\
    \ {\n            return quorem(n).second;\n        }\n\n        template <typename\
    \ Head, typename ...Tails>\n        uint32_t mul(Head &&head, Tails &&...tails)\
    \ const {\n            if constexpr (sizeof...(tails)) {\n                return\
    \ rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));\n            } else\
    \ {\n                return head;\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_BARRETT_REDUCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/barrett_reduction.hpp
  requiredBy:
  - library/sequence/binomial_coefficient.hpp
  - library/util/step_sum.hpp
  timestamp: '2023-05-11 13:33:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/binomial_coefficient/binomial_coefficient.test.cpp
  - test/src/util/step_sum/dummy.test.cpp
documentation_of: library/number/barrett_reduction.hpp
layout: document
title: Barrett Reduction
---
## Barrett Reduction
