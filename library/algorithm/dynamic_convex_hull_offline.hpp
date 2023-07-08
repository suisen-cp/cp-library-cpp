#ifndef SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE
#define SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE

#include <algorithm>
#include <cstdint>
#include <limits>
#include <set>
#include <tuple>
#include <vector>

namespace suisen {
    struct DynamicConvexHullOffline {
    private:
        static constexpr int64_t inf = std::numeric_limits<int32_t>::max();

        struct Point {
            int64_t x, y;
            Point() = default;
            Point(int64_t x, int64_t y) : x(x), y(y) {}

            bool operator==(const Point& other) const { return x == other.x and y == other.y; }
            bool operator!=(const Point& other) const { return not operator==(other); }

            Point operator+(const Point& other) const { return { x + other.x, y + other.y }; }
            Point operator-(const Point& other) const { return { x - other.x, y - other.y }; }

            operator std::pair<int32_t, int32_t>() const { return { x, y }; }

            friend int64_t det(Point p, Point q) {
                return p.x * q.y - p.y * q.x;
            }
        };

        struct Node {
            std::pair<Point, Point> bridge;
            int64_t min_x;

            Node() = default;
            Node(Point p) : bridge(p, p), min_x(p.x) {}
            Node(std::pair<Point, Point> bridge, int64_t min_x) : bridge(bridge), min_x(min_x) {}

            bool operator==(const Node& other) const { return bridge == other.bridge and min_x == other.min_x; }
            bool operator!=(const Node& other) const { return not operator==(other); }
        };

        static inline const Node None{ Point{ -inf, -inf } };

        int _m;
        std::vector<int32_t> _xs;
        std::vector<std::set<int32_t>> _points_upper;
        std::vector<std::set<int32_t>> _points_lower;

        std::vector<Node> _seg_upper;
        std::vector<Node> _seg_lower;

        static int next_branch(int i, const std::vector<Node>& seg) {
            while (seg[2 * i] == None or seg[2 * i + 1] == None) i = 2 * i + (seg[2 * i] == None);
            return i;
        }

        static Node merge(int x, int y, std::vector<Node>& seg) {
            if (seg[x] == None) return seg[y];
            if (seg[y] == None) return seg[x];

            const int64_t min_x = seg[x].min_x;
            const int64_t sep_x = seg[y].min_x;

            Point a, b, c, d;
            while (true) {
                std::tie(a, b) = seg[x].bridge;
                std::tie(c, d) = seg[y].bridge;
                if (a == b and c == d) break;
                if (a != b and det(b - a, c - a) > 0) {
                    x = 2 * next_branch(x, seg);
                } else if (c != d and det(c - b, d - b) > 0) {
                    y = 2 * next_branch(y, seg) + 1;
                } else if (a == b) {
                    y = 2 * next_branch(y, seg);
                } else if (c == d) {
                    x = 2 * next_branch(x, seg) + 1;
                } else {
                    __int128_t c1 = det(b - a, c - a);
                    __int128_t c2 = det(a - b, d - b);
                    if (c1 + c2 == 0 or c1 * d.x + c2 * c.x < sep_x * (c1 + c2)) {
                        x = 2 * next_branch(x, seg) + 1;
                    } else {
                        y = 2 * next_branch(y, seg);
                    }
                }
            }
            return Node({ a, c }, min_x);
        }

        void set(int32_t i, const Node& dat, std::vector<Node>& seg) {
            seg[_m + i] = dat;
            for (i = (_m + i) >> 1; i > 0; i >>= 1) {
                seg[i] = merge(2 * i, 2 * i + 1, seg);
            }
        }

        void insert(int32_t x, int32_t y, std::vector<Node>& seg, std::vector<std::set<int32_t>>& points) {
            int i = index(x);
            int32_t old_y = seg[_m + i].bridge.first.y;
            points[i].insert(y);
            if (old_y >= y) return;
            set(i, Node{ Point{x, y} }, seg);
        }

        void erase(int32_t x, int32_t y, std::vector<Node>& seg, std::vector<std::set<int32_t>>& points) {
            int i = index(x);
            points[i].erase(y);
            int32_t old_y = seg[_m + i].bridge.first.y;
            if (old_y != y) return;
            set(i, points[i].empty() ? None : Node{ Point{x, *points[i].rbegin()} }, seg);
        }

        static int ceil_pow2(int n) {
            int res = 1;
            while (res < n) res <<= 1;
            return res;
        }

        int index(int32_t x) const {
            return std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin();
        }

        int64_t linear_max(int32_t a, int32_t b, const std::vector<Node>& seg) const {
            int64_t res = std::numeric_limits<int64_t>::min();
            for (int k = 1;;) {
                const auto& [p, q] = seg[k].bridge;
                res = std::max(res, p.x * a + p.y * b);
                res = std::max(res, q.x * a + q.y * b);
                if (p == q) break;
                k = 2 * next_branch(k, seg) | ((q.y - p.y) * b >= (q.x - p.x) * -a);
            }
            return res;
        }

        void get_upper_hull(int32_t l, int32_t r, int32_t k, const std::vector<Node>& seg, std::vector<std::pair<int32_t, int32_t>>& res) const {
            if (l > r or seg[k] == None) return;
            if (k >= _m) {
                res.push_back(seg[k].bridge.first);
                return;
            }
            if (seg[2 * k + 0] == None) return get_upper_hull(l, r, 2 * k + 1, seg, res);
            if (seg[2 * k + 1] == None) return get_upper_hull(l, r, 2 * k + 0, seg, res);
            int bl = seg[k].bridge.first.x, br = seg[k].bridge.second.x;
            if (r <= bl) return get_upper_hull(l, r, 2 * k + 0, seg, res);
            if (br <= l) return get_upper_hull(l, r, 2 * k + 1, seg, res);
            get_upper_hull(l, bl, 2 * k + 0, seg, res);
            get_upper_hull(br, r, 2 * k + 1, seg, res);
        }
    public:
        DynamicConvexHullOffline() = default;

        template <typename T>
        DynamicConvexHullOffline(const std::vector<T>& xs) {
            std::copy(xs.begin(), xs.end(), std::back_inserter(_xs));
            std::sort(_xs.begin(), _xs.end());
            _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());
            _m = ceil_pow2(_xs.size());
            _points_upper.resize(_m);
            _points_lower.resize(_m);
            _seg_upper = std::vector<Node>(2 * _m, None);
            _seg_lower = std::vector<Node>(2 * _m, None);
        }

        void insert(int32_t x, int32_t y) {
            insert(x, +y, _seg_upper, _points_upper);
            insert(x, -y, _seg_lower, _points_lower);
        }
        void erase(int32_t x, int32_t y) {
            erase(x, +y, _seg_upper, _points_upper);
            erase(x, -y, _seg_lower, _points_lower);
        }

        // returns max { ax + by | (x, y) in S }
        int64_t linear_max(int32_t a, int32_t b) const {
            return b >= 0 ? linear_max(a, +b, _seg_upper) : linear_max(a, -b, _seg_lower);
        }
        // returns min { ax + by | (x, y) in S }
        int64_t linear_min(int32_t a, int32_t b) const {
            return -linear_max(-a, -b);
        }

        std::vector<std::pair<int32_t, int32_t>> get_upper_hull() const {
            std::vector<std::pair<int32_t, int32_t>> res;
            get_upper_hull(-inf, inf, 1, _seg_upper, res);
            return res;
        }
        std::vector<std::pair<int32_t, int32_t>> get_lower_hull() const {
            std::vector<std::pair<int32_t, int32_t>> res;
            get_upper_hull(-inf, inf, 1, _seg_lower, res);
            for (auto& [x, y] : res) y = -y;
            return res;
        }
        std::vector<std::pair<int32_t, int32_t>> get_hull() const {
            auto upper = get_upper_hull();
            auto lower = get_lower_hull();
            if (upper.empty()) return upper;
            int32_t xl = upper.front().first, xr = upper.back().first;
            int32_t yld = lower.front().second, ylu = upper.front().second;
            int32_t yrd = lower.back().second, yru = upper.back().second;
            lower.erase(std::set_difference(lower.begin(), lower.end(), upper.begin(), upper.end(), lower.begin()), lower.end());
            for (int32_t y : _points_upper[index(xr)]) if (yrd < y and y < yru) lower.emplace_back(xr, y);
            std::reverse(lower.begin(), lower.end());
            for (auto& p : lower) upper.push_back(std::move(p));
            if (xl == xr) return upper;
            for (int32_t y : _points_upper[index(xl)]) if (yld < y and y < ylu) upper.emplace_back(xl, y);
            return upper;
        }
    };
} // namespace suisen


#endif // SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE
