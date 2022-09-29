#ifndef SUISEN_BINARY_HEAP
#define SUISEN_BINARY_HEAP

#include <algorithm>
#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

#include "library/datastructure/heap/heap_tag.hpp"

namespace suisen {
    namespace internal::heap {
        template <typename T, typename Comp, typename HeapTag>
        struct BinaryHeap {
            using value_type = T;
            using compare_type = Comp;
            using heap_tag = HeapTag;

            static constexpr bool is_min_heap = heap_tag::is_min_heap;
            static constexpr bool is_max_heap = heap_tag::is_max_heap;

            BinaryHeap() = default;
            BinaryHeap(const Comp& comp) : _comp(comp) {}

            template <typename InputIterator>
            BinaryHeap(InputIterator first, InputIterator last) : _dat(first, last) {
                construct_heap();
            }
            template <typename InputIterator>
            BinaryHeap(InputIterator first, InputIterator last, const Comp& comp) : _dat(first, last), _comp(comp) {
                construct_heap();
            }

            template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>
            BinaryHeap(const Iterable& dat) : BinaryHeap(dat.begin(), dat.end()) {}
            template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>
            BinaryHeap(const Iterable& dat, Comp& comp) : BinaryHeap(dat.begin(), dat.end(), comp) {}

            void reserve(int capacity) { _dat.reserve(capacity); }

            bool empty() const { return _dat.empty(); }
            int size() const { return _dat.size(); }

            void clear() { _dat.clear(); }
            void shrink_to_fit() { _dat.shrink_to_fit(); }

            void push(const value_type& v) {
                _dat.push_back(v);
                heapify_up(_dat.size() - 1);
            }
            template <typename ...Args>
            void emplace(Args &&...args) {
                push(value_type(std::forward<Args>(args)...));
            }

            const value_type& top() const {
                assert(_dat.size());
                return _dat.front();
            }

            value_type pop() {
                assert(_dat.size());
                // std::pop_heap(_dat.begin(), _dat.end(), [this](const value_type &x, const value_type &y) { return compare(y, x); });
                std::swap(_dat.front(), _dat.back());
                value_type res = std::move(_dat.back());
                _dat.pop_back();
                heapify_down(0);
                return res;
            }

            const std::vector<value_type>& data() const { return _dat; }
            std::vector<value_type>& data() { return _dat; }

            // @brief O(n)
            void construct_heap() {
                const int m = _dat.size() >> 1;
                for (int i = m - 1; i >= 0; --i) heapify_down(i);
            }

            // for debug
            void check_heap_property() const {
                const int n = _dat.size(), m = n >> 1;
                for (int i = 0; i < m; ++i) {
                    const int lch = 2 * i + 1, rch = 2 * i + 2;
                    if (lch < n) assert(not compare(_dat[lch], _dat[i]));
                    if (rch < n) assert(not compare(_dat[rch], _dat[i]));
                }
            }

        private:
            std::vector<value_type> _dat;
            compare_type _comp;

            void heapify_up(const int leaf, const int root = 0) {
                int cur = leaf;
                value_type val = std::move(_dat[cur]);
                while (cur != root) {
                    int par = (cur - 1) >> 1;
                    if (not compare(val, _dat[par])) break;
                    _dat[std::exchange(cur, par)] = std::move(_dat[par]);
                }
                _dat[cur] = std::move(val);
            }
            void heapify_down(const int root) {
                const int n = _dat.size(), m = n >> 1;
                int cur = root;
                value_type val = std::move(_dat[cur]);
                while (cur < m) {
                    int ch = (cur << 1) + 1;
                    ch += ch + 1 < n and compare(_dat[ch + 1], _dat[ch]);
                    if (not compare(_dat[ch], val)) break;
                    _dat[cur] = std::move(_dat[ch]);
                    cur = ch;
                }
                _dat[cur] = std::move(val);
                // heapify_up(cur, root);
            }

            bool compare(const T& lhs, const T& rhs) const {
                if constexpr (is_min_heap) {
                    return _comp(lhs, rhs);
                } else {
                    return _comp(rhs, lhs);
                }
            }
        };
    }
    template <
        typename T, typename Comp = std::less<T>,
        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t> = nullptr
    >
    using MinBinaryHeap = internal::heap::BinaryHeap<T, Comp, min_heap_tag>;
    template <
        typename T, typename Comp = std::less<T>,
        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t> = nullptr
    >
    using MaxBinaryHeap = internal::heap::BinaryHeap<T, Comp, max_heap_tag>;
} // namespace suisen


#endif // SUISEN_BINARY_HEAP
