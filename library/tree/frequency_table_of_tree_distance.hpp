#ifndef SUISEN_FREQUENCY_TABLE_OF_TREE_DISTANCE
#define SUISEN_FREQUENCY_TABLE_OF_TREE_DISTANCE

#include <cmath>
#include <iostream>
#include <atcoder/convolution>
#include "library/tree/centroid_decomposition.hpp"

#include "library/util/timer.hpp"

namespace suisen {
    /**
     * @brief Given a tree with N vertices, calculates the number of unordered pair (u, v) s.t. dist(u, v) = k for k = 1, ..., N - 1.
     * @param n size of tree
     * @param edges edges of tree
     * @return std::vector<long long> v : v[k] is the number of unordered pair (u, v) s.t. dist(u, v) = k
     */
    std::vector<long long> frequency_table_of_tree_distance(const size_t n, const std::vector<std::pair<int, int>>& edges) {
        static constexpr long long MOD1 = 998244353;
        static constexpr long long MOD2 = 754974721;
        static constexpr long long INV_MOD1 = atcoder::internal::inv_gcd(MOD1, MOD2).second;

        using mint1 = atcoder::static_modint<MOD1>;
        using mint2 = atcoder::static_modint<MOD2>;

        auto garner = [](mint1 x1, mint2 x2) -> long long {
            long long v1 = x1.val(), v2 = x2.val();
            return mint2((v2 - v1) * INV_MOD1).val() * MOD1 + v1;
        };

        std::vector<long long> res(n);

        CentroidDecompositionUnweighted g(UnweightedGraph::create_undirected_graph(n, edges));

        const int garner_threshold = ::sqrt(MOD1);

        for (size_t root = 0; root < n; ++root) {
            std::vector<std::vector<std::pair<int, int>>> d = g.collect(root, 0);
            for (size_t i = 0; i < d.size(); ++i) {
                int max_dep = 0;
                for (auto [v, w] : d[i]) max_dep = std::max(max_dep, w);
                std::vector<int> f(max_dep + 1);
                for (auto [v, w] : d[i]) ++f[w];

                std::vector<int> sq_f1 = atcoder::convolution<mint1::mod()>(f, f);
                int coef = i == 0 ? +1 : -1;
                if (d[i].size() <= garner_threshold) {
                    for (size_t i = 0; i < std::min(n, sq_f1.size()); ++i) {
                        res[i] += coef * sq_f1[i];
                    }
                } else {
                    std::vector<int> sq_f2 = atcoder::convolution<mint2::mod()>(f, f);
                    for (size_t i = 0; i < std::min(n, sq_f1.size()); ++i) {
                        res[i] += coef * garner(sq_f1[i], sq_f2[i]);
                    }
                }
            }
        }

        for (size_t i = 1; i < n; ++i) {
            res[i] >>= 1;
        }
        return res;
    }
} // namespace suisen


#endif // SUISEN_FREQUENCY_TABLE_OF_TREE_DISTANCE
