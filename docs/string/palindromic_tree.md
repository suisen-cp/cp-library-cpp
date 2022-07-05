---
title: Palindromic Tree (回文木)
documentation_of: //library/string/palindromic_tree.hpp
---
## Palindromic Tree (回文木)

**回文木 (Palindromic Tree)** は、文字列 $S$ の回文部分文字列を効率的に扱うデータ構造である。$\sigma$ を文字種数として、$O(\vert S\vert \log \sigma)$ 時間で構築可能である。

以下、$S_r$ を $S$ の $r$ 文字目までを取り出して出来る文字列とする。また、$S$ の最長の回文接尾辞 (Longest Suffix-Palindrome; LSP) を $\mathrm{LSP}(S)$ と書く。

回文木は回文を表す節点と節点間を結ぶ有向 link からなる。節点集合は長さ $-1,0$ の文字列を表す節点 $2$ 個と、各回文部分文字列と対応する節点からなる。各節点 $v$ は以下の情報を持つ。節点 $v$ が表す回文を $P_v$ とおく。

- $\mathrm{child}(c):$ 回文 $c\cdot P_v\cdot c$ を表す節点への link。特に、$-1$ 節点では回文 $c$ への link、$0$ 節点では回文 $c\cdot c$ への link である。ただし、$c\cdot P_v\cdot c$ が $S$ の部分文字列として現れないなら $\mathrm{child}(c)$ は定義されない。
- $\mathrm{suffix\\_link}:$ $P_v$ の suffix のうち、$P_v$ より短い最長の回文を表す節点への link。特に、$-1$ 節点では $-1$ 節点への link、$0$ 節点では $-1$ 節点への link である。
- $\mathrm{length}:$ $\vert P_v\vert$
- $\mathrm{multiplicity}:$ $\mathrm{LSP}(S_i) = P_v$ となる $1\leq i\leq \vert S\vert$ の個数。**$P_v$ が部分文字列として現れる回数ではないことに注意。**

## 回文木の性質

節点集合を $V$ とおく。child により張られる link の集合を $E_{\mathrm{child}}$、 suffix link により張られる link の集合を $E_{\mathrm{suffix}}$ とおく。link の集合 $E$ に対して、すべての link を逆向きにして得られる辺集合を $\overline{E}$ で表す。

- $\vert V\vert \leq\vert S\vert +2\ (\star)$
- $\vert E_{\mathrm{child}}\vert \leq \vert S\vert$
- $S$ に含まれる回文部分文字列の個数は、$\vert V\vert -2$ 個。$-2$ しているのは、長さ $-1,0$ の節点が存在するため。
- 有向グラフ $D(V,E_{\mathrm{child}})$ は $-1$ 節点と $0$ 節点をそれぞれ根とする $2$ つの有向木 $T_{-1},T_0$ の和、即ち森である。$T_{-1}$ は長さが奇数の回文、$T_0$ は長さが偶数の回文からなる。
- 有向グラフ $D(V,\overline{E_{\mathrm{suffix}}})$ から辺 $(-1,-1)$ を除いたグラフは、$-1$ 節点を根とする有向木 $T_\mathrm{suffix}$ を成す。
    - 添字 $i$ で終わる回文部分文字列の個数は、$\mathrm{LSP}(S_i)$ を表す節点の $T_\mathrm{suffix}$ における深さに一致する。
    - $S$ における $P_v$ の出現回数は、$T_{\mathrm{suffix}}$ における $v$ を根とする部分木の $\mathrm{multiplicity}$ の和に一致する。
- 有向グラフ $D(V,\overline{E_{\mathrm{child}}}\cup E_{\mathrm{suffix}})$ において、$u\in V$ から $v\in V$ から到達可能であることは、$v$ が $u$ の部分文字列であることと同値である。
    - 例えば $v=bcdcdcb,u=cdc$ の例を考える。$u$ から suffix link を辿ることで $u$ の先頭に $cd$ を付加してできる回文 $cdcdc$ を得、その後 $\mathrm{child}(b)$ の link を辿って両端に $b$ を追加することで $v=bcdcdcb$ を得る。
    - $v$ の中心またはそれよりも右側に $u$ の中心が存在するようにできることから、上記の構成を一般化できる。
    - この事実を用いる問題: [AtCoder Beginner Contest 237 Ex - Hakata](https://atcoder.jp/contests/abc237/tasks/abc237_h)

$(\star)$ は回文部分文字列に関する以下の事実から従う。証明は https://hackmd.io/@tatyam-prime/pallindromes などを参照。

> 任意の文字列 $S$ に対して、$S$ の非空な回文部分文字列の個数は $\vert S\vert$ 以下である。

## 仕様

- 回文木の各節点には $0$ から順に非負整数が id として振られている
  - 特に、$-1$ 節点には id として $0$ が、$0$ 節点には id として $1$ が振られている。
- `add` 関数に $i$ 文字目を与えたときの返り値は $\mathrm{LSP}(S_i)$ を表す節点に振られた id である
- 節点 $v$ と節点 $p:=v.\mathrm{ suffix\_link }$ に関して、$v$ に振られた id は $p$ に振られた id よりも大きい。即ち、例えば $T_{\mathrm{suffix}}$ に対して葉から値を確定させる DP は単に id の降順に見ればよい。逆に、根から値を決めていく場合は id の昇順に見ればよい。
- 同様に、節点 $p$ と $v:=p.\mathrm{child}(c)$ に関して、($v$ が定義されているならば) $v$ に振られた id は $p$ に振られた id よりも大きい。
- `PalindromicTree` は各節点で $\mathrm{child}$ を `std::map` で管理するバージョンである。基本的にはこれを用いればよい。
- `PalindromicTreeArr` は各節点で $\mathrm{child}$ を `std::array` で管理するバージョンである。01 文字列など、文字種が極端に少ないことが分かっている場合はこれを用いればよい。
- `PalindromicTreeVec` は各節点で $\mathrm{child}$ を `std::vector` で管理するバージョンである。使う場面は無さそう。

## 参考文献

- [Parindromic Tree - math314のブログ](https://math314.hateblo.jp/entry/2016/12/19/005919) が非常に分かりやすい。