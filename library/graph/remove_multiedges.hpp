#ifndef SUISEN_REMOVE_MULTIPLE_EDGES
#define SUISEN_REMOVE_MULTIPLE_EDGES

#include <algorithm>
#include <vector>
#include <cstdint>

namespace suisen {

void remove_multiedges(std::vector<std::vector<int>> &g) {
    std::vector<uint8_t> exists(g.size(), 0);
    auto rem_pred = [&](int v) {
        bool cond = not exists[v];
        exists[v] = false;
        return cond;
    };
    for (auto &vs : g) {
        for (int v : vs) exists[v] = true;
        vs.erase(std::remove_if(vs.begin(), vs.end(), rem_pred), vs.end());
    }
}

} // namespace suisen


#endif // SUISEN_REMOVE_MULTIPLE_EDGES
