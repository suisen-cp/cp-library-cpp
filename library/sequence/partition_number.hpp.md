---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/partition_number/partition_function.test.cpp
    title: test/src/sequence/partition_number/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/partition_number/partition_function_2.test.cpp
    title: test/src/sequence/partition_number/partition_function_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/partition_number.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename FPSType>\n    std::vector<typename\
    \ FPSType::value_type> partition_number(int n) {\n        FPSType inv(n + 1);\n\
    \        inv[0] = 1;\n        for (int i = 1, k = 1; k <= n; k += 3 * i + 1, i++)\
    \ {\n            if (i & 1) --inv[k];\n            else ++inv[k];\n        }\n\
    \        for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {\n            if\
    \ (i & 1) --inv[k];\n            else ++inv[k];\n        }\n        inv.inv_inplace(n\
    \ + 1), inv.resize(n + 1);\n        return inv;\n    }\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_PARTITON_NUMBER\n#define SUISEN_PARTITON_NUMBER\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename FPSType>\n    std::vector<typename\
    \ FPSType::value_type> partition_number(int n) {\n        FPSType inv(n + 1);\n\
    \        inv[0] = 1;\n        for (int i = 1, k = 1; k <= n; k += 3 * i + 1, i++)\
    \ {\n            if (i & 1) --inv[k];\n            else ++inv[k];\n        }\n\
    \        for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {\n            if\
    \ (i & 1) --inv[k];\n            else ++inv[k];\n        }\n        inv.inv_inplace(n\
    \ + 1), inv.resize(n + 1);\n        return inv;\n    }\n} // namespace suisen\n\
    \n#endif // SUISEN_PARTITON_NUMBER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/sequence/partition_number.hpp
  requiredBy: []
  timestamp: '2022-07-21 04:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/partition_number/partition_function_2.test.cpp
  - test/src/sequence/partition_number/partition_function.test.cpp
documentation_of: library/sequence/partition_number.hpp
layout: document
title: Partition Number
---
## Partition Number

### partition_number

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> partition_number(int n)
  ```

- 概要

  分割数 $P_0,\ldots,P_N$ を計算します．ここで，$P_i$ は，正整数を要素とする多重集合であって，総和が $i$ であるようなものの個数と一致します．

  母関数は $\displaystyle \sum_{i=0} ^ \infty P_i x ^ i=\prod_{k=1} ^ \infty \dfrac{1}{1-x ^ k}$ で表され，オイラーの五角数定理 :

  $$\prod_{k=1} ^ \infty(1-x ^ k)=\sum_{k=-\infty} ^ \infty(-1) ^ k x ^ {k(3k-1)/2}$$

  を用いることで，

  $$
  \begin{aligned}
  \sum_{i=0} ^ n P_i x ^ i
  &=\left(1+\sum_{k=1} ^ n (-1) ^ k \Bigl(x ^ {k(3k-1)/2}+x ^ {k(3k+1)/2}\Bigr)\right) ^ {-1}\bmod x ^ {n+1}
  \end{aligned}
  $$

  により計算できます．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  分割数 $\\\{P_i\\\} _ {i=0} ^ N$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$

- 参考

  - [(形式的)べき級数と数え上げの写像12相との関係性　後編](https://sen-comp.hatenablog.com/entry/2019/12/11/110958)

