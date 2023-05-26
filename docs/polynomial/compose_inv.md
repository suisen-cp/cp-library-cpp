---
title: 逆関数
documentation_of: //library/polynomial/compose_inv.hpp
---
## 逆関数

形式的冪級数 $\displaystyle f(x) = \sum _ {i = 0} ^ \infty f _ i x ^ i$ の前 $n$ 項が与えられたときに $g(f(x)) = f(g(x)) = x$ を満たす形式的冪級数 $g(x)$ の前 $n$ 項を計算するライブラリ。

ただし $f _ 0 = 0$ および $f _ 1\neq 0$ を仮定する。

## アルゴリズム

$B := \lceil \sqrt{n} \rceil$ と定めると、次が成り立つ。

$$g(f(x)) \equiv \sum _ {i = 0} ^ {n - 1} g _ i (f(x)) ^ i \equiv \sum _ {q = 0} ^ {B - 1}x ^ {qB} ((f(x) / x) ^ B) ^ q \sum _ {r = 0} ^ {B - 1} g _ {qB + r} x ^ r (f(x) / x) ^ {r} \pmod{x ^ n}.$$

$h _ r(x) := (f(x) / x) ^ r \bmod x ^ n \ (r=0,1,\ldots,B-1)$ および $H _ q(x) := ((f(x) / x) ^ B) ^ q\bmod x ^ n\ (q=0,1,\ldots,B-1)$ を前計算しておく。この前計算は $O(Bn\log n) = O(n ^ {3/2} \log n)$ 時間で可能である。

$H _ q,h _ r$ を用いて $g(f(x))$ を書き直すと次のようになる。

$$g(f(x)) \equiv \sum _ {q = 0} ^ {B - 1}x ^ {qB} H _ q(x) \sum _ {r = 0} ^ {B - 1} g _ {qB + r} x ^ r h _ r(x) \pmod{x ^ n}.$$

係数 $g _ 0, \ldots, g _ {qB - 1}$ の値が既知として、係数 $g _ {qB}, \ldots, g _ {(q + 1)B - 1}$ を得ることを考える。

$g(f(x)) = x$ より $g _ {qB}, \ldots, g _ {(q + 1)B - 1}$ は次を満たす。

$$x ^ {qB} H _ q(x) \sum _ {r = 0} ^ {B - 1} g _ {qB + r} x ^ r h _ r(x) \equiv x - \sum _ {q' = 0} ^ {q - 1}x ^ {q'B} H _ {q'}(x) \sum _ {r = 0} ^ {B - 1} g _ {q'B + r} x ^ r h _ r(x) \pmod{x ^ {(q + 1)B}}.$$

$\displaystyle I _ q(x) := x - \sum _ {q' = 0} ^ {q - 1}x ^ {q'B} H _ {q'}(x) \sum _ {r = 0} ^ {B - 1} g _ {q'B + r} x ^ r h _ r(x)$ とおいて整理することで次を得る。

$$\sum _ {r = 0} ^ {B - 1} g _ {qB + r} x ^ r h _ r(x) \equiv \dfrac{1}{H _ q(x)} \cdot \dfrac{I _ q(x)}{x ^ {qB}} \pmod{x ^ B}.$$

右辺を改めて $J _ q(x)$ とおく。左辺の $x ^ r$ の係数は $g _ {qB}, \ldots, g _ {qB + r}$ のみから定まり、次が成り立つ。

$$g _ {qB + r} = (\lbrack x ^ 0 \rbrack h _ r(x)) ^ {-1} \left((\lbrack x ^ r \rbrack J _ q(x)) - \sum _ {r' = 0} ^ {r - 1} g _ {qB + r'} (\lbrack x ^ {r - r'}\rbrack h _ {r'}(x)) \right).$$

($I _ q(x)$ が得られていると仮定すれば) $J _ q(x) \bmod x ^ B$ の計算は $O(B \log B)$ 時間で可能なので、$g _ {qB}, \ldots, g _ {(q + 1)B - 1}$ の計算は $O(B ^ 2) = O(n)$ 時間となる。

$I _ q(x)$ に関しては $\displaystyle I _ {q + 1}(x) = I _ q(x) - x ^ {qB} H _ q(x) \sum _ {r = 0} ^ {B - 1} g _ {qB + r} x ^ r h _ r(x)$ を用いて更新すれば、各々 $O(Bn + n \log n) = O(n ^ {3/2})$ 時間で計算できる。

結局、全体の計算量は $I _ q$ の更新がボトルネックとなり $O(Bn ^ {3/2}) = O(n ^ 2)$ 時間である。