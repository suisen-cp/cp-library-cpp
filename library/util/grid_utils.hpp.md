---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/grid_utils.hpp\"\n#include <utility>\n#include\
    \ <vector>\n\n// l <= x < r\ntemplate <typename T>\nconstexpr inline bool in_range(const\
    \ T &x, const T &l, const T &r) {\n    return l <= x and x < r;\n}\n// 0 <= x\
    \ < r\ntemplate <typename T>\nconstexpr inline bool in_range(const T &x, const\
    \ T &r) {\n    return (std::make_unsigned_t<T>) x < (std::make_unsigned_t<T>)\
    \ r;\n}\n// not (l <= x < r)\ntemplate <typename T>\nconstexpr inline bool out_range(const\
    \ T &x, const T &l, const T &r) {\n    return x < l or r <= x;\n}\n// not (0 <=\
    \ x < r)\ntemplate <typename T>\nconstexpr inline bool out_range(const T &x, const\
    \ T &r) {\n    return (std::make_unsigned_t<T>) x >= (std::make_unsigned_t<T>)\
    \ r;\n}\n\nconstexpr int dx4[4] = {1, 0, -1, 0};\nconstexpr int dy4[4] = {0, 1,\
    \ 0, -1};\nconstexpr int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1};\nconstexpr int\
    \ dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};\n\nconstexpr std::pair<int, int> dxy4[4]\
    \ = {\n    { dx4[0], dy4[0] }, { dx4[1], dy4[1] }, { dx4[2], dy4[2] }, { dx4[3],\
    \ dy4[3] },\n};\nconstexpr std::pair<int, int> dxy8[8] = {\n    { dx8[0], dy8[0]\
    \ }, { dx8[1], dy8[1] }, { dx8[2], dy8[2] }, { dx8[3], dy8[3] },\n    { dx8[4],\
    \ dy8[4] }, { dx8[5], dy8[5] }, { dx8[6], dy8[6] }, { dx8[7], dy8[7] },\n};\n\n\
    template <int D, auto dx, auto dy>\nstruct AdjacentCells {\n    struct Iterator\
    \ {\n        const int x, y;\n        int d;\n        bool operator!=(std::nullptr_t)\
    \ { return d != D; }\n        void operator++() { ++d; }\n        std::pair<int,\
    \ int> operator*() { return { x + dx[d], y + dy[d] }; }\n    };\n    const int\
    \ x, y;\n    AdjacentCells(int x, int y) : x(x), y(y) {}\n    auto begin() { return\
    \ Iterator { x, y, 0 }; }\n    constexpr std::nullptr_t end() { return nullptr;\
    \ }\n    operator std::vector<std::pair<int, int>>() {\n        std::vector<std::pair<int,\
    \ int>> res;\n        for (const auto &p : *this) res.push_back(p);\n        return\
    \ res;\n    }\n};\n\ntemplate <int D, auto dx, auto dy>\nstruct AdjacentCellsBounded\
    \ {\n    struct Iterator {\n        const int x, y, xl, xr, yl, yr;\n        int\
    \ d;\n        bool operator!=(std::nullptr_t) {\n            for (; d != D; ++d)\
    \ if (in_range(x + dx[d], xl, xr) and in_range(y + dy[d], yl, yr)) return true;\n\
    \            return false;\n        }\n        void operator++() { ++d; }\n  \
    \      std::pair<int, int> operator*() { return { x + dx[d], y + dy[d] }; }\n\
    \    };\n    const int x, y, xl, xr, yl, yr;\n    AdjacentCellsBounded(int x,\
    \ int y, int xl, int xr, int yl, int yr) : x(x), y(y), xl(xl), xr(xr), yl(yl),\
    \ yr(yr) {}\n    AdjacentCellsBounded(int x, int y, int xr, int yr) : AdjacentCellsBounded(x,\
    \ y, 0, xr, 0, yr) {}\n    auto begin() { return Iterator { x, y, xl, xr, yl,\
    \ yr, 0 }; }\n    constexpr std::nullptr_t end() { return nullptr; }\n    operator\
    \ std::vector<std::pair<int, int>>() {\n        std::vector<std::pair<int, int>>\
    \ res;\n        for (const auto &p : *this) res.push_back(p);\n        return\
    \ res;\n    }\n};\n\n// [ {x+dx4[i], y+dy4[i]} for i in range(4) ]\nusing AdjacentFourCells\
    \ = AdjacentCells<4, dx4, dy4>;\n// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4)\
    \ if xl<=nx<xr and yl<=ny<yr ]\nusing AdjacentFourCellsBounded = AdjacentCellsBounded<4,\
    \ dx4, dy4>;\n\n// [ {x+dx8[i], y+dy8[i]} for i in range(8) ]\nusing AdjacentEightCells\
    \ = AdjacentCells<8, dx8, dy8>;\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8)\
    \ if xl<=nx<xr and yl<=ny<yr ]\nusing AdjacentEightCellsBounded = AdjacentCellsBounded<8,\
    \ dx8, dy8>;\n\n// [ {x+dx4[i], y+dy4[i]} for i in range(4) ]\nauto adjacent_four_cells(int\
    \ x, int y) { return AdjacentFourCells { x, y }; }\n// [ {nx:=x+dx4[i], ny:=y+dy4[i]}\
    \ for i in range(4) if xl<=nx<xr and yl<=ny<yr ]\nauto adjacent_four_cells(int\
    \ x, int y, int xl, int xr, int yl, int yr) { return AdjacentFourCellsBounded\
    \ { x, y, xl, xr, yl, yr }; }\n// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4)\
    \ if 0 <=nx<xr and 0 <=ny<yr ]\nauto adjacent_four_cells(int x, int y,       \
    \  int xr,         int yr) { return AdjacentFourCellsBounded { x, y, 0 , xr, 0\
    \ , yr }; }\n\n// [ {x+dx8[i], y+dy8[i]} for i in range(8) ]\nauto adjacent_eight_cells(int\
    \ x, int y) { return AdjacentEightCells { x, y }; }\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]}\
    \ for i in range(8) if xl<=nx<xr and yl<=ny<yr ]\nauto adjacent_eight_cells(int\
    \ x, int y, int xl, int xr, int yl, int yr) { return AdjacentEightCellsBounded\
    \ { x, y, xl, xr, yl, yr }; }\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8)\
    \ if 0 <=nx<xr and 0 <=ny<yr ]\nauto adjacent_eight_cells(int x, int y,      \
    \   int xr,         int yr) { return AdjacentEightCellsBounded { x, y, 0 , xr,\
    \ 0 , yr }; }\n"
  code: "#include <utility>\n#include <vector>\n\n// l <= x < r\ntemplate <typename\
    \ T>\nconstexpr inline bool in_range(const T &x, const T &l, const T &r) {\n \
    \   return l <= x and x < r;\n}\n// 0 <= x < r\ntemplate <typename T>\nconstexpr\
    \ inline bool in_range(const T &x, const T &r) {\n    return (std::make_unsigned_t<T>)\
    \ x < (std::make_unsigned_t<T>) r;\n}\n// not (l <= x < r)\ntemplate <typename\
    \ T>\nconstexpr inline bool out_range(const T &x, const T &l, const T &r) {\n\
    \    return x < l or r <= x;\n}\n// not (0 <= x < r)\ntemplate <typename T>\n\
    constexpr inline bool out_range(const T &x, const T &r) {\n    return (std::make_unsigned_t<T>)\
    \ x >= (std::make_unsigned_t<T>) r;\n}\n\nconstexpr int dx4[4] = {1, 0, -1, 0};\n\
    constexpr int dy4[4] = {0, 1, 0, -1};\nconstexpr int dx8[8] = {1, 1, 0, -1, -1,\
    \ -1, 0, 1};\nconstexpr int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};\n\nconstexpr\
    \ std::pair<int, int> dxy4[4] = {\n    { dx4[0], dy4[0] }, { dx4[1], dy4[1] },\
    \ { dx4[2], dy4[2] }, { dx4[3], dy4[3] },\n};\nconstexpr std::pair<int, int> dxy8[8]\
    \ = {\n    { dx8[0], dy8[0] }, { dx8[1], dy8[1] }, { dx8[2], dy8[2] }, { dx8[3],\
    \ dy8[3] },\n    { dx8[4], dy8[4] }, { dx8[5], dy8[5] }, { dx8[6], dy8[6] }, {\
    \ dx8[7], dy8[7] },\n};\n\ntemplate <int D, auto dx, auto dy>\nstruct AdjacentCells\
    \ {\n    struct Iterator {\n        const int x, y;\n        int d;\n        bool\
    \ operator!=(std::nullptr_t) { return d != D; }\n        void operator++() { ++d;\
    \ }\n        std::pair<int, int> operator*() { return { x + dx[d], y + dy[d] };\
    \ }\n    };\n    const int x, y;\n    AdjacentCells(int x, int y) : x(x), y(y)\
    \ {}\n    auto begin() { return Iterator { x, y, 0 }; }\n    constexpr std::nullptr_t\
    \ end() { return nullptr; }\n    operator std::vector<std::pair<int, int>>() {\n\
    \        std::vector<std::pair<int, int>> res;\n        for (const auto &p : *this)\
    \ res.push_back(p);\n        return res;\n    }\n};\n\ntemplate <int D, auto dx,\
    \ auto dy>\nstruct AdjacentCellsBounded {\n    struct Iterator {\n        const\
    \ int x, y, xl, xr, yl, yr;\n        int d;\n        bool operator!=(std::nullptr_t)\
    \ {\n            for (; d != D; ++d) if (in_range(x + dx[d], xl, xr) and in_range(y\
    \ + dy[d], yl, yr)) return true;\n            return false;\n        }\n     \
    \   void operator++() { ++d; }\n        std::pair<int, int> operator*() { return\
    \ { x + dx[d], y + dy[d] }; }\n    };\n    const int x, y, xl, xr, yl, yr;\n \
    \   AdjacentCellsBounded(int x, int y, int xl, int xr, int yl, int yr) : x(x),\
    \ y(y), xl(xl), xr(xr), yl(yl), yr(yr) {}\n    AdjacentCellsBounded(int x, int\
    \ y, int xr, int yr) : AdjacentCellsBounded(x, y, 0, xr, 0, yr) {}\n    auto begin()\
    \ { return Iterator { x, y, xl, xr, yl, yr, 0 }; }\n    constexpr std::nullptr_t\
    \ end() { return nullptr; }\n    operator std::vector<std::pair<int, int>>() {\n\
    \        std::vector<std::pair<int, int>> res;\n        for (const auto &p : *this)\
    \ res.push_back(p);\n        return res;\n    }\n};\n\n// [ {x+dx4[i], y+dy4[i]}\
    \ for i in range(4) ]\nusing AdjacentFourCells = AdjacentCells<4, dx4, dy4>;\n\
    // [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4) if xl<=nx<xr and yl<=ny<yr\
    \ ]\nusing AdjacentFourCellsBounded = AdjacentCellsBounded<4, dx4, dy4>;\n\n//\
    \ [ {x+dx8[i], y+dy8[i]} for i in range(8) ]\nusing AdjacentEightCells = AdjacentCells<8,\
    \ dx8, dy8>;\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8) if xl<=nx<xr\
    \ and yl<=ny<yr ]\nusing AdjacentEightCellsBounded = AdjacentCellsBounded<8, dx8,\
    \ dy8>;\n\n// [ {x+dx4[i], y+dy4[i]} for i in range(4) ]\nauto adjacent_four_cells(int\
    \ x, int y) { return AdjacentFourCells { x, y }; }\n// [ {nx:=x+dx4[i], ny:=y+dy4[i]}\
    \ for i in range(4) if xl<=nx<xr and yl<=ny<yr ]\nauto adjacent_four_cells(int\
    \ x, int y, int xl, int xr, int yl, int yr) { return AdjacentFourCellsBounded\
    \ { x, y, xl, xr, yl, yr }; }\n// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4)\
    \ if 0 <=nx<xr and 0 <=ny<yr ]\nauto adjacent_four_cells(int x, int y,       \
    \  int xr,         int yr) { return AdjacentFourCellsBounded { x, y, 0 , xr, 0\
    \ , yr }; }\n\n// [ {x+dx8[i], y+dy8[i]} for i in range(8) ]\nauto adjacent_eight_cells(int\
    \ x, int y) { return AdjacentEightCells { x, y }; }\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]}\
    \ for i in range(8) if xl<=nx<xr and yl<=ny<yr ]\nauto adjacent_eight_cells(int\
    \ x, int y, int xl, int xr, int yl, int yr) { return AdjacentEightCellsBounded\
    \ { x, y, xl, xr, yl, yr }; }\n// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8)\
    \ if 0 <=nx<xr and 0 <=ny<yr ]\nauto adjacent_eight_cells(int x, int y,      \
    \   int xr,         int yr) { return AdjacentEightCellsBounded { x, y, 0 , xr,\
    \ 0 , yr }; }\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/grid_utils.hpp
  requiredBy: []
  timestamp: '2021-08-09 15:18:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/grid_utils.hpp
layout: document
title: Grid Utils
---
## Grid Utils