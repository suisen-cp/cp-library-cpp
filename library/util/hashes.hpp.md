---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/ZDD.hpp
    title: ZDD
  - icon: ':heavy_check_mark:'
    path: library/tree/tree_isomorphism_classification.hpp
    title: Tree Isomorphism Classification
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
    title: test/src/datastructure/ZDD/maximum_independent_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
    title: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/hashes.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cstdint>\n#include <tuple>\n#include <utility>\n\nnamespace std {\n    namespace\
    \ {\n        template <class T>\n        inline void hash_combine(std::size_t&\
    \ seed, T const& v) {\n            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed <<\
    \ 6) + (seed >> 2);\n        }\n\n        template <class Tuple, size_t Index\
    \ = std::tuple_size<Tuple>::value - 1>\n        struct HashValueImpl {\n     \
    \       static void apply(size_t& seed, Tuple const& t) {\n                HashValueImpl<Tuple,\
    \ Index - 1>::apply(seed, t);\n                hash_combine(seed, get<Index>(t));\n\
    \            }\n        };\n\n        template <class Tuple>\n        struct HashValueImpl<Tuple,\
    \ 0> {\n            static void apply(size_t& seed, Tuple const& t) {\n      \
    \          hash_combine(seed, get<0>(t));\n            }\n        };\n    }\n\n\
    \    template <typename T, typename U>\n    struct hash<std::pair<T, U>> {\n \
    \       size_t operator()(std::pair<T, U> const& tt) const {\n            size_t\
    \ seed = 0;\n            HashValueImpl<std::pair<T, U>>::apply(seed, tt);\n  \
    \          return seed;\n        }\n    };\n    template <typename ...Args>\n\
    \    struct hash<std::tuple<Args...>> {\n        size_t operator()(std::tuple<Args...>\
    \ const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed,\
    \ tt);\n            return seed;\n        }\n    };\n    template <typename T,\
    \ std::size_t N>\n    struct hash<std::array<T, N>> {\n        size_t operator()(std::array<T,\
    \ N> const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::array<T,\
    \ N>>::apply(seed, tt);\n            return seed;\n        }\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_TUPLE_HASH\n#define SUISEN_TUPLE_HASH\n\n#include <array>\n\
    #include <cstdint>\n#include <tuple>\n#include <utility>\n\nnamespace std {\n\
    \    namespace {\n        template <class T>\n        inline void hash_combine(std::size_t&\
    \ seed, T const& v) {\n            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed <<\
    \ 6) + (seed >> 2);\n        }\n\n        template <class Tuple, size_t Index\
    \ = std::tuple_size<Tuple>::value - 1>\n        struct HashValueImpl {\n     \
    \       static void apply(size_t& seed, Tuple const& t) {\n                HashValueImpl<Tuple,\
    \ Index - 1>::apply(seed, t);\n                hash_combine(seed, get<Index>(t));\n\
    \            }\n        };\n\n        template <class Tuple>\n        struct HashValueImpl<Tuple,\
    \ 0> {\n            static void apply(size_t& seed, Tuple const& t) {\n      \
    \          hash_combine(seed, get<0>(t));\n            }\n        };\n    }\n\n\
    \    template <typename T, typename U>\n    struct hash<std::pair<T, U>> {\n \
    \       size_t operator()(std::pair<T, U> const& tt) const {\n            size_t\
    \ seed = 0;\n            HashValueImpl<std::pair<T, U>>::apply(seed, tt);\n  \
    \          return seed;\n        }\n    };\n    template <typename ...Args>\n\
    \    struct hash<std::tuple<Args...>> {\n        size_t operator()(std::tuple<Args...>\
    \ const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::tuple<Args...>>::apply(seed,\
    \ tt);\n            return seed;\n        }\n    };\n    template <typename T,\
    \ std::size_t N>\n    struct hash<std::array<T, N>> {\n        size_t operator()(std::array<T,\
    \ N> const& tt) const {\n            size_t seed = 0;\n            HashValueImpl<std::array<T,\
    \ N>>::apply(seed, tt);\n            return seed;\n        }\n    };\n}\n\n#endif\
    \ // SUISEN_TUPLE_HASH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/hashes.hpp
  requiredBy:
  - library/tree/tree_isomorphism_classification.hpp
  - library/datastructure/ZDD.hpp
  timestamp: '2022-10-23 23:57:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  - test/src/datastructure/ZDD/maximum_independent_set.test.cpp
documentation_of: library/util/hashes.hpp
layout: document
title: Hashes
---
## Hashes

`std::pair`, `std::tuple`, `std::array` の hash を定義し、`std::unordered_map` の key として使えるようにする。
