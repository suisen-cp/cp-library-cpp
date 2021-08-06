---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - icon: ':x:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/walsh_hadamard.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n\nnamespace internal {\n\ntemplate <typename\
    \ T>\nvoid fwht(std::vector<T>& a, bool rev) {\n    const int n = a.size();\n\
    \    assert((-n & n) == n);\n    for (int i = 1; i < n; i *= 2) {\n        for\
    \ (int k = 0; k < n; k += i * 2) {\n            for (int j = k; j < k + i; ++j)\
    \ {\n                T u = a[j], v = a[j + i];\n                a[j] = u + v;\n\
    \                a[j + i] = u - v;\n            }\n        }\n    }\n    if (rev)\
    \ {\n        T inv = T(1) / T(n);\n        for (int i = 0; i < n; i++) a[i] *=\
    \ inv;\n    }\n}\n\n} // nemaspace internal\n\ntemplate <typename T>\nstruct WalshHadamard\
    \ {\n    static void transform(std::vector<T> &a) {\n        internal::fwht(a,\
    \ false);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n   \
    \     internal::fwht(a, true);\n    }\n};\n\n} // namespace suisen::walsh_hadamard_transform\n\
    \n\n\n"
  code: "#ifndef SUISEN_WALSH_HADAMARD_TRANSFORM\n#define SUISEN_WALSH_HADAMARD_TRANSFORM\n\
    \n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n\nnamespace internal\
    \ {\n\ntemplate <typename T>\nvoid fwht(std::vector<T>& a, bool rev) {\n    const\
    \ int n = a.size();\n    assert((-n & n) == n);\n    for (int i = 1; i < n; i\
    \ *= 2) {\n        for (int k = 0; k < n; k += i * 2) {\n            for (int\
    \ j = k; j < k + i; ++j) {\n                T u = a[j], v = a[j + i];\n      \
    \          a[j] = u + v;\n                a[j + i] = u - v;\n            }\n \
    \       }\n    }\n    if (rev) {\n        T inv = T(1) / T(n);\n        for (int\
    \ i = 0; i < n; i++) a[i] *= inv;\n    }\n}\n\n} // nemaspace internal\n\ntemplate\
    \ <typename T>\nstruct WalshHadamard {\n    static void transform(std::vector<T>\
    \ &a) {\n        internal::fwht(a, false);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        internal::fwht(a, true);\n    }\n};\n\n} // namespace suisen::walsh_hadamard_transform\n\
    \n\n#endif // SUISEN_WALSH_HADAMARD_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/walsh_hadamard.hpp
  requiredBy:
  - library/convolution/xor_convolution.hpp
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - test/src/convolution/polynomial_eval/nim_counting.test.cpp
documentation_of: library/transform/walsh_hadamard.hpp
layout: document
title: "Walsh Hadamard \u5909\u63DB"
---

### struct WalshHadamard

- シグネチャ

  ```cpp
  template <typename T>
  struct WalshHadamard {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に [アダマール変換](https://ja.wikipedia.org/wiki/%E3%82%A2%E3%83%80%E3%83%9E%E3%83%BC%E3%83%AB%E5%A4%89%E6%8F%9B) を施す関数 `WalshHadamard<T>::transform` およびその逆変換を施す関数 `WalshHadamard<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

- テンプレート引数

  - `T`: 列の要素の型．`operator+`，`operator-`，`operator*=` が定義されている必要があります．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$
