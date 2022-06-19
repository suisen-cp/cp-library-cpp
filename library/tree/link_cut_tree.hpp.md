---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree/dummy1.test.cpp
    title: test/src/tree/link_cut_tree/dummy1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree/dynamic_tree_vertex_add_path_sum.test.cpp
    title: test/src/tree/link_cut_tree/dynamic_tree_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/src/tree/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree/lca.test.cpp
    title: test/src/tree/link_cut_tree/lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/link_cut_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"library/util/object_pool.hpp\"\
    \n\n\n\n#include <deque>\n#line 6 \"library/util/object_pool.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, bool auto_extend = false>\n    struct ObjectPool\
    \ {\n        using value_type = T;\n        using value_pointer_type = T*;\n\n\
    \        template <typename U>\n        using container_type = std::conditional_t<auto_extend,\
    \ std::deque<U>, std::vector<U>>;\n\n        container_type<value_type> pool;\n\
    \        container_type<value_pointer_type> stock;\n        decltype(stock.begin())\
    \ it;\n\n        ObjectPool() : ObjectPool(0) {}\n        ObjectPool(int siz)\
    \ : pool(siz), stock(siz) {\n            clear();\n        }\n\n        int capacity()\
    \ const { return pool.size(); }\n        int size() const { return it - stock.begin();\
    \ }\n\n        value_pointer_type alloc() {\n            if constexpr (auto_extend)\
    \ ensure();\n            return *it++;\n        }\n\n        void free(value_pointer_type\
    \ t) {\n            *--it = t;\n        }\n\n        void clear() {\n        \
    \    int siz = pool.size();\n            it = stock.begin();\n            for\
    \ (int i = 0; i < siz; i++) stock[i] = &pool[i];\n        }\n\n        void ensure()\
    \ {\n            if (it != stock.end()) return;\n            int siz = stock.size();\n\
    \            for (int i = siz; i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 10 \"library/tree/link_cut_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n\
    \    struct LinkCutTree {\n        struct SplayTreeNode;\n\n        using node_type\
    \ = SplayTreeNode;\n        using node_pointer_type = node_type*;\n        using\
    \ value_type = T;\n\n        struct SplayTreeNode {\n            friend struct\
    \ LinkCutTree;\n\n            explicit SplayTreeNode(const value_type& val = e())\
    \ : _val(val), _sum(val) {}\n\n        private:\n            node_pointer_type\
    \ _p = nullptr;\n            node_pointer_type _ch[2]{ nullptr, nullptr };\n\n\
    \            int _siz = 1;\n            value_type _val, _sum;\n\n           \
    \ bool _rev = false;\n            \n            bool is_root() const {\n     \
    \           return not _p or (_p->_ch[0] != this and _p->_ch[1] != this);\n  \
    \          }\n\n            void update() {\n                _siz = 1, _sum =\
    \ _val;\n                if (_ch[0]) _siz += _ch[0]->_siz, _sum = op(_ch[0]->_sum,\
    \ _sum);\n                if (_ch[1]) _siz += _ch[1]->_siz, _sum = op(_sum, _ch[1]->_sum);\n\
    \            }\n\n            void reverse_all() {\n                _rev ^= true;\n\
    \                std::swap(_ch[0], _ch[1]);\n                _sum = toggle(_sum);\n\
    \            }\n\n            void push() {\n                if (std::exchange(_rev,\
    \ false)) {\n                    if (_ch[0]) _ch[0]->reverse_all();\n        \
    \            if (_ch[1]) _ch[1]->reverse_all();\n                }\n         \
    \   }\n\n            void rot(int ch_idx) {\n                assert(_ch[ch_idx]);\n\
    \n                node_pointer_type rt = _ch[ch_idx];\n                if (not\
    \ is_root()) _p->_ch[_p->_ch[1] == this] = rt;\n\n                if ((_ch[ch_idx]\
    \ = rt->_ch[ch_idx ^ 1])) {\n                    _ch[ch_idx]->_p = this;\n   \
    \             }\n                rt->_ch[ch_idx ^ 1] = this;\n               \
    \ rt->_p = std::exchange(_p, rt);\n\n                update(), rt->update();\n\
    \            }\n\n            void splay() {\n                push();\n      \
    \          while (not is_root()) {\n                    if (_p->is_root()) {\n\
    \                        _p->push(), push();\n                        _p->rot(_p->_ch[1]\
    \ == this);\n                    } else {\n                        node_pointer_type\
    \ pp = _p->_p;\n                        pp->push(), _p->push(), push();\n    \
    \                    const int idx_pp = pp->_ch[1] == _p, idx_p = _p->_ch[1] ==\
    \ this;\n                        if (idx_p == idx_pp) {\n                    \
    \        pp->rot(idx_pp), _p->rot(idx_p);\n                        } else {\n\
    \                            _p->rot(idx_p), pp->rot(idx_pp);\n              \
    \          }\n                    }\n                }\n            }\n      \
    \  };\n\n        LinkCutTree() = delete;\n\n        static void init_pool(int\
    \ capacity) {\n            _pool = ObjectPool<node_type>(capacity);\n        }\n\
    \n        static node_pointer_type make_node(const value_type& val = e()) {\n\
    \            return &(*_pool.alloc() = node_type(val));\n        }\n        static\
    \ std::vector<node_pointer_type> make_nodes(const std::vector<value_type>& vals)\
    \ {\n            std::vector<node_pointer_type> nodes;\n            nodes.reserve(vals.size());\n\
    \            for (const auto& val : vals) nodes.push_back(make_node(val));\n \
    \           return nodes;\n        }\n\n        static node_pointer_type expose(node_pointer_type\
    \ node) {\n            assert(node);\n            node_pointer_type rch = nullptr;\n\
    \            for (node_pointer_type cur = node; cur; cur = cur->_p) {\n      \
    \          cur->splay();\n                cur->_ch[1] = std::exchange(rch, cur);\n\
    \                cur->update();\n            }\n            node->splay();\n \
    \           return rch;\n        }\n\n        static void link(node_pointer_type\
    \ ch, node_pointer_type par) {\n            evert(ch), expose(par);\n        \
    \    assert(not (ch == par or ch->_p)); // check un-connectivity\n           \
    \ par->_ch[1] = ch;\n            ch->_p = par;\n            par->update();\n \
    \       }\n\n        static void cut(node_pointer_type ch) {\n            expose(ch);\n\
    \            node_pointer_type par = ch->_ch[0];\n            assert(par);\n \
    \           par->_p = ch->_ch[0] = nullptr;\n            ch->update();\n     \
    \   }\n        static void cut(node_pointer_type u, node_pointer_type v) {\n \
    \           evert(u);\n            expose(v);\n            assert(v->_ch[0] ==\
    \ u); // check connectivity\n            u->_p = v->_ch[0] = nullptr;\n      \
    \      v->update();\n        }\n\n        static void evert(node_pointer_type\
    \ u) {\n            expose(u);\n            u->reverse_all();\n            u->push();\n\
    \        }\n\n        static bool is_connected(node_pointer_type u, node_pointer_type\
    \ v) {\n            expose(u), expose(v);\n            return u == v or u->_p;\n\
    \        }\n\n        static node_pointer_type lca(node_pointer_type u, node_pointer_type\
    \ v) {\n            expose(u);\n            node_pointer_type a = expose(v);\n\
    \            return u == v or u->_p ? a : nullptr;\n        }\n\n        static\
    \ value_type prod_from_root(node_pointer_type u) {\n            expose(u);\n \
    \           return u->_sum;\n        }\n        static value_type prod(node_pointer_type\
    \ u, node_pointer_type v) {\n            evert(u);\n            expose(v);\n \
    \           assert(u == v or u->_p); // check connectivity\n            return\
    \ v->_sum;\n        }\n\n        static value_type get(node_pointer_type u) {\n\
    \            // expose(u);\n            return u->_val;\n        }\n        static\
    \ void set(node_pointer_type u, const value_type& val) {\n            apply(u,\
    \ [&val](const value_type&) { return val; });\n        }\n        template <typename\
    \ Fun>\n        static void apply(node_pointer_type u, Fun&& f) {\n          \
    \  expose(u);\n            u->_val = f(u->_val);\n            u->update();\n \
    \       }\n\n        static std::vector<node_pointer_type> path_from_root(node_pointer_type\
    \ u) {\n            std::vector<node_pointer_type> res;\n            expose(u);\n\
    \            auto dfs = [&](auto dfs, node_pointer_type cur) -> void {\n     \
    \           cur->push();\n                if (cur->_ch[0]) dfs(dfs, cur->_ch[0]);\n\
    \                res.push_back(cur);\n                if (cur->_ch[1]) dfs(dfs,\
    \ cur->_ch[1]);\n            };\n            dfs(dfs, u);\n            return\
    \ res;\n        }\n        static std::optional<std::vector<node_pointer_type>>\
    \ path(node_pointer_type u, node_pointer_type v) {\n            evert(u);\n  \
    \          expose(v);\n            if (u == v or u->_p) return path_from_root(v);\n\
    \            return std::nullopt;\n        }\n    \n    private:\n        static\
    \ inline ObjectPool<node_type> _pool{};\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_LINK_CUT_TREE\n#define SUISEN_LINK_CUT_TREE\n\n#include <cassert>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#include \"library/util/object_pool.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n\
    \    struct LinkCutTree {\n        struct SplayTreeNode;\n\n        using node_type\
    \ = SplayTreeNode;\n        using node_pointer_type = node_type*;\n        using\
    \ value_type = T;\n\n        struct SplayTreeNode {\n            friend struct\
    \ LinkCutTree;\n\n            explicit SplayTreeNode(const value_type& val = e())\
    \ : _val(val), _sum(val) {}\n\n        private:\n            node_pointer_type\
    \ _p = nullptr;\n            node_pointer_type _ch[2]{ nullptr, nullptr };\n\n\
    \            int _siz = 1;\n            value_type _val, _sum;\n\n           \
    \ bool _rev = false;\n            \n            bool is_root() const {\n     \
    \           return not _p or (_p->_ch[0] != this and _p->_ch[1] != this);\n  \
    \          }\n\n            void update() {\n                _siz = 1, _sum =\
    \ _val;\n                if (_ch[0]) _siz += _ch[0]->_siz, _sum = op(_ch[0]->_sum,\
    \ _sum);\n                if (_ch[1]) _siz += _ch[1]->_siz, _sum = op(_sum, _ch[1]->_sum);\n\
    \            }\n\n            void reverse_all() {\n                _rev ^= true;\n\
    \                std::swap(_ch[0], _ch[1]);\n                _sum = toggle(_sum);\n\
    \            }\n\n            void push() {\n                if (std::exchange(_rev,\
    \ false)) {\n                    if (_ch[0]) _ch[0]->reverse_all();\n        \
    \            if (_ch[1]) _ch[1]->reverse_all();\n                }\n         \
    \   }\n\n            void rot(int ch_idx) {\n                assert(_ch[ch_idx]);\n\
    \n                node_pointer_type rt = _ch[ch_idx];\n                if (not\
    \ is_root()) _p->_ch[_p->_ch[1] == this] = rt;\n\n                if ((_ch[ch_idx]\
    \ = rt->_ch[ch_idx ^ 1])) {\n                    _ch[ch_idx]->_p = this;\n   \
    \             }\n                rt->_ch[ch_idx ^ 1] = this;\n               \
    \ rt->_p = std::exchange(_p, rt);\n\n                update(), rt->update();\n\
    \            }\n\n            void splay() {\n                push();\n      \
    \          while (not is_root()) {\n                    if (_p->is_root()) {\n\
    \                        _p->push(), push();\n                        _p->rot(_p->_ch[1]\
    \ == this);\n                    } else {\n                        node_pointer_type\
    \ pp = _p->_p;\n                        pp->push(), _p->push(), push();\n    \
    \                    const int idx_pp = pp->_ch[1] == _p, idx_p = _p->_ch[1] ==\
    \ this;\n                        if (idx_p == idx_pp) {\n                    \
    \        pp->rot(idx_pp), _p->rot(idx_p);\n                        } else {\n\
    \                            _p->rot(idx_p), pp->rot(idx_pp);\n              \
    \          }\n                    }\n                }\n            }\n      \
    \  };\n\n        LinkCutTree() = delete;\n\n        static void init_pool(int\
    \ capacity) {\n            _pool = ObjectPool<node_type>(capacity);\n        }\n\
    \n        static node_pointer_type make_node(const value_type& val = e()) {\n\
    \            return &(*_pool.alloc() = node_type(val));\n        }\n        static\
    \ std::vector<node_pointer_type> make_nodes(const std::vector<value_type>& vals)\
    \ {\n            std::vector<node_pointer_type> nodes;\n            nodes.reserve(vals.size());\n\
    \            for (const auto& val : vals) nodes.push_back(make_node(val));\n \
    \           return nodes;\n        }\n\n        static node_pointer_type expose(node_pointer_type\
    \ node) {\n            assert(node);\n            node_pointer_type rch = nullptr;\n\
    \            for (node_pointer_type cur = node; cur; cur = cur->_p) {\n      \
    \          cur->splay();\n                cur->_ch[1] = std::exchange(rch, cur);\n\
    \                cur->update();\n            }\n            node->splay();\n \
    \           return rch;\n        }\n\n        static void link(node_pointer_type\
    \ ch, node_pointer_type par) {\n            evert(ch), expose(par);\n        \
    \    assert(not (ch == par or ch->_p)); // check un-connectivity\n           \
    \ par->_ch[1] = ch;\n            ch->_p = par;\n            par->update();\n \
    \       }\n\n        static void cut(node_pointer_type ch) {\n            expose(ch);\n\
    \            node_pointer_type par = ch->_ch[0];\n            assert(par);\n \
    \           par->_p = ch->_ch[0] = nullptr;\n            ch->update();\n     \
    \   }\n        static void cut(node_pointer_type u, node_pointer_type v) {\n \
    \           evert(u);\n            expose(v);\n            assert(v->_ch[0] ==\
    \ u); // check connectivity\n            u->_p = v->_ch[0] = nullptr;\n      \
    \      v->update();\n        }\n\n        static void evert(node_pointer_type\
    \ u) {\n            expose(u);\n            u->reverse_all();\n            u->push();\n\
    \        }\n\n        static bool is_connected(node_pointer_type u, node_pointer_type\
    \ v) {\n            expose(u), expose(v);\n            return u == v or u->_p;\n\
    \        }\n\n        static node_pointer_type lca(node_pointer_type u, node_pointer_type\
    \ v) {\n            expose(u);\n            node_pointer_type a = expose(v);\n\
    \            return u == v or u->_p ? a : nullptr;\n        }\n\n        static\
    \ value_type prod_from_root(node_pointer_type u) {\n            expose(u);\n \
    \           return u->_sum;\n        }\n        static value_type prod(node_pointer_type\
    \ u, node_pointer_type v) {\n            evert(u);\n            expose(v);\n \
    \           assert(u == v or u->_p); // check connectivity\n            return\
    \ v->_sum;\n        }\n\n        static value_type get(node_pointer_type u) {\n\
    \            // expose(u);\n            return u->_val;\n        }\n        static\
    \ void set(node_pointer_type u, const value_type& val) {\n            apply(u,\
    \ [&val](const value_type&) { return val; });\n        }\n        template <typename\
    \ Fun>\n        static void apply(node_pointer_type u, Fun&& f) {\n          \
    \  expose(u);\n            u->_val = f(u->_val);\n            u->update();\n \
    \       }\n\n        static std::vector<node_pointer_type> path_from_root(node_pointer_type\
    \ u) {\n            std::vector<node_pointer_type> res;\n            expose(u);\n\
    \            auto dfs = [&](auto dfs, node_pointer_type cur) -> void {\n     \
    \           cur->push();\n                if (cur->_ch[0]) dfs(dfs, cur->_ch[0]);\n\
    \                res.push_back(cur);\n                if (cur->_ch[1]) dfs(dfs,\
    \ cur->_ch[1]);\n            };\n            dfs(dfs, u);\n            return\
    \ res;\n        }\n        static std::optional<std::vector<node_pointer_type>>\
    \ path(node_pointer_type u, node_pointer_type v) {\n            evert(u);\n  \
    \          expose(v);\n            if (u == v or u->_p) return path_from_root(v);\n\
    \            return std::nullopt;\n        }\n    \n    private:\n        static\
    \ inline ObjectPool<node_type> _pool{};\n    };\n} // namespace suisen\n\n#endif\
    \ // SUISEN_LINK_CUT_TREE\n"
  dependsOn:
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/tree/link_cut_tree.hpp
  requiredBy: []
  timestamp: '2022-06-19 16:27:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  - test/src/tree/link_cut_tree/dynamic_tree_vertex_add_path_sum.test.cpp
  - test/src/tree/link_cut_tree/lca.test.cpp
  - test/src/tree/link_cut_tree/dummy1.test.cpp
documentation_of: library/tree/link_cut_tree.hpp
layout: document
title: Link Cut Tree
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
