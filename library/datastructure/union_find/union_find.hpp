#ifndef SUISEN_UNION_FIND
#define SUISEN_UNION_FIND

#include <algorithm>
#include <vector>

namespace suisen {
    struct UnionFind {
        UnionFind() {}
        explicit UnionFind(int _n) : _n(_n), _dat(_n, -1) {}
        // Get the root of `x`. equivalent to `operator[](x)`
        int root(int x) {
            static std::vector<int> buf;
            while (_dat[x] >= 0) buf.push_back(x), x = _dat[x];
            while (buf.size()) _dat[buf.back()] = x, buf.pop_back();
            return x;
        }
        // Get the root of `x`. euivalent to `root(x)`
        int operator[](int x) {
            return root(x);
        }
        // Merge two vertices `x` and `y`.
        bool merge(int x, int y) {
            x = root(x), y = root(y);
            if (x == y) return false;
            if (_dat[x] > _dat[y]) std::swap(x, y);
            _dat[x] += _dat[y], _dat[y] = x;
            return true;
        }
        // Check if `x` and `y` belongs to the same connected component.
        bool same(int x, int y) {
            return root(x) == root(y);
        }
        // Get the size of connected componet to which `x` belongs.
        int size(int x) {
            return -_dat[root(x)];
        }
        // Get all of connected components.
        std::vector<std::vector<int>> groups() {
            std::vector<std::vector<int>> res(_n);
            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);
            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g) { return g.empty(); }), res.end());
            return res;
        }
    protected:
        int _n;
        std::vector<int> _dat;
    };
} // namespace suisen

#endif // SUISEN_UNION_FIND
