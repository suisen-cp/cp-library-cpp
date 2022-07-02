#ifndef SUISEN_PERSISTENT_UNION_FIND
#define SUISEN_PERSISTENT_UNION_FIND

#include <algorithm>
#include <utility>

#include "library/datastructure/persistent_array.hpp"

namespace suisen {
    struct PersistentUnionFind {
        using array_type = PersistentArray<int, 4>;

        PersistentUnionFind() {}
        explicit PersistentUnionFind(int n) : _n(n), _dat(_n, -1) {}

        static void init_pool(int capacity) {
            array_type::init_pool(capacity);
        }

        // Get the root of `x`. equivalent to `operator[](x)`
        int root(int x) {
            static std::vector<int> buf;
            while (true) {
                if (int r = _dat.get(x); r >= 0) buf.push_back(std::exchange(x, r));
                else break;
            }
            while (buf.size()) _dat.mut_set(buf.back(), x), buf.pop_back();
            return x;
        }
        // Get the root of `x`. euivalent to `root(x)`
        int operator[](int x) {
            return root(x);
        }
        // Merge two vertices `x` and `y`.
        std::pair<PersistentUnionFind, bool> merge(int x, int y) {
            x = root(x), y = root(y);
            if (x == y) return { *this, false };
            int vx = _dat.get(x), vy = _dat.get(y);
            if (vx > vy) std::swap(x, y), std::swap(vx, vy);
            array_type new_dat = _dat;
            new_dat = new_dat.set(x, vx + vy);
            new_dat = new_dat.set(y, x);
            return { PersistentUnionFind(new_dat), true };
        }
        // Check if `x` and `y` belongs to the same connected component.
        bool same(int x, int y) {
            return root(x) == root(y);
        }
        // Get the size of connected componet to which `x` belongs.
        int size(int x) {
            return -_dat.get(root(x));
        }
        // Get all of connected components.
        std::vector<std::vector<int>> groups() {
            std::vector<std::vector<int>> res(_n);
            for (int i = 0; i < _n; ++i) res[root(i)].push_back(i);
            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g) { return g.empty(); }), res.end());
            return res;
        }
        std::vector<int> dump() {
            return _dat.dump();
        }
    protected:
        int _n;
        array_type _dat;

        explicit PersistentUnionFind(array_type dat) : _n(dat.size()), _dat(dat) {}
    };
} // namespace suisen


#endif // SUISEN_PERSISTENT_UNION_FIND
