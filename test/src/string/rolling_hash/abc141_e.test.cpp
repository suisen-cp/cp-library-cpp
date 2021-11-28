#define PROBLEM "https://atcoder.jp/contests/abc141/tasks/abc141_e"

#include <iostream>
#include <set>

#include "library/string/rolling_hash.hpp"
using suisen::RollingHash;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s;
    std::cin >> n >> s;

    auto rh = RollingHash<>::from_lowercase_alphabet(s);

    auto f = [&](int l) -> bool {
        std::vector<RollingHash<>::hash_type> hashes(n);
        std::set<RollingHash<>::hash_type> s;
        for (int i = 0; i + l <= n; ++i) {
            if (i >= l) s.insert(hashes[i - l]);
            auto h = rh(i, i + l)[0].val();
            hashes[i] = h;
            if (s.count(h)) return true;
        }
        return false;
    };

    int ok = 0, ng = n + 1;
    while (ng - ok > 1) {
        int l = (ok + ng) / 2;
        if (f(l)) {
            ok = l;
        } else {
            ng = l;
        }
    }
    std::cout << ok << std::endl;
    return 0;
}