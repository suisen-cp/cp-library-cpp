---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/dynamic_convex_hull_offline/convex_layers.test.cpp
    title: test/src/algorithm/dynamic_convex_hull_offline/convex_layers.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/dynamic_convex_hull_offline.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <cstdint>\n#include <limits>\n#include <set>\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    struct DynamicConvexHullOffline\
    \ {\n    private:\n        static constexpr int64_t inf = std::numeric_limits<int32_t>::max();\n\
    \n        struct Point {\n            int64_t x, y;\n            Point() = default;\n\
    \            Point(int64_t x, int64_t y) : x(x), y(y) {}\n\n            bool operator==(const\
    \ Point& other) const { return x == other.x and y == other.y; }\n            bool\
    \ operator!=(const Point& other) const { return not operator==(other); }\n\n \
    \           Point operator+(const Point& other) const { return { x + other.x,\
    \ y + other.y }; }\n            Point operator-(const Point& other) const { return\
    \ { x - other.x, y - other.y }; }\n\n            operator std::pair<int32_t, int32_t>()\
    \ const { return { x, y }; }\n\n            friend int64_t det(Point p, Point\
    \ q) {\n                return p.x * q.y - p.y * q.x;\n            }\n       \
    \ };\n\n        struct Node {\n            std::pair<Point, Point> bridge;\n \
    \           int64_t min_x;\n\n            Node() = default;\n            Node(Point\
    \ p) : bridge(p, p), min_x(p.x) {}\n            Node(std::pair<Point, Point> bridge,\
    \ int64_t min_x) : bridge(bridge), min_x(min_x) {}\n\n            bool operator==(const\
    \ Node& other) const { return bridge == other.bridge and min_x == other.min_x;\
    \ }\n            bool operator!=(const Node& other) const { return not operator==(other);\
    \ }\n        };\n\n        static inline const Node None{ Point{ -inf, -inf }\
    \ };\n\n        int _m;\n        std::vector<int32_t> _xs;\n        std::vector<std::set<int32_t>>\
    \ _points_upper;\n        std::vector<std::set<int32_t>> _points_lower;\n\n  \
    \      std::vector<Node> _seg_upper;\n        std::vector<Node> _seg_lower;\n\n\
    \        static int next_branch(int i, const std::vector<Node>& seg) {\n     \
    \       while (seg[2 * i] == None or seg[2 * i + 1] == None) i = 2 * i + (seg[2\
    \ * i] == None);\n            return i;\n        }\n\n        static Node merge(int\
    \ x, int y, std::vector<Node>& seg) {\n            if (seg[x] == None) return\
    \ seg[y];\n            if (seg[y] == None) return seg[x];\n\n            const\
    \ int64_t min_x = seg[x].min_x;\n            const int64_t sep_x = seg[y].min_x;\n\
    \n            Point a, b, c, d;\n            while (true) {\n                std::tie(a,\
    \ b) = seg[x].bridge;\n                std::tie(c, d) = seg[y].bridge;\n     \
    \           if (a == b and c == d) break;\n                if (a != b and det(b\
    \ - a, c - a) > 0) {\n                    x = 2 * next_branch(x, seg);\n     \
    \           } else if (c != d and det(c - b, d - b) > 0) {\n                 \
    \   y = 2 * next_branch(y, seg) + 1;\n                } else if (a == b) {\n \
    \                   y = 2 * next_branch(y, seg);\n                } else if (c\
    \ == d) {\n                    x = 2 * next_branch(x, seg) + 1;\n            \
    \    } else {\n                    __int128_t c1 = det(b - a, c - a);\n      \
    \              __int128_t c2 = det(a - b, d - b);\n                    if (c1\
    \ + c2 == 0 or c1 * d.x + c2 * c.x < sep_x * (c1 + c2)) {\n                  \
    \      x = 2 * next_branch(x, seg) + 1;\n                    } else {\n      \
    \                  y = 2 * next_branch(y, seg);\n                    }\n     \
    \           }\n            }\n            return Node({ a, c }, min_x);\n    \
    \    }\n\n        void set(int32_t i, const Node& dat, std::vector<Node>& seg)\
    \ {\n            seg[_m + i] = dat;\n            for (i = (_m + i) >> 1; i > 0;\
    \ i >>= 1) {\n                seg[i] = merge(2 * i, 2 * i + 1, seg);\n       \
    \     }\n        }\n\n        void insert(int32_t x, int32_t y, std::vector<Node>&\
    \ seg, std::vector<std::set<int32_t>>& points) {\n            int i = index(x);\n\
    \            int32_t old_y = seg[_m + i].bridge.first.y;\n            points[i].insert(y);\n\
    \            if (old_y >= y) return;\n            set(i, Node{ Point{x, y} },\
    \ seg);\n        }\n\n        void erase(int32_t x, int32_t y, std::vector<Node>&\
    \ seg, std::vector<std::set<int32_t>>& points) {\n            int i = index(x);\n\
    \            points[i].erase(y);\n            int32_t old_y = seg[_m + i].bridge.first.y;\n\
    \            if (old_y != y) return;\n            set(i, points[i].empty() ? None\
    \ : Node{ Point{x, *points[i].rbegin()} }, seg);\n        }\n\n        static\
    \ int ceil_pow2(int n) {\n            int res = 1;\n            while (res < n)\
    \ res <<= 1;\n            return res;\n        }\n\n        int index(int32_t\
    \ x) const {\n            return std::lower_bound(_xs.begin(), _xs.end(), x) -\
    \ _xs.begin();\n        }\n\n        int64_t linear_max(int32_t a, int32_t b,\
    \ const std::vector<Node>& seg) const {\n            int64_t res = std::numeric_limits<int64_t>::min();\n\
    \            for (int k = 1;;) {\n                const auto& [p, q] = seg[k].bridge;\n\
    \                res = std::max(res, p.x * a + p.y * b);\n                res\
    \ = std::max(res, q.x * a + q.y * b);\n                if (p == q) break;\n  \
    \              k = 2 * next_branch(k, seg) | ((q.y - p.y) * b >= (q.x - p.x) *\
    \ -a);\n            }\n            return res;\n        }\n\n        void get_upper_hull(int32_t\
    \ l, int32_t r, int32_t k, const std::vector<Node>& seg, std::vector<std::pair<int32_t,\
    \ int32_t>>& res) const {\n            if (l > r or seg[k] == None) return;\n\
    \            if (k >= _m) {\n                res.push_back(seg[k].bridge.first);\n\
    \                return;\n            }\n            if (seg[2 * k + 0] == None)\
    \ return get_upper_hull(l, r, 2 * k + 1, seg, res);\n            if (seg[2 * k\
    \ + 1] == None) return get_upper_hull(l, r, 2 * k + 0, seg, res);\n          \
    \  int bl = seg[k].bridge.first.x, br = seg[k].bridge.second.x;\n            if\
    \ (r <= bl) return get_upper_hull(l, r, 2 * k + 0, seg, res);\n            if\
    \ (br <= l) return get_upper_hull(l, r, 2 * k + 1, seg, res);\n            get_upper_hull(l,\
    \ bl, 2 * k + 0, seg, res);\n            get_upper_hull(br, r, 2 * k + 1, seg,\
    \ res);\n        }\n    public:\n        DynamicConvexHullOffline() {}\n\n   \
    \     template <typename T>\n        DynamicConvexHullOffline(const std::vector<T>&\
    \ xs) {\n            std::copy(xs.begin(), xs.end(), std::back_inserter(_xs));\n\
    \            std::sort(_xs.begin(), _xs.end());\n            _xs.erase(std::unique(_xs.begin(),\
    \ _xs.end()), _xs.end());\n            _m = ceil_pow2(_xs.size());\n         \
    \   _points_upper.resize(_m);\n            _points_lower.resize(_m);\n       \
    \     _seg_upper = std::vector<Node>(2 * _m, None);\n            _seg_lower =\
    \ std::vector<Node>(2 * _m, None);\n        }\n\n        void insert(int32_t x,\
    \ int32_t y) {\n            insert(x, +y, _seg_upper, _points_upper);\n      \
    \      insert(x, -y, _seg_lower, _points_lower);\n        }\n        void erase(int32_t\
    \ x, int32_t y) {\n            erase(x, +y, _seg_upper, _points_upper);\n    \
    \        erase(x, -y, _seg_lower, _points_lower);\n        }\n\n        // returns\
    \ max { ax + by | (x, y) in S }\n        int64_t linear_max(int32_t a, int32_t\
    \ b) const {\n            return b >= 0 ? linear_max(a, +b, _seg_upper) : linear_max(a,\
    \ -b, _seg_lower);\n        }\n        // returns min { ax + by | (x, y) in S\
    \ }\n        int64_t linear_min(int32_t a, int32_t b) const {\n            return\
    \ -linear_max(-a, -b);\n        }\n\n        std::vector<std::pair<int32_t, int32_t>>\
    \ get_upper_hull() const {\n            std::vector<std::pair<int32_t, int32_t>>\
    \ res;\n            get_upper_hull(-inf, inf, 1, _seg_upper, res);\n         \
    \   return res;\n        }\n        std::vector<std::pair<int32_t, int32_t>> get_lower_hull()\
    \ const {\n            std::vector<std::pair<int32_t, int32_t>> res;\n       \
    \     get_upper_hull(-inf, inf, 1, _seg_lower, res);\n            for (auto& [x,\
    \ y] : res) y = -y;\n            return res;\n        }\n        std::vector<std::pair<int32_t,\
    \ int32_t>> get_hull() const {\n            auto upper = get_upper_hull();\n \
    \           auto lower = get_lower_hull();\n            if (upper.empty()) return\
    \ upper;\n            int32_t xl = upper.front().first, xr = upper.back().first;\n\
    \            int32_t yld = lower.front().second, ylu = upper.front().second;\n\
    \            int32_t yrd = lower.back().second, yru = upper.back().second;\n \
    \           lower.erase(std::set_difference(lower.begin(), lower.end(), upper.begin(),\
    \ upper.end(), lower.begin()), lower.end());\n            for (int32_t y : _points_upper[index(xr)])\
    \ if (yrd < y and y < yru) lower.emplace_back(xr, y);\n            std::reverse(lower.begin(),\
    \ lower.end());\n            for (auto& p : lower) upper.push_back(std::move(p));\n\
    \            if (xl == xr) return upper;\n            for (int32_t y : _points_upper[index(xl)])\
    \ if (yld < y and y < ylu) upper.emplace_back(xl, y);\n            return upper;\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE\n#define SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE\n\
    \n#include <algorithm>\n#include <cstdint>\n#include <limits>\n#include <set>\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    struct DynamicConvexHullOffline\
    \ {\n    private:\n        static constexpr int64_t inf = std::numeric_limits<int32_t>::max();\n\
    \n        struct Point {\n            int64_t x, y;\n            Point() = default;\n\
    \            Point(int64_t x, int64_t y) : x(x), y(y) {}\n\n            bool operator==(const\
    \ Point& other) const { return x == other.x and y == other.y; }\n            bool\
    \ operator!=(const Point& other) const { return not operator==(other); }\n\n \
    \           Point operator+(const Point& other) const { return { x + other.x,\
    \ y + other.y }; }\n            Point operator-(const Point& other) const { return\
    \ { x - other.x, y - other.y }; }\n\n            operator std::pair<int32_t, int32_t>()\
    \ const { return { x, y }; }\n\n            friend int64_t det(Point p, Point\
    \ q) {\n                return p.x * q.y - p.y * q.x;\n            }\n       \
    \ };\n\n        struct Node {\n            std::pair<Point, Point> bridge;\n \
    \           int64_t min_x;\n\n            Node() = default;\n            Node(Point\
    \ p) : bridge(p, p), min_x(p.x) {}\n            Node(std::pair<Point, Point> bridge,\
    \ int64_t min_x) : bridge(bridge), min_x(min_x) {}\n\n            bool operator==(const\
    \ Node& other) const { return bridge == other.bridge and min_x == other.min_x;\
    \ }\n            bool operator!=(const Node& other) const { return not operator==(other);\
    \ }\n        };\n\n        static inline const Node None{ Point{ -inf, -inf }\
    \ };\n\n        int _m;\n        std::vector<int32_t> _xs;\n        std::vector<std::set<int32_t>>\
    \ _points_upper;\n        std::vector<std::set<int32_t>> _points_lower;\n\n  \
    \      std::vector<Node> _seg_upper;\n        std::vector<Node> _seg_lower;\n\n\
    \        static int next_branch(int i, const std::vector<Node>& seg) {\n     \
    \       while (seg[2 * i] == None or seg[2 * i + 1] == None) i = 2 * i + (seg[2\
    \ * i] == None);\n            return i;\n        }\n\n        static Node merge(int\
    \ x, int y, std::vector<Node>& seg) {\n            if (seg[x] == None) return\
    \ seg[y];\n            if (seg[y] == None) return seg[x];\n\n            const\
    \ int64_t min_x = seg[x].min_x;\n            const int64_t sep_x = seg[y].min_x;\n\
    \n            Point a, b, c, d;\n            while (true) {\n                std::tie(a,\
    \ b) = seg[x].bridge;\n                std::tie(c, d) = seg[y].bridge;\n     \
    \           if (a == b and c == d) break;\n                if (a != b and det(b\
    \ - a, c - a) > 0) {\n                    x = 2 * next_branch(x, seg);\n     \
    \           } else if (c != d and det(c - b, d - b) > 0) {\n                 \
    \   y = 2 * next_branch(y, seg) + 1;\n                } else if (a == b) {\n \
    \                   y = 2 * next_branch(y, seg);\n                } else if (c\
    \ == d) {\n                    x = 2 * next_branch(x, seg) + 1;\n            \
    \    } else {\n                    __int128_t c1 = det(b - a, c - a);\n      \
    \              __int128_t c2 = det(a - b, d - b);\n                    if (c1\
    \ + c2 == 0 or c1 * d.x + c2 * c.x < sep_x * (c1 + c2)) {\n                  \
    \      x = 2 * next_branch(x, seg) + 1;\n                    } else {\n      \
    \                  y = 2 * next_branch(y, seg);\n                    }\n     \
    \           }\n            }\n            return Node({ a, c }, min_x);\n    \
    \    }\n\n        void set(int32_t i, const Node& dat, std::vector<Node>& seg)\
    \ {\n            seg[_m + i] = dat;\n            for (i = (_m + i) >> 1; i > 0;\
    \ i >>= 1) {\n                seg[i] = merge(2 * i, 2 * i + 1, seg);\n       \
    \     }\n        }\n\n        void insert(int32_t x, int32_t y, std::vector<Node>&\
    \ seg, std::vector<std::set<int32_t>>& points) {\n            int i = index(x);\n\
    \            int32_t old_y = seg[_m + i].bridge.first.y;\n            points[i].insert(y);\n\
    \            if (old_y >= y) return;\n            set(i, Node{ Point{x, y} },\
    \ seg);\n        }\n\n        void erase(int32_t x, int32_t y, std::vector<Node>&\
    \ seg, std::vector<std::set<int32_t>>& points) {\n            int i = index(x);\n\
    \            points[i].erase(y);\n            int32_t old_y = seg[_m + i].bridge.first.y;\n\
    \            if (old_y != y) return;\n            set(i, points[i].empty() ? None\
    \ : Node{ Point{x, *points[i].rbegin()} }, seg);\n        }\n\n        static\
    \ int ceil_pow2(int n) {\n            int res = 1;\n            while (res < n)\
    \ res <<= 1;\n            return res;\n        }\n\n        int index(int32_t\
    \ x) const {\n            return std::lower_bound(_xs.begin(), _xs.end(), x) -\
    \ _xs.begin();\n        }\n\n        int64_t linear_max(int32_t a, int32_t b,\
    \ const std::vector<Node>& seg) const {\n            int64_t res = std::numeric_limits<int64_t>::min();\n\
    \            for (int k = 1;;) {\n                const auto& [p, q] = seg[k].bridge;\n\
    \                res = std::max(res, p.x * a + p.y * b);\n                res\
    \ = std::max(res, q.x * a + q.y * b);\n                if (p == q) break;\n  \
    \              k = 2 * next_branch(k, seg) | ((q.y - p.y) * b >= (q.x - p.x) *\
    \ -a);\n            }\n            return res;\n        }\n\n        void get_upper_hull(int32_t\
    \ l, int32_t r, int32_t k, const std::vector<Node>& seg, std::vector<std::pair<int32_t,\
    \ int32_t>>& res) const {\n            if (l > r or seg[k] == None) return;\n\
    \            if (k >= _m) {\n                res.push_back(seg[k].bridge.first);\n\
    \                return;\n            }\n            if (seg[2 * k + 0] == None)\
    \ return get_upper_hull(l, r, 2 * k + 1, seg, res);\n            if (seg[2 * k\
    \ + 1] == None) return get_upper_hull(l, r, 2 * k + 0, seg, res);\n          \
    \  int bl = seg[k].bridge.first.x, br = seg[k].bridge.second.x;\n            if\
    \ (r <= bl) return get_upper_hull(l, r, 2 * k + 0, seg, res);\n            if\
    \ (br <= l) return get_upper_hull(l, r, 2 * k + 1, seg, res);\n            get_upper_hull(l,\
    \ bl, 2 * k + 0, seg, res);\n            get_upper_hull(br, r, 2 * k + 1, seg,\
    \ res);\n        }\n    public:\n        DynamicConvexHullOffline() {}\n\n   \
    \     template <typename T>\n        DynamicConvexHullOffline(const std::vector<T>&\
    \ xs) {\n            std::copy(xs.begin(), xs.end(), std::back_inserter(_xs));\n\
    \            std::sort(_xs.begin(), _xs.end());\n            _xs.erase(std::unique(_xs.begin(),\
    \ _xs.end()), _xs.end());\n            _m = ceil_pow2(_xs.size());\n         \
    \   _points_upper.resize(_m);\n            _points_lower.resize(_m);\n       \
    \     _seg_upper = std::vector<Node>(2 * _m, None);\n            _seg_lower =\
    \ std::vector<Node>(2 * _m, None);\n        }\n\n        void insert(int32_t x,\
    \ int32_t y) {\n            insert(x, +y, _seg_upper, _points_upper);\n      \
    \      insert(x, -y, _seg_lower, _points_lower);\n        }\n        void erase(int32_t\
    \ x, int32_t y) {\n            erase(x, +y, _seg_upper, _points_upper);\n    \
    \        erase(x, -y, _seg_lower, _points_lower);\n        }\n\n        // returns\
    \ max { ax + by | (x, y) in S }\n        int64_t linear_max(int32_t a, int32_t\
    \ b) const {\n            return b >= 0 ? linear_max(a, +b, _seg_upper) : linear_max(a,\
    \ -b, _seg_lower);\n        }\n        // returns min { ax + by | (x, y) in S\
    \ }\n        int64_t linear_min(int32_t a, int32_t b) const {\n            return\
    \ -linear_max(-a, -b);\n        }\n\n        std::vector<std::pair<int32_t, int32_t>>\
    \ get_upper_hull() const {\n            std::vector<std::pair<int32_t, int32_t>>\
    \ res;\n            get_upper_hull(-inf, inf, 1, _seg_upper, res);\n         \
    \   return res;\n        }\n        std::vector<std::pair<int32_t, int32_t>> get_lower_hull()\
    \ const {\n            std::vector<std::pair<int32_t, int32_t>> res;\n       \
    \     get_upper_hull(-inf, inf, 1, _seg_lower, res);\n            for (auto& [x,\
    \ y] : res) y = -y;\n            return res;\n        }\n        std::vector<std::pair<int32_t,\
    \ int32_t>> get_hull() const {\n            auto upper = get_upper_hull();\n \
    \           auto lower = get_lower_hull();\n            if (upper.empty()) return\
    \ upper;\n            int32_t xl = upper.front().first, xr = upper.back().first;\n\
    \            int32_t yld = lower.front().second, ylu = upper.front().second;\n\
    \            int32_t yrd = lower.back().second, yru = upper.back().second;\n \
    \           lower.erase(std::set_difference(lower.begin(), lower.end(), upper.begin(),\
    \ upper.end(), lower.begin()), lower.end());\n            for (int32_t y : _points_upper[index(xr)])\
    \ if (yrd < y and y < yru) lower.emplace_back(xr, y);\n            std::reverse(lower.begin(),\
    \ lower.end());\n            for (auto& p : lower) upper.push_back(std::move(p));\n\
    \            if (xl == xr) return upper;\n            for (int32_t y : _points_upper[index(xl)])\
    \ if (yld < y and y < ylu) upper.emplace_back(xl, y);\n            return upper;\n\
    \        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_DYNAMIC_CONVEX_HULL_OFFLINE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/dynamic_convex_hull_offline.hpp
  requiredBy: []
  timestamp: '2022-03-31 17:13:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/dynamic_convex_hull_offline/convex_layers.test.cpp
documentation_of: library/algorithm/dynamic_convex_hull_offline.hpp
layout: document
redirect_from:
- /library/library/algorithm/dynamic_convex_hull_offline.hpp
- /library/library/algorithm/dynamic_convex_hull_offline.hpp.html
title: library/algorithm/dynamic_convex_hull_offline.hpp
---
