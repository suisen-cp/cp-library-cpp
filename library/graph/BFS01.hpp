#ifndef SUISEN_BFS01
#define SUISEN_BFS01

#include <limits>
#include <map>
#include <queue>
#include <vector>

namespace suisen {
template <typename Cost, typename Node, typename Container>
class BFS01_base {
    protected:
        Container _dist;

        virtual Cost get_dist(const Node &node) const = 0;

        template <typename Iterable, typename Graph>
        auto bfs(const Iterable &src_list, const Graph g) -> decltype(src_list.begin(), src_list.end(), void()) {
            std::deque<Node> dq;
            for (auto &src : src_list) {
                dq.push_back(src);
                _dist[src] = 0;
            }
            while (dq.size()) {
                Node u = dq.front(); dq.pop_front();
                g(u, [&](const Node &v, const bool cost) {
                    Cost old_dist = get_dist(v);
                    Cost new_dist = get_dist(u) + cost;
                    if (new_dist < old_dist) {
                        _dist[v] = new_dist;
                        if (cost) {
                            dq.push_back(v);
                        } else {
                            dq.push_front(v);
                        }
                    }
                });
            }
        }
    public:
        static constexpr Cost INF = std::numeric_limits<Cost>::max();

        inline Cost operator[](const Node &node)   const { return get_dist(node); }
        inline bool is_reachable(const Node &node)   const { return get_dist(node) != INF; }
        inline bool is_unreachable(const Node &node) const { return get_dist(node) == INF; }
};

template <typename Cost, typename Node = unsigned int, typename Container = std::vector<Cost>>
class BFS01 : public BFS01_base<Cost, Node, Container> {
    using base = BFS01_base<Cost, Node, Container>;
    public:
        template <typename Graph>
        BFS01(const Node n, const Node src, const Graph g) : base::_dist(n, this->INF) { this->bfs(std::vector<Node>{src}, g); }
        template <typename Iterable, typename Graph>
        BFS01(const Node n, const Iterable &src_list, const Graph g) : base::_dist(n, this->INF) { this->bfs(src_list, g); }
    protected:
        inline Cost get_dist(const Node &node) const override { return this->_dist[node]; }
};

template <typename Cost, typename Node>
class BFS01<Cost, Node, std::map<Node, Cost>> : public BFS01_base<Cost, Node, std::map<Node, Cost>> {
    public:
        template <typename Graph>
        BFS01(const Node src, const Graph g) { this->bfs(std::vector<Node>{src}, g); }
        template <typename Iterable, typename Graph>
        BFS01(const Iterable &src_list, const Graph g) { this->bfs(src_list, g); }
    protected:
        inline Cost get_dist(const Node &node) const override { return this->_dist.count(node) ? this->_dist.at(node) : this->INF; }
};
} // namespace suisen

#endif // SUISEN_BFS01
