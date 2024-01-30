---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/number/fast_discrete_logarithm.hpp
    title: Fast Discrete Logarithm
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/discrete_logarithm/discrete_logarithm_mod.test.cpp
    title: test/src/number/discrete_logarithm/discrete_logarithm_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/discrete_logarithm.hpp\"\n\n\n\n#include\
    \ <cmath>\n#include <unordered_map>\n#include <numeric>\n\nnamespace suisen {\n\
    \    namespace internal::discrete_logarithm {\n        int floor_log2(int m) {\n\
    \            int res = 0;\n            while (1 << (res + 1) <= m) ++res;\n  \
    \          return res;\n        }\n    }\n\n    template <typename mint>\n   \
    \ int discrete_logarithm_coprime(mint x, mint y) {\n        const int m = mint::mod();\n\
    \        if (y == 1 or m == 1) return 0;\n        if (x == 0) return y == 0 ?\
    \ 1 : -1;\n        const int p = ::sqrt(m) + 1;\n        mint a = mint(x).inv().pow(p);\n\
    \        std::unordered_map<int, int> mp;\n        mint pow_x = 1;\n        for\
    \ (int j = 0; j < p; ++j, pow_x *= x) mp.try_emplace(pow_x.val(), j);\n      \
    \  mint ya = y;\n        for (int i = 0; i < p; ++i, ya *= a) {\n            if\
    \ (auto it = mp.find(ya.val()); it != mp.end()) return p * i + it->second;\n \
    \       }\n        return -1;\n    }\n\n    template <typename mint>\n    int\
    \ discrete_logarithm(mint x, mint y) {\n        using namespace internal::discrete_logarithm;\n\
    \        const int m = mint::mod();\n        if (m == 1) return 0;\n        const\
    \ int d = floor_log2(m);\n        mint pow_x = 1;\n        for (int i = 0; i <\
    \ d; ++i, pow_x *= x) if (pow_x == y) return i;\n        const int g = std::gcd(pow_x.val(),\
    \ m);\n        if (y.val() % g) return -1;\n        mint::set_mod(m / g);\n  \
    \      const int t = discrete_logarithm_coprime(mint(x.val()), mint(y.val()) *\
    \ mint(pow_x.val()).inv());\n        mint::set_mod(m);\n        return t != -1\
    \ ? d + t : -1;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DISCRETE_LOGARITHM\n#define SUISEN_DISCRETE_LOGARITHM\n\n\
    #include <cmath>\n#include <unordered_map>\n#include <numeric>\n\nnamespace suisen\
    \ {\n    namespace internal::discrete_logarithm {\n        int floor_log2(int\
    \ m) {\n            int res = 0;\n            while (1 << (res + 1) <= m) ++res;\n\
    \            return res;\n        }\n    }\n\n    template <typename mint>\n \
    \   int discrete_logarithm_coprime(mint x, mint y) {\n        const int m = mint::mod();\n\
    \        if (y == 1 or m == 1) return 0;\n        if (x == 0) return y == 0 ?\
    \ 1 : -1;\n        const int p = ::sqrt(m) + 1;\n        mint a = mint(x).inv().pow(p);\n\
    \        std::unordered_map<int, int> mp;\n        mint pow_x = 1;\n        for\
    \ (int j = 0; j < p; ++j, pow_x *= x) mp.try_emplace(pow_x.val(), j);\n      \
    \  mint ya = y;\n        for (int i = 0; i < p; ++i, ya *= a) {\n            if\
    \ (auto it = mp.find(ya.val()); it != mp.end()) return p * i + it->second;\n \
    \       }\n        return -1;\n    }\n\n    template <typename mint>\n    int\
    \ discrete_logarithm(mint x, mint y) {\n        using namespace internal::discrete_logarithm;\n\
    \        const int m = mint::mod();\n        if (m == 1) return 0;\n        const\
    \ int d = floor_log2(m);\n        mint pow_x = 1;\n        for (int i = 0; i <\
    \ d; ++i, pow_x *= x) if (pow_x == y) return i;\n        const int g = std::gcd(pow_x.val(),\
    \ m);\n        if (y.val() % g) return -1;\n        mint::set_mod(m / g);\n  \
    \      const int t = discrete_logarithm_coprime(mint(x.val()), mint(y.val()) *\
    \ mint(pow_x.val()).inv());\n        mint::set_mod(m);\n        return t != -1\
    \ ? d + t : -1;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_DISCRETE_LOGARITHM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/discrete_logarithm.hpp
  requiredBy:
  - library/number/fast_discrete_logarithm.hpp
  timestamp: '2022-09-28 21:35:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/discrete_logarithm/discrete_logarithm_mod.test.cpp
documentation_of: library/number/discrete_logarithm.hpp
layout: document
title: Discrete Logarithm
---
## Discrete Logarithm