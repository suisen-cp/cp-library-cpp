---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u4F5C\u7528\u304C\u53EF\
      \u63DB\u306A\u5834\u5408)"
  - icon: ':x:'
    path: library/datastructure/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
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
    \ library/datastructure/segment_tree/commutative_dual_segment_tree.hpp: line 6:\
    \ unable to process #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \nusing suisen::DualSegmentTree;\n\nint mapping(int f, int x) { return f + x;\
    \ }\nint composition(int f, int g) { return f + g; }\nint id() { return 0; }\n\
    \nint main() {\n    int n, q;\n    std::cin >> n >> q;\n    DualSegmentTree<int,\
    \ int, mapping, composition, id> seg(n, 0);\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        std::cin >> t;\n        if (t == 0) {\n            int\
    \ s, t, x;\n            std::cin >> s >> t >> x;\n            seg.apply(--s, t,\
    \ x);\n        } else {\n            int i;\n            std::cin >> i;\n    \
    \        std::cout << seg[--i] << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/dual_segment_tree.hpp
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
  requiredBy: []
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp.html
title: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
---
