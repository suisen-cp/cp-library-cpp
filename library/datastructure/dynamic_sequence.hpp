#ifndef SUISEN_DYNAMIC_SEQUENCE
#define SUISEN_DYNAMIC_SEQUENCE

#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

namespace suisen {
namespace internal::dynamic_sequence {

template <typename T>
struct Node {
    T val;
    int siz;
    Node *ch[2] {nullptr, nullptr};
    Node() : val() siz(1) {}
    Node(const T &val) : val(val), siz(1) {}
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
    static int locate(Node *node, int index) {
        int siz_l = size(node->ch[0]);
        return index == siz_l ? LOC_ROOT : index > siz_l;
    }
    static Node* splay(Node *node, int index) {
        std::vector<Node*> path;
        Node *work_root = new Node();
        Node *work_leaf[2] {work_root, work_root};
        while (true) {
            int loc = locate(node, index);
            if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;
            if (loc == LOC_RIGHT) index -= size(node->ch[0]) + 1;
            int ch_loc = locate(node->ch[loc], index);
            if (ch_loc == loc) { // zig-zig
                if (loc == LOC_RIGHT) index -= size(node->ch[loc]->ch[0]) + 1;
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
    static Node* insert(Node *node, int index, const T &val) {
        if (node == nullptr) return new Node(val);
        node = splay(node, index);
        Node *new_node = new Node(val);
        bool loc = index <= size(node->ch[0]);
        new_node->ch[loc] = node;
        new_node->ch[loc ^ 1] = node->ch[loc ^ 1];
        node->ch[loc ^ 1] = nullptr;
        node->update(), new_node->update();
        return new_node;
    }
    static Node* erase(Node *node, int index) {
        if (node == nullptr) return node;
        node = splay(node, index);
        if (node->ch[0] != nullptr and node->ch[1] != nullptr) {
            Node *left_max_node = splay(node->ch[0], index);
            left_max_node->ch[1] = node->ch[1];
            node->ch[0] = node->ch[1] = nullptr;
            delete node;
            left_max_node->update();
            return left_max_node;
        } else {
            int choose = node->ch[0] == nullptr;
            Node *res = node->ch[choose];
            node->ch[choose] = nullptr;
            delete node;
            return res;
        }
    }
    static std::pair<Node*, Node*> split(Node *node, int k) {
        if (node == nullptr) return { nullptr, nullptr };
        if (k == size(node)) return { node, nullptr };
        Node *tree_r = splay(node, k);
        Node *tree_l = tree_r->ch[0];
        tree_r->ch[0] = nullptr;
        tree_r->update();
        return { tree_l, tree_r };
    }
    static Node* merge(Node *node_l, Node *node_r) {
        if (node_l == nullptr) return node_r;
        if (node_r == nullptr) return node_l;
        node_r = splay(node_r, 0);
        node_r->ch[0] = node_l;
        node_r->update();
        return node_r;
    }
};
}

template <typename T>
class DynamicSequence {
    using Node = internal::dynamic_sequence::Node<T>;
    public:
        DynamicSequence() : root(nullptr) {}
        ~DynamicSequence() {
            delete root;
        }
        void insert(int k, const T& val) {
            index_bounds_check(k, size() + 1);
            root = Node::insert(root, k, val);
        }
        void erase(int k) {
            index_bounds_check(k, size());
            root = Node::erase(root, k);
        }
        T& operator[](int k) {
            index_bounds_check(k, size());
            root = Node::splay(root, k);
            return root->val;
        }
        int size() {
            return Node::size(root);
        }
        DynamicSequence& operator+=(DynamicSequence &&right) {
            root = Node::merge(root, right.root);
            return *this;
        }
        void concat(DynamicSequence &&right) {
            *this += std::move(right);
        }
        void concat_left(DynamicSequence &&left) {
            this->root = (left += std::move(*this)).root;
        }
        // [0, k), [k, size())
        std::pair<DynamicSequence, DynamicSequence> split(int k) {
            auto [l, r] = Node::split(k);
            return { DynamicSequence(l), DynamicSequence(r) };
        }
    private:
        Node *root;
        DynamicSequence(Node *root) : root(root) {}
        bool index_bounds_check(unsigned int k, unsigned int n) {
            return k < n;
        }
};
}

#endif // SUISEN_DYNAMIC_SEQUENCE
