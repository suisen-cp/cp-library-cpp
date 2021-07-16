# algorithm

## sliding_window_minimum

スライド最小値．Queue に詰めた要素の最小値を取得する．なお，ここでは予め全ての要素を与えておくような実装になっている．

```cpp
template <typename T, typename Comparator = prioritizing_mode::left_most_min<T>>
class sliding_window_minimum
```

1. `typename T`: 要素の型
2. `typename Comparator`: 比較器の型．比較モードによって動作を変更できる．
   - `suisen::prioritizing_mode::left_most_min<T>`: 最小値 (タイブレークは添字の小さい方を優先) を取得する
   - `suisen::prioritizing_mode::right_most_min<T>`: 最小値 (タイブレークは添字の大きい方を優先) を取得する
   - `suisen::prioritizing_mode::left_most_max<T>`: 最大値 (タイブレークは添字の小さい方を優先) を取得する
   - `suisen::prioritizing_mode::right_most_max<T>`: 最大値 (タイブレークは添字の大きい方を優先) を取得する

### コンストラクタ

```cpp
template <typename Gen>
sliding_window_minimum(int n, Gen gen)
```

- `int n`: 要素の数
- `Gen gen` : `int -> T` の関数．配列の要素を生成する関数．

### メソッド

#### __追加__

```cpp
void proc_right()
void proc_right(int to_index)
```

1 要素の追加につき amortized $O(1)$．

#### __削除__

```cpp
void proc_left()
void proc_left(int to_index)
```

1 要素の削除につき amortized $O(1)$．

#### __追加 + 削除__

```cpp
void proc(int new_l, int new_r)
```

1 要素の追加・削除につき amortized $O(1)$．

#### __最小値取得クエリ__

```cpp
int arg_query() const
```

最小値を達成する添え字を取得．$O(1)$．

```cpp
T query() const
```

最小値を取得．$O(1)$．

#### __Queue の状態を取得__

```cpp
int get_left() const
int get_right() const
int get_window_size() const
```

Queue に入っている連続部分列が区間 `[l,r)` であるとして，順に

1. `l` の取得
2. `r` の取得
3. `r-l` の取得

を行う．$O(1)$．
