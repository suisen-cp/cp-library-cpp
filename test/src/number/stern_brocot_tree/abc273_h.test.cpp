#define PROBLEM "https://atcoder.jp/contests/abc273/tasks/abc273_Ex"

#include "library/number/stern_brocot_tree.hpp"

#include <iostream>
#include <map>
#include <set>

#include <atcoder/modint>

using mint = atcoder::modint998244353;

using sbt_node = suisen::sbt_node<int>;
using rational = sbt_node::rational;

mint solve(std::vector<rational> xs) {
    const int n = xs.size();

    const auto all = [](int n) -> mint {
        return (long long) n * (n + 1) / 2;
    };

    mint res = all(n);
    {
        // only (0,1), (1,0)
        auto check = [](rational r) {
            return r == rational{ 1, 0 } or r == rational{ 0, 1 };
        };
        for (int i = 0; i < n; ++i) if (check(xs[i])) {
            xs[i] = { 1, 1 };
            int j = i + 1;
            while (j < n and check(xs[j])) {
                xs[j++] = { 1, 1 };
            }
            // [i, j)
            res -= all(j - i);
            i = j;
        }
    }
    xs.emplace_back(1, 1);
    const auto g = sbt_node::auxiliary_tree(std::vector<sbt_node>(xs.begin(), xs.end()));
    xs.pop_back();

    const int r = g.root();

    std::map<rational, int> mp;
    for (int i = 0; i < n; ++i) mp[xs[i]] = i;

    assert(g.node(r) == sbt_node(1, 1));

    auto dfs = [&](auto dfs, int u, int p) -> std::pair<std::set<int>, mint> {
        std::set<int> su{ -1, n };
        mint nu = 0;

        auto add = [&](int i) {
            if (i == -1 or i == n) return;
            auto it = su.lower_bound(i);
            int r = *it;
            int l = *--it + 1;
            nu += all(r - l);
            su.insert(i);
            nu -= all(r - (i + 1));
            nu -= all(i - l);
        };
        auto merge = [&](std::set<int> &sv, mint nv) {
            if (su.size() < sv.size()) std::swap(su, sv), std::swap(nu, nv);
            for (int i : sv) add(i);
        };

        for (int v : g[u]) if (v != p) {
            int d = sbt_node::dist(g.node(u), g.node(v));
            auto [sv, nv] = dfs(dfs, v, u);
            res += d * nv;
            merge(sv, nv);
        }

        if (auto it = mp.find(g.node(u)); it != mp.end()) add(it->second);
        return { std::move(su), nu };
    };
    dfs(dfs, r, -1);

    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    mint ans = 0;
    std::vector<rational> xs;

    for (int r = 0; r < n; ++r) {
        int a, b;
        std::cin >> a >> b;
        if (std::gcd(a, b) != 1) {
            ans += solve(xs);
            xs.clear();
            continue;
        }
        xs.emplace_back(a, b);
    }
    ans += solve(xs);
    std::cout << ans.val() << std::endl;
}
