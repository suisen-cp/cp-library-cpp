---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/linear_algebra/xor_base/AOJ_3277.test.cpp
    title: test/src/linear_algebra/xor_base/AOJ_3277.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/linear_algebra/xor_base.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename T>\n    struct XorBase {\n      \
    \  XorBase() = default;\n        XorBase(const std::vector<T> &a) : XorBase()\
    \ {\n            for (const auto &v : a) add(v);\n        }\n\n        bool add(T\
    \ v) {\n            for (const auto &e : _basis) if (T w = e ^ v; w < v) v = std::move(w);\n\
    \            return v ? (_basis.push_back(v), true) : false;\n        }\n    \
    \    XorBase<T>& operator+=(const XorBase<T> &rhs) {\n            for (const T\
    \ &e : rhs._basis) add(e);\n            return *this;\n        }\n        XorBase<T>&\
    \ operator+=(const T &v) {\n            add(v);\n            return *this;\n \
    \       }\n        XorBase<T> operator+(const XorBase<T> &rhs) const {\n     \
    \       XorBase<T> res;\n            res._basis = _basis;\n            return\
    \ res += rhs;\n        }\n        XorBase<T> operator+(const T &v) const {\n \
    \           return *this + XorBase<T>({ v });\n        }\n\n        XorBase<T>\
    \ intersection(const XorBase<T> &rhs) const {\n            std::vector<std::pair<T,\
    \ T>> basis;\n            for (const T &e : _basis) basis.emplace_back(e, e);\n\
    \            XorBase<T> res;\n            for (T e : rhs._basis) {\n         \
    \       T s;\n                if constexpr (std::is_integral_v<T>) s = 0;\n  \
    \              for (const auto &[v, t] : basis) if (T w = e ^ v; w < e) e = std::move(w),\
    \ s ^= t;\n                if (e) basis.emplace_back(e, s);\n                else\
    \ res.add(s);\n            }\n            return res;\n        }\n        XorBase<T>&\
    \ operator&=(const XorBase<T> &rhs) {\n            return *this = intersection(rhs);\n\
    \        }\n        XorBase<T> operator&(const XorBase<T> &rhs) const {\n    \
    \        return intersection(rhs);\n        }\n\n        int dim() const { return\
    \ _basis.size(); }\n\n        const std::vector<T>& get_basis() const { return\
    \ _basis; }\n    private:\n        std::vector<T> _basis;\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_XOR_BASE\n#define SUISEN_XOR_BASE\n\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T>\n    struct XorBase {\n        XorBase()\
    \ = default;\n        XorBase(const std::vector<T> &a) : XorBase() {\n       \
    \     for (const auto &v : a) add(v);\n        }\n\n        bool add(T v) {\n\
    \            for (const auto &e : _basis) if (T w = e ^ v; w < v) v = std::move(w);\n\
    \            return v ? (_basis.push_back(v), true) : false;\n        }\n    \
    \    XorBase<T>& operator+=(const XorBase<T> &rhs) {\n            for (const T\
    \ &e : rhs._basis) add(e);\n            return *this;\n        }\n        XorBase<T>&\
    \ operator+=(const T &v) {\n            add(v);\n            return *this;\n \
    \       }\n        XorBase<T> operator+(const XorBase<T> &rhs) const {\n     \
    \       XorBase<T> res;\n            res._basis = _basis;\n            return\
    \ res += rhs;\n        }\n        XorBase<T> operator+(const T &v) const {\n \
    \           return *this + XorBase<T>({ v });\n        }\n\n        XorBase<T>\
    \ intersection(const XorBase<T> &rhs) const {\n            std::vector<std::pair<T,\
    \ T>> basis;\n            for (const T &e : _basis) basis.emplace_back(e, e);\n\
    \            XorBase<T> res;\n            for (T e : rhs._basis) {\n         \
    \       T s;\n                if constexpr (std::is_integral_v<T>) s = 0;\n  \
    \              for (const auto &[v, t] : basis) if (T w = e ^ v; w < e) e = std::move(w),\
    \ s ^= t;\n                if (e) basis.emplace_back(e, s);\n                else\
    \ res.add(s);\n            }\n            return res;\n        }\n        XorBase<T>&\
    \ operator&=(const XorBase<T> &rhs) {\n            return *this = intersection(rhs);\n\
    \        }\n        XorBase<T> operator&(const XorBase<T> &rhs) const {\n    \
    \        return intersection(rhs);\n        }\n\n        int dim() const { return\
    \ _basis.size(); }\n\n        const std::vector<T>& get_basis() const { return\
    \ _basis; }\n    private:\n        std::vector<T> _basis;\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_XOR_BASE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/linear_algebra/xor_base.hpp
  requiredBy: []
  timestamp: '2022-05-14 02:45:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/linear_algebra/xor_base/AOJ_3277.test.cpp
documentation_of: library/linear_algebra/xor_base.hpp
layout: document
title: "XOR \u57FA\u5E95"
---
## XOR 基底