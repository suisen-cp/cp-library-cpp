---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://yukicoder.me/wiki/sum_totient
  bundledCode: "#line 1 \"library/number/sum_of_mobius_function.hpp\"\n\n\n\n#include\
    \ <cstdint>\n#include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ suisen {\n    // reference: https://yukicoder.me/wiki/sum_totient\n    template\
    \ <typename T>\n    struct SumOfMobiusFunction {\n        SumOfMobiusFunction()\
    \ : SumOfMobiusFunction(1) {}\n        SumOfMobiusFunction(uint64_t n) : _n(n),\
    \ _sz_s(threshold(_n) + 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l)\
    \ {\n            std::vector<int32_t> mpf(_sz_s), mobius(_sz_s, 1);\n        \
    \    for (long long p = 2; p < _sz_s; ++p) {\n                if (mpf[p]) continue;\n\
    \                mpf[p] = p;\n                mobius[p] = -1;\n              \
    \  for (long long q = p * 2; q < _sz_s; q += p) {\n                    if (not\
    \ mpf[q]) mpf[q] = p;\n                    mobius[q] = q % (p * p) ? -mobius[q]\
    \ : 0;\n                }\n            }\n            for (uint32_t i = 1; i <\
    \ _sz_s; ++i) _dp_s[i] = mobius[i] + _dp_s[i - 1];\n\n            for (uint32_t\
    \ d = _sz_l - 1; d > 0; --d) {\n                uint64_t i = _n / d;\n       \
    \         // sum_{i=1,d}\\sum_{j|d}mu(j)=1\n                _dp_l[d] = 1;\n  \
    \              for (uint64_t l = 2; l <= i;) {\n                    uint64_t q\
    \ = i / l, r = i / q;\n                    _dp_l[d] -= (q < _sz_s ? _dp_s[q] :\
    \ _dp_l[d * l]) * (r - l + 1);\n                    l = r + 1;\n             \
    \   }\n            }\n        }\n\n        T operator()(uint64_t denominator =\
    \ 1) const {\n            uint64_t q = _n / denominator;\n            return q\
    \ < _sz_s ? _dp_s[q] : _dp_l[_n / (q + 1) + 1];\n        }\n\n    private:\n \
    \       uint64_t _n;\n        uint32_t _sz_s, _sz_l;\n        std::vector<T> _dp_s;\n\
    \        std::vector<T> _dp_l;\n\n        // q = (n / log log n) ^ (2 / 3)\n \
    \       static uint32_t threshold(uint64_t n) {\n            double t = std::cbrt(n\
    \ / std::max(1., std::log(std::max(1., std::log(n)))));\n            return uint32_t(std::max(1.,\
    \ t * t));\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SUM_OF_MOBIUS_FUNCTION\n#define SUISEN_SUM_OF_MOBIUS_FUNCTION\n\
    \n#include <cstdint>\n#include <cmath>\n#include <numeric>\n#include <vector>\n\
    \nnamespace suisen {\n    // reference: https://yukicoder.me/wiki/sum_totient\n\
    \    template <typename T>\n    struct SumOfMobiusFunction {\n        SumOfMobiusFunction()\
    \ : SumOfMobiusFunction(1) {}\n        SumOfMobiusFunction(uint64_t n) : _n(n),\
    \ _sz_s(threshold(_n) + 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l)\
    \ {\n            std::vector<int32_t> mpf(_sz_s), mobius(_sz_s, 1);\n        \
    \    for (long long p = 2; p < _sz_s; ++p) {\n                if (mpf[p]) continue;\n\
    \                mpf[p] = p;\n                mobius[p] = -1;\n              \
    \  for (long long q = p * 2; q < _sz_s; q += p) {\n                    if (not\
    \ mpf[q]) mpf[q] = p;\n                    mobius[q] = q % (p * p) ? -mobius[q]\
    \ : 0;\n                }\n            }\n            for (uint32_t i = 1; i <\
    \ _sz_s; ++i) _dp_s[i] = mobius[i] + _dp_s[i - 1];\n\n            for (uint32_t\
    \ d = _sz_l - 1; d > 0; --d) {\n                uint64_t i = _n / d;\n       \
    \         // sum_{i=1,d}\\sum_{j|d}mu(j)=1\n                _dp_l[d] = 1;\n  \
    \              for (uint64_t l = 2; l <= i;) {\n                    uint64_t q\
    \ = i / l, r = i / q;\n                    _dp_l[d] -= (q < _sz_s ? _dp_s[q] :\
    \ _dp_l[d * l]) * (r - l + 1);\n                    l = r + 1;\n             \
    \   }\n            }\n        }\n\n        T operator()(uint64_t denominator =\
    \ 1) const {\n            uint64_t q = _n / denominator;\n            return q\
    \ < _sz_s ? _dp_s[q] : _dp_l[_n / (q + 1) + 1];\n        }\n\n    private:\n \
    \       uint64_t _n;\n        uint32_t _sz_s, _sz_l;\n        std::vector<T> _dp_s;\n\
    \        std::vector<T> _dp_l;\n\n        // q = (n / log log n) ^ (2 / 3)\n \
    \       static uint32_t threshold(uint64_t n) {\n            double t = std::cbrt(n\
    \ / std::max(1., std::log(std::max(1., std::log(n)))));\n            return uint32_t(std::max(1.,\
    \ t * t));\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_SUM_OF_MOBIUS_FUNCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/sum_of_mobius_function.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:37:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/sum_of_mobius_function.hpp
layout: document
title: Sum Of Mobius Function
---
## Sum Of Mobius Function