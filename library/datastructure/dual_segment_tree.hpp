#ifndef SUISEN_DUAL_SEGTREE
#define SUISEN_DUAL_SEGTREE

#include <cassert>
#include <vector>
#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <
    typename T, typename F, typename Mapping, typename Composition,
    constraints_t<std::is_same<T, std::invoke_result_t<Mapping, F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr
>
class CommutativeDualSegmentTree {
    public:
        CommutativeDualSegmentTree() {}
        CommutativeDualSegmentTree(int n, const T &fill_value, const F &id, Mapping mapping, Composition composition) :
            n(n), m(ceil_pow2(n)), id(id), mapping(mapping), composition(composition), data(n, fill_value), lazy(m, id) {}
        CommutativeDualSegmentTree(std::vector<T> &&a, const F &id, Mapping mapping, Composition composition) :
            n(a.size()), m(ceil_pow2(a.size())), id(id), mapping(mapping), composition(composition), data(std::move(a)), lazy(m, id) {}
        CommutativeDualSegmentTree(const std::vector<T> &a, const F &id, Mapping mapping, Composition composition) :
            CommutativeDualSegmentTree(std::vector<T>(a), id, mapping, composition) {}

        T operator[](int i) const {
            assert(0 <= i and i < n);
            T res = data[i];
            for (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);
            return res;
        }
        T get(int i) const {
            return (*this)[i];
        }
        void apply(int l, int r, const F &f) {
            assert(0 <= l and r <= n);
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, f);
                if (r & 1) apply(--r, f);
            }
        }
    protected:
        int n, m;
        F id;
        Mapping mapping;
        Composition composition;
        std::vector<T> data;
        std::vector<F> lazy;

        void apply(int k, const F &f) {
            if (k < m) {
                lazy[k] = composition(f, lazy[k]);
            } else {
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

template <
    typename T, typename F, typename Mapping, typename Composition,
    constraints_t<std::is_same<T, std::invoke_result_t<Mapping, F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr
>
class DualSegmentTree : public CommutativeDualSegmentTree<T, F, Mapping, Composition> {
    using BaseType = CommutativeDualSegmentTree<T, F, Mapping, Composition>;
    public:
        using BaseType::CommutativeDualSegmentTree;
        void apply(int l, int r, const F &f) {
            assert(0 <= l and r <= this->n);
            for (int lk = l + this->m, rk = r + this->m, i = 1; lk >> i; ++i) {
                if (((lk >> i) << i) != lk) push(lk >> i);
                if (((rk >> i) << i) != rk) push((rk - 1) >> i);
            }
            BaseType::apply(l, r, f);
        }
    private:
        void push(int k) {
            if (this->lazy[k] != this->id) {
                BaseType::apply(2 * k, this->lazy[k]), BaseType::apply(2 * k + 1, this->lazy[k]);
                this->lazy[k] = this->id;
            }
        }
};

template <typename T, typename F, typename Mapping, typename Composition>
DualSegmentTree(int, T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;

template <typename T, typename F, typename Mapping, typename Composition>
DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;

} // namespace suisen


#endif // SUISEN_DUAL_SEGTREE
