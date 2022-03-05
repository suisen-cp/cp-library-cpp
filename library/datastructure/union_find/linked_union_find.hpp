#ifndef SUISEN_LINKED_UNION_FIND
#define SUISEN_LINKED_UNION_FIND

#include <numeric>
#include "library/datastructure/union_find/union_find.hpp"

namespace suisen {
class LinkedUnionFind : public UnionFind {
    public:
        LinkedUnionFind() {}
        explicit LinkedUnionFind(int n) : UnionFind(n), link(n) {
            std::iota(link.begin(), link.end(), 0);
        }
        // Merge two vertices `x` and `y`.
        bool merge(int x, int y) {
            if (UnionFind::merge(x, y)) {
                std::swap(link[x], link[y]);
                return true;
            }
            return false;
        }
        // Get items connected to `x` (including `x`). Let the size of return value be `m`, time complexity is O(m).
        std::vector<int> connected_component(int x) const {
            std::vector<int> comp {x};
            for (int y = link[x]; y != x; y = link[y]) comp.push_back(y);
            return comp;
        }
    private:
        std::vector<int> link;
};
} // namespace suisen

#endif // SUISEN_LINKED_UNION_FIND
