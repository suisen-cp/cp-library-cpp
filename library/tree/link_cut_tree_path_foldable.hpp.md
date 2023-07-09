---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/link_cut_tree_base.hpp
    title: Link Cut Tree Base
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree_path_foldable/dummy1.test.cpp
    title: test/src/tree/link_cut_tree_path_foldable/dummy1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_add_path_sum.test.cpp
    title: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/link_cut_tree_path_foldable/lca.test.cpp
    title: test/src/tree/link_cut_tree_path_foldable/lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/link_cut_tree_path_foldable.hpp\"\n\n\n\n#line\
    \ 1 \"library/tree/link_cut_tree_base.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"library/util/object_pool.hpp\"\
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
    \ namespace suisen\n\n\n#line 10 \"library/tree/link_cut_tree_base.hpp\"\n\nnamespace\
    \ suisen::internal::link_cut_tree {\n    template <typename T, typename Derived>\n\
    \    struct SplayTreeNodeBase {\n        friend Derived;\n        template <typename,\
    \ typename>\n        friend struct LinkCutTreeBase;\n\n        using value_type\
    \ = T;\n        using node_type = Derived;\n        using node_pointer_type =\
    \ node_type*;\n\n        explicit SplayTreeNodeBase(const value_type& val = value_type{})\
    \ : _val(val) {}\n\n    protected:\n        node_pointer_type _p = nullptr;\n\
    \        node_pointer_type _ch[2]{ nullptr, nullptr };\n\n        int _siz = 1;\n\
    \        value_type _val;\n\n        bool _rev = false;\n        \n        static\
    \ bool is_root(node_pointer_type node) {\n            return not node->_p or (node->_p->_ch[0]\
    \ != node and node->_p->_ch[1] != node);\n        }\n        static node_pointer_type&\
    \ parent(node_pointer_type node) {\n            return node->_p;\n        }\n\
    \        static node_pointer_type& child(node_pointer_type node, int ch_idx) {\n\
    \            return node->_ch[ch_idx];\n        }\n        static int size(node_pointer_type\
    \ node) {\n            return node ? node->_siz : 0;\n        }\n        static\
    \ const value_type& value(node_pointer_type node) {\n            return node->_val;\n\
    \        }\n        static void set_value(node_pointer_type node, const value_type\
    \ &new_val) {\n            node->_val = new_val;\n        }\n        static void\
    \ update(node_pointer_type node) {\n            node->_siz = 1 + node_type::size(node->_ch[0])\
    \ + node_type::size(node->_ch[1]);\n        }\n\n        static void reverse_all(node_pointer_type\
    \ node) {\n            if (not node) return;\n            node->_rev ^= true;\n\
    \            std::swap(node->_ch[0], node->_ch[1]);\n        }\n\n        static\
    \ void push(node_pointer_type node) {\n            if (std::exchange(node->_rev,\
    \ false)) {\n                node_type::reverse_all(node->_ch[0]);\n         \
    \       node_type::reverse_all(node->_ch[1]);\n            }\n        }\n\n  \
    \      static void rot(node_pointer_type node, int ch_idx) {\n            assert(node->_ch[ch_idx]);\n\
    \n            node_pointer_type rt = node->_ch[ch_idx];\n            if (not node_type::is_root(node))\
    \ node->_p->_ch[node->_p->_ch[1] == node] = rt;\n\n            if ((node->_ch[ch_idx]\
    \ = rt->_ch[ch_idx ^ 1])) node->_ch[ch_idx]->_p = node;\n\n            rt->_ch[ch_idx\
    \ ^ 1] = node;\n            rt->_p = std::exchange(node->_p, rt);\n\n        \
    \    node_type::update(node), node_type::update(rt);\n        }\n\n        static\
    \ void splay(node_pointer_type node) {\n            node_type::push(node);\n \
    \           while (not node_type::is_root(node)) {\n                node_pointer_type\
    \ p = node->_p;\n                if (node_type::is_root(p)) {\n              \
    \      node_type::push(p), node_type::push(node);\n                    node_type::rot(p,\
    \ p->_ch[1] == node);\n                } else {\n                    node_pointer_type\
    \ pp = p->_p;\n                    node_type::push(pp), node_type::push(p), node_type::push(node);\n\
    \                    const int idx_pp = pp->_ch[1] == p, idx_p = p->_ch[1] ==\
    \ node;\n                    if (idx_p == idx_pp) {\n                        node_type::rot(pp,\
    \ idx_pp), node_type::rot(p, idx_p);\n                    } else {\n         \
    \               node_type::rot(p, idx_p), node_type::rot(pp, idx_pp);\n      \
    \              }\n                }\n            }\n        }\n    };\n\n    template\
    \ <typename NodeType, typename Derived>\n    struct LinkCutTreeBase {\n      \
    \  using derived_tree_type = Derived;\n\n        using node_type = typename NodeType::node_type;\n\
    \        using node_pointer_type = typename NodeType::node_pointer_type;\n   \
    \     using value_type = typename NodeType::value_type;\n\n        LinkCutTreeBase()\
    \ = delete;\n\n        static void init_pool(int capacity) {\n            _pool\
    \ = ObjectPool<node_type>(capacity);\n        }\n\n        template <typename\
    \ ...Args>\n        static node_pointer_type make_node(Args&&...args) {\n    \
    \        return &(*_pool.alloc() = node_type(std::forward<Args>(args)...));\n\
    \        }\n        static std::vector<node_pointer_type> make_nodes(const std::vector<value_type>&\
    \ vals) {\n            std::vector<node_pointer_type> nodes;\n            nodes.reserve(vals.size());\n\
    \            for (const auto& val : vals) nodes.push_back(make_node(val));\n \
    \           return nodes;\n        }\n\n        static node_pointer_type expose(node_pointer_type\
    \ node) {\n            assert(node);\n            node_pointer_type rch = nullptr;\n\
    \            for (node_pointer_type cur = node; cur; cur = node_type::parent(cur))\
    \ {\n                node_type::splay(cur);\n                node_type::child(cur,\
    \ 1) = std::exchange(rch, cur);\n                node_type::update(cur);\n   \
    \         }\n            node_type::splay(node);\n            return rch;\n  \
    \      }\n\n        static void link(node_pointer_type ch, node_pointer_type par)\
    \ {\n            derived_tree_type::evert(ch), derived_tree_type::expose(par);\n\
    \            // check un-connectivity\n            if (ch == par or node_type::parent(ch))\
    \ assert(false);\n            node_type::child(par, 1) = ch;\n            node_type::parent(ch)\
    \ = par;\n            node_type::update(par);\n        }\n\n        static void\
    \ cut(node_pointer_type ch) {\n            derived_tree_type::expose(ch);\n  \
    \          node_pointer_type par = node_type::child(ch, 0);\n            assert(par);\n\
    \            node_type::parent(par) = node_type::child(ch, 0) = nullptr;\n   \
    \         node_type::update(ch);\n        }\n        static void cut(node_pointer_type\
    \ u, node_pointer_type v) {\n            derived_tree_type::evert(u);\n      \
    \      derived_tree_type::expose(v);\n            // check connectivity\n    \
    \        if (node_type::child(v, 0) != u) assert(false);\n            node_type::parent(u)\
    \ = node_type::child(v, 0) = nullptr;\n            node_type::update(v);\n   \
    \     }\n\n        static void evert(node_pointer_type u) {\n            derived_tree_type::expose(u);\n\
    \            node_type::reverse_all(u);\n            node_type::push(u);\n   \
    \     }\n\n        static bool is_connected(node_pointer_type u, node_pointer_type\
    \ v) {\n            derived_tree_type::expose(u), derived_tree_type::expose(v);\n\
    \            return u == v or node_type::parent(u);\n        }\n\n        static\
    \ node_pointer_type lca(node_pointer_type u, node_pointer_type v) {\n        \
    \    derived_tree_type::expose(u);\n            node_pointer_type a = derived_tree_type::expose(v);\n\
    \            return u == v or node_type::parent(u) ? a : nullptr;\n        }\n\
    \n        static value_type get(node_pointer_type u) {\n            // expose(u);\n\
    \            return node_type::value(u);\n        }\n        static void set(node_pointer_type\
    \ u, const value_type& val) {\n            derived_tree_type::update_value(u,\
    \ [&val](const value_type&) { return val; });\n        }\n        template <typename\
    \ Fun>\n        static void update_value(node_pointer_type u, Fun&& f) {\n   \
    \         derived_tree_type::expose(u);\n            node_type::set_value(u, f(node_type::value(u)));\n\
    \            node_type::update(u);\n        }\n\n        static std::vector<node_pointer_type>\
    \ path_from_root(node_pointer_type u) {\n            std::vector<node_pointer_type>\
    \ res;\n            derived_tree_type::expose(u);\n            auto dfs = [&](auto\
    \ dfs, node_pointer_type cur) -> void {\n                node_type::push(cur);\n\
    \                if (node_type::child(cur, 0)) dfs(dfs, node_type::child(cur,\
    \ 0));\n                res.push_back(cur);\n                if (node_type::child(cur,\
    \ 1)) dfs(dfs, node_type::child(cur, 1));\n            };\n            dfs(dfs,\
    \ u);\n            return res;\n        }\n        static std::optional<std::vector<node_pointer_type>>\
    \ path(node_pointer_type u, node_pointer_type v) {\n            derived_tree_type::evert(u);\n\
    \            derived_tree_type::expose(v);\n            if (u == v or node_type::parent(u))\
    \ return derived_tree_type::path_from_root(v);\n            return std::nullopt;\n\
    \        }\n    \n    private:\n        static inline ObjectPool<node_type> _pool{};\n\
    \    };\n} // namespace suisen\n\n\n#line 5 \"library/tree/link_cut_tree_path_foldable.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::link_cut_tree {\n        template\
    \ <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n        struct PathFoldableSplayTreeNode\
    \ : public SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T, op, e, toggle>> {\n\
    \            using base_node_type = SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>>;\n            \n            template <typename, typename>\n\
    \            friend struct SplayTreeNodeBase;\n            template <typename,\
    \ typename>\n            friend struct LinkCutTreeBase;\n            template\
    \ <typename T2, T2(*)(T2, T2), T2(*)(), T2(*)(T2)>\n            friend struct\
    \ LinkCutTreePathFoldable;\n\n            using value_type = typename base_node_type::value_type;\n\
    \            using node_type = typename base_node_type::node_type;\n         \
    \   using node_pointer_type = typename base_node_type::node_pointer_type;\n\n\
    \            explicit PathFoldableSplayTreeNode(const value_type& val = e()) :\
    \ base_node_type(val), _sum(val) {}\n\n        protected:\n            value_type\
    \ _sum;\n\n            static value_type sum(node_pointer_type node) {\n     \
    \           return node ? node->_sum : e();\n            }\n            static\
    \ void update(node_pointer_type node) {\n                base_node_type::update(node);\n\
    \                node->_sum = op(op(node_type::sum(node_type::child(node, 0)),\
    \ node_type::value(node)), node_type::sum(node_type::child(node, 1)));\n     \
    \       }\n\n            static void reverse_all(node_pointer_type node) {\n \
    \               if (not node) return;\n                base_node_type::reverse_all(node);\n\
    \                node->_sum = toggle(node->_sum);\n            }\n        };\n\
    \n        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n      \
    \  struct LinkCutTreePathFoldable : public LinkCutTreeBase<PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>, LinkCutTreePathFoldable<T, op, e, toggle>> {\n            using\
    \ base_type = LinkCutTreeBase<PathFoldableSplayTreeNode<T, op, e, toggle>, LinkCutTreePathFoldable<T,\
    \ op, e, toggle>>;\n            using node_type = PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>;\n            using node_pointer_type = typename node_type::node_pointer_type;\n\
    \            using value_type = typename node_type::value_type;\n\n          \
    \  static value_type prod_from_root(node_pointer_type u) {\n                base_type::expose(u);\n\
    \                return node_type::sum(u);\n            }\n            static\
    \ value_type prod(node_pointer_type u, node_pointer_type v) {\n              \
    \  base_type::evert(u);\n                base_type::expose(v);\n             \
    \   // check connectivity\n                if (not (u == v or node_type::parent(u)))\
    \ assert(false);\n                return node_type::sum(v);\n            }\n \
    \       };\n    } // namespace internal::link_cut_tree\n    \n    using internal::link_cut_tree::LinkCutTreePathFoldable;\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_LINK_CUT_TREE\n#define SUISEN_LINK_CUT_TREE\n\n#include \"\
    library/tree/link_cut_tree_base.hpp\"\n\nnamespace suisen {\n    namespace internal::link_cut_tree\
    \ {\n        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n   \
    \     struct PathFoldableSplayTreeNode : public SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>> {\n            using base_node_type = SplayTreeNodeBase<T, PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>>;\n            \n            template <typename, typename>\n\
    \            friend struct SplayTreeNodeBase;\n            template <typename,\
    \ typename>\n            friend struct LinkCutTreeBase;\n            template\
    \ <typename T2, T2(*)(T2, T2), T2(*)(), T2(*)(T2)>\n            friend struct\
    \ LinkCutTreePathFoldable;\n\n            using value_type = typename base_node_type::value_type;\n\
    \            using node_type = typename base_node_type::node_type;\n         \
    \   using node_pointer_type = typename base_node_type::node_pointer_type;\n\n\
    \            explicit PathFoldableSplayTreeNode(const value_type& val = e()) :\
    \ base_node_type(val), _sum(val) {}\n\n        protected:\n            value_type\
    \ _sum;\n\n            static value_type sum(node_pointer_type node) {\n     \
    \           return node ? node->_sum : e();\n            }\n            static\
    \ void update(node_pointer_type node) {\n                base_node_type::update(node);\n\
    \                node->_sum = op(op(node_type::sum(node_type::child(node, 0)),\
    \ node_type::value(node)), node_type::sum(node_type::child(node, 1)));\n     \
    \       }\n\n            static void reverse_all(node_pointer_type node) {\n \
    \               if (not node) return;\n                base_node_type::reverse_all(node);\n\
    \                node->_sum = toggle(node->_sum);\n            }\n        };\n\
    \n        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n      \
    \  struct LinkCutTreePathFoldable : public LinkCutTreeBase<PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>, LinkCutTreePathFoldable<T, op, e, toggle>> {\n            using\
    \ base_type = LinkCutTreeBase<PathFoldableSplayTreeNode<T, op, e, toggle>, LinkCutTreePathFoldable<T,\
    \ op, e, toggle>>;\n            using node_type = PathFoldableSplayTreeNode<T,\
    \ op, e, toggle>;\n            using node_pointer_type = typename node_type::node_pointer_type;\n\
    \            using value_type = typename node_type::value_type;\n\n          \
    \  static value_type prod_from_root(node_pointer_type u) {\n                base_type::expose(u);\n\
    \                return node_type::sum(u);\n            }\n            static\
    \ value_type prod(node_pointer_type u, node_pointer_type v) {\n              \
    \  base_type::evert(u);\n                base_type::expose(v);\n             \
    \   // check connectivity\n                if (not (u == v or node_type::parent(u)))\
    \ assert(false);\n                return node_type::sum(v);\n            }\n \
    \       };\n    } // namespace internal::link_cut_tree\n    \n    using internal::link_cut_tree::LinkCutTreePathFoldable;\n\
    } // namespace suisen\n\n#endif // SUISEN_LINK_CUT_TREE\n"
  dependsOn:
  - library/tree/link_cut_tree_base.hpp
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/tree/link_cut_tree_path_foldable.hpp
  requiredBy: []
  timestamp: '2022-06-23 03:06:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/link_cut_tree_path_foldable/dummy1.test.cpp
  - test/src/tree/link_cut_tree_path_foldable/lca.test.cpp
  - test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
  - test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_add_path_sum.test.cpp
documentation_of: library/tree/link_cut_tree_path_foldable.hpp
layout: document
title: "\u30D1\u30B9\u548C\u53D6\u5F97\u304C\u3067\u304D\u308B Link Cut Tree"
---
## パス和取得ができる Link Cut Tree

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

#include "library/tree/link_cut_tree_path_foldable.hpp"

int op(int x, int y) { return x + y; } // モノイドの二項演算
int e() { return 0; }                  // モノイドの単位元
int toggle(int x) { return x; }        // モノイドが非可換な場合は，逆順で和を取ったものを同時に計算してここで swap する

using DynamicTree = suisen::LinkCutTreePathFoldable<int, op, e, toggle>;

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
