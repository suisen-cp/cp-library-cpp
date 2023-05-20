---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/queue_aggregation.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    template <typename T,\
    \ typename SumType, SumType(*e)(), SumType(*append)(SumType, T), typename R, R(*merge)(SumType,\
    \ SumType)>\n    struct QueueAggregation {\n        using value_type = T;\n  \
    \      using pointer = T*;\n        using const_pointer = const T*;\n        using\
    \ reference = T&;\n        using const_reference = const T&;\n\n        using\
    \ sum_type = SumType;\n\n    private:\n        struct QueueAggregationIterator\
    \ {\n            using difference_type = int;\n            using value_type =\
    \ T;\n            using pointer = const_pointer;\n            using reference\
    \ = const_reference;\n            using iterator_category = std::random_access_iterator_tag;\n\
    \n        private:\n            using fi_iterator_type = typename std::vector<std::pair<value_type,\
    \ value_type>>::const_reverse_iterator;\n            using se_iterator_type =\
    \ typename std::vector<std::pair<value_type, value_type>>::const_iterator;\n \
    \       public:\n\n            fi_iterator_type it_l;\n            fi_iterator_type\
    \ it_l_end;\n            se_iterator_type it_r_begin;\n            se_iterator_type\
    \ it_r;\n\n            QueueAggregationIterator& operator++() {\n            \
    \    if (it_l == it_l_end) ++it_r;\n                else ++it_l;\n           \
    \     return *this;\n            }\n            QueueAggregationIterator operator++(int)\
    \ { QueueAggregationIterator ret = *this; ++(*this); return ret; }\n         \
    \   QueueAggregationIterator& operator--() {\n                if (it_r == it_r_begin)\
    \ --it_l;\n                else --it_r;\n                return *this;\n     \
    \       }\n            QueueAggregationIterator operator--(int) { QueueAggregationIterator\
    \ ret = *this; --(*this); return ret; }\n            QueueAggregationIterator&\
    \ operator+=(difference_type dif) {\n                if (dif < 0) return *this\
    \ -= -dif;\n                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end,\
    \ it_r += dif - d;\n                else it_l += dif;\n                return\
    \ *this;\n            }\n            friend QueueAggregationIterator operator+(QueueAggregationIterator\
    \ it, difference_type dif) { it += dif; return it; }\n            friend QueueAggregationIterator\
    \ operator+(difference_type dif, QueueAggregationIterator it) { it += dif; return\
    \ it; }\n            QueueAggregationIterator& operator-=(difference_type dif)\
    \ {\n                if (dif < 0) return *this += -dif;\n                if (int\
    \ d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l -= dif - d;\n      \
    \          else it_r -= dif;\n                return *this;\n            }\n \
    \           friend QueueAggregationIterator operator-(QueueAggregationIterator\
    \ it, difference_type dif) { it -= dif; return it; }\n            difference_type\
    \ operator-(const QueueAggregationIterator& rhs) const {\n                difference_type\
    \ d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;\n             \
    \   difference_type d2 = rhs.it_l == rhs.it_l_end ? rhs.it_r - rhs.it_r_begin\
    \ : rhs.it_l - rhs.it_l_end;\n                return d1 - d2;\n            }\n\
    \            reference operator[](difference_type i) const { return *((*this)\
    \ + i); }\n            reference operator*() const { return it_l == it_l_end ?\
    \ it_r->first : it_l->first; }\n            bool operator!=(const QueueAggregationIterator&\
    \ rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }\n            bool\
    \ operator==(const QueueAggregationIterator& rhs) const { return not (*this !=\
    \ rhs); }\n            bool operator< (const QueueAggregationIterator& rhs) const\
    \ { return (*this) - rhs < 0; }\n            bool operator<=(const QueueAggregationIterator&\
    \ rhs) const { return (*this) - rhs <= 0; }\n            bool operator> (const\
    \ QueueAggregationIterator& rhs) const { return (*this) - rhs > 0; }\n       \
    \     bool operator>=(const QueueAggregationIterator& rhs) const { return (*this)\
    \ - rhs >= 0; }\n        };\n    \n    public:\n        using iterator = QueueAggregationIterator;\n\
    \        using const_iterator = iterator;\n\n        QueueAggregation() = default;\n\
    \        template <typename InputIterator, std::enable_if_t<std::is_constructible_v<value_type,\
    \ typename InputIterator::value_type>, std::nullptr_t> = nullptr>\n        QueueAggregation(InputIterator\
    \ first, InputIterator last) {\n            for (; first != last; ++first) push_back(*first);\n\
    \        }\n        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        QueueAggregation(const\
    \ Container& c): QueueAggregation(std::begin(c), std::end(c)) {}\n\n        R\
    \ prod() const {\n            return merge(prod(_st_l), prod(_st_r));\n      \
    \  }\n        void push_back(const value_type& val) { _st_r.emplace_back(val,\
    \ append(prod(_st_r), val)); }\n        void pop_front() {\n            if (_st_l.size())\
    \ return _st_l.pop_back();\n            const int siz = _st_r.size();\n      \
    \      assert(siz);\n            for (int i = siz - 1; i > 0; --i) {\n       \
    \         value_type v = std::move(_st_r[i].first);\n                _st_l.emplace_back(v,\
    \ append(prod(_st_l), v));\n            }\n            _st_r.clear();\n      \
    \  }\n        const value_type& front() const { return _st_l.size() ? _st_l.back().first\
    \ : _st_r.front().first; }\n        const value_type& back() const { return _st_r.size()\
    \ ? _st_r.back().first : _st_l.front().first; }\n        const value_type& operator[](int\
    \ i) const {\n            const int k = i - _st_l.size();\n            return\
    \ k < 0 ? _st_l[~k].first : _st_r[k].first;\n        }\n\n        int size() const\
    \ { return _st_l.size() + _st_r.size(); }\n        void clear() { _st_l.clear(),\
    \ _st_r.clear(); }\n        void shrink_to_fit() { _st_l.shrink_to_fit(), _st_r.shrink_to_fit();\
    \ }\n\n        iterator begin() const { return iterator{ _st_l.rbegin(), _st_l.rend(),\
    \ _st_r.begin(), _st_r.begin() }; }\n        iterator end() const { return iterator{\
    \ _st_l.rend(), _st_l.rend(), _st_r.begin(), _st_r.end() }; }\n        iterator\
    \ cbegin() const { return begin(); }\n        iterator cend() const { return end();\
    \ }\n\n    private:\n        std::vector<std::pair<value_type, sum_type>> _st_l,\
    \ _st_r;\n\n        sum_type prod(const std::vector<std::pair<value_type, sum_type>>&\
    \ st) const {\n            return st.empty() ? e() : st.back().second;\n     \
    \   }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_QUEUE_SUM\n#define SUISEN_QUEUE_SUM\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, typename SumType,\
    \ SumType(*e)(), SumType(*append)(SumType, T), typename R, R(*merge)(SumType,\
    \ SumType)>\n    struct QueueAggregation {\n        using value_type = T;\n  \
    \      using pointer = T*;\n        using const_pointer = const T*;\n        using\
    \ reference = T&;\n        using const_reference = const T&;\n\n        using\
    \ sum_type = SumType;\n\n    private:\n        struct QueueAggregationIterator\
    \ {\n            using difference_type = int;\n            using value_type =\
    \ T;\n            using pointer = const_pointer;\n            using reference\
    \ = const_reference;\n            using iterator_category = std::random_access_iterator_tag;\n\
    \n        private:\n            using fi_iterator_type = typename std::vector<std::pair<value_type,\
    \ value_type>>::const_reverse_iterator;\n            using se_iterator_type =\
    \ typename std::vector<std::pair<value_type, value_type>>::const_iterator;\n \
    \       public:\n\n            fi_iterator_type it_l;\n            fi_iterator_type\
    \ it_l_end;\n            se_iterator_type it_r_begin;\n            se_iterator_type\
    \ it_r;\n\n            QueueAggregationIterator& operator++() {\n            \
    \    if (it_l == it_l_end) ++it_r;\n                else ++it_l;\n           \
    \     return *this;\n            }\n            QueueAggregationIterator operator++(int)\
    \ { QueueAggregationIterator ret = *this; ++(*this); return ret; }\n         \
    \   QueueAggregationIterator& operator--() {\n                if (it_r == it_r_begin)\
    \ --it_l;\n                else --it_r;\n                return *this;\n     \
    \       }\n            QueueAggregationIterator operator--(int) { QueueAggregationIterator\
    \ ret = *this; --(*this); return ret; }\n            QueueAggregationIterator&\
    \ operator+=(difference_type dif) {\n                if (dif < 0) return *this\
    \ -= -dif;\n                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end,\
    \ it_r += dif - d;\n                else it_l += dif;\n                return\
    \ *this;\n            }\n            friend QueueAggregationIterator operator+(QueueAggregationIterator\
    \ it, difference_type dif) { it += dif; return it; }\n            friend QueueAggregationIterator\
    \ operator+(difference_type dif, QueueAggregationIterator it) { it += dif; return\
    \ it; }\n            QueueAggregationIterator& operator-=(difference_type dif)\
    \ {\n                if (dif < 0) return *this += -dif;\n                if (int\
    \ d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l -= dif - d;\n      \
    \          else it_r -= dif;\n                return *this;\n            }\n \
    \           friend QueueAggregationIterator operator-(QueueAggregationIterator\
    \ it, difference_type dif) { it -= dif; return it; }\n            difference_type\
    \ operator-(const QueueAggregationIterator& rhs) const {\n                difference_type\
    \ d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;\n             \
    \   difference_type d2 = rhs.it_l == rhs.it_l_end ? rhs.it_r - rhs.it_r_begin\
    \ : rhs.it_l - rhs.it_l_end;\n                return d1 - d2;\n            }\n\
    \            reference operator[](difference_type i) const { return *((*this)\
    \ + i); }\n            reference operator*() const { return it_l == it_l_end ?\
    \ it_r->first : it_l->first; }\n            bool operator!=(const QueueAggregationIterator&\
    \ rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }\n            bool\
    \ operator==(const QueueAggregationIterator& rhs) const { return not (*this !=\
    \ rhs); }\n            bool operator< (const QueueAggregationIterator& rhs) const\
    \ { return (*this) - rhs < 0; }\n            bool operator<=(const QueueAggregationIterator&\
    \ rhs) const { return (*this) - rhs <= 0; }\n            bool operator> (const\
    \ QueueAggregationIterator& rhs) const { return (*this) - rhs > 0; }\n       \
    \     bool operator>=(const QueueAggregationIterator& rhs) const { return (*this)\
    \ - rhs >= 0; }\n        };\n    \n    public:\n        using iterator = QueueAggregationIterator;\n\
    \        using const_iterator = iterator;\n\n        QueueAggregation() = default;\n\
    \        template <typename InputIterator, std::enable_if_t<std::is_constructible_v<value_type,\
    \ typename InputIterator::value_type>, std::nullptr_t> = nullptr>\n        QueueAggregation(InputIterator\
    \ first, InputIterator last) {\n            for (; first != last; ++first) push_back(*first);\n\
    \        }\n        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        QueueAggregation(const\
    \ Container& c): QueueAggregation(std::begin(c), std::end(c)) {}\n\n        R\
    \ prod() const {\n            return merge(prod(_st_l), prod(_st_r));\n      \
    \  }\n        void push_back(const value_type& val) { _st_r.emplace_back(val,\
    \ append(prod(_st_r), val)); }\n        void pop_front() {\n            if (_st_l.size())\
    \ return _st_l.pop_back();\n            const int siz = _st_r.size();\n      \
    \      assert(siz);\n            for (int i = siz - 1; i > 0; --i) {\n       \
    \         value_type v = std::move(_st_r[i].first);\n                _st_l.emplace_back(v,\
    \ append(prod(_st_l), v));\n            }\n            _st_r.clear();\n      \
    \  }\n        const value_type& front() const { return _st_l.size() ? _st_l.back().first\
    \ : _st_r.front().first; }\n        const value_type& back() const { return _st_r.size()\
    \ ? _st_r.back().first : _st_l.front().first; }\n        const value_type& operator[](int\
    \ i) const {\n            const int k = i - _st_l.size();\n            return\
    \ k < 0 ? _st_l[~k].first : _st_r[k].first;\n        }\n\n        int size() const\
    \ { return _st_l.size() + _st_r.size(); }\n        void clear() { _st_l.clear(),\
    \ _st_r.clear(); }\n        void shrink_to_fit() { _st_l.shrink_to_fit(), _st_r.shrink_to_fit();\
    \ }\n\n        iterator begin() const { return iterator{ _st_l.rbegin(), _st_l.rend(),\
    \ _st_r.begin(), _st_r.begin() }; }\n        iterator end() const { return iterator{\
    \ _st_l.rend(), _st_l.rend(), _st_r.begin(), _st_r.end() }; }\n        iterator\
    \ cbegin() const { return begin(); }\n        iterator cend() const { return end();\
    \ }\n\n    private:\n        std::vector<std::pair<value_type, sum_type>> _st_l,\
    \ _st_r;\n\n        sum_type prod(const std::vector<std::pair<value_type, sum_type>>&\
    \ st) const {\n            return st.empty() ? e() : st.back().second;\n     \
    \   }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_QUEUE_SUM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/queue_aggregation.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:19:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/queue_aggregation.hpp
layout: document
title: Queue Aggregation
---
## Queue Aggregation
