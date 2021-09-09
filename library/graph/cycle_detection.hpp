#ifndef SUISEN_CYCLE_DETECTION
#define SUISEN_CYCLE_DETECTION

#include <optional>
#include <vector>

namespace suisen {

enum class GraphType {
    DIRECTED, UNDIRECTED
};

template <GraphType t>
std::optional<std::vector<int>> get_cycle(const std::vector<std::vector<int>> &g) {
    const int n = g.size();
    // detect multiedge
    if constexpr (t == GraphType::UNDIRECTED) {
        std::vector<uint8_t> exists(n, 0);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) if (exists[v]++) return std::vector<int> { u, v };
            for (int v : g[u]) exists[v] = 0;
        }
    }
    // simulate dfs
    std::vector<int> itr(n, 0), stk, par(0);
    if constexpr (t == GraphType::UNDIRECTED) par.resize(n, -1);
    stk.reserve(n);
    std::vector<uint8_t> in(n, false);
    for (int i = 0; i < n; ++i) {
        if (itr[i] == 0) stk.push_back(i), in[i] = true;
        while (stk.size()) {
            const int u = stk.back();
            if (itr[u] < int(g[u].size())) {
                const int v = g[u][itr[u]++];
                if constexpr (t == GraphType::UNDIRECTED) if (v == par[u]) continue;
                if (in[v]) return stk.erase(stk.begin(), std::find(stk.begin(), stk.end(), v)), stk;
                if (itr[v] == 0) {
                    stk.push_back(v), in[v] = true;
                    if constexpr (t == GraphType::UNDIRECTED) par[v] = u;
                }
            } else stk.pop_back(), in[u] = false;
        }
    }
    return std::nullopt;
}

template <GraphType t, typename T>
std::optional<std::vector<T>> get_cycle_values(const std::vector<std::vector<std::pair<int, T>>> &g) {
    const int n = g.size();
    // detect multiedge
    if constexpr (t == GraphType::UNDIRECTED) {
        std::vector<uint8_t> exists(n, 0);
        std::vector<T> vals(n);
        for (int u = 0; u < n; ++u) {
            for (const auto &[v, val] : g[u]) if (exists[v]++) return std::vector<T> { vals[v], val };
            for (const auto &[v, val] : g[u]) exists[v] = 0;
        }
    }
    // simulate dfs
    std::vector<int> itr(n, 0), stk, par(0);
    std::vector<T> vals;
    if constexpr (t == GraphType::UNDIRECTED) par.resize(n, -1);
    stk.reserve(n), vals.reserve(n);
    std::vector<uint8_t> in(n, false);
    for (int i = 0; i < n; ++i) {
        if (itr[i] == 0) stk.push_back(i), in[i] = true, vals.push_back(T{});
        while (stk.size()) {
            const int u = stk.back();
            if (itr[u] < int(g[u].size())) {
                const auto &[v, val] = g[u][itr[u]++];
                if constexpr (t == GraphType::UNDIRECTED) if (v == par[u]) continue;
                if (in[v]) {
                    const int idx = std::find(stk.begin(), stk.end(), v) - stk.begin();
                    vals[idx] = val;
                    vals.erase(vals.begin(), vals.begin() + idx);
                    return vals;
                }
                if (itr[v] == 0) {
                    stk.push_back(v), in[v] = true, vals.push_back(val);
                    if constexpr (t == GraphType::UNDIRECTED) par[v] = u;
                }
            } else stk.pop_back(), in[u] = false, vals.pop_back();
        }
    }
    return std::nullopt;
}

} // namespace suisen

#endif // SUISEN_CYCLE_DETECTION
