#ifndef SUISEN_SPARSE_LAZY_SEGTREE
#define SUISEN_SPARSE_LAZY_SEGTREE

#include <cassert>
#include <vector>
#include "library/util/update_proxy_object.hpp"

namespace suisen {
template <
    typename index_t,               // type of index (integral: int, long long, etc.)
    typename T,                     // type of element
    typename OpTT,                  // type of binary operator on T
    typename F,                     // type of operator which acts on T
    typename OpFT,                  // type of action F on T
    typename OpFF,                  // type of binary operator on F
    typename ProductInitializer,    // type of function which initializes product of segment [l, r)
    constraints_t<
        std::is_integral<index_t>,                                          // index_t is integral
        is_bin_op<OpTT, T>,                                                 // OpTT is (T, T) -> T
        is_same_as_invoke_result<T, OpFT, F, T>,                            // OpFT is (F, T) -> T
        is_bin_op<OpFF, F>,                                                 // OpFF is (F, F) -> F
        is_same_as_invoke_result<T, ProductInitializer, index_t, index_t>   // ProductInitializer is (index_t, index_t) -> T
    > = nullptr
>
class SparseLazySegmentTree {
    using unsigned_index_t = typename std::make_unsigned_t<index_t>;

    struct Node {
        Node *par;
        Node *ch[2] { nullptr, nullptr };
        unsigned_index_t l, r;
        T dat;
        F laz;
        Node(Node *par, unsigned_index_t l, unsigned_index_t r, const T &dat, const F &laz) : par(par), l(l), r(r), dat(dat), laz(laz) {}
        ~Node() {
            delete ch[0];
            delete ch[1];
        }
    };

    public:
        SparseLazySegmentTree() : SparseLazySegmentTree(0, T{}, OpTT{}, F{}, OpFT{}, OpFF{}, ProductInitializer{}) {}
        /**
         * 1. number of element
         * 2. id of ･. ∀x:T, x･e=e･x=x .
         * 3. (x,y) -> x･y
         * 4. id of ◦. ∀f:F, f◦id=id◦f=f, ∀x:T, id(x)=x.
         * 5. (f,x) -> f(x). ∀x,y:T, ∀f,g:F, f(x)･g(y)=(f◦g)(x･y).
         * 6. (f,g) -> f◦g
         * 7. (l,r) -> initial product of segment [l,r).
         */
        SparseLazySegmentTree(index_t n, T e, OpTT op, F id, OpFT mapping, OpFF composition, ProductInitializer init) : n(n), e(e), op(op), id(id), mapping(mapping), composition(composition), init(init), root(new Node(nullptr, 0, n, init(0, n), id)) {}

        ~SparseLazySegmentTree() {
            delete root;
        }

        auto operator[](unsigned_index_t i) {
            assert(i < n);
            Node* leaf = get_or_create_leaf(i);
            return UpdateProxyObject { leaf->dat, [this, leaf]{ update_from(leaf); } };
        }

        T get(unsigned_index_t i) {
            return (*this)[i];
        }
        void set(unsigned_index_t i, const T& val) {
            (*this)[i] = val;
        }
        void apply(unsigned_index_t i, const F &f) {
            (*this)[i].apply([this, f](const T &dat) { return mapping(f, dat); });
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

        void apply(unsigned_index_t l, unsigned_index_t r, const F &f) {
            assert(l <= r and r <= n);
            apply(root, l, r, f);
        }
        void apply_all(const F &f) {
            apply_all(root, f);
        }

    private:
        unsigned_index_t n;
        T e;
        OpTT op;
        F id;
        OpFT mapping;
        OpFF composition;
        ProductInitializer init;
        Node* root;

        Node* get_or_create_leaf(unsigned_index_t i) {
            Node *cur = root;
            while (cur->r - cur->l > 1) {
                push(cur);
                cur = cur->ch[i >= (cur->l + cur->r) >> 1];
            }
            return cur;
        }
        Node* get_or_create_child(Node* node, int index) {
            if (not node->ch[index]) {
                unsigned_index_t l = node->l, r = node->r, m = (l + r) >> 1;
                unsigned_index_t cl = index ? m : l;
                unsigned_index_t cr = index ? r : m;
                node->ch[index] = new Node(node, cl, cr, init(cl, cr), id);
            }
            return node->ch[index];
        }
    
        void apply_all(Node* node, const F &f) {
            node->dat = mapping(f, node->dat);
            node->laz = composition(f, node->laz);
        }
        void push(Node* node) {
            apply_all(get_or_create_child(node, 0), node->laz);
            apply_all(get_or_create_child(node, 1), node->laz);
            node->laz = id;
        }

        void update(Node* node) {
            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);
        }
        void update_from(Node* leaf) {
            while (leaf->par) update(leaf = leaf->par);
        }

        T query(Node *node, unsigned_index_t ql, unsigned_index_t qr) {
            unsigned_index_t tl = node->l, tr = node->r;
            if (tr <= ql or qr <= tl) return e;
            if (ql <= tl and tr <= qr) return node->dat;
            push(node);
            return op(query(node->ch[0], ql, qr), query(node->ch[1], ql, qr));
        }

        void apply(Node *node, unsigned_index_t ql, unsigned_index_t qr, const F &f) {
            unsigned_index_t tl = node->l, tr = node->r;
            if (tr <= ql or qr <= tl) return;
            if (ql <= tl and tr <= qr) return apply_all(node, f);
            push(node);
            apply(node->ch[0], ql, qr, f);
            apply(node->ch[1], ql, qr, f);
            update(node);
        }
};

}

#endif // SUISEN_SPARSE_LAZY_SEGTREE
