---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/slope_trick/absolute_minima.test.cpp
    title: test/src/algorithm/slope_trick/absolute_minima.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/slope_trick/inc_dec_decomposition.test.cpp
    title: test/src/algorithm/slope_trick/inc_dec_decomposition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/slope_trick/narrow_rectangles.test.cpp
    title: test/src/algorithm/slope_trick/narrow_rectangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/slope_trick.hpp\"\n\n\n\n#include <cassert>\n\
    #include <limits>\n#include <queue>\n\nnamespace suisen {\ntemplate <typename\
    \ T>\nclass SlopeTrick {\n    using pq_dsc = std::priority_queue<T>;\n    using\
    \ pq_asc = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n    public:\n\
    \        SlopeTrick() : base(0), add_l(0), add_r(0) {\n            l.push(-inf),\
    \ r.push(+inf);\n        }\n        T min() const {\n            return base;\n\
    \        }\n        std::pair<T, T> argmin_range() const {\n            return\
    \ {l.top() + add_l, r.top() + add_r};\n        }\n        SlopeTrick& add_const(const\
    \ T a) {\n            base += a;\n            return *this;\n        }\n     \
    \   // $f \\leftarrow f + max(0, x - a)$\n        SlopeTrick& add_right(const\
    \ T a) {\n            if (l.top() + add_l <= a) {\n                r.push(a -\
    \ add_r);\n            } else {\n                base += (l.top() + add_l) - a;\n\
    \                l.push(a - add_l), r.push(l.top() + add_l - add_r), l.pop();\n\
    \            }\n            return *this;\n        }\n        // $f \\leftarrow\
    \ f + max(0, a - x)$\n        SlopeTrick& add_left(const T a) {\n            if\
    \ (r.top() + add_r >= a) {\n                l.push(a - add_l);\n            }\
    \ else {\n                base += a - (r.top() + add_r);\n                r.push(a\
    \ - add_r), l.push(r.top() + add_r - add_l), r.pop();\n            }\n       \
    \     return *this;\n        }\n        // $f \\leftarrow f + |x - a|$\n     \
    \   SlopeTrick& add_abs(const T a) {\n            add_left(a), add_right(a);\n\
    \            return *this;\n        }\n        SlopeTrick& cumulative_min_left()\
    \ {\n            r = pq_asc{}, r.push(+inf);\n            return *this;\n    \
    \    }\n        SlopeTrick& cumulative_min_right() {\n            l = pq_dsc{},\
    \ l.push(-inf);\n            return *this;\n        }\n        SlopeTrick& operator<<=(const\
    \ T shamt_left) {\n            add_l -= shamt_left, add_r -= shamt_left;\n   \
    \         return *this;\n        }\n        SlopeTrick& operator>>=(const T shamt_right)\
    \ {\n            add_l += shamt_right, add_r += shamt_right;\n            return\
    \ *this;\n        }\n        SlopeTrick& translate(const T dx) {\n           \
    \ return dx >= 0 ? *this >>= dx : *this <<= -dx;\n        }\n        SlopeTrick&\
    \ sliding_window_minimum(const T a, const T b) {\n            assert(a <= b);\n\
    \            add_l += a, add_r += b;\n            return *this;\n        }\n \
    \   private:\n        static constexpr T inf = std::numeric_limits<T>::max() /\
    \ 2;\n        T base, add_l, add_r;\n        pq_dsc l;\n        pq_asc r;\n};\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SLOPE_TRICK\n#define SUISEN_SLOPE_TRICK\n\n#include <cassert>\n\
    #include <limits>\n#include <queue>\n\nnamespace suisen {\ntemplate <typename\
    \ T>\nclass SlopeTrick {\n    using pq_dsc = std::priority_queue<T>;\n    using\
    \ pq_asc = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n    public:\n\
    \        SlopeTrick() : base(0), add_l(0), add_r(0) {\n            l.push(-inf),\
    \ r.push(+inf);\n        }\n        T min() const {\n            return base;\n\
    \        }\n        std::pair<T, T> argmin_range() const {\n            return\
    \ {l.top() + add_l, r.top() + add_r};\n        }\n        SlopeTrick& add_const(const\
    \ T a) {\n            base += a;\n            return *this;\n        }\n     \
    \   // $f \\leftarrow f + max(0, x - a)$\n        SlopeTrick& add_right(const\
    \ T a) {\n            if (l.top() + add_l <= a) {\n                r.push(a -\
    \ add_r);\n            } else {\n                base += (l.top() + add_l) - a;\n\
    \                l.push(a - add_l), r.push(l.top() + add_l - add_r), l.pop();\n\
    \            }\n            return *this;\n        }\n        // $f \\leftarrow\
    \ f + max(0, a - x)$\n        SlopeTrick& add_left(const T a) {\n            if\
    \ (r.top() + add_r >= a) {\n                l.push(a - add_l);\n            }\
    \ else {\n                base += a - (r.top() + add_r);\n                r.push(a\
    \ - add_r), l.push(r.top() + add_r - add_l), r.pop();\n            }\n       \
    \     return *this;\n        }\n        // $f \\leftarrow f + |x - a|$\n     \
    \   SlopeTrick& add_abs(const T a) {\n            add_left(a), add_right(a);\n\
    \            return *this;\n        }\n        SlopeTrick& cumulative_min_left()\
    \ {\n            r = pq_asc{}, r.push(+inf);\n            return *this;\n    \
    \    }\n        SlopeTrick& cumulative_min_right() {\n            l = pq_dsc{},\
    \ l.push(-inf);\n            return *this;\n        }\n        SlopeTrick& operator<<=(const\
    \ T shamt_left) {\n            add_l -= shamt_left, add_r -= shamt_left;\n   \
    \         return *this;\n        }\n        SlopeTrick& operator>>=(const T shamt_right)\
    \ {\n            add_l += shamt_right, add_r += shamt_right;\n            return\
    \ *this;\n        }\n        SlopeTrick& translate(const T dx) {\n           \
    \ return dx >= 0 ? *this >>= dx : *this <<= -dx;\n        }\n        SlopeTrick&\
    \ sliding_window_minimum(const T a, const T b) {\n            assert(a <= b);\n\
    \            add_l += a, add_r += b;\n            return *this;\n        }\n \
    \   private:\n        static constexpr T inf = std::numeric_limits<T>::max() /\
    \ 2;\n        T base, add_l, add_r;\n        pq_dsc l;\n        pq_asc r;\n};\n\
    } // namespace suisen\n\n#endif // SUISEN_SLOPE_TRICK"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/slope_trick.hpp
  requiredBy: []
  timestamp: '2021-07-20 16:59:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/slope_trick/narrow_rectangles.test.cpp
  - test/src/algorithm/slope_trick/inc_dec_decomposition.test.cpp
  - test/src/algorithm/slope_trick/absolute_minima.test.cpp
documentation_of: library/algorithm/slope_trick.hpp
layout: document
redirect_from:
- /library/library/algorithm/slope_trick.hpp
- /library/library/algorithm/slope_trick.hpp.html
title: library/algorithm/slope_trick.hpp
---