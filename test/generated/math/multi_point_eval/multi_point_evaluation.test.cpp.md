---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: atcoder/modint:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multipoint_evaluation\"\
    \n\n#include <iostream>\n\n#include \"atcoder/modint\"\n#include \"atcoder/convolution\"\
    \n\n#include \"library/math/multi_point_eval.hpp\"\n\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    suisen::FPS<mint>::set_multiplication([](const auto &a, const\
    \ auto &b) { return atcoder::convolution(a, b); });\n    \n    int n, m;\n   \
    \ std::cin >> n >> m;\n    suisen::FPS<mint> f(n);\n    for (int i = 0; i < n;\
    \ ++i) {\n        int coef;\n        std::cin >> coef;\n        f[i] = coef;\n\
    \    }\n    std::vector<mint> xs(m);\n    for (int i = 0; i < m; ++i) {\n    \
    \    int x;\n        std::cin >> x;\n        xs[i] = x;\n    }\n    auto ys =\
    \ suisen::multi_point_eval(f, xs);\n    for (int i = 0; i < m; ++i) {\n      \
    \  std::cout << ys[i].val() << \" \\n\"[i == m - 1];\n    }\n    return 0;\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/generated/math/multi_point_eval/multi_point_evaluation.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/generated/math/multi_point_eval/multi_point_evaluation.test.cpp
layout: document
redirect_from:
- /verify/test/generated/math/multi_point_eval/multi_point_evaluation.test.cpp
- /verify/test/generated/math/multi_point_eval/multi_point_evaluation.test.cpp.html
title: test/generated/math/multi_point_eval/multi_point_evaluation.test.cpp
---
