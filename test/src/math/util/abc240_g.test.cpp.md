---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: library/math/util.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc240/tasks/abc240_g\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/math/util.hpp\"\n\nint main() {\n    int n, x, y, z;\n  \
    \  std::cin >> n >> x >> y >> z;\n\n    suisen::factorial<mint> fac(n);\n\n  \
    \  mint ans = 0;\n    for (int i = 0; i <= n; ++i) {\n        int j = i - z;\n\
    \        ans += fac.binom(n, i) * fac.binom(n - i, j) * suisen::random_walk_2d<mint>(n\
    \ - i - j, x, y);\n    }\n    std::cout << ans.val() << std::endl;\n\n    return\
    \ 0;\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/src/math/util/abc240_g.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/math/util/abc240_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/util/abc240_g.test.cpp
- /verify/test/src/math/util/abc240_g.test.cpp.html
title: test/src/math/util/abc240_g.test.cpp
---
