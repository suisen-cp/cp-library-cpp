---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/util/priority_sum/agc018_c.test.cpp
    title: test/src/datastructure/util/priority_sum/agc018_c.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/util/priority_sum.hpp\"\n\n\n\n#include\
    \ <queue>\n#include <utility>\n\nnamespace suisen {\n    namespace internal::priority_sum\
    \ {\n        template <typename T, typename Comparator, typename RevComparator>\n\
    \        struct PrioritySum {\n            using value_type = T;\n           \
    \ using comparator_type = Comparator;\n            using reverse_comparator_type\
    \ = RevComparator;\n\n            PrioritySum() : PrioritySum(0) {}\n        \
    \    PrioritySum(int k) : _k(k), _sum(0), _cmp(), _rev_cmp(), _head_k(_cmp), _del_head_k(_cmp),\
    \ _tail(_rev_cmp), _del_tail(_rev_cmp) {}\n\n            value_type get_sum()\
    \ const {\n                return _sum;\n            }\n\n            void insert(const\
    \ value_type &v) {\n                _sum += v;\n                _head_k.push(v);\n\
    \                fix();\n            }\n\n            void erase(const value_type\
    \ &v) {\n                if (_head_k.size() and v == _head_k.top()) {\n      \
    \              _sum -= v;\n                    _head_k.pop();\n              \
    \  } else if (_head_k.size() and _rev_cmp(v, _head_k.top())) {\n             \
    \       _sum -= v;\n                    _del_head_k.push(v);\n               \
    \ } else {\n                    _del_tail.push(v);\n                }\n      \
    \          fix();\n            }\n\n            int get_k() const { return _k;\
    \ }\n\n            void set_k(int new_k) { _k = new_k, fix(); }\n            void\
    \ incr_k() { set_k(get_k() + 1); }\n            void decr_k() { set_k(get_k()\
    \ - 1); }\n\n            int size() const {\n                return int((_head_k.size()\
    \ + _tail.size()) - (_del_head_k.size() + _del_tail.size()));\n            }\n\
    \n        private:\n            int _k;\n            value_type _sum;\n      \
    \      comparator_type _cmp;\n            reverse_comparator_type _rev_cmp;\n\
    \            std::priority_queue<value_type, std::vector<value_type>, comparator_type>\
    \ _head_k, _del_head_k;\n            std::priority_queue<value_type, std::vector<value_type>,\
    \ reverse_comparator_type> _tail, _del_tail;\n\n            void fix() {\n   \
    \             while (int(_head_k.size() - _del_head_k.size()) < _k and _tail.size())\
    \ {\n                    value_type v = std::move(_tail.top());\n            \
    \        _tail.pop();\n                    if (_del_tail.size() and _del_tail.top()\
    \ == v) {\n                        _del_tail.pop();\n                    } else\
    \ {\n                        _sum += v;\n                        _head_k.push(std::move(v));\n\
    \                    }\n                }\n                while (int(_head_k.size()\
    \ - _del_head_k.size()) > _k) {\n                    value_type v = std::move(_head_k.top());\n\
    \                    _head_k.pop();\n                    if (_del_head_k.size()\
    \ and _del_head_k.top() == v) {\n                        _del_head_k.pop();\n\
    \                    } else {\n                        _sum -= v;\n          \
    \              _tail.push(std::move(v));\n                    }\n            \
    \    }\n            }\n        };\n    } // internal::priority_sum\n\n    template\
    \ <typename T>\n    using MaximumPrioritySum = internal::priority_sum::PrioritySum<T,\
    \ std::less<T>, std::greater<T>>;\n    template <typename T>\n    using MinimumPrioritySum\
    \ = internal::priority_sum::PrioritySum<T, std::greater<T>, std::less<T>>;\n}\
    \ // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_PRIORITY_SUM\n#define SUISEN_PRIORITY_SUM\n\n#include <queue>\n\
    #include <utility>\n\nnamespace suisen {\n    namespace internal::priority_sum\
    \ {\n        template <typename T, typename Comparator, typename RevComparator>\n\
    \        struct PrioritySum {\n            using value_type = T;\n           \
    \ using comparator_type = Comparator;\n            using reverse_comparator_type\
    \ = RevComparator;\n\n            PrioritySum() : PrioritySum(0) {}\n        \
    \    PrioritySum(int k) : _k(k), _sum(0), _cmp(), _rev_cmp(), _head_k(_cmp), _del_head_k(_cmp),\
    \ _tail(_rev_cmp), _del_tail(_rev_cmp) {}\n\n            value_type get_sum()\
    \ const {\n                return _sum;\n            }\n\n            void insert(const\
    \ value_type &v) {\n                _sum += v;\n                _head_k.push(v);\n\
    \                fix();\n            }\n\n            void erase(const value_type\
    \ &v) {\n                if (_head_k.size() and v == _head_k.top()) {\n      \
    \              _sum -= v;\n                    _head_k.pop();\n              \
    \  } else if (_head_k.size() and _rev_cmp(v, _head_k.top())) {\n             \
    \       _sum -= v;\n                    _del_head_k.push(v);\n               \
    \ } else {\n                    _del_tail.push(v);\n                }\n      \
    \          fix();\n            }\n\n            int get_k() const { return _k;\
    \ }\n\n            void set_k(int new_k) { _k = new_k, fix(); }\n            void\
    \ incr_k() { set_k(get_k() + 1); }\n            void decr_k() { set_k(get_k()\
    \ - 1); }\n\n            int size() const {\n                return int((_head_k.size()\
    \ + _tail.size()) - (_del_head_k.size() + _del_tail.size()));\n            }\n\
    \n        private:\n            int _k;\n            value_type _sum;\n      \
    \      comparator_type _cmp;\n            reverse_comparator_type _rev_cmp;\n\
    \            std::priority_queue<value_type, std::vector<value_type>, comparator_type>\
    \ _head_k, _del_head_k;\n            std::priority_queue<value_type, std::vector<value_type>,\
    \ reverse_comparator_type> _tail, _del_tail;\n\n            void fix() {\n   \
    \             while (int(_head_k.size() - _del_head_k.size()) < _k and _tail.size())\
    \ {\n                    value_type v = std::move(_tail.top());\n            \
    \        _tail.pop();\n                    if (_del_tail.size() and _del_tail.top()\
    \ == v) {\n                        _del_tail.pop();\n                    } else\
    \ {\n                        _sum += v;\n                        _head_k.push(std::move(v));\n\
    \                    }\n                }\n                while (int(_head_k.size()\
    \ - _del_head_k.size()) > _k) {\n                    value_type v = std::move(_head_k.top());\n\
    \                    _head_k.pop();\n                    if (_del_head_k.size()\
    \ and _del_head_k.top() == v) {\n                        _del_head_k.pop();\n\
    \                    } else {\n                        _sum -= v;\n          \
    \              _tail.push(std::move(v));\n                    }\n            \
    \    }\n            }\n        };\n    } // internal::priority_sum\n\n    template\
    \ <typename T>\n    using MaximumPrioritySum = internal::priority_sum::PrioritySum<T,\
    \ std::less<T>, std::greater<T>>;\n    template <typename T>\n    using MinimumPrioritySum\
    \ = internal::priority_sum::PrioritySum<T, std::greater<T>, std::less<T>>;\n}\
    \ // namespace suisen\n\n\n#endif // SUISEN_PRIORITY_SUM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/util/priority_sum.hpp
  requiredBy: []
  timestamp: '2022-04-10 03:30:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/util/priority_sum/agc018_c.test.cpp
documentation_of: library/datastructure/util/priority_sum.hpp
layout: document
redirect_from:
- /library/library/datastructure/util/priority_sum.hpp
- /library/library/datastructure/util/priority_sum.hpp.html
title: library/datastructure/util/priority_sum.hpp
---
