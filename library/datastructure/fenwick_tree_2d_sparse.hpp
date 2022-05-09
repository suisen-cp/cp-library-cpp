#ifndef SUISEN_SEGMENT_TREE_2D_SPARSE
#define SUISEN_SEGMENT_TREE_2D_SPARSE

#include <algorithm>
#include <cassert>
#include <tuple>

#include "library/datastructure/fenwick_tree.hpp"

namespace suisen {

    template <typename T>
    class FenwickTree2DSparse {
    public:
        FenwickTree2DSparse() {}
        explicit FenwickTree2DSparse(int x_num) : n(x_num + 1), data(n), points(), pos_x(), pos_y(n) {}

        void add_point(int x, int y) {
            built = false;
            pos_x.push_back(x);
            points.emplace_back(x, y);
        }

        void build() {
            static constexpr int inf = std::numeric_limits<int>::max();
            built = true;
            pos_x.push_back(inf);
            std::sort(pos_x.begin(), pos_x.end());
            pos_x.erase(std::unique(pos_x.begin(), pos_x.end()), pos_x.end());
            assert(int(pos_x.size()) <= n);
            for (const auto& [x, y] : points) for (int k = comp_x(x) + 1; k <= n; k += k & -k) {
                pos_y[k - 1].push_back(y);
            }
            for (int k = 0; k < n; ++k) {
                pos_y[k].push_back(inf);
                std::sort(pos_y[k].begin(), pos_y[k].end());
                pos_y[k].erase(std::unique(pos_y[k].begin(), pos_y[k].end()), pos_y[k].end());
                data[k] = FenwickTree<T>(pos_y[k].size());
            }
        }

        T sum(int l, int r, int d, int u) const {
            return (*this)(l, r, d, u);
        }
        T operator()(int l, int r, int d, int u) const {
            assert(built);
            return sum(r, d, u) - sum(l, d, u);
        }

        T get(int x, int y) const {
            return (*this)(x, x + 1, y, y + 1);
        }
        void add(int x, int y, const T& val) {
            for (int k = comp_x(x) + 1; k <= n; k += k & -k) data[k - 1].add(comp_y(k - 1, y), val);
        }
        template <typename F>
        void apply(int x, int y, F &&f) {
            T old_val = get(x, y);
            add(x, y, f(old_val) - old_val);
        }
        void set(int x, int y, const T &val) {
            apply(x, y, [&](const T&) { return val; });
        }

    private:
        int n, m;
        std::vector<FenwickTree<T>> data;
        std::vector<std::pair<int, int>> points;
        std::vector<int> pos_x;
        std::vector<std::vector<int>> pos_y;
        bool built = true;

        int comp_x(int x) const {
            return std::lower_bound(pos_x.begin(), pos_x.end(), x) - pos_x.begin();
        }
        int comp_y(int k, int y) const {
            return std::lower_bound(pos_y[k].begin(), pos_y[k].end(), y) - pos_y[k].begin();
        }

        T sum(int r, int d, int u) const {
            T res{};
            for (r = comp_x(r); r; r -= r & -r) res += data[r - 1].sum(comp_y(r - 1, d), comp_y(r - 1, u));
            return res;
        }
    };
} // namespace suisen


#endif // SUISEN_SEGMENT_TREE_2D_SPARSE
