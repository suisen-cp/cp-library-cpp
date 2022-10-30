---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sliding_window_minimum.hpp
    title: Sliding Window Minimum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D
  bundledCode: "#line 1 \"test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/sliding_window_minimum.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n#include <queue>\n#include <type_traits>\n\
    \nnamespace suisen {\nnamespace prioritizing_mode {\n    template <typename T>\n\
    \    using left_most_min  = std::greater<T>;\n    template <typename T>\n    using\
    \ right_most_min = std::greater_equal<T>;\n    template <typename T>\n    using\
    \ left_most_max  = std::less<T>;\n    template <typename T>\n    using right_most_max\
    \ = std::less_equal<T>;\n}\n\ntemplate <\n    typename T, typename Comparator\
    \ = prioritizing_mode::left_most_min<T>,\n    std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Comparator, T, T>, std::nullptr_t> = nullptr\n>\nclass sliding_window_minimum\
    \ {\n    public:\n        template <typename Gen, std::enable_if_t<std::is_invocable_r_v<T,\
    \ Gen, int>, std::nullptr_t> = nullptr>\n        sliding_window_minimum(int n,\
    \ Gen gen) : _n(n), _a(n) {\n            for (int i = 0; i < _n; ++i) _a[i] =\
    \ gen(i);\n        }\n        void proc_right() {\n            assert(_r < _n);\n\
    \            T v = _a[_r];\n            while (not _dq.empty() and _cmp(_a[_dq.back()],\
    \ v)) _dq.pop_back();\n            _dq.push_back(_r++);\n        }\n        void\
    \ proc_right(int to_index) {\n            while (_r < to_index) proc_right();\n\
    \        }\n        void proc_left() {\n            assert(_l < _r);\n       \
    \     if (_dq.front() == _l) _dq.pop_front();\n            ++_l;\n        }\n\
    \        void proc_left(int to_index) {\n            while (_l < to_index) proc_left();\n\
    \        }\n        void proc(int new_l, int new_r) {\n            proc_right(new_r),\
    \ proc_left(new_l);\n        }\n        int arg_query() const {\n            assert(_l\
    \ < _r);\n            return _dq.front();\n        }\n        T query() const\
    \ {\n            return _a[arg_query()];\n        }\n\n        int get_left()\
    \ const {\n            return _l;\n        }\n        int get_right() const {\n\
    \            return _r;\n        }\n        int get_window_size() const {\n  \
    \          return _r - _l;\n        }\n    private:\n        const int _n;\n \
    \       int _l = 0, _r = 0;\n        std::vector<T> _a;\n        std::deque<int>\
    \ _dq;\n        Comparator _cmp;\n};\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp\"\
    \nusing suisen::sliding_window_minimum;\n\nint main() {\n    int n, l;\n    std::cin\
    \ >> n >> l;\n    std::vector<int> a(n);\n    for (int &e : a) std::cin >> e;\n\
    \    sliding_window_minimum<int> swm(n, [&a](int i) { return a[i]; });\n    for\
    \ (int r = l; r <= n; ++r) {\n        swm.proc(r - l, r);\n        std::cout <<\
    \ swm.query() << \" \\n\"[r == n];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/sliding_window_minimum.hpp\"\
    \nusing suisen::sliding_window_minimum;\n\nint main() {\n    int n, l;\n    std::cin\
    \ >> n >> l;\n    std::vector<int> a(n);\n    for (int &e : a) std::cin >> e;\n\
    \    sliding_window_minimum<int> swm(n, [&a](int i) { return a[i]; });\n    for\
    \ (int r = l; r <= n; ++r) {\n        swm.proc(r - l, r);\n        std::cout <<\
    \ swm.query() << \" \\n\"[r == n];\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/sliding_window_minimum.hpp
  isVerificationFile: true
  path: test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp
  requiredBy: []
  timestamp: '2022-10-30 21:37:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp
- /verify/test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp.html
title: test/src/datastructure/sliding_window_minimum/DSL_3_D.test.cpp
---
