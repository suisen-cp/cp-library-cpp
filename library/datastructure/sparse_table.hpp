#ifndef SUISEN_SPARSE_TABLE
#define SUISEN_SPARSE_TABLE

#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <typename T, typename Op, constraints_t<is_bin_op<Op, T>> = nullptr>
class SparseTable {
    public:
        SparseTable() {}
        SparseTable(std::vector<T> &&a, T e, Op op) : n(a.size()), log(floor_log2(n)), e(e), op(op), table(log + 1), flog(n + 1, 0) {
            build_table(std::move(a));
            build_flog_table();
        }
        SparseTable(const std::vector<T> &a, T e, Op op) : SparseTable(std::vector<T>(a), e, op) {}
        T operator()(int l, int r) const {
            if (l >= r) return e;
            int i = flog[r - l];
            return op(table[i][l], table[i][r - (1 << i)]);
        }
        T prod(int l, int r) const {
            return (*this)(l, r);
        }
    private:
        int n;
        int log;
        T e;
        Op op;
        std::vector<std::vector<T>> table;
        std::vector<int> flog;

        void build_table(std::vector<T> &&a) {
            table[0] = std::move(a);
            for (int i = 0; i < log; ++i) {
                int lmax = n - (1 << (i + 1));
                table[i + 1].resize(lmax + 1);
                for (int l = 0; l <= lmax; ++l) table[i + 1][l] = op(table[i][l], table[i][l + (1 << i)]);
            }
        }
        void build_flog_table() {
            for (int l = 0; l < log; ++l) {
                std::fill(flog.begin() + (1 << l), flog.begin() + (1 << (l + 1)), l);
            }
            std::fill(flog.begin() + (1 << log), flog.end(), log);
        }
        static int floor_log2(int i) {
            return 31 - __builtin_clz(i);
        }
};
} // namespace suisen

#endif // SUISEN_SPARSE_TABLE
