#ifndef SUISEN_CARTESIAN_TREE
#define SUISEN_CARTESIAN_TREE

#include <array>
#include <functional>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
    struct CartesianTree : public std::vector<std::array<int, 2>> {
        using base_type = std::vector<std::array<int, 2>>;

        static constexpr int absent = -1;

        const int root;

        CartesianTree() : base_type(), root(0) {}
        CartesianTree(int root, const base_type& g) : base_type(g), root(root) {}
        CartesianTree(int root, base_type&& g) : base_type(std::move(g)), root(root) {}

        auto ranges() const {
            std::vector<std::pair<int, int>> res;
            res.reserve(size());
            auto rec = [&](auto rec, int l, int m, int r) -> void {
                if (m == absent) return;
                const auto& [lm, rm] = (*this)[m];
                rec(rec, l, lm, m), res.emplace_back(l, r), rec(rec, m + 1, rm, r);
            };
            rec(rec, 0, root, size());
            return res;
        }
    };

    template <typename T, typename Comparator, constraints_t<is_comparator<Comparator, T>> = nullptr>
    struct CartesianTreeBuilder {
        CartesianTreeBuilder() {}
        template <typename RandomAccessibleContainer>
        CartesianTreeBuilder(const RandomAccessibleContainer& a, Comparator comp = Comparator{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}

        CartesianTree build() const {
            int root = -1;
            std::vector<std::array<int, 2>> g(n, { CartesianTree::absent, CartesianTree::absent });
            for (int i = 0; i < n; ++i) {
                int p = par[i];
                (p >= 0 ? g[p][p <= i] : root) = i;
            }
            return CartesianTree{ root, std::move(g) };
        }

        template <typename RandomAccessibleContainer>
        static CartesianTree build(const RandomAccessibleContainer& a, Comparator comp = Comparator{}) {
            return CartesianTreeBuilder(a, comp).build();
        }

        int parent(std::size_t i) const {
            assert(i < n);
            return par[i];
        }
        int operator[](std::size_t i) const {
            return parent(i);
        }
    private:
        const int n;
        const Comparator comp;
        const std::vector<int> par;

        template <typename RandomAccessibleContainer>
        static std::vector<int> calc_par(const RandomAccessibleContainer& a, Comparator comp) {
            const int n = a.size();
            std::vector<int> par(n, -1);
            for (int i = 1; i < n; ++i) {
                int p = i - 1, l = i;
                while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];
                par[l] = i, par[i] = p;
            }
            return par;
        }
    };
} // namespace suisen

#endif // SUISEN_CARTESIAN_TREE
