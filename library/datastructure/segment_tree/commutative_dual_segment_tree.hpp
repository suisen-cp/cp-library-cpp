#ifndef SUISEN_COM_DUAL_SEGTREE
#define SUISEN_COM_DUAL_SEGTREE

#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct CommutativeDualSegmentTree {
        CommutativeDualSegmentTree() = default;
        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()), m(ceil_pow2(a.size())), data(std::move(a)), lazy(m, id()) {}
        CommutativeDualSegmentTree(const std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a)) {}
        CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n, fill_value)) {}

        T operator[](int i) const {
            assert(0 <= i and i < n);
            T res = data[i];
            for (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);
            return res;
        }
        T get(int i) const {
            return (*this)[i];
        }
        void apply(int l, int r, const F& f) {
            assert(0 <= l and r <= n);
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, f);
                if (r & 1) apply(--r, f);
            }
        }
    protected:
        int n, m;
        std::vector<T> data;
        std::vector<F> lazy;

        void apply(int k, const F& f) {
            if (k < m) {
                lazy[k] = composition(f, lazy[k]);
            } else if (k - m < n) {
                data[k - m] = mapping(f, data[k - m]);
            }
        }
    private:
        static int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }
    };
} // namespace suisen

#endif // SUISEN_COM_DUAL_SEGTREE
