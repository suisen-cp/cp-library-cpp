#ifndef SUISEN_RECTANGLE_ADD_RECTANGLE_SUM
#define SUISEN_RECTANGLE_ADD_RECTANGLE_SUM

#include "library/util/tuple_ops.hpp"
#include "library/datastructure/fenwick_tree_2d_sparse.hpp"

namespace suisen {
    template <typename T>
    struct RectangleAddRectangleSum {
        using value_type = T;
        using data_type = std::tuple<value_type, value_type, value_type, value_type>;

        RectangleAddRectangleSum() = default;
        explicit RectangleAddRectangleSum(int xnum) : _seg(xnum) {}

        void register_add_query_rectangle(int l, int r, int d, int u) {
            _seg.add_point(l, d), _seg.add_point(r, d);
            _seg.add_point(l, u), _seg.add_point(r, u);
        }
        void build() {
            _seg.build();
        }

        void add(int l, int r, int d, int u, const value_type& val) {
            add(l, d, val), add(r, d, -val);
            add(l, u, -val), add(r, u, val);
        }

        value_type sum(int l, int r, int d, int u) const {
            return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);
        }

    private:
        static constexpr data_type op_data(data_type x, data_type y) { return x + y; }
        static constexpr data_type e_data() { return data_type{}; }

        FenwickTree2DSparse<data_type> _seg;

        void add(int l, int d, const value_type& v) {
            // v(x - l)(y - d) = v xy - vd x - vl y + vld
            _seg.add(l, d, data_type{ v, -v * d, -v * l, v * l * d });
        }

        value_type sum(int r, int u) const {
            static constexpr int inf = std::numeric_limits<int>::max();
            auto [a, b, c, d] = _seg.sum(-inf, r, -inf, u);
            return a * r * u + b * r + c * u + d;
        }
    };
} // namespace suisen

#endif // SUISEN_RECTANGLE_ADD_RECTANGLE_SUM
