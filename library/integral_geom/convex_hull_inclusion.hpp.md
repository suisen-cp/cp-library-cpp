---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/inclusion.hpp
    title: Inclusion
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/integral_geom/convex_hull_inclusion.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <limits>\n#include <vector>\n\
    \n#line 1 \"library/integral_geom/inclusion.hpp\"\n\n\n\nnamespace suisen::integral_geometry\
    \ {\n    enum class Inclusion { OUT, ON, IN };\n}\n\n\n#line 10 \"library/integral_geom/convex_hull_inclusion.hpp\"\
    \n\nnamespace suisen::integral_geometry {\n    /**\n     * P: convex hull\n  \
    \   * \n     * Split P to P_up, P_lo:\n     * \n     *          P_up   o---x (max\
    \ point)\n     *                /    |\n     *               o  P  o\n     * \
    \              |    /\n     *   (min point) x---o    P_lo\n     * \n     * 1.\
    \ if (x, y) is on P_lo or on P_up:\n     *      (x, y) is on P\n     * 2. if (x,\
    \ y) is above P_lo and below P_up:\n     *      (x, y) is in P\n     * 3. otherwise:\n\
    \     *      (x, y) is out of P\n    */\n\n    // Requirement:\n    // 1. for\
    \ p: Point, p_x = std::get<0>(p) and p_y = std::get<1>(p)\n    // 2. std::tuple_element_t<k,\
    \ Point> is integral type for k=0,1\n    // For example, pair<Int, Int> and tuple<Int,\
    \ Int> (Int = int, long long, ...) are acceptable.\n    template <typename Point>\n\
    \    struct ConvexHullInclusion {\n    private:\n        template <typename Int>\n\
    \        static constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<Int>>::digits;\n\
    \        template <typename Int1, typename Int2>\n        using LargerInt = std::conditional_t<bit_num<Int1>\
    \ >= bit_num<Int2>, Int1, Int2>;\n\n        using X_type = std::tuple_element_t<0,\
    \ Point>;\n        using Y_type = std::tuple_element_t<1, Point>;\n\n        static_assert(std::is_integral_v<X_type>);\n\
    \        static_assert(std::is_integral_v<Y_type>);\n\n        using Int = std::make_signed_t<LargerInt<X_type,\
    \ Y_type>>;\n    public:\n        ConvexHullInclusion() = default;\n\n       \
    \ // O(n)\n        ConvexHullInclusion(std::vector<Point> ccw_convex_hull) {\n\
    \            assert(not ccw_convex_hull.empty());\n\n            // Remove duplicates\n\
    \            ccw_convex_hull.erase(std::unique(ccw_convex_hull.begin(), ccw_convex_hull.end()),\
    \ ccw_convex_hull.end());\n            while (ccw_convex_hull.size() >= 2 and\
    \ ccw_convex_hull.front() == ccw_convex_hull.back()) {\n                ccw_convex_hull.pop_back();\n\
    \            }\n\n            auto compare = [&](const Point& p, const Point&\
    \ q) {\n                Int px = get_x(p), py = get_y(p);\n                Int\
    \ qx = get_x(q), qy = get_y(q);\n                return px != qx ? px < qx : py\
    \ < qy;\n            };\n            {\n                auto it_min = std::min_element(ccw_convex_hull.begin(),\
    \ ccw_convex_hull.end(), compare);\n                std::rotate(ccw_convex_hull.begin(),\
    \ it_min, ccw_convex_hull.end());\n            }\n            auto it_min = ccw_convex_hull.begin();\n\
    \            auto it_max = std::max_element(ccw_convex_hull.begin(), ccw_convex_hull.end(),\
    \ compare);\n\n            _xmin = get_x(*it_min);\n            _xmax = get_x(*it_max);\n\
    \n            if (_xmin == _xmax) {\n                _lo1 = { *it_min, *it_max\
    \ };\n                _lo2 = { *it_max, *it_min };\n            } else {\n   \
    \             _lo1 = std::vector<Point>(it_min, it_max);\n                while\
    \ (_lo1.size() >= 2 and get_x(_lo1.end()[-2]) == get_x(_lo1.end()[-1])) {\n  \
    \                  _lo1.pop_back();\n                }\n                _lo1.push_back(*it_max);\n\
    \n                _lo2 = std::vector<Point>(it_max, ccw_convex_hull.end());\n\
    \                while (_lo2.size() >= 2 and get_x(_lo2.end()[-2]) == get_x(_lo2.end()[-1]))\
    \ {\n                    _lo2.pop_back();\n                }\n               \
    \ _lo2.push_back(*it_min);\n            }\n\n            for (auto& p : _lo2)\
    \ {\n                std::get<0>(p) = -get_x(p);\n                std::get<1>(p)\
    \ = -get_y(p);\n            }\n        }\n\n        // O(log n)\n        template\
    \ <typename Point_>\n        Inclusion operator()(const Point_& p) const {\n \
    \           Int x = std::get<0>(p), y = std::get<1>(p);\n            if (x < _xmin\
    \ or x > _xmax) {\n                return Inclusion::OUT;\n            }\n   \
    \         Position pos1 = get_pos(_lo1, +x, +y);\n            Position pos2 =\
    \ get_pos(_lo2, -x, -y);\n            if (pos1 == Position::ON or pos2 == Position::ON)\
    \ {\n                return Inclusion::ON;\n            } else if (pos1 == Position::ABOVE\
    \ and pos2 == Position::ABOVE) {\n                return Inclusion::IN;\n    \
    \        } else {\n                return Inclusion::OUT;\n            }\n   \
    \     }\n        Inclusion operator()(const Int &x, const Int &y) const {\n  \
    \          return (*this)(std::make_pair(x, y));\n        }\n    private:\n  \
    \      Int _xmin, _xmax;\n        std::vector<Point> _lo1, _lo2;\n\n        static\
    \ Int get_x(const Point& p) {\n            return std::get<0>(p);\n        }\n\
    \        static Int get_y(const Point& p) {\n            return std::get<1>(p);\n\
    \        }\n\n        enum class Position {\n            ABOVE, ON, BELOW\n  \
    \      };\n\n        static Position get_pos(const std::vector<Point>& lower_ch,\
    \ Int x, Int y) {\n            // point (x, y) is (above / on / below)? lower_ch\n\
    \n            using MInt = std::conditional_t<bit_num<Int> <= 32, int64_t, __int128_t>;\n\
    \n            const Int xmin = get_x(lower_ch.front()), xmax = get_x(lower_ch.back());\n\
    \n            if (get_x(lower_ch.end()[-2]) == xmax and x == xmax) {\n       \
    \         // vertical\n                Int yl = get_y(lower_ch.end()[-2]), yr\
    \ = get_y(lower_ch.end()[-1]);\n                return y < yl ? Position::BELOW\
    \ : y > yr ? Position::ABOVE : Position::ON;\n            } else if (x == xmin)\
    \ {\n                Int yt = get_y(lower_ch.front());\n                return\
    \ y < yt ? Position::BELOW : y > yt ? Position::ABOVE : Position::ON;\n      \
    \      } else {\n                auto compare_x = [](const Point& p, const Int&\
    \ x) {\n                    return get_x(p) < x;\n                };\n       \
    \         // it1 > begin() since xmin < x.\n                auto it1 = std::lower_bound(lower_ch.begin(),\
    \ lower_ch.end(), x, compare_x);\n                auto it0 = it1 - 1;\n      \
    \          // x is in (x0, x1]\n                Int x0 = get_x(*it0), y0 = get_y(*it0);\n\
    \                Int x1 = get_x(*it1), y1 = get_y(*it1);\n                // \
    \     compare(y-y0, (y1-y0)/(x1-x0) * (x-x0))\n                //      <=> compare((y-y0)(x1-x0),\
    \ (y1-y0)(x-x0))\n                // since x0 < x1.\n                MInt lhs\
    \ = MInt(y - y0) * MInt(x1 - x0);\n                MInt rhs = MInt(y1 - y0) *\
    \ MInt(x - x0);\n                return lhs < rhs ? Position::BELOW : lhs > rhs\
    \ ? Position::ABOVE : Position::ON;\n            }\n        }\n    };\n} // namespace\
    \ suisen::integral_geometry\n\n\n\n"
  code: "#ifndef SUISEN_CONVEX_HULL_INCLUSION\n#define SUISEN_CONVEX_HULL_INCLUSION\n\
    \n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <vector>\n\
    \n#include \"library/integral_geom/inclusion.hpp\"\n\nnamespace suisen::integral_geometry\
    \ {\n    /**\n     * P: convex hull\n     * \n     * Split P to P_up, P_lo:\n\
    \     * \n     *          P_up   o---x (max point)\n     *                /  \
    \  |\n     *               o  P  o\n     *               |    /\n     *   (min\
    \ point) x---o    P_lo\n     * \n     * 1. if (x, y) is on P_lo or on P_up:\n\
    \     *      (x, y) is on P\n     * 2. if (x, y) is above P_lo and below P_up:\n\
    \     *      (x, y) is in P\n     * 3. otherwise:\n     *      (x, y) is out of\
    \ P\n    */\n\n    // Requirement:\n    // 1. for p: Point, p_x = std::get<0>(p)\
    \ and p_y = std::get<1>(p)\n    // 2. std::tuple_element_t<k, Point> is integral\
    \ type for k=0,1\n    // For example, pair<Int, Int> and tuple<Int, Int> (Int\
    \ = int, long long, ...) are acceptable.\n    template <typename Point>\n    struct\
    \ ConvexHullInclusion {\n    private:\n        template <typename Int>\n     \
    \   static constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<Int>>::digits;\n\
    \        template <typename Int1, typename Int2>\n        using LargerInt = std::conditional_t<bit_num<Int1>\
    \ >= bit_num<Int2>, Int1, Int2>;\n\n        using X_type = std::tuple_element_t<0,\
    \ Point>;\n        using Y_type = std::tuple_element_t<1, Point>;\n\n        static_assert(std::is_integral_v<X_type>);\n\
    \        static_assert(std::is_integral_v<Y_type>);\n\n        using Int = std::make_signed_t<LargerInt<X_type,\
    \ Y_type>>;\n    public:\n        ConvexHullInclusion() = default;\n\n       \
    \ // O(n)\n        ConvexHullInclusion(std::vector<Point> ccw_convex_hull) {\n\
    \            assert(not ccw_convex_hull.empty());\n\n            // Remove duplicates\n\
    \            ccw_convex_hull.erase(std::unique(ccw_convex_hull.begin(), ccw_convex_hull.end()),\
    \ ccw_convex_hull.end());\n            while (ccw_convex_hull.size() >= 2 and\
    \ ccw_convex_hull.front() == ccw_convex_hull.back()) {\n                ccw_convex_hull.pop_back();\n\
    \            }\n\n            auto compare = [&](const Point& p, const Point&\
    \ q) {\n                Int px = get_x(p), py = get_y(p);\n                Int\
    \ qx = get_x(q), qy = get_y(q);\n                return px != qx ? px < qx : py\
    \ < qy;\n            };\n            {\n                auto it_min = std::min_element(ccw_convex_hull.begin(),\
    \ ccw_convex_hull.end(), compare);\n                std::rotate(ccw_convex_hull.begin(),\
    \ it_min, ccw_convex_hull.end());\n            }\n            auto it_min = ccw_convex_hull.begin();\n\
    \            auto it_max = std::max_element(ccw_convex_hull.begin(), ccw_convex_hull.end(),\
    \ compare);\n\n            _xmin = get_x(*it_min);\n            _xmax = get_x(*it_max);\n\
    \n            if (_xmin == _xmax) {\n                _lo1 = { *it_min, *it_max\
    \ };\n                _lo2 = { *it_max, *it_min };\n            } else {\n   \
    \             _lo1 = std::vector<Point>(it_min, it_max);\n                while\
    \ (_lo1.size() >= 2 and get_x(_lo1.end()[-2]) == get_x(_lo1.end()[-1])) {\n  \
    \                  _lo1.pop_back();\n                }\n                _lo1.push_back(*it_max);\n\
    \n                _lo2 = std::vector<Point>(it_max, ccw_convex_hull.end());\n\
    \                while (_lo2.size() >= 2 and get_x(_lo2.end()[-2]) == get_x(_lo2.end()[-1]))\
    \ {\n                    _lo2.pop_back();\n                }\n               \
    \ _lo2.push_back(*it_min);\n            }\n\n            for (auto& p : _lo2)\
    \ {\n                std::get<0>(p) = -get_x(p);\n                std::get<1>(p)\
    \ = -get_y(p);\n            }\n        }\n\n        // O(log n)\n        template\
    \ <typename Point_>\n        Inclusion operator()(const Point_& p) const {\n \
    \           Int x = std::get<0>(p), y = std::get<1>(p);\n            if (x < _xmin\
    \ or x > _xmax) {\n                return Inclusion::OUT;\n            }\n   \
    \         Position pos1 = get_pos(_lo1, +x, +y);\n            Position pos2 =\
    \ get_pos(_lo2, -x, -y);\n            if (pos1 == Position::ON or pos2 == Position::ON)\
    \ {\n                return Inclusion::ON;\n            } else if (pos1 == Position::ABOVE\
    \ and pos2 == Position::ABOVE) {\n                return Inclusion::IN;\n    \
    \        } else {\n                return Inclusion::OUT;\n            }\n   \
    \     }\n        Inclusion operator()(const Int &x, const Int &y) const {\n  \
    \          return (*this)(std::make_pair(x, y));\n        }\n    private:\n  \
    \      Int _xmin, _xmax;\n        std::vector<Point> _lo1, _lo2;\n\n        static\
    \ Int get_x(const Point& p) {\n            return std::get<0>(p);\n        }\n\
    \        static Int get_y(const Point& p) {\n            return std::get<1>(p);\n\
    \        }\n\n        enum class Position {\n            ABOVE, ON, BELOW\n  \
    \      };\n\n        static Position get_pos(const std::vector<Point>& lower_ch,\
    \ Int x, Int y) {\n            // point (x, y) is (above / on / below)? lower_ch\n\
    \n            using MInt = std::conditional_t<bit_num<Int> <= 32, int64_t, __int128_t>;\n\
    \n            const Int xmin = get_x(lower_ch.front()), xmax = get_x(lower_ch.back());\n\
    \n            if (get_x(lower_ch.end()[-2]) == xmax and x == xmax) {\n       \
    \         // vertical\n                Int yl = get_y(lower_ch.end()[-2]), yr\
    \ = get_y(lower_ch.end()[-1]);\n                return y < yl ? Position::BELOW\
    \ : y > yr ? Position::ABOVE : Position::ON;\n            } else if (x == xmin)\
    \ {\n                Int yt = get_y(lower_ch.front());\n                return\
    \ y < yt ? Position::BELOW : y > yt ? Position::ABOVE : Position::ON;\n      \
    \      } else {\n                auto compare_x = [](const Point& p, const Int&\
    \ x) {\n                    return get_x(p) < x;\n                };\n       \
    \         // it1 > begin() since xmin < x.\n                auto it1 = std::lower_bound(lower_ch.begin(),\
    \ lower_ch.end(), x, compare_x);\n                auto it0 = it1 - 1;\n      \
    \          // x is in (x0, x1]\n                Int x0 = get_x(*it0), y0 = get_y(*it0);\n\
    \                Int x1 = get_x(*it1), y1 = get_y(*it1);\n                // \
    \     compare(y-y0, (y1-y0)/(x1-x0) * (x-x0))\n                //      <=> compare((y-y0)(x1-x0),\
    \ (y1-y0)(x-x0))\n                // since x0 < x1.\n                MInt lhs\
    \ = MInt(y - y0) * MInt(x1 - x0);\n                MInt rhs = MInt(y1 - y0) *\
    \ MInt(x - x0);\n                return lhs < rhs ? Position::BELOW : lhs > rhs\
    \ ? Position::ABOVE : Position::ON;\n            }\n        }\n    };\n} // namespace\
    \ suisen::integral_geometry\n\n\n#endif // SUISEN_CONVEX_HULL_INCLUSION\n"
  dependsOn:
  - library/integral_geom/inclusion.hpp
  isVerificationFile: false
  path: library/integral_geom/convex_hull_inclusion.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:21:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/integral_geom/convex_hull_inclusion.hpp
layout: document
title: Convex Hull Inclusion
---
## Convex Hull Inclusion
