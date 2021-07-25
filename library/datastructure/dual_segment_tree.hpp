#ifndef SUISEN_DUAL_SEGTREE
#define SUISEN_DUAL_SEGTREE

#include "library/datastructure/commutative_dual_segment_tree.hpp"

namespace suisen {
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
            push(l, r);
            BaseType::apply(l, r, f);
        }
    private:
        void push(int k) {
            if (this->lazy[k] != this->id) {
                BaseType::apply(2 * k, this->lazy[k]), BaseType::apply(2 * k + 1, this->lazy[k]);
                this->lazy[k] = this->id;
            }
        }
        void push(int l, int r) {
            static const int log = __builtin_ctz(this->m);
            l += this->m, r += this->m;
            for (int i = log; (l >> i) << i != l; --i) push(l >> i);
            for (int i = log; (r >> i) << i != r; --i) push(r >> i);
        }
};

template <typename T, typename F, typename Mapping, typename Composition>
DualSegmentTree(int, T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;

template <typename T, typename F, typename Mapping, typename Composition>
DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;

} // namespace suisen


#endif // SUISEN_DUAL_SEGTREE
