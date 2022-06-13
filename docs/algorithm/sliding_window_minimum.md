---
title: Sliding Window Minimum
documentation_of: //library/algorithm/sliding_window_minimum.hpp
---
## Sliding Window Minimum

長さ $N$ の列 $A=(A_0,\ldots, A_{N-1})$ と $0$ で初期化された整数 $l,r$ に対して、次の操作を行う。

- $\mathrm{proc\\_right}$ : $r\leftarrow r + 1$ とする。操作前の時点で $r=N$ の場合、この操作はできない。
- $\mathrm{proc\\_left}$ : $l\leftarrow l + 1$ とする。操作前の時点で $l=r$ の場合、この操作はできない。
- $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
- $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。

$\mathrm{proc\\_right}$ は償却 $\Theta(1)$ 時間、その他は最悪 $\Theta(1)$ 時間である。

テンプレート引数の第二引数によって、$\min$ と $\max$ のどちらを計算するか、また $\mathrm{arg\\_query}$ において等しい値が複数ある場合により小さい添字を優先するか、より大きい添字を優先するかの挙動を選択することが出来る。

`suisen::prioritizing_mode` 名前空間にテンプレート引数の第二引数に与えるための比較器の型エイリアスが定義されている。意味は次の通り。

- `suisen::prioritizing_mode::left_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最小__ のものを返す。
- `suisen::prioritizing_mode::right_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最大__ のものを返す。
- `suisen::prioritizing_mode::left_most_max<T>`
  - $\mathrm{query}$ : $\displaystyle \max _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\max}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最小__ のものを返す。
- `suisen::prioritizing_mode::left_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \max _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\max}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最大__ のものを返す。
