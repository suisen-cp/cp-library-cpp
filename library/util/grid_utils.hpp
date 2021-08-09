#include <utility>
#include <vector>

// l <= x < r
template <typename T>
constexpr inline bool in_range(const T &x, const T &l, const T &r) {
    return l <= x and x < r;
}
// 0 <= x < r
template <typename T>
constexpr inline bool in_range(const T &x, const T &r) {
    return (std::make_unsigned_t<T>) x < (std::make_unsigned_t<T>) r;
}
// not (l <= x < r)
template <typename T>
constexpr inline bool out_range(const T &x, const T &l, const T &r) {
    return x < l or r <= x;
}
// not (0 <= x < r)
template <typename T>
constexpr inline bool out_range(const T &x, const T &r) {
    return (std::make_unsigned_t<T>) x >= (std::make_unsigned_t<T>) r;
}

constexpr int dx4[4] = {1, 0, -1, 0};
constexpr int dy4[4] = {0, 1, 0, -1};
constexpr int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

constexpr std::pair<int, int> dxy4[4] = {
    { dx4[0], dy4[0] }, { dx4[1], dy4[1] }, { dx4[2], dy4[2] }, { dx4[3], dy4[3] },
};
constexpr std::pair<int, int> dxy8[8] = {
    { dx8[0], dy8[0] }, { dx8[1], dy8[1] }, { dx8[2], dy8[2] }, { dx8[3], dy8[3] },
    { dx8[4], dy8[4] }, { dx8[5], dy8[5] }, { dx8[6], dy8[6] }, { dx8[7], dy8[7] },
};

template <int D, auto dx, auto dy>
struct AdjacentCells {
    struct Iterator {
        const int x, y;
        int d;
        bool operator!=(std::nullptr_t) { return d != D; }
        void operator++() { ++d; }
        std::pair<int, int> operator*() { return { x + dx[d], y + dy[d] }; }
    };
    const int x, y;
    AdjacentCells(int x, int y) : x(x), y(y) {}
    auto begin() { return Iterator { x, y, 0 }; }
    constexpr std::nullptr_t end() { return nullptr; }
    operator std::vector<std::pair<int, int>>() {
        std::vector<std::pair<int, int>> res;
        for (const auto &p : *this) res.push_back(p);
        return res;
    }
};

template <int D, auto dx, auto dy>
struct AdjacentCellsBounded {
    struct Iterator {
        const int x, y, xl, xr, yl, yr;
        int d;
        bool operator!=(std::nullptr_t) {
            for (; d != D; ++d) if (in_range(x + dx[d], xl, xr) and in_range(y + dy[d], yl, yr)) return true;
            return false;
        }
        void operator++() { ++d; }
        std::pair<int, int> operator*() { return { x + dx[d], y + dy[d] }; }
    };
    const int x, y, xl, xr, yl, yr;
    AdjacentCellsBounded(int x, int y, int xl, int xr, int yl, int yr) : x(x), y(y), xl(xl), xr(xr), yl(yl), yr(yr) {}
    AdjacentCellsBounded(int x, int y, int xr, int yr) : AdjacentCellsBounded(x, y, 0, xr, 0, yr) {}
    auto begin() { return Iterator { x, y, xl, xr, yl, yr, 0 }; }
    constexpr std::nullptr_t end() { return nullptr; }
    operator std::vector<std::pair<int, int>>() {
        std::vector<std::pair<int, int>> res;
        for (const auto &p : *this) res.push_back(p);
        return res;
    }
};

// [ {x+dx4[i], y+dy4[i]} for i in range(4) ]
using AdjacentFourCells = AdjacentCells<4, dx4, dy4>;
// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4) if xl<=nx<xr and yl<=ny<yr ]
using AdjacentFourCellsBounded = AdjacentCellsBounded<4, dx4, dy4>;

// [ {x+dx8[i], y+dy8[i]} for i in range(8) ]
using AdjacentEightCells = AdjacentCells<8, dx8, dy8>;
// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8) if xl<=nx<xr and yl<=ny<yr ]
using AdjacentEightCellsBounded = AdjacentCellsBounded<8, dx8, dy8>;

// [ {x+dx4[i], y+dy4[i]} for i in range(4) ]
auto adjacent_four_cells(int x, int y) { return AdjacentFourCells { x, y }; }
// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4) if xl<=nx<xr and yl<=ny<yr ]
auto adjacent_four_cells(int x, int y, int xl, int xr, int yl, int yr) { return AdjacentFourCellsBounded { x, y, xl, xr, yl, yr }; }
// [ {nx:=x+dx4[i], ny:=y+dy4[i]} for i in range(4) if 0 <=nx<xr and 0 <=ny<yr ]
auto adjacent_four_cells(int x, int y,         int xr,         int yr) { return AdjacentFourCellsBounded { x, y, 0 , xr, 0 , yr }; }

// [ {x+dx8[i], y+dy8[i]} for i in range(8) ]
auto adjacent_eight_cells(int x, int y) { return AdjacentEightCells { x, y }; }
// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8) if xl<=nx<xr and yl<=ny<yr ]
auto adjacent_eight_cells(int x, int y, int xl, int xr, int yl, int yr) { return AdjacentEightCellsBounded { x, y, xl, xr, yl, yr }; }
// [ {nx:=x+dx8[i], ny:=y+dy8[i]} for i in range(8) if 0 <=nx<xr and 0 <=ny<yr ]
auto adjacent_eight_cells(int x, int y,         int xr,         int yr) { return AdjacentEightCellsBounded { x, y, 0 , xr, 0 , yr }; }
