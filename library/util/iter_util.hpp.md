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
  bundledCode: "#line 1 \"library/util/iter_util.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename,\
    \ typename ...Ints>\n    class product_range {\n        static constexpr std::size_t\
    \ D = sizeof...(Ints);\n        struct iterator {\n            std::array<int,\
    \ D> ns, values;\n            bool done;\n\n            iterator(const std::array<int,\
    \ D>& ns) : ns(ns), values{}, done(*std::min_element(ns.begin(), ns.end()) <=\
    \ 0) {}\n\n            const std::array<int, D>& operator*() const { return values;\
    \ }\n            bool operator!=(std::nullptr_t) const { return not done; }\n\
    \            iterator& operator++() { return succ(), *this; }\n            template\
    \ <std::size_t I = D - 1>\n            void succ() {\n                if constexpr\
    \ (I == ~std::size_t(0)) {\n                    done = true;\n               \
    \ } else if (++values[I] == ns[I]) {\n                    values[I] = 0;\n   \
    \                 succ<I - 1>();\n                }\n            }\n        };\n\
    \        std::array<int, D> ns;\n    public:\n        product_range(const Ints\
    \ &...ns) : ns{ static_cast<int>(ns)... } {}\n        auto begin() const { return\
    \ iterator{ns}; }\n        auto end() const { return nullptr; }\n    };\n    template\
    \ <typename ...Ints>\n    product_range(const Ints &...) -> product_range<std::enable_if_t<std::conjunction_v<std::bool_constant<(sizeof...(Ints)\
    \ > 0)>, std::is_integral<Ints>...>>, Ints...>;\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ITER_UTILS\n#define SUISEN_ITER_UTILS\n\n#include <algorithm>\n\
    #include <array>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename,\
    \ typename ...Ints>\n    class product_range {\n        static constexpr std::size_t\
    \ D = sizeof...(Ints);\n        struct iterator {\n            std::array<int,\
    \ D> ns, values;\n            bool done;\n\n            iterator(const std::array<int,\
    \ D>& ns) : ns(ns), values{}, done(*std::min_element(ns.begin(), ns.end()) <=\
    \ 0) {}\n\n            const std::array<int, D>& operator*() const { return values;\
    \ }\n            bool operator!=(std::nullptr_t) const { return not done; }\n\
    \            iterator& operator++() { return succ(), *this; }\n            template\
    \ <std::size_t I = D - 1>\n            void succ() {\n                if constexpr\
    \ (I == ~std::size_t(0)) {\n                    done = true;\n               \
    \ } else if (++values[I] == ns[I]) {\n                    values[I] = 0;\n   \
    \                 succ<I - 1>();\n                }\n            }\n        };\n\
    \        std::array<int, D> ns;\n    public:\n        product_range(const Ints\
    \ &...ns) : ns{ static_cast<int>(ns)... } {}\n        auto begin() const { return\
    \ iterator{ns}; }\n        auto end() const { return nullptr; }\n    };\n    template\
    \ <typename ...Ints>\n    product_range(const Ints &...) -> product_range<std::enable_if_t<std::conjunction_v<std::bool_constant<(sizeof...(Ints)\
    \ > 0)>, std::is_integral<Ints>...>>, Ints...>;\n} // namespace suisen\n\n#endif\
    \ // SUISEN_ITER_UTILS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/iter_util.hpp
  requiredBy: []
  timestamp: '2023-09-06 20:34:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/iter_util.hpp
layout: document
title: Iter Util
---
## Iter Util