---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
    title: test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
  - icon: ':x:'
    path: test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
    title: test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/sliding_window_minimum.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n#include <queue>\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 8 \"\
    library/algorithm/sliding_window_minimum.hpp\"\n\nnamespace suisen {\nnamespace\
    \ prioritizing_mode {\n    template <typename T>\n    using left_most_min  = std::greater<T>;\n\
    \    template <typename T>\n    using right_most_min = std::greater_equal<T>;\n\
    \    template <typename T>\n    using left_most_max  = std::less<T>;\n    template\
    \ <typename T>\n    using right_most_max = std::less_equal<T>;\n}\n\ntemplate\
    \ <typename T, typename Comparator = prioritizing_mode::left_most_min<T>, constraints_t<is_comparator<Comparator,\
    \ T>> = nullptr>\nclass sliding_window_minimum {\n    public:\n        template\
    \ <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>\n\
    \        sliding_window_minimum(int n, Gen gen) : _n(n), _a(n) {\n           \
    \ for (int i = 0; i < _n; ++i) _a[i] = gen(i);\n        }\n        void proc_right()\
    \ {\n            assert(_r < _n);\n            T v = _a[_r];\n            while\
    \ (not _dq.empty() and _cmp(_a[_dq.back()], v)) _dq.pop_back();\n            _dq.push_back(_r++);\n\
    \        }\n        void proc_right(int to_index) {\n            while (_r < to_index)\
    \ proc_right();\n        }\n        void proc_left() {\n            assert(_l\
    \ < _r);\n            if (_dq.front() == _l) _dq.pop_front();\n            ++_l;\n\
    \        }\n        void proc_left(int to_index) {\n            while (_l < to_index)\
    \ proc_left();\n        }\n        void proc(int new_l, int new_r) {\n       \
    \     proc_right(new_r), proc_left(new_l);\n        }\n        int arg_query()\
    \ const {\n            assert(_l < _r);\n            return _dq.front();\n   \
    \     }\n        T query() const {\n            return _a[arg_query()];\n    \
    \    }\n\n        int get_left() const {\n            return _l;\n        }\n\
    \        int get_right() const {\n            return _r;\n        }\n        int\
    \ get_window_size() const {\n            return _r - _l;\n        }\n    private:\n\
    \        const int _n;\n        int _l = 0, _r = 0;\n        std::vector<T> _a;\n\
    \        std::deque<int> _dq;\n        Comparator _cmp;\n};\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_SLIDING_WINDOW_MINIMUM\n#define SUISEN_SLIDING_WINDOW_MINIMUM\n\
    \n#include <cassert>\n#include <vector>\n#include <queue>\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\nnamespace prioritizing_mode {\n    template <typename\
    \ T>\n    using left_most_min  = std::greater<T>;\n    template <typename T>\n\
    \    using right_most_min = std::greater_equal<T>;\n    template <typename T>\n\
    \    using left_most_max  = std::less<T>;\n    template <typename T>\n    using\
    \ right_most_max = std::less_equal<T>;\n}\n\ntemplate <typename T, typename Comparator\
    \ = prioritizing_mode::left_most_min<T>, constraints_t<is_comparator<Comparator,\
    \ T>> = nullptr>\nclass sliding_window_minimum {\n    public:\n        template\
    \ <typename Gen, constraints_t<is_same_as_invoke_result<T, Gen, int>> = nullptr>\n\
    \        sliding_window_minimum(int n, Gen gen) : _n(n), _a(n) {\n           \
    \ for (int i = 0; i < _n; ++i) _a[i] = gen(i);\n        }\n        void proc_right()\
    \ {\n            assert(_r < _n);\n            T v = _a[_r];\n            while\
    \ (not _dq.empty() and _cmp(_a[_dq.back()], v)) _dq.pop_back();\n            _dq.push_back(_r++);\n\
    \        }\n        void proc_right(int to_index) {\n            while (_r < to_index)\
    \ proc_right();\n        }\n        void proc_left() {\n            assert(_l\
    \ < _r);\n            if (_dq.front() == _l) _dq.pop_front();\n            ++_l;\n\
    \        }\n        void proc_left(int to_index) {\n            while (_l < to_index)\
    \ proc_left();\n        }\n        void proc(int new_l, int new_r) {\n       \
    \     proc_right(new_r), proc_left(new_l);\n        }\n        int arg_query()\
    \ const {\n            assert(_l < _r);\n            return _dq.front();\n   \
    \     }\n        T query() const {\n            return _a[arg_query()];\n    \
    \    }\n\n        int get_left() const {\n            return _l;\n        }\n\
    \        int get_right() const {\n            return _r;\n        }\n        int\
    \ get_window_size() const {\n            return _r - _l;\n        }\n    private:\n\
    \        const int _n;\n        int _l = 0, _r = 0;\n        std::vector<T> _a;\n\
    \        std::deque<int> _dq;\n        Comparator _cmp;\n};\n} // namespace suisen\n\
    \n#endif // SUISEN_SLIDING_WINDOW_MINIMUM\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/algorithm/sliding_window_minimum.hpp
  requiredBy: []
  timestamp: '2021-07-20 14:25:15+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/algorithm/sliding_window_minimum/tenkei006.test.cpp
  - test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
documentation_of: library/algorithm/sliding_window_minimum.hpp
layout: document
redirect_from:
- /library/library/algorithm/sliding_window_minimum.hpp
- /library/library/algorithm/sliding_window_minimum.hpp.html
title: library/algorithm/sliding_window_minimum.hpp
---
