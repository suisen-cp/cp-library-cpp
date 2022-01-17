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
  bundledCode: "#line 1 \"library/util/variant_utils.hpp\"\n\n\n\n#include <cassert>\n\
    #include <variant>\n\nnamespace suisen {\n\ntemplate <typename ...Types>\nclass\
    \ Match {\n    public:\n        Match(std::variant<Types...> &&v) : v_(std::move(v))\
    \ {}\n        Match(const std::variant<Types...> &v) : v_(v) {}\n\n        template\
    \ <typename T, typename F>\n        Match&& with(F f) && {\n            if (std::holds_alternative<T>(v_))\
    \ {\n                assert(not matched);\n                matched = true;\n \
    \               f(std::get<T>(v_));\n            }\n            return std::move(*this);\n\
    \        }\n        template <typename F>\n        void otherwise(F f) && {\n\
    \            if (not matched) f();\n        }\n    private:\n        std::variant<Types...>\
    \ v_;\n        bool matched = false;\n};\n\ntemplate <typename ...Types>\nMatch(std::variant<Types...>)\
    \ -> Match<Types...>;\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_VARIANT_UTILS\n#define SUISEN_VARIANT_UTILS\n\n#include <cassert>\n\
    #include <variant>\n\nnamespace suisen {\n\ntemplate <typename ...Types>\nclass\
    \ Match {\n    public:\n        Match(std::variant<Types...> &&v) : v_(std::move(v))\
    \ {}\n        Match(const std::variant<Types...> &v) : v_(v) {}\n\n        template\
    \ <typename T, typename F>\n        Match&& with(F f) && {\n            if (std::holds_alternative<T>(v_))\
    \ {\n                assert(not matched);\n                matched = true;\n \
    \               f(std::get<T>(v_));\n            }\n            return std::move(*this);\n\
    \        }\n        template <typename F>\n        void otherwise(F f) && {\n\
    \            if (not matched) f();\n        }\n    private:\n        std::variant<Types...>\
    \ v_;\n        bool matched = false;\n};\n\ntemplate <typename ...Types>\nMatch(std::variant<Types...>)\
    \ -> Match<Types...>;\n\n} // namespace suisen\n\n\n#endif // SUISEN_VARIANT_UTILS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/variant_utils.hpp
  requiredBy: []
  timestamp: '2021-09-02 19:44:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/variant_utils.hpp
layout: document
title: Variant Utils
---
## Variant Utils