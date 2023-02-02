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

        bool _rev = false;

        Node(const value_type val = {}): _val(val), _size(1), _priority(rng()) {}

        static void reserve(size_type capacity) { _nodes.reserve(capacity); }

        static node_type& node(node_pointer t) { return _nodes[t]; }
        static const node_type& const_node(node_pointer t) { return _nodes[t]; }

        static value_type& value(node_pointer t) { return node(t)._val; }
        static value_type set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t), new_val); }

        static bool empty(node_pointer t) { return t == null; }
        static size_type& size(node_pointer t) { return node(t)._size; }
        static size_type safe_size(node_pointer t) { return empty(t) ? 0 : size(t); }

        static priority_type priority(node_pointer t) { return const_node(t)._priority; }

        static node_pointer& child0(node_pointer t) { return node(t)._ch[0]; }
        static node_pointer& child1(node_pointer t) { return node(t)._ch[1]; }
        static node_pointer child(node_pointer t, bool b) { return node(t)._ch[b]; }
        static node_pointer set_child0(node_pointer t, node_pointer cid) { return std::exchange(child0(t), cid); }
        static node_pointer set_child1(node_pointer t, node_pointer cid) { return std::exchange(child1(t), cid); }

        static bool& reversed(node_pointer t) { return node(t)._rev; }

        static node_pointer update(node_pointer t) { // t : not null
            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;
            return t;
        }
        static bool push(node_pointer t) { // t : not null
            bool rev = t != null and std::exchange(reversed(t), false);
            if (rev) {
                reverse_all(child0(t));
                reverse_all(child1(t));
            }
            return rev;
        }

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
            if (t == null) return;
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
            if (t == null) {
                return { null, null };
            }
            node_type::push(t);
            if (k == 0) {
                return { null, t };
            }
            if (k == size(t)) {
                return { t, null };
            }
            if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                auto [ll, lr] = split(child0(t), k);
                set_child0(t, lr);
                return { ll, node_type::update(t) };
            } else {
                auto [rl, rr] = split(child1(t), k - (lsiz + 1));
                set_child1(t, rl);
                return { node_type::update(t), rr };
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
            if (t == null) {
                return { null, null };
            }
            node_type::push(t);
            if (f(value(t))) {
                auto [ll, lr] = split_binary_search(child0(t), f);
                set_child0(t, lr);
                return { ll, node_type::update(t) };
            } else {
                auto [rl, rr] = split_binary_search(child1(t), f);
                set_child1(t, rl);
                return { node_type::update(t), rr };
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

        static node_pointer merge(node_pointer tl, node_pointer tr) {
            if (tl == null or tr == null) {
                return tl ^ tr ^ null;
            }
            if (priority(tl) < priority(tr)) {
                node_type::push(tr);
                set_child0(tr, merge(tl, child0(tr)));
                return node_type::update(tr);
            } else {
                node_type::push(tl);
                set_child1(tl, merge(child1(tl), tr));
                return node_type::update(tl);
            }
        }
        static node_pointer merge(node_pointer tl, node_pointer tm, node_pointer tr) {
            return merge(merge(tl, tm), tr);
        }
        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer new_node) {
            if (t == null) {
                return new_node;
            }
            if (priority(new_node) > priority(t)) {
                auto [tl, tr] = split(t, k);
                set_child0(new_node, tl);
                set_child1(new_node, tr);
                return node_type::update(new_node);
            } else {
                node_type::push(t);
                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                    set_child0(t, insert_impl(child0(t), k, new_node));
                } else {
                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1), new_node));
                }
                return node_type::update(t);
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
            if (t == null) {
                return { new_node, 0 };
            }
            if (priority(new_node) > priority(t)) {
                auto [tl, tr] = split_binary_search(t, f);
                set_child0(new_node, tl);
                set_child1(new_node, tr);
                return { node_type::update(new_node), safe_size(tl) };
            } else {
                node_type::push(t);
                if (f(value(t))) {
                    auto [c0, pos] = insert_binary_search_impl(child0(t), f, new_node);
                    set_child0(t, c0);
                    return { node_type::update(t), pos };
                } else {
                    auto [c1, pos] = insert_binary_search_impl(child1(t), f, new_node);
                    set_child1(t, c1);
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
                return { node_type::update(t), std::move(v) };
            } else {
                auto [c1, v] = erase(child1(t), k - (lsiz + 1));
                set_child1(t, c1);
                return { node_type::update(t), std::move(v) };
            }
        }
        static std::pair<node_pointer, value_type> pop_front(node_pointer t) { return erase(t, 0); }
        static std::pair<node_pointer, value_type> pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }

        // Erase the first element that satisfies the condition f if it also satisfies the condition g.
        // returns { node, optional(position, value) }
        template <typename Predicate, typename RemovePredicate>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_binary_search(node_pointer t, const Predicate& f, const RemovePredicate& g) {
            if (t == null) return { null, std::nullopt };
            node_type::push(t);
            if (f(value(t))) {
                auto [c0, erased] = erase_binary_search(child0(t), f, g);
                if (erased) {
                    set_child0(t, c0);
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
                    size_type &pos = erased->first;
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

        static node_pointer reverse_all(node_pointer t) {
            if (t != null) {
                reversed(t) ^= true;
                std::swap(child0(t), child1(t));
            }
            return t;
        }
        static node_pointer reverse(node_pointer t, size_type l, size_type r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, Derived::reverse_all(tm), tr);
        }

        static std::vector<value_type> dump(node_pointer t) {
            std::vector<value_type> res;
            res.reserve(safe_size(t));
            auto rec = [&](auto rec, node_pointer t) -> void {
                if (t == null) return;
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
            if (res == null) {
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
            NodeIterator(node_pointer root, size_type index): root(root), index(index) {}

            reference operator*() const { return value(stk.back()); }
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

            static NodeIterator kth_iter(node_pointer t, size_type k) {
                NodeIterator it(t, k);
                if (k == safe_size(t)) return it;
                auto& stk = it.stk;
                while (t != null) {
                    node_type::push(t);
                    stk.push_back(t);
                    if (size_type siz = safe_size(child(t, reversed)); k == siz) {
                        break;
                    } else if (k < siz) {
                        t = child(t, reversed);
                    } else {
                        k -= siz + 1;
                        t = child(t, not reversed);
                    }
                }
                return it;
            }
        private:
            node_pointer root;
            size_type index;
            std::vector<node_pointer> stk;

            void up(const bool positive) {
                node_pointer t = stk.back();
                do {
                    stk.pop_back();
                    if (stk.empty() or t == child(stk.back(), not positive)) break;
                    t = stk.back();
                } while (stk.size());
            }
            void down(node_pointer t, size_type k, const bool positive) {
                while (true) {
                    node_type::push(t);
                    stk.push_back(t);

                    if (size_type siz = safe_size(child(t, not positive)); k == siz) {
                        break;
                    } else if (k < siz) {
                        t = child(t, not positive);
                    } else {
                        k -= siz + 1;
                        t = child(t, positive);
                    }
                }
            }
            void suc(difference_type k) {
                index += k;
                const bool positive = k < 0 ? (k = -k, reversed) : not reversed;
                if (k and stk.empty()) {
                    for (node_pointer t = root; t != null; t = child(t, not positive)) {
                        node_type::push(t);
                        stk.push_back(t);
                    }
                    --k;
                }
                while (k) {
                    node_pointer t = child(stk.back(), positive);
                    if (difference_type siz = safe_size(t); k > siz) {
                        up(positive);
                        k -= siz + 1;
                    } else {
                        down(t, k - 1, positive);
                        break;
                    }
                }
            }
        };
        using iterator = NodeIterator<false, false>;
        using reverse_iterator = NodeIterator<true, false>;
        using const_iterator = NodeIterator<false, true>;
        using const_reverse_iterator = NodeIterator<true, true>;

        static iterator begin(node_pointer t) { return ++iterator(t, -1); }
        static iterator end(node_pointer t) { return iterator(t, safe_size(t)); }
        static iterator kth_iterator(node_pointer t, size_type k) { return iterator::kth_iter(t, k); }
        static reverse_iterator rbegin(node_pointer t) { return ++reverse_iterator(t, -1); }
        static reverse_iterator rend(node_pointer t) { return reverse_iterator(t, safe_size(t)); }
        static reverse_iterator kth_reverse_iterator(node_pointer t, size_type k) { return reverse_iterator::kth_iter(t, k); }
        static const_iterator cbegin(node_pointer t) { return ++const_iterator(t, -1); }
        static const_iterator cend(node_pointer t) { return const_iterator(t, safe_size(t)); }
        static const_iterator kth_const_iterator(node_pointer t, size_type k) { return const_iterator::kth_iter(t, k); }
        static const_reverse_iterator crbegin(node_pointer t) { return ++const_reverse_iterator(t, -1); }
        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator(t, safe_size(t)); }
        static const_reverse_iterator kth_const_reverse_iterator(node_pointer t, size_type k) { return const_reverse_iterator::kth_iter(t, k); }
    };
} // namespace suisen::internal::implicit_treap

#endif // SUISEN_IMPLICIT_TREAP_BASE
