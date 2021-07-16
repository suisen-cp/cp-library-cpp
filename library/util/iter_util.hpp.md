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
  bundledCode: "#line 1 \"library/util/iter_util.hpp\"\n#include <algorithm>\n#include\
    \ <array>\n#include <initializer_list>\n#include <numeric>\n#include <limits>\n\
    \nnamespace suisen {\nnamespace internal {\n\ntemplate <typename T>\nconst auto\
    \ true_pred = [](const T){ return true; };\n\ntemplate <typename Container, bool\
    \ ascending, bool (*f)(typename Container::iterator, typename Container::iterator)>\n\
    class internal_permutations {\n    private:\n        struct permutations_iterator\
    \ {\n            Container p;\n            bool next;\n            permutations_iterator(const\
    \ Container &&container) : p(std::move(container)), next(p.size()) { next = p.size();\
    \ }\n            permutations_iterator() {\n                if (ascending) std::iota(p.\
    \ begin(), p. end(), 0);\n                else           std::iota(p.rbegin(),\
    \ p.rend(), 0);\n                next = p.size();\n            }\n           \
    \ Container operator*() const {\n                return p;\n            }\n  \
    \          bool operator!=(const permutations_iterator) const {\n            \
    \    return next;\n            }\n            permutations_iterator& operator++()\
    \ {\n                next = f(p.begin(), p.end());\n                return *this;\n\
    \            }\n        };\n        Container container;\n        bool init;\n\
    \    public:\n        internal_permutations() : container(), init(false) {}\n\
    \        internal_permutations(const Container  &container) : container(container),\
    \ init(true) {}\n        internal_permutations(const Container &&container) :\
    \ container(std::move(container)), init(true) {}\n        permutations_iterator\
    \ begin() const { return init ? permutations_iterator(std::move(container)) :\
    \ end(); }\n        permutations_iterator end()   const { return permutations_iterator{};\
    \ }\n};\n\ntemplate <int n>\nusing permutations      = internal_permutations<std::array<int,\
    \ n>, true,  std::next_permutation<typename std::array<int, n>::iterator>>;\n\
    template <int n>\nusing permutations_desc = internal_permutations<std::array<int,\
    \ n>, false, std::prev_permutation<typename std::array<int, n>::iterator>>;\n\
    using vec_permutations      = internal_permutations<std::vector<int>, true,  std::next_permutation<typename\
    \ std::vector<int>::iterator>>;\nusing vec_permutations_desc = internal_permutations<std::vector<int>,\
    \ false, std::prev_permutation<typename std::vector<int>::iterator>>;\n\n} //\
    \ namespace internal\n\ntemplate <\n    typename F, typename Iterable,\n    typename\
    \ Iterator = typename Iterable::const_iterator, typename value_type = typename\
    \ Iterable::value_type\n>\nclass enumerate_if {\n    private:\n        struct\
    \ enumerate_iterator {\n            F pred;\n            Iterator it;\n      \
    \      int num;\n            int i;\n            enumerate_iterator(const F pred,\
    \ const Iterator iterator, int num) : pred(pred), it(iterator), num(num), i(0)\
    \ {}\n            std::pair<int, value_type> operator*() const {\n           \
    \     return {i, *it};\n            }\n            bool operator!=(const enumerate_iterator\
    \ &other) {\n                if (i == num) return false;\n                while\
    \ (it != other.it and not pred(*it)) ++it;\n                return it != other.it;\n\
    \            }\n            enumerate_iterator& operator++() {\n             \
    \   ++i, ++it;\n                return *this;\n            }\n        };\n   \
    \     const F pred;\n        const Iterable &iterable;\n        const int max_iterate_num;\n\
    \    public:\n        enumerate_if(const F pred, const Iterable &iterable, const\
    \ int max_iterate_num = std::numeric_limits<int>::max())\n            : pred(pred),\
    \ iterable(iterable), max_iterate_num(max_iterate_num) {}\n        auto begin()\
    \ const {\n            return enumerate_iterator(pred, iterable.begin(), max_iterate_num);\n\
    \        }\n        auto end() const {\n            return enumerate_iterator(pred,\
    \ iterable.end(), max_iterate_num);\n        }\n};\n\ntemplate <typename Iterable,\
    \ typename Iterator = typename Iterable::const_iterator, typename value_type =\
    \ typename Iterable::value_type>\nstruct enumerate : public enumerate_if<decltype(internal::true_pred<value_type>),\
    \ Iterable> {\n    enumerate(const Iterable &iterable, const int max_iterate_num\
    \ = std::numeric_limits<int>::max()) :\n        enumerate_if<decltype(internal::true_pred<value_type>),\
    \ Iterable>(internal::true_pred<value_type>, iterable, max_iterate_num) {}\n};\n\
    \ntemplate <typename T>\nclass range {\n    private:\n        struct range_iterator\
    \ {\n            T cur;\n            const T r, step;\n            range_iterator(T\
    \ l, T r, T step) : cur(l), r(r), step(step) {}\n            range_iterator()\
    \ : range_iterator(0, 0, 0) {}\n            T operator*() const {\n          \
    \      return cur;\n            }\n            bool operator!=(const range_iterator)\
    \ const {\n                return cur < r;\n            }\n            range_iterator&\
    \ operator++() {\n                cur += step;\n                return *this;\n\
    \            }\n        };\n        const T l, r, step;\n    public:\n       \
    \ range(T l, T r, T step) : l(l), r(r), step(step) {}\n        range(T l, T r)\
    \ : range(l, r, 1) {}\n        range(T r) : range(0, r) {}\n        auto begin()\
    \ const { return range_iterator{l, r, step}; }\n        auto end()   const { return\
    \ range_iterator{}; }\n};\n\ntemplate <int n>\nauto all_permutations() { return\
    \ internal::permutations<n>{}; }\ntemplate <int n>\nauto all_permutations(const\
    \ std::array<int, n>  &a) { return internal::permutations<n>(a); }\ntemplate <int\
    \ n>\nauto all_permutations(const std::array<int, n> &&a) { return internal::permutations<n>(std::move(a));\
    \ }\ntemplate <int n>\nauto all_permutations_desc() { return internal::permutations_desc<n>{};\
    \ }\ntemplate <int n>\nauto all_permutations_desc(const std::array<int, n>  &a)\
    \ { return internal::permutations_desc<n>(a); }\ntemplate <int n>\nauto all_permutations_desc(const\
    \ std::array<int, n> &&a) { return internal::permutations_desc<n>(std::move(a));\
    \ }\nauto all_permutations(int n) {\n    std::vector<int> p(n);\n    std::iota(p.begin(),\
    \ p.end(), 0);\n    return internal::vec_permutations(std::move(p));\n}\nauto\
    \ all_permutations(const std::vector<int>  &p) { return internal::vec_permutations(p);\
    \ }\nauto all_permutations(const std::vector<int> &&p) { return internal::vec_permutations(std::move(p));\
    \ }\nauto all_permutations_desc(int n) {\n    std::vector<int> p(n);\n    std::iota(p.rbegin(),\
    \ p.rend(), 0);\n    return internal::vec_permutations_desc(std::move(p));\n}\n\
    auto all_permutations_desc(const std::vector<int>  &p) { return internal::vec_permutations_desc(p);\
    \ }\nauto all_permutations_desc(const std::vector<int> &&p) { return internal::vec_permutations_desc(std::move(p));\
    \ }\n\n} // namespace suisen\n"
  code: "#include <algorithm>\n#include <array>\n#include <initializer_list>\n#include\
    \ <numeric>\n#include <limits>\n\nnamespace suisen {\nnamespace internal {\n\n\
    template <typename T>\nconst auto true_pred = [](const T){ return true; };\n\n\
    template <typename Container, bool ascending, bool (*f)(typename Container::iterator,\
    \ typename Container::iterator)>\nclass internal_permutations {\n    private:\n\
    \        struct permutations_iterator {\n            Container p;\n          \
    \  bool next;\n            permutations_iterator(const Container &&container)\
    \ : p(std::move(container)), next(p.size()) { next = p.size(); }\n           \
    \ permutations_iterator() {\n                if (ascending) std::iota(p. begin(),\
    \ p. end(), 0);\n                else           std::iota(p.rbegin(), p.rend(),\
    \ 0);\n                next = p.size();\n            }\n            Container\
    \ operator*() const {\n                return p;\n            }\n            bool\
    \ operator!=(const permutations_iterator) const {\n                return next;\n\
    \            }\n            permutations_iterator& operator++() {\n          \
    \      next = f(p.begin(), p.end());\n                return *this;\n        \
    \    }\n        };\n        Container container;\n        bool init;\n    public:\n\
    \        internal_permutations() : container(), init(false) {}\n        internal_permutations(const\
    \ Container  &container) : container(container), init(true) {}\n        internal_permutations(const\
    \ Container &&container) : container(std::move(container)), init(true) {}\n  \
    \      permutations_iterator begin() const { return init ? permutations_iterator(std::move(container))\
    \ : end(); }\n        permutations_iterator end()   const { return permutations_iterator{};\
    \ }\n};\n\ntemplate <int n>\nusing permutations      = internal_permutations<std::array<int,\
    \ n>, true,  std::next_permutation<typename std::array<int, n>::iterator>>;\n\
    template <int n>\nusing permutations_desc = internal_permutations<std::array<int,\
    \ n>, false, std::prev_permutation<typename std::array<int, n>::iterator>>;\n\
    using vec_permutations      = internal_permutations<std::vector<int>, true,  std::next_permutation<typename\
    \ std::vector<int>::iterator>>;\nusing vec_permutations_desc = internal_permutations<std::vector<int>,\
    \ false, std::prev_permutation<typename std::vector<int>::iterator>>;\n\n} //\
    \ namespace internal\n\ntemplate <\n    typename F, typename Iterable,\n    typename\
    \ Iterator = typename Iterable::const_iterator, typename value_type = typename\
    \ Iterable::value_type\n>\nclass enumerate_if {\n    private:\n        struct\
    \ enumerate_iterator {\n            F pred;\n            Iterator it;\n      \
    \      int num;\n            int i;\n            enumerate_iterator(const F pred,\
    \ const Iterator iterator, int num) : pred(pred), it(iterator), num(num), i(0)\
    \ {}\n            std::pair<int, value_type> operator*() const {\n           \
    \     return {i, *it};\n            }\n            bool operator!=(const enumerate_iterator\
    \ &other) {\n                if (i == num) return false;\n                while\
    \ (it != other.it and not pred(*it)) ++it;\n                return it != other.it;\n\
    \            }\n            enumerate_iterator& operator++() {\n             \
    \   ++i, ++it;\n                return *this;\n            }\n        };\n   \
    \     const F pred;\n        const Iterable &iterable;\n        const int max_iterate_num;\n\
    \    public:\n        enumerate_if(const F pred, const Iterable &iterable, const\
    \ int max_iterate_num = std::numeric_limits<int>::max())\n            : pred(pred),\
    \ iterable(iterable), max_iterate_num(max_iterate_num) {}\n        auto begin()\
    \ const {\n            return enumerate_iterator(pred, iterable.begin(), max_iterate_num);\n\
    \        }\n        auto end() const {\n            return enumerate_iterator(pred,\
    \ iterable.end(), max_iterate_num);\n        }\n};\n\ntemplate <typename Iterable,\
    \ typename Iterator = typename Iterable::const_iterator, typename value_type =\
    \ typename Iterable::value_type>\nstruct enumerate : public enumerate_if<decltype(internal::true_pred<value_type>),\
    \ Iterable> {\n    enumerate(const Iterable &iterable, const int max_iterate_num\
    \ = std::numeric_limits<int>::max()) :\n        enumerate_if<decltype(internal::true_pred<value_type>),\
    \ Iterable>(internal::true_pred<value_type>, iterable, max_iterate_num) {}\n};\n\
    \ntemplate <typename T>\nclass range {\n    private:\n        struct range_iterator\
    \ {\n            T cur;\n            const T r, step;\n            range_iterator(T\
    \ l, T r, T step) : cur(l), r(r), step(step) {}\n            range_iterator()\
    \ : range_iterator(0, 0, 0) {}\n            T operator*() const {\n          \
    \      return cur;\n            }\n            bool operator!=(const range_iterator)\
    \ const {\n                return cur < r;\n            }\n            range_iterator&\
    \ operator++() {\n                cur += step;\n                return *this;\n\
    \            }\n        };\n        const T l, r, step;\n    public:\n       \
    \ range(T l, T r, T step) : l(l), r(r), step(step) {}\n        range(T l, T r)\
    \ : range(l, r, 1) {}\n        range(T r) : range(0, r) {}\n        auto begin()\
    \ const { return range_iterator{l, r, step}; }\n        auto end()   const { return\
    \ range_iterator{}; }\n};\n\ntemplate <int n>\nauto all_permutations() { return\
    \ internal::permutations<n>{}; }\ntemplate <int n>\nauto all_permutations(const\
    \ std::array<int, n>  &a) { return internal::permutations<n>(a); }\ntemplate <int\
    \ n>\nauto all_permutations(const std::array<int, n> &&a) { return internal::permutations<n>(std::move(a));\
    \ }\ntemplate <int n>\nauto all_permutations_desc() { return internal::permutations_desc<n>{};\
    \ }\ntemplate <int n>\nauto all_permutations_desc(const std::array<int, n>  &a)\
    \ { return internal::permutations_desc<n>(a); }\ntemplate <int n>\nauto all_permutations_desc(const\
    \ std::array<int, n> &&a) { return internal::permutations_desc<n>(std::move(a));\
    \ }\nauto all_permutations(int n) {\n    std::vector<int> p(n);\n    std::iota(p.begin(),\
    \ p.end(), 0);\n    return internal::vec_permutations(std::move(p));\n}\nauto\
    \ all_permutations(const std::vector<int>  &p) { return internal::vec_permutations(p);\
    \ }\nauto all_permutations(const std::vector<int> &&p) { return internal::vec_permutations(std::move(p));\
    \ }\nauto all_permutations_desc(int n) {\n    std::vector<int> p(n);\n    std::iota(p.rbegin(),\
    \ p.rend(), 0);\n    return internal::vec_permutations_desc(std::move(p));\n}\n\
    auto all_permutations_desc(const std::vector<int>  &p) { return internal::vec_permutations_desc(p);\
    \ }\nauto all_permutations_desc(const std::vector<int> &&p) { return internal::vec_permutations_desc(std::move(p));\
    \ }\n\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/util/iter_util.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/iter_util.hpp
layout: document
redirect_from:
- /library/library/util/iter_util.hpp
- /library/library/util/iter_util.hpp.html
title: library/util/iter_util.hpp
---
