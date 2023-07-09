---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/rolling_hash_field.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cstdint>\n#include <functional>\n#include <string>\n#include\
    \ <random>\n#include <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 12 \"library/string/rolling_hash_field.hpp\"\n\nnamespace suisen {\n\
    \    template <\n        typename T,\n        size_t base_num,\n        auto add\
    \ = default_operator::add<T>,\n        auto zero = default_operator::zero<T>,\n\
    \        auto neg = default_operator::neg<T>,\n        auto mul = default_operator::mul<T>,\n\
    \        auto one = default_operator::one<T>\n    >\n    struct RollingHashField\
    \ {\n        using hash_type = std::array<T, base_num>;\n\n        RollingHashField()\
    \ = default;\n\n        hash_type operator()(int l, int r) {\n            ensure_pows(r\
    \ - l);\n            hash_type res;\n            for (size_t base_id = 0; base_id\
    \ < base_num; ++base_id) {\n                res[base_id] = add(hash[base_id][r],\
    \ neg(mul(hash[base_id][l], pows[base_id][r - l])));\n            }\n        \
    \    return res;\n        }\n\n        static hash_type concat(hash_type h1, hash_type\
    \ h2, int length_h2) {\n            ensure_pows(length_h2);\n            hash_type\
    \ res;\n            for (int base_id = 0; base_id < base_num; ++base_id) {\n \
    \               res[base_id] = add(mul(h1[base_id], pows[base_id][length_h2]),\
    \ h2[base_id]);\n            }\n            return res;\n        }\n        static\
    \ hash_type pointwise_add(hash_type h1, hash_type h2) {\n            hash_type\
    \ h3;\n            for (size_t i = 0; i < base_num; ++i) h3[i] = add(h1[i], h2[i]);\n\
    \            return h3;\n        }\n\n        static void set_bases(const std::array<T,\
    \ base_num>& new_bases) {\n            bases = new_bases;\n            already_set_bases\
    \ = true;\n        }\n\n        template <typename Iterable>\n        static RollingHashField\
    \ create(const Iterable& s, const std::array<std::function<T(typename Iterable::value_type)>,\
    \ base_num> &hasher) {\n            std::vector<std::array<T, base_num>> a;\n\
    \            for (const auto& e : s) {\n                auto &h = a.emplace_back();\n\
    \                for (size_t i = 0; i < base_num; ++i) {\n                   \
    \ h[i] = hasher[i](e);\n                }\n            }\n            return RollingHashField(a);\n\
    \        }\n\n        int lcp(int pos1, int pos2) {\n            if (pos1 > pos2)\
    \ std::swap(pos1, pos2);\n            int l = 0, r = n - pos2 + 1;\n         \
    \   while (r - l > 1) {\n                int m = (l + r) >> 1;\n             \
    \   ((*this)(pos1, pos1 + m) == (*this)(pos2, pos2 + m) ? l : r) = m;\n      \
    \      }\n            return l;\n        }\n\n    private:\n        static inline\
    \ std::array<T, base_num> bases;\n        static inline std::array<std::vector<T>,\
    \ base_num> pows;\n        static inline bool already_set_bases = false;\n\n \
    \       int n;\n        std::array<std::vector<T>, base_num> hash;\n\n       \
    \ RollingHashField(const std::vector<std::array<T, base_num>>& a) : n(a.size())\
    \ {\n            assert(already_set_bases);\n            for (size_t base_id =\
    \ 0; base_id < base_num; ++base_id) {\n                hash[base_id].resize(n\
    \ + 1);\n                hash[base_id][0] = zero();\n                for (int\
    \ i = 0; i < n; ++i) hash[base_id][i + 1] = add(mul(hash[base_id][i], bases[base_id]),\
    \ a[i][base_id]);\n            }\n        }\n\n        static void ensure_pows(int\
    \ n) {\n            if (int(pows[0].size()) > n) return;\n            for (size_t\
    \ base_id = 0; base_id < base_num; ++base_id) {\n                const int old_size\
    \ = std::max(size_t(1), pows[base_id].size());\n                pows[base_id].resize(n\
    \ + 1);\n                pows[base_id][0] = one();\n                for (int i\
    \ = old_size; i <= n; ++i) pows[base_id][i] = mul(pows[base_id][i - 1], bases[base_id]);\n\
    \            }\n        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ROLLING_HASH_FIELD\n#define SUISEN_ROLLING_HASH_FIELD\n\n\
    #include <array>\n#include <cstdint>\n#include <functional>\n#include <string>\n\
    #include <random>\n#include <vector>\n\n#include \"library/util/default_operator.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T,\n        size_t base_num,\n\
    \        auto add = default_operator::add<T>,\n        auto zero = default_operator::zero<T>,\n\
    \        auto neg = default_operator::neg<T>,\n        auto mul = default_operator::mul<T>,\n\
    \        auto one = default_operator::one<T>\n    >\n    struct RollingHashField\
    \ {\n        using hash_type = std::array<T, base_num>;\n\n        RollingHashField()\
    \ = default;\n\n        hash_type operator()(int l, int r) {\n            ensure_pows(r\
    \ - l);\n            hash_type res;\n            for (size_t base_id = 0; base_id\
    \ < base_num; ++base_id) {\n                res[base_id] = add(hash[base_id][r],\
    \ neg(mul(hash[base_id][l], pows[base_id][r - l])));\n            }\n        \
    \    return res;\n        }\n\n        static hash_type concat(hash_type h1, hash_type\
    \ h2, int length_h2) {\n            ensure_pows(length_h2);\n            hash_type\
    \ res;\n            for (int base_id = 0; base_id < base_num; ++base_id) {\n \
    \               res[base_id] = add(mul(h1[base_id], pows[base_id][length_h2]),\
    \ h2[base_id]);\n            }\n            return res;\n        }\n        static\
    \ hash_type pointwise_add(hash_type h1, hash_type h2) {\n            hash_type\
    \ h3;\n            for (size_t i = 0; i < base_num; ++i) h3[i] = add(h1[i], h2[i]);\n\
    \            return h3;\n        }\n\n        static void set_bases(const std::array<T,\
    \ base_num>& new_bases) {\n            bases = new_bases;\n            already_set_bases\
    \ = true;\n        }\n\n        template <typename Iterable>\n        static RollingHashField\
    \ create(const Iterable& s, const std::array<std::function<T(typename Iterable::value_type)>,\
    \ base_num> &hasher) {\n            std::vector<std::array<T, base_num>> a;\n\
    \            for (const auto& e : s) {\n                auto &h = a.emplace_back();\n\
    \                for (size_t i = 0; i < base_num; ++i) {\n                   \
    \ h[i] = hasher[i](e);\n                }\n            }\n            return RollingHashField(a);\n\
    \        }\n\n        int lcp(int pos1, int pos2) {\n            if (pos1 > pos2)\
    \ std::swap(pos1, pos2);\n            int l = 0, r = n - pos2 + 1;\n         \
    \   while (r - l > 1) {\n                int m = (l + r) >> 1;\n             \
    \   ((*this)(pos1, pos1 + m) == (*this)(pos2, pos2 + m) ? l : r) = m;\n      \
    \      }\n            return l;\n        }\n\n    private:\n        static inline\
    \ std::array<T, base_num> bases;\n        static inline std::array<std::vector<T>,\
    \ base_num> pows;\n        static inline bool already_set_bases = false;\n\n \
    \       int n;\n        std::array<std::vector<T>, base_num> hash;\n\n       \
    \ RollingHashField(const std::vector<std::array<T, base_num>>& a) : n(a.size())\
    \ {\n            assert(already_set_bases);\n            for (size_t base_id =\
    \ 0; base_id < base_num; ++base_id) {\n                hash[base_id].resize(n\
    \ + 1);\n                hash[base_id][0] = zero();\n                for (int\
    \ i = 0; i < n; ++i) hash[base_id][i + 1] = add(mul(hash[base_id][i], bases[base_id]),\
    \ a[i][base_id]);\n            }\n        }\n\n        static void ensure_pows(int\
    \ n) {\n            if (int(pows[0].size()) > n) return;\n            for (size_t\
    \ base_id = 0; base_id < base_num; ++base_id) {\n                const int old_size\
    \ = std::max(size_t(1), pows[base_id].size());\n                pows[base_id].resize(n\
    \ + 1);\n                pows[base_id][0] = one();\n                for (int i\
    \ = old_size; i <= n; ++i) pows[base_id][i] = mul(pows[base_id][i - 1], bases[base_id]);\n\
    \            }\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_ROLLING_HASH_FIELD\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/string/rolling_hash_field.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/string/rolling_hash_field.hpp
layout: document
title: "Rolling Hash (\u4E00\u822C\u306E\u4F53)"
---
## Rolling Hash (一般の体)
