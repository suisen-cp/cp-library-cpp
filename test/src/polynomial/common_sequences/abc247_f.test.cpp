#define PROBLEM "https://atcoder.jp/contests/abc247/tasks/abc247_h"

#include <iostream>
#include <queue>

#include <atcoder/modint>
#include <atcoder/convolution>
using mint = atcoder::modint998244353;

#include "library/polynomial/common_sequences.hpp"

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });
    
    int n, k;
    std::cin >> n >> k;

    k -= std::max(0, (k - n)) / 2 * 2;

    std::vector<int> c(n);
    for (auto &e : c) std::cin >> e, --e;
 
    std::vector<int> cnt(n);
    for (auto &e : c) ++cnt[e];
    
    auto comp = [&](const std::vector<mint> &f, const std::vector<mint> &g) { return f.size() > g.size(); };
    std::priority_queue<std::vector<mint>, std::vector<std::vector<mint>>, decltype(comp)> pq { comp };
    for (int v : cnt) pq.push(suisen::stirling_number1_reversed<mint>(v));
 
    while (pq.size() > 1) {
        auto f = std::move(pq.top());
        pq.pop();
        auto g = std::move(pq.top());
        pq.pop();
        auto h = atcoder::convolution(f, g);
        h.resize(f.size() + g.size() - 1);
        pq.push(std::move(h));
    }
 
    mint ans = 0;
    auto f = pq.top();
    for (; k >= 0; k -= 2) {
        if (k < int(f.size())) ans += f[k];
    }
    std::cout << ans.val() << std::endl;
 
    return 0;
}