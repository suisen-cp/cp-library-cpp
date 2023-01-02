#ifndef SUISEN_SCC_TOURNAMENT
#define SUISEN_SCC_TOURNAMENT

#include <numeric>
#include <vector>

namespace suisen {
    std::vector<std::vector<int>> scc_tournament(const std::vector<int> &in_deg) {
        const int n = in_deg.size();
        std::vector<std::vector<int>> bucket(n);
        for (int i = 0; i < n; ++i) {
            int d = in_deg[i];
            bucket[d].push_back(i);
        }
        std::vector<std::vector<int>> scc{{}};
        int removed_num = 0;
        long long num = 0;
        long long sum = 0;
        for (int d = 0; d < n; ++d) for (int v : bucket[d]) {
            scc.back().push_back(v);
            num += 1;
            sum += d - removed_num;
            if (num * (num - 1) == 2 * sum) {
                removed_num += num;
                num = 0, sum = 0;
                scc.emplace_back();
            }
        }
        scc.pop_back();
        return scc;
    }
} // namespace suisen


#endif // SUISEN_SCC_TOURNAMENT
