---
title: Hessenberg Reduction
documentation_of: //library/linear_algebra/hessenberg_reduction.hpp
---
## Hessenberg Reduction

$N \times N$ 行列 $A$ と相似な上 Hessenberg 行列 $H$ を $\Theta(N ^ 3)$ 時間で計算します．

### 概要

Reference : http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf

__方針__

行列 $A$ に対して行基本変形を $k$ 回行った結果得られる行列 $B$ は基本変形を表す行列 $P _ 1, P_ 2, \ldots, P _ k$ により $B = P _ k P _ {k - 1} \cdots P _ 1 A$ と表される．

基本変形を表す行列は正則であるから，$(P _ k P _ {k - 1} \cdots P _ 1) A (P _ k P _ {k - 1} \cdots P _ 1) ^ {-1} = P _ k (P _ {k - 1} (\cdots (P _ 1 A P _ 1 ^ {-1}) \cdots) P _ {k - 1} ^ {-1}) P _ k ^ {-1}$ は相似変換である．

即ち，行基本変形とその逆行列による列基本変形をセットにして行列 $A$ を掃き出すことで上 Hessenberg 行列 $H$ を得ることが出来れば，$A$ と $H$ は相似である．

__アルゴリズム__

次のような，掃き出し法により上三角行列を得るアルゴリズムとよく似た手続きにより上 Hessenberg 行列へと相似変換することができる．

1. $i = 0, \ldots, N - 3$ の順に以下を行う．
   1. $i + 1\leq j \lt N$ かつ $A _ {j, i} \neq 0$ を満たす $j$ を任意に $1$ つ選ぶ．ただし，そのような $j$ が存在しない場合は，次の $i$ に進む．
   2. $A$ の $i + 1$ 行目と $j$ 行目を swap する．
   3. 相似変換であることを保つため，$A$ の $i + 1$ 列目と $j$ 列目を swap する．
   4. 各 $k = i + 2, \ldots, N - 1$ に対して以下を行う．
      1. $c := \dfrac{A _ {k, i}}{A _ {i + 1, i}}$ とする．
      2. $A$ の $k$ 行目から $i + 1$ 行目の $c$ 倍を差し引く．
      3. 相似変換であることを保つため，$A$ の $i + 1$ 列目に $k$ 列目の $c$ 倍を足し込む．

列基本変形により以前 $0$ にした部分が再び非零になったり，あるいは $A _ {i + 1, i} = 0$ となってしまったりすると上 Hessenberg 行列への変換は失敗するが，列基本変形は $i + 1$ 列目から $N - 1$ 列目までにしか変更を加えないため，そのようなことは起こり得ない．

従って，上記の手続きにより $A$ は上 Hessenberg 行列へと相似変換される．時間計算量は $\Theta(N ^ 3)$ である．