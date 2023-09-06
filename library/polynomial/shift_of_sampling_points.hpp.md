---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/sum_i^d_r^i.hpp
    title: $\displaystyle \sum _ i i ^ d r ^ i$
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
    title: test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
    title: test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/shift_of_sampling_points.hpp\"\n\n\n\n\
    #include <vector>\n#include <atcoder/convolution>\n\n#line 1 \"library/math/factorial.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, typename U = T>\n    struct factorial {\n\
    \        factorial() = default;\n        factorial(int n) { ensure(n); }\n\n \
    \       static void ensure(const int n) {\n            int sz = _fac.size();\n\
    \            if (n + 1 <= sz) return;\n            int new_size = std::max(n +\
    \ 1, sz * 2);\n            _fac.resize(new_size), _fac_inv.resize(new_size);\n\
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
    \ suisen\n\n\n#line 8 \"library/polynomial/shift_of_sampling_points.hpp\"\n\n\
    namespace suisen {\n    template <typename mint>\n    std::vector<mint> shift_of_sampling_points(const\
    \ std::vector<mint>& ys, mint t, int m) {\n        const int n = ys.size();\n\
    \        factorial<mint> fac(std::max(n, m));\n\n        std::vector<mint> b =\
    \ [&] {\n            std::vector<mint> f(n), g(n);\n            for (int i = 0;\
    \ i < n; ++i) {\n                f[i] = ys[i] * fac.fac_inv(i);\n            \
    \    g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);\n            }\n            std::vector<mint>\
    \ b = atcoder::convolution(f, g);\n            b.resize(n);\n            return\
    \ b;\n        }();\n        std::vector<mint> e = [&] {\n            std::vector<mint>\
    \ c(n);\n            mint prd = 1;\n            std::reverse(b.begin(), b.end());\n\
    \            for (int i = 0; i < n; ++i) {\n                b[i] *= fac.fac(n\
    \ - i - 1);\n                c[i] = prd * fac.fac_inv(i);\n                prd\
    \ *= t - i;\n            }\n            std::vector<mint> e = atcoder::convolution(b,\
    \ c);\n            e.resize(n);\n            return e;\n        }();\n       \
    \ std::reverse(e.begin(), e.end());\n        for (int i = 0; i < n; ++i) {\n \
    \           e[i] *= fac.fac_inv(i);\n        }\n\n        std::vector<mint> f(m);\n\
    \        for (int i = 0; i < m; ++i) f[i] = fac.fac_inv(i);\n        std::vector<mint>\
    \ res = atcoder::convolution(e, f);\n        res.resize(m);\n        for (int\
    \ i = 0; i < m; ++i) res[i] *= fac.fac(i);\n        return res;\n    }\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_SHIFT_OF_SAMPLING_POINTS\n#define SUISEN_SHIFT_OF_SAMPLING_POINTS\n\
    \n#include <vector>\n#include <atcoder/convolution>\n\n#include \"library/math/factorial.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint>\n    std::vector<mint> shift_of_sampling_points(const\
    \ std::vector<mint>& ys, mint t, int m) {\n        const int n = ys.size();\n\
    \        factorial<mint> fac(std::max(n, m));\n\n        std::vector<mint> b =\
    \ [&] {\n            std::vector<mint> f(n), g(n);\n            for (int i = 0;\
    \ i < n; ++i) {\n                f[i] = ys[i] * fac.fac_inv(i);\n            \
    \    g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);\n            }\n            std::vector<mint>\
    \ b = atcoder::convolution(f, g);\n            b.resize(n);\n            return\
    \ b;\n        }();\n        std::vector<mint> e = [&] {\n            std::vector<mint>\
    \ c(n);\n            mint prd = 1;\n            std::reverse(b.begin(), b.end());\n\
    \            for (int i = 0; i < n; ++i) {\n                b[i] *= fac.fac(n\
    \ - i - 1);\n                c[i] = prd * fac.fac_inv(i);\n                prd\
    \ *= t - i;\n            }\n            std::vector<mint> e = atcoder::convolution(b,\
    \ c);\n            e.resize(n);\n            return e;\n        }();\n       \
    \ std::reverse(e.begin(), e.end());\n        for (int i = 0; i < n; ++i) {\n \
    \           e[i] *= fac.fac_inv(i);\n        }\n\n        std::vector<mint> f(m);\n\
    \        for (int i = 0; i < m; ++i) f[i] = fac.fac_inv(i);\n        std::vector<mint>\
    \ res = atcoder::convolution(e, f);\n        res.resize(m);\n        for (int\
    \ i = 0; i < m; ++i) res[i] *= fac.fac(i);\n        return res;\n    }\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_SHIFT_OF_SAMPLING_POINTS\n"
  dependsOn:
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/polynomial/shift_of_sampling_points.hpp
  requiredBy:
  - library/math/sum_i^d_r^i.hpp
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/polynomial/shift_of_sampling_points/shift_of_sampling_points_of_polynomial.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial.test.cpp
  - test/src/math/sum_i^d_r^i/sum_of_exponential_times_polynomial_limit.test.cpp
documentation_of: library/polynomial/shift_of_sampling_points.hpp
layout: document
title: Shift of Sampling Points of Polynomial
---
## Shift of Sampling Points of Polynomial

[Shift of Sampling Points of Polynomial](https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial) を解く実装。[hos-lyric さんのコメント](https://github.com/yosupo06/library-checker-problems/issues/680#issuecomment-879544125) を解読しました。

## 解法

### Step 1. $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ {\underline{i}}$ を満たす列 $a=(a _ 0,\ldots,a _ {N-1})$ を求める

ラグランジュの補間公式より、$f$ は次の表示を持つ:

$$\begin{aligned}
f(x)
&= \sum _ {i = 0} ^ {N -1} f(i)\prod _ {j\in [N]\setminus \lbrace i \rbrace}\dfrac{x - j}{i - j} \newline
&= \sum _ {i = 0} ^ {N -1} \dfrac{(-1) ^ {N-i-1} \cdot f(i)}{i!\cdot (N-1-i)!} \prod _ {j \in [N] \setminus \lbrace i \rbrace} (x - j).
\end{aligned}$$

見やすさのために $p _ i = \dfrac{(-1) ^ {N-i-1} \cdot f(i)}{i!\cdot (N-1-i)!}$ とすると、次のように書くことができる。

$$f(x) = \sum _ {i = 0} ^ {N - 1} p _ i \prod _ {j \in [N] \setminus \lbrace i \rbrace} (x - j).$$

最高次の係数に注目することで $\displaystyle a _ {N - 1} = \sum _ {i = 0} ^ {N - 1} p _ i$ を得る。$f(x) - a _ {N - 1} x ^ {\underline{N - 1}}$ を計算してみると、

$$\begin{aligned}
f(x) - a _ {N - 1} x ^ {\underline{N - 1}}
&=\sum _ {i = 0} ^ {N - 2} p _ i \cdot (-1) \cdot (N - 1 - i) \prod _ {j \in [N - 1]\setminus\lbrace i \rbrace} (x - j) \newline
&=\sum _ {i = 0} ^ {N - 2}p' _ i \prod _ {j \in [N - 1]\setminus\lbrace i \rbrace} (x - j) && (p' _ i := p _ i \cdot (-1) \cdot (N - 1 - i))
\end{aligned}$$

となり、サイズが $1$ だけ小さい問題が得られる。これを繰り返すことで、次を得る。

$$a _ {N - k} = (-1) ^ {k + 1}\sum _ {i = 0} ^ {N - k} p _ i \cdot \dfrac{(N - i - 1)!}{(N - i - k)!}.$$

これを整理して、次を得る。

$$a _ i = \sum _ {j = 0} ^ i \dfrac{f(j)}{j!} \cdot \dfrac{(-1) ^ {i - j}}{(i - j) !}.$$

これは畳み込みで高速化できる形なので、$a$ を $O(N \log N)$ 時間で計算することができた。

### Step 2. $k = 0, \ldots, M-1$ に対する $f(c + k)$ の計算

下降階乗冪に関する以下の恒等式が重要。

$$(a + b) ^ {\underline{n}} = \sum _ {i = 0} ^ n \binom{n}{i} a ^ {\underline{i}} b ^ {\underline{n - i}}.$$

Step 1 で $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ {\underline{i}}$ という表示を得ているので、これに $x = c + k$ を代入して整理すると、次のようになる。([Polynomial Taylor Shift](https://judge.yosupo.jp/problem/polynomial_taylor_shift) のときと全く同じように変形する)

$$\begin{aligned}
f(c+k)
&= \sum _ {i = 0} ^ {N - 1} a _ i (c + k) ^ {\underline{i}} \newline
&= \sum _ {i = 0} ^ {N - 1} a _ i \sum _ {j = 0} ^ i \binom{i}{j} c ^ {\underline{i - j}} k ^ {\underline{j}} \newline
&= \sum _ {j = 0} ^ {N - 1} \dfrac{k ^ {\underline{j}}}{j!} \sum _ {i = j} ^ {N - 1} (a _ i \cdot i!)\cdot \dfrac{c ^ {\underline{i - j}}}{(i - j)!} \newline
&= \sum _ {j = 0} ^ {k} \binom{k}{j} \sum _ {i = 0} ^ {N - 1 - j} (a _ {i + j} \cdot (i + j)!)\cdot \dfrac{c ^ {\underline{i}}}{i!} \newline
&= \sum _ {j = 0} ^ {k} \binom{k}{j} \sum _ {i = 0} ^ {N - 1 - j} a' _ {(N - 1 - j) - i}\cdot \dfrac{c ^ {\underline{i}}}{i!} && (a' _ i := a _ {N - i - 1} \cdot (N - i - 1)!) \newline
&= \sum _ {j = 0} ^ {k} \binom{k}{j} b _ {N - 1 - j} && (b _ i := \sum _ {j = 0} ^ i a' _ {i - j}\cdot \dfrac{c ^ {\underline{j}}}{j!}) \newline
&= k! \sum _ {j = 0} ^ k \dfrac{b _ {N - 1 - j}}{j!} \cdot \dfrac{1}{(k - j)!}.
\end{aligned}$$

途中で定義した $b$ は畳み込みの形をしているので $O(N \log N)$ 時間で計算することができる。また、$c ^ {\underline{i}}$ に関しては $i$ の昇順に計算することで必要な部分を全体 $O(N)$ 時間で列挙できる。

最後の式も畳み込みの形をしているので $O((M + N) \log (M + N))$ 時間で計算することができる。

以上より、全体 $O((M + N) \log (M + N))$ 時間で問題を解くことができた。
