#ifndef SUISEN_LAZY_SEGMENT_TREE
#define SUISEN_LAZY_SEGMENT_TREE

#include <cassert>
#include <vector>
#include "library/util/update_proxy_object.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)(), bool enable_beats = false>
    struct LazySegmentTree {
        using value_type = T;
        using operator_type = F;

        LazySegmentTree() : LazySegmentTree(0) {}
        LazySegmentTree(int n) : LazySegmentTree(std::vector<value_type>(n, e())) {}
        LazySegmentTree(const std::vector<value_type>& init) : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)), data(2 * m, e()), lazy(m, id()) {
            std::copy(init.begin(), init.end(), data.begin() + m);
            for (int k = m - 1; k > 0; --k) update(k);
        }

        void apply(int l, int r, const operator_type& f) {
            assert(0 <= l and l <= r and r <= n);
            push_to(l, r);
            for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {
                if (l2 & 1) all_apply(l2++, f);
                if (r2 & 1) all_apply(--r2, f);
            }
            update_from(l, r);
        }
        void apply(int p, const operator_type& f) {
            (*this)[p] = mapping(f, get(p));
        }

        value_type operator()(int l, int r) {
            assert(0 <= l and l <= r and r <= n);
            push_to(l, r);
            value_type res_l = e(), res_r = e();
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res_l = op(res_l, data[l++]);
                if (r & 1) res_r = op(data[--r], res_r);
            }
            return op(res_l, res_r);
        }

        value_type prod(int l, int r) { return (*this)(l, r); }
        value_type prefix_prod(int r) { return (*this)(0, r); }
        value_type suffix_prod(int l) { return (*this)(l, m); }
        value_type all_prod() const { return data[1]; }

        auto operator[](int p) {
            assert(0 <= p and p < n);
            push_to(p);
            return UpdateProxyObject{ data[p + m], [this, p] { update_from(p); } };
        }
        value_type get(int p) { return (*this)[p]; }
        void set(int p, value_type v) { (*this)[p] = v; }

        template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred, value_type>> = nullptr>
        int max_right(int l, Pred g) {
            assert(0 <= l && l <= n);
            assert(g(e()));
            if (l == n) return n;
            l += m;
            for (int i = lg; i >= 1; --i) push(l >> i);
            value_type sum = e();
            do {
                while ((l & 1) == 0) l >>= 1;
                if (not g(op(sum, data[l]))) {
                    while (l < m) {
                        push(l);
                        l = 2 * l;
                        if (g(op(sum, data[l]))) sum = op(sum, data[l++]);
                    }
                    return l - m;
                }
                sum = op(sum, data[l++]);
            } while ((l & -l) != l);
            return n;
        }
        template <bool(*f)(value_type)>
        int max_right(int l) { return max_right(l, f); }

        template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred, value_type>> = nullptr>
        int min_left(int r, Pred g) {
            assert(0 <= r && r <= n);
            assert(g(e()));
            if (r == 0) return 0;
            r += m;
            for (int i = lg; i >= 1; --i) push(r >> i);
            value_type sum = e();
            do {
                r--;
                while (r > 1 and (r & 1)) r >>= 1;
                if (not g(op(data[r], sum))) {
                    while (r < m) {
                        push(r);
                        r = 2 * r + 1;
                        if (g(op(data[r], sum))) sum = op(data[r--], sum);
                    }
                    return r + 1 - m;
                }
                sum = op(data[r], sum);
            } while ((r & -r) != r);
            return 0;
        }
        template <bool(*f)(value_type)>
        int min_left(int l) { return min_left(l, f); }
    private:
        int n, m, lg;
        std::vector<value_type> data;
        std::vector<operator_type> lazy;

        static constexpr int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }

        void all_apply(int k, const operator_type& f) {
            data[k] = mapping(f, data[k]);
            if (k < m) {
                lazy[k] = composition(f, lazy[k]);
                if constexpr (enable_beats) if (data[k].fail) push(k), update(k);
            }
        }
        void push(int k) {
            all_apply(2 * k, lazy[k]), all_apply(2 * k + 1, lazy[k]);
            lazy[k] = id();
        }
        void push_to(int p) {
            p += m;
            for (int i = lg; i >= 1; --i) push(p >> i);
        }
        void push_to(int l, int r) {
            l += m, r += m;
            int li = __builtin_ctz(l), ri = __builtin_ctz(r);
            for (int i = lg; i >= li + 1; --i) push(l >> i);
            for (int i = lg; i >= ri + 1; --i) push(r >> i);
        }
        void update(int k) {
            data[k] = op(data[2 * k], data[2 * k + 1]);
        }
        void update_from(int p) {
            p += m;
            for (int i = 1; i <= lg; ++i) update(p >> i);
        }
        void update_from(int l, int r) {
            l += m, r += m;
            int li = __builtin_ctz(l), ri = __builtin_ctz(r);
            for (int i = li + 1; i <= lg; ++i) update(l >> i);
            for (int i = ri + 1; i <= lg; ++i) update(r >> i);
        }
    };
}

#endif // SUISEN_LAZY_SEGMENT_TREE
