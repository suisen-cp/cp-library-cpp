#ifndef SUISEN_QUEUE_SUM
#define SUISEN_QUEUE_SUM

#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, typename SumType, SumType(*e)(), SumType(*append)(SumType, T), typename R, R(*merge)(SumType, SumType)>
    struct QueueAggregation {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        using sum_type = SumType;

    private:
        struct QueueAggregationIterator {
            using difference_type = int;
            using value_type = T;
            using pointer = const_pointer;
            using reference = const_reference;
            using iterator_category = std::random_access_iterator_tag;

        private:
            using fi_iterator_type = typename std::vector<std::pair<value_type, value_type>>::const_reverse_iterator;
            using se_iterator_type = typename std::vector<std::pair<value_type, value_type>>::const_iterator;
        public:

            fi_iterator_type it_l;
            fi_iterator_type it_l_end;
            se_iterator_type it_r_begin;
            se_iterator_type it_r;

            QueueAggregationIterator& operator++() {
                if (it_l == it_l_end) ++it_r;
                else ++it_l;
                return *this;
            }
            QueueAggregationIterator operator++(int) { QueueAggregationIterator ret = *this; ++(*this); return ret; }
            QueueAggregationIterator& operator--() {
                if (it_r == it_r_begin) --it_l;
                else --it_r;
                return *this;
            }
            QueueAggregationIterator operator--(int) { QueueAggregationIterator ret = *this; --(*this); return ret; }
            QueueAggregationIterator& operator+=(difference_type dif) {
                if (dif < 0) return *this -= -dif;
                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end, it_r += dif - d;
                else it_l += dif;
                return *this;
            }
            friend QueueAggregationIterator operator+(QueueAggregationIterator it, difference_type dif) { it += dif; return it; }
            friend QueueAggregationIterator operator+(difference_type dif, QueueAggregationIterator it) { it += dif; return it; }
            QueueAggregationIterator& operator-=(difference_type dif) {
                if (dif < 0) return *this += -dif;
                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l -= dif - d;
                else it_r -= dif;
                return *this;
            }
            friend QueueAggregationIterator operator-(QueueAggregationIterator it, difference_type dif) { it -= dif; return it; }
            difference_type operator-(const QueueAggregationIterator& rhs) const {
                difference_type d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;
                difference_type d2 = rhs.it_l == rhs.it_l_end ? rhs.it_r - rhs.it_r_begin : rhs.it_l - rhs.it_l_end;
                return d1 - d2;
            }
            reference operator[](difference_type i) const { return *((*this) + i); }
            reference operator*() const { return it_l == it_l_end ? it_r->first : it_l->first; }
            bool operator!=(const QueueAggregationIterator& rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }
            bool operator==(const QueueAggregationIterator& rhs) const { return not (*this != rhs); }
            bool operator< (const QueueAggregationIterator& rhs) const { return (*this) - rhs < 0; }
            bool operator<=(const QueueAggregationIterator& rhs) const { return (*this) - rhs <= 0; }
            bool operator> (const QueueAggregationIterator& rhs) const { return (*this) - rhs > 0; }
            bool operator>=(const QueueAggregationIterator& rhs) const { return (*this) - rhs >= 0; }
        };
    
    public:
        using iterator = QueueAggregationIterator;
        using const_iterator = iterator;

        QueueAggregation() = default;
        template <typename InputIterator, std::enable_if_t<std::is_constructible_v<value_type, typename InputIterator::value_type>, std::nullptr_t> = nullptr>
        QueueAggregation(InputIterator first, InputIterator last) {
            for (; first != last; ++first) push_back(*first);
        }
        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type, typename Container::value_type>, std::nullptr_t> = nullptr>
        QueueAggregation(const Container& c): QueueAggregation(std::begin(c), std::end(c)) {}

        R prod() const {
            return merge(prod(_st_l), prod(_st_r));
        }
        void push_back(const value_type& val) { _st_r.emplace_back(val, append(prod(_st_r), val)); }
        void pop_front() {
            if (_st_l.size()) return _st_l.pop_back();
            const int siz = _st_r.size();
            assert(siz);
            for (int i = siz - 1; i > 0; --i) {
                value_type v = std::move(_st_r[i].first);
                _st_l.emplace_back(v, append(prod(_st_l), v));
            }
            _st_r.clear();
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

        iterator begin() const { return iterator{ _st_l.rbegin(), _st_l.rend(), _st_r.begin(), _st_r.begin() }; }
        iterator end() const { return iterator{ _st_l.rend(), _st_l.rend(), _st_r.begin(), _st_r.end() }; }
        iterator cbegin() const { return begin(); }
        iterator cend() const { return end(); }

    private:
        std::vector<std::pair<value_type, sum_type>> _st_l, _st_r;

        sum_type prod(const std::vector<std::pair<value_type, sum_type>>& st) const {
            return st.empty() ? e() : st.back().second;
        }
    };
} // namespace suisen


#endif // SUISEN_QUEUE_SUM
