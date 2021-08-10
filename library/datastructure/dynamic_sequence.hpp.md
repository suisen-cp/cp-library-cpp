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
  bundledCode: "#line 1 \"library/datastructure/dynamic_sequence.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n#include <utility>\n\nnamespace\
    \ suisen {\nnamespace internal::dynamic_sequence {\n\ntemplate <typename T>\n\
    struct Node {\n    T val;\n    int siz;\n    Node *ch[2] {nullptr, nullptr};\n\
    \    Node() : val() siz(1) {}\n    Node(const T &val) : val(val), siz(1) {}\n\
    \    ~Node() {\n        delete ch[0];\n        delete ch[1];\n    }\n    void\
    \ update() {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n    }\n    static\
    \ int size(Node *node) {\n        return node == nullptr ? 0 : node->siz;\n  \
    \  }\n    static Node* rotate(Node *node, int dir) { // dir: LEFT = 0, RIGHT =\
    \ 1\n        assert(node->ch[dir ^ 1] != nullptr);\n        Node *par = node->ch[dir\
    \ ^ 1];\n        node->ch[dir ^ 1] = par->ch[dir];\n        par->ch[dir] = node;\n\
    \        node->update(), par->update();\n        return par;\n    }\n    static\
    \ int locate(Node *node, int index) {\n        int siz_l = size(node->ch[0]);\n\
    \        return index == siz_l ? LOC_ROOT : index > siz_l;\n    }\n    static\
    \ Node* splay(Node *node, int index) {\n        std::vector<Node*> path;\n   \
    \     Node *work_root = new Node();\n        Node *work_leaf[2] {work_root, work_root};\n\
    \        while (true) {\n            int loc = locate(node, index);\n        \
    \    if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;\n            if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[0]) + 1;\n            int ch_loc = locate(node->ch[loc],\
    \ index);\n            if (ch_loc == loc) { // zig-zig\n                if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[loc]->ch[0]) + 1;\n                node\
    \ = rotate(node, loc ^ 1);\n                if (node->ch[loc] == nullptr) break;\n\
    \            }\n            path.push_back(node);\n            work_leaf[loc]->ch[loc]\
    \ = node;\n            work_leaf[loc] = node;\n            node = node->ch[loc];\n\
    \        }\n        work_leaf[0]->ch[0] = node->ch[1];\n        work_leaf[1]->ch[1]\
    \ = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n        node->ch[1]\
    \ = work_root->ch[0];\n        work_root->ch[0] = work_root->ch[1] = nullptr;\n\
    \        delete work_root;\n        while (path.size()) path.back()->update(),\
    \ path.pop_back();\n        node->update();\n        return node;\n    }\n   \
    \ static Node* insert(Node *node, int index, const T &val) {\n        if (node\
    \ == nullptr) return new Node(val);\n        node = splay(node, index);\n    \
    \    Node *new_node = new Node(val);\n        bool loc = index <= size(node->ch[0]);\n\
    \        new_node->ch[loc] = node;\n        new_node->ch[loc ^ 1] = node->ch[loc\
    \ ^ 1];\n        node->ch[loc ^ 1] = nullptr;\n        node->update(), new_node->update();\n\
    \        return new_node;\n    }\n    static Node* erase(Node *node, int index)\
    \ {\n        if (node == nullptr) return node;\n        node = splay(node, index);\n\
    \        if (node->ch[0] != nullptr and node->ch[1] != nullptr) {\n          \
    \  Node *left_max_node = splay(node->ch[0], index);\n            left_max_node->ch[1]\
    \ = node->ch[1];\n            node->ch[0] = node->ch[1] = nullptr;\n         \
    \   delete node;\n            left_max_node->update();\n            return left_max_node;\n\
    \        } else {\n            int choose = node->ch[0] == nullptr;\n        \
    \    Node *res = node->ch[choose];\n            node->ch[choose] = nullptr;\n\
    \            delete node;\n            return res;\n        }\n    }\n    static\
    \ std::pair<Node*, Node*> split(Node *node, int k) {\n        if (node == nullptr)\
    \ return { nullptr, nullptr };\n        if (k == size(node)) return { node, nullptr\
    \ };\n        Node *tree_r = splay(node, k);\n        Node *tree_l = tree_r->ch[0];\n\
    \        tree_r->ch[0] = nullptr;\n        tree_r->update();\n        return {\
    \ tree_l, tree_r };\n    }\n    static Node* merge(Node *node_l, Node *node_r)\
    \ {\n        if (node_l == nullptr) return node_r;\n        if (node_r == nullptr)\
    \ return node_l;\n        node_r = splay(node_r, 0);\n        node_r->ch[0] =\
    \ node_l;\n        node_r->update();\n        return node_r;\n    }\n};\n}\n\n\
    template <typename T>\nclass DynamicSequence {\n    using Node = internal::dynamic_sequence::Node<T>;\n\
    \    public:\n        DynamicSequence() : root(nullptr) {}\n        ~DynamicSequence()\
    \ {\n            delete root;\n        }\n        void insert(int k, const T&\
    \ val) {\n            index_bounds_check(k, size() + 1);\n            root = Node::insert(root,\
    \ k, val);\n        }\n        void erase(int k) {\n            index_bounds_check(k,\
    \ size());\n            root = Node::erase(root, k);\n        }\n        T& operator[](int\
    \ k) {\n            index_bounds_check(k, size());\n            root = Node::splay(root,\
    \ k);\n            return root->val;\n        }\n        int size() {\n      \
    \      return Node::size(root);\n        }\n        DynamicSequence& operator+=(DynamicSequence\
    \ &&right) {\n            root = Node::merge(root, right.root);\n            return\
    \ *this;\n        }\n        void concat(DynamicSequence &&right) {\n        \
    \    *this += std::move(right);\n        }\n        void concat_left(DynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \   }\n        // [0, k), [k, size())\n        std::pair<DynamicSequence, DynamicSequence>\
    \ split(int k) {\n            auto [l, r] = Node::split(k);\n            return\
    \ { DynamicSequence(l), DynamicSequence(r) };\n        }\n    private:\n     \
    \   Node *root;\n        DynamicSequence(Node *root) : root(root) {}\n       \
    \ bool index_bounds_check(unsigned int k, unsigned int n) {\n            return\
    \ k < n;\n        }\n};\n}\n\n\n"
  code: "#ifndef SUISEN_DYNAMIC_SEQUENCE\n#define SUISEN_DYNAMIC_SEQUENCE\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n#include <utility>\n\nnamespace\
    \ suisen {\nnamespace internal::dynamic_sequence {\n\ntemplate <typename T>\n\
    struct Node {\n    T val;\n    int siz;\n    Node *ch[2] {nullptr, nullptr};\n\
    \    Node() : val() siz(1) {}\n    Node(const T &val) : val(val), siz(1) {}\n\
    \    ~Node() {\n        delete ch[0];\n        delete ch[1];\n    }\n    void\
    \ update() {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n    }\n    static\
    \ int size(Node *node) {\n        return node == nullptr ? 0 : node->siz;\n  \
    \  }\n    static Node* rotate(Node *node, int dir) { // dir: LEFT = 0, RIGHT =\
    \ 1\n        assert(node->ch[dir ^ 1] != nullptr);\n        Node *par = node->ch[dir\
    \ ^ 1];\n        node->ch[dir ^ 1] = par->ch[dir];\n        par->ch[dir] = node;\n\
    \        node->update(), par->update();\n        return par;\n    }\n    static\
    \ int locate(Node *node, int index) {\n        int siz_l = size(node->ch[0]);\n\
    \        return index == siz_l ? LOC_ROOT : index > siz_l;\n    }\n    static\
    \ Node* splay(Node *node, int index) {\n        std::vector<Node*> path;\n   \
    \     Node *work_root = new Node();\n        Node *work_leaf[2] {work_root, work_root};\n\
    \        while (true) {\n            int loc = locate(node, index);\n        \
    \    if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;\n            if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[0]) + 1;\n            int ch_loc = locate(node->ch[loc],\
    \ index);\n            if (ch_loc == loc) { // zig-zig\n                if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[loc]->ch[0]) + 1;\n                node\
    \ = rotate(node, loc ^ 1);\n                if (node->ch[loc] == nullptr) break;\n\
    \            }\n            path.push_back(node);\n            work_leaf[loc]->ch[loc]\
    \ = node;\n            work_leaf[loc] = node;\n            node = node->ch[loc];\n\
    \        }\n        work_leaf[0]->ch[0] = node->ch[1];\n        work_leaf[1]->ch[1]\
    \ = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n        node->ch[1]\
    \ = work_root->ch[0];\n        work_root->ch[0] = work_root->ch[1] = nullptr;\n\
    \        delete work_root;\n        while (path.size()) path.back()->update(),\
    \ path.pop_back();\n        node->update();\n        return node;\n    }\n   \
    \ static Node* insert(Node *node, int index, const T &val) {\n        if (node\
    \ == nullptr) return new Node(val);\n        node = splay(node, index);\n    \
    \    Node *new_node = new Node(val);\n        bool loc = index <= size(node->ch[0]);\n\
    \        new_node->ch[loc] = node;\n        new_node->ch[loc ^ 1] = node->ch[loc\
    \ ^ 1];\n        node->ch[loc ^ 1] = nullptr;\n        node->update(), new_node->update();\n\
    \        return new_node;\n    }\n    static Node* erase(Node *node, int index)\
    \ {\n        if (node == nullptr) return node;\n        node = splay(node, index);\n\
    \        if (node->ch[0] != nullptr and node->ch[1] != nullptr) {\n          \
    \  Node *left_max_node = splay(node->ch[0], index);\n            left_max_node->ch[1]\
    \ = node->ch[1];\n            node->ch[0] = node->ch[1] = nullptr;\n         \
    \   delete node;\n            left_max_node->update();\n            return left_max_node;\n\
    \        } else {\n            int choose = node->ch[0] == nullptr;\n        \
    \    Node *res = node->ch[choose];\n            node->ch[choose] = nullptr;\n\
    \            delete node;\n            return res;\n        }\n    }\n    static\
    \ std::pair<Node*, Node*> split(Node *node, int k) {\n        if (node == nullptr)\
    \ return { nullptr, nullptr };\n        if (k == size(node)) return { node, nullptr\
    \ };\n        Node *tree_r = splay(node, k);\n        Node *tree_l = tree_r->ch[0];\n\
    \        tree_r->ch[0] = nullptr;\n        tree_r->update();\n        return {\
    \ tree_l, tree_r };\n    }\n    static Node* merge(Node *node_l, Node *node_r)\
    \ {\n        if (node_l == nullptr) return node_r;\n        if (node_r == nullptr)\
    \ return node_l;\n        node_r = splay(node_r, 0);\n        node_r->ch[0] =\
    \ node_l;\n        node_r->update();\n        return node_r;\n    }\n};\n}\n\n\
    template <typename T>\nclass DynamicSequence {\n    using Node = internal::dynamic_sequence::Node<T>;\n\
    \    public:\n        DynamicSequence() : root(nullptr) {}\n        ~DynamicSequence()\
    \ {\n            delete root;\n        }\n        void insert(int k, const T&\
    \ val) {\n            index_bounds_check(k, size() + 1);\n            root = Node::insert(root,\
    \ k, val);\n        }\n        void erase(int k) {\n            index_bounds_check(k,\
    \ size());\n            root = Node::erase(root, k);\n        }\n        T& operator[](int\
    \ k) {\n            index_bounds_check(k, size());\n            root = Node::splay(root,\
    \ k);\n            return root->val;\n        }\n        int size() {\n      \
    \      return Node::size(root);\n        }\n        DynamicSequence& operator+=(DynamicSequence\
    \ &&right) {\n            root = Node::merge(root, right.root);\n            return\
    \ *this;\n        }\n        void concat(DynamicSequence &&right) {\n        \
    \    *this += std::move(right);\n        }\n        void concat_left(DynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \   }\n        // [0, k), [k, size())\n        std::pair<DynamicSequence, DynamicSequence>\
    \ split(int k) {\n            auto [l, r] = Node::split(k);\n            return\
    \ { DynamicSequence(l), DynamicSequence(r) };\n        }\n    private:\n     \
    \   Node *root;\n        DynamicSequence(Node *root) : root(root) {}\n       \
    \ bool index_bounds_check(unsigned int k, unsigned int n) {\n            return\
    \ k < n;\n        }\n};\n}\n\n#endif // SUISEN_DYNAMIC_SEQUENCE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/dynamic_sequence.hpp
  requiredBy: []
  timestamp: '2021-08-11 01:57:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/dynamic_sequence.hpp
layout: document
redirect_from:
- /library/library/datastructure/dynamic_sequence.hpp
- /library/library/datastructure/dynamic_sequence.hpp.html
title: library/datastructure/dynamic_sequence.hpp
---
