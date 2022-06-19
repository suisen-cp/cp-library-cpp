---
title: Link Cut Tree
documentation_of: //library/tree/link_cut_tree.hpp
---
## Link Cut Tree

### サポートする関数

全て`static` 関数として各種操作をサポートされる．

- `static void init_pool(int capacity)`
  
  __使用前に必ず呼ぶこと．__ `capacity` には使用するノード数を与える．
- `static node_pointer_type make_node(const value_type &val)`
  
  値 `val` を持つノードを作成して返す．
- `static std::vector<node_pointer_type> make_node(const std::vector<value_type> &vals)`
  
  `vals` の各要素 `val` に対して `make_node(val)` を呼び，その結果を `std::vector<node_pointer_type>` に元の順番通りに格納して返す．
- `static node_pointer_type expose(node_pointer_type node)`
  
  `node` から根までを heavy path で結ぶ．`node` の子への link は全て light edge となり，heavy path を管理する splay 木において `node` は根となる．返り値は通常の用途において使用しない (と思う)．`expose` 自体を外から使うこと自体が少なそう．
- `static void link(node_pointer_type ch, node_pointer_type par`
  
  `ch` が属する木で `ch` を根にした (`evert`) 後，`par` の子に `ch` を追加する．__操作前に `ch` と `par` が連結であってはならない．__
- `static void cut(node_pointer_type ch)`
  
  `ch` と `ch` の親の間の辺を削除する．__操作前に `ch` が根であってはならない．__
- `static void cut(node_pointer_type u, node_pointer_type v)`
  
  `u` と `v` の間の辺を削除する．__操作前に `u` と `v` を直接結ぶ辺が存在しなければならない．__
- `static void evert(node_pointer_type u)`
  
  `u` が属する木の根を `u` に変更する．

- `static bool is_connected(node_pointer_type u, node_pointer_type v)`

  `u` と `v` が連結なら `true`，そうでなければ `false` を返す．
- `static node_pointer_type lca(node_pointer_type u, node_pointer_type v)`

  `u` と `v` の Lowest Common Ancestor を返す．`u` と `v` が異なる木に属する場合は，`nullptr` を返す．`u` および `v` が属している木の根 `r` を指定するためには先に `evert(r)` を呼ぶこと (詳しくは lca のテストファイルを参照)．
- `static value_type prod_from_root(node_pointer_type u)`
  
  `u` が属する木の根から `u` までのパス上の頂点を順番に `op` で畳込んだ結果を返す．
- `static value_type prod(node_pointer_type u, node_pointer_type v)`
  
  `u` から `v` へのパス上の頂点を順番に `op` で畳込んだ結果を返す．__操作前の時点で `u` と `v` は連結でなければならない．__
- `static value_type get(node_pointer_type u)`
  
  `u` に書かれた値を返す．
- `static void set(node_pointer_type u, const value_type &val)`
  
  `u` に書かれた値を `val` に更新する
- `template <typename Fun> static void apply(node_pointer_type u, Fun&& f)`
  
  `u` に書かれた値 `val` を `f(val)` に更新する．即ち，`Fun` は `value_type -> value_type` の関数型を想定している．
- `static std::vector<node_pointer_type> path_from_root(node_pointer_type u)`
  
  `u` が属する木の根から `u` までのパスを返す．
- `static std::optional<std::vector<node_pointer_type>> path(node_pointer_type u, node_pointer_type v)`
  
  `u` から `v` までのパスを返す．__操作前に `u` と `v` が連結である必要がある．__

### 注意点

`evert` を呼び出した後でも，その他の関数によって根が再び別の頂点に変更される可能性がある．具体的には，以下の関数では根の変更が暗黙的に行われる．

- `link`
  
  この操作では2つの連結成分が merge されるので，根は `par` 側の根に統一される．
- `cut(node_pointer_type ch)`

  操作後の `ch` 側の木の根は `ch` である．親側の根は変化しない．
- `cut(node_pointer_type u, node_pointer_type v)`
  
  操作後の `u` 側の木の根は `u` に，`v` 側の木の根は `v` となる．
- `evert(node_pointer_type u)`
  
  操作後に `u` が根となる．
- `prod(node_pointer_type u, node_pointer_type v)`
  
  操作後に `u` が根となる．
- `path(node_pointer_type u, node_pointer_type v)`

  操作後に `u` が根となる．

### 使い方

```cpp

#include "library/tree/link_cut_tree.hpp"

int op(int x, int y) { return x + y; } // モノイドの二項演算
int e() { return 0; }                  // モノイドの単位元
int toggle(int x) { return x; }        // モノイドが非可換な場合は，逆順で和を取ったものを同時に計算してここで swap する

using DynamicTree = suisen::LinkCutTree<int, op, e, toggle>;

int main() {
    const int n = 5;
    
    DynamicTree::init_pool(n); // 使用するノードの個数を予め確保

    std::vector<int> init_values { 1, 2, 3, 4, 5 };

    std::vector<DynamicTree::node_pointer_type> nodes = DynamicTree::make_nodes(init_values);

    /**
     * ノードを [添字(値)] と表記
     * 
     * [0(1)]   [1(2)]   [2(3)]   [3(4)]   [4(5)]
     */
    
    // nodes[0] と nodes[1] の間に辺を張る (操作前に非連結である必要がある)
    DynamicTree::link(nodes[0], nodes[1]);
    /**
     * [0(1)]---[1(2)]   [2(3)]   [3(4)]   [4(5)]
     */
    DynamicTree::link(nodes[1], nodes[4]);
    /**
     * [0(1)]---[1(2)]---[4(5)]   [2(3)]   [3(4)]
     */
    DynamicTree::link(nodes[1], nodes[3]);
    /**
     * [0(1)]---[1(2)]---[4(5)]   [2(3)]
     *            |
     *          [3(4)]
     */

    // nodes[3] から nodes[4] までのパス上の値を二項演算 op で畳込む
    int sum = DynamicTree::prod(nodes[3], nodes[4]); // 4 + 2 + 5

    // nodes[3] と nodes[4] の間の辺を切る (操作前に直接結ぶ辺が存在する必要がある)
    DynamicTree::cut(nodes[1], nodes[4]);
    /**
     * [0(1)]---[1(2)]   [4(5)]   [2(3)]
     *            |
     *          [3(4)]
     */
    DynamicTree::link(nodes[0], nodes[4]);
    /**
     * [4(5)]---[0(1)]---[1(2)]     [2(3)]
     *                     |
     *                   [3(4)]
     */
    DynamicTree::link(nodes[0], nodes[2]);
    /**
     * [4(5)]---[0(1)]---[1(2)]
     *            |        |
     *          [2(3)]   [3(4)]
     */
    
    // nodes[1] を，nodes[1] が属する木の根にする (以降の操作で根は勝手に変更される可能性があるので，毎回evertを呼ぶ)
    DynamicTree::evert(nodes[1]);
    /**
     * [1(2)]
     *  |  |
     *  |  +------+
     *  |         |
     * [0(1)]  [3(4)]
     *  |  |
     *  |  +------+
     *  |         |
     * [4(5)]  [2(3)]
     */

    // nodes[2] と nodes[4] の lca を返す．今は nodes[1] が根なので，lca は nodes[0];
    DynamicTree::node_pointer_type a = DynamicTree::lca(nodes[0], nodes[3]);
    return 0;
}
```
