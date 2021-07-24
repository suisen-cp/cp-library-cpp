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
  bundledCode: "#line 1 \"library/util/run_length_encoder.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename Container>\nclass RunLengthEncoder {\n\
    \    public:\n        using content_type   = typename Container::value_type;\n\
    \        using value_type     = std::pair<content_type, long long>;\n        using\
    \ iterator       = typename std::vector<value_type>::iterator;\n        using\
    \ const_iterator = typename std::vector<value_type>::const_iterator;\n\n     \
    \   RunLengthEncoder() noexcept : _length(0), comp() {}\n        RunLengthEncoder(const\
    \ Container &c) noexcept {\n            compress(c, comp);\n            _length\
    \ = c.size();\n        }\n        long long length() const noexcept {\n      \
    \      return _length;\n        }\n        void swap(RunLengthEncoder<Container>\
    \  &other) { comp.swap(other.comp); }\n        void swap(RunLengthEncoder<Container>\
    \ &&other) { comp.swap(other.comp); }\n        void clear() { comp.clear(); }\n\
    \        auto begin()   const noexcept { return comp.begin();   }\n        auto\
    \ end()     const noexcept { return comp.end();     }\n        auto rbegin() \
    \ const noexcept { return comp.rbegin();  }\n        auto rend()    const noexcept\
    \ { return comp.rend();    }\n        auto cbegin()  const noexcept { return comp.cbegin();\
    \  }\n        auto cend()    const noexcept { return comp.cend();    }\n     \
    \   auto crbegin() const noexcept { return comp.crbegin(); }\n        auto crend()\
    \   const noexcept { return comp.crend();   }\n\n        const auto& front() const\
    \ { return comp.front(); }\n        const auto& back()  const { return comp.back();\
    \ }\n\n        void push_back(const content_type &val, const long long num = 1)\
    \ {\n            if (comp.size() and comp.back().first == val) {\n           \
    \     comp.back().second += num;\n            } else {\n                comp.emplace_back(val,\
    \ num);\n            }\n            _length += num;\n        }\n\n        long\
    \ long pop_back(const long long num = 1) {\n            long long rem = 0;\n \
    \           while (comp.size()) {\n                long long cnt = comp.back().second;\n\
    \                if (cnt > num) {\n                    comp.back.second -= num;\n\
    \                    return rem + num;\n                }\n                num\
    \ -= cnt, rem += cnt;\n                comp.pop_back();\n            }\n     \
    \       _length -= rem;\n            return rem;\n        }\n\n    private:\n\
    \        long long _length;\n        std::vector<value_type> comp;\n\n       \
    \ static void compress(const Container &c, std::vector<value_type> &res) {\n \
    \           res.clear();\n            for (auto it_l = c.begin(), it_r = c.begin();\
    \ it_l != c.end(); it_l = it_r) {\n                while (it_r != c.end() and\
    \ *it_l == *it_r) ++it_r;\n                res.emplace_back(*it_l, it_r - it_l);\n\
    \            }\n        }\n        static std::vector<value_type> compress(const\
    \ Container &c) {\n            std::vector<value_type> res;\n            compress(c,\
    \ res);\n            return res;\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_RUN_LENGTH_ENCODER\n#define SUISEN_RUN_LENGTH_ENCODER\n\n\
    #include <vector>\n\nnamespace suisen {\ntemplate <typename Container>\nclass\
    \ RunLengthEncoder {\n    public:\n        using content_type   = typename Container::value_type;\n\
    \        using value_type     = std::pair<content_type, long long>;\n        using\
    \ iterator       = typename std::vector<value_type>::iterator;\n        using\
    \ const_iterator = typename std::vector<value_type>::const_iterator;\n\n     \
    \   RunLengthEncoder() noexcept : _length(0), comp() {}\n        RunLengthEncoder(const\
    \ Container &c) noexcept {\n            compress(c, comp);\n            _length\
    \ = c.size();\n        }\n        long long length() const noexcept {\n      \
    \      return _length;\n        }\n        void swap(RunLengthEncoder<Container>\
    \  &other) { comp.swap(other.comp); }\n        void swap(RunLengthEncoder<Container>\
    \ &&other) { comp.swap(other.comp); }\n        void clear() { comp.clear(); }\n\
    \        auto begin()   const noexcept { return comp.begin();   }\n        auto\
    \ end()     const noexcept { return comp.end();     }\n        auto rbegin() \
    \ const noexcept { return comp.rbegin();  }\n        auto rend()    const noexcept\
    \ { return comp.rend();    }\n        auto cbegin()  const noexcept { return comp.cbegin();\
    \  }\n        auto cend()    const noexcept { return comp.cend();    }\n     \
    \   auto crbegin() const noexcept { return comp.crbegin(); }\n        auto crend()\
    \   const noexcept { return comp.crend();   }\n\n        const auto& front() const\
    \ { return comp.front(); }\n        const auto& back()  const { return comp.back();\
    \ }\n\n        void push_back(const content_type &val, const long long num = 1)\
    \ {\n            if (comp.size() and comp.back().first == val) {\n           \
    \     comp.back().second += num;\n            } else {\n                comp.emplace_back(val,\
    \ num);\n            }\n            _length += num;\n        }\n\n        long\
    \ long pop_back(const long long num = 1) {\n            long long rem = 0;\n \
    \           while (comp.size()) {\n                long long cnt = comp.back().second;\n\
    \                if (cnt > num) {\n                    comp.back.second -= num;\n\
    \                    return rem + num;\n                }\n                num\
    \ -= cnt, rem += cnt;\n                comp.pop_back();\n            }\n     \
    \       _length -= rem;\n            return rem;\n        }\n\n    private:\n\
    \        long long _length;\n        std::vector<value_type> comp;\n\n       \
    \ static void compress(const Container &c, std::vector<value_type> &res) {\n \
    \           res.clear();\n            for (auto it_l = c.begin(), it_r = c.begin();\
    \ it_l != c.end(); it_l = it_r) {\n                while (it_r != c.end() and\
    \ *it_l == *it_r) ++it_r;\n                res.emplace_back(*it_l, it_r - it_l);\n\
    \            }\n        }\n        static std::vector<value_type> compress(const\
    \ Container &c) {\n            std::vector<value_type> res;\n            compress(c,\
    \ res);\n            return res;\n        }\n};\n} // namespace suisen\n\n#endif\
    \ // SUISEN_RUN_LENGTH_ENCODER"
  dependsOn: []
  isVerificationFile: false
  path: library/util/run_length_encoder.hpp
  requiredBy: []
  timestamp: '2021-07-25 00:34:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/run_length_encoder.hpp
layout: document
redirect_from:
- /library/library/util/run_length_encoder.hpp
- /library/library/util/run_length_encoder.hpp.html
title: library/util/run_length_encoder.hpp
---
