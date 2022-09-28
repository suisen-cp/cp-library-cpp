---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
    title: test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/li_chao_segment_tree/segment_add_get_min.test.cpp
    title: test/src/datastructure/segment_tree/li_chao_segment_tree/segment_add_get_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/li_chao_segment_tree.hpp\"\
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
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_LI_CHAO_SEGTREE\n#define SUISEN_LI_CHAO_SEGTREE\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T, bool is_min_query = true>\n    class\
    \ LiChaoSegmentTree {\n        struct Line {\n            static constexpr Line\
    \ e{ T(0), std::numeric_limits<T>::max() };\n            T a, b;\n           \
    \ bool operator==(const Line& other) const {\n                return a == other.a\
    \ and b == other.b;\n            }\n            T operator()(T x) const {\n  \
    \              return *this == e ? std::numeric_limits<T>::max() : a * x + b;\n\
    \            }\n            Line operator-() const { return Line{ -a, -b }; }\n\
    \        };\n\n    public:\n        LiChaoSegmentTree() : LiChaoSegmentTree(std::vector<T>{})\
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
    } // namespace suisen\n\n\n#endif // SUISEN_LI_CHAO_SEGTREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/segment_tree/li_chao_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/li_chao_segment_tree/line_add_get_min.test.cpp
  - test/src/datastructure/segment_tree/li_chao_segment_tree/segment_add_get_min.test.cpp
documentation_of: library/datastructure/segment_tree/li_chao_segment_tree.hpp
layout: document
title: Li Chao Segment Tree
---
## Li Chao Segment Tree