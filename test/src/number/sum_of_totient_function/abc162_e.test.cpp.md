---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/sum_of_totient_function.hpp
    title: Prefix Sum of Totient Function
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc162/tasks/abc162_e
    links:
    - https://atcoder.jp/contests/abc162/tasks/abc162_e
  bundledCode: "#line 1 \"test/src/number/sum_of_totient_function/abc162_e.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc162/tasks/abc162_e\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint1000000007;\n\
    \n#line 1 \"library/number/sum_of_totient_function.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen {\n\
    \    // reference: https://yukicoder.me/wiki/sum_totient\n    template <typename\
    \ T>\n    struct SumOfTotientFunction {\n        SumOfTotientFunction() : SumOfTotientFunction(1)\
    \ {}\n        SumOfTotientFunction(uint64_t n) : _n(n), _sz_s(threshold(_n) +\
    \ 1), _sz_l(_n / _sz_s + 1), _dp_s(_sz_s), _dp_l(_sz_l) {\n            std::vector<uint32_t>\
    \ phi(_sz_s);\n            std::iota(phi.begin(), phi.end(), 0);\n           \
    \ for (uint32_t p = 2; p < _sz_s; ++p) {\n                if (phi[p] != p) continue;\n\
    \                for (uint32_t q = p; q < _sz_s; q += p) phi[q] = phi[q] / p *\
    \ (p - 1);\n            }\n            for (uint32_t i = 1; i < _sz_s; ++i) _dp_s[i]\
    \ = phi[i] + _dp_s[i - 1];\n\n            for (uint32_t d = _sz_l - 1; d > 0;\
    \ --d) {\n                uint64_t i = _n / d;\n                // avoid overflow\n\
    \                if (i & 1) _dp_l[d] = (i + 1) / 2, _dp_l[d] *= i;\n         \
    \       else       _dp_l[d] = i / 2, _dp_l[d] *= i + 1;\n                for (uint64_t\
    \ l = 2; l <= i;) {\n                    uint64_t q = i / l, r = i / q;\n    \
    \                _dp_l[d] -= (q < _sz_s ? _dp_s[q] : _dp_l[d * l]) * (r - l +\
    \ 1);\n                    l = r + 1;\n                }\n            }\n    \
    \    }\n\n        T operator()(uint64_t denominator = 1) const {\n           \
    \ uint64_t q = _n / denominator;\n            return q < _sz_s ? _dp_s[q] : _dp_l[_n\
    \ / (q + 1) + 1];\n        }\n\n    private:\n        uint64_t _n;\n        uint32_t\
    \ _sz_s, _sz_l;\n        std::vector<T> _dp_s;\n        std::vector<T> _dp_l;\n\
    \n        // q = (n / log log n) ^ (2 / 3)\n        static uint32_t threshold(uint64_t\
    \ n) {\n            double t = std::cbrt(n / std::max(1., std::log(std::max(1.,\
    \ std::log(n)))));\n            return uint32_t(std::max(1., t * t));\n      \
    \  }\n    };\n} // namespace suisen\n\n\n\n#line 9 \"test/src/number/sum_of_totient_function/abc162_e.test.cpp\"\
    \n\n// O(K^(2/3) (log log K)^(1/3) + K^(1/2) log N)\nint main() {\n    int n,\
    \ k;\n    std::cin >> n >> k;\n\n    // calculate sum(d) := \u03A3[i=1,floor(k/d)]\
    \ \u03C6(i) for all integer d in O(K^(2/3) (log log K)^(1/3) time.\n    suisen::SumOfTotientFunction<mint>\
    \ sum(k);\n\n    mint ans = 0;\n    for (int l = 1; l <= k;) {\n        int q\
    \ = k / l;\n        ans += (sum(q) - sum(q + 1)) * mint(q).pow(n);\n        l\
    \ = k / q + 1;\n    }\n    std::cout << ans.val() << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc162/tasks/abc162_e\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint1000000007;\n\
    \n#include \"library/number/sum_of_totient_function.hpp\"\n\n// O(K^(2/3) (log\
    \ log K)^(1/3) + K^(1/2) log N)\nint main() {\n    int n, k;\n    std::cin >>\
    \ n >> k;\n\n    // calculate sum(d) := \u03A3[i=1,floor(k/d)] \u03C6(i) for all\
    \ integer d in O(K^(2/3) (log log K)^(1/3) time.\n    suisen::SumOfTotientFunction<mint>\
    \ sum(k);\n\n    mint ans = 0;\n    for (int l = 1; l <= k;) {\n        int q\
    \ = k / l;\n        ans += (sum(q) - sum(q + 1)) * mint(q).pow(n);\n        l\
    \ = k / q + 1;\n    }\n    std::cout << ans.val() << std::endl;\n    return 0;\n\
    }"
  dependsOn:
  - library/number/sum_of_totient_function.hpp
  isVerificationFile: true
  path: test/src/number/sum_of_totient_function/abc162_e.test.cpp
  requiredBy: []
  timestamp: '2022-05-27 16:10:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/number/sum_of_totient_function/abc162_e.test.cpp
layout: document
redirect_from:
- /verify/test/src/number/sum_of_totient_function/abc162_e.test.cpp
- /verify/test/src/number/sum_of_totient_function/abc162_e.test.cpp.html
title: test/src/number/sum_of_totient_function/abc162_e.test.cpp
---
