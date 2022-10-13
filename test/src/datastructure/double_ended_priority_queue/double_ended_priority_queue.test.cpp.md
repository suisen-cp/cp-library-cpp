---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/double_ended_priority_queue.hpp
    title: Double Ended Priority Queue
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/double_ended_priority_queue
    links:
    - https://judge.yosupo.jp/problem/double_ended_priority_queue
  bundledCode: "#line 1 \"test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/double_ended_priority_queue.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n#include\
    \ <functional>\n#include <utility>\n\nnamespace suisen {\n    template <typename\
    \ T, typename Comp = std::less<T>>\n    struct DoubleEndedPriorityQueue {\n  \
    \      using value_type = T;\n        using compare_type = Comp;\n\n        DoubleEndedPriorityQueue()\
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
    \   value_type pop() { return pop_max(); }\n\n        std::vector<value_type>\
    \ dump_sorted() const {\n            std::vector<value_type> res_l(_min_heap),\
    \ res_r(_max_heap);\n            std::sort(res_l.begin(), res_l.end(), _comp);\n\
    \            std::sort(res_r.begin(), res_r.end(), _comp);\n            res_l.reserve(size());\n\
    \            std::copy(res_r.begin(), res_r.end(), std::back_inserter(res_l));\n\
    \            return res_l;\n        }\n\n    private:\n        compare_type _comp;\n\
    \        struct {\n            compare_type* comp;\n            bool operator()(const\
    \ value_type& x, const value_type& y) { return (*comp)(y, x); }\n        } _rev_comp{\
    \ &_comp };\n\n        std::vector<value_type> _max_heap, _min_heap;\n       \
    \ value_type pivot;\n\n        void ensure_min_heap_nonempty() {\n           \
    \ const int siz = size();\n            assert(siz);\n            if (not _min_heap.empty())\
    \ return;\n            if (siz == 1) {\n                std::swap(_min_heap, _max_heap);\n\
    \                pivot = _min_heap.front();\n            } else {\n          \
    \      const int mid = (siz + 1) >> 1;\n                std::nth_element(_max_heap.begin(),\
    \ _max_heap.begin() + mid - 1, _max_heap.end(), _comp);\n                pivot\
    \ = _max_heap[mid - 1];\n                _min_heap.reserve(mid);\n           \
    \     std::move(_max_heap.begin(), _max_heap.begin() + mid, std::back_inserter(_min_heap));\n\
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
    \ suisen\n\n\n\n#line 6 \"test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> init(n);\n  \
    \  for (auto &e : init) std::cin >> e;\n    suisen::DoubleEndedPriorityQueue<int>\
    \ pq(init.begin(), init.end());\n\n    for (int i = 0; i < q; ++i) {\n       \
    \ int query_type;\n        std::cin >> query_type;\n        if (query_type ==\
    \ 0) {\n            int x;\n            std::cin >> x;\n            pq.push(x);\n\
    \        } else if (query_type == 1) {\n            std::cout << pq.pop_min()\
    \ << '\\n';\n        } else {\n            std::cout << pq.pop_max() << '\\n';\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/double_ended_priority_queue.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> init(n);\n  \
    \  for (auto &e : init) std::cin >> e;\n    suisen::DoubleEndedPriorityQueue<int>\
    \ pq(init.begin(), init.end());\n\n    for (int i = 0; i < q; ++i) {\n       \
    \ int query_type;\n        std::cin >> query_type;\n        if (query_type ==\
    \ 0) {\n            int x;\n            std::cin >> x;\n            pq.push(x);\n\
    \        } else if (query_type == 1) {\n            std::cout << pq.pop_min()\
    \ << '\\n';\n        } else {\n            std::cout << pq.pop_max() << '\\n';\n\
    \        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/double_ended_priority_queue.hpp
  isVerificationFile: true
  path: test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp
  requiredBy: []
  timestamp: '2022-10-13 20:07:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp
- /verify/test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp.html
title: test/src/datastructure/double_ended_priority_queue/double_ended_priority_queue.test.cpp
---
