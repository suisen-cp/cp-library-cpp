#ifndef SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM
#define SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM

#include <algorithm>
#include <limits>

#include "library/datastructure/segment_tree/segment_tree_beats.hpp"

namespace suisen {
    template <typename T>
    struct RangeChMinMaxAddRangeSum {
        friend struct DataType;
        struct DataType {
            friend struct RangeChMinMaxAddRangeSum;

            bool fail = false;

            constexpr DataType() : lo(inf), lo2(inf), hi(-inf), hi2(-inf), sum(0), siz(0), num_lo(0), num_hi(0) {}
            constexpr DataType(T x, int num = 1) : lo(x), lo2(inf), hi(x), hi2(-inf), sum(x * num), siz(num), num_lo(num), num_hi(num) {}

            T get_min() const { return lo; }
            T get_max() const { return hi; }
            T get_second_min() const { return lo2; }
            T get_second_max() const { return hi2; }
            T get_min_num() const { return num_lo; }
            T get_max_num() const { return num_hi; }
            T get_sum() const { return sum; }
        private:
            T lo, lo2, hi, hi2, sum;
            int siz, num_lo, num_hi;
        };

        explicit RangeChMinMaxAddRangeSum(const int n = 0) : RangeChMinMaxAddRangeSum(std::vector<T>(n, 0)) {}
        RangeChMinMaxAddRangeSum(const std::vector<T> &init) {
            const int n = init.size();
            std::vector<DataType> a(n);
            for (int i = 0; i < n; ++i) {
                a[i] = DataType{init[i]};
            }
            seg = SegmentTreeBeats<DataType, op, e, F, mapping, composition, id>{ a };
        }

        void chmin(int l, int r, T val) {
            seg.apply(l, r, F::chmin_query(val));
        }
        void chmax(int l, int r, T val) {
            seg.apply(l, r, F::chmax_query(val));
        }
        void update(int l, int r, T val) {
            seg.apply(l, r, F::update_query(val));
        }
        void add(int l, int r, T val) {
            seg.apply(l, r, F::add_query(val));
        }
        T max(int l, int r) {
            return seg.prod(l, r).get_max();
        }
        T min(int l, int r) {
            return seg.prod(l, r).get_min();
        }
        T sum(int l, int r) {
            return seg.prod(l, r).get_sum();
        }
        DataType prod(int l, int r) {
            return seg.prod(l, r);
        }
        template <bool(*pred)(DataType)>
        int max_right(int l) {
            return seg.max_right<pred>(l);
        }
        template <typename Pred>
        int max_right(int l, Pred &&pred) {
            return seg.max_right(l, std::forward<Pred>(pred));
        }
        template <bool(*pred)(DataType)>
        int min_left(int r) {
            return seg.min_left<pred>(r);
        }
        template <typename Pred>
        int min_left(int r, Pred &&pred) {
            return seg.min_left(r, std::forward<Pred>(pred));
        }

    private:
        static constexpr T inf = std::numeric_limits<T>::max() / 2;

        struct F {
            T lb, ub, add;
            constexpr F(T lb = -inf, T ub = inf, T add = 0) : lb(lb), ub(ub), add(add) {}
            static constexpr F chmin_query(T x) { return F { -inf, x, 0 }; }
            static constexpr F chmax_query(T x) { return F { x, inf, 0 }; }
            static constexpr F update_query(T x) { return F { x, x, 0 }; }
            static constexpr F add_query(T x) { return F { -inf, inf, x }; }
        };

        static constexpr T second_lo(T lo11, T lo12, T lo21, T lo22) {
            if (lo11 == lo21) return std::min(lo12, lo22);
            if (lo12 <= lo21) return lo12;
            if (lo22 <= lo11) return lo22;
            return std::max(lo11, lo21);
        }
        static constexpr T second_hi(T hi11, T hi12, T hi21, T hi22) {
            if (hi11 == hi21) return std::max(hi12, hi22);
            if (hi12 >= hi21) return hi12;
            if (hi22 >= hi11) return hi22;
            return std::min(hi11, hi21);
        }

        static constexpr DataType op(DataType x, DataType y) {
            DataType z{};
            z.lo = std::min(x.lo, y.lo);
            z.hi = std::max(x.hi, y.hi);
            z.lo2 = second_lo(x.lo, x.lo2, y.lo, y.lo2);
            z.hi2 = second_hi(x.hi, x.hi2, y.hi, y.hi2);
            z.sum = x.sum + y.sum;
            z.siz = x.siz + y.siz;
            z.num_lo = (z.lo == x.lo) * x.num_lo + (z.lo == y.lo) * y.num_lo;
            z.num_hi = (z.hi == x.hi) * x.num_hi + (z.hi == y.hi) * y.num_hi;
            return z;
        }
        static constexpr DataType e() {
            return DataType{};
        }
    
        static constexpr DataType mapping(F f, DataType x) {
            if (x.siz == 0) {
                return e();
            } else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub <= x.lo) {
                return DataType { std::clamp(x.lo, f.lb, f.ub) + f.add, x.siz };
            } else if (x.lo2 == x.hi) { // 2
                x.lo = x.hi2 = std::max(x.lo, f.lb) + f.add;
                x.hi = x.lo2 = std::min(x.hi, f.ub) + f.add;
                x.sum = x.lo * x.num_lo + x.hi * x.num_hi;
                return x;
            } else if (f.lb < x.lo2 and f.ub > x.hi2) { // >= 3
                T nlo = std::max(x.lo, f.lb);
                T nhi = std::min(x.hi, f.ub);
                x.sum += (nlo - x.lo) * x.num_lo + (nhi - x.hi) * x.num_hi + f.add * x.siz;
                x.lo = nlo + f.add;
                x.hi = nhi + f.add;
                x.lo2 += f.add;
                x.hi2 += f.add;
                return x;
            }
            x.fail = true;
            return x;
        }
        static constexpr F composition(F f, F g) {
            F h;
            h.lb = std::clamp(g.lb + g.add, f.lb, f.ub) - g.add;
            h.ub = std::clamp(g.ub + g.add, f.lb, f.ub) - g.add;
            h.add = f.add + g.add;
            return h;
        }
        static constexpr F id() {
            return F{};
        }
    
        SegmentTreeBeats<DataType, op, e, F, mapping, composition, id> seg;
    };
} // namespace suisen


#endif // SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM
