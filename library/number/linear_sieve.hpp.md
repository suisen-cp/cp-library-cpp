---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/number/anymod_binom.hpp
    title: library/number/anymod_binom.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://37zigen.com/linear-sieve/
  bundledCode: "#line 1 \"library/number/linear_sieve.hpp\"\n#include <numeric>\n\
    #include <vector>\n\nnamespace suisen {\n// referece: https://37zigen.com/linear-sieve/\n\
    class LinearSieve {\n    public:\n        LinearSieve(const unsigned int n) :\
    \ _n(n), min_prime_factor(std::vector<unsigned int>(n + 1)) {\n            std::iota(min_prime_factor.begin(),\
    \ min_prime_factor.end(), 0);\n            prime_list.reserve(_n / 3);\n     \
    \       for (unsigned int d = 2; d <= _n; ++d) {\n                if (min_prime_factor[d]\
    \ == d) prime_list.push_back(d);\n                const unsigned int prime_max\
    \ = std::min(min_prime_factor[d], _n / d);\n                for (unsigned int\
    \ prime : prime_list) {\n                    if (prime > prime_max) break;\n \
    \                   min_prime_factor[prime * d] = prime;\n                }\n\
    \            }\n        }\n        unsigned int prime_num() const { return prime_list.size();\
    \ }\n        const std::vector<unsigned int>& get_prime_list() const { return\
    \ prime_list; }\n        const std::vector<unsigned int>& get_min_prime_factor()\
    \ const { return min_prime_factor; }\n    private:\n        const unsigned int\
    \ _n;\n        std::vector<unsigned int> min_prime_factor;\n        std::vector<unsigned\
    \ int> prime_list;\n};\n} // namespace suisen\n"
  code: "#include <numeric>\n#include <vector>\n\nnamespace suisen {\n// referece:\
    \ https://37zigen.com/linear-sieve/\nclass LinearSieve {\n    public:\n      \
    \  LinearSieve(const unsigned int n) : _n(n), min_prime_factor(std::vector<unsigned\
    \ int>(n + 1)) {\n            std::iota(min_prime_factor.begin(), min_prime_factor.end(),\
    \ 0);\n            prime_list.reserve(_n / 3);\n            for (unsigned int\
    \ d = 2; d <= _n; ++d) {\n                if (min_prime_factor[d] == d) prime_list.push_back(d);\n\
    \                const unsigned int prime_max = std::min(min_prime_factor[d],\
    \ _n / d);\n                for (unsigned int prime : prime_list) {\n        \
    \            if (prime > prime_max) break;\n                    min_prime_factor[prime\
    \ * d] = prime;\n                }\n            }\n        }\n        unsigned\
    \ int prime_num() const { return prime_list.size(); }\n        const std::vector<unsigned\
    \ int>& get_prime_list() const { return prime_list; }\n        const std::vector<unsigned\
    \ int>& get_min_prime_factor() const { return min_prime_factor; }\n    private:\n\
    \        const unsigned int _n;\n        std::vector<unsigned int> min_prime_factor;\n\
    \        std::vector<unsigned int> prime_list;\n};\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/number/linear_sieve.hpp
  requiredBy:
  - library/number/anymod_binom.hpp
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/linear_sieve.hpp
layout: document
redirect_from:
- /library/library/number/linear_sieve.hpp
- /library/library/number/linear_sieve.hpp.html
title: library/number/linear_sieve.hpp
---
