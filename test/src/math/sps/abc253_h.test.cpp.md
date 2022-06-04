---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':x:'
    path: library/linear_algebra/count_spanning_trees.hpp
    title: "\u884C\u5217\u6728\u5B9A\u7406\u306B\u3088\u308B\u5168\u57DF\u6728\u306E\
      \u6570\u3048\u4E0A\u3052"
  - icon: ':question:'
    path: library/linear_algebra/matrix.hpp
    title: Matrix
  - icon: ':question:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':question:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':x:'
    path: library/math/sps.hpp
    title: Set Power Series
  - icon: ':question:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':question:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  - icon: ':question:'
    path: library/util/subset_iterator.hpp
    title: Subset Iterator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc253/tasks/abc253_Ex
    links:
    - https://atcoder.jp/contests/abc253/tasks/abc253_Ex
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/convolution/subset_convolution.hpp: line 5: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc253/tasks/abc253_Ex\"\n\n\
    #include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/util/subset_iterator.hpp\"\n#include \"library/linear_algebra/count_spanning_trees.hpp\"\
    \n#include \"library/math/factorial.hpp\"\n#include \"library/math/sps.hpp\"\n\
    \nint main() {\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n\n    for (auto& [u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n        --u, --v;\n    }\n\n    suisen::FPSNaive<mint>::set_max_deg(n);\n\
    \n    suisen::SPS<suisen::FPSNaive<mint>> f(n, suisen::FPSNaive<mint>(n));\n \
    \   for (int s = 1; s < 1 << n; ++s) {\n        std::vector<int> ids(n, -1);\n\
    \        int id = 0;\n        for (int i : suisen::all_setbit(s)) ids[i] = id++;\n\
    \        std::vector<std::pair<int, int>> Es;\n        for (const auto& [u, v]\
    \ : edges) if (ids[u] >= 0 and ids[v] >= 0) {\n            Es.emplace_back(ids[u],\
    \ ids[v]);\n        }\n        f[s] = { 0, suisen::count_spanning_trees<mint>(id,\
    \ Es) };\n    }\n\n    suisen::factorial<mint> fac(n);\n\n    auto g = f.exp().back();\n\
    \n    for (int k = 1; k < n; ++k) {\n        std::cout << (fac.fac(k) * g[n -\
    \ k] / mint(m).pow(k)).val() << std::endl;\n    }\n\n    return 0;\n}\n\n"
  dependsOn:
  - library/util/subset_iterator.hpp
  - library/linear_algebra/count_spanning_trees.hpp
  - library/linear_algebra/matrix.hpp
  - library/math/factorial.hpp
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
  path: test/src/math/sps/abc253_h.test.cpp
  requiredBy: []
  timestamp: '2022-06-04 18:33:47+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/math/sps/abc253_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/sps/abc253_h.test.cpp
- /verify/test/src/math/sps/abc253_h.test.cpp.html
title: test/src/math/sps/abc253_h.test.cpp
---
