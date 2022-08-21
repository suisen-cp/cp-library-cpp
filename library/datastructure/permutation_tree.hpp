#ifndef SUISEN_PERMUTATION_TREE
#define SUISEN_PERMUTATION_TREE

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace suisen {
    struct PermutationTree : std::vector<PermutationTree> {
        using base_type = std::vector<PermutationTree>;

        PermutationTree() : PermutationTree(0, 0, 0) {}

        PermutationTree(const std::vector<int>& p) : PermutationTree(build(p)) {}

        int length() const { return len; }

        int begin_index() const { return il; }
        int end_index() const { return il + len; }
        int min_index() const { return begin_index(); }
        int max_index() const { return end_index() - 1; }
        std::pair<int, int> get_index_range() const { return { begin_index(), end_index() }; }
        std::pair<int, int> get_index_range_closed() const { return { min_index(), max_index() }; }

        int begin_value() const { return vl; }
        int end_value() const { return vl + len; }
        int min_value() const { return begin_value(); }
        int max_value() const { return end_value() - 1; }
        std::pair<int, int> get_value_range() const { return { begin_value(), end_value() }; }
        std::pair<int, int> get_value_range_closed() const { return { min_value(), max_value() }; }

        bool is_join_node() const { return _is_join_node; }

        friend std::ostream& operator<<(std::ostream& out, const PermutationTree& t) {
            std::vector<std::string> lines;
            auto dfs = [&](auto dfs, const PermutationTree& u, std::size_t d) -> void {
                if (d >= lines.size()) lines.emplace_back(t.length(), ' ');
                if (u.length() == 1) {
                    lines[d][u.min_index()] = '|';
                } else {
                    if (u.is_join_node()) {
                        lines[d][u.min_index()] = '[';
                        lines[d][u.max_index()] = ']';
                    } else {
                        lines[d][u.min_index()] = '{';
                        lines[d][u.max_index()] = '}';
                    }
                }
                for (const auto& ch : u) dfs(dfs, ch, d + 1);
            };
            dfs(dfs, t, 0);
            for (const auto& line : lines) out << line << '\n';
            return out;
        }

    private:
        int len;
        int il, vl;
        bool _is_join_node;

        PermutationTree(int len, int il, int vl) : base_type(), len(len), il(il), vl(vl), _is_join_node(true) {}

        static std::vector<std::vector<int>> left_strong_intervals(const std::vector<int>& p) {
            const int n = p.size();

            struct DoublyLinkedList {
                using list_node_pointer = DoublyLinkedList*;
                int idx, delta, max_idx, min_idx;
                list_node_pointer prv = nullptr, nxt = nullptr;
                DoublyLinkedList(int idx) : idx(idx) {}
            };
            using list_node_pointer = DoublyLinkedList::list_node_pointer;
            list_node_pointer tail = nullptr;

            using minmax_stack = std::vector<std::pair<int, list_node_pointer>>;
            minmax_stack max_val, min_val;

            auto erase = [&](list_node_pointer node) -> list_node_pointer {
                list_node_pointer nxt = node->nxt, prv = node->prv;
                if (list_node_pointer& nl = max_val[node->max_idx].second; node == nl) nl = nxt and nxt->max_idx == node->max_idx ? nxt : nullptr;
                if (list_node_pointer& nl = min_val[node->min_idx].second; node == nl) nl = nxt and nxt->min_idx == node->min_idx ? nxt : nullptr;
                if (nxt) nxt->prv = prv, nxt->delta += node->delta;
                if (prv) prv->nxt = nxt;
                delete node;
                return nxt;
            };
            auto pop_tail = [&] { erase(std::exchange(tail, tail->prv)); };

            std::vector<std::vector<int>> select(n);
            for (int i = 0, pl = n; i < n; ++i) {
                while (tail and tail->idx > pl) pop_tail();
                list_node_pointer new_node = new DoublyLinkedList(i);
                auto rec_update = [&](auto rec_update, minmax_stack& vals, list_node_pointer nr, auto comp) -> bool {
                    if (vals.empty()) return false;
                    auto [val, nl] = vals.back();
                    if (comp(val, p[i])) return false;
                    vals.pop_back();
                    if (not nl) nl = nr;
                    if (not rec_update(rec_update, vals, nl, comp)) {
                        list_node_pointer new_tail = nullptr;
                        if (nl) {
                            new_tail = nl->prv;
                            nl->delta -= std::abs(val - p[i]);
                            while (nl != nr and nl->delta < 0) nl = erase(nl);
                            if (nl == nr) {
                                nl = new_node;
                            } else {
                                new_tail = nr ? nr->prv : tail;
                            }
                        } else {
                            nl = new_node;
                            new_tail = nr ? nr->prv : tail;
                        }
                        for (list_node_pointer cur = nr; cur;) cur = erase(cur);
                        vals.emplace_back(p[i], nl);
                        tail = new_tail;
                    }
                    return true;
                };
                if (not rec_update(rec_update, max_val, nullptr, std::greater<int>())) max_val.emplace_back(p[i], new_node);
                if (not rec_update(rec_update, min_val, nullptr, std::less<int>()))    min_val.emplace_back(p[i], new_node);
                new_node->max_idx = max_val.size() - 1;
                new_node->min_idx = min_val.size() - 1;

                auto splitter_num = [&](list_node_pointer node) {
                    return (max_val[node->max_idx].first - min_val[node->min_idx].first) - (i - node->idx);
                };

                if (tail) {
                    new_node->prv = tail;
                    tail->nxt = new_node;
                    new_node->delta = splitter_num(tail);
                } else {
                    new_node->delta = std::numeric_limits<int>::max() / 2;
                }
                tail = new_node;
                if (list_node_pointer& nl = min_val.back().second; not nl) nl = tail;
                if (list_node_pointer& nl = max_val.back().second; not nl) nl = tail;

                for (list_node_pointer cur = tail; cur and splitter_num(cur) == 0; cur = cur->prv) {
                    select[i].push_back(cur->idx);
                }
                pl = select[i].back();
            }
            while (tail) pop_tail();

            return select;
        }

        static std::vector<std::vector<int>> right_strong_intervals(std::vector<int> p) {
            const int n = p.size();
            std::reverse(p.begin(), p.end());
            std::vector<std::vector<int>> res(n);
            auto tmp = left_strong_intervals(p);
            for (int r = 0; r < n; ++r) for (int l : tmp[r]) res[n - l - 1].push_back(n - r - 1);
            return res;
        }

        static bool connectable(const std::pair<int, int>& p, const std::pair<int, int>& q) {
            return std::max(p.second, q.second) - std::min(p.first, q.first) == (p.second - p.first) + (q.second - q.first);
        }

        static PermutationTree build(const std::vector<int>& p) {
            const int n = p.size();
            std::vector<std::vector<int>> sel_l = left_strong_intervals(p);
            std::vector<std::vector<int>> sel_r = right_strong_intervals(p);

            std::vector<PermutationTree> ch;
            ch.reserve(n);

            // strong intervals are enumerated in post order of dfs.
            for (int r = 0; r < n; ++r) {
                // iterate on the intersection of sel_l[r] and sel_r[r]
                for (auto it1 = sel_l[r].cbegin(), end1 = sel_l[r].cend(), it2 = sel_r[r].cbegin(), end2 = sel_r[r].cend(); ; ++it1, ++it2) {
                    while (it1 != end1 and it2 != end2 and *it1 != *it2) ++(*it1 > *it2 ? it1 : it2);
                    if (it1 == end1 or it2 == end2) break;
                    const int l = *it1;
                    if (l == r) { // leaf
                        ch.push_back(PermutationTree(1, l, p[l]));
                        continue;
                    }
                    int vl = std::numeric_limits<int>::max();
                    auto it = ch.end();
                    while ((--it)->il != l) vl = std::min(vl, it->vl);
                    PermutationTree t(r - l + 1, l, std::min(vl, it->vl));
                    t.resize(ch.end() - it);
                    std::move(it, ch.end(), t.begin());
                    t._is_join_node = connectable(t[0].get_value_range(), t[1].get_value_range());
                    ch.erase(it, ch.end());
                    ch.push_back(std::move(t));
                }
            }
            return std::move(ch.back());
        }
    };
} // namespace suisen

#endif // SUISEN_PERMUTATION_TREE
