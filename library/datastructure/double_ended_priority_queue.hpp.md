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
    \n\n\n#include <cassert>\n#include <vector>\n#include <functional>\n\nnamespace\
    \ suisen {\n    template <typename T, typename Comp = std::less<T>>\n    struct\
    \ DoubleEndedPriorityQueue {\n        DoubleEndedPriorityQueue() {}\n        DoubleEndedPriorityQueue(const\
    \ Comp& comp) : _comp(comp) {}\n\n        void push(const T& v) {\n          \
    \  _dat.push_back(v);\n            fix_up(_dat.size() - 1);\n        }\n     \
    \   template <typename ...Args>\n        void emplace(Args &&...args) {\n    \
    \        push(T(std::forward<Args>(args)...));\n        }\n\n        const T&\
    \ max() const {\n            assert(_dat.size());\n            return _dat[_dat.size()\
    \ >= 2];\n        }\n        const T& min() const {\n            assert(_dat.size());\n\
    \            return _dat[0];\n        }\n\n        T pop_max() {\n           \
    \ assert(_dat.size());\n            int idx = _dat.size() >= 2;\n            T\
    \ res = std::move(_dat[idx]);\n            if (_dat.size() == 1) {\n         \
    \       _dat.pop_back();\n                return res;\n            }\n       \
    \     _dat[idx] = std::move(_dat.back());\n            _dat.pop_back();\n\n  \
    \          const int siz = _dat.size();\n            while (true) {\n        \
    \        int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);\n     \
    \           lch -= lch >= siz;\n                rch -= rch >= siz;\n         \
    \       if (lch >= siz) {\n                    fix_up(idx);\n                \
    \    break;\n                }\n                int ch = rch < siz and _comp(_dat[lch],\
    \ _dat[rch]) ? rch : lch;\n                if (_comp(_dat[idx], _dat[ch])) {\n\
    \                    std::swap(_dat[idx], _dat[ch]);\n                    idx\
    \ = ch;\n                } else break;\n            }\n            return res;\n\
    \        }\n        T pop_min() {\n            assert(_dat.size());\n        \
    \    int idx = 0;\n            T res = std::move(_dat[idx]);\n            if (_dat.size()\
    \ == 1) {\n                _dat.pop_back();\n                return res;\n   \
    \         }\n            _dat[idx] = std::move(_dat.back());\n            _dat.pop_back();\n\
    \n            const int siz = _dat.size();\n            while (true) {\n     \
    \           int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);\n  \
    \              if (lch >= siz) {\n                    fix_up(idx);\n         \
    \           break;\n                }\n                int ch = rch < siz and\
    \ _comp(_dat[rch], _dat[lch]) ? rch : lch;\n                if (_comp(_dat[ch],\
    \ _dat[idx])) {\n                    std::swap(_dat[idx], _dat[ch]);\n       \
    \             idx = ch;\n                } else break;\n            }\n      \
    \      return res;\n        }\n\n        const std::vector<T>& data() const {\n\
    \            return _dat;\n        }\n    private:\n        // even : min_heap\n\
    \        // odd  : max_heap\n        std::vector<T> _dat;\n        Comp _comp;\n\
    \n        void fix_up(int idx) {\n            int l = idx & ~0b1, r = l | 1;\n\
    \            if (r < int(_dat.size())) {\n                if (_comp(_dat[r], _dat[l]))\
    \ {\n                    std::swap(_dat[l], _dat[r]);\n                    idx\
    \ ^= 1;\n                }\n                fix_min_heap_up(l), fix_max_heap_up(r);\n\
    \            } else {\n                fix_min_heap_up(l), fix_max_heap_up(l);\n\
    \            }\n        }\n        void fix_min_heap_up(int idx) {\n         \
    \   while (idx >= 2) {\n                int par = min_heap_parent(idx);\n    \
    \            if (_comp(_dat[idx], _dat[par])) {\n                    std::swap(_dat[idx],\
    \ _dat[par]);\n                    idx = par;\n                } else return;\n\
    \            }\n        }\n        void fix_max_heap_up(int idx) {\n         \
    \   while (idx >= 2) {\n                int par = max_heap_parent(idx);\n    \
    \            if (_comp(_dat[par], _dat[idx])) {\n                    std::swap(_dat[idx],\
    \ _dat[par]);\n                    idx = par;\n                } else return;\n\
    \            }\n        }\n\n        static constexpr int min_heap_parent(int\
    \ idx) {\n            return (idx - 2) >> 2 << 1;\n        }\n        static constexpr\
    \ int max_heap_parent(int idx) {\n            return min_heap_parent(idx) | 1;\n\
    \        }\n        static constexpr int min_heap_child_l(int idx) {\n       \
    \     return (idx + 1) << 1;\n        }\n        static constexpr int min_heap_child_r(int\
    \ idx) {\n            return (idx + 2) << 1;\n        }\n        static constexpr\
    \ int max_heap_child_l(int idx) {\n            return min_heap_child_l(idx - 1)\
    \ | 1;\n        }\n        static constexpr int max_heap_child_r(int idx) {\n\
    \            return min_heap_child_r(idx - 1) | 1;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n#define SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n\
    \n#include <cassert>\n#include <vector>\n#include <functional>\n\nnamespace suisen\
    \ {\n    template <typename T, typename Comp = std::less<T>>\n    struct DoubleEndedPriorityQueue\
    \ {\n        DoubleEndedPriorityQueue() {}\n        DoubleEndedPriorityQueue(const\
    \ Comp& comp) : _comp(comp) {}\n\n        void push(const T& v) {\n          \
    \  _dat.push_back(v);\n            fix_up(_dat.size() - 1);\n        }\n     \
    \   template <typename ...Args>\n        void emplace(Args &&...args) {\n    \
    \        push(T(std::forward<Args>(args)...));\n        }\n\n        const T&\
    \ max() const {\n            assert(_dat.size());\n            return _dat[_dat.size()\
    \ >= 2];\n        }\n        const T& min() const {\n            assert(_dat.size());\n\
    \            return _dat[0];\n        }\n\n        T pop_max() {\n           \
    \ assert(_dat.size());\n            int idx = _dat.size() >= 2;\n            T\
    \ res = std::move(_dat[idx]);\n            if (_dat.size() == 1) {\n         \
    \       _dat.pop_back();\n                return res;\n            }\n       \
    \     _dat[idx] = std::move(_dat.back());\n            _dat.pop_back();\n\n  \
    \          const int siz = _dat.size();\n            while (true) {\n        \
    \        int lch = max_heap_child_l(idx), rch = max_heap_child_r(idx);\n     \
    \           lch -= lch >= siz;\n                rch -= rch >= siz;\n         \
    \       if (lch >= siz) {\n                    fix_up(idx);\n                \
    \    break;\n                }\n                int ch = rch < siz and _comp(_dat[lch],\
    \ _dat[rch]) ? rch : lch;\n                if (_comp(_dat[idx], _dat[ch])) {\n\
    \                    std::swap(_dat[idx], _dat[ch]);\n                    idx\
    \ = ch;\n                } else break;\n            }\n            return res;\n\
    \        }\n        T pop_min() {\n            assert(_dat.size());\n        \
    \    int idx = 0;\n            T res = std::move(_dat[idx]);\n            if (_dat.size()\
    \ == 1) {\n                _dat.pop_back();\n                return res;\n   \
    \         }\n            _dat[idx] = std::move(_dat.back());\n            _dat.pop_back();\n\
    \n            const int siz = _dat.size();\n            while (true) {\n     \
    \           int lch = min_heap_child_l(idx), rch = min_heap_child_r(idx);\n  \
    \              if (lch >= siz) {\n                    fix_up(idx);\n         \
    \           break;\n                }\n                int ch = rch < siz and\
    \ _comp(_dat[rch], _dat[lch]) ? rch : lch;\n                if (_comp(_dat[ch],\
    \ _dat[idx])) {\n                    std::swap(_dat[idx], _dat[ch]);\n       \
    \             idx = ch;\n                } else break;\n            }\n      \
    \      return res;\n        }\n\n        const std::vector<T>& data() const {\n\
    \            return _dat;\n        }\n    private:\n        // even : min_heap\n\
    \        // odd  : max_heap\n        std::vector<T> _dat;\n        Comp _comp;\n\
    \n        void fix_up(int idx) {\n            int l = idx & ~0b1, r = l | 1;\n\
    \            if (r < int(_dat.size())) {\n                if (_comp(_dat[r], _dat[l]))\
    \ {\n                    std::swap(_dat[l], _dat[r]);\n                    idx\
    \ ^= 1;\n                }\n                fix_min_heap_up(l), fix_max_heap_up(r);\n\
    \            } else {\n                fix_min_heap_up(l), fix_max_heap_up(l);\n\
    \            }\n        }\n        void fix_min_heap_up(int idx) {\n         \
    \   while (idx >= 2) {\n                int par = min_heap_parent(idx);\n    \
    \            if (_comp(_dat[idx], _dat[par])) {\n                    std::swap(_dat[idx],\
    \ _dat[par]);\n                    idx = par;\n                } else return;\n\
    \            }\n        }\n        void fix_max_heap_up(int idx) {\n         \
    \   while (idx >= 2) {\n                int par = max_heap_parent(idx);\n    \
    \            if (_comp(_dat[par], _dat[idx])) {\n                    std::swap(_dat[idx],\
    \ _dat[par]);\n                    idx = par;\n                } else return;\n\
    \            }\n        }\n\n        static constexpr int min_heap_parent(int\
    \ idx) {\n            return (idx - 2) >> 2 << 1;\n        }\n        static constexpr\
    \ int max_heap_parent(int idx) {\n            return min_heap_parent(idx) | 1;\n\
    \        }\n        static constexpr int min_heap_child_l(int idx) {\n       \
    \     return (idx + 1) << 1;\n        }\n        static constexpr int min_heap_child_r(int\
    \ idx) {\n            return (idx + 2) << 1;\n        }\n        static constexpr\
    \ int max_heap_child_l(int idx) {\n            return min_heap_child_l(idx - 1)\
    \ | 1;\n        }\n        static constexpr int max_heap_child_r(int idx) {\n\
    \            return min_heap_child_r(idx - 1) | 1;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_DOUBLE_ENDED_PRIORITY_QUEUE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/double_ended_priority_queue.hpp
  requiredBy: []
  timestamp: '2022-09-28 21:41:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/double_ended_priority_queue.hpp
layout: document
redirect_from:
- /library/library/datastructure/double_ended_priority_queue.hpp
- /library/library/datastructure/double_ended_priority_queue.hpp.html
title: library/datastructure/double_ended_priority_queue.hpp
---
