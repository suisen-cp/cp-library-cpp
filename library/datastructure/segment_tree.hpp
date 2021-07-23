#ifndef SUISEN_SEGMENT_TREE
#define SUISEN_SEGMENT_TREE

#include <cassert>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <typename T, typename F, constraints_t<is_bin_op<F, T>> = nullptr>
class SegmentTree {
    public:
        SegmentTree() : n(0), m(0), e(), op() {}
        SegmentTree(int n, const T &e, const F &op) : n(n), m(ceil_pow2(n)), data(m * 2, e), e(e), op(op) {}
        SegmentTree(const std::vector<T> &a, const T &e, const F &op) : SegmentTree(a.size(), e, op) {
            build(a);
        }
        void build(const std::vector<T> &a) {
            assert(int(a.size()) <= m);
            std::copy(a.begin(), a.end(), data.begin() + m);
            for (int k = m - 1; k > 0; --k) update(k);
        }
        inline T get(int i) const {
            assert(0 <= i and i < n);
            return data[i + m];
        }
        T operator()(int l, int r) const {
            T res_l = e, res_r = e;
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res_l = op(res_l, data[l++]);
                if (r & 1) res_r = op(data[--r], res_r);
            }
            return op(res_l, res_r);
        }
        inline T prefix_prod(int r) const {
            assert(0 <= r and r <= n);
            return (*this)(0, r);
        }
        inline T suffix_prod(int l) const {
            assert(0 <= l and l <= n);
            return (*this)(l, m);
        }
        inline T all_prod() const {
            return data[1];
        }

        inline void set(int i, const T &val) {
            assert(0 <= i and i < n);
            int k = i + m;
            data[k] = val, propagate(k);
        }
        inline auto operator[](int i) {
            assert(0 <= i and i < n);
            struct {
                const int k;
                SegmentTree &seg;
                inline operator T() const { return seg.data[k]; }
                inline auto& operator++() { ++seg.data[k], seg.propagate(k); return *this; }
                inline auto& operator--() { --seg.data[k], seg.propagate(k); return *this; }
                inline auto& operator+=(const T &val) { seg.data[k] += val, seg.propagate(k); return *this; }
                inline auto& operator-=(const T &val) { seg.data[k] -= val, seg.propagate(k); return *this; }
                inline auto& operator*=(const T &val) { seg.data[k] *= val, seg.propagate(k); return *this; }
                inline auto& operator/=(const T &val) { seg.data[k] /= val, seg.propagate(k); return *this; }
                inline auto& operator%=(const T &val) { seg.data[k] %= val, seg.propagate(k); return *this; }
                inline auto& operator =(const T &val) { seg.data[k]  = val, seg.propagate(k); return *this; }
            } obj {i + m, *this};
            return obj;
        }

        template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred, T>> = nullptr>
        int max_right(int l, const Pred &f) const {
            assert(0 <= l and l <= n);
            assert(f(e));
            if (l == n) return n;
            l += m;
            T sum_l = e;
            do {
                while (l % 2 == 0) l >>= 1;
                if (not f(op(sum_l, data[l]))) {
                    while (l < m) {
                        l = 2 * l;
                        if (f(op(sum_l, data[l]))) sum_l = op(sum_l, data[l++]);
                    }
                    return l - m;
                }
                sum_l = op(sum_l, data[l]);
                l++;
            } while ((l & -l) != l);
            return n;
        }

        template <typename Pred, constraints_t<is_same_as_invoke_result<bool, Pred, T>> = nullptr>
        int min_left(int r, const Pred &f) const {
            assert(0 <= r && r <= n);
            assert(f(e));
            if (r == 0) return 0;
            r += m;
            T sum_r = e;
            do {
                r--;
                while (r > 1 && (r % 2)) r >>= 1;
                if (not f(op(data[r], sum_r))) {
                    while (r < m) {
                        r = 2 * r + 1;
                        if (f(op(data[r], sum_r))) sum_r = op(data[r--], sum_r);
                    }
                    return r + 1 - m;
                }
                sum_r = op(data[r], sum_r);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        const int n, m;
        std::vector<T> data;
        const T e;
        const F op;

        static constexpr int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }
        inline void propagate(int k) {
            for (k >>= 1; k; k >>= 1) update(k);
        }
        inline void update(int k) {
            data[k] = op(data[k * 2], data[k * 2 + 1]);
        }
};
} // namespace suisen


#endif // SUISEN_SEGMENT_TREE
