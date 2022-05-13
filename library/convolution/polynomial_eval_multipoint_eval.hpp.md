---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: library/math/multi_point_eval.hpp:\
    \ line -1: no such header\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n#define SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n\
    \n#include \"library/math/multi_point_eval.hpp\"\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint, auto transform, auto transform_inv>\n\
    \    std::vector<mint> polynomial_eval(std::vector<mint> &&a, const FPS<mint>\
    \ &f) {\n        transform(a);\n        a = multi_point_eval(f, a);\n        transform_inv(a);\n\
    \        return a;\n    }\n\n    template <typename mint, auto transform, auto\
    \ transform_inv>\n    std::vector<mint> polynomial_eval(const std::vector<mint>\
    \ &a, const FPS<mint> &f) {\n        return polynomial_eval<mint, transform, transform_inv>(std::vector<mint>(a),\
    \ f);\n    }\n} // namespace suisen\n\n#endif // SUISEN_APPLY_POLYNOMIAL_MULTIPOINT_EVAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/polynomial_eval_multipoint_eval.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/convolution/polynomial_eval_multipoint_eval.hpp
layout: document
title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\u306E\
  \u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
---

### polynomial_eval

- シグネチャ

  ```cpp
  template <typename mint, auto transform, auto transform_inv>
  std::vector<mint> polynomial_eval(std::vector<mint> &&a, const FPS<mint> &f) // (1)

  template <typename mint, auto transform, auto transform_inv>
  std::vector<mint> polynomial_eval(const std::vector<mint> &a, const FPS<mint> &f) // (2)
  ```

- 概要

  列 $A$ を変数に持つ多項式 $\displaystyle f(A)=\sum_{i=0}^{M-1} C_i \cdot A^i$ を評価します．ここで，$A^i$ はある畳み込み演算 $\ast$ に対して以下で定義されるものとします．

  $$ A^i = \underbrace{A \ast A \ast \cdots \ast A}_{i} $$

  また，$\ast$ に対してある正則な変換行列 $\mathcal{F}$ が存在して，任意の列 $X,Y$ に対して

  $$ \mathcal{F}[X] \odot \mathcal{F}[Y]=\mathcal{F}[X\ast Y]$$

  を満たす必要があります．ここで，$\odot$ は各点積をとる演算です．このとき，$f(A)$ は次のように計算されます．

  $$\begin{aligned}
  f(A)
  &=\mathcal{F}^{-1}\left[\sum_{i=0}^{M-1}C_i\cdot \left(\underbrace{\mathcal{F}[A]\odot\cdots\odot\mathcal{F}[A]}_{i}\right)\right]\\
  &=\mathcal{F}^{-1}\left[\begin{pmatrix}
  f(\mathcal{F}[A]_0)\\
  f(\mathcal{F}[A]_1)\\
  \vdots\\
  f(\mathcal{F}[A]_{\vert A\vert-1})\\
  \end{pmatrix}\right]
  \end{aligned}$$

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `transform` および `transform_inv` であり，$f(\cdot)$ を評価するのが引数 `f` です．

  このライブラリでは $f(\cdot)$ たちの計算に多点評価のアルゴリズムを用いることで高速化を図ります．従って，引数として与える多項式 $f$ を形式的冪級数型 `FPS` に制限し，値型は `atcoder::modint` であることを想定しています．

- テンプレート引数

  - `mint`: 列の要素の型．`atcoder::modint` 型を想定しています．
  - `transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を施す関数
  - `transform_inv`: 逆変換 $\mathcal{F}^{-1}$ を施す関数

- 引数

  - `a`: 列 $A$
  - `f`: 多項式 $f$

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`transform` の計算量を $\Theta(f(N))$, `transform_inv` の計算量を $\Theta(g(N))$ として，$\Theta(f(N)+g(N)+N (\log N) ^ 2)$ です．

