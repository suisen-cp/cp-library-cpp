---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/ZDD.hpp
    title: ZDD
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
    title: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/tuple_hash.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <tuple>\n\nnamespace std {\n    namespace {\n        template <class\
    \ T>\n        inline void hash_combine(std::size_t& seed, T const& v) {\n    \
    \        seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);\n    \
    \    }\n\n        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value\
    \ - 1>\n        struct HashValueImpl {\n            static void apply(size_t&\
    \ seed, Tuple const& t) {\n                HashValueImpl<Tuple, Index - 1>::apply(seed,\
    \ t);\n                hash_combine(seed, get<Index>(t));\n            }\n   \
    \     };\n\n        template <class Tuple>\n        struct HashValueImpl<Tuple,\
    \ 0> {\n            static void apply(size_t& seed, Tuple const& t) {\n      \
    \          hash_combine(seed, get<0>(t));\n            }\n        };\n    }\n\n\
    \    template <typename ...Args>\n    struct hash<std::tuple<Args...>> {\n   \
    \     size_t operator()(std::tuple<Args...> const& tt) const {\n            size_t\
    \ seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed, tt);\n\
    \            return seed;\n        }\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_TUPLE_HASH\n#define SUISEN_TUPLE_HASH\n\n#include <cstdint>\n\
    #include <tuple>\n\nnamespace std {\n    namespace {\n        template <class\
    \ T>\n        inline void hash_combine(std::size_t& seed, T const& v) {\n    \
    \        seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);\n    \
    \    }\n\n        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value\
    \ - 1>\n        struct HashValueImpl {\n            static void apply(size_t&\
    \ seed, Tuple const& t) {\n                HashValueImpl<Tuple, Index - 1>::apply(seed,\
    \ t);\n                hash_combine(seed, get<Index>(t));\n            }\n   \
    \     };\n\n        template <class Tuple>\n        struct HashValueImpl<Tuple,\
    \ 0> {\n            static void apply(size_t& seed, Tuple const& t) {\n      \
    \          hash_combine(seed, get<0>(t));\n            }\n        };\n    }\n\n\
    \    template <typename ...Args>\n    struct hash<std::tuple<Args...>> {\n   \
    \     size_t operator()(std::tuple<Args...> const& tt) const {\n            size_t\
    \ seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed, tt);\n\
    \            return seed;\n        }\n    };\n}\n\n#endif // SUISEN_TUPLE_HASH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/tuple_hash.hpp
  requiredBy:
  - library/datastructure/ZDD.hpp
  timestamp: '2022-01-15 00:25:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/ZDD/maximum_independent_set.test.cpp
documentation_of: library/util/tuple_hash.hpp
layout: document
title: Tuple Hash
---
## Tuple Hash