---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_segment_tree.hpp
    title: "\u533A\u9593\u548C\u53D6\u5F97\u304C\u53EF\u80FD\u306A\u8D64\u9ED2\u6728"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_tree_base.hpp
    title: Red Black Tree Base
  - icon: ':question:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc238/tasks/abc238_f
    links:
    - https://atcoder.jp/contests/abc238/tasks/abc238_f
  bundledCode: "#line 1 \"test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc238/tasks/abc238_f\"\n\n#include\
    \ <iostream>\n#line 1 \"library/datastructure/bbst/red_black_segment_tree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/red_black_tree_base.hpp\"\n\n\n\n\
    #include <cassert>\n#include <sstream>\n#include <string>\n#include <tuple>\n\
    #line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include <deque>\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename T, bool auto_extend = false>\n  \
    \  struct ObjectPool {\n        using value_type = T;\n        using value_pointer_type\
    \ = T*;\n\n        template <typename U>\n        using container_type = std::conditional_t<auto_extend,\
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
    \ namespace suisen\n\n\n#line 9 \"library/datastructure/bbst/red_black_tree_base.hpp\"\
    \n\nnamespace suisen::bbst::internal {\n    template <typename T, typename Derived>\n\
    \    struct RedBlackTreeNodeBase {\n        enum RedBlackTreeNodeColor { RED,\
    \ BLACK };\n\n        using base_type = void;\n        using size_type = int;\n\
    \n        using value_type = T;\n\n        using node_type = Derived;\n      \
    \  using tree_type = node_type*;\n\n        using color_type = RedBlackTreeNodeColor;\n\
    \n        RedBlackTreeNodeBase() = default;\n\n        static inline ObjectPool<node_type>\
    \ pool{};\n\n        static void init_pool(int siz) { pool = ObjectPool<node_type>(siz);\
    \ }\n        static int node_num() { return pool.size(); }\n\n        static tree_type\
    \ empty_tree() { return nullptr; }\n\n        static size_type size(tree_type\
    \ node) { return node ? node->_siz : 0; }\n        static bool empty(tree_type\
    \ node) { return not node; }\n\n        template <bool force_black_root = true>\n\
    \        static tree_type merge(tree_type l, tree_type r) {\n            if (not\
    \ l) return r;\n            if (not r) return l;\n\n            tree_type res\
    \ = nullptr;\n            if (size_type hl = height(l), hr = height(r); hl > hr)\
    \ {\n                l = node_type::push(l);\n                tree_type c = l->_ch[1]\
    \ = merge<false>(l->_ch[1], r);\n                if (l->_col == BLACK and c->_col\
    \ == RED and color(c->_ch[1]) == RED) {\n                    std::swap(l->_col,\
    \ c->_col);\n                    if (std::exchange(l->_ch[0]->_col, BLACK) ==\
    \ BLACK) return rotate(l, 1);\n                }\n                res = node_type::update(l);\n\
    \            } else if (hr > hl) {\n                r = node_type::push(r);\n\
    \                tree_type c = r->_ch[0] = merge<false>(l, r->_ch[0]);\n     \
    \           if (r->_col == BLACK and c->_col == RED and color(c->_ch[0]) == RED)\
    \ {\n                    std::swap(r->_col, c->_col);\n                    if\
    \ (std::exchange(r->_ch[1]->_col, BLACK) == BLACK) return rotate(r, 0);\n    \
    \            }\n                res = node_type::update(r);\n            } else\
    \ {\n                res = create_branch(l, r);\n            }\n            if\
    \ constexpr (force_black_root) res->_col = BLACK;\n            return res;\n \
    \       }\n\n        static std::pair<tree_type, tree_type> split(tree_type node,\
    \ size_type k) {\n            if (not node) return { nullptr, nullptr };\n   \
    \         node = node_type::push(node);\n            if (k == 0) return { nullptr,\
    \ node };\n            if (k == size(node)) return { node, nullptr };\n\n    \
    \        tree_type l = std::exchange(node->_ch[0], nullptr);\n            tree_type\
    \ r = std::exchange(node->_ch[1], nullptr);\n\n            free_node(node);\n\n\
    \            if (color(l) == RED) l->_col = BLACK;\n            if (color(r) ==\
    \ RED) r->_col = BLACK;\n\n            size_type szl = size(l);\n            tree_type\
    \ m;\n            if (k < szl) {\n                std::tie(l, m) = split(l, k);\n\
    \                return { l, merge(m, r) };\n            }\n            if (k\
    \ > szl) {\n                std::tie(m, r) = split(r, k - szl);\n            \
    \    return { merge(l, m), r };\n            }\n            return { l, r };\n\
    \        }\n\n        static std::tuple<tree_type, tree_type, tree_type> split_range(tree_type\
    \ node, size_type l, size_type r) {\n            auto [tlm, tr] = split(node,\
    \ r);\n            auto [tl, tm] = split(tlm, l);\n            return { tl, tm,\
    \ tr };\n        }\n\n        static tree_type insert(tree_type node, size_type\
    \ k, const value_type& val) {\n            auto [tl, tr] = split(node, k);\n \
    \           return merge(merge(tl, create_leaf(val)), tr);\n        }\n      \
    \  static tree_type push_front(tree_type node, const value_type &val) { return\
    \ insert(node, 0, val); }\n        static tree_type push_back(tree_type node,\
    \ const value_type &val) { return insert(node, size(node), val); }\n\n       \
    \ static std::pair<tree_type, value_type> erase(tree_type node, size_type k) {\n\
    \            auto [tl, tm, tr] = split_range(node, k, k + 1);\n            value_type\
    \ erased_value = tm->_val;\n            free_node(tm);\n            return { merge(tl,\
    \ tr) , erased_value };\n        }\n        static std::pair<tree_type, value_type>\
    \ pop_front(tree_type node) { return erase(node, 0); }\n        static std::pair<tree_type,\
    \ value_type> pop_back(tree_type node) { return erase(node, size(node) - 1); }\n\
    \n        template <typename U>\n        static tree_type build(const std::vector<U>&\
    \ a, int l, int r) {\n            if (r - l == 1) return create_leaf(a[l]);\n\
    \            int m = (l + r) >> 1;\n            return merge(build(a, l, m), build(a,\
    \ m, r));\n        }\n        template <typename U>\n        static tree_type\
    \ build(const std::vector<U>& a) {\n            return a.empty() ? empty_tree()\
    \ : build(a, 0, a.size());\n        }\n\n        template <typename OutputIterator>\n\
    \        static void dump(tree_type node, OutputIterator it) {\n            if\
    \ (empty(node)) return;\n            auto dfs = [&](auto dfs, tree_type cur) ->\
    \ void {\n                if (cur->is_leaf()) {\n                    *it++ = cur->_val;\n\
    \                    return;\n                }\n                dfs(dfs, cur->_ch[0]);\n\
    \                dfs(dfs, cur->_ch[1]);\n            };\n            dfs(dfs,\
    \ node);\n        }\n\n        // Don't use on persistent tree.\n        static\
    \ void free(tree_type node) {\n            auto dfs = [&](auto dfs, tree_type\
    \ cur) -> void {\n                if (not cur) return;\n                dfs(dfs,\
    \ cur->_ch[0]);\n                dfs(dfs, cur->_ch[1]);\n                free_node(cur);\n\
    \            };\n            dfs(dfs, node);\n        }\n\n        template <typename\
    \ ToStr>\n        static std::string to_string(tree_type node, ToStr f) {\n  \
    \          std::vector<value_type> dat;\n            node_type::dump(node, std::back_inserter(dat));\n\
    \            std::ostringstream res;\n            int siz = dat.size();\n    \
    \        res << '[';\n            for (int i = 0; i < siz; ++i) {\n          \
    \      res << f(dat[i]);\n                if (i != siz - 1) res << \", \";\n \
    \           }\n            res << ']';\n            return res.str();\n      \
    \  }\n        static std::string to_string(tree_type node) {\n            return\
    \ to_string(node, [](const auto &e) { return e; });\n        }\n\n        static\
    \ void check_rbtree_properties(tree_type node) {\n            assert(color(node)\
    \ == BLACK);\n            auto dfs = [&](auto dfs, tree_type cur) -> int {\n \
    \               if (not cur) return 0;\n                if (cur->_col == RED)\
    \ {\n                    assert(color(cur->_ch[0]) == BLACK);\n              \
    \      assert(color(cur->_ch[1]) == BLACK);\n                }\n             \
    \   int bl = dfs(dfs, cur->_ch[0]);\n                int br = dfs(dfs, cur->_ch[1]);\n\
    \                assert(bl == br);\n                return bl + (cur->_col ==\
    \ BLACK);\n            };\n            dfs(dfs, node);\n        }\n\n    protected:\n\
    \        color_type _col;\n        tree_type _ch[2]{ nullptr, nullptr };\n   \
    \     value_type _val;\n        size_type _siz, _lev;\n\n        RedBlackTreeNodeBase(const\
    \ value_type& val) : _col(BLACK), _val(val), _siz(1), _lev(0) {}\n        RedBlackTreeNodeBase(tree_type\
    \ l, tree_type r) : _col(RED), _ch{ l, r }, _siz(l->_siz + r->_siz), _lev(l->_lev\
    \ + (l->_col == BLACK)) {}\n\n        static void clear_pool() { pool.clear();\
    \ }\n        static int pool_capacity() { return pool.capacity(); }\n\n      \
    \  static color_type color(tree_type node) { return node ? node->_col : BLACK;\
    \ }\n        static size_type height(tree_type node) { return node ? node->_lev\
    \ : 0; }\n\n        bool is_leaf() const { return not (_ch[0] or _ch[1]); }\n\n\
    \        static tree_type clone(tree_type node) {\n            return node;\n\
    \        }\n        static tree_type update(tree_type node) {\n            node->_siz\
    \ = node->is_leaf() ? 1 : size(node->_ch[0]) + size(node->_ch[1]);\n         \
    \   node->_lev = node->_ch[0] ? height(node->_ch[0]) + (node->_ch[0]->_col ==\
    \ BLACK) : 0;\n            return node;\n        }\n        static tree_type push(tree_type\
    \ node) {\n            return node;\n        }\n\n        static tree_type rotate(tree_type\
    \ node, int index) {\n            node = node_type::push(node);\n            tree_type\
    \ ch_node = node_type::push(node->_ch[index]);\n            node->_ch[index] =\
    \ std::exchange(ch_node->_ch[index ^ 1], node);\n            return node_type::update(node),\
    \ node_type::update(ch_node);\n        }\n\n        static tree_type create_leaf(const\
    \ value_type& val = value_type{}) {\n            return &(*pool.alloc() = node_type(val));\n\
    \        }\n\n        static tree_type create_branch(tree_type l, tree_type r)\
    \ {\n            return node_type::update(&(*pool.alloc() = node_type(l, r)));\n\
    \        }\n\n        static void free_node(tree_type node) {\n            if\
    \ (node) pool.free(node);\n        }\n    };\n} // namespace suisen\n\n\n#line\
    \ 5 \"library/datastructure/bbst/red_black_segment_tree.hpp\"\n\nnamespace suisen::bbst::segtree\
    \ {\n    template <typename T, T(*op)(T, T), T(*e)(), template <typename, typename>\
    \ typename BaseNode = internal::RedBlackTreeNodeBase>\n    struct RedBlackTreeNode\
    \ : public BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>> {\n        using\
    \ base_type = BaseNode<T, RedBlackTreeNode<T, op, e, BaseNode>>;\n        using\
    \ node_type = typename base_type::node_type;\n        using tree_type = typename\
    \ base_type::tree_type;\n        using size_type = typename base_type::size_type;\n\
    \        using value_type = typename base_type::value_type;\n\n        friend\
    \ base_type;\n        friend typename base_type::base_type;\n\n        RedBlackTreeNode()\
    \ : base_type() {}\n\n        static std::pair<tree_type, value_type> prod(tree_type\
    \ node, size_type l, size_type r) {\n            auto [tl, tm, tr] = base_type::split_range(node,\
    \ l, r);\n            value_type res = value(tm);\n            return { base_type::merge(base_type::merge(tl,\
    \ tm), tr), res };\n        }\n        static value_type prod_all(tree_type node)\
    \ {\n            return value(node);\n        }\n\n    private:\n        RedBlackTreeNode(const\
    \ value_type& val) : base_type(val) {}\n        RedBlackTreeNode(tree_type l,\
    \ tree_type r) : base_type(l, r) {}\n\n        static value_type value(tree_type\
    \ node) { return node ? node->_val : e(); }\n\n        static tree_type update(tree_type\
    \ node) {\n            base_type::update(node);\n            node->_val = op(value(node->_ch[0]),\
    \ value(node->_ch[1]));\n            return node;\n        }\n    };\n}\n\n\n\
    #line 5 \"test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp\"\
    \n\n#include <atcoder/modint>\n \nusing mint = atcoder::modint998244353;\n \n\
    mint op(mint x, mint y) {\n    return x + y;\n}\nmint e() {\n    return 0;\n}\n\
    \ \nusing Node = suisen::bbst::segtree::RedBlackTreeNode<mint, op, e>;\nusing\
    \ Tree = Node::tree_type;\n \nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    Node::init_pool(200000);\n \n    int n, k;\n\
    \    std::cin >> n >> k;\n \n    std::vector<int> p(n), q(n);\n    for (auto&\
    \ e : p) std::cin >> e, --e;\n    for (auto& e : q) std::cin >> e, --e;\n \n \
    \   std::vector<int> v(n);\n    for (int i = 0; i < n; ++i) {\n        v[p[i]]\
    \ = q[i];\n    }\n \n    std::vector<Tree> dp(k + 1, Node::empty_tree());\n  \
    \  for (int c = 0; c <= k; ++c) {\n        dp[c] = Node::push_back(dp[c], c ==\
    \ 0);\n    }\n \n    std::vector<int> index(n, 0);\n \n    for (int i = 0; i <\
    \ n; ++i) {\n        for (int c = k; c >= 0; --c) {\n            Tree rseq;\n\
    \            std::tie(dp[c], rseq) = Node::split(dp[c], index[v[i]]);\n      \
    \      dp[c] = Node::push_back(dp[c], Node::prod_all(rseq));\n            if (c\
    \ < k) {\n                dp[c + 1] = Node::merge(dp[c + 1], rseq);\n        \
    \    } else {\n                Node::free(rseq);\n            }\n        }\n \
    \       dp[0] = Node::merge(dp[0], Node::build(std::vector<mint>(i + 1 - index[v[i]],\
    \ 0)));\n        for (int m = v[i] + 1; m < n; ++m) {\n            ++index[m];\n\
    \        }\n    }\n \n    std::cout << Node::prod_all(dp[k]).val() << std::endl;\n\
    \ \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc238/tasks/abc238_f\"\n\n\
    #include <iostream>\n#include \"library/datastructure/bbst/red_black_segment_tree.hpp\"\
    \n\n#include <atcoder/modint>\n \nusing mint = atcoder::modint998244353;\n \n\
    mint op(mint x, mint y) {\n    return x + y;\n}\nmint e() {\n    return 0;\n}\n\
    \ \nusing Node = suisen::bbst::segtree::RedBlackTreeNode<mint, op, e>;\nusing\
    \ Tree = Node::tree_type;\n \nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    Node::init_pool(200000);\n \n    int n, k;\n\
    \    std::cin >> n >> k;\n \n    std::vector<int> p(n), q(n);\n    for (auto&\
    \ e : p) std::cin >> e, --e;\n    for (auto& e : q) std::cin >> e, --e;\n \n \
    \   std::vector<int> v(n);\n    for (int i = 0; i < n; ++i) {\n        v[p[i]]\
    \ = q[i];\n    }\n \n    std::vector<Tree> dp(k + 1, Node::empty_tree());\n  \
    \  for (int c = 0; c <= k; ++c) {\n        dp[c] = Node::push_back(dp[c], c ==\
    \ 0);\n    }\n \n    std::vector<int> index(n, 0);\n \n    for (int i = 0; i <\
    \ n; ++i) {\n        for (int c = k; c >= 0; --c) {\n            Tree rseq;\n\
    \            std::tie(dp[c], rseq) = Node::split(dp[c], index[v[i]]);\n      \
    \      dp[c] = Node::push_back(dp[c], Node::prod_all(rseq));\n            if (c\
    \ < k) {\n                dp[c + 1] = Node::merge(dp[c + 1], rseq);\n        \
    \    } else {\n                Node::free(rseq);\n            }\n        }\n \
    \       dp[0] = Node::merge(dp[0], Node::build(std::vector<mint>(i + 1 - index[v[i]],\
    \ 0)));\n        for (int m = v[i] + 1; m < n; ++m) {\n            ++index[m];\n\
    \        }\n    }\n \n    std::cout << Node::prod_all(dp[k]).val() << std::endl;\n\
    \ \n    return 0;\n}"
  dependsOn:
  - library/datastructure/bbst/red_black_segment_tree.hpp
  - library/datastructure/bbst/red_black_tree_base.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
  requiredBy: []
  timestamp: '2022-03-03 17:52:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
- /verify/test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp.html
title: test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
---
