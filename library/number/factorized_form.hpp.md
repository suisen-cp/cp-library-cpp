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
  bundledCode: "#line 1 \"library/number/factorized_form.hpp\"\n\n\n\n#include <type_traits>\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    struct\
    \ PrimePower {\n        T prime;\n        int exponent;\n        template <std::size_t\
    \ Index>\n        std::tuple_element_t<Index, PrimePower>& get() {\n         \
    \   static_assert(Index < 2);\n            if constexpr (Index == 0) return prime;\n\
    \            if constexpr (Index == 1) return exponent;\n        }\n        template\
    \ <std::size_t Index>\n        const std::tuple_element_t<Index, PrimePower>&\
    \ get() const {\n            static_assert(Index < 2);\n            if constexpr\
    \ (Index == 0) return prime;\n            if constexpr (Index == 1) return exponent;\n\
    \        }\n    };\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    using FactorizedForm = std::vector<PrimePower>;\n\
    } // namespace suisen\n\nnamespace std {\n    template <typename T>\n    struct\
    \ tuple_size<suisen::PrimePower<T>> : std::integral_constant<std::size_t, 2> {};\n\
    \    template <std::size_t Index, typename T>\n    struct tuple_element<Index,\
    \ suisen::PrimePower<T>> : std::tuple_element<Index, std::tuple<T, int>> {};\n\
    }\n\n\n"
  code: "#ifndef SUISEN_FACTORIZED_FORM\n#define SUISEN_FACTORIZED_FORM\n\n#include\
    \ <type_traits>\n#include <tuple>\n#include <vector>\n\nnamespace suisen {\n \
    \   template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    struct PrimePower {\n        T prime;\n        int exponent;\n\
    \        template <std::size_t Index>\n        std::tuple_element_t<Index, PrimePower>&\
    \ get() {\n            static_assert(Index < 2);\n            if constexpr (Index\
    \ == 0) return prime;\n            if constexpr (Index == 1) return exponent;\n\
    \        }\n        template <std::size_t Index>\n        const std::tuple_element_t<Index,\
    \ PrimePower>& get() const {\n            static_assert(Index < 2);\n        \
    \    if constexpr (Index == 0) return prime;\n            if constexpr (Index\
    \ == 1) return exponent;\n        }\n    };\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    using FactorizedForm = std::vector<PrimePower>;\n\
    } // namespace suisen\n\nnamespace std {\n    template <typename T>\n    struct\
    \ tuple_size<suisen::PrimePower<T>> : std::integral_constant<std::size_t, 2> {};\n\
    \    template <std::size_t Index, typename T>\n    struct tuple_element<Index,\
    \ suisen::PrimePower<T>> : std::tuple_element<Index, std::tuple<T, int>> {};\n\
    }\n\n#endif // SUISEN_FACTORIZED_FORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/factorized_form.hpp
  requiredBy: []
  timestamp: '2022-10-20 19:29:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/factorized_form.hpp
layout: document
redirect_from:
- /library/library/number/factorized_form.hpp
- /library/library/number/factorized_form.hpp.html
title: library/number/factorized_form.hpp
---
