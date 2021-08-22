#ifndef SUISEN_SEGMENT_TREE_2D
#define SUISEN_SEGMENT_TREE_2D

#include <algorithm>
#include <tuple>

#include "library/datastructure/segment_tree.hpp"

namespace suisen {

template <typename T, typename F, constraints_t<is_bin_op<F, T>> = nullptr>
class SegmentTree2D {
    public:
        SegmentTree2D() {}
        SegmentTree2D(int x_num, const T &e, const F &op) : n(x_num + 1), m(ceil_pow2(n)), data(m * 2), e(e), op(op), points(), pos_x(), pos_y(m * 2) {}

        void add_point(int x, int y) {
            built = false;
            pos_x.push_back(x);
            points.emplace_back(x, y);
        }

        void build() {
            built = true;
            pos_x.push_back(std::numeric_limits<int>::max());
            std::sort(pos_x.begin(), pos_x.end());
            pos_x.erase(std::unique(pos_x.begin(), pos_x.end()), pos_x.end());
            assert(int(pos_x.size()) <= n);
            for (auto [x, y] : points) {
                for (int k = comp_x(x) + m; k; k >>= 1) pos_y[k].push_back(y);
            }
            for (int k = 1; k < 2 * m; ++k) {
                pos_y[k].push_back(std::numeric_limits<int>::max());
                std::sort(pos_y[k].begin(), pos_y[k].end());
                pos_y[k].erase(std::unique(pos_y[k].begin(), pos_y[k].end()), pos_y[k].end());
                data[k] = SegmentTree(pos_y[k].size(), e, op);
            }
        }

        T prod(int l, int r, int d, int u) const {
            return (*this)(l, r, d, u);
        }
        T operator()(int l, int r, int d, int u) const {
            assert(built);
            T res_l = e, res_r = e;
            for (l = comp_x(l) + m, r = comp_x(r) + m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res_l = op(res_l, prod(l++, d, u));
                if (r & 1) res_r = op(prod(--r, d, u), res_r);
            }
            return op(res_l, res_r);
        }
        T all_prod() const {
            assert(built);
            return data[1].all_prod();
        }

        const T& get(int x, int y) const {
            assert(built);
            int i = comp_x(x), j = comp_y(i + m, y);
            assert(pos_x[i] == x);
            assert(pos_y[i + m][j] == y);
            return data[i + m].get(j);
        }
        void set(int x, int y, T val) {
            (*this)[{x, y}] = val;
        }
        auto operator[](const std::pair<int, int> &p) {
            int x, y;
            std::tie(x, y) = p;
            return UpdateProxyObject { const_cast<T&>(get(x, y)), [this, k = comp_x(x) + m, y]{ update_from(k, y); } };
        }

    private:
        int n, m;
        std::vector<SegmentTree<T, F>> data;
        T e;
        F op;
        std::vector<std::pair<int, int>> points;
        std::vector<int> pos_x;
        std::vector<std::vector<int>> pos_y;
        bool built = true;

        static constexpr int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }

        int comp_x(int x) const {
            return std::lower_bound(pos_x.begin(), pos_x.end(), x) - pos_x.begin();
        }
        int comp_y(int k, int y) const {
            return std::lower_bound(pos_y[k].begin(), pos_y[k].end(), y) - pos_y[k].begin();
        }

        T prod(int k, int d, int u) const {
            return data[k](comp_y(k, d), comp_y(k, u));
        }

        void update(int k, int y) {
            int p = comp_y(k, y);
            assert(pos_y[k][p] == y);
            if (k < m) {
                int l = comp_y(k * 2, y), r = comp_y(k * 2 + 1, y);
                const T& lv = pos_y[k * 2 + 0][l] == y ? data[k * 2 + 0].get(l) : e;
                const T& rv = pos_y[k * 2 + 1][r] == y ? data[k * 2 + 1].get(r) : e;
                data[k][p] = op(lv, rv);
            } else {
                data[k][p] = T(data[k][p]);
            }
        }
        void update_from(int k, int y) {
            for (; k; k >>= 1) update(k, y);
        }
};

} // namespace suisen


#endif // SUISEN_SEGMENT_TREE_2D
