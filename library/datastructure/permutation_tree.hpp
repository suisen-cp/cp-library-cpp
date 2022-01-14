#ifndef SUISEN_PERMUTATION_TREE
#define SUISEN_PERMUTATION_TREE

#include <atcoder/lazysegtree>
#include <deque>
#include <iostream>
#include <limits>

namespace suisen {

    namespace internal::permutation_tree {
        using S = std::pair<int, int>;
        using F = int;
        S op(S x, S y) { return (x.first == y.first ? x.second > y.second : x.first < y.first) ? x : y; }
        S e() { return { std::numeric_limits<int>::max(), -1 }; }
        S mapping(F f, S x) { return { f + x.first, x.second }; }
        F composition(F f, F g) { return f + g; }
        F id() { return 0; }
        using RangeAddRangeMin = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
    }

    struct PermutationTree : std::vector<PermutationTree> {
        using base_type = std::vector<PermutationTree>;

        template <typename RandomAccessibleContainer>
        PermutationTree(const RandomAccessibleContainer& p) : PermutationTree(build(p)) {}

        int size() const { return vr - vl; }

        int begin_index() const { return idx; }
        int end_index() const { return idx + size(); }
        int min_index() const { return begin_index(); }
        int max_index() const { return end_index() - 1; }
        std::pair<int, int> get_index_range() const { return { begin_index(), end_index() }; }
        std::pair<int, int> get_index_range_closed() const { return { min_index(), max_index() }; }
    
        int begin_value() const { return vl; }
        int end_value() const { return vr; }
        int min_value() const { return begin_value(); }
        int max_value() const { return end_value() - 1; }
        std::pair<int, int> get_value_range() const { return { begin_value(), end_value() }; }
        std::pair<int, int> get_value_range_closed() const { return { min_value(), max_value() }; }

        bool is_join_node() const { return _is_join_node; }

        friend std::ostream& operator<<(std::ostream& out, const PermutationTree& t) {
            std::vector<std::string> lines;
            auto dfs = [&](auto dfs, const PermutationTree &u, std::size_t d) -> void {
                if (d >= lines.size()) lines.emplace_back(t.size(), ' ');
                if (u.size() == 1) {
                    lines[d][u.min_index()] = '|';
                } else {
                    lines[d][u.min_index()] = '[';
                    lines[d][u.max_index()] = ']';
                }
                for (const auto& ch : u) dfs(dfs, ch, d + 1);
            };
            dfs(dfs, t, 0);
            for (const auto& line : lines) out << line << '\n';
            return out;
        }

    private:
        int idx, vl, vr;
        bool _is_join_node;

        PermutationTree() : PermutationTree(0, 0, 0, false) {}
        template <typename ...Args>
        PermutationTree(int idx, int vl, int vr, bool is_join_node, Args &&...args) :
            base_type(std::forward<Args>(args)...), idx(idx), vl(vl), vr(vr), _is_join_node(is_join_node) {}

        bool try_add_child(const PermutationTree& node) {
            if (not is_join_node() or (node.vl != vr and node.vr != vl) or empty()) return false;
            int l0 = end()[-2].vl, l1 = end()[-1].vl, l2 = node.vl;
            if ((l0 < l1) ^ (l1 < l2)) return false;
            push_back(node);
            vl = std::min(vl, node.vl), vr = std::max(vr, node.vr);
            return true;
        }

        template <typename RandomAccessibleContainer>
        static PermutationTree build(const RandomAccessibleContainer& p) {
            std::vector<PermutationTree> st;
            const int n = p.size();

            internal::permutation_tree::RangeAddRangeMin seg(n);

            std::vector<std::pair<int, int>> max_val, min_val;

            for (int i = 0; i < n; ++i) {
                auto update = [&](std::vector<std::pair<int, int>>& vals, auto comp) {
                    seg.set(i, { i, i });
                    int start = i;
                    while (vals.size()) {
                        const auto& [val, idx] = vals.back();
                        if (comp(val, p[i])) break;
                        seg.apply(idx, start, std::abs(val - p[i]));
                        start = idx;
                        vals.pop_back();
                    }
                    vals.emplace_back(p[i], start);
                };
                update(max_val, std::greater<int>());
                update(min_val, std::less<int>());

                PermutationTree node{ i, p[i], p[i] + 1, true };
                while (true) {
                    if (st.empty()) break;
                    if (auto& top_node = st.back(); top_node.try_add_child(node)) {
                        node = std::move(top_node);
                        st.pop_back();
                    } else if (node.vl == top_node.vr or node.vr == top_node.vl) {
                        node = PermutationTree {
                            top_node.idx,
                            std::min(node.vl, top_node.vl),
                            std::max(node.vr, top_node.vr),
                            true,
                            std::vector<PermutationTree> { std::move(top_node), std::move(node) }
                        };
                        st.pop_back();
                    } else {
                        int st_sum = i + 1 - (node.vr - node.vl);
                        const auto& [val, idx] = seg.prod(0, st_sum);
                        if (val != i) break;
                        int vl = node.vl, vr = node.vr;
                        auto it = st.end();
                        for (int erase_num = st_sum - idx; erase_num;) {
                            --it;
                            erase_num -= it->vr - it->vl;
                            vl = std::min(vl, it->vl), vr = std::max(vr, it->vr);
                        }
                        std::vector<PermutationTree> ch;
                        std::move(it, st.end(), std::back_inserter(ch));
                        ch.push_back(std::move(node));
                        st.erase(it, st.end());
                        node = PermutationTree { ch.front().idx, vl, vr, false, std::move(ch) };
                    }
                }
                st.push_back(std::move(node));
            }
            return st.back();
        }
    };

} // namespace suisen


#endif // SUISEN_PERMUTATION_TREE
