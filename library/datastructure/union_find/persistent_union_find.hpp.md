---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/persistent_array.hpp
    title: library/datastructure/persistent_array.hpp
  - icon: ':question:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
    title: test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/persistent_union_find.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <utility>\n\n#line 1 \"library/datastructure/persistent_array.hpp\"\
    \n\n\n\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include <deque>\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T, bool auto_extend =\
    \ false>\n    struct ObjectPool {\n        using value_type = T;\n        using\
    \ value_pointer_type = T*;\n\n        template <typename U>\n        using container_type\
    \ = std::conditional_t<auto_extend, std::deque<U>, std::vector<U>>;\n\n      \
    \  container_type<value_type> pool;\n        container_type<value_pointer_type>\
    \ stock;\n        decltype(stock.begin()) it;\n\n        ObjectPool() : ObjectPool(0)\
    \ {}\n        ObjectPool(int siz) : pool(siz), stock(siz) {\n            clear();\n\
    \        }\n\n        int capacity() const { return pool.size(); }\n        int\
    \ size() const { return it - stock.begin(); }\n\n        value_pointer_type alloc()\
    \ {\n            if constexpr (auto_extend) ensure();\n            return *it++;\n\
    \        }\n\n        void free(value_pointer_type t) {\n            *--it = t;\n\
    \        }\n\n        void clear() {\n            int siz = pool.size();\n   \
    \         it = stock.begin();\n            for (int i = 0; i < siz; i++) stock[i]\
    \ = &pool[i];\n        }\n\n        void ensure() {\n            if (it != stock.end())\
    \ return;\n            int siz = stock.size();\n            for (int i = siz;\
    \ i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 6 \"library/datastructure/persistent_array.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, int lg_ary = 4>\n    struct\
    \ PersistentArray {\n        struct Node;\n        using node_type = Node;\n \
    \       using node_pointer_type = node_type*;\n        using value_type = T;\n\
    \        using pool_type = ObjectPool<node_type>;\n        struct Node {\n   \
    \         static inline pool_type pool{};\n            static constexpr int mask\
    \ = (1 << lg_ary) - 1;\n\n            node_pointer_type _ch[1 << lg_ary]{};\n\
    \            value_type _val;\n            Node(const value_type& val = value_type{})\
    \ : _val(val) {}\n\n            static node_pointer_type clone(node_pointer_type\
    \ node) {\n                return &(*pool.alloc() = *node);\n            }\n \
    \           static node_pointer_type new_node(const value_type& val) {\n     \
    \           return &(*pool.alloc() = node_type(val));\n            }\n       \
    \     static value_type& get(node_pointer_type node, int id) {\n             \
    \   for (; id; --id >>= lg_ary) node = node->_ch[id & mask];\n               \
    \ return node->_val;\n            }\n            static node_pointer_type set(node_pointer_type\
    \ node, int id, const value_type& val) {\n                node_pointer_type res\
    \ = clone(node), cur = res;\n                for (; id; --id >>= lg_ary) cur =\
    \ cur->_ch[id & mask] = clone(cur->_ch[id & mask]);\n                cur->_val\
    \ = val;\n                return res;\n            }\n            static value_type\
    \ mut_set(node_pointer_type node, int id, const value_type& val) {\n         \
    \       return std::exchange(get(node, id), val);\n            }\n           \
    \ static node_pointer_type build(const std::vector<value_type>& init) {\n    \
    \            const int n = init.size();\n                if (n == 0) return nullptr;\n\
    \                auto dfs = [&](auto dfs, node_pointer_type cur, int id, int p)\
    \ -> void {\n                    int np = p << lg_ary, nid = id + p;\n       \
    \             for (int d = 1; d < 1 << lg_ary; ++d, nid += p) {\n            \
    \            if (nid < n) dfs(dfs, cur->_ch[d] = new_node(init[nid]), nid, np);\n\
    \                        else return;\n                    }\n               \
    \     if (nid < n) dfs(dfs, cur->_ch[0] = new_node(init[nid]), nid, np);\n   \
    \             };\n                node_pointer_type root = new_node(init[0]);\n\
    \                dfs(dfs, root, 0, 1);\n                return root;\n       \
    \     }\n            static std::vector<value_type> dump(node_pointer_type node)\
    \ {\n                if (not node) return {};\n                std::vector<value_type>\
    \ res;\n                auto dfs = [&](auto dfs, node_pointer_type cur, int id,\
    \ int p) -> void {\n                    if (int(res.size()) <= id) res.resize(id\
    \ + 1);\n                    res[id] = node->_val;\n                    int np\
    \ = p << lg_ary, nid = id + p;\n                    for (int d = 1; d < 1 << lg_ary;\
    \ ++d, nid += p) {\n                        if (cur->_ch[d]) dfs(dfs, cur->_ch[d],\
    \ nid, np);\n                        else return;\n                    }\n   \
    \                 if (cur->_ch[0]) dfs(dfs, cur->_ch[0], nid, np);\n         \
    \       };\n                dfs(dfs, node, 0, 1);\n                return res;\n\
    \            }\n        };\n\n        static void init_pool(int capacity) {\n\
    \            node_type::pool = pool_type(capacity);\n        }\n\n        PersistentArray()\
    \ {}\n        explicit PersistentArray(int n, const value_type& val = value_type{})\
    \ : PersistentArray(std::vector<value_type>(n, val)) {}\n        PersistentArray(const\
    \ std::vector<value_type>& init) : _n(init.size()), _root(node_type::build(init))\
    \ {}\n\n        int size() const {\n            return _n;\n        }\n      \
    \  const value_type& get(int id) {\n            return node_type::get(_root, id);\n\
    \        }\n        PersistentArray set(int id, const value_type& new_val) {\n\
    \            return PersistentArray{ _n, node_type::set(_root, id, new_val) };\n\
    \        }\n        value_type mut_set(int id, const value_type& new_val) {\n\
    \            return node_type::mut_set(_root, id, new_val);\n        }\n     \
    \   PersistentArray clone() {\n            if (not _root) return PersistentArray\
    \ { _n, _root };\n            return PersistentArray{ _n, node_type::clone(_root)\
    \ };\n        }\n        std::vector<value_type> dump() {\n            return\
    \ node_type::dump(_root);\n        }\n    private:\n        int _n;\n        node_pointer_type\
    \ _root;\n        explicit PersistentArray(int n, node_pointer_type root) : _n(n),\
    \ _root(root) {}\n    };\n} // namespace suisen\n\n\n#line 8 \"library/datastructure/union_find/persistent_union_find.hpp\"\
    \n\nnamespace suisen {\n    struct PersistentUnionFind {\n        using array_type\
    \ = PersistentArray<int, 4>;\n\n        PersistentUnionFind() {}\n        explicit\
    \ PersistentUnionFind(int n) : _n(n), _dat(_n, -1) {}\n\n        static void init_pool(int\
    \ capacity) {\n            array_type::init_pool(capacity);\n        }\n\n   \
    \     // Get the root of `x`. equivalent to `operator[](x)`\n        int root(int\
    \ x) {\n            static std::vector<int> buf;\n            while (true) {\n\
    \                if (int r = _dat.get(x); r >= 0) buf.push_back(std::exchange(x,\
    \ r));\n                else break;\n            }\n            while (buf.size())\
    \ _dat.mut_set(buf.back(), x), buf.pop_back();\n            return x;\n      \
    \  }\n        // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y`.\n        std::pair<PersistentUnionFind, bool> merge(int x, int\
    \ y) {\n            x = root(x), y = root(y);\n            if (x == y) return\
    \ { *this, false };\n            int vx = _dat.get(x), vy = _dat.get(y);\n   \
    \         if (vx > vy) std::swap(x, y), std::swap(vx, vy);\n            array_type\
    \ new_dat = _dat;\n            new_dat = new_dat.set(x, vx + vy);\n          \
    \  new_dat = new_dat.set(y, x);\n            return { PersistentUnionFind(new_dat),\
    \ true };\n        }\n        // Check if `x` and `y` belongs to the same connected\
    \ component.\n        bool same(int x, int y) {\n            return root(x) ==\
    \ root(y);\n        }\n        // Get the size of connected componet to which\
    \ `x` belongs.\n        int size(int x) {\n            return -_dat.get(root(x));\n\
    \        }\n        // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(_n);\n           \
    \ for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto& g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n        std::vector<int> dump() {\n            return\
    \ _dat.dump();\n        }\n    protected:\n        int _n;\n        array_type\
    \ _dat;\n\n        explicit PersistentUnionFind(array_type dat) : _n(dat.size()),\
    \ _dat(dat) {}\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_PERSISTENT_UNION_FIND\n#define SUISEN_PERSISTENT_UNION_FIND\n\
    \n#include <algorithm>\n#include <utility>\n\n#include \"library/datastructure/persistent_array.hpp\"\
    \n\nnamespace suisen {\n    struct PersistentUnionFind {\n        using array_type\
    \ = PersistentArray<int, 4>;\n\n        PersistentUnionFind() {}\n        explicit\
    \ PersistentUnionFind(int n) : _n(n), _dat(_n, -1) {}\n\n        static void init_pool(int\
    \ capacity) {\n            array_type::init_pool(capacity);\n        }\n\n   \
    \     // Get the root of `x`. equivalent to `operator[](x)`\n        int root(int\
    \ x) {\n            static std::vector<int> buf;\n            while (true) {\n\
    \                if (int r = _dat.get(x); r >= 0) buf.push_back(std::exchange(x,\
    \ r));\n                else break;\n            }\n            while (buf.size())\
    \ _dat.mut_set(buf.back(), x), buf.pop_back();\n            return x;\n      \
    \  }\n        // Get the root of `x`. euivalent to `root(x)`\n        int operator[](int\
    \ x) {\n            return root(x);\n        }\n        // Merge two vertices\
    \ `x` and `y`.\n        std::pair<PersistentUnionFind, bool> merge(int x, int\
    \ y) {\n            x = root(x), y = root(y);\n            if (x == y) return\
    \ { *this, false };\n            int vx = _dat.get(x), vy = _dat.get(y);\n   \
    \         if (vx > vy) std::swap(x, y), std::swap(vx, vy);\n            array_type\
    \ new_dat = _dat;\n            new_dat = new_dat.set(x, vx + vy);\n          \
    \  new_dat = new_dat.set(y, x);\n            return { PersistentUnionFind(new_dat),\
    \ true };\n        }\n        // Check if `x` and `y` belongs to the same connected\
    \ component.\n        bool same(int x, int y) {\n            return root(x) ==\
    \ root(y);\n        }\n        // Get the size of connected componet to which\
    \ `x` belongs.\n        int size(int x) {\n            return -_dat.get(root(x));\n\
    \        }\n        // Get all of connected components.\n        std::vector<std::vector<int>>\
    \ groups() {\n            std::vector<std::vector<int>> res(_n);\n           \
    \ for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);\n            res.erase(std::remove_if(res.begin(),\
    \ res.end(), [](const auto& g) { return g.empty(); }), res.end());\n         \
    \   return res;\n        }\n        std::vector<int> dump() {\n            return\
    \ _dat.dump();\n        }\n    protected:\n        int _n;\n        array_type\
    \ _dat;\n\n        explicit PersistentUnionFind(array_type dat) : _n(dat.size()),\
    \ _dat(dat) {}\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_PERSISTENT_UNION_FIND\n"
  dependsOn:
  - library/datastructure/persistent_array.hpp
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/datastructure/union_find/persistent_union_find.hpp
  requiredBy: []
  timestamp: '2022-07-02 19:24:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
documentation_of: library/datastructure/union_find/persistent_union_find.hpp
layout: document
redirect_from:
- /library/library/datastructure/union_find/persistent_union_find.hpp
- /library/library/datastructure/union_find/persistent_union_find.hpp.html
title: library/datastructure/union_find/persistent_union_find.hpp
---
