#ifndef SUISEN_FENWICK_TREE_PREFIX
#define SUISEN_FENWICK_TREE_PREFIX

#include <vector>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct FenwickTreePrefix {
        FenwickTreePrefix() : FenwickTreePrefix(0) {}
        explicit FenwickTreePrefix(int n) : _n(n), _dat(_n + 1, e()) {}
        FenwickTreePrefix(const std::vector<T> &dat) : _n(dat.size()), _dat(_n + 1, e()) {
            for (int i = _n; i > 0; --i) {
                _dat[i] = op(_dat[i], dat[i - 1]);
                if (int p = i + (-i & i); p <= _n) _dat[p] = op(_dat[p], _dat[i]);
            }
        }
        void apply(int i, const T& val) {
            for (++i; i <= _n; i += -i & i) _dat[i] = op(_dat[i], val);
        }
        T prefix_query(int r) const {
            T res = e();
            for (; r; r -= -r & r) res = op(res, _dat[r]);
            return res;
        }
    private:
        int _n;
        std::vector<T> _dat;
    };
} // namespace suisen


#endif // SUISEN_FENWICK_TREE_PREFIX
