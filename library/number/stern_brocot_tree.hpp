#ifndef SUISEN_STERN_BROCOT_TREE
#define SUISEN_STERN_BROCOT_TREE

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

namespace suisen {
    template <typename Int, std::enable_if_t<std::is_integral_v<Int>, std::nullptr_t> = nullptr>
    struct sbt_node {
        // { a, b } <==> a/b
        using rational = std::pair<Int, Int>;
        using sbt_arc = bool;
        static constexpr sbt_arc Left = false, Right = true;
        using sbt_path = std::vector<std::pair<sbt_arc, Int>>;

        // 1/1
        sbt_node() = default;
        // a/b (a and b must be positive integer)
        sbt_node(Int a, Int b) : sbt_node() {
            assert(a > 0 and b > 0);
            // implicitly computes the continued fraction
            sbt_arc dir = a < b ? Left : Right;
            if (dir == Left) std::swap(a, b);
            for (; b; dir = not dir) {
                const Int q = a / b, r = a % b;
                // If r != 0: [...,1] ----(q   step)----> [...,q+1] = [...,q,1]
                // If r == 0: [...,1] ----(q-1 step)----> [...,q] (end)
                move_down(dir, q - (r == 0));
                a = b, b = r;
            }
        }
        // { a, b } <==> a/b
        sbt_node(const rational& x) : sbt_node(x.first, x.second) {}
        sbt_node(const sbt_path& path) : sbt_node() {
            for (const auto& [dir, first] : path) move_down(dir, first);
        }

        operator rational() const { return { _l.first + _r.first, _l.second + _r.second }; }
        // get the rational number
        rational get() const { return *this; }
        // { inf, sup } of the subtree
        std::pair<rational, rational> range() const { return { _l, _r }; }
        // path from the root node 1/1
        const sbt_path& path() const { return _path; }
        // distance from the root node 1/1
        Int depth() const { return _dep; }

        // lowest common ancestor
        static sbt_node lca(const sbt_node& a, const sbt_node& b) {
            const sbt_path& pa = a.path(), & pb = b.path();
            const int k = std::min(pa.size(), pb.size());
            sbt_node c;
            for (int i = 0; i < k; ++i) {
                if (pa[i] == pb[i]) {
                    c.move_down(pa[i].first, pa[i].second);
                } else {
                    if (pa[i].first == pb[i].first) {
                        // same direction but different lengths
                        c.move_down(pa[i].first, std::min(pa[i].second, pb[i].second));
                    }
                    break;
                }
            }
            return c;
        }
        // lowest common ancestor
        sbt_node lca(const sbt_node& other) { return lca(*this, other); }

        // distance from a to b
        static Int dist(const sbt_node& a, const sbt_node& b) {
            const sbt_node c = lca(a, b);
            return (a.depth() - c.depth()) + (b.depth() - c.depth());
        }
        // distance to another node
        Int dist(const sbt_node& other) { return dist(*this, other); }

        // Check if this is an ancestor of the given node
        bool is_ancestor_of(const sbt_node& a) const { return less(_l, a) and less(a, _r); }
        // Check if this is a descendant of the given node
        bool is_descendant_of(const sbt_node& a) const { return a.is_ancestor_of(*this); }

        // move k steps to the root node. returns true if 0<=k<=depth, false otherwise (and makes no change).
        bool move_up(Int k) {
            if (k < 0 or k > depth()) return false;
            while (k) {
                auto& [dir, first] = _path.back();
                const Int u = std::min(k, first);
                k -= u;
                _dep -= u;
                if (dir == Left) {
                    _r.first -= _l.first * u, _r.second -= _l.second * u;
                } else {
                    _l.first -= _r.first * u, _l.second -= _r.second * u;
                }
                first -= u;
                if (first == 0) _path.pop_back();
            }
            return true;
        }

        // move down k steps to the left
        void move_down_left(Int k) { move(Left, k); }
        // move down k steps to the right
        void move_down_right(Int k) { move(Right, k); }
        // move down k steps in the direction `dir`
        void move_down(sbt_arc dir, Int k) {
            assert(k >= 0);
            if (k == 0) return;
            if (_path.size() and _path.back().first == dir) {
                _path.back().second += k;
            } else {
                _path.emplace_back(dir, k);
            }
            _dep += k;
            if (dir == Left) {
                _r.first += _l.first * k, _r.second += _l.second * k;
            } else {
                _l.first += _r.first * k, _l.second += _r.second * k;
            }
        }

        // move k steps to the destination node. returns true if dist(this, dst)<=k, false otherwise (and makes no change).
        bool move_to(const sbt_node& dst, Int k) {
            const sbt_node a = lca(dst);
            const Int d1 = depth() - a.depth(), d2 = dst.depth() - a.depth();
            if (k <= d1) return move_up(k);
            if (k - d1 > d2) return false;
            *this = dst;
            return move_up(d2 - (k - d1));
        }

        friend bool operator==(const sbt_node& a, const sbt_node& b) { return a._l == b._l and a._r == b._r; }
        friend bool operator!=(const sbt_node& a, const sbt_node& b) { return not (a == b); }
        friend bool operator<(const sbt_node& a, const sbt_node& b) { return less(rational(a), rational(b)); }
        friend bool operator>(const sbt_node& a, const sbt_node& b) { return (b < a); }
        friend bool operator<=(const sbt_node& a, const sbt_node& b) { return not (b < a); }
        friend bool operator>=(const sbt_node& a, const sbt_node& b) { return not (a < b); }

        static int compare_in_order(const sbt_node& a, const sbt_node& b) {
            if (a == b) return 0;
            return a < b ? -1 : +1;
        }
        static int compare_pre_order(const sbt_node& a, const sbt_node& b) {
            if (a == b) return 0;
            if (a.is_ancestor_of(b)) return -1;
            if (b.is_ancestor_of(a)) return +1;
            return a < b ? -1 : +1;
        }
        static int compare_post_order(const sbt_node& a, const sbt_node& b) {
            if (a == b) return 0;
            if (a.is_ancestor_of(b)) return +1;
            if (b.is_ancestor_of(a)) return -1;
            return a < b ? -1 : +1;
        }

        // undirected
        static auto auxiliary_tree(std::vector<sbt_node> xs) {
            std::sort(xs.begin(), xs.end(), [](const sbt_node& a, const sbt_node& b) { return compare_pre_order(a, b) < 0; });
            xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

            const int k = xs.size();

            std::vector<std::vector<int>> g(k);

            std::vector<int> st{ 0 };
            for (int i = 0; i < k - 1; ++i) {
                const sbt_node w = lca(xs[i], xs[i + 1]);

                if (w != xs[i]) {
                    int id_last = st.back();
                    st.pop_back();
                    while (st.size() and w.depth() < xs[st.back()].depth()) {
                        int id_u = st.back();
                        g[id_u].push_back(id_last);
                        g[id_last].push_back(id_u);
                        id_last = id_u;
                        st.pop_back();
                    }
                    int id_w = xs.size();
                    if (st.empty() or xs[st.back()] != w) {
                        st.push_back(id_w);
                        xs.push_back(w);
                        g.emplace_back();
                    } else {
                        id_w = st.back();
                    }
                    g[id_w].push_back(id_last);
                    g[id_last].push_back(id_w);
                }
                st.push_back(i + 1);
            }
            if (k) assert(st.size());
            const int root = st.empty() ? 0 : st.front();
            const int siz = st.size();
            for (int i = 0; i < siz - 1; ++i) {
                g[st[i]].push_back(st[i + 1]);
                g[st[i + 1]].push_back(st[i]);
            }
            struct AuxiliaryTree {
                AuxiliaryTree(int root, const std::vector<sbt_node> &nodes, const std::vector<std::vector<int>> &g) : _root(root), _nodes(nodes), _g(g) {}
                
                int size() const { return _nodes.size(); }

                int root() const { return _root; }
                
                std::vector<int>& operator[](int i) { return _g[i]; }
                const std::vector<int>& operator[](int i) const { return _g[i]; }

                const sbt_node& node(int i) const { return _nodes[i]; }
                const std::vector<sbt_node>& nodes() const { return _nodes; }
            private:
                int _root;
                std::vector<sbt_node> _nodes;
                std::vector<std::vector<int>> _g;
            };
            return AuxiliaryTree{ root, std::move(xs), std::move(g) };
        }
    private:
        rational _l = rational{ 0, 1 }, _r = rational{ 1, 0 };
        Int _dep = 0;
        sbt_path _path{};

        static bool less(const rational& a, const rational& b) {
            using LInt = std::conditional_t<(std::numeric_limits<Int>::digits <= 32), uint64_t, __uint128_t>;
            return LInt(a.first) * b.second < LInt(b.first) * a.second;
        }
    };
}


#endif // SUISEN_STERN_BROCOT_TREE
