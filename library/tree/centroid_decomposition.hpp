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

        auto operator[](int u) {
            return AdjacentList{ this, u };
        }
        auto operator[](int u) const {
            return ConstAdjacentList{ this, u };
        }

        template <typename DownF, typename UpF = decltype(dummy)>
        void decomp(DownF down, UpF up = dummy) {
            removed.assign(size(), false);
            std::vector<int> sub(size(), 0);
            auto rec = [&](auto rec, int r, int siz) -> void {
                int pc = -1, c = -1;
                auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                    sub[u] = 1;
                    for (int v : (*this)[u]) {
                        if (v == p) continue;
                        get_centroid(get_centroid, v, u);
                        sub[u] += sub[v];
                    }
                    if (c < 0 and sub[u] * 2 > siz) pc = p, c = u;
                };
                get_centroid(get_centroid, r, -1);
                down(c, siz);
                removed[c] = true;
                for (int v : (*this)[c]) rec(rec, v, v == pc ? siz - sub[c] : sub[v]);
                removed[c] = false;
                up(c, siz);
            };
            rec(rec, 0, size());
        }
    };

} // namespace suisen

#endif // SUISEN_CENTROID_DECOMPOSITION
