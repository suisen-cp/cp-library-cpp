#ifndef SUISEN_SPARSE_LAZY_SEGTREE
#define SUISEN_SPARSE_LAZY_SEGTREE

#include <array>
#include <cassert>
#include <vector>

namespace suisen {
    template <
        typename IndexType,                      // type of index (integral: bool, long long, etc.)
        typename T,                              // type of element
        T(*op)(T, T),                            // type of binary operator on T
        T(*e)(),                                 //
        typename F,                              // type of operator which acts on T
        T(*mapping)(F, T, IndexType, IndexType), // type of action F on T
        F(*composition)(F, F),                   // type of binary operator on F
        F(*id)(),                                //
        T(*init)(IndexType, IndexType)           // type of function which initializes product of segment [l, r)
    >
    struct SparseLazySegmentTree {
        using index_type = IndexType;
        using value_type = T;
        using operator_type = F;
    private:
        using pool_index_type = uint32_t;

        struct Node {
            pool_index_type ch[2]{ 0, 0 };
            value_type dat;
            operator_type laz;
            Node(const value_type& dat) : dat(dat), laz(id()) {}
        };

        static inline std::vector<Node> pool{ Node{ e() } };

        static pool_index_type new_node(const value_type& dat) {
            const pool_index_type res = pool.size();
            return pool.emplace_back(dat), res;
        }
    public:
        SparseLazySegmentTree() : SparseLazySegmentTree(0) {}
        explicit SparseLazySegmentTree(IndexType n) : n(n), root(new_node(init(0, n))) {}

        static void reserve(int siz) {
            pool.reserve(siz);
        }

        value_type get(index_type i) const {
            assert(0 <= i and i < n);
            operator_type f = id();
            pool_index_type cur = root;
            for (std::array<index_type, 2> lr { 0, n }; cur and lr[1] - lr[0] > 1;) {
                index_type m = (lr[0] + lr[1]) >> 1;
                bool b = i >= m;
                f = composition(f, pool[cur].laz);
                cur = pool[cur].ch[b], lr[not b] = m;
            }
            return mapping(f, cur ? pool[cur].dat : init(i, i + 1), i, i + 1);
        }
        template <typename Fun>
        void apply_fun(index_type i, Fun &&fun) {
            assert(0 <= i and i < n);
            static std::vector<pool_index_type> path;
            pool_index_type cur = root;
            for (std::array<index_type, 2> lr { 0, n }; lr[1] - lr[0] > 1;) {
                path.push_back(cur);
                index_type m = (lr[0] + lr[1]) >> 1;
                bool b = i >= m;
                push(cur);
                cur = pool[cur].ch[b], lr[not b] = m;
            }
            pool[cur].dat = fun(pool[cur].dat);
            while (path.size()) update(path.back()), path.pop_back();
        }
        void set(index_type i, const value_type& val) {
            apply_fun(i, [&val](const value_type&) { return val; });
        }
        void apply(index_type i, const operator_type& f) {
            apply_fun(i, [&f, i](const value_type& val) { return mapping(f, val, i, i + 1); });
        }

        value_type operator()(index_type l, index_type r) {
            assert(0 <= l and l <= r and r <= n);
            return query(root, l, r, 0, n);
        }
        value_type prod(index_type l, index_type r) {
            return (*this)(l, r);
        }
        value_type prod_all() {
            return pool[root].dat;
        }

        void apply(index_type l, index_type r, const operator_type& f) {
            assert(0 <= l and l <= r and r <= n);
            apply(root, f, l, r, 0, n);
        }
        void apply_all(const operator_type& f) {
            apply_all(root, f, 0, n);
        }

    private:
        index_type n;
        pool_index_type root;

        pool_index_type get_or_create_child(pool_index_type node, int index, index_type tl, index_type tr) {
            if (pool[node].ch[index]) return pool[node].ch[index];
            const pool_index_type ch = new_node(init(tl, tr));
            return pool[node].ch[index] = ch;
        }

        void apply_all(pool_index_type node, const operator_type& f, index_type tl, index_type tr) {
            pool[node].dat = mapping(f, pool[node].dat, tl, tr);
            pool[node].laz = composition(f, pool[node].laz);
        }
        void push(pool_index_type node, index_type tl, index_type tr) {
            const index_type tm = (tl + tr) >> 1;
            const operator_type laz = pool[node].laz;
            apply_all(get_or_create_child(node, 0, tl, tm), laz, tl, tm);
            apply_all(get_or_create_child(node, 1, tm, tr), laz, tm, tr);
            pool[node].laz = id();
        }

        void update(pool_index_type node) {
            pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];
            pool[node].dat = op(pool[lch].dat, pool[rch].dat);
        }

        value_type query(pool_index_type node, index_type ql, index_type qr, index_type tl, index_type tr) {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return pool[node].dat;
            push(node, tl, tr);
            const index_type tm = (tl + tr) >> 1;
            return op(query(pool[node].ch[0], ql, qr, tl, tm), query(pool[node].ch[1], ql, qr, tm, tr));
        }

        void apply(pool_index_type node, const operator_type& f, index_type ql, index_type qr, index_type tl, index_type tr) {
            if (tr <= ql or qr <= tl) return;
            if (ql <= tl and tr <= qr) return apply_all(node, f, tl, tr);
            const index_type tm = (tl + tr) >> 1;
            push(node, tl, tr);
            apply(pool[node].ch[0], f, ql, qr, tl, tm), apply(pool[node].ch[1], f, ql, qr, tm, tr);
            update(node);
        }
    };
}

#endif // SUISEN_SPARSE_LAZY_SEGTREE
