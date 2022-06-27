#ifndef SUISEN_UNDO_UNION_FIND
#define SUISEN_UNDO_UNION_FIND

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace suisen {
    struct UndoUnionFind {
        UndoUnionFind() : UndoUnionFind(0) {}
        explicit UndoUnionFind(int n) : _n(n), _dat(n, -1) {}

        int root(int x) const {
            assert(x < _n);
            return _dat[x] < 0 ? x : root(_dat[x]);
        }
        int operator[](int x) const {
            return root(x);
        }
        bool merge(int x, int y) {
            x = root(x), y = root(y);
            if (x == y) return false;
            if (_dat[x] > _dat[y]) std::swap(x, y);
            _history.emplace_back(x, std::exchange(_dat[x], _dat[x] + _dat[y]));
            _history.emplace_back(y, std::exchange(_dat[y], x));
            return true;
        }
        bool same(int x, int y) const {
            return root(x) == root(y);
        }
        int size(int x) const {
            return -_dat[root(x)];
        }
        auto groups() const {
            std::vector<std::vector<int>> res(_n);
            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);
            res.erase(std::remove_if(res.begin(), res.end(), [](const auto &g) { return g.empty(); }), res.end());
            return res;
        }
        void snapshot() {
            _history.clear();
        }
        void undo() {
            assert(_history.size());
            _dat[_history.back().first] = _history.back().second, _history.pop_back();
            _dat[_history.back().first] = _history.back().second, _history.pop_back();
        }
        void rollback() {
            while (_history.size()) undo();
        }
    protected:
        int _n;
        std::vector<int> _dat;
        std::vector<std::pair<int, int>> _history;
    };
} // namespace suisen


#endif // SUISEN_UNDO_UNION_FIND
