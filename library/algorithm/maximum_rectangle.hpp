#ifndef SUISEN_MAXIMUM_RECTANGLE
#define SUISEN_MAXIMUM_RECTANGLE

#include <tuple>
#include <vector>

namespace suisen {
    // f : (l, r, h) -> void
    template <typename Histogram, typename Func>
    void maximal_rectangles_hist(const Histogram& h, Func &&f) {
        using Value = std::decay_t<decltype(h[0])>;

        static_assert((std::is_invocable_v<Func, int, int, Value>));

        const int n = h.size();
        std::vector<std::pair<int, Value>> stack;
        for (int r = 0; r <= n; ++r) {
            Value hr = r < n ? h[r] : 0;
            int j = r; // min j s.t. min(h[j], ..., h[r]) >= h[r]
            while (stack.size()) {
                auto [l, hl] = stack.back();
                if (hl < hr) break;
                f(l, r, hl);
                stack.pop_back();
                j = l;
            }
            stack.emplace_back(j, hr);
        }
    }

    // f : (u, d, l, r) -> void
    template <typename Grid, typename Func>
    void maximal_rectangles(const Grid& g, Func &&f) {
        static_assert((std::is_invocable_v<Func, int, int, int, int>));
        const int n = g.size();
        if (n == 0) return;
        const int m = g[0].size();
        std::vector<int> h(m), cnt_zero(m + 1);
        for (int i = 0; i < n; ++i) {
            for (int r = 0; r < m; ++r) {
                h[r] = g[i][r] ? h[r] + 1 : 0;
                cnt_zero[r + 1] = cnt_zero[r] + (i + 1 != n ? not bool(g[i + 1][r]) : 1);
            }
            maximal_rectangles_hist(h, [i, &f, &cnt_zero](int l, int r, int h) {
                if (cnt_zero[r] - cnt_zero[l]) {
                    f(i - h + 1, i + 1, l, r);
                }
            });
        }
    }

    // Returns { max_area, { u, d, l, r } } where g[u,d)*[l,r) is one of the maximum rectangles.
    template <typename Grid>
    std::pair<int, std::tuple<int, int, int, int>> maximum_rectngle(const Grid& g) {
        int max_area = 0;
        std::tuple<int, int, int, int> max_rect;

        maximal_rectangles(g, [&max_area, &max_rect](int u, int d, int l, int r){
            int area = (d - u) * (r - l);
            if (area > max_area) {
                max_area = area;
                max_rect = { u, d, l, r };
            }
        });

        return { max_area, max_rect };
    }
} // namespace suisen


#endif // SUISEN_MAXIMUM_RECTANGLE
