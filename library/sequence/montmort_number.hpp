#ifndef SUISEN_MONTMORT_NUMBER
#define SUISEN_MONTMORT_NUMBER

#include <vector>

namespace suisen {
    template <typename mint>
    std::vector<mint> montmort_number(int n) {
        std::vector<mint> res{ 1, 0 };
        for (int i = 2; i <= n; ++i) res.push_back((i - 1) * (res[i - 1] + res[i - 2]));
        res.resize(n + 1);
        return res;
    }
} // namespace suisen

#endif // SUISEN_MONTMORT_NUMBER
