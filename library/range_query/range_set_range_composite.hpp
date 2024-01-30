#ifndef SUISEN_RANGE_SET_RANGE_COMPOSITE
#define SUISEN_RANGE_SET_RANGE_COMPOSITE

#include "library/datastructure/fenwick_tree/fenwick_tree_set.hpp"

#include <atcoder/segtree>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct RangeSetRangeComposite {
        RangeSetRangeComposite() : RangeSetRangeComposite(0) {}
        explicit RangeSetRangeComposite(int n, T val = e()) : _n(n), _seg(std::vector(_n, e())), _vs(n, e()) {
            _pos.insert(0), _vs[0] = val;
            _seg.set(0, _pow(0, n));
            _pos.insert(_n);
        }
        explicit RangeSetRangeComposite(const std::vector<T>& a) : _n(a.size()), _seg(a), _vs(a), _pos(_n + 1, true) {}

        void set(int l, int r, const T& f) {
            assert(0 <= l and l <= r and r <= _n);
            if (l == r) return;
            if (const int ml = _pos.min_geq(l); ml != l) {
                const int pl = _pos.max_lt(ml);
                _pos.insert(l);
                _vs[l] = _vs[pl];
                _seg.set(pl, _pow(pl, l - pl));
            }
            if (const int mr = _pos.min_geq(r); mr != r) {
                const int pr = _pos.max_lt(mr);
                _pos.insert(r);
                _vs[r] = _vs[pr];
                _seg.set(r, _pow(r, mr - r));
            }
            _vs[l] = f;
            _seg.set(l, _pow(l, r - l));
            for (int i = l; (i = _pos.min_gt(i)) != r;) _pos.erase(i), _seg.set(i, e());
        }
        T prod(int l, int r) {
            assert(0 <= l and l <= r and r <= _n);
            if (l == r) return e();
            const auto ml = _pos.min_geq(l);
            if (ml >= r) return _pow(_pos.max_lt(ml), r - l);
            const int mr = _pos.max_leq(r);
            T fl = ml == l ? e() : _pow(_pos.max_lt(ml), ml - l);
            T fm = _seg.prod(ml, mr);
            T fr = mr == r ? e() : _pow(mr, r - mr);
            return op(op(fl, fm), fr);
        }
    private:
        int _n;
        atcoder::segtree<T, op, e> _seg;
        std::vector<T> _vs;
        suisen::fenwick_tree_set _pos;

        T _pow(int i, int n) const {
            T res = e();
            for (T v = _vs[i]; n; n >>= 1) {
                if (n & 1) res = op(res, v);
                v = op(v, v);
            }
            return res;
        }
    };
} // namespace suisen

#endif // SUISEN_RANGE_SET_RANGE_COMPOSITE
