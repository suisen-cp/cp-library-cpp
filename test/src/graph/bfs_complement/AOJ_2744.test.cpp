#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2744"

#include <cassert>
#include <iostream>

#include "library/graph/bfs.hpp"
#include "library/graph/bfs_complement.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> res = [rec = [](auto rec, const std::vector<std::vector<int>> &g) -> std::vector<int> {
        const int n = g.size();
        if (n == 1) return { 0, 0 };
        auto cmps = suisen::BFS{g}.connected_components();
        if (cmps.size() == 1) {
            auto ccmps = suisen::ComplementBFS{g}.connected_components();
            assert(ccmps.size() != 1);
            std::vector<int> pd { 0 };
            std::vector<int8_t> in(n);
            std::vector<int> idx(n);
            for (const auto &cmp : ccmps) {
                const int siz = cmp.size();
                for (int i = 0; i < siz; ++i) {
                    idx[cmp[i]] = i;
                }
                std::vector<std::vector<int>> h(siz);
                for (int v : cmp) in[v] = true;
                for (int u : cmp) for (int v : g[u]) if (in[v]) {
                    h[idx[u]].push_back(idx[v]);
                }
                for (int v : cmp) in[v] = false;
                std::vector<int> val = rec(rec, h);
                const int l = pd.size() - 1, r = val.size() - 1;
                std::vector<int> dp(l + r + 1);
                for (int i = 0; i <= l; ++i) {
                    for (int j = 0; j <= r; ++j) {
                        dp[i + j] = std::max(dp[i + j], pd[i] + val[j] + i * (r - j) + (l - i) * j);
                    }
                }
                pd.swap(dp);
            }
            return pd;
        } else {
            std::vector<int> pd{ 0 };
            std::vector<int> idx(n);
            for (const auto &cmp : cmps) {
                const int siz = cmp.size();
                for (int i = 0; i < siz; ++i) idx[cmp[i]] = i;
                std::vector<std::vector<int>> h(siz);
                for (int u : cmp) for (int v : g[u]) {
                    h[idx[u]].push_back(idx[v]);
                }
                std::vector<int> val = rec(rec, h);
                const int l = pd.size() - 1, r = val.size() - 1;
                std::vector<int> dp(l + r + 1);
                for (int i = 0; i <= l; ++i) {
                    for (int j = 0; j <= r; ++j) {
                        dp[i + j] = std::max(dp[i + j], pd[i] + val[j]);
                    }
                }
                pd.swap(dp);
            }
            return pd;
        }
    }, &g]{ return rec(rec, g); }();

    std::cout << *std::max_element(res.begin(), res.end()) << std::endl;

}