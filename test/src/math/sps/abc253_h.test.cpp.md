---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/count_spanning_trees.hpp
    title: "\u884C\u5217\u6728\u5B9A\u7406\u306B\u3088\u308B\u5168\u57DF\u6728\u306E\
      \u6570\u3048\u4E0A\u3052"
  - icon: ':heavy_check_mark:'
    path: library/linear_algebra/matrix.hpp
    title: Matrix
  - icon: ':heavy_check_mark:'
    path: library/math/factorial.hpp
    title: "\u968E\u4E57\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/inv_mods.hpp
    title: "\u9006\u5143\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: library/math/modint_extension.hpp
    title: Modint Extension
  - icon: ':heavy_check_mark:'
    path: library/math/sps.hpp
    title: Set Power Series
  - icon: ':heavy_check_mark:'
    path: library/polynomial/fps_naive.hpp
    title: "FFT-free \u306A\u5F62\u5F0F\u7684\u3079\u304D\u7D1A\u6570"
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  - icon: ':heavy_check_mark:'
    path: library/util/subset_iterator.hpp
    title: Subset Iterator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc253/tasks/abc253_Ex
    links:
    - https://atcoder.jp/contests/abc253/tasks/abc253_Ex
  bundledCode: "#line 1 \"test/src/math/sps/abc253_h.test.cpp\"\n#define PROBLEM \"\
    https://atcoder.jp/contests/abc253/tasks/abc253_Ex\"\n\n#include <iostream>\n\n\
    #include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\n#line 1 \"\
    library/util/subset_iterator.hpp\"\n\n\n\n#ifdef _MSC_VER\n#  include <intrin.h>\n\
    #else\n#  include <x86intrin.h>\n#endif\n\n#include <cassert>\n#include <cstdint>\n\
    #line 13 \"library/util/subset_iterator.hpp\"\n#include <limits>\n\nnamespace\
    \ suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct all_subset {\n        struct all_subset_iter\
    \ {\n            const T s; T t;\n            constexpr all_subset_iter(T s) :\
    \ s(s), t(s + 1) {}\n            constexpr auto operator*() const { return t;\
    \ }\n            constexpr auto operator++() {}\n            constexpr auto operator!=(std::nullptr_t)\
    \ { return t ? (--t &= s, true) : false; }\n        };\n        T s;\n       \
    \ constexpr all_subset(T s) : s(s) {}\n        constexpr auto begin() { return\
    \ all_subset_iter(s); }\n        constexpr auto end() { return nullptr; }\n  \
    \  };\n\n    // iterator over T s.t. T is subset of S and |T| = k\n    struct\
    \ all_subset_k {\n        struct all_subset_k_iter {\n            const uint32_t\
    \ n, k, s;\n            uint32_t t;\n            __attribute__((target(\"avx2\"\
    )))\n            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) <<\
    \ _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}\n            __attribute__((target(\"\
    bmi2\")))\n            auto operator*() const { return _pdep_u32(t, s); }\n  \
    \          __attribute__((target(\"bmi\")))\n            auto operator++() {\n\
    \                if (k == 0) {\n                    t = std::numeric_limits<uint32_t>::max();\n\
    \                } else {\n                    uint32_t y = t + _blsi_u32(t);\
    \ // t + (-t & t)\n                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n\
    \                }\n            }\n            auto operator!=(std::nullptr_t)\
    \ const { return t < n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t\
    \ s, uint32_t k) : s(s), k(k) {\n            assert(s != std::numeric_limits<uint32_t>::max());\n\
    \        }\n        auto begin() { return all_subset_k_iter(s, k); }\n       \
    \ auto end() { return nullptr; }\n    };\n\n    struct all_subset_k_64 {\n   \
    \     struct all_subset_k_iter_64 {\n            const uint64_t n, s;\n      \
    \      const uint32_t k;\n            uint64_t t;\n            __attribute__((target(\"\
    avx2\")))\n            all_subset_k_iter_64(uint64_t s, uint32_t k) : n(uint64_t(1)\
    \ << _mm_popcnt_u64(s)), s(s), k(k), t((uint64_t(1) << k) - 1) {}\n          \
    \  __attribute__((target(\"bmi2\")))\n            auto operator*() const { return\
    \ _pdep_u64(t, s); }\n            __attribute__((target(\"bmi\")))\n         \
    \   auto operator++() {\n                if (k == 0) {\n                    t\
    \ = std::numeric_limits<uint64_t>::max();\n                } else {\n        \
    \            uint64_t y = t + _blsi_u64(t);\n                    t = y | ((y ^\
    \ t) >> _tzcnt_u64(t << 2));\n                }\n            }\n            auto\
    \ operator!=(std::nullptr_t) const { return t < n; }\n        };\n        uint64_t\
    \ s;\n        uint32_t k;\n        all_subset_k_64(uint64_t s, uint32_t k) : s(s),\
    \ k(k) {\n            assert(s != std::numeric_limits<uint64_t>::max());\n   \
    \     }\n        auto begin() { return all_subset_k_iter_64(s, k); }\n       \
    \ auto end() { return nullptr; }\n    };\n\n    struct all_setbit {\n        struct\
    \ all_setbit_iter {\n            uint32_t s;\n            all_setbit_iter(uint32_t\
    \ s) : s(s) {}\n            __attribute__((target(\"bmi\")))\n            auto\
    \ operator*() { return _tzcnt_u32(s); }\n            __attribute__((target(\"\
    bmi\")))\n            auto operator++() { s = __blsr_u32(s); }\n            auto\
    \ operator!=(std::nullptr_t) { return s; }\n        };\n        uint32_t s;\n\
    \        all_setbit(uint32_t s) : s(s) {}\n        auto begin() { return all_setbit_iter(s);\
    \ }\n        auto end() { return nullptr; }\n    };\n\n    struct all_setbit_64\
    \ {\n        struct all_setbit_iter_64 {\n            uint64_t s;\n          \
    \  all_setbit_iter_64(uint64_t s) : s(s) {}\n            __attribute__((target(\"\
    bmi\")))\n            auto operator*() { return _tzcnt_u64(s); }\n           \
    \ __attribute__((target(\"bmi\")))\n            auto operator++() { s = __blsr_u64(s);\
    \ }\n            auto operator!=(std::nullptr_t) { return s; }\n        };\n \
    \       uint64_t s;\n        all_setbit_64(uint64_t s) : s(s) {}\n        auto\
    \ begin() { return all_setbit_iter_64(s); }\n        auto end() { return nullptr;\
    \ }\n    };\n} // namespace suisen\n\n\n#line 1 \"library/linear_algebra/count_spanning_trees.hpp\"\
    \n\n\n\n#line 1 \"library/linear_algebra/matrix.hpp\"\n\n\n\n#line 5 \"library/linear_algebra/matrix.hpp\"\
    \n#include <optional>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T>\n    struct Matrix {\n        std::vector<std::vector<T>> data;\n\n     \
    \   Matrix() {}\n        Matrix(int n, int m, T fill_value = T(0)) : data(n, std::vector<T>(m,\
    \ fill_value)) {}\n        Matrix(const std::vector<std::vector<T>>& data) noexcept\
    \ : data(data) {}\n        Matrix(std::vector<std::vector<T>>&& data) noexcept\
    \ : data(std::move(data)) {}\n        Matrix(const Matrix<T>& other) noexcept\
    \ : data(other.data) {}\n        Matrix(Matrix<T>&& other) noexcept : data(std::move(other.data))\
    \ {}\n\n        Matrix<T>& operator=(const Matrix<T>& other) noexcept {\n    \
    \        data = other.data;\n            return *this;\n        }\n        Matrix<T>&\
    \ operator=(Matrix<T>&& other) noexcept {\n            data = std::move(other.data);\n\
    \            return *this;\n        }\n\n        const std::vector<T>& operator[](int\
    \ i) const { return data[i]; }\n        std::vector<T>& operator[](int i) { return\
    \ data[i]; }\n\n        std::pair<int, int> size() const {\n            if (data.empty())\
    \ {\n                return { 0, 0 };\n            } else {\n                return\
    \ { data.size(), data[0].size() };\n            }\n        }\n        int row_size()\
    \ const {\n            return data.size();\n        }\n        int col_size()\
    \ const {\n            return data.empty() ? 0 : data[0].size();\n        }\n\n\
    \        Matrix<T>& operator+=(const Matrix<T>& other) {\n            assert(size()\
    \ == other.size());\n            auto [n, m] = size();\n            for (int i\
    \ = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n                data[i][j] +=\
    \ other[i][j];\n            }\n            return *this;\n        }\n        Matrix<T>&\
    \ operator-=(const Matrix<T>& other) {\n            assert(size() == other.size());\n\
    \            auto [n, m] = size();\n            for (int i = 0; i < n; ++i) for\
    \ (int j = 0; j < m; ++j) {\n                data[i][j] -= other[i][j];\n    \
    \        }\n            return *this;\n        }\n        Matrix<T>& operator*=(const\
    \ Matrix<T>& other) {\n            return *this = *this * other;\n        }\n\
    \        Matrix<T>& operator*=(const T& val) {\n            auto [n, m] = size();\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {\n     \
    \           data[i][j] *= val;\n            }\n            return *this;\n   \
    \     }\n        Matrix<T>& operator/=(const T& val) {\n            return *this\
    \ *= T(1) / val;\n        }\n        Matrix<T> operator+(const Matrix<T>& other)\
    \ const {\n            return Matrix<T>(*this) += other;\n        }\n        Matrix<T>\
    \ operator-(const Matrix<T>& other) const {\n            return Matrix<T>(*this)\
    \ -= other;\n        }\n        Matrix<T> operator*(const Matrix<T>& other) const\
    \ {\n            auto [n, m] = size();\n            auto [m2, l] = other.size();\n\
    \            assert(m == m2);\n            std::vector res(n, std::vector(l, T(0)));\n\
    \            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int\
    \ k = 0; k < l; ++k) {\n                res[i][k] += (*this)[i][j] * other[j][k];\n\
    \            }\n            return res;\n        }\n        Matrix<T> operator*(const\
    \ T& val) const {\n            return Matrix<T>(*this) *= val;\n        }\n  \
    \      Matrix<T> operator/(const T& val) const {\n            return Matrix<T>(*this)\
    \ /= val;\n        }\n\n        std::vector<T> operator*(const std::vector<T>&\
    \ x) const {\n            auto [n, m] = size();\n            assert(m == int(x.size()));\n\
    \            std::vector<T> b(n, T(0));\n            for (int i = 0; i < n; ++i)\
    \ for (int j = 0; j < m; ++j) {\n                b[i] += data[i][j] * x[j];\n\
    \            }\n            return b;\n        }\n    };\n\n    template <typename\
    \ T>\n    class SquareMatrix : public Matrix<T> {\n    public:\n        SquareMatrix()\
    \ {}\n        SquareMatrix(int n, T fill_value = T(0)) : Matrix<T>::Matrix(n,\
    \ n, fill_value) {}\n        SquareMatrix(const std::vector<std::vector<T>>& data)\
    \ : Matrix<T>::Matrix(data) {\n            auto [n, m] = this->size();\n     \
    \       assert(n == m);\n        }\n        SquareMatrix(std::vector<std::vector<T>>&&\
    \ data) : Matrix<T>::Matrix(std::move(data)) {\n            auto [n, m] = this->size();\n\
    \            assert(n == m);\n        }\n        SquareMatrix(const SquareMatrix<T>&\
    \ other) : SquareMatrix(other.data) {}\n        SquareMatrix(SquareMatrix<T>&&\
    \ other) : SquareMatrix(std::move(other.data)) {}\n        SquareMatrix(const\
    \ Matrix<T>& other) : Matrix<T>::Matrix(other.data) {}\n        SquareMatrix(Matrix<T>&&\
    \ other) : Matrix<T>::Matrix(std::move(other.data)) {}\n\n        SquareMatrix<T>&\
    \ operator=(const SquareMatrix<T>& other) noexcept {\n            this->data =\
    \ other.data;\n            return *this;\n        }\n        SquareMatrix<T>&\
    \ operator=(SquareMatrix<T>&& other) noexcept {\n            this->data = std::move(other.data);\n\
    \            return *this;\n        }\n\n        bool operator==(const SquareMatrix<T>&\
    \ other) noexcept {\n            return this->data == other.data;\n        }\n\
    \        bool operator!=(const SquareMatrix<T>& other) noexcept {\n          \
    \  return this->data != other.data;\n        }\n\n        static SquareMatrix<T>\
    \ e0(int n) { return SquareMatrix<T>(n, false); }\n        static SquareMatrix<T>\
    \ e1(int n) { return SquareMatrix<T>(n, true); }\n\n        static std::optional<SquareMatrix<T>>\
    \ inv(SquareMatrix<T>&& A) {\n            auto& data = A.data;\n            int\
    \ n = data.size();\n            for (int i = 0; i < n; ++i) {\n              \
    \  data[i].resize(2 * n, T{ 0 });\n                data[i][n + i] = T{ 1 };\n\
    \            }\n            for (int i = 0; i < n; ++i) {\n                int\
    \ pivot = -1;\n                for (int k = i; k < n; ++k) {\n               \
    \     if (data[k][i] != T{ 0 }) {\n                        pivot = k;\n      \
    \                  break;\n                    }\n                }\n        \
    \        if (pivot < 0) return std::nullopt;\n                data[i].swap(data[pivot]);\n\
    \                T coef = T{ 1 } / data[i][i];\n                for (int j = i;\
    \ j < 2 * n; ++j) data[i][j] *= coef;\n                for (int k = 0; k < n;\
    \ ++k) {\n                    if (k == i or data[k][i] == T{ 0 }) continue;\n\
    \                    T c = data[k][i];\n                    for (int j = i; j\
    \ < 2 * n; ++j) data[k][j] -= c * data[i][j];\n                }\n           \
    \ }\n            for (auto& row : data) row.erase(row.begin(), row.begin() + n);\n\
    \            return std::make_optional(std::move(A));\n        }\n        static\
    \ std::optional<SquareMatrix<T>> inv(const SquareMatrix<T>& A) {\n           \
    \ return SquareMatrix<T>::inv(SquareMatrix<T>(A));\n        }\n        static\
    \ T det(SquareMatrix<T>&& A) {\n            auto& data = A.data;\n           \
    \ T det_inv = T{ 1 };\n            int n = data.size();\n            for (int\
    \ i = 0; i < n; ++i) {\n                int pivot = -1;\n                for (int\
    \ k = i; k < n; ++k) {\n                    if (data[k][i] != T{ 0 }) {\n    \
    \                    pivot = k;\n                        break;\n            \
    \        }\n                }\n                if (pivot < 0) return T{ 0 };\n\
    \                data[i].swap(data[pivot]);\n                if (pivot != i) det_inv\
    \ *= T{ -1 };\n                T coef = T{ 1 } / data[i][i];\n               \
    \ for (int j = i; j < n; ++j) data[i][j] *= coef;\n                det_inv *=\
    \ coef;\n                for (int k = i + 1; k < n; ++k) {\n                 \
    \   if (data[k][i] == T(0)) continue;\n                    T c = data[k][i];\n\
    \                    for (int j = i; j < n; ++j) data[k][j] -= c * data[i][j];\n\
    \                }\n            }\n            return T{ 1 } / det_inv;\n    \
    \    }\n        static T det(const SquareMatrix<T>& A) {\n            return SquareMatrix<T>::det(SquareMatrix<T>(A));\n\
    \        }\n        SquareMatrix<T>& inv_inplace() {\n            return *this\
    \ = *SquareMatrix<T>::inv(std::move(*this));\n        }\n        SquareMatrix<T>\
    \ inv() const {\n            return *SquareMatrix<T>::inv(*this);\n        }\n\
    \        T det() const {\n            return SquareMatrix<T>::det(SquareMatrix<T>(*this));\n\
    \        }\n\n        SquareMatrix<T>& operator/=(const SquareMatrix<T>& other)\
    \ { return *this *= other.inv(); }\n        SquareMatrix<T>& operator/=(SquareMatrix<T>&&\
    \ other) { return *this *= other.inv_inplace(); }\n        SquareMatrix<T>  operator/\
    \ (const SquareMatrix<T>& other) const { return SquareMatrix<T>(*this) *= other.inv();\
    \ }\n        SquareMatrix<T>  operator/ (SquareMatrix<T>&& other) const { return\
    \ SquareMatrix<T>(*this) *= other.inv_inplace(); }\n\n        SquareMatrix<T>\
    \ pow(long long b) {\n            assert(b >= 0);\n            SquareMatrix<T>\
    \ res(SquareMatrix<T>::e1(this->data.size())), p(*this);\n            for (; b;\
    \ b >>= 1) {\n                if (b & 1) res *= p;\n                p *= p;\n\
    \            }\n            return res;\n        }\n    private:\n        SquareMatrix(int\
    \ n, bool mult_identity) : Matrix<T>::Matrix(n, n) {\n            if (mult_identity)\
    \ for (int i = 0; i < n; ++i) this->data[i][i] = 1;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#line 5 \"library/linear_algebra/count_spanning_trees.hpp\"\n\n\
    namespace suisen {\n    template <typename T, typename Edge>\n    T count_spanning_trees(const\
    \ int n, const std::vector<Edge> &edges) {\n        SquareMatrix<T> A(n - 1);\n\
    \        for (auto [u, v] : edges) if (u != v) {\n            if (u > v) std::swap(u,\
    \ v);\n            ++A[u][u];\n            if (v != n - 1) ++A[v][v], --A[u][v],\
    \ --A[v][u];\n        }\n        return SquareMatrix<T>::det(std::move(A));\n\
    \    }\n} // namespace suisen\n\n\n\n#line 1 \"library/math/factorial.hpp\"\n\n\
    \n\n#line 6 \"library/math/factorial.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T, typename U = T>\n    struct factorial {\n        factorial() {}\n\
    \        factorial(int n) { ensure(n); }\n\n        static void ensure(const int\
    \ n) {\n            int sz = _fac.size();\n            if (n + 1 <= sz) return;\n\
    \            int new_size = std::max(n + 1, sz * 2);\n            _fac.resize(new_size),\
    \ _fac_inv.resize(new_size);\n            for (int i = sz; i < new_size; ++i)\
    \ _fac[i] = _fac[i - 1] * i;\n            _fac_inv[new_size - 1] = U(1) / _fac[new_size\
    \ - 1];\n            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] =\
    \ _fac_inv[i] * i;\n        }\n\n        T fac(const int i) {\n            ensure(i);\n\
    \            return _fac[i];\n        }\n        T operator()(int i) {\n     \
    \       return fac(i);\n        }\n        U fac_inv(const int i) {\n        \
    \    ensure(i);\n            return _fac_inv[i];\n        }\n        U binom(const\
    \ int n, const int r) {\n            if (n < 0 or r < 0 or n < r) return 0;\n\
    \            ensure(n);\n            return _fac[n] * _fac_inv[r] * _fac_inv[n\
    \ - r];\n        }\n        U perm(const int n, const int r) {\n            if\
    \ (n < 0 or r < 0 or n < r) return 0;\n            ensure(n);\n            return\
    \ _fac[n] * _fac_inv[n - r];\n        }\n    private:\n        static std::vector<T>\
    \ _fac;\n        static std::vector<U> _fac_inv;\n    };\n    template <typename\
    \ T, typename U>\n    std::vector<T> factorial<T, U>::_fac{ 1 };\n    template\
    \ <typename T, typename U>\n    std::vector<U> factorial<T, U>::_fac_inv{ 1 };\n\
    } // namespace suisen\n\n\n#line 1 \"library/math/sps.hpp\"\n\n\n\n#line 1 \"\
    library/convolution/subset_convolution.hpp\"\n\n\n\n#line 1 \"library/polynomial/fps_naive.hpp\"\
    \n\n\n\n#line 5 \"library/polynomial/fps_naive.hpp\"\n#include <cmath>\n#line\
    \ 7 \"library/polynomial/fps_naive.hpp\"\n#include <type_traits>\n#line 9 \"library/polynomial/fps_naive.hpp\"\
    \n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 6 \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 11 \"library/polynomial/fps_naive.hpp\"\n\n#line\
    \ 1 \"library/math/modint_extension.hpp\"\n\n\n\n#line 6 \"library/math/modint_extension.hpp\"\
    \n\n/**\n * refernce: https://37zigen.com/tonelli-shanks-algorithm/\n * calculates\
    \ x s.t. x^2 = a mod p in O((log p)^2).\n */\ntemplate <typename mint>\nstd::optional<mint>\
    \ optional_sqrt(mint a) {\n    static int p = mint::mod();\n    if (a == 0) return\
    \ std::make_optional(0);\n    if (p == 2) return std::make_optional(a);\n    if\
    \ (a.pow((p - 1) / 2) != 1) return std::nullopt;\n    mint b = 1;\n    while (b.pow((p\
    \ - 1) / 2) == 1) ++b;\n    static int tlz = __builtin_ctz(p - 1), q = (p - 1)\
    \ >> tlz;\n    mint x = a.pow((q + 1) / 2);\n    b = b.pow(q);\n    for (int shift\
    \ = 2; x * x != a; ++shift) {\n        mint e = a.inv() * x * x;\n        if (e.pow(1\
    \ << (tlz - shift)) != 1) x *= b;\n        b *= b;\n    }\n    return std::make_optional(x);\n\
    }\n\n/**\n * calculates x s.t. x^2 = a mod p in O((log p)^2).\n * if not exists,\
    \ raises runtime error.\n */\ntemplate <typename mint>\nauto sqrt(mint a) -> decltype(mint::mod(),\
    \ mint()) {\n    return *optional_sqrt(a);\n}\ntemplate <typename mint>\nauto\
    \ log(mint a) -> decltype(mint::mod(), mint())  {\n    assert(a == 1);\n    return\
    \ 0;\n}\ntemplate <typename mint>\nauto exp(mint a) -> decltype(mint::mod(), mint())\
    \  {\n    assert(a == 0);\n    return 1;\n}\ntemplate <typename mint, typename\
    \ T>\nauto pow(mint a, T b) -> decltype(mint::mod(), mint())  {\n    return a.pow(b);\n\
    }\ntemplate <typename mint>\nauto inv(mint a) -> decltype(mint::mod(), mint())\
    \ {\n    return a.inv();\n}\n\n\n#line 1 \"library/math/inv_mods.hpp\"\n\n\n\n\
    #line 5 \"library/math/inv_mods.hpp\"\n\nnamespace suisen {\ntemplate <typename\
    \ mint>\nclass inv_mods {\n    public:\n        inv_mods() {}\n        inv_mods(int\
    \ n) { ensure(n); }\n        const mint& operator[](int i) const {\n         \
    \   ensure(i);\n            return invs[i];\n        }\n        static void ensure(int\
    \ n) {\n            int sz = invs.size();\n            if (sz < 2) invs = {0,\
    \ 1}, sz = 2;\n            if (sz < n + 1) {\n                invs.resize(n +\
    \ 1);\n                for (int i = sz; i <= n; ++i) invs[i] = mint(mod - mod\
    \ / i) * invs[mod % i];\n            }\n        }\n    private:\n        static\
    \ std::vector<mint> invs;\n        static constexpr int mod = mint::mod();\n};\n\
    template <typename mint>\nstd::vector<mint> inv_mods<mint>::invs{};\n}\n\n\n#line\
    \ 14 \"library/polynomial/fps_naive.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T>\n    struct FPSNaive : std::vector<T> {\n        static inline\
    \ int MAX_DEG = std::numeric_limits<int>::max() / 2;\n\n        using value_type\
    \ = T;\n        using element_type = rec_value_type_t<T>;\n        using std::vector<value_type>::vector;\n\
    \n        FPSNaive(const std::initializer_list<value_type> l) : std::vector<value_type>::vector(l)\
    \ {}\n\n        static void set_max_deg(int max_deg) {\n            FPSNaive<T>::MAX_DEG\
    \ = max_deg;\n        }\n\n        const value_type operator[](int n) const {\n\
    \            return n <= deg() ? unsafe_get(n) : value_type{ 0 };\n        }\n\
    \        value_type& operator[](int n) {\n            return ensure_deg(n), unsafe_get(n);\n\
    \        }\n\n        int size() const {\n            return std::vector<value_type>::size();\n\
    \        }\n        int deg() const {\n            return size() - 1;\n      \
    \  }\n        int normalize() {\n            while (size() and this->back() ==\
    \ value_type{ 0 }) this->pop_back();\n            return deg();\n        }\n \
    \       FPSNaive& cut_inplace(int max_deg) {\n            if (deg() > max_deg)\
    \ this->resize(std::max(0, max_deg + 1));\n            return *this;\n       \
    \ }\n        FPSNaive cut(int max_deg) const {\n            return FPSNaive(*this).cut_inplace(max_deg);\n\
    \        }\n\n        FPSNaive operator+() const {\n            return FPSNaive(*this);\n\
    \        }\n        FPSNaive operator-() const {\n            FPSNaive f(*this);\n\
    \            for (auto& e : f) e = -e;\n            return f;\n        }\n   \
    \     FPSNaive& operator++() { return ++(*this)[0], * this; }\n        FPSNaive&\
    \ operator--() { return --(*this)[0], * this; }\n        FPSNaive& operator+=(const\
    \ value_type x) { return (*this)[0] += x, *this; }\n        FPSNaive& operator-=(const\
    \ value_type x) { return (*this)[0] -= x, *this; }\n        FPSNaive& operator+=(const\
    \ FPSNaive& g) {\n            ensure_deg(g.deg());\n            for (int i = 0;\
    \ i <= g.deg(); ++i) unsafe_get(i) += g.unsafe_get(i);\n            return *this;\n\
    \        }\n        FPSNaive& operator-=(const FPSNaive& g) {\n            ensure_deg(g.deg());\n\
    \            for (int i = 0; i <= g.deg(); ++i) unsafe_get(i) -= g.unsafe_get(i);\n\
    \            return *this;\n        }\n        FPSNaive& operator*=(const FPSNaive&\
    \ g) { return *this = *this * g; }\n        FPSNaive& operator*=(const value_type\
    \ x) {\n            for (auto& e : *this) e *= x;\n            return *this;\n\
    \        }\n        FPSNaive& operator/=(const FPSNaive& g) { return *this = *this\
    \ / g; }\n        FPSNaive& operator%=(const FPSNaive& g) { return *this = *this\
    \ % g; }\n        FPSNaive& operator<<=(const int shamt) {\n            this->insert(this->begin(),\
    \ shamt, value_type { 0 });\n            return *this;\n        }\n        FPSNaive&\
    \ operator>>=(const int shamt) {\n            if (shamt > size()) this->clear();\n\
    \            else this->erase(this->begin(), this->begin() + shamt);\n       \
    \     return *this;\n        }\n\n        friend FPSNaive operator+(FPSNaive f,\
    \ const FPSNaive& g)   { f += g; return f; }\n        friend FPSNaive operator+(FPSNaive\
    \ f, const value_type &x) { f += x; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const FPSNaive& g)   { f -= g; return f; }\n        friend FPSNaive operator-(FPSNaive\
    \ f, const value_type &x) { f -= x; return f; }\n        friend FPSNaive operator*(const\
    \ FPSNaive &f, const FPSNaive& g) {\n            if (f.empty() or g.empty()) return\
    \ FPSNaive{};\n            const int n = f.size(), m = g.size();\n           \
    \ FPSNaive h(std::min(MAX_DEG + 1, n + m - 1));\n            for (int i = 0; i\
    \ < n; ++i) for (int j = 0; j < m; ++j) {\n                if (i + j > MAX_DEG)\
    \ break;\n                h.unsafe_get(i + j) += f.unsafe_get(i) * g.unsafe_get(j);\n\
    \            }\n            return h;\n        }\n        friend FPSNaive operator*(FPSNaive\
    \ f, const value_type &x) { f *= x; return f; }\n        friend FPSNaive operator/(FPSNaive\
    \ f, FPSNaive g) { return std::move(div_mod(std::move(f), std::move(g)).first);\
    \ }\n        friend FPSNaive operator%(FPSNaive f, FPSNaive g) { return std::move(div_mod(std::move(f),\
    \ std::move(g)).second); }\n        friend FPSNaive operator*(const value_type\
    \ x, FPSNaive f) { f *= x; return f; }\n        friend FPSNaive operator<<(FPSNaive\
    \ f, const int shamt)   { f <<= shamt; return f; }\n        friend FPSNaive operator>>(FPSNaive\
    \ f, const int shamt)   { f >>= shamt; return f; }\n\n        friend std::pair<FPSNaive,\
    \ FPSNaive> div_mod(FPSNaive f, FPSNaive g) {\n            const int fd = f.normalize(),\
    \ gd = g.normalize();\n            assert(gd >= 0);\n            if (fd < gd)\
    \ return { FPSNaive{}, f };\n            if (gd == 0) return { f *= g.unsafe_get(0).inv(),\
    \ FPSNaive{} };\n            const int k = f.deg() - gd;\n            value_type\
    \ head_inv = g.unsafe_get(gd).inv();\n            FPSNaive q(k + 1);\n       \
    \     for (int i = k; i >= 0; --i) {\n                value_type div = f.unsafe_get(i\
    \ + gd) * head_inv;\n                q.unsafe_get(i) = div;\n                for\
    \ (int j = 0; j <= gd; ++j) f.unsafe_get(i + j) -= div * g.unsafe_get(j);\n  \
    \          }\n            return { q, f.cut_inplace(gd - 1) };\n        }\n\n\
    \        friend bool operator==(const FPSNaive& f, const FPSNaive& g) {\n    \
    \        const int n = f.size(), m = g.size();\n            if (n < m) return\
    \ g == f;\n            for (int i = 0; i < m; ++i) if (f.unsafe_get(i) != g.unsafe_get(i))\
    \ return false;\n            for (int i = m; i < n; ++i) if (f.unsafe_get(i) !=\
    \ 0) return false;\n            return true;\n        }\n        friend bool operator!=(const\
    \ FPSNaive& f, const FPSNaive& g) {\n            return not (f == g);\n      \
    \  }\n\n        FPSNaive mul(const FPSNaive& g, int max_deg) const {\n       \
    \     if (this->empty() or g.empty()) return FPSNaive{};\n            const int\
    \ n = size(), m = g.size();\n            FPSNaive h(std::min(max_deg + 1, n +\
    \ m - 1));\n            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)\
    \ {\n                if (i + j > max_deg) break;\n                h.unsafe_get(i\
    \ + j) += unsafe_get(i) * g.unsafe_get(j);\n            }\n            return\
    \ h;\n        }\n        FPSNaive diff() const {\n            if (this->empty())\
    \ return {};\n            FPSNaive g(size() - 1);\n            for (int i = 1;\
    \ i <= deg(); ++i) g.unsafe_get(i - 1) = unsafe_get(i) * i;\n            return\
    \ g;\n        }\n        FPSNaive intg() const {\n            const int n = size();\n\
    \            FPSNaive g(n + 1);\n            for (int i = 0; i < n; ++i) g.unsafe_get(i\
    \ + 1) = unsafe_get(i) * invs[i + 1];\n            if (g.deg() > MAX_DEG) g.cut_inplace(MAX_DEG);\n\
    \            return g;\n        }\n        FPSNaive inv(int max_deg) const {\n\
    \            FPSNaive g(max_deg + 1);\n            const value_type inv_f0 = ::inv(unsafe_get(0));\n\
    \            g.unsafe_get(0) = inv_f0;\n            for (int i = 1; i <= max_deg;\
    \ ++i) {\n                for (int j = 1; j <= i; ++j) g.unsafe_get(i) -= g.unsafe_get(i\
    \ - j) * (*this)[j];\n                g.unsafe_get(i) *= inv_f0;\n           \
    \ }\n            return g;\n        }\n        FPSNaive exp(int max_deg) const\
    \ {\n            assert(unsafe_get(0) == value_type{ 0 });\n            FPSNaive\
    \ g(max_deg + 1);\n            g.unsafe_get(0) = value_type{ 1 };\n          \
    \  for (int i = 1; i <= max_deg; ++i) {\n                for (int j = 1; j <=\
    \ i; ++j) g.unsafe_get(i) += j * g.unsafe_get(i - j) * (*this)[j];\n         \
    \       g.unsafe_get(i) *= invs[i];\n            }\n            return g;\n  \
    \      }\n        FPSNaive log(int max_deg) const {\n            assert(unsafe_get(0)\
    \ == value_type{ 1 });\n            FPSNaive g(max_deg + 1);\n            g.unsafe_get(0)\
    \ = value_type{ 0 };\n            for (int i = 1; i <= max_deg; ++i) {\n     \
    \           g.unsafe_get(i) = i * (*this)[i];\n                for (int j = 1;\
    \ j < i; ++j) g.unsafe_get(i) -= (i - j) * g.unsafe_get(i - j) * (*this)[j];\n\
    \                g.unsafe_get(i) *= invs[i];\n            }\n            return\
    \ g;\n        }\n        FPSNaive pow(const long long k, int max_deg) const {\n\
    \            if (k == 0) return { value_type{ 1 } };\n            int z = 0;\n\
    \            while (z < size() and unsafe_get(z) == value_type{ 0 }) ++z;\n  \
    \          if (z == size() or z > max_deg / k) return FPSNaive{};\n          \
    \  const int d = max_deg - z * k;\n\n            FPSNaive g(d + 1);\n        \
    \    const value_type inv_f0 = ::inv(unsafe_get(z));\n            g.unsafe_get(0)\
    \ = unsafe_get(z).pow(k);\n            for (int i = 1; i <= d; ++i) {\n      \
    \          for (int j = 1; j <= i; ++j) g.unsafe_get(i) += (element_type{ k }\
    \ * j - (i - j)) * g.unsafe_get(i - j) * (*this)[z + j];\n                g.unsafe_get(i)\
    \ *= inv_f0 * invs[i];\n            }\n            g <<= z * k;\n            return\
    \ g;\n        }\n\n        std::optional<FPSNaive> optional_sqrt(int max_deg)\
    \ const {\n            int dl = 0;\n            while (dl < size() and unsafe_get(dl)\
    \ == value_type{ 0 }) ++dl;\n            if (dl == size()) return FPSNaive{};\n\
    \            if (dl & 1) return std::nullopt;\n\n            const int d = max_deg\
    \ - dl / 2;\n\n            FPSNaive g(d + 1);\n            auto opt_g0 = ::optional_sqrt((*this)[dl]);\n\
    \            if (not opt_g0.has_value()) return std::nullopt;\n            g.unsafe_get(0)\
    \ = *opt_g0;\n            value_type inv_2g0 = ::inv(2 * g.unsafe_get(0));\n \
    \           for (int i = 1; i <= d; ++i) {\n                g.unsafe_get(i) =\
    \ (*this)[dl + i];\n                for (int j = 1; j < i; ++j) g.unsafe_get(i)\
    \ -= g.unsafe_get(j) * g.unsafe_get(i - j);\n                g.unsafe_get(i) *=\
    \ inv_2g0;\n            }\n            g <<= dl / 2;\n            return g;\n\
    \        }\n        FPSNaive sqrt(int max_deg) const {\n            return *optional_sqrt(max_deg);\n\
    \        }\n\n        value_type eval(value_type x) const {\n            value_type\
    \ y = 0;\n            for (int i = size() - 1; i >= 0; --i) y = y * x + unsafe_get(i);\n\
    \            return y;\n        }\n\n    private:\n        static inline inv_mods<element_type>\
    \ invs;\n\n        void ensure_deg(int d) {\n            if (deg() < d) this->resize(d\
    \ + 1, value_type{ 0 });\n        }\n        const value_type& unsafe_get(int\
    \ i) const {\n            return std::vector<value_type>::operator[](i);\n   \
    \     }\n        value_type& unsafe_get(int i) {\n            return std::vector<value_type>::operator[](i);\n\
    \        }\n    };\n} // namespace suisen\n\ntemplate <typename mint>\nauto sqrt(suisen::FPSNaive<mint>\
    \ a) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.sqrt(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint>\nauto log(suisen::FPSNaive<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPSNaive<mint>{}) {\n    return a.log(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint>\nauto exp(suisen::FPSNaive<mint> a) -> decltype(mint::mod(),\
    \ suisen::FPSNaive<mint>{}) {\n    return a.exp(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\ntemplate <typename mint, typename T>\nauto pow(suisen::FPSNaive<mint> a, T\
    \ b) -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.pow(b,\
    \ suisen::FPSNaive<mint>::MAX_DEG == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG\
    \ : a.deg());\n}\ntemplate <typename mint>\nauto inv(suisen::FPSNaive<mint> a)\
    \ -> decltype(mint::mod(), suisen::FPSNaive<mint>{}) {\n    return a.inv(suisen::FPSNaive<mint>::MAX_DEG\
    \ == std::numeric_limits<int>::max() / 2 ? suisen::FPSNaive<mint>::MAX_DEG : a.deg());\n\
    }\n\n\n\n#line 5 \"library/convolution/subset_convolution.hpp\"\n\n#line 1 \"\
    library/transform/subset.hpp\"\n\n\n\n#line 1 \"library/transform/kronecker_power.hpp\"\
    \n\n\n\n#line 5 \"library/transform/kronecker_power.hpp\"\n#include <utility>\n\
    #line 7 \"library/transform/kronecker_power.hpp\"\n\n#line 1 \"library/util/default_operator.hpp\"\
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
    \n\n#line 9 \"library/transform/kronecker_power.hpp\"\n\nnamespace suisen {\n\
    \    namespace kronecker_power_transform {\n        namespace internal {\n   \
    \         template <typename UnitTransform, typename ReferenceGetter, std::size_t...\
    \ Seq>\n            void unit_transform(UnitTransform transform, ReferenceGetter\
    \ ref_getter, std::index_sequence<Seq...>) {\n                transform(ref_getter(Seq)...);\n\
    \            }\n        }\n\n        template <typename T, std::size_t D, auto\
    \ unit_transform>\n        void kronecker_power_transform(std::vector<T> &x) {\n\
    \            const std::size_t n = x.size();\n            for (std::size_t block\
    \ = 1; block < n; block *= D) {\n                for (std::size_t l = 0; l < n;\
    \ l += D * block) {\n                    for (std::size_t offset = l; offset <\
    \ l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/transform/subset.hpp\"\
    \n\nnamespace suisen::subset_transform {\n    namespace internal {\n        template\
    \ <typename T, auto add = default_operator::add<T>>\n        void zeta_unit_transform(T\
    \ &x0, T &x1) {\n                                // 1, 0\n            x1 = add(x1,\
    \ x0);   // 1, 1\n        }\n        template <typename T, auto sub = default_operator::sub<T>>\n\
    \        void mobius_unit_transform(T &x0, T &x1) {\n                        \
    \        //  1, 0\n            x1 = sub(x1, x0);   // -1, 1\n        }\n    }\
    \ // namespace internal\n\n    using kronecker_power_transform::kronecker_power_transform;\n\
    \n    template <typename T, auto add = default_operator::add<T>>\n    void zeta(std::vector<T>\
    \ &a) {\n        kronecker_power_transform<T, 2, internal::zeta_unit_transform<T,\
    \ add>>(a);\n    }\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void mobius(std::vector<T> &a) {\n        kronecker_power_transform<T, 2,\
    \ internal::mobius_unit_transform<T, sub>>(a);\n    }\n} // namespace suisen::subset_transform\n\
    \n\n#line 7 \"library/convolution/subset_convolution.hpp\"\n\nnamespace suisen\
    \ {\n    namespace ranked_subset_transform {\n        template <typename T>\n\
    \        using polynomial_t = FPSNaive<T>;\n\n        namespace internal {\n \
    \           template <typename T>\n            std::vector<polynomial_t<T>> ranked(const\
    \ std::vector<T>& a) {\n                const int n = a.size();\n            \
    \    assert((-n & n) == n);\n                std::vector fs(n, polynomial_t<T>(__builtin_ctz(n)\
    \ + 1, T{ 0 }));\n                for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)]\
    \ = a[i];\n                return fs;\n            }\n            template <typename\
    \ T>\n            std::vector<T> deranked(const std::vector<polynomial_t<T>>&\
    \ polys) {\n                const int n = polys.size();\n                assert((-n\
    \ & n) == n);\n                std::vector<T> a(n);\n                for (int\
    \ i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n               \
    \ return a;\n            }\n        } // suisen::ranked_subset_transform::internal\n\
    \n        template <typename T>\n        std::vector<polynomial_t<T>> ranked_zeta(const\
    \ std::vector<T>& a) {\n            std::vector<polynomial_t<T>> ranked = internal::ranked<T>(a);\n\
    \            subset_transform::zeta(ranked);\n            return ranked;\n   \
    \     }\n        template <typename T>\n        std::vector<T> deranked_mobius(std::vector<polynomial_t<T>>&\
    \ ranked) {\n            subset_transform::mobius(ranked);\n            return\
    \ internal::deranked<T>(ranked);\n        }\n    } // suisen::ranked_subset_transform\n\
    \n    template <typename T>\n    std::vector<T> subset_convolution(const std::vector<T>&\
    \ a, const std::vector<T>& b) {\n        const int n = a.size();\n        auto\
    \ ra = ranked_subset_transform::ranked_zeta(a), rb = ranked_subset_transform::ranked_zeta(b);\n\
    \        for (int i = 0; i < n; ++i) ra[i] = ra[i].mul(rb[i], ra[i].deg());\n\
    \        return ranked_subset_transform::deranked_mobius(ra);\n    }\n} // namespace\
    \ suisen\n\n\n#line 5 \"library/math/sps.hpp\"\n\nnamespace suisen {\n    template\
    \ <typename T>\n    struct SPS : public std::vector<T> {\n        using base_type\
    \ = std::vector<T>;\n        using value_type = typename base_type::value_type;\n\
    \        using size_type = typename base_type::size_type;\n\n        using polynomial_type\
    \ = ranked_subset_transform::polynomial_t<value_type>;\n\n        using base_type::vector;\n\
    \n        SPS() : SPS(0) {}\n        SPS(size_type n) : SPS(n, value_type{ 0 })\
    \ {}\n        SPS(size_type n, const value_type& val) : SPS(std::vector<value_type>(1\
    \ << n, val)) {}\n        SPS(const base_type& a) : SPS(base_type(a)) {}\n   \
    \     SPS(base_type&& a) : base_type(std::move(a)) {\n            const int n\
    \ = this->size();\n            assert(n == (-n & n));\n        }\n        SPS(std::initializer_list<value_type>\
    \ l) : SPS(base_type(l)) {}\n\n        static SPS one(int n) {\n            SPS\
    \ f(n, value_type{ 0 });\n            f[0] = value_type{ 1 };\n            return\
    \ f;\n        }\n\n        void set_cardinality(int n) {\n            this->resize(1\
    \ << n, value_type{ 0 });\n        }\n        int cardinality() const {\n    \
    \        return __builtin_ctz(this->size());\n        }\n\n        SPS cut_lower(size_type\
    \ p) const {\n            return SPS(this->begin(), this->begin() + p);\n    \
    \    }\n        SPS cut_upper(size_type p) const {\n            return SPS(this->begin()\
    \ + p, this->begin() + p + p);\n        }\n\n        void concat(const SPS& upper)\
    \ {\n            assert(this->size() == upper.size());\n            this->insert(this->end(),\
    \ upper.begin(), upper.end());\n        }\n\n        SPS operator+() const {\n\
    \            return *this;\n        }\n        SPS operator-() const {\n     \
    \       SPS res(*this);\n            for (auto& e : res) e = -e;\n           \
    \ return res;\n        }\n        SPS& operator+=(const SPS& g) {\n          \
    \  for (size_type i = 0; i < g.size(); ++i) (*this)[i] += g[i];\n            return\
    \ *this;\n        }\n        SPS& operator-=(const SPS& g) {\n            for\
    \ (size_type i = 0; i < g.size(); ++i) (*this)[i] -= g[i];\n            return\
    \ *this;\n        }\n        SPS& operator*=(const SPS& g) {\n            return\
    \ *this = (zeta() *= g).mobius_inplace();\n        }\n        SPS& operator*=(const\
    \ value_type &c) {\n            for (auto& e : *this) e *= c;\n            return\
    \ *this;\n        }\n        SPS& operator/=(const value_type &c) {\n        \
    \    value_type inv_c = ::inv(c);\n            for (auto& e : *this) e *= inv_c;\n\
    \            return *this;\n        }\n        friend SPS operator+(SPS f, const\
    \ SPS& g) { f += g; return f; }\n        friend SPS operator-(SPS f, const SPS&\
    \ g) { f -= g; return f; }\n        friend SPS operator*(SPS f, const SPS& g)\
    \ { f *= g; return f; }\n        friend SPS operator*(SPS f, const value_type\
    \ &c) { f *= c; return f; }\n        friend SPS operator*(const value_type &c,\
    \ SPS f) { f *= c; return f; }\n        friend SPS operator/(SPS f, const value_type\
    \ &c) { f /= c; return f; }\n\n        SPS inv() {\n            return zeta().inv_inplace().mobius_inplace();\n\
    \        }\n        SPS sqrt() {\n            return zeta().sqrt_inplace().mobius_inplace();\n\
    \        }\n        SPS exp() {\n            return zeta().exp_inplace().mobius_inplace();\n\
    \        }\n        SPS log() {\n            return zeta().log_inplace().mobius_inplace();\n\
    \        }\n        SPS pow(long long k) {\n            return zeta().pow_inplace(k).mobius_inplace();\n\
    \        }\n\n        struct ZetaSPS : public std::vector<polynomial_type> {\n\
    \            using base_type = std::vector<polynomial_type>;\n            ZetaSPS()\
    \ = default;\n            ZetaSPS(const SPS<value_type>& f) : base_type::vector(ranked_subset_transform::ranked_zeta(f)),\
    \ _d(f.cardinality()) {}\n\n            ZetaSPS operator+() const {\n        \
    \        return *this;\n            }\n            ZetaSPS operator-() const {\n\
    \                ZetaSPS res(*this);\n                for (auto& f : res) f =\
    \ -f;\n                return res;\n            }\n            friend ZetaSPS\
    \ operator+(ZetaSPS f, const ZetaSPS& g) { f += g; return f; }\n            friend\
    \ ZetaSPS operator-(ZetaSPS f, const ZetaSPS& g) { f -= g; return f; }\n     \
    \       friend ZetaSPS operator*(ZetaSPS f, const ZetaSPS& g) { f *= g; return\
    \ f; }\n            friend ZetaSPS operator*(ZetaSPS f, const value_type &c) {\
    \ f *= c; return f; }\n            friend ZetaSPS operator*(const value_type &c,\
    \ ZetaSPS f) { f *= c; return f; }\n            friend ZetaSPS operator/(ZetaSPS\
    \ f, const value_type &c) { f /= c; return f; }\n\n            ZetaSPS& operator+=(const\
    \ ZetaSPS& rhs) {\n                assert(_d == rhs._d);\n                for\
    \ (int i = 0; i < 1 << _d; ++i) (*this)[i] += rhs[i];\n                return\
    \ *this;\n            }\n            ZetaSPS& operator-=(const ZetaSPS& rhs) {\n\
    \                assert(_d == rhs._d);\n                for (int i = 0; i < 1\
    \ << _d; ++i) (*this)[i] -= rhs[i];\n                return *this;\n         \
    \   }\n            ZetaSPS& operator*=(value_type c) {\n                for (auto&\
    \ f : *this) f *= c;\n                return *this;\n            }\n         \
    \   ZetaSPS& operator/=(value_type c) {\n                value_type inv_c = ::inv(c);\n\
    \                for (auto& f : *this) f *= inv_c;\n                return *this;\n\
    \            }\n            ZetaSPS& operator*=(const ZetaSPS& rhs) {\n      \
    \          assert(_d == rhs._d);\n                for (size_type i = 0; i < size_type(1)\
    \ << _d; ++i) (*this)[i] = (*this)[i].mul(rhs[i], _d);\n                return\
    \ *this;\n            }\n            ZetaSPS inv()  const { auto f = ZetaSPS(*this).inv_inplace();\
    \  return f; }\n            ZetaSPS sqrt() const { auto f = ZetaSPS(*this).sqrt_inplace();\
    \ return f; }\n            ZetaSPS exp()  const { auto f = ZetaSPS(*this).exp_inplace();\
    \  return f; }\n            ZetaSPS log()  const { auto f = ZetaSPS(*this).log_inplace();\
    \  return f; }\n            ZetaSPS pow(long long k) const { auto f = ZetaSPS(*this).pow_inplace(k);\
    \ return f; }\n            ZetaSPS& inv_inplace() {\n                for (auto&\
    \ f : *this) f = f.inv(_d);\n                return *this;\n            }\n  \
    \          ZetaSPS& sqrt_inplace() {\n                for (auto& f : *this) f\
    \ = f.sqrt(_d);\n                return *this;\n            }\n            ZetaSPS&\
    \ exp_inplace() {\n                for (auto& f : *this) f = f.exp(_d);\n    \
    \            return *this;\n            }\n            ZetaSPS& log_inplace()\
    \ {\n                for (auto& f : *this) f = f.log(_d);\n                return\
    \ *this;\n            }\n            ZetaSPS& pow_inplace(long long k) {\n   \
    \             for (auto& f : *this) f = f.pow(k, _d);\n                return\
    \ *this;\n            }\n            SPS<value_type> mobius_inplace() {\n    \
    \            return ranked_subset_transform::deranked_mobius<value_type>(*this);\n\
    \            }\n            SPS<value_type> mobius() const {\n               \
    \ auto rf = ZetaSPS(*this);\n                return ranked_subset_transform::deranked_mobius<value_type>(rf);\n\
    \            }\n        private:\n            int _d;\n        };\n\n        ZetaSPS\
    \ zeta() const {\n            return ZetaSPS(*this);\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#line 12 \"test/src/math/sps/abc253_h.test.cpp\"\n\nint\
    \ main() {\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n\n    for (auto& [u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n        --u, --v;\n    }\n\n    suisen::FPSNaive<mint>::set_max_deg(n);\n\
    \n    suisen::SPS<suisen::FPSNaive<mint>> f(n, suisen::FPSNaive<mint>(n));\n \
    \   for (int s = 1; s < 1 << n; ++s) {\n        std::vector<int> ids(n, -1);\n\
    \        int id = 0;\n        for (int i : suisen::all_setbit(s)) ids[i] = id++;\n\
    \        std::vector<std::pair<int, int>> Es;\n        for (const auto& [u, v]\
    \ : edges) if (ids[u] >= 0 and ids[v] >= 0) {\n            Es.emplace_back(ids[u],\
    \ ids[v]);\n        }\n        f[s] = { 0, suisen::count_spanning_trees<mint>(id,\
    \ Es) };\n    }\n\n    suisen::factorial<mint> fac(n);\n\n    auto g = f.exp().back();\n\
    \n    for (int k = 1; k < n; ++k) {\n        std::cout << (fac.fac(k) * g[n -\
    \ k] / mint(m).pow(k)).val() << std::endl;\n    }\n\n    return 0;\n}\n\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc253/tasks/abc253_Ex\"\n\n\
    #include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/util/subset_iterator.hpp\"\n#include \"library/linear_algebra/count_spanning_trees.hpp\"\
    \n#include \"library/math/factorial.hpp\"\n#include \"library/math/sps.hpp\"\n\
    \nint main() {\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n\n    for (auto& [u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n        --u, --v;\n    }\n\n    suisen::FPSNaive<mint>::set_max_deg(n);\n\
    \n    suisen::SPS<suisen::FPSNaive<mint>> f(n, suisen::FPSNaive<mint>(n));\n \
    \   for (int s = 1; s < 1 << n; ++s) {\n        std::vector<int> ids(n, -1);\n\
    \        int id = 0;\n        for (int i : suisen::all_setbit(s)) ids[i] = id++;\n\
    \        std::vector<std::pair<int, int>> Es;\n        for (const auto& [u, v]\
    \ : edges) if (ids[u] >= 0 and ids[v] >= 0) {\n            Es.emplace_back(ids[u],\
    \ ids[v]);\n        }\n        f[s] = { 0, suisen::count_spanning_trees<mint>(id,\
    \ Es) };\n    }\n\n    suisen::factorial<mint> fac(n);\n\n    auto g = f.exp().back();\n\
    \n    for (int k = 1; k < n; ++k) {\n        std::cout << (fac.fac(k) * g[n -\
    \ k] / mint(m).pow(k)).val() << std::endl;\n    }\n\n    return 0;\n}\n\n"
  dependsOn:
  - library/util/subset_iterator.hpp
  - library/linear_algebra/count_spanning_trees.hpp
  - library/linear_algebra/matrix.hpp
  - library/math/factorial.hpp
  - library/math/sps.hpp
  - library/convolution/subset_convolution.hpp
  - library/polynomial/fps_naive.hpp
  - library/type_traits/type_traits.hpp
  - library/math/modint_extension.hpp
  - library/math/inv_mods.hpp
  - library/transform/subset.hpp
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: true
  path: test/src/math/sps/abc253_h.test.cpp
  requiredBy: []
  timestamp: '2022-07-02 19:47:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/math/sps/abc253_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/math/sps/abc253_h.test.cpp
- /verify/test/src/math/sps/abc253_h.test.cpp.html
title: test/src/math/sps/abc253_h.test.cpp
---