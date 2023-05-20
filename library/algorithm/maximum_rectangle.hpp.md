---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/maximum_rectangle.hpp\"\n\n\n\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace suisen {\n    // f : (l, r, h) -> void\n\
    \    template <typename HistGram, typename Func>\n    void maximal_rectangles_hist(const\
    \ HistGram& h, Func &&f) {\n        using Value = std::decay_t<decltype(h[0])>;\n\
    \n        static_assert((std::is_invocable_v<Func, int, int, Value>));\n\n   \
    \     const int n = h.size();\n        std::vector<std::pair<int, Value>> stack;\n\
    \        for (int r = 0; r <= n; ++r) {\n            Value hr = r < n ? h[r] :\
    \ 0;\n            int j = r; // min j s.t. min(h[j], ..., h[r]) >= h[r]\n    \
    \        while (stack.size()) {\n                auto [l, hl] = stack.back();\n\
    \                if (hl < hr) break;\n                f(l, r, hl);\n         \
    \       stack.pop_back();\n                j = l;\n            }\n           \
    \ stack.emplace_back(j, hr);\n        }\n    }\n\n    // f : (u, d, l, r) -> void\n\
    \    template <typename Grid, typename Func>\n    void maximal_rectangles(const\
    \ Grid& g, Func &&f) {\n        static_assert((std::is_invocable_v<Func, int,\
    \ int, int, int>));\n        const int n = g.size();\n        if (n == 0) return;\n\
    \        const int m = g[0].size();\n        std::vector<int> h(m), cnt_zero(m\
    \ + 1);\n        for (int i = 0; i < n; ++i) {\n            for (int r = 0; r\
    \ < m; ++r) {\n                h[r] = g[i][r] ? h[r] + 1 : 0;\n              \
    \  cnt_zero[r + 1] = cnt_zero[r] + (i + 1 != n ? not bool(g[i + 1][r]) : 1);\n\
    \            }\n            maximal_rectangles_hist(h, [i, &f, &cnt_zero](int\
    \ l, int r, int h) {\n                if (cnt_zero[r] - cnt_zero[l]) {\n     \
    \               f(i - h + 1, i + 1, l, r);\n                }\n            });\n\
    \        }\n    }\n\n    // Returns { max_area, { u, d, l, r } } where g[u,d)*[l,r)\
    \ is one of the maximum rectangles.\n    template <typename Grid>\n    std::pair<int,\
    \ std::tuple<int, int, int, int>> maximum_rectngle(const Grid& g) {\n        int\
    \ max_area = 0;\n        std::tuple<int, int, int, int> max_rect;\n\n        maximal_rectangles(g,\
    \ [&max_area, &max_rect](int u, int d, int l, int r){\n            int area =\
    \ (d - u) * (r - l);\n            if (area > max_area) {\n                max_area\
    \ = area;\n                max_rect = { u, d, l, r };\n            }\n       \
    \ });\n\n        return { max_area, max_rect };\n    }\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_MAXIMUM_RECTANGLE\n#define SUISEN_MAXIMUM_RECTANGLE\n\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace suisen {\n    // f : (l, r, h) -> void\n\
    \    template <typename HistGram, typename Func>\n    void maximal_rectangles_hist(const\
    \ HistGram& h, Func &&f) {\n        using Value = std::decay_t<decltype(h[0])>;\n\
    \n        static_assert((std::is_invocable_v<Func, int, int, Value>));\n\n   \
    \     const int n = h.size();\n        std::vector<std::pair<int, Value>> stack;\n\
    \        for (int r = 0; r <= n; ++r) {\n            Value hr = r < n ? h[r] :\
    \ 0;\n            int j = r; // min j s.t. min(h[j], ..., h[r]) >= h[r]\n    \
    \        while (stack.size()) {\n                auto [l, hl] = stack.back();\n\
    \                if (hl < hr) break;\n                f(l, r, hl);\n         \
    \       stack.pop_back();\n                j = l;\n            }\n           \
    \ stack.emplace_back(j, hr);\n        }\n    }\n\n    // f : (u, d, l, r) -> void\n\
    \    template <typename Grid, typename Func>\n    void maximal_rectangles(const\
    \ Grid& g, Func &&f) {\n        static_assert((std::is_invocable_v<Func, int,\
    \ int, int, int>));\n        const int n = g.size();\n        if (n == 0) return;\n\
    \        const int m = g[0].size();\n        std::vector<int> h(m), cnt_zero(m\
    \ + 1);\n        for (int i = 0; i < n; ++i) {\n            for (int r = 0; r\
    \ < m; ++r) {\n                h[r] = g[i][r] ? h[r] + 1 : 0;\n              \
    \  cnt_zero[r + 1] = cnt_zero[r] + (i + 1 != n ? not bool(g[i + 1][r]) : 1);\n\
    \            }\n            maximal_rectangles_hist(h, [i, &f, &cnt_zero](int\
    \ l, int r, int h) {\n                if (cnt_zero[r] - cnt_zero[l]) {\n     \
    \               f(i - h + 1, i + 1, l, r);\n                }\n            });\n\
    \        }\n    }\n\n    // Returns { max_area, { u, d, l, r } } where g[u,d)*[l,r)\
    \ is one of the maximum rectangles.\n    template <typename Grid>\n    std::pair<int,\
    \ std::tuple<int, int, int, int>> maximum_rectngle(const Grid& g) {\n        int\
    \ max_area = 0;\n        std::tuple<int, int, int, int> max_rect;\n\n        maximal_rectangles(g,\
    \ [&max_area, &max_rect](int u, int d, int l, int r){\n            int area =\
    \ (d - u) * (r - l);\n            if (area > max_area) {\n                max_area\
    \ = area;\n                max_rect = { u, d, l, r };\n            }\n       \
    \ });\n\n        return { max_area, max_rect };\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_MAXIMUM_RECTANGLE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/maximum_rectangle.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:17:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/maximum_rectangle.hpp
layout: document
title: Maximum Rectangle
---
## Maximum Rectangle
