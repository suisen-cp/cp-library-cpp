---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
    title: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/subset_sum/p_subset_sum_2.test.cpp
    title: test/src/polynomial/subset_sum/p_subset_sum_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/subset_sum.hpp\"\n\n\n\n#include <vector>\n\
    \n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#line 5 \"library/math/inv_mods.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n\
    \        inv_mods() {}\n        inv_mods(int n) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ invs[i];\n        }\n        static void ensure(int n) {\n            int sz\
    \ = invs.size();\n            if (sz < 2) invs = {0, 1}, sz = 2;\n           \
    \ if (sz < n + 1) {\n                invs.resize(n + 1);\n                for\
    \ (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n \
    \           }\n        }\n    private:\n        static std::vector<mint> invs;\n\
    \        static constexpr int mod = mint::mod();\n};\ntemplate <typename mint>\n\
    std::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line 7 \"library/polynomial/subset_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename FPSType>\n    std::vector<typename\
    \ FPSType::value_type> subset_sum(const int n, const std::vector<int>& items)\
    \ {\n        using mint = typename FPSType::value_type;\n        std::vector<int>\
    \ a(n + 1, 0);\n        for (int e : items) {\n            assert(e >= 0);\n \
    \           if (e <= n) ++a[e];\n        }\n        inv_mods<mint> invs(n);\n\
    \        FPSType log(n + 1);\n        for (int i = 1; i <= n; ++i) {\n       \
    \     if (a[i] == 0) continue;\n            for (int j = 1; i * j <= n; ++j) {\n\
    \                if (j & 1) log[i * j] += invs[j] * a[i];\n                else\
    \       log[i * j] -= invs[j] * a[i];\n            }\n        }\n        log.exp_inplace(n\
    \ + 1), log.resize(n + 1);\n        mint p = mint(2).pow(a[0]);\n        for (mint&\
    \ e : log) e *= p;\n        return log;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_SUM\n#define SUISEN_SUBSET_SUM\n\n#include <vector>\n\
    \n#include \"library/math/inv_mods.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ FPSType>\n    std::vector<typename FPSType::value_type> subset_sum(const int\
    \ n, const std::vector<int>& items) {\n        using mint = typename FPSType::value_type;\n\
    \        std::vector<int> a(n + 1, 0);\n        for (int e : items) {\n      \
    \      assert(e >= 0);\n            if (e <= n) ++a[e];\n        }\n        inv_mods<mint>\
    \ invs(n);\n        FPSType log(n + 1);\n        for (int i = 1; i <= n; ++i)\
    \ {\n            if (a[i] == 0) continue;\n            for (int j = 1; i * j <=\
    \ n; ++j) {\n                if (j & 1) log[i * j] += invs[j] * a[i];\n      \
    \          else       log[i * j] -= invs[j] * a[i];\n            }\n        }\n\
    \        log.exp_inplace(n + 1), log.resize(n + 1);\n        mint p = mint(2).pow(a[0]);\n\
    \        for (mint& e : log) e *= p;\n        return log;\n    }\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SUBSET_SUM\n"
  dependsOn:
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/polynomial/subset_sum.hpp
  requiredBy: []
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  - test/src/polynomial/subset_sum/p_subset_sum_2.test.cpp
documentation_of: library/polynomial/subset_sum.hpp
layout: document
title: Subset Sum
---
## Subset Sum