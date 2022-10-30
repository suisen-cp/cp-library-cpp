---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/monotonic_convex_hull_trick.hpp
    title: library/datastructure/monotonic_convex_hull_trick.hpp
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
  bundledCode: "#line 1 \"test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/dp/tasks/dp_z\"\n\n#include <iostream>\n\
    \n#line 1 \"library/datastructure/monotonic_convex_hull_trick.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    namespace internal::monotonic_cht { struct query_tag_base {};\
    \ }\n    struct inc_query_tag : internal::monotonic_cht::query_tag_base {};\n\
    \    struct dec_query_tag : internal::monotonic_cht::query_tag_base {};\n    struct\
    \ non_monotonic_query_tag : internal::monotonic_cht::query_tag_base {};\n\n  \
    \  template <typename T, bool is_min_query, typename QueryTag,\n        std::enable_if_t<std::is_base_of_v<internal::monotonic_cht::query_tag_base,\
    \ QueryTag>, std::nullptr_t> = nullptr\n    >\n    struct MonotonicCHT {\n   \
    \     using value_type = T;\n        using query_tag = QueryTag;\n\n        MonotonicCHT()\
    \ = default;\n    private:\n        template <typename, typename = void>\n   \
    \     struct query_impl {};\n        template <typename Dummy>\n        struct\
    \ query_impl<inc_query_tag, Dummy> {\n            value_type prev_x = std::numeric_limits<value_type>::min();\n\
    \            value_type operator()(MonotonicCHT* ptr, value_type x) {\n      \
    \          assert(x >= prev_x);\n                prev_x = x;\n               \
    \ assert(ptr->lines.size());\n                value_type res = ptr->eval(x, 0);\n\
    \                while (ptr->lines.size() >= 2) {\n                    value_type\
    \ nxt_res = ptr->eval(x, 1);\n                    if (res < nxt_res) break;\n\
    \                    ptr->lines.pop_front();\n                    std::swap(res,\
    \ nxt_res);\n                }\n                return res;\n            }\n \
    \       };\n        template <typename Dummy>\n        struct query_impl<dec_query_tag,\
    \ Dummy> {\n            value_type prev_x = std::numeric_limits<value_type>::max();\n\
    \            value_type operator()(MonotonicCHT* ptr, value_type x) {\n      \
    \          assert(x <= prev_x);\n                prev_x = x;\n               \
    \ assert(ptr->lines.size());\n                value_type res = ptr->eval(x, ptr->lines.size()\
    \ - 1);\n                while (ptr->lines.size() >= 2) {\n                  \
    \  value_type nxt_res = ptr->eval(x, ptr->lines.size() - 2);\n               \
    \     if (res < nxt_res) break;\n                    ptr->lines.pop_back();\n\
    \                    std::swap(res, nxt_res);\n                }\n           \
    \     return res;\n            }\n        };\n        template <typename Dummy>\n\
    \        struct query_impl<non_monotonic_query_tag, Dummy> {\n            value_type\
    \ operator()(MonotonicCHT* ptr, value_type x) {\n                assert(ptr->lines.size());\n\
    \                int l = -1, r = ptr->lines.size();\n                while (r\
    \ - l >= 3) {\n                    int ml = l + (r - l) / 3;\n               \
    \     int mr = r - (r - l) / 3;\n                    if (ptr->eval(x, ml) < ptr->eval(x,\
    \ mr)) {\n                        r = mr;\n                    } else {\n    \
    \                    l = ml;\n                    }\n                }\n     \
    \           assert(r - l == 2);\n                return ptr->eval(x, l + 1);\n\
    \            }\n        };\n    public:\n        void add_line(value_type slope,\
    \ value_type intercept) {\n            if constexpr (not is_min_query) slope =\
    \ -slope, intercept = -intercept;\n            if (slope <= min_slope) {\n   \
    \             min_slope = slope, max_slope = std::max(max_slope, slope);\n   \
    \             add_right(slope, intercept);\n            } else if (slope >= max_slope)\
    \ {\n                max_slope = slope, min_slope = std::min(min_slope, slope);\n\
    \                add_left(slope, intercept);\n            } else assert(false);\n\
    \        }\n\n        value_type query(value_type x) {\n            return (is_min_query\
    \ ? 1 : -1) * _query(this, x);\n        }\n    private:\n        std::deque<std::pair<value_type,\
    \ value_type>> lines;\n        value_type max_slope = std::numeric_limits<value_type>::min();\n\
    \        value_type min_slope = std::numeric_limits<value_type>::max();\n    \
    \    query_impl<query_tag> _query{};\n\n        // check if ma * x + mb is necessary.\n\
    \        bool is_necessary(value_type la, value_type lb, value_type ma, value_type\
    \ mb, value_type ra, value_type rb) {\n            using MultT = std::conditional_t<std::is_integral_v<value_type>,\
    \ __int128_t, value_type>;\n            return MultT(lb - mb) * (ra - ma) > MultT(mb\
    \ - rb) * (ma - la);\n        }\n\n        void add_left(value_type slope, value_type\
    \ intercept) {\n            while (lines.size()) {\n                auto it =\
    \ lines.begin();\n                const auto [a, b] = *it;\n                if\
    \ (a == slope) {\n                    if (intercept >= b) return;\n          \
    \      } else {\n                    if (++it == lines.end() or is_necessary(it->first,\
    \ it->second, a, b, slope, intercept)) break;\n                }\n           \
    \     lines.pop_front();\n            }\n            lines.emplace_front(slope,\
    \ intercept);\n        }\n\n        void add_right(value_type slope, value_type\
    \ intercept) {\n            while (lines.size()) {\n                auto it =\
    \ lines.rbegin();\n                const auto [a, b] = *it;\n                if\
    \ (a == slope) {\n                    if (intercept >= b) return;\n          \
    \      } else {\n                    if (++it == lines.rend() or is_necessary(slope,\
    \ intercept, a, b, it->first, it->second)) break;\n                }\n       \
    \         lines.pop_back();\n            }\n            lines.emplace_back(slope,\
    \ intercept);\n        }\n\n        value_type eval(value_type x, int i) {\n \
    \           const auto& [a, b] = lines[i];\n            return a * x + b;\n  \
    \      }\n    };\n\n    template <typename T, typename QueryTag>\n    using MinMonotonicCHT\
    \ = MonotonicCHT<T, true, QueryTag>;\n    template <typename T, typename QueryTag>\n\
    \    using MaxMonotonicCHT = MonotonicCHT<T, false, QueryTag>;\n} // namespace\
    \ suisen\n\n\n#line 6 \"test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp\"\
    \n\nusing suisen::MaxMonotonicCHT;\nusing suisen::inc_query_tag;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    long long c;\n    std::cin >> n >> c;\n    std::vector<long long> h(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cin >> h[i];\n    }\n    std::vector<long\
    \ long> dp(n, 0);\n    MaxMonotonicCHT<long long, inc_query_tag> cht;\n    for\
    \ (int i = 1; i < n; ++i) {\n        cht.add_line(2 * h[i - 1], -(dp[i - 1] +\
    \ h[i - 1] * h[i - 1]));\n        dp[i] = -cht.query(h[i]) + h[i] * h[i] + c;\n\
    \    }\n    std::cout << dp[n - 1] << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/dp/tasks/dp_z\"\n\n#include\
    \ <iostream>\n\n#include \"library/datastructure/monotonic_convex_hull_trick.hpp\"\
    \n\nusing suisen::MaxMonotonicCHT;\nusing suisen::inc_query_tag;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    long long c;\n    std::cin >> n >> c;\n    std::vector<long long> h(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cin >> h[i];\n    }\n    std::vector<long\
    \ long> dp(n, 0);\n    MaxMonotonicCHT<long long, inc_query_tag> cht;\n    for\
    \ (int i = 1; i < n; ++i) {\n        cht.add_line(2 * h[i - 1], -(dp[i - 1] +\
    \ h[i - 1] * h[i - 1]));\n        dp[i] = -cht.query(h[i]) + h[i] * h[i] + c;\n\
    \    }\n    std::cout << dp[n - 1] << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/monotonic_convex_hull_trick.hpp
  isVerificationFile: true
  path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
  requiredBy: []
  timestamp: '2022-10-30 21:37:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
- /verify/test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp.html
title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
---
