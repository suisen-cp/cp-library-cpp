#ifndef SUISEN_FENWICK_TREE_SET
#define SUISEN_FENWICK_TREE_SET

#include <cassert>
#include <vector>

namespace suisen {
    struct fenwick_tree_set {
        fenwick_tree_set(): fenwick_tree_set(0) {}
        explicit fenwick_tree_set(int n, bool fullset = false): _n(n), _lg(floor_log2(_n)), _siz(fullset ? _n : 0), _d(_n + 1) {
            if (fullset) {
                for (int i = 1; i <= _n; ++i) {
                    ++_d[i];
                    if (int p = i + (-i & i); p <= _n) _d[p] += _d[i];
                }
            }
        }

        int size() const { return _siz; }

        void insert(int v) { add(v, +1); }
        void erase(int v) { add(v, -1); }

        int count_lt(int v) const {
            if (v <= 0) return 0;
            if (v >= _n) return _siz;
            int k = 0;
            for (; v; v -= -v & v) k += _d[v];
            return k;
        }
        int count_leq(int v) const { return count_lt(v + 1); }
        int count_gt(int v) const { return _siz - count_leq(v); }
        int count_geq(int v) const { return _siz - count_lt(v); }
        int count(int v) const { return count_leq(v) - count_lt(v); }

        int index_of(int v) const {
            return count_lt(v);
        }
        int kth_element(int k) const {
            int i = 1 << _lg, s = 0;
            auto check = [&] { return i <= _n and s + _d[i] <= k; };
            for (int bit = _lg - 1; bit >= 0; --bit) {
                if (check()) {
                    s += _d[i];
                    i += 1 << bit;
                } else {
                    i -= 1 << bit;
                }
            }
            return (i + check()) - 1;
        }
    private:
        int _n, _lg, _siz;
        std::vector<int> _d;

        static int floor_log2(int x) {
            int l = 0;
            while (1 << (l + 1) <= x) ++l;
            return l;
        }

        void add(int v, int k) {
            assert(0 <= v and v < _n);
            _siz += k;
            for (++v; v <= _n; v += -v & v) _d[v] += k;
        }
    };
} // namespace suisen


#endif // SUISEN_FENWICK_TREE_SET
