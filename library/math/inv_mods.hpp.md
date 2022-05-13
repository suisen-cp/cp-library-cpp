---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/product_of_differences.hpp
    title: library/math/product_of_differences.hpp
  - icon: ':heavy_check_mark:'
    path: library/polynomial/bostan_mori.hpp
    title: Bostan Mori
  - icon: ':heavy_check_mark:'
    path: library/polynomial/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':question:'
    path: library/polynomial/fps.hpp
    title: "\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: library/polynomial/lagrange_interpolation.hpp
  - icon: ':heavy_check_mark:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  - icon: ':heavy_check_mark:'
    path: library/polynomial/polynomial_interpolation.hpp
    title: library/polynomial/polynomial_interpolation.hpp
  - icon: ':x:'
    path: library/polynomial/polynomial_taylor_shift.hpp
    title: Polynomial Taylor Shift
  - icon: ':x:'
    path: library/polynomial/subset_sum.hpp
    title: Subset Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/product_of_differences/yuki1938.test.cpp
    title: test/src/math/product_of_differences/yuki1938.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
    title: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
    title: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/partition_function.test.cpp
    title: test/src/polynomial/common_sequences/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/stirling_number1.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/common_sequences/stirling_number2.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/fps/division_of_polynomials.test.cpp
    title: test/src/polynomial/fps/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/fps/exp_of_fps.test.cpp
    title: test/src/polynomial/fps/exp_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/fps/inv_of_fps.test.cpp
    title: test/src/polynomial/fps/inv_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/fps/log_of_fps.test.cpp
    title: test/src/polynomial/fps/log_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/fps/pow_of_fps.test.cpp
    title: test/src/polynomial/fps/pow_of_fps.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
    title: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
    title: test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
    title: test/src/polynomial/subset_sum/p_subset_sum.test.cpp
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
  - library/math/product_of_differences.hpp
  - library/polynomial/lagrange_interpolation.hpp
  - library/polynomial/multi_point_eval.hpp
  - library/polynomial/fps.hpp
  - library/polynomial/polynomial_interpolation.hpp
  - library/polynomial/polynomial_taylor_shift.hpp
  - library/polynomial/bostan_mori.hpp
  - library/polynomial/common_sequences.hpp
  - library/polynomial/subset_sum.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - test/src/math/product_of_differences/yuki1938.test.cpp
  - test/src/polynomial/subset_sum/p_subset_sum.test.cpp
  - test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/polynomial/polynomial_interpolation/polynomial_interpolation.test.cpp
  - test/src/polynomial/fps/log_of_fps.test.cpp
  - test/src/polynomial/fps/pow_of_fps.test.cpp
  - test/src/polynomial/fps/inv_of_fps.test.cpp
  - test/src/polynomial/fps/division_of_polynomials.test.cpp
  - test/src/polynomial/fps/exp_of_fps.test.cpp
  - test/src/polynomial/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - test/src/polynomial/common_sequences/partition_function.test.cpp
  - test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy.test.cpp
documentation_of: library/math/inv_mods.hpp
layout: document
title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
---
## 逆元テーブル