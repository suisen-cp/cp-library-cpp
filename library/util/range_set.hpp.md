---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/util/range_set/DSL_2_D.test.cpp
    title: test/src/util/range_set/DSL_2_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/util/range_set/DSL_4_A.test.cpp
    title: test/src/util/range_set/DSL_4_A.test.cpp
  - icon: ':x:'
    path: test/src/util/range_set/past6_m.test.cpp
    title: test/src/util/range_set/past6_m.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/util/range_set/yuki674.test.cpp
    title: test/src/util/range_set/yuki674.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/range_set.hpp\"\n\n\n\n#include <map>\n\nnamespace\
    \ suisen {\n\ntemplate <typename T, bool merge_adjacent_segment = true>\nstruct\
    \ RangeSet : public std::map<T, T> {\n    public:\n        RangeSet() : _size(0)\
    \ {}\n\n        // returns the number of intergers in this set (not the number\
    \ of ranges). O(1)\n        T size() const { return number_of_elements(); }\n\
    \        // returns the number of intergers in this set (not the number of ranges).\
    \ O(1)\n        T number_of_elements() const { return _size; }\n        // returns\
    \ the number of ranges in this set (not the number of integers). O(1)\n      \
    \  int number_of_ranges() const { return std::map<T, T>::size(); }\n\n       \
    \ // returns whether the given integer is in this set or not. O(log N)\n     \
    \   bool contains(T x) const {\n            auto it = this->upper_bound(x);\n\
    \            return it != this->begin() and x <= std::prev(it)->second;\n    \
    \    }\n\n        /**\n         * returns the iterator pointing to the range [l,\
    \ r] in this set s.t. l <= x <= r.\n         * if such a range does not exist,\
    \ returns `end()`.\n         * O(log N)\n         */\n        auto find_range(T\
    \ x) const {\n            auto it = this->upper_bound(x);\n            return\
    \ it != this->begin() and x <= (--it)->second ? it : this->end();\n        }\n\
    \n        // returns whether `x` and `y` is in this set and in the same range.\
    \ O(log N)\n        bool in_the_same_range(T x, T y) const {\n            auto\
    \ it = get_containing_range(x);\n            return it != this->end() and it->first\
    \ <= y and y <= it->second;\n        }\n\n        // inserts the range [x, x]\
    \ and returns the number of integers inserted to this set. O(log N)\n        T\
    \ insert(T x) {\n            return insert(x, x);\n        }\n        \n     \
    \   // inserts the range [l, r] and returns the number of integers inserted to\
    \ this set. amortized O(log N)\n        T insert(T l, T r) {\n            if (l\
    \ > r) return 0;\n            auto it = this->upper_bound(l);\n            if\
    \ (it != this->begin() and is_mergeable(std::prev(it)->second, l)) {\n       \
    \         it = std::prev(it);\n                l = std::min(l, it->first);\n \
    \           }\n            T inserted = 0;\n            for (; it != this->end()\
    \ and is_mergeable(r, it->first); it = std::map<T, T>::erase(it)) {\n        \
    \        auto [cl, cr] = *it; \n                r = std::max(r, cr);\n       \
    \         inserted -= cr - cl + 1;\n            }\n            inserted += r -\
    \ l + 1;\n            (*this)[l] = r;\n            _size += inserted;\n      \
    \      return inserted;\n        }\n\n        // erases the range [x, x] and returns\
    \ the number of intergers erased from this set. O(log N)\n        T erase(T x)\
    \ {\n            return erase(x, x);\n        }\n\n        // erases the range\
    \ [l, r] and returns the number of intergers erased from this set. amortized O(log\
    \ N)\n        T erase(T l, T r) {\n            if (l > r) return 0;\n        \
    \    T tl = l, tr = r;\n            auto it = this->upper_bound(l);\n        \
    \    if (it != this->begin() and l <= std::prev(it)->second) {\n             \
    \   it = std::prev(it);\n                tl = it->first;\n            }\n    \
    \        T erased = 0;\n            for (; it != this->end() and it->first <=\
    \ r; it = std::map<T, T>::erase(it)) {\n                auto [cl, cr] = *it;\n\
    \                tr = cr;\n                erased += cr - cl + 1;\n          \
    \  }\n            if (tl < l) {\n                (*this)[tl] = l - 1;\n      \
    \          erased -= l - tl;\n            }\n            if (r < tr) {\n     \
    \           (*this)[r + 1] = tr;\n                erased -= tr - r;\n        \
    \    }\n            _size -= erased;\n            return erased;\n        }\n\n\
    \        // returns minimum integer x s.t. x >= lower and x is NOT in this set\n\
    \        T minimum_excluded(T lower = 0) const {\n            static_assert(merge_adjacent_segment);\n\
    \            auto it = find_range(lower);\n            return it == this->end()\
    \ ? lower : it->second + 1;\n        }\n\n    private:\n        T _size;\n\n \
    \       bool is_mergeable(T cur_r, T next_l) {\n            return next_l <= cur_r\
    \ + merge_adjacent_segment;\n        }\n};\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_RANGE_SET\n#define SUISEN_RANGE_SET\n\n#include <map>\n\n\
    namespace suisen {\n\ntemplate <typename T, bool merge_adjacent_segment = true>\n\
    struct RangeSet : public std::map<T, T> {\n    public:\n        RangeSet() : _size(0)\
    \ {}\n\n        // returns the number of intergers in this set (not the number\
    \ of ranges). O(1)\n        T size() const { return number_of_elements(); }\n\
    \        // returns the number of intergers in this set (not the number of ranges).\
    \ O(1)\n        T number_of_elements() const { return _size; }\n        // returns\
    \ the number of ranges in this set (not the number of integers). O(1)\n      \
    \  int number_of_ranges() const { return std::map<T, T>::size(); }\n\n       \
    \ // returns whether the given integer is in this set or not. O(log N)\n     \
    \   bool contains(T x) const {\n            auto it = this->upper_bound(x);\n\
    \            return it != this->begin() and x <= std::prev(it)->second;\n    \
    \    }\n\n        /**\n         * returns the iterator pointing to the range [l,\
    \ r] in this set s.t. l <= x <= r.\n         * if such a range does not exist,\
    \ returns `end()`.\n         * O(log N)\n         */\n        auto find_range(T\
    \ x) const {\n            auto it = this->upper_bound(x);\n            return\
    \ it != this->begin() and x <= (--it)->second ? it : this->end();\n        }\n\
    \n        // returns whether `x` and `y` is in this set and in the same range.\
    \ O(log N)\n        bool in_the_same_range(T x, T y) const {\n            auto\
    \ it = get_containing_range(x);\n            return it != this->end() and it->first\
    \ <= y and y <= it->second;\n        }\n\n        // inserts the range [x, x]\
    \ and returns the number of integers inserted to this set. O(log N)\n        T\
    \ insert(T x) {\n            return insert(x, x);\n        }\n        \n     \
    \   // inserts the range [l, r] and returns the number of integers inserted to\
    \ this set. amortized O(log N)\n        T insert(T l, T r) {\n            if (l\
    \ > r) return 0;\n            auto it = this->upper_bound(l);\n            if\
    \ (it != this->begin() and is_mergeable(std::prev(it)->second, l)) {\n       \
    \         it = std::prev(it);\n                l = std::min(l, it->first);\n \
    \           }\n            T inserted = 0;\n            for (; it != this->end()\
    \ and is_mergeable(r, it->first); it = std::map<T, T>::erase(it)) {\n        \
    \        auto [cl, cr] = *it; \n                r = std::max(r, cr);\n       \
    \         inserted -= cr - cl + 1;\n            }\n            inserted += r -\
    \ l + 1;\n            (*this)[l] = r;\n            _size += inserted;\n      \
    \      return inserted;\n        }\n\n        // erases the range [x, x] and returns\
    \ the number of intergers erased from this set. O(log N)\n        T erase(T x)\
    \ {\n            return erase(x, x);\n        }\n\n        // erases the range\
    \ [l, r] and returns the number of intergers erased from this set. amortized O(log\
    \ N)\n        T erase(T l, T r) {\n            if (l > r) return 0;\n        \
    \    T tl = l, tr = r;\n            auto it = this->upper_bound(l);\n        \
    \    if (it != this->begin() and l <= std::prev(it)->second) {\n             \
    \   it = std::prev(it);\n                tl = it->first;\n            }\n    \
    \        T erased = 0;\n            for (; it != this->end() and it->first <=\
    \ r; it = std::map<T, T>::erase(it)) {\n                auto [cl, cr] = *it;\n\
    \                tr = cr;\n                erased += cr - cl + 1;\n          \
    \  }\n            if (tl < l) {\n                (*this)[tl] = l - 1;\n      \
    \          erased -= l - tl;\n            }\n            if (r < tr) {\n     \
    \           (*this)[r + 1] = tr;\n                erased -= tr - r;\n        \
    \    }\n            _size -= erased;\n            return erased;\n        }\n\n\
    \        // returns minimum integer x s.t. x >= lower and x is NOT in this set\n\
    \        T minimum_excluded(T lower = 0) const {\n            static_assert(merge_adjacent_segment);\n\
    \            auto it = find_range(lower);\n            return it == this->end()\
    \ ? lower : it->second + 1;\n        }\n\n    private:\n        T _size;\n\n \
    \       bool is_mergeable(T cur_r, T next_l) {\n            return next_l <= cur_r\
    \ + merge_adjacent_segment;\n        }\n};\n\n} // namespace suisen\n\n#endif\
    \ // SUISEN_RANGE_SET\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/range_set.hpp
  requiredBy: []
  timestamp: '2021-09-21 22:07:20+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/util/range_set/yuki674.test.cpp
  - test/src/util/range_set/past6_m.test.cpp
  - test/src/util/range_set/DSL_4_A.test.cpp
  - test/src/util/range_set/DSL_2_D.test.cpp
documentation_of: library/util/range_set.hpp
layout: document
redirect_from:
- /library/library/util/range_set.hpp
- /library/library/util/range_set.hpp.html
title: library/util/range_set.hpp
---
