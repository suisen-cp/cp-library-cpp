#define PROBLEM "https://atcoder.jp/contests/abc238/tasks/abc238_g"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::static_modint<3>;

#include "library/number/sieve_of_eratosthenes.hpp"
#include "library/algorithm/mo.hpp"

using suisen::Sieve;
using suisen::Mo;

constexpr int M = 1000000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    Sieve<M> sieve;
    std::vector<std::vector<std::pair<int, mint>>> factorized(n);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;

        for (auto &&[p, c] : sieve.factorize(v)) {
            factorized[i].emplace_back(p, c);
        }
    }

    std::vector<std::pair<int, int>> queries(q);
    for (auto &[l, r] : queries) {
        std::cin >> l >> r;
        --l;
    }

    std::vector<mint> index_sum(M + 1, 0);
    int invalid = 0;

    auto answers = Mo(n, queries).solve(
        // Eval
        [&]{
            return invalid == 0;
        },
        // Add
        [&](int i) {
            for (const auto &[p, c] : factorized[i]) {
                invalid -= index_sum[p] != 0;
                index_sum[p] += c;
                invalid += index_sum[p] != 0;
            }
        },
        // Del
        [&](int i) {
            for (const auto &[p, c] : factorized[i]) {
                invalid -= index_sum[p] != 0;
                index_sum[p] -= c;
                invalid += index_sum[p] != 0;
            }
        }
    );

    for (bool answer : answers) {
        if (answer) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
    }
    return 0;
}