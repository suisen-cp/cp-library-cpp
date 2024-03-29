#ifndef SUISEN_REVERSIBLE_IMPLICIT_TREAP_LAZY_SEGTREE
#define SUISEN_REVERSIBLE_IMPLICIT_TREAP_LAZY_SEGTREE

#include "library/datastructure/bbst/reversible_implicit_treap_base.hpp"

#include "library/type_traits/operator.hpp"
#include "library/debug/warning.hpp"

namespace suisen {
    namespace internal::implicit_treap {
        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)()>
        struct ReversibleRangeOperateRangeProductNode: ReversibleNode<T, ReversibleRangeOperateRangeProductNode<T, op, e, toggle, F, mapping, composition, id>> {
            using base = ReversibleNode<T, ReversibleRangeOperateRangeProductNode<T, op, e, toggle, F, mapping, composition, id>>;
            using node_pointer = typename base::node_pointer;
            using value_type = typename base::value_type;
            using operator_type = F;

            value_type _sum;
            operator_type _laz;
            ReversibleRangeOperateRangeProductNode(const value_type& val): base(val), _sum(val), _laz(id()) {}

            // ----- override ----- //
            static node_pointer update(node_pointer t) {
                base::update(t);
                prod_all(t) = op(op(safe_prod(base::child0(t)), base::value(t)), safe_prod(base::child1(t)));
                return t;
            }
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
                    static warning warning_("operator==(F, F) is not defined, so the performance maybe worse.");
                    apply_all(base::child0(t), laz);
                    apply_all(base::child1(t), laz);
                    laz = id();
                }
            }
            static node_pointer reverse_all(node_pointer t) {
                if (t) {
                    base::reversed(t) ^= true;
                    std::swap(base::child0(t), base::child1(t));
                    value_type& sum = prod_all(t);
                    sum = toggle(sum);
                }
                return t;
            }

            // ----- new features ----- //
            static value_type& prod_all(node_pointer t) {
                return t->_sum;
            }
            static value_type safe_prod(node_pointer t) {
                return t ? t->_sum : e();
            }
            static std::pair<node_pointer, value_type> prod(node_pointer t, size_t l, size_t r) {
                auto [tl, tm, tr] = base::split(t, l, r);
                value_type res = safe_prod(tm);
                return { base::merge(tl, tm, tr), res };
            }

            static operator_type& lazy(node_pointer t) {
                return t->_laz;
            }
            static node_pointer apply_all(node_pointer t, const operator_type& f) {
                if (t) {
                    operator_type& laz = lazy(t);
                    laz = composition(f, laz);
                    value_type& val = base::value(t);
                    val = mapping(f, val, 1);
                    value_type& sum = prod_all(t);
                    sum = mapping(f, sum, base::size(t));
                }
                return t;
            }
            static node_pointer apply(node_pointer t, size_t l, size_t r, const operator_type& f) {
                auto [tl, tm, tr] = base::split(t, l, r);
                return base::merge(tl, apply_all(tm, f), tr);
            }

            template <typename Func>
            static node_pointer set(node_pointer t, size_t k, const Func& f) {
                return base::set_update(t, k, f);
            }

            template <typename Predicate>
            static uint32_t max_right(node_pointer t, const Predicate& f) {
                value_type sum = e();
                assert(f(sum));

                uint32_t r = 0;
                while (t) {
                    push(t);

                    node_pointer lch = base::child0(t);

                    value_type nxt_sum = op(sum, safe_prod(lch));
                    if (f(nxt_sum)) {
                        r += base::safe_size(lch);
                        sum = op(nxt_sum, base::value(t));
                        if (f(sum)) {
                            ++r;
                            t = base::child1(t);
                        } else {
                            break;
                        }
                    } else {
                        t = lch;
                    }
                }
                return r;
            }
            template <typename Predicate>
            static std::pair<node_pointer, uint32_t> max_right(node_pointer t, uint32_t l, const Predicate& f) {
                auto [tl, tr] = base::split(t, l);
                size_t w = max_right(tr, f);
                t = base::merge(tl, tr);
                return { t, l + w };
            }
            template <typename Predicate>
            static uint32_t min_left(node_pointer t, const Predicate& f) {
                value_type sum = e();
                assert(f(sum));

                uint32_t l = base::safe_size(t);
                while (t) {
                    push(t);

                    node_pointer rch = base::child1(t);

                    value_type nxt_sum = op(safe_prod(rch), sum);
                    if (f(nxt_sum)) {
                        l -= base::safe_size(rch);
                        sum = op(base::value(t), nxt_sum);
                        if (f(sum)) {
                            --l;
                            t = base::child0(t);
                        } else {
                            break;
                        }
                    } else {
                        t = rch;
                    }
                }
                return l;
            }
            template <typename Predicate>
            static std::pair<node_pointer, uint32_t> min_left(node_pointer t, uint32_t r, const Predicate& f) {
                auto [tl, tr] = base::split(t, r);
                size_t l = min_left(tl, f);
                t = base::merge(tl, tr);
                return { t, l };
            }
        };
    }

    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F, T, int), F(*composition)(F, F), F(*id)()>
    class ReversibleDynamicLazySegmentTree {
        using node_type = internal::implicit_treap::ReversibleRangeOperateRangeProductNode<T, op, e, toggle, F, mapping, composition, id>;
        using node_pointer = typename node_type::node_pointer;

        node_pointer _root;

        struct node_pointer_construct {};
        ReversibleDynamicLazySegmentTree(node_pointer root, node_pointer_construct): _root(root) {}

    public:
        using value_type = typename node_type::value_type;
        using operator_type = typename node_type::operator_type;

        ReversibleDynamicLazySegmentTree(): _root(node_type::empty_node()) {}
        explicit ReversibleDynamicLazySegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value)) {}
        template <typename U>
        ReversibleDynamicLazySegmentTree(const std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}

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
            return node_type::get(_root, k);
        }
        const value_type& front() const { return get(0); }
        const value_type& back() const { return get(size() - 1); }
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
        int insert_binary_search(const value_type& val, const Predicate& f) {
            int pos;
            std::tie(_root, pos) = node_type::insert_binary_search(_root, f, val);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than or equal to the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_lower_bound(const value_type& val, const Compare& comp = {}) {
            int pos;
            std::tie(_root, pos) = node_type::insert_lower_bound(_root, val, comp);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_upper_bound(const value_type& val, const Compare& comp = {}) {
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
        std::optional<std::pair<int, value_type>> erase_binary_search(const Predicate& f, const RemovePredicate& g) {
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
        std::optional<std::pair<int, value_type>> erase_lower_bound(const value_type& val, const Compare& comp = {}) {
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
        std::optional<std::pair<int, value_type>> erase_upper_bound(const value_type& val, const Compare& comp = {}) {
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
        std::optional<std::pair<int, value_type>> erase_if_exists(const value_type& val, const Compare& comp = {}) {
            auto [root, erased] = node_type::erase_if_exists(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }

        // Split immediately before the k-th element.
        ReversibleDynamicLazySegmentTree split(size_t k) {
            assert(k <= size_t(size()));
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(_root, k);
            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that satisfies the condition.
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        ReversibleDynamicLazySegmentTree split_binary_search(const Predicate& f) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_binary_search(_root, f);
            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than or equal to val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicLazySegmentTree split_lower_bound(const value_type& val, const Compare& comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_lower_bound(_root, val, comp);
            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicLazySegmentTree split_upper_bound(const value_type& val, const Compare& comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_upper_bound(_root, val, comp);
            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});
        }
        void merge(ReversibleDynamicLazySegmentTree r) { _root = node_type::merge(_root, r._root); }

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

        // Returns max{ r | f(op(A[l], ..., A[r-1])) = true }
        template <typename Predicate>
        int max_right(size_t l, const Predicate& f) {
            size_t res;
            std::tie(_root, res) = node_type::max_right(_root, l, f);
            return res;
        }
        // Returns min{ l | f(op(A[l], ..., A[r-1])) = true }
        template <typename Predicate>
        int min_left(size_t r, const Predicate& f) {
            size_t res;
            std::tie(_root, res) = node_type::min_left(_root, r, f);
            return res;
        }

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

        // handling internal nodes
        using internal_node = node_type;
        using internal_node_pointer = node_pointer;

        internal_node_pointer& root_node() { return _root; }
        const internal_node_pointer& root_node() const { return _root; }
        void set_root_node(internal_node_pointer new_root) { root_node() = new_root; }
    };
} // namespace suisen


#endif // SUISEN_REVERSIBLE_IMPLICIT_TREAP_LAZY_SEGTREE