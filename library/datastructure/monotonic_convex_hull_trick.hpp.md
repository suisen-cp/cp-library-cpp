---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_dec.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_dec.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_nonmonotonic.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_nonmonotonic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_dec.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_dec.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_inc.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_inc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_nonmonotonic.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_nonmonotonic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/monotonic_convex_hull_trick/abc228_h.test.cpp
    title: test/src/datastructure/monotonic_convex_hull_trick/abc228_h.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/monotonic_convex_hull_trick.hpp\"\n\
    \n\n\n#include <cassert>\n#include <limits>\n#include <queue>\n#include <type_traits>\n\
    \nnamespace suisen {\n    namespace internal::monotonic_cht { struct query_tag_base\
    \ {}; }\n    struct inc_query_tag : internal::monotonic_cht::query_tag_base {};\n\
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
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_MONOTONIC_CHT\n#define SUISEN_MONOTONIC_CHT\n\n#include <cassert>\n\
    #include <limits>\n#include <queue>\n#include <type_traits>\n\nnamespace suisen\
    \ {\n    namespace internal::monotonic_cht { struct query_tag_base {}; }\n   \
    \ struct inc_query_tag : internal::monotonic_cht::query_tag_base {};\n    struct\
    \ dec_query_tag : internal::monotonic_cht::query_tag_base {};\n    struct non_monotonic_query_tag\
    \ : internal::monotonic_cht::query_tag_base {};\n\n    template <typename T, bool\
    \ is_min_query, typename QueryTag,\n        std::enable_if_t<std::is_base_of_v<internal::monotonic_cht::query_tag_base,\
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
    \ suisen\n\n#endif // SUISEN_MONOTONIC_CHT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/monotonic_convex_hull_trick.hpp
  requiredBy: []
  timestamp: '2022-10-30 21:37:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/monotonic_convex_hull_trick/abc228_h.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_dec.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_nonmonotonic.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_dec.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_min_inc.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_inc.test.cpp
  - test/src/datastructure/monotonic_convex_hull_trick/EDPC_Z_max_nonmonotonic.test.cpp
documentation_of: library/datastructure/monotonic_convex_hull_trick.hpp
layout: document
title: "Convex Hull Trick (\u50BE\u304D\u304C\u5358\u8ABF\u306A\u5834\u5408)"
---
## Convex Hull Trick (傾きが単調な場合)
