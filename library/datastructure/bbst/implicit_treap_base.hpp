#ifndef SUISEN_IMPLICIT_TREAP_BASE
#define SUISEN_IMPLICIT_TREAP_BASE

#include <algorithm>
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

        using priority_type = std::invoke_result_t<random_engine>;

        static priority_type random_priority() { return rng(); }

        using node_type = Derived;
        using node_pointer = uint32_t;

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

        Node(const value_type val = {}): _val(val), _size(1), _priority(random_priority()) {}

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

        static priority_type& priority(node_pointer t) { return node(t)._priority; }
        static void set_priority(node_pointer t, priority_type new_priority) { priority(t) = new_priority; }

        static node_pointer& prev(node_pointer t) { return node(t)._prev; }
        static node_pointer& next(node_pointer t) { return node(t)._next; }
        static void link(node_pointer l, node_pointer r) { next(l) = r, prev(r) = l; }

        static node_pointer min(node_pointer t) {
            while (true) {
                node_pointer nt = child0(t);
                if (is_null(nt)) return t;
                t = nt;
            }
        }
        static node_pointer max(node_pointer t) {
            while (true) {
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
            std::vector<value_type> dat(std::forward<Args>(args)...);

            const size_t n = dat.size();

            std::vector<priority_type> priorities(n);
            std::generate(priorities.begin(), priorities.end(), random_priority);
            std::make_heap(priorities.begin(), priorities.end());

            std::vector<node_pointer> nodes(n);

            auto rec = [&](auto rec, size_t heap_index, size_t dat_index_offset) -> std::pair<size_t, node_pointer> {
                if (heap_index >= n) return { 0, null };
                auto [lsiz, lch] = rec(rec, 2 * heap_index + 1, dat_index_offset);
                dat_index_offset += lsiz;
                node_pointer root = create_node(std::move(dat[dat_index_offset]));
                nodes[dat_index_offset] = root;
                set_priority(root, priorities[heap_index]);
                if (dat_index_offset) {
                    link(nodes[dat_index_offset - 1], root);
                }
                dat_index_offset += 1;
                auto [rsiz, rch] = rec(rec, 2 * heap_index + 2, dat_index_offset);
                set_child0(root, lch);
                set_child1(root, rch);
                return { lsiz + 1 + rsiz, node_type::update(root) };
            };
            return rec(rec, 0, 0).second;
        }

        static std::pair<node_pointer, node_pointer> split(node_pointer t, size_type k) {
            if (k == 0) return { null, t };
            if (k == size(t)) return { t, null };

            static std::vector<node_pointer> lp{}, rp{};

            while (true) {
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

        static node_pointer merge_impl(node_pointer tl, node_pointer tr) {
            if (priority(tl) < priority(tr)) {
                if (node_pointer tm = child0(tr); is_null(tm)) {
                    link(max(tl), tr);
                    set_child0(tr, tl);
                } else {
                    set_child0(tr, merge(tl, tm));
                }
                return node_type::update(tr);
            } else {
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

        static std::pair<node_pointer, value_type> erase(node_pointer t, size_type k) {
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

        static node_pointer rotate(node_pointer t, size_type k) {
            auto [tl, tr] = split(t, k);
            return merge(tr, tl);
        }
        static node_pointer rotate(node_pointer t, size_type l, size_type m, size_type r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, rotate(tm, m - l), tr);
        }

        template <typename Func>
        static node_pointer set_update(node_pointer t, size_type k, const Func& f) {
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
                rec(rec, child0(t));
                res.push_back(value(t));
                rec(rec, child1(t));
            };
            rec(rec, t);
            return res;
        }

        template <bool reversed_, bool constant_>
        struct NodeIterator {
            static constexpr bool constant = constant_;
            static constexpr bool reversed = reversed_;

            friend Node;
            friend Derived;

            using difference_type = Node::difference_type;
            using value_type = Node::value_type;
            using pointer = std::conditional_t<constant, Node::const_pointer, Node::pointer>;
            using reference = std::conditional_t<constant, Node::const_reference, Node::reference>;
            using iterator_category = std::random_access_iterator_tag;

            NodeIterator(): NodeIterator(null) {}
            explicit NodeIterator(node_pointer root): NodeIterator(root, 0, null) {}
            NodeIterator(const NodeIterator<reversed, not constant>& it): NodeIterator(it._root, it._index, it._cur) {}

            reference operator*() const {
                if (is_null(_cur) and _index != safe_size(_root)) {
                    _cur = _root;
                    for (size_type k = _index;;) {
                        if (size_type siz = safe_size(child(_cur, reversed)); k == siz) {
                            break;
                        } else if (k < siz) {
                            _cur = child(_cur, reversed);
                        } else {
                            _cur = child(_cur, not reversed);
                            k -= siz + 1;
                        }
                    }
                }
                return value(_cur);
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

            friend difference_type operator-(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index - rhs._index; }

            friend bool operator==(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index == rhs._index; }
            friend bool operator!=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index != rhs._index; }
            friend bool operator<(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index < rhs._index; }
            friend bool operator>(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index > rhs._index; }
            friend bool operator<=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index <= rhs._index; }
            friend bool operator>=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index >= rhs._index; }

            static NodeIterator begin(node_pointer root) { return NodeIterator(root, 0, null); }
            static NodeIterator end(node_pointer root) { return NodeIterator(root, safe_size(root), null); }

            int size() const { return safe_size(_root); }
            int index() const { return _index; }
        private:
            node_pointer _root;
            size_type _index;
            mutable node_pointer _cur; // it==end() or uninitialized (updates only index)

            NodeIterator(node_pointer root, size_type index, node_pointer cur): _root(root), _index(index), _cur(cur) {}

            void suc(difference_type k) {
                _index += k;
                if (_index == safe_size(_root) or std::abs(k) >= 20) _cur = null;
                if (is_null(_cur)) return;

                const bool positive = k < 0 ? (k = -k, reversed) : not reversed;

                if (positive) {
                    while (k-- > 0) _cur = next(_cur);
                } else {
                    while (k-- > 0) _cur = prev(_cur);
                }
            }

            node_pointer root() const { return _root; }
            void set_root(node_pointer new_root, size_type new_index) { _root = new_root, _index = new_index; }

            node_pointer get_child0() const { return child0(_cur); }
            node_pointer get_child1() const { return child1(_cur); }

            template <typename Predicate>
            static NodeIterator binary_search(node_pointer t, const Predicate& f) {
                NodeIterator res(t, safe_size(t), null);
                if (is_null(t)) return res;

                NodeIterator it(t, safe_size(child0(t)), t);
                while (is_not_null(it._cur)) {
                    if (f(it)) {
                        res = it;
                        it._cur = it.get_child0();
                        it._index -= is_null(it._cur) ? 1 : safe_size(it.get_child1()) + 1;
                    } else {
                        it._cur = it.get_child1();
                        it._index += is_null(it._cur) ? 1 : safe_size(it.get_child0()) + 1;
                    }
                }
                return res;
            }

            size_type get_gap_index_left() const {
                if constexpr (reversed) return size() - index();
                else return index();
            }
            size_type get_element_index_left() const {
                if constexpr (reversed) return size() - index() - 1;
                else return index();
            }
        };
        using iterator = NodeIterator<false, false>;
        using reverse_iterator = NodeIterator<true, false>;
        using const_iterator = NodeIterator<false, true>;
        using const_reverse_iterator = NodeIterator<true, true>;

        template <typename>
        struct is_node_iterator: std::false_type {};
        template <bool reversed_, bool constant_>
        struct is_node_iterator<NodeIterator<reversed_, constant_>>: std::true_type {};
        template <typename X>
        static constexpr bool is_node_iterator_v = is_node_iterator<X>::value;

        static iterator begin(node_pointer t) { return iterator::begin(t); }
        static iterator end(node_pointer t) { return iterator::end(t); }
        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t); }
        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t); }
        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t); }
        static const_iterator cend(node_pointer t) { return const_iterator::end(t); }
        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t); }
        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t); }

        // Find the first element that satisfies the condition f : iterator -> { false, true }.
        // Returns const_iterator
        template <typename Iterator, typename Predicate, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static Iterator binary_search(node_pointer t, const Predicate& f) {
            return Iterator::binary_search(t, f);
        }
        // comp(T t, U u) = (t < u)
        template <typename Iterator, typename U, typename Compare = std::less<>, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static Iterator lower_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search<Iterator>(t, [&](Iterator it) { return not comp(*it, target); });
        }
        // comp(T u, U t) = (u < t)
        template <typename Iterator, typename U, typename Compare = std::less<>, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static Iterator upper_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search<Iterator>(t, [&](Iterator it) { return comp(target, *it); });
        }

        template <typename Iterator, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static node_pointer insert(Iterator it, const value_type& val) {
            return insert(it.root(), it.get_gap_index_left(), val);
        }
        template <typename Iterator, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static std::pair<node_pointer, value_type> erase(Iterator it) {
            return erase(it.root(), it.get_element_index_left());
        }
        template <typename Iterator, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        static std::pair<node_pointer, node_pointer> split(Iterator it) {
            return split(it.root(), it.get_gap_index_left());
        }
    };
} // namespace suisen::internal::implicit_treap

#endif // SUISEN_IMPLICIT_TREAP_BASE
