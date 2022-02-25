#define PROBLEM "https://atcoder.jp/contests/abc162/tasks/abc162_e"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint1000000007;

#include "library/number/sum_of_totient_function.hpp"

// O(K^(2/3) (log log K)^(1/3) + K^(1/2) log N)
int main() {
    int n, k;
    std::cin >> n >> k;

    // calculate sum(d) := Σ[i=1,floor(k/d)] φ(i) for all integer d in O(K^(2/3) (log log K)^(1/3) time.
    suisen::SumOfTotientFunction<mint> sum(k);

    mint ans = 0;
    for (int l = 1; l <= k;) {
        int q = k / l;
        ans += (sum(q) - sum(q + 1)) * mint(q).pow(n);
        l = k / q + 1;
    }
    std::cout << ans.val() << std::endl;
    return 0;
}