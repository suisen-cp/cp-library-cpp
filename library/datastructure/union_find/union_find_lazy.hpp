#ifndef SUISEN_UNION_FIND_COMPONENT_SUM
#define SUISEN_UNION_FIND_COMPONENT_SUM

#include "library/datastructure/union_find/linked_union_find.hpp"

namespace suisen {
    /**
     * @brief Union Find with lazy propagation
     * @tparam T type of sum/value: commutative monoid
     * @tparam F type of operator: (possibly non-commutative) group
     * @tparam merge_sum (T& sum_parent, T sum_child) -> void
     * @tparam neg (T x) -> -x
     * @tparam mapping (F f, T& sum, int num) -> void
     * @tparam composition (F f, F g) -> f * g
     * @tparam id () -> identity
     * @tparam inv (F f) -> f^(-1)
     */
    template <typename T, void(*merge_sum)(T&, T), T(*neg)(T), typename F, void(*mapping)(F, T&, int), F(*composition)(F, F), F(*id)(), F(*inv)(F)>
    struct UnionFindLazy : LinkedUnionFind {
        UnionFindLazy() : UnionFindLazy(0) {}
        explicit UnionFindLazy(int n, const T &init_value = T{}) : UnionFindLazy(std::vector<T>(n, init_value)) {}
        explicit UnionFindLazy(const std::vector<T> &init_values) : LinkedUnionFind(init_values.size()), _val(init_values), _sum(init_values), _laz(_n, id()) {}

        bool merge(int x, int y) {
            x = root(x), y = root(y);
            if (x == y) return false;

            UnionFind::merge(x, y);
            if (root(x) == y) std::swap(x, y);
            
            F laz = composition(inv(_laz[x]), _laz[y]);
            for (int v : connected_component(y)) {
                mapping(laz, _val[v], 1);
            }

            merge_sum(_sum[x], std::move(_sum[y]));

            std::swap(_link[x], _link[y]);
            return true;
        }

        const T& get_component(int x) {
            return _sum[root(x)];
        }
        T get_point(int x) {
            T val = _val[x];
            mapping(_laz[root(x)], val, 1);
            return val;
        }
        void apply_component(int x, const F& f) {
            x = root(x);
            mapping(f, _sum[x], size(x));
            _laz[x] = composition(f, _laz[x]);
        }
        void apply_point(int x, const F& f) {
            _apply_point(x, [&f](T& old_value) { mapping(f, old_value, 1); });
        }
        void set_point(int x, const T &new_value) {
            _apply_point(x, [&new_value](T& old_value) { old_value = new_value; });
        }

        void propagate(int x) {
            x = root(x);
            F laz = std::exchange(_laz[x], id());
            for (int v : connected_component(x)) {
                mapping(laz, _val[v], 1);
            }
        }

        T& raw_value(int x) {
            return _val[x];
        }
        const T& raw_value(int x) const {
            return _val[x];
        }
    private:
        std::vector<T> _val;
        std::vector<T> _sum;
        std::vector<F> _laz;

        template <typename Mapping>
        void _apply_point(int x, const Mapping& f) {
            int r = root(x);
            T v = get_point(x);
            merge_sum(_sum[r], neg(v));
            f(v);
            merge_sum(_sum[r], v);
            mapping(inv(_laz[r]), _val[x] = std::move(v), 1);
        }
    };
} // namespace suisen


#endif // SUISEN_UNION_FIND_COMPONENT_SUM
