#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2405&lang=jp"

#include <iostream>
#include <map>
#include <set>

constexpr int mod = 1000003;

#include "library/graph/tree_decomposition_tw2_dp.hpp"

using match = std::pair<int, int>;
using table_key = std::vector<match>;
using table_value = long long;
using table_entry = std::pair<table_key, table_value>;
using table = std::map<table_key, long long>;

struct state {
    static constexpr int Forgotten = -2;
    static constexpr int None = -1;
    table mp;
};

void solve() {
    using namespace suisen;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    if (n == 0 and m == 0) exit(0);

    std::vector<std::set<int>> adj(n);

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        edges.emplace_back(i, (i + 1) % n);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        edges.emplace_back(u, v);
    }

    for (const auto &[u, v] : edges) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    auto leaf = [&](const DecompNodeRooted&, int leaf_vertex) -> state {
        return state { table{ table_entry{ table_key{ match{ leaf_vertex, state::None } }, table_value{ 1 } } } };
    };
    auto introduce = [&](const DecompNodeRooted&, const DecompNodeRooted&, const state& child_result, int introduce_vertex) -> state {
        table ndp;
        for (auto [matching, val] : child_result.mp) {
            {
                auto nxt_matching = matching;
                nxt_matching.emplace_back(introduce_vertex, state::None);
                std::sort(nxt_matching.begin(), nxt_matching.end());
                ndp[nxt_matching] += val;
            }
            const int k = matching.size();
            for (int i = 0; i < k; ++i) {
                auto [u, v] = matching[i];
                if (v != state::None or adj[introduce_vertex].find(u) == adj[introduce_vertex].end()) continue;
                auto nxt_matching = matching;
                nxt_matching[i].second = introduce_vertex;
                nxt_matching.emplace_back(introduce_vertex, u);
                std::sort(nxt_matching.begin(), nxt_matching.end());
                ndp[nxt_matching] += val;
            }
        }
        for (auto &[_, val] : ndp) val %= mod;
        return state { ndp };
    };
    auto forget = [&](const DecompNodeRooted&, const DecompNodeRooted&, const state& child_result, int forget_vertex) -> state {
        table ndp;
        for (auto [matching, val] : child_result.mp) {
            bool ok = true;
            table_key nxt_matching;
            for (auto [u, v] : matching) {
                if (u == forget_vertex) {
                    ok &= v != state::None;
                    continue;
                }
                if (v == forget_vertex) {
                    nxt_matching.emplace_back(u, state::Forgotten);
                } else {
                    nxt_matching.emplace_back(u, v);
                }
            }
            if (not ok) {
                continue;
            }
            std::sort(nxt_matching.begin(), nxt_matching.end());
            ndp[nxt_matching] += val;
        }
        for (auto &[_, val] : ndp) val %= mod;
        return state { ndp };
    };
    auto join = [&](const DecompNodeRooted&, const DecompNodeRooted&, const state& child_result_1, const DecompNodeRooted&, const state& child_result_2) -> state {
        table ndp;
        for (auto [matching1, val1] : child_result_1.mp) for (auto [matching2, val2] : child_result_2.mp) {
            bool ok = true;
            const int k = matching1.size();
            table_key nxt_matching;
            for (int i = 0; i < k; ++i) {
                auto [u1, v1] = matching1[i];
                auto [u2, v2] = matching2[i];
                assert(u1 == u2);
                if (v1 > v2) std::swap(v1, v2);
                if (v1 == state::Forgotten) {
                    if (v2 == state::Forgotten) {
                        ok = false;
                        break;
                    } else if (v2 == state::None) {
                        nxt_matching.emplace_back(u1, v1);
                    } else {
                        ok = false;
                        break;
                    }
                } else if (v1 == state::None) {
                    if (v2 == state::None) {
                        nxt_matching.emplace_back(u1, v1);
                    } else {
                        ok = false;
                        break;
                    }
                } else {
                    if (v1 != v2) {
                        ok = false;
                        break;
                    } else {
                        nxt_matching.emplace_back(u1, v1);
                    }
                }
                if (not ok) break;
            }
            if (ok) {
                std::sort(nxt_matching.begin(), nxt_matching.end());
                ndp[nxt_matching] += val1 * val2;
            }
        }
        for (auto &[_, val] : ndp) val %= mod;
        return state { ndp };
    };

    state dp_root = NiceDecompTree(n, edges).run_dp<state>(leaf, introduce, forget, join);

    long long ans = 0;
    for (auto [matching, val] : dp_root.mp) {
        bool ok = true;
        for (auto &[u, v] : matching) {
            if (v == state::None) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans += val;
        }
    }

    std::cout << ans % mod << std::endl;
}

int main() {
    while (true) solve();
}