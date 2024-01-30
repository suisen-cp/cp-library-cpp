#ifndef SUISEN_SUM_OF_BINOM
#define SUISEN_SUM_OF_BINOM

#include "library/algorithm/mo.hpp"
#include "library/math/pow_mods.hpp"
#include "library/math/factorial.hpp"

#include <tuple>

namespace suisen {
    // {n,m} in qs: Sum[i=0,n] r^i Binom[m,i]
    template <typename Mint>
    std::vector<Mint> binom_sum_prefix(const std::vector<std::pair<int, int>>& qs, const Mint& r = 1) {
        const int q = qs.size();
        std::vector<Mint> res(qs.size());

        if (r == -1) {
            factorial<Mint> fac;
            for (int i = 0; i < q; ++i) {
                auto [n, m] = qs[i];
                n = std::min(n, m);
                if (n < 0) {
                    res[i] = 0;
                } else if (m == 0) {
                    // n = m = 0
                    res[i] = 1;
                } else {
                    res[i] = (n % 2 == 1 ? -1 : +1) * fac.binom(m - 1, n);
                }
            }
            return res;
        }

        std::vector<int> qid;
        std::vector<std::pair<int, int>> ranges;
        qid.reserve(q), ranges.reserve(q);
        int max_m = 1;
        for (int i = 0; i < q; ++i) {
            auto [n, m] = qs[i];
            n = std::min(n, m);
            if (n < 0) {
                res[i] = 0;
            } else if (m == 0) {
                // n = m = 0
                res[i] = 1;
            } else {
                qid.push_back(i);
                ranges.emplace_back(n, m);
                max_m = std::max(max_m, m);
            }
        }
        pow_mods<Mint> pow_r(r, max_m + 1);
        factorial<Mint> fac(max_m + 1);
        const Mint inv_r1 = (r + 1).inv();

        Mo mo(max_m, std::move(ranges));
        Mint sum = 1;
        const std::vector<Mint> res_mo = mo.solve(
            [&] {
                return sum;
            },
            [&](const int n) { // Add Left
                const int m = mo.get_right();
                // (n + 1, m) -> (n, m)
                sum -= pow_r[n + 1] * fac.binom(m, n + 1);
            },
            [&](const int n) { // Del Left
                const int m = mo.get_right();
                // (n, m) -> (n + 1, m)
                sum += pow_r[n + 1] * fac.binom(m, n + 1);
            },
            [&](const int m) { // Add Right
                const int n = mo.get_left();
                // (n, m) -> (n, m + 1)
                sum = (r + 1) * sum - pow_r[n + 1] * fac.binom(m, n);
            },
            [&](const int m) { // Del Right
                const int n = mo.get_left();
                // (n, m + 1) -> (n, m)
                sum = (pow_r[n + 1] * fac.binom(m, n) + sum) * inv_r1;
            }
        );
        for (int i = 0; i < int(qid.size()); ++i) res[qid[i]] = res_mo[i];
        return res;
    }

    // {a,b,m} in qs: Sum[i=a,b] r^i Binom[m,i]
    template <typename Mint>
    std::vector<Mint> binom_sum(const std::vector<std::tuple<int, int, int>>& qs, const Mint& r = 1) {
        const int q = qs.size();
        std::vector<std::pair<int, int>> ls(q), rs(q);
        for (int i = 0; i < q; ++i) {
            const auto [a, b, m] = qs[i];
            ls[i] = { a - 1, m };
            rs[i] = { b, m };
        }
        std::vector<Mint> suml = binom_sum_prefix(ls, r);
        std::vector<Mint> sumr = binom_sum_prefix(rs, r);
        std::vector<Mint> sum(q);
        for (int i = 0; i < q; ++i) sum[i] = sumr[i] - suml[i];
        return sum;
    }
} // namespace suisen



#endif // SUISEN_SUM_OF_BINOM
