#ifndef SUISEN_KRUSCAL
#define SUISEN_KRUSCAL

#include <queue>
#include <atcoder/dsu>

namespace suisen {
// Cost: a type represents weights of edges i.e. (unsigned) int, (unsigned) long long, ...
template <typename Cost>
class minimum_spanning_tree {
    public:
        using edge = std::tuple<Cost, int, int>;
        minimum_spanning_tree(const int n) : _n(n), _m(0) {}
        minimum_spanning_tree(const int n, const int edge_num) : _n(n), _m(edge_num) {
            edges.reserve(edge_num);
        }
        void add_edge(const int u, const int v, const Cost cost) {
            edges.emplace_back(cost, u, v);
        }
        void add_edge(const edge &e) {
            edges.push_back(e);
        }
        /**
         * constructs the MST in O(ElogE) time using Kruskal's algprithm (E is the number of edges).
         * return: whether there exists MST or not (i.e. the graph is connected or not)
         */
        bool build() {
            _weight_sum = 0;
            if (_n == 0) {
                edges.clear();
                return true;
            }
            atcoder::dsu uf(_n);
            std::sort(edges.begin(), edges.end());
            for (int i = 0; i < edges.size(); ++i) {
                auto &[w, u, v] = edges[i];
                if (uf.same(u, v)) {
                    u = v = _n;
                } else {
                    uf.merge(u, v);
                    _weight_sum += w;
                }
            }
            edges.erase(
                std::remove_if(
                    edges.begin(), edges.end(), [this](auto &e) { return std::get<1>(e) == _n; }
                ), edges.end()
            );
            return edges.size() == _n - 1;
        }
        /**
         * ! This must not be called before calling `solve()`.
         * return:
         * 1. connected: sum of weights of edges in the minimum spanning tree
         * 2. otherwise: sum of weights of edges in the minimum spanning forest
         */
        Cost get_minimum_weight() const {
            return _weight_sum;
        }
        /**
         * ! This must not be called before calling `solve()`.
         * return:
         * 1. connected: edges in the minimum spanning tree
         * 2. otherwise: edges in the minimum spanning forest
         * It is guaranteed that edges[i] <= edges[j] iff i <= j.
         */
        const std::vector<edge>& get_mst() const {
            return edges;
        }
    private:
        const int _n, _m;
        std::vector<edge> edges;
        Cost _weight_sum;
};
} // namespace suisen

#endif // SUISEN_KRUSCAL