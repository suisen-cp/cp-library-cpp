#ifndef SUISEN_DIJKSTRA
#define SUISEN_DIJKSTRA

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace suisen {
template<typename Cost>
class dijkstra {
    public:
        template <typename Transition>
        dijkstra(unsigned int n, Transition transition, unsigned int src) : _src(src) {
            _par.resize(n);
            _dist.assign(n, UNREACHABLE);
            _dist[src] = 0;
            using state = std::pair<Cost, unsigned int>;
            std::priority_queue<state, std::vector<state>, std::greater<state>> pq;
            pq.emplace(0, src);
            auto g = [&](unsigned int u) {
                return [&, u](unsigned int v, Cost new_cost) {
                    if (new_cost < _dist[v]) pq.emplace(_dist[v] = new_cost, v), _par[v] = u;
                };
            };
            while (pq.size()) {
                auto [du, u] = pq.top(); pq.pop();
                if (du == _dist[u]) transition(u, du, g(u));
            }
        }
        dijkstra(const std::vector<std::vector<std::pair<int, Cost>>> &g, unsigned int src) :
            dijkstra(g.size(), [&](int u, Cost du, auto f) { for (auto [v, c] : g[u]) f(v, du + c); }, src) {}
        std::vector<unsigned int> path_to(unsigned int t) const {
            assert(is_reachale(t));
            std::vector<unsigned int> path = {t};
            while (t != _src) path.push_back(t = _par[t]);
            std::reverse(path.begin(), path.end());
            return path;
        }
        Cost operator[](unsigned int t) const { return _dist[t]; }
        bool is_reachale   (unsigned int t) const { return _dist[t] != UNREACHABLE; }
        bool is_unreachable(unsigned int t) const { return _dist[t] == UNREACHABLE; }
    private:
        const Cost UNREACHABLE = std::numeric_limits<Cost>::max();
        const unsigned int _src;
        std::vector<Cost> _dist;
        std::vector<unsigned int> _par;
};
} // namespace suisen

#endif // SUISEN_DIJKSTRA
