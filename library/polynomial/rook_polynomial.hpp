#ifndef SUISEN_ROOK_POLYNOMIAL
#define SUISEN_ROOK_POLYNOMIAL

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include "library/polynomial/convert_to_newton_basis.hpp"
#include "library/datastructure/cartesian_tree.hpp"
#include "library/math/factorial.hpp"

namespace suisen {
    // O(n(log n)^2). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking rooks on a ferrers board
    template <typename FPSType>
    FPSType rook_polynomial_ferrers_board(const std::vector<int> &h) {
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

    // O(n^2 log n). returns rook polynomial r s.t. r[k] := # ways to put k non-attacking rooks on a skyline board
    template <typename FPSType>
    FPSType rook_polynomial_skyline_board(const std::vector<int> &h) {
        using fps = FPSType;
        using mint = typename fps::value_type;

        const int n = h.size();

        factorial<mint> fac(n);

        MinCartesianTreeBuilder ct_builder{h};
        CartesianTree t = ct_builder.build();
        auto dfs = [&](auto dfs, int u, int l, int r) -> fps {
            if (u == t.absent) return { 1 };
            fps f = dfs(dfs, t[u][0], l, u);
            fps g = dfs(dfs, t[u][1], u + 1, r);
            fps fg = f * g; // O(n^2)
            fg.push_back(0);

            const int a = h[u] - (u == t.root ? 0 : h[ct_builder.parent(u)]);
            const int b = r - l;
            assert(int(fg.size()) == b + 1);

            fps s(b + 1), t(b + 1);
            mint binom_a_i = 1;
            for (int i = 0; i <= b; ++i) {
                s[i] = fg[i] * fac.fac(b - i);
                t[i] = binom_a_i;
                binom_a_i *= (a - i) * fac.fac_inv(i + 1) * fac.fac(i);
            }
            fps st = s * t;
            st.resize(b + 1);
            for (int i = 0; i <= b; ++i) {
                st[i] *= fac.fac_inv(b - i);
            }
            return st;
        };

        return dfs(dfs, t.root, 0, n);
    }
} // namespace suisen


#endif // SUISEN_ROOK_POLYNOMIAL
