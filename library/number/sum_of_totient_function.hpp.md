---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/sum_of_totient_function/abc162_e.test.cpp
    title: test/src/number/sum_of_totient_function/abc162_e.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sum_of_totient_function/sum_of_totient_function.test.cpp
    title: test/src/number/sum_of_totient_function/sum_of_totient_function.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/wiki/sum_totient
  bundledCode: "#line 1 \"library/number/sum_of_totient_function.hpp\"\n\n\n\n#include\
    \ <cstdint>\n#include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ suisen {\n    // reference: https://yukicoder.me/wiki/sum_totient\n    template\
    \ <typename T>\n    struct SumOfTotientFunction {\n        SumOfTotientFunction()\
    \ : SumOfTotientFunction(1) {}\n        SumOfTotientFunction(uint64_t n) : _n(n),\
    \ _sz_s(threshold(_n) + 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l)\
    \ {\n            std::vector<uint32_t> phi(_sz_s);\n            std::iota(phi.begin(),\
    \ phi.end(), 0);\n            for (uint32_t p = 2; p < _sz_s; ++p) {\n       \
    \         if (phi[p] != p) continue;\n                for (uint32_t q = p; q <\
    \ _sz_s; q += p) phi[q] = phi[q] / p * (p - 1);\n            }\n            for\
    \ (uint32_t i = 1; i < _sz_s; ++i) _dp_s[i] = phi[i] + _dp_s[i - 1];\n\n     \
    \       for (uint32_t d = _sz_l - 1; d > 0; --d) {\n                uint64_t i\
    \ = _n / d;\n                // avoid overflow\n                if (i & 1) {\n\
    \                    _dp_l[d] = (i + 1) / 2, _dp_l[d] *= i;\n                }\
    \ else {\n                    _dp_l[d] = i / 2, _dp_l[d] *= i + 1;\n         \
    \       }\n                for (uint64_t l = 2; l <= i;) {\n                 \
    \   uint64_t q = i / l, r = i / q;\n                    _dp_l[d] -= (q < _sz_s\
    \ ? _dp_s[q] : _dp_l[d * l]) * (r - l + 1);\n                    l = r + 1;\n\
    \                }\n            }\n        }\n\n        T operator()(uint64_t\
    \ denominator = 1) const {\n            uint64_t q = _n / denominator;\n     \
    \       return q < _sz_s ? _dp_s[q] : _dp_l[_n / (q + 1) + 1];\n        }\n\n\
    \    private:\n        uint64_t _n;\n        uint32_t _sz_s, _sz_l;\n        std::vector<T>\
    \ _dp_s;\n        std::vector<T> _dp_l;\n\n        // q = (n / log log n) ^ (2\
    \ / 3)\n        static uint32_t threshold(uint64_t n) {\n            double t\
    \ = std::cbrt(n / std::max(1., std::log(std::max(1., std::log(n)))));\n      \
    \      return uint32_t(std::max(1., t * t));\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_SUM_OF_TOTIENT_FUNCTION\n#define SUISEN_SUM_OF_TOTIENT_FUNCTION\n\
    \n#include <cstdint>\n#include <cmath>\n#include <numeric>\n#include <vector>\n\
    \nnamespace suisen {\n    // reference: https://yukicoder.me/wiki/sum_totient\n\
    \    template <typename T>\n    struct SumOfTotientFunction {\n        SumOfTotientFunction()\
    \ : SumOfTotientFunction(1) {}\n        SumOfTotientFunction(uint64_t n) : _n(n),\
    \ _sz_s(threshold(_n) + 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l)\
    \ {\n            std::vector<uint32_t> phi(_sz_s);\n            std::iota(phi.begin(),\
    \ phi.end(), 0);\n            for (uint32_t p = 2; p < _sz_s; ++p) {\n       \
    \         if (phi[p] != p) continue;\n                for (uint32_t q = p; q <\
    \ _sz_s; q += p) phi[q] = phi[q] / p * (p - 1);\n            }\n            for\
    \ (uint32_t i = 1; i < _sz_s; ++i) _dp_s[i] = phi[i] + _dp_s[i - 1];\n\n     \
    \       for (uint32_t d = _sz_l - 1; d > 0; --d) {\n                uint64_t i\
    \ = _n / d;\n                // avoid overflow\n                if (i & 1) {\n\
    \                    _dp_l[d] = (i + 1) / 2, _dp_l[d] *= i;\n                }\
    \ else {\n                    _dp_l[d] = i / 2, _dp_l[d] *= i + 1;\n         \
    \       }\n                for (uint64_t l = 2; l <= i;) {\n                 \
    \   uint64_t q = i / l, r = i / q;\n                    _dp_l[d] -= (q < _sz_s\
    \ ? _dp_s[q] : _dp_l[d * l]) * (r - l + 1);\n                    l = r + 1;\n\
    \                }\n            }\n        }\n\n        T operator()(uint64_t\
    \ denominator = 1) const {\n            uint64_t q = _n / denominator;\n     \
    \       return q < _sz_s ? _dp_s[q] : _dp_l[_n / (q + 1) + 1];\n        }\n\n\
    \    private:\n        uint64_t _n;\n        uint32_t _sz_s, _sz_l;\n        std::vector<T>\
    \ _dp_s;\n        std::vector<T> _dp_l;\n\n        // q = (n / log log n) ^ (2\
    \ / 3)\n        static uint32_t threshold(uint64_t n) {\n            double t\
    \ = std::cbrt(n / std::max(1., std::log(std::max(1., std::log(n)))));\n      \
    \      return uint32_t(std::max(1., t * t));\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_SUM_OF_TOTIENT_FUNCTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/sum_of_totient_function.hpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/sum_of_totient_function/abc162_e.test.cpp
  - test/src/number/sum_of_totient_function/sum_of_totient_function.test.cpp
documentation_of: library/number/sum_of_totient_function.hpp
layout: document
title: Sum Of Totient Function
---
## Sum Of Totient Function