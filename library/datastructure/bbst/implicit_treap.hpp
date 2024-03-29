#ifndef SUISEN_IMPLICIT_TREAP
#define SUISEN_IMPLICIT_TREAP

#include "library/datastructure/bbst/implicit_treap_base.hpp"

namespace suisen {
    namespace internal::implicit_treap {
        template <typename T>
        struct DefaultNode: Node<T, DefaultNode<T>> {
            using base = Node<T, DefaultNode<T>>;
            using base::base;
        };
    }

    template <typename T>
    class DynamicArray {
        using node_type = internal::implicit_treap::DefaultNode<T>;
        using node_pointer = typename node_type::node_pointer;

        node_pointer _root;

        struct node_pointer_construct {};
        DynamicArray(node_pointer root, node_pointer_construct): _root(root) {}

    public:
        using value_type = typename node_type::value_type;

        DynamicArray(): _root(node_type::empty_node()) {}
        explicit DynamicArray(size_t n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value)) {}
        template <typename U>
        DynamicArray(const std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}

        void free() {
            node_type::delete_tree(_root);
            _root = node_type::empty_node();
        }
        void clear() { free(); }

        static void reserve(size_t capacity) { node_type::reserve(capacity); }

        bool empty() const { return node_type::empty(_root); }
        int size() const { return node_type::safe_size(_root); }

        value_type& operator[](size_t k) {
            assert(k < size_t(size()));
            return begin()[k];
        }
        const value_type& operator[](size_t k) const {
            assert(k < size_t(size()));
            return cbegin()[k];
        }
        value_type& front() { return *begin(); }
        value_type& back() { return *rbegin(); }
        const value_type& front() const { return *cbegin(); }
        const value_type& back() const { return *crbegin(); }

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
        DynamicArray split(size_t k) {
            assert(k <= size_t(size()));
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(_root, k);
            return DynamicArray(root_r, node_pointer_construct{});
        }

        void merge(DynamicArray r) { _root = node_type::merge(_root, r._root); }

        void rotate(size_t k) {
            assert(k <= size_t(size()));
            _root = node_type::rotate(_root, k);
        }
        void rotate(size_t l, size_t m, size_t r) {
            assert(l <= m and m <= r and r <= size_t(size()));
            _root = node_type::rotate(_root, l, m, r);
        }

        std::vector<value_type> dump() const { return node_type::dump(_root); }

        using iterator = typename node_type::iterator;
        using reverse_iterator = typename node_type::reverse_iterator;
        using const_iterator = typename node_type::const_iterator;
        using const_reverse_iterator = typename node_type::const_reverse_iterator;

        iterator begin() { return node_type::begin(_root); }
        iterator end() { return node_type::end(_root); }
        reverse_iterator rbegin() { return node_type::rbegin(_root); }
        reverse_iterator rend() { return node_type::rend(_root); }

        const_iterator begin() const { return cbegin(); }
        const_iterator end() const { return cend(); }
        const_reverse_iterator rbegin() const { return crbegin(); }
        const_reverse_iterator rend() const { return crend(); }
        const_iterator cbegin() const { return node_type::cbegin(_root); }
        const_iterator cend() const { return node_type::cend(_root); }
        const_reverse_iterator crbegin() const { return node_type::crbegin(_root); }
        const_reverse_iterator crend() const { return node_type::crend(_root); }

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
        DynamicArray split(Iterator it) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(it);
            return DynamicArray(root_r, node_pointer_construct{});
        }

        // handling internal nodes
        using internal_node = node_type;
        using internal_node_pointer = node_pointer;

        internal_node_pointer& root_node() { return _root; }
        const internal_node_pointer& root_node() const { return _root; }
        void set_root_node(internal_node_pointer new_root) { root_node() = new_root; }
    };
} // namespace suisen


#endif // SUISEN_IMPLICIT_TREAP
