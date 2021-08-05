---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/transform/walsh_hadamard.hpp
    title: "Walsh Hadamard \u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/xor_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/walsh_hadamard.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\n\nnamespace internal {\n\ntemplate <typename\
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
    \n\n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename T, template <typename> class Transform>\n\
    struct Convolution {\n    static std::vector<T> convolution(std::vector<T> a,\
    \ std::vector<T> b) {\n        const int n = a.size();\n        assert(n == int(b.size()));\n\
    \        Transform<T>::transform(a);\n        Transform<T>::transform(b);\n  \
    \      for (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        const int num = a.size();\n        if (num == 0) return {};\n\
    \        const int n = a[0].size();\n        for (auto &v : a) {\n           \
    \ assert(n == int(v.size()));\n            Transform<T>::transform(v);\n     \
    \   }\n        auto &res = a[0];\n        for (int i = 1; i < num; ++i) {\n  \
    \          for (int j = 0; j < n; ++j) res[j] *= a[i][j];\n        }\n       \
    \ Transform<T>::inverse_transform(res);\n        return res;\n    }\n};\n\n} //\
    \ namespace suisen\n\n\n\n#line 6 \"library/convolution/xor_convolution.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nusing XorConvolution = Convolution<T,\
    \ WalshHadamard>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> xor_convolution(Args\
    \ &&...args) {\n    return XorConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_XOR_CONVOLUTION\n#define SUISEN_XOR_CONVOLUTION\n\n#include\
    \ \"library/transform/walsh_hadamard.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing XorConvolution = Convolution<T,\
    \ WalshHadamard>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> xor_convolution(Args\
    \ &&...args) {\n    return XorConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_XOR_CONVOLUTION\n"
  dependsOn:
  - library/transform/walsh_hadamard.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/xor_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
documentation_of: library/convolution/xor_convolution.hpp
layout: document
title: Bitwise Xor Convolution
---

### xor_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> xor_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字 bitwise xor で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \oplus j = k } A _ i \cdot B _ j $$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
     - $0\leq L\leq 20$
  2. - ある非負整数 $L$ が存在して $\vert\mathcal{A}^0\vert=\vert\mathcal{A}^1\vert=\cdots=2^L$ を満たす
     - $0\leq L\leq 20$

- 時間計算量

  1. $\Theta(N\log N)$，あるいは $\Theta(L\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N\log N)$，あるいは $\Theta(K\cdot L\cdot 2^L)$