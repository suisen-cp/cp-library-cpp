---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/link_cut_tree_lazy.hpp\"\n\n\n\n#include <cassert>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace suisen\
    \ {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T, int), F(*composition)(F, F), F(*id)(), T(*toggle)(T)>\n    struct LinkCutTreeLazy\
    \ {\n        struct SplayTreeNode;\n\n        using node_type = SplayTreeNode;\n\
    \        using node_pointer_type = node_type*;\n        using value_type = T;\n\
    \        using operator_type = F;\n\n        struct SplayTreeNode {\n        \
    \    friend struct LinkCutTreeLazy;\n\n            explicit SplayTreeNode(const\
    \ value_type& val = e()) : _val(val), _sum(val) {}\n        private:\n       \
    \     node_pointer_type _p = nullptr;\n            node_pointer_type _ch[2]{ nullptr,\
    \ nullptr };\n\n            int _siz = 1;\n            value_type _val, _sum;\n\
    \n            operator_type _laz = id();\n            bool _rev = false;\n\n \
    \           bool is_root() const {\n                return not _p or (_p->_ch[0]\
    \ != this and _p->_ch[1] != this);\n            }\n\n            void update()\
    \ {\n                _siz = 1, _sum = _val;\n                if (_ch[0]) _siz\
    \ += _ch[0]->_siz, _sum = op(_ch[0]->_sum, _sum);\n                if (_ch[1])\
    \ _siz += _ch[1]->_siz, _sum = op(_sum, _ch[1]->_sum);\n            }\n\n    \
    \        void apply_all(const operator_type& f) {\n                _laz = composition(f,\
    \ _laz);\n                _val = mapping(f, _val, 1);\n                _sum =\
    \ mapping(f, _sum, _siz);\n            }\n            void reverse_all() {\n \
    \               _rev ^= true;\n                std::swap(_ch[0], _ch[1]);\n  \
    \              _sum = toggle(_sum);\n            }\n\n            void push()\
    \ {\n                if (_ch[0]) _ch[0]->apply_all(_laz);\n                if\
    \ (_ch[1]) _ch[1]->apply_all(_laz);\n                _laz = id();\n          \
    \      if (std::exchange(_rev, false)) {\n                    if (_ch[0]) _ch[0]->reverse_all();\n\
    \                    if (_ch[1]) _ch[1]->reverse_all();\n                }\n \
    \           }\n\n            void rot(int ch_idx) {\n                assert(_ch[ch_idx]);\n\
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
    \  };\n\n        LinkCutTreeLazy() = delete;\n\n        static node_pointer_type\
    \ make_node(const value_type& val = e()) {\n            return new node_type(val);\n\
    \        }\n        static std::vector<node_pointer_type> make_nodes(const std::vector<value_type>&\
    \ vals) {\n            std::vector<node_pointer_type> nodes;\n            nodes.reserve(vals.size());\n\
    \            for (const auto& val : vals) nodes.push_back(make_node(val));\n \
    \           return nodes;\n        }\n        static void delete_nodes(const std::vector<node_pointer_type>\
    \ &nodes) {\n            for (node_pointer_type node : nodes) {\n            \
    \    delete node;\n            }\n        }\n\n        static node_pointer_type\
    \ expose(node_pointer_type node) {\n            assert(node);\n            node_pointer_type\
    \ rch = nullptr;\n            for (node_pointer_type cur = node; cur; cur = cur->_p)\
    \ {\n                cur->splay();\n                cur->_ch[1] = std::exchange(rch,\
    \ cur);\n                cur->update();\n            }\n            node->splay();\n\
    \            return rch;\n        }\n\n        static void link(node_pointer_type\
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
    \            expose(u);\n            return u->_val;\n        }\n        static\
    \ void set(node_pointer_type u, const value_type& val) {\n            apply(u,\
    \ [&val](const value_type&) { return val; });\n        }\n        template <typename\
    \ Fun>\n        static void apply(node_pointer_type u, Fun&& f) {\n          \
    \  expose(u);\n            u->_val = f(u->_val);\n            u->update();\n \
    \       }\n\n        static void apply_from_root(node_pointer_type u, const operator_type&\
    \ f) {\n            expose(u);\n            u->apply_all(f);\n            u->push();\n\
    \        }\n        static void apply(node_pointer_type u, node_pointer_type v,\
    \ const operator_type& f) {\n            evert(u);\n            expose(v);\n \
    \           assert(u == v or u->_p); // check connectivity\n            v->apply_all(f);\n\
    \            v->push();\n        }\n\n        static std::vector<node_pointer_type>\
    \ path_from_root(node_pointer_type u) {\n            std::vector<node_pointer_type>\
    \ res;\n            expose(u);\n            auto dfs = [&](auto dfs, node_pointer_type\
    \ cur) -> void {\n                cur->push();\n                if (cur->_ch[0])\
    \ dfs(dfs, cur->_ch[0]);\n                res.push_back(cur);\n              \
    \  if (cur->_ch[1]) dfs(dfs, cur->_ch[1]);\n            };\n            dfs(dfs,\
    \ u);\n            return res;\n        }\n        static std::optional<std::vector<node_pointer_type>>\
    \ path(node_pointer_type u, node_pointer_type v) {\n            evert(u);\n  \
    \          expose(v);\n            if (u == v or u->_p) return path_from_root(v);\n\
    \            return std::nullopt;\n        }\n    };\n} // namespace suisen\n\n\
    \n\n"
  code: "#ifndef SUISEN_LINK_CUT_TREE_LAZY\n#define SUISEN_LINK_CUT_TREE_LAZY\n\n\
    #include <cassert>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename\
    \ F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)(), T(*toggle)(T)>\n\
    \    struct LinkCutTreeLazy {\n        struct SplayTreeNode;\n\n        using\
    \ node_type = SplayTreeNode;\n        using node_pointer_type = node_type*;\n\
    \        using value_type = T;\n        using operator_type = F;\n\n        struct\
    \ SplayTreeNode {\n            friend struct LinkCutTreeLazy;\n\n            explicit\
    \ SplayTreeNode(const value_type& val = e()) : _val(val), _sum(val) {}\n     \
    \   private:\n            node_pointer_type _p = nullptr;\n            node_pointer_type\
    \ _ch[2]{ nullptr, nullptr };\n\n            int _siz = 1;\n            value_type\
    \ _val, _sum;\n\n            operator_type _laz = id();\n            bool _rev\
    \ = false;\n\n            bool is_root() const {\n                return not _p\
    \ or (_p->_ch[0] != this and _p->_ch[1] != this);\n            }\n\n         \
    \   void update() {\n                _siz = 1, _sum = _val;\n                if\
    \ (_ch[0]) _siz += _ch[0]->_siz, _sum = op(_ch[0]->_sum, _sum);\n            \
    \    if (_ch[1]) _siz += _ch[1]->_siz, _sum = op(_sum, _ch[1]->_sum);\n      \
    \      }\n\n            void apply_all(const operator_type& f) {\n           \
    \     _laz = composition(f, _laz);\n                _val = mapping(f, _val, 1);\n\
    \                _sum = mapping(f, _sum, _siz);\n            }\n            void\
    \ reverse_all() {\n                _rev ^= true;\n                std::swap(_ch[0],\
    \ _ch[1]);\n                _sum = toggle(_sum);\n            }\n\n          \
    \  void push() {\n                if (_ch[0]) _ch[0]->apply_all(_laz);\n     \
    \           if (_ch[1]) _ch[1]->apply_all(_laz);\n                _laz = id();\n\
    \                if (std::exchange(_rev, false)) {\n                    if (_ch[0])\
    \ _ch[0]->reverse_all();\n                    if (_ch[1]) _ch[1]->reverse_all();\n\
    \                }\n            }\n\n            void rot(int ch_idx) {\n    \
    \            assert(_ch[ch_idx]);\n\n                node_pointer_type rt = _ch[ch_idx];\n\
    \                if (not is_root()) _p->_ch[_p->_ch[1] == this] = rt;\n\n    \
    \            if ((_ch[ch_idx] = rt->_ch[ch_idx ^ 1])) {\n                    _ch[ch_idx]->_p\
    \ = this;\n                }\n                rt->_ch[ch_idx ^ 1] = this;\n  \
    \              rt->_p = std::exchange(_p, rt);\n\n                update(), rt->update();\n\
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
    \  };\n\n        LinkCutTreeLazy() = delete;\n\n        static node_pointer_type\
    \ make_node(const value_type& val = e()) {\n            return new node_type(val);\n\
    \        }\n        static std::vector<node_pointer_type> make_nodes(const std::vector<value_type>&\
    \ vals) {\n            std::vector<node_pointer_type> nodes;\n            nodes.reserve(vals.size());\n\
    \            for (const auto& val : vals) nodes.push_back(make_node(val));\n \
    \           return nodes;\n        }\n        static void delete_nodes(const std::vector<node_pointer_type>\
    \ &nodes) {\n            for (node_pointer_type node : nodes) {\n            \
    \    delete node;\n            }\n        }\n\n        static node_pointer_type\
    \ expose(node_pointer_type node) {\n            assert(node);\n            node_pointer_type\
    \ rch = nullptr;\n            for (node_pointer_type cur = node; cur; cur = cur->_p)\
    \ {\n                cur->splay();\n                cur->_ch[1] = std::exchange(rch,\
    \ cur);\n                cur->update();\n            }\n            node->splay();\n\
    \            return rch;\n        }\n\n        static void link(node_pointer_type\
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
    \            expose(u);\n            return u->_val;\n        }\n        static\
    \ void set(node_pointer_type u, const value_type& val) {\n            apply(u,\
    \ [&val](const value_type&) { return val; });\n        }\n        template <typename\
    \ Fun>\n        static void apply(node_pointer_type u, Fun&& f) {\n          \
    \  expose(u);\n            u->_val = f(u->_val);\n            u->update();\n \
    \       }\n\n        static void apply_from_root(node_pointer_type u, const operator_type&\
    \ f) {\n            expose(u);\n            u->apply_all(f);\n            u->push();\n\
    \        }\n        static void apply(node_pointer_type u, node_pointer_type v,\
    \ const operator_type& f) {\n            evert(u);\n            expose(v);\n \
    \           assert(u == v or u->_p); // check connectivity\n            v->apply_all(f);\n\
    \            v->push();\n        }\n\n        static std::vector<node_pointer_type>\
    \ path_from_root(node_pointer_type u) {\n            std::vector<node_pointer_type>\
    \ res;\n            expose(u);\n            auto dfs = [&](auto dfs, node_pointer_type\
    \ cur) -> void {\n                cur->push();\n                if (cur->_ch[0])\
    \ dfs(dfs, cur->_ch[0]);\n                res.push_back(cur);\n              \
    \  if (cur->_ch[1]) dfs(dfs, cur->_ch[1]);\n            };\n            dfs(dfs,\
    \ u);\n            return res;\n        }\n        static std::optional<std::vector<node_pointer_type>>\
    \ path(node_pointer_type u, node_pointer_type v) {\n            evert(u);\n  \
    \          expose(v);\n            if (u == v or u->_p) return path_from_root(v);\n\
    \            return std::nullopt;\n        }\n    };\n} // namespace suisen\n\n\
    \n#endif // SUISEN_LINK_CUT_TREE_LAZY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/link_cut_tree_lazy.hpp
  requiredBy: []
  timestamp: '2022-06-19 16:27:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/link_cut_tree_lazy.hpp
layout: document
title: Link Cut Tree Lazy
---
## Link Cut Tree Lazy