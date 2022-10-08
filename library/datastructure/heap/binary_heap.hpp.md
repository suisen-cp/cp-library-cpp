---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/datastructure/heap/heap_tag.hpp
    title: Heap Tag
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/datastructure/priority_queue.hpp
    title: Priority Queue
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: O(n)
    links: []
  bundledCode: "#line 1 \"library/datastructure/heap/binary_heap.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"library/datastructure/heap/heap_tag.hpp\"\
    \n\n\n\n#line 5 \"library/datastructure/heap/heap_tag.hpp\"\n\nnamespace suisen\
    \ {\n    namespace internal::heap {\n        struct heap_tag_base {};\n    }\n\
    \    struct min_heap_tag : internal::heap::heap_tag_base {\n        static constexpr\
    \ bool is_min_heap = true;\n        static constexpr bool is_max_heap = false;\n\
    \    };\n    struct max_heap_tag : internal::heap::heap_tag_base {\n        static\
    \ constexpr bool is_min_heap = false;\n        static constexpr bool is_max_heap\
    \ = true;\n    };\n\n    template <typename T>\n    struct is_heap_tag {\n   \
    \     static constexpr bool value = std::is_base_of_v<internal::heap::heap_tag_base,\
    \ T>;\n    };\n    template <typename T>\n    constexpr bool is_heap_tag_v = is_heap_tag<T>::value;\n\
    } // namespace suisen\n\n\n\n#line 12 \"library/datastructure/heap/binary_heap.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::heap {\n        template <typename\
    \ T, typename Comp, typename HeapTag>\n        struct BinaryHeap {\n         \
    \   using value_type = T;\n            using compare_type = Comp;\n          \
    \  using heap_tag = HeapTag;\n\n            static constexpr bool is_min_heap\
    \ = heap_tag::is_min_heap;\n            static constexpr bool is_max_heap = heap_tag::is_max_heap;\n\
    \n            BinaryHeap() = default;\n            BinaryHeap(const Comp& comp)\
    \ : _comp(comp) {}\n\n            template <typename InputIterator>\n        \
    \    BinaryHeap(InputIterator first, InputIterator last) : _dat(first, last) {\n\
    \                construct_heap();\n            }\n            template <typename\
    \ InputIterator>\n            BinaryHeap(InputIterator first, InputIterator last,\
    \ const Comp& comp) : _dat(first, last), _comp(comp) {\n                construct_heap();\n\
    \            }\n\n            template <typename Iterable, typename = std::void_t<typename\
    \ Iterable::iterator>>\n            BinaryHeap(const Iterable& dat) : BinaryHeap(dat.begin(),\
    \ dat.end()) {}\n            template <typename Iterable, typename = std::void_t<typename\
    \ Iterable::iterator>>\n            BinaryHeap(const Iterable& dat, Comp& comp)\
    \ : BinaryHeap(dat.begin(), dat.end(), comp) {}\n\n            void reserve(int\
    \ capacity) { _dat.reserve(capacity); }\n\n            bool empty() const { return\
    \ _dat.empty(); }\n            int size() const { return _dat.size(); }\n\n  \
    \          void clear() { _dat.clear(); }\n            void shrink_to_fit() {\
    \ _dat.shrink_to_fit(); }\n\n            void push(const value_type& v) {\n  \
    \              _dat.push_back(v);\n                heapify_up(_dat.size() - 1);\n\
    \            }\n            template <typename ...Args>\n            void emplace(Args\
    \ &&...args) {\n                push(value_type(std::forward<Args>(args)...));\n\
    \            }\n\n            const value_type& top() const {\n              \
    \  assert(_dat.size());\n                return _dat.front();\n            }\n\
    \n            value_type pop() {\n                assert(_dat.size());\n     \
    \           // std::pop_heap(_dat.begin(), _dat.end(), [this](const value_type\
    \ &x, const value_type &y) { return compare(y, x); });\n                std::swap(_dat.front(),\
    \ _dat.back());\n                value_type res = std::move(_dat.back());\n  \
    \              _dat.pop_back();\n                heapify_down(0);\n          \
    \      return res;\n            }\n\n            const std::vector<value_type>&\
    \ data() const { return _dat; }\n            std::vector<value_type>& data() {\
    \ return _dat; }\n\n            // @brief O(n)\n            void construct_heap()\
    \ {\n                const int m = _dat.size() >> 1;\n                for (int\
    \ i = m - 1; i >= 0; --i) heapify_down(i);\n            }\n\n            // for\
    \ debug\n            void check_heap_property() const {\n                const\
    \ int n = _dat.size(), m = n >> 1;\n                for (int i = 0; i < m; ++i)\
    \ {\n                    const int lch = 2 * i + 1, rch = 2 * i + 2;\n       \
    \             if (lch < n) assert(not compare(_dat[lch], _dat[i]));\n        \
    \            if (rch < n) assert(not compare(_dat[rch], _dat[i]));\n         \
    \       }\n            }\n\n        private:\n            std::vector<value_type>\
    \ _dat;\n            compare_type _comp;\n\n            void heapify_up(const\
    \ int leaf, const int root = 0) {\n                int cur = leaf;\n         \
    \       value_type val = std::move(_dat[cur]);\n                while (cur !=\
    \ root) {\n                    int par = (cur - 1) >> 1;\n                   \
    \ if (not compare(val, _dat[par])) break;\n                    _dat[std::exchange(cur,\
    \ par)] = std::move(_dat[par]);\n                }\n                _dat[cur]\
    \ = std::move(val);\n            }\n            void heapify_down(const int root)\
    \ {\n                const int n = _dat.size(), m = n >> 1;\n                int\
    \ cur = root;\n                value_type val = std::move(_dat[cur]);\n      \
    \          while (cur < m) {\n                    int ch = (cur << 1) + 1;\n \
    \                   ch += ch + 1 < n and compare(_dat[ch + 1], _dat[ch]);\n  \
    \                  if (not compare(_dat[ch], val)) break;\n                  \
    \  _dat[cur] = std::move(_dat[ch]);\n                    cur = ch;\n         \
    \       }\n                _dat[cur] = std::move(val);\n                // heapify_up(cur,\
    \ root);\n            }\n\n            bool compare(const T& lhs, const T& rhs)\
    \ const {\n                if constexpr (is_min_heap) {\n                    return\
    \ _comp(lhs, rhs);\n                } else {\n                    return _comp(rhs,\
    \ lhs);\n                }\n            }\n        };\n    }\n    template <\n\
    \        typename T, typename Comp = std::less<T>,\n        std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Comp, T, T>, std::nullptr_t> = nullptr\n    >\n    using MinBinaryHeap = internal::heap::BinaryHeap<T,\
    \ Comp, min_heap_tag>;\n    template <\n        typename T, typename Comp = std::less<T>,\n\
    \        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t>\
    \ = nullptr\n    >\n    using MaxBinaryHeap = internal::heap::BinaryHeap<T, Comp,\
    \ max_heap_tag>;\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BINARY_HEAP\n#define SUISEN_BINARY_HEAP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"library/datastructure/heap/heap_tag.hpp\"\n\n\
    namespace suisen {\n    namespace internal::heap {\n        template <typename\
    \ T, typename Comp, typename HeapTag>\n        struct BinaryHeap {\n         \
    \   using value_type = T;\n            using compare_type = Comp;\n          \
    \  using heap_tag = HeapTag;\n\n            static constexpr bool is_min_heap\
    \ = heap_tag::is_min_heap;\n            static constexpr bool is_max_heap = heap_tag::is_max_heap;\n\
    \n            BinaryHeap() = default;\n            BinaryHeap(const Comp& comp)\
    \ : _comp(comp) {}\n\n            template <typename InputIterator>\n        \
    \    BinaryHeap(InputIterator first, InputIterator last) : _dat(first, last) {\n\
    \                construct_heap();\n            }\n            template <typename\
    \ InputIterator>\n            BinaryHeap(InputIterator first, InputIterator last,\
    \ const Comp& comp) : _dat(first, last), _comp(comp) {\n                construct_heap();\n\
    \            }\n\n            template <typename Iterable, typename = std::void_t<typename\
    \ Iterable::iterator>>\n            BinaryHeap(const Iterable& dat) : BinaryHeap(dat.begin(),\
    \ dat.end()) {}\n            template <typename Iterable, typename = std::void_t<typename\
    \ Iterable::iterator>>\n            BinaryHeap(const Iterable& dat, Comp& comp)\
    \ : BinaryHeap(dat.begin(), dat.end(), comp) {}\n\n            void reserve(int\
    \ capacity) { _dat.reserve(capacity); }\n\n            bool empty() const { return\
    \ _dat.empty(); }\n            int size() const { return _dat.size(); }\n\n  \
    \          void clear() { _dat.clear(); }\n            void shrink_to_fit() {\
    \ _dat.shrink_to_fit(); }\n\n            void push(const value_type& v) {\n  \
    \              _dat.push_back(v);\n                heapify_up(_dat.size() - 1);\n\
    \            }\n            template <typename ...Args>\n            void emplace(Args\
    \ &&...args) {\n                push(value_type(std::forward<Args>(args)...));\n\
    \            }\n\n            const value_type& top() const {\n              \
    \  assert(_dat.size());\n                return _dat.front();\n            }\n\
    \n            value_type pop() {\n                assert(_dat.size());\n     \
    \           // std::pop_heap(_dat.begin(), _dat.end(), [this](const value_type\
    \ &x, const value_type &y) { return compare(y, x); });\n                std::swap(_dat.front(),\
    \ _dat.back());\n                value_type res = std::move(_dat.back());\n  \
    \              _dat.pop_back();\n                heapify_down(0);\n          \
    \      return res;\n            }\n\n            const std::vector<value_type>&\
    \ data() const { return _dat; }\n            std::vector<value_type>& data() {\
    \ return _dat; }\n\n            // @brief O(n)\n            void construct_heap()\
    \ {\n                const int m = _dat.size() >> 1;\n                for (int\
    \ i = m - 1; i >= 0; --i) heapify_down(i);\n            }\n\n            // for\
    \ debug\n            void check_heap_property() const {\n                const\
    \ int n = _dat.size(), m = n >> 1;\n                for (int i = 0; i < m; ++i)\
    \ {\n                    const int lch = 2 * i + 1, rch = 2 * i + 2;\n       \
    \             if (lch < n) assert(not compare(_dat[lch], _dat[i]));\n        \
    \            if (rch < n) assert(not compare(_dat[rch], _dat[i]));\n         \
    \       }\n            }\n\n        private:\n            std::vector<value_type>\
    \ _dat;\n            compare_type _comp;\n\n            void heapify_up(const\
    \ int leaf, const int root = 0) {\n                int cur = leaf;\n         \
    \       value_type val = std::move(_dat[cur]);\n                while (cur !=\
    \ root) {\n                    int par = (cur - 1) >> 1;\n                   \
    \ if (not compare(val, _dat[par])) break;\n                    _dat[std::exchange(cur,\
    \ par)] = std::move(_dat[par]);\n                }\n                _dat[cur]\
    \ = std::move(val);\n            }\n            void heapify_down(const int root)\
    \ {\n                const int n = _dat.size(), m = n >> 1;\n                int\
    \ cur = root;\n                value_type val = std::move(_dat[cur]);\n      \
    \          while (cur < m) {\n                    int ch = (cur << 1) + 1;\n \
    \                   ch += ch + 1 < n and compare(_dat[ch + 1], _dat[ch]);\n  \
    \                  if (not compare(_dat[ch], val)) break;\n                  \
    \  _dat[cur] = std::move(_dat[ch]);\n                    cur = ch;\n         \
    \       }\n                _dat[cur] = std::move(val);\n                // heapify_up(cur,\
    \ root);\n            }\n\n            bool compare(const T& lhs, const T& rhs)\
    \ const {\n                if constexpr (is_min_heap) {\n                    return\
    \ _comp(lhs, rhs);\n                } else {\n                    return _comp(rhs,\
    \ lhs);\n                }\n            }\n        };\n    }\n    template <\n\
    \        typename T, typename Comp = std::less<T>,\n        std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Comp, T, T>, std::nullptr_t> = nullptr\n    >\n    using MinBinaryHeap = internal::heap::BinaryHeap<T,\
    \ Comp, min_heap_tag>;\n    template <\n        typename T, typename Comp = std::less<T>,\n\
    \        std::enable_if_t<std::is_invocable_r_v<bool, Comp, T, T>, std::nullptr_t>\
    \ = nullptr\n    >\n    using MaxBinaryHeap = internal::heap::BinaryHeap<T, Comp,\
    \ max_heap_tag>;\n} // namespace suisen\n\n\n#endif // SUISEN_BINARY_HEAP\n"
  dependsOn:
  - library/datastructure/heap/heap_tag.hpp
  isVerificationFile: false
  path: library/datastructure/heap/binary_heap.hpp
  requiredBy:
  - library/datastructure/priority_queue.hpp
  timestamp: '2022-09-29 21:45:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/heap/binary_heap.hpp
layout: document
title: Binary Heap
---
## Binary Heap