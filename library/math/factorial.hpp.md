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
    \ n) { ensure(n); }\n        inline const T& fac(const int i) { ensure(i); return\
    \ _fac[i]; }\n        inline const U& fac_inv(const int i) { ensure(i); return\
    \ _fac_inv[i]; }\n        inline U binom(const int n, const int r) {\n       \
    \     if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n       \
    \     return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n        inline\
    \ U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n < r)\
    \ return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n -\
    \ r];\n        }\n    private:\n        static std::vector<T> _fac;\n        static\
    \ std::vector<U> _fac_inv;\n        static void ensure(const int n) {\n      \
    \      int sz = _fac.size();\n            if (n + 1 <= sz) return;\n         \
    \   int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n};\ntemplate <typename T, typename U>\nstd::vector<T>\
    \ factorial<T, U>::_fac {1};\ntemplate <typename T, typename U>\nstd::vector<U>\
    \ factorial<T, U>::_fac_inv {1};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL\n#define SUISEN_FACTORIAL\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\ntemplate <typename T, typename U = T>\n\
    class factorial {\n    public:\n        factorial() {}\n        factorial(int\
    \ n) { ensure(n); }\n        inline const T& fac(const int i) { ensure(i); return\
    \ _fac[i]; }\n        inline const U& fac_inv(const int i) { ensure(i); return\
    \ _fac_inv[i]; }\n        inline U binom(const int n, const int r) {\n       \
    \     if (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n       \
    \     return _fac[n] * _fac_inv[r] * _fac_inv[n - r];\n        }\n        inline\
    \ U perm(const int n, const int r) {\n            if (n < 0 or r < 0 or n < r)\
    \ return 0;\n            ensure(n);\n            return _fac[n] * _fac_inv[n -\
    \ r];\n        }\n    private:\n        static std::vector<T> _fac;\n        static\
    \ std::vector<U> _fac_inv;\n        static void ensure(const int n) {\n      \
    \      int sz = _fac.size();\n            if (n + 1 <= sz) return;\n         \
    \   int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n};\ntemplate <typename T, typename U>\nstd::vector<T>\
    \ factorial<T, U>::_fac {1};\ntemplate <typename T, typename U>\nstd::vector<U>\
    \ factorial<T, U>::_fac_inv {1};\n} // namespace suisen\n\n#endif // SUISEN_FACTORIAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/factorial.hpp
  requiredBy:
  - library/math/common_sequences.hpp
  - library/math/polynomial_taylor_shift.hpp
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/polynomial_taylor_shift/polynomial_taylor_shift.test.cpp
  - test/src/math/common_sequences/bernoulli_number.test.cpp
  - test/src/math/common_sequences/partition_function.test.cpp
  - test/src/math/common_sequences/stirling_number2.test.cpp
  - test/src/math/common_sequences/stirling_number1.test.cpp
documentation_of: library/math/factorial.hpp
layout: document
redirect_from:
- /library/library/math/factorial.hpp
- /library/library/math/factorial.hpp.html
title: library/math/factorial.hpp
---
