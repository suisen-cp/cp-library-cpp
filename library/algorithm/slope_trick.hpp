#ifndef SUISEN_SLOPE_TRICK
#define SUISEN_SLOPE_TRICK

#include <cassert>
#include <limits>
#include <queue>

namespace suisen {
template <typename T>
class SlopeTrick {
    using pq_dsc = std::priority_queue<T>;
    using pq_asc = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    public:
        SlopeTrick() {
            l.push(-inf), r.push(+inf);
        }
        T min() const {
            return base;
        }
        std::pair<T, T> argmin_range() const {
            return {l.top() + add_l, r.top() + add_r};
        }
        SlopeTrick& add_const(const T a) {
            base += a;
            return *this;
        }
        // $f \leftarrow f + max(0, x - a)$
        SlopeTrick& add_right(const T a) {
            if (l.top() + add_l <= a) {
                r.push(a - add_r);
            } else {
                base += (l.top() + add_l) - a;
                l.push(a - add_l), r.push(l.top() + add_l - add_r), l.pop();
            }
            return *this;
        }
        // $f \leftarrow f + max(0, a - x)$
        SlopeTrick& add_left(const T a) {
            if (r.top() + add_r >= a) {
                l.push(a - add_l);
            } else {
                base += a - (r.top() + add_r);
                r.push(a - add_r), l.push(r.top() + add_r - add_l), r.pop();
            }
            return *this;
        }
        // $f \leftarrow f + |x - a|$
        SlopeTrick& add_abs(const T a) {
            add_left(a), add_right(a);
            return *this;
        }
        SlopeTrick& cumulative_min_left() {
            r = pq_asc{}, r.push(+inf);
            return *this;
        }
        SlopeTrick& cumulative_min_right() {
            l = pq_dsc{}, l.push(-inf);
            return *this;
        }
        SlopeTrick& operator<<=(const T shamt_left) {
            add_l -= shamt_left, add_r -= shamt_left;
            return *this;
        }
        SlopeTrick& operator>>=(const T shamt_right) {
            add_l += shamt_right, add_r += shamt_right;
            return *this;
        }
        SlopeTrick& translate(const T dx) {
            return dx >= 0 ? *this >>= dx : *this <<= -dx;
        }
        SlopeTrick& sliding_window_minimum(const T a, const T b) {
            assert(a <= b);
            add_l += a, add_r += b;
            return *this;
        }
    private:
        static constexpr T inf = std::numeric_limits<T>::max() / 2;
        T base = T(0);
        pq_dsc l;
        pq_asc r;
        T add_l = T(0), add_r = T(0);
};
} // namespace suisen

#endif // SUISEN_SLOPE_TRICK