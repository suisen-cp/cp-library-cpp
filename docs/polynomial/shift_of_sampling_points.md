---
title: Shift of Sampling Points of Polynomial
documentation_of: //library/polynomial/shift_of_sampling_points.hpp
---
## Shift of Sampling Points of Polynomial

[Shift of Sampling Points of Polynomial](https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial) を解く実装。[hos-lyric さんのコメント](https://github.com/yosupo06/library-checker-problems/issues/680#issuecomment-879544125) を解読しました。

## 解法

### Step 1. $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ {\underline{i}}$ を満たす列 $a=(a _ 0,\ldots,a _ {n-1})$ を求める

ラグランジュの補間公式より、$f$ は次の表示を持つ:

$$\begin{aligned}
f(x)
&= \sum _ {i = 0} ^ {N -1} f(i)\prod _ {j\in [N]\setminus \lbrace i \rbrace}\dfrac{x - j}{i - j} \newline
&= \sum _ {i = 0} ^ {N -1} \dfrac{(-1) ^ {n-i-1} \cdot f(i)}{i!\cdot (n-1-i)!} \prod _ {j \in [N] \setminus \lbrace i \rbrace} (x - j).
\end{aligned}$$

見やすさのために $p _ i = \dfrac{(-1) ^ {n-i-1} \cdot f(i)}{i!\cdot (n-1-i)!}$ とすると、次のように書くことができる。

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
&= \sum _ {j = 0} ^ {k} \binom{k}{j} \sum _ {i = 0} ^ {N - 1 - j} a' _ {(N - 1 - j) - i}\cdot \dfrac{c ^ {\underline{i}}}{i!} && (a' _ i := a _ {N - i - 1} \cdot (n - i - 1)!) \newline
&= \sum _ {j = 0} ^ {k} \binom{k}{j} b _ {N - 1 - j} && (b _ i := \sum _ {j = 0} ^ i a' _ {i - j}\cdot \dfrac{c ^ {\underline{j}}}{j!}) \newline
&= k! \sum _ {j = 0} ^ k \dfrac{b _ {N - 1 - j}}{j!} \cdot \dfrac{1}{(k - j)!}.
\end{aligned}$$

途中で定義した $b$ は畳み込みの形をしているので $O(N \log N)$ 時間で計算することができる。また、$c ^ {\underline{i}}$ に関しては $i$ の昇順に計算することで必要な部分を全体 $O(N)$ 時間で列挙できる。

最後の式も畳み込みの形をしているので $O((M + N) \log (M + N))$ 時間で計算することができる。

以上より、全体 $O((M + N) \log (M + N))$ 時間で問題を解くことができた。
