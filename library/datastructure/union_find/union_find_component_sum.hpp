#ifndef SUISEN_UNION_FIND_COMPONENT_SUM
#define SUISEN_UNION_FIND_COMPONENT_SUM

#include "library/datastructure/union_find/union_find.hpp"

namespace suisen {
    template <typename T, void(*merge_data)(T&, T)>
    struct UnionFindComponentSum : UnionFind {
        UnionFindComponentSum() : UnionFindComponentSum(0) {}
        explicit UnionFindComponentSum(int n, const T &init_value = T{}) : UnionFindComponentSum(std::vector<T>(n, init_value)) {}
        explicit UnionFindComponentSum(const std::vector<T> &init_values) : UnionFind(init_values.size()), _sum(init_values) {}

        bool merge(int x, int y) {
            x = root(x), y = root(y);
            bool res = UnionFind::merge(x, y);
            if (res) {
                if (root(x) == y) std::swap(x, y);
                merge_data(_sum[x], std::move(_sum[y]));
            }
            return res;
        }
        const T& sum(int x) {
            return _sum[root(x)];
        }
    private:
        std::vector<T> _sum;
    };
} // namespace suisen


#endif // SUISEN_UNION_FIND_COMPONENT_SUM
