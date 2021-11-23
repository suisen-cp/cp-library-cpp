#ifndef SUISEN_CENTROID_DECOMPOSITION
#define SUISEN_CENTROID_DECOMPOSITION

#include <vector>

namespace suisen {

    struct CentroidDecomposition : public std::vector<std::vector<int>> {
        using BaseType = std::vector<std::vector<int>>;
    public:
        using BaseType::BaseType;

        void add_edge(int u, int v) {
            BaseType::operator[](u).push_back(v);
            BaseType::operator[](v).push_back(u);
        }

    private:
        std::vector<bool> removed;
        std::vector<int> sub;

        struct AdjacentListIterator {
            using it_t = std::vector<int>::const_iterator;
            const CentroidDecomposition* const ptr;
            const int u;
            it_t it;
            AdjacentListIterator(const CentroidDecomposition* const ptr, int u, it_t it) : ptr(ptr), u(u), it(it) { suc(); }
            AdjacentListIterator& operator++() { return ++it, suc(), * this; }
            int operator*() { return *it; }
            bool operator!=(const AdjacentListIterator& other) { return it != other.it; }
            void suc() { while (it != (*ptr).BaseType::operator[](u).end() and ptr->removed[*it]) ++it; }
        };
        struct AdjacentList {
            CentroidDecomposition* const ptr;
            const int u;
            std::vector<int>& base_vector()& { return ptr->BaseType::operator[](u); }
            auto begin() const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin()); }
            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end()); }
        };
        struct ConstAdjacentList {
            const CentroidDecomposition* const ptr;
            const int u;
            const std::vector<int>& base_vector() const& { return ptr->BaseType::operator[](u); }
            auto begin() const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin()); }
            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end()); }
        };

    public:
        static constexpr void dummy(int, int) {}

        // Returns the list of vertices adjacent to `u`. If called during decomposition, it skips removed vertices.
        auto operator[](int u) {
            return AdjacentList{ this, u };
        }
        // Returns the (constant) list of vertices adjacent to `u`. If called during decomposition, it skips removed vertices.
        auto operator[](int u) const {
            return ConstAdjacentList{ this, u };
        }

        // This method is expected to be called in functions passed to the `decomp`.
        // The argument `root` must be directly connected to the current centroid. If not, the returned value will be undefined.
        int component_size(int root) const {
            return sub[root];
        }

        struct DecompositionTree {
            DecompositionTree() {}
            DecompositionTree(int root, const std::vector<int> &par) : n(par.size()), root(root), par(par) {}

            int size() const { return n; }
            int get_root() const { return root; }
            int get_parent(int u) const { return par[u]; }
            const std::vector<int>& parents() const { return par; }
        private:
            int n;
            int root;
            std::vector<int> par;
        };

        // returns the centroid decomposition tree
        template <typename DownF = decltype(dummy), typename UpF = decltype(dummy)>
        DecompositionTree decomp(DownF down = dummy, UpF up = dummy) {
            removed.assign(size(), false);
            sub.assign(size(), 0);
            std::vector<int> par(size(), -1);
            auto rec = [&](auto rec, int r, int siz) -> int {
                int c = -1;
                auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                    sub[u] = 1;
                    for (int v : (*this)[u]) {
                        if (v == p) continue;
                        get_centroid(get_centroid, v, u);
                        if (v == c) {
                            sub[u] = siz - sub[c];
                            break;
                        }
                        sub[u] += sub[v];
                    }
                    if (c < 0 and sub[u] * 2 > siz) c = u;
                };
                get_centroid(get_centroid, r, -1);
                down(c, siz);
                removed[c] = true;
                for (int v : (*this)[c]) {
                    const int comp_size = sub[v];
                    par[rec(rec, v, comp_size)] = c;
                    sub[v] = comp_size;
                }
                removed[c] = false;
                up(c, siz);
                return c;
            };
            int root = rec(rec, 0, size());
            return DecompositionTree(root, par);
        }
    };

} // namespace suisen

#endif // SUISEN_CENTROID_DECOMPOSITION
