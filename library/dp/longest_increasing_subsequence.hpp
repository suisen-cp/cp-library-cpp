#ifndef SUISEN_LONGEST_INCREASING_SUBSEQUENCE
#define SUISEN_LONGEST_INCREASING_SUBSEQUENCE

#include <algorithm>
#include <vector>

namespace suisen {
    namespace internal::lis {
        template <typename T, typename ComparatorType>
        std::vector<int> solve(const std::vector<T>& a) {
            if (a.empty()) return {};
            const int n = a.size();
            std::vector<T> dp;
            dp.reserve(n);
            std::vector<int> pd(n, -1), id(n, -1);
            for (int i = 0; i < n; ++i) {
                const int pos = std::lower_bound(dp.begin(), dp.end(), a[i], ComparatorType{}) - dp.begin();
                id[pos] = i;
                if (pos >= 1) pd[i] = id[pos - 1];
                if (pos == int(dp.size())) dp.push_back(a[i]);
                else dp[pos] = a[i];
            }
            int len = dp.size();
            std::vector<int> ans(len);
            for (int cur = id[len - 1]; cur >= 0; cur = pd[cur]) ans[--len] = cur;
            return ans;
        }
    }
    // @returns ** indices ** of longest increasing subsequence
    template <typename T>
    std::vector<int> longest_increasing_subsequence(const std::vector<T>& a)    { return internal::lis::solve<T, std::less<T>>(a); }
    // @returns ** indices ** of longest nondecreasing subsequence
    template <typename T>
    std::vector<int> longest_nondecreasing_subsequence(const std::vector<T>& a) { return internal::lis::solve<T, std::less_equal<T>>(a); }
    // @returns ** indices ** of longest nonincreasing subsequence
    template <typename T>
    std::vector<int> longest_nonincreasing_subsequence(const std::vector<T>& a) { return internal::lis::solve<T, std::greater_equal<T>>(a); }
    // @returns ** indices ** of longest decreasing subsequence
    template <typename T>
    std::vector<int> longest_decreasing_subsequence(const std::vector<T>& a)    { return internal::lis::solve<T, std::greater<T>>(a); }
} // namespace suisen

#endif // SUISEN_LONGEST_INCREASING_SUBSEQUENCE
