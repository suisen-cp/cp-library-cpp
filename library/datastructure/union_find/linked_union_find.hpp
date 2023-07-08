#ifndef SUISEN_LINKED_UNION_FIND
#define SUISEN_LINKED_UNION_FIND

#include <numeric>
#include "library/datastructure/union_find/union_find.hpp"

namespace suisen {
    struct LinkedUnionFind : public UnionFind {
        LinkedUnionFind() = default;
        explicit LinkedUnionFind(int n) : UnionFind(n), _link(n) {
            std::iota(_link.begin(), _link.end(), 0);
        }
        // Merge two vertices `x` and `y`.
        bool merge(int x, int y) {
            if (UnionFind::merge(x, y)) {
                std::swap(_link[x], _link[y]);
                return true;
            }
            return false;
        }
        // Get items connected to `x` (including `x`). Let the size of return value be `m`, time complexity is O(m).
        std::vector<int> connected_component(int x) const {
            std::vector<int> comp{ x };
            for (int y = _link[x]; y != x; y = _link[y]) comp.push_back(y);
            return comp;
        }
    protected:
        std::vector<int> _link;
    };
} // namespace suisen

#endif // SUISEN_LINKED_UNION_FIND
