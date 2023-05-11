#ifndef SUISEN_GET_TREE_PATH
#define SUISEN_GET_TREE_PATH

#include <vector>

namespace suisen {
    std::vector<int> get_tree_path(const std::vector<std::vector<int>>& g, int u, int v) {
        std::vector<int> res;
        auto dfs = [&](auto dfs, int cur, int par) -> bool {
            res.push_back(cur);
            if (cur == v) return true;
            for (int nxt : g[cur]) if (nxt != par and dfs(dfs, nxt, cur)) return true;
            res.pop_back();
            return false;
        };
        dfs(dfs, u, -1);
        return res;
    }
} // namespace suisen

#endif // SUISEN_GET_TREE_PATH
