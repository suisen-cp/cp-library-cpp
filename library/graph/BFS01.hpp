#ifndef SUISEN_BFS01
#define SUISEN_BFS01

#include <limits>
#include <map>
#include <queue>
#include <vector>

namespace suisen {
template <typename Node, typename Container>
class BFS01_base {
    protected:
        Container _dist;

        template <typename ...Args>
        BFS01_base(Args &&...args) : _dist(std::forward<Args>(args)...) {}

        virtual int get_dist(const Node &node) const = 0;

        template <typename Graph>
        void bfs(const std::vector<Node> &src_list, const Graph g) {
            std::deque<Node> dq;
            for (auto &src : src_list) {
                dq.push_back(src);
                _dist[src] = 0;
            }
            while (dq.size()) {
                Node u = dq.front(); dq.pop_front();
                g(u, [&](const Node &v, const bool cost) {
                    int old_dist = get_dist(v);
                    int new_dist = get_dist(u) + cost;
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
        static constexpr int INF = std::numeric_limits<int>::max();

        int operator[](const Node &node)   const { return get_dist(node); }
        bool is_reachable(const Node &node)   const { return get_dist(node) != INF; }
        bool is_unreachable(const Node &node) const { return get_dist(node) == INF; }
};

class BFS01 : public BFS01_base<int, std::vector<int>> {
    using base = BFS01_base<int, std::vector<int>>;
    public:
        template <typename Graph>
        BFS01(const int n, const int src, const Graph g) : base(n, this->INF) {
            this->bfs(std::vector<int>{src}, g);
        }
        template <typename Graph>
        BFS01(const int n, const std::vector<int> &src_list, const Graph g) : base(n, this->INF) {
            this->bfs(src_list, g);
        }
    protected:
        int get_dist(const int &node) const override {
            return this->_dist[node];
        }
};

template <typename Node>
class MapBFS01 : public BFS01_base<Node, std::map<Node, int>> {
    using base = BFS01_base<Node, std::map<Node, int>>;
    public:
        template <typename Graph>
        MapBFS01(const Node src, const Graph g) : base() {
            this->bfs(std::vector<Node>{src}, g);
        }
        template <typename Graph>
        MapBFS01(const std::vector<Node> &src_list, const Graph g) : base() {
            this->bfs(src_list, g);
        }
    protected:
        int get_dist(const Node &node) const override {
            return this->_dist.count(node) ? this->_dist.at(node) : this->INF;
        }
};
} // namespace suisen

#endif // SUISEN_BFS01
