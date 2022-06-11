#ifndef SUISEN_MAXIMUM_INDEPENDENT_SET
#define SUISEN_MAXIMUM_INDEPENDENT_SET

#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

namespace suisen {
    std::vector<int> maximum_independent_set(const std::vector<std::vector<int>>& g) {
        const int n = g.size();
        if (n == 0) return {};

        const int argmax_deg = std::max_element(g.begin(), g.end(), [](const auto& adj1, const auto& adj2) { return adj1.size() < adj2.size(); }) - g.begin();

        if (g[argmax_deg].size() <= 2) {
            std::vector<int> mis;
            std::vector<int> color(n, -1);
            for (int i = 0; i < n; ++i) if (color[i] < 0) {
                std::vector<int> updated;
                std::array<int, 2> cnt{};
                color[i] = 0;
                std::deque<int> dq{ i };
                int p = -1;
                while (dq.size()) {
                    int u = dq.front();
                    dq.pop_front();
                    updated.push_back(u);
                    ++cnt[color[u]];
                    for (int v : g[u]) {
                        if (color[v] < 0) {
                            color[v] = 1 ^ color[u];
                            dq.push_back(v);
                        } else if (color[u] == color[v]) {
                            p = u;
                        }
                    }
                }
                int majority = cnt[1] >= cnt[0];
                for (int u : updated) if (color[u] == majority and u != p) {
                    mis.push_back(u);
                }
            }
            return mis;
        }

        std::vector<int> mis;
        for (const auto& remove_vertices : { std::vector<int>{}, g[argmax_deg] }) {
            std::vector<int8_t> rem_flg(n, false);
            rem_flg[argmax_deg] = true;
            for (const auto& e : remove_vertices) {
                rem_flg[e] = true;
            }
            std::vector<int> bias(n + 1);
            for (int i = 0; i < n; ++i) {
                bias[i + 1] = bias[i] + rem_flg[i];
            }
            std::vector<int> decomp(n, -1);
            for (int i = 0; i < n; ++i) if (not rem_flg[i]) {
                decomp[i - bias[i]] = i;
            }

            std::vector<std::vector<int>> h;
            h.reserve(g.size() - remove_vertices.size() - 1);
            for (int i = 0; i < n; ++i) if (not rem_flg[i]) {
                std::vector<int> adj;
                for (int j : g[i]) if (not rem_flg[j]) {
                    adj.push_back(j - bias[j]);
                }
                h.push_back(std::move(adj));
            }

            std::vector<int> vs = maximum_independent_set(h);
            for (auto& e : vs) {
                e = decomp[e];
            }
            if (remove_vertices.size()) {
                vs.push_back(argmax_deg);
            }
            if (vs.size() > mis.size()) {
                mis = std::move(vs);
            }
        }
        return mis;
    }
} // namespace suisen


#endif // SUISEN_MAXIMUM_INDEPENDENT_SET
