---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: library/string/compare_substring.hpp
    title: Compare Substring
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/string/compare_substring/dummy.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#line 1 \"library/string/compare_substring.hpp\"\
    \n\n\n\n#include <atcoder/segtree>\n#include <atcoder/string>\n\n#line 1 \"library/datastructure/sparse_table.hpp\"\
    \n\n\n\n#include <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\
    \n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\n\
    template <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 7 \"library/datastructure/sparse_table.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct SparseTable {\n        SparseTable()\
    \ = default;\n        SparseTable(std::vector<T>&& a) : n(a.size()), log(floor_log2(n)),\
    \ table(log + 1), flog(n + 1, 0) {\n            build_table(std::move(a));\n \
    \           build_flog_table();\n        }\n        SparseTable(const std::vector<T>&\
    \ a) : SparseTable(std::vector<T>(a)) {}\n        T operator()(int l, int r) const\
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
    \ sa)) {}\n    };\n} // namespace suisen\n\n\n#line 7 \"test/src/string/compare_substring/dummy.test.cpp\"\
    \n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>&\
    \ v) {\n    const std::size_t n = v.size();\n    for (std::size_t i = 0; i < n;\
    \ ++i) {\n        out << v[i];\n        if (i + 1 != n) out << ' ';\n    }\n \
    \   return out;\n}\n\ntemplate <typename Container>\nauto subsegment(const Container&\
    \ container, int l, int r) {\n    Container res;\n    std::copy(std::next(std::begin(container),\
    \ l), std::next(std::begin(container), r), std::back_inserter(res));\n    return\
    \ res;\n}\n\ntemplate <typename Container>\nvoid test(const Container& s) {\n\
    \    std::cerr << \"  [\\033[32mINFO\\033[m] Test \\\"\" << s << \"\\\" ... \"\
    ;\n\n    auto naive_compare = [&s](int l1, int r1, int l2, int r2) {\n       \
    \ auto s1 = subsegment(s, l1, r1);\n        auto s2 = subsegment(s, l2, r2);\n\
    \        return s1 < s2 ? -1 : s1 > s2 ? 1 : 0;\n    };\n    suisen::CompareSubstring<suisen::compare_substring_rmq::SparseTableRmQ>\
    \ fast_compare(s);\n\n    const int n = std::size(s);\n    for (int l1 = 0; l1\
    \ <= n; ++l1) for (int r1 = l1; r1 <= n; ++r1) {\n        for (int l2 = 0; l2\
    \ <= n; ++l2) for (int r2 = l2; r2 <= n; ++r2) {\n            int res1 = naive_compare(l1,\
    \ r1, l2, r2);\n            int res2 = fast_compare(l1, r1, l2, r2);\n\n     \
    \       if (res1 != res2) {\n                auto to_symbol = [](int res) { return\
    \ res == 0 ? '=' : res > 0 ? '>' : '<'; };\n\n                std::cerr << \"\\\
    033[31mFailed.\\033[m\" << std::endl;\n                std::cerr << \"  compare\
    \ s[\" << l1 << \",\" << r1 << \") s[\" << l2 << \",\" << r2 << \"):\" << std::endl;\n\
    \                std::cerr << \"    s[\" << l1 << \",\" << r1 << \") = \\\"\"\
    \ << subsegment(s, l1, r1) << \"\\\"\" << std::endl;\n                std::cerr\
    \ << \"    s[\" << l2 << \",\" << r2 << \") = \\\"\" << subsegment(s, l2, r2)\
    \ << \"\\\"\" << std::endl;\n                std::cerr << \"    expected : \"\
    \ << to_symbol(res1) << std::endl;\n                std::cerr << \"    actual\
    \   : \" << to_symbol(res2) << std::endl;\n\n                std::cerr << \"[\\\
    033[31mERROR\\033[m] Test Failed.\" << std::endl;\n\n                assert(false);\n\
    \            }\n        }\n    }\n    std::cerr << \"\\033[32mOK.\\033[m\" <<\
    \ std::endl;\n}\n\nstd::string random_lowercase_alphabet(int len, int alphabet_size,\
    \ uint32_t seed = 0) {\n    std::mt19937 rng{ seed ? seed : std::random_device{}()\
    \ };\n    std::uniform_int_distribution<int> dist(0, alphabet_size - 1);\n   \
    \ std::string res(len, '?');\n    std::generate(std::begin(res), std::end(res),\
    \ [&] { return 'a' + dist(rng); });\n    return res;\n}\n\nstd::vector<uint32_t>\
    \ random_vector_of_uint32_t(int len, uint32_t max_value = std::numeric_limits<uint32_t>::max(),\
    \ uint32_t seed = 0) {\n    std::mt19937 rng{ seed ? seed : std::random_device{}()\
    \ };\n    std::uniform_int_distribution<uint32_t> dist(0, max_value);\n    std::vector<uint32_t>\
    \ res(len);\n    std::generate(std::begin(res), std::end(res), [&] { return dist(rng);\
    \ });\n    return res;\n}\n\nvoid run_tests() {\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] Handmade string...\" << std::endl;\n    test(std::string(\"abracadabra\"\
    ));\n    std::cerr << \"[\\033[32mINFO\\033[m] OK.\" << std::endl;\n\n    std::cerr\
    \ << \"[\\033[32mINFO\\033[m] Random string of lowercase alphabets...\" << std::endl;\n\
    \    test(random_lowercase_alphabet(10, 1));\n    test(random_lowercase_alphabet(30,\
    \ 2));\n    test(random_lowercase_alphabet(30, 26));\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] OK.\" << std::endl;\n\n    std::cerr << \"[\\033[32mINFO\\033[m] Random\
    \ vector of integers...\" << std::endl;\n    test(random_vector_of_uint32_t(10,\
    \ 0));\n    test(random_vector_of_uint32_t(30, 1));\n    test(random_vector_of_uint32_t(30,\
    \ 25));\n    test(random_vector_of_uint32_t(30));\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] OK.\" << std::endl;\n}\n\nint main() {\n    run_tests();\n\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <random>\n\n#include \"library/string/compare_substring.hpp\"\
    \n\ntemplate <typename T>\nstd::ostream& operator<<(std::ostream& out, const std::vector<T>&\
    \ v) {\n    const std::size_t n = v.size();\n    for (std::size_t i = 0; i < n;\
    \ ++i) {\n        out << v[i];\n        if (i + 1 != n) out << ' ';\n    }\n \
    \   return out;\n}\n\ntemplate <typename Container>\nauto subsegment(const Container&\
    \ container, int l, int r) {\n    Container res;\n    std::copy(std::next(std::begin(container),\
    \ l), std::next(std::begin(container), r), std::back_inserter(res));\n    return\
    \ res;\n}\n\ntemplate <typename Container>\nvoid test(const Container& s) {\n\
    \    std::cerr << \"  [\\033[32mINFO\\033[m] Test \\\"\" << s << \"\\\" ... \"\
    ;\n\n    auto naive_compare = [&s](int l1, int r1, int l2, int r2) {\n       \
    \ auto s1 = subsegment(s, l1, r1);\n        auto s2 = subsegment(s, l2, r2);\n\
    \        return s1 < s2 ? -1 : s1 > s2 ? 1 : 0;\n    };\n    suisen::CompareSubstring<suisen::compare_substring_rmq::SparseTableRmQ>\
    \ fast_compare(s);\n\n    const int n = std::size(s);\n    for (int l1 = 0; l1\
    \ <= n; ++l1) for (int r1 = l1; r1 <= n; ++r1) {\n        for (int l2 = 0; l2\
    \ <= n; ++l2) for (int r2 = l2; r2 <= n; ++r2) {\n            int res1 = naive_compare(l1,\
    \ r1, l2, r2);\n            int res2 = fast_compare(l1, r1, l2, r2);\n\n     \
    \       if (res1 != res2) {\n                auto to_symbol = [](int res) { return\
    \ res == 0 ? '=' : res > 0 ? '>' : '<'; };\n\n                std::cerr << \"\\\
    033[31mFailed.\\033[m\" << std::endl;\n                std::cerr << \"  compare\
    \ s[\" << l1 << \",\" << r1 << \") s[\" << l2 << \",\" << r2 << \"):\" << std::endl;\n\
    \                std::cerr << \"    s[\" << l1 << \",\" << r1 << \") = \\\"\"\
    \ << subsegment(s, l1, r1) << \"\\\"\" << std::endl;\n                std::cerr\
    \ << \"    s[\" << l2 << \",\" << r2 << \") = \\\"\" << subsegment(s, l2, r2)\
    \ << \"\\\"\" << std::endl;\n                std::cerr << \"    expected : \"\
    \ << to_symbol(res1) << std::endl;\n                std::cerr << \"    actual\
    \   : \" << to_symbol(res2) << std::endl;\n\n                std::cerr << \"[\\\
    033[31mERROR\\033[m] Test Failed.\" << std::endl;\n\n                assert(false);\n\
    \            }\n        }\n    }\n    std::cerr << \"\\033[32mOK.\\033[m\" <<\
    \ std::endl;\n}\n\nstd::string random_lowercase_alphabet(int len, int alphabet_size,\
    \ uint32_t seed = 0) {\n    std::mt19937 rng{ seed ? seed : std::random_device{}()\
    \ };\n    std::uniform_int_distribution<int> dist(0, alphabet_size - 1);\n   \
    \ std::string res(len, '?');\n    std::generate(std::begin(res), std::end(res),\
    \ [&] { return 'a' + dist(rng); });\n    return res;\n}\n\nstd::vector<uint32_t>\
    \ random_vector_of_uint32_t(int len, uint32_t max_value = std::numeric_limits<uint32_t>::max(),\
    \ uint32_t seed = 0) {\n    std::mt19937 rng{ seed ? seed : std::random_device{}()\
    \ };\n    std::uniform_int_distribution<uint32_t> dist(0, max_value);\n    std::vector<uint32_t>\
    \ res(len);\n    std::generate(std::begin(res), std::end(res), [&] { return dist(rng);\
    \ });\n    return res;\n}\n\nvoid run_tests() {\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] Handmade string...\" << std::endl;\n    test(std::string(\"abracadabra\"\
    ));\n    std::cerr << \"[\\033[32mINFO\\033[m] OK.\" << std::endl;\n\n    std::cerr\
    \ << \"[\\033[32mINFO\\033[m] Random string of lowercase alphabets...\" << std::endl;\n\
    \    test(random_lowercase_alphabet(10, 1));\n    test(random_lowercase_alphabet(30,\
    \ 2));\n    test(random_lowercase_alphabet(30, 26));\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] OK.\" << std::endl;\n\n    std::cerr << \"[\\033[32mINFO\\033[m] Random\
    \ vector of integers...\" << std::endl;\n    test(random_vector_of_uint32_t(10,\
    \ 0));\n    test(random_vector_of_uint32_t(30, 1));\n    test(random_vector_of_uint32_t(30,\
    \ 25));\n    test(random_vector_of_uint32_t(30));\n    std::cerr << \"[\\033[32mINFO\\\
    033[m] OK.\" << std::endl;\n}\n\nint main() {\n    run_tests();\n\n    std::cout\
    \ << \"Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/string/compare_substring.hpp
  - library/datastructure/sparse_table.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/string/compare_substring/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-05-28 01:38:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/string/compare_substring/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/compare_substring/dummy.test.cpp
- /verify/test/src/string/compare_substring/dummy.test.cpp.html
title: test/src/string/compare_substring/dummy.test.cpp
---
