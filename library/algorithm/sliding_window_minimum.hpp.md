---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
    title: test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/sliding_window_minimum.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n#include <queue>\n#include <type_traits>\n\nnamespace\
    \ suisen {\nnamespace prioritizing_mode {\n    template <typename T>\n    using\
    \ left_most_min  = std::greater<T>;\n    template <typename T>\n    using right_most_min\
    \ = std::greater_equal<T>;\n    template <typename T>\n    using left_most_max\
    \  = std::less<T>;\n    template <typename T>\n    using right_most_max = std::less_equal<T>;\n\
    }\n\ntemplate <\n    typename T, typename Comparator = prioritizing_mode::left_most_min<T>,\n\
    \    std::enable_if_t<std::is_invocable_r_v<bool, Comparator, T, T>, std::nullptr_t>\
    \ = nullptr\n>\nclass sliding_window_minimum {\n    public:\n        template\
    \ <typename Gen, std::enable_if_t<std::is_invocable_r_v<T, Gen, int>, std::nullptr_t>\
    \ = nullptr>\n        sliding_window_minimum(int n, Gen gen) : _n(n), _a(n) {\n\
    \            for (int i = 0; i < _n; ++i) _a[i] = gen(i);\n        }\n       \
    \ void proc_right() {\n            assert(_r < _n);\n            T v = _a[_r];\n\
    \            while (not _dq.empty() and _cmp(_a[_dq.back()], v)) _dq.pop_back();\n\
    \            _dq.push_back(_r++);\n        }\n        void proc_right(int to_index)\
    \ {\n            while (_r < to_index) proc_right();\n        }\n        void\
    \ proc_left() {\n            assert(_l < _r);\n            if (_dq.front() ==\
    \ _l) _dq.pop_front();\n            ++_l;\n        }\n        void proc_left(int\
    \ to_index) {\n            while (_l < to_index) proc_left();\n        }\n   \
    \     void proc(int new_l, int new_r) {\n            proc_right(new_r), proc_left(new_l);\n\
    \        }\n        int arg_query() const {\n            assert(_l < _r);\n  \
    \          return _dq.front();\n        }\n        T query() const {\n       \
    \     return _a[arg_query()];\n        }\n\n        int get_left() const {\n \
    \           return _l;\n        }\n        int get_right() const {\n         \
    \   return _r;\n        }\n        int get_window_size() const {\n           \
    \ return _r - _l;\n        }\n    private:\n        const int _n;\n        int\
    \ _l = 0, _r = 0;\n        std::vector<T> _a;\n        std::deque<int> _dq;\n\
    \        Comparator _cmp;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SLIDING_WINDOW_MINIMUM\n#define SUISEN_SLIDING_WINDOW_MINIMUM\n\
    \n#include <cassert>\n#include <vector>\n#include <queue>\n#include <type_traits>\n\
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
    \ _dq;\n        Comparator _cmp;\n};\n} // namespace suisen\n\n#endif // SUISEN_SLIDING_WINDOW_MINIMUM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/sliding_window_minimum.hpp
  requiredBy: []
  timestamp: '2022-10-08 03:16:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
documentation_of: library/algorithm/sliding_window_minimum.hpp
layout: document
title: Sliding Window Minimum
---
## Sliding Window Minimum

長さ $N$ の列 $A=(A_0,\ldots, A_{N-1})$ と $0$ で初期化された整数 $l,r$ に対して、次の操作を行う。

- $\mathrm{proc\\_right}$ : $r\leftarrow r + 1$ とする。操作前の時点で $r=N$ の場合、この操作はできない。
- $\mathrm{proc\\_left}$ : $l\leftarrow l + 1$ とする。操作前の時点で $l=r$ の場合、この操作はできない。
- $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
- $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。

$\mathrm{proc\\_right}$ は償却 $\Theta(1)$ 時間、その他は最悪 $\Theta(1)$ 時間である。

テンプレート引数の第二引数によって、$\min$ と $\max$ のどちらを計算するか、また $\mathrm{arg\\_query}$ において等しい値が複数ある場合により小さい添字を優先するか、より大きい添字を優先するかの挙動を選択することが出来る。

`suisen::prioritizing_mode` 名前空間にテンプレート引数の第二引数に与えるための比較器の型エイリアスが定義されている。意味は次の通り。

- `suisen::prioritizing_mode::left_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最小__ のものを返す。
- `suisen::prioritizing_mode::right_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \min _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\min}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最大__ のものを返す。
- `suisen::prioritizing_mode::left_most_max<T>`
  - $\mathrm{query}$ : $\displaystyle \max _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\max}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最小__ のものを返す。
- `suisen::prioritizing_mode::left_most_min<T>`
  - $\mathrm{query}$ : $\displaystyle \max _ {l\leq i\lt r} A _ i$ を返す。
  - $\mathrm{arg\\_query}$ : $\displaystyle \mathop{\underset{l\leq i\lt r}{\mathrm{arg}\max}} A _ i$ を返す。最小値を達成する添字が複数ある場合は、添字が __最大__ のものを返す。
