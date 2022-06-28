---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/util.hpp
    title: Util
  - icon: ':x:'
    path: library/polynomial/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':x:'
    path: library/polynomial/polynomial_taylor_shift.hpp
    title: Polynomial Taylor Shift
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/linear_algebra/circulant_matrix/arc139_e.test.cpp
    title: test/src/linear_algebra/circulant_matrix/arc139_e.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/array_sps/abc253_h.test.cpp
    title: test/src/math/array_sps/abc253_h.test.cpp
  - icon: ':x:'
    path: test/src/math/array_sps/abc253_h_2.test.cpp
    title: test/src/math/array_sps/abc253_h_2.test.cpp
  - icon: ':x:'
    path: test/src/math/sps/abc253_h.test.cpp
    title: test/src/math/sps/abc253_h.test.cpp
  - icon: ':x:'
    path: test/src/math/sps/abc253_h_2.test.cpp
    title: test/src/math/sps/abc253_h_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/util/abc240_g.test.cpp
    title: test/src/math/util/abc240_g.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/abc247_h.test.cpp
    title: test/src/polynomial/common_sequences/abc247_h.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
    title: test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
    title: test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/partition_function.test.cpp
    title: test/src/polynomial/common_sequences/partition_function.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/stirling_number1.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/common_sequences/stirling_number2.test.cpp
    title: test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, typename U\
    \ = T>\n    struct factorial {\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n\n        static void ensure(const int n) {\n           \
    \ int sz = _fac.size();\n            if (n + 1 <= sz) return;\n            int\
    \ new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL\n#define SUISEN_FACTORIAL\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, typename U\
    \ = T>\n    struct factorial {\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n\n        static void ensure(const int n) {\n           \
    \ int sz = _fac.size();\n            if (n + 1 <= sz) return;\n            int\
    \ new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
    \            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;\n\
    \            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];\n           \
    \ for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;\n\
    \        }\n\n        T fac(const int i) {\n            ensure(i);\n         \
    \   return _fac[i];\n        }\n        T operator()(int i) {\n            return\
    \ fac(i);\n        }\n        U fac_inv(const int i) {\n            ensure(i);\n\
    \            return _fac_inv[i];\n        }\n        U binom(const int n, const\
    \ int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n\
    \            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n    \
    \    U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n <\
    \ r) return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n\
    \ - r];\n        }\n    private:\n        static std::vector<T> _fac;\n      \
    \  static std::vector<U> _fac_inv;\n    };\n    template <typename T, typename\
    \ U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template <typename T,\
    \ typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n} // namespace\
    \ suisen\n\n#endif // SUISEN_FACTORIAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/factorial.hpp
  requiredBy:
  - library/math/util.hpp
  - library/polynomial/polynomial_taylor_shift.hpp
  - library/polynomial/common_sequences.hpp
  timestamp: '2022-05-28 01:05:03+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/math/util/abc240_g.test.cpp
  - test/src/math/array_sps/abc253_h_2.test.cpp
  - test/src/math/array_sps/abc253_h.test.cpp
  - test/src/math/sps/abc253_h_2.test.cpp
  - test/src/math/sps/abc253_h.test.cpp
  - test/src/linear_algebra/circulant_matrix/arc139_e.test.cpp
  - test/src/polynomial/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/polynomial/common_sequences/stirling_number2.test.cpp
  - test/src/polynomial/common_sequences/partition_function.test.cpp
  - test/src/polynomial/common_sequences/stirling_number1.test.cpp
  - test/src/polynomial/common_sequences/montmort_number_mod.test.cpp
  - test/src/polynomial/common_sequences/bernoulli_number.test.cpp
  - test/src/polynomial/common_sequences/abc247_h.test.cpp
documentation_of: library/math/factorial.hpp
layout: document
title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
---
## 階乗テーブル