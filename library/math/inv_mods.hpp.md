---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/math/BostanMori.hpp
    title: library/math/BostanMori.hpp
  - icon: ':warning:'
    path: library/math/common_sequences.hpp
    title: library/math/common_sequences.hpp
  - icon: ':warning:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':warning:'
    path: library/math/lagrange_interpolation.hpp
    title: library/math/lagrange_interpolation.hpp
  - icon: ':warning:'
    path: library/math/multi_point_eval.hpp
    title: library/math/multi_point_eval.hpp
  - icon: ':warning:'
    path: library/math/polynomial_taylor_shift.hpp
    title: library/math/polynomial_taylor_shift.hpp
  - icon: ':warning:'
    path: library/math/subset_sum.hpp
    title: library/math/subset_sum.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n\
    \        inv_mods() {}\n        inv_mods(int n) { ensure(n); }\n        const\
    \ mint& operator[](int i) const {\n            ensure(i);\n            return\
    \ invs[i];\n        }\n        static void ensure(int n) {\n            int sz\
    \ = invs.size();\n            if (sz < 2) invs = {0, 1}, sz = 2;\n           \
    \ if (sz < n + 1) {\n                invs.resize(n + 1);\n                for\
    \ (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n \
    \           }\n        }\n    private:\n        static std::vector<mint> invs;\n\
    \        static constexpr int mod = mint::mod();\n};\ntemplate <typename mint>\n\
    std::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n"
  code: "#ifndef SUISEN_INV_MOD\n#define SUISEN_INV_MOD\n\n#include <vector>\n\nnamespace\
    \ suisen {\ntemplate <typename mint>\nclass inv_mods {\n    public:\n        inv_mods()\
    \ {}\n        inv_mods(int n) { ensure(n); }\n        const mint& operator[](int\
    \ i) const {\n            ensure(i);\n            return invs[i];\n        }\n\
    \        static void ensure(int n) {\n            int sz = invs.size();\n    \
    \        if (sz < 2) invs = {0, 1}, sz = 2;\n            if (sz < n + 1) {\n \
    \               invs.resize(n + 1);\n                for (int i = sz; i <= n;\
    \ ++i) invs[i] = mint(mod - mod / i) * invs[mod % i];\n            }\n       \
    \ }\n    private:\n        static std::vector<mint> invs;\n        static constexpr\
    \ int mod = mint::mod();\n};\ntemplate <typename mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n\
    }\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/inv_mods.hpp
  requiredBy:
  - library/math/multi_point_eval.hpp
  - library/math/common_sequences.hpp
  - library/math/subset_sum.hpp
  - library/math/fps.hpp
  - library/math/polynomial_taylor_shift.hpp
  - library/math/lagrange_interpolation.hpp
  - library/math/BostanMori.hpp
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/inv_mods.hpp
layout: document
redirect_from:
- /library/library/math/inv_mods.hpp
- /library/library/math/inv_mods.hpp.html
title: library/math/inv_mods.hpp
---
