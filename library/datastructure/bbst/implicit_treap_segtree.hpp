#ifndef SUISEN_IMPLICIT_TREAP_SEGTREE
#define SUISEN_IMPLICIT_TREAP_SEGTREE

#include "library/datastructure/bbst/implicit_treap_base.hpp"

namespace suisen {
    namespace internal::implicit_treap {
        template <typename T, T(*op)(T, T), T(*e)()>
        struct RangeProductNode: Node<T, RangeProductNode<T, op, e>> {
            using base = Node<T, RangeProductNode<T, op, e>>;
            using node_pointer = typename base::node_pointer;
            using value_type = typename base::value_type;

            value_type _sum;
            RangeProductNode(const value_type& val): base(val), _sum(val) {}

            // ----- override ----- //
            static node_pointer update(node_pointer t) {
                base::update(t);
                prod_all(t) = op(op(safe_prod(base::child0(t)), base::value(t)), safe_prod(base::child1(t)));
                return t;
            }

            // ----- new features ----- //
            static value_type& prod_all(node_pointer t) {
                return base::node(t)._sum;
            }
            static value_type safe_prod(node_pointer t) {
                return base::is_null(t) ? e() : prod_all(t);
            }
            static std::pair<node_pointer, value_type> prod(node_pointer t, size_t l, size_t r) {
                auto [tl, tm, tr] = base::split(t, l, r);
                value_type res = safe_prod(tm);
                return { base::merge(tl, tm, tr), res };
            }
            template <typename Func>
            static node_pointer set(node_pointer t, size_t k, const Func& f) {
                return base::set_update(t, k, f);
            }

            using const_iterator = typename base::const_iterator;

            template <typename Predicate>
            static std::pair<node_pointer, const_iterator> max_right(node_pointer t, size_t l, const Predicate& f) {
                auto [tl, tr] = base::split(t, l);
                value_type sum = e();
                assert(f(sum));
                const_iterator it = base::template binary_search<const_iterator>(
                    tr, [&](const_iterator it) {
                        value_type nxt_sum = op(op(sum, safe_prod(it.get_child0())), *it);
                        return f(nxt_sum) ? (sum = std::move(nxt_sum), false) : true;
                    }
                );
                it.set_root(t = base::merge(tl, tr), l + it.index());
                return { t, it };
            }
            template <typename Predicate>
            static std::pair<node_pointer, const_iterator> min_left(node_pointer t, size_t r, const Predicate& f) {
                auto [tl, tr] = base::split(t, r);
                value_type sum = e();
                assert(f(sum));
                const_iterator it = base::template binary_search<const_iterator>(
                    tl, [&](const_iterator it) {
                        value_type nxt_sum = op(*it, op(safe_prod(it.get_child1()), sum));
                        return f(nxt_sum) ? (sum = std::move(nxt_sum), true) : false;
                    }
                );
                it.set_root(t = base::merge(tl, tr), it.index());
                return { t, it };
            }
        };
    }

    template <typename T, T(*op)(T, T), T(*e)()>
    class DynamicSegmentTree {
        using node_type = internal::implicit_treap::RangeProductNode<T, op, e>;
        using node_pointer = typename node_type::node_pointer;

        node_pointer _root;

        struct node_pointer_construct {};
        DynamicSegmentTree(node_pointer root, node_pointer_construct): _root(root) {}

    public:
        using value_type = typename node_type::value_type;

        DynamicSegmentTree(): _root(node_type::empty_node()) {}
        explicit DynamicSegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value)) {}
        template <typename U>
        DynamicSegmentTree(const std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}

        void free() {
            node_type::delete_tree(_root);
            _root = node_type::empty_node();
        }
        void clear() { free(); }

        static void reserve(size_t capacity) { node_type::reserve(capacity); }

        bool empty() const { return node_type::empty(_root); }
        int size() const { return node_type::safe_size(_root); }

        const value_type& operator[](size_t k) const { return get(k); }
        const value_type& get(size_t k) const {
            assert(k < size_t(size()));
            return cbegin()[k];
        }
        const value_type& front() const { return *cbegin(); }
        const value_type& back() const { return *crbegin(); }

        void set(size_t k, const value_type& val) {
            assert(k < size_t(size()));
            _root = node_type::set(_root, k, [&](const value_type&) { return val; });
        }
        template <typename Func>
        void apply(size_t k, const Func& f) {
            assert(k < size_t(size()));
            _root = node_type::set(_root, k, [&](const value_type& val) { return f(val); });
        }

        value_type prod_all() const { return node_type::safe_prod(_root); }
        value_type prod(size_t l, size_t r) {
            value_type res;
            std::tie(_root, res) = node_type::prod(_root, l, r);
            return res;
        }

        void insert(size_t k, const value_type& val) {
            assert(k <= size_t(size()));
            _root = node_type::insert(_root, k, val);
        }
        void push_front(const value_type& val) { insert(0, val); }
        void push_back(const value_type& val) { insert(size(), val); }

        value_type erase(size_t k) {
            assert(k <= size_t(size()));
            value_type v;
            std::tie(_root, v) = node_type::erase(_root, k);
            return v;
        }
        value_type pop_front() { return erase(0); }
        value_type pop_back() { return erase(size() - 1); }

        // Split immediately before the k-th element.
        DynamicSegmentTree split(size_t k) {
            assert(k <= size_t(size()));
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(_root, k);
            return DynamicSegmentTree(root_r, node_pointer_construct{});
        }

        void merge(DynamicSegmentTree r) { _root = node_type::merge(_root, r._root); }

        void rotate(size_t k) {
            assert(k <= size_t(size()));
            _root = node_type::rotate(_root, k);
        }
        void rotate(size_t l, size_t m, size_t r) {
            assert(l <= m and m <= r and r <= size_t(size()));
            _root = node_type::rotate(_root, l, m, r);
        }

        std::vector<value_type> dump() const { return node_type::dump(_root); }

        using iterator = typename node_type::const_iterator;
        using reverse_iterator = typename node_type::const_reverse_iterator;
        using const_iterator = typename node_type::const_iterator;
        using const_reverse_iterator = typename node_type::const_reverse_iterator;

        iterator begin() const { return cbegin(); }
        iterator end() const { return cend(); }
        reverse_iterator rbegin() const { return crbegin(); }
        reverse_iterator rend() const { return crend(); }
        const_iterator cbegin() const { return node_type::cbegin(_root); }
        const_iterator cend() const { return node_type::cend(_root); }
        const_reverse_iterator crbegin() const { return node_type::crbegin(_root); }
        const_reverse_iterator crend() const { return node_type::crend(_root); }

        // Returns the iterator with index max{ r | f(op(A[l], ..., A[r-1])) = true } (0 <= r <= size())
        template <typename Predicate>
        iterator max_right(size_t l, const Predicate& f) {
            assert(l <= size_t(size()));
            iterator it;
            std::tie(_root, it) = node_type::max_right(_root, l, f);
            return it;
        }
        // Returns the iterator with index min{ l | f(op(A[l], ..., A[r-1])) = true } (0 <= l <= size())
        template <typename Predicate>
        iterator min_left(size_t r, const Predicate& f) {
            assert(r <= size_t(size()));
            iterator it;
            std::tie(_root, it) = node_type::min_left(_root, r, f);
            return it;
        }

        // Find the first element that satisfies the condition f.
        // Returns { position, optional(value) }
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        iterator binary_search(const Predicate& f) {
            return node_type::template binary_search<iterator>(_root, f);
        }
        // comp(T t, U u) = (t < u)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        iterator lower_bound(const U& target, Compare comp = {}) {
            return node_type::template lower_bound<iterator>(_root, target, comp);
        }
        // comp(T u, U t) = (u < t)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        iterator upper_bound(const U& target, Compare comp = {}) {
            return node_type::template upper_bound<iterator>(_root, target, comp);
        }
        // Find the first element that satisfies the condition f.
        // Returns { position, optional(value) }
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        const_iterator binary_search(const Predicate& f) const {
            return node_type::template binary_search<const_iterator>(_root, f);
        }
        // comp(T t, U u) = (t < u)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        const_iterator lower_bound(const U& target, Compare comp = {}) const {
            return node_type::template lower_bound<const_iterator>(_root, target, comp);
        }
        // comp(T u, U t) = (u < t)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        const_iterator upper_bound(const U& target, Compare comp = {}) const {
            return node_type::template upper_bound<const_iterator>(_root, target, comp);
        }
 
        template <typename Iterator, std::enable_if_t<node_type::template is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        void insert(Iterator it, const value_type &val) {
            _root = node_type::insert(it, val);
        }
        template <typename Iterator, std::enable_if_t<node_type::template is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        value_type erase(Iterator it) {
            value_type erased;
            std::tie(_root, erased) = node_type::erase(it);
            return erased;
        }
        template <typename Iterator, std::enable_if_t<node_type::template is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>
        DynamicSegmentTree split(Iterator it) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(it);
            return DynamicSegmentTree(root_r, node_pointer_construct{});
        }

        // handling internal nodes
        using internal_node = node_type;
        using internal_node_pointer = node_pointer;

        internal_node_pointer& root_node() { return _root; }
        const internal_node_pointer& root_node() const { return _root; }
        void set_root_node(internal_node_pointer new_root) { root_node() = new_root; }
    };
} // namespace suisen


#endif // SUISEN_IMPLICIT_TREAP_SEGTREE
