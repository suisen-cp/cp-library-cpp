---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/heap/interval_heap.hpp
    title: Interval Heap
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
  bundledCode: "#line 1 \"test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/heap/interval_heap.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n#include <functional>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace suisen {\n    template <\n  \
    \      typename T, typename Comp = std::less<T>,\n        std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Comp, T, T>, std::nullptr_t> = nullptr\n    >\n    struct IntervalHeap {\n \
    \       using value_type = T;\n\n        IntervalHeap() {}\n        IntervalHeap(const\
    \ Comp& comp) : _comp(comp) {}\n\n        void reserve(int capacity) { _dat.reserve(capacity);\
    \ }\n\n        bool empty() const { return _dat.empty(); }\n        int size()\
    \ const { return _dat.size(); }\n\n        void push(const value_type& v) {\n\
    \            _dat.push_back(v);\n            fix_up(_dat.size() - 1);\n      \
    \  }\n        template <typename ...Args>\n        void emplace(Args &&...args)\
    \ {\n            push(value_type(std::forward<Args>(args)...));\n        }\n\n\
    \        const value_type& max() const {\n            assert(_dat.size());\n \
    \           return _dat[max_heap_top_index()];\n        }\n        const value_type&\
    \ min() const {\n            assert(_dat.size());\n            return _dat[min_heap_top_index()];\n\
    \        }\n\n        value_type pop_max() {\n            assert(_dat.size());\n\
    \            const int idx = max_heap_top_index();\n            std::swap(_dat[idx],\
    \ _dat.back());\n            value_type res = std::move(_dat.back());\n      \
    \      _dat.pop_back();\n            fix_max_heap_down(idx);\n            return\
    \ res;\n        }\n        value_type pop_min() {\n            assert(_dat.size());\n\
    \            const int idx = min_heap_top_index();\n            std::swap(_dat[idx],\
    \ _dat.back());\n            value_type res = std::move(_dat.back());\n      \
    \      _dat.pop_back();\n            fix_min_heap_down(idx);\n            return\
    \ res;\n        }\n        const auto& data() const { return _dat; }\n       \
    \ auto &data() { return _dat; }\n\n        // for debug\n        void check_heap_property()\
    \ const {\n            const int siz = size();\n            for (int i = 0; i\
    \ < siz; ++i) {\n                if (i % 2 == 0) {\n                    int lch\
    \ = min_heap_child_l(i), rch = min_heap_child_r(i);\n                    if (lch\
    \ < siz) assert(not _comp(_dat[lch], _dat[i]));\n                    if (rch <\
    \ siz) assert(not _comp(_dat[rch], _dat[i]));\n                    if (i + 1 <\
    \ siz) assert(not _comp(_dat[i + 1], _dat[i]));\n                } else {\n  \
    \                  int lch = max_heap_child_l(i), rch = max_heap_child_r(i);\n\
    \                    lch -= lch >= siz, rch -= rch >= siz;\n                 \
    \   if (lch < siz) assert(not _comp(_dat[i], _dat[lch]));\n                  \
    \  if (rch < siz) assert(not _comp(_dat[i], _dat[rch]));\n                }\n\
    \            }\n        }\n    private:\n        // even : min_heap, odd : max_heap\n\
    \        std::vector<value_type> _dat;\n        Comp _comp;\n\n        int min_heap_top_index()\
    \ const { return 0; }\n        int max_heap_top_index() const { return _dat.size()\
    \ >= 2; }\n\n        void fix_up(int idx) {\n            if (const int l = idx\
    \ & ~0b1, r = l | 1; r < int(_dat.size())) {\n                if (_comp(_dat[r],\
    \ _dat[l])) std::swap(_dat[l], _dat[r]), idx ^= 1;\n                fix_min_heap_up(l),\
    \ fix_max_heap_up(r);\n            } else {\n                fix_min_heap_up(l),\
    \ fix_max_heap_up(l);\n            }\n        }\n        void fix_min_heap_up(int\
    \ idx) {\n            while (idx >= 2) {\n                if (int par = min_heap_parent(idx);\
    \ _comp(_dat[idx], _dat[par])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);\n\
    \                else return;\n            }\n        }\n        void fix_max_heap_up(int\
    \ idx) {\n            while (idx >= 2) {\n                if (int par = max_heap_parent(idx);\
    \ _comp(_dat[par], _dat[idx])) std::swap(_dat[std::exchange(idx, par)], _dat[par]);\n\
    \                else return;\n            }\n        }\n        void fix_min_heap_down(int\
    \ idx) {\n            const int siz = _dat.size();\n            while (true) {\n\
    \                int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);\n\
    \                if (lch >= siz) {\n                    fix_up(idx);\n       \
    \             break;\n                }\n                int ch = rch < siz and\
    \ _comp(_dat[rch], _dat[lch]) ? rch : lch;\n                if (_comp(_dat[ch],\
    \ _dat[idx])) std::swap(_dat[std::exchange(idx, ch)], _dat[ch]);\n           \
    \     else break;\n            }\n        }\n        void fix_max_heap_down(int\
    \ idx) {\n            const int siz = _dat.size();\n            while (true) {\n\
    \                int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);\n\
    \                lch -= lch >= siz, rch -= rch >= siz;\n                if (lch\
    \ >= siz) {\n                    fix_up(idx);\n                    break;\n  \
    \              }\n                int ch = rch < siz and _comp(_dat[lch], _dat[rch])\
    \ ? rch : lch;\n                if (_comp(_dat[idx], _dat[ch])) std::swap(_dat[std::exchange(idx,\
    \ ch)], _dat[ch]);\n                else break;\n            }\n        }\n\n\
    \        static constexpr int min_heap_parent(int idx) { return (idx - 2) >> 2\
    \ << 1; }\n        static constexpr int max_heap_parent(int idx) { return min_heap_parent(idx)\
    \ | 1; }\n        static constexpr int min_heap_child_l(int idx) { return (idx\
    \ + 1) << 1; }\n        static constexpr int min_heap_child_r(int idx) { return\
    \ (idx + 2) << 1; }\n        static constexpr int max_heap_child_l(int idx) {\
    \ return min_heap_child_l(idx - 1) | 1; }\n        static constexpr int max_heap_child_r(int\
    \ idx) { return min_heap_child_r(idx - 1) | 1; }\n    };\n} // namespace suisen\n\
    \n\n\n#line 6 \"test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    suisen::IntervalHeap<int> pq;\n\
    \    for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n \
    \       pq.push(v);\n    }\n\n    for (int i = 0; i < q; ++i) {\n        int query_type;\n\
    \        std::cin >> query_type;\n        if (query_type == 0) {\n           \
    \ int x;\n            std::cin >> x;\n            pq.push(x);\n        } else\
    \ if (query_type == 1) {\n            std::cout << pq.pop_min() << '\\n';\n  \
    \      } else {\n            std::cout << pq.pop_max() << '\\n';\n        }\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/heap/interval_heap.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    suisen::IntervalHeap<int> pq;\n\
    \    for (int i = 0; i < n; ++i) {\n        int v;\n        std::cin >> v;\n \
    \       pq.push(v);\n    }\n\n    for (int i = 0; i < q; ++i) {\n        int query_type;\n\
    \        std::cin >> query_type;\n        if (query_type == 0) {\n           \
    \ int x;\n            std::cin >> x;\n            pq.push(x);\n        } else\
    \ if (query_type == 1) {\n            std::cout << pq.pop_min() << '\\n';\n  \
    \      } else {\n            std::cout << pq.pop_max() << '\\n';\n        }\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/heap/interval_heap.hpp
  isVerificationFile: true
  path: test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp
  requiredBy: []
  timestamp: '2022-10-13 20:07:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp
- /verify/test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp.html
title: test/src/datastructure/heap/interval_heap/double_ended_priority_queue.test.cpp
---
