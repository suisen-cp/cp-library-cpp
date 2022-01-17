#ifndef SUISEN_UNION_FIND
#define SUISEN_UNION_FIND

#include <algorithm>
#include <vector>

namespace suisen {
    struct UnionFind {
        UnionFind() {}
        explicit UnionFind(int n) : n(n), data(n, -1) {}
        // Get the root of `x`. equivalent to `operator[](x)`
        int root(int x) {
            static std::vector<int> buf;
            while (data[x] >= 0) buf.push_back(x), x = data[x];
            while (buf.size()) data[buf.back()] = x, buf.pop_back();
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
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y], data[y] = x;
            return true;
        }
        // Check if `x` and `y` belongs to the same connected component.
        bool same(int x, int y) {
            return root(x) == root(y);
        }
        // Get the size of connected componet to which `x` belongs.
        int size(int x) {
            return -data[root(x)];
        }
        // Get all of connected components.
        std::vector<std::vector<int>> groups() {
            std::vector<std::vector<int>> res(n);
            for (int i = 0; i < n; ++i) res[root(i)].push_back(i);
            res.erase(std::remove_if(res.begin(), res.end(), [](const auto& g) { return g.empty(); }), res.end());
            return res;
        }
    private:
        int n;
        std::vector<int> data;
    };
} // namespace suisen

#endif // SUISEN_UNION_FIND
