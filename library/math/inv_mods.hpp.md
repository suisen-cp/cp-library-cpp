---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/polynomial_eval_multipoint_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
  - icon: ':heavy_check_mark:'
    path: library/math/bostan_mori.hpp
    title: Bostan Mori
  - icon: ':heavy_check_mark:'
    path: library/math/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':heavy_check_mark:'
    path: library/math/fps.hpp
    title: Fps
  - icon: ':heavy_check_mark:'
    path: library/math/interpolation.hpp
    title: Interpolation
  - icon: ':heavy_check_mark:'
    path: library/math/multi_point_eval.hpp
    title: Multi Point Eval
  - icon: ':heavy_check_mark:'
    path: library/math/polynomial_taylor_shift.hpp
    title: Polynomial Taylor Shift
  - icon: ':heavy_check_mark:'
    path: library/math/subset_sum.hpp
    title: Subset Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
    title: test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/src/math/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/bernoulli_number.test.cpp
    title: test/src/math/common_sequences/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/common_sequences/montmort_number_mod.test.cpp
    title: test/src/math/common_sequences/montmort_number_mod.test.cpp
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
    path: test/src/math/fps/division_of_polynomials.test.cpp
    title: test/src/math/fps/division_of_polynomials.test.cpp
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
  - icon: ':heavy_check_mark:'
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
  - library/math/common_sequences.hpp
  - library/math/interpolation.hpp
  - library/math/subset_sum.hpp
  - library/math/bostan_mori.hpp
  - library/math/multi_point_eval.hpp
  - library/math/polynomial_taylor_shift.hpp
  - library/math/fps.hpp
  - library/convolution/polynomial_eval_multipoint_eval.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/math/bostan_mori/kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/src/math/common_sequences/bernoulli_number.test.cpp
  - test/src/math/common_sequences/stirling_number1.test.cpp
  - test/src/math/common_sequences/partition_function.test.cpp
  - test/src/math/common_sequences/montmort_number_mod.test.cpp
  - test/src/math/common_sequences/stirling_number2.test.cpp
  - test/src/math/fps/log_of_fps.test.cpp
  - test/src/math/fps/pow_of_fps.test.cpp
  - test/src/math/fps/division_of_polynomials.test.cpp
  - test/src/math/fps/exp_of_fps.test.cpp
  - test/src/math/fps/inv_of_fps.test.cpp
  - test/src/math/subset_sum/p_subset_sum.test.cpp
  - test/src/math/interpolation/polynomial_interpolation.test.cpp
  - test/src/math/interpolation/cumulative_sum.test.cpp
  - test/src/math/multi_point_eval/multi_point_evaluation.test.cpp
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/datastructure/fenwick_tree_2d/random_is.test.cpp
documentation_of: library/math/inv_mods.hpp
layout: document
title: Inv Mods
---
## Inv Mods