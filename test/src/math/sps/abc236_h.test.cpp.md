---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':heavy_check_mark:'
    path: library/math/sps.hpp
    title: Set Power Series
  - icon: ':question:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc236/tasks/abc236_Ex
    links:
    - https://atcoder.jp/contests/abc236/tasks/abc236_Ex
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/convolution/subset_convolution.hpp: line 5: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc236/tasks/abc236_Ex\"\n\n\
    #include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/math/sps.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    size_t n;\n    uint64_t m;\n    std::cin >>\
    \ n >> m;\n    std::vector<uint64_t> d(n);\n    for (auto &e : d) std::cin >>\
    \ e;\n\n    std::vector<mint> h(n + 1);\n    mint fac = 1;\n    for (std::size_t\
    \ i = 1; i <= n; ++i) {\n        h[i] = (i & 1) ? fac : -fac;\n        fac *=\
    \ i;\n    }\n\n    std::vector<uint64_t> lcm(1 << n, 1);\n \n    suisen::SPS<mint>\
    \ f(n);\n    for (std::size_t s = 1; s < 1U << n; ++s) {\n        std::size_t\
    \ i = __builtin_ctz(s);\n        std::size_t t = s ^ (1U << i);\n        uint64_t\
    \ x = d[i] / std::gcd(d[i], lcm[t]);\n        lcm[s] = x > m / lcm[t] ? m + 1\
    \ : x * lcm[t];\n        std::size_t pc = __builtin_popcount(s);\n        f[s]\
    \ = (m / lcm[s]) * h[pc];\n    }\n\n    std::cout << f.exp().back().val() << std::endl;\n\
    \    return 0;\n}"
  dependsOn:
  - library/math/sps.hpp
  - library/convolution/subset_convolution.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/math/sps/abc236_h.test.cpp
  requiredBy: []
  timestamp: '2022-06-27 18:52:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/sps/abc236_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/sps/abc236_h.test.cpp
- /verify/test/src/math/sps/abc236_h.test.cpp.html
title: test/src/math/sps/abc236_h.test.cpp
---
