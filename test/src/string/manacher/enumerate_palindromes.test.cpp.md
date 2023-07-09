---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/string/manacher.hpp
    title: Manacher
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"test/src/string/manacher/enumerate_palindromes.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\n\n\
    #include <iostream>\n#line 1 \"library/string/manacher.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    struct Manacher {\n        Manacher() = default;\n \
    \       template <typename Container>\n        Manacher(const Container& container,\
    \ const typename Container::value_type& dummy) : _n(container.size()), _r(2 *\
    \ _n + 1) {\n            std::vector v{ dummy };\n            for (const auto&\
    \ val : container) v.push_back(val), v.push_back(dummy);\n            build(v);\n\
    \        }\n\n        int operator[](int i) const { return _r[i]; }\n        int\
    \ odd_length(int i) const { return _r[2 * i + 1]; }\n        int even_length(int\
    \ i) const { return _r[2 * i]; }\n    private:\n        int _n;\n        std::vector<int>\
    \ _r;\n\n        template <typename T>\n        void build(const std::vector<T>&\
    \ v) {\n            for (int i = 0, j = 0, siz = v.size(); i < siz;) {\n     \
    \           while (i - j >= 0 and i + j < siz and v[i - j] == v[i + j]) ++j;\n\
    \                _r[i] = j;\n                int k = 1;\n                while\
    \ (i - k >= 0 and k + _r[i - k] < j) _r[i + k] = _r[i - k], ++k;\n           \
    \     i += k, j -= k;\n            }\n            for (int& r : _r) --r;\n   \
    \     }\n    };\n} // namespace suisen\n\n\n\n#line 5 \"test/src/string/manacher/enumerate_palindromes.test.cpp\"\
    \n\nint main() {\n    std::string s;\n    std::cin >> s;\n    suisen::Manacher\
    \ manacher(s, '$');\n    for (int i = 1; i < 2 * int(s.size()); ++i) std::cout\
    \ << manacher[i] << '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n\n#include <iostream>\n#include \"library/string/manacher.hpp\"\n\nint main()\
    \ {\n    std::string s;\n    std::cin >> s;\n    suisen::Manacher manacher(s,\
    \ '$');\n    for (int i = 1; i < 2 * int(s.size()); ++i) std::cout << manacher[i]\
    \ << '\\n';\n    return 0;\n}"
  dependsOn:
  - library/string/manacher.hpp
  isVerificationFile: true
  path: test/src/string/manacher/enumerate_palindromes.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/string/manacher/enumerate_palindromes.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/manacher/enumerate_palindromes.test.cpp
- /verify/test/src/string/manacher/enumerate_palindromes.test.cpp.html
title: test/src/string/manacher/enumerate_palindromes.test.cpp
---
