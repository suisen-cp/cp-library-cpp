---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':x:'
    path: library/datastructure/segment_tree/segment_tree_beats.hpp
    title: Segment Tree Beats
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
    title: test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/range_query/range_chmin_chmax_add_range_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <limits>\n\n#line 1 \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\n\
    \n\n\n#include <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#line 5 \"library/type_traits/type_traits.hpp\"\
    \n#include <iostream>\n#include <type_traits>\n\nnamespace suisen {\n    template\
    \ <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
    namespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n\
    \        auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 7 \"library/datastructure/segment_tree/lazy_segment_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)(), bool enable_beats = false>\n    struct\
    \ LazySegmentTree {\n        using value_type = T;\n        using operator_type\
    \ = F;\n\n        LazySegmentTree() : LazySegmentTree(0) {}\n        LazySegmentTree(int\
    \ n) : LazySegmentTree(std::vector<value_type>(n, e())) {}\n        LazySegmentTree(const\
    \ std::vector<value_type>& init) : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)),\
    \ data(2 * m, e()), lazy(m, id()) {\n            std::copy(init.begin(), init.end(),\
    \ data.begin() + m);\n            for (int k = m - 1; k > 0; --k) update(k);\n\
    \        }\n\n        void apply(int l, int r, const operator_type& f) {\n   \
    \         assert(0 <= l and l <= r and r <= n);\n            push_to(l, r);\n\
    \            for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {\n\
    \                if (l2 & 1) all_apply(l2++, f);\n                if (r2 & 1)\
    \ all_apply(--r2, f);\n            }\n            update_from(l, r);\n       \
    \ }\n        void apply(int p, const operator_type& f) {\n            (*this)[p]\
    \ = mapping(f, get(p));\n        }\n\n        value_type operator()(int l, int\
    \ r) {\n            assert(0 <= l and l <= r and r <= n);\n            push_to(l,\
    \ r);\n            value_type res_l = e(), res_r = e();\n            for (l +=\
    \ m, r += m; l < r; l >>= 1, r >>= 1) {\n                if (l & 1) res_l = op(res_l,\
    \ data[l++]);\n                if (r & 1) res_r = op(data[--r], res_r);\n    \
    \        }\n            return op(res_l, res_r);\n        }\n\n        value_type\
    \ prod(int l, int r) { return (*this)(l, r); }\n        value_type prefix_prod(int\
    \ r) { return (*this)(0, r); }\n        value_type suffix_prod(int l) { return\
    \ (*this)(l, m); }\n        value_type all_prod() const { return data[1]; }\n\n\
    \        auto operator[](int p) {\n            assert(0 <= p and p < n);\n   \
    \         push_to(p);\n            return UpdateProxyObject{ data[p + m], [this,\
    \ p] { update_from(p); } };\n        }\n        value_type get(int p) { return\
    \ (*this)[p]; }\n        void set(int p, value_type v) { (*this)[p] = v; }\n\n\
    \        template <typename Pred, constraints_t<std::is_invocable_r<bool, Pred,\
    \ value_type>> = nullptr>\n        int max_right(int l, Pred g) {\n          \
    \  assert(0 <= l && l <= n);\n            assert(g(e()));\n            if (l ==\
    \ n) return n;\n            l += m;\n            for (int i = lg; i >= 1; --i)\
    \ push(l >> i);\n            value_type sum = e();\n            do {\n       \
    \         while ((l & 1) == 0) l >>= 1;\n                if (not g(op(sum, data[l])))\
    \ {\n                    while (l < m) {\n                        push(l);\n \
    \                       l = 2 * l;\n                        if (g(op(sum, data[l])))\
    \ sum = op(sum, data[l++]);\n                    }\n                    return\
    \ l - m;\n                }\n                sum = op(sum, data[l++]);\n     \
    \       } while ((l & -l) != l);\n            return n;\n        }\n        template\
    \ <bool(*f)(value_type)>\n        int max_right(int l) { return max_right(l, f);\
    \ }\n\n        template <typename Pred, constraints_t<std::is_invocable_r<bool,\
    \ Pred, value_type>> = nullptr>\n        int min_left(int r, Pred g) {\n     \
    \       assert(0 <= r && r <= n);\n            assert(g(e()));\n            if\
    \ (r == 0) return 0;\n            r += m;\n            for (int i = lg; i >= 1;\
    \ --i) push(r >> i);\n            value_type sum = e();\n            do {\n  \
    \              r--;\n                while (r > 1 and (r & 1)) r >>= 1;\n    \
    \            if (not g(op(data[r], sum))) {\n                    while (r < m)\
    \ {\n                        push(r);\n                        r = 2 * r + 1;\n\
    \                        if (g(op(data[r], sum))) sum = op(data[r--], sum);\n\
    \                    }\n                    return r + 1 - m;\n              \
    \  }\n                sum = op(data[r], sum);\n            } while ((r & -r) !=\
    \ r);\n            return 0;\n        }\n        template <bool(*f)(value_type)>\n\
    \        int min_left(int l) { return min_left(l, f); }\n    private:\n      \
    \  int n, m, lg;\n        std::vector<value_type> data;\n        std::vector<operator_type>\
    \ lazy;\n\n        static constexpr int ceil_pow2(int n) {\n            int m\
    \ = 1;\n            while (m < n) m <<= 1;\n            return m;\n        }\n\
    \n        void all_apply(int k, const operator_type& f) {\n            data[k]\
    \ = mapping(f, data[k]);\n            if (k < m) {\n                lazy[k] =\
    \ composition(f, lazy[k]);\n                if constexpr (enable_beats) if (data[k].fail)\
    \ push(k), update(k);\n            }\n        }\n        void push(int k) {\n\
    \            all_apply(2 * k, lazy[k]), all_apply(2 * k + 1, lazy[k]);\n     \
    \       lazy[k] = id();\n        }\n        void push_to(int p) {\n          \
    \  p += m;\n            for (int i = lg; i >= 1; --i) push(p >> i);\n        }\n\
    \        void push_to(int l, int r) {\n            l += m, r += m;\n         \
    \   int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n            for (int i\
    \ = lg; i >= li + 1; --i) push(l >> i);\n            for (int i = lg; i >= ri\
    \ + 1; --i) push(r >> i);\n        }\n        void update(int k) {\n         \
    \   data[k] = op(data[2 * k], data[2 * k + 1]);\n        }\n        void update_from(int\
    \ p) {\n            p += m;\n            for (int i = 1; i <= lg; ++i) update(p\
    \ >> i);\n        }\n        void update_from(int l, int r) {\n            l +=\
    \ m, r += m;\n            int li = __builtin_ctz(l), ri = __builtin_ctz(r);\n\
    \            for (int i = li + 1; i <= lg; ++i) update(l >> i);\n            for\
    \ (int i = ri + 1; i <= lg; ++i) update(r >> i);\n        }\n    };\n}\n\n\n#line\
    \ 5 \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n    using SegmentTreeBeats = LazySegmentTree<T,\
    \ op, e, F, mapping, composition, id, /* enable_beats = */ true>;\n} // namespace\
    \ suisen\n\n\n#line 8 \"library/range_query/range_chmin_chmax_add_range_sum.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct RangeChMinMaxAddRangeSum\
    \ {\n        friend struct DataType;\n        struct DataType {\n            friend\
    \ struct RangeChMinMaxAddRangeSum;\n\n            bool fail = false;\n\n     \
    \       constexpr DataType() : lo(inf), lo2(inf), hi(-inf), hi2(-inf), sum(0),\
    \ siz(0), num_lo(0), num_hi(0) {}\n            constexpr DataType(T x, int num\
    \ = 1) : lo(x), lo2(inf), hi(x), hi2(-inf), sum(x * num), siz(num), num_lo(num),\
    \ num_hi(num) {}\n\n            T get_min() const { return lo; }\n           \
    \ T get_max() const { return hi; }\n            T get_second_min() const { return\
    \ lo2; }\n            T get_second_max() const { return hi2; }\n            T\
    \ get_min_num() const { return num_lo; }\n            T get_max_num() const {\
    \ return num_hi; }\n            T get_sum() const { return sum; }\n        private:\n\
    \            T lo, lo2, hi, hi2, sum;\n            int siz, num_lo, num_hi;\n\
    \        };\n\n        explicit RangeChMinMaxAddRangeSum(const int n = 0) : RangeChMinMaxAddRangeSum(std::vector<T>(n,\
    \ 0)) {}\n        RangeChMinMaxAddRangeSum(const std::vector<T> &init) {\n   \
    \         const int n = init.size();\n            std::vector<DataType> a(n);\n\
    \            for (int i = 0; i < n; ++i) {\n                a[i] = DataType{init[i]};\n\
    \            }\n            seg = SegmentTreeBeats<DataType, op, e, F, mapping,\
    \ composition, id>{ a };\n        }\n\n        void chmin(int l, int r, T val)\
    \ {\n            seg.apply(l, r, F::chmin_query(val));\n        }\n        void\
    \ chmax(int l, int r, T val) {\n            seg.apply(l, r, F::chmax_query(val));\n\
    \        }\n        void update(int l, int r, T val) {\n            seg.apply(l,\
    \ r, F::update_query(val));\n        }\n        void add(int l, int r, T val)\
    \ {\n            seg.apply(l, r, F::add_query(val));\n        }\n        T max(int\
    \ l, int r) {\n            return seg.prod(l, r).get_max();\n        }\n     \
    \   T min(int l, int r) {\n            return seg.prod(l, r).get_min();\n    \
    \    }\n        T sum(int l, int r) {\n            return seg.prod(l, r).get_sum();\n\
    \        }\n        DataType prod(int l, int r) {\n            return seg.prod(l,\
    \ r);\n        }\n        template <bool(*pred)(DataType)>\n        int max_right(int\
    \ l) {\n            return seg.max_right<pred>(l);\n        }\n        template\
    \ <typename Pred>\n        int max_right(int l, Pred &&pred) {\n            return\
    \ seg.max_right(l, std::forward<Pred>(pred));\n        }\n        template <bool(*pred)(DataType)>\n\
    \        int min_left(int r) {\n            return seg.min_left<pred>(r);\n  \
    \      }\n        template <typename Pred>\n        int min_left(int r, Pred &&pred)\
    \ {\n            return seg.min_left(r, std::forward<Pred>(pred));\n        }\n\
    \n    private:\n        static constexpr T inf = std::numeric_limits<T>::max()\
    \ / 2;\n\n        struct F {\n            T lb, ub, add;\n            constexpr\
    \ F(T lb = -inf, T ub = inf, T add = 0) : lb(lb), ub(ub), add(add) {}\n      \
    \      static constexpr F chmin_query(T x) { return F { -inf, x, 0 }; }\n    \
    \        static constexpr F chmax_query(T x) { return F { x, inf, 0 }; }\n   \
    \         static constexpr F update_query(T x) { return F { x, x, 0 }; }\n   \
    \         static constexpr F add_query(T x) { return F { -inf, inf, x }; }\n \
    \       };\n\n        static constexpr T second_lo(T lo11, T lo12, T lo21, T lo22)\
    \ {\n            if (lo11 == lo21) return std::min(lo12, lo22);\n            if\
    \ (lo12 <= lo21) return lo12;\n            if (lo22 <= lo11) return lo22;\n  \
    \          return std::max(lo11, lo21);\n        }\n        static constexpr T\
    \ second_hi(T hi11, T hi12, T hi21, T hi22) {\n            if (hi11 == hi21) return\
    \ std::max(hi12, hi22);\n            if (hi12 >= hi21) return hi12;\n        \
    \    if (hi22 >= hi11) return hi22;\n            return std::min(hi11, hi21);\n\
    \        }\n\n        static constexpr DataType op(DataType x, DataType y) {\n\
    \            DataType z{};\n            z.lo = std::min(x.lo, y.lo);\n       \
    \     z.hi = std::max(x.hi, y.hi);\n            z.lo2 = second_lo(x.lo, x.lo2,\
    \ y.lo, y.lo2);\n            z.hi2 = second_hi(x.hi, x.hi2, y.hi, y.hi2);\n  \
    \          z.sum = x.sum + y.sum;\n            z.siz = x.siz + y.siz;\n      \
    \      z.num_lo = (z.lo == x.lo) * x.num_lo + (z.lo == y.lo) * y.num_lo;\n   \
    \         z.num_hi = (z.hi == x.hi) * x.num_hi + (z.hi == y.hi) * y.num_hi;\n\
    \            return z;\n        }\n        static constexpr DataType e() {\n \
    \           return DataType{};\n        }\n    \n        static constexpr DataType\
    \ mapping(F f, DataType x) {\n            if (x.siz == 0) {\n                return\
    \ e();\n            } else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or\
    \ f.ub <= x.lo) {\n                return DataType { std::clamp(x.lo, f.lb, f.ub)\
    \ + f.add, x.siz };\n            } else if (x.lo2 == x.hi) { // 2\n          \
    \      x.lo = x.hi2 = std::max(x.lo, f.lb) + f.add;\n                x.hi = x.lo2\
    \ = std::min(x.hi, f.ub) + f.add;\n                x.sum = x.lo * x.num_lo + x.hi\
    \ * x.num_hi;\n                return x;\n            } else if (f.lb < x.lo2\
    \ and f.ub > x.hi2) { // >= 3\n                T nlo = std::max(x.lo, f.lb);\n\
    \                T nhi = std::min(x.hi, f.ub);\n                x.sum += (nlo\
    \ - x.lo) * x.num_lo + (nhi - x.hi) * x.num_hi + f.add * x.siz;\n            \
    \    x.lo = nlo + f.add;\n                x.hi = nhi + f.add;\n              \
    \  x.lo2 += f.add;\n                x.hi2 += f.add;\n                return x;\n\
    \            }\n            x.fail = true;\n            return x;\n        }\n\
    \        static constexpr F composition(F f, F g) {\n            F h;\n      \
    \      h.lb = std::clamp(g.lb + g.add, f.lb, f.ub) - g.add;\n            h.ub\
    \ = std::clamp(g.ub + g.add, f.lb, f.ub) - g.add;\n            h.add = f.add +\
    \ g.add;\n            return h;\n        }\n        static constexpr F id() {\n\
    \            return F{};\n        }\n    \n        SegmentTreeBeats<DataType,\
    \ op, e, F, mapping, composition, id> seg;\n    };\n} // namespace suisen\n\n\n\
    \n"
  code: "#ifndef SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM\n#define SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM\n\
    \n#include <algorithm>\n#include <limits>\n\n#include \"library/datastructure/segment_tree/segment_tree_beats.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct RangeChMinMaxAddRangeSum\
    \ {\n        friend struct DataType;\n        struct DataType {\n            friend\
    \ struct RangeChMinMaxAddRangeSum;\n\n            bool fail = false;\n\n     \
    \       constexpr DataType() : lo(inf), lo2(inf), hi(-inf), hi2(-inf), sum(0),\
    \ siz(0), num_lo(0), num_hi(0) {}\n            constexpr DataType(T x, int num\
    \ = 1) : lo(x), lo2(inf), hi(x), hi2(-inf), sum(x * num), siz(num), num_lo(num),\
    \ num_hi(num) {}\n\n            T get_min() const { return lo; }\n           \
    \ T get_max() const { return hi; }\n            T get_second_min() const { return\
    \ lo2; }\n            T get_second_max() const { return hi2; }\n            T\
    \ get_min_num() const { return num_lo; }\n            T get_max_num() const {\
    \ return num_hi; }\n            T get_sum() const { return sum; }\n        private:\n\
    \            T lo, lo2, hi, hi2, sum;\n            int siz, num_lo, num_hi;\n\
    \        };\n\n        explicit RangeChMinMaxAddRangeSum(const int n = 0) : RangeChMinMaxAddRangeSum(std::vector<T>(n,\
    \ 0)) {}\n        RangeChMinMaxAddRangeSum(const std::vector<T> &init) {\n   \
    \         const int n = init.size();\n            std::vector<DataType> a(n);\n\
    \            for (int i = 0; i < n; ++i) {\n                a[i] = DataType{init[i]};\n\
    \            }\n            seg = SegmentTreeBeats<DataType, op, e, F, mapping,\
    \ composition, id>{ a };\n        }\n\n        void chmin(int l, int r, T val)\
    \ {\n            seg.apply(l, r, F::chmin_query(val));\n        }\n        void\
    \ chmax(int l, int r, T val) {\n            seg.apply(l, r, F::chmax_query(val));\n\
    \        }\n        void update(int l, int r, T val) {\n            seg.apply(l,\
    \ r, F::update_query(val));\n        }\n        void add(int l, int r, T val)\
    \ {\n            seg.apply(l, r, F::add_query(val));\n        }\n        T max(int\
    \ l, int r) {\n            return seg.prod(l, r).get_max();\n        }\n     \
    \   T min(int l, int r) {\n            return seg.prod(l, r).get_min();\n    \
    \    }\n        T sum(int l, int r) {\n            return seg.prod(l, r).get_sum();\n\
    \        }\n        DataType prod(int l, int r) {\n            return seg.prod(l,\
    \ r);\n        }\n        template <bool(*pred)(DataType)>\n        int max_right(int\
    \ l) {\n            return seg.max_right<pred>(l);\n        }\n        template\
    \ <typename Pred>\n        int max_right(int l, Pred &&pred) {\n            return\
    \ seg.max_right(l, std::forward<Pred>(pred));\n        }\n        template <bool(*pred)(DataType)>\n\
    \        int min_left(int r) {\n            return seg.min_left<pred>(r);\n  \
    \      }\n        template <typename Pred>\n        int min_left(int r, Pred &&pred)\
    \ {\n            return seg.min_left(r, std::forward<Pred>(pred));\n        }\n\
    \n    private:\n        static constexpr T inf = std::numeric_limits<T>::max()\
    \ / 2;\n\n        struct F {\n            T lb, ub, add;\n            constexpr\
    \ F(T lb = -inf, T ub = inf, T add = 0) : lb(lb), ub(ub), add(add) {}\n      \
    \      static constexpr F chmin_query(T x) { return F { -inf, x, 0 }; }\n    \
    \        static constexpr F chmax_query(T x) { return F { x, inf, 0 }; }\n   \
    \         static constexpr F update_query(T x) { return F { x, x, 0 }; }\n   \
    \         static constexpr F add_query(T x) { return F { -inf, inf, x }; }\n \
    \       };\n\n        static constexpr T second_lo(T lo11, T lo12, T lo21, T lo22)\
    \ {\n            if (lo11 == lo21) return std::min(lo12, lo22);\n            if\
    \ (lo12 <= lo21) return lo12;\n            if (lo22 <= lo11) return lo22;\n  \
    \          return std::max(lo11, lo21);\n        }\n        static constexpr T\
    \ second_hi(T hi11, T hi12, T hi21, T hi22) {\n            if (hi11 == hi21) return\
    \ std::max(hi12, hi22);\n            if (hi12 >= hi21) return hi12;\n        \
    \    if (hi22 >= hi11) return hi22;\n            return std::min(hi11, hi21);\n\
    \        }\n\n        static constexpr DataType op(DataType x, DataType y) {\n\
    \            DataType z{};\n            z.lo = std::min(x.lo, y.lo);\n       \
    \     z.hi = std::max(x.hi, y.hi);\n            z.lo2 = second_lo(x.lo, x.lo2,\
    \ y.lo, y.lo2);\n            z.hi2 = second_hi(x.hi, x.hi2, y.hi, y.hi2);\n  \
    \          z.sum = x.sum + y.sum;\n            z.siz = x.siz + y.siz;\n      \
    \      z.num_lo = (z.lo == x.lo) * x.num_lo + (z.lo == y.lo) * y.num_lo;\n   \
    \         z.num_hi = (z.hi == x.hi) * x.num_hi + (z.hi == y.hi) * y.num_hi;\n\
    \            return z;\n        }\n        static constexpr DataType e() {\n \
    \           return DataType{};\n        }\n    \n        static constexpr DataType\
    \ mapping(F f, DataType x) {\n            if (x.siz == 0) {\n                return\
    \ e();\n            } else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or\
    \ f.ub <= x.lo) {\n                return DataType { std::clamp(x.lo, f.lb, f.ub)\
    \ + f.add, x.siz };\n            } else if (x.lo2 == x.hi) { // 2\n          \
    \      x.lo = x.hi2 = std::max(x.lo, f.lb) + f.add;\n                x.hi = x.lo2\
    \ = std::min(x.hi, f.ub) + f.add;\n                x.sum = x.lo * x.num_lo + x.hi\
    \ * x.num_hi;\n                return x;\n            } else if (f.lb < x.lo2\
    \ and f.ub > x.hi2) { // >= 3\n                T nlo = std::max(x.lo, f.lb);\n\
    \                T nhi = std::min(x.hi, f.ub);\n                x.sum += (nlo\
    \ - x.lo) * x.num_lo + (nhi - x.hi) * x.num_hi + f.add * x.siz;\n            \
    \    x.lo = nlo + f.add;\n                x.hi = nhi + f.add;\n              \
    \  x.lo2 += f.add;\n                x.hi2 += f.add;\n                return x;\n\
    \            }\n            x.fail = true;\n            return x;\n        }\n\
    \        static constexpr F composition(F f, F g) {\n            F h;\n      \
    \      h.lb = std::clamp(g.lb + g.add, f.lb, f.ub) - g.add;\n            h.ub\
    \ = std::clamp(g.ub + g.add, f.lb, f.ub) - g.add;\n            h.add = f.add +\
    \ g.add;\n            return h;\n        }\n        static constexpr F id() {\n\
    \            return F{};\n        }\n    \n        SegmentTreeBeats<DataType,\
    \ op, e, F, mapping, composition, id> seg;\n    };\n} // namespace suisen\n\n\n\
    #endif // SUISEN_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM\n"
  dependsOn:
  - library/datastructure/segment_tree/segment_tree_beats.hpp
  - library/datastructure/segment_tree/lazy_segment_tree.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/range_query/range_chmin_chmax_add_range_sum.hpp
  requiredBy: []
  timestamp: '2024-01-30 22:07:01+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/range_query/range_chmin_chmax_add_range_sum/range_chmin_chmax_add_range_sum.test.cpp
documentation_of: library/range_query/range_chmin_chmax_add_range_sum.hpp
layout: document
title: Range Chmin Chmax Add Range Sum
---
## Range Chmin Chmax Add Range Sum
