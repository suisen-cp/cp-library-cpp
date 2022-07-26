#ifndef SUISEN_NUMBER_OF_SUBSEQUENCES
#define SUISEN_NUMBER_OF_SUBSEQUENCES

#include <algorithm>
#include <vector>

namespace suisen {
    // Requirement: T is comparable 
    template <typename Int, typename T>
    auto number_of_nonempty_subsequences(const std::vector<T> &a) -> decltype(std::declval<T>() < std::declval<T>(), std::declval<Int>()) {
        const int n = a.size();
        std::vector<std::pair<T, int>> sorted(n);
        for (int i = 0; i < n; ++i) sorted[i] = { a[i], i };
        std::sort(sorted.begin(), sorted.end());

        std::vector<int> last(n, -1);
        for (int i = 0; i < n;) {
            for (auto [v, p] = sorted[i]; ++i < n and sorted[i].first == v;) {
                const int c = sorted[i].second;
                last[c] = std::exchange(p, c);
            }
        }

        std::vector<Int> sdp(n + 2);
        sdp[1] = 1;
        for (int i = 0; i < n; ++i) sdp[i + 2] = sdp[i + 1] + sdp[i + 1] - sdp[last[i] + 1];
        return sdp[n + 1] - 1;
    }
} // namespace suisen

#endif // SUISEN_NUMBER_OF_SUBSEQUENCES
