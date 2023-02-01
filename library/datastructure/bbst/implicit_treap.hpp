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
            return node_type::get(_root, k);
        }
        const value_type& operator[](size_t k) const {
            assert(k < size_t(size()));
            return node_type::get(_root, k);
        }
        const value_type& front() const { return (*this)[0]; }
        const value_type& back() const { return (*this)[size() - 1]; }

        void insert(size_t k, const value_type& val) {
            assert(k <= size_t(size()));
            _root = node_type::insert(_root, k, val);
        }
        void push_front(const value_type& val) { _root = node_type::push_front(_root, val); }
        void push_back(const value_type& val) { _root = node_type::push_back(_root, val); }

        void erase(size_t k) {
            assert(k <= size_t(size()));
            _root = node_type::erase(_root, k);
        }
        void pop_front() { _root = node_type::pop_front(_root); }
        void pop_back() { _root = node_type::pop_back(_root); }

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

        void reverse(size_t l, size_t r) {
            assert(l <= r and r <= size_t(size()));
            if (r - l >= 2) _root = node_type::reverse(_root, l, r);
        }
        void reverse_all() { _root = node_type::reverse_all(_root); }

        std::vector<value_type> dump() const { return node_type::dump(_root); }

        // Returns the first i s.t. f(A[i]) = true by binary search.
        // Requirement: f(A[i]) is monotonic.
        template <typename Predicate>
        int binary_search_find_first(const Predicate& f) const { return node_type::binary_search(_root, f); }
        // comp(T t, U u) = (t < u)
        template <typename U, typename Compare = std::less<>>
        int lower_bound(const U& target, Compare comp = {}) { return node_type::lower_bound(_root, target, comp); }
        // comp(T u, U t) = (u < t)
        template <typename U, typename Compare = std::less<>>
        int upper_bound(const U& target, Compare comp = {}) { return node_type::upper_bound(_root, target, comp); }

        using iterator = typename node_type::iterator;
        using reverse_iterator = typename node_type::reverse_iterator;
        using const_iterator = typename node_type::const_iterator;
        using const_reverse_iterator = typename node_type::const_reverse_iterator;

        iterator begin() { return node_type::begin(_root); }
        iterator end() { return node_type::end(_root); }
        iterator kth_iterator(size_t k) { return node_type::kth_iterator(_root, k); }
        reverse_iterator rbegin() { return node_type::rbegin(_root); }
        reverse_iterator rend() { return node_type::rend(_root); }
        reverse_iterator kth_reverse_iterator(size_t k) { return node_type::kth_reverse_iterator(_root, k); }

        const_iterator begin() const { return cbegin(); }
        const_iterator end() const { return cend(); }
        const_iterator kth_iterator(size_t k) const { return kth_const_iterator(k); }
        const_reverse_iterator rbegin() const { return crbegin(); }
        const_reverse_iterator rend() const { return crend(); }
        const_reverse_iterator kth_reverse_iterator(size_t k) const { return kth_const_reverse_iterator(k); }
        const_iterator cbegin() const { return node_type::cbegin(_root); }
        const_iterator cend() const { return node_type::cend(_root); }
        const_iterator kth_const_iterator(size_t k) const { return node_type::kth_const_iterator(_root, k); }
        const_reverse_iterator crbegin() const { return node_type::crbegin(_root); }
        const_reverse_iterator crend() const { return node_type::crend(_root); }
        const_reverse_iterator kth_const_reverse_iterator(size_t k) const { return node_type::kth_const_reverse_iterator(_root, k); }
    };
} // namespace suisen


#endif // SUISEN_IMPLICIT_TREAP
