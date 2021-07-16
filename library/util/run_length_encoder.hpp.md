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
  bundledCode: "#line 1 \"library/util/run_length_encoder.hpp\"\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename Container>\nclass run_length_encoder\
    \ {\n    public:\n        using content_type   = typename Container::value_type;\n\
    \        using value_type     = std::pair<content_type, int>;\n        using iterator\
    \       = typename std::vector<value_type>::iterator;\n        using const_iterator\
    \ = typename std::vector<value_type>::const_iterator;\n\n        run_length_encoder(const\
    \ Container &c) noexcept {\n            compress(c, comp);\n        }\n\n    \
    \    static void compress(const Container &c, std::vector<value_type> &res) {\n\
    \            res.clear();\n            for (auto it_l = c.begin(), it_r = c.begin();\
    \ it_l != c.end(); it_l = it_r) {\n                while (it_r != c.end() and\
    \ *it_l == *it_r) ++it_r;\n                res.emplace_back(*it_l, it_r - it_l);\n\
    \            }\n        }\n        static std::vector<value_type> compress(const\
    \ Container &c) {\n            std::vector<value_type> res;\n            compress(std::forward<Container>(c),\
    \ res);\n            return res;\n        }\n        static std::vector<value_type>\
    \ compress(const Container &&c) {\n            std::vector<value_type> res;\n\
    \            compress(std::forward<Container>(c), res);\n            return res;\n\
    \        }\n\n        const auto& cdata() const noexcept { return comp; }\n  \
    \            auto   data() const noexcept { return comp; }\n\n        int max_size()\
    \ const noexcept { return comp.max_size(); }\n        int capacity() const noexcept\
    \ { return comp.capacity(); }\n        int size()     const noexcept { return\
    \ comp.size(); }\n        void reserve(int n) { comp.reserve(n); }\n        void\
    \ shrink_to_fit() { comp.shrink_to_fit(); }\n        void resize(int n) { comp.resize();\
    \ }\n        void resize(int n, const value_type  &x) { comp.resize(n, x); }\n\
    \        void resize(int n, const value_type &&x) { comp.resize(n, x); }\n   \
    \     void assign(int n, const value_type  &x) { comp.assign(n, x); }\n      \
    \  void assign(int n, const value_type &&x) { comp.assign(n, x); }\n        template\
    \ <typename InputIterator>\n        void assign(const InputIterator first, const\
    \ InputIterator last) { comp.assign(first, last); }\n        void swap(run_length_encoder<Container>\
    \  &other) { comp.swap(other.comp); }\n        void swap(run_length_encoder<Container>\
    \ &&other) { comp.swap(other.comp); }\n        void clear() { comp.clear(); }\n\
    \n        auto begin()   const noexcept { return comp.begin();   }\n        auto\
    \ end()     const noexcept { return comp.end();     }\n        auto rbegin() \
    \ const noexcept { return comp.rbegin();  }\n        auto rend()    const noexcept\
    \ { return comp.rend();    }\n        auto cbegin()  const noexcept { return comp.cbegin();\
    \  }\n        auto cend()    const noexcept { return comp.cend();    }\n     \
    \   auto crbegin() const noexcept { return comp.crbegin(); }\n        auto crend()\
    \   const noexcept { return comp.crend();   }\n\n        const auto& operator[](const\
    \ int i) const { return comp[i]; }\n              auto& operator[](const int i)\
    \       { return comp[i]; }\n        const auto& at(const int i) const { return\
    \ comp.at(i); }\n              auto& at(const int i)       { return comp.at(i);\
    \ }\n        const auto& front() const { return comp.front(); }\n            \
    \  auto& front()       { return comp.front(); }\n        const auto& back()  const\
    \ { return comp.back(); }\n              auto& back()        { return comp.back();\
    \ }\n\n        void erase(const const_iterator pos) { comp.erase(pos); }\n   \
    \     void erase(const const_iterator first, const const_iterator last) { comp.erase(first,\
    \ last); }\n        void pop_back() { comp.pop_back(); }\n        void insert(const\
    \ const_iterator pos, value_type  &entry) { comp.insert(pos, std::forward<value_type>(entry));\
    \ }\n        void insert(const const_iterator pos, value_type &&entry) { comp.insert(pos,\
    \ std::forward<value_type>(entry)); }\n        void push_back(value_type  &entry)\
    \ { comp.push_back(std::forward<value_type>(entry)); }\n        void push_back(value_type\
    \ &&entry) { comp.push_back(std::forward<value_type>(entry)); }\n        template\
    \ <typename ...Args>\n        void emplace(const const_iterator pos, Args  &...args)\
    \ { comp.emplace(pos, std::forward<Args>(args)...); }\n        template <typename\
    \ ...Args>\n        void emplace(const const_iterator pos, Args &&...args) { comp.emplace(pos,\
    \ std::forward<Args>(args)...); }\n        template <typename ...Args>\n     \
    \   void emplace_back(Args  &...args) { comp.emplace_back(std::forward<Args>(args)...);\
    \ }\n        template <typename ...Args>\n        void emplace_back(Args &&...args)\
    \ { comp.emplace_back(std::forward<Args>(args)...); }\n    private:\n        std::vector<value_type>\
    \ comp;\n};\n} // namespace suisen\n"
  code: "#include <vector>\n\nnamespace suisen {\ntemplate <typename Container>\n\
    class run_length_encoder {\n    public:\n        using content_type   = typename\
    \ Container::value_type;\n        using value_type     = std::pair<content_type,\
    \ int>;\n        using iterator       = typename std::vector<value_type>::iterator;\n\
    \        using const_iterator = typename std::vector<value_type>::const_iterator;\n\
    \n        run_length_encoder(const Container &c) noexcept {\n            compress(c,\
    \ comp);\n        }\n\n        static void compress(const Container &c, std::vector<value_type>\
    \ &res) {\n            res.clear();\n            for (auto it_l = c.begin(), it_r\
    \ = c.begin(); it_l != c.end(); it_l = it_r) {\n                while (it_r !=\
    \ c.end() and *it_l == *it_r) ++it_r;\n                res.emplace_back(*it_l,\
    \ it_r - it_l);\n            }\n        }\n        static std::vector<value_type>\
    \ compress(const Container &c) {\n            std::vector<value_type> res;\n \
    \           compress(std::forward<Container>(c), res);\n            return res;\n\
    \        }\n        static std::vector<value_type> compress(const Container &&c)\
    \ {\n            std::vector<value_type> res;\n            compress(std::forward<Container>(c),\
    \ res);\n            return res;\n        }\n\n        const auto& cdata() const\
    \ noexcept { return comp; }\n              auto   data() const noexcept { return\
    \ comp; }\n\n        int max_size() const noexcept { return comp.max_size(); }\n\
    \        int capacity() const noexcept { return comp.capacity(); }\n        int\
    \ size()     const noexcept { return comp.size(); }\n        void reserve(int\
    \ n) { comp.reserve(n); }\n        void shrink_to_fit() { comp.shrink_to_fit();\
    \ }\n        void resize(int n) { comp.resize(); }\n        void resize(int n,\
    \ const value_type  &x) { comp.resize(n, x); }\n        void resize(int n, const\
    \ value_type &&x) { comp.resize(n, x); }\n        void assign(int n, const value_type\
    \  &x) { comp.assign(n, x); }\n        void assign(int n, const value_type &&x)\
    \ { comp.assign(n, x); }\n        template <typename InputIterator>\n        void\
    \ assign(const InputIterator first, const InputIterator last) { comp.assign(first,\
    \ last); }\n        void swap(run_length_encoder<Container>  &other) { comp.swap(other.comp);\
    \ }\n        void swap(run_length_encoder<Container> &&other) { comp.swap(other.comp);\
    \ }\n        void clear() { comp.clear(); }\n\n        auto begin()   const noexcept\
    \ { return comp.begin();   }\n        auto end()     const noexcept { return comp.end();\
    \     }\n        auto rbegin()  const noexcept { return comp.rbegin();  }\n  \
    \      auto rend()    const noexcept { return comp.rend();    }\n        auto\
    \ cbegin()  const noexcept { return comp.cbegin();  }\n        auto cend()   \
    \ const noexcept { return comp.cend();    }\n        auto crbegin() const noexcept\
    \ { return comp.crbegin(); }\n        auto crend()   const noexcept { return comp.crend();\
    \   }\n\n        const auto& operator[](const int i) const { return comp[i]; }\n\
    \              auto& operator[](const int i)       { return comp[i]; }\n     \
    \   const auto& at(const int i) const { return comp.at(i); }\n              auto&\
    \ at(const int i)       { return comp.at(i); }\n        const auto& front() const\
    \ { return comp.front(); }\n              auto& front()       { return comp.front();\
    \ }\n        const auto& back()  const { return comp.back(); }\n             \
    \ auto& back()        { return comp.back(); }\n\n        void erase(const const_iterator\
    \ pos) { comp.erase(pos); }\n        void erase(const const_iterator first, const\
    \ const_iterator last) { comp.erase(first, last); }\n        void pop_back() {\
    \ comp.pop_back(); }\n        void insert(const const_iterator pos, value_type\
    \  &entry) { comp.insert(pos, std::forward<value_type>(entry)); }\n        void\
    \ insert(const const_iterator pos, value_type &&entry) { comp.insert(pos, std::forward<value_type>(entry));\
    \ }\n        void push_back(value_type  &entry) { comp.push_back(std::forward<value_type>(entry));\
    \ }\n        void push_back(value_type &&entry) { comp.push_back(std::forward<value_type>(entry));\
    \ }\n        template <typename ...Args>\n        void emplace(const const_iterator\
    \ pos, Args  &...args) { comp.emplace(pos, std::forward<Args>(args)...); }\n \
    \       template <typename ...Args>\n        void emplace(const const_iterator\
    \ pos, Args &&...args) { comp.emplace(pos, std::forward<Args>(args)...); }\n \
    \       template <typename ...Args>\n        void emplace_back(Args  &...args)\
    \ { comp.emplace_back(std::forward<Args>(args)...); }\n        template <typename\
    \ ...Args>\n        void emplace_back(Args &&...args) { comp.emplace_back(std::forward<Args>(args)...);\
    \ }\n    private:\n        std::vector<value_type> comp;\n};\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/util/run_length_encoder.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/run_length_encoder.hpp
layout: document
redirect_from:
- /library/library/util/run_length_encoder.hpp
- /library/library/util/run_length_encoder.hpp.html
title: library/util/run_length_encoder.hpp
---
