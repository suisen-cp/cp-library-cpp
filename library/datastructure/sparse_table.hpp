#ifndef SUISEN_SPARSE_TABLE
#define SUISEN_SPARSE_TABLE

#include <vector>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct SparseTable {
        SparseTable() = default;
        SparseTable(std::vector<T>&& a) : n(a.size()), log(floor_log2(n)), table(log + 1), flog(n + 1, 0) {
            build_table(std::move(a));
            build_flog_table();
        }
        SparseTable(const std::vector<T>& a) : SparseTable(std::vector<T>(a)) {}
        T operator()(int l, int r) const {
            if (l >= r) return e();
            int i = flog[r - l];
            return op(table[i][l], table[i][r - (1 << i)]);
        }
        T prod(int l, int r) const {
            return (*this)(l, r);
        }
    private:
        int n;
        int log;
        std::vector<std::vector<T>> table;
        std::vector<int> flog;

        void build_table(std::vector<T>&& a) {
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
