---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multiplicative_convolution_mod_2^n.hpp/mul_mod2n_convolution.test.cpp
    title: test/src/convolution/multiplicative_convolution_mod_2^n.hpp/mul_mod2n_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/multiplicative_convolution_mod_2^n.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <vector>\n\n#include <atcoder/convolution>\n\
    \nnamespace suisen {\n    namespace internal::mul_mod_2_n_convolution {\n    \
    \    template <typename T, int n>\n        std::vector<T> multiplicative_convolution_mod_2_n_naive(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n            static constexpr\
    \ int mask = (1 << n) - 1;\n            std::vector<T> c(1 << n);\n          \
    \  for (int i = 0; i < 1 << n; ++i) for (int j = 0; j < 1 << n; ++j) c[(i * j)\
    \ & mask] += a[i] * b[j];\n            return c;\n        }\n\n        constexpr\
    \ int pow_m1(int x) {\n            return x & 1 ? -1 : +1;\n        }\n    }\n\
    \    template <typename T>\n    std::vector<T> multiplicative_convolution_mod_2_n(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n        using namespace internal::mul_mod_2_n_convolution;\n\
    \        const int n = [&a] {\n            int n = 0;\n            while (1 <<\
    \ n < int(a.size())) ++n;\n            return n;\n        }();\n        assert(1\
    \ << n == int(a.size()));\n        assert(1 << n == int(b.size()));\n        const\
    \ int mask = (1 << n) - 1;\n        if (n <= 6) {\n            if (n == 0) return\
    \ multiplicative_convolution_mod_2_n_naive<T, 0>(a, b);\n            if (n ==\
    \ 1) return multiplicative_convolution_mod_2_n_naive<T, 1>(a, b);\n          \
    \  if (n == 2) return multiplicative_convolution_mod_2_n_naive<T, 2>(a, b);\n\
    \            if (n == 3) return multiplicative_convolution_mod_2_n_naive<T, 3>(a,\
    \ b);\n            if (n == 4) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 4>(a, b);\n            if (n == 5) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 5>(a, b);\n            if (n == 6) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 6>(a, b);\n        }\n        static constexpr int g = 5;\n        std::vector<int>\
    \ pows(1 << (n - 2));\n        std::vector<int> p(1 << n), q(1 << n), r(1 << n);\n\
    \        for (int i = 0, pow_g = 1; i < 1 << (n - 2); ++i) {\n            pows[i]\
    \ = pow_g;\n            q[pow_g] = i;\n            r[pow_g] = 0;\n           \
    \ q[-pow_g & mask] = i;\n            r[-pow_g & mask] = 1;\n            pow_g\
    \ = (pow_g * g) & mask;\n        }\n        p[0] = n;\n        for (int i = 2;\
    \ i < 1 << n; i += 2) {\n            p[i] = __builtin_ctz(i);\n            const\
    \ int len = 1 << std::max(n - p[i] - 2, 0);\n            q[i] = q[i >> p[i]] &\
    \ (len - 1);\n            r[i] = r[i >> p[i]];\n        }\n\n        std::array<std::vector<std::vector<T>>,\
    \ 2> a2{}, b2{}, c2{};\n        a2[0].resize(n + 1), a2[1].resize(n + 1);\n  \
    \      b2[0].resize(n + 1), b2[1].resize(n + 1);\n        c2[0].resize(n + 1),\
    \ c2[1].resize(n + 1);\n        for (int i = 0; i <= n; ++i) {\n            const\
    \ int len = 1 << std::max(n - i - 2, 0);\n            a2[0][i].resize(len), a2[1][i].resize(len);\n\
    \            b2[0][i].resize(len), b2[1][i].resize(len);\n            c2[0][i].resize(len),\
    \ c2[1][i].resize(len);\n        }\n        for (int i = 0; i < 1 << n; ++i) {\n\
    \            a2[r[i]][p[i]][q[i]] += a[i];\n            b2[r[i]][p[i]][q[i]] +=\
    \ b[i];\n        }\n        auto adjust_size = [](std::vector<T>& v, int len)\
    \ {\n            for (int i = len; i < int(v.size()); ++i) v[i & (len - 1)] +=\
    \ v[i];\n            v.resize(len);\n        };\n        \n        std::vector<T>\
    \ c(1 << n);\n        constexpr int naive_threshold_log = 4;\n        for (int\
    \ pi = 0; pi <= n; ++pi) for (int pj = 0; pj <= n; ++pj) {\n            const\
    \ int k = pi + pj;\n            const int len = 1 << std::max(n - k - 2, 0);\n\
    \            if (len <= 1 << naive_threshold_log) {\n                for (int\
    \ f = 0; f < 2; ++f) {\n                    adjust_size(a2[f][pi], len);\n   \
    \                 adjust_size(b2[f][pj], len);\n                }\n          \
    \      for (int af = 0; af < 2; ++af) for (int bf = 0; bf < 2; ++bf) {\n     \
    \               for (int ai = 0; ai < len; ++ai) for (int bi = 0; bi < len; ++bi)\
    \ {\n                        int j = (pow_m1(af ^ bf) * ((long long) pows[(ai\
    \ + bi) & (len - 1)] << k)) & mask;\n                        c[j] += a2[af][pi][ai]\
    \ * b2[bf][pj][bi];\n                    }\n                }\n              \
    \  continue;\n            }\n            for (int f = 0; f < 2; ++f) {\n     \
    \           adjust_size(a2[f][pi], len);\n                adjust_size(b2[f][pj],\
    \ len);\n                atcoder::internal::butterfly(a2[f][pi]);\n          \
    \      atcoder::internal::butterfly(b2[f][pj]);\n            }\n            const\
    \ T z = T{ len }.inv();\n            for (int i = 0; i < len; ++i) {\n       \
    \         T &au = a2[0][pi][i], &av = a2[1][pi][i];\n                T &bu = b2[0][pj][i],\
    \ &bv = b2[1][pj][i];\n                c2[0][k][i] += (au * bu + av * bv) * z;\n\
    \                c2[1][k][i] += (au * bv + av * bu) * z;\n                au *=\
    \ z, av *= z, bu *= z, bv *= z;\n            }\n            for (int f = 0; f\
    \ < 2; ++f) {\n                atcoder::internal::butterfly_inv(a2[f][pi]);\n\
    \                atcoder::internal::butterfly_inv(b2[f][pj]);\n            }\n\
    \        }\n        for (int f = 0; f < 2; ++f) for (int k = 0; k < n - 2 - naive_threshold_log;\
    \ ++k) {\n            const int len = 1 << (n - k - 2);\n            atcoder::internal::butterfly_inv(c2[f][k]);\n\
    \            for (int i = 0; i < len; ++i) {\n                int j = (pow_m1(f)\
    \ * ((long long) pows[i] << k)) & mask;\n                c[j] += c2[f][k][i];\n\
    \            }\n        }\n        return c;\n    }\n} // namespace suisen\n\n\
    \n\n"
  code: "#ifndef SUISEN_MUL_MOD_2_N_CONVOLUTION\n#define SUISEN_MUL_MOD_2_N_CONVOLUTION\n\
    \n#include <array>\n#include <cassert>\n#include <vector>\n\n#include <atcoder/convolution>\n\
    \nnamespace suisen {\n    namespace internal::mul_mod_2_n_convolution {\n    \
    \    template <typename T, int n>\n        std::vector<T> multiplicative_convolution_mod_2_n_naive(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n            static constexpr\
    \ int mask = (1 << n) - 1;\n            std::vector<T> c(1 << n);\n          \
    \  for (int i = 0; i < 1 << n; ++i) for (int j = 0; j < 1 << n; ++j) c[(i * j)\
    \ & mask] += a[i] * b[j];\n            return c;\n        }\n\n        constexpr\
    \ int pow_m1(int x) {\n            return x & 1 ? -1 : +1;\n        }\n    }\n\
    \    template <typename T>\n    std::vector<T> multiplicative_convolution_mod_2_n(const\
    \ std::vector<T>& a, const std::vector<T>& b) {\n        using namespace internal::mul_mod_2_n_convolution;\n\
    \        const int n = [&a] {\n            int n = 0;\n            while (1 <<\
    \ n < int(a.size())) ++n;\n            return n;\n        }();\n        assert(1\
    \ << n == int(a.size()));\n        assert(1 << n == int(b.size()));\n        const\
    \ int mask = (1 << n) - 1;\n        if (n <= 6) {\n            if (n == 0) return\
    \ multiplicative_convolution_mod_2_n_naive<T, 0>(a, b);\n            if (n ==\
    \ 1) return multiplicative_convolution_mod_2_n_naive<T, 1>(a, b);\n          \
    \  if (n == 2) return multiplicative_convolution_mod_2_n_naive<T, 2>(a, b);\n\
    \            if (n == 3) return multiplicative_convolution_mod_2_n_naive<T, 3>(a,\
    \ b);\n            if (n == 4) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 4>(a, b);\n            if (n == 5) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 5>(a, b);\n            if (n == 6) return multiplicative_convolution_mod_2_n_naive<T,\
    \ 6>(a, b);\n        }\n        static constexpr int g = 5;\n        std::vector<int>\
    \ pows(1 << (n - 2));\n        std::vector<int> p(1 << n), q(1 << n), r(1 << n);\n\
    \        for (int i = 0, pow_g = 1; i < 1 << (n - 2); ++i) {\n            pows[i]\
    \ = pow_g;\n            q[pow_g] = i;\n            r[pow_g] = 0;\n           \
    \ q[-pow_g & mask] = i;\n            r[-pow_g & mask] = 1;\n            pow_g\
    \ = (pow_g * g) & mask;\n        }\n        p[0] = n;\n        for (int i = 2;\
    \ i < 1 << n; i += 2) {\n            p[i] = __builtin_ctz(i);\n            const\
    \ int len = 1 << std::max(n - p[i] - 2, 0);\n            q[i] = q[i >> p[i]] &\
    \ (len - 1);\n            r[i] = r[i >> p[i]];\n        }\n\n        std::array<std::vector<std::vector<T>>,\
    \ 2> a2{}, b2{}, c2{};\n        a2[0].resize(n + 1), a2[1].resize(n + 1);\n  \
    \      b2[0].resize(n + 1), b2[1].resize(n + 1);\n        c2[0].resize(n + 1),\
    \ c2[1].resize(n + 1);\n        for (int i = 0; i <= n; ++i) {\n            const\
    \ int len = 1 << std::max(n - i - 2, 0);\n            a2[0][i].resize(len), a2[1][i].resize(len);\n\
    \            b2[0][i].resize(len), b2[1][i].resize(len);\n            c2[0][i].resize(len),\
    \ c2[1][i].resize(len);\n        }\n        for (int i = 0; i < 1 << n; ++i) {\n\
    \            a2[r[i]][p[i]][q[i]] += a[i];\n            b2[r[i]][p[i]][q[i]] +=\
    \ b[i];\n        }\n        auto adjust_size = [](std::vector<T>& v, int len)\
    \ {\n            for (int i = len; i < int(v.size()); ++i) v[i & (len - 1)] +=\
    \ v[i];\n            v.resize(len);\n        };\n        \n        std::vector<T>\
    \ c(1 << n);\n        constexpr int naive_threshold_log = 4;\n        for (int\
    \ pi = 0; pi <= n; ++pi) for (int pj = 0; pj <= n; ++pj) {\n            const\
    \ int k = pi + pj;\n            const int len = 1 << std::max(n - k - 2, 0);\n\
    \            if (len <= 1 << naive_threshold_log) {\n                for (int\
    \ f = 0; f < 2; ++f) {\n                    adjust_size(a2[f][pi], len);\n   \
    \                 adjust_size(b2[f][pj], len);\n                }\n          \
    \      for (int af = 0; af < 2; ++af) for (int bf = 0; bf < 2; ++bf) {\n     \
    \               for (int ai = 0; ai < len; ++ai) for (int bi = 0; bi < len; ++bi)\
    \ {\n                        int j = (pow_m1(af ^ bf) * ((long long) pows[(ai\
    \ + bi) & (len - 1)] << k)) & mask;\n                        c[j] += a2[af][pi][ai]\
    \ * b2[bf][pj][bi];\n                    }\n                }\n              \
    \  continue;\n            }\n            for (int f = 0; f < 2; ++f) {\n     \
    \           adjust_size(a2[f][pi], len);\n                adjust_size(b2[f][pj],\
    \ len);\n                atcoder::internal::butterfly(a2[f][pi]);\n          \
    \      atcoder::internal::butterfly(b2[f][pj]);\n            }\n            const\
    \ T z = T{ len }.inv();\n            for (int i = 0; i < len; ++i) {\n       \
    \         T &au = a2[0][pi][i], &av = a2[1][pi][i];\n                T &bu = b2[0][pj][i],\
    \ &bv = b2[1][pj][i];\n                c2[0][k][i] += (au * bu + av * bv) * z;\n\
    \                c2[1][k][i] += (au * bv + av * bu) * z;\n                au *=\
    \ z, av *= z, bu *= z, bv *= z;\n            }\n            for (int f = 0; f\
    \ < 2; ++f) {\n                atcoder::internal::butterfly_inv(a2[f][pi]);\n\
    \                atcoder::internal::butterfly_inv(b2[f][pj]);\n            }\n\
    \        }\n        for (int f = 0; f < 2; ++f) for (int k = 0; k < n - 2 - naive_threshold_log;\
    \ ++k) {\n            const int len = 1 << (n - k - 2);\n            atcoder::internal::butterfly_inv(c2[f][k]);\n\
    \            for (int i = 0; i < len; ++i) {\n                int j = (pow_m1(f)\
    \ * ((long long) pows[i] << k)) & mask;\n                c[j] += c2[f][k][i];\n\
    \            }\n        }\n        return c;\n    }\n} // namespace suisen\n\n\
    \n#endif // SUISEN_MUL_MOD_2_N_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/multiplicative_convolution_mod_2^n.hpp
  requiredBy: []
  timestamp: '2022-10-08 20:12:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/multiplicative_convolution_mod_2^n.hpp/mul_mod2n_convolution.test.cpp
documentation_of: library/convolution/multiplicative_convolution_mod_2^n.hpp
layout: document
title: Multiplicative Convolution Mod 2^n ($c_k = \sum_{i\times j \equiv k \pmod{2
  ^ n}} a_i \cdot b_j$)
---
## Multiplicative Convolution Mod 2^n

列 $A=(a _ 0, a _ 1, \ldots, a _ {2 ^ n - 1}), B = (b _ 0, b _ 1, \ldots, b _ {2 ^ n - 1})$ に対して以下で定義される列 $C=(c _ 0, c _ 1, \ldots, c _ {2 ^ n - 1})$ を $\Theta(n 2 ^ n)$ 時間で計算する。

$$c _ k = \sum _ {i\times j \equiv k \pmod{2 ^ n}} a _ i b _ j.$$

実は、$n \geq 3$ を仮定すると、$(\mathbb{Z}/2 ^ n\mathbb{Z}) ^ \ast$ において $\mathrm{ord}(5) = 2 ^ {n - 2}$ が成り立つ $(\star)$。

<details>

<summary>証明</summary>

<div style="margin:10px; padding:10px; border:1px solid black;">

$(\mathbb{Z}/2 ^ n\mathbb{Z}) ^ \ast$ の位数は $\varphi(2 ^ n) = 2 ^ {n - 1}$ であるから、$\mathrm{ord}(5) \mid 2 ^ {n - 1}$ である。従って、$\mathrm{ord}(5) = 2 ^ {n - 2}$ を示すには以下の $(1), (2)$ を代わりに示せば十分。

$$5 ^ {2 ^ {n - 3}} \not\equiv 1 \pmod{2 ^ n}, \tag{1}$$
$$5 ^ {2 ^ {n - 2}} \equiv 1 \pmod{2 ^ n}.     \tag{2}$$

<ul>
<li>

$(1)$ の証明

以下、$2$ が正整数 $k$ を割り切る回数を $v_2(k)$ と書く。

$$5 ^ {2 ^ {n - 3}} = (1 + 4) ^ {2 ^ {n - 3}} = 1 + 2 ^ {n - 1} + \sum _ {i = 2} ^ {2 ^ {n - 3}} \binom{2 ^ {n - 3}}{i} 2 ^ {2i}$$

であり、$\displaystyle v_2(i!) = \sum _ {j = 1} ^ \infty \left\lfloor\dfrac{i}{2 ^ j}\right\rfloor \leq \sum _ {j = 1} ^ \infty \dfrac{i}{2 ^ j} \leq i$ を満たすので、$i\geq 3$ において $\displaystyle v_2\left(\binom{2 ^ {n - 3}}{i} 2 ^ {2i}\right)\geq n-3+i\geq n$ が成り立つ。また、実際に計算することで $i=2$ の場合もこれが成り立つことが分かる。従って、次を得る:

$$5 ^ {2 ^ {n - 3}} \equiv 1 + 2 ^ {n - 1} \not\equiv 1 \pmod{2 ^ n}.$$

</li>
<li>

$(2)$ の証明
  
$$5 ^ {2 ^ {n - 2}} = (1 + 4) ^ {2 ^ {n - 2}} = 1 +  \sum _ {i = 1} ^ {2 ^ {n - 2}} \binom{2 ^ {n - 2}}{i} 2 ^ {2i}$$

に対して同様の議論により $i\geq 1$ で $\displaystyle v_2\left(\binom{2 ^ {n - 2}}{i} 2 ^ {2i}\right)\geq n$ が成り立つことが分かり、次を得る:

$$5 ^ {2 ^ {n - 2}} \equiv 1 \pmod{2 ^ n}.$$

</li>
</ul>

</div>

</details>

$n \leq 2$ では $\mathrm{ord}(5) = 1$ であるから、結局 $\mathrm{ord}(5) = 2 ^ {\max(n - 2, 0)}$ となる。

以下、$n \geq 3$ を仮定する。

$(\star)$ より、$5$ によって生成される部分群 $\langle 5 \rangle = \lbrace 5 ^ n \mid n \in \mathbb{Z} \rbrace$ の位数は $2 ^ {n - 2}$ である。簡単な計算により $a \in \langle 5 \rangle \Rightarrow a \equiv 1 \pmod{4}$ が分かるが、$a \equiv 1 \pmod{4}$ を満たす $a\in (\mathbb{Z}/2 ^ n\mathbb{Z}) ^ \ast$ の個数はちょうど $2 ^ {n - 2}$ であるから、$\langle 5 \rangle=\lbrace4k+1 \mid k\in \mathbb{Z}\rbrace$ である。同様にして、$\langle -5\rangle = \lbrace4k-1 \mid k\in \mathbb{Z}\rbrace$ も分かる。

以上より、任意の $a\in \mathbb{Z}/2^n\mathbb{Z}$ に対して $a \equiv (-1) ^ {s _ a} \cdot 2 ^ {p _ a} \cdot 5 ^ {q _ a}$ を満たす整数 $s _ a, p _ a, q _ a$ が存在する。そこで、$a = (s _ a, p _ a, q _ a)$ と書くことにすると、$\mathbb{Z}/2^n\mathbb{Z}$ 上の乗算 $a\times b$ は次のように指数の加算へと変換される。

$$a\times b = (s _ a + s _ b, p _ a + p _ b, q _ a + q _ b).$$

さて、$a\in \mathbb{Z}/2 ^ n\mathbb{Z}$ に対して、$a\equiv 0$ の場合を除いて $p_a$ は一意に定まり、$0$ 以上 $n-1$ 以下の値をとる。ここでは、$0$ については $0=(0, n, 0)$ と扱うことにする。

$P _ x := \lbrace i \in \mathbb{Z}/2 ^ n\mathbb{Z} \mid p _ i = x \rbrace$ として、列 $C ^ {x,y} = (c ^ {x, y} _ 0, c ^ {x, y} _ 1, \ldots, c ^ {x, y} _ {2 ^ n - 1})$ を以下で定義する。

$$
c ^ {x, y} _ k = \sum _ {\overset{\scriptsize i \in P _ x, j \in P _ y,}{i \times j \equiv k \pmod{2 ^ n}}} a _ i b _ j
$$

このとき、$\displaystyle C = \sum _ {x = 0} ^ n \sum _ {y = 0} ^ n C ^ {x, y}$ が成り立つ。以降、$C ^ {x, y}$ の計算を考える。

$x,y$ を固定すると、$i\in P _ x, j \in P _ y$ に対して $p _ {i \times j} = \min(n, x+y)=:p$ は一定の値を取る。従って、$i \times j$ の値を追うにあたって必要な情報は $s _ i, q _ i, s _ j, q _ j$ の値のみである。$s$ は $-1$ の指数であるから、$\bmod\; 2$ で同一視してよい。$q$ に関しては、

$$
2 ^ p 5 ^ q \equiv 2 ^ p 5 ^ {q'} \pmod{2 ^ n} \iff 5 ^ q \equiv 5 ^ {q'} \pmod{2 ^ {n - p}}
$$

より $l _ p :=\max(n - p - 2, 0)$ として $\bmod\; 2 ^ {l _ p}$ で同一視してよい。即ち、$2 \times 2 ^ {l _ p}$ の $2$ 次元 FFT により $C ^ {x, y}$ を $\Theta(l _ p \cdot 2 ^ {l _ p})$ 時間で計算できる。ただし、畳み込みに用いる列を元の $A$ や $B$ から計算すると $\Theta(l _ p \cdot 2 ^ {l _ p} + 2 ^ n)$ となってしまうため、組 $(x,y)$ を適切な順番で走査して差分更新を行う必要がある。

計算量を考える。$x + y \geq n - 2$ の各ケースは $\Theta(1)$ で処理できるので、全体への寄与は $\Theta(n ^ 2)$ である。$x + y \lt n - 2$ の場合については $l _ p = n - 2 - (x + y)$ なので、(定数倍を無視して見積もると) 次のように抑えられる。

$$
\sum _ {z = 0} ^ {n - 3} \sum _ {x + y = z} (n - 2 - z) 2 ^ {n - 2 - z} \leq \sum _ {z = 0} ^ {n - 3} (z + 1) (n - 2 - z) 2 ^ {n - 2 - z} = \Theta(n\cdot 2 ^ n)
$$

以上で、全体 $\Theta(n \cdot 2 ^ n)$ 時間で動作するアルゴリズムが構築できた。

## 参考

- https://twitter.com/maspy_stars/status/1447511544053469187
- https://twitter.com/tatyam_prime/status/1447533034396217354
