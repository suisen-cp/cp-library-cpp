#ifndef SUISEN_CYCLE_DETECTION
#define SUISEN_CYCLE_DETECTION

#include <optional>
#include <vector>

namespace suisen {

std::optional<std::vector<int>> get_cycle_digraph(const std::vector<std::vector<int>> &g) {
    const int n = g.size();
    std::vector<int> index(n, -1);
    std::vector<char> vis(n, false);
    std::vector<int> st, it;
    st.reserve(n), it.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        index[i] = 0;
        vis[i] = true;
        st.push_back(i);
        it.push_back(0);
        while (st.size()) {
            const int u = st.back();
            if (it.back() == int(g[u].size())) {
                index[u] = -1;
                st.pop_back();
                it.pop_back();
                continue;
            }
            const int v = g[u][it.back()++];
            if (index[v] >= 0) {
                st.erase(st.begin(), st.begin() + index[v]);
                return st;
            }
            if (vis[v]) continue;
            index[v] = st.size();
            vis[v] = true;
            st.push_back(v);
            it.push_back(0);
        }
    }
    return std::nullopt;
}

} // namespace suisen


#endif // SUISEN_CYCLE_DETECTION
