#ifndef SUISEN_DEQUE_SUM
#define SUISEN_DEQUE_SUM

#include <cassert>
#include <vector>

/**
 * [Idea] reference : https://motsu-xe.hatenablog.com/entry/2021/05/13/224016
 * 
 * SWAG + simulate a deque with 2 stacks
 * 
 * [Operations] reference : https://www.slideshare.net/catupper/amortize-analysis-of-deque-with-2-stack
 * 
 * `l`, `r` is a stack of { value, sum }
 * 
 *     accumulate
 *    <----------  ------> fold values from inside
 *   (     l     ][  r    )
 * 
 * pop_front:
 *  1. `l` is not empty
 *    (   l ][  r  )   ->   ( l ][  r  )      # pop from `l`. O(1)
 *  2. `l` is empty
 *    (][    r     )   -> (   l ][  r  )      # split `r` at its middle point. amortized O(1)
 *    (   l ][  r  )   ->   ( l ][  r  )      # pop from `l`. O(1)
 * 
 * pop_back:
 *  1. `r` is not empty
 *    (  l  ][ r   )   ->   (   l ][ r )      # pop from `r`. O(1)
 *  2. `r` is empty
 *    (     l    ][)   ->   (  l  ][ r   )    # split `l` at its middle point. amortized O(1)
 *    (  l  ][ r   )   ->   (  l  ][ r )      # pop from `r`. O(1)
 * 
 * push_front:
 *    (  l  ][  r  )   -> (    l  ][  r  )    # push to `l`. O(1)
 * 
 * push_back:
 *    (  l  ][  r  )   ->   (  l  ][  r    )  # push to `r`. O(1)
 */

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct DequeAggregation {
        struct DequeAggregationIterator {
            using difference_type = int;
            using value_type = T;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = std::random_access_iterator_tag;

            using fi_iterator_type = typename std::vector<std::pair<value_type, value_type>>::const_reverse_iterator;
            using se_iterator_type = typename std::vector<std::pair<value_type, value_type>>::const_iterator;

            fi_iterator_type it_l;
            fi_iterator_type it_l_end;
            se_iterator_type it_r_begin;
            se_iterator_type it_r;

            DequeAggregationIterator& operator++() {
                if (it_l == it_l_end) ++it_r;
                else ++it_l;
                return *this;
            }
            DequeAggregationIterator operator++(int) { DequeAggregationIterator ret = *this; ++(*this); return ret; }
            DequeAggregationIterator& operator--() {
                if (it_r == it_r_begin) --it_l;
                else --it_r;
                return *this;
            }
            DequeAggregationIterator operator--(int) { DequeAggregationIterator ret = *this; --(*this); return ret; }
            DequeAggregationIterator& operator+=(difference_type dif) {
                if (dif < 0) return *this -= -dif;
                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end, it_r += dif - d;
                else it_l += dif;
                return *this;
            }
            DequeAggregationIterator operator+(difference_type dif) const { DequeAggregationIterator it = *this; it += dif; return it; }
            DequeAggregationIterator& operator-=(difference_type dif) {
                if (dif < 0) return *this += -dif;
                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l -= dif - d;
                else it_r -= dif;
                return *this;
            }
            DequeAggregationIterator operator-(difference_type dif) const { DequeAggregationIterator it = *this; it -= dif; return it; }
            difference_type operator-(const DequeAggregationIterator &rhs) const {
                difference_type d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;
                difference_type d2 = rhs.it_l == rhs.it_l_end ? rhs.it_r - rhs.it_r_begin : rhs.it_l - rhs.it_l_end;
                return d1 - d2;
            }
            const value_type& operator[](difference_type i) const { return *((*this) + i); }
            const value_type& operator*() const { return it_l == it_l_end ? it_r->first : it_l->first; }
            bool operator!=(const DequeAggregationIterator &rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }
            bool operator==(const DequeAggregationIterator &rhs) const { return not (*this != rhs); }
            bool operator<(const DequeAggregationIterator &rhs) const { return (*this) - rhs < 0; }
            bool operator<=(const DequeAggregationIterator &rhs) const { return (*this) - rhs <= 0; }
            bool operator>(const DequeAggregationIterator &rhs) const { return (*this) - rhs > 0; }
            bool operator>=(const DequeAggregationIterator &rhs) const { return (*this) - rhs >= 0; }
        };
        
        using iterator = DequeAggregationIterator;
        using difference_type = typename iterator::difference_type;
        using value_type = typename iterator::value_type;
        using pointer = typename iterator::pointer;
        using reference = typename iterator::reference;

        DequeAggregation() = default;
        template <typename InputIterator, std::enable_if_t<std::is_constructible_v<value_type, typename InputIterator::value_type>, std::nullptr_t> = nullptr>
        DequeAggregation(InputIterator first, InputIterator last) {
            for (; first != last; ++first) push_back(*first);
        }
        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        DequeAggregation(const Container &c) : DequeAggregation(std::begin(c), std::end(c)) {}

        value_type prod() const {
            return op(prod(_st_l), prod(_st_r));
        }
        void push_back(const value_type &val) { _st_r.emplace_back(val, op(prod(_st_r), val)); }
        void push_front(const value_type &val) { _st_l.emplace_back(val, op(val, prod(_st_l))); }
        void pop_back() {
            if (_st_r.size()) return _st_r.pop_back();
            const int siz = _st_l.size();
            const int l = siz >> 1, r = siz - l;
            assert(r); // <=> siz > 0
            for (int i = r - 1; i > 0; --i) push_back(std::move(_st_l[i].first));
            _st_l.erase(_st_l.begin(), _st_l.begin() + r);
            if (l == 0) return;
            _st_l[0].second = _st_l[0].first;
            for (int i = 1; i < l; ++i) _st_l[i].second = op(_st_l[i].first, _st_l[i - 1].second);
        }
        void pop_front() {
            if (_st_l.size()) return _st_l.pop_back();
            const int siz = _st_r.size();
            const int r = siz >> 1, l = siz - r;
            assert(l); // <=> siz > 0
            for (int i = l - 1; i > 0; --i) push_front(std::move(_st_r[i].first));
            _st_r.erase(_st_r.begin(), _st_r.begin() + l);
            if (r == 0) return;
            _st_r[0].second = _st_r[0].first;
            for (int i = 1; i < r; ++i) _st_r[i].second = op(_st_r[i - 1].second, _st_r[i].first);
        }
        const value_type& front() const { return _st_l.size() ? _st_l.back().first : _st_r.front().first; }
        const value_type& back() const { return _st_r.size() ? _st_r.back().first : _st_l.front().first; }
        const value_type& operator[](int i) const {
            const int k = i - _st_l.size();
            return k < 0 ? _st_l[~k].first : _st_r[k].first;
        }

        int size() const { return _st_l.size() + _st_r.size(); }
        void clear() { _st_l.clear(), _st_r.clear(); }
        void shrink_to_fit() { _st_l.shrink_to_fit(), _st_r.shrink_to_fit(); }

        iterator begin() const { return iterator { _st_l.rbegin(), _st_l.rend(), _st_r.begin(), _st_r.begin() }; }
        iterator end() const { return iterator { _st_l.rend(), _st_l.rend(), _st_r.begin(), _st_r.end() }; }
        iterator cbegin() const { return begin(); }
        iterator cend() const { return end(); }

    private:
        std::vector<std::pair<value_type, value_type>> _st_l, _st_r;

        value_type prod(const std::vector<std::pair<value_type, value_type>> &st) const {
            return st.empty() ? e() : st.back().second;
        }
    };
} // namespace suisen


#endif // SUISEN_DEQUE_SUM
