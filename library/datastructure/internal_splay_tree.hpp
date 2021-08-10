#ifndef SUISEN_INTERNAL_SPLAY_TREE
#define SUISEN_INTERNAL_SPLAY_TREE

#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

namespace suisen::internal::splay_tree {

template <typename Key, typename Val>
struct Node {
    Key key;
    Val val;
    int siz;
    Node *ch[2] {nullptr, nullptr};
    Node() : key(), val(), siz(1) {}
    Node(const Key &key, const Val &val) : key(key), val(val), siz(1) {}
    ~Node() {
        delete ch[0];
        delete ch[1];
    }
    void update() {
        siz = 1 + size(ch[0]) + size(ch[1]);
    }
    static int size(Node *node) {
        return node == nullptr ? 0 : node->siz;
    }
    static Node* rotate(Node *node, int dir) { // dir: LEFT = 0, RIGHT = 1
        assert(node->ch[dir ^ 1] != nullptr);
        Node *par = node->ch[dir ^ 1];
        node->ch[dir ^ 1] = par->ch[dir];
        par->ch[dir] = node;
        node->update(), par->update();
        return par;
    }
    static Node* splay(Node *node, const Key &x) {
        std::vector<Node*> path;
        Node *work_root = new Node();
        Node *work_leaf[2] {work_root, work_root};
        while (true) {
            if (x == node->key) break;
            bool loc = x > node->key;
            if (node->ch[loc] == nullptr) break;
            bool ch_loc = x > node->ch[loc]->key;
            if (ch_loc == loc) { // zig-zig
                node = rotate(node, loc ^ 1);
                if (node->ch[loc] == nullptr) break;
            }
            path.push_back(node);
            work_leaf[loc]->ch[loc] = node;
            work_leaf[loc] = node;
            node = node->ch[loc];
        }
        work_leaf[0]->ch[0] = node->ch[1];
        work_leaf[1]->ch[1] = node->ch[0];
        node->ch[0] = work_root->ch[1];
        node->ch[1] = work_root->ch[0];
        work_root->ch[0] = work_root->ch[1] = nullptr;
        delete work_root;
        while (path.size()) path.back()->update(), path.pop_back();
        node->update();
        return node;
    }
    static std::pair<Node*, bool> search(Node *node, const Key &x) {
        if (node == nullptr) return { node, false };
        node = splay(node, x);
        return { node, node->key == x };
    }
    static Node* insert(Node *node, const Key &key, const Val &val, bool overwrite = true) {
        if (node == nullptr) return new Node(key, val);
        auto [dst_node, found] = search(node, key);
        if (found) {
            if (overwrite) dst_node->val = val;
            return dst_node;
        }
        Node *new_node = new Node(key, val);
        bool loc = key < dst_node->key;
        new_node->ch[loc] = dst_node;
        new_node->ch[loc ^ 1] = dst_node->ch[loc ^ 1];
        dst_node->ch[loc ^ 1] = nullptr;
        dst_node->update(), new_node->update();
        return new_node;
    }
    static std::pair<Node*, bool> erase(Node *node, const Key &key) {
        if (node == nullptr) return { node, false };
        auto [dst_node, found] = search(node, key);
        if (not found) return { dst_node, false };
        if (dst_node->ch[0] != nullptr and dst_node->ch[1] != nullptr) {
            Node *left_max_node = splay(dst_node->ch[0], key);
            left_max_node->ch[1] = dst_node->ch[1];
            dst_node->ch[0] = dst_node->ch[1] = nullptr;
            delete dst_node;
            left_max_node->update();
            return { left_max_node, true };
        } else {
            int choose = dst_node->ch[0] == nullptr;
            Node* res = dst_node->ch[choose];
            dst_node->ch[choose] = nullptr;
            delete dst_node;
            return { res, true };
        }
    }
    static std::pair<Node*, Val> get_or_default(Node *node, const Key &key, const Val &default_value) {
        auto [dst_node, found] = search(node, key);
        return { dst_node, found ? dst_node->val : default_value };
    }
    static std::pair<Key, Val> kth_entry(Node *node, int k) {
        assert((unsigned int) k < (unsigned int) size(node));
        while (true) {
            int siz = size(node->ch[0]);
            if (k == siz) return { node->key, node->val };
            if (k > siz) {
                k -= siz + 1;
                node = node->ch[1];
            } else {
                node = node->ch[0];
            }
        }
    }
};
};

#endif // SUISEN_INTERNAL_SPLAY_TREE
