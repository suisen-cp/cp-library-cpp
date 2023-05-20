---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/convolution/polynomial_eval_multipoint_eval.hpp
    title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\
      \u306E\u8A55\u4FA1 (\u591A\u70B9\u8A55\u4FA1\u7248)"
  - icon: ':warning:'
    path: library/math/factorial_large.hpp
    title: Factorial Large
  - icon: ':question:'
    path: library/math/product_of_differences.hpp
    title: Product Of Differences
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  - icon: ':question:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/product_of_differences/yuki1938.test.cpp
    title: test/src/math/product_of_differences/yuki1938.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
    title: test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/multi_point_eval/multi_point_evaluation_2.test.cpp
    title: test/src/polynomial/multi_point_eval/multi_point_evaluation_2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/multi_point_eval.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename FPSType, typename T>\n\
    \    std::vector<typename FPSType::value_type> multi_point_eval(const FPSType&\
    \ f, const std::vector<T>& xs) {\n        int n = xs.size();\n        if (n ==\
    \ 0) return {};\n        std::vector<FPSType> seg(2 * n);\n        for (int i\
    \ = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i], 1 };\n        for (int i = n\
    \ - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = f %\
    \ seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n\
    \        std::vector<typename FPSType::value_type> ys(n);\n        for (int i\
    \ = 0; i < n; ++i) ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;\n        return\
    \ ys;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MULTI_POINT_EVALUATION\n#define SUISEN_MULTI_POINT_EVALUATION\n\
    \n#include <vector>\n\nnamespace suisen {\n    template <typename FPSType, typename\
    \ T>\n    std::vector<typename FPSType::value_type> multi_point_eval(const FPSType&\
    \ f, const std::vector<T>& xs) {\n        int n = xs.size();\n        if (n ==\
    \ 0) return {};\n        std::vector<FPSType> seg(2 * n);\n        for (int i\
    \ = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i], 1 };\n        for (int i = n\
    \ - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];\n        seg[1] = f %\
    \ seg[1];\n        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];\n\
    \        std::vector<typename FPSType::value_type> ys(n);\n        for (int i\
    \ = 0; i < n; ++i) ys[i] = seg[n + i].size() ? seg[n + i][0] : 0;\n        return\
    \ ys;\n    }\n} // namespace suisen\n\n#endif // SUISEN_MULTI_POINT_EVALUATION"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/multi_point_eval.hpp
  requiredBy:
  - library/convolution/polynomial_eval_multipoint_eval.hpp
  - library/polynomial/lagrange_interpolation.hpp
  - library/math/product_of_differences.hpp
  - library/math/factorial_large.hpp
  - library/math/sum_i^d_r^i.hpp
  timestamp: '2023-05-11 13:37:15+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/polynomial/multi_point_eval/multi_point_evaluation_2.test.cpp
  - test/src/polynomial/multi_point_eval/multi_point_evaluation.test.cpp
  - test/src/math/product_of_differences/yuki1938.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
documentation_of: library/polynomial/multi_point_eval.hpp
layout: document
title: Multi Point Evaluation
---
## Multi Point Evaluation

$d$ 次多項式 $f(x)$ に対して、$f(t _ 0), \ldots, f(t _ {N - 1})$ の値を $\Theta(N (\log N) ^ 2 + (d + N) \log (d + N))$ 時間で求める。

## アルゴリズム

任意の $t$ に対して、$f(t) = f(x) \bmod (x - t)$ が成り立つ。

<details>
<summary>証明</summary>

(多項式としての除算で) $f(x)$ を $x - t$ で割った商を $Q _ t(x)$, 余りを $R _ t$ とすると、以下が成り立つ。

$$f(x) = Q _ t(x) (x - t _ i) + R _ t.$$

$x = t$ を代入することで、次を得る。

$$f(t) = Q _ t(t) (t - t) + R _ t = R _ t.$$

$R _ t = f(x) \bmod (x - t)$ であるから、示された。(証明終)

</details>

$0\leq l\lt r\lt N$ を満たす整数 $l, r$ に対して、(多項式としての除算で) $f(x)$ を $\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ で割った商を $Q _ {l, r}(x)$, 余りを $R _ {l, r}(x)$ とおく。求めたいのは、全ての $i=0,\ldots,N-1$ に対する $R _ {i, i + 1}(x)$ である。

$l\leq m \leq r$ を満たす任意の整数 $m$ に対して、

$$\begin{aligned}
f(x)
&= Q _ {l, r}(x) (x - t _ l) \cdots (x - t _ {m - 1}) (x - t _ m) \cdots (x - t _ {r - 1}) + R _ {l, r}(x) \\
&= Q _ {l, m}(x) (x - t _ l) \cdots (x - t _ {m - 1})                                      + R _ {l, m}(x) \\
&= Q _ {m, r}(x)                                      (x - t _ m) \cdots (x - t _ {r - 1}) + R _ {m, r}(x).
\end{aligned}$$

より、次が成り立つ。

$$\begin{aligned}
R _ {l, m}(x) &= R _ {l, r}(x) \bmod ((x - t _ l) \cdots (x - t _ {m - 1})), \\
R _ {m, r}(x) &= R _ {l, r}(x) \bmod ((x - t _ m) \cdots (x - t _ {r - 1})). \\
\end{aligned}$$

従って、$R _ {0, N}(x) = f(x) \bmod ((x - t _ 0) \cdots (x - t _ {N - 1}))$ から始めて再帰的に計算することで、全ての $i=0,\ldots,N-1$ に対する $R _ {i, i + 1}(x)$ を求めることが出来る。

必要な $\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ が既に得られていると仮定する。$m = \left\lfloor \dfrac{l + r}{2} \right\rfloor$ として再帰することにすれば、再帰の部分の時間計算量は 

$$T(N) = \begin{cases} 2T(N / 2) + \Theta(N \log N) & \text{if}\ N \gt 1 \\ O(1) & \text{otherwise} \end{cases}$$

を満たす $T$ を用いて $\Theta(T(N))$ と書ける。$T(N) = \Theta(N (\log N) ^ 2)$ である (★) から、この部分の時間計算量は $\Theta(N (\log N) ^ 2)$ である。

<details>
<summary> (★) の補足 </summary>

http://homepages.math.uic.edu/~leon/cs-mcs401-s08/handouts/extended_master_theorem.pdf の $(3')$ で $a = b = 2, \alpha = 1$ とすることで、$T(N) = \Theta(N (\log N) ^ 2)$ を得る。(補足終)

</details>

$\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ に関しては、再帰の終端から根に向かって求めることで全体 $\Theta(N (\log N) ^ 2)$ 時間で計算可能である (マージテク)。

$R _ {0, N}(x)$ は $\Theta((d + N) \log (d + N))$ 時間で計算可能である。

結局、全体 $\Theta(N (\log N) ^ 2 + (d + N) \log (d + N))$ 時間でこのアルゴリズムは動作する。
