---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/math/bostan_mori.hpp
    title: library/math/bostan_mori.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':question:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':question:'
    path: library/math/interpolation.hpp
    title: library/math/interpolation.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/multi_point_eval.hpp
    title: library/math/multi_point_eval.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/polynomial_taylor_shift.hpp
    title: library/math/polynomial_taylor_shift.hpp
  - icon: ':heavy_check_mark:'
    path: library/math/subset_sum.hpp
    title: library/math/subset_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/bernoulli_number.test.cpp
    title: test/src/math/common_sequences/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/partition_function.test.cpp
    title: test/src/math/common_sequences/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/stirling_number1.test.cpp
    title: test/src/math/common_sequences/stirling_number1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/stirling_number2.test.cpp
    title: test/src/math/common_sequences/stirling_number2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/fps/exp_of_fps.test.cpp
    title: test/src/math/fps/exp_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/fps/inv_of_fps.test.cpp
    title: test/src/math/fps/inv_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/fps/log_of_fps.test.cpp
    title: test/src/math/fps/log_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/fps/pow_of_fps.test.cpp
    title: test/src/math/fps/pow_of_fps.test.cpp
  - icon: ':x:'
    path: test/src/math/interpolation/cumulative_sum.test.cpp
    title: test/src/math/interpolation/cumulative_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/interpolation/polynomial_interpolation.test.cpp
    title: test/src/math/interpolation/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
    title: test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/subset_sum/p_subset_sum.test.cpp
    title: test/src/math/subset_sum/p_subset_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
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
    }\n\n#endif // SUISEN_INV_MOD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/inv_mods.hpp
  requiredBy:
  - library/math/multi_point_eval.hpp
  - library/math/common_sequences.hpp
  - library/math/subset_sum.hpp
  - library/math/fps.hpp
  - library/math/interpolation.hpp
  - library/math/polynomial_taylor_shift.hpp
  - library/math/bostan_mori.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/math/common_sequences/partition_function.test.cpp
  - test/src/math/common_sequences/stirling_number2.test.cpp
  - test/src/math/common_sequences/stirling_number1.test.cpp
  - test/src/math/common_sequences/bernoulli_number.test.cpp
  - test/src/math/interpolation/polynomial_interpolation.test.cpp
  - test/src/math/interpolation/cumulative_sum.test.cpp
  - test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
  - test/src/math/subset_sum/p_subset_sum.test.cpp
  - test/src/math/fps/inv_of_fps.test.cpp
  - test/src/math/fps/log_of_fps.test.cpp
  - test/src/math/fps/exp_of_fps.test.cpp
  - test/src/math/fps/pow_of_fps.test.cpp
documentation_of: library/math/inv_mods.hpp
layout: document
redirect_from:
- /library/library/math/inv_mods.hpp
- /library/library/math/inv_mods.hpp.html
title: library/math/inv_mods.hpp
---
