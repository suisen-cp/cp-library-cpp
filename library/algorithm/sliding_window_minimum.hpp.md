---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
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
    \ <cassert>\n#include <vector>\n#include <queue>\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 8 \"library/algorithm/sliding_window_minimum.hpp\"\
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
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/algorithm/sliding_window_minimum/DSL_3_D.test.cpp
documentation_of: library/algorithm/sliding_window_minimum.hpp
layout: document
title: Sliding Window Minimum
---
## Sliding Window Minimum