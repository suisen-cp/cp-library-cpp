---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/two_sat.hpp\"\n\n\n\n#include <atcoder/twosat>\n\
    \nnamespace suisen {\n    struct TwoSAT : public atcoder::two_sat {\n        using\
    \ base_type = atcoder::two_sat;\n        using base_type::base_type;\n\n     \
    \   void implies(int x, bool f, int y, bool g) {\n            base_type::add_clause(x,\
    \ not f, y, g);\n        }\n        void set(int x, bool f) {\n            base_type::add_clause(x,\
    \ f, x, f);\n        }\n        void at_most_one(int x, bool f, int y, bool g)\
    \ {\n            base_type::add_clause(x, not f, y, not g);\n        }\n     \
    \   void exactly_one(int x, bool f, int y, bool g) {\n            base_type::add_clause(x,\
    \ f, y, g);\n            base_type::add_clause(x, not f, y, not g);\n        }\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TWO_SAT\n#define SUISEN_TWO_SAT\n\n#include <atcoder/twosat>\n\
    \nnamespace suisen {\n    struct TwoSAT : public atcoder::two_sat {\n        using\
    \ base_type = atcoder::two_sat;\n        using base_type::base_type;\n\n     \
    \   void implies(int x, bool f, int y, bool g) {\n            base_type::add_clause(x,\
    \ not f, y, g);\n        }\n        void set(int x, bool f) {\n            base_type::add_clause(x,\
    \ f, x, f);\n        }\n        void at_most_one(int x, bool f, int y, bool g)\
    \ {\n            base_type::add_clause(x, not f, y, not g);\n        }\n     \
    \   void exactly_one(int x, bool f, int y, bool g) {\n            base_type::add_clause(x,\
    \ f, y, g);\n            base_type::add_clause(x, not f, y, not g);\n        }\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_TWO_SAT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/two_sat.hpp
  requiredBy: []
  timestamp: '2022-03-31 17:14:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/algorithm/two_sat.hpp
layout: document
title: Two Sat
---
## Two Sat

`atcoder::two_sat` のラッパー。便利関数を幾つか定義している。
