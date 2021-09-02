---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/commutative_dual_segment_tree.hpp
    title: library/datastructure/commutative_dual_segment_tree.hpp
  - icon: ':question:'
    path: library/datastructure/dual_segment_tree.hpp
    title: library/datastructure/dual_segment_tree.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/commutative_dual_segment_tree.hpp: line 6: unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/dual_segment_tree.hpp\"\
    \nusing suisen::DualSegmentTree;\n\nint main() {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    DualSegmentTree seg(n, 0, 0, std::plus<int>(), std::plus<int>());\n\
    \    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n \
    \       if (t == 0) {\n            int s, t, x;\n            std::cin >> s >>\
    \ t >> x;\n            seg.apply(--s, t, x);\n        } else {\n            int\
    \ i;\n            std::cin >> i;\n            std::cout << seg[--i] << '\\n';\n\
    \        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/dual_segment_tree.hpp
  - library/datastructure/commutative_dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
  requiredBy: []
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
- /verify/test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp.html
title: test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
---
