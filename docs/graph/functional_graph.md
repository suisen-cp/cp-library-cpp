---
title: Functional Graph
documentation_of: //library/graph/functional_graph.hpp
---
## Functional Graph

全ての頂点の出次数がちょうど $1$ のグラフ。$[N] := \\\{0, \ldots, N - 1\\\}$ としたとき、$N$ 頂点の Functional Graph の集合と関数 $f : [N] \to [N]$ の集合は 1 対 1 対応する。

### `Functional Graph` がサポートする関数

- `std::vector<int> kth_iterate(long long k) const`
  
  $f$ の $k$ 回合成 $\underbrace{f\circ f \circ \cdots \circ f}_{k}$ を $f^k$ として、各 $i\in[N]$ に対する $f ^ k(i)$ を計算する。詳細は https://noshi91.hatenablog.com/entry/2019/09/22/114149 を参照するとよい。

  計算量: $O(N)$
- `std::vector<InfinitePath> infinite_paths() const`
  
  Functional Graph の特徴として、任意の $i\in [N]$ に対してある非負整数 $k _ i$ と正整数 $t _ i$ が存在して、$p \geq k _ i$ ならば $f ^ p(i) = f ^ {p + t _ i}(i)$ を満たす (即ち、ある時点からループに入る)。そのような $k _ i, t _ i$ のうち最小のものを $k _ i', t _ i'$ とする。本関数では、全ての $i$ に対する $k _ i', t _ i'$ および $f ^ {k _ i'}(i)$ を計算する。

  返り値は `std::vector<InfinitePath>` であるが、`InfinitePath` は以下のメンバを持つ。
  - `head_v` : $i$ を表す
  - `heav_len` : $k _ i'$ を表す
  - `loop_v` : $f ^ {k _ i'}(i)$ を表す
  - `loop_len` : $t _ i'$ を表す
  
  計算量: $O(N)$
- `Doubling doubling(long long max_step) const`
  
  ダブリングテーブルを構築する。引数の `max_step` はダブリングにおける最大ステップ数。返り値の `Doubling` については後述。

  計算量 : $O(N \log \max \mathrm{step})$
- `template <typename T, T(*op)(T, T), T(*e)()> DoublingSum<T, op, e> doubling(long long max_step, const std::vector<T>& dat) const `
  
  パス上の辺の値を順番通りに fold した値を計算できるダブリングテーブルを構築する。

  テンプレート引数
  - `T` : 辺に書かれた値の型
  - `op` : 二項演算
  - `e` : 単位元 (を与える関数)
  
  引数
  - `max_step`: ダブリングにおける最大ステップ数
  - `dat`: 各辺 $(i,f(i))$ に書かれた値を表す `std::vector`
  
  ただし、$(T,op)$ がモノイドであることを要求する。返り値の型 `DoublingSum` については後述。

  計算量 : $O(N \log \max \mathrm{step})$

### `Doubling` がサポートする関数

- `int query(int u, long long d) const`
  
  $f ^ d(u)$ を計算して返す。

  計算量: $O(\log d)$
- `template <typename Pred> BinarySearchResult max_step(int u, Pred &&pred) const`
  
  引数に与えた $\mathrm{pred} : [N] \to \\\{\mathrm{true},\mathrm{false}\\\}$ に対して、$x := \max \\\{d \mid \mathrm{pred}(f ^ d (u)) = \mathrm{true}\\\}$ を計算する。$x$ が `doubling` 関数に与えた `max_step` 以上であるような場合は、`max_step` 以上の不定値を返す。
  
  注意点として、$\mathrm{pred}(u) = \mathrm{true}$ および $\mathrm{pred}(f ^ d(u)) = \mathrm{false} \Rightarrow \mathrm{pred}(f ^ {d + 1}(u)) = \mathrm{false}$ が成り立つこと (単調性) を要求する。
  
  返り値の `BinarySearchResult` は以下のメンバを持つ。
  - `v` : $f ^ x(u)$ を表す。
  - `step` : $x$ を表す。$x \geq \max \mathrm{step}$ の場合は、`max_step` 以上の不定値となる。
  
  計算量: $O(T \cdot \log \max \mathrm{step})$ ($T$ は $\mathrm{pred}$ の計算時間)
- `template <typename Pred> std::optional<BinarySearchResult> step_until(int u, Pred &&f) const`
  
  引数に与えた $\mathrm{pred} : [N] \to \\\{\mathrm{true},\mathrm{false}\\\}$ に対して、$x := \min \\\{d \mid \mathrm{pred}(f ^ d (u)) = \mathrm{true}\\\}$ を計算する。$x$ が `doubling` 関数に与えた `max_step` 以上であるような場合は、`std::nullopt` を返す。

  注意点として、$\mathrm{pred}(f ^ d(u)) = \mathrm{true} \Rightarrow \mathrm{pred}(f ^ {d + 1}(u)) = \mathrm{true}$ が成り立つこと (単調性) を要求する。特に、$\mathrm{pred}(u) = \mathrm{false}$ でなくてもよい。

  計算量: $O(T \cdot \log \max \mathrm{step})$ ($T$ は $\mathrm{pred}$ の計算時間)

### `DoublingSum` がサポートする関数

辺 $(i, f(i))\in [N]$ に書かれた値を $A _ i$ と書く。また、$op(A _ {i _ 1}, A _ {i _ 2})$ を $A _ {i _ 1} \odot A _ {i _ 2}$ と書く。さらに、$\displaystyle \bigodot _ {j = 1} ^ k A _ {i _ j}$ は $A _ {i _ 1} \odot A _ {i _ 2} \odot \cdots \odot A _ {i _ k}$ を表す。また、単位元を $e$ と書く。

- `Result query(int u, long long d) const`
  
  $f ^ d(u)$ および $\displaystyle \bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}$ を計算する。返り値の `Result` は以下のメンバを持つ。

  - `v` : $f ^ d(u)$ を表す。
  - `sum` : $\displaystyle \bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}$ を表す。

  計算量: $O(T\cdot \log d)$ ($T$ は二項演算 $\odot$ の計算量)
- `template <typename Pred> BinarySearchResult max_step(int u, Pred &&pred) const`
  
  引数に与えた $\mathrm{pred} : T \to \\\{\mathrm{true},\mathrm{false}\\\}$ ($T$ は $A _ i$ の型) に対して、$x := \max \\\{d \mid \mathrm{pred}(\bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}) = \mathrm{true}\\\}$ を計算する。$x$ が `doubling` 関数に与えた `max_step` 以上であるような場合は、`max_step` 以上の不定値を返す。
  
  注意点として、$\mathrm{pred}(e) = \mathrm{true}$ および $\mathrm{pred}(\bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}) = \mathrm{false} \Rightarrow \mathrm{pred}(\bigodot _ {i = 0} ^ {d} A _ {f ^ i(u)}) = \mathrm{false}$ が成り立つこと (単調性) を要求する。
  
  返り値の `BinarySearchResult` は以下のメンバを持つ。
  - `v` : $f ^ x(u)$ を表す。
  - `sum` : $\displaystyle \bigodot _ {i = 0} ^ {x - 1} A _ {f ^ i(u)}$ を表す。
  - `step` : $x$ を表す。$x \geq \max \mathrm{step}$ の場合は、`max_step` 以上の不定値となる。
- `template <typename Pred> std::optional<BinarySearchResult> step_until(int u, Pred &&f) const`
  
  引数に与えた $\mathrm{pred} : T \to \\\{\mathrm{true},\mathrm{false}\\\}$ に対して、$x := \min \\\{d \mid \mathrm{pred}(\bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}) = \mathrm{true}\\\}$ を計算する。$x$ が `doubling` 関数に与えた `max_step` 以上であるような場合は、`std::nullopt` を返す。

  注意点として、$\mathrm{pred}(\bigodot _ {i = 0} ^ {d - 1} A _ {f ^ i(u)}) = \mathrm{true} \Rightarrow \mathrm{pred}(\bigodot _ {i = 0} ^ {d} A _ {f ^ i(u)}) = \mathrm{true}$ が成り立つこと (単調性) を要求する。特に、$\mathrm{pred}(e) = \mathrm{false}$ でなくてもよい。