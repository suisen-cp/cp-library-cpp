---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/polynomial/compose_exp.hpp
    title: Compose Exp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/polynomial/compose_exp/arc154_f.test.cpp
    title: test/src/polynomial/compose_exp/arc154_f.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/rational_fps.hpp\"\n\n\n\n#include <queue>\n\
    #include <utility>\n\nnamespace suisen {\n    template <typename FPSType>\n  \
    \  struct RationalFPS {\n        using mint = typename FPSType::value_type;\n\
    \        \n        FPSType num, den;\n        RationalFPS(const mint &v) : RationalFPS(FPSType{\
    \ v }) {}\n        RationalFPS(const FPSType& num = { 0 }, const FPSType& den\
    \ = { 1 }) : num(num), den(den) {}\n        RationalFPS(const std::pair<FPSType,\
    \ FPSType>& p) : num(p.first), den(p.second) {}\n\n        FPSType to_fps(int\
    \ n) const {\n            int dlz = 0;\n            while (dlz < den.size() and\
    \ den[dlz] == 0) ++dlz;\n            int nlz = 0;\n            while (nlz < num.size()\
    \ and num[nlz] == 0) ++nlz;\n            assert(dlz != den.size());\n        \
    \    if (nlz == num.size()) {\n                return FPSType(n, mint(0));\n \
    \           }\n            assert(dlz <= nlz);\n            return ((num >> dlz)\
    \ * (den >> dlz).inv(n)).cut(n);\n        }\n\n        RationalFPS<FPSType> operator+()\
    \ const { return *this; }\n        RationalFPS<FPSType> operator-() const { return\
    \ { -num, den }; }\n\n        friend RationalFPS<FPSType> operator+(const RationalFPS&\
    \ lhs, const RationalFPS& rhs) {\n            return { lhs.num * rhs.den + lhs.den\
    \ * rhs.num, lhs.den * rhs.den };\n        }\n        friend RationalFPS<FPSType>\
    \ operator-(const RationalFPS& lhs, const RationalFPS& rhs) {\n            return\
    \ { lhs.num * rhs.den - lhs.den * rhs.num, lhs.den * rhs.den };\n        }\n \
    \       friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const RationalFPS&\
    \ rhs) {\n            return { lhs.num * rhs.num, lhs.den * rhs.den };\n     \
    \   }\n        friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const\
    \ mint& val) {\n            return { lhs.num * val, lhs.den };\n        }\n  \
    \      friend RationalFPS<FPSType> operator/(const RationalFPS& lhs, const mint&\
    \ val) {\n            return { lhs.num, lhs.den * val };\n        }\n        friend\
    \ RationalFPS<FPSType> operator*(const mint& val, const RationalFPS& lhs) {\n\
    \            return { lhs.num * val, lhs.den };\n        }\n        friend RationalFPS<FPSType>\
    \ operator/(const mint& val, const RationalFPS& lhs) {\n            return { lhs.den\
    \ * val, lhs.num };\n        }\n\n        RationalFPS<FPSType>& operator+=(const\
    \ RationalFPS& rhs) { return *this = *this + rhs; }\n        RationalFPS<FPSType>&\
    \ operator-=(const RationalFPS& rhs) { return *this = *this - rhs; }\n       \
    \ RationalFPS<FPSType>& operator*=(const RationalFPS& rhs) { return *this = *this\
    \ * rhs; }\n        RationalFPS<FPSType>& operator*=(const mint& val) { return\
    \ num *= val, *this; }\n        RationalFPS<FPSType>& operator/=(const mint& val)\
    \ { return den *= val, *this; }\n\n        RationalFPS<FPSType> inv() const {\
    \ return { den, num }; }\n        RationalFPS<FPSType>& inv_inplace() { return\
    \ std::swap(num, den), * this; }\n\n        void cut(int n) {\n            if\
    \ (int(num.size()) > n) num.resize(n);\n            if (int(den.size()) > n) den.resize(n);\n\
    \        }\n\n        FPSType normalize() {\n            auto [q, r] = num.div_mod(den);\n\
    \            num = std::move(r);\n            return q;\n        }\n\n       \
    \ static RationalFPS<FPSType> sum(const std::vector<RationalFPS<FPSType>>& fs)\
    \ {\n            auto comp = [](const RationalFPS<FPSType>& f, const RationalFPS<FPSType>&\
    \ g) {\n                return f.den.size() > g.den.size();\n            };\n\
    \            std::priority_queue<RationalFPS<FPSType>, std::vector<RationalFPS<FPSType>>,\
    \ decltype(comp)> pq{ comp };\n            for (const auto& f : fs) pq.push(f);\n\
    \n            while (pq.size() > 1) {\n                auto f = pq.top();\n  \
    \              pq.pop();\n                auto g = pq.top();\n               \
    \ pq.pop();\n                pq.emplace(f + g);\n            }\n            return\
    \ pq.top();\n        }\n        static RationalFPS<FPSType> prod(const std::vector<RationalFPS<FPSType>>&\
    \ fs) {\n            std::vector<FPSType> nums, dens;\n            for (const\
    \ auto &f : fs) nums.push_back(f.num), dens.push_back(f.den);\n            return\
    \ { FPSType::prod(nums), FPSType::prod(dens) };\n        }\n    };\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_RATIONAL_FPS\n#define SUISEN_RATIONAL_FPS\n\n#include <queue>\n\
    #include <utility>\n\nnamespace suisen {\n    template <typename FPSType>\n  \
    \  struct RationalFPS {\n        using mint = typename FPSType::value_type;\n\
    \        \n        FPSType num, den;\n        RationalFPS(const mint &v) : RationalFPS(FPSType{\
    \ v }) {}\n        RationalFPS(const FPSType& num = { 0 }, const FPSType& den\
    \ = { 1 }) : num(num), den(den) {}\n        RationalFPS(const std::pair<FPSType,\
    \ FPSType>& p) : num(p.first), den(p.second) {}\n\n        FPSType to_fps(int\
    \ n) const {\n            int dlz = 0;\n            while (dlz < den.size() and\
    \ den[dlz] == 0) ++dlz;\n            int nlz = 0;\n            while (nlz < num.size()\
    \ and num[nlz] == 0) ++nlz;\n            assert(dlz != den.size());\n        \
    \    if (nlz == num.size()) {\n                return FPSType(n, mint(0));\n \
    \           }\n            assert(dlz <= nlz);\n            return ((num >> dlz)\
    \ * (den >> dlz).inv(n)).cut(n);\n        }\n\n        RationalFPS<FPSType> operator+()\
    \ const { return *this; }\n        RationalFPS<FPSType> operator-() const { return\
    \ { -num, den }; }\n\n        friend RationalFPS<FPSType> operator+(const RationalFPS&\
    \ lhs, const RationalFPS& rhs) {\n            return { lhs.num * rhs.den + lhs.den\
    \ * rhs.num, lhs.den * rhs.den };\n        }\n        friend RationalFPS<FPSType>\
    \ operator-(const RationalFPS& lhs, const RationalFPS& rhs) {\n            return\
    \ { lhs.num * rhs.den - lhs.den * rhs.num, lhs.den * rhs.den };\n        }\n \
    \       friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const RationalFPS&\
    \ rhs) {\n            return { lhs.num * rhs.num, lhs.den * rhs.den };\n     \
    \   }\n        friend RationalFPS<FPSType> operator*(const RationalFPS& lhs, const\
    \ mint& val) {\n            return { lhs.num * val, lhs.den };\n        }\n  \
    \      friend RationalFPS<FPSType> operator/(const RationalFPS& lhs, const mint&\
    \ val) {\n            return { lhs.num, lhs.den * val };\n        }\n        friend\
    \ RationalFPS<FPSType> operator*(const mint& val, const RationalFPS& lhs) {\n\
    \            return { lhs.num * val, lhs.den };\n        }\n        friend RationalFPS<FPSType>\
    \ operator/(const mint& val, const RationalFPS& lhs) {\n            return { lhs.den\
    \ * val, lhs.num };\n        }\n\n        RationalFPS<FPSType>& operator+=(const\
    \ RationalFPS& rhs) { return *this = *this + rhs; }\n        RationalFPS<FPSType>&\
    \ operator-=(const RationalFPS& rhs) { return *this = *this - rhs; }\n       \
    \ RationalFPS<FPSType>& operator*=(const RationalFPS& rhs) { return *this = *this\
    \ * rhs; }\n        RationalFPS<FPSType>& operator*=(const mint& val) { return\
    \ num *= val, *this; }\n        RationalFPS<FPSType>& operator/=(const mint& val)\
    \ { return den *= val, *this; }\n\n        RationalFPS<FPSType> inv() const {\
    \ return { den, num }; }\n        RationalFPS<FPSType>& inv_inplace() { return\
    \ std::swap(num, den), * this; }\n\n        void cut(int n) {\n            if\
    \ (int(num.size()) > n) num.resize(n);\n            if (int(den.size()) > n) den.resize(n);\n\
    \        }\n\n        FPSType normalize() {\n            auto [q, r] = num.div_mod(den);\n\
    \            num = std::move(r);\n            return q;\n        }\n\n       \
    \ static RationalFPS<FPSType> sum(const std::vector<RationalFPS<FPSType>>& fs)\
    \ {\n            auto comp = [](const RationalFPS<FPSType>& f, const RationalFPS<FPSType>&\
    \ g) {\n                return f.den.size() > g.den.size();\n            };\n\
    \            std::priority_queue<RationalFPS<FPSType>, std::vector<RationalFPS<FPSType>>,\
    \ decltype(comp)> pq{ comp };\n            for (const auto& f : fs) pq.push(f);\n\
    \n            while (pq.size() > 1) {\n                auto f = pq.top();\n  \
    \              pq.pop();\n                auto g = pq.top();\n               \
    \ pq.pop();\n                pq.emplace(f + g);\n            }\n            return\
    \ pq.top();\n        }\n        static RationalFPS<FPSType> prod(const std::vector<RationalFPS<FPSType>>&\
    \ fs) {\n            std::vector<FPSType> nums, dens;\n            for (const\
    \ auto &f : fs) nums.push_back(f.num), dens.push_back(f.den);\n            return\
    \ { FPSType::prod(nums), FPSType::prod(dens) };\n        }\n    };\n} // namespace\
    \ suisen\n\n#endif // SUISEN_RATIONAL_FPS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/rational_fps.hpp
  requiredBy:
  - library/polynomial/compose_exp.hpp
  timestamp: '2023-05-11 13:36:51+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/polynomial/compose_exp/arc154_f.test.cpp
documentation_of: library/polynomial/rational_fps.hpp
layout: document
title: Rational Fps
---
## Rational Fps