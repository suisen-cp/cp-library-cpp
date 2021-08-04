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
  bundledCode: "#line 1 \"library/util/default_vector.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename T>\nclass default_vector : public std::vector<T>\
    \ {\n    public:\n        using std::vector<T>::vector;\n        void set_default_value(const\
    \ T &val) {\n            default_value = val;\n        }\n        const T& operator[](int\
    \ i) const {\n            return index_out_of_bounds(i) ? default_value : std::vector<T>::operator[](i);\n\
    \        }\n        T& operator[](int i) {\n            if (index_out_of_bounds(i))\
    \ resize(i + 1);\n            return std::vector<T>::operator[](i);\n        }\n\
    \        const T& at(int i) const {\n            return (*this)[i];\n        }\n\
    \        T& at(int i) {\n            return (*this)[i];\n        }\n        T\
    \ get_or_default(int i) const {\n            return index_out_of_bounds(i) ? default_value\
    \ : std::vector<T>::operator[](i);\n        }\n        T get_or_default(int i,\
    \ T tmp_default_value) const {\n            return index_out_of_bounds(i) ? tmp_default_value\
    \ : std::vector<T>::operator[](i);\n        }\n        int size() {\n        \
    \    return std::vector<T>::size();\n        }\n        void resize(int n) {\n\
    \            std::vector<T>::resize(n, default_value);\n        }\n    private:\n\
    \        T default_value;\n        bool index_out_of_bounds(unsigned int i) const\
    \ {\n            return i >= std::vector<T>::size();\n        }\n};\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_DEFAULT_VECTOR\n#define SUISEN_DEFAULT_VECTOR\n\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T>\nclass default_vector\
    \ : public std::vector<T> {\n    public:\n        using std::vector<T>::vector;\n\
    \        void set_default_value(const T &val) {\n            default_value = val;\n\
    \        }\n        const T& operator[](int i) const {\n            return index_out_of_bounds(i)\
    \ ? default_value : std::vector<T>::operator[](i);\n        }\n        T& operator[](int\
    \ i) {\n            if (index_out_of_bounds(i)) resize(i + 1);\n            return\
    \ std::vector<T>::operator[](i);\n        }\n        const T& at(int i) const\
    \ {\n            return (*this)[i];\n        }\n        T& at(int i) {\n     \
    \       return (*this)[i];\n        }\n        T get_or_default(int i) const {\n\
    \            return index_out_of_bounds(i) ? default_value : std::vector<T>::operator[](i);\n\
    \        }\n        T get_or_default(int i, T tmp_default_value) const {\n   \
    \         return index_out_of_bounds(i) ? tmp_default_value : std::vector<T>::operator[](i);\n\
    \        }\n        int size() {\n            return std::vector<T>::size();\n\
    \        }\n        void resize(int n) {\n            std::vector<T>::resize(n,\
    \ default_value);\n        }\n    private:\n        T default_value;\n       \
    \ bool index_out_of_bounds(unsigned int i) const {\n            return i >= std::vector<T>::size();\n\
    \        }\n};\n} // namespace suisen\n\n#endif // SUISEN_DEFAULT_VECTOR"
  dependsOn: []
  isVerificationFile: false
  path: library/util/default_vector.hpp
  requiredBy: []
  timestamp: '2021-08-04 18:37:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/default_vector.hpp
layout: document
redirect_from:
- /library/library/util/default_vector.hpp
- /library/library/util/default_vector.hpp.html
title: library/util/default_vector.hpp
---
