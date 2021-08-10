---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/datastructure/internal_splay_tree.hpp
    title: library/datastructure/internal_splay_tree.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/datastructure/splay_tree_set.hpp
    title: library/datastructure/splay_tree_set.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/splay_tree_map.hpp\"\n\n\n\n#line\
    \ 1 \"library/datastructure/internal_splay_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n#include <utility>\n\nnamespace suisen::internal::splay_tree\
    \ {\n\ntemplate <typename Key, typename Val>\nstruct Node {\n    Key key;\n  \
    \  Val val;\n    int siz;\n    Node *ch[2] {nullptr, nullptr};\n    Node() : key(),\
    \ val(), siz(1) {}\n    Node(const Key &key, const Val &val) : key(key), val(val),\
    \ siz(1) {}\n    ~Node() {\n        delete ch[0];\n        delete ch[1];\n   \
    \ }\n    void update() {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n    }\n\
    \    static int size(Node *node) {\n        return node == nullptr ? 0 : node->siz;\n\
    \    }\n    static Node* rotate(Node *node, int dir) { // dir: LEFT = 0, RIGHT\
    \ = 1\n        assert(node->ch[dir ^ 1] != nullptr);\n        Node *par = node->ch[dir\
    \ ^ 1];\n        node->ch[dir ^ 1] = par->ch[dir];\n        par->ch[dir] = node;\n\
    \        node->update(), par->update();\n        return par;\n    }\n    static\
    \ Node* splay(Node *node, const Key &x) {\n        std::vector<Node*> path;\n\
    \        Node *work_root = new Node();\n        Node *work_leaf[2] {work_root,\
    \ work_root};\n        while (true) {\n            if (x == node->key) break;\n\
    \            bool loc = x > node->key;\n            if (node->ch[loc] == nullptr)\
    \ break;\n            bool ch_loc = x > node->ch[loc]->key;\n            if (ch_loc\
    \ == loc) { // zig-zig\n                node = rotate(node, loc ^ 1);\n      \
    \          if (node->ch[loc] == nullptr) break;\n            }\n            path.push_back(node);\n\
    \            work_leaf[loc]->ch[loc] = node;\n            work_leaf[loc] = node;\n\
    \            node = node->ch[loc];\n        }\n        work_leaf[0]->ch[0] = node->ch[1];\n\
    \        work_leaf[1]->ch[1] = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n\
    \        node->ch[1] = work_root->ch[0];\n        work_root->ch[0] = work_root->ch[1]\
    \ = nullptr;\n        delete work_root;\n        while (path.size()) path.back()->update(),\
    \ path.pop_back();\n        node->update();\n        return node;\n    }\n   \
    \ static std::pair<Node*, bool> search(Node *node, const Key &x) {\n        if\
    \ (node == nullptr) return { node, false };\n        node = splay(node, x);\n\
    \        return { node, node->key == x };\n    }\n    static Node* insert(Node\
    \ *node, const Key &key, const Val &val, bool overwrite = true) {\n        if\
    \ (node == nullptr) return new Node(key, val);\n        auto [dst_node, found]\
    \ = search(node, key);\n        if (found) {\n            if (overwrite) dst_node->val\
    \ = val;\n            return dst_node;\n        }\n        Node *new_node = new\
    \ Node(key, val);\n        bool loc = key < dst_node->key;\n        new_node->ch[loc]\
    \ = dst_node;\n        new_node->ch[loc ^ 1] = dst_node->ch[loc ^ 1];\n      \
    \  dst_node->ch[loc ^ 1] = nullptr;\n        dst_node->update(), new_node->update();\n\
    \        return new_node;\n    }\n    static std::pair<Node*, bool> erase(Node\
    \ *node, const Key &key) {\n        if (node == nullptr) return { node, false\
    \ };\n        auto [dst_node, found] = search(node, key);\n        if (not found)\
    \ return { dst_node, false };\n        if (dst_node->ch[0] != nullptr and dst_node->ch[1]\
    \ != nullptr) {\n            Node *left_max_node = splay(dst_node->ch[0], key);\n\
    \            left_max_node->ch[1] = dst_node->ch[1];\n            dst_node->ch[0]\
    \ = dst_node->ch[1] = nullptr;\n            delete dst_node;\n            left_max_node->update();\n\
    \            return { left_max_node, true };\n        } else {\n            int\
    \ choose = dst_node->ch[0] == nullptr;\n            Node* res = dst_node->ch[choose];\n\
    \            dst_node->ch[choose] = nullptr;\n            delete dst_node;\n \
    \           return { res, true };\n        }\n    }\n    static std::pair<Node*,\
    \ Val> get_or_default(Node *node, const Key &key, const Val &default_value) {\n\
    \        auto [dst_node, found] = search(node, key);\n        return { dst_node,\
    \ found ? dst_node->val : default_value };\n    }\n    static std::pair<Key, Val>\
    \ kth_entry(Node *node, int k) {\n        assert((unsigned int) k < (unsigned\
    \ int) size(node));\n        while (true) {\n            int siz = size(node->ch[0]);\n\
    \            if (k == siz) return { node->key, node->val };\n            if (k\
    \ > siz) {\n                k -= siz + 1;\n                node = node->ch[1];\n\
    \            } else {\n                node = node->ch[0];\n            }\n  \
    \      }\n    }\n};\n};\n\n\n#line 5 \"library/datastructure/splay_tree_map.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename Key, typename Val>\nclass SplayTreeMap\
    \ {\n    using Node = internal::splay_tree::Node<Key, Val>;\n    public:\n   \
    \     SplayTreeMap() : root(nullptr) {}\n        ~SplayTreeMap() {\n         \
    \   delete root;\n        }\n        bool contains(const Key &key) {\n       \
    \     auto [new_root, found] = Node::search(root, key);\n            root = new_root;\n\
    \            return found;\n        }\n        void insert(const Key &key, const\
    \ Val &val) {\n            root = Node::insert(root, key, val, true);\n      \
    \  }\n        void insert_if_absent(const Key &key, const Val &val) {\n      \
    \      root = Node::insert(root, key, val, false);\n        }\n        bool erase(const\
    \ Key &key) {\n            auto [new_root, is_erased] = Node::erase(root, key);\n\
    \            root = new_root;\n            return is_erased;\n        }\n    \
    \    Val& get_or_create(const Key &key, const Val &val) {\n            root =\
    \ Node::insert(root, key, val, false);\n            return root->val;\n      \
    \  }\n        Val& operator[](const Key &key) {\n            return get_or_create(key,\
    \ Val{});\n        }\n        Val get_or_default(const Key &key, const Val &val)\
    \ {\n            auto [new_root, res] = Node::get_or_default(root, key, val);\n\
    \            root = new_root;\n            return res;\n        }\n        std::pair<Key,\
    \ Val> kth_entry(int k) {\n            return Node::kth_entry(root, k);\n    \
    \    }\n        int size() {\n            return Node::size(root);\n        }\n\
    \    private:\n        Node *root;\n};\n\n};\n\n\n"
  code: "#ifndef SUISEN_SPLAY_TREE_MAP\n#define SUISEN_SPLAY_TREE_MAP\n\n#include\
    \ \"library/datastructure/internal_splay_tree.hpp\"\n\nnamespace suisen {\n\n\
    template <typename Key, typename Val>\nclass SplayTreeMap {\n    using Node =\
    \ internal::splay_tree::Node<Key, Val>;\n    public:\n        SplayTreeMap() :\
    \ root(nullptr) {}\n        ~SplayTreeMap() {\n            delete root;\n    \
    \    }\n        bool contains(const Key &key) {\n            auto [new_root, found]\
    \ = Node::search(root, key);\n            root = new_root;\n            return\
    \ found;\n        }\n        void insert(const Key &key, const Val &val) {\n \
    \           root = Node::insert(root, key, val, true);\n        }\n        void\
    \ insert_if_absent(const Key &key, const Val &val) {\n            root = Node::insert(root,\
    \ key, val, false);\n        }\n        bool erase(const Key &key) {\n       \
    \     auto [new_root, is_erased] = Node::erase(root, key);\n            root =\
    \ new_root;\n            return is_erased;\n        }\n        Val& get_or_create(const\
    \ Key &key, const Val &val) {\n            root = Node::insert(root, key, val,\
    \ false);\n            return root->val;\n        }\n        Val& operator[](const\
    \ Key &key) {\n            return get_or_create(key, Val{});\n        }\n    \
    \    Val get_or_default(const Key &key, const Val &val) {\n            auto [new_root,\
    \ res] = Node::get_or_default(root, key, val);\n            root = new_root;\n\
    \            return res;\n        }\n        std::pair<Key, Val> kth_entry(int\
    \ k) {\n            return Node::kth_entry(root, k);\n        }\n        int size()\
    \ {\n            return Node::size(root);\n        }\n    private:\n        Node\
    \ *root;\n};\n\n};\n\n#endif // SUISEN_SPLAY_TREE_MAP\n"
  dependsOn:
  - library/datastructure/internal_splay_tree.hpp
  isVerificationFile: false
  path: library/datastructure/splay_tree_map.hpp
  requiredBy:
  - library/datastructure/splay_tree_set.hpp
  timestamp: '2021-08-11 01:57:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/splay_tree_map.hpp
layout: document
redirect_from:
- /library/library/datastructure/splay_tree_map.hpp
- /library/library/datastructure/splay_tree_map.hpp.html
title: library/datastructure/splay_tree_map.hpp
---
