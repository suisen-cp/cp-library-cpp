#ifndef SUISEN_CONVEX_HULL_INCLUSION
#define SUISEN_CONVEX_HULL_INCLUSION

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

#include "library/integral_geom/inclusion.hpp"

namespace suisen::integral_geometry {
    /**
     * P: convex hull
     * 
     * Split P to P_up, P_lo:
     * 
     *          P_up   o---x (max point)
     *                /    |
     *               o  P  o
     *               |    /
     *   (min point) x---o    P_lo
     * 
     * 1. if (x, y) is on P_lo or on P_up:
     *      (x, y) is on P
     * 2. if (x, y) is above P_lo and below P_up:
     *      (x, y) is in P
     * 3. otherwise:
     *      (x, y) is out of P
    */

    // Requirement:
    // 1. for p: Point, p_x = std::get<0>(p) and p_y = std::get<1>(p)
    // 2. std::tuple_element_t<k, Point> is integral type for k=0,1
    // For example, pair<Int, Int> and tuple<Int, Int> (Int = int, long long, ...) are acceptable.
    template <typename Point>
    struct ConvexHullInclusion {
    private:
        template <typename Int>
        static constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<Int>>::digits;
        template <typename Int1, typename Int2>
        using LargerInt = std::conditional_t<bit_num<Int1> >= bit_num<Int2>, Int1, Int2>;

        using X_type = std::tuple_element_t<0, Point>;
        using Y_type = std::tuple_element_t<1, Point>;

        static_assert(std::is_integral_v<X_type>);
        static_assert(std::is_integral_v<Y_type>);

        using Int = std::make_signed_t<LargerInt<X_type, Y_type>>;
    public:
        ConvexHullInclusion() = default;

        // O(n)
        ConvexHullInclusion(std::vector<Point> ccw_convex_hull) {
            assert(not ccw_convex_hull.empty());

            // Remove duplicates
            ccw_convex_hull.erase(std::unique(ccw_convex_hull.begin(), ccw_convex_hull.end()), ccw_convex_hull.end());
            while (ccw_convex_hull.size() >= 2 and ccw_convex_hull.front() == ccw_convex_hull.back()) {
                ccw_convex_hull.pop_back();
            }

            auto compare = [&](const Point& p, const Point& q) {
                Int px = get_x(p), py = get_y(p);
                Int qx = get_x(q), qy = get_y(q);
                return px != qx ? px < qx : py < qy;
            };
            {
                auto it_min = std::min_element(ccw_convex_hull.begin(), ccw_convex_hull.end(), compare);
                std::rotate(ccw_convex_hull.begin(), it_min, ccw_convex_hull.end());
            }
            auto it_min = ccw_convex_hull.begin();
            auto it_max = std::max_element(ccw_convex_hull.begin(), ccw_convex_hull.end(), compare);

            _xmin = get_x(*it_min);
            _xmax = get_x(*it_max);

            if (_xmin == _xmax) {
                _lo1 = { *it_min, *it_max };
                _lo2 = { *it_max, *it_min };
            } else {
                _lo1 = std::vector<Point>(it_min, it_max);
                while (_lo1.size() >= 2 and get_x(_lo1.end()[-2]) == get_x(_lo1.end()[-1])) {
                    _lo1.pop_back();
                }
                _lo1.push_back(*it_max);

                _lo2 = std::vector<Point>(it_max, ccw_convex_hull.end());
                while (_lo2.size() >= 2 and get_x(_lo2.end()[-2]) == get_x(_lo2.end()[-1])) {
                    _lo2.pop_back();
                }
                _lo2.push_back(*it_min);
            }

            for (auto& p : _lo2) {
                std::get<0>(p) = -get_x(p);
                std::get<1>(p) = -get_y(p);
            }
        }

        // O(log n)
        template <typename Point_>
        Inclusion operator()(const Point_& p) const {
            Int x = std::get<0>(p), y = std::get<1>(p);
            if (x < _xmin or x > _xmax) {
                return Inclusion::OUT;
            }
            Position pos1 = get_pos(_lo1, +x, +y);
            Position pos2 = get_pos(_lo2, -x, -y);
            if (pos1 == Position::ON or pos2 == Position::ON) {
                return Inclusion::ON;
            } else if (pos1 == Position::ABOVE and pos2 == Position::ABOVE) {
                return Inclusion::IN;
            } else {
                return Inclusion::OUT;
            }
        }
        Inclusion operator()(const Int &x, const Int &y) const {
            return (*this)(std::make_pair(x, y));
        }
    private:
        Int _xmin, _xmax;
        std::vector<Point> _lo1, _lo2;

        static Int get_x(const Point& p) {
            return std::get<0>(p);
        }
        static Int get_y(const Point& p) {
            return std::get<1>(p);
        }

        enum class Position {
            ABOVE, ON, BELOW
        };

        static Position get_pos(const std::vector<Point>& lower_ch, Int x, Int y) {
            // point (x, y) is (above / on / below)? lower_ch

            using MInt = std::conditional_t<bit_num<Int> <= 32, int64_t, __int128_t>;

            const Int xmin = get_x(lower_ch.front()), xmax = get_x(lower_ch.back());

            if (get_x(lower_ch.end()[-2]) == xmax and x == xmax) {
                // vertical
                Int yl = get_y(lower_ch.end()[-2]), yr = get_y(lower_ch.end()[-1]);
                return y < yl ? Position::BELOW : y > yr ? Position::ABOVE : Position::ON;
            } else if (x == xmin) {
                Int yt = get_y(lower_ch.front());
                return y < yt ? Position::BELOW : y > yt ? Position::ABOVE : Position::ON;
            } else {
                auto compare_x = [](const Point& p, const Int& x) {
                    return get_x(p) < x;
                };
                // it1 > begin() since xmin < x.
                auto it1 = std::lower_bound(lower_ch.begin(), lower_ch.end(), x, compare_x);
                auto it0 = it1 - 1;
                // x is in (x0, x1]
                Int x0 = get_x(*it0), y0 = get_y(*it0);
                Int x1 = get_x(*it1), y1 = get_y(*it1);
                //      compare(y-y0, (y1-y0)/(x1-x0) * (x-x0))
                //      <=> compare((y-y0)(x1-x0), (y1-y0)(x-x0))
                // since x0 < x1.
                MInt lhs = MInt(y - y0) * MInt(x1 - x0);
                MInt rhs = MInt(y1 - y0) * MInt(x - x0);
                return lhs < rhs ? Position::BELOW : lhs > rhs ? Position::ABOVE : Position::ON;
            }
        }
    };
} // namespace suisen::integral_geometry


#endif // SUISEN_CONVEX_HULL_INCLUSION
