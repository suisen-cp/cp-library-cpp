#ifndef SUISEN_SPARSE_LAZY_SEGTREE
#define SUISEN_SPARSE_LAZY_SEGTREE

#include <cassert>
#include <vector>
#include "library/util/update_proxy_object.hpp"

namespace suisen {
    template <
        typename index_t,      // type of index (integral: int, long long, etc.)
        typename T,            // type of element
        T(*op)(T, T),          // type of binary operator on T
        T(*e)(),               //
        typename F,            // type of operator which acts on T
        T(*mapping)(F, T),     // type of action F on T
        F(*composition)(F, F), // type of binary operator on F
        F(*id)(),              //
        T(*init)(int, int)     // type of function which initializes product of segment [l, r)
    >
    class SparseLazySegmentTree {
        using unsigned_index_t = typename std::make_unsigned_t<index_t>;

        struct Node {
            Node* par;
            Node* ch[2]{ nullptr, nullptr };
            T dat;
            F laz;
            Node(Node* par, const T& dat) : par(par), dat(dat), laz(id()) {}
            ~Node() {
                delete ch[0];
                delete ch[1];
            }
        };

    public:
        SparseLazySegmentTree() : SparseLazySegmentTree(0) {}
        SparseLazySegmentTree(index_t n) : n(n), root(new Node(nullptr, init(0, n))) {}

        ~SparseLazySegmentTree() {
            delete root;
        }

        auto operator[](unsigned_index_t i) {
            assert(i < n);
            Node* leaf = get_or_create_leaf(i);
            return UpdateProxyObject{ leaf->dat, [this, leaf] { update_from(leaf); } };
        }

        T get(unsigned_index_t i) {
            return (*this)[i];
        }
        void set(unsigned_index_t i, const T& val) {
            (*this)[i] = val;
        }
        void apply(unsigned_index_t i, const F& f) {
            (*this)[i].apply([this, f](const T& dat) { return mapping(f, dat); });
        }

        T operator()(unsigned_index_t l, unsigned_index_t r) {
            assert(l <= r and r <= n);
            return query(root, l, r);
        }
        T prod(unsigned_index_t l, unsigned_index_t r) {
            return (*this)(l, r);
        }
        T prod_all() {
            return root->dat;
        }

        void apply(unsigned_index_t l, unsigned_index_t r, const F& f) {
            assert(l <= r and r <= n);
            apply(root, f, l, r, 0, n);
        }
        void apply_all(const F& f) {
            apply_all(root, f);
        }

    private:
        unsigned_index_t n;
        Node* root;

        Node* get_or_create_leaf(unsigned_index_t i) {
            Node* cur = root;
            while (cur->r - cur->l > 1) {
                push(cur);
                cur = cur->ch[i >= (cur->l + cur->r) >> 1];
            }
            return cur;
        }
        Node* get_or_create_child(Node* node, int index, unsigned_index_t tl, unsigned_index_t tr) {
            if (node->ch[index]) return node->ch[index];
            return node->ch[index] = new Node(node, init(tl, tr));
        }

        void apply_all(Node* node, const F& f) {
            node->dat = mapping(f, node->dat);
            node->laz = composition(f, node->laz);
        }
        void push(Node* node, unsigned_index_t tl, unsigned_index_t tr) {
            unsigned_index_t tm = (tl + tr) >> 1;
            apply_all(get_or_create_child(node, 0, tl, tm), node->laz);
            apply_all(get_or_create_child(node, 1, tm, tr), node->laz);
            node->laz = id();
        }

        void update(Node* node) {
            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);
        }
        void update_from(Node* leaf) {
            while (leaf->par) update(leaf = leaf->par);
        }

        T query(Node* node, unsigned_index_t ql, unsigned_index_t qr, unsigned_index_t tl, unsigned_index_t tr) {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return node->dat;
            push(node, tl, tr);
            unsigned_index_t tm = (tl + tr) >> 1;
            return op(query(node->ch[0], ql, qr, tl, tm), query(node->ch[1], ql, qr, tm, tr));
        }

        void apply(Node* node, const F& f, unsigned_index_t ql, unsigned_index_t qr, unsigned_index_t tl, unsigned_index_t tr) {
            if (tr <= ql or qr <= tl) return;
            if (ql <= tl and tr <= qr) return apply_all(node, f);
            unsigned_index_t tm = (tl + tr) >> 1;
            push(node, tl, tr);
            apply(node->ch[0], f, ql, qr, tl, tm);
            apply(node->ch[1], f, ql, qr, tm, tr);
            update(node);
        }
    };
}

#endif // SUISEN_SPARSE_LAZY_SEGTREE
