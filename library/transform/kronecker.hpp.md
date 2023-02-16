---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  - icon: ':warning:'
    path: library/util/step_view.hpp
    title: library/util/step_view.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/kronecker.hpp\"\n\n\n\n#include <cassert>\n\
    #include <type_traits>\n#include <vector>\n\n#line 1 \"library/util/step_view.hpp\"\
    \n\n\n\n#include <iterator>\n\nnamespace suisen {\n    template <typename RandomAccessIterator>\n\
    \    struct StepIterator {\n        using difference_type   = typename std::iterator_traits<RandomAccessIterator>::difference_type;\n\
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
    \        std::size_t _size;\n    };\n} // namespace suisen\n\n\n\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 10 \"library/transform/kronecker.hpp\"\n\nnamespace suisen::kronecker_transform\
    \ {\n    namespace internal {\n        int log(int d, int n) {\n            int\
    \ l = 0, p = 1;\n            while (p < n) p *= d, ++l;\n            assert(p\
    \ == n);\n            return l;\n        }\n    }\n    // trans: (dimension id,\
    \ std::vector<T>&) -> void\n    template <typename T, typename Transform, std::enable_if_t<std::is_invocable_v<Transform,\
    \ int, StepView<std::vector<T>>>, std::nullptr_t> = nullptr>\n    void transform(std::vector<T>&\
    \ f, const std::vector<int>& dims, const Transform& trans) {\n        const int\
    \ n = f.size(), m = dims.size();\n        {\n            int p = 1;\n        \
    \    for (int d : dims) p *= d;\n            assert(p == n);\n        }\n    \
    \    for (int i = 0, block = 1; i < m; ++i) {\n            const int next_block\
    \ = block * dims[i];\n            for (int l = 0; l < n; l += next_block) {\n\
    \                for (int offset = l; offset < l + block; ++offset) {\n      \
    \              trans(i, StepView{ f, offset, block, dims[i] });\n            \
    \    }\n            }\n            block = next_block;\n        }\n    }\n   \
    \ // trans: (std::vector<T>&) -> void\n    template <typename T, typename Transform,\
    \ std::enable_if_t<std::is_invocable_v<Transform, StepView<std::vector<T>>>, std::nullptr_t>\
    \ = nullptr>\n    void transform(std::vector<T>& f, int d, const Transform& trans)\
    \ {\n        transform(f, std::vector<int>(internal::log(d, f.size()), d), [&trans](int,\
    \ StepView<std::vector<T>> view) { trans(view); });\n    }\n\n    template <typename\
    \ T, auto add = default_operator::add<T>>\n    void sub_zeta(std::vector<T>& f,\
    \ const std::vector<int>& dims) {\n        transform(\n            f, dims, [&](int,\
    \ const StepView<std::vector<T>>& f) {\n                for (size_t i = 1; i <\
    \ f.size(); ++i) f[i] = add(f[i], f[i - 1]);\n            }\n        );\n    }\n\
    \    template <typename T, auto add = default_operator::add<T>>\n    void sub_zeta(std::vector<T>&\
    \ f, int d) {\n        sub_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void sub_mobius(std::vector<T>& f, const std::vector<int>& dims) {\n    \
    \    transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = f.size() - 1; i > 0; --i) f[i] = sub(f[i],\
    \ f[i - 1]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ sub = default_operator::sub<T>>\n    void sub_mobius(std::vector<T>& f, int\
    \ d) {\n        sub_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n\n    template <typename T, auto add = default_operator::add<T>>\n\
    \    void sup_zeta(std::vector<T>& f, const std::vector<int>& dims) {\n      \
    \  transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = f.size() - 1; i > 0; --i) f[i - 1] = add(f[i\
    \ - 1], f[i]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ add = default_operator::add<T>>\n    void sup_zeta(std::vector<T>& f, int d)\
    \ {\n        sup_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void sup_mobius(std::vector<T>& f, const std::vector<int>& dims) {\n    \
    \    transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = 1; i < f.size(); ++i) f[i - 1] = sub(f[i\
    \ - 1], f[i]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ sub = default_operator::sub<T>>\n    void sup_mobius(std::vector<T>& f, int\
    \ d) {\n        sup_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n} // namespace suisen::kronecker_transform\n\n\n\n"
  code: "#ifndef SUISEN_KRONECKER_TRANSFORM\n#define SUISEN_KRONECKER_TRANSFORM\n\n\
    #include <cassert>\n#include <type_traits>\n#include <vector>\n\n#include \"library/util/step_view.hpp\"\
    \n#include \"library/util/default_operator.hpp\"\n\nnamespace suisen::kronecker_transform\
    \ {\n    namespace internal {\n        int log(int d, int n) {\n            int\
    \ l = 0, p = 1;\n            while (p < n) p *= d, ++l;\n            assert(p\
    \ == n);\n            return l;\n        }\n    }\n    // trans: (dimension id,\
    \ std::vector<T>&) -> void\n    template <typename T, typename Transform, std::enable_if_t<std::is_invocable_v<Transform,\
    \ int, StepView<std::vector<T>>>, std::nullptr_t> = nullptr>\n    void transform(std::vector<T>&\
    \ f, const std::vector<int>& dims, const Transform& trans) {\n        const int\
    \ n = f.size(), m = dims.size();\n        {\n            int p = 1;\n        \
    \    for (int d : dims) p *= d;\n            assert(p == n);\n        }\n    \
    \    for (int i = 0, block = 1; i < m; ++i) {\n            const int next_block\
    \ = block * dims[i];\n            for (int l = 0; l < n; l += next_block) {\n\
    \                for (int offset = l; offset < l + block; ++offset) {\n      \
    \              trans(i, StepView{ f, offset, block, dims[i] });\n            \
    \    }\n            }\n            block = next_block;\n        }\n    }\n   \
    \ // trans: (std::vector<T>&) -> void\n    template <typename T, typename Transform,\
    \ std::enable_if_t<std::is_invocable_v<Transform, StepView<std::vector<T>>>, std::nullptr_t>\
    \ = nullptr>\n    void transform(std::vector<T>& f, int d, const Transform& trans)\
    \ {\n        transform(f, std::vector<int>(internal::log(d, f.size()), d), [&trans](int,\
    \ StepView<std::vector<T>> view) { trans(view); });\n    }\n\n    template <typename\
    \ T, auto add = default_operator::add<T>>\n    void sub_zeta(std::vector<T>& f,\
    \ const std::vector<int>& dims) {\n        transform(\n            f, dims, [&](int,\
    \ const StepView<std::vector<T>>& f) {\n                for (size_t i = 1; i <\
    \ f.size(); ++i) f[i] = add(f[i], f[i - 1]);\n            }\n        );\n    }\n\
    \    template <typename T, auto add = default_operator::add<T>>\n    void sub_zeta(std::vector<T>&\
    \ f, int d) {\n        sub_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void sub_mobius(std::vector<T>& f, const std::vector<int>& dims) {\n    \
    \    transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = f.size() - 1; i > 0; --i) f[i] = sub(f[i],\
    \ f[i - 1]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ sub = default_operator::sub<T>>\n    void sub_mobius(std::vector<T>& f, int\
    \ d) {\n        sub_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n\n    template <typename T, auto add = default_operator::add<T>>\n\
    \    void sup_zeta(std::vector<T>& f, const std::vector<int>& dims) {\n      \
    \  transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = f.size() - 1; i > 0; --i) f[i - 1] = add(f[i\
    \ - 1], f[i]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ add = default_operator::add<T>>\n    void sup_zeta(std::vector<T>& f, int d)\
    \ {\n        sup_zeta<T, add>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void sup_mobius(std::vector<T>& f, const std::vector<int>& dims) {\n    \
    \    transform(\n            f, dims,\n            [&](int, const StepView<std::vector<T>>&\
    \ f) {\n                for (size_t i = 1; i < f.size(); ++i) f[i - 1] = sub(f[i\
    \ - 1], f[i]);\n            }\n        );\n    }\n    template <typename T, auto\
    \ sub = default_operator::sub<T>>\n    void sup_mobius(std::vector<T>& f, int\
    \ d) {\n        sup_mobius<T, sub>(f, std::vector<int>(internal::log(d, f.size()),\
    \ d));\n    }\n} // namespace suisen::kronecker_transform\n\n\n#endif // SUISEN_KRONECKER_TRANSFORM\n"
  dependsOn:
  - library/util/step_view.hpp
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/transform/kronecker.hpp
  requiredBy: []
  timestamp: '2023-02-16 15:43:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/transform/kronecker.hpp
layout: document
redirect_from:
- /library/library/transform/kronecker.hpp
- /library/library/transform/kronecker.hpp.html
title: library/transform/kronecker.hpp
---
