---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
    title: test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/deque_sum.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T, T),\
    \ T(*e)()>\n    struct DequeSum {\n        using value_type = T;\n\n        struct\
    \ Iterator {\n            using fi_iterator_type = typename std::vector<value_type>::const_reverse_iterator;\n\
    \            using se_iterator_type = typename std::vector<value_type>::const_iterator;\n\
    \            fi_iterator_type it_l;\n            const fi_iterator_type it_l_end;\n\
    \            const se_iterator_type it_r_begin;\n            se_iterator_type\
    \ it_r;\n            Iterator& operator++() {\n                if (it_l == it_l_end)\
    \ ++it_r;\n                else ++it_l;\n                return *this;\n     \
    \       }\n            Iterator operator++(int) { Iterator ret = *this; ++(*this);\
    \ return ret; }\n            Iterator& operator--() {\n                if (it_r\
    \ == it_r_begin) --it_l;\n                else --it_r;\n                return\
    \ *this;\n            }\n            Iterator operator--(int) { Iterator ret =\
    \ *this; --(*this); return ret; }\n            Iterator& operator+=(int dif) {\n\
    \                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end, it_r +=\
    \ dif - d;\n                else it_l += dif;\n                return *this;\n\
    \            }\n            Iterator operator+(int dif) const { Iterator it =\
    \ *this; it += dif; return it; }\n            Iterator& operator-=(int dif) {\n\
    \                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l\
    \ -= dif - d;\n                else it_r -= dif;\n                return *this;\n\
    \            }\n            Iterator operator-(int dif) const { Iterator it =\
    \ *this; it -= dif; return it; }\n            const value_type& operator*() const\
    \ { return it_l == it_l_end ? *it_r : *it_l; }\n            bool operator!=(const\
    \ Iterator &rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }\n    \
    \        bool operator==(const Iterator &rhs) const { return not (*this != rhs);\
    \ }\n        };\n        using iterator_type = Iterator;\n\n        DequeSum()\
    \ = default;\n\n        value_type sum() const {\n            return op(sum(_fi_sum),\
    \ sum(_se_sum));\n        }\n        const value_type& operator[](int i) const\
    \ {\n            const int l = _fi_raw.size(), r = _se_raw.size();\n         \
    \   return i < l ? _fi_raw[l - i - 1] : _se_raw[i - l];\n        }\n        void\
    \ push_back(const value_type &val) {\n            _se_raw.push_back(val);\n  \
    \          _se_sum.push_back(op(sum(_se_sum), val));\n        }\n        void\
    \ push_front(const value_type &val) {\n            _fi_raw.push_back(val);\n \
    \           _fi_sum.push_back(op(val, sum(_fi_sum)));\n        }\n        void\
    \ pop_back() {\n            if (_se_raw.size()) return _se_raw.pop_back(), _se_sum.pop_back();\n\
    \            const int siz = _fi_raw.size();\n            const int l = siz >>\
    \ 1, r = siz - l;\n            assert(r); // <=> siz > 0\n            for (int\
    \ i = r - 1; i > 0; --i) push_back(std::move(_fi_raw[i]));\n            _fi_raw.erase(_fi_raw.begin(),\
    \ _fi_raw.begin() + r);\n            _fi_sum.erase(_fi_sum.begin(), _fi_sum.begin()\
    \ + r);\n            if (l) _fi_sum[0] = _fi_raw[0];\n            for (int i =\
    \ 1; i < l; ++i) _fi_sum[i] = op(_fi_raw[i], _fi_sum[i - 1]);\n        }\n   \
    \     void pop_front() {\n            if (_fi_raw.size()) return _fi_raw.pop_back(),\
    \ _fi_sum.pop_back();\n            const int siz = _se_raw.size();\n         \
    \   const int r = siz >> 1, l = siz - r;\n            assert(l); // <=> siz >\
    \ 0\n            for (int i = l - 1; i > 0; --i) push_front(std::move(_se_raw[i]));\n\
    \            _se_raw.erase(_se_raw.begin(), _se_raw.begin() + l);\n          \
    \  _se_sum.erase(_se_sum.begin(), _se_sum.begin() + l);\n            if (r) _se_sum[0]\
    \ = _se_raw[0];\n            for (int i = 1; i < r; ++i) _se_sum[i] = op(_se_sum[i\
    \ - 1], _se_raw[i]);\n        }\n        const value_type& front() const { return\
    \ _fi_raw.size() ? _fi_raw.back() : _se_raw.front(); }\n        const value_type&\
    \ back() const { return _se_raw.size() ? _se_raw.back() : _fi_raw.front(); }\n\
    \        int size() const { return _fi_raw.size() + _se_raw.size(); }\n      \
    \  void clear() { _fi_raw.clear(), _fi_sum.clear(), _se_raw.clear(), _se_sum.clear();\
    \ }\n        void shrink_to_fit() { _fi_raw.shrink_to_fit(), _fi_sum.shrink_to_fit(),\
    \ _se_raw.shrink_to_fit(), _se_sum.shrink_to_fit(); }\n\n        iterator_type\
    \ begin() const { return iterator_type { _fi_raw.rbegin(), _fi_raw.rend(), _se_raw.begin(),\
    \ _se_raw.begin() }; }\n        iterator_type end() const { return iterator_type\
    \ { _fi_raw.rend(), _fi_raw.rend(), _se_raw.begin(), _se_raw.end() }; }\n    \
    \    iterator_type cbegin() const { return begin(); }\n        iterator_type cend()\
    \ const { return end(); }\n\n    private:\n        std::vector<value_type> _fi_raw,\
    \ _se_raw;\n        std::vector<value_type> _fi_sum, _se_sum;\n\n        value_type\
    \ sum(const std::vector<value_type> &st) const {\n            return st.empty()\
    \ ? e() : st.back();\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DEQUE_SUM\n#define SUISEN_DEQUE_SUM\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T, T),\
    \ T(*e)()>\n    struct DequeSum {\n        using value_type = T;\n\n        struct\
    \ Iterator {\n            using fi_iterator_type = typename std::vector<value_type>::const_reverse_iterator;\n\
    \            using se_iterator_type = typename std::vector<value_type>::const_iterator;\n\
    \            fi_iterator_type it_l;\n            const fi_iterator_type it_l_end;\n\
    \            const se_iterator_type it_r_begin;\n            se_iterator_type\
    \ it_r;\n            Iterator& operator++() {\n                if (it_l == it_l_end)\
    \ ++it_r;\n                else ++it_l;\n                return *this;\n     \
    \       }\n            Iterator operator++(int) { Iterator ret = *this; ++(*this);\
    \ return ret; }\n            Iterator& operator--() {\n                if (it_r\
    \ == it_r_begin) --it_l;\n                else --it_r;\n                return\
    \ *this;\n            }\n            Iterator operator--(int) { Iterator ret =\
    \ *this; --(*this); return ret; }\n            Iterator& operator+=(int dif) {\n\
    \                if (int d = it_l_end - it_l; d < dif) it_l = it_l_end, it_r +=\
    \ dif - d;\n                else it_l += dif;\n                return *this;\n\
    \            }\n            Iterator operator+(int dif) const { Iterator it =\
    \ *this; it += dif; return it; }\n            Iterator& operator-=(int dif) {\n\
    \                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin, it_l\
    \ -= dif - d;\n                else it_r -= dif;\n                return *this;\n\
    \            }\n            Iterator operator-(int dif) const { Iterator it =\
    \ *this; it -= dif; return it; }\n            const value_type& operator*() const\
    \ { return it_l == it_l_end ? *it_r : *it_l; }\n            bool operator!=(const\
    \ Iterator &rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }\n    \
    \        bool operator==(const Iterator &rhs) const { return not (*this != rhs);\
    \ }\n        };\n        using iterator_type = Iterator;\n\n        DequeSum()\
    \ = default;\n\n        value_type sum() const {\n            return op(sum(_fi_sum),\
    \ sum(_se_sum));\n        }\n        const value_type& operator[](int i) const\
    \ {\n            const int l = _fi_raw.size(), r = _se_raw.size();\n         \
    \   return i < l ? _fi_raw[l - i - 1] : _se_raw[i - l];\n        }\n        void\
    \ push_back(const value_type &val) {\n            _se_raw.push_back(val);\n  \
    \          _se_sum.push_back(op(sum(_se_sum), val));\n        }\n        void\
    \ push_front(const value_type &val) {\n            _fi_raw.push_back(val);\n \
    \           _fi_sum.push_back(op(val, sum(_fi_sum)));\n        }\n        void\
    \ pop_back() {\n            if (_se_raw.size()) return _se_raw.pop_back(), _se_sum.pop_back();\n\
    \            const int siz = _fi_raw.size();\n            const int l = siz >>\
    \ 1, r = siz - l;\n            assert(r); // <=> siz > 0\n            for (int\
    \ i = r - 1; i > 0; --i) push_back(std::move(_fi_raw[i]));\n            _fi_raw.erase(_fi_raw.begin(),\
    \ _fi_raw.begin() + r);\n            _fi_sum.erase(_fi_sum.begin(), _fi_sum.begin()\
    \ + r);\n            if (l) _fi_sum[0] = _fi_raw[0];\n            for (int i =\
    \ 1; i < l; ++i) _fi_sum[i] = op(_fi_raw[i], _fi_sum[i - 1]);\n        }\n   \
    \     void pop_front() {\n            if (_fi_raw.size()) return _fi_raw.pop_back(),\
    \ _fi_sum.pop_back();\n            const int siz = _se_raw.size();\n         \
    \   const int r = siz >> 1, l = siz - r;\n            assert(l); // <=> siz >\
    \ 0\n            for (int i = l - 1; i > 0; --i) push_front(std::move(_se_raw[i]));\n\
    \            _se_raw.erase(_se_raw.begin(), _se_raw.begin() + l);\n          \
    \  _se_sum.erase(_se_sum.begin(), _se_sum.begin() + l);\n            if (r) _se_sum[0]\
    \ = _se_raw[0];\n            for (int i = 1; i < r; ++i) _se_sum[i] = op(_se_sum[i\
    \ - 1], _se_raw[i]);\n        }\n        const value_type& front() const { return\
    \ _fi_raw.size() ? _fi_raw.back() : _se_raw.front(); }\n        const value_type&\
    \ back() const { return _se_raw.size() ? _se_raw.back() : _fi_raw.front(); }\n\
    \        int size() const { return _fi_raw.size() + _se_raw.size(); }\n      \
    \  void clear() { _fi_raw.clear(), _fi_sum.clear(), _se_raw.clear(), _se_sum.clear();\
    \ }\n        void shrink_to_fit() { _fi_raw.shrink_to_fit(), _fi_sum.shrink_to_fit(),\
    \ _se_raw.shrink_to_fit(), _se_sum.shrink_to_fit(); }\n\n        iterator_type\
    \ begin() const { return iterator_type { _fi_raw.rbegin(), _fi_raw.rend(), _se_raw.begin(),\
    \ _se_raw.begin() }; }\n        iterator_type end() const { return iterator_type\
    \ { _fi_raw.rend(), _fi_raw.rend(), _se_raw.begin(), _se_raw.end() }; }\n    \
    \    iterator_type cbegin() const { return begin(); }\n        iterator_type cend()\
    \ const { return end(); }\n\n    private:\n        std::vector<value_type> _fi_raw,\
    \ _se_raw;\n        std::vector<value_type> _fi_sum, _se_sum;\n\n        value_type\
    \ sum(const std::vector<value_type> &st) const {\n            return st.empty()\
    \ ? e() : st.back();\n        }\n    };\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_DEQUE_SUM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/deque_sum.hpp
  requiredBy: []
  timestamp: '2022-07-05 16:51:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
documentation_of: library/datastructure/deque_sum.hpp
layout: document
title: "SWAG \u3092 Deque \u306B\u62E1\u5F35\u3057\u305F\u3084\u3064"
---
## SWAG を Deque に拡張したやつ

モノイドの元を要素に持つ deque に対する操作と総和取得を効率的に行うデータ構造。

## サポートする関数

二項演算の計算量を $O(X)$ とする。

- `push_back` : 末尾に要素を追加。$O(X)$
- `push_front` : 先頭に要素を追加。$O(X)$
- `pop_back` : 末尾の要素を削除。amortized $O(X)$
- `pop_front` : 先頭の要素を削除。amortized $O(X)$
- `sum` : 要素を先頭から $v_1,\ldots,v_k$ として、二項演算 `op` で畳み込んだ結果 $op(v_1,op(v_2, op(\ldots, v_k)))$ を計算。$O(X)$
- `operator[]` : ランダムアクセス。$O(1)$
- `back` : 末尾の要素を取得。$O(1)$
- `front` : 先頭の要素を取得。$O(1)$
- `size` : 要素数を取得。$O(1)$
- `clear` : コンテナを空にする。内部的に確保されている capacity は変更しない。$O(1)$
- `shrink_to_fit` : capacity を size まで縮小。$O(1)$
- `begin` : 先頭の要素を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `end` : 末尾の次を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `cbegin` : 先頭の要素を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `cend` : 末尾の次を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$

## 参考

- https://motsu-xe.hatenablog.com/entry/2021/05/13/224016 : SWAG を deque に拡張するアイデア
- https://www.slideshare.net/catupper/amortize-analysis-of-deque-with-2-stack : stack 2 つで deque をシミュレートする方法
