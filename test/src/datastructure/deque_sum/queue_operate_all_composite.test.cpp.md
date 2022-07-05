---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/deque_sum.hpp
    title: "SWAG \u3092 Deque \u306B\u62E1\u5F35\u3057\u305F\u3084\u3064"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/datastructure/deque_sum.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct DequeSum {\n        using value_type\
    \ = T;\n\n        DequeSum() = default;\n\n        value_type sum() const {\n\
    \            return op(sum(_fi_sum), sum(_se_sum));\n        }\n        const\
    \ value_type& operator[](int i) const {\n            const int l = _fi_raw.size(),\
    \ r = _se_raw.size();\n            assert(0 <= i and i < l + r);\n           \
    \ return i < l ? _fi_raw[l - i - 1] : _se_raw[i - l];\n        }\n        void\
    \ push_back(const value_type &val) {\n            _se_raw.push_back(val);\n  \
    \          _se_sum.push_back(op(sum(_se_sum), val));\n        }\n        void\
    \ push_front(const value_type &val) {\n            _fi_raw.push_back(val);\n \
    \           _fi_sum.push_back(op(val, sum(_fi_sum)));\n        }\n        void\
    \ pop_back() {\n            if (_se_raw.size()) return _se_raw.pop_back(), _se_sum.pop_back();\n\
    \            const int siz = _fi_raw.size();\n            const int l = siz >>\
    \ 1, r = siz - l;\n            assert(r); // <=> siz > 0\n            for (int\
    \ i = r - 1; i > 0; --i) push_back(std::move(_fi_raw[i]));\n            _fi_raw.erase(_fi_raw.begin(),\
    \ _fi_raw.begin() + r);\n            _fi_sum.erase(_fi_sum.begin(), _fi_sum.begin()\
    \ + r);\n            if (l) _fi_sum[0] = _fi_raw[0];\n            for (int i =\
    \ 1; i < l; ++i) _fi_sum[i] = op(_fi_raw[i], _fi_sum[i - 1]);\n        }\n   \
    \     void pop_front() {\n            if (_fi_raw.size()) return _fi_raw.pop_back(),\
    \ _fi_sum.pop_back();\n            const int siz = _se_raw.size();\n         \
    \   const int r = siz >> 1, l = siz - r;\n            assert(l); // <=> siz >\
    \ 0\n            for (int i = l - 1; i > 0; --i) push_front(std::move(_se_raw[i]));\n\
    \            _se_raw.erase(_se_raw.begin(), _se_raw.begin() + l);\n          \
    \  _se_sum.erase(_se_sum.begin(), _se_sum.begin() + l);\n            if (r) _se_sum[0]\
    \ = _se_raw[0];\n            for (int i = 1; i < r; ++i) _se_sum[i] = op(_se_sum[i\
    \ - 1], _se_raw[i]);\n        }\n\n    private:\n        std::vector<value_type>\
    \ _fi_raw, _se_raw;\n        std::vector<value_type> _fi_sum, _se_sum;\n\n   \
    \     value_type sum(const std::vector<value_type> &st) const {\n            return\
    \ st.empty() ? e() : st.back();\n        }\n    };\n} // namespace suisen\n\n\n\
    \n#line 19 \"test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp\"\
    \n\nstd::pair<mint, mint> op(std::pair<mint, mint> g, std::pair<mint, mint> f)\
    \ {\n    return { f.first * g.first, f.first * g.second + f.second };\n}\nstd::pair<mint,\
    \ mint> e() {\n    return { 1, 0 };\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    suisen::DequeSum<std::pair<mint, mint>, op,\
    \ e> dq;\n\n    int q;\n    std::cin >> q;\n\n    while (q --> 0) {\n        int\
    \ query_type;\n        std::cin >> query_type;\n        if (query_type == 0) {\n\
    \            mint a, b;\n            std::cin >> a >> b;\n            dq.push_back({\
    \ a, b });\n        } else if (query_type == 1) {\n            dq.pop_front();\n\
    \        } else {\n            mint x;\n            std::cin >> x;\n         \
    \   auto [a, b] = dq.sum();\n            std::cout << a * x + b << '\\n';\n  \
    \      }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/datastructure/deque_sum.hpp\"\
    \n\nstd::pair<mint, mint> op(std::pair<mint, mint> g, std::pair<mint, mint> f)\
    \ {\n    return { f.first * g.first, f.first * g.second + f.second };\n}\nstd::pair<mint,\
    \ mint> e() {\n    return { 1, 0 };\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    suisen::DequeSum<std::pair<mint, mint>, op,\
    \ e> dq;\n\n    int q;\n    std::cin >> q;\n\n    while (q --> 0) {\n        int\
    \ query_type;\n        std::cin >> query_type;\n        if (query_type == 0) {\n\
    \            mint a, b;\n            std::cin >> a >> b;\n            dq.push_back({\
    \ a, b });\n        } else if (query_type == 1) {\n            dq.pop_front();\n\
    \        } else {\n            mint x;\n            std::cin >> x;\n         \
    \   auto [a, b] = dq.sum();\n            std::cout << a * x + b << '\\n';\n  \
    \      }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/deque_sum.hpp
  isVerificationFile: true
  path: test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2022-07-05 16:12:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
- /verify/test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp.html
title: test/src/datastructure/deque_sum/queue_operate_all_composite.test.cpp
---
