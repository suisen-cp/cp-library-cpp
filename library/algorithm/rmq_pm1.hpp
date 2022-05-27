#ifndef SUISEN_RMQ_PM1
#define SUISEN_RMQ_PM1

#include <cassert>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include "library/datastructure/sparse_table.hpp"

namespace suisen {

    template <bool is_min_query = true>
    class RMQpm1 {
        static constexpr typename std::conditional_t<is_min_query, std::less<int>, std::greater<int>> comp{};
        static constexpr int op(int x, int y) {
            return comp(x, y) ? x : y;
        }
        static constexpr int e() {
            if constexpr (is_min_query) {
                return std::numeric_limits<int>::max();
            } else {
                return std::numeric_limits<int>::min();
            }
        }

        static constexpr int LOG = 4;
        static constexpr int SIZE = 1 << LOG;

        static constexpr class S {
        public:
            int prd[1 << RMQpm1<is_min_query>::SIZE];
            constexpr S() : prd(), sum() {
                prd[is_min_query] = sum[is_min_query] = -1, prd[not is_min_query] = sum[not is_min_query] = 1;
                for (int n = 2; n <= RMQpm1<is_min_query>::SIZE; n <<= 1) {
                    for (int s = (1 << n) - 1; s >= 0; --s) merge(s, n >> 1);
                }
            }
        private:
            int sum[1 << RMQpm1<is_min_query>::SIZE];
            constexpr void merge(int s, int half) {
                int upper = s >> half, lower = s ^ (upper << half);
                prd[s] = RMQpm1<is_min_query>::op(prd[lower], sum[lower] + prd[upper]);
                sum[s] = sum[lower] + sum[upper];
            }
        } tabs{};

    public:
        RMQpm1(std::vector<int>&& x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build()) {}
        RMQpm1(const std::vector<int>& x) : RMQpm1(std::vector<int>(x)) {}

        int operator()(int l, int r) const {
            if (l >= r) return e();
            static constexpr int MASK = SIZE - 1;
            auto f = [this](int l, int r) {
                return l < r ? a[l] + tabs.prd[cut(b[l >> LOG], l & MASK, ((r - 1) & MASK) + 1)] : e();
            };
            if (l >> LOG == (r - 1) >> LOG) return f(l, r);
            int spl = (l + SIZE - 1) >> LOG, spr = r >> LOG;
            return op(op(f(l, spl << LOG), f(spr << LOG, r)), tabl(spl, spr));
        }

    private:
        int n, m;
        std::vector<int> a;
        std::vector<std::uint16_t> b;
        SparseTable<int, op, e> tabl;

        std::vector<int> build() {
            std::vector<int> c(m, e());
            for (int i = 0, p = a[0] - 1; i < n; p = a[i++]) {
                int outer = i >> LOG;
                c[outer] = op(c[outer], a[i]);
                b[outer] |= comp(a[i], p) << (i & (SIZE - 1));
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

#endif // SUISEN_RMQ_PM1
