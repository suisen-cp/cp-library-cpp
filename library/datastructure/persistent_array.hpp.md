---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/union_find/persistent_union_find.hpp
    title: library/datastructure/union_find/persistent_union_find.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
    title: test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/persistent_array.hpp\"\n\n\n\n#include\
    \ <utility>\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include <deque>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, bool auto_extend\
    \ = false>\n    struct ObjectPool {\n        using value_type = T;\n        using\
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
    \ _root(root) {}\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_PERSISTENT_ARRAY\n#define SUISEN_PERSISTENT_ARRAY\n\n#include\
    \ <utility>\n#include \"library/util/object_pool.hpp\"\n\nnamespace suisen {\n\
    \    template <typename T, int lg_ary = 4>\n    struct PersistentArray {\n   \
    \     struct Node;\n        using node_type = Node;\n        using node_pointer_type\
    \ = node_type*;\n        using value_type = T;\n        using pool_type = ObjectPool<node_type>;\n\
    \        struct Node {\n            static inline pool_type pool{};\n        \
    \    static constexpr int mask = (1 << lg_ary) - 1;\n\n            node_pointer_type\
    \ _ch[1 << lg_ary]{};\n            value_type _val;\n            Node(const value_type&\
    \ val = value_type{}) : _val(val) {}\n\n            static node_pointer_type clone(node_pointer_type\
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
    \ _root(root) {}\n    };\n} // namespace suisen\n\n#endif // SUISEN_PERSISTENT_ARRAY\n"
  dependsOn:
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/datastructure/persistent_array.hpp
  requiredBy:
  - library/datastructure/union_find/persistent_union_find.hpp
  timestamp: '2022-07-02 19:24:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/union_find/persistent_union_find/persistent_unionfind.test.cpp
documentation_of: library/datastructure/persistent_array.hpp
layout: document
redirect_from:
- /library/library/datastructure/persistent_array.hpp
- /library/library/datastructure/persistent_array.hpp.html
title: library/datastructure/persistent_array.hpp
---
