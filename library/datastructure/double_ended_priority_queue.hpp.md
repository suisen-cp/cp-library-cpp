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
  bundledCode: "#line 1 \"library/datastructure/double_ended_priority_queue.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n#include <functional>\n\
    #include <utility>\n\nnamespace suisen {\n    template <typename T, typename Comp\
    \ = std::less<T>>\n    struct DoubleEndedPriorityQueue {\n        using value_type\
    \ = T;\n        using compare_type = Comp;\n\n        DoubleEndedPriorityQueue()\
    \ = default;\n        DoubleEndedPriorityQueue(const Comp& comp) : _comp(comp)\
    \ {}\n\n        template <typename InputIterator>\n        DoubleEndedPriorityQueue(InputIterator\
    \ first, InputIterator last) : _max_heap(first, last) {\n            std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n        }\n        template <typename InputIterator>\n\
    \        DoubleEndedPriorityQueue(InputIterator first, InputIterator last, const\
    \ Comp& comp) : _comp(comp), _max_heap(first, last) {\n            std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n        }\n\n        template <typename Iterable,\
    \ typename = std::void_t<typename Iterable::iterator>>\n        DoubleEndedPriorityQueue(const\
    \ Iterable& dat) : DoubleEndedPriorityQueue(dat.begin(), dat.end()) {}\n     \
    \   template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>\n\
    \        DoubleEndedPriorityQueue(const Iterable& dat, Comp& comp) : DoubleEndedPriorityQueue(dat.begin(),\
    \ dat.end(), comp) {}\n\n        bool empty() const { return size() == 0; }\n\
    \        int size() const { return _min_heap.size() + _max_heap.size(); }\n\n\
    \        void push(const value_type& v) {\n            if (_min_heap.empty() or\
    \ _comp(pivot, v)) {\n                _max_heap.push_back(v);\n              \
    \  std::push_heap(_max_heap.begin(), _max_heap.end(), _comp);\n            } else\
    \ {\n                _min_heap.push_back(v);\n                std::push_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            }\n        }\n        template <typename\
    \ ...Args>\n        void emplace(Args &&...args) { push(value_type(std::forward<Args>(args)...));\
    \ }\n\n        const value_type& max() const {\n            assert(size());\n\
    \            return _max_heap.size() ? _max_heap.front() : pivot;\n        }\n\
    \        const value_type& min() {\n            ensure_min_heap_nonempty();\n\
    \            return _min_heap.front();\n        }\n        const value_type& top()\
    \ const { return max(); }\n\n        value_type pop_max() {\n            ensure_max_heap_nonempty();\n\
    \            std::pop_heap(_max_heap.begin(), _max_heap.end(), _comp);\n     \
    \       value_type res = std::move(_max_heap.back());\n            _max_heap.pop_back();\n\
    \            return res;\n        }\n        value_type pop_min() {\n        \
    \    ensure_min_heap_nonempty();\n            std::pop_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            value_type res = std::move(_min_heap.back());\n\
    \            _min_heap.pop_back();\n            return res;\n        }\n     \
    \   value_type pop() { return pop_max(); }\n\n    private:\n        compare_type\
    \ _comp;\n        std::vector<value_type> _max_heap, _min_heap;\n        value_type\
    \ pivot;\n\n        struct {\n            compare_type* _comp;\n            bool\
    \ operator()(const value_type& x, const value_type& y) { return (*_comp)(y, x);\
    \ }\n        } _rev_comp{ &_comp };\n\n        void ensure_min_heap_nonempty()\
    \ {\n            const int siz = size();\n            assert(siz);\n         \
    \   if (not _min_heap.empty()) return;\n            if (siz == 1) {\n        \
    \        std::swap(_min_heap, _max_heap);\n                pivot = _min_heap.front();\n\
    \            } else {\n                const int mid = (siz + 1) >> 1;\n     \
    \           std::nth_element(_max_heap.begin(), _max_heap.begin() + mid - 1, _max_heap.end(),\
    \ _comp);\n                pivot = _max_heap[mid - 1];\n                _min_heap.reserve(mid);\n\
    \                std::move(_max_heap.begin(), _max_heap.begin() + mid, std::back_inserter(_min_heap));\n\
    \                _max_heap.erase(_max_heap.begin(), _max_heap.begin() + mid);\n\
    \                std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);\n\
    \                std::make_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);\n\
    \            }\n        }\n        void ensure_max_heap_nonempty() {\n       \
    \     const int siz = size();\n            assert(siz);\n            if (not _max_heap.empty())\
    \ return;\n            if (siz == 1) {\n                std::swap(_min_heap, _max_heap);\n\
    \            } else {\n                const int mid = siz >> 1;\n           \
    \     std::nth_element(_min_heap.begin(), _min_heap.begin() + mid - 1, _min_heap.end(),\
    \ _comp);\n                pivot = _min_heap[mid - 1];\n                _max_heap.reserve(siz\
    \ - mid);\n                std::move(_min_heap.begin() + mid, _min_heap.end(),\
    \ std::back_inserter(_max_heap));\n                _min_heap.erase(_min_heap.begin()\
    \ + mid, _min_heap.end());\n                std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n                std::make_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n#define SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n#include <functional>\n\
    #include <utility>\n\nnamespace suisen {\n    template <typename T, typename Comp\
    \ = std::less<T>>\n    struct DoubleEndedPriorityQueue {\n        using value_type\
    \ = T;\n        using compare_type = Comp;\n\n        DoubleEndedPriorityQueue()\
    \ = default;\n        DoubleEndedPriorityQueue(const Comp& comp) : _comp(comp)\
    \ {}\n\n        template <typename InputIterator>\n        DoubleEndedPriorityQueue(InputIterator\
    \ first, InputIterator last) : _max_heap(first, last) {\n            std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n        }\n        template <typename InputIterator>\n\
    \        DoubleEndedPriorityQueue(InputIterator first, InputIterator last, const\
    \ Comp& comp) : _comp(comp), _max_heap(first, last) {\n            std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n        }\n\n        template <typename Iterable,\
    \ typename = std::void_t<typename Iterable::iterator>>\n        DoubleEndedPriorityQueue(const\
    \ Iterable& dat) : DoubleEndedPriorityQueue(dat.begin(), dat.end()) {}\n     \
    \   template <typename Iterable, typename = std::void_t<typename Iterable::iterator>>\n\
    \        DoubleEndedPriorityQueue(const Iterable& dat, Comp& comp) : DoubleEndedPriorityQueue(dat.begin(),\
    \ dat.end(), comp) {}\n\n        bool empty() const { return size() == 0; }\n\
    \        int size() const { return _min_heap.size() + _max_heap.size(); }\n\n\
    \        void push(const value_type& v) {\n            if (_min_heap.empty() or\
    \ _comp(pivot, v)) {\n                _max_heap.push_back(v);\n              \
    \  std::push_heap(_max_heap.begin(), _max_heap.end(), _comp);\n            } else\
    \ {\n                _min_heap.push_back(v);\n                std::push_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            }\n        }\n        template <typename\
    \ ...Args>\n        void emplace(Args &&...args) { push(value_type(std::forward<Args>(args)...));\
    \ }\n\n        const value_type& max() const {\n            assert(size());\n\
    \            return _max_heap.size() ? _max_heap.front() : pivot;\n        }\n\
    \        const value_type& min() {\n            ensure_min_heap_nonempty();\n\
    \            return _min_heap.front();\n        }\n        const value_type& top()\
    \ const { return max(); }\n\n        value_type pop_max() {\n            ensure_max_heap_nonempty();\n\
    \            std::pop_heap(_max_heap.begin(), _max_heap.end(), _comp);\n     \
    \       value_type res = std::move(_max_heap.back());\n            _max_heap.pop_back();\n\
    \            return res;\n        }\n        value_type pop_min() {\n        \
    \    ensure_min_heap_nonempty();\n            std::pop_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            value_type res = std::move(_min_heap.back());\n\
    \            _min_heap.pop_back();\n            return res;\n        }\n     \
    \   value_type pop() { return pop_max(); }\n\n    private:\n        compare_type\
    \ _comp;\n        std::vector<value_type> _max_heap, _min_heap;\n        value_type\
    \ pivot;\n\n        struct {\n            compare_type* _comp;\n            bool\
    \ operator()(const value_type& x, const value_type& y) { return (*_comp)(y, x);\
    \ }\n        } _rev_comp{ &_comp };\n\n        void ensure_min_heap_nonempty()\
    \ {\n            const int siz = size();\n            assert(siz);\n         \
    \   if (not _min_heap.empty()) return;\n            if (siz == 1) {\n        \
    \        std::swap(_min_heap, _max_heap);\n                pivot = _min_heap.front();\n\
    \            } else {\n                const int mid = (siz + 1) >> 1;\n     \
    \           std::nth_element(_max_heap.begin(), _max_heap.begin() + mid - 1, _max_heap.end(),\
    \ _comp);\n                pivot = _max_heap[mid - 1];\n                _min_heap.reserve(mid);\n\
    \                std::move(_max_heap.begin(), _max_heap.begin() + mid, std::back_inserter(_min_heap));\n\
    \                _max_heap.erase(_max_heap.begin(), _max_heap.begin() + mid);\n\
    \                std::make_heap(_max_heap.begin(), _max_heap.end(), _comp);\n\
    \                std::make_heap(_min_heap.begin(), _min_heap.end(), _rev_comp);\n\
    \            }\n        }\n        void ensure_max_heap_nonempty() {\n       \
    \     const int siz = size();\n            assert(siz);\n            if (not _max_heap.empty())\
    \ return;\n            if (siz == 1) {\n                std::swap(_min_heap, _max_heap);\n\
    \            } else {\n                const int mid = siz >> 1;\n           \
    \     std::nth_element(_min_heap.begin(), _min_heap.begin() + mid - 1, _min_heap.end(),\
    \ _comp);\n                pivot = _min_heap[mid - 1];\n                _max_heap.reserve(siz\
    \ - mid);\n                std::move(_min_heap.begin() + mid, _min_heap.end(),\
    \ std::back_inserter(_max_heap));\n                _min_heap.erase(_min_heap.begin()\
    \ + mid, _min_heap.end());\n                std::make_heap(_max_heap.begin(),\
    \ _max_heap.end(), _comp);\n                std::make_heap(_min_heap.begin(),\
    \ _min_heap.end(), _rev_comp);\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/double_ended_priority_queue.hpp
  requiredBy: []
  timestamp: '2022-09-29 21:45:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/double_ended_priority_queue.hpp
layout: document
redirect_from:
- /library/library/datastructure/double_ended_priority_queue.hpp
- /library/library/datastructure/double_ended_priority_queue.hpp.html
title: library/datastructure/double_ended_priority_queue.hpp
---
