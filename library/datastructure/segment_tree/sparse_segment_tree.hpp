#ifndef SUISEN_SPARSE_SEGTREE
#define SUISEN_SPARSE_SEGTREE

#include <cassert>
#include <vector>

namespace suisen {
    template <
        typename IndexType,            // type of index (integral: bool, long long, etc.)
        typename T,                    // type of element
        T(*op)(T, T),                  // type of binary operator on T
        T(*e)(),                       //
        T(*init)(IndexType, IndexType) // type of function which initializes product of segment [l, r)
    >
    struct SparseSegmentTree {
        using index_type = IndexType;
        using value_type = T;
    private:
        using pool_index_type = uint32_t;

        struct Node {
            pool_index_type ch[2]{ 0, 0 };
            value_type dat;
            Node(const value_type& dat) : dat(dat) {}
        };

        static inline std::vector<Node> pool{ Node{ e() } };

        static pool_index_type new_node(const value_type& dat) {
            const pool_index_type res = pool.size();
            return pool.emplace_back(dat), res;
        }
    public:
        SparseSegmentTree() : SparseSegmentTree(0) {}
        explicit SparseSegmentTree(IndexType n) : n(n), root(new_node(init(0, n))) {}

        static void reserve(int siz) {
            pool.reserve(siz);
        }

        value_type get(index_type i) const {
            assert(0 <= i and i < n);
            pool_index_type cur = root;
            for (index_type l = 0, r = n; cur and r - l > 1;) {
                index_type m = (lr[0] + lr[1]) >> 1;
                if (i < m) cur = pool[cur].ch[0], r = m;
                else       cur = pool[cur].ch[1], l = m;
            }
            return cur ? pool[cur].dat : init(i, i + 1);
        }
        template <typename Fun>
        void apply_fun(index_type i, Fun &&fun) {
            assert(0 <= i and i < n);
            static std::vector<pool_index_type> path;
            pool_index_type cur = root;
            for (index_type l = 0, r = n; r - l > 1;) {
                path.push_back(cur);
                index_type m = (lr[0] + lr[1]) >> 1;
                if (i < m) cur = get_or_create_child(cur, 0, l, m), r = m;
                else       cur = get_or_create_child(cur, 1, m, r), l = m;
            }
            pool[cur].dat = fun(pool[cur].dat);
            while (path.size()) update(path.back()), path.pop_back();
        }
        void set(index_type i, const value_type& val) {
            apply_fun(i, [&val](const value_type&) { return val; });
        }

        value_type operator()(index_type l, index_type r) const {
            assert(0 <= l and l <= r and r <= n);
            return query(root, l, r, 0, n);
        }
        value_type prod(index_type l, index_type r) const {
            return (*this)(l, r);
        }
        value_type prod_all() const {
            return pool[root].dat;
        }

    private:
        index_type n;
        pool_index_type root;

        pool_index_type get_or_create_child(pool_index_type node, int index, index_type tl, index_type tr) {
            if (pool[node].ch[index]) return pool[node].ch[index];
            const pool_index_type ch = new_node(init(tl, tr));
            return pool[node].ch[index] = ch;
        }

        void update(pool_index_type node) {
            pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];
            pool[node].dat = op(pool[lch].dat, pool[rch].dat);
        }

        value_type query(pool_index_type node, index_type ql, index_type qr, index_type tl, index_type tr) const {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return pool[node].dat;
            const index_type tm = (tl + tr) >> 1;
            return op(query(pool[node].ch[0], ql, qr, tl, tm), query(pool[node].ch[1], ql, qr, tm, tr));
        }
    };
}

#endif // SUISEN_SPARSE_SEGTREE
