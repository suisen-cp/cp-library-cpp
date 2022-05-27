#ifndef SUISEN_RMQ_PM1_INDEX
#define SUISEN_RMQ_PM1_INDEX

#include <cassert>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include "library/datastructure/sparse_table.hpp"

namespace suisen {

    template <bool is_min_query = true>
    class RMQpm1WithIndex {
        static constexpr typename std::conditional_t<is_min_query, std::less<std::pair<int, int>>, std::greater<std::pair<int, int>>> comp{};
        static constexpr typename std::conditional_t<is_min_query, std::less<int>, std::greater<int>> comp_val{};

        static constexpr std::pair<int, int> op(std::pair<int, int> x, std::pair<int, int> y) {
            return comp(x, y) ? x : y;
        }
        static constexpr std::pair<int, int> e() {
            if constexpr (is_min_query) {
                return { std::numeric_limits<int>::max(), -1 };
            } else {
                return { std::numeric_limits<int>::min(), -1 };
            }
        }

        static constexpr int LOG = 4;
        static constexpr int SIZE = 1 << LOG;

        static constexpr class S {
        public:
            int prd[1 << RMQpm1WithIndex<is_min_query>::SIZE];
            int arg[1 << RMQpm1WithIndex<is_min_query>::SIZE];
            constexpr S() : prd(), arg(), sum() {
                prd[is_min_query] = sum[is_min_query] = -1, prd[not is_min_query] = sum[not is_min_query] = 1;
                arg[is_min_query] = arg[not is_min_query] = 0;
                for (int n = 2; n <= RMQpm1WithIndex<is_min_query>::SIZE; n <<= 1) {
                    for (int s = (1 << n) - 1; s >= 0; --s) merge(s, n >> 1);
                }
            }
        private:
            int sum[1 << RMQpm1WithIndex<is_min_query>::SIZE];
            constexpr void merge(int s, int half) {
                int upper = s >> half, lower = s ^ (upper << half);
                if (RMQpm1WithIndex<is_min_query>::comp_val(prd[lower], sum[lower] + prd[upper])) {
                    prd[s] = prd[lower];
                    arg[s] = arg[lower];
                } else {
                    prd[s] = sum[lower] + prd[upper];
                    arg[s] = half + arg[upper];
                }
                sum[s] = sum[lower] + sum[upper];
            }
        } tabs{};

    public:
        RMQpm1WithIndex(std::vector<int>&& x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build()) {}
        RMQpm1WithIndex(const std::vector<int>& x) : RMQpm1WithIndex(std::vector<int>(x)) {}

        std::pair<int, int> operator()(int l, int r) const {
            if (l >= r) return e();
            static constexpr int MASK = SIZE - 1;
            auto f = [this](int l, int r) -> std::pair<int, int> {
                if (l >= r) return e();
                int idx = cut(b[l >> LOG], l & MASK, ((r - 1) & MASK) + 1);
                return { a[l] + tabs.prd[idx], l + tabs.arg[idx] };
            };
            if (l >> LOG == (r - 1) >> LOG) return f(l, r);
            int spl = (l + SIZE - 1) >> LOG, spr = r >> LOG;
            return op(op(f(l, spl << LOG), f(spr << LOG, r)), tabl(spl, spr));
        }

    private:
        int n, m;
        std::vector<int> a;
        std::vector<std::uint16_t> b;
        SparseTable<std::pair<int, int>, op, e> tabl;

        std::vector<std::pair<int, int>> build() {
            std::vector<std::pair<int, int>> c(m, e());
            if (n == 0) return c;
            std::pair<int, int> p{ a[0] - 1, -1 };
            for (int i = 0; i < n; p = { a[i], i }, ++i) {
                std::pair<int, int> q{ a[i], i };
                int outer = i >> LOG;
                c[outer] = op(c[outer], q);
                b[outer] |= comp(q, p) << (i & (SIZE - 1));
            }
            a.insert(a.begin(), a[0] - 1);
            assert(std::adjacent_find(a.begin(), a.end(), [](int x, int y) { return std::abs(x - y) != 1; }) == a.end());
            return c;
        }

        static constexpr std::uint16_t cut(const std::uint16_t bits, const int l, const int r) {
            return std::uint16_t(bits << (SIZE - r)) >> (SIZE - r + l);
        }
    };
} // namespace suisen

#endif // SUISEN_RMQ_PM1_INDEX
