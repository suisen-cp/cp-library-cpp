---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/math/fmt.hpp
    title: library/math/fmt.hpp
  - icon: ':warning:'
    path: library/math/fzt.hpp
    title: library/math/fzt.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/fmt.hpp\"\n#include <cassert>\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename T>\nvoid fmt_subset(const int n, std::vector<T>\
    \ &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1\
    \ << (n - 1); k >= 1; k >>= 1) {\n        for (int l = 0; l < (1 << n); l += 2\
    \ * k) {\n            int m = l + k;\n            for (int p = 0; p < k; ++p)\
    \ f[m + p] -= f[l + p];\n        }\n    }\n}\ntemplate <typename T>\nvoid fmt_supset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {\n        for (int l = 0; l\
    \ < (1 << n); l += 2 * k) {\n            int m = l + k;\n            for (int\
    \ p = 0; p < k; ++p) f[l + p] -= f[m + p];\n        }\n    }\n}\n} // namespace\
    \ suisen\n#line 3 \"library/math/fzt.hpp\"\n\nnamespace suisen {\ntemplate <typename\
    \ T>\nvoid fzt_subset(const int n, std::vector<T> &f) {\n    int sz = f.size();\n\
    \    assert(sz == 1 << n);\n    for (int k = 1; k < (1 << n); k <<= 1) {\n   \
    \     for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l + k;\n\
    \            for (int p = 0; p < k; ++p) f[m + p] += f[l + p];\n        }\n  \
    \  }\n}\ntemplate <typename T>\nvoid fzt_supset(const int n, std::vector<T> &f)\
    \ {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1; k\
    \ < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) f[l + p]\
    \ += f[m + p];\n        }\n    }\n}\n} // namespace suisen\n#line 3 \"test/math/fzt_fmt_test.cpp\"\
    \n\ntemplate <typename T>\nstd::vector<T> naive_fzt_subset(const int n, std::vector<T>\
    \ f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    std::vector<T>\
    \ g(sz, 0);\n    for (int s = 0; s < 1 << n; ++s) {\n        for (int t = s;;\
    \ t = (t - 1) & s) {\n            g[s] += f[t];\n            if (t == 0) break;\n\
    \        }\n    }\n    return g;\n}\n\ntemplate <typename T>\nstd::vector<T> naive_fzt_supset(const\
    \ int n, std::vector<T> f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    std::vector<T> g(sz, 0);\n    for (int s = 0; s < 1 << n; ++s) {\n      \
    \  for (int t = s;; t = (t - 1) & s) {\n            g[t] += f[s];\n          \
    \  if (t == 0) break;\n        }\n    }\n    return g;\n}\n\nint main() {\n  \
    \  []{\n        int log = 3;\n        std::vector<int> f = { 1, 1, 2, 3, 4, 5,\
    \ 6, 7 };\n        std::vector<int> fzt_subset_expected = naive_fzt_subset(log,\
    \ f);\n        fzt_subset(log, f);\n        assert(f == fzt_subset_expected);\n\
    \    }(), []{\n        int log = 3;\n        std::vector<int> f = { 1, 1, 2, 3,\
    \ 4, 5, 6, 7 };\n        std::vector<int> fzt_supset_expected = naive_fzt_supset(log,\
    \ f);\n        fzt_supset(log, f);\n        assert(f == fzt_supset_expected);\n\
    \    }();\n}\n"
  code: "#include \"../../library/math/fmt.hpp\"\n#include \"../../library/math/fzt.hpp\"\
    \n\ntemplate <typename T>\nstd::vector<T> naive_fzt_subset(const int n, std::vector<T>\
    \ f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    std::vector<T>\
    \ g(sz, 0);\n    for (int s = 0; s < 1 << n; ++s) {\n        for (int t = s;;\
    \ t = (t - 1) & s) {\n            g[s] += f[t];\n            if (t == 0) break;\n\
    \        }\n    }\n    return g;\n}\n\ntemplate <typename T>\nstd::vector<T> naive_fzt_supset(const\
    \ int n, std::vector<T> f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    std::vector<T> g(sz, 0);\n    for (int s = 0; s < 1 << n; ++s) {\n      \
    \  for (int t = s;; t = (t - 1) & s) {\n            g[t] += f[s];\n          \
    \  if (t == 0) break;\n        }\n    }\n    return g;\n}\n\nint main() {\n  \
    \  []{\n        int log = 3;\n        std::vector<int> f = { 1, 1, 2, 3, 4, 5,\
    \ 6, 7 };\n        std::vector<int> fzt_subset_expected = naive_fzt_subset(log,\
    \ f);\n        fzt_subset(log, f);\n        assert(f == fzt_subset_expected);\n\
    \    }(), []{\n        int log = 3;\n        std::vector<int> f = { 1, 1, 2, 3,\
    \ 4, 5, 6, 7 };\n        std::vector<int> fzt_supset_expected = naive_fzt_supset(log,\
    \ f);\n        fzt_supset(log, f);\n        assert(f == fzt_supset_expected);\n\
    \    }();\n}"
  dependsOn:
  - library/math/fmt.hpp
  - library/math/fzt.hpp
  isVerificationFile: false
  path: test/math/fzt_fmt_test.cpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/math/fzt_fmt_test.cpp
layout: document
redirect_from:
- /library/test/math/fzt_fmt_test.cpp
- /library/test/math/fzt_fmt_test.cpp.html
title: test/math/fzt_fmt_test.cpp
---
