#ifndef SUISEN_DYNAMIC_SEQUENCE
#define SUISEN_DYNAMIC_SEQUENCE

#include <cstddef>
#include <cassert>
#include <tuple>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {

namespace internal::dynamic_sequence {

template <typename T, typename Derived>
struct DynamicSequenceNodeBase {
    using node_ptr_t = Derived *;

    T val;
    int siz;
    bool rev;
    node_ptr_t ch[2] {nullptr, nullptr};

    DynamicSequenceNodeBase() : val(), siz(1), rev(false) {}
    DynamicSequenceNodeBase(const T &val) : val(val), siz(1), rev(false) {}

    ~DynamicSequenceNodeBase() {
        delete ch[0];
        delete ch[1];
    }

    void update() {
        siz = 1 + size(ch[0]) + size(ch[1]);
    }
    void push() {
        reverse_all(this->ch[0], rev), reverse_all(this->ch[1], rev);
        rev = false;
    }
    static int size(node_ptr_t node) {
        return node == nullptr ? 0 : node->siz;
    }

    static node_ptr_t rotate(node_ptr_t node, bool is_right) {
        node_ptr_t root = node->ch[is_right ^ true];
        node->ch[is_right ^ true] = root->ch[is_right];
        root->ch[is_right] = node;
        node->update(), root->update();
        return root;
    }

    static node_ptr_t splay(node_ptr_t node, int index) {
        std::vector<node_ptr_t> path;
        node_ptr_t work_root = new Derived();
        node_ptr_t work_leaf[2] { work_root, work_root };
        while (true) {
            node->push();
            int size_l = size(node->ch[0]);
            bool is_right = index > size_l;
            node_ptr_t next_node = node->ch[is_right];
            if (index == size_l or next_node == nullptr) { // found the target node
                break;
            }
            if (is_right) {
                index -= size_l + 1;
            }
            int size_l_ch = size(next_node->ch[0]);
            if (index != size_l_ch) {
                bool is_right_ch = index > size_l_ch;
                if (is_right_ch == is_right) { // zig-zig
                    if (is_right_ch) {
                        index -= size_l_ch + 1;
                    }
                    next_node->push();
                    node = rotate(node, is_right ^ true);
                    next_node = node->ch[is_right];
                    if (next_node == nullptr) { // found the target node
                        break;
                    }
                }
            }
            path.push_back(node);
            work_leaf[is_right]->ch[is_right] = node;
            work_leaf[is_right] = node;
            node = next_node;
        }
        work_leaf[0]->ch[0] = node->ch[1];
        work_leaf[1]->ch[1] = node->ch[0];
        node->ch[0] = work_root->ch[1];
        node->ch[1] = work_root->ch[0];
    
        work_root->ch[0] = work_root->ch[1] = nullptr;
        delete work_root;

        while (path.size()) {
            path.back()->update(), path.pop_back();
        }
        node->update();

        return node;
    }

    static std::pair<node_ptr_t, node_ptr_t> split(node_ptr_t node, int k) {
        if (k == 0) return { nullptr, node };
        if (k == size(node)) return { node, nullptr };
        node_ptr_t r = splay(node, k);
        node_ptr_t l = r->ch[0];
        r->ch[0] = nullptr;
        r->update();
        return { l, r };
    }
    static std::tuple<node_ptr_t, node_ptr_t, node_ptr_t> split(node_ptr_t node, int l, int r) {
        auto [tl, tmr] = split(node, l);
        auto [tm, tr] = split(tmr, r - l);
        return { tl, tm, tr };
    }
    static node_ptr_t merge(node_ptr_t l, node_ptr_t r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;
        node_ptr_t new_root = splay(r, 0);
        new_root->ch[0] = l;
        new_root->update();
        return new_root;
    }
    static node_ptr_t merge(node_ptr_t tl, node_ptr_t tm, node_ptr_t tr) {
        return merge(merge(tl, tm), tr);
    }
    static node_ptr_t insert(node_ptr_t node, int index, const T &val) {
        node_ptr_t new_node = new Derived(val);
        if (index == 0) {
            new_node->ch[1] = node;
            new_node->update();
            return new_node;
        } else if (index == size(node)) {
            new_node->ch[0] = node;
            new_node->update();
            return new_node;
        } else {
            auto [l, r] = split(node, index);
            new_node->ch[0] = l;
            new_node->update();
            r->ch[0] = new_node;
            r->update();
            return r;
        }
    }
    static node_ptr_t erase(node_ptr_t node, int index) {
        auto [l, r] = split(index ? node : splay(node, 0), index);
        node_ptr_t res = merge(l, r->ch[1]);
        r->ch[1] = nullptr;
        delete r;
        return res;
    }

    static void reverse_all(node_ptr_t node, bool rev = true) {
        if (node != nullptr and rev) {
            std::swap(node->ch[0], node->ch[1]);
            node->rev ^= true;
        }
    }
    static node_ptr_t reverse(node_ptr_t node, int l, int r) {
        auto [tl, tm, tr] = split(node, l, r);
        reverse_all(tm);
        return merge(tl, tm, tr);
    }
};

template <typename T>
struct DynamicSequenceNode : public DynamicSequenceNodeBase<T, DynamicSequenceNode<T>> {
    using Base = DynamicSequenceNodeBase<T, DynamicSequenceNode<T>>;
    using Base::DynamicSequenceNodeBase;
    using node_ptr_t = typename Base::node_ptr_t;
};
}

template <typename T, typename SplayNode>
struct DynamicSequenceBase {
    using node_ptr_t = typename SplayNode::node_ptr_t;
    public:
        using value_type = T;

        DynamicSequenceBase() : root(nullptr) {}
        ~DynamicSequenceBase() { delete root; }

        void insert(int k, const T& val) {
            index_bounds_check(k, size() + 1);
            root = SplayNode::insert(root, k, val);
        }
        void erase(int k) {
            index_bounds_check(k, size());
            root = SplayNode::erase(root, k);
        }
        int size() {
            return SplayNode::size(root);
        }
        void reverse(int l, int r) {
            range_bounds_check(l, r, size());
            root = SplayNode::reverse(root, l, r);
        }
        void reverse_all() {
            SplayNode::reverese_all(root);
        }
    protected:
        node_ptr_t root;

        DynamicSequenceBase(node_ptr_t root) : root(root) {}
    
        static void index_bounds_check(unsigned int k, unsigned int n) {
            assert(k < n);
        }
        static void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {
            assert(l <= r and r <= n);
        }
};

template <typename T>
struct DynamicSequence : public DynamicSequenceBase<T, internal::dynamic_sequence::DynamicSequenceNode<T>> {
    using Node = internal::dynamic_sequence::DynamicSequenceNode<T>;
    using Base = DynamicSequenceBase<T, Node>;
    using node_ptr_t = typename Node::node_ptr_t;
    public:
        using value_type = T;
        using Base::DynamicSequenceBase;

        DynamicSequence& operator=(const DynamicSequence&) = delete;
        DynamicSequence& operator=(DynamicSequence&& other) {
            delete this->root;
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }

        T& operator[](int k) {
            this->index_bounds_check(k, this->size());
            this->root = Node::splay(this->root, k);
            return this->root->val;
        }

        DynamicSequence& operator+=(DynamicSequence &&right) {
            this->root = Node::merge(this->root, right.root);
            right.root = nullptr;
            return *this;
        }
        void concat(DynamicSequence &&right) {
            *this += std::move(right);
        }
        void concat_left(DynamicSequence &&left) {
            this->root = (left += std::move(*this)).root;
            left.root = nullptr;
        }
        // erases [k, size()) and returns [k, size())
        // template <typename T = decltype(*this), constraints_t<std::is_same<typename T::Node, Node>> = nullptr>
        DynamicSequence split(int k) {
            this->index_bounds_check(k, this->size() + 1);
            auto [l, r] = Node::split(this->root, k);
            this->root = l;
            return DynamicSequence(r);
        }
};

}

#endif // SUISEN_DYNAMIC_SEQUENCE
