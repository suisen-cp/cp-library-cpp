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
  bundledCode: "#line 1 \"library/geom/convex_hull.hpp\"\n#include <algorithm>\n#include\
    \ <complex>\n#include <numeric>\n#include <vector>\n\nnamespace suisen {\nnamespace\
    \ geometry {\n    template <typename T>\n    std::vector<int> convex_hull(const\
    \ std::vector<std::complex<T>> &points) {\n        const int n = points.size();\n\
    \        std::vector<int> sorted(n);\n        std::iota(sorted.begin(), sorted.end(),\
    \ 0);\n        std::sort(sorted.begin(), sorted.end(), [&points](int i, int j)\
    \ {\n            auto &a = points[i], &b = points[j];\n            return a.real()\
    \ == b.real() ? a.imag() < b.imag() : a.real() < b.real();\n        });\n    \
    \    std::vector<char> used(n, false);\n        sorted.resize(2 * n - 1);\n  \
    \      std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);\n  \
    \      std::vector<int> res;\n        res.reserve(n);\n        int first = sorted[0],\
    \ last = sorted[n - 1];\n        const T eps = 1e-9;\n        auto sgn = [&eps](T\
    \ x) -> int {\n            return x <= -eps ? -1 : x >= eps ? 1 : 0;\n       \
    \ };\n        auto isp_pos = [&sgn](T x1, T y1, T x2, T y2) -> bool {\n      \
    \      int det_sgn = sgn(x1 * y2 - y1 * x2);\n            return det_sgn > 0 or\
    \ (det_sgn == 0 and sgn(x1 * x2 + y1 * y2) > 0);\n        };\n        for (int\
    \ k : sorted) {\n            if (k != first and used[k]) continue;\n         \
    \   for (int sz = res.size(); sz >= 2; --sz) {\n                int i = res[sz\
    \ - 2], j = res[sz - 1];\n                if (j == last) break;\n            \
    \    std::complex<T> ab = points[j] - points[i];\n                std::complex<T>\
    \ bc = points[k] - points[j];\n                if (isp_pos(ab.real(), ab.imag(),\
    \ bc.real(), bc.imag())) break;\n                res.pop_back(), used[j] = false;\n\
    \            }\n            if (not used[k]) res.push_back(k);\n            used[k]\
    \ = true;\n        }\n        return res;\n    }\n    std::vector<int> convex_hull(const\
    \ std::vector<std::pair<long long, long long>> &points) {\n        const int n\
    \ = points.size();\n        std::vector<int> sorted(n);\n        std::iota(sorted.begin(),\
    \ sorted.end(), 0);\n        std::sort(sorted.begin(), sorted.end(), [&points](int\
    \ i, int j) {\n            auto &a = points[i], &b = points[j];\n            return\
    \ a.first == b.first ? a.second < b.second : a.first < b.first;\n        });\n\
    \        std::vector<char> used(n, false);\n        sorted.resize(2 * n - 1);\n\
    \        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);\n\
    \        std::vector<int> res;\n        res.reserve(n);\n        int first = sorted[0],\
    \ last = sorted[n - 1];\n        auto isp_pos = [](long long x1, long long y1,\
    \ long long x2, long long y2) -> bool {\n            long long det = x1 * y2 -\
    \ y1 * x2;\n            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);\n\
    \        };\n        for (int k : sorted) {\n            if (k != first and used[k])\
    \ continue;\n            for (int sz = res.size(); sz >= 2; --sz) {\n        \
    \        int i = res[sz - 2], j = res[sz - 1];\n                if (j == last)\
    \ break;\n                long long ab_x = points[j].first - points[i].first,\
    \ ab_y = points[j].second - points[i].second;\n                long long bc_x\
    \ = points[k].first - points[j].first, bc_y = points[k].second - points[j].second;\n\
    \                if (isp_pos(ab_x, ab_y, bc_x, bc_y)) break;\n               \
    \ res.pop_back(), used[j] = false;\n            }\n            if (not used[k])\
    \ res.push_back(k);\n            used[k] = true;\n        }\n        return res;\n\
    \    }\n}\n} // namespace suisen\n"
  code: "#include <algorithm>\n#include <complex>\n#include <numeric>\n#include <vector>\n\
    \nnamespace suisen {\nnamespace geometry {\n    template <typename T>\n    std::vector<int>\
    \ convex_hull(const std::vector<std::complex<T>> &points) {\n        const int\
    \ n = points.size();\n        std::vector<int> sorted(n);\n        std::iota(sorted.begin(),\
    \ sorted.end(), 0);\n        std::sort(sorted.begin(), sorted.end(), [&points](int\
    \ i, int j) {\n            auto &a = points[i], &b = points[j];\n            return\
    \ a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();\n        });\n\
    \        std::vector<char> used(n, false);\n        sorted.resize(2 * n - 1);\n\
    \        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);\n\
    \        std::vector<int> res;\n        res.reserve(n);\n        int first = sorted[0],\
    \ last = sorted[n - 1];\n        const T eps = 1e-9;\n        auto sgn = [&eps](T\
    \ x) -> int {\n            return x <= -eps ? -1 : x >= eps ? 1 : 0;\n       \
    \ };\n        auto isp_pos = [&sgn](T x1, T y1, T x2, T y2) -> bool {\n      \
    \      int det_sgn = sgn(x1 * y2 - y1 * x2);\n            return det_sgn > 0 or\
    \ (det_sgn == 0 and sgn(x1 * x2 + y1 * y2) > 0);\n        };\n        for (int\
    \ k : sorted) {\n            if (k != first and used[k]) continue;\n         \
    \   for (int sz = res.size(); sz >= 2; --sz) {\n                int i = res[sz\
    \ - 2], j = res[sz - 1];\n                if (j == last) break;\n            \
    \    std::complex<T> ab = points[j] - points[i];\n                std::complex<T>\
    \ bc = points[k] - points[j];\n                if (isp_pos(ab.real(), ab.imag(),\
    \ bc.real(), bc.imag())) break;\n                res.pop_back(), used[j] = false;\n\
    \            }\n            if (not used[k]) res.push_back(k);\n            used[k]\
    \ = true;\n        }\n        return res;\n    }\n    std::vector<int> convex_hull(const\
    \ std::vector<std::pair<long long, long long>> &points) {\n        const int n\
    \ = points.size();\n        std::vector<int> sorted(n);\n        std::iota(sorted.begin(),\
    \ sorted.end(), 0);\n        std::sort(sorted.begin(), sorted.end(), [&points](int\
    \ i, int j) {\n            auto &a = points[i], &b = points[j];\n            return\
    \ a.first == b.first ? a.second < b.second : a.first < b.first;\n        });\n\
    \        std::vector<char> used(n, false);\n        sorted.resize(2 * n - 1);\n\
    \        std::copy(sorted.rbegin() + n, sorted.rend(), sorted.begin() + n);\n\
    \        std::vector<int> res;\n        res.reserve(n);\n        int first = sorted[0],\
    \ last = sorted[n - 1];\n        auto isp_pos = [](long long x1, long long y1,\
    \ long long x2, long long y2) -> bool {\n            long long det = x1 * y2 -\
    \ y1 * x2;\n            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);\n\
    \        };\n        for (int k : sorted) {\n            if (k != first and used[k])\
    \ continue;\n            for (int sz = res.size(); sz >= 2; --sz) {\n        \
    \        int i = res[sz - 2], j = res[sz - 1];\n                if (j == last)\
    \ break;\n                long long ab_x = points[j].first - points[i].first,\
    \ ab_y = points[j].second - points[i].second;\n                long long bc_x\
    \ = points[k].first - points[j].first, bc_y = points[k].second - points[j].second;\n\
    \                if (isp_pos(ab_x, ab_y, bc_x, bc_y)) break;\n               \
    \ res.pop_back(), used[j] = false;\n            }\n            if (not used[k])\
    \ res.push_back(k);\n            used[k] = true;\n        }\n        return res;\n\
    \    }\n}\n} // namespace suisen\n"
  dependsOn: []
  isVerificationFile: false
  path: library/geom/convex_hull.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/geom/convex_hull.hpp
layout: document
redirect_from:
- /library/library/geom/convex_hull.hpp
- /library/library/geom/convex_hull.hpp.html
title: library/geom/convex_hull.hpp
---
