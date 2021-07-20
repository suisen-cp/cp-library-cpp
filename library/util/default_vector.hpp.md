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
  bundledCode: "#line 1 \"library/util/default_vector.hpp\"\n\n\n\n#include <iostream>\n\
    #include <initializer_list>\n#include <vector>\n\nnamespace suisen {\ntemplate\
    \ <typename T>\nclass default_vector {\n    public:\n        default_vector()\
    \ {}\n        explicit default_vector(const T default_value) : _default_value(default_value)\
    \ {}\n        explicit default_vector(const T default_value, int n) : _default_value(default_value),\
    \ _data(n, default_value) {}\n        explicit default_vector(const T default_value,\
    \ const std::initializer_list<T> list) : _default_value(default_value), _data(list)\
    \ {}\n\n        void set_default_value(const T val) {\n            _default_value\
    \ = val;\n        }\n\n        int size() const {\n            return _data.size();\n\
    \        }\n        void reserve(int n) {\n            _data.reserve(n);\n   \
    \     }\n        const T& operator[](int i) const {\n            ensure_size(i);\n\
    \            return _data[i];\n        }\n        T& operator[](int i) {\n   \
    \         ensure_size(i);\n            return _data[i];\n        }\n        const\
    \ T& front() const { return _data.front(); }\n        T& front()             {\
    \ return _data.front(); }\n        const T& back() const  { return _data.back();\
    \ }\n        T& back()              { return _data.back(); }\n    \n        auto\
    \ begin()   { return _data.begin(); }\n        auto end()     { return _data.end();\
    \ }\n        auto rbegin()  { return _data.rbegin(); }\n        auto rend()  \
    \  { return _data.rend(); }\n        auto cbegin()  { return _data.cbegin(); }\n\
    \        auto cend()    { return _data.cend(); }\n        auto crbegin() { return\
    \ _data.crbegin(); }\n        auto crend()   { return _data.crend(); }\n    \n\
    \        void push_back(const T &element) {\n            _data.push_back(element);\n\
    \        }\n        void push_back(const T &&element) {\n            _data.push_back(element);\n\
    \        }\n        template <typename ...Args>\n        void emplace_back(Args\
    \ &&...args) {\n            _data.emplace_back(std::forward<Args>(args)...);\n\
    \        }\n\n        void pop_back() {\n            _data.pop_back();\n     \
    \   }\n\n        void erase(const typename std::vector<T>::const_iterator position)\
    \ {\n            _data.erase(position);\n        }\n        void erase(const typename\
    \ std::vector<T>::const_iterator first, const typename std::vector<T>::const_iterator\
    \ last) {\n            _data.erase(first, last);\n        }\n        void clear()\
    \ {\n            _data.clear();\n        }\n        void insert(const typename\
    \ std::vector<T>::const_iterator position, const T &element) {\n            _data.insert(position,\
    \ element);\n        }\n        void insert(const typename std::vector<T>::const_iterator\
    \ position, const T &&element) {\n            _data.insert(position, element);\n\
    \        }\n        void insert(const typename std::vector<T>::const_iterator\
    \ position, const std::initializer_list<T> list) {\n            _data.insert(position,\
    \ list);\n        }\n        template <typename InputIterator>\n        void insert(const\
    \ typename std::vector<T>::const_iterator position, const InputIterator first,\
    \ const InputIterator last) {\n            _data.insert(position, first, last);\n\
    \        }\n\n        void swap(default_vector<T> &other) {\n            _data.swap(other._data);\n\
    \        }\n\n        friend std::istream& operator>>(std::ostream& in, const\
    \ default_vector<T> &a) {\n            return in >> a._data;\n        }\n    \
    \    friend std::ostream& operator<<(std::ostream& out, const default_vector<T>\
    \ &a) {\n            return out << a._data;\n        }\n    private:\n       \
    \ T _default_value;\n        std::vector<T> _data;\n        void ensure_size(int\
    \ n) {\n            if (int(_data.size()) < n + 1) {\n                _data.resize(n\
    \ + 1, _default_value);\n            }\n        }\n};\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_DEFAULT_VECTOR\n#define SUISEN_DEFAULT_VECTOR\n\n#include\
    \ <iostream>\n#include <initializer_list>\n#include <vector>\n\nnamespace suisen\
    \ {\ntemplate <typename T>\nclass default_vector {\n    public:\n        default_vector()\
    \ {}\n        explicit default_vector(const T default_value) : _default_value(default_value)\
    \ {}\n        explicit default_vector(const T default_value, int n) : _default_value(default_value),\
    \ _data(n, default_value) {}\n        explicit default_vector(const T default_value,\
    \ const std::initializer_list<T> list) : _default_value(default_value), _data(list)\
    \ {}\n\n        void set_default_value(const T val) {\n            _default_value\
    \ = val;\n        }\n\n        int size() const {\n            return _data.size();\n\
    \        }\n        void reserve(int n) {\n            _data.reserve(n);\n   \
    \     }\n        const T& operator[](int i) const {\n            ensure_size(i);\n\
    \            return _data[i];\n        }\n        T& operator[](int i) {\n   \
    \         ensure_size(i);\n            return _data[i];\n        }\n        const\
    \ T& front() const { return _data.front(); }\n        T& front()             {\
    \ return _data.front(); }\n        const T& back() const  { return _data.back();\
    \ }\n        T& back()              { return _data.back(); }\n    \n        auto\
    \ begin()   { return _data.begin(); }\n        auto end()     { return _data.end();\
    \ }\n        auto rbegin()  { return _data.rbegin(); }\n        auto rend()  \
    \  { return _data.rend(); }\n        auto cbegin()  { return _data.cbegin(); }\n\
    \        auto cend()    { return _data.cend(); }\n        auto crbegin() { return\
    \ _data.crbegin(); }\n        auto crend()   { return _data.crend(); }\n    \n\
    \        void push_back(const T &element) {\n            _data.push_back(element);\n\
    \        }\n        void push_back(const T &&element) {\n            _data.push_back(element);\n\
    \        }\n        template <typename ...Args>\n        void emplace_back(Args\
    \ &&...args) {\n            _data.emplace_back(std::forward<Args>(args)...);\n\
    \        }\n\n        void pop_back() {\n            _data.pop_back();\n     \
    \   }\n\n        void erase(const typename std::vector<T>::const_iterator position)\
    \ {\n            _data.erase(position);\n        }\n        void erase(const typename\
    \ std::vector<T>::const_iterator first, const typename std::vector<T>::const_iterator\
    \ last) {\n            _data.erase(first, last);\n        }\n        void clear()\
    \ {\n            _data.clear();\n        }\n        void insert(const typename\
    \ std::vector<T>::const_iterator position, const T &element) {\n            _data.insert(position,\
    \ element);\n        }\n        void insert(const typename std::vector<T>::const_iterator\
    \ position, const T &&element) {\n            _data.insert(position, element);\n\
    \        }\n        void insert(const typename std::vector<T>::const_iterator\
    \ position, const std::initializer_list<T> list) {\n            _data.insert(position,\
    \ list);\n        }\n        template <typename InputIterator>\n        void insert(const\
    \ typename std::vector<T>::const_iterator position, const InputIterator first,\
    \ const InputIterator last) {\n            _data.insert(position, first, last);\n\
    \        }\n\n        void swap(default_vector<T> &other) {\n            _data.swap(other._data);\n\
    \        }\n\n        friend std::istream& operator>>(std::ostream& in, const\
    \ default_vector<T> &a) {\n            return in >> a._data;\n        }\n    \
    \    friend std::ostream& operator<<(std::ostream& out, const default_vector<T>\
    \ &a) {\n            return out << a._data;\n        }\n    private:\n       \
    \ T _default_value;\n        std::vector<T> _data;\n        void ensure_size(int\
    \ n) {\n            if (int(_data.size()) < n + 1) {\n                _data.resize(n\
    \ + 1, _default_value);\n            }\n        }\n};\n} // namespace suisen\n\
    \n#endif // SUISEN_DEFAULT_VECTOR"
  dependsOn: []
  isVerificationFile: false
  path: library/util/default_vector.hpp
  requiredBy: []
  timestamp: '2021-07-20 14:25:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/default_vector.hpp
layout: document
redirect_from:
- /library/library/util/default_vector.hpp
- /library/library/util/default_vector.hpp.html
title: library/util/default_vector.hpp
---
