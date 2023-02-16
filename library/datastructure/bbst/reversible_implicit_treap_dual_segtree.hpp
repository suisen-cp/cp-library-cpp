#ifndef SUISEN_REVERSIBLE_IMPLICIT_TREAP_DUAL_SEGTREE
#define SUISEN_REVERSIBLE_IMPLICIT_TREAP_DUAL_SEGTREE

#include "library/datastructure/bbst/reversible_implicit_treap_base.hpp"
#include "library/type_traits/operator.hpp"

namespace suisen {
    namespace internal::implicit_treap {
        template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
        struct ReversibleRangeOperateNode: ReversibleNode<T, ReversibleRangeOperateNode<T, F, mapping, composition, id>> {
            using base = ReversibleNode<T, ReversibleRangeOperateNode<T, F, mapping, composition, id>>;
            using node_pointer = typename base::node_pointer;
            using value_type = typename base::value_type;
            using operator_type = F;

            operator_type _laz;
            ReversibleRangeOperateNode(const value_type& val): base(val), _laz(id()) {}

            // ----- override ----- //
            static void push(node_pointer t) {
                base::push(t);
                operator_type& laz = lazy(t);
                if constexpr (has_operator_equal_to<operator_type>::value) {
                    if (not (laz == id())) {
                        operator_type& laz = lazy(t);
                        apply_all(base::child0(t), laz);
                        apply_all(base::child1(t), laz);
                        laz = id();
                    }
                } else {
                    apply_all(base::child0(t), laz);
                    apply_all(base::child1(t), laz);
                    laz = id();
                }
            }

            // ----- new features ----- //
            static operator_type& lazy(node_pointer t) {
                return base::node(t)._laz;
            }
            static node_pointer apply_all(node_pointer t, const operator_type& f) {
                if (t != base::null) {
                    operator_type& laz = lazy(t);
                    laz = composition(f, laz);
                    value_type& val = base::value(t);
                    val = mapping(f, val);
                }
                return t;
            }
            static node_pointer apply(node_pointer t, size_t l, size_t r, const operator_type& f) {
                auto [tl, tm, tr] = base::split(t, l, r);
                return base::merge(tl, apply_all(tm, f), tr);
            }
        };
    }

    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    class ReversibleDynamicDualSegmentTree {
        using node_type = internal::implicit_treap::ReversibleRangeOperateNode<T, F, mapping, composition, id>;
        using node_pointer = typename node_type::node_pointer;

        node_pointer _root;

        struct node_pointer_construct {};
        ReversibleDynamicDualSegmentTree(node_pointer root, node_pointer_construct): _root(root) {}

    public:
        using value_type = typename node_type::value_type;
        using operator_type = typename node_type::operator_type;

        ReversibleDynamicDualSegmentTree(): _root(node_type::empty_node()) {}
        explicit ReversibleDynamicDualSegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value)) {}
        template <typename U>
        ReversibleDynamicDualSegmentTree(const std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}

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
        value_type& front() { return (*this)[0]; }
        value_type& back() { return (*this)[size() - 1]; }
        const value_type& front() const { return (*this)[0]; }
        const value_type& back() const { return (*this)[size() - 1]; }

        void apply_all(const operator_type& f) { _root = node_type::apply_all(_root, f); }
        void apply(size_t l, size_t r, const operator_type& f) { _root = node_type::apply(_root, l, r, f); }

        void insert(size_t k, const value_type& val) {
            assert(k <= size_t(size()));
            _root = node_type::insert(_root, k, val);
        }
        void push_front(const value_type& val) { _root = node_type::push_front(_root, val); }
        void push_back(const value_type& val) { _root = node_type::push_back(_root, val); }

        // Insert a new value immediately before the first element that satisfies the condition f.
        // Returns: the inserted position
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        int insert_binary_search(const value_type& val, const Predicate &f) {
            int pos;
            std::tie(_root, pos) = node_type::insert_binary_search(_root, f, val);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than or equal to the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_lower_bound(const value_type& val, const Compare &comp = {}) {
            int pos;
            std::tie(_root, pos) = node_type::insert_lower_bound(_root, val, comp);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_upper_bound(const value_type& val, const Compare &comp = {}) {
            int pos;
            std::tie(_root, pos) = node_type::insert_upper_bound(_root, val, comp);
            return pos;
        }

        value_type erase(size_t k) {
            assert(k <= size_t(size()));
            value_type v;
            std::tie(_root, v) = node_type::erase(_root, k);
            return v;
        }
        value_type pop_front() { return erase(0); }
        value_type pop_back() { return erase(size() - 1); }

        // Erase the first element that satisfies the condition f if it also satisfies the condition g.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Predicate, typename RemovePredicate>
        std::optional<std::pair<int, value_type>> erase_binary_search(const Predicate &f, const RemovePredicate& g) {
            auto [root, erased] = node_type::erase_binary_search(_root, f, g);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is greater than or equal to val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_lower_bound(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_lower_bound(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is greater than val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_upper_bound(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_upper_bound(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is equal to val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_if_exists(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_if_exists(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }

        // Split immediately before the k-th element.
        ReversibleDynamicDualSegmentTree split(size_t k) {
            assert(k <= size_t(size()));
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(_root, k);
            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that satisfies the condition.
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        ReversibleDynamicDualSegmentTree split_binary_search(const Predicate &f) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_binary_search(_root, f);
            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than or equal to val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicDualSegmentTree split_lower_bound(const value_type &val, const Compare &comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_lower_bound(_root, val, comp);
            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicDualSegmentTree split_upper_bound(const value_type &val, const Compare &comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_upper_bound(_root, val, comp);
            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});
        }

        void merge(ReversibleDynamicDualSegmentTree r) { _root = node_type::merge(_root, r._root); }

        void rotate(size_t k) {
            assert(k <= size_t(size()));
            _root = node_type::rotate(_root, k);
        }
        void rotate(size_t l, size_t m, size_t r) {
            assert(l <= m and m <= r and r <= size_t(size()));
            _root = node_type::rotate(_root, l, m, r);
        }

        void reverse(size_t l, size_t r) {
            assert(l <= r and r <= size_t(size()));
            if (r - l >= 2) _root = node_type::reverse(_root, l, r);
        }
        void reverse_all() { _root = node_type::reverse_all(_root); }

        std::vector<value_type> dump() const { return node_type::dump(_root); }

        // Find the first element that satisfies the condition f.
        // Returns { position, optional(value) }
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        std::pair<int, std::optional<value_type>> binary_search(const Predicate& f) const {
            auto [pos, val] = node_type::binary_search(_root, f);
            return { pos, std::move(val) };
        }
        // comp(T t, U u) = (t < u)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        std::pair<int, std::optional<value_type>> lower_bound(const U& target, Compare comp = {}) const {
            auto [pos, val] = node_type::lower_bound(_root, target, comp);
            return { pos, std::move(val) };
        }
        // comp(T u, U t) = (u < t)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        std::pair<int, std::optional<value_type>> upper_bound(const U& target, Compare comp = {}) const {
            auto [pos, val] = node_type::upper_bound(_root, target, comp);
            return { pos, std::move(val) };
        }

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

        // handling internal nodes
        using internal_node = node_type;
        using internal_node_pointer = node_pointer;

        internal_node_pointer& root_node() { return _root; }
        const internal_node_pointer& root_node() const { return _root; }
        void set_root_node(internal_node_pointer new_root) { root_node() = new_root; }
    };
} // namespace suisen


#endif // SUISEN_REVERSIBLE_IMPLICIT_TREAP_DUAL_SEGTREE