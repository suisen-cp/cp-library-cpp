#ifndef SUISEN_PERSISTENT_COMMUTATIVE_DUAL_SEGMENT_TREE
#define SUISEN_PERSISTENT_COMMUTATIVE_DUAL_SEGMENT_TREE

#include <cassert>

#include "library/util/object_pool.hpp"

namespace suisen {
    template <typename F, F(*composition)(F, F), F(*id)()>
    struct PersistentCommutativeDualSegmentTree {
        struct Node;

        using operator_type = F;

        using node_type = Node;
        using node_pointer_type = node_type*;

        struct Node {
            static inline ObjectPool<node_type> _pool;

            node_pointer_type _ch[2]{ nullptr, nullptr };
            operator_type _laz;

            Node() : _laz(id()) {}

            static node_pointer_type clone(node_pointer_type node) {
                return &(*_pool.alloc() = *node);
            }

            static node_pointer_type build(const int n) {
                auto rec = [&](auto rec, int l, int r) -> node_pointer_type {
                    node_pointer_type res = _pool.alloc();
                    res->_laz = id();
                    if (r - l > 1) {
                        int m = (l + r) >> 1;
                        res->_ch[0] = rec(rec, l, m), res->_ch[1] = rec(rec, m, r);
                    }
                    return res;
                };
                return rec(rec, 0, n);
            }

            static node_pointer_type apply_all(node_pointer_type node, const operator_type& f) {
                if (not node) return nullptr;
                node_pointer_type res = clone(node);
                res->_laz = composition(f, res->_laz);
                return res;
            }
            static node_pointer_type apply(node_pointer_type node, int tl, int tr, int ql, int qr, const operator_type& f) {
                if (tr <= ql or qr <= tl) return node;
                if (ql <= tl and tr <= qr) return apply_all(node, f);
                node_pointer_type res = clone(node);
                int tm = (tl + tr) >> 1;
                res->_ch[0] = apply(res->_ch[0], tl, tm, ql, qr, f);
                res->_ch[1] = apply(res->_ch[1], tm, tr, ql, qr, f);
                return res;
            }

            static operator_type get(node_pointer_type node, int siz, int i) {
                operator_type f = id();
                node_pointer_type cur = node;
                for (int l = 0, r = siz; r - l > 1;) {
                    f = composition(f, cur->_laz);
                    int m = (l + r) >> 1;
                    if (i < m) {
                        cur = cur->_ch[0];
                        r = m;
                    } else {
                        cur = cur->_ch[1];
                        l = m;
                    }
                }
                return composition(f, cur->_laz);
            }
        };

        PersistentCommutativeDualSegmentTree() : _n(0), _root(nullptr) {}
        explicit PersistentCommutativeDualSegmentTree(int n) : _n(n), _root(node_type::build(n)) {}

        static void init_pool(int siz) {
            node_type::_pool = ObjectPool<node_type>(siz);
        }
        static void clear_pool() {
            node_type::_pool.clear();
        }

        PersistentCommutativeDualSegmentTree apply_all(const operator_type& f) {
            return PersistentCommutativeDualSegmentTree(_n, node_type::apply_all(_root, f));
        }
        PersistentCommutativeDualSegmentTree apply(int l, int r, const operator_type& f) {
            return PersistentCommutativeDualSegmentTree(_n, node_type::apply(_root, 0, _n, l, r, f));
        }

        operator_type get(int i) {
            assert(0 <= i and i < _n);
            return node_type::get(_root, _n, i);
        }
        operator_type operator[](int i) {
            return get(i);
        }

    private:
        int _n;
        node_pointer_type _root;
        PersistentCommutativeDualSegmentTree(int n, node_pointer_type root) : _n(n), _root(root) {}
    };
}

#endif // SUISEN_PERSISTENT_COMMUTATIVE_DUAL_SEGMENT_TREE
