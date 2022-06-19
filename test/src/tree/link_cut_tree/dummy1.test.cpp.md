---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/link_cut_tree.hpp
    title: Link Cut Tree
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/tree/link_cut_tree/dummy1.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/tree/link_cut_tree.hpp\"\n\n\n\n#include <cassert>\n\
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
    \ inline ObjectPool<node_type> _pool{};\n    };\n} // namespace suisen\n\n\n#line\
    \ 6 \"test/src/tree/link_cut_tree/dummy1.test.cpp\"\n\nint op(int x, int y) {\
    \ return x + y; }\nint e() { return 0; }\nint toggle(int x) { return x; }\n\n\
    using DynamicTree = suisen::LinkCutTree<int, op, e, toggle>;\n\nvoid test() {\n\
    \    const int n = 5;\n\n    DynamicTree::init_pool(n);\n\n    std::vector<int>\
    \ init_values { 1, 2, 3, 4, 5 };\n\n    std::vector<DynamicTree::node_pointer_type>\
    \ nodes = DynamicTree::make_nodes(init_values);\n\n    /**\n     * [0(1)]   [1(2)]\
    \   [2(3)]   [3(4)]   [4(5)]\n     */\n\n    DynamicTree::link(nodes[0], nodes[1]);\n\
    \n    /**\n     * [0(1)]---[1(2)]   [2(3)]   [3(4)]   [4(5)]\n     */\n\n    int\
    \ sum_0 = DynamicTree::prod(nodes[0], nodes[1]);\n    assert(sum_0 == 1 + 2);\n\
    \n\n    DynamicTree::link(nodes[1], nodes[4]);\n\n    /**\n     * [0(1)]---[1(2)]---[4(5)]\
    \   [2(3)]   [3(4)]\n     */\n\n    int sum_1 = DynamicTree::prod(nodes[0], nodes[4]);\n\
    \    assert(sum_1 == 1 + 2 + 5);\n\n    DynamicTree::link(nodes[1], nodes[3]);\n\
    \n    /**\n     * [0(1)]---[1(2)]---[4(5)]   [2(3)]\n     *            |\n   \
    \  *          [3(4)]\n     */\n\n    auto path_0 = DynamicTree::path(nodes[3],\
    \ nodes[4]);\n    assert(*path_0 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[3], nodes[1], nodes[4] }));\n\n    auto path_1 = DynamicTree::path(nodes[3],\
    \ nodes[3]);\n    assert(*path_1 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[3] }));\n\n    auto path_2 = DynamicTree::path(nodes[0], nodes[2]);\n\
    \    assert(path_2 == std::nullopt);\n\n    int sum_2 = DynamicTree::prod(nodes[3],\
    \ nodes[4]);\n    assert(sum_2 == 4 + 2 + 5);\n\n    DynamicTree::link(nodes[3],\
    \ nodes[2]);\n\n    /**\n     * [0(1)]---[1(2)]---[4(5)]\n     *            |\n\
    \     *          [3(4)]---[2(3)]\n     */\n\n    int sum_3 = DynamicTree::prod(nodes[1],\
    \ nodes[2]);\n    assert(sum_3 == 2 + 4 + 3);\n\n    DynamicTree::set(nodes[1],\
    \ 7);\n\n    /**\n     * [0(1)]---[1(7)]---[4(5)]\n     *            |\n     *\
    \          [3(4)]---[2(3)]\n     */\n\n    int sum_4 = DynamicTree::prod(nodes[0],\
    \ nodes[4]);\n    assert(sum_4 == 1 + 7 + 5);\n\n    auto path_3 = DynamicTree::path(nodes[0],\
    \ nodes[3]);\n    assert(*path_3 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[0], nodes[1], nodes[3] }));\n\n    DynamicTree::cut(nodes[1], nodes[3]);\n\
    \n    /**\n     * [0(1)]---[1(7)]---[4(5)]\n     * \n     *          [3(4)]---[2(3)]\n\
    \     */\n\n    auto path_4 = DynamicTree::path(nodes[1], nodes[3]);\n    assert(path_4\
    \ == std::nullopt);\n\n    DynamicTree::set(nodes[4], 9);\n\n    /**\n     * [0(1)]---[1(7)]---[4(9)]\n\
    \     * \n     *          [3(4)]---[2(3)]\n     */\n\n    int sum_5 = DynamicTree::prod(nodes[0],\
    \ nodes[4]);\n    assert(sum_5 == 1 + 7 + 9);\n\n    DynamicTree::link(nodes[0],\
    \ nodes[2]);\n\n    /**\n     * [0(1)]---[1(7)]---[4(9)]\n     *   |\n     * [2(3)]---[3(4)]\n\
    \     */\n\n    int sum_6 = DynamicTree::prod(nodes[1], nodes[3]);\n    assert(sum_6\
    \ == 7 + 1 + 3 + 4);\n\n    DynamicTree::cut(nodes[1], nodes[0]);\n\n    /**\n\
    \     * [0(1)]   [1(7)]---[4(9)]\n     *   |\n     * [2(3)]---[3(4)]\n     */\n\
    \n    auto path_5 = DynamicTree::path(nodes[0], nodes[4]);\n    assert(path_5\
    \ == std::nullopt);\n\n    DynamicTree::link(nodes[2], nodes[4]);\n\n    /**\n\
    \     * [0(1)]\n     *   |\n     * [2(3)]---[3(4)]\n     *   |\n     * [4(9)]\n\
    \     *   |\n     * [1(7)]\n     */\n\n    int sum_7 = DynamicTree::prod(nodes[3],\
    \ nodes[4]);\n    assert(sum_7 == 4 + 3 + 9);\n\n    auto path_6 = DynamicTree::path(nodes[0],\
    \ nodes[1]);\n    assert(*path_6 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[0], nodes[2], nodes[4], nodes[1] }));\n\n    auto path_7 = DynamicTree::path(nodes[4],\
    \ nodes[3]);\n    assert(*path_7 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[4], nodes[2], nodes[3] }));\n}\n\nint main() {\n    test();\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n\n#include \"library/tree/link_cut_tree.hpp\"\n\nint\
    \ op(int x, int y) { return x + y; }\nint e() { return 0; }\nint toggle(int x)\
    \ { return x; }\n\nusing DynamicTree = suisen::LinkCutTree<int, op, e, toggle>;\n\
    \nvoid test() {\n    const int n = 5;\n\n    DynamicTree::init_pool(n);\n\n  \
    \  std::vector<int> init_values { 1, 2, 3, 4, 5 };\n\n    std::vector<DynamicTree::node_pointer_type>\
    \ nodes = DynamicTree::make_nodes(init_values);\n\n    /**\n     * [0(1)]   [1(2)]\
    \   [2(3)]   [3(4)]   [4(5)]\n     */\n\n    DynamicTree::link(nodes[0], nodes[1]);\n\
    \n    /**\n     * [0(1)]---[1(2)]   [2(3)]   [3(4)]   [4(5)]\n     */\n\n    int\
    \ sum_0 = DynamicTree::prod(nodes[0], nodes[1]);\n    assert(sum_0 == 1 + 2);\n\
    \n\n    DynamicTree::link(nodes[1], nodes[4]);\n\n    /**\n     * [0(1)]---[1(2)]---[4(5)]\
    \   [2(3)]   [3(4)]\n     */\n\n    int sum_1 = DynamicTree::prod(nodes[0], nodes[4]);\n\
    \    assert(sum_1 == 1 + 2 + 5);\n\n    DynamicTree::link(nodes[1], nodes[3]);\n\
    \n    /**\n     * [0(1)]---[1(2)]---[4(5)]   [2(3)]\n     *            |\n   \
    \  *          [3(4)]\n     */\n\n    auto path_0 = DynamicTree::path(nodes[3],\
    \ nodes[4]);\n    assert(*path_0 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[3], nodes[1], nodes[4] }));\n\n    auto path_1 = DynamicTree::path(nodes[3],\
    \ nodes[3]);\n    assert(*path_1 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[3] }));\n\n    auto path_2 = DynamicTree::path(nodes[0], nodes[2]);\n\
    \    assert(path_2 == std::nullopt);\n\n    int sum_2 = DynamicTree::prod(nodes[3],\
    \ nodes[4]);\n    assert(sum_2 == 4 + 2 + 5);\n\n    DynamicTree::link(nodes[3],\
    \ nodes[2]);\n\n    /**\n     * [0(1)]---[1(2)]---[4(5)]\n     *            |\n\
    \     *          [3(4)]---[2(3)]\n     */\n\n    int sum_3 = DynamicTree::prod(nodes[1],\
    \ nodes[2]);\n    assert(sum_3 == 2 + 4 + 3);\n\n    DynamicTree::set(nodes[1],\
    \ 7);\n\n    /**\n     * [0(1)]---[1(7)]---[4(5)]\n     *            |\n     *\
    \          [3(4)]---[2(3)]\n     */\n\n    int sum_4 = DynamicTree::prod(nodes[0],\
    \ nodes[4]);\n    assert(sum_4 == 1 + 7 + 5);\n\n    auto path_3 = DynamicTree::path(nodes[0],\
    \ nodes[3]);\n    assert(*path_3 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[0], nodes[1], nodes[3] }));\n\n    DynamicTree::cut(nodes[1], nodes[3]);\n\
    \n    /**\n     * [0(1)]---[1(7)]---[4(5)]\n     * \n     *          [3(4)]---[2(3)]\n\
    \     */\n\n    auto path_4 = DynamicTree::path(nodes[1], nodes[3]);\n    assert(path_4\
    \ == std::nullopt);\n\n    DynamicTree::set(nodes[4], 9);\n\n    /**\n     * [0(1)]---[1(7)]---[4(9)]\n\
    \     * \n     *          [3(4)]---[2(3)]\n     */\n\n    int sum_5 = DynamicTree::prod(nodes[0],\
    \ nodes[4]);\n    assert(sum_5 == 1 + 7 + 9);\n\n    DynamicTree::link(nodes[0],\
    \ nodes[2]);\n\n    /**\n     * [0(1)]---[1(7)]---[4(9)]\n     *   |\n     * [2(3)]---[3(4)]\n\
    \     */\n\n    int sum_6 = DynamicTree::prod(nodes[1], nodes[3]);\n    assert(sum_6\
    \ == 7 + 1 + 3 + 4);\n\n    DynamicTree::cut(nodes[1], nodes[0]);\n\n    /**\n\
    \     * [0(1)]   [1(7)]---[4(9)]\n     *   |\n     * [2(3)]---[3(4)]\n     */\n\
    \n    auto path_5 = DynamicTree::path(nodes[0], nodes[4]);\n    assert(path_5\
    \ == std::nullopt);\n\n    DynamicTree::link(nodes[2], nodes[4]);\n\n    /**\n\
    \     * [0(1)]\n     *   |\n     * [2(3)]---[3(4)]\n     *   |\n     * [4(9)]\n\
    \     *   |\n     * [1(7)]\n     */\n\n    int sum_7 = DynamicTree::prod(nodes[3],\
    \ nodes[4]);\n    assert(sum_7 == 4 + 3 + 9);\n\n    auto path_6 = DynamicTree::path(nodes[0],\
    \ nodes[1]);\n    assert(*path_6 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[0], nodes[2], nodes[4], nodes[1] }));\n\n    auto path_7 = DynamicTree::path(nodes[4],\
    \ nodes[3]);\n    assert(*path_7 == (std::vector<DynamicTree::node_pointer_type>{\
    \ nodes[4], nodes[2], nodes[3] }));\n}\n\nint main() {\n    test();\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/tree/link_cut_tree.hpp
  - library/util/object_pool.hpp
  isVerificationFile: true
  path: test/src/tree/link_cut_tree/dummy1.test.cpp
  requiredBy: []
  timestamp: '2022-06-19 16:27:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/link_cut_tree/dummy1.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/link_cut_tree/dummy1.test.cpp
- /verify/test/src/tree/link_cut_tree/dummy1.test.cpp.html
title: test/src/tree/link_cut_tree/dummy1.test.cpp
---