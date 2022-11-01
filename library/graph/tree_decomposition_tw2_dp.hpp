#ifndef SUISEN_TREE_DECOMPOSITION_TW2_DP
#define SUISEN_TREE_DECOMPOSITION_TW2_DP

#include <functional>

#include "library/graph/tree_decomposition_tw2.hpp"

namespace suisen {
    enum class NodeType {
        LEAF,
        INTRODUCE,
        FORGET,
        JOIN
    };

    struct NiceDecompTree {
        static constexpr int root = 0;

        NiceDecompTree() = default;
        NiceDecompTree(std::vector<DecompNodeRooted>&& nodes) : _n(nodes.size()), _nodes(std::move(nodes)), _pst(_n, -1) {}
        NiceDecompTree(const std::vector<DecompNodeRooted>& nodes) : _n(nodes.size()), _nodes(nodes), _pst(_n, -1) {}
        NiceDecompTree(int n, const std::vector<std::pair<int, int>>& edges) : NiceDecompTree(*TreeDecompositionTW2{ n, edges }.nice_decomp()) {}
        NiceDecompTree(const std::vector<std::vector<int>>& g) : NiceDecompTree(*TreeDecompositionTW2{ g }.nice_decomp()) {}

        int size() const { return _n; }

        NodeType get_node_type(int i) const {
            if (_nodes[i].ch.size() == 0) return NodeType::LEAF;
            if (_nodes[i].ch.size() == 2) return NodeType::JOIN;
            if (_nodes[i].bag.size() > _nodes[_nodes[i].ch[0]].bag.size()) return NodeType::INTRODUCE;
            return NodeType::FORGET;
        }
        std::vector<NodeType> get_node_types() const {
            std::vector<NodeType> types(_n);
            for (int i = 0; i < _n; ++i) types[i] = get_node_type(i);
            return types;
        }

        const DecompNodeRooted& operator[](int i) const { return _nodes[i]; }
        DecompNodeRooted& operator[](int i) { return _nodes[i]; }

        template <typename T> T run_dp(
            std::function<T(const DecompNodeRooted& node, int leaf_vertex)> leaf,
            std::function<T(const DecompNodeRooted& node, const DecompNodeRooted& child_node, const T& child_result, int introduce_vertex)> introduce,
            std::function<T(const DecompNodeRooted& node, const DecompNodeRooted& child_node, const T& child_result, int forget_vertex)> forget,
            std::function<T(const DecompNodeRooted& node, const DecompNodeRooted& child_node_1, const T& child_result_1, const DecompNodeRooted& child_node_2, const T& child_result_2)> join
        ) const {
            prepare_post_order();
            std::vector<T> dp(_n);
            for (int i : _pst) {
                dp[i] = [&, this] {
                    switch (get_node_type(i)) {
                    case NodeType::LEAF:
                    {
                        return leaf(_nodes[i], _nodes[i].bag[0]);
                    }
                    case NodeType::INTRODUCE:
                    {
                        int j = _nodes[i].ch[0];
                        int sj = _nodes[j].bag.size();
                        int v = _nodes[i].bag[sj];
                        for (int k = 0; k < sj; ++k) if (_nodes[i].bag[k] != _nodes[j].bag[k]) {
                            v = _nodes[i].bag[k];
                            break;
                        }
                        return introduce(_nodes[i], _nodes[j], dp[j], v);
                    }
                    case NodeType::FORGET:
                    {
                        int j = _nodes[i].ch[0];
                        int si = _nodes[i].bag.size();
                        int v = _nodes[j].bag[si];
                        for (int k = 0; k < si; ++k) if (_nodes[i].bag[k] != _nodes[j].bag[k]) {
                            v = _nodes[j].bag[k];
                            break;
                        }
                        return forget(_nodes[i], _nodes[j], dp[j], v);
                    }
                    case NodeType::JOIN:
                    {
                        int j = _nodes[i].ch[0], k = _nodes[i].ch[1];
                        return join(_nodes[i], _nodes[j], dp[j], _nodes[k], dp[k]);
                    }
                    default:
                    {
                        assert(false);
                    }
                    }
                }();
            }
            return dp[root];
        }

    private:
        int _n;
        std::vector<DecompNodeRooted> _nodes;

        mutable std::vector<int> _pst;

        void prepare_post_order() const {
            if (_pst.empty() or _pst.front() >= 0) return;
            auto it = _pst.begin();
            std::vector<std::size_t> eid(_n, 0);
            for (int cur = root; cur >= 0;) {
                if (eid[cur] == _nodes[cur].ch.size()) {
                    *it++ = cur;
                    cur = _nodes[cur].par;
                } else {
                    cur = _nodes[cur].ch[eid[cur]++];
                }
            }
        }
    };
} // namespace suisen


#endif // SUISEN_TREE_DECOMPOSITION_TW2_DP
