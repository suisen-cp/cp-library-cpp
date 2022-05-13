---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: library/math/multi_point_eval.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc212/tasks/abc212_h\"\n\n\
    #include <iostream>\n#include <atcoder/convolution>\n#include <atcoder/modint>\n\
    \n#include \"library/transform/walsh_hadamard.hpp\"\n#include \"library/convolution/polynomial_eval_multipoint_eval.hpp\"\
    \nusing namespace suisen;\n\nusing mint = atcoder::modint998244353;\n\nconstexpr\
    \ int M = 1 << 16;\n\nint main() {\n    FPS<mint>::set_multiplication([](const\
    \ auto& f, const auto& g) { return atcoder::convolution(f, g); });\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, k;\n    std::cin >> n >> k;\n\n    std::vector<mint>\
    \ c(M, 0);\n    for (int i = 0; i < k; ++i) {\n        int v;\n        std::cin\
    \ >> v;\n        ++c[v];\n    }\n\n    FPS<mint> f(n + 1, 1);\n    f[0] = 0;\n\
    \n    using namespace walsh_hadamard_transform;\n\n    auto res = polynomial_eval<mint,\
    \ walsh_hadamard<mint>, walsh_hadamard_inv<mint>>(c, f);\n\n    std::cout << std::accumulate(res.begin()\
    \ + 1, res.end(), mint(0)).val() << std::endl;\n\n    return 0;\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
- /verify/test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp.html
title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
---
