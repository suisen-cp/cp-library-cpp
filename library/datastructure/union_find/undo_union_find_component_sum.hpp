#ifndef SUISEN_UNDO_UNION_FIND_COMPONENT_SUM
#define SUISEN_UNDO_UNION_FIND_COMPONENT_SUM

#include "library/datastructure/union_find/undo_union_find.hpp"

namespace suisen {
    template <typename T, void(*merge_data)(T&, const T&), void(*undo_data)(T&)>
    struct UndoUnionFindComponentSum : UndoUnionFind {
        UndoUnionFindComponentSum() : UndoUnionFindComponentSum(0) {}
        explicit UndoUnionFindComponentSum(int n, const T &init_value = T{}) : UndoUnionFindComponentSum(std::vector<T>(n, init_value)) {}
        explicit UndoUnionFindComponentSum(const std::vector<T> &init_values) : UndoUnionFind(init_values.size()), _sum(init_values) {}

        bool merge(int x, int y) {
            x = root(x), y = root(y);
            if (x == y) return false;
            if (_dat[x] > _dat[y]) std::swap(x, y);
            _history.emplace_back(x, std::exchange(_dat[x], _dat[x] + _dat[y]));
            _history.emplace_back(y, std::exchange(_dat[y], x));
            merge_data(_sum[x], _sum[y]);
            return true;
        }
        void snapshot() {
            _history.clear();
        }
        void undo() {
            assert(_history.size());
            _dat[_history.back().first] = _history.back().second, _history.pop_back();
            undo_data(_sum[_history.back().first]);
            _dat[_history.back().first] = _history.back().second, _history.pop_back();
        }
        void rollback() {
            while (_history.size()) undo();
        }
        const T& sum(int x) const {
            return _sum[root(x)];
        }
        T& sum(int x) {
            return _sum[root(x)];
        }
    protected:
        std::vector<T> _sum;
    };
} // namespace suisen


#endif // SUISEN_UNDO_UNION_FIND_COMPONENT_SUM
