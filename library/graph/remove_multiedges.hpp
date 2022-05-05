#ifndef SUISEN_REMOVE_MULTIPLE_EDGES
#define SUISEN_REMOVE_MULTIPLE_EDGES

#include <algorithm>
#include <vector>
#include <cstdint>

namespace suisen {

void remove_multiedges(std::vector<std::vector<int>> &g) {
    std::vector<uint8_t> exists(g.size(), 0);
    for (auto &vs : g) {
        for (int v : vs) exists[v] = true;
        vs.erase(std::remove_if(vs.begin(), vs.end(), [&](int v) { return not std::exchange(exists[v], false); }), vs.end());
    }
}

} // namespace suisen


#endif // SUISEN_REMOVE_MULTIPLE_EDGES
