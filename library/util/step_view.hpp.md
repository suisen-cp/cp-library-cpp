---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/transform/kronecker.hpp
    title: library/transform/kronecker.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/step_view.hpp\"\n\n\n\n#include <iterator>\n\
    \nnamespace suisen {\n    template <typename RandomAccessIterator>\n    struct\
    \ StepIterator {\n        using difference_type   = typename std::iterator_traits<RandomAccessIterator>::difference_type;\n\
    \        using value_type        = typename std::iterator_traits<RandomAccessIterator>::value_type;\n\
    \        using pointer           = typename std::iterator_traits<RandomAccessIterator>::pointer;\n\
    \        using reference         = typename std::iterator_traits<RandomAccessIterator>::reference;\n\
    \        using iterator_category = typename std::iterator_traits<RandomAccessIterator>::iterator_category;\n\
    \        static_assert(std::is_same_v<iterator_category, std::random_access_iterator_tag>);\n\
    \n        StepIterator(const RandomAccessIterator &it, int step) : _it(it), _step(step)\
    \ {}\n        StepIterator& operator++() { return _it += _step, *this; }\n   \
    \     StepIterator& operator--() { return _it -= _step, *this; }\n        StepIterator\
    \ operator++(int) { StepIterator ret = *this; ++(*this); return ret; }\n     \
    \   StepIterator operator--(int) { StepIterator ret = *this; --(*this); return\
    \ ret; }\n        StepIterator& operator+=(difference_type dif) { return _it +=\
    \ dif * _step, *this; }\n        StepIterator& operator-=(difference_type dif)\
    \ { return _it -= dif * _step, *this; }\n        friend StepIterator operator+(StepIterator\
    \ it, difference_type dif) { it += dif; return it; }\n        friend StepIterator\
    \ operator+(difference_type dif, StepIterator it) { it += dif; return it; }\n\
    \        friend StepIterator operator-(StepIterator it, difference_type dif) {\
    \ it -= dif; return it; }\n        friend difference_type operator-(const StepIterator\
    \ &lhs, const StepIterator &rhs) { return (lhs._it - rhs._it) / lhs._step; }\n\
    \        reference operator[](difference_type i) const { return _it[i * _step];\
    \ }\n        reference operator*() const { return *_it; }\n        friend bool\
    \ operator==(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it\
    \ == rhs._it; }\n        friend bool operator!=(const StepIterator &lhs, const\
    \ StepIterator &rhs) { return lhs._it != rhs._it; }\n        friend bool operator<\
    \ (const StepIterator &lhs, const StepIterator &rhs) { return lhs._it <  rhs._it;\
    \ }\n        friend bool operator<=(const StepIterator &lhs, const StepIterator\
    \ &rhs) { return lhs._it <= rhs._it; }\n        friend bool operator> (const StepIterator\
    \ &lhs, const StepIterator &rhs) { return lhs._it >  rhs._it; }\n        friend\
    \ bool operator>=(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it\
    \ >= rhs._it; }\n    private:\n        RandomAccessIterator _it;\n        int\
    \ _step;\n    };\n\n    template <typename RandomAccesibleContainer>\n    struct\
    \ StepView {\n        using iterator   = typename RandomAccesibleContainer::iterator;\n\
    \        using value_type = typename RandomAccesibleContainer::value_type;\n \
    \       using reference  = typename RandomAccesibleContainer::reference;\n   \
    \     \n        StepView(RandomAccesibleContainer& dat, int start, int step, int\
    \ size) : _start(dat.begin() + start, step), _size(size) {}\n        std::size_t\
    \ size() const { return _size; }\n        reference operator[](std::size_t k)\
    \ const { return _start[k]; }\n    private:\n        StepIterator<iterator> _start;\n\
    \        std::size_t _size;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_STEP_VIEW\n#define SUISEN_STEP_VIEW\n\n#include <iterator>\n\
    \nnamespace suisen {\n    template <typename RandomAccessIterator>\n    struct\
    \ StepIterator {\n        using difference_type   = typename std::iterator_traits<RandomAccessIterator>::difference_type;\n\
    \        using value_type        = typename std::iterator_traits<RandomAccessIterator>::value_type;\n\
    \        using pointer           = typename std::iterator_traits<RandomAccessIterator>::pointer;\n\
    \        using reference         = typename std::iterator_traits<RandomAccessIterator>::reference;\n\
    \        using iterator_category = typename std::iterator_traits<RandomAccessIterator>::iterator_category;\n\
    \        static_assert(std::is_same_v<iterator_category, std::random_access_iterator_tag>);\n\
    \n        StepIterator(const RandomAccessIterator &it, int step) : _it(it), _step(step)\
    \ {}\n        StepIterator& operator++() { return _it += _step, *this; }\n   \
    \     StepIterator& operator--() { return _it -= _step, *this; }\n        StepIterator\
    \ operator++(int) { StepIterator ret = *this; ++(*this); return ret; }\n     \
    \   StepIterator operator--(int) { StepIterator ret = *this; --(*this); return\
    \ ret; }\n        StepIterator& operator+=(difference_type dif) { return _it +=\
    \ dif * _step, *this; }\n        StepIterator& operator-=(difference_type dif)\
    \ { return _it -= dif * _step, *this; }\n        friend StepIterator operator+(StepIterator\
    \ it, difference_type dif) { it += dif; return it; }\n        friend StepIterator\
    \ operator+(difference_type dif, StepIterator it) { it += dif; return it; }\n\
    \        friend StepIterator operator-(StepIterator it, difference_type dif) {\
    \ it -= dif; return it; }\n        friend difference_type operator-(const StepIterator\
    \ &lhs, const StepIterator &rhs) { return (lhs._it - rhs._it) / lhs._step; }\n\
    \        reference operator[](difference_type i) const { return _it[i * _step];\
    \ }\n        reference operator*() const { return *_it; }\n        friend bool\
    \ operator==(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it\
    \ == rhs._it; }\n        friend bool operator!=(const StepIterator &lhs, const\
    \ StepIterator &rhs) { return lhs._it != rhs._it; }\n        friend bool operator<\
    \ (const StepIterator &lhs, const StepIterator &rhs) { return lhs._it <  rhs._it;\
    \ }\n        friend bool operator<=(const StepIterator &lhs, const StepIterator\
    \ &rhs) { return lhs._it <= rhs._it; }\n        friend bool operator> (const StepIterator\
    \ &lhs, const StepIterator &rhs) { return lhs._it >  rhs._it; }\n        friend\
    \ bool operator>=(const StepIterator &lhs, const StepIterator &rhs) { return lhs._it\
    \ >= rhs._it; }\n    private:\n        RandomAccessIterator _it;\n        int\
    \ _step;\n    };\n\n    template <typename RandomAccesibleContainer>\n    struct\
    \ StepView {\n        using iterator   = typename RandomAccesibleContainer::iterator;\n\
    \        using value_type = typename RandomAccesibleContainer::value_type;\n \
    \       using reference  = typename RandomAccesibleContainer::reference;\n   \
    \     \n        StepView(RandomAccesibleContainer& dat, int start, int step, int\
    \ size) : _start(dat.begin() + start, step), _size(size) {}\n        std::size_t\
    \ size() const { return _size; }\n        reference operator[](std::size_t k)\
    \ const { return _start[k]; }\n    private:\n        StepIterator<iterator> _start;\n\
    \        std::size_t _size;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_STEP_VIEW\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/step_view.hpp
  requiredBy:
  - library/transform/kronecker.hpp
  timestamp: '2023-02-16 15:43:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/step_view.hpp
layout: document
redirect_from:
- /library/library/util/step_view.hpp
- /library/library/util/step_view.hpp.html
title: library/util/step_view.hpp
---
