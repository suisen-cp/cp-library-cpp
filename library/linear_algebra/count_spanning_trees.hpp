#ifndef SUISEN_COUNT_SPANNING_TREES
#define SUISEN_COUNT_SPANNING_TREES

#include "library/linear_algebra/matrix.hpp"

namespace suisen {
    template <typename T, typename Edge>
    T count_spanning_trees(const int n, const std::vector<Edge> &edges) {
        SquareMatrix<T> A(n - 1);
        for (auto [u, v] : edges) if (u != v) {
            if (u > v) std::swap(u, v);
            ++A[u][u];
            if (v != n - 1) ++A[v][v], --A[u][v], --A[v][u];
        }
        return SquareMatrix<T>::det(std::move(A));
    }
} // namespace suisen


#endif // SUISEN_COUNT_SPANNING_TREES
