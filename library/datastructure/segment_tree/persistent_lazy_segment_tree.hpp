#ifndef SUISEN_PERSISTENT_LAZYSEGMENT_TREE
#define SUISEN_PERSISTENT_LAZYSEGMENT_TREE

#include <cassert>

#include "library/util/object_pool.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct PersistentLazySegmentTree {
        struct Node;

        using value_type = T;
        using operator_type = F;

        using node_type = Node;
        using node_pointer_type = node_type*;

        struct Node {
            static inline ObjectPool<node_type> _pool;

            node_pointer_type _ch[2]{ nullptr, nullptr };
            value_type _dat;
            operator_type _laz;

            Node() : _dat(e()), _laz(id()) {}

            static node_pointer_type clone(node_pointer_type node) {
                return &(*_pool.alloc() = *node);
            }

            static void update(node_pointer_type node) {
                node->_dat = op(node->_ch[0]->_dat, node->_ch[1]->_dat);
            }
            template <bool do_clone = true>
            static auto push(node_pointer_type node) {
                node_pointer_type res = node;
                if constexpr (do_clone) res = clone(res);
                res->_ch[0] = apply_all(res->_ch[0], res->_laz);
                res->_ch[1] = apply_all(res->_ch[1], res->_laz);
                res->_laz = id();
                if constexpr (do_clone) {
                    return res;
                } else {
                    return;
                }
            }

            static bool is_leaf(node_pointer_type node) {
                return not node->_ch[0];
            }

            static node_pointer_type build(const std::vector<value_type>& dat) {
                auto rec = [&](auto rec, int l, int r) -> node_pointer_type {
                    node_pointer_type res = _pool.alloc();
                    if (r - l == 1) {
                        res->_dat = dat[l];
                        res->_laz = id();
                    } else {
                        int m = (l + r) >> 1;
                        res->_ch[0] = rec(rec, l, m), res->_ch[1] = rec(rec, m, r);
                        update(res);
                        res->_laz = id();
                    }
                    return res;
                };
                return rec(rec, 0, dat.size());
            }

            static value_type prod_all(node_pointer_type node) {
                return node ? node->_dat : e();
            }
            static value_type prod(node_pointer_type node, int tl, int tr, int ql, int qr, const operator_type &f = id()) {
                if (tr <= ql or qr <= tl) return e();
                if (ql <= tl and tr <= qr) return mapping(f, node->_dat);
                int tm = (tl + tr) >> 1;
                operator_type g = composition(f, node->_laz);
                return op(prod(node->_ch[0], tl, tm, ql, qr, g), prod(node->_ch[1], tm, tr, ql, qr, g));
            }

            static node_pointer_type apply_all(node_pointer_type node, const operator_type &f) {
                if (not node) return nullptr;
                node_pointer_type res = clone(node);
                res->_dat = mapping(f, res->_dat);
                res->_laz = composition(f, res->_laz);
                return res;
            }
            static node_pointer_type apply(node_pointer_type node, int tl, int tr, int ql, int qr, const operator_type &f) {
                if (tr <= ql or qr <= tl) return node;
                if (ql <= tl and tr <= qr) return apply_all(node, f);
                node_pointer_type res = push(node);
                int tm = (tl + tr) >> 1;
                res->_ch[0] = apply(res->_ch[0], tl, tm, ql, qr, f);
                res->_ch[1] = apply(res->_ch[1], tm, tr, ql, qr, f);
                update(res);
                return res;
            }

            template <typename Func>
            static auto update_leaf(node_pointer_type node, int siz, int i, Func &&f) {
                static std::vector<node_pointer_type> path;

                node_pointer_type res = clone(node);
                node_pointer_type cur = res;

                for (int l = 0, r = siz; r - l > 1;) {
                    path.push_back(cur);
                    push</*do_clone = */false>(cur);
                    int m = (l + r) >> 1;
                    if (i < m) {
                        cur = cur->_ch[0];
                        r = m;
                    } else {
                        cur = cur->_ch[1];
                        l = m;
                    }
                }
                cur->_dat = f(cur->_dat);
                while (path.size()) update(path.back()), path.pop_back();
                return res;
            }

            static value_type get(node_pointer_type node, int siz, int i) {
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
                return mapping(f, cur->_dat);
            }
            template <typename Func>
            static node_pointer_type apply(node_pointer_type node, int siz, int i, Func&& f) {
                return update_leaf(node, siz, i, [&](const value_type &v) { return f(v); });
            }
            static node_pointer_type set(node_pointer_type node, int siz, int i, const value_type& dat) {
                return apply(node, siz, i, [&](const value_type&) { return dat; });
            }

            template <typename Pred>
            static int max_right(node_pointer_type node, int siz, int l, Pred&& pred) {
                assert(pred(e()));
                auto rec = [&](auto rec, node_pointer_type cur, int tl, int tr, value_type& sum, const operator_type &f) -> int {
                    if (tr <= l) return tr;
                    if (l <= tl) {
                        value_type nxt_sum = op(sum, mapping(f, cur->_dat));
                        if (pred(nxt_sum)) {
                            sum = std::move(nxt_sum);
                            return tr;
                        }
                        if (tr - tl == 1) return tl;
                    }
                    int tm = (tl + tr) >> 1;
                    operator_type g = composition(f, cur->_laz);
                    int res_l = rec(rec, cur->_ch[0], tl, tm, sum, g);
                    return res_l != tm ? res_l : rec(rec, cur->_ch[1], tm, tr, sum, g);
                };
                value_type sum = e();
                return rec(rec, node, 0, siz, sum, id());
            }
            template <typename Pred>
            static int min_left(node_pointer_type node, int siz, int r, Pred&& pred) {
                assert(pred(e()));
                auto rec = [&](auto rec, node_pointer_type cur, int tl, int tr, value_type& sum, const operator_type &f) -> int {
                    if (r <= tl) return tl;
                    if (tr <= r) {
                        value_type nxt_sum = op(mapping(f, cur->_dat), sum);
                        if (pred(nxt_sum)) {
                            sum = std::move(nxt_sum);
                            return tl;
                        }
                        if (tr - tl == 1) return tr;
                    }
                    int tm = (tl + tr) >> 1;
                    operator_type g = composition(f, cur->_laz);
                    int res_r = rec(rec, cur->_ch[1], tm, tr, sum, g);
                    return res_r != tm ? res_r : rec(rec, cur->_ch[0], tl, tm, sum, g);
                };
                value_type sum = e();
                return rec(rec, node, 0, siz, sum, id());
            }

            template <typename OutputIterator>
            static void dump(node_pointer_type node, OutputIterator it) {
                if (not node) return;
                auto rec = [&](auto rec, node_pointer_type cur, const operator_type &f) -> void {
                    if (is_leaf(cur)) {
                        *it++ = mapping(f, cur->_dat);
                    } else {
                        *it++ = mapping(f, cur->_dat);
                        rec(rec, cur->_ch[0], composition(cur->_laz, f)), rec(rec, cur->_ch[1], composition(cur->_laz, f));
                    }
                };
                rec(rec, node, id());
            }
            static std::vector<value_type> dump(node_pointer_type node) {
                std::vector<value_type> res;
                dump(node, std::back_inserter(res));
                return res;
            }
        };

        PersistentLazySegmentTree() : _n(0), _root(nullptr) {}
        explicit PersistentLazySegmentTree(int n) : PersistentLazySegmentTree(std::vector<value_type>(n, e())) {}
        PersistentLazySegmentTree(const std::vector<value_type>& dat) : _n(dat.size()), _root(node_type::build(dat)) {}

        static void init_pool(int siz) {
            node_type::_pool = ObjectPool<node_type>(siz);
        }
        static void clear_pool() {
            node_type::_pool.clear();
        }

        value_type prod_all() {
            return node_type::prod_all(_root);
        }
        value_type prod(int l, int r) {
            assert(0 <= l and l <= r and r <= _n);
            return node_type::prod(_root, 0, _n, l, r);
        }
        value_type operator()(int l, int r) {
            return prod(l, r);
        }

        PersistentLazySegmentTree apply_all(const operator_type &f) {
            return PersistentLazySegmentTree(_n, node_type::apply_all(_root, f));
        }
        PersistentLazySegmentTree apply(int l, int r, const operator_type &f) {
            return PersistentLazySegmentTree(_n, node_type::apply(_root, 0, _n, l, r, f));
        }

        value_type get(int i) {
            assert(0 <= i and i < _n);
            return node_type::get(_root, _n, i);
        }
        value_type operator[](int i) {
            return get(i);
        }

        template <typename Func>
        PersistentLazySegmentTree apply(int i, Func&& f) {
            assert(0 <= i and i < _n);
            return PersistentLazySegmentTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));
        }
        PersistentLazySegmentTree set(int i, const value_type& v) {
            assert(0 <= i and i < _n);
            return PersistentLazySegmentTree(_n, node_type::set(_root, _n, i, v));
        }

        template <typename Pred>
        int max_right(int l, Pred&& pred) {
            assert(0 <= l and l <= _n);
            return node_type::max_right(_root, _n, l, std::forward<Pred>(pred));
        }
        template <bool(*pred)(value_type)>
        static int max_right(int l) {
            return max_right(l, pred);
        }
        template <typename Pred>
        int min_left(int r, Pred&& pred) {
            assert(0 <= r and r <= _n);
            return node_type::min_left(_root, _n, r, std::forward<Pred>(pred));
        }
        template <bool(*pred)(value_type)>
        static int min_left(int r) {
            return min_left(r, pred);
        }

        template <typename OutputIterator>
        void dump(OutputIterator it) {
            node_type::dump(_root, it);
        }
        std::vector<value_type> dump() {
            return node_type::dump(_root);
        }

    private:
        int _n;
        node_pointer_type _root;
        PersistentLazySegmentTree(int n, node_pointer_type root) : _n(n), _root(root) {}
    };
}

#endif // SUISEN_PERSISTENT_LAZYSEGMENT_TREE
