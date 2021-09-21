#ifndef SUISEN_SEGMENT_TREE_GRAPH
#define SUISEN_SEGMENT_TREE_GRAPH

#include <cassert>
#include <type_traits>
#include <vector>

namespace suisen {

class SegmentTreeGraph {
    public:
        struct SegmentNode { const int order_id, l, r; };

        SegmentTreeGraph() : SegmentTreeGraph(0) {}
        SegmentTreeGraph(int n) : n(n), next_id(n), ceil_log2(n + 2, 0), is_invalid_node(n, false) {
            for (int i = 1, l = 0; i <= n + 1; ++i) {
                ceil_log2[i] = l;
                l += (i & -i) == i;
            }
            if (n) {
                for (int m = n / (-n & n) >> 1;; m >>= 1) {
                    is_invalid_node[m] = true;
                    if (m == 0) break;
                }
            }
        }

        int size() const {
            return next_id;
        }

        int add_order(const std::vector<int> &p) {
            assert(int(p.size()) == n);
            std::vector<int> seg(2 * n, -1);
            for (int i = 0; i < n; ++i) seg[n + i] = p[i];
            for (int i = 1; i < n; ++i) seg[i] = next_id++;
            segs.push_back(std::move(seg));
            return segs.size() - 1;
        }
        int add_order_identity() {
            std::vector<int> p(n);
            for (int i = 0; i < n; ++i) p[i] = i;
            return add_order(p);
        }

        bool is_segment_node(int node_id) const {
            return node_id >= n;
        }

        SegmentNode get_segment_node(int node_id) const {
            assert(node_id >= n);
            node_id -= n;
            int order_id = node_id / (n - 1);
            int k = node_id - order_id * (n - 1) + 1;
            int l = k << ceil_log2[(n + k - 1) / k], r = (k + 1) << ceil_log2[n / (k + 1) + 1];
            return SegmentNode { order_id, l - n, r - n };
        }
        SegmentNode operator[](int node_id) const {
            return get_segment_node(node_id);
        }

        // add_edge(parent, child_l, child_r)
        template <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge, int, int, int>, std::nullptr_t> = nullptr>
        void add_edges_to_children(AddEdge add_edge) {
            for (const auto &seg : segs) {
                for (int i = 1; i < n; ++i) {
                    if (is_invalid_node[i]) continue;
                    add_edge(seg[i], seg[i * 2 + 0], seg[i * 2 + 1]);
                }
            }
        }
        // add_edge(parent, child)
        template <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge, int, int>, std::nullptr_t> = nullptr>
        void add_edges_to_children(AddEdge add_edge) {
            for (const auto &seg : segs) {
                for (int i = 1; i < n; ++i) {
                    if (is_invalid_node[i]) continue;
                    add_edge(seg[i], seg[i * 2 + 0]);
                    add_edge(seg[i], seg[i * 2 + 1]);
                }
            }
        }

        // add_edge(from, to)
        template <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge, int, int>, std::nullptr_t> = nullptr>
        void add_edge(int from, SegmentNode to, AddEdge add_edge_func) {
            const auto &seg = segs[to.order_id];
            for (int lk = to.l + n, rk = to.r + n; lk < rk; lk >>= 1, rk >>= 1) {
                if (lk & 1) add_edge_func(from, seg[lk++]);
                if (rk & 1) add_edge_func(from, seg[--rk]);
            }
        }

    private:
        int n;
        int next_id;
        std::vector<int> ceil_log2;
        std::vector<char> is_invalid_node;
        std::vector<std::vector<int>> segs;
};

} // namespace suisen


#endif // SUISEN_SEGMENT_TREE_GRAPH
