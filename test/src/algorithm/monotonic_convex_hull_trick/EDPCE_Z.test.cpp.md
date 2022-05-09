---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/monotonic_convex_hull_trick.hpp
    title: "\u50BE\u304D\u306E\u5358\u8ABF\u6027\u3092\u4EEE\u5B9A\u3059\u308B Convex\
      \ Hull Trick"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/dp/tasks/dp_z
    links:
    - https://atcoder.jp/contests/dp/tasks/dp_z
  bundledCode: "#line 1 \"test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/dp/tasks/dp_z\"\n\n#include <iostream>\n\
    \n#line 1 \"library/algorithm/monotonic_convex_hull_trick.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\n#include <type_traits>\n\
    \nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 9 \"library/algorithm/monotonic_convex_hull_trick.hpp\"\n\nnamespace suisen\
    \ {\n\ntemplate <typename T, bool is_min_query = true>\nclass MonotonicCHT {\n\
    \    using MultT = safely_multipliable_t<T>;\n\n    public:\n        MonotonicCHT()\
    \ {}\n    \n        void add_line(T slope, T intercept) {\n            if constexpr\
    \ (not is_min_query) {\n                slope = -slope;\n                intercept\
    \ = -intercept;\n            }\n            if (slope <= min_slope) {\n      \
    \          min_slope = slope;\n                max_slope = std::max(max_slope,\
    \ slope);\n                add_right(slope, intercept);\n            } else if\
    \ (slope >= max_slope) {\n                max_slope = slope;\n               \
    \ min_slope = std::min(min_slope, slope);\n                add_left(slope, intercept);\n\
    \            } else assert(false);\n        }\n\n        MultT query(T x) const\
    \ {\n            assert(not (called_ascending_query or called_descending_query));\n\
    \            called_general_query = true;\n            assert(lines.size() > 0);\n\
    \            int l = -1, r = lines.size();\n            while (r - l >= 3) {\n\
    \                int ml = l + (r - l) / 3;\n                int mr = r - (r -\
    \ l) / 3;\n                if (eval(x, ml) < eval(x, mr)) {\n                \
    \    r = mr;\n                } else {\n                    l = ml;\n        \
    \        }\n            }\n            assert(r - l == 2);\n            MultT\
    \ res = eval(l + 1);\n            return is_min_query ? res : -res;\n        }\n\
    \n        MultT ascending_query(T x) {\n            assert(not (called_general_query\
    \ or called_descending_query));\n            if (not called_ascending_query) {\n\
    \                prev_query = x;\n                called_ascending_query = true;\n\
    \            }\n            assert(x >= prev_query);\n            prev_query =\
    \ x;\n            assert(lines.size() > 0);\n            MultT res = eval(x, 0);\n\
    \            while (lines.size() >= 2) {\n                MultT nxt_res = eval(x,\
    \ 1);\n                if (res < nxt_res) break;\n                lines.pop_front();\n\
    \                std::swap(res, nxt_res);\n            }\n            return is_min_query\
    \ ? res : -res;\n        }\n\n        MultT descending_query(T x) {\n        \
    \    assert(not (called_general_query or called_ascending_query));\n         \
    \   if (not called_descending_query) {\n                prev_query = x;\n    \
    \            called_descending_query = true;\n            }\n            assert(x\
    \ <= prev_query);\n            prev_query = x;\n            assert(lines.size()\
    \ > 0);\n            MultT res = eval(x, lines.size() - 1);\n            while\
    \ (lines.size() >= 2) {\n                MultT nxt_res = eval(x, lines.size()\
    \ - 2);\n                if (res < nxt_res) break;\n                lines.pop_back();\n\
    \                std::swap(res, nxt_res);\n            }\n            return is_min_query\
    \ ? res : -res;\n        }\n\n    private:\n        std::deque<std::pair<T, T>>\
    \ lines;\n        T max_slope = std::numeric_limits<T>::min();\n        T min_slope\
    \ = std::numeric_limits<T>::max();\n\n        bool called_general_query = false;\n\
    \        bool called_ascending_query = false;\n        bool called_descending_query\
    \ = false;\n\n        T prev_query = 0;\n\n        // check if ma * x + mb is\
    \ necessary.\n        bool is_necessary(T la, T lb, T ma, T mb, T ra, T rb) {\n\
    \            return (MultT) (lb - mb) * (ra - ma) > (MultT) (mb - rb) * (ma -\
    \ la);\n        }\n\n        void add_left(T slope, T intercept) {\n         \
    \   while (lines.size()) {\n                auto it = lines.begin();\n       \
    \         const auto [a, b] = *it;\n                if (a == slope) {\n      \
    \              if (intercept >= b) return;\n                } else {\n       \
    \             if (++it == lines.end() or is_necessary(it->first, it->second, a,\
    \ b, slope, intercept)) break;\n                }\n                lines.pop_front();\n\
    \            }\n            lines.emplace_front(slope, intercept);\n        }\n\
    \n        void add_right(T slope, T intercept) {\n            while (lines.size())\
    \ {\n                auto it = lines.rbegin();\n                const auto [a,\
    \ b] = *it;\n                if (a == slope) {\n                    if (intercept\
    \ >= b) return;\n                } else {\n                    if (++it == lines.rend()\
    \ or is_necessary(slope, intercept, a, b, it->first, it->second)) break;\n   \
    \             }\n                lines.pop_back();\n            }\n          \
    \  lines.emplace_back(slope, intercept);\n        }\n\n        MultT eval(T x,\
    \ int i) {\n            const auto &[a, b] = lines[i];\n            return (MultT)\
    \ a * x + b;\n        }\n};\n\n} // namespace suisen\n\n\n#line 6 \"test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp\"\
    \n\nusing suisen::MonotonicCHT;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    long long c;\n    std::cin >> n >>\
    \ c;\n    std::vector<long long> h(n);\n    for (int i = 0; i < n; ++i) {\n  \
    \      std::cin >> h[i];\n    }\n    std::vector<long long> dp(n, 0);\n    MonotonicCHT<long\
    \ long> cht;\n    for (int i = 1; i < n; ++i) {\n        cht.add_line(-2 * h[i\
    \ - 1], dp[i - 1] + h[i - 1] * h[i - 1]);\n        dp[i] = cht.ascending_query(h[i])\
    \ + h[i] * h[i] + c;\n    }\n    std::cout << dp[n - 1] << std::endl;\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/dp/tasks/dp_z\"\n\n#include\
    \ <iostream>\n\n#include \"library/algorithm/monotonic_convex_hull_trick.hpp\"\
    \n\nusing suisen::MonotonicCHT;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    long long c;\n    std::cin >> n >>\
    \ c;\n    std::vector<long long> h(n);\n    for (int i = 0; i < n; ++i) {\n  \
    \      std::cin >> h[i];\n    }\n    std::vector<long long> dp(n, 0);\n    MonotonicCHT<long\
    \ long> cht;\n    for (int i = 1; i < n; ++i) {\n        cht.add_line(-2 * h[i\
    \ - 1], dp[i - 1] + h[i - 1] * h[i - 1]);\n        dp[i] = cht.ascending_query(h[i])\
    \ + h[i] * h[i] + c;\n    }\n    std::cout << dp[n - 1] << std::endl;\n    return\
    \ 0;\n}"
  dependsOn:
  - library/algorithm/monotonic_convex_hull_trick.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp
  requiredBy: []
  timestamp: '2022-05-09 17:42:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp
layout: document
redirect_from:
- /verify/test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp
- /verify/test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp.html
title: test/src/algorithm/monotonic_convex_hull_trick/EDPCE_Z.test.cpp
---
