---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/li_chao_segment_tree.hpp
    title: Li Chao Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 1 \"library/datastructure/segment_tree/li_chao_segment_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T, bool is_min_query\
    \ = true>\n    class LiChaoSegmentTree {\n        struct Line {\n            static\
    \ constexpr Line e{ T(0), std::numeric_limits<T>::max() };\n            T a, b;\n\
    \            bool operator==(const Line& other) const {\n                return\
    \ a == other.a and b == other.b;\n            }\n            T operator()(T x)\
    \ const {\n                return *this == e ? std::numeric_limits<T>::max() :\
    \ a * x + b;\n            }\n            Line operator-() const { return Line{\
    \ -a, -b }; }\n        };\n\n    public:\n        LiChaoSegmentTree() : LiChaoSegmentTree(std::vector<T>{})\
    \ {}\n\n        // `query_coordinates` has to hold all coordinates x that will\
    \ be passed to `operator()` or `query`.\n        LiChaoSegmentTree(const std::vector<T>&\
    \ query_coordinates) : pos(query_coordinates) {\n            std::sort(pos.begin(),\
    \ pos.end());\n            pos.erase(std::unique(pos.begin(), pos.end()), pos.end());\n\
    \            n = pos.size();\n            m = ceil_pow2(n);\n            log_m\
    \ = floor_log2(m);\n            pos.resize(m, pos.size() ? pos.back() : T(0));\n\
    \            seg.resize(2 * m, Line::e);\n        }\n\n        // Add ax+b for\
    \ x in [min_x, max_x] (CLOSED range).\n        void add_segment(T min_x, T max_x,\
    \ T a, T b) {\n            Line f{ a, b };\n            if constexpr (not is_min_query)\
    \ f = -f;\n\n            int l = std::lower_bound(pos.begin(), pos.end(), min_x)\
    \ - pos.begin();\n            int r = std::upper_bound(pos.begin(), pos.end(),\
    \ max_x) - pos.begin();\n            if (r == n) r = m;\n            for (l +=\
    \ m, r += m; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) add_segment(l++,\
    \ f);\n                if (r & 1) add_segment(--r, f);\n            }\n      \
    \  }\n\n        // Add ax+b for x in (-infty, infty)\n        void add_line(T\
    \ a, T b) {\n            add_segment(std::numeric_limits<T>::min(), std::numeric_limits<T>::max(),\
    \ a, b);\n        }\n\n        /**\n         * Get min(/max) at x.\n         *\
    \ If no segment is added to x, then returns nullopt.\n         * It is required\
    \ that x is contained in the vector passed to constructor.\n         * If the\
    \ vector does not contain x, the assertion will fail.\n         */\n        std::optional<T>\
    \ operator()(T x) const {\n            int p = std::lower_bound(pos.begin(), pos.end(),\
    \ x) - pos.begin();\n            assert(pos[p] == x);\n            T res = std::numeric_limits<T>::max();\n\
    \            bool none = true;\n            for (p += m; p; p >>= 1) {\n     \
    \           none &= seg[p] == Line::e;\n                res = std::min(res, seg[p](x));\n\
    \            }\n            if (none) return std::nullopt;\n            if constexpr\
    \ (is_min_query) {\n                return std::make_optional(res);\n        \
    \    } else {\n                return std::make_optional(-res);\n            }\n\
    \        }\n\n        /**\n         * Get min(/max) at x.\n         * If no segment\
    \ is added to x, then returns nullopt.\n         * It is required that x is contained\
    \ in the vector passed to constructor.\n         * If the vector does not contain\
    \ x, the assertion will fail.\n         */\n        std::optional<T> query(T x)\
    \ const {\n            return (*this)(x);\n        }\n\n    private:\n       \
    \ std::vector<T> pos;\n        int n, m, log_m;\n        std::vector<Line> seg;\n\
    \n        static int ceil_pow2(int n) {\n            int k = 1;\n            while\
    \ (k < n) k <<= 1;\n            return k;\n        }\n        static int floor_log2(int\
    \ n) {\n            return 31 - __builtin_clz(n);\n        }\n\n        std::pair<int,\
    \ int> get_index_range(int k) {\n            int log_w = log_m - floor_log2(k),\
    \ w = 1 << log_w;\n            int l = (k << log_w) - m;\n            return {\
    \ l, l + w };\n        }\n\n        void add_segment(int k, Line f) {\n      \
    \      auto [l, r] = get_index_range(k);\n            for (int w = r - l; w;)\
    \ {\n                Line& g = seg[k];\n                const T xl = pos[l], xm\
    \ = pos[(l + r) >> 1], xr = pos[r - 1];\n                T fl = f(xl), fm = f(xm),\
    \ fr = f(xr);\n                T gl = g(xl), gm = g(xm), gr = g(xr);\n       \
    \         if (fm < gm) std::swap(f, g), std::swap(fl, gl), std::swap(fm, gm),\
    \ std::swap(fr, gr);\n                k <<= 1, w >>= 1;\n                if (fl\
    \ < gl) {\n                    k |= 0, r -= w;\n                } else if (fr\
    \ < gr) {\n                    k |= 1, l += w;\n                } else {\n   \
    \                 break;\n                }\n            }\n        }\n    };\n\
    } // namespace suisen\n\n\n\n#line 7 \"test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp\"\
    \n\nusing suisen::LiChaoSegmentTree;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> pos;\n    std::vector<std::pair<long long, long long>> init(n);\n    std::vector<std::tuple<int,\
    \ long long, long long>> queries(q);\n    for (int i = 0; i < n; ++i) {\n    \
    \    long long a, b;\n        std::cin >> a >> b;\n        init[i] = { a, b };\n\
    \    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >>\
    \ t;\n        long long a, b = 0;\n        if (t == 0) {\n            std::cin\
    \ >> a >> b;\n        } else {\n            std::cin >> a;\n        }\n      \
    \  queries[i] = { t, a, b };\n        if (t == 1) {\n            pos.push_back(a);\n\
    \        }\n    }\n    LiChaoSegmentTree<long long> seg(pos);\n    for (const\
    \ auto &[a, b] : init) {\n        seg.add_line(a, b);\n    }\n    for (const auto\
    \ &[t, a, b] : queries) {\n        if (t == 0) {\n            seg.add_line(a,\
    \ b);\n        } else {\n            std::cout << *(seg(a)) << '\\n';\n      \
    \  }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n\
    #include <iostream>\n#include <tuple>\n\n#include \"library/datastructure/segment_tree/li_chao_segment_tree.hpp\"\
    \n\nusing suisen::LiChaoSegmentTree;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> pos;\n    std::vector<std::pair<long long, long long>> init(n);\n    std::vector<std::tuple<int,\
    \ long long, long long>> queries(q);\n    for (int i = 0; i < n; ++i) {\n    \
    \    long long a, b;\n        std::cin >> a >> b;\n        init[i] = { a, b };\n\
    \    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >>\
    \ t;\n        long long a, b = 0;\n        if (t == 0) {\n            std::cin\
    \ >> a >> b;\n        } else {\n            std::cin >> a;\n        }\n      \
    \  queries[i] = { t, a, b };\n        if (t == 1) {\n            pos.push_back(a);\n\
    \        }\n    }\n    LiChaoSegmentTree<long long> seg(pos);\n    for (const\
    \ auto &[a, b] : init) {\n        seg.add_line(a, b);\n    }\n    for (const auto\
    \ &[t, a, b] : queries) {\n        if (t == 0) {\n            seg.add_line(a,\
    \ b);\n        } else {\n            std::cout << *(seg(a)) << '\\n';\n      \
    \  }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/li_chao_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
- /verify/test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp.html
title: test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
---
