---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_table.hpp
    title: Sparse Table
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/rmq_pm1.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <cmath>\n#include <algorithm>\n\n#line 1 \"library/datastructure/sparse_table.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T,\
    \ T), T(*e)()>\n    struct SparseTable {\n        SparseTable() = default;\n \
    \       SparseTable(std::vector<T>&& a) : n(a.size()), log(floor_log2(n)), table(log\
    \ + 1), flog(n + 1, 0) {\n            build_table(std::move(a));\n           \
    \ build_flog_table();\n        }\n        SparseTable(const std::vector<T>& a)\
    \ : SparseTable(std::vector<T>(a)) {}\n        T operator()(int l, int r) const\
    \ {\n            if (l >= r) return e();\n            int i = flog[r - l];\n \
    \           return op(table[i][l], table[i][r - (1 << i)]);\n        }\n     \
    \   T prod(int l, int r) const {\n            return (*this)(l, r);\n        }\n\
    \    private:\n        int n;\n        int log;\n        std::vector<std::vector<T>>\
    \ table;\n        std::vector<int> flog;\n\n        void build_table(std::vector<T>&&\
    \ a) {\n            table[0] = std::move(a);\n            for (int i = 0; i <\
    \ log; ++i) {\n                int lmax = n - (1 << (i + 1));\n              \
    \  table[i + 1].resize(lmax + 1);\n                for (int l = 0; l <= lmax;\
    \ ++l) table[i + 1][l] = op(table[i][l], table[i][l + (1 << i)]);\n          \
    \  }\n        }\n        void build_flog_table() {\n            for (int l = 0;\
    \ l < log; ++l) {\n                std::fill(flog.begin() + (1 << l), flog.begin()\
    \ + (1 << (l + 1)), l);\n            }\n            std::fill(flog.begin() + (1\
    \ << log), flog.end(), log);\n        }\n        static int floor_log2(int i)\
    \ {\n            return 31 - __builtin_clz(i);\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#line 10 \"library/algorithm/rmq_pm1.hpp\"\n\nnamespace suisen {\n\
    \n    template <bool is_min_query = true>\n    class RMQpm1 {\n        static\
    \ constexpr typename std::conditional_t<is_min_query, std::less<int>, std::greater<int>>\
    \ comp{};\n        static constexpr int op(int x, int y) {\n            return\
    \ comp(x, y) ? x : y;\n        }\n        static constexpr int e() {\n       \
    \     if constexpr (is_min_query) {\n                return std::numeric_limits<int>::max();\n\
    \            } else {\n                return std::numeric_limits<int>::min();\n\
    \            }\n        }\n\n        static constexpr int LOG = 4;\n        static\
    \ constexpr int SIZE = 1 << LOG;\n\n        static constexpr class S {\n     \
    \   public:\n            int prd[1 << RMQpm1<is_min_query>::SIZE];\n         \
    \   constexpr S() : prd(), sum() {\n                prd[is_min_query] = sum[is_min_query]\
    \ = -1, prd[not is_min_query] = sum[not is_min_query] = 1;\n                for\
    \ (int n = 2; n <= RMQpm1<is_min_query>::SIZE; n <<= 1) {\n                  \
    \  for (int s = (1 << n) - 1; s >= 0; --s) merge(s, n >> 1);\n               \
    \ }\n            }\n        private:\n            int sum[1 << RMQpm1<is_min_query>::SIZE];\n\
    \            constexpr void merge(int s, int half) {\n                int upper\
    \ = s >> half, lower = s ^ (upper << half);\n                prd[s] = RMQpm1<is_min_query>::op(prd[lower],\
    \ sum[lower] + prd[upper]);\n                sum[s] = sum[lower] + sum[upper];\n\
    \            }\n        } tabs{};\n\n    public:\n        RMQpm1(std::vector<int>&&\
    \ x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build())\
    \ {}\n        RMQpm1(const std::vector<int>& x) : RMQpm1(std::vector<int>(x))\
    \ {}\n\n        int operator()(int l, int r) const {\n            if (l >= r)\
    \ return e();\n            static constexpr int MASK = SIZE - 1;\n           \
    \ auto f = [this](int l, int r) {\n                return l < r ? a[l] + tabs.prd[cut(b[l\
    \ >> LOG], l & MASK, ((r - 1) & MASK) + 1)] : e();\n            };\n         \
    \   if (l >> LOG == (r - 1) >> LOG) return f(l, r);\n            int spl = (l\
    \ + SIZE - 1) >> LOG, spr = r >> LOG;\n            return op(op(f(l, spl << LOG),\
    \ f(spr << LOG, r)), tabl(spl, spr));\n        }\n\n    private:\n        int\
    \ n, m;\n        std::vector<int> a;\n        std::vector<std::uint16_t> b;\n\
    \        SparseTable<int, op, e> tabl;\n\n        std::vector<int> build() {\n\
    \            std::vector<int> c(m, e());\n            for (int i = 0, p = a[0]\
    \ - 1; i < n; p = a[i++]) {\n                int outer = i >> LOG;\n         \
    \       c[outer] = op(c[outer], a[i]);\n                b[outer] |= comp(a[i],\
    \ p) << (i & (SIZE - 1));\n            }\n            a.insert(a.begin(), a[0]\
    \ - 1);\n            assert(std::adjacent_find(a.begin(), a.end(), [](int x, int\
    \ y) { return std::abs(x - y) != 1; }) == a.end());\n            return c;\n \
    \       }\n\n        static constexpr std::uint16_t cut(const std::uint16_t bits,\
    \ const int l, const int r) {\n            return std::uint16_t(bits << (SIZE\
    \ - r)) >> (SIZE - r + l);\n        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_RMQ_PM1\n#define SUISEN_RMQ_PM1\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <cmath>\n#include <algorithm>\n\n#include \"library/datastructure/sparse_table.hpp\"\
    \n\nnamespace suisen {\n\n    template <bool is_min_query = true>\n    class RMQpm1\
    \ {\n        static constexpr typename std::conditional_t<is_min_query, std::less<int>,\
    \ std::greater<int>> comp{};\n        static constexpr int op(int x, int y) {\n\
    \            return comp(x, y) ? x : y;\n        }\n        static constexpr int\
    \ e() {\n            if constexpr (is_min_query) {\n                return std::numeric_limits<int>::max();\n\
    \            } else {\n                return std::numeric_limits<int>::min();\n\
    \            }\n        }\n\n        static constexpr int LOG = 4;\n        static\
    \ constexpr int SIZE = 1 << LOG;\n\n        static constexpr class S {\n     \
    \   public:\n            int prd[1 << RMQpm1<is_min_query>::SIZE];\n         \
    \   constexpr S() : prd(), sum() {\n                prd[is_min_query] = sum[is_min_query]\
    \ = -1, prd[not is_min_query] = sum[not is_min_query] = 1;\n                for\
    \ (int n = 2; n <= RMQpm1<is_min_query>::SIZE; n <<= 1) {\n                  \
    \  for (int s = (1 << n) - 1; s >= 0; --s) merge(s, n >> 1);\n               \
    \ }\n            }\n        private:\n            int sum[1 << RMQpm1<is_min_query>::SIZE];\n\
    \            constexpr void merge(int s, int half) {\n                int upper\
    \ = s >> half, lower = s ^ (upper << half);\n                prd[s] = RMQpm1<is_min_query>::op(prd[lower],\
    \ sum[lower] + prd[upper]);\n                sum[s] = sum[lower] + sum[upper];\n\
    \            }\n        } tabs{};\n\n    public:\n        RMQpm1(std::vector<int>&&\
    \ x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build())\
    \ {}\n        RMQpm1(const std::vector<int>& x) : RMQpm1(std::vector<int>(x))\
    \ {}\n\n        int operator()(int l, int r) const {\n            if (l >= r)\
    \ return e();\n            static constexpr int MASK = SIZE - 1;\n           \
    \ auto f = [this](int l, int r) {\n                return l < r ? a[l] + tabs.prd[cut(b[l\
    \ >> LOG], l & MASK, ((r - 1) & MASK) + 1)] : e();\n            };\n         \
    \   if (l >> LOG == (r - 1) >> LOG) return f(l, r);\n            int spl = (l\
    \ + SIZE - 1) >> LOG, spr = r >> LOG;\n            return op(op(f(l, spl << LOG),\
    \ f(spr << LOG, r)), tabl(spl, spr));\n        }\n\n    private:\n        int\
    \ n, m;\n        std::vector<int> a;\n        std::vector<std::uint16_t> b;\n\
    \        SparseTable<int, op, e> tabl;\n\n        std::vector<int> build() {\n\
    \            std::vector<int> c(m, e());\n            for (int i = 0, p = a[0]\
    \ - 1; i < n; p = a[i++]) {\n                int outer = i >> LOG;\n         \
    \       c[outer] = op(c[outer], a[i]);\n                b[outer] |= comp(a[i],\
    \ p) << (i & (SIZE - 1));\n            }\n            a.insert(a.begin(), a[0]\
    \ - 1);\n            assert(std::adjacent_find(a.begin(), a.end(), [](int x, int\
    \ y) { return std::abs(x - y) != 1; }) == a.end());\n            return c;\n \
    \       }\n\n        static constexpr std::uint16_t cut(const std::uint16_t bits,\
    \ const int l, const int r) {\n            return std::uint16_t(bits << (SIZE\
    \ - r)) >> (SIZE - r + l);\n        }\n    };\n} // namespace suisen\n\n#endif\
    \ // SUISEN_RMQ_PM1\n"
  dependsOn:
  - library/datastructure/sparse_table.hpp
  isVerificationFile: false
  path: library/algorithm/rmq_pm1.hpp
  requiredBy: []
  timestamp: '2022-05-29 02:48:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/rmq_pm1.hpp
layout: document
title: "\u96A3\u63A5\u8981\u7D20\u306E\u5DEE\u304C $\\pm 1$ \u306E\u5834\u5408\u306E\
  \ RMQ"
---
## 隣接要素の差が $\pm 1$ の場合の RMQ
