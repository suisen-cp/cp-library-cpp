#ifndef SUISEN_AREA_OF_UNION_OF_RECTANGLES
#define SUISEN_AREA_OF_UNION_OF_RECTANGLES

#include <limits>
#include <tuple>
#include <vector>

#include <atcoder/lazysegtree>

namespace suisen {
    namespace internal::area_of_union_of_rectangles {
        constexpr int inf = std::numeric_limits<int>::max() / 2;

        template <typename T> struct S {
            int min_cnt;
            T len;
        };
        template <typename T> S<T> op(S<T> x, S<T> y) {
            if (x.min_cnt < y.min_cnt) return x;
            else if (x.min_cnt > y.min_cnt) return y;
            else return { x.min_cnt, x.len + y.len };
        }
        template <typename T> S<T> e() { return { inf , 0 }; }
        template <typename T> S<T> mapping(int f, S<T> x) { return { x.min_cnt + f, x.len }; }
        int composition(int f, int g) { return f + g; }
        int id() { return 0; }
    }

    /**
     * @brief Calculates area of union of rectangles in O(NlogN) time.
     * @tparam T type of coordinates
     * @param rects vector of { l, r, d, u }.
     * @return area of union of rectangles
     */
    template <typename T>
    T area_of_union_of_rectangles(const std::vector<std::tuple<T, T, T, T>> &rects) {
        if (rects.empty()) return T{0};

        using namespace internal::area_of_union_of_rectangles;

        const int k = rects.size();

        std::vector<std::tuple<T, T, T, bool>> event;
        event.reserve(2 * k);

        std::vector<T> ys;
        ys.reserve(2 * k);

        for (const auto &[l, r, d, u] : rects) {
            event.emplace_back(l, d, u, true);
            event.emplace_back(r, d, u, false);
            ys.push_back(d), ys.push_back(u);
        }
        std::sort(event.begin(), event.end(), [](const auto& e1, const auto &e2) { return std::get<0>(e1) < std::get<0>(e2); });
        std::sort(ys.begin(), ys.end()), ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

        const int m = ys.size();

        std::vector<S<T>> init(m - 1);
        for (int i = 0; i < m - 1; ++i) {
            init[i] = { 0, ys[i + 1] - ys[i] };
        }
        atcoder::lazy_segtree<S<T>, op<T>, e<T>, int, mapping<T>, composition, id> seg(init);

        T ans = 0;
        T lx = std::get<0>(event.front());
        for (int i = 0; lx != std::get<0>(event.back());) {
            for (;; ++i) {
                auto [xi, d, u, b] = event[i];
                if (xi != lx) break;
                int ly = std::lower_bound(ys.begin(), ys.end(), d) - ys.begin();
                int ry = std::lower_bound(ys.begin(), ys.end(), u) - ys.begin();
                seg.apply(ly, ry, b ? +1 : -1);
            }
            T rx = std::get<0>(event[i]);
            auto [min_cnt, len] = seg.all_prod();
            ans += (rx - lx) * (ys.back() - ys.front() - (min_cnt == 0 ? len : T{0}));
            lx = rx;
        }
        return ans;
    }
} // namespace suisen

#endif // SUISEN_AREA_OF_UNION_OF_RECTANGLES
