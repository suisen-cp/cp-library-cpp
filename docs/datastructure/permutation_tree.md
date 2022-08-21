---
title: Permutation Tree
documentation_of: //library/datastructure/permutation_tree.hpp
---
## Permutation Tree

$[l,r]:=\{l,l+1,\ldots,r\}$

$\sigma$ : $[1,n]$ の順列

$\sigma([l,r]) = \{\sigma(l),\ldots,\sigma(r)\}$

$[l,r]$ が common interval: $\exists x,y\in [1,n]\; \text{s.t.}\; \sigma([l,r])=[x,y]$

common interval の集合 : $\mathcal{F}$

$[l,r]\in\mathcal{F}$ が Right-Strong Interval : $l\lt l'\leq r \lt r'$ ならば $[l',r']\notin\mathcal{F}$ (i.e. $l$ を含まず $r$ をまたぐような common interval がない)

$i$ に対して $r\in [i,n]$ が useless : 任意の $l\leq i$ に対して $[l,r]$ は right-strong interval でない

$\mathrm{Select}(i) = \{j \mid [i,j]\in\mathcal{F} \text{が right-strong interval} \}$

補題 1.

$m_i = \max\{j\mid [i,j]\in\mathcal{F} \}$ とすると、以下の 1,2 が成立

1. $\max \mathrm{Select}(i) = m_i$
2. $i\lt r\lt m_{i+1}$ なる $r$ は $i$ に対して useless

証明.

1. 背理法。$i \lt i' \leq m \lt m'$ で $[i',m']\in\mathcal{F}$ とすると $[i,m']\in\mathcal{F}$ で $m_i$ の最大性に矛盾。
2. $l\lt i+1\leq r\lt m_{i+1}$ かつ $[i+1,m_{i+1}]\in\mathcal{F}$ より $[l,r]$ は right-strong interval でない。

系 1.

$\sum_i \vert \mathrm{Select}(i) \vert \leq 2n$

証明.

$\mathrm{Select}(i) \setminus \{m_i\}$ たちはどの 2 つも共通要素を持たないことを示せば十分。任意に $i,j\in[1,n]\; (i\neq j)$ を固定する。

1. $j\lt i$ のとき
  
  任意に $r\in \mathrm{Select}(i) \setminus \{m_i\}$ を取る。
  $j \leq i - 1 \lt r \lt m _ {(i - 1) + 1}$ と補題 1 より $r\notin\mathrm{Select}(j)$。

2. $j \gt i$ のとき
  
  任意に $r\in \mathrm{Select}(i) \setminus \{m_i\}$ を取る。$r\in \mathrm{Select}(j) \setminus \{m_j\}$ と仮定する。$i\lt j \leq r \lt m_j$ かつ $[r,m_j]\in\mathcal{F}$ であるから、$[i,r]\in \mathrm{Select}(i)$ に矛盾。

アルゴリズム.

アイデア: $i$ を $n\to 1$ の順に走査し、$\mathrm{Select}(i)$ たちを変数 `Potential` を用いて計算する。`Potential` は $\{r \mid \exists l\leq i\leq r \;\text{s.t.}\;[l,r] \text{が right-strong interval}\}$ と等しくなるように上手く差分更新していく。

はじめ、`Potential` は空。