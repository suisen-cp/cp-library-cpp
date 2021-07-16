#ifndef SUISEN_CONVEX_HULL
#define SUISEN_CONVEX_HULL

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

namespace suisen {
namespace geometry {
    template <typename T>
    std::vector<int> convex_hull(const std::vector<std::complex<T>> &points) {
        const int n = points.size();
        std::vector<int> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j) {
            auto &a = points[i], &b = points[j];
            return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();
        });
        std::vector<char> used(n, false);
        sorted.resize(2 * n - 1);
        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);
        std::vector<int> res;
        res.reserve(n);
        int first = sorted[0], last = sorted[n - 1];
        const T eps = 1e-9;
        auto sgn = [&eps](T x) -> int {
            return x <= -eps ? -1 : x >= eps ? 1 : 0;
        };
        auto isp_pos = [&sgn](T x1, T y1, T x2, T y2) -> bool {
            int det_sgn = sgn(x1 * y2 - y1 * x2);
            return det_sgn > 0 or (det_sgn == 0 and sgn(x1 * x2 + y1 * y2) > 0);
        };
        for (int k : sorted) {
            if (k != first and used[k]) continue;
            for (int sz = res.size(); sz >= 2; --sz) {
                int i = res[sz - 2], j = res[sz - 1];
                if (j == last) break;
                std::complex<T> ab = points[j] - points[i];
                std::complex<T> bc = points[k] - points[j];
                if (isp_pos(ab.real(), ab.imag(), bc.real(), bc.imag())) break;
                res.pop_back(), used[j] = false;
            }
            if (not used[k]) res.push_back(k);
            used[k] = true;
        }
        return res;
    }
    std::vector<int> convex_hull(const std::vector<std::pair<long long, long long>> &points) {
        const int n = points.size();
        std::vector<int> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j) {
            auto &a = points[i], &b = points[j];
            return a.first == b.first ? a.second < b.second : a.first < b.first;
        });
        std::vector<char> used(n, false);
        sorted.resize(2 * n - 1);
        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);
        std::vector<int> res;
        res.reserve(n);
        int first = sorted[0], last = sorted[n - 1];
        auto isp_pos = [](long long x1, long long y1, long long x2, long long y2) -> bool {
            long long det = x1 * y2 - y1 * x2;
            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);
        };
        for (int k : sorted) {
            if (k != first and used[k]) continue;
            for (int sz = res.size(); sz >= 2; --sz) {
                int i = res[sz - 2], j = res[sz - 1];
                if (j == last) break;
                long long ab_x = points[j].first - points[i].first, ab_y = points[j].second - points[i].second;
                long long bc_x = points[k].first - points[j].first, bc_y = points[k].second - points[j].second;
                if (isp_pos(ab_x, ab_y, bc_x, bc_y)) break;
                res.pop_back(), used[j] = false;
            }
            if (not used[k]) res.push_back(k);
            used[k] = true;
        }
        return res;
    }
}
} // namespace suisen

#endif // SUISEN_CONVEX_HULL
