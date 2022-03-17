#ifndef SUISEN_BIPARTITE_GRAPH_RECOGNITION
#define SUISEN_BIPARTITE_GRAPH_RECOGNITION

#include <deque>
#include <optional>
#include <vector>

namespace suisen {
    static std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>>& g, int col0 = 0, int col1 = 1) {
        const int n = g.size();
        int uncolored = 2;
        while (uncolored == col0 or uncolored == col1) ++uncolored;
        std::vector<int> color(n, uncolored);
        for (int i = 0; i < n; ++i) {
            if (color[i] != uncolored) continue;
            color[i] = col0;
            std::deque<int> dq { i };
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : g[u]) {
                    if (color[v] == uncolored) {
                        dq.push_back(v);
                        color[v] = color[u] ^ col0 ^ col1;
                    } else if (color[v] == color[u]) {
                        return std::nullopt;
                    }
                }
            }
        }
        return color;
    }
} // namespace suisen


#endif // SUISEN_BIPARTITE_GRAPH_RECOGNITION
