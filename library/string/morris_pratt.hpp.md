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
  bundledCode: "#line 1 \"library/string/morris_pratt.hpp\"\n\n\n\n#include <string>\n\
    #include <vector>\n\nnamespace suisen {\n    namespace morris_pratt {\n      \
    \  template <typename RandomAccessIterator>\n        std::vector<int> morris_pratt(RandomAccessIterator\
    \ start, RandomAccessIterator last) {\n            const int n = last - start;\n\
    \            std::vector<int> mp(n + 1);\n            mp[0] = -1;\n          \
    \  int j = -1;\n            for (int i = 0; i < n; ++i) {\n                while\
    \ (j >= 0 and *(start + i) != *(start + j)) j = mp[j];\n                mp[i +\
    \ 1] = ++j;\n            }\n            return mp;\n        }\n        template\
    \ <typename RandomAccessibleContainer>\n        auto morris_pratt(const RandomAccessibleContainer\
    \ &s) { return morris_pratt(s.begin(), s.end()); }\n\n        template <typename\
    \ RandomAccessIterator, typename OutputIterator>\n        void min_period(RandomAccessIterator\
    \ start, RandomAccessIterator last, OutputIterator result, bool accept_fragment\
    \ = true) {\n            auto mp = morris_pratt(start, last);\n            int\
    \ n = mp.size() - 1, p = n - mp[n];\n            int l = not accept_fragment and\
    \ n % p ? n : p;\n            while (l --> 0) *result++ = *start++;\n        }\n\
    \n        template <typename RandomAccessibleContainer>\n        struct MatcherMP\
    \ {\n            MatcherMP() {}\n            MatcherMP(const RandomAccessibleContainer\
    \ &s) : s(s), mp(morris_pratt(s)) {}\n            vector<int> operator()(const\
    \ RandomAccessibleContainer &t) {\n                const int n = s.size(), m =\
    \ t.size();\n                std::vector<int> res;\n                for (int i\
    \ = 0, j = 0; i < m; ++i) {\n                    while (j >= 0 and s[j] != t[i])\
    \ j = mp[j];\n                    if (++j == n) res.push_back(i - n + 1);\n  \
    \              }\n                return res;\n            }\n            vector<int>\
    \ enumerate_occurences(const RandomAccessibleContainer &t) {\n               \
    \ return (*this)(t);\n            }\n        private:\n            RandomAccessibleContainer\
    \ s;\n            std::vector<int> mp;\n        };\n    }\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_MORRIS_PRATT\n#define SUISEN_MORRIS_PRATT\n\n#include <string>\n\
    #include <vector>\n\nnamespace suisen {\n    namespace morris_pratt {\n      \
    \  template <typename RandomAccessIterator>\n        std::vector<int> morris_pratt(RandomAccessIterator\
    \ start, RandomAccessIterator last) {\n            const int n = last - start;\n\
    \            std::vector<int> mp(n + 1);\n            mp[0] = -1;\n          \
    \  int j = -1;\n            for (int i = 0; i < n; ++i) {\n                while\
    \ (j >= 0 and *(start + i) != *(start + j)) j = mp[j];\n                mp[i +\
    \ 1] = ++j;\n            }\n            return mp;\n        }\n        template\
    \ <typename RandomAccessibleContainer>\n        auto morris_pratt(const RandomAccessibleContainer\
    \ &s) { return morris_pratt(s.begin(), s.end()); }\n\n        template <typename\
    \ RandomAccessIterator, typename OutputIterator>\n        void min_period(RandomAccessIterator\
    \ start, RandomAccessIterator last, OutputIterator result, bool accept_fragment\
    \ = true) {\n            auto mp = morris_pratt(start, last);\n            int\
    \ n = mp.size() - 1, p = n - mp[n];\n            int l = not accept_fragment and\
    \ n % p ? n : p;\n            while (l --> 0) *result++ = *start++;\n        }\n\
    \n        template <typename RandomAccessibleContainer>\n        struct MatcherMP\
    \ {\n            MatcherMP() {}\n            MatcherMP(const RandomAccessibleContainer\
    \ &s) : s(s), mp(morris_pratt(s)) {}\n            vector<int> operator()(const\
    \ RandomAccessibleContainer &t) {\n                const int n = s.size(), m =\
    \ t.size();\n                std::vector<int> res;\n                for (int i\
    \ = 0, j = 0; i < m; ++i) {\n                    while (j >= 0 and s[j] != t[i])\
    \ j = mp[j];\n                    if (++j == n) res.push_back(i - n + 1);\n  \
    \              }\n                return res;\n            }\n            vector<int>\
    \ enumerate_occurences(const RandomAccessibleContainer &t) {\n               \
    \ return (*this)(t);\n            }\n        private:\n            RandomAccessibleContainer\
    \ s;\n            std::vector<int> mp;\n        };\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_MORRIS_PRATT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/morris_pratt.hpp
  requiredBy: []
  timestamp: '2022-01-15 00:28:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/string/morris_pratt.hpp
layout: document
redirect_from:
- /library/library/string/morris_pratt.hpp
- /library/library/string/morris_pratt.hpp.html
title: library/string/morris_pratt.hpp
---
