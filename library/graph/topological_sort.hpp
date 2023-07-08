#ifndef SUISEN_TOPOLOGICAL_SORT
#define SUISEN_TOPOLOGICAL_SORT

#include <queue>
#include <vector>

namespace suisen {
class topological_sort {
    public:
        topological_sort(const std::vector<std::vector<int>> &g): _n(g.size()) {
            build(g);
        }
        bool is_dag() const { return int(_ord.size()) == _n; }
        const std::vector<int>& sorted() const { return _ord; }
        int operator[](int i) const { return _ord[i]; }
    private:
        const int _n;
        std::vector<int> _ord;
        void build(const std::vector<std::vector<int>> &g) {
            std::vector<int> in(_n);
            for (auto &adj : g) for (int j : adj) ++in[j];
            std::deque<int> dq;
            for (int i = 0; i < _n; ++i) {
                if (in[i] == 0) dq.push_back(i);
            }
            _ord.reserve(_n);
            while (dq.size()) {
                int u = dq.front(); dq.pop_front();
                _ord.push_back(u);
                for (int v : g[u]) {
                    if (--in[v] == 0) dq.push_back(v);
                }
            }
        }
};
} // namespace suisen

#endif // SUISEN_TOPOLOGICAL_SORT