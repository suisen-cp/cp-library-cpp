#define PROBLEM "https://atcoder.jp/contests/past202203-open/tasks/past202203_h"

#include <iostream>

#include "library/datastructure/union_find/linked_union_find.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;

    suisen::LinkedUnionFind uf(n);
    
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 1) {
            int u, v;
            std::cin >> u >> v;
            --u, --v;
            uf.merge(u, v);
        } else {
            int u;
            std::cin >> u;
            --u;
            auto ans = uf.connected_component(u);
            std::sort(ans.begin(), ans.end());
            int len = ans.size();
            for (int i = 0; i < len; ++i) {
                std::cout << ans[i] + 1;
                if (i != len - 1) std::cout << ' ';
            }
            std::cout << '\n';
        }
    }
    return 0;
}