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
  bundledCode: "#line 1 \"library/util/container_utils.hpp\"\n#include <vector>\n\
    #include <optional>\n\nnamespace suisen {\ntemplate <typename T>\nvoid unique_erase(std::vector<T>\
    \ &v) {\n    v.erase(std::unique(v.begin(), v.end()), v.end());\n}\n\ntemplate\
    \ <typename T>\nint count_leq(const std::vector<T> &v, const T &&key) {\n    return\
    \ std::upper_bound(v.begin(), v.end(), key) - v.begin(); \n}\ntemplate <typename\
    \ T>\nint count_lt(const std::vector<T> &v, const T &&key) {\n    return std::lower_bound(v.begin(),\
    \ v.end(), key) - v.begin(); \n}\ntemplate <typename T>\nint count_geq(const std::vector<T>\
    \ &v, const T &&key) {\n    return v.size() - count_lt(v, key);\n}\ntemplate <typename\
    \ T>\nint count_gt(const std::vector<T> &v, const T &&key) {\n    return v.size()\
    \ - count_leq(v, key);\n}\n\ntemplate <typename _Container, typename _Key>\nauto\
    \ min_geq(const _Container &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    auto it = container.lower_bound(key);\n    return it == container.end()\
    \ ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto min_geq(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.lower_bound(key))) {\n    auto it = container.lower_bound(key);\n\
    \    return it == container.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto min_gt(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    auto it = container.upper_bound(key);\n    return it == container.end()\
    \ ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto min_gt(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.upper_bound(key))) {\n    auto it = container.upper_bound(key);\n\
    \    return it == container.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto max_leq(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    auto it = container.upper_bound(key);\n    return it == container.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto max_leq(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.upper_bound(key))) {\n    auto it = container.upper_bound(key);\n\
    \    return it == container.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto max_lt(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    auto it = container.lower_bound(key);\n    return it == container.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto max_lt(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.lower_bound(key))) {\n    auto it = container.lower_bound(key);\n\
    \    return it == container.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\n\ntemplate <typename T>\nstd::optional<T> min_geq(const std::vector<T> &v,\
    \ const T &&key) {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n\
    \    return it == v.end() ? std::nullopt : std::make_optional(*it);\n}\ntemplate\
    \ <typename T>\nstd::optional<T> min_geq(const std::vector<T> &v, const T &key)\
    \ {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n    return it ==\
    \ v.end() ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename T>\n\
    std::optional<T> min_gt(const std::vector<T> &v, const T &&key) {\n    auto it\
    \ = std::upper_bound(v.begin(), v.end(), key);\n    return it == v.end() ? std::nullopt\
    \ : std::make_optional(*it);\n}\ntemplate <typename T>\nstd::optional<T> min_gt(const\
    \ std::vector<T> &v, const T &key) {\n    auto it = std::upper_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_leq(const std::vector<T> &v, const\
    \ T &&key) {\n    auto it = std::upper_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> max_leq(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::upper_bound(v.begin(), v.end(), key);\n    return it == v.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename T>\nstd::optional<T>\
    \ max_lt(const std::vector<T> &v, const T &&key) {\n    auto it = std::lower_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_lt(const std::vector<T> &v, const\
    \ T &key) {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\n} // namespace\
    \ suisen\n"
  code: "#include <vector>\n#include <optional>\n\nnamespace suisen {\ntemplate <typename\
    \ T>\nvoid unique_erase(std::vector<T> &v) {\n    v.erase(std::unique(v.begin(),\
    \ v.end()), v.end());\n}\n\ntemplate <typename T>\nint count_leq(const std::vector<T>\
    \ &v, const T &&key) {\n    return std::upper_bound(v.begin(), v.end(), key) -\
    \ v.begin(); \n}\ntemplate <typename T>\nint count_lt(const std::vector<T> &v,\
    \ const T &&key) {\n    return std::lower_bound(v.begin(), v.end(), key) - v.begin();\
    \ \n}\ntemplate <typename T>\nint count_geq(const std::vector<T> &v, const T &&key)\
    \ {\n    return v.size() - count_lt(v, key);\n}\ntemplate <typename T>\nint count_gt(const\
    \ std::vector<T> &v, const T &&key) {\n    return v.size() - count_leq(v, key);\n\
    }\n\ntemplate <typename _Container, typename _Key>\nauto min_geq(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    auto it = container.lower_bound(key);\n    return it == container.end()\
    \ ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto min_geq(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.lower_bound(key))) {\n    auto it = container.lower_bound(key);\n\
    \    return it == container.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto min_gt(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    auto it = container.upper_bound(key);\n    return it == container.end()\
    \ ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto min_gt(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.upper_bound(key))) {\n    auto it = container.upper_bound(key);\n\
    \    return it == container.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto max_leq(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.upper_bound(key)))\
    \ {\n    auto it = container.upper_bound(key);\n    return it == container.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto max_leq(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.upper_bound(key))) {\n    auto it = container.upper_bound(key);\n\
    \    return it == container.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\ntemplate <typename _Container, typename _Key>\nauto max_lt(const _Container\
    \ &container, const _Key &&key) -> decltype(std::make_optional(*container.lower_bound(key)))\
    \ {\n    auto it = container.lower_bound(key);\n    return it == container.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename _Container,\
    \ typename _Key>\nauto max_lt(const _Container &container, const _Key &key) ->\
    \ decltype(std::make_optional(*container.lower_bound(key))) {\n    auto it = container.lower_bound(key);\n\
    \    return it == container.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\n\ntemplate <typename T>\nstd::optional<T> min_geq(const std::vector<T> &v,\
    \ const T &&key) {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n\
    \    return it == v.end() ? std::nullopt : std::make_optional(*it);\n}\ntemplate\
    \ <typename T>\nstd::optional<T> min_geq(const std::vector<T> &v, const T &key)\
    \ {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n    return it ==\
    \ v.end() ? std::nullopt : std::make_optional(*it);\n}\ntemplate <typename T>\n\
    std::optional<T> min_gt(const std::vector<T> &v, const T &&key) {\n    auto it\
    \ = std::upper_bound(v.begin(), v.end(), key);\n    return it == v.end() ? std::nullopt\
    \ : std::make_optional(*it);\n}\ntemplate <typename T>\nstd::optional<T> min_gt(const\
    \ std::vector<T> &v, const T &key) {\n    auto it = std::upper_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.end() ? std::nullopt : std::make_optional(*it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_leq(const std::vector<T> &v, const\
    \ T &&key) {\n    auto it = std::upper_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename\
    \ T>\nstd::optional<T> max_leq(const std::vector<T> &v, const T &key) {\n    auto\
    \ it = std::upper_bound(v.begin(), v.end(), key);\n    return it == v.begin()\
    \ ? std::nullopt : std::make_optional(*--it);\n}\ntemplate <typename T>\nstd::optional<T>\
    \ max_lt(const std::vector<T> &v, const T &&key) {\n    auto it = std::lower_bound(v.begin(),\
    \ v.end(), key);\n    return it == v.begin() ? std::nullopt : std::make_optional(*--it);\n\
    }\ntemplate <typename T>\nstd::optional<T> max_lt(const std::vector<T> &v, const\
    \ T &key) {\n    auto it = std::lower_bound(v.begin(), v.end(), key);\n    return\
    \ it == v.begin() ? std::nullopt : std::make_optional(*--it);\n}\n} // namespace\
    \ suisen\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/container_utils.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/container_utils.hpp
layout: document
redirect_from:
- /library/library/util/container_utils.hpp
- /library/library/util/container_utils.hpp.html
title: library/util/container_utils.hpp
---
