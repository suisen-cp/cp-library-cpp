---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/algorithm/slope_trick.hpp
    title: library/algorithm/slope_trick.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc127/tasks/abc127_f
    links:
    - https://atcoder.jp/contests/abc127/tasks/abc127_f
  bundledCode: "#line 1 \"test/src/algorithm/slope_trick/absolute_minima.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc127/tasks/abc127_f\"\n\n#include\
    \ <iostream>\n#line 1 \"library/algorithm/slope_trick.hpp\"\n\n\n\n#include <cassert>\n\
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
    } // namespace suisen\n\n\n#line 5 \"test/src/algorithm/slope_trick/absolute_minima.test.cpp\"\
    \n\nvoid solve() {\n    suisen::SlopeTrick<long long> f;\n    int q;\n    std::cin\
    \ >> q;\n    while (q --> 0) {\n        int t;\n        std::cin >> t;\n     \
    \   if (t == 1) {\n            int a, b;\n            std::cin >> a >> b;\n  \
    \          f.add_abs(a), f.add_const(b);\n        } else {\n            std::cout\
    \ << f.argmin_range().first << ' ' << f.min() << '\\n';\n        }\n    }\n}\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    solve();        \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc127/tasks/abc127_f\"\n\n\
    #include <iostream>\n#include \"library/algorithm/slope_trick.hpp\"\n\nvoid solve()\
    \ {\n    suisen::SlopeTrick<long long> f;\n    int q;\n    std::cin >> q;\n  \
    \  while (q --> 0) {\n        int t;\n        std::cin >> t;\n        if (t ==\
    \ 1) {\n            int a, b;\n            std::cin >> a >> b;\n            f.add_abs(a),\
    \ f.add_const(b);\n        } else {\n            std::cout << f.argmin_range().first\
    \ << ' ' << f.min() << '\\n';\n        }\n    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    solve();        \n    return 0;\n}"
  dependsOn:
  - library/algorithm/slope_trick.hpp
  isVerificationFile: true
  path: test/src/algorithm/slope_trick/absolute_minima.test.cpp
  requiredBy: []
  timestamp: '2021-07-20 16:59:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/algorithm/slope_trick/absolute_minima.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/slope_trick/absolute_minima.test.cpp
- /verify/test/src/algorithm/slope_trick/absolute_minima.test.cpp.html
title: test/src/algorithm/slope_trick/absolute_minima.test.cpp
---
