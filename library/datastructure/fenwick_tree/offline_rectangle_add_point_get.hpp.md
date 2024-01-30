---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/fenwick_tree/offline_rectangle_add_point_get/rectangle_add_point_get.test.cpp
    title: test/src/datastructure/fenwick_tree/offline_rectangle_add_point_get/rectangle_add_point_get.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <numeric>\n#include <vector>\n\
    \n#include <atcoder/fenwicktree>\n\nnamespace suisen {\n    template <typename\
    \ T, typename Index = int>\n    struct OfflineRectangleAddPointGet {\n    private:\n\
    \        using Rectangle = std::array<Index, 4>;\n        using Point = std::array<Index,\
    \ 2>;\n    public:\n        void add(Index l, Index r, Index d, Index u, T w)\
    \ {\n            assert(l <= r and d <= u);\n            if (l == r or d == u)\
    \ return;\n            _rects.push_back({ l, r, d, u });\n            _weights.push_back(w);\n\
    \        }\n        void get(Index x, Index y) {\n            _points.push_back({\
    \ x, y });\n            _times.push_back(_rects.size());\n        }\n\n      \
    \  std::vector<T> solve() const {\n            std::vector<T> ans(_points.size());\n\
    \n            const int rect_num = _rects.size();\n\n            using Key = std::pair<Index,\
    \ int>;\n            constexpr auto comp_key = [](const Key &k1, const Key& k2)\
    \ { return k1.first < k2.first; };\n\n            /**\n             * [---------------------8]\n\
    \             * [---------4]............[----------12]\n             * [---2]......[---6]......[--10]........[----14]\n\
    \             * [1]...[3]...[5]...[7]...[9]...[11]....[13]....\n             *\
    \ \n             * ---------------- rectangles ----------------->\n          \
    \   */\n\n            // Event      (l,d,+w), (l,u,-w), (r,d,-w), (r,u,+w)\n \
    \           // Index(x)      2i        2i       2i+1      2i+1\n            //\
    \ Index(y)      2i       2i+1       2i       2i+1\n            std::vector<Key>\
    \ es_asc_x(2 * rect_num), es_asc_y(2 * rect_num);\n            for (int i = 0;\
    \ i < rect_num; ++i) {\n                es_asc_x[2 * i + 0] = Key{ _rects[i][0],\
    \ 2 * i + 0 }; // l\n                es_asc_x[2 * i + 1] = Key{ _rects[i][1],\
    \ 2 * i + 1 }; // r\n                es_asc_y[2 * i + 0] = Key{ _rects[i][2],\
    \ 2 * i + 0 }; // d\n                es_asc_y[2 * i + 1] = Key{ _rects[i][3],\
    \ 2 * i + 1 }; // u\n            }\n            std::vector<std::vector<Key>>\
    \ ps_asc_x(rect_num), ps_asc_y(rect_num);\n            for (int pid = 0; pid <\
    \ int(_points.size()); ++pid) if (_times[pid]) {\n                const int r\
    \ = floor_pow2(_times[pid]);\n                ps_asc_x[r - 1].emplace_back(_points[pid][0],\
    \ pid); // x\n                ps_asc_y[r - 1].emplace_back(_points[pid][1], pid);\
    \ // y\n            }\n\n            std::vector<int> ps_comp_y(_points.size()),\
    \ es_comp_y(2 * rect_num);\n\n            for (int r = 1; r <= rect_num; ++r)\
    \ {\n                const int w = -r & r, l = r - w;\n                for (int\
    \ t = 1; t < w; t <<= 1) {\n                    // Merge Sort\n              \
    \      // r=8 : {8}  -> {7,8}   -> {5,6,7,8}    -> {1,2,3,4,5,6,7,8}\n       \
    \             // r=12: {12} -> {11,12} -> {9,10,11,12}\n                    auto\
    \ it_r_x = es_asc_x.begin() + 2 * r, it_m_x = it_r_x - 2 * t, it_l_x = it_m_x\
    \ - 2 * t;\n                    std::inplace_merge(it_l_x, it_m_x, it_r_x, comp_key);\n\
    \                    auto it_r_y = es_asc_y.begin() + 2 * r, it_m_y = it_r_y -\
    \ 2 * t, it_l_y = it_m_y - 2 * t;\n                    std::inplace_merge(it_l_y,\
    \ it_m_y, it_r_y, comp_key);\n                }\n\n                const int point_num\
    \ = ps_asc_x[r - 1].size();\n                if (point_num == 0) continue;\n \
    \               if (r == (-r & r)) {\n                    std::sort(ps_asc_x[r\
    \ - 1].begin(), ps_asc_x[r - 1].end(), comp_key);\n                    std::sort(ps_asc_y[r\
    \ - 1].begin(), ps_asc_y[r - 1].end(), comp_key);\n                }\n       \
    \         int num_y = 0;\n                {\n                    std::vector<Key>\
    \ mixed_asc_y(es_asc_y.begin() + 2 * l, es_asc_y.begin() + 2 * r);\n         \
    \           const int mid_siz = mixed_asc_y.size(), siz = mid_siz + point_num;\n\
    \                    mixed_asc_y.reserve(siz);\n                    for (const\
    \ auto& [y, pid] : ps_asc_y[r - 1]) mixed_asc_y.emplace_back(y, ~pid);\n     \
    \               std::inplace_merge(mixed_asc_y.begin(), mixed_asc_y.begin() +\
    \ mid_siz, mixed_asc_y.end(), comp_key);\n                    for (int t = 0;\
    \ t < siz; ++t) {\n                        const Key pkey = t ? mixed_asc_y[t\
    \ - 1] : Key{ 0, 0 }, key = mixed_asc_y[t];\n                        num_y +=\
    \ t and comp_key(pkey, key) and (pkey.second < 0) and (key.second >= 0);\n   \
    \                     const int i = key.second;\n                        (i >=\
    \ 0 ? es_comp_y[i] : ps_comp_y[~i]) = num_y;\n                    }\n        \
    \            ++num_y;\n                }\n                atcoder::fenwick_tree<T>\
    \ ft(num_y);\n                for (int j = 0, i = 2 * l; j < point_num; ++j) {\n\
    \                    const auto &[px, pid] = ps_asc_x[r - 1][j];\n           \
    \         for (; i < 2 * r; ++i) {\n                        const auto &[ex, eid]\
    \ = es_asc_x[i];\n                        if (px < ex) break;\n              \
    \          const T& w = _weights[eid >> 1];\n                        ft.add(es_comp_y[eid\
    \ & ~1], (eid & 1) ? -w : +w);\n                        ft.add(es_comp_y[eid |\
    \ 1], (eid & 1) ? +w : -w);\n                    }\n                    ans[pid]\
    \ += ft.sum(0, ps_comp_y[pid] + 1);\n                }\n                for (Key\
    \ &key : ps_asc_x[r - 1]) if (int d = _times[key.second] - r) {\n            \
    \        ps_asc_x[r + floor_pow2(d) - 1].push_back(std::move(key));\n        \
    \        }\n                ps_asc_x[r - 1].clear(), ps_asc_x[r - 1].shrink_to_fit();\n\
    \                for (Key &key : ps_asc_y[r - 1]) if (int d = _times[key.second]\
    \ - r) {\n                    ps_asc_y[r + floor_pow2(d) - 1].push_back(std::move(key));\n\
    \                }\n                ps_asc_y[r - 1].clear(), ps_asc_y[r - 1].shrink_to_fit();\n\
    \            }\n            return ans;\n        }\n    private:\n        std::vector<Rectangle>\
    \ _rects{};\n        std::vector<T> _weights{};\n        std::vector<Point> _points{};\n\
    \        std::vector<int> _times{};\n\n        static int floor_pow2(int x) {\
    \ return 1 << (31 - __builtin_clz(x)); }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_OFFLINE_RECT_ADD_POINT_GET\n#define SUISEN_OFFLINE_RECT_ADD_POINT_GET\n\
    \n#include <algorithm>\n#include <array>\n#include <numeric>\n#include <vector>\n\
    \n#include <atcoder/fenwicktree>\n\nnamespace suisen {\n    template <typename\
    \ T, typename Index = int>\n    struct OfflineRectangleAddPointGet {\n    private:\n\
    \        using Rectangle = std::array<Index, 4>;\n        using Point = std::array<Index,\
    \ 2>;\n    public:\n        void add(Index l, Index r, Index d, Index u, T w)\
    \ {\n            assert(l <= r and d <= u);\n            if (l == r or d == u)\
    \ return;\n            _rects.push_back({ l, r, d, u });\n            _weights.push_back(w);\n\
    \        }\n        void get(Index x, Index y) {\n            _points.push_back({\
    \ x, y });\n            _times.push_back(_rects.size());\n        }\n\n      \
    \  std::vector<T> solve() const {\n            std::vector<T> ans(_points.size());\n\
    \n            const int rect_num = _rects.size();\n\n            using Key = std::pair<Index,\
    \ int>;\n            constexpr auto comp_key = [](const Key &k1, const Key& k2)\
    \ { return k1.first < k2.first; };\n\n            /**\n             * [---------------------8]\n\
    \             * [---------4]............[----------12]\n             * [---2]......[---6]......[--10]........[----14]\n\
    \             * [1]...[3]...[5]...[7]...[9]...[11]....[13]....\n             *\
    \ \n             * ---------------- rectangles ----------------->\n          \
    \   */\n\n            // Event      (l,d,+w), (l,u,-w), (r,d,-w), (r,u,+w)\n \
    \           // Index(x)      2i        2i       2i+1      2i+1\n            //\
    \ Index(y)      2i       2i+1       2i       2i+1\n            std::vector<Key>\
    \ es_asc_x(2 * rect_num), es_asc_y(2 * rect_num);\n            for (int i = 0;\
    \ i < rect_num; ++i) {\n                es_asc_x[2 * i + 0] = Key{ _rects[i][0],\
    \ 2 * i + 0 }; // l\n                es_asc_x[2 * i + 1] = Key{ _rects[i][1],\
    \ 2 * i + 1 }; // r\n                es_asc_y[2 * i + 0] = Key{ _rects[i][2],\
    \ 2 * i + 0 }; // d\n                es_asc_y[2 * i + 1] = Key{ _rects[i][3],\
    \ 2 * i + 1 }; // u\n            }\n            std::vector<std::vector<Key>>\
    \ ps_asc_x(rect_num), ps_asc_y(rect_num);\n            for (int pid = 0; pid <\
    \ int(_points.size()); ++pid) if (_times[pid]) {\n                const int r\
    \ = floor_pow2(_times[pid]);\n                ps_asc_x[r - 1].emplace_back(_points[pid][0],\
    \ pid); // x\n                ps_asc_y[r - 1].emplace_back(_points[pid][1], pid);\
    \ // y\n            }\n\n            std::vector<int> ps_comp_y(_points.size()),\
    \ es_comp_y(2 * rect_num);\n\n            for (int r = 1; r <= rect_num; ++r)\
    \ {\n                const int w = -r & r, l = r - w;\n                for (int\
    \ t = 1; t < w; t <<= 1) {\n                    // Merge Sort\n              \
    \      // r=8 : {8}  -> {7,8}   -> {5,6,7,8}    -> {1,2,3,4,5,6,7,8}\n       \
    \             // r=12: {12} -> {11,12} -> {9,10,11,12}\n                    auto\
    \ it_r_x = es_asc_x.begin() + 2 * r, it_m_x = it_r_x - 2 * t, it_l_x = it_m_x\
    \ - 2 * t;\n                    std::inplace_merge(it_l_x, it_m_x, it_r_x, comp_key);\n\
    \                    auto it_r_y = es_asc_y.begin() + 2 * r, it_m_y = it_r_y -\
    \ 2 * t, it_l_y = it_m_y - 2 * t;\n                    std::inplace_merge(it_l_y,\
    \ it_m_y, it_r_y, comp_key);\n                }\n\n                const int point_num\
    \ = ps_asc_x[r - 1].size();\n                if (point_num == 0) continue;\n \
    \               if (r == (-r & r)) {\n                    std::sort(ps_asc_x[r\
    \ - 1].begin(), ps_asc_x[r - 1].end(), comp_key);\n                    std::sort(ps_asc_y[r\
    \ - 1].begin(), ps_asc_y[r - 1].end(), comp_key);\n                }\n       \
    \         int num_y = 0;\n                {\n                    std::vector<Key>\
    \ mixed_asc_y(es_asc_y.begin() + 2 * l, es_asc_y.begin() + 2 * r);\n         \
    \           const int mid_siz = mixed_asc_y.size(), siz = mid_siz + point_num;\n\
    \                    mixed_asc_y.reserve(siz);\n                    for (const\
    \ auto& [y, pid] : ps_asc_y[r - 1]) mixed_asc_y.emplace_back(y, ~pid);\n     \
    \               std::inplace_merge(mixed_asc_y.begin(), mixed_asc_y.begin() +\
    \ mid_siz, mixed_asc_y.end(), comp_key);\n                    for (int t = 0;\
    \ t < siz; ++t) {\n                        const Key pkey = t ? mixed_asc_y[t\
    \ - 1] : Key{ 0, 0 }, key = mixed_asc_y[t];\n                        num_y +=\
    \ t and comp_key(pkey, key) and (pkey.second < 0) and (key.second >= 0);\n   \
    \                     const int i = key.second;\n                        (i >=\
    \ 0 ? es_comp_y[i] : ps_comp_y[~i]) = num_y;\n                    }\n        \
    \            ++num_y;\n                }\n                atcoder::fenwick_tree<T>\
    \ ft(num_y);\n                for (int j = 0, i = 2 * l; j < point_num; ++j) {\n\
    \                    const auto &[px, pid] = ps_asc_x[r - 1][j];\n           \
    \         for (; i < 2 * r; ++i) {\n                        const auto &[ex, eid]\
    \ = es_asc_x[i];\n                        if (px < ex) break;\n              \
    \          const T& w = _weights[eid >> 1];\n                        ft.add(es_comp_y[eid\
    \ & ~1], (eid & 1) ? -w : +w);\n                        ft.add(es_comp_y[eid |\
    \ 1], (eid & 1) ? +w : -w);\n                    }\n                    ans[pid]\
    \ += ft.sum(0, ps_comp_y[pid] + 1);\n                }\n                for (Key\
    \ &key : ps_asc_x[r - 1]) if (int d = _times[key.second] - r) {\n            \
    \        ps_asc_x[r + floor_pow2(d) - 1].push_back(std::move(key));\n        \
    \        }\n                ps_asc_x[r - 1].clear(), ps_asc_x[r - 1].shrink_to_fit();\n\
    \                for (Key &key : ps_asc_y[r - 1]) if (int d = _times[key.second]\
    \ - r) {\n                    ps_asc_y[r + floor_pow2(d) - 1].push_back(std::move(key));\n\
    \                }\n                ps_asc_y[r - 1].clear(), ps_asc_y[r - 1].shrink_to_fit();\n\
    \            }\n            return ans;\n        }\n    private:\n        std::vector<Rectangle>\
    \ _rects{};\n        std::vector<T> _weights{};\n        std::vector<Point> _points{};\n\
    \        std::vector<int> _times{};\n\n        static int floor_pow2(int x) {\
    \ return 1 << (31 - __builtin_clz(x)); }\n    };\n} // namespace suisen\n\n#endif\
    \ // SUISEN_OFFLINE_RECT_ADD_POINT_GET\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp
  requiredBy: []
  timestamp: '2024-01-30 19:37:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/fenwick_tree/offline_rectangle_add_point_get/rectangle_add_point_get.test.cpp
documentation_of: library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp
layout: document
redirect_from:
- /library/library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp
- /library/library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp.html
title: library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp
---
