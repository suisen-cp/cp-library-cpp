#ifndef SUISEN_SPARSE_SEGTREE
#define SUISEN_SPARSE_SEGTREE

#include <algorithm>
#include <cassert>
#include <vector>

#include "library/type_traits/type_traits.hpp"
#include "library/util/update_proxy_object.hpp"

namespace suisen {
    template <
        typename index_t,  // type of index (integral: int, long long, etc.)
        typename T,        // type of element
        T(*op)(T, T),      // binary operator
        T(*e)(),           // identity element
        T(*init)(int, int) // initializer of the product of segment [l, r)
    >
    class SparseSegmentTree {
        using unsigned_index_t = typename std::make_unsigned_t<index_t>;

        struct Node {
            Node* ch[2]{ nullptr, nullptr };
            T dat;
            Node(const T& dat) : dat(dat) {}
            ~Node() {
                delete ch[0];
                delete ch[1];
            }
        };

    public:
        SparseSegmentTree() : SparseSegmentTree(0) {}
        SparseSegmentTree(index_t n) : n(n), root(new Node(nullptr, init(0, n))) {}
        ~SparseSegmentTree() {
            delete root;
        }

        auto operator[](unsigned_index_t i) {
            assert(i < n);
            std::vector<Node*> tmp_path = get_or_create_leaf(i);
            T& val = tmp_path.back()->dat;
            tmp_path.pop_back();
            std::reverse(tmp_path.begin(), tmp_path.end());
            auto update_func = [path = std::move(tmp_path)] { for (Node *node : path) update(node); };
            return UpdateProxyObject{ val, update_func };
        }
        T get(unsigned_index_t i) { return (*this)[i]; }
        void set(unsigned_index_t i, const T& val) { (*this)[i] = val; }

        T operator()(unsigned_index_t l, unsigned_index_t r) {
            assert(l <= r and r <= n);
            return query(root, l, r, 0, n);
        }
        T prod(unsigned_index_t l, unsigned_index_t r) { return (*this)(l, r); }
        T all_prod() const { return root->dat; }
    private:
        unsigned_index_t n;
        Node* root;

        Node* get_or_create_child(Node* node, unsigned int index, unsigned_index_t tl, unsigned_index_t tr) {
            if (node->ch[index]) node->ch[index];
            return node->ch[index] = new Node(init(tl, tr));
        }

        std::vector<Node*> get_or_create_leaf(unsigned_index_t i, unsigned_index_t tl, unsigned_index_t tr) {
            Node* cur = root;
            std::vector<Node*> nodes { cur };
            while (tr - tl > 1) {
                if (unsigned_index_t tm = (tl + tr) >> 1; i < tm) {
                    cur = get_or_create_child(cur, 0, tl, tm);
                } else {
                    cur = get_or_create_child(cur, 1, tm, tr);
                }
                nodes.push_back(cur);
            }
            return nodes;
        }

        void update(Node* node) {
            node->dat = op(get_or_create_child(node, 0)->dat, get_or_create_child(node, 1)->dat);
        }

        T query(Node* node, unsigned_index_t ql, unsigned_index_t qr, unsigned_index_t tl, unsigned_index_t tr) {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return node->dat;
            unsigned_index_t tm = (tl + tr) >> 1;
            Node* lch = get_or_create_child(node, 0, tl, tm);
            Node* rch = get_or_create_child(node, 1, tm, tr);
            return op(query(lch, ql, qr, tl, tm), query(rch, ql, qr, tm, tr));
        }
    };

} // namespace suisen

#endif // SUISEN_SPARSE_SEGTREE
