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
  bundledCode: "#line 1 \"library/datastructure/heap/interval_heap.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n#include <functional>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace suisen {\n    template <\n        typename T,\
    \ typename Comp = std::less<T>,\n        std::enable_if_t<std::is_invocable_r_v<bool,\
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
    \n\n\n"
  code: "#ifndef SUISEN_INTERVAL_HEAP\n#define SUISEN_INTERVAL_HEAP\n\n#include <cassert>\n\
    #include <vector>\n#include <functional>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace suisen {\n    template <\n        typename T, typename Comp = std::less<T>,\n\
    \        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t>\
    \ = nullptr\n    >\n    struct IntervalHeap {\n        using value_type = T;\n\
    \n        IntervalHeap() {}\n        IntervalHeap(const Comp& comp) : _comp(comp)\
    \ {}\n\n        void reserve(int capacity) { _dat.reserve(capacity); }\n\n   \
    \     bool empty() const { return _dat.empty(); }\n        int size() const {\
    \ return _dat.size(); }\n\n        void push(const value_type& v) {\n        \
    \    _dat.push_back(v);\n            fix_up(_dat.size() - 1);\n        }\n   \
    \     template <typename ...Args>\n        void emplace(Args &&...args) {\n  \
    \          push(value_type(std::forward<Args>(args)...));\n        }\n\n     \
    \   const value_type& max() const {\n            assert(_dat.size());\n      \
    \      return _dat[max_heap_top_index()];\n        }\n        const value_type&\
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
    \n\n#endif // SUISEN_INTERVAL_HEAP\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/heap/interval_heap.hpp
  requiredBy: []
  timestamp: '2022-09-29 21:45:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/heap/interval_heap.hpp
layout: document
redirect_from:
- /library/library/datastructure/heap/interval_heap.hpp
- /library/library/datastructure/heap/interval_heap.hpp.html
title: library/datastructure/heap/interval_heap.hpp
---
