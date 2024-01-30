#define PROBLEM "https://atcoder.jp/contests/abc334/tasks/abc334_g"

#include "library/graph/low_link.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> s(h);
    for (auto &e : s) std::cin >> e;

    constexpr char GREEN = '#';

    int num_green = 0;
    std::vector id(h, std::vector<int>(w, -1));
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        if (s[i][j] == GREEN) {
            id[i][j] = num_green++;
        }
    }

    constexpr int d[3]{ 0, 1, 0 };
    
    suisen::LowLink ll(num_green);
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        if (s[i][j] != GREEN) continue;

        for (int dir = 0; dir < 2; ++dir) {
            int ni = i + d[dir], nj = j + d[dir + 1];
            if (ni < 0 or ni >= h) continue;
            if (nj < 0 or nj >= w) continue;
            if (s[ni][nj] != GREEN) continue;

            const int u = id[i][j], v = id[ni][nj];
            ll.add_edge(u, v);
        }
    }
    ll.build();

    long long sum = 0;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        if (s[i][j] == GREEN) {
            sum += ll.connected_component_num_if_removed(id[i][j]);
        }
    }

    constexpr int MOD = 998244353;
    constexpr auto inv_mod = [](int x) {
        int ix = 1;
        for (int b = MOD - 2; b; b >>= 1) {
            if (b & 1) ix = 1LL * ix * x % MOD;
            x = 1LL * x * x % MOD;
        }
        return ix;
    };
    std::cout << (sum % MOD * inv_mod(num_green) % MOD) << '\n';
}