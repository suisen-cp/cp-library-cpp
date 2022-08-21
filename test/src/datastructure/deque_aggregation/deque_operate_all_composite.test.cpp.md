---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algebra/monoid/affine.hpp
    title: library/algebra/monoid/affine.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/deque_aggregation.hpp
    title: "SWAG \u3092 Deque \u306B\u62E1\u5F35\u3057\u305F\u3084\u3064"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/deque_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/deque_operate_all_composite
  bundledCode: "#line 1 \"test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/algebra/monoid/affine.hpp\"\n\n\n\n#line 5 \"library/algebra/monoid/affine.hpp\"\
    \n#include <utility>\n\nnamespace suisen {\n    template <typename T>\n    struct\
    \ Affine {\n        T a, b;\n        Affine(const T &a = 1, const T &b = 0) :\
    \ a(a), b(b) {}\n\n        static Affine<T> id() { return Affine<T>{}; }\n   \
    \     static Affine<T> compose(const Affine<T>& f, const Affine<T>& g) { return\
    \ f.compose(g); }\n\n        Affine<T> compose(const Affine<T>& g) const { return\
    \ { a * g.a, affine(g.b) }; }\n\n        template <typename U = T>\n        U\
    \ affine(const T &x) const { return U(a) * x + b; }\n        T operator()(const\
    \ T &x) const { return affine<T>(x); }\n\n        Affine<T> operator+() const\
    \ { return *this; }\n        Affine<T> operator-() const { return { -a, -b };\
    \ }\n\n        Affine<T>& operator++() { ++b; return *this; }\n        Affine<T>&\
    \ operator--() { --b; return *this; }\n        Affine<T> operator++(int) { Affine<T>\
    \ f(*this); ++(*this); return f; }\n        Affine<T> operator--(int) { Affine<T>\
    \ f(*this); --(*this); return f; }\n\n        Affine<T>& operator+=(const T& c)\
    \ { b += c; return *this; }\n        Affine<T>& operator-=(const T& c) { b -=\
    \ c; return *this; }\n        friend Affine<T> operator+(Affine<T> f, const T\
    \ &c) { f += c; return f; }\n        friend Affine<T> operator-(Affine<T> f, const\
    \ T &c) { f -= c; return f; }\n\n        Affine<T>& operator+=(const Affine<T>\
    \ &g) { a += g.a, b += g.b; return *this; }\n        Affine<T>& operator-=(const\
    \ Affine<T> &g) { a -= g.a, b -= g.b; return *this; }\n        friend Affine<T>\
    \ operator+(Affine<T> f, const Affine<T> &g) { f += g; return f; }\n        friend\
    \ Affine<T> operator-(Affine<T> f, const Affine<T> &g) { f -= g; return f; }\n\
    \n        template <typename U = T, typename V = T>\n        operator std::pair<U,\
    \ V>() { return std::pair<U, V>{ a, b }; }\n        template <typename U = T,\
    \ typename V = T>\n        operator std::tuple<U, V>() { return std::tuple<U,\
    \ V>{ a, b }; }\n\n        friend std::istream& operator<<(std::istream& in, Affine<T>\
    \ &f) { return in >> f.a >> f.b; }\n        friend std::ostream& operator>>(std::ostream&\
    \ out, const Affine<T> &f) { return out << f.a << ' ' << f.b; }\n    };\n} //\
    \ namespace suisen\n\n\n#line 1 \"library/datastructure/deque_aggregation.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\n/**\n * [Idea] reference : https://motsu-xe.hatenablog.com/entry/2021/05/13/224016\n\
    \ * \n * SWAG + simulate a deque with 2 stacks\n * \n * [Operations] reference\
    \ : https://www.slideshare.net/catupper/amortize-analysis-of-deque-with-2-stack\n\
    \ * \n * `l`, `r` is a stack of { value, sum }\n * \n *     accumulate\n *   \
    \ <----------  ------> fold values from inside\n *   (     l     ][  r    )\n\
    \ * \n * pop_front:\n *  1. `l` is not empty\n *    (   l ][  r  )   ->   ( l\
    \ ][  r  )      # pop from `l`. O(1)\n *  2. `l` is empty\n *    (][    r    \
    \ )   -> (   l ][  r  )      # split `r` at its middle point. amortized O(1)\n\
    \ *    (   l ][  r  )   ->   ( l ][  r  )      # pop from `l`. O(1)\n * \n * pop_back:\n\
    \ *  1. `r` is not empty\n *    (  l  ][ r   )   ->   (   l ][ r )      # pop\
    \ from `r`. O(1)\n *  2. `r` is empty\n *    (     l    ][)   ->   (  l  ][ r\
    \   )    # split `l` at its middle point. amortized O(1)\n *    (  l  ][ r   )\
    \   ->   (  l  ][ r )      # pop from `r`. O(1)\n * \n * push_front:\n *    (\
    \  l  ][  r  )   -> (    l  ][  r  )    # push to `l`. O(1)\n * \n * push_back:\n\
    \ *    (  l  ][  r  )   ->   (  l  ][  r    )  # push to `r`. O(1)\n */\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct DequeAggregation\
    \ {\n        struct DequeAggregationIterator {\n            using difference_type\
    \ = int;\n            using value_type = T;\n            using pointer = value_type*;\n\
    \            using reference = value_type&;\n            using iterator_category\
    \ = std::random_access_iterator_tag;\n\n            using fi_iterator_type = typename\
    \ std::vector<std::pair<value_type, value_type>>::const_reverse_iterator;\n  \
    \          using se_iterator_type = typename std::vector<std::pair<value_type,\
    \ value_type>>::const_iterator;\n\n            fi_iterator_type it_l;\n      \
    \      fi_iterator_type it_l_end;\n            se_iterator_type it_r_begin;\n\
    \            se_iterator_type it_r;\n\n            DequeAggregationIterator& operator++()\
    \ {\n                if (it_l == it_l_end) ++it_r;\n                else ++it_l;\n\
    \                return *this;\n            }\n            DequeAggregationIterator\
    \ operator++(int) { DequeAggregationIterator ret = *this; ++(*this); return ret;\
    \ }\n            DequeAggregationIterator& operator--() {\n                if\
    \ (it_r == it_r_begin) --it_l;\n                else --it_r;\n               \
    \ return *this;\n            }\n            DequeAggregationIterator operator--(int)\
    \ { DequeAggregationIterator ret = *this; --(*this); return ret; }\n         \
    \   DequeAggregationIterator& operator+=(difference_type dif) {\n            \
    \    if (dif < 0) return *this -= -dif;\n                if (int d = it_l_end\
    \ - it_l; d < dif) it_l = it_l_end, it_r += dif - d;\n                else it_l\
    \ += dif;\n                return *this;\n            }\n            friend DequeAggregationIterator\
    \ operator+(DequeAggregationIterator it, difference_type dif) { it += dif; return\
    \ it; }\n            friend DequeAggregationIterator operator+(difference_type\
    \ dif, DequeAggregationIterator it) { it += dif; return it; }\n            DequeAggregationIterator&\
    \ operator-=(difference_type dif) {\n                if (dif < 0) return *this\
    \ += -dif;\n                if (int d = it_r - it_r_begin; d < dif) it_r = it_r_begin,\
    \ it_l -= dif - d;\n                else it_r -= dif;\n                return\
    \ *this;\n            }\n            friend DequeAggregationIterator operator-(DequeAggregationIterator\
    \ it, difference_type dif) { it -= dif; return it; }\n            difference_type\
    \ operator-(const DequeAggregationIterator &rhs) const {\n                difference_type\
    \ d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;\n             \
    \   difference_type d2 = rhs.it_l == rhs.it_l_end ? rhs.it_r - rhs.it_r_begin\
    \ : rhs.it_l - rhs.it_l_end;\n                return d1 - d2;\n            }\n\
    \            const value_type& operator[](difference_type i) const { return *((*this)\
    \ + i); }\n            const value_type& operator*() const { return it_l == it_l_end\
    \ ? it_r->first : it_l->first; }\n            bool operator!=(const DequeAggregationIterator\
    \ &rhs) const { return it_l != rhs.it_l or it_r != rhs.it_r; }\n            bool\
    \ operator==(const DequeAggregationIterator &rhs) const { return not (*this !=\
    \ rhs); }\n            bool operator< (const DequeAggregationIterator &rhs) const\
    \ { return (*this) - rhs <  0; }\n            bool operator<=(const DequeAggregationIterator\
    \ &rhs) const { return (*this) - rhs <= 0; }\n            bool operator> (const\
    \ DequeAggregationIterator &rhs) const { return (*this) - rhs >  0; }\n      \
    \      bool operator>=(const DequeAggregationIterator &rhs) const { return (*this)\
    \ - rhs >= 0; }\n        };\n        \n        using iterator = DequeAggregationIterator;\n\
    \        using difference_type = typename iterator::difference_type;\n       \
    \ using value_type = typename iterator::value_type;\n        using pointer = typename\
    \ iterator::pointer;\n        using reference = typename iterator::reference;\n\
    \n        DequeAggregation() = default;\n        template <typename InputIterator,\
    \ std::enable_if_t<std::is_constructible_v<value_type, typename InputIterator::value_type>,\
    \ std::nullptr_t> = nullptr>\n        DequeAggregation(InputIterator first, InputIterator\
    \ last) {\n            for (; first != last; ++first) push_back(*first);\n   \
    \     }\n        template <typename Container, std::enable_if_t<std::is_constructible_v<value_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        DequeAggregation(const\
    \ Container &c) : DequeAggregation(std::begin(c), std::end(c)) {}\n\n        value_type\
    \ prod() const {\n            return op(prod(_st_l), prod(_st_r));\n        }\n\
    \        void push_back(const value_type &val) { _st_r.emplace_back(val, op(prod(_st_r),\
    \ val)); }\n        void push_front(const value_type &val) { _st_l.emplace_back(val,\
    \ op(val, prod(_st_l))); }\n        void pop_back() {\n            if (_st_r.size())\
    \ return _st_r.pop_back();\n            const int siz = _st_l.size();\n      \
    \      const int l = siz >> 1, r = siz - l;\n            assert(r); // <=> siz\
    \ > 0\n            for (int i = r - 1; i > 0; --i) push_back(std::move(_st_l[i].first));\n\
    \            _st_l.erase(_st_l.begin(), _st_l.begin() + r);\n            if (l\
    \ == 0) return;\n            _st_l[0].second = _st_l[0].first;\n            for\
    \ (int i = 1; i < l; ++i) _st_l[i].second = op(_st_l[i].first, _st_l[i - 1].second);\n\
    \        }\n        void pop_front() {\n            if (_st_l.size()) return _st_l.pop_back();\n\
    \            const int siz = _st_r.size();\n            const int r = siz >> 1,\
    \ l = siz - r;\n            assert(l); // <=> siz > 0\n            for (int i\
    \ = l - 1; i > 0; --i) push_front(std::move(_st_r[i].first));\n            _st_r.erase(_st_r.begin(),\
    \ _st_r.begin() + l);\n            if (r == 0) return;\n            _st_r[0].second\
    \ = _st_r[0].first;\n            for (int i = 1; i < r; ++i) _st_r[i].second =\
    \ op(_st_r[i - 1].second, _st_r[i].first);\n        }\n        const value_type&\
    \ front() const { return _st_l.size() ? _st_l.back().first : _st_r.front().first;\
    \ }\n        const value_type& back() const { return _st_r.size() ? _st_r.back().first\
    \ : _st_l.front().first; }\n        const value_type& operator[](int i) const\
    \ {\n            const int k = i - _st_l.size();\n            return k < 0 ? _st_l[~k].first\
    \ : _st_r[k].first;\n        }\n\n        int size() const { return _st_l.size()\
    \ + _st_r.size(); }\n        void clear() { _st_l.clear(), _st_r.clear(); }\n\
    \        void shrink_to_fit() { _st_l.shrink_to_fit(), _st_r.shrink_to_fit();\
    \ }\n\n        iterator begin() const { return iterator { _st_l.rbegin(), _st_l.rend(),\
    \ _st_r.begin(), _st_r.begin() }; }\n        iterator end() const { return iterator\
    \ { _st_l.rend(), _st_l.rend(), _st_r.begin(), _st_r.end() }; }\n        iterator\
    \ cbegin() const { return begin(); }\n        iterator cend() const { return end();\
    \ }\n\n    private:\n        std::vector<std::pair<value_type, value_type>> _st_l,\
    \ _st_r;\n\n        value_type prod(const std::vector<std::pair<value_type, value_type>>\
    \ &st) const {\n            return st.empty() ? e() : st.back().second;\n    \
    \    }\n    };\n} // namespace suisen\n\n\n\n#line 11 \"test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp\"\
    \n\nusing suisen::Affine;\nusing suisen::DequeAggregation;\n\nAffine<mint> op(Affine<mint>\
    \ f, Affine<mint> g) { return g.compose(f); }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    DequeAggregation<Affine<mint>, op, Affine<mint>::id>\
    \ dq;\n\n    int q;\n    std::cin >> q;\n\n    for (int i = 0; i < q; ++i) {\n\
    \        int query_type;\n        std::cin >> query_type;\n        if (query_type\
    \ == 0) {\n            int a, b;\n            std::cin >> a >> b;\n          \
    \  dq.push_front({ a, b });\n        } else if (query_type == 1) {\n         \
    \   int a, b;\n            std::cin >> a >> b;\n            dq.push_back({ a,\
    \ b });\n        } else if (query_type == 2) {\n            dq.pop_front();\n\
    \        } else if (query_type == 3) {\n            dq.pop_back();\n        }\
    \ else {\n            int x;\n            std::cin >> x;\n            std::cout\
    \ << dq.prod().affine(x).val() << '\\n';\n        }\n    }\n    \n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/algebra/monoid/affine.hpp\"\n#include \"library/datastructure/deque_aggregation.hpp\"\
    \n\nusing suisen::Affine;\nusing suisen::DequeAggregation;\n\nAffine<mint> op(Affine<mint>\
    \ f, Affine<mint> g) { return g.compose(f); }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    DequeAggregation<Affine<mint>, op, Affine<mint>::id>\
    \ dq;\n\n    int q;\n    std::cin >> q;\n\n    for (int i = 0; i < q; ++i) {\n\
    \        int query_type;\n        std::cin >> query_type;\n        if (query_type\
    \ == 0) {\n            int a, b;\n            std::cin >> a >> b;\n          \
    \  dq.push_front({ a, b });\n        } else if (query_type == 1) {\n         \
    \   int a, b;\n            std::cin >> a >> b;\n            dq.push_back({ a,\
    \ b });\n        } else if (query_type == 2) {\n            dq.pop_front();\n\
    \        } else if (query_type == 3) {\n            dq.pop_back();\n        }\
    \ else {\n            int x;\n            std::cin >> x;\n            std::cout\
    \ << dq.prod().affine(x).val() << '\\n';\n        }\n    }\n    \n    return 0;\n\
    }"
  dependsOn:
  - library/algebra/monoid/affine.hpp
  - library/datastructure/deque_aggregation.hpp
  isVerificationFile: true
  path: test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2022-08-21 18:20:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
- /verify/test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp.html
title: test/src/datastructure/deque_aggregation/deque_operate_all_composite.test.cpp
---
