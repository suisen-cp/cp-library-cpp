#ifndef SUISEN_WEIGHTED_UNION_FIND
#define SUISEN_WEIGHTED_UNION_FIND

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {

// reference: https://noshi91.hatenablog.com/entry/2018/05/30/191943

template <
    typename T, typename Op = std::plus<T>, typename Inv = std::negate<T>,
    constraints_t<is_uni_op<Inv, T>, is_bin_op<Op, T>> = nullptr
>
class WeightedUnionFind {
    public:
        WeightedUnionFind() {}
        explicit WeightedUnionFind(int n, const T &e = T(0)) : n(n), par(n), siz(n, 1), e(e), value(n, e) {
            std::iota(par.begin(), par.end(), 0);
        }
        WeightedUnionFind(int n, const T &e, Op op, Inv inv) : n(n), par(n), siz(n, 1), e(e), value(n, e), op(op), inv(inv) {
            std::iota(par.begin(), par.end(), 0);
        }
        // Get the root of `x`. equivalent to `operator[](x)`
        int root(int x) {
            while (par[x] != x) {
                int &p = par[x];
                value[x] = op(value[p], value[x]);
                x = p = par[p];
            }
            return x;
        }
        // Get the root of `x`. euivalent to `root(x)`
        int operator[](int x) {
            return root(x);
        }
        // Merge two vertices `x` and `y` with the distance d = y - x.
        bool merge(int x, int y, const T &d) {
            /**
             *   [root(x)] ----> [root(y)]  
             *       |     ??=rd     |      
             *  w(x) |               | w(y) 
             *       v               v      
             *      [x] ----------> [y]     
             *               d              
             */
            T rd = op(op(weight(x), d), inv(weight(y)));
            x = root(x), y = root(y);
            if (x == y) return false;
            if (siz[x] < siz[y]) {
                std::swap(x, y);
                rd = inv(std::move(rd));
            }
            siz[x] += siz[y], par[y] = x;
            value[y] = std::move(rd);
            return true;
        }
        // Return the distance d = y - x.
        T diff(int x, int y) {
            assert(same(x, y));
            return op(inv(weight(x)), weight(y));
        }
        // Check if `x` and `y` belongs to the same connected component.
        bool same(int x, int y) {
            return root(x) == root(y);
        }
        // Get the size of connected componet to which `x` belongs.
        int size(int x) {
            return siz[root(x)];
        }
        // Get all of connected components.
        std::vector<std::vector<int>> groups() {
            std::vector<std::vector<int>> res(n);
            for (int i = 0; i < n; ++i) res[root(i)].push_back(i);
            res.erase(std::remove_if(res.begin(), res.end(), [](const auto &g) { return g.empty(); }), res.end());
            return res;
        }
    private:
        int n;
        std::vector<int> par, siz;
        T e;
        std::vector<T> value;
        Op op;
        Inv inv;

        T weight(int x) {
            T res = e;
            while (par[x] != x) {
                int &p = par[x];
                value[x] = op(value[p], value[x]);
                res = op(value[x], res);
                x = p = par[p];
            }
            return res;
        }
};
} // namespace suisen

#endif // SUISEN_WEIGHTED_UNION_FIND
