#ifndef SUISEN_CARTESIAN_TREE
#define SUISEN_CARTESIAN_TREE

#include <array>
#include <functional>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
template <typename T, typename Comparator, constraints_t<is_comparator<Comparator, T>> = nullptr>
class CartesianTree {
    public:
        CartesianTree(std::vector<T> &&a, Comparator comp = Comparator{}) : n(a.size()), comp(comp), par(n, -1) {
            for (int i = 1; i < n; ++i) {
                int p = i - 1, l = i;
                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];
                par[l] = i, par[i] = p;
            }
        }
        CartesianTree(const std::vector<T> &a, Comparator comp = Comparator{}) : CartesianTree(std::vector<T>(a), comp) {}

        struct Tree {
            const int absent;
            const int root;
            const std::vector<std::array<int, 2>> g;

            std::vector<std::pair<int, int>> ranges() const {
                std::vector<std::pair<int, int>> res(g.size());
                auto dfs = [&](auto self, int u) -> void {
                    res[u] = {u, u + 1};
                    auto [l, r] = g[u];
                    if (l != absent) {
                        self(self, l);
                        res[u].first = res[l].first;
                    }
                    if (r != absent) {
                        self(self, r);
                        res[u].second = res[r].second;
                    }
                };
                dfs(dfs, root);
                return res;
            }
        };

        std::vector<std::array<int, 2>> build_tree() const {
            int root = -1;
            std::vector<std::array<int, 2>> g(n, {-1, -1});
            for (int i = 0; i < n; ++i) {
                int p = par[i];
                if (p >= 0) {
                    g[p][p <= i] = i;
                } else {
                    root = p;
                }
            }
            return Tree {-1, root, std::move(g)};
        }

        int parent(int i) const {
            return par[i];
        }
    private:
        const int n;
        const Comparator comp;
        std::vector<int> par;
};
} // namespace suisen

#endif // SUISEN_CARTESIAN_TREE
