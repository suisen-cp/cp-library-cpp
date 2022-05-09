#ifndef SUISEN_FENWICK_TREE_2D
#define SUISEN_FENWICK_TREE_2D

#include <vector>

namespace suisen {

    template <typename T>
    class FenwickTree2D {
    public:
        FenwickTree2D() {}
        explicit FenwickTree2D(int n, int m) : n(n), m(m), data(n, std::vector<T>(m, T{})) {}
        void add(int i, int j, T v) {
            for (int x = i + 1; x <= n; x += (x & -x)) for (int y = j + 1; y <= m; y += (y & -y)) {
                data[x - 1][y - 1] += v;
            }
        }
        T sum(int xl, int xr, int yl, int yr) const {
            return sum(xr, yr) - sum(xl, yr) - sum(xr, yl) + sum(xl, yl);
        }
        auto operator[](std::pair<int, int> index) {
            auto [i, j] = index;
            struct {
                int i, j;
                FenwickTree2D& ft;
                operator T() const { return ft.sum(i, i + 1, j, j + 1); }
                auto& operator++() { return *this += 1; }
                auto& operator--() { return *this -= 1; }
                auto& operator+=(T val) { ft.add(i, j, val); return *this; }
                auto& operator-=(T val) { ft.add(i, j, -val); return *this; }
                auto& operator*=(T val) { T cur = *this; ft.add(i, j, cur * val - cur); return *this; }
                auto& operator/=(T val) { T cur = *this; ft.add(i, j, cur / val - cur); return *this; }
                auto& operator%=(T val) { T cur = *this; ft.add(i, j, cur % val - cur); return *this; }
                auto& operator =(T val) { T cur = *this; ft.add(i, j, val - cur); return *this; }
            } obj{ i, j, *this };
            return obj;
        }
        T operator()(int xl, int xr, int yl, int yr) const { return sum(xl, xr, yl, yr); }

    private:
        int n, m;
        std::vector<std::vector<T>> data;

        T sum(int xr, int yr) const {
            T s{};
            for (int x = xr; x; x -= x & -x) for (int y = yr; y; y -= y & -y) {
                s += data[x - 1][y - 1];
            }
            return s;
        }
    };

} // namespace suisen

#endif // SUISEN_FENWICK_TREE_2D
