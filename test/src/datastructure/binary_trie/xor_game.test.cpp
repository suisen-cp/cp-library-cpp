#define PROBLEM "https://atcoder.jp/contests/arc122/tasks/arc122_d"

#include <iostream>

#include "library/datastructure/binary_trie.hpp"

constexpr int M = 30;

int solve(const int n, const std::vector<int> &a, const int m) {
    if (m < 0) return 0;

    int res = 0;
    std::vector<std::vector<int>> ls(m);
    for (int k = 0; k < n; ++k) {
        int v = a[k];
        for (int i = 0; i < m; ++i) {
            if ((v >> i) & 1) {
                ls[i].push_back(k);
            }
        }
    }
 
    std::vector<char> used(n, false);
    for (int i = m; i --> 0;) {
        int sz = ls[i].size();
        for (int j = 0; j < sz; ++j) {
            while (j < sz and used[ls[i][j]]) {
                std::swap(ls[i][j], ls[i][--sz]), ls[i].pop_back();
            }
        }
        if (sz & 1) {
            suisen::BinaryTrie<int, M> bt;
            for (int k = 0; k < n; ++k) {
                if (a[k] < (1 << i)) {
                    bt.insert(a[k]);
                }
            }
            int min = std::numeric_limits<int>::max();
            for (int k : ls[i]) {
                min = std::min(min, int(bt.xor_min(a[k])));
            }
            return std::max(min, res);
        } else {
            if (sz == 0) continue;
            std::vector<int> next;
            next.reserve(sz);
            for (int k : ls[i]) {
                next.push_back(a[k] ^ (1 << i));
                used[k] = true;
            }
            ls[i].clear();
            res = std::max(res, solve(sz, next, i));
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(2 * n);
    for (auto &e : a) std::cin >> e;
    std::cout << solve(a.size(), a, M) << '\n';
    return 0;
}