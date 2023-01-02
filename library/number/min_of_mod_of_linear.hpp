#ifndef SUISEN_MIN_OF_MOD_OF_LINEAR
#define SUISEN_MIN_OF_MOD_OF_LINEAR

#include <numeric>
#include <vector>

#include <atcoder/math>

namespace suisen {
    // min{ (ax+b) mod m | 0<=x<n }
    int min_of_mod_of_linear(int n, int m, int a, int b) {
        // let k be an integer s.t. 0<=k<m.
        //     ax+b mod M <= k
        // <=> (ax+b-k)/m <= floor((ax+b)/m)
        // <=> floor((ax+b+(m-1-k))/m) <= floor((ax+b)/m)
        // <=> floor((ax+b+(m-1-k))/m)  = floor((ax+b)/m)    (because 0<=m-1-k<m)

        // if there exists an integer x in [0,n) s.t. floor((ax+b+(m-1-k))/m) = floor((ax+b)/m),
        //   floor_sum(n, m, a, b+(m-1-k)) < floor_sum(n, m, a, b) + n
        // holds.

        // Applying binary search on k, we can get min{ (ax+b) mod m | 0<=x<n } in O((log m)^2) time.

        long long v = atcoder::floor_sum(n, m, a, b) + n;

        int l = -1, r = m - 1;
        while (r - l > 1) {
            int k = (l + r) >> 1;
            if (atcoder::floor_sum(n, m, a, b + (m - 1 - k)) < v) {
                r = k;
            } else {
                l = k;
            }
        }
        return r;
    }
} // namespace suisen


#endif // SUISEN_MIN_OF_MOD_OF_LINEAR
