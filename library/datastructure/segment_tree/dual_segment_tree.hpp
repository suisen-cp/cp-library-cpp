#ifndef SUISEN_DUAL_SEGTREE
#define SUISEN_DUAL_SEGTREE

#include "library/datastructure/segment_tree/commutative_dual_segment_tree.hpp"

namespace suisen {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct DualSegmentTree : public CommutativeDualSegmentTree<T, F, mapping, composition, id> {
        using base_type = CommutativeDualSegmentTree<T, F, mapping, composition, id>;
        using base_type::base_type;
        void apply(int l, int r, const F& f) {
            push(l, r);
            base_type::apply(l, r, f);
        }
    private:
        void push(int k) {
            base_type::apply(2 * k, this->lazy[k]), base_type::apply(2 * k + 1, this->lazy[k]);
            this->lazy[k] = id();
        }
        void push(int l, int r) {
            const int log = __builtin_ctz(this->m);

            l += this->m, r += this->m;

            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l) push(l >> i);
                if (((r >> i) << i) != r) push((r - 1) >> i);
            }
        }
    };

    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    DualSegmentTree(int, T)->DualSegmentTree<T, F, mapping, composition, id>;

    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    DualSegmentTree(std::vector<T>)->DualSegmentTree<T, F, mapping, composition, id>;
} // namespace suisen


#endif // SUISEN_DUAL_SEGTREE
