#include <cmath>
#include <numeric>
#include <vector>

namespace suisen {
namespace geometry {
    // return: calculate the number of lattice points in the polygon or on at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).
    long long count_lattice_points(const std::vector<std::pair<long long, long long>> &polygon) {
        const int n = polygon.size();
        long long s = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            auto [x1, y1] = polygon[i];
            auto [x2, y2] = polygon[(i + 1) % n];
            s += x1 * y2 - y1 * x2;
            b += std::abs(std::gcd(x2 - x1, y2 - y1));
        }
        return (s + 2 + b) / 2;
    }
}
} // namespace suisen