---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/common_sequences.hpp
    title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
  - icon: ':heavy_check_mark:'
    path: library/math/polynomial_taylor_shift.hpp
    title: library/math/polynomial_taylor_shift.hpp
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
    path: test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
    title: test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/factorial.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\ntemplate <typename T, typename U = T>\n\
    class factorial {\n    public:\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n        const T& fac(const int i) {\n            ensure(i);\n\
    \            return fac_[i];\n        }\n        const T& operator()(int i) {\n\
    \            return fac(i);\n        }\n        const U& inv(const int i) {\n\
    \            ensure(i);\n            return inv_[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return fac_[n] * inv_[r] * inv_[n - r];\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return fac_[n]\
    \ * inv_[n - r];\n        }\n    private:\n        static std::vector<T> fac_;\n\
    \        static std::vector<U> inv_;\n        static void ensure(const int n)\
    \ {\n            int sz = fac_.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            fac_.resize(new_size),\
    \ inv_.resize(new_size);\n            for (int i = sz; i < new_size; ++i) fac_[i]\
    \ = fac_[i - 1] * i;\n            inv_[new_size - 1] = U(1) / fac_[new_size -\
    \ 1];\n            for (int i = new_size - 1; i > sz; --i) inv_[i - 1] = inv_[i]\
    \ * i;\n        }\n};\ntemplate <typename T, typename U>\nstd::vector<T> factorial<T,\
    \ U>::fac_ {1};\ntemplate <typename T, typename U>\nstd::vector<U> factorial<T,\
    \ U>::inv_ {1};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL\n#define SUISEN_FACTORIAL\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\ntemplate <typename T, typename U = T>\n\
    class factorial {\n    public:\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n        const T& fac(const int i) {\n            ensure(i);\n\
    \            return fac_[i];\n        }\n        const T& operator()(int i) {\n\
    \            return fac(i);\n        }\n        const U& inv(const int i) {\n\
    \            ensure(i);\n            return inv_[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return fac_[n] * inv_[r] * inv_[n - r];\n\
    \        }\n        U perm(const int n, const int r) {\n            if (n < 0\
    \ or r < 0 or n < r) return 0;\n            ensure(n);\n            return fac_[n]\
    \ * inv_[n - r];\n        }\n    private:\n        static std::vector<T> fac_;\n\
    \        static std::vector<U> inv_;\n        static void ensure(const int n)\
    \ {\n            int sz = fac_.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            fac_.resize(new_size),\
    \ inv_.resize(new_size);\n            for (int i = sz; i < new_size; ++i) fac_[i]\
    \ = fac_[i - 1] * i;\n            inv_[new_size - 1] = U(1) / fac_[new_size -\
    \ 1];\n            for (int i = new_size - 1; i > sz; --i) inv_[i - 1] = inv_[i]\
    \ * i;\n        }\n};\ntemplate <typename T, typename U>\nstd::vector<T> factorial<T,\
    \ U>::fac_ {1};\ntemplate <typename T, typename U>\nstd::vector<U> factorial<T,\
    \ U>::inv_ {1};\n} // namespace suisen\n\n#endif // SUISEN_FACTORIAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/factorial.hpp
  requiredBy:
  - library/math/common_sequences.hpp
  - library/math/polynomial_taylor_shift.hpp
  timestamp: '2021-08-07 15:47:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/common_sequences/partition_function.test.cpp
  - test/src/math/common_sequences/stirling_number1.test.cpp
  - test/src/math/common_sequences/bernoulli_number.test.cpp
  - test/src/math/common_sequences/stirling_number2.test.cpp
  - test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
documentation_of: library/math/factorial.hpp
layout: document
redirect_from:
- /library/library/math/factorial.hpp
- /library/library/math/factorial.hpp.html
title: library/math/factorial.hpp
---
