---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/util/range_set.hpp
    title: library/datastructure/util/range_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/674
    links:
    - https://yukicoder.me/problems/no/674
  bundledCode: "#line 1 \"test/src/datastructure/util/range_set/yuki674.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/674\"\n\n#include <iostream>\n\
    \n#line 1 \"library/datastructure/util/range_set.hpp\"\n\n\n\n#include <map>\n\
    \nnamespace suisen {\n\ntemplate <typename T, bool merge_adjacent_segment = true>\n\
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
    \ ? lower : it->second + 1;\n        }\n\n        // returns maximum integer x\
    \ s.t. x <= upper and x is NOT in this set\n        T maximum_excluded(T upper)\
    \ const {\n            static_assert(merge_adjacent_segment);\n            auto\
    \ it = find_range(upper);\n            return it == this->end() ? upper : it->first\
    \ - 1;\n        }\n\n    private:\n        T _size;\n\n        bool is_mergeable(T\
    \ cur_r, T next_l) {\n            return next_l <= cur_r + merge_adjacent_segment;\n\
    \        }\n};\n\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/util/range_set/yuki674.test.cpp\"\
    \nusing suisen::RangeSet;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    long long d;\n    int q;\n    std::cin >> d >>\
    \ q;\n\n    long long ans = 0;\n    RangeSet<long long> set;\n    while (q -->\
    \ 0) {\n        long long l, r;\n        std::cin >> l >> r;\n        set.insert(l,\
    \ r);\n        auto [nl, nr] = *set.find_range(l);\n        ans = std::max(ans,\
    \ nr - nl + 1);\n        std::cout << ans << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/674\"\n\n#include <iostream>\n\
    \n#include \"library/datastructure/util/range_set.hpp\"\nusing suisen::RangeSet;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    long long d;\n    int q;\n    std::cin >> d >> q;\n\n    long long ans =\
    \ 0;\n    RangeSet<long long> set;\n    while (q --> 0) {\n        long long l,\
    \ r;\n        std::cin >> l >> r;\n        set.insert(l, r);\n        auto [nl,\
    \ nr] = *set.find_range(l);\n        ans = std::max(ans, nr - nl + 1);\n     \
    \   std::cout << ans << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/util/range_set.hpp
  isVerificationFile: true
  path: test/src/datastructure/util/range_set/yuki674.test.cpp
  requiredBy: []
  timestamp: '2022-04-10 03:29:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/util/range_set/yuki674.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/util/range_set/yuki674.test.cpp
- /verify/test/src/datastructure/util/range_set/yuki674.test.cpp.html
title: test/src/datastructure/util/range_set/yuki674.test.cpp
---
