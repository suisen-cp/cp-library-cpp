#ifndef SUISEN_SPARSE_SEGTREE
#define SUISEN_SPARSE_SEGTREE

#include <cassert>
#include <vector>

#include "library/type_traits/type_traits.hpp"
#include "library/util/update_proxy_object.hpp"

namespace suisen {
template <
    typename index_t,               // type of index (integral: int, long long, etc.)
    typename T,                     // type of element
    typename OpTT,                  // type of binary operator on T
    typename ProductInitializer,    // type of function which initializes product of segment [l, r)
    constraints_t<
        std::is_integral<index_t>,                                          // index_t is integral
        is_bin_op<OpTT, T>,                                                 // OpTT is (T, T) -> T
        is_same_as_invoke_result<T, ProductInitializer, index_t, index_t>   // ProductInitializer is (index_t, index_t) -> T
    > = nullptr
>
class SparseSegmentTree {
    using unsigned_index_t = typename std::make_unsigned_t<index_t>;

    struct Node {
        Node *par;
        Node *ch[2] { nullptr, nullptr };
        unsigned_index_t l, r;
        T dat;
        Node(Node *par, unsigned_index_t l, unsigned_index_t r, const T &dat) : par(par), l(l), r(r), dat(dat) {}
        ~Node() {
            delete ch[0];
            delete ch[1];
        }
    };

    public:
        SparseSegmentTree() : SparseSegmentTree(0, T{}, OpTT{}, ProductInitializer{}) {}
        /**
         * 1. number of element
         * 2. id of ･. ∀x:T, x･e=e･x=x .
         * 3. (x,y) -> x･y
         * 4. (l,r) -> initial product of segment [l,r).
         */
        SparseSegmentTree(index_t n, const T &e, const OpTT &op, ProductInitializer init) : n(n), e(e), op(op), init(init), root(new Node(nullptr, 0, n, init(0, n))) {}

        ~SparseSegmentTree() {
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
        void set(unsigned_index_t i, T val) {
            (*this)[i] = val;
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

    private:
        unsigned_index_t n;
        T e;
        OpTT op;
        ProductInitializer init;
        Node* root;

        Node* get_or_create_child(Node* node, unsigned int index) {
            if (not node->ch[index]) {
                unsigned_index_t l = node->l, r = node->r, m = (l + r) >> 1;
                unsigned_index_t cl = index ? m : l;
                unsigned_index_t cr = index ? r : m;
                node->ch[index] = new Node(node, cl, cr, init(cl, cr));
            }
            return node->ch[index];
        }

        Node* get_or_create_leaf(unsigned_index_t i) {
            Node* cur = root;
            while (cur->r - cur->l > 1) cur = get_or_create_child(cur, i >= (cur->l + cur->r) >> 1);
            return cur;
        }

        void update(Node* node) {
            node->dat = op(get_or_create_child(node, 0)->dat, get_or_create_child(node, 1)->dat);
        }
        void update_from(Node* leaf) {
            while (leaf->par) update(leaf = leaf->par);
        }

        T query(Node* node, unsigned_index_t ql, unsigned_index_t qr) {
            unsigned_index_t tl = node->l, tr = node->r;
            if (tr <= ql or qr <= tl) return e;
            if (ql <= tl and tr <= qr) return node->dat;
            return op(query(get_or_create_child(node, 0), ql, qr), query(get_or_create_child(node, 1), ql, qr));
        }
};

} // namespace suisen

#endif // SUISEN_SPARSE_SEGTREE
