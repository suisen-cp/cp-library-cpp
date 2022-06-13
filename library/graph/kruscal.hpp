#ifndef SUISEN_KRUSCAL
#define SUISEN_KRUSCAL

#include <atcoder/dsu>

namespace suisen {
    namespace internal::kruscal {
        // CostType: a type represents weights of edges i.e. (unsigned) int, (unsigned) long long, ...
        template <typename CostType, typename ComparatorType>
        struct KruscalMST {
            using cost_type = CostType;
            using edge_type = std::tuple<int, int, cost_type>;
            using comparator_type = ComparatorType;

            KruscalMST() : KruscalMST(0) {}
            explicit KruscalMST(const int n) : _n(n) {}

            void add_edge(const int u, const int v, const cost_type& cost) {
                _built = false;
                _edges.emplace_back(u, v, cost);
            }
            void add_edge(const edge_type& e) {
                _built = false;
                _edges.push_back(e);
            }
            /**
             * constructs the MST in O(ElogE) time using Kruskal's algprithm (E is the number of edges).
             * return: whether there exists MST or not (i.e. the graph is connected or not)
             */
            bool build() {
                _built = true;
                _weight_sum = 0;
                if (_n == 0) return true;
                atcoder::dsu uf(_n);
                std::sort(_edges.begin(), _edges.end(), [this](const auto& e1, const auto& e2) { return _comp(std::get<2>(e1), std::get<2>(e2)); });
                for (auto& [u, v, w] : _edges) {
                    if (uf.same(u, v)) {
                        u = v = _n;
                    } else {
                        uf.merge(u, v);
                        _weight_sum += w;
                    }
                }
                _edges.erase(std::remove_if(_edges.begin(), _edges.end(), [this](auto& e) { return std::get<0>(e) == _n; }), _edges.end());
                return int(_edges.size()) == _n - 1;
            }
            /**
             * ! This must not be called before calling `solve()`.
             * return:
             * 1. connected: sum of weights of edges in the minimum spanning tree
             * 2. otherwise: sum of weights of edges in the minimum spanning forest
             */
            cost_type get_weight() const {
                assert(_built);
                return _weight_sum;
            }
            /**
             * ! This must not be called before calling `solve()`.
             * return:
             * 1. connected: edges in the minimum spanning tree
             * 2. otherwise: edges in the minimum spanning forest
             * It is guaranteed that edges[i] <= edges[j] iff i <= j.
             */
            const std::vector<edge_type>& get_mst() const {
                assert(_built);
                return _edges;
            }
        private:
            int _n;
            cost_type _weight_sum;
            std::vector<edge_type> _edges;
            bool _built = false;
            comparator_type _comp{};
        };
    } // namespace internal::kruscal

    template <typename CostType>
    using KruscalMinimumSpanningTree = internal::kruscal::KruscalMST<CostType, std::less<CostType>>;
    template <typename CostType>
    using KruscalMaximumSpanningTree = internal::kruscal::KruscalMST<CostType, std::greater<CostType>>;
} // namespace suisen

#endif // SUISEN_KRUSCAL