#ifndef SUISEN_LI_CHAO_SEGTREE
#define SUISEN_LI_CHAO_SEGTREE

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace suisen {

template <typename T, bool is_min_query = true>
class LiChaoSegmentTree {
    struct Line {
        static constexpr Line e { T(0), std::numeric_limits<T>::max() };
        T a, b;
        bool operator==(const Line &other) const {
            return a == other.a and b == other.b;
        }
        T operator()(T x) const {
            return *this == e ? std::numeric_limits<T>::max() : a * x + b;
        }
        Line operator-() const { return Line { -a, -b }; }
    };
    
    public:
        LiChaoSegmentTree() : LiChaoSegmentTree(std::vector<T>{}) {}

        // `query_coordinates` has to hold all coordinates x that will be passed to `operator()` or `query`.
        LiChaoSegmentTree(const std::vector<T> &query_coordinates) : pos(query_coordinates) {
            std::sort(pos.begin(), pos.end());
            pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
            n = pos.size();
            m = ceil_pow2(n);
            log_m = floor_log2(m);
            pos.resize(m, pos.size() ? pos.back() : T(0));
            seg.resize(2 * m, Line::e);
        }

        // Add ax+b for x in [min_x, max_x] (CLOSED range).
        void add_segment(T min_x, T max_x, T a, T b) {
            Line f { a, b };
            if constexpr (not is_min_query) f = -f;

            int l = std::lower_bound(pos.begin(), pos.end(), min_x) - pos.begin();
            int r = std::upper_bound(pos.begin(), pos.end(), max_x) - pos.begin();
            if (r == n) r = m;
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) add_segment(l++, f);
                if (r & 1) add_segment(--r, f);
            }
        }

        // Add ax+b for x in (-infty, infty)
        void add_line(T a, T b) {
            add_segment(std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), a, b);
        }

        /**
         * Get min(/max) at x.
         * If no segment is added to x, then returns nullopt.
         * It is required that x is contained in the vector passed to constructor.
         * If the vector does not contain x, the assertion will fail.
         */
        std::optional<T> operator()(T x) const {
            int p = std::lower_bound(pos.begin(), pos.end(), x) - pos.begin();
            assert(pos[p] == x);
            T res = std::numeric_limits<T>::max();
            bool none = true;
            for (p += m; p; p >>= 1) {
                none &= seg[p] == Line::e;
                res = std::min(res, seg[p](x));
            }
            if (none) return std::nullopt;
            if constexpr (is_min_query) {
                return std::make_optional(res);
            } else {
                return std::make_optional(-res);
            }
        }

        /**
         * Get min(/max) at x.
         * If no segment is added to x, then returns nullopt.
         * It is required that x is contained in the vector passed to constructor.
         * If the vector does not contain x, the assertion will fail.
         */
        std::optional<T> query(T x) const {
            return (*this)(x);
        }

    private:
        std::vector<T> pos;
        int n, m, log_m;
        std::vector<Line> seg;

        static int ceil_pow2(int n) {
            int k = 1;
            while (k < n) k <<= 1;
            return k;
        }
        static int floor_log2(int n) {
            return 31 - __builtin_clz(n);
        }

        std::pair<int, int> get_index_range(int k) {
            int log_w = log_m - floor_log2(k), w = 1 << log_w;
            int l = (k << log_w) - m;
            return { l, l + w };
        }

        void add_segment(int k, Line f) {
            auto [l, r] = get_index_range(k);
            for (int w = r - l; w;) {
                Line &g = seg[k];
                const T xl = pos[l], xm = pos[(l + r) >> 1], xr = pos[r - 1];
                T fl = f(xl), fm = f(xm), fr = f(xr);
                T gl = g(xl), gm = g(xm), gr = g(xr);
                if (fm < gm) std::swap(f, g), std::swap(fl, gl), std::swap(fm, gm), std::swap(fr, gr);
                k <<= 1, w >>= 1;
                if (fl < gl) {
                    k |= 0, r -= w;
                } else if (fr < gr) {
                    k |= 1, l += w;
                } else {
                    break;
                }
            }
        }
};

} // namespace suisen


#endif // SUISEN_LI_CHAO_SEGTREE
