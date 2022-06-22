---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/link_cut_tree_base.hpp
    title: library/tree/link_cut_tree_base.hpp
  - icon: ':heavy_check_mark:'
    path: library/tree/link_cut_tree_path_foldable.hpp
    title: library/tree/link_cut_tree_path_foldable.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
  bundledCode: "#line 1 \"test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/tree/link_cut_tree_path_foldable.hpp\"\
    \n\n\n\n#line 1 \"library/tree/link_cut_tree_base.hpp\"\n\n\n\n#include <cassert>\n\
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
    } // namespace suisen\n\n\n#line 19 \"test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n\nstruct S {\n    mint a, b;\n    mint ra, rb;\n\n    S() = default;\n    S(mint\
    \ a, mint b) : a(a), b(b), ra(a), rb(b) {}\n    S(mint a, mint b, mint ra, mint\
    \ rb) : a(a), b(b), ra(ra), rb(rb) {}\n\n    S compose(const S &g) const {\n \
    \       return S { a * g.a, a * g.b + b, g.ra * ra, g.ra * rb + g.rb };\n    }\n\
    \    S toggle() const {\n        return S { ra, rb, a, b };\n    }\n    mint eval(mint\
    \ x) const {\n        return a * x + b;\n    }\n};\n\nS op(S x, S y) {\n    return\
    \ y.compose(x);\n}\nS e() {\n    return S{ 1, 0 };\n}\nS toggle(S x) {\n    return\
    \ x.toggle();\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S> a(n);\n    for\
    \ (int i = 0; i < n; ++i) {\n        mint c, d;\n        std::cin >> c >> d;\n\
    \        a[i] = S { c, d };\n    }\n\n    using DynamicTree = suisen::LinkCutTreePathFoldable<S,\
    \ op, e, toggle>;\n\n    DynamicTree::init_pool(n);\n\n    auto nodes = DynamicTree::make_nodes(a);\n\
    \n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >>\
    \ u >> v;\n        DynamicTree::link(nodes[u], nodes[v]);\n    }\n\n    while\
    \ (q-- > 0) {\n        int query_type;\n        std::cin >> query_type;\n    \
    \    if (query_type == 0) {\n            int u, v, w, x;\n            std::cin\
    \ >> u >> v >> w >> x;\n            DynamicTree::cut(nodes[u], nodes[v]);\n  \
    \          DynamicTree::link(nodes[w], nodes[x]);\n        } else if (query_type\
    \ == 1) {\n            int p;\n            mint c, d;\n            std::cin >>\
    \ p >> c >> d;\n            DynamicTree::set(nodes[p], S { c, d });\n        }\
    \ else {\n            int u, v;\n            mint x;\n            std::cin >>\
    \ u >> v >> x;\n            std::cout << DynamicTree::prod(nodes[u], nodes[v]).eval(x)\
    \ << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/tree/link_cut_tree_path_foldable.hpp\"\
    \n\nstruct S {\n    mint a, b;\n    mint ra, rb;\n\n    S() = default;\n    S(mint\
    \ a, mint b) : a(a), b(b), ra(a), rb(b) {}\n    S(mint a, mint b, mint ra, mint\
    \ rb) : a(a), b(b), ra(ra), rb(rb) {}\n\n    S compose(const S &g) const {\n \
    \       return S { a * g.a, a * g.b + b, g.ra * ra, g.ra * rb + g.rb };\n    }\n\
    \    S toggle() const {\n        return S { ra, rb, a, b };\n    }\n    mint eval(mint\
    \ x) const {\n        return a * x + b;\n    }\n};\n\nS op(S x, S y) {\n    return\
    \ y.compose(x);\n}\nS e() {\n    return S{ 1, 0 };\n}\nS toggle(S x) {\n    return\
    \ x.toggle();\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S> a(n);\n    for\
    \ (int i = 0; i < n; ++i) {\n        mint c, d;\n        std::cin >> c >> d;\n\
    \        a[i] = S { c, d };\n    }\n\n    using DynamicTree = suisen::LinkCutTreePathFoldable<S,\
    \ op, e, toggle>;\n\n    DynamicTree::init_pool(n);\n\n    auto nodes = DynamicTree::make_nodes(a);\n\
    \n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >>\
    \ u >> v;\n        DynamicTree::link(nodes[u], nodes[v]);\n    }\n\n    while\
    \ (q-- > 0) {\n        int query_type;\n        std::cin >> query_type;\n    \
    \    if (query_type == 0) {\n            int u, v, w, x;\n            std::cin\
    \ >> u >> v >> w >> x;\n            DynamicTree::cut(nodes[u], nodes[v]);\n  \
    \          DynamicTree::link(nodes[w], nodes[x]);\n        } else if (query_type\
    \ == 1) {\n            int p;\n            mint c, d;\n            std::cin >>\
    \ p >> c >> d;\n            DynamicTree::set(nodes[p], S { c, d });\n        }\
    \ else {\n            int u, v;\n            mint x;\n            std::cin >>\
    \ u >> v >> x;\n            std::cout << DynamicTree::prod(nodes[u], nodes[v]).eval(x)\
    \ << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - library/tree/link_cut_tree_path_foldable.hpp
  - library/tree/link_cut_tree_base.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2022-06-23 03:06:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
- /verify/test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp.html
title: test/src/tree/link_cut_tree_path_foldable/dynamic_tree_vertex_set_path_composite.test.cpp
---
