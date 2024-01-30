---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_table.hpp
    title: Sparse Table
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/abc141_e.test.cpp
    title: test/src/string/compare_substring/abc141_e.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/dummy.test.cpp
    title: test/src/string/compare_substring/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/string_search.test.cpp
    title: test/src/string/compare_substring/string_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/substring.test.cpp
    title: test/src/string/compare_substring/substring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/compare_substring.hpp\"\n\n\n\n#include <atcoder/segtree>\n\
    #include <atcoder/string>\n\n#line 1 \"library/datastructure/sparse_table.hpp\"\
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
    \ suisen\n\n\n#line 8 \"library/string/compare_substring.hpp\"\n\nnamespace suisen\
    \ {\n    namespace internal::compare_substring {\n        constexpr int op(int\
    \ x, int y) { return std::min(x, y); }\n        constexpr int e() { return std::numeric_limits<int>::max();\
    \ }\n    }\n    namespace compare_substring_rmq {\n        using SegmentTreeRmQ\
    \ = atcoder::segtree<int, internal::compare_substring::op, internal::compare_substring::e>;\n\
    \        using SparseTableRmQ = SparseTable<int, internal::compare_substring::op,\
    \ internal::compare_substring::e>;\n    }\n    template <typename RmQ = compare_substring_rmq::SparseTableRmQ>\n\
    \    struct CompareSubstring {\n        CompareSubstring() = default;\n      \
    \  CompareSubstring(const std::vector<int> &sa, const std::vector<int> &lcp) :\
    \ _n(sa.size()), _sa_inv(_n), _lcp_min(lcp) {\n            for (int i = 0; i <\
    \ _n; ++i) _sa_inv[sa[i]] = i;\n        }\n        template <typename T>\n   \
    \     CompareSubstring(const std::vector<T> &s) : CompareSubstring(s, atcoder::suffix_array(s),\
    \ DUMMY_PARAMETER) {}\n        template <typename T>\n        CompareSubstring(const\
    \ std::vector<T> &s, const T& upper) : CompareSubstring(s, atcoder::suffix_array(s,\
    \ upper), DUMMY_PARAMETER) {}\n        CompareSubstring(const std::string &s)\
    \ : CompareSubstring(s, atcoder::suffix_array(s), DUMMY_PARAMETER) {}\n\n    \
    \    int lcp(int l1, int r1, int l2, int r2) const {\n            assert(0 <=\
    \ l1 and l1 <= r1 and r1 <= _n);\n            assert(0 <= l2 and l2 <= r2 and\
    \ r2 <= _n);\n            if (l1 == r1 or l2 == r2) return 0;\n            auto\
    \ [i1, i2] = std::minmax(_sa_inv[l1], _sa_inv[l2]);\n            return std::min(std::min(r1\
    \ - l1, r2 - l2), _lcp_min(i1, i2));\n        }\n        int compare(int l1, int\
    \ r1, int l2, int r2) const {\n            const int len = lcp(l1, r1, l2, r2);\n\
    \            const int w1 = r1 - l1, w2 = r2 - l2;\n            return len ==\
    \ w1 and len == w2 ? 0 : len == w1 ? -1 : len == w2 ? 1 : _sa_inv[l1 + len] <\
    \ _sa_inv[l2 + len] ? -1 : 1;\n        }\n        int operator()(int l1, int r1,\
    \ int l2, int r2) const {\n            return compare(l1, r1, l2, r2);\n     \
    \   }\n\n        int lcp(const std::pair<int, int> &seg1, const std::pair<int,\
    \ int> &seg2) const {\n            return lcp(seg1.first, seg1.second, seg2.first,\
    \ seg2.second);\n        }\n        int compare(const std::pair<int, int> &seg1,\
    \ const std::pair<int, int> &seg2) const {\n            return compare(seg1.first,\
    \ seg1.second, seg2.first, seg2.second);\n        }\n        int operator()(const\
    \ std::pair<int, int> &seg1, const std::pair<int, int> &seg2) const {\n      \
    \      return compare(seg1, seg2);\n        }\n\n        struct Substring {\n\
    \            int l, r;\n            Substring() = default;\n            Substring(int\
    \ l, int r, CompareSubstring<RmQ> const * ptr) : l(l), r(r), _ptr(ptr) {}\n\n\
    \            int size() const { return r - l; }\n\n            int lcp(const Substring\
    \ &rhs) const {\n                return _ptr->lcp(l, r, rhs.l, rhs.r);\n     \
    \       }\n            int compare(const Substring &rhs) const {\n           \
    \     assert(rhs._ptr == _ptr);\n                return _ptr->compare(l, r, rhs.l,\
    \ rhs.r);\n            }\n            bool operator==(const Substring &rhs) const\
    \ { return compare(rhs) == 0; }\n            bool operator!=(const Substring &rhs)\
    \ const { return compare(rhs) != 0; }\n            bool operator< (const Substring\
    \ &rhs) const { return compare(rhs) <  0; }\n            bool operator<=(const\
    \ Substring &rhs) const { return compare(rhs) <= 0; }\n            bool operator>\
    \ (const Substring &rhs) const { return compare(rhs) >  0; }\n            bool\
    \ operator>=(const Substring &rhs) const { return compare(rhs) >= 0; }\n     \
    \   private:\n            CompareSubstring<RmQ> const * _ptr;\n        };\n\n\
    \        Substring substr(int l, int r) const { return Substring(l, r, this);\
    \ }\n        Substring substr(const std::pair<int, int> &seg) const { return substr(seg.first,\
    \ seg.second); }\n    private:\n        static constexpr bool DUMMY_PARAMETER{};\n\
    \        int _n;\n        std::vector<int> _sa_inv;\n        RmQ _lcp_min;\n\n\
    \        template <typename Container>\n        CompareSubstring(const Container\
    \ &s, const std::vector<int> &sa, bool) : CompareSubstring(sa, atcoder::lcp_array(s,\
    \ sa)) {}\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_COMPARE_SUBSTRING\n#define SUISEN_COMPARE_SUBSTRING\n\n#include\
    \ <atcoder/segtree>\n#include <atcoder/string>\n\n#include \"library/datastructure/sparse_table.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::compare_substring {\n        constexpr\
    \ int op(int x, int y) { return std::min(x, y); }\n        constexpr int e() {\
    \ return std::numeric_limits<int>::max(); }\n    }\n    namespace compare_substring_rmq\
    \ {\n        using SegmentTreeRmQ = atcoder::segtree<int, internal::compare_substring::op,\
    \ internal::compare_substring::e>;\n        using SparseTableRmQ = SparseTable<int,\
    \ internal::compare_substring::op, internal::compare_substring::e>;\n    }\n \
    \   template <typename RmQ = compare_substring_rmq::SparseTableRmQ>\n    struct\
    \ CompareSubstring {\n        CompareSubstring() = default;\n        CompareSubstring(const\
    \ std::vector<int> &sa, const std::vector<int> &lcp) : _n(sa.size()), _sa_inv(_n),\
    \ _lcp_min(lcp) {\n            for (int i = 0; i < _n; ++i) _sa_inv[sa[i]] = i;\n\
    \        }\n        template <typename T>\n        CompareSubstring(const std::vector<T>\
    \ &s) : CompareSubstring(s, atcoder::suffix_array(s), DUMMY_PARAMETER) {}\n  \
    \      template <typename T>\n        CompareSubstring(const std::vector<T> &s,\
    \ const T& upper) : CompareSubstring(s, atcoder::suffix_array(s, upper), DUMMY_PARAMETER)\
    \ {}\n        CompareSubstring(const std::string &s) : CompareSubstring(s, atcoder::suffix_array(s),\
    \ DUMMY_PARAMETER) {}\n\n        int lcp(int l1, int r1, int l2, int r2) const\
    \ {\n            assert(0 <= l1 and l1 <= r1 and r1 <= _n);\n            assert(0\
    \ <= l2 and l2 <= r2 and r2 <= _n);\n            if (l1 == r1 or l2 == r2) return\
    \ 0;\n            auto [i1, i2] = std::minmax(_sa_inv[l1], _sa_inv[l2]);\n   \
    \         return std::min(std::min(r1 - l1, r2 - l2), _lcp_min(i1, i2));\n   \
    \     }\n        int compare(int l1, int r1, int l2, int r2) const {\n       \
    \     const int len = lcp(l1, r1, l2, r2);\n            const int w1 = r1 - l1,\
    \ w2 = r2 - l2;\n            return len == w1 and len == w2 ? 0 : len == w1 ?\
    \ -1 : len == w2 ? 1 : _sa_inv[l1 + len] < _sa_inv[l2 + len] ? -1 : 1;\n     \
    \   }\n        int operator()(int l1, int r1, int l2, int r2) const {\n      \
    \      return compare(l1, r1, l2, r2);\n        }\n\n        int lcp(const std::pair<int,\
    \ int> &seg1, const std::pair<int, int> &seg2) const {\n            return lcp(seg1.first,\
    \ seg1.second, seg2.first, seg2.second);\n        }\n        int compare(const\
    \ std::pair<int, int> &seg1, const std::pair<int, int> &seg2) const {\n      \
    \      return compare(seg1.first, seg1.second, seg2.first, seg2.second);\n   \
    \     }\n        int operator()(const std::pair<int, int> &seg1, const std::pair<int,\
    \ int> &seg2) const {\n            return compare(seg1, seg2);\n        }\n\n\
    \        struct Substring {\n            int l, r;\n            Substring() =\
    \ default;\n            Substring(int l, int r, CompareSubstring<RmQ> const *\
    \ ptr) : l(l), r(r), _ptr(ptr) {}\n\n            int size() const { return r -\
    \ l; }\n\n            int lcp(const Substring &rhs) const {\n                return\
    \ _ptr->lcp(l, r, rhs.l, rhs.r);\n            }\n            int compare(const\
    \ Substring &rhs) const {\n                assert(rhs._ptr == _ptr);\n       \
    \         return _ptr->compare(l, r, rhs.l, rhs.r);\n            }\n         \
    \   bool operator==(const Substring &rhs) const { return compare(rhs) == 0; }\n\
    \            bool operator!=(const Substring &rhs) const { return compare(rhs)\
    \ != 0; }\n            bool operator< (const Substring &rhs) const { return compare(rhs)\
    \ <  0; }\n            bool operator<=(const Substring &rhs) const { return compare(rhs)\
    \ <= 0; }\n            bool operator> (const Substring &rhs) const { return compare(rhs)\
    \ >  0; }\n            bool operator>=(const Substring &rhs) const { return compare(rhs)\
    \ >= 0; }\n        private:\n            CompareSubstring<RmQ> const * _ptr;\n\
    \        };\n\n        Substring substr(int l, int r) const { return Substring(l,\
    \ r, this); }\n        Substring substr(const std::pair<int, int> &seg) const\
    \ { return substr(seg.first, seg.second); }\n    private:\n        static constexpr\
    \ bool DUMMY_PARAMETER{};\n        int _n;\n        std::vector<int> _sa_inv;\n\
    \        RmQ _lcp_min;\n\n        template <typename Container>\n        CompareSubstring(const\
    \ Container &s, const std::vector<int> &sa, bool) : CompareSubstring(sa, atcoder::lcp_array(s,\
    \ sa)) {}\n    };\n} // namespace suisen\n\n#endif // SUISEN_COMPARE_SUBSTRING\n"
  dependsOn:
  - library/datastructure/sparse_table.hpp
  isVerificationFile: false
  path: library/string/compare_substring.hpp
  requiredBy: []
  timestamp: '2022-05-29 02:48:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/compare_substring/substring.test.cpp
  - test/src/string/compare_substring/dummy.test.cpp
  - test/src/string/compare_substring/string_search.test.cpp
  - test/src/string/compare_substring/abc141_e.test.cpp
documentation_of: library/string/compare_substring.hpp
layout: document
title: Compare Substring
---
## Compare Substring