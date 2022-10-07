---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/datastructure/heap/binary_heap.hpp
    title: O(n)
  - icon: ':warning:'
    path: library/datastructure/priority_queue.hpp
    title: library/datastructure/priority_queue.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/heap/heap_tag.hpp\"\n\n\n\n#include\
    \ <type_traits>\n\nnamespace suisen {\n    namespace internal::heap {\n      \
    \  struct heap_tag_base {};\n    }\n    struct min_heap_tag : internal::heap::heap_tag_base\
    \ {\n        static constexpr bool is_min_heap = true;\n        static constexpr\
    \ bool is_max_heap = false;\n    };\n    struct max_heap_tag : internal::heap::heap_tag_base\
    \ {\n        static constexpr bool is_min_heap = false;\n        static constexpr\
    \ bool is_max_heap = true;\n    };\n\n    template <typename T>\n    struct is_heap_tag\
    \ {\n        static constexpr bool value = std::is_base_of_v<internal::heap::heap_tag_base,\
    \ T>;\n    };\n    template <typename T>\n    constexpr bool is_heap_tag_v = is_heap_tag<T>::value;\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_HEAP_TAG\n#define SUISEN_HEAP_TAG\n\n#include <type_traits>\n\
    \nnamespace suisen {\n    namespace internal::heap {\n        struct heap_tag_base\
    \ {};\n    }\n    struct min_heap_tag : internal::heap::heap_tag_base {\n    \
    \    static constexpr bool is_min_heap = true;\n        static constexpr bool\
    \ is_max_heap = false;\n    };\n    struct max_heap_tag : internal::heap::heap_tag_base\
    \ {\n        static constexpr bool is_min_heap = false;\n        static constexpr\
    \ bool is_max_heap = true;\n    };\n\n    template <typename T>\n    struct is_heap_tag\
    \ {\n        static constexpr bool value = std::is_base_of_v<internal::heap::heap_tag_base,\
    \ T>;\n    };\n    template <typename T>\n    constexpr bool is_heap_tag_v = is_heap_tag<T>::value;\n\
    } // namespace suisen\n\n\n#endif // SUISEN_HEAP_TAG\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/heap/heap_tag.hpp
  requiredBy:
  - library/datastructure/priority_queue.hpp
  - library/datastructure/heap/binary_heap.hpp
  timestamp: '2022-09-29 21:45:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/heap/heap_tag.hpp
layout: document
redirect_from:
- /library/library/datastructure/heap/heap_tag.hpp
- /library/library/datastructure/heap/heap_tag.hpp.html
title: library/datastructure/heap/heap_tag.hpp
---
