#define PROBLEM "https://atcoder.jp/contests/arc132/tasks/arc132_f"

#include <array>
#include <iostream>

#include "library/transform/kronecker_power.hpp"

using suisen::kronecker_power_transform::kronecker_power_transform;

void trans(long long &x0, long long &x1, long long &x2, long long &x3) {
    x3 += x0 + x1 + x2;
}
 
void trans2(long long &x0, long long &x1, long long &x2, long long &x3) {
    x0 = x3 - x0;
    x1 = x3 - x1;
    x2 = x3 - x2;
    x3 = 0;
}
 
int main() {
    std::array<int, 256> mp;
    mp['P'] = 0, mp['R'] = 1, mp['S'] = 2;
 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int k, n, m;
    std::cin >> k >> n >> m;
 
    auto count = [&](int num) {
        std::vector<long long> f(1 << (2 * k), 0);
        for (int i = 0; i < num; ++i) {
            int a = 0;
            for (int j = 0; j < k; ++j) {
                char c;
                std::cin >> c;
                a |= mp[c] << (2 * j);
            }
            ++f[a];
        }
        return f;
    };
    auto f = count(n), g = count(m);
 
    kronecker_power_transform<long long, 4, trans>(f);
    kronecker_power_transform<long long, 4, trans>(g);
    for (int i = 0; i < 1 << (2 * k); ++i) f[i] *= g[i];
    kronecker_power_transform<long long, 4, trans2>(f);
 
    int pow3 = 1;
    for (int i = 0; i < k; ++i) pow3 *= 3;
 
    for (int i = 0; i < pow3; ++i) {
        int v = 0;
        for (int t = i, j = 0; j < k; ++j, t /= 3) {
            int d = t % 3;
            v |= (d == 2 ? 0 : d + 1) << (2 * (k - j - 1));
        }
        std::cout << (long long) n * m - f[v] << '\n';
    }
    
    return 0;
}