#ifndef SUISEN_ROOK_POLYNOMIAL
#define SUISEN_ROOK_POLYNOMIAL

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include "library/polynomial/convert_to_newton_basis.hpp"

namespace suisen {
    // O(n(log n)^2). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking rooks on a Young tableau
    template <typename FPSType>
    FPSType rook_polynomial_young_tableau(const std::vector<int> &h) {
        using mint = typename FPSType::value_type;
        assert(std::is_sorted(h.begin(), h.end()));
        const int n = h.size();
        std::vector<FPSType> fs(n);
        for (int i = 0; i < n; ++i) fs[i] = FPSType{ h[i] - i, 1 };
        FPSType f = FPSType::prod(fs);
        std::vector<mint> p(n + 1);
        std::iota(p.begin(), p.end(), 0);
        FPSType r = convert_to_newton_basis(f, p);
        std::reverse(r.begin(), r.end());
        return r;
    }
} // namespace suisen


#endif // SUISEN_ROOK_POLYNOMIAL
