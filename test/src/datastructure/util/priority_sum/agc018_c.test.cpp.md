---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/util/priority_sum.hpp
    title: Priority Sum
  - icon: ':heavy_check_mark:'
    path: library/util/permutation.hpp
    title: Permutation
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/agc018/tasks/agc018_c
    links:
    - https://atcoder.jp/contests/agc018/tasks/agc018_c
  bundledCode: "#line 1 \"test/src/datastructure/util/priority_sum/agc018_c.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/agc018/tasks/agc018_c\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#line 1 \"library/datastructure/util/priority_sum.hpp\"\
    \n\n\n\n#include <queue>\n#include <utility>\n\nnamespace suisen {\n    namespace\
    \ internal::priority_sum {\n        template <typename T, typename Comparator,\
    \ typename RevComparator>\n        struct PrioritySum {\n            using value_type\
    \ = T;\n            using comparator_type = Comparator;\n            using reverse_comparator_type\
    \ = RevComparator;\n\n            PrioritySum() : PrioritySum(0) {}\n        \
    \    PrioritySum(int k) : _k(k), _sum(0), _cmp(), _rev_cmp(), _head_k(_cmp), _del_head_k(_cmp),\
    \ _tail(_rev_cmp), _del_tail(_rev_cmp) {}\n\n            value_type get_sum()\
    \ const {\n                return _sum;\n            }\n\n            void insert(const\
    \ value_type &v) {\n                _sum += v;\n                _head_k.push(v);\n\
    \                fix();\n            }\n\n            void erase(const value_type\
    \ &v) {\n                if (_head_k.size() and v == _head_k.top()) {\n      \
    \              _sum -= v;\n                    _head_k.pop();\n              \
    \  } else if (_head_k.size() and _rev_cmp(v, _head_k.top())) {\n             \
    \       _sum -= v;\n                    _del_head_k.push(v);\n               \
    \ } else {\n                    _del_tail.push(v);\n                }\n      \
    \          fix();\n            }\n\n            int get_k() const { return _k;\
    \ }\n\n            void set_k(int new_k) { _k = new_k, fix(); }\n            void\
    \ incr_k() { set_k(get_k() + 1); }\n            void decr_k() { set_k(get_k()\
    \ - 1); }\n\n            int size() const {\n                return int((_head_k.size()\
    \ + _tail.size()) - (_del_head_k.size() + _del_tail.size()));\n            }\n\
    \n        private:\n            int _k;\n            value_type _sum;\n      \
    \      comparator_type _cmp;\n            reverse_comparator_type _rev_cmp;\n\
    \            std::priority_queue<value_type, std::vector<value_type>, comparator_type>\
    \ _head_k, _del_head_k;\n            std::priority_queue<value_type, std::vector<value_type>,\
    \ reverse_comparator_type> _tail, _del_tail;\n\n            void fix() {\n   \
    \             while (int(_head_k.size() - _del_head_k.size()) < _k and _tail.size())\
    \ {\n                    value_type v = std::move(_tail.top());\n            \
    \        _tail.pop();\n                    if (_del_tail.size() and _del_tail.top()\
    \ == v) {\n                        _del_tail.pop();\n                    } else\
    \ {\n                        _sum += v;\n                        _head_k.push(std::move(v));\n\
    \                    }\n                }\n                while (int(_head_k.size()\
    \ - _del_head_k.size()) > _k) {\n                    value_type v = std::move(_head_k.top());\n\
    \                    _head_k.pop();\n                    if (_del_head_k.size()\
    \ and _del_head_k.top() == v) {\n                        _del_head_k.pop();\n\
    \                    } else {\n                        _sum -= v;\n          \
    \              _tail.push(std::move(v));\n                    }\n            \
    \    }\n            }\n        };\n    } // internal::priority_sum\n\n    template\
    \ <typename T>\n    using MaximumPrioritySum = internal::priority_sum::PrioritySum<T,\
    \ std::less<T>, std::greater<T>>;\n    template <typename T>\n    using MinimumPrioritySum\
    \ = internal::priority_sum::PrioritySum<T, std::greater<T>, std::less<T>>;\n}\
    \ // namespace suisen\n\n\n\n#line 1 \"library/util/permutation.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <numeric>\n#line 8 \"library/util/permutation.hpp\"\
    \n\nnamespace suisen {\n    struct Permutation : public std::vector<int> {\n \
    \       using base_type = std::vector<int>;\n        using base_type::base_type;\n\
    \n        Permutation() : Permutation(0) {}\n        Permutation(std::size_t n)\
    \ : Permutation(int(n)) {}\n        Permutation(int n) : base_type(n) {\n    \
    \        std::iota(begin(), end(), 0);\n        }\n        Permutation(const std::vector<int>&\
    \ a) : std::vector<int>(a) {}\n        Permutation(std::vector<int>&& a) : std::vector<int>(std::move(a))\
    \ {}\n\n        // returns b s.t. b[i] = a[p[i]]\n        template <typename T>\n\
    \        std::vector<T> permute(const std::vector<T>& a) const {\n           \
    \ const int n = a.size();\n            std::vector<T> res(n);\n            for\
    \ (int i = 0; i < n; ++i) res[i] = a[(*this)[i]];\n            return res;\n \
    \       }\n        // returns b s.t. b[p[i]] = a[i]\n        template <typename\
    \ T>\n        std::vector<T> inv_permute(const std::vector<T>& a) const {\n  \
    \          const int n = a.size();\n            std::vector<T> res(n);\n     \
    \       for (int i = 0; i < n; ++i) res[(*this)[i]] = a[i];\n            return\
    \ res;\n        }\n\n        // returns p * q s.t. (p * q)[i] = p[q[i]]\n    \
    \    friend Permutation operator*(const Permutation& p, const Permutation& q)\
    \ {\n            return q.permute(p);\n        }\n        Permutation& operator*=(const\
    \ Permutation& q) {\n            return *this = *this * q;\n        }\n      \
    \  Permutation inv() const {\n            const int n = size();\n            Permutation\
    \ res(n);\n            for (int i = 0; i < n; ++i) res[(*this)[i]] = i;\n    \
    \        return res;\n        }\n        Permutation pow(long long k) const {\n\
    \            assert(k >= 0);\n            const int n = size();\n            std::vector<int8_t>\
    \ seen(n, false);\n            Permutation res(n);\n            for (int s = 0;\
    \ s < n; ++s) {\n                if (seen[s]) continue;\n                std::vector<int>\
    \ cycle { s };\n                for (int v = (*this)[s]; v != s; v = (*this)[v])\
    \ cycle.push_back(v);\n                const int l = cycle.size();\n         \
    \       for (int j = 0; j < l; ++j) {\n                    int v = cycle[j];\n\
    \                    seen[v] = true;\n                    res[v] = cycle[(j +\
    \ k) % l];\n                }\n            }\n            return res;\n      \
    \  }\n\n        template <typename T, typename Comp = std::less<T>>\n        static\
    \ Permutation index_sort(const std::vector<T>& a, Comp comp = Comp{}) {\n    \
    \        Permutation p(a.size());\n            std::sort(p.begin(), p.end(), [&](int\
    \ i, int j) { return comp(a[i], a[j]); });\n            return p;\n        }\n\
    \    };\n\n    template <typename hash_t>\n    struct PermutationHash {\n    \
    \    hash_t operator()(const Permutation &p) const {\n            return hash(p);\n\
    \        }\n        /**\n         * minimal perfect hash function for permutations.\n\
    \         * complexity: O(n) time, O(n) extra space\n         * reference: https://twitter.com/noshi91/status/1452081886025555972?s=20\n\
    \         */\n        static hash_t hash(const Permutation &per) {\n         \
    \   hash_t h = 0;\n            const int n = per.size();\n            Permutation\
    \ p = per;\n            Permutation q = per.inv();\n            for (int i = n\
    \ - 1; i >= 0; --i) {\n                h = h * (i + 1) + p[i];\n             \
    \   p[q[i]] = p[i];\n                q[p[i]] = q[i];\n            }\n        \
    \    return h;\n        }\n        static Permutation unhash(int n, hash_t h)\
    \ {\n            Permutation p = Permutation(n), q = p;\n            for (int\
    \ i = 0; i < n; ++i) {\n                p[i] = h % (i + 1), q[i] = q[p[i]];\n\
    \                q[p[i]] = p[q[i]] = i;\n                h /= i + 1;\n       \
    \     }\n            return p;\n        }\n    };\n} // namespace suisen\n\n\n\
    #line 8 \"test/src/datastructure/util/priority_sum/agc018_c.test.cpp\"\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int x, y, z;\n    std::cin >> x >> y >> z;\n\n    const int n = x + y +\
    \ z;\n    std::vector<long long> b(n), c(n), d(n);\n\n    long long sum_a = 0;\n\
    \    for (int i = 0; i < n; i++) {\n        long long a, x, y;\n        std::cin\
    \ >> a >> x >> y;\n        b[i] = a - x;\n        c[i] = a - y;\n        d[i]\
    \ = x - y;\n        sum_a += a;\n    }\n\n    auto p = suisen::Permutation::index_sort(b);\n\
    \    b = p.permute(b);\n    c = p.permute(c);\n    d = p.permute(d);\n\n    std::vector<long\
    \ long> sum_t(n);\n    suisen::MaximumPrioritySum<long long> topk_t;\n    for\
    \ (int i = n - 1; i >= y - 1; --i) {\n        if (i <= y + z - 1) {\n        \
    \    sum_t[i] = topk_t.get_sum();\n            topk_t.incr_k();\n        }\n \
    \       topk_t.insert(c[i]);\n    }\n    std::vector<long long> sum_h(n);\n  \
    \  suisen::MaximumPrioritySum<long long> topk_h;\n    long long sum_b = 0;\n \
    \   for (int i = 0; i <= y + z - 1; ++i) {\n        sum_b += b[i];\n        topk_h.insert(d[i]);\n\
    \        if (i >= y - 1) {\n            sum_h[i] = topk_h.get_sum() + sum_b;\n\
    \            topk_h.incr_k();\n        }\n    }\n    long long ans = 0;\n    for\
    \ (int i = y - 1; i < y + z; i++) {\n        ans = std::max(ans, sum_a - (sum_h[i]\
    \ + sum_t[i]));\n    }\n    std::cout << ans << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/agc018/tasks/agc018_c\"\n\n\
    #include <iostream>\n#include <vector>\n\n#include \"library/datastructure/util/priority_sum.hpp\"\
    \n#include \"library/util/permutation.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int x, y, z;\n    std::cin >> x >> y >> z;\n\
    \n    const int n = x + y + z;\n    std::vector<long long> b(n), c(n), d(n);\n\
    \n    long long sum_a = 0;\n    for (int i = 0; i < n; i++) {\n        long long\
    \ a, x, y;\n        std::cin >> a >> x >> y;\n        b[i] = a - x;\n        c[i]\
    \ = a - y;\n        d[i] = x - y;\n        sum_a += a;\n    }\n\n    auto p =\
    \ suisen::Permutation::index_sort(b);\n    b = p.permute(b);\n    c = p.permute(c);\n\
    \    d = p.permute(d);\n\n    std::vector<long long> sum_t(n);\n    suisen::MaximumPrioritySum<long\
    \ long> topk_t;\n    for (int i = n - 1; i >= y - 1; --i) {\n        if (i <=\
    \ y + z - 1) {\n            sum_t[i] = topk_t.get_sum();\n            topk_t.incr_k();\n\
    \        }\n        topk_t.insert(c[i]);\n    }\n    std::vector<long long> sum_h(n);\n\
    \    suisen::MaximumPrioritySum<long long> topk_h;\n    long long sum_b = 0;\n\
    \    for (int i = 0; i <= y + z - 1; ++i) {\n        sum_b += b[i];\n        topk_h.insert(d[i]);\n\
    \        if (i >= y - 1) {\n            sum_h[i] = topk_h.get_sum() + sum_b;\n\
    \            topk_h.incr_k();\n        }\n    }\n    long long ans = 0;\n    for\
    \ (int i = y - 1; i < y + z; i++) {\n        ans = std::max(ans, sum_a - (sum_h[i]\
    \ + sum_t[i]));\n    }\n    std::cout << ans << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/util/priority_sum.hpp
  - library/util/permutation.hpp
  isVerificationFile: true
  path: test/src/datastructure/util/priority_sum/agc018_c.test.cpp
  requiredBy: []
  timestamp: '2022-04-10 03:30:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/util/priority_sum/agc018_c.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/util/priority_sum/agc018_c.test.cpp
- /verify/test/src/datastructure/util/priority_sum/agc018_c.test.cpp.html
title: test/src/datastructure/util/priority_sum/agc018_c.test.cpp
---
