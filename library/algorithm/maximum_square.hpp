#ifndef SUISEN_MAXIMUM_SQUARE
#define SUISEN_MAXIMUM_SQUARE

#include <algorithm>
#include <tuple>
#include <vector>

namespace suisen {
    // Returns { max_area, { u, d, l, r } } where g[u,d)*[l,r) is one of the maximum squares.
    template <typename Grid>
    std::pair<int, std::tuple<int, int, int, int>> maximum_square(const Grid& g) {
        int max_l = 0;
        std::tuple<int, int, int, int> max_square;

        const int n = g.size();
        const int m = n == 0 ? 0 : g[0].size();
        
        std::vector<int> pd(m);
        for (int i = 0; i < n; ++i) {
            std::vector<int> dp(m);
            for (int j = 0; j < m; ++j) if (g[i][j]) {
                if (j == 0) {
                    dp[j] = 1;
                } else {
                    dp[j] = 1 + std::min({ dp[j - 1], pd[j - 1], pd[j] });
                }
                if (dp[j] > max_l) {
                    max_l = dp[j];
                    max_square = { i + 1 - max_l, i + 1, j + 1 - max_l, j + 1 };
                }
            }
            dp.swap(pd);
        }
        return { max_l * max_l, max_square };
    }
} // namespace suisen


#endif // SUISEN_MAXIMUM_SQUARE
