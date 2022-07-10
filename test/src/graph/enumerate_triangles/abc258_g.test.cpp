#define PROBLEM "https://atcoder.jp/contests/abc258/tasks/abc258_g"

#include <iostream>

#include "library/graph/enumerate_triangles.hpp"

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> g(n);
    for (int u = 0; u < n; ++u) {
        std::string s;
        std::cin >> s;
        for (int v = 0; v < n; ++v) if (s[v] == '1') {
            g[u].push_back(v);
        }
    }

    long long ans = 0;
    suisen::enumerate_triangles(g, [&ans](int, int, int) { ++ans; });
    std::cout << ans << std::endl;

    return 0;
}