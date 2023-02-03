#ifndef SUISEN_IMPLICIT_TREAP_BASE
#define SUISEN_IMPLICIT_TREAP_BASE

#include <cassert>
#include <cstdint>
#include <optional>
#include <string>
#include <random>
#include <tuple>
#include <vector>
#include <utility>

namespace suisen::internal::implicit_treap {
    template <typename T, typename Derived>
    struct Node {
        using random_engine = std::mt19937;
        static inline random_engine rng{ std::random_device{}() };

        using node_type = Derived;
        using node_pointer = uint32_t;
        using priority_type = std::invoke_result_t<random_engine>;

        using size_type = uint32_t;

        using difference_type = int32_t;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;

        static inline std::vector<node_type> _nodes{};
        static inline std::vector<node_pointer> _erased{};

        static constexpr node_pointer null = ~node_pointer(0);

        node_pointer _ch[2]{ null, null };
        value_type _val;
        size_type _size;
        priority_type _priority;

        node_pointer _prev = null, _next = null;

        Node(const value_type val = {}): _val(val), _size(1), _priority(rng()) {}

        static void reserve(size_type capacity) { _nodes.reserve(capacity); }

        static bool is_null(node_pointer t) { return t == null; }
        static bool is_not_null(node_pointer t) { return not is_null(t); }

        static node_type& node(node_pointer t) { return _nodes[t]; }
        static const node_type& const_node(node_pointer t) { return _nodes[t]; }

        static value_type& value(node_pointer t) { return node(t)._val; }
        static value_type set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t), new_val); }

        static bool empty(node_pointer t) { return is_null(t); }
        static size_type& size(node_pointer t) { return node(t)._size; }
        static size_type safe_size(node_pointer t) { return empty(t) ? 0 : size(t); }

        static priority_type priority(node_pointer t) { return const_node(t)._priority; }

        static node_pointer& prev(node_pointer t) { return node(t)._prev; }
        static node_pointer& next(node_pointer t) { return node(t)._next; }
        static void link(node_pointer l, node_pointer r) { next(l) = r, prev(r) = l; }

        static node_pointer min(node_pointer t) {
            while (true) {
                node_type::push(t);
                node_pointer nt = child0(t);
                if (is_null(nt)) return t;
                t = nt;
            }
        }
        static node_pointer max(node_pointer t) {
            while (true) {
                node_type::push(t);
                node_pointer nt = child1(t);
                if (is_null(nt)) return t;
                t = nt;
            }
        }

        static node_pointer& child0(node_pointer t) { return node(t)._ch[0]; }
        static node_pointer& child1(node_pointer t) { return node(t)._ch[1]; }
        static node_pointer& child(node_pointer t, bool b) { return node(t)._ch[b]; }
        static node_pointer set_child0(node_pointer t, node_pointer cid) { return std::exchange(child0(t), cid); }
        static node_pointer set_child1(node_pointer t, node_pointer cid) { return std::exchange(child1(t), cid); }
        static node_pointer set_child(node_pointer t, bool b, node_pointer cid) { return std::exchange(child(t, b), cid); }

        static node_pointer update(node_pointer t) { // t : not null
            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;
            return t;
        }
        static void push(node_pointer) {}

        static node_pointer empty_node() { return null; }
        template <typename ...Args>
        static node_pointer create_node(Args &&...args) {
            if (_erased.size()) {
                node_pointer res = _erased.back();
                _erased.pop_back();
                node(res) = node_type(std::forward<Args>(args)...);
                return res;
            } else {
                node_pointer res = _nodes.size();
                _nodes.emplace_back(std::forward<Args>(args)...);
                return res;
            }
        }
        static void delete_node(node_pointer t) { _erased.push_back(t); }
        static void delete_tree(node_pointer t) {
            if (is_null(t)) return;
            delete_tree(child0(t));
            delete_tree(child1(t));
            delete_node(t);
        }

        template <typename ...Args>
        static node_pointer build(Args &&... args) {
            node_pointer res = empty_node();
            for (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {
                res = push_back(res, std::move(e));
            }
            return res;
        }

        static std::pair<node_pointer, node_pointer> split(node_pointer t, size_type k) {
            if (k == 0) return { null, t };
            if (k == size(t)) return { t, null };

            static std::vector<node_pointer> lp{}, rp{};

            while (true) {
                node_type::push(t);
                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                    if (rp.size()) set_child0(rp.back(), t);
                    rp.push_back(t);
                    if (k == lsiz) {
                        if (lp.size()) set_child1(lp.back(), child0(t));

                        node_pointer lt = set_child0(t, null), rt = null;

                        while (lp.size()) node_type::update(lt = lp.back()), lp.pop_back();
                        while (rp.size()) node_type::update(rt = rp.back()), rp.pop_back();

                        return { lt, rt };
                    }
                    t = child0(t);
                } else {
                    if (lp.size()) set_child1(lp.back(), t);
                    lp.push_back(t);
                    t = child1(t);
                    k -= lsiz + 1;
                }
            }
        }
        static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer t, size_type l, size_type r) {
            auto [tlm, tr] = split(t, r);
            auto [tl, tm] = split(tlm, l);
            return { tl, tm, tr };
        }
        // Split immediately before the first element that satisfies the condition.
        template <typename Predicate>
        static std::pair<node_pointer, node_pointer> split_binary_search(node_pointer t, const Predicate& f) {
            if (is_null(t)) {
                return { null, null };
            }
            node_type::push(t);
            if (f(value(t))) {
                auto [l, tl] = split_binary_search(child0(t), f);
                set_child0(t, tl);
                return { l, node_type::update(t) };
            } else {
                auto [tr, r] = split_binary_search(child1(t), f);
                set_child1(t, tr);
                return { node_type::update(t), r };
            }
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, node_pointer> split_lower_bound(node_pointer t, const value_type& target, const Compare& comp) {
            return split_binary_search(t, [&](const value_type& v) { return not comp(v, target); });
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, node_pointer> split_upper_bound(node_pointer t, const value_type& target, const Compare& comp) {
            return split_binary_search(t, [&](const value_type& v) { return comp(target, v); });
        }

        static node_pointer merge_impl(node_pointer tl, node_pointer tr) {
            if (priority(tl) < priority(tr)) {
                node_type::push(tr);
                if (node_pointer tm = child0(tr); is_null(tm)) {
                    link(max(tl), tr);
                    set_child0(tr, tl);
                } else {
                    set_child0(tr, merge(tl, tm));
                }
                return node_type::update(tr);
            } else {
                node_type::push(tl);
                if (node_pointer tm = child1(tl); is_null(tm)) {
                    link(tl, min(tr));
                    set_child1(tl, tr);
                } else {
                    set_child1(tl, merge(tm, tr));
                }
                return node_type::update(tl);
            }
        }
        static node_pointer merge(node_pointer tl, node_pointer tr) {
            if (is_null(tl)) return tr;
            if (is_null(tr)) return tl;
            return merge_impl(tl, tr);
        }
        static node_pointer merge(node_pointer tl, node_pointer tm, node_pointer tr) {
            return merge(merge(tl, tm), tr);
        }
        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer new_node) {
            if (is_null(t)) return new_node;
            static std::vector<node_pointer> st;
            bool b = false;

            while (true) {
                if (is_null(t) or priority(new_node) > priority(t)) {
                    if (is_null(t)) {
                        t = new_node;
                    } else {
                        auto [tl, tr] = split(t, k);
                        if (is_not_null(tl)) link(max(tl), new_node);
                        if (is_not_null(tr)) link(new_node, min(tr));
                        set_child0(new_node, tl);
                        set_child1(new_node, tr);
                        t = node_type::update(new_node);
                    }
                    if (st.size()) {
                        set_child(st.back(), b, t);
                        do t = node_type::update(st.back()), st.pop_back(); while (st.size());
                    }
                    return t;
                } else {
                    node_type::push(t);
                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                        if (k == lsiz) link(new_node, t);
                        st.push_back(t), b = false;
                        t = child0(t);
                    } else {
                        if (k == lsiz + 1) link(t, new_node);
                        st.push_back(t), b = true;
                        t = child1(t);
                        k -= lsiz + 1;
                    }
                }
            }
        }
        template <typename ...Args>
        static node_pointer insert(node_pointer t, size_type k, Args &&...args) {
            return insert_impl(t, k, create_node(std::forward<Args>(args)...));
        }
        template <typename ...Args>
        static node_pointer push_front(node_pointer t, Args &&...args) {
            return insert(t, 0, std::forward<Args>(args)...);
        }
        template <typename ...Args>
        static node_pointer push_back(node_pointer t, Args &&...args) {
            return insert(t, safe_size(t), std::forward<Args>(args)...);
        }

        // Insert a new node immediately before the first element that satisfies the condition.
        // Returns { node, position to insert }
        template <typename Predicate>
        static std::pair<node_pointer, size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer new_node) {
            if (is_null(t)) {
                return { new_node, 0 };
            }
            if (priority(new_node) > priority(t)) {
                auto [tl, tr] = split_binary_search(t, f);
                if (is_not_null(tl)) link(max(tl), t);
                if (is_not_null(tr)) link(min(tr), t);
                set_child0(new_node, tl);
                set_child1(new_node, tr);
                return { node_type::update(new_node), safe_size(tl) };
            } else {
                node_type::push(t);
                if (f(value(t))) {
                    auto [c0, pos] = insert_binary_search_impl(child0(t), f, new_node);
                    set_child0(t, c0);
                    if (is_null(next(new_node))) link(new_node, t);
                    return { node_type::update(t), pos };
                } else {
                    auto [c1, pos] = insert_binary_search_impl(child1(t), f, new_node);
                    set_child1(t, c1);
                    if (is_null(prev(new_node))) link(t, new_node);
                    return { node_type::update(t), pos + safe_size(child0(t)) + 1 };
                }
            }
        }
        template <typename Predicate, typename ...Args>
        static std::pair<node_pointer, size_type> insert_binary_search(node_pointer t, const Predicate& f, Args &&...args) {
            return insert_binary_search_impl(t, f, create_node(std::forward<Args>(args)...));
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, size_type> insert_lower_bound(node_pointer t, const value_type& v, Compare comp) {
            return insert_binary_search(t, [&](const value_type& x) { return not comp(x, v); }, v);
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, size_type> insert_upper_bound(node_pointer t, const value_type& v, Compare comp) {
            return insert_binary_search(t, [&](const value_type& x) { return comp(v, x); }, v);
        }

        static std::pair<node_pointer, value_type> erase(node_pointer t, size_type k) {
            node_type::push(t);
            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                delete_node(t);
                return { merge(child0(t), child1(t)), std::move(value(t)) };
            } else if (k < lsiz) {
                auto [c0, v] = erase(child0(t), k);
                set_child0(t, c0);
                if (is_not_null(c0) and k == lsiz - 1) link(max(c0), t);
                return { node_type::update(t), std::move(v) };
            } else {
                auto [c1, v] = erase(child1(t), k - (lsiz + 1));
                set_child1(t, c1);
                if (is_not_null(c1) and k == lsiz + 1) link(t, min(c1));
                return { node_type::update(t), std::move(v) };
            }
        }
        static std::pair<node_pointer, value_type> pop_front(node_pointer t) { return erase(t, 0); }
        static std::pair<node_pointer, value_type> pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }

        // Erase the first element that satisfies the condition f if it also satisfies the condition g.
        // returns { node, optional(position, value) }
        template <typename Predicate, typename RemovePredicate>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_binary_search(node_pointer t, const Predicate& f, const RemovePredicate& g) {
            if (is_null(t)) return { null, std::nullopt };
            node_type::push(t);
            if (f(value(t))) {
                auto [c0, erased] = erase_binary_search(child0(t), f, g);
                if (erased) {
                    set_child0(t, c0);
                    size_type& pos = erased->first;
                    if (is_not_null(c0) and pos == safe_size(c0)) link(max(c0), t);
                    return { node_type::update(t), std::move(erased) };
                } else if (g(value(t))) {
                    delete_node(t);
                    std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)), std::move(value(t)) };
                    return { merge(child0(t), child1(t)), std::move(erased_entry) };
                } else {
                    return { t, std::nullopt };
                }
            } else {
                auto [c1, erased] = erase_binary_search(child1(t), f, g);
                if (erased) {
                    set_child1(t, c1);
                    size_type& pos = erased->first;
                    if (is_not_null(c1) and pos == 0) link(t, min(c1));
                    pos += safe_size(child0(t)) + 1;
                    return { node_type::update(t), std::move(erased) };
                } else {
                    return { t, std::nullopt };
                }
            }
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_lower_bound(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return not comp(x, v); },
                [] { return true; }
            );
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_upper_bound(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return comp(v, x); },
                [] { return true; }
            );
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_if_exists(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return not comp(x, v); },
                [&](const value_type& x) { return not comp(v, x); }
            );
        }

        static node_pointer rotate(node_pointer t, size_type k) {
            auto [tl, tr] = split(t, k);
            return merge(tr, tl);
        }
        static node_pointer rotate(node_pointer t, size_type l, size_type m, size_type r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, rotate(tm, m - l), tr);
        }

        static value_type& get(node_pointer t, size_type k) {
            while (true) {
                node_type::push(t);
                if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                    return value(t);
                } else if (k < lsiz) {
                    t = child0(t);
                } else {
                    k -= lsiz + 1;
                    t = child1(t);
                }
            }
        }

        template <typename Func>
        static node_pointer set_update(node_pointer t, size_type k, const Func& f) {
            node_type::push(t);
            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                value_type& val = value(t);
                val = f(const_cast<const value_type&>(val));
            } else if (k < lsiz) {
                set_child0(t, set_update(child0(t), k, f));
            } else {
                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));
            }
            return node_type::update(t);
        }

        static std::vector<value_type> dump(node_pointer t) {
            std::vector<value_type> res;
            res.reserve(safe_size(t));
            auto rec = [&](auto rec, node_pointer t) -> void {
                if (is_null(t)) return;
                node_type::push(t);
                rec(rec, child0(t));
                res.push_back(value(t));
                rec(rec, child1(t));
            };
            rec(rec, t);
            return res;
        }

        // Find the first element that satisfies the condition f : (value, index) -> { false, true }.
        // Returns { optional(value), position }
        template <typename Predicate>
        static std::pair<size_type, std::optional<value_type>> binary_search(node_pointer t, const Predicate& f) {
            node_pointer res = null;
            int ng = -1, ok = safe_size(t);
            while (ok - ng > 1) {
                node_type::push(t);
                if (const int root = ng + safe_size(child0(t)) + 1; f(value(t), root)) {
                    res = t;
                    ok = root, t = child0(t);
                } else {
                    ng = root, t = child1(t);
                }
            }
            if (is_null(res)) {
                return { ok, std::nullopt };
            } else {
                return { ok, value(res) };
            }
        }

        // comp(T t, U u) = (t < u)
        template <typename U, typename Compare = std::less<>>
        static std::pair<size_type, std::optional<value_type>> lower_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search(t, [&](const value_type& v, int) { return not comp(v, target); });
        }
        // comp(T u, U t) = (u < t)
        template <typename U, typename Compare = std::less<>>
        static std::pair<size_type, std::optional<value_type>> upper_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search(t, [&](const value_type& v, int) { return comp(target, v); });
        }

        template <bool reversed_, bool constant_>
        struct NodeIterator {
            static constexpr bool constant = constant_;
            static constexpr bool reversed = reversed_;

            using difference_type = Node::difference_type;
            using value_type = Node::value_type;
            using pointer = std::conditional_t<constant, Node::const_pointer, Node::pointer>;
            using reference = std::conditional_t<constant, Node::const_reference, Node::reference>;
            using iterator_cateogory = std::random_access_iterator_tag;

            NodeIterator(): root(null), index(0) {}

            reference operator*() {
                if (is_null(cur) and index != safe_size(root)) {
                    cur = root;
                    for (size_type k = index;;) {
                        node_type::push(cur);
                        if (size_type siz = safe_size(child(cur, reversed)); k == siz) {
                            break;
                        } else if (k < siz) {
                            cur = child(cur, reversed);
                        } else {
                            cur = child(cur, not reversed);
                            k -= siz + 1;
                        }
                    }
                }
                return value(cur);
            }
            reference operator[](difference_type k) const { return *((*this) + k); }

            NodeIterator& operator++() { return *this += 1; }
            NodeIterator& operator--() { return *this -= 1; }
            NodeIterator& operator+=(difference_type k) { return suc(+k), * this; }
            NodeIterator& operator-=(difference_type k) { return suc(-k), * this; }
            NodeIterator operator++(int) { NodeIterator res = *this; ++(*this); return res; }
            NodeIterator operator--(int) { NodeIterator res = *this; --(*this); return res; }
            friend NodeIterator operator+(NodeIterator it, difference_type k) { return it += k; }
            friend NodeIterator operator+(difference_type k, NodeIterator it) { return it += k; }
            friend NodeIterator operator-(NodeIterator it, difference_type k) { return it -= k; }

            friend difference_type operator-(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index - rhs.index; }

            friend bool operator==(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index == rhs.index; }
            friend bool operator!=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index != rhs.index; }
            friend bool operator<(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index < rhs.index; }
            friend bool operator>(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index > rhs.index; }
            friend bool operator<=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index <= rhs.index; }
            friend bool operator>=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index >= rhs.index; }

            static NodeIterator begin(node_pointer root) { return NodeIterator(root, 0); }
            static NodeIterator end(node_pointer root) { return NodeIterator(root, safe_size(root)); }
        private:
            node_pointer root;
            size_type index;
            node_pointer cur = null; // it==end() or uninitialized (updates only index)

            NodeIterator(node_pointer root, size_type index): root(root), index(index) {}

            void suc(difference_type k) {
                index += k;
                if (index == safe_size(root) or std::abs(k) >= 10) cur = null;
                if (is_null(cur)) return;

                const bool positive = k < 0 ? (k = -k, reversed) : not reversed;

                if (positive) {
                    while (k-- > 0) cur = next(cur);
                } else {
                    while (k-- > 0) cur = prev(cur);
                }
            }
        };
        using iterator = NodeIterator<false, false>;
        using reverse_iterator = NodeIterator<true, false>;
        using const_iterator = NodeIterator<false, true>;
        using const_reverse_iterator = NodeIterator<true, true>;

        static iterator begin(node_pointer t) { return iterator::begin(t); }
        static iterator end(node_pointer t) { return iterator::end(t); }
        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t); }
        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t); }
        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t); }
        static const_iterator cend(node_pointer t) { return const_iterator::end(t); }
        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t); }
        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t); }
    };
} // namespace suisen::internal::implicit_treap

#endif // SUISEN_IMPLICIT_TREAP_BASE
