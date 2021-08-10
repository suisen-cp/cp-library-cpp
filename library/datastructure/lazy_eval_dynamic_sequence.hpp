#ifndef SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE
#define SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE

#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

#include "library/util/update_proxy_object.hpp"

namespace suisen {
namespace internal::lazy_eval_dynamic_sequence {

static constexpr int LOC_LEFT = 0;
static constexpr int LOC_RIGHT = 1;
static constexpr int LOC_ROOT = 2;

template <typename T, T (*e)(), T(*op)(T, T), typename F, F (*id)(), T(*mapping)(F, T), F(*composition)(F, F)>
struct Node {
    T val;
    T dat;
    F laz;
    bool rev;
    int siz;
    Node *ch[2] {nullptr, nullptr};
    Node() : val(e()), dat(e()), laz(id()), rev(false), siz(1) {}
    Node(const T &val) : val(val), dat(val), laz(id()), rev(false), siz(1) {}
    ~Node() {
        delete ch[0];
        delete ch[1];
    }
    void update() {
        siz = 1 + size(ch[0]) + size(ch[1]);
        dat = op(op(prod_subtree(ch[0]), val), prod_subtree(ch[1]));
    }
    void push() {
        apply(ch[0], laz), apply_rev(ch[0], rev);
        apply(ch[1], laz), apply_rev(ch[1], rev);
        laz = id(), rev = false;
    }
    static T prod_subtree(Node *node) {
        return node == nullptr ? e() : node->dat;
    }
    static void apply(Node *node, const F &f) {
        if (node == nullptr) return;
        node->val = mapping(f, node->val);
        node->dat = mapping(f, node->dat);
        node->laz = composition(f, node->laz);
    }
    static void apply_rev(Node *node, bool rev = true) {
        if (node == nullptr) return;
        if (rev) std::swap(node->ch[0], node->ch[1]);
        node->rev ^= rev;
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
            node->push();
            int loc = locate(node, index);
            if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;
            if (loc == LOC_RIGHT) index -= size(node->ch[0]) + 1;
            int ch_loc = locate(node->ch[loc], index);
            if (ch_loc == loc) { // zig-zig
                if (loc == LOC_RIGHT) index -= size(node->ch[loc]->ch[0]) + 1;
                node->ch[loc]->push();
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
        if (k == 0) return { nullptr, node };
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
    static Node* apply(Node *node, const F &f, int l, int r) {
        auto [node_l, node_mr] = split(node, l);
        auto [node_m, node_r] = split(node_mr, r - l);
        apply(node_m, f);
        return merge(node_l, merge(node_m, node_r));
    }
    static Node* reverse(Node *node, int l, int r) {
        auto [node_l, node_mr] = split(node, l);
        auto [node_m, node_r] = split(node_mr, r - l);
        apply_rev(node_m);
        return merge(node_l, merge(node_m, node_r));
    }
    static std::pair<Node*, T> prod(Node *node, int l, int r) {
        auto [node_l, node_mr] = split(node, l);
        auto [node_m, node_r] = split(node_mr, r - l);
        T res = prod_subtree(node_m);
        return { merge(node_l, merge(node_m, node_r)), res };
    }
};
}

template <typename T, T (*e)(), T(*op)(T, T), typename F, F (*id)(), T(*mapping)(F, T), F(*composition)(F, F)>
class LazyEvalDynamicSequence {
    using Node = internal::lazy_eval_dynamic_sequence::Node<T, e, op, F, id, mapping, composition>;
    public:
        LazyEvalDynamicSequence() : root(nullptr) {}
        ~LazyEvalDynamicSequence() {
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
        auto operator[](int k) {
            index_bounds_check(k, size());
            root = Node::splay(root, k);
            return UpdateProxyObject { root->val, [this]{ root->update(); } };
        }
        int size() {
            return Node::size(root);
        }
        void apply(const F &f, int l, int r) {
            assert(0 <= l and l <= r and r <= size());
            root = Node::apply(root, f, l, r);
        }
        T prod(int l, int r) {
            assert(0 <= l and l <= r and r <= size());
            auto [new_root, res] = Node::prod(root, l, r);
            root = new_root;
            return res;
        }
        T operator()(int l, int r) {
            return prod(l, r);
        }
        void reverse(int l, int r) {
            assert(0 <= l and l <= r and r <= size());
            root = Node::reverse(root, l, r);
        }
        LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) {
            root = Node::merge(root, right.root);
            return *this;
        }
        void concat(LazyEvalDynamicSequence &&right) {
            *this += std::move(right);
        }
        void concat_left(LazyEvalDynamicSequence &&left) {
            this->root = (left += std::move(*this)).root;
        }
        // [0, k), [k, size())
        std::pair<LazyEvalDynamicSequence, LazyEvalDynamicSequence> split(int k) {
            auto [l, r] = Node::split(root, k);
            return { LazyEvalDynamicSequence(l), LazyEvalDynamicSequence(r) };
        }
    private:
        Node *root;
        LazyEvalDynamicSequence(Node *root) : root(root) {}
        bool index_bounds_check(unsigned int k, unsigned int n) {
            return k < n;
        }
};
}

#endif // SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE
