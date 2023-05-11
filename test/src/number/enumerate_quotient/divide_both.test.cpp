#define PROBLEM "https://atcoder.jp/contests/abc206/tasks/abc206_e"

#include <iostream>
#include <unordered_map>

#include "library/number/enumerate_quotient.hpp"

using namespace suisen;

constexpr int MAX = 1000010;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int l, r;
    std::cin >> l >> r;
    l = std::max(l - 1, 1);
    std::unordered_map<long long, long long> memo;
    auto f = [&memo](auto self, int l, int r) -> long long {
        const long long key = (long long) l * MAX + r;
        {
            auto it = memo.find(key);
            if (it != memo.end()) return it->second;
        }
        long long res = (long long) (r - l) * (r - l);
        for (auto [lg, rg, qs] : multiple_quotients_ranges(std::array<int, 2>{l, r})) {
            if (lg == 1 and rg == 1) continue;
            auto [nl, nr] = qs;
            res -= (rg - lg + 1) * self(self, nl, nr);
        }
        return memo[key] = res;
    };
    long long whole_pairs = (long long) (r - l) * (r - l);
    long long divisor_pairs = 0;
    for (auto [lg, rg, q] : quotient_ranges(r)) {
        divisor_pairs += (long long) std::max(0, (rg - std::max(lg - 1, l))) * q;
    }
    divisor_pairs += divisor_pairs - (r - l);
    std::cout << whole_pairs - f(f, l, r) - divisor_pairs << std::endl;
    return 0;
}