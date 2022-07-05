#ifndef SUISEN_DEQUE_SUM
#define SUISEN_DEQUE_SUM

#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct DequeSum {
        using value_type = T;

        struct Iterator {
            using fi_iterator_type = typename std::vector<value_type>::const_reverse_iterator;
            using se_iterator_type = typename std::vector<value_type>::const_iterator;
            fi_iterator_type it_l;
            const fi_iterator_type it_l_end;
            const se_iterator_type it_r_begin;
            se_iterator_type it_r;
            Iterator& operator++() {
                if (it_l == it_l_end) ++it_r;
                else ++it_l;
                return *this;
            }
            Iterator operator++(int) { Iterator ret = *this; ++(*this); return ret; }
            Iterator& operator--() {
                if (it_r == it_r_begin) --it_l;
                else --it_r;
                return *this;
            }
            Iterator operator--(int) { Iterator ret = *this; --(*this); return ret; }
            Iterator& operator+=(int dif) {
                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end, it_r += dif - d;
                else it_l += dif;
                return *this;
            }
            Iterator operator+(int dif) const { Iterator it = *this; it += dif; return it; }
            Iterator& operator-=(int dif) {
                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l -= dif - d;
                else it_r -= dif;
                return *this;
            }
            Iterator operator-(int dif) const { Iterator it = *this; it -= dif; return it; }
            const value_type& operator*() const { return it_l == it_l_end ? *it_r : *it_l; }
            bool operator!=(const Iterator &rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }
            bool operator==(const Iterator &rhs) const { return not (*this != rhs); }
        };
        using iterator_type = Iterator;

        DequeSum() = default;

        value_type sum() const {
            return op(sum(_fi_sum), sum(_se_sum));
        }
        const value_type& operator[](int i) const {
            const int l = _fi_raw.size(), r = _se_raw.size();
            return i < l ? _fi_raw[l - i - 1] : _se_raw[i - l];
        }
        void push_back(const value_type &val) {
            _se_raw.push_back(val);
            _se_sum.push_back(op(sum(_se_sum), val));
        }
        void push_front(const value_type &val) {
            _fi_raw.push_back(val);
            _fi_sum.push_back(op(val, sum(_fi_sum)));
        }
        void pop_back() {
            if (_se_raw.size()) return _se_raw.pop_back(), _se_sum.pop_back();
            const int siz = _fi_raw.size();
            const int l = siz >> 1, r = siz - l;
            assert(r); // <=> siz > 0
            for (int i = r - 1; i > 0; --i) push_back(std::move(_fi_raw[i]));
            _fi_raw.erase(_fi_raw.begin(), _fi_raw.begin() + r);
            _fi_sum.erase(_fi_sum.begin(), _fi_sum.begin() + r);
            if (l) _fi_sum[0] = _fi_raw[0];
            for (int i = 1; i < l; ++i) _fi_sum[i] = op(_fi_raw[i], _fi_sum[i - 1]);
        }
        void pop_front() {
            if (_fi_raw.size()) return _fi_raw.pop_back(), _fi_sum.pop_back();
            const int siz = _se_raw.size();
            const int r = siz >> 1, l = siz - r;
            assert(l); // <=> siz > 0
            for (int i = l - 1; i > 0; --i) push_front(std::move(_se_raw[i]));
            _se_raw.erase(_se_raw.begin(), _se_raw.begin() + l);
            _se_sum.erase(_se_sum.begin(), _se_sum.begin() + l);
            if (r) _se_sum[0] = _se_raw[0];
            for (int i = 1; i < r; ++i) _se_sum[i] = op(_se_sum[i - 1], _se_raw[i]);
        }
        const value_type& front() const { return _fi_raw.size() ? _fi_raw.back() : _se_raw.front(); }
        const value_type& back() const { return _se_raw.size() ? _se_raw.back() : _fi_raw.front(); }
        int size() const { return _fi_raw.size() + _se_raw.size(); }
        void clear() { _fi_raw.clear(), _fi_sum.clear(), _se_raw.clear(), _se_sum.clear(); }
        void shrink_to_fit() { _fi_raw.shrink_to_fit(), _fi_sum.shrink_to_fit(), _se_raw.shrink_to_fit(), _se_sum.shrink_to_fit(); }

        iterator_type begin() const { return iterator_type { _fi_raw.rbegin(), _fi_raw.rend(), _se_raw.begin(), _se_raw.begin() }; }
        iterator_type end() const { return iterator_type { _fi_raw.rend(), _fi_raw.rend(), _se_raw.begin(), _se_raw.end() }; }
        iterator_type cbegin() const { return begin(); }
        iterator_type cend() const { return end(); }

    private:
        std::vector<value_type> _fi_raw, _se_raw;
        std::vector<value_type> _fi_sum, _se_sum;

        value_type sum(const std::vector<value_type> &st) const {
            return st.empty() ? e() : st.back();
        }
    };
} // namespace suisen


#endif // SUISEN_DEQUE_SUM
